#include "widget.h"
#include <QApplication>
#include <QWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;


    // устанавливаем цвет фона

    w.show();

    return a.exec();
}
