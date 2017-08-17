#include "warlord_factory.hpp"
#include "item_database.hpp"

warlord_factory::warlord_factory(int difficulty):difficulty_{difficulty}{}

monster* warlord_factory::create_monster(){
	monster* temp=new monster("Warlord", visible::CREATURE_BOSS, "Troll", 0, 0);
    item_database id{};
    temp->set_stamina(255*(1+difficulty_*abstract_monster_factory::STAMINA_PR_LEVEL));
    temp->set_power(200*(1+difficulty_*abstract_monster_factory::POWER_PR_LEVEL));
    temp->set_armor(6*(1+difficulty_*abstract_monster_factory::ARMOR_PR_LEVEL));
    temp->add_item(id.get_item(item_database::LEGENDARY_WEP));
    temp->add_item(id.get_item(item_database::ARMAGEDDON));
    temp->add_item(id.get_item(item_database::THUNDERFURY));
    temp->add_item(id.get_item(item_database::PLATE_ARMOR));
    temp->add_item(id.get_item(item_database::DESTROYER_ARMOR));
    return temp;
}
