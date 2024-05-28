#ifndef PAINTMAIN_H
#define PAINTMAIN_H

#include "class.h"
#include <QGraphicsScene>
#include <unordered_map>

void paintLine(QGraphicsScene& sc, Line* cLine);
void paintMain(QGraphicsScene& pr);
void paintTime(QGraphicsScene& sc, std::unordered_map<Station*, int> timeMap);
void clearTime(QGraphicsScene& sc);


#endif // PAINTMAIN_H
