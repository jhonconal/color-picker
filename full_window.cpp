#include "full_window.h"
#include <QKeyEvent>
#include <QPainter>
#include <QGuiApplication>
#include <QScreen>

FullWindow::FullWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setWindowState(Qt::WindowActive | Qt::WindowFullScreen);
}

void FullWindow::start()
{
    auto screens = QGuiApplication::screens();
    QList<QPixmap> scrs;
    int w = 0, h = 0, p = 0;
    foreach (auto scr, screens) {
      QPixmap pix = scr->grabWindow(0);
      w += pix.width();
      if (h < pix.height()) h = pix.height();
      scrs << pix;
    }
    QPixmap final(w, h);
    QPainter painter(&final);
    final.fill(Qt::black);
    foreach (auto scr, scrs) {
      painter.drawPixmap(QPoint(p, 0), scr);
      p += scr.width();
    }
    m_loadPixmap = final;
}

void FullWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        hide();
    }
}

void FullWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if (event->button() == Qt::LeftButton)
    {
        QImage image = m_loadPixmap.toImage();
        QColor rgb = image.pixel(QCursor::pos());
        QString hex = "#" +QString::number(rgb.red(), 16).toUpper() + QString::number(rgb.green(), 16).toUpper() + QString::number(rgb.blue(), 16).toUpper();
        emit sendSignal(hex);
        hide();
    }
}

void FullWindow::paintEvent(QPaintEvent *event)
{
    QPainter m_painter(this);

    m_painter.drawPixmap(0, 0, m_loadPixmap);

    m_painter.end();
}
