#ifndef GUI_HANDLER
#define GUI_HANDLER
#include <game_button.h>
#include <game.hpp>
#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QListView>
#include <QGraphicsView>
#include <stdexcept>
#include "gui_handler.hpp"
#include "map.hpp"
#include "inventoryuiitem.hpp"

class gui_handler : public QObject{

    Q_OBJECT                                                // REQUIRED

    static QWidget* centralWidget;                          // This is the "Game" widget
    QWidget* inventoryUI;                                   // This is the inventory widget
    QWidget* mapUI;                                         // This is the map widget


public:
    static const int MAX_VIEWABLE_TILES_X = 10;             // Amount of buttons in Game widget on the X-axis.
    static const int MAX_VIEWABLE_TILES_Y = 6;              // Amount of buttons in Game widget on the Y-axis.
    gui_handler(std::string playername, QWidget* centralWidget_, QWidget* inventoryUI_, QWidget* mapUI_, QObject * parent = 0);
    bool disableControls = false;                           // Disables the controls if the player is on other tabs.
    static game* gameplay;                                  // Game, required for many things.
    static map* currentMap;                                 // Map of the current level
    static game_button* buttons[10][6];                     // The viewable game board. Must be static for get_button().
    static QTextEdit *command_log;                          // command log text. Must be static for report_to_log()
    static QIcon convert_to_icon(char charactericon);       // Static so we can convert an icon always.
    static void update_log();                               // Bruker report_to_log() til å oppdatere loggen fra game.get_report()
    static void report_to_log(std::string sendtolog);       // Static so we can send information to the log always.
    static game_button* get_button(int x, int y);           // Static so we can get a button's properties always.
    static void redraw();                                   // Redraw all tiles. Needs to be static so turn() in game can do it.
    static void check_current_inventory();                  // Checks the current inventory for any new items
    static void update_hp_bar();                            // Updates the HP on the bar
    void update_inventory_status_screen();                  // Updates the HP, power and armor on the inventory screen
    void initialize_inventory();                            // Initializes the inventory at the beginning
    static void you_died();                                 // Shows a death screen.
    virtual ~gui_handler();


public slots:
    void move_up();                     // Move character up.
    void move_down();                   // Move character down.
    void move_right();                  // Move character right.
    void move_left();                   // Move character left.
    void player_inventory_usage();      // Equips the player from the UI.
    void redraw_map(int i);


private:
    static QGraphicsView* hpBar;        // HP bar
    static QGraphicsScene* hpLeft;      // HP bar's scene
    QLabel *weaponLabel;
    QLabel *armorLabel;
    QLabel *inventoryLabel;
    QLabel *playerLabel;
    QLabel *hpLabel;
    QLabel *powerLabel;
    QLabel *armorlabelTwo;
    QFrame *line;                       // Player's status background
    QListView *listView;                // QListWidget's model
    static QLabel *hpEditable;          // HP that updates automatically
    static QLabel *powerEditable;       // Power that updates
    static QLabel *armorEditable;       // Armor that updates
    QLineEdit *weaponEquipBox;          // Shows equipped weapon
    QLineEdit *armorEquipBox;           // Shows equipped armor
    static QListWidget *inventoryBox;   // Inventory shown
};

#endif // GUI_HANDLER

