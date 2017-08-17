/*
 * Representerer en level. Lager en labyrint av blocker og plasserer monstere i denne. Tar seg av kontrollen av monstere.
*/

#ifndef LEVEL_HPP
#define LEVEL_HPP
#include "block.hpp"
#include "player.hpp"
#include "monster.hpp"
#include "abstract_monster_factory.hpp"

class level:public reportable{
    std::vector<block*> blocks_;//blockene labyrinten består av
    block* null_block_;//standard block for udefinert område
    std::vector<monster*> monsters_;//alle monstere på denne levlen
    abstract_monster_factory* mf_;//monster factory
    creature* player_;//spiller, nødvendig for å plassere monstere i forhold til player
	void create_road(std::vector<std::vector<int>> &map, int x, int y);//lager veier gjennom map
	void position_monsters(std::vector<std::vector<int>> &map, int x, int y);//recursive metode for å plassere ut monstere.
	void position_monsters(std::vector<std::vector<int>> &map);//starter recursive metode.
	void create_blocks(std::vector<std::vector<int>> &map);//lage blokker etter map
	void init();//initialisering metode
    void follow_player(monster* monster);//monster følger etter player
    void walk_random(monster* monster);//monster beveger seg tilfeldig

public:
    static const int MAX_POSITION_X=100;
    static const int MAX_POSITION_Y=100;
	static const int ATTACK_RANGE=1;
    static const int COMBAT_RAMGE=3;

    level(creature *player, abstract_monster_factory* mf);
    level(const level& l);
    level(level&& l);

    level& operator=(const level& l);
    level& operator=(level&& l);
	//mulig konstruktør som tar en bitmap som beskriver labyrinten. Kan være nyttig for utvidbarhet.
	void turn();//flytte monstere/attacke
	void visible_blocks(int x, int y, const int RANGE);//setter alle blockene i området +- RANGE rundt player til synlig.
	void add_monster(int x, int y);
    bool valid_block_position(int x, int y);//gyldig posisjon for en block
    bool valid_monster_position(int x, int y);//gyldig posisjon for monster
	bool valid_position(int x, int y);//tester om det er mulig å bevege seg til posisjon x, y. Test før creature flyttes, ikke etter.
	static bool valid_range(creature &a, creature &b, const int RANGE);//in range?
	clickable* get_element(int x, int y);//returnerer det som er "øverst" på posisjon x, y. monster>block
    block* get_block(int x, int y);//returnerer block på posisjon (x, y)
    monster* get_monster(unsigned int i);//returnerer monster på plass i i monsters_, nyttig hvis det skal itereres over monstere
	std::vector<std::vector<int>> create_bitmap(const int X, const int Y);//gir en x*y int array
	~level();
};

#endif
