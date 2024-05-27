#ifndef SEARCH_H
#define SEARCH_H

#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>

class Plan{
    static Station* origin;
    static Station* destination;

};




std::unordered_map<Station*, Station*> dijkstra(Station* start);
void printPath(const std::unordered_map<Station*, Station*>& previous, Station* target);

#endif // SEARCH_H
