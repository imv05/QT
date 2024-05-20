#include "paint.h"

#include <QApplication>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QFont>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QSvgRenderer>
#include <QString>
#include <QLabel>
#include <QtSvg>
#include <QWheelEvent>
#include <QMessageBox>

void paint(QGraphicsScene& pr){
    int i,j;
    QGraphicsEllipseItem* stationPointerList[27][40];
    QGraphicsTextItem* stationPointerText[27][40];

    
    {//2号线
        QColor twocolor(0, 95, 152);
        QPen pen(twocolor);
        pen.setWidth(3);
        pen.setStyle(Qt::SolidLine);
        QBrush lbrush(twocolor);
        pr.addRect(20,40,20,10,pen,lbrush);
        QGraphicsTextItem *textItem = pr.addText("2号线");
        textItem->setPos(45,32);
        QFont font("微软雅黑", 10);
        textItem->setFont(font);
        textItem->setDefaultTextColor(twocolor);
        QBrush fbrush(Qt::NoBrush);
        pr.addRect(440,270,145,105,pen,fbrush);
        pen.setWidth(1);
        QBrush brush(Qt::white);
        pr.addEllipse(507,267, 6, 6,pen,brush);//8-鼓楼大街
        pr.addEllipse(470,267, 6, 6,pen,brush);//19-积水潭
        pr.addEllipse(537,267, 6, 6,pen,brush);//安定门
        pr.addEllipse(557,267, 6, 6,pen,brush);//5-雍和宫
        pr.addEllipse(582,287, 6, 6,pen,brush);//13,首都机场-东直门
        pr.addEllipse(582,302, 6, 6,pen,brush);//东四十条
        pr.addEllipse(582,317, 6, 6,pen,brush);//6-朝阳门
        pr.addEllipse(582,347, 6, 6,pen,brush);//1-建国门
        pr.addEllipse(582,367, 6, 6,pen,brush);//北京站
        pr.addEllipse(557,372, 6, 6,pen,brush);//5-崇文门
        pr.addEllipse(527,372, 6, 6,pen,brush);//8-前门
        pr.addEllipse(497,372, 6, 6,pen,brush);//和平门
        pr.addEllipse(462,372, 6, 6,pen,brush);//4-宣武门
        pr.addEllipse(442,372, 6, 6,pen,brush);//19-长椿街
        pr.addEllipse(437,347, 6, 6,pen,brush);//1-复兴门
        pr.addEllipse(437,327, 6, 6,pen,brush);//阜成门
        pr.addEllipse(437,302, 6, 6,pen,brush);//6-车公庄
        pr.addEllipse(437,279, 6, 6,pen,brush);//4,13-西直门
    }
    {//4号线
        QColor fourcolor(0, 142, 156);
        QPen pen(fourcolor);
        pen.setWidth(3);
        pen.setStyle(Qt::SolidLine);
        QBrush lbrush(fourcolor);
        pr.addRect(20,60,20,10,pen,lbrush);
        QGraphicsTextItem *textItem = pr.addText("4号线大兴线");
        textItem->setPos(45,52);
        QFont font("微软雅黑", 10);
        textItem->setFont(font);
        textItem->setDefaultTextColor(fourcolor);
        pr.addLine(465,282,465,627,pen);
        pr.addLine(360,282,465,282,pen);
        pr.addLine(360,182,360,282,pen);
        pr.addLine(300,182,360,182,pen);
        pen.setWidth(1);
        QBrush brush(Qt::white);
        pr.addEllipse(297,179, 6, 6,pen,brush);//安河桥北
        pr.addEllipse(317,179, 6, 6,pen,brush);//北宫门
        pr.addEllipse(337,179, 6, 6,pen,brush);//16-西苑
        pr.addEllipse(357,179, 6, 6,pen,brush);//圆明园
        pr.addEllipse(357,194, 6, 6,pen,brush);//北京大学东门
        pr.addEllipse(357,207, 6, 6,pen,brush);//中关村
        pr.addEllipse(357,226, 6, 6,pen,brush);//10-海淀黄庄
        pr.addEllipse(357,243, 6, 6,pen,brush);//人民大学
        pr.addEllipse(357,259, 6, 6,pen,brush);//魏公村
        pr.addEllipse(366,279, 6, 6,pen,brush);//9,16-国家图书馆
        pr.addEllipse(407,279, 6, 6,pen,brush);//动物园
        pr.addEllipse(437,279, 6, 6,pen,brush);//2,13-西直门
        pr.addEllipse(462,279, 6, 6,pen,brush);//新街口
        pr.addEllipse(462,302, 6, 6,pen,brush);//6,19-平安里
        pr.addEllipse(462,317, 6, 6,pen,brush);//西四
        pr.addEllipse(462,330, 6, 6,pen,brush);//灵境胡同
        pr.addEllipse(462, 347, 6, 6,pen,brush);//1-西单
        pr.addEllipse(462,372, 6, 6,pen,brush);//2-宣武门
        pr.addEllipse(462,387, 6, 6,pen,brush);//7-菜市口
        pr.addEllipse(462,402, 6, 6,pen,brush);//陶然亭
        pr.addEllipse(462,417, 6, 6,pen,brush);//14-北京南站
        pr.addEllipse(462,432, 6, 6,pen,brush);//马家堡
        pr.addEllipse(462,447, 6, 6,pen,brush);//10-角门西
        pr.addEllipse(462,462, 6, 6,pen,brush);//公益西桥
        pr.addEllipse(462,477, 6, 6,pen,brush);//19-新宫
        pr.addEllipse(462,492, 6, 6,pen,brush);//西红门
        pr.addEllipse(462,507, 6, 6,pen,brush);//高米店北
        pr.addEllipse(462,522, 6, 6,pen,brush);//高米店南
        pr.addEllipse(462,537, 6, 6,pen,brush);//枣园
        pr.addEllipse(462,552, 6, 6,pen,brush);//清源路
        pr.addEllipse(462,567, 6, 6,pen,brush);//黄村西大街
        pr.addEllipse(462,582, 6, 6,pen,brush);//黄村火车站
        pr.addEllipse(462,597, 6, 6,pen,brush);//义和庄
        pr.addEllipse(462,612, 6, 6,pen,brush);//生物医药基地
        pr.addEllipse(462,627, 6, 6,pen,brush);//天宫院
    }
    {//5号线
        QColor fivecolor(166, 33, 127);
        QPen pen(fivecolor);
        pen.setWidth(3);
        pen.setStyle(Qt::SolidLine);
        QBrush lbrush(fivecolor);
        pr.addRect(20,80,20,10,pen,lbrush);
        QGraphicsTextItem *textItem = pr.addText("5号线");
        textItem->setPos(45,72);
        QFont font("微软雅黑", 10);
        textItem->setFont(font);
        textItem->setDefaultTextColor(fivecolor);
        pr.addLine(560,100,560,447,pen);
        pen.setWidth(1);
        QBrush brush(Qt::white);
        pr.addEllipse(557,97,6,6,pen,brush);//天通苑北
        pr.addEllipse(557,112,6,6,pen,brush);//天通苑
        pr.addEllipse(557,127,6,6,pen,brush);//天通苑南
        pr.addEllipse(557,142,6,6,pen,brush);//立水桥
        pr.addEllipse(557,157,6,6,pen,brush);//立水桥南
        pr.addEllipse(557,172,6,6,pen,brush);//北苑路北
        pr.addEllipse(557,192,6,6,pen,brush);//大屯路东
        pr.addEllipse(557,209,6,6,pen,brush);//惠新西街北口
        pr.addEllipse(557,226,6,6,pen,brush);//惠新西街南口
        pr.addEllipse(557,239,6,6,pen,brush);//和平西桥
        pr.addEllipse(557,253,6,6,pen,brush);//和平里北街
        pr.addEllipse(557,267, 6, 6,pen,brush);//2-雍和宫
        pr.addEllipse(557,287, 6, 6,pen,brush);//北新桥
        pr.addEllipse(557,302, 6, 6,pen,brush);//张自忠路
        pr.addEllipse(557,317, 6, 6,pen,brush);//东四
        pr.addEllipse(557,332, 6, 6,pen,brush);//灯市口
        pr.addEllipse(557, 347, 6, 6,pen,brush);//1-东单
        pr.addEllipse(557,372, 6, 6,pen,brush);//2-崇文门
        pr.addEllipse(557,387, 6, 6,pen,brush);//7-磁器口
        pr.addEllipse(557,402, 6, 6,pen,brush);//天坛东门
        pr.addEllipse(557,417, 6, 6,pen,brush);//14-蒲黄榆
        pr.addEllipse(557,432, 6, 6,pen,brush);//刘家窑
        pr.addEllipse(557,447, 6, 6,pen,brush);//10,亦庄-宋家庄
    }
    {//6号线
        QColor sixcolor(210, 151, 0);
        QPen pen(sixcolor);
        pen.setWidth(3);
        pen.setStyle(Qt::SolidLine);
        QBrush lbrush(sixcolor);
        pr.addRect(20,100,20,10,pen,lbrush);
        QGraphicsTextItem *textItem = pr.addText("6号线");
        textItem->setPos(45,92);
        QFont font("微软雅黑", 10);
        textItem->setFont(font);
        textItem->setDefaultTextColor(sixcolor);
        pr.addLine(186,326,186,305,pen);
        pr.addLine(186,305,510,305,pen);
        pr.addLine(510,305,532,320,pen);
        pr.addLine(532,320,866,320,pen);
        pr.addLine(866,320,888,358,pen);
        pr.addLine(888,358,970,358,pen);
        pen.setWidth(1);
        QBrush brush(Qt::white);
        pr.addEllipse(183, 323, 6, 6,pen,brush);//1,S1-苹果园
        pr.addEllipse(183, 312, 6, 6,pen,brush);//杨庄
        pr.addEllipse(183, 302, 6, 6,pen,brush);//西黄村
        pr.addEllipse(213, 302, 6, 6,pen,brush);//廖公庄
        pr.addEllipse(243, 302, 6, 6,pen,brush);//田村
        pr.addEllipse(273, 302, 6, 6,pen,brush);//海淀五路居
        pr.addEllipse(303, 302, 6, 6,pen,brush);//10-慈寿寺
        pr.addEllipse(334, 302, 6, 6,pen,brush);//花园桥
        pr.addEllipse(366, 302, 6, 6,pen,brush);//9-白石桥南
        pr.addEllipse(380,302, 6, 6,pen,brush);//二里沟
        pr.addEllipse(403,302, 6, 6,pen,brush);//车公庄西
        pr.addEllipse(437,302, 6, 6,pen,brush);//2-车公庄
        pr.addEllipse(462,302, 6, 6,pen,brush);//4,19-平安里
        pr.addEllipse(487,302, 6, 6,pen,brush);//北海北
        pr.addEllipse(507,302, 6, 6,pen,brush);//8-南锣鼓巷
        pr.addEllipse(557,317, 6, 6,pen,brush);//5-东四
        pr.addEllipse(582,317, 6, 6,pen,brush);//2-朝阳门
        pr.addEllipse(605,317, 6, 6,pen,brush);//东大桥
        pr.addEllipse(630, 317, 6, 6,pen,brush);//10-呼家楼
        pr.addEllipse(654, 317, 6, 6,pen,brush);//金台路
        pr.addEllipse(680, 317, 6, 6,pen,brush);//十里堡
        pr.addEllipse(706, 317, 6, 6,pen,brush);//青年路
        pr.addEllipse(732, 317, 6, 6,pen,brush);//褡裢坡
        pr.addEllipse(758, 317, 6, 6,pen,brush);//黄渠
        pr.addEllipse(784, 317, 6, 6,pen,brush);//常营
        pr.addEllipse(810, 317, 6, 6,pen,brush);//草房
        pr.addEllipse(836, 317, 6, 6,pen,brush);//物资学院路
        pr.addEllipse(863, 317, 6, 6,pen,brush);//通州北关
        pr.addEllipse(885, 355, 6, 6,pen,brush);//北运河西
        pr.addEllipse(905, 355, 6, 6,pen,brush);//北运河东
        pr.addEllipse(925, 355, 6, 6,pen,brush);//郝家府
        pr.addEllipse(946, 355, 6, 6,pen,brush);//东夏园
        pr.addEllipse(967, 355, 6, 6,pen,brush);//潞城
    }
    {//7号线
        QColor sevencolor(245, 197, 135);
        QPen pen(sevencolor);
        pen.setWidth(3);
        pen.setStyle(Qt::SolidLine);
        QBrush lbrush(sevencolor);
        pr.addRect(20,120,20,10,pen,lbrush);
        QGraphicsTextItem *textItem = pr.addText("7号线");
        textItem->setPos(45,112);
        QFont font("微软雅黑", 10);
        textItem->setFont(font);
        textItem->setDefaultTextColor(sevencolor);
        pr.addLine(369,375, 380, 390,pen);
        pr.addLine(380,390, 710, 390,pen);
        pr.addLine(710,390, 710, 469,pen);
        pr.addLine(710,469, 899, 469,pen);
        pr.addLine(899,469, 899, 520,pen);
        pen.setWidth(1);
        QBrush brush(Qt::white);
        pr.addEllipse(366, 372, 6, 6,pen,brush);//9-北京西站
        pr.addEllipse(377, 387, 6, 6,pen,brush);//湾子
        pr.addEllipse(390, 387, 6, 6,pen,brush);//达官营
        pr.addEllipse(427, 387, 6, 6,pen,brush);//广安门内
        pr.addEllipse(462,387, 6, 6,pen,brush);//4-菜市口
        pr.addEllipse(482,387, 6, 6,pen,brush);//虎坊桥
        pr.addEllipse(507,387, 6, 6,pen,brush);//8-珠市口
        pr.addEllipse(537,387, 6, 6,pen,brush);//桥湾
        pr.addEllipse(557,387, 6, 6,pen,brush);//5-磁器口
        pr.addEllipse(581,387, 6, 6,pen,brush);//广渠门内
        pr.addEllipse(605,387, 6, 6,pen,brush);//广渠门外
        pr.addEllipse(630,387, 6, 6,pen,brush);//10-双井
        pr.addEllipse(654,387, 6, 6,pen,brush);//14-九龙山
        pr.addEllipse(678,387, 6, 6,pen,brush);//大郊亭
        pr.addEllipse(707,387, 6, 6,pen,brush);//百子湾
        pr.addEllipse(707,420, 6, 6,pen,brush);//化工
        pr.addEllipse(707,452, 6, 6,pen,brush);//南楼梓庄
        pr.addEllipse(717,466, 6, 6,pen,brush);//欢乐谷景区
        pr.addEllipse(735,466, 6, 6,pen,brush);//垡头
        pr.addEllipse(752,466, 6, 6,pen,brush);//双合
        pr.addEllipse(770,466, 6, 6,pen,brush);//焦化厂
        pr.addEllipse(787,466, 6, 6,pen,brush);//黄厂
        pr.addEllipse(805,466, 6, 6,pen,brush);//郎辛庄
        pr.addEllipse(822,466, 6, 6,pen,brush);//黑庄户
        pr.addEllipse(840,466, 6, 6,pen,brush);//万盛西
        pr.addEllipse(857,466, 6, 6,pen,brush);//群芳
        pr.addEllipse(878,466, 6, 6,pen,brush);//高楼金
        pr.addEllipse(898, 466, 6, 6,pen,brush);//1-花庄
        pr.addEllipse(898, 517, 6, 6,pen,brush);//1-环球度假区
    }
    {//8号线
        QColor eightcolor(22, 154, 108);
        QPen pen(eightcolor);
        pen.setWidth(3);
        pen.setStyle(Qt::SolidLine);
        QBrush lbrush(eightcolor);
        pr.addRect(20,140,20,10,pen,lbrush);
        QGraphicsTextItem *textItem = pr.addText("8号线");
        textItem->setPos(45,132);
        QFont font("微软雅黑", 10);
        textItem->setFont(font);
        textItem->setDefaultTextColor(eightcolor);
        pr.addLine(430,113,510,113,pen);
        pr.addLine(510,113,510,305,pen);
        pr.addLine(510,305,520,325,pen);
        pr.addLine(520,325,537,335,pen);
        pr.addLine(537,335,537,350,pen);
        pr.addLine(537,350,530,375,pen);
        pr.addLine(530,375,510,390,pen);
        pr.addLine(510,390,510,525,pen);
        pr.addLine(510,525,570,585,pen);
        pr.addLine(570,585,570,605,pen);
        pen.setWidth(1);
        QBrush brush(Qt::white);
        pr.addEllipse(427,110, 6, 6,pen,brush);//昌平-朱辛庄
        pr.addEllipse(457,110, 6, 6,pen,brush);//育知路
        pr.addEllipse(487,110, 6, 6,pen,brush);//平西府
        pr.addEllipse(507,120, 6, 6,pen,brush);//回龙观东大街
        pr.addEllipse(507,140, 6, 6,pen,brush);//13-霍营
        pr.addEllipse(507,151, 6, 6,pen,brush);//育新
        pr.addEllipse(507,162, 6, 6,pen,brush);//西小口
        pr.addEllipse(507,172, 6, 6,pen,brush);//永泰庄
        pr.addEllipse(507,182, 6, 6,pen,brush);//林萃桥
        pr.addEllipse(507,192, 6, 6,pen,brush);//森林公园南门
        pr.addEllipse(507,203, 6, 6,pen,brush);//15-奥林匹克公园
        pr.addEllipse(507,214, 6, 6,pen,brush);//奥体中心
        pr.addEllipse(507,226, 6, 6,pen,brush);//10-北土城
        pr.addEllipse(507,240, 6, 6,pen,brush);//安华桥
        pr.addEllipse(507,253, 6, 6,pen,brush);//安德里北街
        pr.addEllipse(507,267, 6, 6,pen,brush);//2-鼓楼大街
        pr.addEllipse(507,286, 6, 6,pen,brush);//什刹海
        pr.addEllipse(507,302, 6, 6,pen,brush);//6-南锣鼓巷
        pr.addEllipse(517,322, 6, 6,pen,brush);//中国美术馆
        pr.addEllipse(534,332, 6, 6,pen,brush);//金鱼胡同
        pr.addEllipse(534, 347, 6, 6,pen,brush);//1-王府井
        pr.addEllipse(527,372, 6, 6,pen,brush);//2-前门
        pr.addEllipse(507,387, 6, 6,pen,brush);//7-珠市口
        pr.addEllipse(507,402, 6, 6,pen,brush);//天桥
        pr.addEllipse(507,417, 6, 6,pen,brush);//14-永定门外
        pr.addEllipse(507,427, 6, 6,pen,brush);//木樨园
        pr.addEllipse(507,437, 6, 6,pen,brush);//海户屯
        pr.addEllipse(507,462, 6, 6,pen,brush);//大红门南
        pr.addEllipse(507,477, 6, 6,pen,brush);//和义
        pr.addEllipse(507,500, 6, 6,pen,brush);//东高地
        pr.addEllipse(507,522, 6, 6,pen,brush);//火箭万源
        pr.addEllipse(537,552, 6, 6,pen,brush);//五福堂
        pr.addEllipse(567,582, 6, 6,pen,brush);//德茂
        pr.addEllipse(567,602, 6, 6,pen,brush);//瀛海
    }
    {//9号线
        QColor ninecolor(144, 194, 50);
        QPen pen(ninecolor);
        pen.setWidth(3);
        pen.setStyle(Qt::SolidLine);
        QBrush lbrush(ninecolor);
        pr.addRect(20,160,20,10,pen,lbrush);
        QGraphicsTextItem *textItem = pr.addText("9号线");
        textItem->setPos(45,152);
        QFont font("微软雅黑", 10);
        textItem->setFont(font);
        textItem->setDefaultTextColor(ninecolor);
        pr.addLine(369,282,369,375,pen);
        pr.addLine(369,375,329,415,pen);
        pr.addLine(329,415,329,465,pen);
        pen.setWidth(1);
        QBrush brush(Qt::white);
        pr.addEllipse(366,279, 6, 6,pen,brush);//4,16-国家图书馆
        pr.addEllipse(366, 302, 6, 6,pen,brush);//6-白石桥南
        pr.addEllipse(366, 323, 6, 6,pen,brush);//白堆子
        pr.addEllipse(366, 347, 6, 6,pen,brush);//1-军事博物馆
        pr.addEllipse(366, 372, 6, 6,pen,brush);//7-北京西站
        pr.addEllipse(353, 385, 6, 6,pen,brush);//六里桥东
        pr.addEllipse(340, 398, 6, 6,pen,brush);//10-六里桥
        pr.addEllipse(326, 412, 6, 6,pen,brush);//七里庄
        pr.addEllipse(326, 422, 6, 6,pen,brush);//丰台东大街
        pr.addEllipse(326, 432, 6, 6,pen,brush);//16-丰台南路
        pr.addEllipse(326, 442, 6, 6,pen,brush);//科怡路
        pr.addEllipse(326, 452, 6, 6,pen,brush);//丰台科技园
        pr.addEllipse(326, 462, 6, 6,pen,brush);//郭公庄
    }
    {//大兴机场线
        QColor daxingcolor(9, 77, 155);
        QPen pen(daxingcolor);
        pen.setWidth(3);
        pen.setStyle(Qt::SolidLine);
        QBrush lbrush(daxingcolor);
        pr.addRect(20,180,20,10,pen,lbrush);
        QGraphicsTextItem *textItem = pr.addText("大兴机场线");
        textItem->setPos(45,172);
        QFont font("微软雅黑", 10);
        textItem->setFont(font);
        textItem->setDefaultTextColor(daxingcolor);
        pr.addLine(442,450,442,487,pen);
        pr.addLine(442,487,497,487,pen);
        pr.addLine(497,487,497,680,pen);
        pen.setWidth(1);
        QBrush brush(Qt::white);
        pr.addEllipse(439,447, 6, 6,pen,brush);//草桥
        pr.addEllipse(494,582, 6, 6,pen,brush);//大兴新城
        pr.addEllipse(494,677, 6, 6,pen,brush);//大兴机场
    }
}

