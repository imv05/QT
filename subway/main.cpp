#include "mainwindow.h"
#include "realtimewindow.h"
#include "global.h"
#include "class.h"
#include "load.h"
#include "search.h"
#include "menu.h"

#include <QApplication>
#include <QBrush>
#include <QGraphicsScene>
#include <QString>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    menu *newmenu = new menu;
    newmenu->setWindowTitle("地铁线路规划");
    newmenu->show();
    RealtimeWindow *realtimewindow = new RealtimeWindow;
    // realtimewindow->show();
    load();//加载，主要的作用是提取.json文件

    return a.exec();
}
