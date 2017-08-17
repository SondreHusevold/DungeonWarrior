/*
 * Monster factory lager boss monstere
*/
#ifndef MONOROTH_FACTORY_HPP
#define MONOROTH_FACTORY_HPP
#include "abstract_monster_factory.hpp"

class monoroth_factory:public abstract_monster_factory{
	int difficulty_;
public:
	monoroth_factory(int difficulty);
    monster* create_monster() override;

};
#endif
