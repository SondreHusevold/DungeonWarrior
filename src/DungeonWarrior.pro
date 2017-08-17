#-------------------------------------------------
#
# Project created by QtCreator 2015-04-16T12:06:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DungeonWarrior
TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    game_button.cpp \
    block.cpp \
    clickable.cpp \
    level.cpp \
    position.cpp \
    visible.cpp \
    gui_handler.cpp \
    creature.cpp \
    monster.cpp \
    player.cpp \
    item.cpp \
    game.cpp \
    monster_factory.cpp \
    map.cpp \
    deathwing_factory.cpp \
    monoroth_factory.cpp \
    warlord_factory.cpp \
    warrior_factory.cpp \
    warscout_factory.cpp \
    wrathguard_factory.cpp \
    wyrmguard_factory.cpp \
    item_database.cpp \
    inventoryuiitem.cpp \
    reportable.cpp

HEADERS  += mainwindow.h \
    game_button.h \
    block.hpp \
    clickable.hpp \
    level.hpp \
    position.hpp \
    visible.hpp \
    gui_handler.hpp \
    creature.hpp \
    monster.hpp \
    player.hpp \
    item.hpp \
    game.hpp \
    abstract_monster_factory.hpp \
    monster_factory.hpp \
    map.hpp \
    deathwing_factory.hpp \
    monoroth_factory.hpp \
    warlord_factory.hpp \
    warrior_factory.hpp \
    warscout_factory.hpp \
    wrathguard_factory.hpp \
    wyrmguard_factory.hpp \
    item_database.hpp \
    inventoryuiitem.hpp \
    reportable.hpp

FORMS    += mainwindow.ui

RESOURCES = resources.qrc

RC_FILE = icon_windows.rc       # Windows Icon
ICON = icon_osx.icns     # OS X Icon

QMAKE_CXXFLAGS += -std=c++11
macx{
QMAKE_CXXFLAGS += -std=c++0x -stdlib=libc++
QMAKE_LFLAGS += -lc++
}
