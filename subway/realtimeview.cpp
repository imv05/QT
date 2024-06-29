#include "realtimeview.h"

RealtimeView::RealtimeView(QGraphicsScene& scene, QWidget*parent)
    : QGraphicsView(parent), scene_(scene){


    setMouseTracking(true); // 开启鼠标跟踪
}
