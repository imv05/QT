#ifndef MAINVIEW_H
#define MAINVIEW_H

#include<QGraphicsView>

class MainGraphicsView : public QGraphicsView
{
public:
    const qreal HIGHLIGHT_ELEVATION = 200;  //高亮对象zpos的抬升值
    QVector<QGraphicsItem*> highlightItemList;
    bool highlightActivated;
    MainGraphicsView(QGraphicsScene& scene, QWidget *parent = nullptr);
    void refreshHighlight(void);
    QGraphicsItem* mask;    //半透明遮罩的item指针
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
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
