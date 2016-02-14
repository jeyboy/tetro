#-------------------------------------------------
#
# Project created by QtCreator 2016-02-02T01:13:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tetro
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    items/rect_item.h \
    tetro_scene.h \
    items/tetro_item.h \
    tetro_game.h \
    items/block_item.h \
    items/li_item.h \
    items/li_rev_item.h \
    items/line_item.h \
    items/ti_item.h \
    items/zu_item.h \
    items/zu_rev_item.h \
    items/index.h \
    items/tetro_part.h \
    items/text_item.h \
    items/rotation_container.h

FORMS    += mainwindow.ui
