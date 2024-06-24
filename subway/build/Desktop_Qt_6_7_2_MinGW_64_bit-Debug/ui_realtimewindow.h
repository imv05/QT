/********************************************************************************
** Form generated from reading UI file 'realtimewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REALTIMEWINDOW_H
#define UI_REALTIMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RealtimeWindow
{
public:
    QWidget *centralwidget;
    QPushButton *toggleButton;
    QGraphicsView *singleView;
    QTimeEdit *timeEdit;
    QPushButton *updButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *RealtimeWindow)
    {
        if (RealtimeWindow->objectName().isEmpty())
            RealtimeWindow->setObjectName("RealtimeWindow");
        RealtimeWindow->resize(800, 600);
        centralwidget = new QWidget(RealtimeWindow);
        centralwidget->setObjectName("centralwidget");
        toggleButton = new QPushButton(centralwidget);
        toggleButton->setObjectName("toggleButton");
        toggleButton->setGeometry(QRect(160, 20, 111, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setPointSize(12);
        toggleButton->setFont(font);
        singleView = new QGraphicsView(centralwidget);
        singleView->setObjectName("singleView");
        singleView->setGeometry(QRect(160, 120, 591, 351));
        timeEdit = new QTimeEdit(centralwidget);
        timeEdit->setObjectName("timeEdit");
        timeEdit->setGeometry(QRect(280, 20, 131, 31));
        timeEdit->setFont(font);
        updButton = new QPushButton(centralwidget);
        updButton->setObjectName("updButton");
        updButton->setGeometry(QRect(160, 80, 111, 31));
        updButton->setFont(font);
        RealtimeWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(RealtimeWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        RealtimeWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(RealtimeWindow);
        statusbar->setObjectName("statusbar");
        RealtimeWindow->setStatusBar(statusbar);

        retranslateUi(RealtimeWindow);

        QMetaObject::connectSlotsByName(RealtimeWindow);
    } // setupUi

    void retranslateUi(QMainWindow *RealtimeWindow)
    {
        RealtimeWindow->setWindowTitle(QCoreApplication::translate("RealtimeWindow", "MainWindow", nullptr));
        toggleButton->setText(QCoreApplication::translate("RealtimeWindow", "PushButton", nullptr));
        updButton->setText(QCoreApplication::translate("RealtimeWindow", "\345\210\207\346\215\242\346\226\271\345\220\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RealtimeWindow: public Ui_RealtimeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REALTIMEWINDOW_H
