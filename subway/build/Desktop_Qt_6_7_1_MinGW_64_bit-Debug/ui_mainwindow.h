/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QListView *listView;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QMenu *menumainWindow;
    QMenu *menu_lastTrain;
    QMenu *menu_realTime;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(737, 452);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(90, 0, 71, 41));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(9, 50, 141, 23));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 10, 71, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("A\345\236\213\344\272\244\351\200\232\346\240\207\345\277\227\344\270\223\347\224\250\345\255\227\344\275\223")});
        font1.setPointSize(14);
        pushButton->setFont(font1);
        listView = new QListView(centralwidget);
        listView->setObjectName("listView");
        listView->setGeometry(QRect(9, 70, 141, 121));
        formLayoutWidget = new QWidget(centralwidget);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(160, 0, 91, 221));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(270, 30, 461, 371));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 737, 21));
        menumainWindow = new QMenu(menubar);
        menumainWindow->setObjectName("menumainWindow");
        menu_lastTrain = new QMenu(menubar);
        menu_lastTrain->setObjectName("menu_lastTrain");
        menu_realTime = new QMenu(menubar);
        menu_realTime->setObjectName("menu_realTime");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menumainWindow->menuAction());
        menubar->addAction(menu_lastTrain->menuAction());
        menubar->addAction(menu_realTime->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "\347\202\271\345\207\273\346\255\244\345\244\204\346\220\234\347\264\242\350\275\246\347\253\231", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
        menumainWindow->setTitle(QCoreApplication::translate("MainWindow", "mainWindow", nullptr));
        menu_lastTrain->setTitle(QCoreApplication::translate("MainWindow", "\346\234\253\350\275\246\345\217\257\350\276\276", nullptr));
        menu_realTime->setTitle(QCoreApplication::translate("MainWindow", "\345\256\236\346\227\266\345\234\260\351\223\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
