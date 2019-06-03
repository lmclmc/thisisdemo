#include "popupmenu.h"

#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>

#define SCREEN_WIDTH (160)
#define SCREEN_HEIGHT (170)

PopupMenu::PopupMenu(QWidget *parent, int mode, int flag) :
    QWidget(parent),
    mMode(mode)
{
    overAllLabel = new QLabel(this);
    overAllLabel->setGeometry(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    overAllLabel->setStyleSheet("background-color: rgba(0, 0, 0, 50%);");
    mainLabel = new QLabel(this);
    mainLabel->setGeometry(0, 30, 160, 100);
    mainLabel->setStyleSheet("background-color:white;border-radius:"+QString::number(SCREEN_WIDTH>>4)+"px");

    mainTextLabel = new QLabel(this);
    mainTextLabel->setGeometry(0, 30, 160, 40);
    mainTextLabel->setStyleSheet("background-color:white;border-radius:"+QString::number(SCREEN_WIDTH>>4)+"px");

    if (mMode == 1){
    } else if (mMode == 2){
    } else {
        leftLabel = new QPushButton(this);
        rightLabel = new QPushButton(this);
        leftLabel->setGeometry(10, 80, 50, 35);
        rightLabel->setGeometry(90, 80, 50, 35);
    }

    connect(leftLabel, SIGNAL(clicked()), this, SLOT(responYes()));
    connect(rightLabel, SIGNAL(clicked()), this, SLOT(responNo()));
}

void PopupMenu::setMainText(QString src)
{
    if (src.indexOf('\n') == -1)
         src.insert(10, '\n');
    mainTextLabel->setText(src);    
    mainTextLabel->setAlignment(Qt::AlignCenter);
    mainTextLabel->setWordWrap(true);
}

void PopupMenu::setLeftText(QString src)
{
    leftLabel->setText(src);
    leftLabel->setStyleSheet("color:white");
    leftLabel->raise();
}

void PopupMenu::setRightText(QString src)
{
    rightLabel->setText(src);
    rightLabel->setStyleSheet("color:white");
    rightLabel->raise();
}

void PopupMenu::setCenText(QString src)
{
    cenLabel->setText(src);
    cenLabel->setStyleSheet("background-position:center;background-repeat:no-repeat;background-image:url(:/resource/pickpoint/check.png);color:white");
    cenLabel->setAlignment(Qt::AlignCenter);
    cenLabel->setWordWrap(true);
    cenLabel->show();
    cenLabel->raise();
}

void PopupMenu::setYValue(int Y)
{
    setGeometry(0, Y, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void PopupMenu::setMode(int mode)
{
    if (mode){
        leftLabel->hide();
        rightLabel->setGeometry(50, 80, 50, 40);
    } else {
        leftLabel->show();
        leftLabel->setGeometry(10, 80, 50, 35);
        rightLabel->setGeometry(90, 80, 50, 35);
    }
}

void PopupMenu::responYes()
{
    this->hide();
    yesChange();
}

void PopupMenu::responNo()
{
    this->hide();
}
