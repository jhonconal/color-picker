#include "main_window.h"
#include <QPainter>
#include <QApplication>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QClipboard>

QString styleSheet = "";

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
{
    QHBoxLayout *hexLayout = new QHBoxLayout();
    QHBoxLayout *rgbLayout = new QHBoxLayout();

    hexLabel = new QLabel("HEX:");
    rgbLabel = new QLabel("RGB:");

    fullWindow = new FullWindow(this);
    centWidget = new QWidget();
    layout = new QVBoxLayout();
    colorLabel = new ColorLabel();
    hexEdit = new QLineEdit();
    rgbEdit = new QLineEdit();
    copyHexButton = new QPushButton("Copy");
    copyRgbButton = new QPushButton("Copy");

    hexLayout->addWidget(hexLabel);
    hexLayout->addWidget(hexEdit);
    hexLayout->addWidget(copyHexButton);
    rgbLayout->addWidget(rgbLabel);
    rgbLayout->addWidget(rgbEdit);
    rgbLayout->addWidget(copyRgbButton);

    layout->addStretch();
    layout->addWidget(colorLabel, 0, Qt::AlignCenter);
    layout->addStretch();
    layout->addLayout(hexLayout);
    layout->addLayout(rgbLayout);
    layout->addStretch();

    centWidget->setLayout(layout);
    this->setCentralWidget(centWidget);

    initUI();

    connect(colorLabel, SIGNAL(clicked()), this, SLOT(on_colorButton_clicked()));
    connect(fullWindow, SIGNAL(setColor(QColor)), this, SLOT(setColor(QColor)));
    connect(copyHexButton, SIGNAL(clicked()), this, SLOT(on_hexButton_clicked()));
    connect(copyRgbButton, SIGNAL(clicked()), this, SLOT(on_rgbButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete fullWindow;
}

void MainWindow::initUI()
{
    hexEdit->setEnabled(false);
    rgbEdit->setEnabled(false);

    hexEdit->setText("#404244");
    hexEdit->setStyleSheet("background-color: #2C2E32; color: #FFFFFF; border: 1px solid #DFE1E6; border-radius: 2px;");
    hexEdit->setFixedWidth(80);

    rgbEdit->setText("64,66,68");
    rgbEdit->setStyleSheet("background-color: #2C2E32; color: #FFFFFF; border: 1px solid #DFE1E6; border-radius: 2px;");
    rgbEdit->setFixedWidth(80);

    rgbLabel->setStyleSheet("color: #FFFFFF;");
    hexLabel->setStyleSheet("color: #FFFFFF;");

    copyHexButton->setFixedSize(33, 25);
    copyRgbButton->setFixedSize(33, 25);
}

void MainWindow::on_colorButton_clicked()
{
    fullWindow->setVisible(true);
    fullWindow->start();
}

void MainWindow::on_rgbButton_clicked()
{
    QClipboard *cb = QApplication::clipboard();
    cb->setText(rgbEdit->text());
}

void MainWindow::on_hexButton_clicked()
{
    QClipboard *cb = QApplication::clipboard();
    cb->setText(hexEdit->text());
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor("#404244"));
    p.drawRect(rect());
}

void MainWindow::setColor(QColor color)
{
    QString hex = QString("#%1%2%3").arg(color.red(), 2, 16, QLatin1Char('0'))
                                        .arg(color.green(), 2, 16, QLatin1Char('0'))
                                        .arg(color.blue(), 2, 16, QLatin1Char('0')).toUpper();

    hexEdit->setText(hex);
    colorLabel->background_color(hexEdit->text());

    rgbEdit->setText(QString::number(color.red()) + "," + QString::number(color.green()) + "," + QString::number(color.blue()));
}
