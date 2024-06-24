#include "load.h"
#include "class.h"
#include "global.h"

#include <QFile>
#include <QDataStream>
#include <qdebug.h>
#include <fstream>

int load(int citycode){//从json数据库加载
    QString path = ":/data/data/" + QString::number(citycode) + "main.json";
    QFile src(path);
    json j;
    if(src.open(QIODevice::ReadOnly)){
        QTextStream in(&src);
        QString jsonString = in.readAll();
        src.close();
        try {
            j = json::parse(jsonString.toStdString()); // 解析JSON字符串
        } catch (json::exception& e) {
            // 处理解析错误
            qDebug() << "JSON解析错误：" << e.what();
        }
    }else{//找不到指定的json文件
        qDebug() << "Unable to find data of citycode " << QString::number(citycode);
        return 0;
    }
    int lineCnt =  j.size();
    //第一次读数据，建立所有line和station
    for(int i=0; i<lineCnt; i++){
        json jLine = j[i];
        int lineId = int(jLine["lineId"]);
        lineMap.insert(lineId, new Line(jLine));
    }
    //第二次读数据，建立station的connection
    auto lineIt = lineMap.begin();
    for(int i=0; i<lineCnt; i++){
        Line* cLine = *lineIt;
        json jLine = j[i];
        cLine->initializeConnectionLine(jLine);
        lineIt++;
    }
    return lineCnt;
}
