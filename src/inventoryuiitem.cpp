#include "inventoryuiitem.hpp"

// This is a widget so that it can be added to a QListWidget.

inventoryUIitem::inventoryUIitem(item* i) : heldItem{i} {
    std::stringstream toolTipStream;                                                               // Sets the tooltip to describe what the item does.
    toolTipStream << "This is " << heldItem->get_name() << ".\nItem type: ";
    if(heldItem->get_type() == item::WEAPON)
        toolTipStream << "weapon.\n";
    else if(heldItem->get_type() == item::ARMOR)
        toolTipStream << "armor.\n";
    else if(heldItem->get_type() == item::CONSUMABLE)
        toolTipStream << "consumable item.\nFor <NUMBER OF TURNS> ";
    else{
        toolTipStream << "ERROR";
        setToolTip(QString::fromStdString(toolTipStream.str()));
        return;
    }
    toolTipStream<<"This item will give you:"<<"\nStamina: "<<i->get_stamina()<<"\nPower: "<<i->get_power()<<"\nArmor: "<<i->get_armor();

    setToolTip(QString::fromStdString(toolTipStream.str()));
}

item* inventoryUIitem::getItem(){                                                               // Get what this list item's item is.
    return heldItem;
}

void inventoryUIitem::setItem(item* i){                                                         // Unused, but could be handy in other implementations.
    heldItem = i;
}

inventoryUIitem::~inventoryUIitem() {}

