#pragma once
#include <string>
#include <vector>
#include "cocos2d.h"

#include <algorithm> 

USING_NS_CC;
using namespace std;

struct MyStruct
{
	string name;
	long long  money;
	char ctype;
	int shootnum;
	bool wfcool;
	int base;
	bool operator >(const MyStruct& Pinfo) const;  //降序排列需要重载的操作符
	bool operator <(const MyStruct& pinfo) const;  //升序排列需要重载的操作符

};

class AllRobot
{
public:
    static int readnetLeiji[4];
    static int readnetHuafeiQuan[4];
    static int iRobotWinNum;
	AllRobot(void);
	~AllRobot(void); 
	vector<MyStruct> robot;
	void initplayer(int iPlayerNum,int itype,string SelfName);
	int iRobotBase[20];
	MyStruct firstboy[3];
	void sortandshoot(long long selfmoney);
    void setRobotWin();
	int getmyrank();
	int iTime;
	static int myrank;
	static bool shanshan;
	int iRandomTime[6]; 

};

