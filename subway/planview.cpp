#include "planview.h"

//planview::planview() {}
PlanGraphicsView::PlanGraphicsView(QGraphicsScene& scene, QWidget *parent)
    : QGraphicsView(parent),scene_(scene){

}
