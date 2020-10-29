#include "pingpongview.h"
#include "ui_pingpongview.h"

#define SIZE_X 32
#define SIZE_Y 16

pingpongview::pingpongview(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pingpongview)
{
    //16х16

    ui->setupUi(this);
    view_board = new QLabel**[SIZE_Y];
    for (int i = 0; i < SIZE_Y ;i++ )
    {
        view_board[i] = new QLabel*[SIZE_X];
    }
    //
    //Create board
    //
    for (int i = 0; i < SIZE_Y; i++ ) {
        QHBoxLayout* line = new QHBoxLayout;
        line->setSpacing(0);
        for (int j = 0 ; j < SIZE_X; j++ ) {
            QVBoxLayout* cell = new QVBoxLayout;
            QLabel* label = new QLabel;
            QPixmap pixmap(30,30);
            pixmap.fill(Qt::white);
            label->setPixmap(pixmap);
            cell->addWidget(label);
            line->addLayout(cell);
            view_board[i][j] = label;

        }
        ui->field->addLayout(line);
    }
    //
    //start pos
    //
    board.reset(new pingpongmodel);
    QPair<int,int>* player1_pos = board->get_player1_pos();
    QPair<int,int>* player2_pos = board->get_player2_pos();
    QPair<int,int> ball_pos = board->get_ball_pos();
    QPixmap pixmap(30,30);
    pixmap.fill(Qt::red);

    view_board[ball_pos.second][ball_pos.first]->setPixmap(pixmap);
    for (int i = 0 ; i < 4 ;i++)
    {
        QPixmap pixmap(30,30);
        pixmap.fill(Qt::black);
        view_board[player1_pos[i].second][player1_pos[i].first]->setPixmap(pixmap);

        view_board[player2_pos[i].second][player2_pos[i].first]->setPixmap(pixmap);
    }
    //
    //Connection
    //
    connect(board.data(),SIGNAL(update_ball()),this,SLOT(update_ball()));
    connect(board.data(),SIGNAL(remove_old_ball()),this,SLOT(remove_old_ball()));
    connect(ui->startbutton,SIGNAL(released()),board.data(),SLOT(start_game()));
    connect(ui->startbutton,SIGNAL(released()),this,SLOT(disable_button()));
    connect(this,SIGNAL(key_pressed(int)),board.data(),SLOT(player_move(int)));
    connect(board.data(),SIGNAL(remove_old_player_pos(QPair<int, int>)),this,SLOT(remove_old_player_pos(QPair<int, int>)));
    connect(board.data(),SIGNAL(update_player(QPair<int, int>)),this,SLOT(update_player(QPair<int, int>)));
    connect(board.data(),SIGNAL(rebound_view(QPair<int,int>)),this,SLOT(rebound_view(QPair<int,int>)));

}

pingpongview::~pingpongview()
{
    delete ui;
}

void pingpongview::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    emit key_pressed(key);
}

void pingpongview::update_ball()
{
    auto ball_pos = board->get_ball_pos();

    QPixmap pixmap(30,30);
    pixmap.fill(Qt::red);

    view_board[ball_pos.second][ball_pos.first]->setPixmap(pixmap);
}

void pingpongview::remove_old_ball()
{
    auto ball_pos = board->get_ball_pos();

    QPixmap pixmap(30,30);
    pixmap.fill(Qt::white);

    view_board[ball_pos.second][ball_pos.first]->setPixmap(pixmap);
}

void pingpongview::disable_button()
{
    ui->startbutton->setEnabled(false);
}

void pingpongview::remove_old_player_pos(QPair<int, int> player_pos)
{


    QPixmap pixmap(30,30);
    pixmap.fill(Qt::white);
    view_board[player_pos.second][player_pos.first]->setPixmap(pixmap);
}

void pingpongview::update_player(QPair<int, int> player_pos)
{
    QPixmap pixmap(30,30);
    pixmap.fill(Qt::black);
    view_board[player_pos.second][player_pos.first]->setPixmap(pixmap);
}

void pingpongview::rebound_view(QPair<int, int> ball_pos)
{
    QPixmap pixmap(30,30);
    pixmap.fill(Qt::black);
    view_board[ball_pos.second][ball_pos.first]->setPixmap(pixmap);
}

