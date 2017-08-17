#include <game_button.h>
#include <mainwindow.h>


game_button::game_button(const QString & text, game* gameplay_, QWidget * parent) : QPushButton(text, parent), gameplay{gameplay_}{
    setIconSize(QSize(128, 128));                                                   // The icon is 128x128. Always.
    setText(QString(""));                                                           // Always no text on the button.
}

clickable* game_button::get_element(){
    return click_item;                                                              // Get current held thing whatever it might be.
}

void game_button::set_element(clickable* c){
    click_item = c;                                                                 // Can be anything. Block, player, monster, anything clickable.
}

void game_button::mousePressEvent(QMouseEvent *e) {
    if(e->button()==Qt::RightButton)
        emit right_clicked();                                                       // If the event is Qt::RightButton then it'll emit right clicked as a signal.
    else{
        emit released();                                                            // Otherwise it's a left click always.
    }
}

void game_button::redraw(){                                                         // Redraws this button's icon.
    QIcon icon;                                                                     //Create temporary icon.
    if(!click_item->is_visible())
       icon = gui_handler::convert_to_icon('b');                                    // Unecessary ?? (!)
    else
        icon = gui_handler::convert_to_icon(click_item->get_icon());                // Get clickable thing's icon.
     setIcon(icon);                                                                 // Sets the icon
}

void game_button::left_click_tile(){
    gameplay->left_click_action(click_item);                                        // Do a left click action.
    gui_handler::update_log();
}

void game_button::right_click_tile(){                                               // Same implementation as left_click_tile.
    gui_handler::report_to_log(click_item->to_string());                            // Right click always reports back the block's description.
}


game_button::~game_button(){
    gameplay=nullptr;
}
