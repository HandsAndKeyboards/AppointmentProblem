#include "helper.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    helper w;
    w.show();
    return a.exec();
}
