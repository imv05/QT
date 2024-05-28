#ifndef MAINVIEW_H
#define MAINVIEW_H

#include<QGraphicsView>

class MainGraphicsView : public QGraphicsView
{
public:
    MainGraphicsView(QGraphicsScene& scene, QWidget *parent = nullptr);
protected:
    // 重写鼠标按下事件
    void mousePressEvent(QMouseEvent *event) override;
    // 重写鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event) override;
    // 重写鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event) override;
    // 重写滚轮事件
    void wheelEvent(QWheelEvent *event) override;
private:
    bool isDragging; // 是否正在拖动
    QPoint lastMousePos; // 上次鼠标位置
    QGraphicsScene& scene_;
    QGraphicsTextItem* m_infoLabel = nullptr;
    void showInfoLabel(const QPointF& pos, const QString& text);
    void hideInfoLabel();
};


#endif // MAINVIEW_H
