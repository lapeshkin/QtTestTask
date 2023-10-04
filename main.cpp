#include "QtTestTask.h"
#include <QtWidgets/QApplication>

#ifdef _DEBUG
#include <vld.h>
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtTestTask w;
    w.show();
    w.start();
    return a.exec();
}
