#include "menu.h"
#include "ui_menu.h"
MainWindow* menu::mw;
//创建了一个新的窗口（主界面）
menu::menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);
    ui->label_3->setScaledContents(true);
    ui->label_3->setAlignment(Qt::AlignCenter);
    // ui->label->setStyleSheet("color:red");

    ui->label_3->setStyleSheet("background-image:url(:/images/src/combined.png);");

}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_clicked()
{
    delete this;
    mw=new MainWindow;
    mw->show();
}


void menu::on_pushButton_2_clicked()
{
    QApplication::quit();
}

