#ifndef BUTTONMANAGE_H
#define BUTTONMANAGE_H

#include <QPushButton>

class buttonManage{
public:
    QPushButton* button;
    int lineOrder;
    buttonManage(QPushButton* text,int i);
};

#endif // BUTTONMANAGE_H
