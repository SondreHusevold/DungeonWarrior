#include "player.hpp"
#include "item_database.hpp"

player::player(std::string name_, char icon_, std::string information_, int x_, int y_) : creature(name_, icon_, information_, x_, y_), equiped_sword_{false}, equiped_armor_{false}{
    // Starting equipment, starting stats and such should be randomly generated here once the player starts.
    target_=this;
    set_stamina(250);
    set_power(100);
    set_armor(5);
    //item_database id{};
    //equip_item(id.get_item(item_database::DRAGON_SLAYER));
    //equip_item(id.get_item(item_database::PITLORD_ARMOR));

    //add_item(new item(0, "Fists", WEAPON, 0, 0, 0, 0));   // (Name, item type, droprate, stamina, power, armor, isConsumable)
    //add_item(new item(1, "Filthy Clothes", ARMOR, 0, 0, 0, 0));
    //add_item(new item("TESTARMOR", ARMOR, 0.10, 100, 100, 100));
}
player::player(const player& p):creature(p), equiped_sword_{p.equiped_sword_}, equiped_armor_{p.equiped_armor_}{
    if(equiped_sword_)
        *sword_=*p.sword_;
    if(equiped_armor_)
        *armor_=*p.armor_;
}
player::player(player&& p):creature(p), equiped_sword_{p.equiped_sword_}, equiped_armor_{p.equiped_armor_}{
    if(equiped_sword_)
        *sword_=*p.sword_;
    if(equiped_armor_)
        *armor_=*p.armor_;
    p.sword_=nullptr;
    p.armor_=nullptr;
}
player& player::operator=(const player& p){
    if(&p==this)
        return *this;
    equiped_sword_=p.equiped_sword_;
    equiped_armor_=p.equiped_armor_;

    if(equiped_sword_)
        *sword_=*p.sword_;
    if(equiped_armor_)
        *armor_=*p.armor_;
    creature::operator=(p);
    return *this;
}
player& player::operator=(player&& p){
    if(&p==this)
        return *this;
    equiped_sword_=p.equiped_sword_;
    equiped_armor_=p.equiped_armor_;

    if(equiped_sword_)
        sword_=p.sword_;
    if(equiped_armor_)
        armor_=p.armor_;
    p.sword_=nullptr;
    p.armor_=nullptr;
    creature::operator=(p);
    return *this;
}

void player::equip_item(item* i){
    if(i->get_type() == item::WEAPON){
        sword_ = i;                             // Sets a weapon.
        equiped_sword_=true;
    }
    else if(i->get_type() == item::ARMOR){
        armor_ = i;                             // Set an armor.
        equiped_armor_=true;
    }
    else
        report("Can't equip that.");  // Responds to the player that they can't equip something that isn't a weapon or a piece of armor.
    power=0;
    armor=0;
    stamina=0;
    if(equiped_sword_){
        power += sword_->get_power();
        armor += sword_->get_armor();
        stamina += sword_->get_stamina();
    }
    if(equiped_armor_){
        power += armor_->get_power();
        armor += armor_->get_armor();
        stamina += armor_->get_stamina();

    }    
}

action_call player::left_click(){
    return clickable::NO_ACTION;
}

std::string player::to_string(){
    std::string response = "This is you!";
    return response;
}
