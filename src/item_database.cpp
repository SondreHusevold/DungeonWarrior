#include "item_database.hpp"


item_database::item_database(){
    items_.push_back(new item(COMMON_ARMOR, "Common Weapon", item::WEAPON, 80, 2, 5, 0));//(const_name, name, type, dropchanse, stamina, power, armor)
    items_.push_back(new item(COMMON_WEP, "Common Armor", item::ARMOR, 80, 5, 0, 1));
    items_.push_back(new item(LEGENDARY_WEP, "Alfreds Staff of Wisdom", item::WEAPON, 1, 50, 1500, 1));

    items_.push_back(new item(DEMON_WARGLAIVE, "Warglaive of the Demonslayer", item::WEAPON, 10, 10, 30, 0));
    items_.push_back(new item(TROLL_STAFF, "Greatstaff of the Troll Wizard", item::WEAPON, 10, 20, 20, 1));
    items_.push_back(new item(DRAGON_SLAYER, "Blade of the Dragon Slayer", item::WEAPON, 10, 15, 25, 2));
    items_.push_back(new item(ORC_BLADE, "Orcsayer Blade", item::WEAPON, 10, 20, 15, 2));

    items_.push_back(new item(KINGS_BLADE, "Sword of Kings", item::WEAPON, 15, 8, 10, 0));
    items_.push_back(new item(BLADE_BANISHER, "Demon Banishers Blade", item::WEAPON, 15, 7, 15, 0));
    items_.push_back(new item(BLACK_DRAGON, "Runeblade of the Black Dragon", item::WEAPON, 15, 5, 18, 0));
    items_.push_back(new item(WARHAMMER, "The Hammer of War", item::WEAPON, 15, 2, 30, 0));

    items_.push_back(new item(ARMAGEDDON, "Armageddon", item::WEAPON, 20, 20, 50, 2));
    items_.push_back(new item(THUNDERFURY, "Thunderfury", item::WEAPON, 20, 40, 35, 2));
    items_.push_back(new item(FROSTMOURNE, "Frostmaurne", item::WEAPON, 20, 30, 40, 3));
    items_.push_back(new item(SULFURAS, "Sulfuras", item::WEAPON, 20, 10, 60, 2));

    items_.push_back(new item(PLATE_ARMOR, "Plated Armor", item::ARMOR, 20, 100, 0, 5));
    items_.push_back(new item(DRAGONSKIN_ARMOR, "Dragonskin Armor", item::ARMOR, 20, 120, 15, 3));
    items_.push_back(new item(DEMONIC_ARMOR, "Demonic Armor", item::ARMOR, 20, 80, 20, 2));
    items_.push_back(new item(DESTROYER_ARMOR, "Destroyers Armor", item::ARMOR, 20, 40, 60, 2));

    items_.push_back(new item(ORC_ARMOR, "Orc Armor", item::ARMOR, 15, 50, 5, 2));
    items_.push_back(new item(DEMON_ARMOR, "Demonslayer Armor", item::ARMOR, 15, 30, 10, 1));
    items_.push_back(new item(DRAGON_ARMOR, "Dragonslayer Armor", item::ARMOR, 15, 40, 7, 1));
    items_.push_back(new item(TROLL_ARMOR, "Troll Armor", item::ARMOR, 15, 25, 15, 3));

    items_.push_back(new item(WAR_ARMOR, "Vicious War Armor", item::ARMOR, 10, 25, 60, 2));
    items_.push_back(new item(WIZZARD_ARMOR, "Armor of the Troll Wizard", item::ARMOR, 10, 35, 25, 3));
    items_.push_back(new item(WYRM_ARMOR, "Wyrmhero Armor", item::ARMOR, 10, 50, 12, 1));
    items_.push_back(new item(PITLORD_ARMOR, "Armor of the Pitlord", item::ARMOR, 10, 40, 20, 1));

}
item_database::item_database(const item_database& id){
    for(unsigned int i=0; i<id.items_.size(); i++)
        items_.push_back(new item(*id.items_[i]));
}
item_database::item_database(item_database &&id){
    for(unsigned int i=0; i<id.items_.size(); i++){
        items_.push_back(id.items_[i]);
        id.items_[i]=nullptr;
    }
    id.items_.clear();
}
item_database& item_database::operator=(const item_database& id){
    if(&id==this)
        return *this;
    items_.clear();
    for(unsigned int i=0; i<id.items_.size(); i++)
        items_.push_back(new item(*id.items_[i]));
    return *this;
}
item_database& item_database::operator=(item_database&& id){
    if(&id==this)
        return *this;
    for(unsigned int i=0; i<id.items_.size(); i++){
        items_.push_back(id.items_[i]);
        id.items_[i]=nullptr;
    }
    id.items_.clear();
    return *this;
}

item* item_database::get_item(const int NAME){
    for(unsigned int i=0; i<items_.size(); i++)//kunne vært lagt i en raskere datastruktør enn en liste
        if(items_[i]->ITEM_NAME==NAME)
            return new item(*items_[i]);
	return nullptr;
}
item_database::~item_database(){
	for(unsigned int i=0; i<items_.size(); i++)
		delete items_[i];
}
