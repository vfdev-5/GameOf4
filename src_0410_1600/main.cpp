

#include <QtGUI/QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc,argv);
    MainWindow gameOf4;
    gameOf4.show();

    return app.exec();
}
