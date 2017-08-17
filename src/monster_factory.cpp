#include "monster_factory.hpp"
#include "monoroth_factory.hpp"
#include "warlord_factory.hpp"
#include "deathwing_factory.hpp"
#include "warscout_factory.hpp"
#include "wyrmguard_factory.hpp"
#include "warrior_factory.hpp"
#include "wrathguard_factory.hpp"

monster_factory::monster_factory(int difficulty):difficulty_{difficulty}, boss_spawned_{false}{
	//legge monstere inn i array
	mobs_.push_back(new warscout_factory(difficulty_));
	mobs_.push_back(new wyrmguard_factory(difficulty_));
    mobs_.push_back(new warrior_factory(difficulty_));
	mobs_.push_back(new wrathguard_factory(difficulty_));
	//legge bosser i array
	bosses_.push_back(new deathwing_factory(difficulty_));
	bosses_.push_back(new warlord_factory(difficulty_));
	bosses_.push_back(new monoroth_factory(difficulty_));

}
monster_factory::monster_factory(const monster_factory& mf):difficulty_{mf.difficulty_}, boss_spawned_{mf.boss_spawned_}{
    mobs_=mf.mobs_;//vil dette fungere?
    bosses_=mf.bosses_;

}
monster_factory::monster_factory(monster_factory&& mf){
    for(unsigned int i=0; i<mf.mobs_.size(); i++){
        mobs_.push_back(mf.mobs_[i]);
        mf.mobs_[i]=nullptr;
    }
    for(unsigned int i=0; i<mf.bosses_.size(); i++){
        bosses_.push_back(mf.bosses_[i]);
        mf.bosses_[i]=nullptr;
    }
    mf.mobs_.clear();
    mf.bosses_.clear();
}
monster_factory& monster_factory::operator=(const monster_factory& mf){
    if(&mf==this)
        return *this;
    mobs_.clear();
    bosses_.clear();

    mobs_=mf.mobs_;//vil dette fungere?
    bosses_=mf.bosses_;
    return *this;
}
monster_factory& monster_factory::operator=(monster_factory&& mf){
    if(&mf==this)
        return *this;
    for(unsigned int i=0; i<mf.mobs_.size(); i++){
        mobs_.push_back(mf.mobs_[i]);
        mf.mobs_[i]=nullptr;
    }
    for(unsigned int i=0; i<mf.bosses_.size(); i++){
        bosses_.push_back(mf.bosses_[i]);
        mf.bosses_[i]=nullptr;
    }
    mf.mobs_.clear();
    mf.bosses_.clear();
    return *this;
}

monster* monster_factory::create_monster(){
    monster* temp;
    int i=0;
    if(!boss_spawned_ && rand()%10==0){//10% sansynlighet for å spawne en boss hvis den enda ikke har spawnet
        i=rand()%bosses_.size();
        temp=bosses_[i]->create_monster();//et tilfeldig boss
        boss_spawned_=true;
	}
	else{
        i=rand()%mobs_.size();
        temp=mobs_[i]->create_monster();//et tilfeldig monster
    }
    return temp;
}
monster_factory::~monster_factory(){
    for(unsigned int i=0; i<mobs_.size(); i++)
		delete mobs_[i];
    for(unsigned int i=0; i<bosses_.size(); i++)
		delete bosses_[i];
}
