#include "class.h"

#include <QDebug>
#include <QPainterPath>

QMap<int, Line*> lineMap = QMap<int, Line*>();  //lineId,
QVector<Station*> allStations = QVector<Station*>();
QMap<QString, Station*> allStationNames = QMap<QString, Station*>();
QMap<QPair<Station*, Station*>, SPath*> spathMap = QMap<QPair<Station*, Station*>, SPath*>();   //双向只有一对
// QHash<SPath*, QGraphicsPathItem*> spathToItemMap = QHash<SPath*, QGraphicsPathItem*>();
QMap<QPair<Station*, Station*>, QGraphicsPathItem*> pathItemMap = QMap<QPair<Station*, Station*>, QGraphicsPathItem*>();    //双向有两对
QMap<QString, QGraphicsItem*> stationItemMap = QMap<QString, QGraphicsItem*>();
QMap<QString, QGraphicsTextItem*> stationTextMap = QMap<QString, QGraphicsTextItem*>();
QMap<QString, QVector<Station*> > stationsByName = QMap<QString, QVector<Station*> >();

Line::Line(json jLine){
    lineId = int(jLine["lineId"]);
    lineName = QString::fromStdString(jLine["lineName"]);
    lineEngName = QString::fromStdString(jLine["lineEngName"]);
    incDirection = QString::fromStdString(jLine["incDirection"]);
    decDirection = QString::fromStdString(jLine["decDirection"]);
    // isLoop = jLine["loop"];
    // isNumeral = jLine["isNumeral"];
    // interval = 60 * int(jLine["interval"]);
    color = QColor::fromString(std::string(jLine["color"]));
    stationCnt = jLine["stationList"].size();
    for(int i=0; i<stationCnt; i++){
        json& jStation = jLine["stationList"][i];
        stationMap.insert(jStation["stationId"], new Station(jStation, this));
    }
}
void Line::initializeConnectionLine(json jLine){
    auto stationIt = stationMap.begin();
    for(int i=0; i<stationCnt; i++){    //建立站点图的connection
        Station* cStation = *stationIt;
        json& jStation = jLine["stationList"][i];
        cStation->initializeConnection(jStation);
        stationIt++;
    }
    stationIt = stationMap.begin();
    //绘制connection对应的path
    for(int i=0; i<stationCnt; i++){
        Station* cStation = *stationIt;
        int cCnt = cStation->cList.size();
        for(int ci=0; ci<cCnt; ci++){
            Connection& cit = cStation->cList[ci];
            if(!cit.isTransfer){
                Station* tostn = cit.to;
                Station* fromstn = cit.from;
                qreal toId = tostn->stationId; qreal fromId = fromstn->stationId;
                if(toId < fromId){//保证from的车站id比end小
                    qreal temp=toId; toId=fromId; fromId=temp;
                    Station* tempstn=tostn; tostn=fromstn; fromstn=tempstn;
                }
                if(spathMap.contains(QPair<Station*, Station*>(fromstn, tostn)))continue;
                else{
                    SPath* cSP = new SPath;
                    spathMap[QPair<Station*, Station*>(fromstn, tostn)] = cSP;
                    cSP->start = QPointF(fromstn->x, fromstn->y);
                    cSP->end = QPointF(tostn->x, tostn->y);
                }
            }
        }
        stationIt++;
    }
    json& jalist = jLine["anchorList"];
    int anchorCnt = jalist.size();
    for(int i=0; i<anchorCnt; i++){
        int sid = jalist[i]["startId"];//保证start的车站id比end小
        int eid = jalist[i]["endId"];
        Station* sstn = stationMap[sid];
        Station* estn = stationMap[eid];
        if(spathMap.contains(QPair<Station*, Station*>(sstn, estn))){
            spathMap[QPair<Station*, Station*>(sstn, estn)]->corner.push_back(QPointF(int(jalist[i]["x"]), int(jalist[i]["y"])));
        }else{
            qDebug() << "Does not contain spath info of station pair" << sstn->line->lineName << sstn->stationId << sstn->stationName;
            qDebug() << estn->line->lineName << estn->stationId << estn->stationName;
        }
    }
}
Station* Line::operator[](int stationId){//通过stationId获取Station的引用
    if(!stationMap.contains(stationId)){
        qDebug() << "cannot find stationId="<<stationId<<"in lineId="<<lineId;
        return nullptr;
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
    // available = jStation["available"];
    x = jStation["screen"]["x"];
    y = jStation["screen"]["y"];
    stationsByName[stationName].push_back(this);
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
        //临时解决方案：通过this的stationId和nextStation的id判断方向。
        if(nId == from->stationId + 1){
            direction = 1;
        }else if(nId == from->stationId - 1){
            direction = -1;
        }else if(nId == 1){//环线最大id，+1
            direction = 1;
        }else if(from->stationId==1){//环线最小id，-1
            direction = -1;
        }else{
            direction = -1;
        }
        //临时解决方案末尾
        to = from->line->stationMap[nId];
        dist = jconnection["dist"];
        time = jconnection["duration"];
        int oCnt = jconnection["operationList"].size();
        const int daySec = 24*3600;
        last = toSec(19,0,0) + daySec; //最早末班车初始化为19:00:00
        if(jconnection.contains("lastTime")){//当前的数据库里仅考虑最晚的末班（即能到下一站的末班车）
            first = jconnection["firstTime"];
            last = jconnection["lastTime"];
        }else{//预留：以后数据库会有多个终点的情况
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
        }
        //此时last表示此方向最晚的末班车
    }
}
