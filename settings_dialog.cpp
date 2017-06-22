#include "settings_dialog.h"

/**
 * Draw the dialog for game setting
 * @param main_window_
 * @param parent
 */
SettingsDialog::SettingsDialog(MainWindow *main_window_, QWidget *parent) :
    QWidget(parent),

    player_setting_group(tr("对弈模式")),
    human_vs_ai(tr("人类 vs AI")),
    ai_vs_human(tr("AI vs 人类")),
    human_vs_human(tr("人类 vs 人类")),

    rule_group(tr("规则")),
    free_style(tr("自由")),
    std_gomoku(tr("长连不胜")),
    renju(tr("连珠（禁手）")),

    board_setting_group(tr("棋盘尺寸")),
    width_label(tr("宽度")),
    height_label(tr("高度")),

    round_setting_group(tr("局")),
    round1(tr("一局定胜")),
    round5(tr("五局三胜")),

    create_new_but(tr("创建新的游戏")),
    cancel_but(tr("取消")),

    //Confirm whether the input of width and height is valid
    width_validator(GameFactory::min_board_dim_width_threshold,
                    GameFactory::max_board_dim_width_threshold),
    height_validator(GameFactory::min_board_dim_height_threshold,
                     GameFactory::max_board_dim_height_threshold)

{
  setWindowIcon(QIcon(":/icons/icon.ico"));
  main_window = main_window_;
  setFixedSize(450, 280);
  setLayout(&layout);
  //Draw the group box for player settings
  player_setting_layout.addWidget(&human_vs_ai);
  human_vs_ai.setChecked(true);
  player_setting_layout.addWidget(&ai_vs_human);
  player_setting_layout.addWidget(&human_vs_human);
  player_setting_group.setLayout(&player_setting_layout);
  layout.addWidget(&player_setting_group, 0, 0);

  //Draw the group box for rule settings
  rule_layout.addWidget(&free_style);
  free_style.setChecked(true);
  rule_layout.addWidget(&std_gomoku);
  rule_layout.addWidget(&renju);
  rule_group.setLayout(&rule_layout);
  layout.addWidget(&rule_group, 0, 1);

  //Draw the group box for board size settings
  board_setting_layout.addWidget(&width_label);
  board_setting_layout.addWidget(&width_edit);
  width_edit.setText("15");
  width_edit.setValidator(&width_validator);
  board_setting_layout.addWidget(&height_label);
  board_setting_layout.addWidget(&height_edit);
  height_edit.setText("15");
  height_edit.setValidator(&height_validator);
  board_setting_group.setLayout(&board_setting_layout);
  layout.addWidget(&board_setting_group, 0, 2);

  //Draw the group box for board size setting
  round_setting_layout.addWidget(&round1);
  round1.setChecked(true);
  round_setting_layout.addWidget(&round5);
  round_setting_group.setLayout(&round_setting_layout);
  layout.addWidget(&round_setting_group, 1, 0, 2, 1);

  //Buttons for create a new game or not
  layout.addWidget(&create_new_but, 1, 2);
  layout.addWidget(&cancel_but, 2, 2);

  // Signal slot connection
  connect(&create_new_but, SIGNAL(clicked()), SLOT(create_game_object()));
  connect(&cancel_but, SIGNAL(clicked()), SLOT(toggle_this()));
}

/**
 * Create a game object according to the setting.
 */
void SettingsDialog::create_game_object() {
  GameFactory::PlayerType player1_type;
  GameFactory::PlayerType player2_type;
  GameFactory::GameRule game_rule = GameFactory::standard_rule;
  GameFactory::GameJudge game_judge;
  unsigned to_set_width = width_edit.text().toUInt();
  unsigned to_set_height = height_edit.text().toUInt();
  unsigned to_set_n_round;

  //player settings
  if (human_vs_ai.isChecked()) {
    player1_type = GameFactory::human_player;
    player2_type = GameFactory::primary_ai;
  } else if (ai_vs_human.isChecked()) {
    player1_type = GameFactory::primary_ai;
    player2_type = GameFactory::human_player;
  } else {
    player1_type = GameFactory::human_player;
    player2_type = GameFactory::human_player;
  }

  //judge rule ettings
  if (free_style.isChecked()) {
    game_judge = GameFactory::free_style_gomoku;
  } else if (std_gomoku.isChecked()) {
    game_judge = GameFactory::standard_gomoku;
  } else {
    game_judge = GameFactory::renju;
  }

  //Set the number of round
  if (round1.isChecked()) {
    to_set_n_round = 1;
  } else {
    to_set_n_round = 5;
  }

  //Create a game object according to the setting parameter
  Game *new_game = GameFactory::create_game(to_set_n_round,
                                            player1_type,
                                            player2_type,
                                            game_rule,
                                            game_judge,
                                            to_set_width,
                                            to_set_height);

  //If a new game is created successfully, delete the default game and show the new game in main window
  if (new_game) {
    Game *to_delete = main_window->get_game();
    main_window->set_game(new_game);
    delete to_delete;
    main_window->update();
    this->hide();
    main_window->show();
  }
}

