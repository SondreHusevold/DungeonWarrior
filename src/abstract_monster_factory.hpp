/*
 * Base klasse for monster factorier.
*/

#ifndef ABSTRACT_MONSTER_FACTORY_HPP
#define ABSTRACT_MONSTER_FACTORY_HPP
#include "monster.hpp"
class abstract_monster_factory{
public:
    const double STAMINA_PR_LEVEL=0.3;//hvor mye skal de ulike statsene øke med per level
    const double POWER_PR_LEVEL=0.3;
    const double ARMOR_PR_LEVEL=0.1;
    abstract_monster_factory& operator=(const abstract_monster_factory&){
    	return *this;}
    abstract_monster_factory& operator=(const abstract_monster_factory&&){
        return *this;}/*copy og move assign operator må være med for const medlemene.*/
    virtual monster* create_monster()=0;//returnerer en monster pointer.
	virtual ~abstract_monster_factory(){}
};
#endif
