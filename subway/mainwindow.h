#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QString>
#include<QGraphicsScene>
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
    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_editingFinished();

    void on_lineEdit_returnPressed();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
};
#endif // MAINWINDOW_H
