#include "zoom.h"

Zoom::Zoom(QWidget *parent)
    : QLabel(parent)
{
    this->setFixedSize(59, 59);
}

void Zoom::getColor(QColor &color)
{
    m_color = color;
}

void Zoom::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(QColor(m_color));
    painter.drawRect(rect());
}

void Zoom::showTips()
{
    if (!this->isVisible())
        this->setVisible(true);

    QPoint movePos = cursor().pos();
    this->move(movePos.x() + 10, movePos.y() + 10);

    update();
}
