#ifndef ZOOM_H
#define ZOOM_H

#include <QLabel>
#include <QPainter>

class Zoom : public QLabel
{
    Q_OBJECT

public:
    Zoom(QWidget* parent = 0);

    void showMagnifier(QPoint pos);

    QPixmap pixmap;

protected:
    void paintEvent(QPaintEvent *);
};

#endif // ZOOM_H
