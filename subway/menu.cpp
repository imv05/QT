#include "menu.h"
#include "ui_menu.h"

menu::menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_clicked()
{
    delete this;
    //YOUR CODE HERE
    //显示主要界面


    MainWindow* mw=new MainWindow;
    mw->show();
}


void menu::on_pushButton_2_clicked()
{
    QApplication::quit();
}

