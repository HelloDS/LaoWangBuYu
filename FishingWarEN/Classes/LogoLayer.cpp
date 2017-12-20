#include "LogoLayer.h"  
#include "SimpleAudioEngine.h"  
#include "GameBegin.h" 
#include "GameData.h"
#include "GameHallLayer.h"

TcpClientSocket *LogoLayer::m_pGameSocket = NULL;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "../cocos2d/external/curl/include/ios/curl/curl.h"
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#endif

string LogoLayer::gHIpStr = "";
unsigned short LogoLayer::gHPortStr = 0;

string LogoLayer::gGIpStr = "";
unsigned short LogoLayer::gGPortStr = 0;

#if(CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include "../cocos2d/external/curl/include/android/curl/curl.h"
#include <sys/stat.h> 
#include <unistd.h>
#include <dirent.h> 
#endif


#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include "..\cocos2d\external\curl\include\win32\curl\curl.h"
#endif

USING_NS_CC;
using namespace std;
 

int LogoLayer::timeTmp[6] = {0};
bool LogoLayer::iskuozhan = false;
bool LogoLayer::moreGameFlag = false;
bool LogoLayer::dengluFlag = false;
char LogoLayer::room = 0;

Scene* LogoLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LogoLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool LogoLayer::init()
{

	// 1. super init first
	if ( !Layer::init() )	
	{
		return false;
	}
    room = 0;
 
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
 
	ptempLogoBack = Sprite::create("logopng.png");
    ptempLogoBack->setRotation(270);
    NotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LogoLayer::loadIpFinish), "loadIpFinish", NULL);
    
    
    //ptempLogoBack->setScale(0.5);
    
	ptempLogoBack->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	addChild(ptempLogoBack);
  
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo minfo;
		jobject jobj;
		if( JniHelper::getStaticMethodInfo(minfo,"org.cocos2dx.cpp.AppActivity","startLoginWithType","(I)V") )
		{	
			cocos2d::log("find startLogin success");
			jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID,34);//3
			minfo.env->DeleteLocalRef(minfo.classID);
		}else
		{
			cocos2d::log("find startLogin fail");
		}
#endif
	cocos2d::log("MoreGameCurl start");

	MoreGameCurl();

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(LogoLayer::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(LogoLayer::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(LogoLayer::onTouchEnded,this);
	listener->setSwallowTouches(true);
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
 
    scheduleOnce(schedule_selector(LogoLayer::loadIpAndPort), 0.5);
    
    
	cocos2d::log("init end");
	return true;
}

void LogoLayer::disDianXinLG(float dt)
{
	dianxinLG->setVisible(false);
	ptempLogoBack->setVisible(true);
  
	scheduleOnce(schedule_selector(LogoLayer::updataDisplay), 0.01);
}

bool LogoLayer::onTouchBegan(Touch* touch, Event* event) 
{  
	return true;
}

void LogoLayer::onTouchEnded(Touch* touch, Event* event)
{

}	

void LogoLayer::onTouchMoved(Touch* touch, Event* event)
{
	 
}

void LogoLayer::updataDisplay(float dt)
{
    
    
    if(UserDefault::getInstance()->getBoolForKey ("FirstGetAccount") == false)
    {
        
        // 取得 Game Sokcet
        TcpClientSocket *pHallSocket = LogoLayer::GetSocket();//this will be activited by receiving info;
        
        // 检查连线状况
        if(pHallSocket->IsConnect() == false)
        {
        }
        
        int tempRecvLength;
        
        char *pRecvBuffer;
        
        pHallSocket->RecvPack(&pRecvBuffer, tempRecvLength);
        fishHead dataHead={0};
        //已处理封包长度
        int tempPackLength = 0;
        
        // 检查有无资料
        if(tempRecvLength > 0)
        {
            fishHead dataHead={0};
            memcpy(&dataHead,pRecvBuffer,sizeof(fishHead));
            dataHead.len=ntohl(dataHead.len);
            if(dataHead.type==FIRSTLOGINBAK)
            {
                FirstLoginBak* FirstLoginBakMsg = (FirstLoginBak*)(pRecvBuffer+sizeof(fishHead));
            
                UserDefault::getInstance()->setIntegerForKey("myid",ntohl(FirstLoginBakMsg->account));
                UserDefault::getInstance()->setBoolForKey("FirstGetAccount",true);
                pHallSocket->CleanRecvBuffer(tempRecvLength);
                pHallSocket->CloseSocket();
            }
        }
        return;
    }
    //π´∏ÊºÏ≤‚
  /*  CURL *curl;
    CURLcode res;
    
    curl=curl_easy_init();
    if(curl)
    {
        
            curl_easy_setopt( curl, CURLOPT_URL, "http://dwby-hk.iyueyo.com/qpby2/iosfanti/ios_gonggao_v6.0.php" QWdfgthyjuik ¬"
); //«Î«Ûµƒµÿ÷∑
69++ 0       curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&GameHallLayer::gonggao_return); //¥¶¿Ìµƒ∫Ø ˝
     08   curl_easy_setopt(curl, CURLOPT_TIMEOUT,2000);
        res=curl_easy_perform(curl);
        if(res!=CURLE_OK)
        {
            log("¡™Õ¯≥¨ ± %i",res);
        }
        curl_easy_cleanup(curl);
    }
    else
    {
        return ;
    }*/
    
    cocos2d::log("updataDisplay start");
    //通过精灵缓存帧对象 添加 gamehall 所需的资源
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common/commons0.plist","common/commons0.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common/commons1.plist","ccommon/ommons1.png");
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common/noyasuo.plist","common/noyasuo.png");
     SpriteFrameCache::getInstance()->addSpriteFramesWithFile("boss/bossfishlist1.plist","boss/bossfishlist1.png");
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("boss/bossfishlist2.plist","boss/bossfishlist2.png");
    
    Vector<SpriteFrame*> sp_vec;
    //手的动画
    if(AnimationCache::getInstance()->getAnimation("hand") == NULL)
    {
        
        
        sp_vec.clear();
        for(int j = 1;j < 3;j++)
        {
            char cTempFishSprite[30];
            sprintf(cTempFishSprite,"hand%d.png" ,j);
            SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
            sp_vec.pushBack(spriteFrame);
        }
        auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
        JiGuangFrameTwo->setDelayPerUnit(1.0f);
        AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "hand");
    }
    //设置齿轮动画
    if(AnimationCache::getInstance()->getAnimation("hall_set") == NULL)
    {
        sp_vec.clear();
        for(int j = 1;j < 4;j++)
        {
            char cTempFishSprite[30];
            sprintf(cTempFishSprite,"hall_menu_shezhi_%d.png" ,j);
            SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
            sp_vec.pushBack(spriteFrame);
        }
        auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
        JiGuangFrameTwo->setDelayPerUnit(0.03f);
        AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "hall_set");
    }
    //立即购买动画
   /* if(AnimationCache::getInstance()->getAnimation("yiyuan_goumai") == NULL)
    {
        sp_vec.clear();
        for(int j = 0;j < 30;j++)
        {
            char cTempFishSprite[30];
            sprintf(cTempFishSprite,"ANG_000%d.png" ,j);
            SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
            sp_vec.pushBack(spriteFrame);
        }
        auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
        JiGuangFrameTwo->setDelayPerUnit(0.035f);
        AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "yiyuan_goumai");
    }*/
    /*
    //大厅的鱼正侧面动画
    int tmpbossnum[6] = {60,51,41,31,31,61};
    
    for(int i = 0; i< 6 ; i++)
    {
        int bossnum = tmpbossnum[i];
        sp_vec.clear();
        for(int j = 1;j < bossnum + 1;j++)
        {
            char cTempFishSprite[30];
            sprintf(cTempFishSprite,"hall_fish_%d (%d).png" ,i + 1,j);
            SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
            sp_vec.pushBack(spriteFrame);
        }
        Animation* fishAnimation = Animation::createWithSpriteFrames(sp_vec);
        fishAnimation->setDelayPerUnit(0.02f);
        
        char cTempFishAniName[40];
        sprintf(cTempFishAniName,"hall_fish_animate_%d",i + 1);
        AnimationCache::getInstance()->addAnimation(fishAnimation, cTempFishAniName);
        
        Animation* fishdAnimation = Animation::createWithSpriteFrames(sp_vec);
        fishdAnimation->setDelayPerUnit(0.002f);
        
        sprintf(cTempFishAniName,"hall_dfish_animate_%d",i + 1);
        AnimationCache::getInstance()->addAnimation(fishdAnimation, cTempFishAniName);
    }
    */
    //大厅的鱼斜侧面动画
    int tmpbossnum1[1] = {10};
    for(int i = 0; i< 1 ; i++)
    {
        int bossnum = tmpbossnum1[i];
        sp_vec.clear();
        for(int j = 1;j < bossnum + 1;j++)
        {
            char cTempFishSprite[30];
            sprintf(cTempFishSprite,"hall_fish_ce_%d_%d.png" ,i + 1,j);
            SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
            sp_vec.pushBack(spriteFrame);
        }
        Animation* fishAnimation = Animation::createWithSpriteFrames(sp_vec);
        fishAnimation->setDelayPerUnit(0.1f);
        
        char cTempFishAniName[40];
        sprintf(cTempFishAniName,"hall_fish_ce_animate_%d",i+1);
        AnimationCache::getInstance()->addAnimation(fishAnimation, cTempFishAniName);
        
        Animation* fishdAnimation = Animation::createWithSpriteFrames(sp_vec);
        fishdAnimation->setDelayPerUnit(0.01f);
        
        sprintf(cTempFishAniName,"hall_dfish_animate_%d",i + 7);
        AnimationCache::getInstance()->addAnimation(fishdAnimation, cTempFishAniName);
    }
    
    //大厅的水母动画
    int tmpbossnum2[1] = {61};
    for(int i = 0; i< 1 ; i++)
    {
        int bossnum = tmpbossnum2[i];
        sp_vec.clear();
        for(int j = 1;j < bossnum + 1;j++)
        {
            char cTempFishSprite[30];
            sprintf(cTempFishSprite,"hall_fish_shang_%d (%d).png" ,i + 1,j);
            SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
            sp_vec.pushBack(spriteFrame);
        }
        Animation* fishAnimation = Animation::createWithSpriteFrames(sp_vec);
        fishAnimation->setDelayPerUnit(0.02f);
        
        char cTempFishAniName[40];
        sprintf(cTempFishAniName,"hall_fish_shang_animate_%d",i+1);
        AnimationCache::getInstance()->addAnimation(fishAnimation, cTempFishAniName);
        
        Animation* fishdAnimation = Animation::createWithSpriteFrames(sp_vec);
        fishdAnimation->setDelayPerUnit(0.002f);
        
        sprintf(cTempFishAniName,"hall_dfish_animate_%d",i + 8);
        AnimationCache::getInstance()->addAnimation(fishdAnimation, cTempFishAniName);
    }
    
    
   
    
    
   
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("button1.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("button2.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("button3.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("button4.mp3"); 
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("zuanpan.mp3"); //
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("LeftAndRightGlueScreenPopDown.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("LeftAndRightGlueScreenPopUp.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("bs_room_xiangq1.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("bs_room_xiangq.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("bs_fapai.mp3");
    
	/*char cTempMuseName[30];
	for(int i = 0; i< 9; i++)
	{
		memset(cTempMuseName,0,sizeof(cTempMuseName));
		sprintf(cTempMuseName,"bgmusic (%d).mp3",i);
		 CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(cTempMuseName);
	}*/
	cocos2d::log("updataDisplay end");
    
    std::string mimi = "mimi.zip";
    std::string mimiwritelujin =  FileUtils::getInstance()->getWritablePath()+mimi;
    std::string mimiziplujin = FileUtils::getInstance()->fullPathForFilename("mimi.zip");
    
    Data data = FileUtils::getInstance()->getDataFromFile(mimiziplujin);
    if (!data.isNull())
    {
        cocos2d::log("datehave");
    }
    
    
    //从zip中读取图片数据
    FILE *fpTemp = fopen(mimiwritelujin.c_str(),"r");
    if(fpTemp)
    {
        
        fclose(fpTemp);
        
    }
    else
    {
        unsigned long len = 0;
        unsigned char *datazip = NULL;
        datazip = (unsigned char*)malloc(sizeof(unsigned char) * data.getSize());
        memcpy(datazip, data.getBytes(),  data.getSize());
        if(datazip != NULL)
        {
            cocos2d::log("zipcpy");
            
            FILE *fp = fopen(mimiwritelujin.c_str(),"w+");
            fwrite(datazip,sizeof(char), data.getSize(),fp);
            fclose(fp);
            delete []datazip;
            datazip = NULL; 
        } 
        
    }
    

    this->removeAllChildrenWithCleanup(true);
    this->unscheduleAllSelectors();
    
    Scene* scene = GameBegin::createScene();
    Director::getInstance()->replaceScene(scene);
 
}

void LogoLayer::update(float dt)
{
 
}


bool LogoLayer::initDeviceNo(char * deviceNo)
{
 
	if(deviceNo != "-")
	{
		cocos2d::log("success:phonedeviceNo is : %s",deviceNo);
		UserDefault::getInstance()->setStringForKey("DeviceNo",deviceNo);
		UserDefault::getInstance()->flush();
		return true;
	}
	else
	{
		cocos2d::log("fail:phonedeviceNo is : %s",deviceNo);
	}
	return false;
}

size_t  LogoLayer::huidiaohanshu(uint8_t *buffer,size_t size,size_t nmemb,void *stream)
{
	//打印收到的数据
	//log((const char *)buffer);																	
	char tmp[30]="";
	int m = 0;
	int i=0;
	int j=0;

	while(buffer[i]!='\0')
	{
		char c = buffer[i];
		if(c=='-'||c==' '||c==':')
		{
			timeTmp[m] = std::atoi(tmp);
			memset(tmp,0,sizeof(tmp));
			j=0;
			m++;
			
		}
		else
			{
				tmp[j] = c;
				j++;
			}
		i++;
	}

 	timeTmp[m] = std::atoi(tmp);	
	memset(tmp,0,sizeof(tmp));
	timeTmp[0] -= 1900;
	 
	//返回数据长度
	size_t sizes = size*nmemb;

	return sizes;
}

void LogoLayer::curlTime()
{
	CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
	if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "http://dwby-hk.iyueyo.com/qpby2/MMpay/Time.php");
		curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&huidiaohanshu);
		curl_easy_setopt(curl, CURLOPT_POST, true);                     //启用POST提交 
		curl_easy_setopt(curl,CURLOPT_TIMEOUT,1000);
		curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L); 
		curl_easy_setopt(curl,CURLOPT_POSTFIELDS,"R = 10");

        res=curl_easy_perform(curl);
        if(res!=CURLE_OK)
        {
            log("联网超时 %i",res);		
        } 
        curl_easy_cleanup(curl);
 
    }
    else
    {
        log("返回错误");
        return ;
    }
}

size_t  LogoLayer::moregame_call(uint8_t *buffer,size_t size,size_t nmemb,void *stream)
{
	//打印收到的数据
	//log((const char *)buffer);																	
 
	if(buffer[0]=='1')
	{
		moreGameFlag = true;
        UserDefault::getInstance()->setIntegerForKey("ios_huifeiFlag", 1);
        UserDefault::getInstance()->flush();
    }else
    {
        UserDefault::getInstance()->setIntegerForKey("ios_huifeiFlag", 0);
        UserDefault::getInstance()->flush();
    }
    
    if(buffer[1]=='1')
    {
        dengluFlag = true;
        UserDefault::getInstance()->setIntegerForKey("ios_dengluFlag", 1);
        UserDefault::getInstance()->flush();
    }else
    {
        UserDefault::getInstance()->setIntegerForKey("ios_dengluFlag", 0);
        UserDefault::getInstance()->flush();
    }
 
	//返回数据长度
	size_t sizes = size*nmemb;

	return sizes;
}

void LogoLayer::MoreGameCurl()
{
	CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
	if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "http://dwby-hk.iyueyo.com/qpby2/iosfanti/iosEn_denglu_flag_googlev6.3.php");
		curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&moregame_call);
		curl_easy_setopt(curl, CURLOPT_POST, true);                     //启用POST提交 
		curl_easy_setopt(curl,CURLOPT_TIMEOUT,100);
		curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L); 
		curl_easy_setopt(curl,CURLOPT_POSTFIELDS,"R = 10");

        res=curl_easy_perform(curl);
        if(res!=CURLE_OK)
        {
            log("联网超时 %i",res);		
        } 
        curl_easy_cleanup(curl);
 
    }
    else
    {
        log("返回错误");
        return ;
    }
}

time_t LogoLayer::getTime()
{
	curlTime();
	struct tm nowTime;

	nowTime.tm_year = timeTmp[0];
	nowTime.tm_mon = timeTmp[1] - 1;
	nowTime.tm_mday = timeTmp[2];
	nowTime.tm_hour = timeTmp[3];
	nowTime.tm_min = timeTmp[4];
	nowTime.tm_sec = timeTmp[5];
	//nowTime.tm_isdst = 1;
	nowTime.tm_wday = 0;
	nowTime.tm_yday = 0;

	time_t shijian =  mktime(&nowTime) + 28800;//因为之后用的是gmtime  所以这里加了8小时
	return shijian;
}

time_t LogoLayer::getHBTime()
{
	time_t currentTime;
	time(&currentTime);
 
	time_t shijian =  currentTime - 365*24*60*60*(2014 - 1970) + 28800  ;//因为之后用的是gmtime  所以这里加了8小时
	return shijian;
}




void LogoLayer::loadIpAndPort(float dt)
{
    CURL *curl;
    CURLcode res;
    std::string cc;
    curl=curl_easy_init();
    
    if(curl)
    {
        curl_easy_setopt( curl, CURLOPT_URL, "http://dwby-hk.iyueyo.com/qpby2/GooglePay/LoginIpAndPortyw.php"); //«Î«Ûµƒµÿ÷∑
        
        curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&loadIpAndPortCallback); //¥¶¿Ìµƒ∫Ø ˝
        res=curl_easy_perform(curl);
        if(res!=CURLE_OK)
        {
            
        }
        curl_easy_cleanup(curl);
    }
}

size_t LogoLayer::loadIpAndPortCallback( uint8_t *buffer,size_t size,size_t nmemb,void *stream )
{
    cocos2d::log("loadIpAndPortCallback  = %s ", (const char *)buffer);
    
    std::string tmpStr;
    std::stringstream bufferSs;
    
    bufferSs << buffer;
    bufferSs >> tmpStr;
    
    cocos2d::log("tmpStr  = %s ", tmpStr.c_str());
    
    std::string::iterator strIt = tmpStr.begin();
    
    std::stringstream ss;
    
    bool isGameIp = false;  //为true时读取游戏IP端口
    for (strIt; strIt != tmpStr.end(); strIt++)
    {
        
        
        if (*strIt == ',' )
        {
            if (isGameIp)
            {
                ss >> gGIpStr;
            }
            else
            {
                ss >> gHIpStr;
            }
            
            ss.clear();
        }
        else if (*strIt == 'H' )
        {
            ss >> gHPortStr;
            ss.clear();
            
            isGameIp = true;
        }
        else if (*strIt == 'G')
        {
            ss >> gGPortStr;
            ss.clear();
        }
        else
        {
            ss << *strIt;
        }
    }
    // 	gGIpStr = "47.89.27.99";
    // 	gHIpStr = "47.89.27.99";
    
    cocos2d::log("gIpStr  = %s ", gHIpStr.c_str());
    cocos2d::log("gPortStr  = %d ", gHPortStr);
    cocos2d::log("gGIpStr  = %s ", gGIpStr.c_str());
    cocos2d::log("gGPortStr  = %d ", gGPortStr);
    
    size_t sizes = size*nmemb;
    
    NotificationCenter::sharedNotificationCenter()->postNotification("loadIpFinish",NULL);
    
    return sizes;
}



void LogoLayer::loadIpFinish( Ref* pRef )
{
    scheduleOnce(schedule_selector(LogoLayer::tcpRequestTimer), 0.01);
}


void LogoLayer::tcpRequestTimer( float dt )
{
    //取得Room Sokcet
    TcpClientSocket *ptempHallSocket = LogoLayer::GetSocket();
    ptempHallSocket->CloseSocket();
    
    ptempHallSocket->ConnectServer((char*)LogoLayer::gHIpStr.data(), LogoLayer::gHPortStr);
    
    if(ptempHallSocket->IsConnect() == false)
    {
        
        
        
    }
    else
    {
        
        
        if(UserDefault::getInstance()->getBoolForKey ("FirstGetAccount") == false)
        {
            FirstLoginSend LoginFirstSendMsg;
            LoginFirstSendMsg.applyAccount = true;
            ptempHallSocket->SendMsgToSocket(&LoginFirstSendMsg, FIRSTLOGINSEND, sizeof(FirstLoginSend));
        }
        
    }
    
    
    
    
    schedule(schedule_selector(LogoLayer::updataDisplay), 0.01);
    cocos2d::log("init end");
}

TcpClientSocket *LogoLayer::GetSocket(void)
{
    if(m_pGameSocket == NULL)
    {
        m_pGameSocket = new TcpClientSocket();
    }
    return m_pGameSocket;
}



