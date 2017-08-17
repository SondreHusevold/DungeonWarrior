#include <gui_handler.hpp>
#include <QMessageBox>


QWidget* gui_handler::centralWidget;
QTextEdit* gui_handler::command_log;                 // Static member for logging
game_button* gui_handler::buttons[10][6];            // Static member for buttons.
game* gui_handler::gameplay;                        // Static member for pointer to game.
QLabel* gui_handler::hpEditable;                    // Must be static due to redraw().
QLabel* gui_handler::powerEditable;                 // Must be static due to redraw().
QLabel* gui_handler::armorEditable;                 // Must be static due to redraw().
QListWidget* gui_handler::inventoryBox;             // Must be static due to redraw().
QGraphicsView* gui_handler::hpBar;
QGraphicsScene* gui_handler::hpLeft;
map* gui_handler::currentMap;

gui_handler::gui_handler(std::string playername, QWidget *centralWidget_, QWidget* inventoryUI_, QWidget* mapUI_, QObject *parent) : QObject(parent),
                                                    inventoryUI{inventoryUI_}, mapUI{mapUI_} {
    centralWidget = centralWidget_;
    initialize_inventory();

    gameplay = new game(playername);
    for(int x = 0; x < MAX_VIEWABLE_TILES_X; x++){                    // 10 x 6 board.
        for(int y = 0; y < MAX_VIEWABLE_TILES_Y; y++){
            buttons[x][y] = new game_button(QString(""), gameplay, centralWidget);                    // Initialize button with empty string and put it into the central container.
            buttons[x][y]->setGeometry(QRect(QPoint((x*128), (y*126)),QSize(128, 128)));    // Set button width and height to 128x128.
        }
    }
    command_log = new QTextEdit(centralWidget);                        // Create the log
    command_log->setGeometry(QRect(0, 757, 1280, 143));                // (x, y, width, height)
    command_log->setReadOnly(true);                                    // Cannot modify the log.
    hpBar = new QGraphicsView(centralWidget);
    hpBar->setGeometry(QRect(525, 220, 100, 10));
    hpLeft = new QGraphicsScene(0,0, 100, 10);
    hpLeft->addRect(0,0,100,10,QPen(Qt::red), QBrush(Qt::red));
    hpBar->setScene(hpLeft);
    hpBar->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    hpBar->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    currentMap = new map(mapUI, gameplay, mapUI);
    currentMap->redraw();
    redraw();                                                          // Redraws everything and sets player.
}

game_button* gui_handler::get_button(int x, int y){
    return buttons[x][y];
}

void gui_handler::move_up(){
    if(disableControls == true){
        return;
    }
    gameplay->move_player(0,-1);     // Do not move player in x, move player +1 in y.
}

void gui_handler::move_down(){
    if(disableControls == true){
        return;
    }
    gameplay->move_player(0,1);    // Do not move player in x, move player -1 in y.
}

void gui_handler::move_right(){
    if(disableControls == true){
        return;
    }
    gameplay->move_player(1, 0);    // Move player +1 in x, do not move in y.
}

void gui_handler::move_left(){
    if(disableControls == true){
        return;
    }
    gameplay->move_player(-1, 0);   // Move player -1 in x, do not move in y.
}

void gui_handler::redraw_map(int i){
    if(i == 2){
        disableControls = true;
        currentMap->redraw();
    }
    else if(i == 1){
        disableControls = false;
        update_inventory_status_screen();
    }
    else{
        disableControls = false;
    }
}

void gui_handler::redraw(){
    int playerpos_x = ((gameplay->get_player()->x()) -4);       // Player will always be in the middle of the screen.
    int playerpos_y = ((gameplay->get_player()->y()) -2);       // At position 4,2.
    for(int x = 0; x < MAX_VIEWABLE_TILES_X; x++){
        for(int y = 0; y < MAX_VIEWABLE_TILES_Y; y++){
            buttons[x][y]->set_element(gameplay->get_element((playerpos_x + x), (playerpos_y + y)));    // Give button the object at x, y relative to the player.
            buttons[x][y]->redraw();                                                                    // Redraw that button.
        }
    }
    buttons[4][2]->set_element(gameplay->get_player());         // After drawing the elements, place character at 4,2 as intended.
    buttons[4][2]->redraw();                                    // redraw him.
    //check_current_inventory();// Checks the inventory - Has the player got new items? ->For tung operasjon, lagger hvis du holder pil inne med denne på. kalles av loot metoden i game
    update_log();
}

QIcon gui_handler::convert_to_icon(char charactericon){
    switch(charactericon){                                      // Convert characters into icon resources.
        case '@' :                                              // Example:  "@" becomes images/creature_naked.png
            return QIcon{":/images/creature_naked.png"};
        case 'A' :
            return QIcon{":/images/creature_armored.png"};
        case 'L' :
            return QIcon{":/images/loot.png"};
        case 'F' :
            return QIcon{":/images/creature_ghost.png"};
        case 'R' :
            return QIcon{":/images/creature_priest.png"};
        case 'E' :
            return QIcon{":/images/creature_elf.png"};
        case 'D' :
            return QIcon{":/images/stairs_down.png"};
        case '.' :
            return QIcon{":/images/floor.png"};
        case 'U' :
            return QIcon{":/images/stairs_up.png"};
        case 'C' :
            return QIcon{":/images/chest.png"};
        case 'P' :
            return QIcon{":/images/creature_armored_cape.png"};
        case 'B' :
            return QIcon{":/images/creature_bard.png"};
        case 'O' :
            return QIcon{":/images/creature_boss.png"};
        case 'W' :
            return QIcon{":/images/creature_girl.png"};
        case 'K' :
            return QIcon{":/images/creature_king.png"};
        case 'N' :
            return QIcon{":/images/creature_ninja.png"};
        case 'H' :
            return QIcon{":/images/house.png"};
        case 'M' :
            return QIcon{":/images/monster.png"};
        case 'S' :
            return QIcon{":/images/skeleton.png"};
        case 'T' :
            return QIcon{":/images/tree.png"};
        case '#' :
            return QIcon{":/images/wall.png"};
    }
    return QIcon{":/images/void.png"};
}

void gui_handler::update_inventory_status_screen(){  // This update the player's status on the inventory screen like "HP: 97 / 150 (100 + 25)".
    std::stringstream powerStream;
    std::stringstream armorStream;
    std::stringstream hpStream;
    hpStream << gameplay->get_player()->get_hp() << " / " <<
                  (gameplay->get_player()->get_base_stamina() + gameplay->get_player()->get_stamina()) << " (" <<
                  gameplay->get_player()->get_base_stamina() << " + " << gameplay->get_player()->get_stamina() << ")";

    powerStream << gameplay->get_player()->get_base_power() + gameplay->get_player()->get_power() << " (" <<
                  gameplay->get_player()->get_base_power() << " + " << gameplay->get_player()->get_power() << ")";

    armorStream << gameplay->get_player()->get_base_armor() + gameplay->get_player()->get_armor() << " (" <<
                  gameplay->get_player()->get_base_armor() << " + " << gameplay->get_player()->get_armor() << ")";

    hpEditable->setText(QString::fromStdString(hpStream.str()));                    // Sets HP text
    powerEditable->setText(QString::fromStdString(powerStream.str()));              // Sets power text.
    armorEditable->setText(QString::fromStdString(armorStream.str()));              // Sets armor text.
}

void gui_handler::player_inventory_usage(){                                             // Double click on the inventoryBox widget's items will active this slot.
    inventoryUIitem* temp = (inventoryUIitem*)(inventoryBox->itemWidget(inventoryBox->currentItem()));
    item* itemtobeused = temp->getItem();
    if(itemtobeused->get_type() == item::WEAPON){                                        // Found an item - A weapon.
        weaponEquipBox->setText(QString::fromStdString(itemtobeused->get_name()));      // Equips the weapon in the weapon box.
        gameplay->get_player()->equip_item(itemtobeused);                               // Actually equips it on the player
    }
    else if(itemtobeused->get_type() == item::ARMOR){                                     // Same as weapon with armor instead.
        armorEquipBox->setText(QString::fromStdString(itemtobeused->get_name()));
        gameplay->get_player()->equip_item(itemtobeused);
        gameplay->get_player()->set_icon(visible::ARMORED_PLAYER);
    }
    else if(itemtobeused->get_type() == item::CONSUMABLE){                                // Use a consuamble item.
        // USE ITEM!
    }
    else{                                                                           // Something else happened. Stop!
        throw(std::runtime_error("This item had an unexpected error."));
    }
    update_inventory_status_screen();
    redraw();
}

void gui_handler::check_current_inventory(){
    if((unsigned)inventoryBox->count() != gameplay->get_player()->get_items().size()){                   // Has the player's inventory changed?
        item* itemtobeadded = gameplay->get_player()->get_items().back();                        // Gets the last item to be added.
        QListWidgetItem* newItem = new QListWidgetItem(QString::fromStdString(itemtobeadded->get_name()), inventoryBox, 0);     // Creates a new listitem based on item.
        inventoryUIitem* newInventoryItem = new inventoryUIitem(itemtobeadded);
        inventoryBox->setItemWidget(newItem, newInventoryItem);
    }
}

void gui_handler::update_log(){
    std::string temp=gameplay->get_report();
    if(temp.size()>0)
        gui_handler::report_to_log(temp);
}

void gui_handler::report_to_log(const std::string sendtolog){
    gui_handler::command_log->append(QString::fromStdString(sendtolog));
    while(gui_handler::command_log->document()->blockCount() > 6){                              // Returns a QTextDocument that can count lines. 6 lines maximum.
        gui_handler::command_log->setFocus();                                                   // Sets focus on the command viewer.
        QTextCursor storeCursorPos = gui_handler::command_log->textCursor();                    // Stores current text cursor position.
        gui_handler::command_log->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);      // Moves text cursor to the start and puts an anchor there.
        gui_handler::command_log->moveCursor(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);  // Moves it to the end of the line, marks everything between anchor and it.
        gui_handler::command_log->textCursor().removeSelectedText();                            // Removes marked text (the entire line).
        gui_handler::command_log->textCursor().deleteChar();                                    // Deletes \n that resides after line delete.
        gui_handler::command_log->setTextCursor(storeCursorPos);                                // Sets the cursor back at the end.
    }
}

void gui_handler::update_hp_bar(){
    if(gameplay->get_player()->get_hp() > 0){
        delete hpLeft;
        float playerHP = (gameplay->get_player()->get_hp());
        float playerSTAM = (gameplay->get_player()->get_base_stamina() + gameplay->get_player()->get_stamina());
        float currentHPLeftPercentage = (playerHP / playerSTAM) * 100;
        float barSize = 100 / (100/currentHPLeftPercentage);
        hpLeft = new QGraphicsScene(600,243, barSize, 10);
        hpLeft->addRect(0,0,barSize,10,QPen(Qt::red), QBrush(Qt::red));
        hpBar->setSceneRect(0, 0, 100, 10);
        hpLeft->setSceneRect(0,0,100,10);
        hpBar->setScene(hpLeft);
    }
    else{
        delete hpLeft;
        hpLeft = new QGraphicsScene(0,0, 100, 20);
        hpBar->setScene(hpLeft);
    }
}

void gui_handler::initialize_inventory(){
    inventoryBox = new QListWidget(inventoryUI);                                    // Creates the list where items reside.
    inventoryBox->setGeometry(QRect(710, 100, 411, 531));                           // Set a certain pixel perfect size on this one.
    inventoryBox->setEditTriggers(QAbstractItemView::NoEditTriggers);               // You can't edit the items on the list.
    inventoryBox->setAlternatingRowColors(true);                                    // Makes them easier to distinguish
    inventoryBox->setSelectionMode(QAbstractItemView::SingleSelection);             // Can only select one item at a time.
    inventoryBox->setGridSize(QSize(50, 18));                                       // How large each item is inside the list.
    //inventoryBox->setSelectionRectVisible(false);

    weaponEquipBox = new QLineEdit(inventoryUI);                                    // The weapon equipped box where you see currently equipped stuff.
    weaponEquipBox->setGeometry(QRect(190, 120, 241, 21));
    weaponEquipBox->setReadOnly(true);                                              // Is not editable in any way, shape or form.

    armorEquipBox = new QLineEdit(inventoryUI);                                     // This is the same as weaponEquipBox, for armor.
    armorEquipBox->setGeometry(QRect(190, 190, 241, 21));
    armorEquipBox->setReadOnly(true);

    weaponLabel = new QLabel(inventoryUI);                                          // Label that says "Weapon: "
    weaponLabel->setGeometry(QRect(190, 90, 59, 16));

    armorLabel = new QLabel(inventoryUI);                                           // Label that says "Armor: "
    armorLabel->setGeometry(QRect(190, 160, 59, 16));

    inventoryLabel = new QLabel(inventoryUI);                                       // Label that says "Inventory: "
    inventoryLabel->setGeometry(QRect(710, 70, 59, 16));

    playerLabel = new QLabel(inventoryUI);                                          // Bold label that says "Player: "
    playerLabel->setGeometry(QRect(220, 300, 111, 21));

    connect(inventoryBox, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(player_inventory_usage()));    // If items inside the list are double clicked - Use that item.

    QFont font;                                                                     // Bold and underlined font for the "Player: " label.
    font.setBold(true);
    font.setUnderline(true);
    font.setWeight(75);
    playerLabel->setFont(font);

    // Status information
    line = new QFrame(inventoryUI);                                                 // Simple background to make it "Pop out" more.
    line->setGeometry(QRect(220, 330, 118, 3));
    hpLabel = new QLabel(inventoryUI);                                              // Label that says "HP: "
    hpLabel->setGeometry(QRect(220, 340, 59, 16));
    powerLabel = new QLabel(inventoryUI);                                           // Label that says "Power: "
    powerLabel->setGeometry(QRect(220, 360, 59, 16));
    armorlabelTwo = new QLabel(inventoryUI);                                        // Label that says "Armor: "
    armorlabelTwo->setGeometry(QRect(220, 380, 59, 16));
    hpEditable = new QLabel(inventoryUI);                                           // The HP label that is edited with update_inventory_status_screen().
    hpEditable->setGeometry(QRect(290, 340, 240, 16));
    powerEditable = new QLabel(inventoryUI);                                        // The power label that is edited with update_inventory_status_screen().
    powerEditable->setGeometry(QRect(290, 360, 120, 16));
    armorEditable = new QLabel(inventoryUI);                                        // The armor label that is edited with update_inventory_status_screen().
    armorEditable->setGeometry(QRect(290, 380, 120, 16));

    listView = new QListView(inventoryUI);
    listView->setGeometry(QRect(190, 260, 241, 191));
    listView->setAutoScroll(false);
    listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listView->setSelectionMode(QAbstractItemView::NoSelection);

    playerLabel->raise();                                                           // All status labels must be raised to not fall under the background.
    hpLabel->raise();
    powerLabel->raise();
    armorlabelTwo->raise();
    hpEditable->raise();
    powerEditable->raise();
    armorEditable->raise();

    weaponLabel->setText(QString("Weapon:"));                                      // Sets the label's text.
    armorLabel->setText(QString("Armor:"));
    inventoryLabel->setText(QString("Inventory:"));
    playerLabel->setText(QString("Player:"));
    hpLabel->setText(QString("HP:"));
    powerLabel->setText(QString("Power:"));
    armorlabelTwo->setText(QString("Armor:"));

}

void gui_handler::you_died(){
    QLabel* you_are_dead = new QLabel(centralWidget);
    you_are_dead->setGeometry(250,200, 700, 200);
    you_are_dead->setPixmap(QPixmap{":/images/THOU_ART_DEAD.png"});
    QPushButton* try_again_button = new QPushButton(QString(""), centralWidget);              // New game button
    try_again_button->setGeometry(QRect(450, 560, 320, 80));
    try_again_button->setIconSize(QSize(320, 80));                                           // button image is 320x80.
    try_again_button->setFlat(true);                                                         // Remove borders
   // try_again_button->setFocusPolicy(Qt::NoFocus);                                           // No tab possibilities

    // Use CSS instead of icon to remove on-click borders, hover and press changes.
    try_again_button->setStyleSheet("border: 0px solid #000000;	 background-image: url(:/images/button_try_again.png); }"
                                   "QPushButton:hover{ background-image: url(:/images/button_try_again_active.png); }"
                                   "QPushButton:pressed{  background-image: url(:/images/button_try_again.png); ");

    QPushButton* exit_button = new QPushButton(QString(""), centralWidget);
    exit_button->setGeometry(QRect(450, 650, 320, 80));
    exit_button->setIconSize(QSize(320, 80));
    exit_button->setFlat(true);
    //exit_button->setFocusPolicy(Qt::NoFocus);
    exit_button->setStyleSheet("border: 0px solid #000000;	 background-image: url(:/images/button_exit.png); }"
                                   "QPushButton:hover{ background-image: url(:/images/button_exit_active.png); }"
                                   "QPushButton:pressed{  background-image: url(:/images/button_exit.png); ");
    you_are_dead->show();
    try_again_button->show();
    exit_button->show();

    connect(try_again_button, SIGNAL (released()), gui_handler::centralWidget->parent()->parent()->parent()->parent(), SLOT (initialize_new_game()));  // When new game is pressed - Initialize a new game.
    connect(exit_button, SIGNAL(released()), gui_handler::centralWidget->parent()->parent()->parent()->parent(), SLOT(close()));       // When exit is pressed - Close the window and thus fully exit.
}

gui_handler::~gui_handler(){
    delete gameplay;
    delete hpLeft;
}
