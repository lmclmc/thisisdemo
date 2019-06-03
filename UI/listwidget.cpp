#include "listwidget.h"
#include "File/fopt.h"
#include "File/deflection.h"
#include "Editwidget.h"
#include "graphwidget.h"
#include "UI/popupmenu.h"

#include <QPushButton>
#include <QScrollBar>
#include <QLabel>
#include <QMouseEvent>

SonWidget::SonWidget(DataType type, QWidget *parent) : QWidget(parent),
    max(0),
    mType(type)
{
    init();
}

ListWidget::ListWidget(DataType type, QWidget *parent) : QWidget(parent),
    mType(type)
{
    scroll = new QScrollBar(this);
    scroll->setGeometry(150, 0, 10, 150);

    s = new SonWidget(mType, this);
    s->setGeometry(0, 0, 150, 15000);
    scroll->setRange(0, s->max);

    back = new QLabel(this);
    back->setGeometry(0, 150, 150, 20);
    back->setStyleSheet("background-color:white");;
    back->raise();

    add = new QPushButton(this);
    add->setText("+");
    add->setGeometry(0, 150, 20, 20);
    add->raise();

    p = new PopupMenu(this);
    p->setGeometry(0, 0, 160, 170);
    p->hide();

    del = new QPushButton(this);
    del->setText("-");
    del->setGeometry(140, 150, 20, 20);
    del->raise();

    enter = new QPushButton(this);
    enter->setText("进入");
    enter->setGeometry(85, 150, 40, 20);
    enter->raise();

    graph = new QPushButton(this);
    graph->setText("曲线图");
    graph->setGeometry(30, 150, 50, 20);
    graph->raise();

    g = new GraphWidget(mType, this);
    g->setGeometry(0, 0, 160, 170);
    g->hide();

    e = new EditWidget(mType, this);
    e->setGeometry(0, 0, 160, 170);
    e->hide();

    connect(scroll, SIGNAL(valueChanged(int)), this, SLOT(responScroll(int)));
    connect(add, SIGNAL(clicked()), this, SLOT(addNewId()));
    connect(enter, SIGNAL(clicked()), this, SLOT(showEditWidget()));
    connect(graph, SIGNAL(clicked()), this, SLOT(showGraphWidget()));
    connect(del, SIGNAL(clicked()), this, SLOT(responDelButton()));
    connect(p, SIGNAL(yesChange()), s, SLOT(deleteId()));
    connect(s, SIGNAL(pushIdx(int)), this, SLOT(showEditWidget()));
    connect(s, SIGNAL(deleteSuccess()), this, SLOT(responDeleteSuccess()));
}

void SonWidget::init()
{
    FileWrapper *f = FileWrapper::getInstance();
    FOpt  *fd = dynamic_cast<FOpt *>(f->getFileMap().find(mType)->second);
    FOpt::TMap::iterator iter;
    std::shared_ptr<QLabel> p;

    max = 0;
    listLabel.clear();
    for (iter = fd->getData().begin(); iter != fd->getData().end(); iter++){
        p = std::make_shared<QLabel>(this);
        p->setGeometry(0, 20*max, 50, 20);
        p->setText(QString::number(iter->first));
        p->show();
        p->raise();
        listLabel.emplace_back(std::pair<std::shared_ptr<QLabel>, int>(p, iter->first));
        max++;
    }
}

void SonWidget::deleteId()
{
    std::list<std::pair<std::shared_ptr<QLabel>, int>>::iterator iter;
    for (iter = listLabel.begin(); iter != listLabel.end(); iter++){
        if (iter->second == id){
            listLabel.erase(iter);
            FileWrapper *f = FileWrapper::getInstance();
            FOpt  *fd = dynamic_cast<FOpt *>(f->getFileMap().find(mType)->second);
            fd->getData().erase(fd->getData().find(id));
            fd->flush();
            break;
        }
    }
    max = 0;
    for (auto tmp : listLabel){
        tmp.first.get()->setGeometry(0, 20*max, 50, 20);
        max++;
    }

    deleteSuccess();
}

void SonWidget::mouseReleaseEvent(QMouseEvent *event)
{
    int idx = event->pos().y()/20;
    for (auto tmp : listLabel){
        if (idx-- == 0){
            tmp.first.get()->setStyleSheet("background-color:rgb(122,122,122);color:black");
            id = tmp.second;
        } else {
            tmp.first.get()->setStyleSheet("background-color:white;color:black");
        }
    }
}

void SonWidget::focusInEvent(QFocusEvent *)
{
    id = -1;
}

void ListWidget::responScroll(int idx)
{
    s->setGeometry(0, -idx*(20-150/s->max), 150, 15000);
}

void ListWidget::showEditWidget()
{
    e->setIdx(s->getId());
    e->show();
    e->raise();
    e->setFocus();
}

void ListWidget::addNewId()
{
    e->setIdx(-100);
    e->show();
    e->raise();
    e->setFocus();
}

void ListWidget::showGraphWidget()
{
    g->setGeometry(0, 0, 160, 170);
    g->setIdx(s->getId());
    g->show();
    g->raise();
    g->setFocus();
}

void ListWidget::responDelButton()
{
    p->setMode(0);
    p->setMainText(QString("是否删除该编号:")+QString::number(s->getId()));
    p->setLeftText("是");
    p->setRightText("否");
    p->show();
    p->raise();
    p->setFocus();
}

void ListWidget::responDeleteSuccess()
{
    p->setMode(1);
    p->setMainText("删除成功");
    p->setRightText("确定");
    p->show();
    p->raise();
    p->setFocus();
}

void ListWidget::focusInEvent(QFocusEvent *)
{
    s->init();
}
