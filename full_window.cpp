#include "full_window.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QScreen>

FullWindow::FullWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);
    setMouseTracking(true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    
    this->setCursor(Qt::BlankCursor);
}

FullWindow::~FullWindow()
{
	
}

void FullWindow::start()
{
    pixmap = qApp->primaryScreen()->grabWindow(0);

    resize(pixmap.size());
    move(0, 0);
}

void FullWindow::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event);

    if (event->key() == Qt::Key_Escape)
    {
        this->setVisible(false);
    }
}

void FullWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if (event->button() == Qt::LeftButton)
    {
        image = pixmap.toImage();
        QColor color = image.pixel(QCursor::pos());

        this->setVisible(false);

        emit setColor(color);
    }
}

void FullWindow::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    update();
}

void FullWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPoint tl, br, pos(QCursor::pos());

    tl.setX(pos.x() - 10);
    tl.setY(pos.y() - 10);
    br.setX(pos.x() + 10);
    br.setY(pos.y() + 10);

    QRect rect(tl, br);

    QPixmap pix = pixmap.copy(rect);
    QPixmap zoomPix = pix.scaled(pix.width() * 4, pix.height() * 4);

    QPainter painter(this);
    //painter.drawPixmap(0, 0, pixmap);

    int x = qMax(0, pos.x() - (zoomPix.width() / 2));
    int y = qMax(0, pos.y() - (zoomPix.height() / 2));

    painter.drawPixmap(x, y, zoomPix);
    painter.setPen(Qt::SolidLine);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(x, y, zoomPix.width(), zoomPix.height());
    painter.drawRect(pos.x()-2, pos.y() - 2, 4, 4);

    QImage img = pixmap.copy(pos.x(), pos.y(), 1, 1).toImage();
    QColor color = QColor(img.pixel(0, 0));
    QString hex = QString("#%1%2%3").arg(color.red(), 2, 16, QLatin1Char('0'))
            .arg(color.green(), 2, 16, QLatin1Char('0'))
            .arg(color.blue(), 2, 16, QLatin1Char('0')).toUpper();

    QRect textRect = painter.boundingRect(QRect(x, y + zoomPix.height(), 10, 10), Qt::TextWordWrap, hex);
    textRect.adjust(0, 2, 2, 2);

    painter.setBrush(Qt::white);
    painter.drawRect(textRect);
    painter.drawText(textRect, hex);
    painter.end();
}
