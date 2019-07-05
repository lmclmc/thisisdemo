#include "Editwidget.h"

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

EditWidget::EditWidget(DataType type, QWidget *parent) : QWidget(parent),
    mType(type)
{
    mainLabel = new QLabel(this);
    mainLabel->setGeometry(0, 0, 200, 200);
    mainLabel->setStyleSheet("background-color:white");
    yearLabel = new QLabel(this);
    monthLabel = new QLabel(this);
    dayLabel = new QLabel(this);
    hourLabel = new QLabel(this);
    minLabel = new QLabel(this);
    secLabel = new QLabel(this);

    yearLabel->setText("年");
    monthLabel->setText("月");
    dayLabel->setText("日");
    hourLabel->setText("时");
    minLabel->setText("分");
    secLabel->setText("秒");

    yearLabel->setGeometry(0, 0, 20, 20);
    monthLabel->setGeometry(80, 0, 20, 20);
    dayLabel->setGeometry(0, 20, 20, 20);
    hourLabel->setGeometry(80, 20, 20, 20);
    minLabel->setGeometry(0, 40, 20, 20);
    secLabel->setGeometry(80, 40, 20, 20);

    yearLineEdit = new QLineEdit(this);
    yearLineEdit->setGeometry(20, 0, 60, 20);
    monthLineEdit = new QLineEdit(this);
    monthLineEdit->setGeometry(100, 0, 60, 20);
    dayLineEdit = new QLineEdit(this);
    dayLineEdit->setGeometry(20, 20, 60, 20);
    hourLineEdit = new QLineEdit(this);
    hourLineEdit->setGeometry(100, 20, 60, 20);
    minLineEdit = new QLineEdit(this);
    minLineEdit->setGeometry(20, 40, 60, 20);
    secLineEdit = new QLineEdit(this);
    secLineEdit->setGeometry(100, 40, 60, 20);

    idLabel = new QLabel(this);
    idLabel->setGeometry(0, 60, 40, 20);
    idLabel->setText("编号");
    valueLabel = new QLabel(this);
    valueLabel->setGeometry(0, 80, 40, 20);
    valueLabel->setText("值");
    unitLabel = new QLabel(this);
    unitLabel->setGeometry(0, 100, 40, 20);
    unitLabel->setText("单位");

    idLineEdit = new QLineEdit(this);
    idLineEdit->setGeometry(40, 60, 100, 20);
    valueLineEdit = new QLineEdit(this);
    valueLineEdit->setGeometry(40, 80, 100, 20);
    unitLineEdit = new QLineEdit(this);
    unitLineEdit->setGeometry(40, 100, 100, 20);

    editButton = new QPushButton(this);
    editButton->setGeometry(80, 140, 60, 20);
    editButton->setText("确认修改");

    nextButton = new QPushButton(this);
    nextButton->setGeometry(0, 120, 40, 20);
    nextButton->setText("下一页");

    lastButton = new QPushButton(this);
    lastButton->setGeometry(80, 120, 40, 20);
    lastButton->setText("上一页");

    backButton = new QPushButton(this);
    backButton->setGeometry(0, 140, 40, 20);
    backButton->setText("返回");

    connect(editButton, SIGNAL(clicked()), this, SLOT(ensure()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(nextPage()));
    connect(lastButton, SIGNAL(clicked()), this, SLOT(lastPage()));
    connect(backButton, SIGNAL(clicked()), this, SLOT(exitEdit()));
}

void EditWidget::setIdx(int idx)
{
    FileWrapper *f = FileWrapper::getInstance();
    fd = dynamic_cast<FOpt *>(f->getFileMap().find(mType)->second.get());

    mIdx = idx;

    fd->getNodeIter(mIdx, mIter);

    mLIdx = 0;

    if (idx == -100){
        idLineEdit->setEnabled(true);
        setData(0, 0, 0, 0, 0, 0, idx, 0, nullptr);
    } else {
        idLineEdit->setEnabled(false);
        mIter = fd->getData().find(mIdx)->second.begin();
        setData(mIter->t.year, mIter->t.month, mIter->t.day, mIter->t.hour, mIter->t.min, mIter->t.sec, mIter->id, mIter->value, mIter->unit);
    }
}

void EditWidget::exitEdit()
{
    this->hide();
    this->parentWidget()->setFocus();
}

void EditWidget::nextPage()
{
    if (fd->setNodeIter(mIdx, 1, mIter)){
        setData(mIter->t.year, mIter->t.month, mIter->t.day, mIter->t.hour, mIter->t.min, mIter->t.sec, mIter->id, mIter->value, mIter->unit);
    } else {
        setData(0, 0, 0, 0, 0, 0, mIdx, 0, nullptr);
    }


//    if (mIter == fd->getData().find(mIdx)->second.end()){
//        mIter--;
//
//    } else {
//        setData(mIter->t.year, mIter->t.month, mIter->t.day, mIter->t.hour, mIter->t.min, mIter->t.sec, mIter->id, mIter->value, mIter->unit);
//    }
}

void EditWidget::lastPage()
{
    if (fd->setNodeIter(mIdx, 0, mIter)){
        setData(mIter->t.year, mIter->t.month, mIter->t.day, mIter->t.hour, mIter->t.min, mIter->t.sec, mIter->id, mIter->value, mIter->unit);
    } else {
    //    setData(0, 0, 0, 0, 0, 0, mIdx, 0, nullptr);
    }

//    if (mIter != fd->getData().find(mIdx)->second.begin()) mIter--;
//    setData(mIter->t.year, mIter->t.month, mIter->t.day, mIter->t.hour, mIter->t.min, mIter->t.sec, mIter->id, mIter->value, mIter->unit);
}

void EditWidget::ensure()
{
    TT t;

    if (mIdx == -100){
        t.t.year = yearLineEdit->text().toInt();
        t.t.month = monthLineEdit->text().toInt();
        t.t.day = dayLineEdit->text().toInt();

        t.t.hour = hourLineEdit->text().toInt();
        t.t.min = minLineEdit->text().toInt();
        t.t.sec = secLineEdit->text().toInt();

        t.id = idLineEdit->text().toInt();
        t.value = valueLineEdit->text().toInt();
        std::list<TT> l;
        l.emplace_back(t);
        fd->getData().insert(std::pair<int, std::list<TT>>(t.id, l));
        fd->flush();
        return;
    }

    FOpt::TList::iterator tmpIter = mIter;

    if (++tmpIter == fd->getData().find(mIdx)->second.end()){
        t.t.year = yearLineEdit->text().toInt();
        t.t.month = monthLineEdit->text().toInt();
        t.t.day = dayLineEdit->text().toInt();

        t.t.hour = hourLineEdit->text().toInt();
        t.t.min = minLineEdit->text().toInt();
        t.t.sec = secLineEdit->text().toInt();

        t.id = idLineEdit->text().toInt();
        t.value = valueLineEdit->text().toInt();
        ::memset(t.unit, 0, sizeof(mIter->unit));
        ::memcpy(t.unit, unitLineEdit->text().toUtf8().data(), ::strlen(unitLineEdit->text().toUtf8().data()));
        fd->getData().find(mIdx)->second.push_back(t);
    } else {
        mIter->t.year = yearLineEdit->text().toInt();
        mIter->t.month = monthLineEdit->text().toInt();
        mIter->t.day = dayLineEdit->text().toInt();

        mIter->t.hour = hourLineEdit->text().toInt();
        mIter->t.min = minLineEdit->text().toInt();
        mIter->t.sec = secLineEdit->text().toInt();

        mIter->id = idLineEdit->text().toInt();
        mIter->value = valueLineEdit->text().toInt();
        ::memset(mIter->unit, 0, sizeof(mIter->unit));
        ::memcpy(mIter->unit, unitLineEdit->text().toUtf8().data(), ::strlen(unitLineEdit->text().toUtf8().data()));
    }
    fd->flush();
}

void EditWidget::setData(int y, int m, int d, int h, int mi, int s, int i, double v, char *u)
{
    yearLineEdit->setText(QString::number(y));
    monthLineEdit->setText(QString::number(m));
    dayLineEdit->setText(QString::number(d));
    hourLineEdit->setText(QString::number(h));
    minLineEdit->setText(QString::number(mi));
    secLineEdit->setText(QString::number(s));
    idLineEdit->setText(QString::number(i));
    valueLineEdit->setText(QString::number(v, 'f', 6));
    unitLineEdit->setText(u);
}
