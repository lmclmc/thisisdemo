#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <memory>

#include "File/filewrapper.h"

class QPushButton;
class QScrollBar;
class QLabel;
class EditWidget;
class GraphWidget;
class FOpt;
class PopupMenu;

class SonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SonWidget(DataType type, QWidget *parent = nullptr);
    void init();
    int max;
    inline int getId(){
        return id;
    }

signals:
    void pushIdx(int);
    void deleteSuccess();

private slots:
    void deleteId();

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void focusInEvent(QFocusEvent *);

private:
    int id;
    DataType mType;

private:
    std::list<std::pair<std::shared_ptr<QLabel>, int>> listLabel;
};

class ListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ListWidget(DataType type, QWidget *parent = nullptr);
    void init();

private slots:
    void responScroll(int idx);
    void showEditWidget();
    void addNewId();
    void showGraphWidget();
    void responDelButton();
    void responDeleteSuccess();

protected:
    void focusInEvent(QFocusEvent *);

private:
    int id;
    DataType mType;

private:
    SonWidget *s;                   //列表控件，该控件为自定义控件

    QLabel *back;                   //标签控件，QT内部控件

    QPushButton *add;
    QPushButton *del;
    QPushButton *enter;
    QPushButton *graph;             //按钮控件，QT内部控件

    QScrollBar *scroll;             //滚动条控件，该控件为QT内部控件

    EditWidget *e;                  //编辑界面控件，该控件为自定义控件

    GraphWidget *g;                 //曲线图控件， 该控件为自定义控件

    PopupMenu *p;                   //提示框控件， 该控件为自定义控件
};



#endif // LISTWIDGET_H
