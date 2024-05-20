#ifndef CLASS_H
#define CLASS_H

#include "global.h"
#include <QColor>
#include <QString>
#include <QVector>
#include <QGraphicsItem>

class Line;
class Station;
class Connection;
class Operation;

class Station{//站点类，换乘站按线路分开计
public:
    Line* line;
    int lineId; //该站所在线的lineId
    int stationId;  //该站的stationId
    QString stationName;    //该站的中文名
    QString stationEngName; //该站的罗马字母拼写
    bool available; //该站是否已经开通
    int cCnt;   //通过本线列车，该站所能直接到达站点的数量，通常情况下，非换乘站：起终点为1，其余站为2
    QVector<Connection> cList; //直接到达站点列表
    int iCnt;   //可换乘其他线数量
    int opCnt;  //运营首末班车时间的条目数量，不小于cCnt
    QVector<Operation> opList; //运营条目列表
    int floor;  //站台层，用以判断是否是高架站（观光用）
    QString scenery;    //风景点描述，例如“可去往故宫、天安门广场”，****建议创建Scenery类，届时此处改为Scenery****
    QString note;   //备注，例如“该站不可付费区内换向”
    QGraphicsItem* item;
    QGraphicsTextItem* textItem;
    int x;
    int y;
public:
    Station(json jstation, Line* cLine);
    void initializeConnection(json jstation);
};

class Connection{//直接连接类，用在规划算法中
public:
    bool isTransfer;    //该连接类是否是换乘。true为是，false为不是（即在一条线上）
    Station* from;  //本站指针
    Station* to;    //指向下一站的指针
    int dist;  //至下一站的距离，单位m
    int time;  //至下一站的运行时间，单位s
    int last;  //此方向至下一站的末班车时间
    QString note;   //当这一连接为换乘时，可能有说明。
    bool isOut; //是否为出站换乘
public:
    Connection(json jconnection, Station* cStation);
};

class Operation{//首末班车类，用以在站点详情中显示
public:
    QString direction;  //首末班车时间的说明，例如“开往：安河桥北”、“内环 终点站：西直门”、“终点站：四惠东”，直接显示即可。
    bool isFirst;   //是否有首班车
    bool isLast;    //是否有末班车
    int first; //首班车时间
    int last;  //末班车时间
};

class Line{//线路类
public:
    int lineId; //该线的lineId
    QString lineName;   //该线的中文名
    QString lineEngName;    //该线的英文名
    bool isLoop;    //是否是环线（在当前数据结构下，似乎没用）
    bool isNumeral; //是否为纯数字
    int interval;  //发车间隔
    QColor color;
    QMap<int, Station*> stationMap;         //<int stationId, Station*>
    int stationCnt;
    QGraphicsRectItem* item;
    QGraphicsTextItem* textItem;
public:
    Line(json jLine);
    void initializeConnectionLine(json jLine);
    Station* operator[](int stationId);
};

class Route{
public:
    Station* origin;
    QVector<Connection*> detail;
    Station* destination;
};

extern QMap<int, Line*> lineMap;
extern QVector<Station*> allStations;

#endif // CLASS_H
