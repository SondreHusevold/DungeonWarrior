/*
 * Holder alle items som brukes i spillet. Har en static const for hvert item og en get metode for å hente ut item etter const navn
*/

#ifndef ITEM_DATABASE_HPP
#define ITEM_DATABASE_HPP
#include "item.hpp"

class item_database{
	std::vector<item*>items_;
public:
    //konstanter for ulike items
    //mob items:
	static const int COMMON_WEP=0;
	static const int COMMON_ARMOR=1;
	static const int LEGENDARY_WEP=8;
    //demon items:
    static const int BLADE_BANISHER=18;
    static const int DEMON_WARGLAIVE=9;
    static const int DEMON_ARMOR=26;
    static const int PITLORD_ARMOR=32;
    //troll items:
    static const int KINGS_BLADE=17;
    static const int TROLL_STAFF=10;
    static const int TROLL_ARMOR=28;
    static const int WIZZARD_ARMOR=30;
    //dragon items:
    static const int BLACK_DRAGON=19;
    static const int DRAGON_SLAYER=11;
    static const int DRAGON_ARMOR=27;
    static const int WYRM_ARMOR=31;
    //orc items:
    static const int WARHAMMER=20;
    static const int ORC_BLADE=12;
    static const int ORC_ARMOR=25;
    static const int WAR_ARMOR=29;

    //boss items:
    static const int ARMAGEDDON=13;
    static const int THUNDERFURY=14;
    static const int FROSTMOURNE=15;
    static const int SULFURAS=16;

    static const int PLATE_ARMOR=21;
    static const int DRAGONSKIN_ARMOR=22;
    static const int DEMONIC_ARMOR=23;
    static const int DESTROYER_ARMOR=24;

	item_database();
    item_database(const item_database& id);
    item_database(item_database&& id);
    item_database& operator=(const item_database& id);
    item_database& operator=(item_database&& id);
    item* get_item(const int NAME);//returnerer et item med ITEM_NAME==NAME, nullptr hvis dette ikke finnes
	~item_database();
};

#endif
