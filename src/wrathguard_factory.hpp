/*
 * Monster factory lager et monster
*/
#ifndef WRATHGUARD_FACTORY_HPP
#define WRATHGUARD_FACTORY_HPP
#include "abstract_monster_factory.hpp"

class wrathguard_factory:public abstract_monster_factory{
	int difficulty_;
public:
	wrathguard_factory(int difficulty);
    monster* create_monster() override ;

};
#endif
