#ifndef MONSTER
#define MONSTER
#include "creature.hpp"
#include <vector>

class monster : public creature{
    bool looted_;                                                                       // Is the creature looted?
public:
    monster(std::string name, char icon, std::string information, int x, int y);        // Constructor - Most of this is added directly to creature's constructor.
    std::vector<item*> get_loot();                                                      // Get loot from monster
    action_call left_click() override;                                                  // What happens on left click.
    bool dead() override;                                                               // When dead, give loot and show skeleton.
    virtual ~monster();                                                                 // Destructor
};

#endif // MONSTER

