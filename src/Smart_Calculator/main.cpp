#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // Create a QApplication instance

    // Create an instance of the MainWindow class
    MainWindow win;

    // Show the MainWindow
    win.show();

    // Start the event loop of the application
    return app.exec();
}
