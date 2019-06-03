#ifndef POPUPMENU_H
#define POPUPMENU_H

#include <QWidget>

class QLabel;
class QPushButton;

class PopupMenu : public QWidget
{
    Q_OBJECT
public:
    explicit PopupMenu(QWidget *parent = nullptr, int mode = 10);
    void setMainText(QString src);
    void setLeftText(QString src);
    void setRightText(QString src);
    void setCenText(QString src);
    void setYValue(int Y);
    void setMode(int mode);

signals:
    void yesChange();
    void noChange();

private slots:
    void responYes();
    void responNo();

private:
    int mMode;                                      //选项模式 0：双选项 1：单选项  2:无选项

private:
    QLabel *overAllLabel;

    QLabel *mainLabel;
    QPushButton *leftLabel;
    QPushButton *rightLabel;
    QLabel *cenLabel;
    QLabel* pixLeftLabel;
    QLabel* pixRightLabel;
    QLabel* pixCenLabel;

    QLabel* mainTextLabel;
};

#endif // POPUPMENU_H
