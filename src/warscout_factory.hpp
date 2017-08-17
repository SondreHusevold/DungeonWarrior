/*
 * Monster factory lager et monster
*/
#ifndef WARSCOUT_FACTORY_HPP
#define WARSCOUT_FACTORY_HPP
#include "abstract_monster_factory.hpp"

class warscout_factory:public abstract_monster_factory{
	int difficulty_;
public:
	warscout_factory(int difficulty);
    monster* create_monster() override;

};
#endif
