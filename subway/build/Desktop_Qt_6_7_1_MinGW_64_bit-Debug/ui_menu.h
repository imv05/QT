/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_menu
{
public:
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_2;
    QLabel *label_3;

    void setupUi(QWidget *menu)
    {
        if (menu->objectName().isEmpty())
            menu->setObjectName("menu");
        menu->resize(876, 572);
        pushButton = new QPushButton(menu);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(330, 290, 191, 71));
        QFont font;
        font.setPointSize(30);
        pushButton->setFont(font);
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        label = new QLabel(menu);
        label->setObjectName("label");
        label->setGeometry(QRect(330, 60, 201, 131));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\344\272\244\351\200\232\346\240\207\345\277\227\344\270\223\347\224\250\345\255\227\344\275\223")});
        font1.setPointSize(60);
        label->setFont(font1);
        label_2 = new QLabel(menu);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(350, 190, 501, 51));
        QFont font2;
        font2.setPointSize(22);
        label_2->setFont(font2);
        pushButton_2 = new QPushButton(menu);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(330, 400, 191, 71));
        pushButton_2->setFont(font);
        pushButton_2->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_2->setFlat(false);
        label_3 = new QLabel(menu);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 871, 571));
        label_3->raise();
        pushButton->raise();
        label->raise();
        label_2->raise();
        pushButton_2->raise();

        retranslateUi(menu);

        QMetaObject::connectSlotsByName(menu);
    } // setupUi

    void retranslateUi(QWidget *menu)
    {
        menu->setWindowTitle(QCoreApplication::translate("menu", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("menu", "start", nullptr));
        label->setText(QCoreApplication::translate("menu", "\346\200\273\350\247\210", nullptr));
        label_2->setText(QCoreApplication::translate("menu", "--by \345\210\230\345\215\223\346\264\213\357\274\214\350\265\265\347\221\236\346\215\267\357\274\214\350\260\242\345\256\207\347\277\224", nullptr));
        pushButton_2->setText(QCoreApplication::translate("menu", "exit", nullptr));
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class menu: public Ui_menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
