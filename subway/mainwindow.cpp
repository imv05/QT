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
#include <QScrollBar>
QSplitter* splitter;
QStringList matchingStationsA;
QStringList matchingStationsB;

int MainWindow::curh = 21;
int MainWindow::curm = 0;
QString MainWindow::hstr = "21";
QString MainWindow::mstr = "00";
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
    planScene.setSceneRect(0,0,301,1600);
    planScene.setBackgroundBrush(QBrush(Qt::white));
    PlanGraphicsView* planView=new PlanGraphicsView(planScene,this);
    planView->setScene(&planScene);
    ui->planGraphicsView->verticalScrollBar()->setValue(0);
    planView->verticalScrollBar()->setValue(0);
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
    QAction* helpAction = ui->menubar->addAction("帮助");
    connect(helpAction, &QAction::triggered, qApp, &QApplication::quit);
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
    isCan = false; //默认非末车可达查询模式

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
        for(auto station=allStationNames.begin(); station!=allStationNames.end(); station++){
            if(*station != nullptr){ //此处未知原因偶现nullptr导致的SIGSEV，已排除c++11 ranged-based loop might detach QT container
                QString name = (*station)->stationName;
                QString pinyin((*station)->stationEngName);
                QRegularExpression argpy(arg1);
                if(pinyin.contains(argpy)){
                    matchingStationsB.append(name);
                }
            }
        }
    } else { //如果输入的字符串不是纯字母，则进行中文站名匹配
        for(auto station=allStationNames.begin(); station!=allStationNames.end(); station++){
            if(*station != nullptr){ //此处未知原因偶现nullptr导致的SIGSEV，已排除c++11 ranged-based loop might detach QT container
                QString name = (*station)->stationName;
                if(name.contains(arg1)){
                    matchingStationsB.append(name);
                }
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
    if(!ui->listA->hasFocus())ui->listA->hide();//无论输的对不对，离开inputA后，listA均需要隐藏
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
    if(!ui->listB->hasFocus())ui->listB->hide();
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

void MainWindow::on_listB_clicked(const QModelIndex &index)
{
    ui->listB->hide();
    QString selectedName = matchingStationsB.value(index.row());
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
    }else if(Plan::stationA && Plan::stationB){
        QMessageBox noPathMsg;
        QString info("找不到 "+Plan::stationA->stationName+" 到 "+Plan::stationB->stationName);
        if(Plan::isLastMode){
            info += " 出发时间" + hstr + ":" + mstr;
        }
        info += " 的路径！";
        noPathMsg.setText(info);
        noPathMsg.exec();
    }
}

void MainWindow::on_hincButton_clicked()
{
    curh ++;
    if(curh==24)curh=0;
    refreshTime();
}

void MainWindow::on_hdecButton_clicked()
{
    curh--;
    if(curh==-1)curh=23;
    refreshTime();
}

void MainWindow::on_mincButton_clicked()
{
    curm++;
    if(curm==60){
        curm=0;
        on_hincButton_clicked();
    }
    refreshTime();
}

void MainWindow::on_mdecButton_clicked()
{
    curm--;
    if(curm==-1){
        curm=59;
        on_hdecButton_clicked();
    }
    refreshTime();
}

void MainWindow::on_hEdit_editingFinished()
{
    const QString arg1 = ui->hEdit->text();
    bool valid = true;
    int nv = 0;
    if(arg1.size()>2){
        valid = false;
    }else{
        nv = arg1.toInt();
        if(nv==24)nv=0;
        if(nv>23||nv<0){
            valid = false;
        }
    }
    if(valid){
        curh = nv;
    }
    refreshTime();
}

void MainWindow::on_mEdit_editingFinished()
{
    const QString arg1 = ui->mEdit->text();
    bool valid = true;
    int nv = 0;
    if(arg1.size()>2){
        valid = false;
    }else{
        nv = arg1.toInt();
        if(nv==60)nv=0;
        if(nv>59||nv<0){
            valid = false;
        }
    }
    if(valid){
        curm = nv;
    }
    refreshTime();
}

void MainWindow::refreshTime(void){
    hstr = QString("%1").arg(curh, 2, 10, QLatin1Char('0'));
    ui->hEdit->setText(hstr);
    mstr = QString("%1").arg(curm, 2, 10, QLatin1Char('0'));
    ui->mEdit->setText(mstr);
    Plan::starth = curh;
    Plan::startm = curm;
    Plan::starttime = 3600*curh+60*curm;
    if(Plan::starttime<=3*3600){
        Plan::starttime += 24*3600;
    }
    if(isCan){
        requestCanSearch();
    }else{
        switchToLast(); //当修改了时间，自动切换为末车查询模式
    }
}

void MainWindow::on_switchButton_clicked()
{
    if(Plan::isLastMode){
        switchToOrdinary();
    }else{
        switchToLast();
    }
}

void MainWindow::switchToLast(void)
{
    Plan::isLastMode = true;
    ui->switchButton->setText("当前为末车查询");
    isCan = false;
    startupPlan();
}

void MainWindow::switchToOrdinary(void)
{
    Plan::isLastMode = false;
    ui->switchButton->setText("当前为普通查询");
    startupPlan();
    isCan = false;
}

void MainWindow::on_canButton_clicked()
{
    Plan::isLastMode = true;
    isCan = true;
    requestCanSearch();
}

void MainWindow::requestCanSearch(void){
    ui->inputB->clear();
    planScene.clear();
    ui->switchButton->setText("当前为末车可达");
    mainView->highlightItemList.clear();
    if(Plan::makePlan()){
        for(auto station: allStations){
            Plan::stationB = station;
            if(Plan::getRoute()){
                mainView->highlightItemList += Plan::hlList;
            }
        }
    }
    mainView->showHighlight();
    Plan::stationB = nullptr;
}
