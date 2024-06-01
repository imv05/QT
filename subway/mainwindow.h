#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainview.h"
#include "planview.h"

#include <QMainWindow>
#include <QPainter>
#include <QString>
#include <QGraphicsScene>
#include <QCompleter>
#include <QStringList>
#include <QStringListModel>
#include <QPushButton>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class buttonManage{
public:
    QPushButton* button;
    int lineOrder;
    buttonManage(QPushButton* text,int i):button(text),lineOrder(i){}
};

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

private:
    Ui::MainWindow *ui;
    QGraphicsScene scene;
    MainGraphicsView* mainView;

public:
    QGraphicsScene planScene;
    QVector<buttonManage> lineButtons;

};
bool plan(void);//尝试规划函数
#endif // MAINWINDOW_H
