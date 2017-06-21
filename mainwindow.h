#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <string>
#include "game.h"
#include "game_factory.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Game *game_, QWidget *parent = 0);
    void set_game(Game *game_);
    ~MainWindow();
private:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    unsigned grid_size;
    Game *game;
};

#endif // MAINWINDOW_H
