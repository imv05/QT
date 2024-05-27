#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "class.h"
#include "menu.h"
#include "paint.h"
#include "search.h"

#include <QMessageBox>
#include <QStringList>
#include <QStringListModel>
#include <QLabel>
#include <QSplitter>
#include "qdebug.h"

QSplitter* splitter;
QStringList matchingStationsA;
QStringList matchingStationsB;
Station* stationA = nullptr;
Station* stationB = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置场景的背景和大小
    scene.setSceneRect(0, 0, 1920, 1080);
    scene.setBackgroundBrush(QBrush(Qt::white));
    //在场景中添加图形项
    paint(scene);
    qDebug() << "Enter mainwindow";
    CustomGraphicsView* view = new CustomGraphicsView(scene, this);
    view->setScene(&scene);

    view->setParent(ui->graphicsView); // 设置CustomGraphicsView的父控件为ui->graphicsView
    view->show(); // 确保CustomGraphicsView是可见的
    ui->listA->hide();
    ui->listB->hide();
    connect(ui->inputA, &QLineEdit::textEdited, this, &MainWindow::on_inputA_textEdited);
    connect(ui->inputB, &QLineEdit::textEdited, this, &MainWindow::on_inputB_textEdited);
    std::vector<QColor> AllColor={
        QColor(255,0,0),QColor(0,0,255),QColor(124,25,70)
        //只是一个接口

    };//保存所有的颜色，用来绘图
    std::vector<QString> AllName={
        //接口，保存所有线的名字

    };
    for(auto color: AllColor){
        QLabel* colorLabel =new QLabel(this);
        colorLabel->setStyleSheet(QString("background-color:%1;").arg(color.name()));
        QLabel* text=new QLabel("haha",this);
        text->setStyleSheet(QString("color:%1;").arg(color.name()));
        ui->formLayout->addRow(colorLabel,text);
    }

    std::unordered_map<Station*, Station*> uom = dijkstra(lineMap[1]->stationMap[3]);
    printPath(uom, lineMap[2]->stationMap[2]);

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
void MainWindow::on_inputA_returnPressed()
{
    bool flag=false;
    for(auto station:allStations){
        auto name=station->stationName;
        QString input=ui->inputA->text();
        if(name == input){ //按Enter键的，要求他完全匹配才行
            QMessageBox *find=new QMessageBox;//这个messagebox仅用于调试，以后会删除
            find->setWindowTitle("提示");
            find->setInformativeText("找到了该站！");
            stationA = allStationNames[name];
            find->setDefaultButton(QMessageBox::Ok);
            int result=find->exec();
            if(result==QMessageBox::Ok){
                delete find;
            }
            flag=true;
        }
    }
    if(flag){
        ui->inputA->clearFocus();
        ui->inputB->setFocus();
    }else{
        ui->inputA->setText(QString(""));
        QMessageBox *err=new QMessageBox;
        err->setWindowTitle("提示");
        err->setInformativeText("没有找到该站");
        err->setDefaultButton(QMessageBox::Ok);
        int result=err->exec();
        if(result==QMessageBox::Ok){
            delete err;
        }
    }
}

void MainWindow::on_inputA_editingFinished()
{
    ui->listA->hide();
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
    ui->inputA->clearFocus();
    ui->inputB->setFocus();

    QMessageBox* msg=new QMessageBox;
    msg->setInformativeText("点击了" + selectedName);
    ui->inputA->setText(selectedName);
    stationA = allStationNames[selectedName];
    msg->setDefaultButton(QMessageBox::Ok);
    int result=msg->exec();
    if(result==QMessageBox::Ok){
        delete msg;
    }
}

