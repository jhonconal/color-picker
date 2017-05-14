#include "main_window.h"
#include <QPainter>
#include <QApplication>
#include <QMouseEvent>
#include <QPaintEvent>

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
{
    fullWindow = new FullWindow(this);
    centWidget = new QWidget();
    layout = new QVBoxLayout();
    colorLabel = new ColorLabel();
    edit = new QLineEdit();

    layout->addWidget(colorLabel, 0, Qt::AlignCenter);
    layout->addWidget(edit, 0, Qt::AlignCenter);

    centWidget->setLayout(layout);
    this->setCentralWidget(centWidget);

    initUI();

    connect(colorLabel, SIGNAL(clicked()), this, SLOT(on_colorButton_clicked()));
    connect(fullWindow, SIGNAL(sendSignal(QString)), this, SLOT(setColor(QString)));
}

void MainWindow::initUI()
{
    edit->setFocusPolicy(Qt::NoFocus);
    edit->setText("#FFFFFF");
    edit->setStyleSheet("background-color: #404244; color: #FFFFFF; border: 1px solid #D3D3D4; border-radius: 3px;");
    edit->setFixedWidth(100);
}

void MainWindow::on_colorButton_clicked()
{
    fullWindow->setVisible(true);
    fullWindow->start();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor("#404244"));
    p.drawRect(rect());
}

void MainWindow::setColor(QString hex)
{
    edit->setText(hex);
    colorLabel->background_color(edit->text());
}
