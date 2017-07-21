#include "pickerwindow.h"
#include <QApplication>
#include <QScreen>
#include <QPainter>
#include <QKeyEvent>

PickerWindow::PickerWindow(QWidget *parent)
    : QWidget(parent)
{
    zoom = new Zoom(this);

    setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);
    setMouseTracking(true);

    //setCursor(Qt::BlankCursor);

    zoom->hide();
}

void PickerWindow::start()
{
    m_pixmap = QApplication::primaryScreen()->grabWindow(0);

    resize(m_pixmap.size());
    move(0, 0);

    zoom->pixmap = m_pixmap;
    zoom->showMagnifier(QCursor::pos());
}

void PickerWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_pixmap);
    painter.end();
}

void PickerWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        setVisible(false);
}

void PickerWindow::mouseMoveEvent(QMouseEvent *e)
{
    zoom->showMagnifier(QCursor::pos());
}

void PickerWindow::mousePressEvent(QMouseEvent *e)
{

}

void PickerWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        image = m_pixmap.toImage();

        QColor color = image.pixel(QCursor::pos());

        setVisible(false);

        emit finished(color);
    }
}
