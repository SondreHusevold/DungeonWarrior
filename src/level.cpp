#include "level.hpp"
#include <stdexcept>
#include <math.h>

const int BRICK=0;
const int FLOOR=1;
const int SEEN=2;
const int STAIR_DOWN=3;
const int STAIR_UP=4;
const int ESCAPE_CHANCE=20;//1/ESCAPE_CHANCE=sansynlighet for å slippe fra monster, litt missvisende navn
const int MONSER_CHANCE=50;//høyre tall gir færre monstere.

level::level(creature* player, abstract_monster_factory* mf):mf_{mf}, player_{player}{
	init();
}
level::level(const level& l){
    *mf_=*l.mf_;
    *player_=*l.player_;
    *null_block_=*l.null_block_;
    for(unsigned int i=0; i<l.blocks_.size(); i++)
		blocks_.push_back(new block(*l.blocks_[i]));
    for(unsigned int i=0; i<l.monsters_.size(); i++)
		monsters_.push_back(new monster(*l.monsters_[i]));

}
level::level(level&& l):null_block_{l.null_block_}, mf_{l.mf_}, player_{l.player_}{
	l.mf_=nullptr;
	for(unsigned int i=0; i<l.blocks_.size(); i++){
		blocks_.push_back(l.blocks_[i]);
		l.blocks_[i]=nullptr;
	}
	for(unsigned int i=0; i<l.monsters_.size(); i++){
		monsters_.push_back(l.monsters_[i]);
		l.monsters_[i]=nullptr;
	}
	l.blocks_.clear();
	l.monsters_.clear();
}
level& level::operator=(const level& l){
	if(&l==this)
		return *this;
    *mf_=*l.mf_;
	*player_=*l.player_;
	*null_block_=*l.null_block_;
	for(unsigned int i=0; i<l.blocks_.size(); i++)
		blocks_.push_back(new block(*l.blocks_[i]));
	for(unsigned int i=0; i<l.monsters_.size(); i++)
		monsters_.push_back(new monster(*l.monsters_[i]));
    return *this;
}
level& level::operator=(level&& l){
	if(&l==this)
        return *this;
    mf_=l.mf_;
	player_=l.player_;
	null_block_=l.null_block_;
	for(unsigned int i=0; i<l.blocks_.size(); i++){
		blocks_.push_back(l.blocks_[i]);
		l.blocks_[i]=nullptr;
	}
	for(unsigned int i=0; i<l.monsters_.size(); i++){
		monsters_.push_back(l.monsters_[i]);
		l.monsters_[i]=nullptr;
	}
	l.mf_=nullptr;
	l.player_=nullptr;
	l.null_block_=nullptr;
    return *this;
}
void level::init(){
    std::vector<std::vector<int>> map = create_bitmap(MAX_POSITION_X+1, MAX_POSITION_Y+1);//lage kartet labyrinten skal tegnes på
    for(int i=0; i<2; i++)//lage veier gjennom labyrinten
        create_road(map, player_->x(), player_->y());
    create_blocks(map);//lage selve labyrinten
    position_monsters(map);//sette ut monstere
    null_block_=new block('b', "Tomt område", -1, -1, visible::NO_ACTION);//nullblock for void området(området rund labyrinten)
}
void level::turn(){
	bool player_combat=false;
    for(unsigned int i=0; i<monsters_.size(); i++){//går gjennom alle monstere
        if(monsters_[i]->dead());//hopper over monsteret hvis det er dødt
        else if(monsters_[i]->range()){//attack() hvis monsteret er nærme nok
            monsters_[i]->attack();
			player_combat=true;
		}
        else if(monsters_[i]->in_combat()){//følger etter spiller hvis monsteret er i combat
			player_combat=true;
			follow_player(monsters_[i]);
		}
        else if(valid_range(*monsters_[i], *player_, COMBAT_RAMGE)){//setter monster til combat hvis det kan "se" player
			player_combat=true;
			monsters_[i]->set_combat(true);
			monsters_[i]->target(player_);
			follow_player(monsters_[i]);
		}
		else{//gå i random retning/eventuelt stå stille
			walk_random(monsters_[i]);
		}//end else
        report(monsters_[i]->get_report());//henter ut raporten til monsteret
	}//end for
	player_->set_combat(player_combat);
}//end turn
void level::walk_random(monster* monster){
    //+-1 i x eller y retning
	int x=rand()%3-1;
	int y=0;
	if(x==0)
		y=rand()%3-1;
    if(valid_monster_position(monster->x()+x, monster->y()+y))//tester om ny posisjon er gyldig
		monster->move(x, y);
}
void level::follow_player(monster* monster){
    int x=(player_->x()-monster->x());//differanse i x retning
    int y=(player_->y()-monster->y());//differanse i y retning
	int escape=rand()%ESCAPE_CHANCE;
	if(escape==0){//slipper unna, monster går andre veien hvis mulig.
		x=x*-1;
		y=y*-1;
		monster->set_combat(false);
	}
    if(x>0)//ikke "pen" kode, men finner ingen bedre løsning her, sørger for at absolutt verdien til x og y ikke er over 1
		x=1;
	if(x<0)
		x=-1;
	if(y>0)
		y=1;
	if(y<0)
		y=-1;
    if(!(x==0) && valid_monster_position(monster->x()+x, monster->y()))//flytter monstere en block i x eller y retning slik at det følger etter player
		monster->move(x, 0);
    else if(!(y==0) && valid_monster_position(monster->x(), monster->y()+y))
		monster->move(0, y);
}
void level::visible_blocks(int x, int y, const int RANGE){
	for(int i=x-RANGE; i<x+RANGE; i++)
		for(int j=y-RANGE; j<y+RANGE; j++){
			get_block(i, j)->set_visible(true);
			get_element(i, j)->set_visible(true);//hvis det er et monster på denne posisjonen
		}


}
void level::create_blocks(std::vector<std::vector<int>> &map){
	if(!map.size()-1==MAX_POSITION_X && !map[0].size()-1==MAX_POSITION_Y)
		throw(std::runtime_error("bitmapet har feil dimensjoner, kastet av create_blocks()"));
    bool stair=false;
	for(int x=0; x<=MAX_POSITION_X; x++){
		for(int y=0; y<=MAX_POSITION_Y; y++){//går gjennom map
			if(map[x][y]==BRICK)
                blocks_.push_back(new block(visible::WALL, "You see a wall.", x, y, visible::NO_ACTION));
            else if(map[x][y]==STAIR_DOWN && !stair){//hvis det skal være en trapp ned her, og det ikke finnes en trapp ned fra før
                block* temp=new block(visible::STAIR_DOWN, "You see a staircase going downwards.", x, y, visible::NEXT_LEVEL);
				temp->set_accessable(true);
				blocks_.push_back(temp);
				stair=true;
			}
            /*else if(map[x][y]==STAIR_UP && !stair){//kan brukes hvis ønskelig. Deaktivert i dette spillet, men har den for utvidbarhet
                block* temp=new block(visible::STAIR_UP, "Trapp OPP", x, y, visible::PREV_LEVEL);
				temp->set_accessable(true);
				blocks_.push_back(temp);
				stair=true;
			}*/
			else{
                block* temp=new block(visible::FLOOR, "You look at the floor.", x, y, visible::NO_ACTION);
				temp->set_accessable(true);
				blocks_.push_back(temp);
			}//end if else
		}//end for y
	}//end for x
}
std::vector<std::vector<int>> level::create_bitmap(const int X, const int Y){//burde kanskje hete int_map
	/*Sette opp kartet med riktige dimensjoner og start verdier*/
    std::vector<std::vector<int>> map;
    map.resize(X);//setter X til høyeste posisjon for x
    for(int i=0; i<X; i++){
        map[i].resize(Y);//setter Y som høyeste posisjon for y
        for(int j=0; j<Y; j++)
            map[i][j]=BRICK;//startverdi
    }
	return map;
}
void level::create_road(std::vector<std::vector<int>> &map, int x, int y){
	if(!valid_block_position(x, y))
		throw(std::runtime_error("x eller y ligger utenfor definert område, kastet av create_road()"));
	if(!map.size()-1==MAX_POSITION_X && !map[0].size()-1==MAX_POSITION_Y)
		throw(std::runtime_error("bitmapet har feil dimensjoner, kastet av create_road()"));
	int md=rand()%4;
    map[x][y]=STAIR_UP;//tilbake til forrige level
	for(int i=0; i<(MAX_POSITION_X+MAX_POSITION_Y)*10; i++){//gir passe veier/vegg fordeling
		int d=rand()%12;//12 gir best balangse mellom svinger og rette veier. For høy eller lav verdi gjør at labyrinten "klumper" seg med store rom.
		if(d>5)//fortsette samme vei
			d=md;
		int temp_x=x;
		int temp_y=y;
		if(d==0)//
			y--;
		if(d==1)
			y++;
		if(d==2)
			x++;
		if(d==3)
			x--;
		if(d==4)
			md=rand()%4;
        if(x<1 || x>MAX_POSITION_X-1 || y<1 || y>MAX_POSITION_Y-1){//sørge for at det blir en ramme med vegg-blocker rundt labyrinten.
			x=temp_x;
			y=temp_y;
			md=rand()%4;
		}//end if
		map[x][y]=FLOOR;
	}//end for
	map[x][y]=STAIR_DOWN;//legger inn en trapp der løkken ender.
}
void level::position_monsters(std::vector<std::vector<int>> &map){
	int x=player_->x();
	int y=player_->y();
    map[x][y]=SEEN;
    //sikrer at monster ikke starter på spiller. Bedre enn å kalle position_monsters(map, x, y) og teste om x==player->x()&&y==player->y() i den recursive metoden.
	position_monsters(map, x+1, y);
	position_monsters(map, x-1, y);
	position_monsters(map, x, y+1);
	position_monsters(map, x, y-1);
}
void level::position_monsters(std::vector<std::vector<int>> &map, int x, int y){
	if(!valid_block_position(x, y)||map[x][y]==BRICK)
		return;
	if(map[x][y]!=FLOOR)
		return;
	map[x][y]=SEEN;
	int add=rand()%(MONSER_CHANCE);
	if(add==0)//plassere monster her hvis add==0
		add_monster(x, y);

	position_monsters(map, x+1, y);
	position_monsters(map, x-1, y);
	position_monsters(map, x, y+1);
	position_monsters(map, x, y-1);
}
void level::add_monster(int x, int y){//setter et monster på posisjon x, y.
	if(!valid_position(x, y))
        throw(std::runtime_error("Ugyldig posisjon for monster, kastet av add_monster()"));
    monster* temp=mf_->create_monster();
    temp->set_x(x);
    temp->set_y(y);
    monsters_.push_back(temp);
}
clickable* level::get_element(int x, int y){
    for(unsigned int i=0; i<monsters_.size(); i++)//tester om det er et monster på denne posisjonen
        if(monsters_[i]->x()==x && monsters_[i]->y()==y)
            return monsters_[i];
	return get_block(x, y);
}
block* level::get_block(int x, int y){
	if(!valid_block_position(x, y))//returnerer standard void blocken hvis (x, y) er utenfor labyrinten.
		return null_block_;
	return blocks_[(x*(MAX_POSITION_Y+1))+y];
}
monster* level::get_monster(unsigned int i){
	if(i>=monsters_.size())
		return nullptr;
	return monsters_[i];
}

bool level::valid_block_position(int x, int y){
	if(x<0 || x>MAX_POSITION_X || y<0 || y>MAX_POSITION_Y)
		return false;
	return true;
}
bool level::valid_monster_position(int x, int y){
    if((player_->x()==x && player_->y()==y) || get_element(x, y)->access()!=visible::NO_ACTION)//monster går ikke på trapper, eller player
		return false;
	return valid_position(x, y);
}
bool level::valid_position(int x, int y){
	if(!valid_block_position(x, y))
		return false;
	if(get_element(x, y)->is_accessable())
		return true;
    return false;
}
bool level::valid_range(creature &a, creature &b, const int RANGE){//tester om a og b er in range, dvs. kan angripe hverandre
    int ax=a.x();
    int ay=a.y();
    int bx=b.x();
    int by=b.y();
	int dist=sqrt( (ax-bx)*(ax-bx)+(ay-by)*(ay-by) );//absoluttverdien til avstanden mellom a og b
	return dist<=RANGE;
}

level::~level(){
    for(unsigned int i=0; i<blocks_.size(); i++)
        delete blocks_[i];
    for(unsigned int i=0; i<monsters_.size(); i++)
		delete monsters_[i];
	delete null_block_;
    delete mf_;
}
