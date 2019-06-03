#include "widget.h"

#include <QPushButton>
#include <QLabel>

#include "UI/listwidget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setGeometry(0, 0, 640, 480);

    QLabel *a1 = new QLabel(this);
    a1->setGeometry(0, 0, 160, 40);
    a1->setText("挠度");
    list = new ListWidget(DataType::Deflection, this);
    list->setGeometry(0, 40, 160, 170);

    QLabel *a2 = new QLabel(this);
    a2->setGeometry(200, 0, 160, 40);
    a2->setText("应变");
    list = new ListWidget(DataType::Strain, this);
    list->setGeometry(200, 40, 160, 170);

    QLabel *a3 = new QLabel(this);
    a3->setGeometry(400, 0, 160, 40);
    a3->setText("位移");
    list = new ListWidget(DataType::Displacement, this);
    list->setGeometry(400, 40, 160, 170);

    //connect(list, SIGNAL);
}

Widget::~Widget()
{

}
