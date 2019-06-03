#include "widget.h"
#include "File/filewrapper.h"
#include "File/deflection.h"
#include "File/strain.h"
#include "File/displacement.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    FileWrapper *f = FileWrapper::getInstance();
    f->attach(new Deflection, DataType::Deflection);
    f->attach(new strain, DataType::Strain);
    f->attach(new Displacement, DataType::Displacement);

    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
