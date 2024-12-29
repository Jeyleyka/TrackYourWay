#include "greetings.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Greetings window;
    window.show();
    return a.exec();
}


