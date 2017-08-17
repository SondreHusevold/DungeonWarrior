#include "wrathguard_factory.hpp"
#include "item_database.hpp"

wrathguard_factory::wrathguard_factory(int difficulty):difficulty_{difficulty}{}

monster* wrathguard_factory::create_monster(){
    monster* temp=new monster("Wrathguard", visible::GHOST, "Demon", 0, 0);
    item_database id{};
    std::random_device rd;                                                          // Seed engine.
    std::mt19937 rng(rd());                                                         // Using Mersenne-Twister random-genereator engine.
    std::uniform_int_distribution<int> powerlevel(0,20);
    std::uniform_int_distribution<int> armorlevel(0,2);
    temp->set_stamina(120*(1+difficulty_*abstract_monster_factory::STAMINA_PR_LEVEL));
    temp->set_power(160*(1+difficulty_*abstract_monster_factory::POWER_PR_LEVEL)+powerlevel(rng));
    temp->set_armor(3*(1+difficulty_*abstract_monster_factory::ARMOR_PR_LEVEL)+armorlevel(rng));
    temp->add_item(id.get_item(item_database::LEGENDARY_WEP));
    temp->add_item(id.get_item(item_database::COMMON_ARMOR));
    temp->add_item(id.get_item(item_database::COMMON_WEP));
    temp->add_item(id.get_item(item_database::BLADE_BANISHER));
    temp->add_item(id.get_item(item_database::DEMON_WARGLAIVE));
    temp->add_item(id.get_item(item_database::DEMON_ARMOR));
    temp->add_item(id.get_item(item_database::PITLORD_ARMOR));
    return temp;
}
