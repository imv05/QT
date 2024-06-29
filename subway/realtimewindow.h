#ifndef REALTIMEWINDOW_H
#define REALTIMEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStringList>
#include <QList>
#include <QIODevice>
#include <QFile>
#include "class.h"
#include "buttonmanage.h"
#include "realtimeview.h"
#include "realtimeclass.h"

namespace Ui {
class RealtimeWindow;
}

class RealtimeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RealtimeWindow(QWidget *parent = nullptr);
    ~RealtimeWindow();

private slots:
    void on_whdayButton_clicked();

    void on_hincButton_clicked();

    void on_hdecButton_clicked();

    void on_mincButton_clicked();

    void on_mdecButton_clicked();

    void on_hEdit_editingFinished();

    void on_mEdit_editingFinished();

private:
    Ui::RealtimeWindow *ui;
    bool isWorkday;
    int direction;  //在实时窗口中定义1为一个方向，2为另一个方向
    Line* curLine;
    int curStationId;
    int curh;
    int curm;
    int nowtime;
    QVector<buttonManage> lineButtons;
    void lineButtonclicked(void);
    void refreshTime(void);
    void rtLoad(void);
    QStringList header;
    QList<QString> code; //车次，共n
    QList<QList<int> > time;    //时刻表，共n*stationCnt
    QList<QList<int> > crowd;   //拥挤度，共n*stationCnt
    QList<int> origId;
    QList<int> destId;
    int stationCnt; //总站数
    int n;  //总车次数
    QGraphicsScene rtScene;
};

#endif // REALTIMEWINDOW_H
