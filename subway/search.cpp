#include "global.h"
#include "class.h"
#include "search.h"

#include <climits>

Station* Plan::stationA = nullptr;
Station* Plan::stationB = nullptr;
std::unordered_map<Station*, Station*> Plan::last_of;
std::unordered_map<Station*, int> Plan::timeMap;
QVector<Station*> Plan::planRoute;
QVector<QGraphicsItem*> Plan::hlList;
QVector<Connection> Plan::planConnections;
QVector<Line*> Plan::planLines;   //（按照line的出现顺序）
QVector<QVector<Station*> > Plan::planRouteSplit;  //（按照line的出现顺序）以不同线路分开的Station*列表
QVector<int> Plan::timeOfLine;     //（按照line的出现顺序）不同line的花费时间，按秒计，共lines个
QVector<int> Plan::directionOfLine;    //（按照line的出现顺序）不同line的方向，共lines个
QVector<Connection> Plan::transferConnections; //换乘的connection，用于展示换乘详情，共lines-1个

std::unordered_map<Station*, Station*> dijkstra(Station* start) {
    std::unordered_map<Station*, Station*> previous; // 上一个节点（父节点）
    std::priority_queue<std::pair<int, Station*>, std::vector<std::pair<int, Station*>>, std::greater<std::pair<int, Station*>>> pq; // 优先队列，按照距离排序
    std::unordered_map<Station*, int>& distance = Plan::timeMap;
    // 初始化距离和previous哈希表
    for (auto station : allStations) {
        distance[station] = INT_MAX; // 假设INT_MAX表示无穷大
        previous[station] = nullptr;
        if (station == start) {
            distance[station] = 0;
            pq.push({0, start});
        }
    }

    while (!pq.empty()) {
        auto [currDist, currStation] = pq.top();
        pq.pop();
        // 遍历当前节点的所有邻居
        for (const auto& conn : currStation->cList) {
            Station* neighbor = conn.to;
            int newDistance = distance[currStation] + conn.time;
            // 如果通过当前节点到达邻居的距离更短，则更新距离和previous哈希表
            if (newDistance < distance[neighbor]) {
                distance[neighbor] = newDistance;
                previous[neighbor] = currStation;
                pq.emplace(QPair<int, Station*>(newDistance, neighbor));
            }
        }
    }
    // 返回previous哈希表，用于回溯路径
    return previous;
}

// 使用示例：打印从起始站到目标站的路径
QVector<Station*> getPath(const std::unordered_map<Station*, Station*>& previous, Station* target) {
    if (previous.find(target)==previous.end() || previous.at(target) == nullptr) {
        qDebug() << "No path found to" << target->stationName;
        return QVector<Station*>();
    }

    QVector<Station*> path;
    for (Station* current = target; current != nullptr; current = previous.at(current)) {
        path.prepend(current); // 反向添加节点到路径中
    }
    if(path.size()>=2){
        if(path[0]->lineId != path[1]->lineId){
            path.pop_front();
        }
        if(path.size()>=2){
            if(path[path.size()-1]->lineId != path[path.size()-2]->lineId){
                path.pop_back();
            }
        }
    }
    // qDebug() << "Path from start to" << target->stationName << ":";
    // for (Station* station : path) {
    //     qDebug() << station->line->lineName << " " << station->stationName;
    // }
    return path;
}

bool Plan::makePlan(void){
    // qDebug() << "Enter plan";
    if(stationA){//起点已给出，即可开始规划
        last_of = dijkstra(stationA);//算法返回最后一步，用于回溯。
        // qDebug() << last_of.size();
        return true;
    }else{//起点为nullptr，失败
        return false;
    }
}
bool Plan::getRoute(void){//规划成功返回true
    if(stationA && stationB && stationA != stationB){//终点已给出，可以开始回溯
        qDebug() << "trying to get route";
        planRoute = getPath(last_of, stationB);//完成回溯，输出起点到终点的路线
        int routeNodeCnt = planRoute.size();
        if(routeNodeCnt<=1)return false;
        for(auto planNode: planRoute){
            qDebug() << planNode->line->lineName << planNode->stationName;
        }
        //维护planConnections
        for(int i=0; i<routeNodeCnt-1; i++){
            Station* current = planRoute[i];
            for(auto cit: current->cList){
                if(cit.to == planRoute[i+1]){
                    planConnections.push_back(cit);
                    break;
                }
            }
        }
        if(planConnections.size()!=routeNodeCnt-1){ //检查planConnections的数量是否正确
            qDebug() << "finding route Connection incomplete";
        }
        //维护hlList
        for(int i=0; i<routeNodeCnt; i++){//将每个涉及的车站加入预高亮列表
            hlList.push_back(planRoute[i]->item);
            hlList.push_back(planRoute[i]->textItem);
        }
        for(int i=0; i<routeNodeCnt-1; i++){//将每个涉及的车站连接器加入预高亮列表
            if(!planConnections[i].isTransfer){//前后两车站不是换乘关系时需要
                hlList.push_back(pathItemMap[QPair<Station*, Station*>(planRoute[i],  planRoute[i+1])]);
            }
        }
        //维护planLines,planRouteSplit,timeOfLine,directionOfLine,transferConnections共5个变量
        planLines.push_back(planRoute[0]->line);
        timeOfLine.push_back(0);
        planRouteSplit.push_back(QVector<Station*>());
        planRouteSplit[0].push_back(planRoute[0]);//添加分线Station*的第一个车站
        int currentLineOrder = 0;//当前加入的车站所在线在plan中的顺位
        for(int i=0; i<routeNodeCnt-1; i++){
            if(!planConnections[i].isTransfer){//前后两车站不是换乘关系时
                //添加directionOfLine
                directionOfLine.push_back(planConnections[i].direction);
                //需要添加Path至预高亮item列表
                hlList.push_back(pathItemMap[QPair<Station*, Station*>(planRoute[i],  planRoute[i+1])]);
                //然后将车站加到当前的Split
                planRouteSplit[currentLineOrder].push_back(planRoute[i+1]);
                //增加分线时间
                timeOfLine[currentLineOrder] += planConnections[i].time;
            }else{//如果是换乘关系，则加入换乘列表
                currentLineOrder ++ ;
                transferConnections.push_back(planConnections[i]);  //当前Connection加入transferConnections
                planLines.push_back(planConnections[i].to->line);   //将该次换乘后的line加入line列表
                //Split列表加入新线，然后顺位+1
                planRouteSplit.push_back(QVector<Station*>());
                planRouteSplit[currentLineOrder].push_back(planRoute[i+1]);
                //分线时间切换到下一个
                timeOfLine.push_back(0);
            }
        }
        for(int i=0; i<planLines.size()-1; i++){
            qDebug() << transferConnections[i].note;
        }
        return true;
    }else return false;
}
