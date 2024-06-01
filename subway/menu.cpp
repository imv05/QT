#include "menu.h"
#include "ui_menu.h"

//创建了一个新的窗口（主界面）
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
    MainWindow* mw=new MainWindow;
    mw->show();
}


void menu::on_pushButton_2_clicked()
{
    QApplication::quit();
}

