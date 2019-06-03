#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class ListWidget;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    ListWidget *list;                           //列表控件
};

#endif // WIDGET_H
