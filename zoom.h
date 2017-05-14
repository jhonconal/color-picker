#ifndef ZOOM_H
#define ZOOM_H

#include <QLabel>
#include <QPainter>
#include <QPaintEvent>

class Zoom : public QLabel
{
    Q_OBJECT

public:
    Zoom(QWidget *parent = 0);

    void getColor(QColor &color);
    void showTips();

private:
    QColor m_color;

    void paintEvent(QPaintEvent *);
};

#endif // ZOOM_H
