#include "global.h"
#include "class.h"
#include "search.h"

#include <climits>

Station* Plan::stationA = nullptr;
Station* Plan::stationB = nullptr;
std::unordered_map<Station*, Station*> Plan::last_of;
std::unordered_map<Station*, int> Plan::timeMap;
QVector<Station*> Plan::planRoute;

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

    qDebug() << "Path from start to" << target->stationName << ":";
    for (Station* station : path) {
        qDebug() << station->line->lineName << " " << station->stationName;
    }
    return path;
}

bool Plan::makePlan(void){
    qDebug() << "Enter plan";
    if(stationA){//起点已给出，即可开始规划
        last_of = dijkstra(stationA);//算法返回最后一步，用于回溯。

        return true;
    }else{//起终点中有nullptr，失败
        return false;
    }
}
bool Plan::getRoute(void){
    qDebug() << "trying to get route";
    if(stationB){//终点已给出，可以开始回溯
        planRoute = getPath(last_of, stationB);//完成回溯，输出起点到终点的路线
        for(auto planNode: planRoute){

        }
    }
}
