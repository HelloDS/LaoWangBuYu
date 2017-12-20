#include "LoadRes.h"  
#include "SimpleAudioEngine.h" 
#include "FishLayer.h"
#include "GameScene.h"
#include "StaticData.h" 
#include "Gongxi.h"
#include "FishRandSwatch.h"
#include "AllRobot.h"
#include "GameBegin.h" 
#include "GameHallLayer.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "../cocos2d/external/curl/include/ios/curl/curl.h"
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#endif


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

bool LoadRes::bFirstFanWei = false;
bool LoadRes::bFirstJiaSu = false;
bool LoadRes::bFirstJiGuang = false;
bool LoadRes::bFirtDingPing = false;
int LoadRes::hasWifi = -1;
int LoadRes::RoomType = 0;
Scene* LoadRes::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadRes::create();
	scene->addChild(layer);

	return scene;
}

bool LoadRes::onTouchBegan(Touch* touch, Event* event)
{  
	int d =3;
return true;
}

void LoadRes::onTouchMoved(Touch* touch, Event* event)
{

 int df = 34;

}

void LoadRes::onTouchEnded(Touch* touch, Event* event)
{ 
	int a =34;
}

void LoadRes::onEnter()
{
    Node::onEnter();
    GameBegin::removeSouce(1);
    GameBegin::removeSouce(2);
}

bool LoadRes::init()
{

	// 1. super init first
	if ( !Layer::init() )	
	{
		return false;
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(LoadRes::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(LoadRes::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(LoadRes::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触摸
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);


	visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	fishNum[0] = 1;fishNum[1] = 1;fishNum[2] = 1;fishNum[3] = 1;fishNum[4] = 1;fishNum[5] = 2;fishNum[6] = 2;fishNum[7] = 1;fishNum[8] = 1;fishNum[9] = 2;fishNum[10] = 2;fishNum[11] = 3;
	BSfishNum[0] = 1;BSfishNum[1] = 1;BSfishNum[2] = 1;BSfishNum[3] = 1;
 
	iRoomType = RoomType;
	srand((unsigned)time(NULL)); 

	Vector<SpriteFrame*> sp_vec;    

	char RoomTypeFlag1[20];
	sprintf(RoomTypeFlag1,"Room%dHas",RoomType+1);
	

	string text = ""  ;
	int iRand = CCRANDOM_0_1()*70;
	if(iRand < 10)
	{
		text = GAME_DATA_STRING("tips1");
	}
	else if(iRand <20)
	{
		text = GAME_DATA_STRING("tips2");
	}
	else if(iRand <30)
	{
		text = GAME_DATA_STRING("tips3");
	}
	else if(iRand <40)
	{
		text = GAME_DATA_STRING("tips4");
	}
	else if(iRand <50)
	{
		text = GAME_DATA_STRING("tips5");
	}
	else if(iRand <60)
	{
		text = GAME_DATA_STRING("tips6");
	}
	else if(iRand <70)
	{
		text = GAME_DATA_STRING("tips7");
	}



	auto wordTTF = LabelTTF::create(text,GameHallLayer::wordKind,26);
	wordTTF->setColor(Color3B(233,227,205));
	wordTTF->setPosition(Point(visibleSize.width/2,visibleSize.height*0.3));
	this->addChild(wordTTF,1000); 
 
	auto  SprLoad = Sprite::createWithSpriteFrameName("loadsmall.png");
	this->addChild(SprLoad);
	SprLoad->setPosition(Vec2(visibleSize.width*0.5,visibleSize.height*0.4)); 
 

	LoadBar = ControlSlider::create("img/jindutiao.png","img/jindutiao1.png","img/33.png");
	LoadBar->setPosition(Point(visibleSize.width/2,visibleSize.height*0.15));
	LoadBar->setMinimumValue(0.0f);
	LoadBar->setMaximumValue(100.0f);
	LoadBar->setValue(0.0f);
	this->addChild(LoadBar,100);
    
    //随机鱼的种类1-6
    char hallCharTemp[100];
    int fish_kind = (int)(CCRANDOM_0_1() * 100000) % 2 + 1;
    //fish_kind = 8;
    if(fish_kind ==2)//水母
    {
        sprintf(hallCharTemp,"hall_fish_shang_%d (1).png",1);
        auto fish_sp = Sprite::createWithSpriteFrameName(hallCharTemp);
        this->addChild(fish_sp,10);
        
        sprintf(hallCharTemp,"hall_fish_shang_animate_%d",1);
        fish_sp->runAction(RepeatForever::create( Animate::create(AnimationCache::getInstance()->getAnimation(hallCharTemp))));
        fish_sp->setPosition(Vec2(visibleSize.width/2 , visibleSize.height * 0.55));
        
    }
    else//斜鱼
    {
        sprintf(hallCharTemp,"hall_fish_ce_%d_1.png",1);
        auto fish_sp = Sprite::createWithSpriteFrameName(hallCharTemp);
        fish_sp->setPosition(Vec2(visibleSize.width/2 , visibleSize.height * 0.55));
        this->addChild(fish_sp,10);
        
        sprintf(hallCharTemp,"hall_fish_ce_animate_%d",1);
        fish_sp->runAction(RepeatForever::create( Animate::create(AnimationCache::getInstance()->getAnimation(hallCharTemp))));
    }

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bosscome.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bosscome2.mp3");
	if(UserDefault::getInstance()->getBoolForKey("firstdingping") == false)
	{
		bFirtDingPing = true;
	}
	if(UserDefault::getInstance()->getBoolForKey("firstjiasu") == false)
	{
		bFirstJiaSu = true;
	}
	if(UserDefault::getInstance()->getBoolForKey("firstfanwei") == false)
	{
		bFirstFanWei = true;
	}
	if(UserDefault::getInstance()->getBoolForKey("firstjiguang") == false)
	{
		bFirstJiGuang = true;
	}
	bLoadRes =false;
	iLoadNum = 0;

	if(iRoomType>2 && iRoomType < 20)
	{
		
		if(!UserDefault::getInstance()->getBoolForKey(RoomTypeFlag1))
		{
			schedule(schedule_selector(LoadRes::updataAddRes),0.02f);
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)		
			JniMethodInfo minfo;
			jobject jobj;
			if( JniHelper::getStaticMethodInfo(minfo,"org.cocos2dx.cpp.AppActivity","startLoginWithType","(I)V") )
			{	
				jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID,100);
				minfo.env->DeleteLocalRef(minfo.classID);		
			} 
#endif
			firstInLabel = LabelTTF::create(GAME_DATA_STRING("firstInTip"),GameHallLayer::wordKind,26);
			firstInLabel->setColor(Color3B(255,242,0));
			firstInLabel->setPosition(Point(visibleSize.width/2,visibleSize.height*0.8));
			this->addChild(firstInLabel,1000); 
			this->scheduleUpdate();
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)		
		schedule(schedule_selector(LoadRes::updataAddRes),0.02f);
#endif
		}else
		{
			schedule(schedule_selector(LoadRes::updataAddRes),0.02f);
		}
	}
else
	{
		//鱼游动	
		schedule(schedule_selector(LoadRes::updataAddRes),0.02f);
	}
	
	return true;
}

void LoadRes::update(float dt)
{
	if(hasWifi == 1)
	{
 
		hasWifi = -1;
		schedule(schedule_selector(LoadRes::updataAddRes),0.02f);
	}

	if(hasWifi == 0)
	{
		hasWifi = -1;
		this->unschedule(schedule_selector(LoadRes::updataAddRes));

		auto gongxi = Gongxi::create(99,GAME_DATA_STRING("firstInTip4"));
		gongxi->setPosition(Point::ZERO);
		this->addChild(gongxi,1000,1000);

		auto quedingSprite =  Sprite::createWithSpriteFrameName("XR_qd.png");
		auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(LoadRes::jixuGame,this));
		auto btnMenu = Menu::create(quedingItem,nullptr);
		btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
		gongxi->getChildByTag(1)->addChild(btnMenu,100);
 
		auto xquedingItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("hall_menu_X.png"),Sprite::createWithSpriteFrameName("hall_menu_X_d.png"), CC_CALLBACK_0(LoadRes::fanhuiGame,this));
		auto xbtnMenu = Menu::create(xquedingItem,nullptr);
		xbtnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width - 10,gongxi->getChildByTag(1)->getContentSize().height - 10));
		gongxi->getChildByTag(1)->addChild(xbtnMenu,100);
	}

	if(hasWifi == -1)
	{
		//schedule(schedule_selector(LoadRes::updataAddRes),0.02f);
	}
}

void LoadRes::jixuGame()
{
	this->getChildByTag(1000)->setVisible(false);
	iLoadNum-- ;
	schedule(schedule_selector(LoadRes::updataAddRes),0.02f);
}

void LoadRes::fanhuiGame()
{
	this->removeAllChildrenWithCleanup(true);
	this->unscheduleAllSelectors(); 

	auto scene = GameHallLayer::createScene();
	Director::getInstance()->replaceScene(scene);
}

bool LoadRes::loadResource(int room)
{
	cocos2d::log("wo shou kai shi");
	
	string fishlujin = FileUtils::getInstance()->getWritablePath();//文件下载路劲
	FILE *outfile;
	char sceneName[20];
	sprintf(sceneName,"scene%d.zip",room);


	CURL *curl;
	CURLcode res;
	curl=curl_easy_init();
	
	if(curl)
	{
		outfile = fopen((fishlujin+sceneName).c_str(),"wb"); 
		switch(room)
		{
		case 4:{
			curl_easy_setopt( curl, CURLOPT_URL, "http://oc537zw9x.bkt.clouddn.com/scene4.zip"); //请求的地址4
			   }
			   break;
		case 5:{
			curl_easy_setopt( curl, CURLOPT_URL, "http://oc537zw9x.bkt.clouddn.com/scene5.zip"); //请求的地址4
			   }
			   break;
		case 6:{
			curl_easy_setopt( curl, CURLOPT_URL, "http://oc537zw9x.bkt.clouddn.com/scene6.zip"); //请求的地址4
			   }
			   break;
		case 7:{
			curl_easy_setopt( curl, CURLOPT_URL, "http://oc537zw9x.bkt.clouddn.com/scene7.zip"); //请求的地址4
			   }
			   break;
		case 8:{
			curl_easy_setopt( curl, CURLOPT_URL, "http://oc537zw9x.bkt.clouddn.com/scene8.zip"); //请求的地址4
			   }
			   break;
		case 9:{
			curl_easy_setopt( curl, CURLOPT_URL, "http://oc537zw9x.bkt.clouddn.com/scene9.zip"); //请求的地址4
			   }
			   break;
		case 10:{
			curl_easy_setopt( curl, CURLOPT_URL, "http://oc537zw9x.bkt.clouddn.com/scene10.zip"); //请求的地址4
				}
				break;
		case 11:{
			curl_easy_setopt( curl, CURLOPT_URL, "http://oc537zw9x.bkt.clouddn.com/scene11.zip"); //请求的地址4
				}
				break;
		case 12:{
			curl_easy_setopt( curl, CURLOPT_URL, "http://oc537zw9x.bkt.clouddn.com/scene12.zip"); //请求的地址4
				}
				break;
		case 66:{
			curl_easy_setopt( curl, CURLOPT_URL, "http://oc537zw9x.bkt.clouddn.com/scene66.zip"); //请求的地址4
				}
				break;
		default:log("canshu error");break;
		}		
		if(outfile)  
		{  
			curl_easy_setopt(curl, CURLOPT_FILE, outfile); 
		}
		curl_easy_setopt(curl , CURLOPT_WRITEFUNCTION, &callbackFunction);
		curl_easy_setopt(curl,CURLOPT_TIMEOUT,30L);
		res=curl_easy_perform(curl);
		if(res!=CURLE_OK)
		{
			log("联网超时 %i",res);
			this->unschedule(schedule_selector(LoadRes::updataAddRes));
			return false;
		} 		 
		curl_easy_cleanup(curl);
	}
	else
	{
		log("curl is null");
		this->unschedule(schedule_selector(LoadRes::updataAddRes));
		return false;
	}
	{
		fclose(outfile); 
		if(room == 66)
		{
			jiazaiChange();
		}
		else
		{
			jiazaiPlist(room);
		}
		
	}
	return true;
}

size_t LoadRes::callbackFunction(void *buffer,size_t size,size_t nmemb,FILE *stream)
{
	size_t written = fwrite(buffer, size, nmemb, (FILE *)stream);  
	return written; 
}
 
void LoadRes::jiazaiChange( )
{
	
	//声明要用的变量
	char  token[20];
	sprintf(token,"scene%d.zip",iRoomType+1);
	string fullminizip =  FileUtils::getInstance()->getWritablePath()+token; 

	//下载fishlist文件
	for(int i = 0; i< 2; i++)
	{	
		ssize_t fZize ;
		unsigned char * plistBuf = NULL;  
		unsigned char * pngBuf = NULL;  

		char bossPlistName[30];
		char bossPngName[30];

		sprintf(bossPlistName,"bossfishlist%d.plist",i+1);
		sprintf(bossPngName,"bossfishlist%d.png",i+1);
			
		//下载plist文件
		plistBuf =FileUtils::getInstance()->getFileDataFromZip(fullminizip,bossPlistName,&fZize);//获取.dat文件内容
		FILE * outPlistFile = fopen((FileUtils::getInstance()->getWritablePath()+bossPlistName).c_str(),"wb");
		if(outPlistFile)
		{
			fwrite(plistBuf,1,fZize,outPlistFile);
		}
		fclose(outPlistFile);	

		//下载png文件
		pngBuf =FileUtils::getInstance()->getFileDataFromZip(fullminizip,bossPngName,&fZize);//获取png文件内容
		unsigned char* newpngBuf = new unsigned char[fZize];
		if(pngBuf!=NULL&&fZize>0)
		{
			for (int i = 0; i<fZize; i++) {
				newpngBuf[i] = pngBuf[i];
			}
			FILE * outPngFile = fopen((FileUtils::getInstance()->getWritablePath()+bossPngName).c_str(),"wb+");
			if(outPngFile)
			{
				fwrite(newpngBuf,1,fZize,outPngFile);
			}
			fclose(outPngFile);
		}
	}
	 	

}

void LoadRes::jiazaiPlist(int room)
{
	
	//声明要用的变量
	char  token1[20];
	sprintf(token1,"scene%d.zip",room);
	string fullminizip =  FileUtils::getInstance()->getWritablePath()+token1; 

	int bossNumF = 1;
	int fishNumF = fishNum[room-1];
	//下载scenebg.png
	ssize_t fZize1;
	char bossBGPngName1[30];
	sprintf(bossBGPngName1,"scene%dBG.jpg",room);
	unsigned char * pngBossBuf1 = NULL;  

	pngBossBuf1 =FileUtils::getInstance()->getFileDataFromZip(fullminizip,bossBGPngName1,&fZize1);//获取png文件内容
	unsigned char* newpngBuf1 = new unsigned char[fZize1];
	if(pngBossBuf1!=NULL&&fZize1>0)
	{
		for (int i = 0; i<fZize1; i++) {
			newpngBuf1[i] = pngBossBuf1[i];
		}
		FILE * outPngFile1 = fopen((FileUtils::getInstance()->getWritablePath()+bossBGPngName1).c_str(),"wb+");
		if(outPngFile1)
		{
			fwrite(newpngBuf1,1,fZize1,outPngFile1);
		}
		fclose(outPngFile1);
	}

	 

	//下载fishlist文件
	for(int i = 0; i< fishNumF; i++)
	{	
		ssize_t fZizef ;
		unsigned char * plistBuff = NULL;  
		unsigned char * pngBuff = NULL;  

		char bossPlistNamef[30];
		char bossPngNamef[30];

		sprintf(bossPlistNamef,"scene%dfishlist%d.plist",room,i+1);
		sprintf(bossPngNamef,"scene%dfishlist%d.png",room,i+1);
			
		//下载plist文件
		plistBuff =FileUtils::getInstance()->getFileDataFromZip(fullminizip,bossPlistNamef,&fZizef);//获取.dat文件内容
		FILE * outPlistFilef = fopen((FileUtils::getInstance()->getWritablePath()+bossPlistNamef).c_str(),"wb");
		if(outPlistFilef)
		{
			fwrite(plistBuff,1,fZizef,outPlistFilef);
		}
		fclose(outPlistFilef);	

		//下载png文件
		pngBuff =FileUtils::getInstance()->getFileDataFromZip(fullminizip,bossPngNamef,&fZizef);//获取png文件内容
		unsigned char* newpngBuff = new unsigned char[fZizef];
		if(pngBuff!=NULL&&fZizef>0)
		{
			for (int i = 0; i<fZizef; i++) {
				newpngBuff[i] = pngBuff[i];
			}
			FILE * outPngFilef = fopen((FileUtils::getInstance()->getWritablePath()+bossPngNamef).c_str(),"wb+");
			if(outPngFilef)
			{
				fwrite(newpngBuff,1,fZizef,outPngFilef);
			}
			fclose(outPngFilef);
		}
	}

	//下载info.plist
	ssize_t fZize3 ;
	unsigned char * plistBuf3 = NULL;  
	char infoPlistName[30];

	sprintf(infoPlistName,"scene%dfishinfo.plist",room);
	plistBuf3 =FileUtils::getInstance()->getFileDataFromZip(fullminizip,infoPlistName,&fZize3);//获取.dat文件内容
	FILE * outPlistFile = fopen((FileUtils::getInstance()->getWritablePath()+infoPlistName).c_str(),"wb");
	if(outPlistFile)
	{
		fwrite(plistBuf3,1,fZize3,outPlistFile);
	}
	fclose(outPlistFile);	

}



void LoadRes::getrank()
{
   
    
    string deviceId = UserDefault::getInstance()->getStringForKey("DeviceNo");
    
 
    CURL *curl;
    CURLcode res;
    std::string cc;
    curl=curl_easy_init();
    char postFields[300];
    
    
    int itermd=GameHallLayer::RoomType-89;
    sprintf(postFields," &deviceId=%s&roomtype=%d",deviceId.c_str(),itermd);
    
    log("postfile = %s",postFields);
    if(curl)
    {
        curl_easy_setopt( curl, CURLOPT_URL, "http://buyu2.iyueyo.com/qpby2/ios/login/huoqu_huafei.php");
        curl_easy_setopt(curl, CURLOPT_POST, true);
        curl_easy_setopt(curl,CURLOPT_TIMEOUT,3000);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields);
        curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&getrankcall);
        res=curl_easy_perform(curl);
        if(res!=CURLE_OK)
        {
            //log("curl result = %s",res);
            
        }
        curl_easy_cleanup(curl);
    }
    else
    {
        //log("curl fail");
        return ;
    }
}

size_t LoadRes::getrankcall(uint8_t *buffer,size_t size,size_t nmemb,void *stream)
{
    cocos2d::log("补单返回数据： %s ", (const char *)buffer);
    
    string tmpstring = (const char *)buffer;
    if(tmpstring == "deviceidkong")
    {
        
        AllRobot ::iRobotWinNum = 100;
    }
    else
    {
        AllRobot ::iRobotWinNum = atoi(tmpstring.c_str());
        
    }
    
    size_t sizes = size*nmemb;
    return sizes;
}

void LoadRes::updataAddRes(float dt)
{

	if(iLoadNum == 0)
	{
       
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("scene/bullet_comp.plist","scene/bullet_comp.png");
        
		LoadBar->setValue(10.0f);
	 
       
		cocos2d::log("0");
	}
	else if(iLoadNum == 1)
	{
        
		LoadBar->setValue(11);
       
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("scene/gameScene1.plist","scene/gameScene1.png");
    }else if(iLoadNum == 2)
    {
        LoadBar->setValue(20);
        
    }else if(iLoadNum == 3)
    {
         
        LoadBar->setValue(30);
       
    }else if(iLoadNum == 4)
    {
        LoadBar->setValue(40);
      
       
    }else if(iLoadNum == 5)
    {
        LoadBar->setValue(50);
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common/commons1.plist","common/commons1.png");
    }
    else if(iLoadNum == 6)
    {
        LoadBar->setValue(60);
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common/commons2.plist","common/commons2.png");
    }
	else if(iLoadNum == 7)
	{
        if(GameHallLayer::RoomType != 89 && GameScene::cGameType == 1  )
        {
            getrank();
        }
		LoadBar->setValue(70);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("die11.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("die22.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("die33.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("die44.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("die555.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("die600.mp3");
        
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("die03.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("die04.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("die05.mp3");
        
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("threekillone.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("threekilltwo.mp3");

        
		  
	}
	else if(iLoadNum == 8)
	{
       
		LoadBar->setValue(75);
		cocos2d::log("6");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("die06.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("die07.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("die08.mp3");
        
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("matchoverwf0.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("matchoverwf1.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("matchoverwf2.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("matchoverwf3.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("matchoverwf4.mp3");
        
        
        
	}
	else if(iLoadNum == 9)
	{
		LoadBar->setValue(80);
		cocos2d::log("7");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("qiehuanbeishu.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("shootok1.mp3");
        
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("shootok21.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("shootok22.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("shootok23.mp3");
        
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("shootpia.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("boom.mp3");
        
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("shootok3.mp3");
        
	}
	else if(iLoadNum == 10)
	{
		LoadBar->setValue(82);
          SpriteFrameCache::getInstance()->addSpriteFramesWithFile("scene/gameScene3.plist","scene/gameScene3.png");
		cocos2d::log("***********5");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Bigdie01.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("coin1.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("wfcoin4.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("wfcoin3.mp3");
	}
 
	else if(iLoadNum == 11)
	{  
		  
		LoadBar->setValue(85);
		cocos2d::log("***********6");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("lvup.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("net.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("deadgirl.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("changecannon.mp3");
		   
         SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common/commons0.plist","common/commons0.png");
        
        
		//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("panzi.mp3");
 
		Vector<SpriteFrame*> sp_vec; 

        // 新的钱的动画
        if(AnimationCache::getInstance()->getAnimation("coinwf") == NULL)
        {
            sp_vec.clear();
            for(int j = 1;j < 7;j++)
            {
                char cTempFishSprite[30];
                sprintf(cTempFishSprite,"coin_%d.png" ,j);
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                sp_vec.pushBack(spriteFrame);
            }
            auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
            JiGuangFrameTwo->setDelayPerUnit(0.05f);
            AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "coinwf");
        }
         
        
        if(AnimationCache::getInstance()->getAnimation("paoTexiao") == NULL)
        {
            sp_vec.clear();
            for(int j = 1;j < 8;j++)
            {
                char cTempFishSprite[30];
                sprintf(cTempFishSprite,"paoframe%d.png" ,j);
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                sp_vec.pushBack(spriteFrame);
            }
            auto paoTexiao = Animation::createWithSpriteFrames(sp_vec);
            paoTexiao->setDelayPerUnit(0.05f);
            AnimationCache::getInstance()->addAnimation(paoTexiao, "paoTexiao");
            
        }
        
        
        if(AnimationCache::getInstance()->getAnimation("shuibo") == NULL)
        {
            
            sp_vec.clear();
            for(int j = 1;j < 33;j++)
            {
                char cTempFishSprite[30];
                sprintf(cTempFishSprite,"wave_frame_%d.png" ,j);
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                sp_vec.pushBack(spriteFrame);
            }
            auto jiguangthree = Animation::createWithSpriteFrames(sp_vec);
            jiguangthree->setDelayPerUnit(0.1f);
            AnimationCache::getInstance()->addAnimation(jiguangthree, "shuibo");
        }
        
        
        if(AnimationCache::getInstance()->getAnimation("fish_animation_ship") == NULL)
        {
            
            sp_vec.clear();
            for(int j = 1;j < 9;j++)
            {
                char cTempFishSprite[30];
                sprintf(cTempFishSprite,"ship%d.png" ,j);
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                sp_vec.pushBack(spriteFrame);
            }
            auto jiguangthree = Animation::createWithSpriteFrames(sp_vec);
            jiguangthree->setDelayPerUnit(0.2f);
            AnimationCache::getInstance()->addAnimation(jiguangthree, "fish_animation_ship");
        }
        
        
        if(AnimationCache::getInstance()->getAnimation("jineng_g") == NULL)
        {
            
            sp_vec.clear();
            for(int j = 1;j < 11;j++)
            {
                char cTempFishSprite[30];
                sprintf(cTempFishSprite,"jineng_%d.png" ,j);
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                sp_vec.pushBack(spriteFrame);
            }
            auto jiguangthree = Animation::createWithSpriteFrames(sp_vec);
            jiguangthree->setDelayPerUnit(0.08f);
            AnimationCache::getInstance()->addAnimation(jiguangthree, "jineng_g");
        }
        
    }
    else if(iLoadNum == 12)
    {
        cocos2d::log("***********7");
        LoadBar->setValue(88);
        preloadResources();
    }
    else if(iLoadNum == 13)
    {
        cocos2d::log("***********7");
        LoadBar->setValue(90);
        loadAnimate();
    }
   
    else if(iLoadNum == 14)
    {
        cocos2d::log("***********81");
        LoadBar->setValue(95);
        Vector<SpriteFrame*> sp_vec;
         
        if(AnimationCache::getInstance()->getAnimation("fanweioneani") == NULL)
        {
            
            sp_vec.clear();
            for(int j = 1;j < 4;j++)
            {
                char cTempFishSprite[30];
                sprintf(cTempFishSprite,"fanweipaoframe%d.png" ,j);
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                sp_vec.pushBack(spriteFrame);
            }
            auto fanweione = Animation::createWithSpriteFrames(sp_vec);
            fanweione->setDelayPerUnit(0.07f);
            AnimationCache::getInstance()->addAnimation(fanweione, "fanweioneani");
        }
        cocos2d::log("***********28");
        if(AnimationCache::getInstance()->getAnimation("jiguanganione") == NULL)
        {
            
            sp_vec.clear();
            for(int j = 1;j < 4;j++)
            {
                char cTempFishSprite[30];
                sprintf(cTempFishSprite,"jiguangtwoframe%d.png" ,j);
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                sp_vec.pushBack(spriteFrame);
            }
            auto jiguanganione = Animation::createWithSpriteFrames(sp_vec);
            jiguanganione->setDelayPerUnit(0.02f);
            AnimationCache::getInstance()->addAnimation(jiguanganione, "jiguanganione");
        }
        if(AnimationCache::getInstance()->getAnimation("jiguanganitwo") == NULL)
        {
            sp_vec.clear();
            for(int j = 1;j < 4;j++)
            {
                char cTempFishSprite[30];
                sprintf(cTempFishSprite,"jiguangtwoframe1%d.png" ,j);
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                sp_vec.pushBack(spriteFrame);
                
            }
            auto jiguanganitwo = Animation::createWithSpriteFrames(sp_vec);
            jiguanganitwo->setDelayPerUnit(0.06f);
            AnimationCache::getInstance()->addAnimation(jiguanganitwo, "jiguanganitwo");
        }
        //加载激光3的动画
        if(AnimationCache::getInstance()->getAnimation("jiguanganithree") == NULL)
        {
            sp_vec.clear();
            for(int j = 1;j < 5;j++)
            {
                char cTempFishSprite[30];
                sprintf(cTempFishSprite,"jiguangthreeframe%d.png" ,j);
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                sp_vec.pushBack(spriteFrame);
            }
            auto jiguangthree = Animation::createWithSpriteFrames(sp_vec);
            jiguangthree->setDelayPerUnit(0.05f);
            AnimationCache::getInstance()->addAnimation(jiguangthree, "jiguanganithree");
        }
        //加载金币的动画
        if(AnimationCache::getInstance()->getAnimation("jb_") == NULL)
        {
            
            sp_vec.clear();
            for(int j = 1;j < 10;j++)
            {
                char cTempFishSprite[30];
                sprintf(cTempFishSprite,"jb_%d.png" ,j);
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                sp_vec.pushBack(spriteFrame);
            }
            auto jb_ = Animation::createWithSpriteFrames(sp_vec);
            jb_->setDelayPerUnit(0.05f);
            AnimationCache::getInstance()->addAnimation(jb_, "jb_");
        }
        //加载银币的动画
        if(AnimationCache::getInstance()->getAnimation("yb_") == NULL)
        {
            sp_vec.clear();
            for(int j = 1;j < 10;j++)
            {
                char cTempFishSprite[30];
                sprintf(cTempFishSprite,"yb_%d.png" ,j);
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                sp_vec.pushBack(spriteFrame);
            }
            auto yb_ = Animation::createWithSpriteFrames(sp_vec);
            yb_->setDelayPerUnit(0.05f);
            AnimationCache::getInstance()->addAnimation(yb_, "yb_");
        }
        cocos2d::log("***********8");
        
        //加载激光2的动画
        if(AnimationCache::getInstance()->getAnimation("JiGuangFrameTwo") == NULL)
        {
            sp_vec.clear();
            for(int j = 1;j < 5;j++)
            {
                char cTempFishSprite[30];
                sprintf(cTempFishSprite,"JiGuangFrame%d.png" ,j);
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                sp_vec.pushBack(spriteFrame);
            }
            auto JiGuangFrame = Animation::createWithSpriteFrames(sp_vec);
            JiGuangFrame->setDelayPerUnit(0.05f);
            AnimationCache::getInstance()->addAnimation(JiGuangFrame, "JiGuangFrameTwo");
            
        }
        
        
        
        
        //加载激光5的动画
        if(AnimationCache::getInstance()->getAnimation("JiGuangFrameThree") == NULL)
        {
            
            sp_vec.clear();
            for(int j = 1;j < 6;j++)
            {
                char cTempFishSprite[30];
                sprintf(cTempFishSprite,"JiGuangFrame1%d.png" ,j);
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                sp_vec.pushBack(spriteFrame);
            }
            auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
            JiGuangFrameTwo->setDelayPerUnit(0.07f);
            AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "JiGuangFrameThree");
        }
        
        //爆炸动画
        if(AnimationCache::getInstance()->getAnimation("baozaframe") == NULL)
        {
            sp_vec.clear();
            for(int j = 0;j < 20;j++)
            {
                char cTempFishSprite[30];
                sprintf(cTempFishSprite,"quan%d.png" ,j);
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                sp_vec.pushBack(spriteFrame);
            }
            auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
            JiGuangFrameTwo->setDelayPerUnit(0.035f);
            AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "baozaframe");
        }
        
        //盘子动画
        if(AnimationCache::getInstance()->getAnimation("panziguang") == NULL)
        {
            sp_vec.clear();
            for(int j = 1;j < 11;j++)
            {
                char cTempFishSprite[30];
                sprintf(cTempFishSprite,"panziguang%d.png" ,j);
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                sp_vec.pushBack(spriteFrame);
            }
            auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
            JiGuangFrameTwo->setDelayPerUnit(0.07f);
            AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "panziguang");
        }
        //子弹动画
        if(AnimationCache::getInstance()->getAnimation("bulletComb0") == NULL)
        {
            sp_vec.clear();
            for(int j = 5;j < 29;j++)
            {
                char cTempFishSprite[30];
                sprintf(cTempFishSprite,"Comp 1_000%d.png" ,j);
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                sp_vec.pushBack(spriteFrame);
            }
            auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
            JiGuangFrameTwo->setDelayPerUnit(0.035f);
            AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "bulletComb0");
        }
        if(AnimationCache::getInstance()->getAnimation("bulletComb1") == NULL)
        {
            sp_vec.clear();
            for(int j =5;j < 29;j++)
            {
                char cTempFishSprite[30];
                sprintf(cTempFishSprite,"Comp 2_000%d.png" ,j);
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                sp_vec.pushBack(spriteFrame);
            }
            auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
            JiGuangFrameTwo->setDelayPerUnit(0.035f);
            AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "bulletComb1");
        }
        if(AnimationCache::getInstance()->getAnimation("bulletComb2") == NULL)
        {
            sp_vec.clear();
            for(int j = 5;j < 29;j++)
            {
                char cTempFishSprite[30];
                sprintf(cTempFishSprite,"Comp 3_000%d.png" ,j);
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                sp_vec.pushBack(spriteFrame);
            }
            auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
            JiGuangFrameTwo->setDelayPerUnit(0.03f);
            AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "bulletComb2");
        }
        if(AnimationCache::getInstance()->getAnimation("bulletComb3") == NULL)
        {
            sp_vec.clear();
            for(int j = 5;j < 28;j++)
            {
                char cTempFishSprite[30];
                sprintf(cTempFishSprite,"Comp 4_000%d.png" ,j); 
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite); 
                sp_vec.pushBack(spriteFrame); 
            }
            auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
            JiGuangFrameTwo->setDelayPerUnit(0.035f);  
            AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "bulletComb3");  
        }
        
        
    }
    
    else if(iLoadNum == 15)
    {  
        LoadBar->setValue(100);
        
        FishTrack::LoadAllTrackData(); 
        FishScript::LoadAllScriptData();
        FishLineup::LoadAllFishLieupData();
        FishRandSwatch::LoadAllRandSwatchData();
        this->unscheduleAllSelectors();
        
        this->scheduleOnce(schedule_selector(LoadRes::jinruChangjin),1.0f);	
        
    }
    iLoadNum++;
}

void LoadRes::jinruChangjin(float dt)
{
	this->removeAllChildrenWithCleanup(true);
	this->unscheduleAllSelectors();

	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void LoadRes::preloadResources()
{ 
	int room = iRoomType+1;
	char RoomTypeFlag[20];
	sprintf(RoomTypeFlag,"Room%dHas",iRoomType+1);

	//下载资源
	if(iRoomType>2 && iRoomType < 20)
	{
		if(!UserDefault::getInstance()->getBoolForKey(RoomTypeFlag))
		{
			//下载资源
			if(loadResource(iRoomType+1))
			{
				UserDefault::getInstance()->setBoolForKey(RoomTypeFlag,true);
				UserDefault::getInstance()->flush();
			}else
			{
				auto gongxi = Gongxi::create(99,GAME_DATA_STRING("firstInTip3"));
				gongxi->setPosition(Point::ZERO);
				this->addChild(gongxi,1000,1000);

				auto quedingSprite = Scale9Sprite::createWithSpriteFrameName("XR_qd.png");
				auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(LoadRes::fanhuiGame,this));
				auto btnMenu = Menu::create(quedingItem,nullptr);
				btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
				gongxi->getChildByTag(1)->addChild(btnMenu,100);

				return;
			}	
			firstInLabel->setString(GAME_DATA_STRING("firstInTip1"));
		}

	}   
	
    cocos2d::log("******wf*****7");
	//加载fish资源
	addResource(room);
 
	kroom = room;
} 

void LoadRes::loadAnimate()
{
	////加载动画
	 
 

	if(AnimationCache::getInstance()->getAnimation("fish_animation_0") == NULL )//若没有鱼动画，加载每条鱼的动画
	{
		//场景1只有19种鱼，其余场景都是20种
		int fishesNum = 26;
		if(kroom == 66)
		{ 
			fishesNum = 18;
		}  
		//根据infoplist来加载鱼的动画
		for (int i=0; i<fishesNum; i++)
		{  
			
			//得到场景iRoomType+1第i+1种鱼的数量
			char cTempFishFrame[20];
			sprintf(cTempFishFrame,"fish_%d_num",i);
			int fishFrame = STATIC_DATA_INT(cTempFishFrame); 

			//得到第i+1种鱼的游动动画
			Vector<SpriteFrame*> sp_vec; 

			for(int j = 0;j < fishFrame;j++)
			{ 
				char cTempFishSprite[40];
				sprintf(cTempFishFrame,"fish_%d_%d.png",i,j);  

				SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishFrame); 
				sp_vec.pushBack(spriteFrame); 
			} 

			Animation* fishAnimation = Animation::createWithSpriteFrames(sp_vec);
			float a  = STATIC_DATA_FLOAT("fish_frame_delay");
			fishAnimation->setDelayPerUnit(STATIC_DATA_FLOAT("fish_frame_delay"));//设置两帧之间的时间间隔

			//添加鱼动画到动画缓冲池中
			char cTempFishAniName[40];
			sprintf(cTempFishAniName,"fish_animation_%d_%d",LoadRes::RoomType,i);
			AnimationCache::getInstance()->addAnimation(fishAnimation, cTempFishAniName);
 
			//得到第i+1种鱼的死动画
			Animation* dfishAnimation = Animation::createWithSpriteFrames(sp_vec);
			dfishAnimation->setDelayPerUnit(0.015f);//设置两帧之间的时间间隔

			//添加死鱼动画到动画缓冲池中
			char dcTempFishAniName[20];
			sprintf(dcTempFishAniName,"dfish_animation_%d",i);
			AnimationCache::getInstance()->addAnimation(dfishAnimation, dcTempFishAniName); 
		} 
	}
	   
    
}

/*
void LoadRes::load_huafeileiji(char cinfo)
{
    //÷¥––∏≈¬ œ¬‘ÿ
    CURL *curl;
    CURLcode res;
    std::string cc;
    curl=curl_easy_init();
    
    if(curl)
    {
        
        curl_easy_setopt( curl, CURLOPT_URL, "http://buyu2.iyueyo.com/qpby2/ios/HuaFeiLeiji.php"); //«Î«Ûµƒµÿ÷∑
     
        curl_easy_setopt(curl,CURLOPT_TIMEOUT,3000);
        curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&load_huafeileiji_call); //¥¶¿Ìµƒ∫Ø ˝
        res=curl_easy_perform(curl);
        if(res!=CURLE_OK)
        {
            log("¡™Õ¯≥¨ ± %i",res);
            GameScene::is_success_load = false;
        }
        curl_easy_cleanup(curl);
    }else
    {
        GameScene::is_success_load = false;
    }
}

size_t LoadRes::load_huafeileiji_call(uint8_t *buffer,size_t size,size_t nmemb,void *stream)
{
    cocos2d::log("buffer jia = %s ", (const char *)buffer);
    
    //¥Ú”° ’µΩµƒ ˝æ›
    char tmp[10]="";
    
    int i=0;
    int j=0;
    
    int iCount = 0;
    while(buffer[i]!='\0')
    {
        char c = buffer[i];
        if(c=='%')
        {
            if(iCount < 4)
            {
                AllRobot::readnetLeiji[iCount] = atof(tmp);
            }
            else
            {
                AllRobot::readnetHuafeiQuan[iCount-4] = atof(tmp);
            }
            iCount++;
            j = 0;
            memset(tmp,0,sizeof(tmp));
        }
        else
        {
            tmp[j] = c;
            j++;
        }
        i++;
    }
    
    size_t sizes = size*nmemb;
    return sizes;
}

*/

void LoadRes::addResource(int room)
{
	string resourceRoad = FileUtils::getInstance()->getWritablePath();

	if(room == 66)
	{
		room = LogoLayer::room + 1;
		cocos2d::log("room = %d",room);
        
        
		iRoomType = 66;
		GameHallLayer::RoomType = room - 1;
        LoadRes::RoomType = room-1;
	}

	if(room < 13)
	{
		for(int i = 0; i<fishNum[room-1];i++)
		{
            cocos2d::log("*****%d******7",room);
            
			if(room>3)
			{
				char plistname[30];
				char pngname[30];

				sprintf(plistname,"scene%dfishlist%d.plist",room,i+1);
				sprintf(pngname,"scene%dfishlist%d.png",room,i+1);
				SpriteFrameCache::getInstance()->addSpriteFramesWithFile(resourceRoad + plistname,resourceRoad + pngname); 
			}else
			{
				char plistname[30];
				char pngname[30];

				sprintf(plistname,"scene/scene%dfishlist%d.plist",room,i+1);
				sprintf(pngname,"scene/scene%dfishlist%d.png",room,i+1);
				SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistname,pngname);
                
			}        	
		}
	}

	if( room>90  && room<95)
	{
		char plistname[50];
		char pngname[50];

		if(room == 94)
		{
			sprintf(plistname,"BSscene/BSscene%dfishlist1.plist",4);
			sprintf(pngname,"BSscene/BSscene%dfishlist1.png",4);
		}
		else
		{
			sprintf(plistname,"BSscene/BSscene%dfishlist1.plist",room - 89);
			sprintf(pngname,"BSscene/BSscene%dfishlist1.png",room - 89);
		}		
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistname,pngname); 
	}
	
    
    
}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_NoWifi(JNIEnv * env, jclass ,jint j)
{
	cocos2d::log("fan hui j = %d",j);
	LoadRes::hasWifi = j;
}

#endif