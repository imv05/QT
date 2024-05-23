#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "class.h"
#include"menu.h"
#include"paint.h"
#include"search.h"
#include <QMessageBox>
#include<QStringList>
#include<QStringListModel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::on_lineEdit_textChanged);
    connect(ui->lineEdit, &QLineEdit::textEdited, this, &MainWindow::on_lineEdit_textEdited);
    std::vector<QColor> AllColor={
        QColor(255,0,0),QColor(0,0,255),QColor(124,25,70)
        //只是一个接口

    };//保存所有的颜色，用来绘图
    std::vector<QString> AllName={
        //接口，保存所有线的名字
    };
    for(auto color:AllColor){
        QLabel* colorLabel =new QLabel(this);
        colorLabel->setStyleSheet(QString("background-color:%1;").arg(color.name()));
        QLabel* text=new QLabel("haha",this);
        text->setStyleSheet(QString("color:%1;").arg(color.name()));
        ui->formLayout->addRow(colorLabel,text);
    }

    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 1920, 1080);
    scene.setBackgroundBrush(QBrush(Qt::white));


    // 在场景中添加图形项
    paint(scene);

    // // 创建一个自定义的视图
    // CustomGraphicsView view(scene);
    // view.setScene(&scene);
    // view.show();

    std::unordered_map<Station*, Station*> uom = dijkstra(lineMap[1]->stationMap[3]);
    printPath(uom, lineMap[2]->stationMap[2]);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{

}


void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    QStringList matchingStations;
    matchingStations.clear();
    for(auto station:allStations){
        auto name=station->stationName;
        if(name.contains(arg1)){
            //YOUR CODE HERE
            //高亮所有找到的地方
            matchingStations.append(name);


        }
    }

    QStringListModel* model= new QStringListModel(matchingStations,this);
    ui->listView->setModel(model);
    ui->listView->show();
}



void MainWindow::on_lineEdit_returnPressed()
{
    bool flag=false;
    for(auto station:allStations){
        auto name=station->stationName;
        QString input=ui->lineEdit->text();
        if(name.contains(input)){
            //YOUR CODE HERE
            //高亮所有找到的地方


            QMessageBox *find=new QMessageBox;//这个messagebox仅用于调试，以后会删除
            find->setWindowTitle("提示");
            find->setInformativeText("找到了该站！");
            find->setDefaultButton(QMessageBox::Ok);
            int result=find->exec();
            if(result==QMessageBox::Ok){
                delete find;
            }
            flag=true;
        }
    }
    if(!flag){
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


void MainWindow::on_lineEdit_editingFinished()
{

}


void MainWindow::on_pushButton_clicked()
{
    delete this;
    menu *newmenu=new menu;
    newmenu->show();
}


void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QString selectedText = index.data(Qt::DisplayRole).toString();
    for(auto station:allStations){
        QString name=station->stationName;
        if(name.contains(selectedText)&&selectedText.contains(name)){
            QMessageBox* msg=new QMessageBox;
            msg->setInformativeText("找到了对应的站");
            msg->setDefaultButton(QMessageBox::Ok);
            int result=msg->exec();
            if(result==QMessageBox::Ok){
                delete msg;
            }
        }
    }
}

