#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>

#include "File/filewrapper.h"
#include "File/fopt.h"
#include "File/deflection.h"

class QLineEdit;
class QLabel;
class QPushButton;
class FOpt;

class EditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EditWidget(DataType type, QWidget *parent = nullptr);
    void setIdx(int idx);

private slots:
    void exitEdit();
    void nextPage();
    void lastPage();
    void ensure();

private:
    void setData(int y, int m, int d, int h, int mi, int s, int i, double v, char *u = nullptr);

private:
    int mIdx;
    int mLIdx;

    FOpt::TList::iterator mIter;
    FOpt  *fd;
    DataType mType;

private:
    QLabel *mainLabel;

    QLabel *yearLabel;
    QLabel *monthLabel;
    QLabel *dayLabel;
    QLabel *hourLabel;
    QLabel *minLabel;
    QLabel *secLabel;
    QLabel *idLabel;
    QLabel *valueLabel;
    QLabel *unitLabel;

    QLineEdit *yearLineEdit;
    QLineEdit *monthLineEdit;
    QLineEdit *dayLineEdit;
    QLineEdit *hourLineEdit;
    QLineEdit *minLineEdit;
    QLineEdit *secLineEdit;
    QLineEdit *idLineEdit;
    QLineEdit *valueLineEdit;
    QLineEdit *unitLineEdit;

    QPushButton *editButton;
    QPushButton *nextButton;
    QPushButton *lastButton;
    QPushButton *backButton;
};

#endif // BASEWIDGET_H
