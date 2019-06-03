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
    void focusInEvent(QFocusEvent *event);

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
    void focusInEvent(QFocusEvent *event);

private:
    int id;
    DataType mType;

private:
    SonWidget *s;

    QLabel *back;

    QPushButton *add;
    QPushButton *del;
    QPushButton *enter;
    QPushButton *graph;

    QScrollBar *scroll;

    EditWidget *e;

    GraphWidget *g;

    PopupMenu *p;
};



#endif // LISTWIDGET_H
