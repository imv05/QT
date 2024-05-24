#include "mainwindow.h"

#include <QApplication>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QFont>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QString>
#include <QLabel>
#include <QWheelEvent>
#include <QMessageBox>
#include <unordered_map>

#include "global.h"
#include "class.h"
#include "load.h"
#include "paint.h"
#include "search.h"
#include "menu.h"
#include "mouse.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    menu *newmenu=new menu;
    // newmenu->resize(1000,700);
    newmenu->setWindowTitle("北京地铁线路总览");
    newmenu->show();


    // 创建一个场景
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 1920, 1080);
    scene.setBackgroundBrush(QBrush(Qt::white));

    load();

    // 在场景中添加图形项
    paint(scene);

    // 创建一个自定义的视图
    CustomGraphicsView view(scene);
    view.setScene(&scene);
    view.show();

    std::unordered_map<Station*, Station*> uom = dijkstra(lineMap[1]->stationMap[3]);
    printPath(uom, lineMap[2]->stationMap[2]);
    /*
    MainWindow w;
    w.resize(1000,700);

    w.setWindowTitle("北京地铁线路图总览");
    w.show();*/
    return a.exec();
}
