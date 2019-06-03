#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include "File/fopt.h"
#include "File/filewrapper.h"

class QLabel;
class QPushButton;

class GraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphWidget(DataType type, QWidget *parent = nullptr);
    void setIdx(int idx);

private slots:
    void back();

private:
    void refresh();

private:
    int mIdx;
    FOpt::TList tL;
    DataType mType;
    FOpt::TList::iterator mIter;

    double maxValue;
    double minValue;
    long long maxTimeStamp;
    long long minTimeStamp;

private:
    QLabel *mainLabel;

    QLabel *imgLabel;

    QPushButton *backButton;

};

#endif // GRAPHWIDGET_H
