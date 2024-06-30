/********************************************************************************
** Form generated from reading UI file 'realtimewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REALTIMEWINDOW_H
#define UI_REALTIMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RealtimeWindow
{
public:
    QWidget *centralwidget;
    QPushButton *whdayButton;
    QGraphicsView *singleView;
    QPushButton *swapButton;
    QLineEdit *hEdit;
    QLineEdit *whdayEdit;
    QLineEdit *mEdit;
    QWidget *formLayoutWidget;
    QFormLayout *lineLayout;
    QPushButton *hincButton;
    QPushButton *hdecButton;
    QPushButton *mincButton;
    QPushButton *mdecButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *RealtimeWindow)
    {
        if (RealtimeWindow->objectName().isEmpty())
            RealtimeWindow->setObjectName("RealtimeWindow");
        RealtimeWindow->resize(1080, 726);
        centralwidget = new QWidget(RealtimeWindow);
        centralwidget->setObjectName("centralwidget");
        whdayButton = new QPushButton(centralwidget);
        whdayButton->setObjectName("whdayButton");
        whdayButton->setGeometry(QRect(160, 20, 111, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setPointSize(12);
        whdayButton->setFont(font);
        singleView = new QGraphicsView(centralwidget);
        singleView->setObjectName("singleView");
        singleView->setGeometry(QRect(160, 130, 800, 600));
        swapButton = new QPushButton(centralwidget);
        swapButton->setObjectName("swapButton");
        swapButton->setGeometry(QRect(160, 100, 111, 31));
        swapButton->setFont(font);
        hEdit = new QLineEdit(centralwidget);
        hEdit->setObjectName("hEdit");
        hEdit->setGeometry(QRect(280, 50, 41, 41));
        QFont font1;
        font1.setPointSize(12);
        hEdit->setFont(font1);
        hEdit->setAlignment(Qt::AlignCenter);
        whdayEdit = new QLineEdit(centralwidget);
        whdayEdit->setObjectName("whdayEdit");
        whdayEdit->setGeometry(QRect(160, 50, 113, 41));
        QFont font2;
        font2.setPointSize(14);
        whdayEdit->setFont(font2);
        whdayEdit->setAlignment(Qt::AlignCenter);
        whdayEdit->setReadOnly(true);
        mEdit = new QLineEdit(centralwidget);
        mEdit->setObjectName("mEdit");
        mEdit->setGeometry(QRect(360, 50, 41, 41));
        mEdit->setFont(font1);
        mEdit->setLayoutDirection(Qt::LeftToRight);
        mEdit->setAlignment(Qt::AlignCenter);
        formLayoutWidget = new QWidget(centralwidget);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(20, 0, 101, 561));
        lineLayout = new QFormLayout(formLayoutWidget);
        lineLayout->setObjectName("lineLayout");
        lineLayout->setContentsMargins(0, 0, 0, 0);
        hincButton = new QPushButton(centralwidget);
        hincButton->setObjectName("hincButton");
        hincButton->setGeometry(QRect(320, 50, 16, 20));
        hdecButton = new QPushButton(centralwidget);
        hdecButton->setObjectName("hdecButton");
        hdecButton->setGeometry(QRect(320, 70, 16, 20));
        mincButton = new QPushButton(centralwidget);
        mincButton->setObjectName("mincButton");
        mincButton->setGeometry(QRect(400, 50, 16, 20));
        mdecButton = new QPushButton(centralwidget);
        mdecButton->setObjectName("mdecButton");
        mdecButton->setGeometry(QRect(400, 70, 16, 20));
        RealtimeWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(RealtimeWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1080, 21));
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
        whdayButton->setText(QCoreApplication::translate("RealtimeWindow", "\345\210\207\346\215\242\346\227\245\346\234\237\345\261\236\346\200\247", nullptr));
        swapButton->setText(QCoreApplication::translate("RealtimeWindow", "\345\210\207\346\215\242\346\226\271\345\220\221", nullptr));
        hEdit->setText(QCoreApplication::translate("RealtimeWindow", "08", nullptr));
        whdayEdit->setText(QCoreApplication::translate("RealtimeWindow", "\345\267\245\344\275\234\346\227\245", nullptr));
        mEdit->setText(QCoreApplication::translate("RealtimeWindow", "00", nullptr));
        hincButton->setText(QCoreApplication::translate("RealtimeWindow", "\342\226\262", nullptr));
        hdecButton->setText(QCoreApplication::translate("RealtimeWindow", "\342\226\274", nullptr));
        mincButton->setText(QCoreApplication::translate("RealtimeWindow", "\342\226\262", nullptr));
        mdecButton->setText(QCoreApplication::translate("RealtimeWindow", "\342\226\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RealtimeWindow: public Ui_RealtimeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REALTIMEWINDOW_H
