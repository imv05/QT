#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "class.h"
#include"menu.h"
#include"paint.h"
#include"search.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::on_lineEdit_textChanged);
    connect(ui->lineEdit, &QLineEdit::textEdited, this, &MainWindow::on_lineEdit_textEdited);
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

    for(auto station:allStations){
        auto name=station->stationName;
        if(name.contains(arg1)){
            //YOUR CODE HERE
            //高亮所有找到的地方

        }
    }

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

