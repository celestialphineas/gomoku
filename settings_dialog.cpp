#include "settings_dialog.h"

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

    create_new_but(tr("创建新的游戏")),
    cancel_but(tr("取消")),

    width_validator(GameFactory::min_board_dim_width_threshold,
              GameFactory::max_board_dim_width_threshold),
    height_validator(GameFactory::min_board_dim_height_threshold,
                     GameFactory::max_board_dim_height_threshold)
{
    main_window = main_window_;
    setFixedSize(500, 200);
    setLayout(&layout);
    // Player settings
    player_setting_layout.addWidget(&human_vs_ai);
    human_vs_ai.setChecked(true);
    player_setting_layout.addWidget(&ai_vs_human);
    player_setting_layout.addWidget(&human_vs_human);
    player_setting_group.setLayout(&player_setting_layout);
    layout.addWidget(&player_setting_group, 0, 0);
    // Rule settings
    rule_layout.addWidget(&free_style);
    free_style.setChecked(true);
    rule_layout.addWidget(&std_gomoku);
    rule_layout.addWidget(&renju);
    rule_group.setLayout(&rule_layout);
    layout.addWidget(&rule_group, 0, 1);
    // Board settings
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
    // Buttons
    layout.addWidget(&create_new_but, 1, 0);
    layout.addWidget(&cancel_but, 1, 1);
}

