#ifndef _LOADRES_H_
#define _LOADRES_H_

#include "cocos2d.h" 
#include "cocos-ext.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#ifdef __cplusplus
extern "C"{
#endif

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_NoWifi(JNIEnv * env, jclass ,jint); 
 
#ifdef __cplusplus
}
#endif

#endif

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

  
class  LoadRes : public cocos2d::Layer
{
public:
    void onEnter();
	static cocos2d::Scene * createScene();
	virtual bool init();              //初始化
	CREATE_FUNC(LoadRes);		  //创建层

	static int RoomType;

	Menu* m_GoBoss;
	//todo 预载入资源，实现StartScene后将其删除
	void preloadResources(); 
	bool loadResource(int room);//下载房间room的资源
	static size_t callbackFunction(void *buffer,size_t size,size_t nmemb,FILE *stream);
	void jiazaiPlist(int room);//加载房间plist 和  wang文件
	void jiazaiChange();
	int lastone;
	void updataDisplay(float dt);
	void gogogo(float dt);
	int iLoadNum;
	bool bLoadRes;
	void updataAddRes(float dt);
	void loadAnimate();

	void addResource(int room);
	void fanhuiGame();//返回游戏大厅
	void jixuGame();//返回游戏大厅
	void jinruChangjin(float dt);

	static bool bFirstJiaSu;
	static bool bFirtDingPing;
	static bool bFirstFanWei;
	static bool bFirstJiGuang; 
	static int hasWifi; 

	LabelTTF * firstInLabel;
	Size visibleSize; 
	bool jihuo();
	void update(float dt);
	 
    void getrank();
    static size_t getrankcall(uint8_t *buffer,size_t size,size_t nmemb,void *stream);
    //void load_huafeileiji(char cinfo);
    //static size_t load_huafeileiji_call(uint8_t *buffer,size_t size,size_t nmemb,void *stream) ;
    
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 


private:
	//void AddBoss(int iBossId);
	int iRoomType; 
	int fishNum[12];
	int BSfishNum[4];
	int kroom;
	

	ControlSlider * LoadBar;
};

#endif

