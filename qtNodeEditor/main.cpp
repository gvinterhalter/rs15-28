#include <QtWidgets>
#include <QApplication>
#include "qnemainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QNEMainWindow w;
    w.show();

    return a.exec();
}
