#ifndef REALTIMEWINDOW_H
#define REALTIMEWINDOW_H

#include <QMainWindow>

namespace Ui {
class RealtimeWindow;
}

class RealtimeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RealtimeWindow(QWidget *parent = nullptr);
    ~RealtimeWindow();

private slots:
    void on_toggleButton_clicked();

private:
    Ui::RealtimeWindow *ui;
    bool isWorkingDay;
};

#endif // REALTIMEWINDOW_H
