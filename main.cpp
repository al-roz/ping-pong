#include "pingpongview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pingpongview w;
    w.show();
    return a.exec();
}
