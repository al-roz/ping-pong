#ifndef PINGPONGMODEL_H
#define PINGPONGMODEL_H

#include <QObject>
#include <QPair>
#include <QTimer>
#include <QMessageBox>

#define SIZE_X 32
#define SIZE_Y 16

enum direction {UP_LEFT,DOWN_LEFT,UP_RIGHT,DOWN_RIGHT};

class pingpongmodel : public QObject
{
    Q_OBJECT

private:
    QPair <int,int> player1[4] = {qMakePair(0,SIZE_Y/2 - 2),qMakePair(0,SIZE_Y/2 - 1),qMakePair(0,SIZE_Y/2),qMakePair(0,SIZE_Y/2 + 1)};
    QPair <int,int> player2[4] = {qMakePair(SIZE_X - 1,SIZE_Y/2 - 2),qMakePair(SIZE_X - 1,SIZE_Y/2 - 1),
                                  qMakePair(SIZE_X - 1,SIZE_Y/2),qMakePair(SIZE_X - 1,SIZE_Y/2 + 1)};
    QPair <int,int> ball = {qMakePair(SIZE_X/2,SIZE_Y/2)};
    QTimer* timer;
    direction ball_direction;


    //QTimer* player_timer;

private slots:
    void start_game (void);
    void move_ball(void);
    void player_move(int);

signals:
    void update_ball();
    void remove_old_ball();
    void remove_old_player_pos(QPair<int,int>);
    void update_player(QPair<int,int>);
    void rebound_view(QPair<int,int>);

public:
    QPair <int,int>* get_player1_pos(void);
    QPair <int,int>* get_player2_pos(void);
    QPair <int,int> get_ball_pos(void);

    explicit pingpongmodel(QObject *parent = nullptr);

signals:

};

#endif // PINGPONGMODEL_H
