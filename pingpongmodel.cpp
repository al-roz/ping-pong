#include "pingpongmodel.h"



void pingpongmodel::start_game()
{
    timer->start();
}

void pingpongmodel::move_ball()
{
    emit remove_old_ball();

    if (ball.second == 0 || ball.second == SIZE_Y - 1)
    {
        switch (ball_direction)
        {
        case UP_LEFT:
            ball_direction = DOWN_LEFT;
            break;
        case UP_RIGHT:
            ball_direction = DOWN_RIGHT;
            break;
        case DOWN_LEFT:
            ball_direction = UP_LEFT;
            break;
        case DOWN_RIGHT:
            ball_direction = UP_RIGHT;
            break;
        }
    }

    switch (ball_direction)
    {
    case UP_LEFT:
        ball.first--;
        ball.second--;
        break;
    case UP_RIGHT:
        ball.first++;
        ball.second--;
        break;
    case DOWN_LEFT:
        ball.first--;
        ball.second++;
        break;
    case DOWN_RIGHT:
        ball.first++;
        ball.second++;
    }
    bool flag = false;
    if (ball.first == 1)
    {
        for (int i = 0 ; i < 4 ; i++)
            if (ball.first - 1 == player1[i].first && ball.second == player1[i].second) flag = true;
        if (flag == true){
            ball_direction = static_cast<direction>(rand()%2 + 2);
            timer->setInterval(timer->interval() - 20);
        }
        if (flag == false){
            QMessageBox msg;
            msg.setText("Player1 win");
            timer->stop();
            msg.exec();
        }

    }
    if (ball.first == SIZE_X - 2)
    {

        for (int i = 0 ; i < 4 ; i++)
            if (ball.first + 1 == player2[i].first && ball.second == player2[i].second) flag = true;
        if (flag == true){
            ball_direction = static_cast<direction>(rand()%2);
            timer->setInterval(timer->interval() - 20);
        }
        if (flag == false){
            QMessageBox msg;
            msg.setText("Player2 win");
            timer->stop();
            msg.exec();
        }
    }


   emit update_ball();
}

void pingpongmodel::player_move(int key)
{
    switch (key) {
    case Qt::Key::Key_W:
        if (player1[0].second != 0){
            emit remove_old_player_pos(player1[3]);
            for(int i = 0 ; i < 4 ;i++)
                player1[i].second--;
        emit update_player(player1[0]);}
        break;
    case Qt::Key::Key_S:
        if (player1[3].second != SIZE_Y - 1){
            emit remove_old_player_pos(player1[0]);
            for(int i = 0 ; i < 4 ;i++)
                player1[i].second++;
        emit update_player(player1[3]);}
        break;
    case Qt::Key::Key_Up:
        if (player2[0].second != 0){
            emit remove_old_player_pos(player2[3]);
            for(int i = 0 ; i < 4 ;i++)
                player2[i].second--;
        emit update_player(player2[0]);}
        break;
     case Qt::Key::Key_Down:
        if (player2[3].second != SIZE_Y - 1){
            emit remove_old_player_pos(player2[0]);
            for(int i = 0 ; i < 4 ;i++)
                player2[i].second++;
        emit update_player(player2[3]);}
        break;
    }

}

QPair<int, int> *pingpongmodel::get_player1_pos()
{
    return player1;
}

QPair<int, int> *pingpongmodel::get_player2_pos()
{
    return player2;
}

QPair<int, int> pingpongmodel::get_ball_pos()
{
    return ball;
}

pingpongmodel::pingpongmodel(QObject *parent) : QObject(parent)
{
    srand(time(nullptr));
    timer = new QTimer;
    timer->setInterval(300);
    ball_direction = static_cast<direction>(rand()%4);
    connect(timer,SIGNAL(timeout()),this,SLOT(move_ball()));
}
