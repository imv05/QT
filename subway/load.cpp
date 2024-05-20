#include "load.h"
#include "class.h"
#include "global.h"
#include <fstream>

int load(void){//从json数据库加载
    std::ifstream src("D:/QT/subway/stations.json");
    std::ofstream dest("D:/QT/subway/temp.out");
    json j;
    src >> j;
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
