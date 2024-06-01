#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "class.h"
#include "menu.h"
#include "paintmain.h"
#include "paintplan.h"
#include "search.h"
#include "mainview.h"

#include <QMessageBox>
#include <QStringList>
#include <QStringListModel>
#include <QLabel>
#include <QSplitter>
#include <QVector>
#include <QDebug>
QSplitter* splitter;
QStringList matchingStationsA;
QStringList matchingStationsB;

//QGraphicsScene MainWindow::planScene;

QVector<Station*> planPath;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap backgroundPixmap(":/images/src/doubleArrow.jpg");
    backgroundPixmap=backgroundPixmap.scaled(ui->swapButton->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    ui->swapButton->setIcon(QIcon(backgroundPixmap));
    ui->swapButton->setIconSize(ui->swapButton->size());
    ui->swapButton->setToolTip("交换起点与终点");
    //设置主场景的背景和大小
    // scene.setSceneRect(0, 0, 4536, 2990);
    scene.setBackgroundBrush(QBrush(Qt::white));
    //在主场景中绘制线路图
    paintMain(scene);
    mainView = new MainGraphicsView(scene, this                                                                                                                                                       );
    mainView->setScene(&scene);
    // 设置MainGraphicsView的父控件为ui->mainGraphicsView
    mainView->setParent(ui->mainGraphicsView);
    mainView->show();

    //设置规划场景的背景和大小
    planScene.setSceneRect(0,0,301,731);
    planScene.setBackgroundBrush(QBrush(Qt::white));
    PlanGraphicsView* planView=new PlanGraphicsView(planScene,this);
    planView->setScene(&planScene);
    // 设置PlanGraphicsView的父控件为ui->planGraphicsView
    planView->setParent(ui->planGraphicsView);
    planView->show();

    ui->listA->hide();
    ui->listB->hide();
    connect(ui->inputA, &QLineEdit::textEdited, this, &MainWindow::on_inputA_textEdited);
    connect(ui->inputB, &QLineEdit::textEdited, this, &MainWindow::on_inputB_textEdited);
    int lineCnt = lineMap.size();
    std::vector<QColor> allColor={};//保存所有的颜色，用来绘图
    std::vector<QString> allName={};
    QVector<Line*> allLine = {};
    for(auto cline: lineMap){
        allColor.push_back(cline->color);
        allName.push_back(cline->lineName);
        allLine.push_back(cline);
    }

    for(int i=0; i<lineCnt; i++){
        QLabel* colorLabel =new QLabel(this);
        colorLabel->setStyleSheet(QString("background-color:%1;").arg(allColor[i].name()));
        QPushButton* text=new QPushButton(allName[i]);
        text->setStyleSheet("QPushButton { text-align: left; }");
        lineButtons.append(buttonManage(text,i));
        connect(text,&QPushButton::clicked,this,&MainWindow::lineButtonclicked);
        // QLabel* text=new QLabel(allName[i], this);
        // text->setStyleSheet(QString("color:#000000;"));
        ui->formLayout->addRow(colorLabel, text);
    }

    QAction* quitAction = ui->menubar->addAction("退出");
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);

    // // 直接在菜单项写
    // QAction* desiredAction = ui->menubar->addAction("action");
    // connect(desiredAction, &QAction::triggered, qApp, &func);
    // // 写子菜单
    // QMenu* menu = ui->menubar->addMenu("YOUR MENU");
    // QAction* desiredAction1 = ui->menubar->addAction("action1");
    // connect(desiredAction1, &QAction::triggered, qApp, &func1);
    // QAction* desiredAction2 = ui->menubar->addAction("action2");
    // connect(desiredAction2, &QAction::triggered, qApp, &func2);
    // menu->addSeparator();//建立另一个父菜单

}

void MainWindow::lineButtonclicked(){   //点击右侧的线路，高亮该线路
    auto* button = qobject_cast<QPushButton*>(sender());
    if(button){
        for(auto one: lineButtons){
            if(one.button==button){
                Line* cLine = *(lineMap.begin().operator +=(one.lineOrder));
                QVector<QGraphicsItem*> hlList = cLine->pathItemList;
                for(auto stn: cLine->stationMap){
                    hlList.push_back(stn->item);
                    hlList.push_back(stn->textItem);
                }
                mainView->highlightItemList = hlList;
                mainView->showHighlight();
                break;
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_inputA_textEdited(const QString &arg1)
{
    matchingStationsA.clear();
    QRegularExpression rx("^[A-Za-z]+$");
    if (arg1.contains(rx)) {//如果输入的字符串是纯字母，则进行拼音匹配
        for(auto station: allStationNames){
            QString name = station->stationName;
            QString pinyin(station->stationEngName);
            QRegularExpression argpy(arg1);
            if(pinyin.contains(argpy)){
                matchingStationsA.append(name);
            }
        }
    } else { //如果输入的字符串不是纯字母，则进行中文站名匹配
        for(auto station: allStationNames){
            QString name = station->stationName;
            if(name.contains(arg1)){
                matchingStationsA.append(name);
            }
        }
    }
    QStringListModel* model= new QStringListModel(matchingStationsA, this);
    ui->listA->setModel(model);
    ui->listA->show();
}
void MainWindow::on_inputB_textEdited(const QString &arg1)
{
    matchingStationsB.clear();
    QRegularExpression rx("^[A-Za-z]+$");
    if (arg1.contains(rx)) {//如果输入的字符串是纯字母，则进行拼音匹配
        for(auto station: allStationNames){
            QString name = station->stationName;
            QString pinyin(station->stationEngName);
            QRegularExpression argpy(arg1);
            if(pinyin.contains(argpy)){
                matchingStationsB.append(name);
            }
        }
    } else { //如果输入的字符串不是纯字母，则进行中文站名匹配
        for(auto station: allStationNames){
            QString name = station->stationName;
            if(name.contains(arg1)){
                matchingStationsB.append(name);
            }
        }
    }
    QStringListModel* model= new QStringListModel(matchingStationsB, this);
    ui->listB->setModel(model);
    ui->listB->show();
}
void MainWindow::on_inputA_editingFinished()
{
    bool flag=false;
    for(auto station:allStations){
        auto name=station->stationName;
        QString input=ui->inputA->text();
        if(name == input){ //按Enter键的，要求他完全匹配才行
            Plan::stationA = allStationNames[name];
            flag=true;
        }
    }
    if(flag){
        ui->inputA->clearFocus();
        ui->inputB->setFocus();
        startupPlan();
    }else{
        ui->inputA->setText(QString(""));//无法匹配则清空输入，需要重新输入
    }
    ui->listA->hide();//无论输的对不对，离开inputA后，listA均需要隐藏
}

void MainWindow::on_inputB_editingFinished()
{
    bool flag=false;
    for(auto station:allStations){
        auto name=station->stationName;
        QString input=ui->inputB->text();
        if(name == input){ //按Enter键的，要求他完全匹配才行
            Plan::stationB = allStationNames[name];
            flag=true;
        }
    }
    if(flag){
        ui->inputB->clearFocus();
        startupPlan();
    }else{
        ui->inputB->setText(QString(""));
    }
    ui->listB->hide();
}

void MainWindow::on_pushButton_clicked()
{
    delete this;
    menu *newmenu=new menu;
    newmenu->show();
}

void MainWindow::on_listA_clicked(const QModelIndex &index)
{
    ui->listA->hide();
    QString selectedName = matchingStationsA.value(index.row());
    ui->inputA->setText(selectedName);
    Plan::stationA = allStationNames[selectedName];
    ui->inputA->clearFocus();
    ui->inputB->setFocus();
    startupPlan();
}

void MainWindow::on_listA_clicked(const QString selectedName)
{
    ui->inputA->setText(selectedName);
    Plan::stationA = allStationNames[selectedName];
    ui->inputA->clearFocus();
    ui->inputB->setFocus();
    startupPlan();
}

void MainWindow::on_listB_clicked(const QModelIndex &index)
{
    ui->listB->hide();
    QString selectedName = matchingStationsB.value(index.row());
    ui->inputB->setText(selectedName);
    Plan::stationB = allStationNames[selectedName];
    ui->inputB->clearFocus();
    startupPlan();
}

void MainWindow::on_listB_clicked(const QString selectedName)
{
    ui->inputB->setText(selectedName);
    Plan::stationB = allStationNames[selectedName];
    ui->inputB->clearFocus();
    startupPlan();
}

void MainWindow::on_swapButton_clicked()
{
    QString a=ui->inputA->text();
    QString b=ui->inputB->text();
    ui->inputA->setText(b);
    ui->inputB->setText(a);
    Plan::stationA=allStationNames[b];
    Plan::stationB=allStationNames[a];
    startupPlan();
}

void MainWindow::startupPlan(){//所有做规划以及之后的显示动作
    if(Plan::makePlan())if(Plan::getRoute()){
        paintPlan(planScene);
        //高亮
        mainView->highlightItemList = Plan::hlList;
        mainView->showHighlight();
    }
}
