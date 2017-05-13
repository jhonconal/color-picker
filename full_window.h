#ifndef FULLWINDOW_H
#define FULLWINDOW_H

#include <QWidget>

class FullWindow : public QWidget
{
    Q_OBJECT

public:
    FullWindow(QWidget *parent = 0);

    QPixmap m_loadPixmap;

    void start();

private:
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    //void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void sendSignal(QString hex);
};

#endif // FULLWINDOW_H
