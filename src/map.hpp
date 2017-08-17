#ifndef MAP_HPP
#define MAP_HPP

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QScrollArea>
#include <QGraphicsScene>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include "game.hpp"

class map : public QObject{

    Q_OBJECT

    QWidget* centralWidget;                     // Map widget
    QGraphicsScene* tiles;                      // Scene which all the map tiles are painted on
    QGraphicsView* grapViewer;                  // GraphicsView that shows the scene
    QScrollArea* scrollings;                    // Scrollbars-

public:
    game* currentLevel;                         // Required to get level layout
    map(QWidget* centralWidget_, game* currentLevel_, QObject * parent = 0);
    void redraw();                              // Redraws the entire map
    QPixmap convert_to_map_tile(char y);        // Converts characters into small map tiles
    virtual ~map();                             // Required destructor
};

#endif // MAP_HPP
