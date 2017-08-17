#ifndef GAME_BUTTON
#define GAME_BUTTON
#include <QPushButton>
#include <QObject>
#include <clickable.hpp>
#include <visible.hpp>
#include <QMouseEvent>
#include <QTextEdit>
#include <QIcon>
#include "game.hpp"


class game_button : public QPushButton{

    Q_OBJECT                                // REQUIRED!

    clickable* click_item;                  // All clickable things

public:
    game_button(const QString & text, game* gameplay_, QWidget * parent = 0);
    clickable* get_element();               // Gets the block or element that this button currently represents
    void set_element(clickable* c);         // Sets a new block or element that this button should represent
    void redraw();                          // Redraw this block to show it's new form
    game * gameplay;                        // Required for left_click actions
    virtual ~game_button();                 // Destructor

private slots:
    void mousePressEvent(QMouseEvent *e);       // Required to be able to do both right and left click actions

signals:
    void right_clicked();                       // Right click signal when button is right clicked

public slots:
    void left_click_tile();                     // Left clicked action
    void right_click_tile();                    // Right clicked action
};

#endif // GAME_BUTTON

