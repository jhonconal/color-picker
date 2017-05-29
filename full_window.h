#ifndef FULLWINDOW_H
#define FULLWINDOW_H

#include <QWidget>

class FullWindow : public QWidget
{
    Q_OBJECT

public:
    FullWindow(QWidget *parent = 0);
    ~FullWindow();

    QPixmap pixmap;

    void start();

private:
    QImage image;

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void setColor(QColor hex);
};

#endif // FULLWINDOW_H
