#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainview.h"
#include "planview.h"
#include "help.h"
#include <QMainWindow>
#include <QPainter>
#include <QString>
#include <QGraphicsScene>
#include <QCompleter>
#include <QStringList>
#include <QStringListModel>
#include "buttonmanage.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class MainGraphicsView;
public:
    void startupPlan(void);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_listA_clicked(const QModelIndex &index);
    void on_listB_clicked(const QModelIndex &index);

    void on_inputA_textEdited(const QString &arg1);
    void on_inputB_textEdited(const QString &arg1);

    void on_inputA_editingFinished();
    void on_inputB_editingFinished();

    void on_pushButton_clicked();

    void lineButtonclicked();
    void on_swapButton_clicked();

    void on_hincButton_clicked();

    void on_hdecButton_clicked();

    void on_mincButton_clicked();

    void on_mdecButton_clicked();

    void on_hEdit_editingFinished();

    void on_mEdit_editingFinished();
    void on_switchButton_clicked();

    void on_canButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene scene;
    MainGraphicsView* mainView;
    void refreshTime(); //刷新时间显示
    void helpwindow();
    static int curh;
    static int curm;
    static QString hstr;
    static QString mstr;
    void switchToOrdinary(void);
    void switchToLast(void);

public:
    QGraphicsScene planScene;
    QVector<buttonManage> lineButtons;
    // static int nowtime;
    // static bool isLastMode; //是否为末车规划模式
};
bool plan(void);//尝试规划函数
#endif // MAINWINDOW_H
