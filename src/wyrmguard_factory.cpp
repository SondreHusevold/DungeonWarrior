#include "wyrmguard_factory.hpp"
#include "item_database.hpp"

wyrmguard_factory::wyrmguard_factory(int difficulty):difficulty_{difficulty}{}

monster* wyrmguard_factory::create_monster(){
    item_database id{};
    monster* temp=new monster("Wyrmguard", visible::CREATURE_NINJA, "Dragon", 0, 0);
    std::random_device rd;                                                          // Seed engine.
    std::mt19937 rng(rd());                                                         // Using Mersenne-Twister random-genereator engine.
    std::uniform_int_distribution<int> powerlevel(0,20);
    std::uniform_int_distribution<int> armorlevel(0,2);
    temp->set_stamina(130*(1+difficulty_*abstract_monster_factory::STAMINA_PR_LEVEL));
    temp->set_power(200*(1+difficulty_*abstract_monster_factory::POWER_PR_LEVEL)-powerlevel(rng));
    temp->set_armor(4*(1+difficulty_*abstract_monster_factory::ARMOR_PR_LEVEL)-armorlevel(rng));
    temp->add_item(id.get_item(item_database::LEGENDARY_WEP));
    temp->add_item(id.get_item(item_database::COMMON_ARMOR));
    temp->add_item(id.get_item(item_database::COMMON_WEP));
    temp->add_item(id.get_item(item_database::BLACK_DRAGON));
    temp->add_item(id.get_item(item_database::DRAGON_SLAYER));
    temp->add_item(id.get_item(item_database::DRAGON_ARMOR));
    temp->add_item(id.get_item(item_database::WYRM_ARMOR));

    return temp;
}
