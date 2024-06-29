#ifndef REALTIMEVIEW_H
#define REALTIMEVIEW_H

#include "item.h"
#include "class.h"

#include <QGraphicsView>

class RealtimeView : public QGraphicsView
{
public:

    RealtimeView(QGraphicsScene& scene, QWidget *parent = nullptr);
private:
    QGraphicsScene& scene_;
};

#endif // REALTIMEVIEW_H
