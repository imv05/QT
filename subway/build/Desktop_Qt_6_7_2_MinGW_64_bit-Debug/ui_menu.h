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
    QPushButton *enterButton;
    QLabel *authors;
    QPushButton *exitButton;

    void setupUi(QWidget *menu)
    {
        if (menu->objectName().isEmpty())
            menu->setObjectName("menu");
        menu->resize(876, 572);
        enterButton = new QPushButton(menu);
        enterButton->setObjectName("enterButton");
        enterButton->setGeometry(QRect(200, 230, 191, 71));
        QFont font;
        font.setPointSize(30);
        enterButton->setFont(font);
        enterButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        authors = new QLabel(menu);
        authors->setObjectName("authors");
        authors->setGeometry(QRect(190, 160, 501, 51));
        QFont font1;
        font1.setPointSize(22);
        authors->setFont(font1);
        exitButton = new QPushButton(menu);
        exitButton->setObjectName("exitButton");
        exitButton->setGeometry(QRect(510, 230, 191, 71));
        exitButton->setFont(font);
        exitButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        exitButton->setFlat(false);

        retranslateUi(menu);

        QMetaObject::connectSlotsByName(menu);
    } // setupUi

    void retranslateUi(QWidget *menu)
    {
        menu->setWindowTitle(QCoreApplication::translate("menu", "Form", nullptr));
        enterButton->setText(QCoreApplication::translate("menu", "\350\277\233\345\205\245", nullptr));
        authors->setText(QCoreApplication::translate("menu", "--by \345\210\230\345\215\223\346\264\213\357\274\214\350\265\265\347\221\236\346\215\267\357\274\214\350\260\242\345\256\207\347\277\224", nullptr));
        exitButton->setText(QCoreApplication::translate("menu", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class menu: public Ui_menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
