#include <QApplication>
#include <QDesktopWidget>
#include "main_window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.setWindowTitle("Color");
    w.setFixedSize(150, 150);
    w.show();

    w.move ((QApplication::desktop()->width() - w.width()) / 2,
    		(QApplication::desktop()->height() - w.height()) / 2);

    return app.exec();
}
