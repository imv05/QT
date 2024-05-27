#ifndef PAINT_H
#define PAINT_H

#include "class.h"
#include <QGraphicsScene>
#include <unordered_map>

void paintLine(QGraphicsScene& sc, Line* cLine);
void paint(QGraphicsScene& pr);
void paintTime(QGraphicsScene& sc, std::unordered_map<Station*, int> timeMap);
void clearTime(QGraphicsScene& sc);


#endif // PAINT_H
