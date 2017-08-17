#include "item.hpp"

item::item(const int IN, std::string name_, itemtype type_, int drop_rate_, int stam, int pow, int arm) :ITEM_NAME{IN}, name{name_}, type{type_},
                        dropped_{false}, drop_rate{drop_rate_}, stamina{stam}, power{pow}, armor{arm}{
    int d=rand()%100+1;
    if(drop_rate_>=d)
        dropped_=true;
}
item& item::operator=(const item& i){
    if(this==&i)
        return *this;
    name=i.name;
    type=i.type;
    drop_rate=i.drop_rate;
    stamina=i.stamina;
    power=i.power;
    armor=i.armor;
    dropped_=i.dropped_;
    return *this;

}

bool item::drop(){
    return dropped_;
}

int item::get_stamina(){
    return stamina;
}

int item::get_power(){
    return power;
}

int item::get_armor(){
    return armor;
}

itemtype item::get_type(){
    return type;
}

bool item::use_item(){
    if(!(get_type() == CONSUMABLE)){
        return false;
    }
    // More if things if type is... Then do.
    return true;
}

std::string item::get_name(){
    return name;
}

std::string item::to_string(){                              // Item description on right click.
    std::stringstream streamer;
    streamer << "[" << name << "]";
    return streamer.str();
}
