#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   // ui->setupUi(this);
    this->setFixedSize(1280,900);                                                           // Window size, 1280x900.
    QWidget::setWindowIcon(QIcon{":/images/icon_osx.png"});                                 // Set an icon.
    initialize_title_screen();                                                              // Start up the title screen.
    gui_handler_ = NULL;
}

void MainWindow::initialize_title_screen(){
    centralWidget = new QWidget(this);                                                      // Central container that we put all the interface elements into.
    this->setCentralWidget(centralWidget);
    title_screen = new QWidget(centralWidget);                                              // Title screen widget on top of centralWidget.
    title_screen->setGeometry(0,0,1280,900);                                                // Set title screen to the entire window.
    title_screen->setStyleSheet("background-image: url(:/images/background_title.png)");    // CSS - Set widget's background.
    QPushButton* new_game_button = new QPushButton(QString(""), title_screen);              // New game button
    new_game_button->setGeometry(QRect(450, 580, 320, 80));
    new_game_button->setIconSize(QSize(320, 80));                                           // button image is 320x80.
    new_game_button->setFlat(true);                                                         // Remove borders
    new_game_button->setFocusPolicy(Qt::NoFocus);                                           // No tab possibilities

    // Use CSS instead of icon to remove on-click borders, hover and press changes.
    new_game_button->setStyleSheet("border: 0px solid #000000;	 background-image: url(:/images/button_new_game.png); }"
                                   "QPushButton:hover{ background-image: url(:/images/button_new_game_active.png); }"
                                   "QPushButton:pressed{  background-image: url(:/images/button_new_game.png); ");

    QPushButton* about_button = new QPushButton(QString(""), title_screen);              // New game button
    about_button->setGeometry(QRect(460, 655, 320, 80));
    about_button->setIconSize(QSize(320, 80));                                           // button image is 320x80.
    about_button->setFlat(true);                                                         // Remove borders
    about_button->setFocusPolicy(Qt::NoFocus);                                           // No tab possibilities

    // Use CSS instead of icon to remove on-click borders, hover and press changes.
    about_button->setStyleSheet("border: 0px solid #000000;	 background-image: url(:/images/button_about.png); }"
                                  "QPushButton:hover{ background-image: url(:/images/button_about_active.png); }"
                                  "QPushButton:pressed{  background-image: url(:/images/button_about.png); ");

    QPushButton* exit_button = new QPushButton(QString(""), title_screen);
    exit_button->setGeometry(QRect(450, 730, 320, 80));
    exit_button->setIconSize(QSize(320, 80));
    exit_button->setFlat(true);
    exit_button->setFocusPolicy(Qt::NoFocus);
    exit_button->setStyleSheet("border: 0px solid #000000;	 background-image: url(:/images/button_exit.png); }"
                                   "QPushButton:hover{ background-image: url(:/images/button_exit_active.png); }"
                                   "QPushButton:pressed{  background-image: url(:/images/button_exit.png); ");


    connect(new_game_button, SIGNAL (released()), this, SLOT (initialize_new_game()));                          // When new game is pressed - Initialize a new game.
    connect(about_button, SIGNAL(released()), this, SLOT(showAbout()));
    connect(exit_button, SIGNAL(released()), this, SLOT(close()));                                              // When exit is pressed - Close the window and thus fully exit.
}

void MainWindow::showAbout(){
    QMessageBox* about = new QMessageBox();

    about->setIconPixmap(QPixmap{QString(":/images/creature_king.png")});
    about->setText(QString::fromStdString("Made by Sondre Husevold (s198755) and Magnus Tønsager (s198761)."));
    about->setInformativeText("Spacefox tileset made by Spacefox and Sphyr for Dwarf Fortress.\nWebsite: http://www.bay12forums.com/smf/index.php?topic=129219.0");
    about->setStandardButtons(QMessageBox::Ok);
    about->exec();
    delete about;
}

void MainWindow::initialize_new_game(){
    if(playerName.isEmpty()){
        bool confirm;
        playerName = QInputDialog::getText(centralWidget, tr("What is your name?"),
                                             tr("Please input your name:"), QLineEdit::Normal,
                                             "", &confirm);
    }
    delete centralWidget;                                      // Call destructor on the title screen.
    if(gui_handler_){                                          // If game already exists, call destructor on everything connected to old game.
        delete gui_handler_;
        delete keyboard_left;
        delete keyboard_right;
        delete keyboard_up;
        delete keyboard_down;
        delete keyboard_i;
        delete keyboard_m;
    }
    centralWidget = new QWidget(this);                         // Central container that we put all the interface elements into.
    this->setCentralWidget(centralWidget);
    tabWidget = new QTabWidget(centralWidget);                 // Tab widget for tabs.
    tabWidget->setGeometry(QRect(0, 0, 1280, 900));            // Tab widget takes entire window.
    Game = new QWidget(centralWidget);                                      // Create widget to put stuff in game tab.
    tabWidget->insertTab(0, Game, QString());                  // Create a new tab and use game widget as central container.
    Inventory = new QWidget();                                 // Create inventory widget to put stuff in inventory tab.
    tabWidget->insertTab(1, Inventory, QString());             // Create a new tab and use invetory as central widget.
    Map = new QWidget();                                       // Create map widget for map tab.
    QPalette Palette(palette());                               // Create a pallete for map's background.
    Palette.setColor(QPalette::Background, Qt::black);         // Map's widget's background is sat as black.
    Map->setAutoFillBackground(true);                          // Fill the entire widget's background with black.
    Map->setPalette(Palette);                                  // Set it pallette.
    tabWidget->insertTab(2, Map, QString());                   // Create a new tab - Insert map into said tab.
    gui_handler_ = new gui_handler(playerName.toStdString(), Game, Inventory, Map, this);                // Creates a new gui_handler to handle the gui.
    for(int x = 0; x < 10; x++){                                        // Connect the 10x6 grid of buttons with right and left click.
        for(int y = 0; y < 6; y++){
            connect(gui_handler::buttons[x][y], SIGNAL (released()), gui_handler::buttons[x][y], SLOT (left_click_tile()));     // Connect tile with left click.
            connect(gui_handler::buttons[x][y], SIGNAL(right_clicked()), gui_handler::buttons[x][y], SLOT(right_click_tile())); // Connect tile with right click.
        }
    }
    tabWidget->setCurrentIndex(0);              // When created, start on game tab.

   tabWidget->setTabText(tabWidget->indexOf(Game), QApplication::translate("MainWindow", "Game", 0));                  // Set name of first tab - Game
   tabWidget->setTabText(tabWidget->indexOf(Inventory), QApplication::translate("MainWindow", "Inventory (I)", 0));        // Set name of second tab - Inventory
   tabWidget->setTabText(tabWidget->indexOf(Map), QApplication::translate("MainWindow", "Map (M)", 0));                    // Set name of third tab - Map.

    keyboard_left = new QAction(this);                         // Sets left key.
    keyboard_left->setShortcut(Qt::Key_Left);

    connect(keyboard_left, SIGNAL(triggered()), gui_handler_, SLOT(move_left()));
    this->addAction(keyboard_left);

    keyboard_right = new QAction(this);                        // Sets right key.
    keyboard_right->setShortcut(Qt::Key_Right);

    connect(keyboard_right, SIGNAL(triggered()), gui_handler_, SLOT(move_right()));
    this->addAction(keyboard_right);

    keyboard_up = new QAction(this);                           // Set up key.
    keyboard_up->setShortcut(Qt::Key_Up);

    connect(keyboard_up, SIGNAL(triggered()), gui_handler_, SLOT(move_up()));
    this->addAction(keyboard_up);

    keyboard_down = new QAction(this);                         // Set down key.
    keyboard_down->setShortcut(Qt::Key_Down);

    connect(keyboard_down, SIGNAL(triggered()), gui_handler_, SLOT(move_down()));
    this->addAction(keyboard_down);

    keyboard_m = new QAction(this);                         // Set M key.
    keyboard_m->setShortcut(Qt::Key_M);

    connect(keyboard_m, SIGNAL(triggered()), this, SLOT(change_to_map()));
    this->addAction(keyboard_m);

    keyboard_i = new QAction(this);                         // Set I key.
    keyboard_i->setShortcut(Qt::Key_I);

    connect(keyboard_i, SIGNAL(triggered()), this, SLOT(change_to_inventory()));
    this->addAction(keyboard_i);


    connect(tabWidget, SIGNAL(currentChanged(int)), gui_handler_, SLOT(redraw_map(int)));
}

void MainWindow::change_to_map(){               // Slot for "M" keyboard press.
    if(tabWidget->currentIndex() != 2)          // On a tab other than "Map"
        tabWidget->setCurrentIndex(2);          // Go to "Map"
    else
        tabWidget->setCurrentIndex(0);          // Otherwise go to game.
}

void MainWindow::change_to_inventory(){         // Slot for "I" keyboard press.
    if(tabWidget->currentIndex() != 1)          // ON a tab other than "Inventory"
        tabWidget->setCurrentIndex(1);          // Go to Inventory.
    else
        tabWidget->setCurrentIndex(0);          // Otherwise go to game.
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gui_handler_;//seg fault her hvis spill avsluttes fra tittle screen
}
