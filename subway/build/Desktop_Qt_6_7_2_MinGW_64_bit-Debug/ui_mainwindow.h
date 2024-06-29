/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
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
    QGraphicsView *mainGraphicsView;
    QLineEdit *inputB;
    QListView *listB;
    QGraphicsView *planGraphicsView;
    QPushButton *swapButton;
    QPushButton *hincButton;
    QPushButton *mincButton;
    QLineEdit *hEdit;
    QPushButton *hdecButton;
    QLineEdit *mEdit;
    QPushButton *mdecButton;
    QPushButton *switchButton;
    QMenuBar *menubar;
    QMenu *menu_realTime;
    QMenu *menu_mainWindow;
    QMenu *menu_lastTrain;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1366, 810);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1366, 768));
        MainWindow->setAutoFillBackground(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        inputA = new QLineEdit(centralwidget);
        inputA->setObjectName("inputA");
        inputA->setGeometry(QRect(10, 0, 191, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setPointSize(12);
        inputA->setFont(font);
        inputA->setFrame(true);
        inputA->setDragEnabled(false);
        inputA->setClearButtonEnabled(true);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(20, 1000, 71, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font1.setPointSize(13);
        pushButton->setFont(font1);
        listA = new QListView(centralwidget);
        listA->setObjectName("listA");
        listA->setGeometry(QRect(10, 30, 191, 131));
        listA->setFont(font);
        listA->setAutoFillBackground(true);
        formLayoutWidget = new QWidget(centralwidget);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(1260, 0, 101, 761));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        mainGraphicsView = new QGraphicsView(centralwidget);
        mainGraphicsView->setObjectName("mainGraphicsView");
        mainGraphicsView->setGeometry(QRect(220, 0, 1031, 761));
        mainGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        mainGraphicsView->setAlignment(Qt::AlignCenter);
        mainGraphicsView->setDragMode(QGraphicsView::NoDrag);
        inputB = new QLineEdit(centralwidget);
        inputB->setObjectName("inputB");
        inputB->setGeometry(QRect(10, 70, 191, 31));
        inputB->setFont(font);
        inputB->setClearButtonEnabled(true);
        listB = new QListView(centralwidget);
        listB->setObjectName("listB");
        listB->setGeometry(QRect(10, 100, 191, 131));
        listB->setFont(font);
        listB->setAutoFillBackground(true);
        planGraphicsView = new QGraphicsView(centralwidget);
        planGraphicsView->setObjectName("planGraphicsView");
        planGraphicsView->setGeometry(QRect(10, 140, 191, 541));
        planGraphicsView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        swapButton = new QPushButton(centralwidget);
        swapButton->setObjectName("swapButton");
        swapButton->setGeometry(QRect(90, 40, 21, 21));
        swapButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        hincButton = new QPushButton(centralwidget);
        hincButton->setObjectName("hincButton");
        hincButton->setGeometry(QRect(70, 690, 16, 20));
        mincButton = new QPushButton(centralwidget);
        mincButton->setObjectName("mincButton");
        mincButton->setGeometry(QRect(150, 690, 16, 20));
        hEdit = new QLineEdit(centralwidget);
        hEdit->setObjectName("hEdit");
        hEdit->setGeometry(QRect(30, 690, 41, 41));
        QFont font2;
        font2.setPointSize(12);
        hEdit->setFont(font2);
        hEdit->setAlignment(Qt::AlignCenter);
        hdecButton = new QPushButton(centralwidget);
        hdecButton->setObjectName("hdecButton");
        hdecButton->setGeometry(QRect(70, 710, 16, 20));
        mEdit = new QLineEdit(centralwidget);
        mEdit->setObjectName("mEdit");
        mEdit->setGeometry(QRect(110, 690, 41, 41));
        mEdit->setFont(font2);
        mEdit->setLayoutDirection(Qt::LeftToRight);
        mEdit->setAlignment(Qt::AlignCenter);
        mdecButton = new QPushButton(centralwidget);
        mdecButton->setObjectName("mdecButton");
        mdecButton->setGeometry(QRect(150, 710, 16, 20));
        switchButton = new QPushButton(centralwidget);
        switchButton->setObjectName("switchButton");
        switchButton->setGeometry(QRect(30, 730, 141, 31));
        switchButton->setFont(font2);
        MainWindow->setCentralWidget(centralwidget);
        swapButton->raise();
        mainGraphicsView->raise();
        pushButton->raise();
        formLayoutWidget->raise();
        inputA->raise();
        inputB->raise();
        planGraphicsView->raise();
        listA->raise();
        listB->raise();
        hincButton->raise();
        mincButton->raise();
        hEdit->raise();
        hdecButton->raise();
        mEdit->raise();
        mdecButton->raise();
        switchButton->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1366, 27));
        menubar->setFont(font);
        menu_realTime = new QMenu(menubar);
        menu_realTime->setObjectName("menu_realTime");
        menu_mainWindow = new QMenu(menubar);
        menu_mainWindow->setObjectName("menu_mainWindow");
        menu_lastTrain = new QMenu(menubar);
        menu_lastTrain->setObjectName("menu_lastTrain");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(inputA, inputB);
        QWidget::setTabOrder(inputB, pushButton);
        QWidget::setTabOrder(pushButton, listA);
        QWidget::setTabOrder(listA, listB);
        QWidget::setTabOrder(listB, mainGraphicsView);

        menubar->addAction(menu_mainWindow->menuAction());
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
        inputB->setText(QString());
        inputB->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\347\273\210\347\202\271\350\275\246\347\253\231", nullptr));
        swapButton->setText(QString());
        hincButton->setText(QCoreApplication::translate("MainWindow", "\342\226\262", nullptr));
        mincButton->setText(QCoreApplication::translate("MainWindow", "\342\226\262", nullptr));
        hEdit->setText(QCoreApplication::translate("MainWindow", "21", nullptr));
        hdecButton->setText(QCoreApplication::translate("MainWindow", "\342\226\274", nullptr));
        mEdit->setText(QCoreApplication::translate("MainWindow", "00", nullptr));
        mdecButton->setText(QCoreApplication::translate("MainWindow", "\342\226\274", nullptr));
        switchButton->setText(QCoreApplication::translate("MainWindow", "\345\210\207\346\215\242\345\210\260\346\234\253\350\275\246\346\237\245\350\257\242", nullptr));
        menu_realTime->setTitle(QCoreApplication::translate("MainWindow", "\345\256\236\346\227\266\345\234\260\351\223\201", nullptr));
        menu_mainWindow->setTitle(QCoreApplication::translate("MainWindow", "\350\267\257\347\272\277\350\247\204\345\210\222", nullptr));
        menu_lastTrain->setTitle(QCoreApplication::translate("MainWindow", "\346\234\253\350\275\246\345\217\257\350\276\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
