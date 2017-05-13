#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLineEdit>
#include "color_label.h"
#include "full_window.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QMainWindow *parent = 0);

    void paintEvent(QPaintEvent *event);

private slots:
    void on_colorButton_clicked();
    void setColor(QString hex);

private:
    FullWindow *fullWindow;
    QWidget *centWidget;
    QVBoxLayout *layout;
    ColorLabel *colorLabel;
    QLineEdit *edit;
    QPixmap m_loadPixmap;
    bool state;

    void initUI();
};

#endif
