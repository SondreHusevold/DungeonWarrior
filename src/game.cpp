#include "game.hpp"
#include "monster_factory.hpp"
#include <stdexcept>
#include "gui_handler.hpp"//må være med her for å kalle gui_handler::redraw()

const int LOOK_RANGE=6;//hvor mange blocker skal være synlig rundt player.
const int PASSIVE_HEAL_PRC=2;//hvor mange prosent av maks hp skal passivt heales hver turn når spiller ikke er i combat
game::game(std::string player_name):current_{0}{
    player_=new player(player_name, '@', "Spiller", level::MAX_POSITION_X/2, level::MAX_POSITION_Y/2);
	player_->set_visible(true);
	init();
}
game::game(player* player):current_{0}{
    player_ = player;
	init();
}
game::game(game& g):player_{g.player_}, current_level_{g.current_level_}, current_{g.current_}{
    for(unsigned int i=0; i<g.levels_.size(); i++)
        levels_.push_back(new level(*g.levels_[i]));

}
game::game(game&& g):player_{g.player_}, current_level_{g.current_level_}, current_{g.current_}{
    g.player_=nullptr;
    g.current_level_=nullptr;
    g.current_=0;
    for(unsigned int i=0; i<g.levels_.size(); i++){
        levels_.push_back(g.levels_[i]);
        g.levels_[i]=nullptr;
    }
    g.levels_.clear();
}
game& game::operator=(const game& g){
    if(&g==this)
        return *this;
    *player_=*g.player_;
    for(unsigned int i=0; i<g.levels_.size(); i++)
        levels_.push_back(new level(*g.levels_[i]));
    *current_level_=*g.current_level_;
    current_=g.current_;
    return *this;
}
game& game::operator=(game&& g){
    if(&g==this)
        return *this;
    player_=g.player_;
    for(unsigned int i=0; i<g.levels_.size(); i++){
        levels_.push_back(g.levels_[i]);
        g.levels_[i]=nullptr;
    }
    current_level_=g.current_level_;
    current_=g.current_;
    g.current_level_=nullptr;
    g.current_=0;
    return *this;
}
void game::init(){
    srand((unsigned)time(NULL));//seed for rand()
    current_level_=new level(player_, new monster_factory(current_));//oppretter level med factory
    //current_level_=new level(player_, new monster_factory(1));//oppretter level med factory
    levels_.push_back(current_level_);
    current_level_->visible_blocks(player_->x(), player_->y(), LOOK_RANGE);//gjør elementene rundt player synlige
}
void game::turn(){
	if(!current_level_->valid_position(player_->x(), player_->y()))//tester at spiller ikke er på en ugyldig posisjon
		throw(std::runtime_error("player sin posisjon er feil. Kastet av game::turn()"));
    const int ACTION=current_level_->get_block(player_->x(), player_->y())->access();//tester om spiller står på en posisjon med en action
    if(ACTION==visible::NO_ACTION)
        current_level_->turn();
    else if(ACTION==visible::NEXT_LEVEL)
		next_level();
	else if(ACTION==visible::PREV_LEVEL)
		prev_level();
	current_level_->visible_blocks(player_->x(), player_->y(), LOOK_RANGE);//gjør elementene rundt player synlige
    report(player_->get_report());//oppdaterer raport med player.raport
    report(current_level_->get_report());
    if(player_->dead()){// Is the player dead after this action?
        player_->set_info("Your corpse.");
        report("You are dead.");
        gui_handler::you_died();
    }
    gui_handler::update_hp_bar();
    gui_handler::redraw();//tegner endringer
}
void game::move_player(int x, int y){
    if(player_->dead()){
        return;
    }
	if(current_level_->valid_position(player_->x()+x, player_->y()+y)){//tester om ny posisjon er gyldig
		player_->move(x, y);
        if(!player_->in_combat())//passive heal hvis player ikke er i combat
            player_->heal((int)(player_->get_stamina()+player_->get_base_stamina())/100*PASSIVE_HEAL_PRC);
		turn();
	}
}
void game::next_level(){
    if(current_==levels_.size()-1){//hvis neste level ikke er opprettet
		current_level_=new level(player_, new monster_factory(++current_));
		levels_.push_back(current_level_);
	}
	else
		current_level_=levels_[++current_];
}
void game::prev_level(){//ikke i bruk
    if(current_==0)//hvis player er på første level
		return;
	current_level_=levels_[--current_];

}

void game::left_click_action(clickable* left_click_object){//element trykket på
    if(left_click_object->left_click() == clickable::ATTACK){//hvis elementet skal angripes
        player_->target(((monster*)left_click_object));//sette element som player.target
        bool attacked = player_->attack();//prøve å angripe
        if(attacked)//hvis angrepet ble utført
            turn();
    }
    else if(left_click_object->left_click() == clickable::LOOT){//hvis elementet skal lootes
        std::vector<item*> items=((monster*)left_click_object)->get_loot();//hente ut monstere sine items
        for(unsigned int i=0; i<items.size(); i++)//gå gjennom items
            if(player_->add_item(new item(*items[i]))){//legge til en kopi av itemet i player sin inventory hvis det ikke er der fra før av
                std::stringstream streamer;
                //skrive til raport
                streamer<<"You looted: "<<items[i]->to_string();
                report(streamer.str());
                //std::string temp=(items[i]->to_string());
                //gui_handler::report_to_log(streamer.str());
                gui_handler::check_current_inventory();//finne på noe her når inventory er ferdig
            }
        turn();
    }
    else if(left_click_object->left_click()==clickable::NO_ACTION){
        //no action
    }
    report(player_->get_report());
}
player* game::get_player(){
	return player_;
}
clickable* game::get_element(int x, int y){
	return current_level_->get_element(x, y);
}
block* game::get_block(int x, int y){
	return current_level_->get_block(x, y);
}
monster* game::get_monster(int i){
	return current_level_->get_monster(i);
}
game::~game(){
    current_level_=nullptr;
    for(unsigned int i=0; i<levels_.size(); i++)
		delete levels_[i];
    delete player_;
}
