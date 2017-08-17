#ifndef ITEM
#define ITEM
#include <random>
#include <string>
#include <sstream>

typedef int itemtype;

class item {

public:
    static const itemtype WEAPON=1;
    static const itemtype ARMOR=2;
    static const itemtype CONSUMABLE=3;
    const int ITEM_NAME;//et unikt navn for itemet
    item(const int IN, std::string name, itemtype type_, int drop_rate_, int stam, int pow, int arm);
    item& operator=(const item& i);
    bool drop();
    int get_stamina();
    int get_power();
    int get_armor();
    bool use_item();
    itemtype get_type();
    std::string get_name();
    std::string to_string();

private:
    std::string name;
    itemtype type;
    bool dropped_;
    int drop_rate;
    int stamina;
    int power;
    int armor;


};

#endif // ITEM

