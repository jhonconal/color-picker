#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLineEdit>
#include "color_label.h"
#include "full_window.h"
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QMainWindow *parent = 0);

private slots:
    void on_colorButton_clicked();
    void setColor(QColor color);
    void on_rgbButton_clicked();
    void on_hexButton_clicked();

private:
    FullWindow *fullWindow;
    QWidget *centWidget;
    QVBoxLayout *layout;
    ColorLabel *colorLabel;
    QLineEdit *hexEdit;
    QLineEdit *rgbEdit;
    QPixmap m_loadPixmap;

    QLabel *hexLabel;
    QLabel *rgbLabel;
    QPushButton *copyHexButton;
    QPushButton *copyRgbButton;

    void initUI();

protected:
    void paintEvent(QPaintEvent *event);
};

#endif
