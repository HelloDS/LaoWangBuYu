#ifndef _LOGO_LAYER_H_
#define _LOGO_LAYER_H_

#include"cocos2d.h" 
#include "TcpClientSocket.h"


#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#ifdef __cplusplus
extern "C"{
#endif

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_returnDeviceNo(JNIEnv * env, jclass ,jstring device); 

#ifdef __cplusplus
}
#endif

#endif

USING_NS_CC;
using namespace std;
  
class LogoLayer : public cocos2d::Layer
{
public:
	 
	static cocos2d::Scene* createScene();

	virtual bool init(); 
	bool updateGameInfo(string address);
	void updataDisplay(float dt);

    // 得到 Game Connect Socket
    static TcpClientSocket *m_pGameSocket;
    
    // 得到 Game Connect Socket
    static TcpClientSocket *GetSocket(void);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 

	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);

	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 

	static void baidu_denglu(int i);
	static size_t  possText(uint8_t *buffer,size_t size,size_t nmemb,void *stream);

	static size_t gameinfo_call(void *buffer,size_t size,size_t nmemb,FILE *stream);
	static bool initDeviceNo(char * deviceNo);

	void update(float dt);
	static bool iskuozhan;

    static char room;

	static time_t getTime();
	static time_t getHBTime();
	static int timeTmp[6];//用于储存网络时间的数组

	static void curlTime();   //获取网络时间

    
    //大厅地址
    static std::string gHIpStr;
    static unsigned short gHPortStr;
    
    //游戏地址
    static std::string gGIpStr;
    static unsigned short gGPortStr;
    
    
    static void MoreGameCurl();   //获取更多游戏
	static bool moreGameFlag;
    static bool dengluFlag;
    
	static size_t moregame_call(uint8_t *buffer,size_t size,size_t nmemb,void *stream);
	static size_t huidiaohanshu(uint8_t *buffer,size_t size,size_t nmemb,void *stream);   //网络返回数据回调函数
    
    
    void tcpRequestTimer(float dt);
    void loadIpAndPort(float dt);
    static size_t loadIpAndPortCallback(uint8_t *buffer,size_t size,size_t nmemb,void *stream) ;
    void loadIpFinish(Ref* pRef );
    
    
    
private: 
	CREATE_FUNC(LogoLayer);

    
    Sprite * ptempLogoBack;
	Sprite * dianxinLG;
	void disDianXinLG(float dt);
};

#endif

