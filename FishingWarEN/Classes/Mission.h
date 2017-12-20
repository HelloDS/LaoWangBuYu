 #ifndef _MISSION_
#define _MISSION_
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
  
class Mission: public cocos2d::Node
{
public:
	static Mission * create();
	virtual bool init();
	void changeMisson(int fishtype);//改变任务状态
	bool getIsMission(); //返回任务状态
	void zhuanpan(float dt);//进入转盘
private:
	//任务相关
	LabelTTF * missionLabel;
	Sprite * fish;
	Sprite * missionBG;
	LabelTTF * missionA;
	LabelTTF * missionB;

	int fishKind; //当前任务鱼的种类
	int missionNum; //完成任务数
	int missionKind; //当前任务种类
	bool isMissionIng; //任务是否进行中
	int roomBeilv; //当前任务的倍率
	float scaleNum; // 鱼缩小的倍数
};

#endif
