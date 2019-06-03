#include "graphwidget.h"

#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <string.h>
#include <QPushButton>

#define SCREEN_WIDTH (240)
#define SCREEN_HEIGHT (320)

#define FONT_BOLD20 QFont("", 20, 75)
#define FONT_BOLD QFont("", 17, 75)
#define FONT_BOLD16 QFont("", 14, 75)
#define FONT_TINY QFont("", 9, 50)
#define FONT_TINY11 QFont("", 11, 50)

#define GET_EVENT_POS_X            event->pos().x()
#define GET_EVENT_POS_Y            event->pos().y()

GraphWidget::GraphWidget(DataType type, QWidget *parent) :
    QWidget(parent),
    mType(type)
{
    mainLabel = new QLabel(this);
    mainLabel->setGeometry(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    mainLabel->setStyleSheet("background-color:white");

    imgLabel = new QLabel(this);
    imgLabel->setGeometry(5, 40, 155, 160);

    backButton = new QPushButton(this);
    backButton->setGeometry(0, 0, 40, 40);
    backButton->setText("返回");

    connect(backButton, SIGNAL(clicked()), this, SLOT(back()));
}

void GraphWidget::setIdx(int idx)
{
    FileWrapper *f = FileWrapper::getInstance();
//    FOpt *fd = dynamic_cast<FOpt *>(f->getFileMap().find(mType)->second);
    tL.clear();
    tL = dynamic_cast<FOpt *>(f->getFileMap().find(mType)->second)->getData().find(idx)->second;
//    TT node;
//    for (mIter = fd->getData().find(idx)->second.begin(); mIter != fd->getData().find(idx)->second.end(); mIter++){
//        ::memcpy(&node.t, &mIter->t, sizeof(TT));
//        node.id = mIter->id;
//        node.value = mIter->value;
//        ::memcpy(node.unit, mIter->unit, sizeof(node.unit));
//        tL.emplace_back(node);
//    }
//    printf("tL = %d\n", tL.size());
    tL.sort();
 //   mIdx = idx;
    refresh();
}

void GraphWidget::back()
{
    this->hide();
}

void GraphWidget::refresh()
{
    QPolygon polygon;

    if (tL.size()<2){
        return;
    }

//    for (mIter = tL.begin(); mIter != tL.end(); mIter++){
//        if (mList.at(i).distanceD*225/maxLength/5-mX>=112){
//            tmp = i;
//            break;
//        }
//    }
//    int tmpX1;
//    if (tmp == 0){
//        tmpX1 = 112;
//    } else {
//        tmpX1 = destination.at(tmp-1).distanceD*225/maxLength/5;
//    }

//    int tmpX2 = destination.at(tmp).distanceD*225/maxLength/5;
//    int tmpX = tmpX2-tmpX1;
//    int tmpY = 180-destination.at(tmp).ele*180/maxHigh/4;;
//    int tmpYDV = 0;

//    if (tmpX>4 && destination.size() > 0 && tmp > 0){
//        tmpYDV = (destination.at(tmp).ele-destination.at(tmp-1).ele)*180/maxHigh/4;
//        tmpYDV = tmpYDV*(mX-tmpX2+112)/tmpX;
//        printf("ele=%d, x= %d, xa = %d\n", tmpYDV, (mX-tmpX2+112), tmpX);

//    }

//    tmpY = tmpY-tmpYDV;
    maxValue = minValue = tL.begin()->value;
    maxTimeStamp = minTimeStamp = tL.begin()->timeStamp;
    for (mIter = tL.begin(); mIter != tL.end(); mIter++){
        maxValue = maxValue < mIter->value ? mIter->value:maxValue;
        minValue = minValue > mIter->value ? mIter->value:minValue;
        maxTimeStamp = maxTimeStamp < mIter->timeStamp ? mIter->timeStamp:maxTimeStamp;
        minTimeStamp = minTimeStamp > mIter->timeStamp ? mIter->timeStamp:minTimeStamp;
    }

    QImage img(160, 170, QImage::Format_RGB32);
    memset(img.bits(), 255, 160*170*4);
    QPainter painter(&img);

    long long tmpTimeStamp = maxTimeStamp-minTimeStamp;
    double tmpValue = maxValue-minValue;
    polygon.append(QPoint(0, 150));
    int x, y;

    for (mIter = tL.begin(); mIter != tL.end(); mIter++){
        x = static_cast<int>((mIter->timeStamp-minTimeStamp)*170/tmpTimeStamp);

        y = static_cast<int>(120-(mIter->value-minValue)/tmpValue*100);
   //     printf("x = %d, y = %d, %lf, %lf, %lf\n", x, y, mIter->value, minValue, tmpValue);
        polygon.append(QPoint(x, y));
    }

    polygon.append(QPoint(170, 150));

//    xTextLabel->setText(QString::number(maxLength)+"m");
//    yTextLabel->setText(QString::number(maxHigh)+"m");

//    distanceTextLabel->setText(getLengthString(destination.at(tmp).distanceD));
//    altitudeTextLabel->setText(getLengthString(destination.at(tmp).ele));

//    if (mMode == 1 || mMode == 2){
//        QString time = destination.at(tmp).time;
//        int y = time.mid(0, 4).toInt();
//        int m = time.mid(5, 2).toInt();
//        int d = time.mid(8, 2).toInt();
//        int h = time.mid(11, 2).toInt();
//        int m1 = time.mid(14, 2).toInt();
//        int s = time.mid(17, 2).toInt();
//        QDateTime datetime = getRealTime(0, 1, y, m, d, h, m1, s);
//        timeLabel->setText(QString("%4").arg(datetime.date().year(), 4, 10, QChar('0'))+"-"+
//                           QString("%2").arg(datetime.date().month(), 2, 10, QChar('0'))+"-"+
//                           QString("%2").arg(datetime.date().day(), 2, 10, QChar('0'))+" "+
//                           QString("%2").arg(datetime.time().hour(), 2, 10, QChar('0'))+":"+
//                           QString("%2").arg(datetime.time().minute(), 2, 10, QChar('0'))+":"+
//                           QString("%2").arg(datetime.time().second(), 2, 10, QChar('0')));
//    }

//    polygon.append(QPoint(finalDistance, 240));

    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(QColor::fromRgb(75, 188, 48));
    painter.drawPolygon(polygon);

    painter.setPen(QPen(Qt::red, 5));
    for (mIter = tL.begin(); mIter != tL.end(); mIter++){
        x = static_cast<int>((mIter->timeStamp-minTimeStamp)*170/tmpTimeStamp);

        y = static_cast<int>(120-(mIter->value-minValue)/tmpValue*100);
        painter.drawPoint(x, y);
    }

    painter.setPen(QPen(Qt::black, 1));
    painter.drawText(0, 20, QString::number(maxValue));
    painter.drawText(0, 120, QString::number(minValue));
    painter.drawText(0, 130, QString::number(minTimeStamp/31104000)+"-"+QString::number(minTimeStamp%31104000/2592000)+"-"+QString::number(minTimeStamp%2592000/86400)
                     +" "+QString::number(minTimeStamp%86400/3600)+":"+QString::number(minTimeStamp%3600/60)+":"+QString::number(minTimeStamp%60));
    painter.drawText(130, 100, QString::number(maxTimeStamp/31104000)+"-"+QString::number(maxTimeStamp%31104000/2592000)+"-"+QString::number(maxTimeStamp%2592000/86400)
                     +" "+QString::number(maxTimeStamp%86400/3600)+":"+QString::number(maxTimeStamp%3600/60)+":"+QString::number(maxTimeStamp%60));

    imgLabel->setPixmap(QPixmap::fromImage(img));
    imgLabel->raise();
}
