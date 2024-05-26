#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mouse.h"

#include <QMainWindow>
#include <QPainter>
#include <QString>
#include <QGraphicsScene>
#include <QCompleter>
#include <QStringList>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_inputA_textEdited(const QString &arg1);
    void on_inputB_textEdited(const QString &arg1);

    void on_inputA_editingFinished();

    void on_inputA_returnPressed();

    void on_pushButton_clicked();

    void on_listA_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    QGraphicsScene scene;

};
#endif // MAINWINDOW_H
