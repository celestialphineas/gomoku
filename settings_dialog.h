#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include "mainwindow.h"

class SettingsDialog: public QWidget {
 Q_OBJECT
 public:
  //The dialog for game setting
  explicit SettingsDialog(MainWindow *main_window_, QWidget *parent = 0);
 public slots:
  //Create a game object according to the setting
  void create_game_object();
  void toggle_this() {
    this->hide();
    main_window->show();
  }
 private:
  //GUI elements for the dialog
  QGridLayout layout;

  MainWindow *main_window;

  QGroupBox player_setting_group;
  QVBoxLayout player_setting_layout;
  QRadioButton human_vs_ai, ai_vs_human, human_vs_human;

  QGroupBox rule_group;
  QVBoxLayout rule_layout;
  QRadioButton free_style, std_gomoku, renju;

  QGroupBox board_setting_group;
  QVBoxLayout board_setting_layout;
  QLabel width_label, height_label;
  QLineEdit width_edit, height_edit;

  QGroupBox round_setting_group;
  QVBoxLayout round_setting_layout;
  QRadioButton round1, round5;

  QIntValidator width_validator;
  QIntValidator height_validator;

  QPushButton create_new_but;
  QPushButton cancel_but;
};

#endif // SETTINGS_DIALOG_H
