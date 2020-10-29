#ifndef PINGPONGVIEW_H
#define PINGPONGVIEW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QKeyEvent>
#include "pingpongmodel.h"


QT_BEGIN_NAMESPACE
namespace Ui { class pingpongview; }
QT_END_NAMESPACE

class pingpongview : public QMainWindow
{
    Q_OBJECT
    QLabel*** view_board;
    QScopedPointer<pingpongmodel> board;

public:
    pingpongview(QWidget *parent = nullptr);
    ~pingpongview();

private:
    Ui::pingpongview *ui;
    virtual void keyPressEvent(QKeyEvent* event);
private slots:
    void update_ball();
    void remove_old_ball();
    void disable_button();
    void remove_old_player_pos(QPair<int,int>);
    void update_player(QPair<int,int>);
    void rebound_view(QPair<int,int>);
 signals:
    void key_pressed(int);
};
#endif // PINGPONGVIEW_H
