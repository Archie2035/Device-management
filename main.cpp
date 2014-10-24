#include "widget.h"
#include <QApplication>
#include "connection.h"
int main(int argc, char *argv[])
{
    if(!creatConnection())
    {
        qDebug("数据库打开失败");
        return 0;
    }

    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
