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
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setWindowState(Qt::WindowActive | Qt::WindowFullScreen);
    setMouseTracking(true); // make MouseMove can response

    m_zoom = new Zoom(this);
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

    this->setCursor(Qt::CrossCursor);
    this->setWindowState(Qt::WindowActive | Qt::WindowFullScreen);
}

void FullWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        this->setVisible(false);
        m_zoom->setVisible(false);
    }
}

void FullWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if (event->button() == Qt::LeftButton)
    {
        QImage image = m_loadPixmap.toImage();
        QColor color = image.pixel(QCursor::pos());
        QString hex = rgbTohex(color);

        emit sendSignal(hex);

        this->setVisible(false);
        m_zoom->setVisible(false);
    }
}

void FullWindow::mouseMoveEvent(QMouseEvent *event)
{
    QImage image = m_loadPixmap.toImage();
    QColor color = image.pixel(QCursor::pos());
    m_zoom->getColor(color);
    m_zoom->showTips();
}

QString FullWindow::rgbTohex(const QColor &color)
{
    QString hex = "#";

    int r, g, b;
    int x1, x2;
    char s[2];

    r = color.red();
    g = color.green();
    b = color.blue();

    x1 = color.red() % 16;
    x2 = color.red() / 16;

    if (x1 > 9)
        s[0] = x1 - 10 + 65;
    else
        s[0] = x1 + 48;
    if (x2 > 9)
        s[1] = x2 - 10 + 65;
    else
        s[1] = x2 + 48;
    hex += QString("%1%2").arg(s[1]).arg(s[0]);

    x1 = color.green() % 16;
    x2 = color.green() / 16;
    if (x1 > 9)
        s[0] = x1 - 10 + 65;
    else
        s[0] = x1 + 48;
    if (x2 > 9)
        s[1] = x2 - 10 + 65;
    else
        s[1] = x2 + 48;
    hex += QString("%1%2").arg(s[1]).arg(s[0]);

    x1 = color.blue() % 16;
    x2 = color.blue() / 16;
    if (x1 > 9)
        s[0] = x1-10 + 65;
    else
        s[0] = x1 + 48;
    if (x2 > 9)
        s[1] = x2 - 10 + 65;
    else
        s[1] = x2 + 48;
    hex += QString("%1%2").arg(s[1]).arg(s[0]);

    return hex;
}

void FullWindow::paintEvent(QPaintEvent *event)
{
    QPainter m_painter(this);
    m_painter.drawPixmap(0, 0, m_loadPixmap);
    m_painter.end();
}
