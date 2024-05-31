#include "realtimewindow.h"
#include "ui_realtimewindow.h"

RealtimeWindow::RealtimeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RealtimeWindow)
{
    ui->setupUi(this);
    isWorkingDay = true;
    ui->toggleButton->setText("切换到节假日");
}

RealtimeWindow::~RealtimeWindow()
{
    delete ui;
}

void RealtimeWindow::on_toggleButton_clicked()
{
    isWorkingDay = !isWorkingDay;
    if(isWorkingDay){
        qDebug() << "swi";
        ui->toggleButton->setText("切换到节假日");
    }else{
        ui->toggleButton->setText("切换到工作日");
    }

}

