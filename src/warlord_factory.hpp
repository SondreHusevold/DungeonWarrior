/*
 * Monster factory lager boss monstere
*/
#ifndef WARLORD_FACTORY_HPP
#define WARLORD_FACTORY_HPP
#include "abstract_monster_factory.hpp"

class warlord_factory:public abstract_monster_factory{
	int difficulty_;
public:
	warlord_factory(int difficulty);
    monster* create_monster() override;

};
#endif
