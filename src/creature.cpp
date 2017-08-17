#include "creature.hpp"
#include "level.hpp"
#include <math.h>


creature::creature(std::string _name, char icon_, std::string information_, int x_, int y_) : clickable(icon_, information_, x_, y_),
                                    name{_name}, stamina{0}, power{0}, armor{0}, base_stamina{0}, base_power{0}, base_armor{0}, hp_{0},
                                    in_combat_{false}, has_target_{false}{
}
creature::creature(const creature& c):clickable(c), name{c.name}, stamina{c.stamina}, power{c.power}, armor{c.armor},
                                    base_stamina{c.base_stamina}, base_power{c.base_power}, base_armor{c.base_armor},
                                    hp_{c.hp_}, in_combat_{false}, has_target_{c.has_target_}{
    if(has_target_)
        *target_=*c.target_;
    for(unsigned int i=0; i<c.inventory.size(); i++)
        inventory.push_back(new item(*c.inventory[i]));
}
creature::creature(creature&& c):clickable(c),  name{c.name}, stamina{c.stamina}, power{c.power}, armor{c.armor},
                                base_stamina{c.base_stamina}, base_power{c.base_power}, base_armor{c.base_armor},
                                hp_{c.hp_}, in_combat_{false}, has_target_{c.has_target_}{
    c.stamina=0;
    c.power=0;
    c.armor=0;
    c.base_power=0;
    c.base_stamina=0;
    c.base_armor=0;
    c.hp_=0;
    c.name="";
    c.in_combat_=false;
    c.has_target_=false;
    target_=c.target_;
    c.target_=nullptr;
    for(unsigned int i=0; i<c.inventory.size(); i++){
        inventory.push_back(c.inventory[i]);
        c.inventory[i]=nullptr;
    }
    c.inventory.clear();

}
creature& creature::operator=(const creature& c){
    if(this==&c)
        return *this;
    if(c.has_target_)
        *target_=*c.target_;//pointer
    name=c.name;
    base_stamina=c.base_stamina;
    base_armor=c.base_armor;
    base_power=c.base_power;
    stamina=c.stamina;
    armor=c.armor;
    power=c.power;
    in_combat_=c.in_combat_;
    has_target_=c.has_target_;
    for(unsigned int i=0; i<c.inventory.size(); i++)
        inventory.push_back(new item(*c.inventory[i]));
    return *this;
    clickable::operator=(c);
}
creature& creature::operator=(creature&& c){
    if(&c==this)
        return *this;
    name=c.name;
    base_stamina=c.base_stamina;
    base_armor=c.base_armor;
    base_power=c.base_power;
    stamina=c.stamina;
    armor=c.armor;
    power=c.power;
    in_combat_=c.in_combat_;
    has_target_=c.has_target_;
    c.stamina=0;
    c.power=0;
    c.armor=0;
    c.base_power=0;
    c.base_stamina=0;
    c.base_armor=0;
    c.hp_=0;
    c.name="";
    c.in_combat_=false;
    c.has_target_=false;
    target_=c.target_;
    c.target_=nullptr;
    for(unsigned int i=0; i<c.inventory.size(); i++){
        inventory.push_back(c.inventory[i]);
        c.inventory[i]=nullptr;
    }
    c.inventory.clear();
    return *this;
    
}
int creature::take_damage(int d){
    // Armor will have impact on damage taken.
    int damage_dealt = (d / (base_armor + armor));
    hp_ -= damage_dealt;
    return damage_dealt;
}

int creature::deal_damage(){
    // power is based on weapon
    return (base_power + power);
}

bool creature::attack(){                                                            // Creature attacks something
    if(!dead()){
        std::stringstream streamer;
        if(!range()){                                                               // Creature is too far away
            streamer << "Target is too far away!";
            report(streamer.str());
            return false;
        }
        else if(target_->dead()){                                                   // Creature is already dead
            streamer << "Target is already dead!";
            report(streamer.str());
            return false;
        }
        int damage_dealt = target_->take_damage(deal_damage());                     // Deal damage to the target
        streamer << name << " dealt " << damage_dealt << " damage to " << target_->name;    // Report to the log what happened
        report(streamer.str());
        return true;
    }
    return false;
}

void creature::target(creature* target){
    has_target_=true;
    target_=target;
}

bool creature::has_target(){
    return has_target_;
}

void creature::move(int _x, int _y){
    //bruk x+=sin(d), y+=cos(d) d skal være 1, 2, 3 eller 4 *TAU der TAU=M_PI/2
    /*lettere å bruke hvis den flytter x i retning x, og y i retning y, bedre for game*/
    if(dead())
        return;

    set_x(x()+_x);
    set_y(y()+_y);
    /*set_x(_x);
    set_y(_y);*/
    // Move the creature in direction d.
}

std::vector<item*> creature::get_items(){
    return inventory;
    // Item factory.
}

bool creature::add_item(item* i){
    if(i->get_type()==item::ARMOR || i->get_type()==item::WEAPON)
        for(unsigned int j=0; j<inventory.size(); j++)          //tar ikke flere av samme item, ellers vil inventory bli fult av "søppel"
            if(inventory[j]->ITEM_NAME==i->ITEM_NAME){
                delete i;
                return false;
            }

    inventory.push_back(i);
    return true;
}

bool creature::dead(){
    if(hp_ <= 0){
        set_moveable(false);                                    // Stops the creature from doing further actions.
        std::stringstream streamer;
        streamer << "This is " << name << ". It is dead.";      // New description on monster.
        set_info(streamer.str());                               // Set that info.
        set_accessable(true);                                   // Make it possible to move through the dead creature.
        set_icon(visible::SKELETON);
        return true;                                            // Yup, it's dead.
    }
    return false;                                               // Nope, it's alive.
}

bool creature::range(){
    if(!has_target_)
        return false;
    return level::valid_range(*this, *target_, level::ATTACK_RANGE);
}

bool creature::in_combat(){                                     // Is the creature currently in combat?
    return in_combat_;
}

void creature::heal(int h){
    hp_+=h;
    if(hp_>base_stamina+stamina)
        hp_=base_stamina+stamina;
}

int creature::get_stamina(){
    return stamina;
}

int creature::get_power(){
    return power;
}

int creature::get_armor(){
    return armor;
}

int creature::get_hp(){
    return hp_;
}

int creature::get_base_stamina(){
    return base_stamina;
}

int creature::get_base_armor(){
    return base_armor;
}

int creature::get_base_power(){
    return base_power;
}

void creature::set_stamina(int stam){
    base_stamina = stam;
    hp_=base_stamina+stamina;
}

void creature::set_power(int pow){
    base_power = pow;
}

void creature::set_armor(int armour){
    base_armor = armour;
}
void creature::set_combat(bool c){
    in_combat_=c;
}

int creature::access(){
    return NO_ACTION;
}

std::string creature::to_string(){                                          // Describes the creature to the player on right click.
    std::stringstream stringstreamer;                                       // Also shows current status of the monster.
    stringstreamer << "You see a " << name << ". It looks ";
    if(get_hp() >= (get_stamina()+get_base_stamina())){                     // At high health
        stringstreamer << "healthy. ";
    }
    else if(get_hp() > (int)(get_stamina()+get_base_stamina())*30/100){     // At medium health
        stringstreamer << "wounded. ";
    }
    else if(get_hp() > 0){                                                  // At low health
        stringstreamer << "like it is on its last legs. ";
    }
    else                                                                    // Dead
        stringstreamer<<"dead.";

    return stringstreamer.str();                                            // "You see a [creature] It looks [status]".
}

creature::~creature(){
    for(unsigned int i=0; i<inventory.size(); i++)
        delete inventory[i];
    target_=nullptr;
}
