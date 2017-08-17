/*
 * Monster factory lager et monster
*/
#ifndef WYRMGUARD_FACTORY_HPP
#define WYRMGUARD_FACTORY_HPP
#include "abstract_monster_factory.hpp"

class wyrmguard_factory:public abstract_monster_factory{
	int difficulty_;
public:
	wyrmguard_factory(int difficulty);
    monster* create_monster() override;

};
#endif
