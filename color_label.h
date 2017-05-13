#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QLabel>
#include <QWidget>

class ColorLabel : public QLabel
{
    Q_OBJECT

public:
    ColorLabel(QLabel *parent = 0);

    void background_color(const QString &text);

    QString defaultStyle;

protected:
      virtual void mouseReleaseEvent(QMouseEvent *event);

signals:
    void clicked();
};

#endif // COLORLABEL_H
