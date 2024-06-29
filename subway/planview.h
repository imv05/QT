#ifndef PLANVIEW_H
#define PLANVIEW_H

#include<QGraphicsView>

class PlanGraphicsView: public QGraphicsView//新的QGraphicsView的派生类，用于显示规划出来的路径
{
public:
    PlanGraphicsView(QGraphicsScene& scene, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QGraphicsScene& scene_;
};

#endif // PLANVIEW_H
