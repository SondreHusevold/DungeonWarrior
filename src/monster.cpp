#include "monster.hpp"

monster::monster(std::string name_, char icon, std::string information, int x, int y) : creature(name_, icon, information, x, y), looted_{false}{

}

std::vector<item*> monster::get_loot(){
    std::vector<item*> loot;                                // All the loot it dropped.

    if(looted_)
        return loot;
    for(item* anitem : get_items()){                        // Goes through the monster's inventory.
        if(anitem->drop()){                                 // Checks if the item dropped.
            loot.push_back(anitem);                         // If it did, then add to the vector.
        }
    }
    looted_=true;
    set_icon(visible::SKELETON);
    return loot;                                            // Returns with all the loot.
}

bool monster::dead(){
    if(creature::dead()){
        if(!looted_){
            set_icon(visible::LOOTABLE);                    // Make the creature into a loot icon.
        }
        else{
            set_icon(visible::SKELETON);
        }
        return true;
    }
    return false;
}

action_call monster::left_click(){
    if(dead())
        return LOOT;
    return ATTACK;
}

monster::~monster(){

}
