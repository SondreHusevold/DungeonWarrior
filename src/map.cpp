#include "map.hpp"
#include <gui_handler.hpp>

map::map(QWidget* centralWidget_, game* currentLevel_, QObject * parent) : QObject(parent), centralWidget{centralWidget_}, currentLevel{currentLevel_} {
    scrollings = new QScrollArea(centralWidget);                                                                    // Create a new ScrollArea
    scrollings->setGeometry(0,0,1275,871);                                                                          // Sets the grapViewer so that the scrollbars are visible
    grapViewer = new QGraphicsView(scrollings);                                                                     // Set the GraphicsView inside the scrolling area.
    grapViewer->setGeometry(QRect(0,0, 32*(level::MAX_POSITION_X+1), 32*(level::MAX_POSITION_Y+1)));                // Sets the graphViewer's map size to level's MAX position.
    scrollings->setWidget(grapViewer);
    QBrush brushBack(Qt::black);                                                                                    // Create a black brush to paint the background.
    grapViewer->setBackgroundBrush(brushBack);                                                                      // Paint it black
    tiles = new QGraphicsScene(0,0, 32*(level::MAX_POSITION_X+1), 32*(level::MAX_POSITION_Y+1),centralWidget);      // Create a new scene temporarily.
    redraw();                                                                                                       // Redraw everything.
}

QPixmap map::convert_to_map_tile(char y){                               // Converts chars into map tiles at 9x9 pixels.
    if(y == '#')
        return QPixmap{QString(":/images/map_wall.png")};               // Wall
    else if(y == 'D')
        return QPixmap{QString(":/images/map_stairs_down.png")};        // Stairs down
    else if(y == 'U')
        return QPixmap{QString(":/images/map_stairs_up.png")};          // Stairs up
    else if(y == '@')
        return QPixmap{QString(":/images/map_creature_naked.png")};     // Player
    else if(y == 'A')
        return QPixmap{QString(":/images/map_creature_armored.png")};   // Player when armored.
    else if(y == 'S')
        return QPixmap{QString(":/images/map_skeleton.png")};           // Dead player.
    return QPixmap{QString(":/images/map_floor.png")};                  // Floor
}

void map::redraw(){
    delete tiles;                                                                                                  // Deletes the previous map redraw.
    tiles = new QGraphicsScene(0,0, 32*(level::MAX_POSITION_X+1), 32*(level::MAX_POSITION_Y+1),centralWidget);     // Sets the scene's size to level's max position.
    for(int x = 0; x <= level::MAX_POSITION_X; x++){                                                               // Each floor is as big as level's max pos (default: 101x101).
        for(int y = 0; y <= level::MAX_POSITION_Y; y++){
            if(currentLevel->get_block(x, y)->is_visible()){                                                       // Fog of War - Has the player been here before?
                QGraphicsPixmapItem* anewtile = new QGraphicsPixmapItem(convert_to_map_tile(currentLevel->get_block(x, y)->get_icon()));    // Creates a image item
                anewtile->setPos(((x*32)), (32*y));                                                                                         // Sets that item at 32x32 position * x or y.
                tiles->addItem(anewtile);                                                                                                   // Adds the item to the scene.
            }
        }
    }
    QGraphicsPixmapItem* playertile = new QGraphicsPixmapItem(convert_to_map_tile(currentLevel->get_player()->get_icon()));                 // Create image of the player as well
    playertile->setPos(((currentLevel->get_player()->x()*32)), (32*currentLevel->get_player()->y()));                                       // At current player position
    tiles->addItem(playertile);                                                                                                             // Add the player to the scene
    grapViewer->setScene(tiles);                                                                                                            // Add the scene to the grapViewer
    grapViewer->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));                                                                       // No scrollbars. ScrollArea fixes this.
    grapViewer->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));                                                                     // No scrollbars, ScrollArea fixes this.
    scrollings->ensureVisible(((currentLevel->get_player()->x()*32)-640), ((currentLevel->get_player()->y()*32)-450), 50, 50);              // When redrawn, scroll automatically to player position.
}

map::~map(){}

