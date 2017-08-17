#include "warscout_factory.hpp"
#include "item_database.hpp"

warscout_factory::warscout_factory(int difficulty):difficulty_{difficulty}{}

monster* warscout_factory::create_monster(){
    monster* temp=new monster("Warscout", visible::CREATURE_BARD, "Troll", 0, 0);
    item_database id{};
    std::random_device rd;                                                          // Seed engine.
    std::mt19937 rng(rd());                                                         // Using Mersenne-Twister random-genereator engine.
    std::uniform_int_distribution<int> powerlevel(0,20);
    std::uniform_int_distribution<int> armorlevel(0,2);
    temp->set_stamina(180*(1+difficulty_*abstract_monster_factory::STAMINA_PR_LEVEL));
    temp->set_power(100*(1+difficulty_*abstract_monster_factory::POWER_PR_LEVEL)-powerlevel(rng));
    temp->set_armor(7*(1+difficulty_*abstract_monster_factory::ARMOR_PR_LEVEL)-armorlevel(rng));
    temp->add_item(id.get_item(item_database::LEGENDARY_WEP));
    temp->add_item(id.get_item(item_database::COMMON_ARMOR));
    temp->add_item(id.get_item(item_database::COMMON_WEP));
    temp->add_item(id.get_item(item_database::KINGS_BLADE));
    temp->add_item(id.get_item(item_database::TROLL_STAFF));
    temp->add_item(id.get_item(item_database::TROLL_ARMOR));
    temp->add_item(id.get_item(item_database::WIZZARD_ARMOR));
    return temp;
}
