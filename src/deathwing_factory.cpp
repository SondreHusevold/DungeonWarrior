#include "deathwing_factory.hpp"
#include "item_database.hpp"

deathwing_factory::deathwing_factory(int difficulty):difficulty_{difficulty}{}

monster* deathwing_factory::create_monster(){
	monster* temp=new monster("Deathwing", visible::CREATURE_BOSS, "Dragon", 0, 0);
    item_database id{};
    temp->set_stamina(300*(1+difficulty_*abstract_monster_factory::STAMINA_PR_LEVEL));
    temp->set_power(180*(1+difficulty_*abstract_monster_factory::POWER_PR_LEVEL));
    temp->set_armor(6*(1+difficulty_*abstract_monster_factory::ARMOR_PR_LEVEL));
    temp->add_item(id.get_item(item_database::ARMAGEDDON));
    temp->add_item(id.get_item(item_database::SULFURAS));
    temp->add_item(id.get_item(item_database::DRAGONSKIN_ARMOR));
    temp->add_item(id.get_item(item_database::DESTROYER_ARMOR));
    return temp;
}
