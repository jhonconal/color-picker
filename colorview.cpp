#include "colorview.h"

ColorView::ColorView(QWidget *parent)
    : QLabel(parent)
{
    setFixedSize(92, 70);
}

void ColorView::setBackgroundColor(const QString &color)
{
    setStyleSheet("background: " + color);
}
