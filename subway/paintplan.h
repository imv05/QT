#ifndef PAINTPLAN_H
#define PAINTPLAN_H

#include "class.h"
#include "item.h"
#include <QGraphicsScene>

extern bool fold[50];;//用于判断当前模块是折叠态还是展开态
extern QVector<TriangleItem *> triangleItem;//展示折叠的三角形，和线路名称一同出现
extern int packedsize;

void paintFolded(QGraphicsScene& pr,int num);
void paintExpand(QGraphicsScene& pr,int num);
void paintPlan(QGraphicsScene& pr);

#endif // PAINTPLAN_H
