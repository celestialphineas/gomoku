#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QFont>
#include <QFontDatabase>
#include <string>
#include "game.h"
#include "game_factory.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Game *game_, QWidget *parent = 0);
    void set_game(Game *game_) {game = game_;}
    void set_dialog(QWidget *widget_) {dialog = widget_;}
    Game *get_game() {return game;}
    ~MainWindow();
private:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    unsigned grid_size;
    Game *game;

    int pen_thin = 2, pen_thick = 4;
    QColor board_color;
    QColor line_color;
    QColor black_stone_color;
    QColor white_stone_color;
    QColor invalid_but_color;
    QColor valid_but_color;
    QPen thin_pen;
    QPen thick_pen;
    QPen black_stone_pen;
    QPen white_stone_pen;
    QPen black_text_pen;
    QPen white_text_pen;
    QPen invalid_but_pen;
    QPen valid_but_pen;
    QBrush default_brush;
    QBrush black_stone_brush;
    QBrush white_stone_brush;
    double stone_radius_ratio;
    QFont fa;
    QFont minor;

    QWidget *dialog;
};

#endif // MAINWINDOW_H
