#include "mainwindow.h"
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
    // newmenu->resize(1000,700);
    newmenu->setWindowTitle("总览");
    newmenu->show();

    // 创建一个场景
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 1920, 1080);
    scene.setBackgroundBrush(QBrush(Qt::white));

    load();//加载，主要的作用是提取.json文件

    return a.exec();
}
