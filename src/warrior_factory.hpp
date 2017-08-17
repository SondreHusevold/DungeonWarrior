/*
 * Monster factory lager et monster
*/
#ifndef WARRIOR_FACTORY_HPP
#define WARRIOR_FACTORY_HPP
#include "abstract_monster_factory.hpp"

class warrior_factory:public abstract_monster_factory{
	int difficulty_;
public:
	warrior_factory(int difficulty);
    monster* create_monster() override;

};
#endif
