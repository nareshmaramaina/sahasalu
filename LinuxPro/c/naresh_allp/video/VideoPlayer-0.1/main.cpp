#include "widget.h"
#include <QApplication>
#include <QMotifStyle>
#include <QPlastiqueStyle>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(new QPlastiqueStyle);
    Widget w;
    w.show();

    return a.exec();
}
