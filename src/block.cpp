#include "block.hpp"

block::block(char ikon, std::string info, int x, int y, const int ACCESS):clickable(ikon, info, x, y), ACCESS_{ACCESS}{}

int block::access(){
    return ACCESS_;
}
action_call block::left_click(){
    return clickable::NO_ACTION;
}
