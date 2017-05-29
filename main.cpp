#include <QApplication>
#include <QDesktopWidget>
#include "main_window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.setWindowTitle("Color");
    w.setFixedSize(170, 160);
    w.setWindowIcon(QIcon("icon.svg"));
    w.show();

    w.move ((QApplication::desktop()->width() - w.width()) / 2,
    		(QApplication::desktop()->height() - w.height()) / 2);

    return app.exec();
}
