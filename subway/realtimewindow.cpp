#include "realtimewindow.h"
#include "ui_realtimewindow.h"
#include <QLabel>

int s2s(const QString& timestr){
    if(timestr.size() == 8){// hh:mm:ss
        if(timestr[0] == '?'){
            return -2;
        }
        int hour = (timestr[0].unicode()-'0')*10+(timestr[1].unicode()-'0');
        int minute = (timestr[3].unicode()-'0')*10+(timestr[4].unicode()-'0');
        int second = (timestr[6].unicode()-'0')*10+(timestr[7].unicode()-'0');
        return 3600*hour+60*minute+second;
    }else{
        return -1;
    }
}

RealtimeWindow::RealtimeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RealtimeWindow)
{
    ui->setupUi(this);
    //工作日早八点是默认值
    isWorkday = true;
    curh = 8;
    curm = 0;
    ui->whdayButton->setText("切换到双休日");

    std::vector<QColor> allColor={};//保存所有的颜色，用来绘图
    std::vector<QString> allName={};
    QVector<Line*> allLine = {};
    for(auto cline: lineMap){
        allColor.push_back(cline->color);
        allName.push_back(cline->lineName);
        allLine.push_back(cline);
    }
    int lineCnt = lineMap.size();
    for(int i=0; i<lineCnt; i++){
        QLabel* colorLabel =new QLabel(this);
        colorLabel->setStyleSheet(QString("background-color:%1;").arg(allColor[i].name()));
        QPushButton* text=new QPushButton(allName[i]);
        text->setStyleSheet("QPushButton { text-align: left; }");
        lineButtons.append(buttonManage(text,i));
        connect(text,&QPushButton::clicked,this,&RealtimeWindow::lineButtonclicked);
        // QLabel* text=new QLabel(allName[i], this);
        // text->setStyleSheet(QString("color:#000000;"));
        ui->lineLayout->addRow(colorLabel, text);
    }

    rtScene.setSceneRect(0,0,800,600);
    rtScene.setBackgroundBrush(QBrush(Qt::white));
    RealtimeView* rtView=new RealtimeView(rtScene,this);
    rtView->setScene(&rtScene);
    // 设置PlanGraphicsView的父控件为ui->singleView
    rtView->setParent(ui->singleView);
    rtView->show();
}

RealtimeWindow::~RealtimeWindow()
{
    delete ui;
}

void RealtimeWindow::on_whdayButton_clicked()
{
    isWorkday = !isWorkday;
    if(isWorkday){
        ui->whdayButton->setText("切换到双休日");
        ui->whdayEdit->setText("工作日");
    }else{
        ui->whdayButton->setText("切换到工作日");
        ui->whdayEdit->setText("双休日");
    }

}

void RealtimeWindow::lineButtonclicked(){
    auto* button = qobject_cast<QPushButton*>(sender());
    if(button){
        for(auto one: lineButtons){
            if(one.button==button){ //找到了按键
                curLine = *(lineMap.begin().operator +=(one.lineOrder));
                direction = 1;
                curStationId = 1;
                break;
            }
        }
    }
    rtLoad();
}

void RealtimeWindow::on_hincButton_clicked()
{
    curh ++;
    if(curh==24)curh=0;
    refreshTime();
}

void RealtimeWindow::on_hdecButton_clicked()
{
    curh--;
    if(curh==-1)curh=23;
    refreshTime();
}

void RealtimeWindow::on_mincButton_clicked()
{
    curm++;
    if(curm==60)curm=0;
    refreshTime();
}

void RealtimeWindow::on_mdecButton_clicked()
{
    curm--;
    if(curm==-1)curm=59;
    refreshTime();
}

void RealtimeWindow::on_hEdit_editingFinished()
{
    const QString arg1 = ui->hEdit->text();
    bool valid = true;
    int nv = 0;
    if(arg1.size()>2){
        valid = false;
    }else{
        nv = arg1.toInt();
        if(nv==24)nv=0;
        if(nv>23||nv<0){
            valid = false;
        }
    }
    if(valid){
        curh = nv;
    }
    refreshTime();
}

void RealtimeWindow::on_mEdit_editingFinished()
{
    const QString arg1 = ui->mEdit->text();
    bool valid = true;
    int nv = 0;
    if(arg1.size()>2){
        valid = false;
    }else{
        nv = arg1.toInt();
        if(nv==60)nv=0;
        if(nv>59||nv<0){
            valid = false;
        }
    }
    if(valid){
        curm = nv;
    }
    refreshTime();
}

void RealtimeWindow::refreshTime(void){
    QString hstr = QString("%1").arg(curh, 2, 10, QLatin1Char('0'));
    ui->hEdit->setText(hstr);
    QString mstr = QString("%1").arg(curm, 2, 10, QLatin1Char('0'));
    ui->mEdit->setText(mstr);
    QGraphicsScene &sc = rtScene;
    nowtime = 3600*curh+60*curm;
    if(nowtime<3*3600){
        nowtime += 24*3600;
    }


}

void RealtimeWindow::rtLoad(void){
    QString filePath = ":/data/data/" + QString::number(curLine->lineId)
    + ',' + QString::number(direction) + ',' + QString::number(isWorkday) + ".csv";
    QFile src(filePath);
    QList<QStringList> timedata;
    QList<QStringList> crowddata;
    int length;
    if(!src.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "reading csv error";
    }else{
        QTextStream stream(&src);
        QString headerline = stream.readLine();
        header = headerline.split(',');
        length = header.size();
        header.pop_front();
        stationCnt = length-1;
        n = 0;

        while(!stream.atEnd()){
            n++;
            QString l1 = stream.readLine();
            QStringList l1list = l1.split(',');
            timedata.append(l1list);
            QString l2 = stream.readLine();
            QStringList l2list = l2.split(',');
            crowddata.append(l2list);
        }

        qDebug() << n;
        for(int i=0; i<n; i++){
            code.append(timedata[i][0]);
            time.append(QList<int>());
            crowd.append(QList<int>());
            for(int j=1; j<length; j++){
                time[i].append(s2s(timedata[i][j]));
            }
            for(int j=1; j<length; j++){
                crowd[i].append(QString(crowddata[i][j]).toInt());
            }
        }
    }
    QGraphicsScene &sc = rtScene;
    rtScene.clear();
    QColor color = curLine->color;
    QBrush brush(QColor("#2E3192"));
    QGraphicsRectItem* separator = sc.addRect(0,400,800,10);
    separator->setBrush(brush);
    separator->setPen(QPen(Qt::white));
    QList<QList<QGraphicsTextItem*>> stationItems;
    QFont stationFont = QFont("等线", 12);
    for(int i=0; i<stationCnt; i++){
        stationItems.append(QList<QGraphicsTextItem*>());
        for(int j=0; j<header[i].size(); j++){
            rtTextItem* temp = new rtTextItem(header[i][j]);
            temp->setFont(stationFont);
            temp->setDefaultTextColor(Qt::black);
            temp->setPos(10+i*768/stationCnt, 100+j*15);
            temp->setData(150, i);
            sc.addItem(temp);
            stationItems[i].append(temp);
        }
    }

    QPen pen(color);
    pen.setWidth(5);
    QGraphicsLineItem* line = sc.addLine(0,100,800,100,pen);
}
