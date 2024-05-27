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
    QLineEdit *inputA;
    QPushButton *pushButton;
    QListView *listA;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QGraphicsView *graphicsView;
    QLineEdit *inputB;
    QListView *listB;
    QMenuBar *menubar;
    QMenu *menumainWindow;
    QMenu *menu_lastTrain;
    QMenu *menu_realTime;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1920, 1080);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setAutoFillBackground(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        inputA = new QLineEdit(centralwidget);
        inputA->setObjectName("inputA");
        inputA->setGeometry(QRect(29, 50, 131, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setPointSize(12);
        inputA->setFont(font);
        inputA->setFrame(true);
        inputA->setDragEnabled(false);
        inputA->setClearButtonEnabled(true);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 10, 71, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font1.setPointSize(13);
        pushButton->setFont(font1);
        listA = new QListView(centralwidget);
        listA->setObjectName("listA");
        listA->setGeometry(QRect(29, 80, 131, 121));
        listA->setAutoFillBackground(true);
        formLayoutWidget = new QWidget(centralwidget);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(160, 0, 91, 221));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(250, 0, 1671, 1041));
        inputB = new QLineEdit(centralwidget);
        inputB->setObjectName("inputB");
        inputB->setGeometry(QRect(29, 120, 131, 31));
        inputB->setFont(font);
        listB = new QListView(centralwidget);
        listB->setObjectName("listB");
        listB->setGeometry(QRect(29, 150, 131, 121));
        MainWindow->setCentralWidget(centralwidget);
        pushButton->raise();
        formLayoutWidget->raise();
        graphicsView->raise();
        listB->raise();
        inputA->raise();
        inputB->raise();
        listA->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1920, 27));
        menubar->setFont(font);
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
        QWidget::setTabOrder(inputA, inputB);
        QWidget::setTabOrder(inputB, pushButton);
        QWidget::setTabOrder(pushButton, listA);
        QWidget::setTabOrder(listA, listB);
        QWidget::setTabOrder(listB, graphicsView);

        menubar->addAction(menumainWindow->menuAction());
        menubar->addAction(menu_lastTrain->menuAction());
        menubar->addAction(menu_realTime->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
#if QT_CONFIG(whatsthis)
        inputA->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
#if QT_CONFIG(accessibility)
        inputA->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
        inputA->setText(QString());
        inputA->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\350\265\267\347\202\271\350\275\246\347\253\231", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
#if QT_CONFIG(whatsthis)
        inputB->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        inputB->setText(QCoreApplication::translate("MainWindow", "\347\273\210\347\202\271\350\275\246\347\253\231", nullptr));
        menumainWindow->setTitle(QCoreApplication::translate("MainWindow", "\350\267\257\347\272\277\350\247\204\345\210\222", nullptr));
        menu_lastTrain->setTitle(QCoreApplication::translate("MainWindow", "\346\234\253\350\275\246\345\217\257\350\276\276", nullptr));
        menu_realTime->setTitle(QCoreApplication::translate("MainWindow", "\345\256\236\346\227\266\345\234\260\351\223\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
