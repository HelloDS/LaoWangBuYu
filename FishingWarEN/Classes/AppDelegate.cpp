#include "AppDelegate.h" 
#include "LogoLayer.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "GameBegin.h"
#include "GameHallLayer.h"


#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "Adjust\Adjust2dx.h"
#include "Adjust\AdjustEvent2dx.h"
#endif


USING_NS_CC;


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}
void AppDelegate::initGLContextAttrs(){
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

//wfios007
 
bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    
    

    
    
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }


#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	std::string appToken = "fwd5btdcvklc";
	std::string environment = AdjustEnvironmentProduction2dx;
	AdjustConfig2dx config = AdjustConfig2dx(appToken,environment);
	config.setLogLevel(AdjustLogLevel2dxVerbose);
	Adjust2dx::start(config);
#endif

    time_t current_t;
    time(&current_t);
    GameScene::houtaiTime = current_t;
    GameScene::qiantaiTime = current_t;

  

    
 

    // turn on display FPS
    director->setDisplayStats(false);
	  
	Size TempSize = glview->getFrameSize();

	float resolutionRate=TempSize.width/TempSize.height;
 
	 glview->setDesignResolutionSize(1024, 768, kResolutionFixedWidth);

	 
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);


    // create a scene. it's an autorelease objects
    auto scene = LogoLayer::createScene();

    // run
    director->runWithScene(scene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
	
	if(GameScene::cGameType == 1)
	{
		time_t current_t;
		time(&current_t);
		GameScene::houtaiTime = current_t;		//«–µΩ∫ÛÃ®µƒµ±«∞ ±º�?
	}
     
    
    GameBegin::cal_lastTime();
	cocos2d::log("qiedao  houtai, time = %ld" , GameScene::houtaiTime);

    // if you use SimpleAudioEngine, it must be pause
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
	if(GameScene::cGameType == 1)
	{
		time_t current_t;
		time(&current_t);
		GameScene::qiantaiTime = current_t;		//«–µΩ∫ÛÃ®µƒµ±«∞ ±º�?
		if(GameScene::qiantaiTime > GameScene::houtaiTime + 600)
		{
			GameScene::isduankai = true;
		}
	}
    
    time_t hb_last_lq_time = GameBegin::getFileData("hb_last_lq_time.txt");
    
    
    time_t cur_time;
    time(&cur_time);
    //2 * 3600
    
    if(hb_last_lq_time == 0 || hb_last_lq_time +2 * 3600 <  cur_time)////第一次进入游�?或�?距离上次领取红包已经过了两小�? 均可领取红包
    {
        GameHallLayer::hall_hb_times = 0;
    }else//否则显示计时�?
    {
        GameHallLayer::hall_hb_times = 7200 - (cur_time - hb_last_lq_time);
        if(GameHallLayer::hall_hb_times < 0 || GameHallLayer::hall_hb_times > 7200)
        {
            GameHallLayer::hall_hb_times = 7200;
        }
    }
    
    UserDefault::getInstance()->setIntegerForKey("start_login_time",cur_time);
    UserDefault::getInstance()->flush();
    
	cocos2d::log("qiedao  houtai, time = %ld" , GameScene::qiantaiTime);
	
    // if you use SimpleAudioEngine, it must resume here
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
