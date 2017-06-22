#include "mainwindow.h"

/**
 * Main window of the program
 * @param game_
 * @param parent
 */
MainWindow::MainWindow(Game *game_, QWidget *parent) :
    QMainWindow(parent),
    board_color(180, 133, 87),
    line_color(136, 76, 58),
    black_stone_color(28, 28, 28),
    white_stone_color(252, 250, 242),
    invalid_but_color(line_color),
    valid_but_color(black_stone_color),
    thin_pen(line_color, pen_thin),
    thick_pen(line_color, pen_thick),
    black_stone_pen(Qt::transparent, pen_thin),
    white_stone_pen(Qt::transparent, pen_thin),
    black_text_pen(black_stone_color),
    white_text_pen(white_stone_color),
    invalid_but_pen(invalid_but_color),
    valid_but_pen(valid_but_color),
    default_brush(Qt::transparent),
    black_stone_brush(black_stone_color),
    white_stone_brush(white_stone_color),
    stone_radius_ratio(0.4) {
  setMinimumSize(600, 600);
  setMaximumSize(600, 600);

  this->game = game_;
  if (!game) exit(0);

  //Set color of the board
  QPalette palette(this->palette());
  palette.setColor(QPalette::Background, board_color);
  this->setPalette(palette);

  //Set font
  QFontDatabase::addApplicationFont(":/fonts/fa.ttf");
  fa.setFamily("FontAwesome");
  fa.setPixelSize(26);
  minor.setFamily("Helvetica, Helvetica Neue, Arial");
  minor.setPixelSize(20);
}

MainWindow::~MainWindow() {

}

/**
 * Use QPainter to draw the board
 * @param event
 */
void MainWindow::paintEvent(QPaintEvent *event) {
  setWindowIcon(QIcon(":/icons/icon.ico"));
  QPainter painter(this);

  //Set pen and brush of the painter
  painter.setPen(thin_pen);
  painter.setBrush(default_brush);

  unsigned cols = game->board_width(), rows = game->board_height();

  //Calculate size of every grid
  grid_size = 600 / ((cols > rows ? cols : rows) - 1);

  //Calculate stone radius,windows' width and height according to the grid size
  unsigned stone_radius = stone_radius_ratio * grid_size;
  unsigned window_width = grid_size * (cols + 1);
  unsigned window_height = grid_size * (rows + 1.5);
  setFixedSize(window_width, window_height + 20);

  //Antialiasing setting
  painter.setRenderHint(QPainter::Antialiasing);

  //Draw the board
  for (unsigned i = 0; i < cols; i++) {
    if (i == 0 || i == cols - 1)
      painter.setPen(thick_pen);
    else
      painter.setPen(thin_pen);
    painter.drawLine((i + 1) * grid_size, grid_size,
                     (i + 1) * grid_size, rows * grid_size);
  }
  for (unsigned i = 0; i < rows; i++) {
    if (i == 0 || i == rows - 1)
      painter.setPen(thick_pen);
    else
      painter.setPen(thin_pen);
    painter.drawLine(grid_size, (i + 1) * grid_size,
                     cols * grid_size, (i + 1) * grid_size);
  }

  //Draw the stones
  for (unsigned i = 1; i <= rows; i++)
    for (unsigned j = 1; j <= cols; j++) {
      if (game->pos_status(i, rows - j + 1) == Game::black_stone) {
        painter.setPen(black_stone_pen);
        painter.setBrush(black_stone_brush);
        painter.drawEllipse(QPoint(i * grid_size, j * grid_size), stone_radius, stone_radius);
      } else if (game->pos_status(i, rows - j + 1) == Game::white_stone) {
        painter.setPen(white_stone_pen);
        painter.setBrush(white_stone_brush);
        painter.drawEllipse(QPoint(i * grid_size, j * grid_size), stone_radius, stone_radius);
      }
    }

  //Draw the symbols
  //Go previous
  fa.setPixelSize(grid_size);
  painter.setFont(fa);
  if (game->previous_round_validity()) painter.setPen(valid_but_pen);
  else painter.setPen(invalid_but_pen);
  painter.drawText(grid_size / 2, window_height - grid_size, grid_size, grid_size, Qt::AlignCenter, QChar(0xf104));

  //Current status
  if (game->current_status() == Game::not_started) {
    painter.setPen(valid_but_pen);
    painter.drawText(grid_size * 3 / 2,
                     window_height - grid_size,
                     grid_size,
                     grid_size,
                     Qt::AlignCenter,
                     QChar(0xf04b));
  } else if (game->current_status() == Game::ongoing) {
    painter.setPen(invalid_but_pen);
    painter.drawText(grid_size * 3 / 2,
                     window_height - grid_size,
                     grid_size,
                     grid_size,
                     Qt::AlignCenter,
                     QChar(0xf111));
  } else if (game->current_status() == Game::black_wins) {
    painter.setPen(black_text_pen);
    painter.drawText(grid_size * 3 / 2,
                     window_height - grid_size,
                     grid_size,
                     grid_size,
                     Qt::AlignCenter,
                     QChar(0xf111));
  } else if (game->current_status() == Game::white_wins) {
    painter.setPen(white_text_pen);
    painter.drawText(grid_size * 3 / 2,
                     window_height - grid_size,
                     grid_size,
                     grid_size,
                     Qt::AlignCenter,
                     QChar(0xf111));
  }
  //Rounds
  painter.setPen(invalid_but_pen);
  painter.setFont(minor);
  painter.drawText(grid_size * 5 / 2,
                   window_height - grid_size,
                   grid_size,
                   grid_size,
                   Qt::AlignCenter,
                   QString::number(game->current_round()) + "/" + QString::number(game->n_rounds()));
  //Go next
  painter.setFont(fa);
  if (game->next_round_validity() &&
      (game->current_status() == Game::black_wins
          || game->current_status() == Game::white_wins))
    painter.setPen(valid_but_pen);
  else painter.setPen(invalid_but_pen);
  painter.drawText(grid_size * 7 / 2, window_height - grid_size, grid_size, grid_size, Qt::AlignCenter, QChar(0xf105));

  //Settings
  painter.setPen(valid_but_pen);
  painter.drawText(window_width - grid_size * 3 / 2,
                   window_height - grid_size,
                   grid_size,
                   grid_size,
                   Qt::AlignCenter,
                   QChar(0xf142));
  return;
}

/**
 * Monitor mouse press event which decide the behavior of main window
 * @param event
 */
void MainWindow::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {//When mouse's left button is pressed
    game->next();
    QPoint mouse_point = mapFromGlobal(QCursor::pos());

    //Define coordinate of the board
    int mouse_x = (mouse_point.x() + grid_size / 2) / grid_size;
    int mouse_y = game->board_height() - (mouse_point.y() - grid_size / 2) / grid_size;

    //When previous round is valid and the previous round symbol is pressed, switch to previous round
    if (game->previous_round_validity()
        && mouse_x == 1 && mouse_y == 0) {
      game->switch_to_previous_round();
      repaint();
    }

    //When next round is valid and the previous round symbol is pressed, switch to next round
    if (game->next_round_validity() &&
        (game->current_status() == Game::black_wins
            || game->current_status() == Game::white_wins)
        && mouse_x == 4 && mouse_y == 0) {
      game->switch_to_next_round();
      repaint();
    }

    //When the setting symbol is pressed, show the setting dialog
    if (mouse_x == game->board_width() && mouse_y == 0) {
      dialog->show();
      hide();
    }

    //When the game is going, change the mouse event into input of the game
    if (game->current_status() == Game::ongoing) {
      game->input(mouse_x, mouse_y);
      game->next();
      repaint();
      game->next();
      repaint();
    }
  }
}
