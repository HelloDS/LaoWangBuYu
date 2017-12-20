#ifndef _GAMEBEGIN_H_
#define _GAMEBEGIN_H_

#include"cocos2d.h"
#include "cocos-ext.h"
#include "LogoLayer.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#ifdef __cplusplus
extern "C"{
#endif

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_qiehanSuc(JNIEnv * env, jclass ,jstring device); 
JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_dengluSuc(JNIEnv * env, jclass ,jstring device); 
JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_dengluFail(JNIEnv * env, jclass ); 
 
#ifdef __cplusplus
}
#endif

#endif

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

#define ANNIULAYER 100
class GameBegin : public cocos2d::Layer,public cocos2d::ui::EditBoxDelegate
{
public:
    //************* 登录系统 ******************
    
    static size_t log_poss(uint8_t *buffer,size_t size,size_t nmemb,void *stream);
    static void cal_lastTime();
    
    void login_system(); 
    void login_cancel();
    
    void GameBiginInit();
    static char cGetDev;
    
    
    static bool isPhoneNum(const std::string& strIp);
    
    virtual void editBoxReturn(cocos2d::extension::EditBox *editBox);
    
    static size_t  login_poss(uint8_t *buffer,size_t size,size_t nmemb,void *stream);
    static bool login_success;
    static bool login_fail;
    static int  login_fail_flag;
    static bool login_xiaxian; 
    
    void get_deviceNo(float dt);
	void get_Test(float dt);
    static size_t deviceNo_poss(uint8_t *buffer,size_t size,size_t nmemb,void *stream);
    
   
    void get_devi_fail();
    void get_devi_succ();
    void reget_deviceNo();
    //**************  end   ************************
    int wait_time;
    static int gb_fish_num[12];
    
    static void removeSouce(int i);
    
 
    
    Sprite * hallBackground;
    float yutime;
    void randomFish();
	 
	static cocos2d::Scene* createScene();

    static char ifOldZhangHao;
	virtual bool init(); 
	//virtual void onExit();
	Menu* kaishiMenu;
    
    void fanhuiGame();//返回游戏大厅
    void pinglun();//返回游戏大厅
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 

	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);

	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 
	
	void menuGo(Ref* pSender);
	void update(float dt);

	void afterCaptured(bool succeed, const std::string& outputFile); // 屏幕截图

	void gameEmail(Ref* pSender);					//邮箱处理

	void gameSet(Ref* pSender);						//设置处理

	void gameHelp(Ref* pSender);					//帮助管理

	void gameExit(Ref* pSender);					//退出管理

	void queding();

	void caihongFade();

	void jieping(float dt);


	//登录
	static void baidu_denglu(int i);
	static size_t  possText(uint8_t *buffer,size_t size,size_t nmemb,void *stream);

	static void baidu_qiehuan();
	static size_t  possText1(uint8_t *buffer,size_t size,size_t nmemb,void *stream);

    static char cjingxipingbi;
	static float  scaleYNum;


	static string baiduID;
	static bool inituserid(char * deviceNo , int i);

	static int playSound(string soundPath); //播放声音
	static void buttonSound();				//按钮点击声音
	static void playMusic(string soundPath,char cType = 0);//播放音乐
	static void stopMusic();//播放音乐

	static bool canPlaySound;				//是否播放声音
	static bool canPlayMusic;				//是否播放音乐
	static bool dengluCheng;				//登录成功
	static bool dengluShi;					//失败

	static void setFileData(string tmpPath,int tmpIntData); //写文件操作
	static int getFileData(string tmpPath);					//读文件操作

	static int WangW[6];
	static int  musicNum;

	static bool isJinRu;  //是否进入场景
	static int curScene;  //1,游戏开始  2，大厅 3 远征  4，场景内
	//void jinruGame(); //
    
    static bool dengluios;   //ios数据库登录状态
    static int dengluint;	//ios返回消息
    
    static bool is_ios_yueyu;     //是否为越狱版本
	
    void ooooo(float dt);
private:
	
	CREATE_FUNC(GameBegin); 
	Sprite * GB_taiyang;
	Sprite * GB_logo;  
	//Sprite * GB_guangmang;
	Sprite * GB_haiou1;
	Sprite * GB_haiou2;
	Sprite * GB_haiou3;
	Sprite * GB_kaishi;
	Sprite * GB_kaishid;
	Size visibleSize ;
	Point origin ;
	bool baiyun1Zeng;
	bool baiyun2Zeng;
 
	float ho2_x;
	float ho2_y;
	int ho2_jiaodu;
	int fangjian;
};

class GameLogin : public cocos2d::Layer,public cocos2d::ui::EditBoxDelegate
{
public:
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    void init_zhuce();
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    virtual void editBoxReturn(cocos2d::ui::EditBox *editBox);
    static size_t  possText(uint8_t *buffer,size_t size,size_t nmemb,void *stream);//服务器请求回调函数
    
    CREATE_FUNC(GameLogin);
     
    void denglu();
    void qingchu();
    
    void exit();
    
private:
    
    Size visibleSize ;
    Point origin ;
    cocos2d::ui::Scale9Sprite  * controlBg;
    
    cocos2d::ui::EditBox * id_kuang;
    cocos2d::ui::EditBox * pwd_kuang;
    
    char name_so[36];
    MenuItemSprite * zhuceItem;
    MenuItemSprite * dengluItem;
    MenuItemSprite * suijiItem;
    
    
    cocos2d::ui::Scale9Sprite  * controlBg1;
    cocos2d::ui::EditBox * id_kuang1;
    cocos2d::ui::EditBox * pwd_kuang1;
    cocos2d::ui::EditBox * pwd_kuang2;
    
};

#endif

