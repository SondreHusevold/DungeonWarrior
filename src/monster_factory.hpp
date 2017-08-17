#ifndef MONSTER_FAACTORY_HPP
#define MONSTER_FAACTORY_HPP
#include "abstract_monster_factory.hpp"

class monster_factory:public abstract_monster_factory{

	int difficulty_;
	bool boss_spawned_;
	std::vector<abstract_monster_factory*> mobs_;
	std::vector<abstract_monster_factory*> bosses_;
public:
	monster_factory(int difficulty);
    monster_factory(const monster_factory& mf);
    monster_factory(monster_factory&& mf);
    monster_factory& operator=(const monster_factory& mf);
    monster_factory& operator=(monster_factory&& mf);
	monster* create_monster() override;
	~monster_factory();

};

#endif
