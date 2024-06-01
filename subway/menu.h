#ifndef MENU_H
#define MENU_H

#include "mainwindow.h"

#include <QWidget>

namespace Ui {
class menu;
}

class menu : public QWidget
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    static MainWindow* mw;
    ~menu();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::menu *ui;
};

#endif // MENU_H
