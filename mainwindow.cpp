#include "mainwindow.h"

MainWindow::MainWindow(Game *game_, QWidget *parent):
    QMainWindow(parent)
{
    setMinimumSize(600, 600);
    setMaximumSize(600, 600);

//    GameFactory game_factory;
//    this->game = game_factory.create_game();
    this->game = game_;
    if(!game) exit(0);

    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, QColor(180, 133, 87));
    this->setPalette(palette);
}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    int pen_thin = 2, pen_thick = 4;
    QColor line_color(136, 76, 58);
    QPen thin_pen(line_color, pen_thin);
    QPen thick_pen(line_color, pen_thick);
    QPen black_stone_pen(QColor(28, 28, 28));
    QPen white_stone_pen(QColor(252, 250, 242));
    QBrush default_brush(Qt::transparent);
    QBrush black_stone_brush(QColor(28, 28, 28));
    QBrush white_stone_brush(QColor(252, 250, 242));
    double stone_radius_ratio = 0.4;

    QPainter painter(this);

    painter.setPen(thin_pen);
    painter.setBrush(default_brush);
    unsigned cols = game->board_width(), rows = game->board_height();
    grid_size = 600/((cols > rows ? cols : rows) - 1);
    unsigned stone_radius = stone_radius_ratio * grid_size;
    setFixedSize(grid_size * (cols + 1), grid_size * (rows + 1));
    // Antialiasing setting
    painter.setRenderHint(QPainter::Antialiasing);
    for(unsigned i = 0; i < cols; i++)
    {
        if(i == 0 || i == cols - 1)
            painter.setPen(thick_pen);
        else
            painter.setPen(thin_pen);
        painter.drawLine((i + 1) * grid_size, grid_size,
                         (i + 1) * grid_size, rows * grid_size);
    }
    for(unsigned i = 0; i < rows; i++)
    {
        if(i == 0 || i == rows - 1)
            painter.setPen(thick_pen);
        else
            painter.setPen(thin_pen);
        painter.drawLine(grid_size, (i + 1) * grid_size,
                         cols * grid_size, (i + 1) * grid_size);
    }
    for(unsigned i = 1; i <= rows; i++)
    for(unsigned j = 1; j <= cols; j++)
    {
        if(game->pos_status(i, rows - j + 1) == Game::black_stone)
        {
            painter.setPen(black_stone_pen);
            painter.setBrush(black_stone_brush);
            painter.drawEllipse(QPoint(i * grid_size, j * grid_size), stone_radius, stone_radius);
        }
        else if(game->pos_status(i, rows - j + 1) == Game::white_stone)
        {
            painter.setPen(white_stone_pen);
            painter.setBrush(white_stone_brush);
            painter.drawEllipse(QPoint(i * grid_size, j * grid_size), stone_radius, stone_radius);
        }
    }
    return;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        game->next();
        QPoint mouse_point = mapFromGlobal(QCursor::pos());
        int mouse_x = (mouse_point.x() + grid_size/2)/grid_size;
        int mouse_y = game->board_height() - (mouse_point.y() - grid_size/2)/grid_size;
        qDebug("x: %d, y: %d", mouse_x, mouse_y);
        game->input(mouse_x, mouse_y);
        game->next();
        repaint();
        game->next();
        repaint();
    }
}
