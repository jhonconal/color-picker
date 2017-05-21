#ifndef FULLWINDOW_H
#define FULLWINDOW_H

#include <QWidget>
#include "zoom.h"

class FullWindow : public QWidget
{
    Q_OBJECT

public:
    FullWindow(QWidget *parent = 0);
    ~FullWindow();

    QPixmap pixmap;

    void start();

private:
    Zoom *m_zoom;

    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void sendSignal(QString hex);
};

#endif // FULLWINDOW_H
