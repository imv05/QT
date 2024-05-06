#include "mainwindow.h"

#include <QApplication>
#include <QPainter>
#include <QSvgRenderer>
#include <QString>
#include <QLabel>
#include <QtSvg>


void MainWindow::paintEvent(QPaintEvent *e){
    //北京地铁的基本构架
    //总像素定为
    QPainter pr;
    pr.begin(this);
    pr.setPen(Qt::NoPen);
    pr.setBrush(Qt::white);
    pr.drawRect(rect());
    {//1号线
        pr.setPen(QPen(Qt::red,3,Qt::SolidLine));
        pr.drawLine(170,300,200,350);
        pr.drawLine(200,350,825,350);
        pr.drawLine(825,350,902,469);
        pr.drawLine(902,469,902,520);
        QPen pen(Qt::red);
        pen.setWidth(1);
        pr.setPen(pen);
        pr.drawEllipse(167, 297, 6, 6);//福寿岭
        pr.drawEllipse(183, 323, 6, 6);//6,S1-苹果园
        pr.drawEllipse(197, 347, 6, 6);//古城
        pr.drawEllipse(222, 347, 6, 6);//八角游乐园
        pr.drawEllipse(246, 347, 6, 6);//八宝山
        pr.drawEllipse(270, 347, 6, 6);//玉泉路
        pr.drawEllipse(294, 347, 6, 6);//五棵松
        pr.drawEllipse(318, 347, 6, 6);//万寿路
        pr.drawEllipse(342, 347, 6, 6);//10-公主坟
        pr.drawEllipse(366, 347, 6, 6);//9-军事博物馆
        pr.drawEllipse(390, 347, 6, 6);//16-木樨地
        pr.drawEllipse(414, 347, 6, 6);//南礼士路
        pr.drawEllipse(437, 347, 6, 6);//2-复兴门
        pr.drawEllipse(462, 347, 6, 6);//4-西单
        pr.drawEllipse(486, 347, 6, 6);//天安门西
        pr.drawEllipse(510, 347, 6, 6);//天安门东
        pr.drawEllipse(534, 347, 6, 6);//8-王府井
        pr.drawEllipse(557, 347, 6, 6);//5-东单
        pr.drawEllipse(582, 347, 6, 6);//2-建国门
        pr.drawEllipse(606, 347, 6, 6);//永安里
        pr.drawEllipse(630, 347, 6, 6);//10-国贸
        pr.drawEllipse(654, 347, 6, 6);//14-大望路
        pr.drawEllipse(678, 347, 6, 6);//四惠
        pr.drawEllipse(702, 347, 6, 6);//四惠东
        pr.drawEllipse(726, 347, 6, 6);//高碑店
        pr.drawEllipse(750, 347, 6, 6);//传媒大学
        pr.drawEllipse(774, 347, 6, 6);//双桥
        pr.drawEllipse(798, 347, 6, 6);//管庄
        pr.drawEllipse(822, 347, 6, 6);//八里桥
        pr.drawEllipse(833, 364, 6, 6);//通州北苑
        pr.drawEllipse(844, 381, 6, 6);//果园
        pr.drawEllipse(855, 398, 6, 6);//九棵树
        pr.drawEllipse(866, 415, 6, 6);//梨园
        pr.drawEllipse(877, 432, 6, 6);//临河里
        pr.drawEllipse(888, 449, 6, 6);//土桥
        pr.drawEllipse(898, 466, 6, 6);//7-花庄
        pr.drawEllipse(898, 517, 6, 6);//7-环球度假区
    }
    {//2号线
        QColor twocolor(0, 95, 152);
        pr.setPen(QPen(twocolor,3,Qt::SolidLine));
        pr.setBrush(Qt::NoBrush);
        pr.drawRoundedRect(440,270,145,105,5,5);
        QPen pen(twocolor);
        pen.setWidth(1);
        pr.setBrush(Qt::white);
        pr.setPen(pen);
        pr.drawEllipse(507,267, 6, 6);//8-鼓楼大街
        pr.drawEllipse(470,267, 6, 6);//19-积水潭
        pr.drawEllipse(537,267, 6, 6);//安定门
        pr.drawEllipse(557,267, 6, 6);//5-雍和宫
        pr.drawEllipse(582,287, 6, 6);//13,首都机场-东直门
        pr.drawEllipse(582,302, 6, 6);//东四十条
        pr.drawEllipse(582,317, 6, 6);//6-朝阳门
        pr.drawEllipse(582, 347, 6, 6);//1-建国门
        pr.drawEllipse(582,367, 6, 6);//北京站
        pr.drawEllipse(557,372, 6, 6);//5-崇文门
        pr.drawEllipse(527,372, 6, 6);//8-前门
        pr.drawEllipse(497,372, 6, 6);//和平门
        pr.drawEllipse(462,372, 6, 6);//4-宣武门
        pr.drawEllipse(442,372, 6, 6);//19-长椿街
        pr.drawEllipse(437,347, 6, 6);//1-复兴门
        pr.drawEllipse(437,327, 6, 6);//阜成门
        pr.drawEllipse(437,302, 6, 6);//6-车公庄
        pr.drawEllipse(437,279, 6, 6);//4,13-西直门
    }
    {//4号线
        QColor fourcolor(0, 142, 156);
        pr.setPen(QPen(fourcolor,3,Qt::SolidLine));
        pr.drawLine(465,282,465,627);
        pr.drawLine(360,282,465,282);
        pr.drawLine(360,182,360,282);
        pr.drawLine(300,182,360,182);
        QPen pen(fourcolor);
        pen.setWidth(1);
        pr.setBrush(Qt::white);
        pr.setPen(pen);
        pr.drawEllipse(297,179, 6, 6);//安河桥北
        pr.drawEllipse(317,179, 6, 6);//北宫门
        pr.drawEllipse(337,179, 6, 6);//16-西苑
        pr.drawEllipse(357,179, 6, 6);//圆明园
        pr.drawEllipse(357,194, 6, 6);//北京大学东门
        pr.drawEllipse(357,207, 6, 6);//中关村
        pr.drawEllipse(357,226, 6, 6);//10-海淀黄庄
        pr.drawEllipse(357,243, 6, 6);//人民大学
        pr.drawEllipse(357,259, 6, 6);//魏公村
        pr.drawEllipse(366,279, 6, 6);//9,16-国家图书馆
        pr.drawEllipse(407,279, 6, 6);//动物园
        pr.drawEllipse(437,279, 6, 6);//2,13-西直门
        pr.drawEllipse(462,279, 6, 6);//新街口
        pr.drawEllipse(462,302, 6, 6);//6,19-平安里
        pr.drawEllipse(462,317, 6, 6);//西四
        pr.drawEllipse(462,330, 6, 6);//灵境胡同
        pr.drawEllipse(462, 347, 6, 6);//1-西单
        pr.drawEllipse(462,372, 6, 6);//2-宣武门
        pr.drawEllipse(462,387, 6, 6);//7-菜市口
        pr.drawEllipse(462,402, 6, 6);//陶然亭
        pr.drawEllipse(462,417, 6, 6);//14-北京南站
        pr.drawEllipse(462,432, 6, 6);//马家堡
        pr.drawEllipse(462,447, 6, 6);//10-角门西
        pr.drawEllipse(462,462, 6, 6);//公益西桥
        pr.drawEllipse(462,477, 6, 6);//19-新宫
        pr.drawEllipse(462,492, 6, 6);//西红门
        pr.drawEllipse(462,507, 6, 6);//高米店北
        pr.drawEllipse(462,522, 6, 6);//高米店南
        pr.drawEllipse(462,537, 6, 6);//枣园
        pr.drawEllipse(462,552, 6, 6);//清源路
        pr.drawEllipse(462,567, 6, 6);//黄村西大街
        pr.drawEllipse(462,582, 6, 6);//黄村火车站
        pr.drawEllipse(462,597, 6, 6);//义和庄
        pr.drawEllipse(462,612, 6, 6);//生物医药基地
        pr.drawEllipse(462,627, 6, 6);//天宫院
    }
    {//5号线
        QColor fivecolor(166, 33, 127);
        pr.setPen(QPen(fivecolor,3,Qt::SolidLine));
        pr.drawLine(560,100,560,447);
        QPen pen(fivecolor);
        pen.setWidth(1);
        pr.setBrush(Qt::white);
        pr.setPen(pen);
        pr.drawEllipse(557,97,6,6);//天通苑北
        pr.drawEllipse(557,112,6,6);//天通苑
        pr.drawEllipse(557,127,6,6);//天通苑南
        pr.drawEllipse(557,142,6,6);//立水桥
        pr.drawEllipse(557,157,6,6);//立水桥南
        pr.drawEllipse(557,172,6,6);//北苑路北
        pr.drawEllipse(557,192,6,6);//大屯路东
        pr.drawEllipse(557,209,6,6);//惠新西街北口
        pr.drawEllipse(557,226,6,6);//惠新西街南口
        pr.drawEllipse(557,239,6,6);//和平西桥
        pr.drawEllipse(557,253,6,6);//和平里北街
        pr.drawEllipse(557,267, 6, 6);//2-雍和宫
        pr.drawEllipse(557,287, 6, 6);//北新桥
        pr.drawEllipse(557,302, 6, 6);//张自忠路
        pr.drawEllipse(557,317, 6, 6);//东四
        pr.drawEllipse(557,332, 6, 6);//灯市口
        pr.drawEllipse(557, 347, 6, 6);//1-东单
        pr.drawEllipse(557,372, 6, 6);//2-崇文门
        pr.drawEllipse(557,387, 6, 6);//7-磁器口
        pr.drawEllipse(557,402, 6, 6);//天坛东门
        pr.drawEllipse(557,417, 6, 6);//14-蒲黄榆
        pr.drawEllipse(557,432, 6, 6);//刘家窑
        pr.drawEllipse(557,447, 6, 6);//10,亦庄-宋家庄
    }
    {//6号线
        QColor sixcolor(210, 151, 0);
        pr.setPen(QPen(sixcolor,3,Qt::SolidLine));
        pr.drawLine(186,326,186,305);
        pr.drawLine(186,305,510,305);
        pr.drawLine(510,305,532,320);
        pr.drawLine(532,320,866,320);
        pr.drawLine(866,320,888,358);
        pr.drawLine(888,358,970,358);
        QPen pen(sixcolor);
        pen.setWidth(1);
        pr.setBrush(Qt::white);
        pr.setPen(pen);
        pr.drawEllipse(183, 323, 6, 6);//1,S1-苹果园
        pr.drawEllipse(183, 312, 6, 6);//杨庄
        pr.drawEllipse(183, 302, 6, 6);//西黄村
        pr.drawEllipse(213, 302, 6, 6);//廖公庄
        pr.drawEllipse(243, 302, 6, 6);//田村
        pr.drawEllipse(273, 302, 6, 6);//海淀五路居
        pr.drawEllipse(303, 302, 6, 6);//10-慈寿寺
        pr.drawEllipse(334, 302, 6, 6);//花园桥
        pr.drawEllipse(366, 302, 6, 6);//9-白石桥南
        pr.drawEllipse(380,302, 6, 6);//二里沟
        pr.drawEllipse(403,302, 6, 6);//车公庄西
        pr.drawEllipse(437,302, 6, 6);//2-车公庄
        pr.drawEllipse(462,302, 6, 6);//4,19-平安里
        pr.drawEllipse(487,302, 6, 6);//北海北
        pr.drawEllipse(507,302, 6, 6);//8-南锣鼓巷
        pr.drawEllipse(557,317, 6, 6);//5-东四
        pr.drawEllipse(582,317, 6, 6);//2-朝阳门
        pr.drawEllipse(605,317, 6, 6);//东大桥
        pr.drawEllipse(630, 317, 6, 6);//10-呼家楼
        pr.drawEllipse(654, 317, 6, 6);//金台路
        pr.drawEllipse(680, 317, 6, 6);//十里堡
        pr.drawEllipse(706, 317, 6, 6);//青年路
        pr.drawEllipse(732, 317, 6, 6);//褡裢坡
        pr.drawEllipse(758, 317, 6, 6);//黄渠
        pr.drawEllipse(784, 317, 6, 6);//常营
        pr.drawEllipse(810, 317, 6, 6);//草房
        pr.drawEllipse(836, 317, 6, 6);//物资学院路
        pr.drawEllipse(863, 317, 6, 6);//通州北关
        pr.drawEllipse(885, 355, 6, 6);//北运河西
        pr.drawEllipse(905, 355, 6, 6);//北运河东
        pr.drawEllipse(925, 355, 6, 6);//郝家府
        pr.drawEllipse(946, 355, 6, 6);//东夏园
        pr.drawEllipse(967, 355, 6, 6);//潞城
    }
    {//7号线
        QColor sevencolor(245, 197, 135);
        pr.setPen(QPen(sevencolor,3,Qt::SolidLine));
        pr.drawLine(369,375, 380, 390);
        pr.drawLine(380,390, 710, 390);
        pr.drawLine(710,390, 710, 469);
        pr.drawLine(710,469, 899, 469);
        pr.drawLine(899,469, 899, 520);
        QPen pen(sevencolor);
        pen.setWidth(1);
        pr.setBrush(Qt::white);
        pr.setPen(pen);
        pr.drawEllipse(366, 372, 6, 6);//9-北京西站
        pr.drawEllipse(377, 387, 6, 6);//湾子
        pr.drawEllipse(390, 387, 6, 6);//达官营
        pr.drawEllipse(427, 387, 6, 6);//广安门内
        pr.drawEllipse(462,387, 6, 6);//4-菜市口
        pr.drawEllipse(482,387, 6, 6);//虎坊桥
        pr.drawEllipse(507,387, 6, 6);//8-珠市口
        pr.drawEllipse(537,387, 6, 6);//桥湾
        pr.drawEllipse(557,387, 6, 6);//5-磁器口
        pr.drawEllipse(581,387, 6, 6);//广渠门内
        pr.drawEllipse(605,387, 6, 6);//广渠门外
        pr.drawEllipse(630,387, 6, 6);//10-双井
        pr.drawEllipse(654,387, 6, 6);//14-九龙山
        pr.drawEllipse(678,387, 6, 6);//大郊亭
        pr.drawEllipse(707,387, 6, 6);//百子湾
        pr.drawEllipse(707,420, 6, 6);//化工
        pr.drawEllipse(707,452, 6, 6);//南楼梓庄
        pr.drawEllipse(717,466, 6, 6);//欢乐谷景区
        pr.drawEllipse(735,466, 6, 6);//垡头
        pr.drawEllipse(752,466, 6, 6);//双合
        pr.drawEllipse(770,466, 6, 6);//焦化厂
        pr.drawEllipse(787,466, 6, 6);//黄厂
        pr.drawEllipse(805,466, 6, 6);//郎辛庄
        pr.drawEllipse(822,466, 6, 6);//黑庄户
        pr.drawEllipse(840,466, 6, 6);//万盛西
        pr.drawEllipse(857,466, 6, 6);//群芳
        pr.drawEllipse(878,466, 6, 6);//高楼金
        pr.drawEllipse(898, 466, 6, 6);//1-花庄
        pr.drawEllipse(898, 517, 6, 6);//1-环球度假区
    }
    {//8号线
        QColor eightcolor(22, 154, 108);
        pr.setPen(QPen(eightcolor,3,Qt::SolidLine));
        pr.drawLine(430,113,510,113);
        pr.drawLine(510,113,510,305);
        pr.drawLine(510,305,520,325);
        pr.drawLine(520,325,537,335);
        pr.drawLine(537,335,537,350);
        pr.drawLine(537,350,530,375);
        pr.drawLine(530,375,510,390);
        pr.drawLine(510,390,510,525);
        pr.drawLine(510,525,570,585);
        pr.drawLine(570,585,570,605);
        QPen pen(eightcolor);
        pen.setWidth(1);
        pr.setBrush(Qt::white);
        pr.setPen(pen);
        pr.drawEllipse(427,110, 6, 6);//昌平-朱辛庄
        pr.drawEllipse(457,110, 6, 6);//育知路
        pr.drawEllipse(487,110, 6, 6);//平西府
        pr.drawEllipse(507,120, 6, 6);//回龙观东大街
        pr.drawEllipse(507,140, 6, 6);//13-霍营
        pr.drawEllipse(507,151, 6, 6);//育新
        pr.drawEllipse(507,162, 6, 6);//西小口
        pr.drawEllipse(507,172, 6, 6);//永泰庄
        pr.drawEllipse(507,182, 6, 6);//林萃桥
        pr.drawEllipse(507,192, 6, 6);//森林公园南门
        pr.drawEllipse(507,203, 6, 6);//15-奥林匹克公园
        pr.drawEllipse(507,214, 6, 6);//奥体中心
        pr.drawEllipse(507,226, 6, 6);//10-北土城
        pr.drawEllipse(507,240, 6, 6);//安华桥
        pr.drawEllipse(507,253, 6, 6);//安德里北街
        pr.drawEllipse(507,267, 6, 6);//2-鼓楼大街
        pr.drawEllipse(507,286, 6, 6);//什刹海
        pr.drawEllipse(507,302, 6, 6);//6-南锣鼓巷
        pr.drawEllipse(517,322, 6, 6);//中国美术馆
        pr.drawEllipse(534,332, 6, 6);//金鱼胡同
        pr.drawEllipse(534, 347, 6, 6);//1-王府井
        pr.drawEllipse(527,372, 6, 6);//2-前门
        pr.drawEllipse(507,387, 6, 6);//7-珠市口
        pr.drawEllipse(507,402, 6, 6);//天桥
        pr.drawEllipse(507,417, 6, 6);//14-永定门外
        pr.drawEllipse(507,427, 6, 6);//木樨园
        pr.drawEllipse(507,437, 6, 6);//海户屯
        pr.drawEllipse(507,462, 6, 6);//大红门南
        pr.drawEllipse(507,477, 6, 6);//和义
        pr.drawEllipse(507,500, 6, 6);//东高地
        pr.drawEllipse(507,522, 6, 6);//火箭万源
        pr.drawEllipse(537,552, 6, 6);//五福堂
        pr.drawEllipse(567,582, 6, 6);//德茂
        pr.drawEllipse(567,602, 6, 6);//瀛海
    }
    {//9号线
        QColor ninecolor(144, 194, 50);
        pr.setPen(QPen(ninecolor,3,Qt::SolidLine));
        pr.drawLine(369,282,369,375);
        pr.drawLine(369,375,329,415);
        pr.drawLine(329,415,329,465);
        QPen pen(ninecolor);
        pen.setWidth(1);
        pr.setBrush(Qt::white);
        pr.setPen(pen);
        pr.drawEllipse(366,279, 6, 6);//4,16-国家图书馆
        pr.drawEllipse(366, 302, 6, 6);//6-白石桥南
        pr.drawEllipse(366, 323, 6, 6);//白堆子
        pr.drawEllipse(366, 347, 6, 6);//1-军事博物馆
        pr.drawEllipse(366, 372, 6, 6);//7-北京西站
        pr.drawEllipse(353, 385, 6, 6);//六里桥东
        pr.drawEllipse(340, 398, 6, 6);//10-六里桥
        pr.drawEllipse(326, 412, 6, 6);//七里庄
        pr.drawEllipse(326, 422, 6, 6);//丰台东大街
        pr.drawEllipse(326, 432, 6, 6);//16-丰台南路
        pr.drawEllipse(326, 442, 6, 6);//科怡路
        pr.drawEllipse(326, 452, 6, 6);//丰台科技园
        pr.drawEllipse(326, 462, 6, 6);//郭公庄
    }
    {//大兴机场线
        QColor daxingcolor(9, 77, 155);
        pr.setPen(QPen(daxingcolor,3,Qt::SolidLine));
        pr.drawLine(442,450,442,487);
        pr.drawLine(442,487,497,487);
        pr.drawLine(497,487,497,680);
        QPen pen(daxingcolor);
        pen.setWidth(1);
        pr.setBrush(Qt::white);
        pr.setPen(pen);
        pr.drawEllipse(439,447, 6, 6);//草桥
        pr.drawEllipse(494,582, 6, 6);//大兴新城
        pr.drawEllipse(494,677, 6, 6);//大兴机场
    }
    pr.end();
}//绘图函数

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1000,700);
    //w.setStyleSheet("background-color: white;");
    w.setWindowTitle("北京地铁线路图总览");
    w.show();
    return a.exec();
}
