#include "full_window.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QGuiApplication>
#include <QScreen>

FullWindow::FullWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);
    setMouseTracking(true);

    m_zoom = new Zoom(this);
    
    this->setCursor(Qt::CrossCursor);
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
    if (event->key() == Qt::Key_Escape)
    {
        this->close();
        m_zoom->close();
    }
}

void FullWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if (event->button() == Qt::LeftButton)
    {
        QImage image = pixmap.toImage();
        QColor color = image.pixel(QCursor::pos());
        QString hex = QString("#%1%2%3").arg(color.red(), 2, 16, QLatin1Char('0'))
                                        .arg(color.green(), 2, 16, QLatin1Char('0'))
                                        .arg(color.blue(), 2, 16, QLatin1Char('0')).toUpper();

        emit sendSignal(hex);

        this->setVisible(false);
        m_zoom->setVisible(true);
    }
}

void FullWindow::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    QImage image = pixmap.toImage();
    QColor color = image.pixel(QCursor::pos());
    m_zoom->takeColor(color);
    m_zoom->showTips();
}

void FullWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);
    p.drawPixmap(0, 0, pixmap);
    p.end();
}
