/*
 * Har ansvar for et spill, har levelene og spiller. Sørger for å utføre riktig handling for input og kaller riktige metoder for level og spiller
*/

#ifndef GAME_HPP
#define GAME_HPP
#include "level.hpp"
#include "player.hpp"
#include "reportable.hpp"

class game:public reportable{
    player* player_;
	std::vector<level*> levels_;
	level* current_level_;//nåværende level peker
    unsigned int current_;//nåværende level nummer
	void init();//initialsiering metode
public:
	game(std::string player_name);
	game(player* player);
	game(game& g);
	game(game&& g);
	game& operator=(const game& g);
	game& operator=(game&& g);
	void turn();//skal kalles etter hver action som attack, bevegelse, osv.
    void next_level();//Gå til neste level
    void prev_level();//Gå til forrige level, ikke i bruk
    player* get_player();//returnerer player.
    void left_click_action(clickable* left_click_object);//utfører instruction på clickable element
    void move_player(int x, int y);//fytter player x i x retning og y i y retning hvis dette ender i en gyldig posisjon
	clickable* get_element(int x, int y);//bruker level sin get_element()
	block* get_block(int x, int y);//bruker level sin get_block()
	monster* get_monster(int i);//bruker level sin get_monster()
	~game();

};
#endif
