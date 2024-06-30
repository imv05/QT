/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
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
        pushButton->setGeometry(QRect(200, 230, 191, 71));
        QFont font;
        font.setPointSize(30);
        pushButton->setFont(font);
        pushButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        label_2 = new QLabel(menu);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(190, 160, 501, 51));
        QFont font1;
        font1.setPointSize(22);
        label_2->setFont(font1);
        pushButton_2 = new QPushButton(menu);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(510, 230, 191, 71));
        pushButton_2->setFont(font);
        pushButton_2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_2->setFlat(false);
        label_3 = new QLabel(menu);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 871, 571));
        label_3->raise();
        pushButton->raise();
        label_2->raise();
        pushButton_2->raise();

        retranslateUi(menu);

        QMetaObject::connectSlotsByName(menu);
    } // setupUi

    void retranslateUi(QWidget *menu)
    {
        menu->setWindowTitle(QCoreApplication::translate("menu", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("menu", "\350\277\233\345\205\245", nullptr));
        label_2->setText(QCoreApplication::translate("menu", "--by \345\210\230\345\215\223\346\264\213\357\274\214\350\265\265\347\221\236\346\215\267\357\274\214\350\260\242\345\256\207\347\277\224", nullptr));
        pushButton_2->setText(QCoreApplication::translate("menu", "\351\200\200\345\207\272", nullptr));
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class menu: public Ui_menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
