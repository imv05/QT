#include "class.h"

#include <QDebug>
#include <iostream>

QMap<int, Line*> lineMap = QMap<int, Line*>();  //lineId,
QVector<Station*> allStations = QVector<Station*>();
QMap<QString, Station*> allStationNames = QMap<QString, Station*>();

Line::Line(json jLine){
    lineId = int(jLine["lineId"]);
    lineName = QString::fromStdString(jLine["lineName"]);
    lineEngName = QString::fromStdString(jLine["lineEngName"]);
    isLoop = jLine["loop"];
    isNumeral = jLine["isNumeral"];
    interval = 60 * int(jLine["interval"]);
    color = QColor::fromString(std::string(jLine["color"]));
    stationCnt = jLine["stationList"].size();
    for(int i=0; i<stationCnt; i++){
        json jStation = jLine["stationList"][i];
        stationMap.insert(jStation["stationId"], new Station(jStation, this));
    }
}
void Line::initializeConnectionLine(json jLine){
    auto stationIt = stationMap.begin();
    for(int i=0; i<stationCnt; i++){
        Station* cStation = *stationIt;
        json jStation = jLine["stationList"][i];
        cStation->initializeConnection(jStation);
        stationIt++;
    }
}
Station* Line::operator[](int stationId){//通过stationId获取Station的引用
    if(!stationMap.contains(stationId)){
        qDebug() << "cannot find stationId="<<stationId<<"in lineId="<<lineId;
    }
    return stationMap[stationId];
}
Station::Station(json jStation, Line* cLine){
    allStations.push_back(this);    //所有站点都将在allStations中
    line = cLine;
    lineId = cLine->lineId;
    stationId = int(jStation["stationId"]);
    stationName = QString::fromStdString(jStation["stationName"]);
    allStationNames[stationName] = this;
    stationEngName = QString::fromStdString(jStation["stationEngName"]);
    available = jStation["available"];
    x = jStation["screen"]["x"];
    y = jStation["screen"]["y"];
}
void Station::initializeConnection(json jStation){
    cCnt = jStation["connectionList"].size();
    for(int k=0; k<cCnt; k++){
        json jconnection = jStation["connectionList"][k];
        cList.append(Connection(jconnection, this));
    }
    iCnt = jStation["interchangeList"].size();
    for(int k=0; k<iCnt; k++){
        json jinterchange = jStation["interchangeList"][k];
        cList.append(Connection(jinterchange, this));
    }
}
Connection::Connection(json jconnection, Station* cStation){   //使用json jconnection构造
    from = cStation;
    if(jconnection.contains("lineId")){//包含lineId即为换乘
        isTransfer = true;
        int lineId = jconnection["lineId"];
        int nId = jconnection["stationId"];
        to = lineMap[lineId]->stationMap[nId];
        dist = 0;
        time = jconnection["duration"];
        note = QString::fromStdString(jconnection["note"]);
        isOut = jconnection["isOut"];
    }else{
        isTransfer = false;
        int nId = jconnection["nextStationId"];
        to = from->line->stationMap[nId];
        dist = jconnection["dist"];
        time = jconnection["duration"];
        int oCnt = jconnection["operationList"].size();
        const int daySec = 24*3600;
        int last = toSec(19,0,0) + daySec; //最早末班车初始化为19:00:00
        for(int k=0; k<oCnt; k++){//处理多个终点的末班车。
            const int distinct = toSec(19,0,0);
            json jo = jconnection["operationList"][k];
            int thisLast = jo["lastTime"];
            if(thisLast < distinct){
                thisLast += daySec;
            }
            if(thisLast > last){
                last = thisLast;
            }
        }
        //此时last表示此方向最晚的末班车
    }
}

