/*
 * Base klasse for spiller og monstere.
 * Har funksjoner for bevelgelse, angrep og behandling av stats og items.
*/

#ifndef CREATURE
#define CREATURE
#include "clickable.hpp"
#include "item.hpp"
#include "reportable.hpp"

class creature : public clickable, public reportable{

public:
    creature(std::string name_, char icon, std::string information, int x, int y);
    creature(const creature& c);
    creature(creature&& c);
    creature& operator=(const creature& c);
    creature& operator=(creature&& c);
    int take_damage(int d);//ta damage, trekker en sum fra hp_ beregnet ut fra d og nåværende armor
    int deal_damage();//returnerer en int beregnet ut fra nåværende power
    bool attack();//forsøker å angripe nåværende target
    void target(creature* target);//setter target som target
    void move(int x, int y);//flytter creature x i x retning og y i y retning
    virtual bool dead();//hp>0
    bool in_combat();//returnerer om creature er i combat
    bool has_target();//returnerer om creature har et target
    bool range();//returnerer om creature er innen rekkevidde for å angripe target
    int access() override;//hva skjer når dette området accesseres, returnerer en int
    void set_combat(bool c);//setter creature sitt combat status
    void heal(int h);//healer creature med h
    virtual std::string to_string();//returnerer en string med informasjon om creature
    std::vector<item*> get_items();//returnerer en vector med peker til alle creature sine items
    bool add_item(item* i);//forsøker å legge item i til inventory, dublikater blir ikke godtatt for våpen og armor
    void set_stamina(int stam);
    void set_power(int pow);
    void set_armor(int armour);
    int get_stamina();
    int get_power();
    int get_armor();
    int get_base_power();
    int get_base_stamina();
    int get_base_armor();
    int get_hp();
    virtual ~creature();

protected:
    std::vector<item*> inventory;
    std::string name;
    creature* target_;
    int stamina;
    int power;
    int armor;
    int base_stamina;
    int base_power;
    int base_armor;
    int hp_;
    bool in_combat_;
    bool has_target_;
};

#endif // CREATURE

