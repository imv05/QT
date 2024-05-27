#ifndef SEARCH_H
#define SEARCH_H

#include "class.h"
#include <algorithm>
#include <vector>
#include <QVector>
#include <queue>
#include <unordered_map>
#include <utility>

std::unordered_map<Station*, Station*> dijkstra(Station* start, std::unordered_map<Station*, int>* timeMap);
class Plan{//规划方案类
public:
    static Station* stationA;
    static Station* stationB;
    static std::unordered_map<Station*, Station*> last_of;
    static std::unordered_map<Station*, int> timeMap;
    static QVector<Station*> planRoute;
    static bool makePlan(void);
    static bool getRoute(void);
};

#endif // SEARCH_H
