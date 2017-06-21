#include <QApplication>
#include "mainwindow.h"
#include "game_factory.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameFactory game_factory;
    Game *new_game = game_factory.create_game();

    MainWindow w(new_game);
    w.show();

    return a.exec();
}
