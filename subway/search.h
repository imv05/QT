#ifndef SEARCH_H
#define SEARCH_H

#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>

std::unordered_map<Station*, Station*> dijkstra(Station* start, std::unordered_map<Station*, int>* timeMap);
QVector<Station*> getPath(const std::unordered_map<Station*, Station*>& previous, Station* target);

#endif // SEARCH_H
