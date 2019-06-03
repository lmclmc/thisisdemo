#include "widget.h"
#include "File/filewrapper.h"
#include "File/deflection.h"
#include "File/strain.h"
#include "File/displacement.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    FileWrapper *f = FileWrapper::getInstance();                //单例模式的文件操作模块
    f->attach(new Deflection, DataType::Deflection);            //将各个传感器方法注册到该单例模式的文件操作模块内，如果有新增传感器种类
                                                                //均可以使用attach方法注册到文件操作模块中，节省工作量
    f->attach(new strain, DataType::Strain);
    f->attach(new Displacement, DataType::Displacement);

    QApplication a(argc, argv);                                 //QT全局类，用于全局事件的处理及分发
    Widget w;                                                   //UI主界面，该界面继承QWidget，所以拥有QWidget所有特性
                                                                //QWidget属于QT的一套框架，该类会获取来自QApplication循环中分发的事件
    w.show();                                                   //将UI界面显示出来

    return a.exec();                                            //QT事件循环，所有的操作均从这里产生
}
