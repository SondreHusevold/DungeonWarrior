#ifndef PLAYER
#define PLAYER
#include "creature.hpp"
#include <QObject>

class player : public creature {

public:
    player(std::string _name, char icon_, std::string information_, int x_, int y_);        // Most of this goes directly to creature's constructor.
    player(const player& p);                                                                // Copy-constructor
    player(player&& c);                                                                     // Move-constructor
    player& operator=(const player& p);                                                     // Copy-assign constructor
    player& operator=(player&& p);                                                          // Move-assign constructor
    std::string to_string() override;                                                       // Describe the player
    action_call left_click() override;                                                      // Left click on the player does nothing
    void equip_item(item *i);                                                               // Equip an item on the player

private:
    bool equiped_sword_;                                                                    // Have the player equipped weapon?
    bool equiped_armor_;                                                                    // Have the player equipped armor?
    item* sword_;                                                                           // Currently equipped sword
    item* armor_;                                                                           // Currently equipped armor

};


#endif // PLAYER

