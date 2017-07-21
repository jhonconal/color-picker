#include "zoom.h"
#include "utils.h"

namespace {
    const QSize BACKGROUND_SIZE = QSize(59, 59);
    const int IMG_WIDTH =  12;
    const int INDICATOR_WIDTH = 49;
    const int CENTER_RECT_WIDTH = 12;
    const int BOTTOM_RECT_HEIGHT = 14;
}

Zoom::Zoom(QWidget *parent)
    : QLabel(parent)
{
    setFixedSize(BACKGROUND_SIZE);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setStyleSheet("border-image: url(:/image/magnifier.png);");
}

void Zoom::paintEvent(QPaintEvent *)
{
    QPoint centerPos =  this->cursor().pos();
    centerPos = QPoint(centerPos.x() - this->window()->x(), centerPos.y());

    QRgb centerRectRgb = pixmap.toImage().pixel(centerPos);
    QPixmap zoomPix = pixmap.copy(centerPos.x() - IMG_WIDTH/2,
            centerPos.y() - IMG_WIDTH/2, IMG_WIDTH, IMG_WIDTH);

    zoomPix = zoomPix.scaled(QSize(INDICATOR_WIDTH,  INDICATOR_WIDTH), Qt::KeepAspectRatio);

    QPainter painter(this);
    painter.drawPixmap(QRect(5, 5, INDICATOR_WIDTH, INDICATOR_WIDTH), zoomPix);

    QRect centerRect = QRect((BACKGROUND_SIZE.width() - CENTER_RECT_WIDTH)/2 + 1,
                             (BACKGROUND_SIZE.width() - CENTER_RECT_WIDTH)/2 + 1,
                             CENTER_RECT_WIDTH, CENTER_RECT_WIDTH);
    painter.drawPixmap(centerRect, QPixmap(":/image/center_rect.png"));
    painter.fillRect(QRect(INDICATOR_WIDTH/2 + 2, INDICATOR_WIDTH/2 + 2,
            CENTER_RECT_WIDTH - 4, CENTER_RECT_WIDTH - 4), QBrush(QColor(qRed(centerRectRgb),
             qGreen(centerRectRgb), qBlue(centerRectRgb))));

    painter.fillRect(QRect(5, INDICATOR_WIDTH - 9, INDICATOR_WIDTH, BOTTOM_RECT_HEIGHT),
                     QBrush(QColor(0, 0, 0, 125)));
    QFont posFont;
    posFont.setPixelSize(9);
    painter.setFont(posFont);
    painter.setPen(QColor(Qt::white));
    QTextOption posTextOption;
    posTextOption.setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    painter.drawText(QRectF(5, INDICATOR_WIDTH - 10, INDICATOR_WIDTH, INDICATOR_WIDTH),
                     QString("%1, %2").arg(centerPos.x()).arg(centerPos.y()), posTextOption);
}

void Zoom::showMagnifier(QPoint pos)
{
    this->show();

    this->move(pos.x(), pos.y());

    update();
}
