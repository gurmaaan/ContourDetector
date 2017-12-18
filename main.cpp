#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("ContourDetector");
    a.setApplicationDisplayName("Метод Активных Контуров");
    a.setOrganizationName("GDev");
    a.setOrganizationDomain("https://mck-moscow.com");

    MainWindow w;
    w.show();

    return a.exec();
}
