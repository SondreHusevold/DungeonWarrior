#include "monoroth_factory.hpp"
#include "item_database.hpp"

monoroth_factory::monoroth_factory(int difficulty):difficulty_{difficulty}{}

monster* monoroth_factory::create_monster(){
	monster* temp=new monster("Monoroth", visible::CREATURE_BOSS, "Demon", 0, 0);
    item_database id{};
    temp->set_stamina(380*(1+difficulty_*abstract_monster_factory::STAMINA_PR_LEVEL));
    temp->set_power(95*(1+difficulty_*abstract_monster_factory::POWER_PR_LEVEL));
    temp->set_armor(8*(1+difficulty_*abstract_monster_factory::ARMOR_PR_LEVEL));
    temp->add_item(id.get_item(item_database::LEGENDARY_WEP));
    temp->add_item(id.get_item(item_database::ARMAGEDDON));
    temp->add_item(id.get_item(item_database::FROSTMOURNE));
    temp->add_item(id.get_item(item_database::DEMONIC_ARMOR));
    temp->add_item(id.get_item(item_database::DESTROYER_ARMOR));
    return temp;
}
