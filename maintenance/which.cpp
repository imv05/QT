#include <fstream>
#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include <windows.h>
#include "nlohmann/json.hpp" 
using json = nlohmann::json;
json j;
using namespace std;
int toSec(string a){
	if(a.size()==6)
		return ((a[0]-'0')*10+(a[1]-'0'))*3600+((a[2]-'0')*10+a[3]-'0')*60+(a[4]-'0')*10+a[5]-'0';
	if(a.size()==4){
		return ((a[0]-'0')*10+a[1]-'0')*60+(a[2]-'0')*10+a[3]-'0';
	}
	cout << "Error parsing timestr" << endl;
	return -1;
}
json& getStation(json& jline, int stationId){
	return jline["stationList"][stationId-1];
}
json& getLine(int lineId){
	int lineCnt = j.size();
	for(int i=0; i<lineCnt; i++){
		if(j[i]["lineId"] == lineId){
			return j[i];
		}
	}
	cout << "error finding lineId=" << lineId << endl;
	return j[0];
}
void showSec(int total){
	cout << total/3600 << ":" << total%3600/60 << ":" << total%60;
}
void createConnection(json& jc, json& jsl){
	static int firstTime = 0;	//为给缺省情况提供方便，保留上次的输入值 
	static int lastTime = 0;
	static int duration = 0;
	cout << "connectTo " << jc["nextStationId"] << jsl[int(jc["nextStationId"])-1]["stationName"] << endl;
	string timestr;
	cout << "firstTime(hhmm):"; getline(cin, timestr); 
	if(toSec(timestr+"00") != -1){
		firstTime = toSec(timestr+"00");
	}else{
		firstTime += duration*60;
	}
	jc["firstTime"] = firstTime;
	cout << "lastTime(hhmm):"; getline(cin, timestr);
	if(toSec(timestr+"00") != -1){
		lastTime = toSec(timestr+"00");
	}else{
		lastTime += duration*60;
	}
	jc["lastTime"] = lastTime;
	cout << "duration(m):";  cin >> duration; getchar(); 
	jc["duration"] = duration*60;
}
void addinterchange(void){
	cout << "adding interchange relations" << endl;
	while(true){
		restartIc:
		cout << "A,lineId:(-1 to quit)"; int lineAId; cin >> lineAId;
		if(lineAId==-1)break;
		cout << "B,lineId:"; int lineBId; cin >> lineBId; getchar();
		cout << "station name:" ;
		string sName; getline(cin, sName);
		int i;
		json& jsl = getLine(lineAId)["stationList"];
		int stationCnt = jsl.size();
		for(i=0; i<stationCnt; i++){
			json& js = jsl[i];
			if(js["stationName"] == sName){
				break;
			}
			if(i == stationCnt-1){
				cout << "A has no station named " << sName << endl;
				goto restartIc;
			}
		}
		int stationAId = i+1;
		cout << "A,stationId:" << stationAId << "\t";
		json& jslb = getLine(lineBId)["stationList"];
		stationCnt = jslb.size();
		for(i=0; i<stationCnt; i++){
			json& js = jslb[i];
			if(js["stationName"] == sName){
				break;
			}
			if(i == stationCnt-1){
				cout << "A has no station named " << sName << endl;
				goto restartIc;
			}
		}
		int stationBId = i+1;
		cout << "B,stationId:" << stationBId << "\t";
		{
			json& jsa = getStation(getLine(lineAId), stationAId);
			cout << "adding " << lineAId << "->" << lineBId << endl;
			jsa["interchangeList"].push_back(json::object());
			jsa["interchangeList"][jsa["interchangeList"].size()-1]["lineId"] = lineBId;
			jsa["interchangeList"][jsa["interchangeList"].size()-1]["stationId"] = stationBId;
			cout << "duration(seconds)" << endl; int duration; cin >> duration;
			jsa["interchangeList"][jsa["interchangeList"].size()-1]["duration"] = duration;
			cout << "isOut?(1 or 0)" << endl;	bool isOut; cin >> isOut; getchar();
			jsa["interchangeList"][jsa["interchangeList"].size()-1]["isOut"] = isOut;
			cout << "note?" << endl; string note; getline(cin, note);
			jsa["interchangeList"][jsa["interchangeList"].size()-1]["note"] = note.c_str();
		}
		{
			json& jsb = getStation(getLine(lineBId), stationBId);
			cout << "adding " << lineBId << "->" << lineAId << endl;
			jsb["interchangeList"].push_back(json::object());
			jsb["interchangeList"][jsb["interchangeList"].size()-1]["lineId"] = lineAId;
			jsb["interchangeList"][jsb["interchangeList"].size()-1]["stationId"] = stationAId;
			cout << "duration(seconds)" << endl; int duration; cin >> duration;
			jsb["interchangeList"][jsb["interchangeList"].size()-1]["duration"] = duration;
			cout << "isOut?(1 or 0)" << endl;	bool isOut; cin >> isOut; getchar();
			jsb["interchangeList"][jsb["interchangeList"].size()-1]["isOut"] = isOut;
			cout << "note?" << endl; string note; getline(cin, note);
			jsb["interchangeList"][jsb["interchangeList"].size()-1]["note"] = note.c_str();
		}
	}
}
void addLine(void){
	cout << "adding new line, input:" << endl;
	cout << "lineId:";
	int lineId; 
	cin >> lineId;
	int lineCnt = j.size();
	int ins = lineCnt;
	for(int i=0; i<lineCnt; i++){
		if(j[i]["lineId"] > lineId){
			ins = i;
			break;
		}
	}
	j.insert(j.begin()+ins, json({}));
	json& jl = j[ins];
	jl["lineId"] = lineId; getchar();
	cout << "lineName:"; string lineName; getline(cin, lineName); 
	jl["lineName"] = lineName.c_str();
	cout << "lineEngName:"; string lineEngName; getline(cin, lineEngName); 
	jl["lineEngName"] = lineEngName.c_str();
	cout << "incDirection:"; string incDirection; getline(cin, incDirection); 
	jl["incDirection"] = incDirection.c_str();
	cout << "decDirection:"; string DecDirection; getline(cin, DecDirection); 
	jl["decDirection"] = DecDirection.c_str();
	cout << "color: #"; string color; getline(cin, color); 
	jl["color"] = (string("#") + color).c_str();
	cout << "Now creating stations:" << endl;
	jl["stationList"] = json::array();
	json& jsl = jl["stationList"];
	int stationCnt=0;
	cout << "id\tstationName" << endl;
	while(true){
		cout << stationCnt+1 << "\t";
		string stationName; getline(cin, stationName);
		if(stationName.empty())break;
		jsl.insert(jsl.begin()+stationCnt, json({}));
		json& js = jsl[stationCnt];
		js["stationName"] = stationName.c_str();
		cout << "stationEngName:" ;
		string stationEngName; getline(cin, stationEngName);
		js["stationEngName"] = stationEngName.c_str();
		js["stationId"] = stationCnt+1;
		js["interchangeList"] = json::array();
		stationCnt++;
	}
	cout << "now add connections" << endl;
	cout << "general connection?(Y/N)" << endl; char isGeneral = 0;	cin.get(isGeneral); getchar();
	if(isGeneral=='Y'||isGeneral=='y'){
		for(int i=0; i<stationCnt; i++){
			json& js = jsl[i]; 
			cout << js["stationName"];
			js["connectionList"] = json::array();
			json& jcl = js["connectionList"];
			if(i!=stationCnt-1){
				jcl.push_back(json::object());
				json& jc = jcl.back();
				jc["nextStationId"] = i+2;//i锟斤拷0锟斤拷始 
				createConnection(jc, jsl);
			}
		}
		for(int i=stationCnt-1; i>=0; i--){
			json& js = jsl[i]; 
			cout << js["stationName"];
			json& jcl = js["connectionList"];
			if(i!=0){
				jcl.push_back(json::object());
				json& jc = jcl.back();
				jc["nextStationId"] = i;
				createConnection(jc, jsl);
			}
		}
		int distList[100] = {};
		for(int i=0; i<stationCnt-1; i++){//stationId inc;
			json& js = jsl[i]; 
			cout << "Inc" << js["stationName"];
			json& jcl = js["connectionList"];
			json& jc = jcl.front();
			cout << "to" << jc["nextStationId"] << "dist:"; cin >> distList[i];
			jc["dist"] = distList[i];
		}
		for(int i=stationCnt-1; i>=1; i--){//stationId dec; 
			json& js = jsl[i]; 
			cout << "Dec" << js["stationName"];
			json& jcl = js["connectionList"];
			json& jc = jcl.back();
			cout << "to" << jc["nextStationId"] << "dist:"; cout << distList[i-1] << endl;
			jc["dist"] = distList[i-1];
		}
	}
	getchar();
	cout << "now add extra connections(eg.for loop)";
	while(true){
		cout << "connection from" << endl;
		string startName;
		getline(cin, startName);
		if(startName.empty())break;
		for(int i=0; i<stationCnt; i++){
			json& js = jsl[i];
			if(js["stationName"] == startName){
				cout << "start station found.";
				json& jcl = js["connectionList"];
				jcl.push_back(json::object());
				json& jc = jcl.back();
				string toName;
				getline(cin, toName);
				int j=0;
				for(j=0; j<stationCnt; j++){
					json& js2 = jsl[j];
					if(js2["stationName"] == toName){
						cout << "to station found";
						break;
					}
				}
				jc["nextStationId"] = j;
				createConnection(jc, jsl);
			}
		}
	}
	cout << "adding connection finished, total " << jl["stationList"].size() << " stations" << endl;
	cout << "now add coordinates" << endl;
	int tempx, tempy;
	for(int i=0; i<stationCnt; i++){
		json& js = jsl[i];
		cout << js["stationName"] << "x:";
		int x, y;
		if(isdigit(cin.peek())){
			cin >> x;
			tempx = x;
		}else{
			cout << tempx;
			x = tempx;
		}
		getchar();
		cout << "y:";
		if(isdigit(cin.peek())){
			cin >> y;
			tempy = y;
		}else{
			cout << tempy;
			y = tempy;
		}
		getchar();
		js["screen"] = json::object();
		js["screen"]["x"] = x; js["screen"]["y"] = y;
	}
	cout << "now add corner anchors" << endl;
	jl["anchorList"] = json::array();
	json& jal = jl["anchorList"];
	while(true){
		int sid=-1, eid;
		cout << "sid:(enter -1 to stop, sid<eid)";
		cin >> sid;
		if(sid==-1)break;
		jal.push_back(json::object());
		jal.back()["startId"] = sid;
		cout << "eid:";
		cin >> eid;
		jal.back()["endId"] = eid;
		int x=-1, y;
		cout << "x:";
		cin >> x; 
		cout << "y:"; cin >> y;
		jal.back()["x"] = x;
		jal.back()["y"] = y;
	}
	cout << "finished creating line lineId="<< jl["lineId"] << " lineName=" << jl["lineName"] << endl;
}
void showLine(json& j){
	std::cout << "lineId:" << j["lineId"] << std::endl;
	std::cout << "isNumeral:" << j["isNumeral"] << std::endl;
	std::cout << "lineName:" << j["lineName"] << std::endl;
	std::cout << "lineEngName:" << j["lineEngName"] << std::endl;
	std::cout << "loop:" << j["loop"] << std::endl;
	std::cout << "color:" << j["color"] << std::endl;
	std::cout << "interval:" << j["interval"] << std::endl;
	std::cout << "number of stations:" << j["stationList"].size() << std::endl;
	cout << endl;
}
void expandLine(json& j){
	cout << "showing stations of lineId:" << j["lineId"] << " lineName:" << j["lineName"] << endl;
	cout << "number of stations:" << j["stationList"].size() << std::endl;
	for(auto it: j["stationList"]){
		cout <<	it["stationId"] << "\t" << it["stationName"] << it["stationEngName"];
		for(auto cit: it["connectionList"]){
			if(cit["nextStationId"] == int(it["stationId"])+1){
				cout << "\t"; showSec(cit["runTime"]); cout <<"/"<< cit["dist"] << "m";
				for(auto oit: cit["operationList"]){
					cout << "\t" << "first="; showSec(oit["firstTime"]);
					cout << "\t" << "last="; showSec(oit["lastTime"]);
				}
			}
		}
	}
	cout << endl;
}
void showAllLine(void){
	int lineCnt = j.size();
	for(int i=0; i<lineCnt; i++){
        json jLine = j[i];
        cout << "Show info of line "<< i << "/" << lineCnt << endl;
        showLine(jLine);
    }
}

int main(){
	system("chcp 65001");	//json锟侥硷拷使锟斤拷UTF-8锟芥储 
	std::ifstream src("1100main.json");
    src >> j;
    string cmd;
    while(true){
    	cin >> cmd;
    	if(cmd == "exit"){
    		src.close();
    		break;
    	}
    	if(cmd == "show"){
    		cin >> cmd;
    		if(cmd == "line"){
    			cin >> cmd;
    			if(cmd == "all"){
    				showAllLine();
    				continue;
				}else{
					int givenId = atoi(cmd.c_str());
					for(auto it: j){
						if(it["lineId"] == givenId){
							showLine(it);
						}
					}
					continue;
				}
			}
		}
		if(cmd == "expand"){
			cin >> cmd;
			if(cmd == "line"){
				cin >> cmd;
				if(cmd == "all"){
//    				expandAllLine();
    				continue;
				}else{
					int givenId = atoi(cmd.c_str());
					for(auto it: j){
						if(it["lineId"] == givenId){
							expandLine(it);
						}
					}
					continue;
				}
			}
		}
		if(cmd == "delete"){
			cin >> cmd;
			if(cmd == "line"){
				cin >> cmd;
				int givenId = atoi(cmd.c_str());
				int lineCnt = j.size();
				for(int i=0; i<lineCnt; i++){
					if(j[i]["lineId"] == givenId){
						cout << "deleting:" << j[i]["lineName"] << "Y/N?"<<endl;
						cin >> cmd;
						if(cmd=="Y"||cmd=="y"){
							j.erase(i); lineCnt--;
						}
					}
				}
				bool exist = false;
				for(int i=0; i<lineCnt; i++){
					if(j[i]["lineId"] == givenId){
						exist = true;
					}
				}
				if(!exist)cout << "Successfully deleted lineId=" << givenId << endl;
				continue;
			}
		}
		if(cmd == "add"){
			cin >> cmd;
			if(cmd == "line"){
				addLine();
			}else if(cmd == "interchange"){
				addinterchange();
			}
		}
		if(cmd == "save"){
			std::ofstream out("1100maino.json"); 
			if(out << j)cout << "saved\n";
			out.close();
		}
	}
}
