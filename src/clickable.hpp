/*
 * Base klasse for elementer som kan trykkes på. Garanterer en action_call left_click() metode.
*/
#ifndef CLICKABLE_HPP
#define CLICKABLE_HPP
#include "visible.hpp"

typedef int action_call;

class clickable:public visible{

public:
    //action konstanter
    static const action_call ATTACK=1;
    static const action_call LOOT=2;
    static const action_call NO_ACTION=3;

    clickable(char icon, std::string info, int x, int y);
    virtual action_call left_click()=0;
    virtual ~clickable(){}
};

#endif
