/*
 * Definerer en block i spillet. Dette er et synlig element som f.eks. gulv, vegg, trapp.
*/

#ifndef BLOCK_HPP
#define BLOCK_HPP
#include "clickable.hpp"
#include <string>

class block:public clickable{
    int ACCESS_;
public:
    block(char icon, std::string info, int x, int y, const int ACCESS);
    int access() override; /*hva skjer når spiller er på dette området? Returnerer en int konstant*/
    action_call left_click() override;//hva skal skje når dette området trykkes på
    virtual ~block(){}
};
#endif
