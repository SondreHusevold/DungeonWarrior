/*
 * Monster factory lager boss monstere
*/

#ifndef DEATHWING_FACTORY_HPP
#define DEATHWING_FACTORY_HPP
#include "abstract_monster_factory.hpp"

class deathwing_factory:public abstract_monster_factory{
	int difficulty_;
public:
	deathwing_factory(int difficulty);
    monster* create_monster() override;

};
#endif
