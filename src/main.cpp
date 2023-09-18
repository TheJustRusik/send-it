#include "../inc/mainwindow.h"

#include <QApplication>

#include "../inc/filemanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
