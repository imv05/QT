#ifndef SEARCH_H
#define SEARCH_H

#include "class.h"
#include <algorithm>
#include <vector>
#include <QVector>
#include <queue>
#include <unordered_map>
#include <utility>

class Plan{//规划方案类
public:
    static Station* stationA;
    static Station* stationB;
    static int starttime;
    static bool isLastMode;
    static std::unordered_map<Station*, Station*> last_of;
    static std::unordered_map<Station*, int> timeMap;
    static QVector<Station*> planRoute; //所有Staton*
    static QVector<Connection> planConnections; //所有Connection
    static QVector<QGraphicsItem*> hlList;  //预高亮item列表
    static int planTotalTime;       //总时长
    static int planTotalSections;   //总站数（坐几站）
    static QVector<Line*> planLines;   //（按照line的出现顺序）
    static QVector<QVector<Station*> > planRouteSplit;  //（按照line的出现顺序）以不同线路分开的Station*列表
    static QVector<int> timeOfLine;     //（按照line的出现顺序）不同line的花费时间，按秒计，共lines个
    static QVector<int> directionOfLine;    //（按照line的出现顺序）不同line的方向，共lines个
    static QVector<Connection> transferConnections; //换乘的connection，用于展示换乘详情，共lines-1个

    static bool makePlan(void);
    static bool getRoute(void);
    static std::unordered_map<Station*, Station*> dijkstra(Station* start);
    static int makePlan_n(Station* A=Plan::stationA,Station* B=Plan::stationB);

private:
    static QVector<Station*> getPath(const std::unordered_map<Station*, Station*>& previous, Station* target);
};

#endif // SEARCH_H
