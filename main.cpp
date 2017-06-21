#include <QApplication>
#include "mainwindow.h"
#include "settings_dialog.h"
#include "game_factory.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game *new_game = GameFactory::create_game();

    MainWindow w(new_game);
    SettingsDialog dialog(&w);

    w.show();
    dialog.show();

    return a.exec();
}
