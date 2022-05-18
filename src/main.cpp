#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Function_Plotter w;
    w.show();
    return a.exec();
}
