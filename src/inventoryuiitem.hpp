#ifndef INVENTORYUIITEM_HPP
#define INVENTORYUIITEM_HPP
#include "item.hpp"
#include <QWidget>

// Used to have weapons and armor inside the inventoryBox list in gui_handler. See documenation.

class inventoryUIitem : public QWidget {

    item* heldItem;                         // What item is currently held by this listitem

public:
    inventoryUIitem(item* i);               // Constructor adds item.
    item* getItem();                        // Getter
    void setItem(item* i);                  // Setter
    ~inventoryUIitem();
};

#endif // INVENTORYUIITEM_HPP
