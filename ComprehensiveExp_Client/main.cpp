#include "cwidget.h"
#include <QApplication>
#include <client.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CWidget w;
    w.show();

    return a.exec();
}
