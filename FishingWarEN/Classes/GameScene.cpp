#include "GameScene.h"  
#include "StaticData.h" 
#include "FishTrack.h"
#include "LogoLayer.h"
#include "SimpleAudioEngine.h"
#include "GameBegin.h"
#include "Gongxi.h"
#include "OnlineReward.h"
#include "BiBei.h"
#include "TiShi.h"
#include "VIPgongxi.h"
#include "GameHelp.h"
#include "GameTextIn.h"
#include "GameSet.h" 
#include "Mission.h"
#include "FishBaiKe.h"
#include "LoginReward.h"
#include "Waiting.h"
#include "Shark.h" 
#include "GameHallLayer.h"
#include "LoadRes.h"
#include "ChallengeBOSS.h"
#include "Gonggao.h"
#include "ShopJJ.h"

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

bool GameScene::is_success_load = false;		//∏≈¬ º”∑÷ ˝◊È
float  GameScene::gailv_jia[33] = {0};			//∏≈¬ º”∑÷ ˝◊È
float GameScene::gailv_jian[33] = {0};;			//∏≈¬ º”∑÷ ˝◊È
float GameScene::jia_gailv = 0;					//∏≈¬ º”∑÷±»
float GameScene::jian_gailv = 0;				//∏≈¬ º”∑÷±»
int GameScene::gailv_shijian = -1;				//∏≈¬ º”∑÷±»
bool GameScene::is_jiafen = false;

bool GameScene::isqiehuan = false;

FILE *GameScene::moneyTXT = NULL;
FILE *GameScene::expTXT = NULL;
FILE *GameScene::zuanshiTXT = NULL;

bool GameScene::stopBossTime = false;
bool GameScene::vip_goumai_flag = false;
char GameScene::GoNewSence;
char GameScene::cGameType = 0;
char GameScene::cSelfPos = 8;

bool GameScene::bRobotPos[4]; 
char GameScene::cRobotIQ[4]; 

bool GameScene::bShowShangCheng = false;
bool GameScene::lingjiangflag = false;
//ooxx

bool GameScene::bPlayPanzi = false;
int GameScene::iPanziMoney = 0;
bool GameScene::bOverBisai = false;
bool GameScene::isbaoji = false;
bool GameScene::isBiSaiVis = false;
bool GameScene::bSaJingbi = false;
bool GameScene::bBaoZha = false;
Vec2 GameScene::DeadFishPos(0,0);
Label * GameScene::bs_jfb_l[4] = {nullptr};
LabelTTF * GameScene::bs_jfb_n[4] = {nullptr};
long long GameScene::bs_jfb_num[4] = {0};
bool GameScene::bRobotVip[4] = {false};
float GameScene::game_zhenlv =  0.0f;

bool GameScene::isduankai = false;			// «∑Ò∂œø™
time_t GameScene::houtaiTime = 0;		//«–µΩ∫ÛÃ®µƒµ±«∞ ±º‰
time_t GameScene::qiantaiTime = 0;		//ªÿµΩ«∞Ã®µƒµ±«∞ ±º‰

Layer * QiongShenLayer::createScene()
{
	auto layer = QiongShenLayer::create();
	return layer;
}
 
bool QiongShenLayer::init()
{  
	if ( !Layer::init() )	
	{
		return false;
	}
 
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
	auto zheZhao = LayerColor::create(ccc4(0,0,0,150),1024,768);
	zheZhao->setPosition(Point::ZERO);
	zheZhao->setScale(2.0f);
	this->addChild(zheZhao);
    
    auto qiongshen = Sprite::createWithSpriteFrameName("qiongshen1.png");
 
    qiongshen->setPosition(Vec2(visibleSize.width/2 , visibleSize.height * 0.55));
    this->addChild(qiongshen,MENULAYER+98);
    
    
    auto tixingzi = LabelTTF::create(GAME_DATA_STRING("qiongshen_shop"),GameHallLayer::wordKind,38);
    tixingzi->setColor(Color3B::YELLOW);
    tixingzi->setPosition(Vec2(visibleSize.width/2 , visibleSize.height * 0.28));
    addChild(tixingzi);
    
    float time_xq = 0.5f;
    //详情按钮
    auto jump1  = JumpBy::create(time_xq,Vec2::ZERO,30,1);
    auto jump2  = JumpBy::create(time_xq-0.2f,Vec2::ZERO,15,1);
    auto jump3  = JumpBy::create(time_xq-0.3f,Vec2::ZERO,5,1);
    
    tixingzi->runAction(Repeat::create(Sequence::create(DelayTime::create(1.0f),
                                                        jump1,CallFunc::create([&]{GameBegin::playSound("music/bs_room_xiangq.mp3");}),
                                                        jump2, 
                                                        jump3, 
                                                        nullptr),3));
 
	//ÃÌº”¥•√˛ ¬º˛
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(QiongShenLayer::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(QiongShenLayer::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(QiongShenLayer::onTouchEnded,this);
	listener->setSwallowTouches(false);//≤ªœÚœ¬¥´µ›¥•√˛
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
 
	return true;
}
 
bool QiongShenLayer::onTouchBegan(Touch* touch, Event* event) 
{ 
	int a= 3;
	return true;
}

void QiongShenLayer::onTouchMoved(Touch* touch, Event* event) 
{
	int a= 3;
}

void QiongShenLayer::onTouchEnded(Touch* touch, Event* event)
{
	int a= 3;
    auto layer = Shop::create(2);
    this->getParent()->addChild(layer,10000);
}

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
} 

void GameScene::init_jishi()
{
	if(GameScene::cGameType == 2)
	{
		//GameBegin::setFileData("jywopl.txt",GameBegin::getFileData("jywopl.txt") - 500);
		 cocos2d::log("init_jishi()1");
		GetBossMoney();    
		auto pro1 = Sprite::create("img/bossexp.png");
		auto pro2 = Sprite::create("img/bossexptiao.png");
		auto pro3 = Sprite::create("img/33.png"); 

		_progressBossBar = ControlSlider::create(pro1,pro2,pro3);
		_progressBossBar->setPosition(Point(visibleSize.width/2,visibleSize.height*0.80));
		_progressBossBar->setMinimumValue(0.0f);
		_progressBossBar->setMaximumValue(iBossXue);
		_progressBossBar->setValue(iBossXue);
		this->addChild(_progressBossBar,100);
		_progressBossBar->setEnabled(false);

		auto  TimeKuang = Sprite::createWithSpriteFrameName("timekuang1.png");
		TimeKuang->setPosition(Point(visibleSize.width*0.1,visibleSize.height*0.80));
		this->addChild(TimeKuang,100);

		cTimeMiao =BossTimeMiao;
		cTimeMin =BossTimeFen;


		TimeMin = Label::create();
		TimeMin->setCharMap("img/clocknum.png",19,31,'0');
		char min[10];
		sprintf(min,"%d",cTimeMin); 
		TimeMin->setString(min);
		TimeMin->setPosition(Point(visibleSize.width*0.095,visibleSize.height*0.795));
		this->addChild(TimeMin,100);


		TimeMiao = Label::create();
		TimeMiao->setCharMap("img/clocknum.png",19,31,'0');
		char miao[10];
		sprintf(miao,"%d",cTimeMiao);  
		TimeMiao->setString(miao);
		TimeMiao->setPosition(Point(visibleSize.width*0.142,visibleSize.height*0.795));
		this->addChild(TimeMiao,100);


	
		 

		auto mmm = TiShi::create(8,"","",10,FishLayer::cNewBoss);
		this->addChild(mmm,100);

		auto ac1 = DelayTime::create(5.0f);
		auto ac2 = CCCallFunc::create(this,callfunc_selector(GameScene::ShowBossJiangli));
		auto seq = Sequence::create(ac1,ac2,nullptr);
		this->runAction(seq);


		BossGuanOne = Sprite::createWithSpriteFrameName("bossjiangli.png");
		BossGuanOne->setPosition(visibleSize.width * 0.4,visibleSize.height* 0.45);
		this->addChild(BossGuanOne);
		BossGuanOne->setVisible(false);

		char cNum[20];
		BossMoneyOne =  Label::create();         //≈⁄µƒ±∂ ˝
		BossMoneyOne->setCharMap("fengshunum.png",11,17,'0');
		BossMoneyOne->setPosition(Point(visibleSize.width * 0.53,visibleSize.height* 0.45));
		this->addChild(BossMoneyOne);
		BossMoneyOne->setScale(1.5f);
        
        
        
        mGoldLabel = LabelTTF::create("GOLD", GameHallLayer::wordKind, 22);
        mGoldLabel->setPosition(Point(visibleSize.width * 0.61,visibleSize.height* 0.45));
        this->addChild(mGoldLabel);
        mGoldLabel->setVisible(false);
        

		sprintf(cNum,"%d",BossMoney);
		BossMoneyOne->setString(cNum);
		BossMoneyOne->setVisible(false);

		BossMoneyTwo =  Label::create();         //≈⁄µƒ±∂ ˝
		BossMoneyTwo->setCharMap("fengshunum.png",11,17,'0');
		BossMoneyTwo->setPosition(Point(visibleSize.width * 0.68,visibleSize.height* 0.45));
		BossMoneyTwo->setScale(1.5f);
		this->addChild(BossMoneyTwo);
        
        
        mDiamondLabel = LabelTTF::create("DIAMOND", GameHallLayer::wordKind, 22);
        mDiamondLabel->setPosition(Point(visibleSize.width * 0.77,visibleSize.height* 0.45));
        this->addChild(mDiamondLabel);
        mDiamondLabel->setVisible(false);



		memset(cNum,0,sizeof(cNum));
		sprintf(cNum,"%d",BossZuanShi);
		BossMoneyTwo->setString(cNum);
		BossMoneyTwo->setVisible(false);
		this->schedule(schedule_selector(GameScene::updateBossTime),1.0f);
	}
	else if(GameScene::cGameType == 1)
	{
		cocos2d::log("init_jishi()2");
		OnlineStateInt = 0; //≥ı ºªØŒ™0
		auto  TimeKuang = Sprite::createWithSpriteFrameName("timekuang1.png");
		TimeKuang->setPosition(Point(visibleSize.width*0.5,visibleSize.height-20));
		this->addChild(TimeKuang,100);

		TimeMin = Label::create();
		TimeMin->setCharMap("img/clocknum.png",19,31,'0');
		TimeMin->setString("4");
		TimeMin->setPosition(Point(visibleSize.width*0.495,visibleSize.height-23));
		this->addChild(TimeMin,100);


		TimeMiao = Label::create();
		TimeMiao->setCharMap("img/clocknum.png",19,31,'0');
		TimeMiao->setString("59");
		TimeMiao->setPosition(Point(visibleSize.width*0.542,visibleSize.height-23));
		this->addChild(TimeMiao,100);


		cTimeMiao = 59;
		cTimeMin = 4;
		this->schedule(schedule_selector(GameScene::updateBossTime),1.0f);
	}
	else  //≥ı ºªØ‘⁄œﬂ¡ÏΩ±
	{ 
		cocos2d::log("init_jishi()3");
		time_t currentTime;
		time(&currentTime);

		double preTime = UserDefault::getInstance()->getDoubleForKey("preTime");
		char cNumTwo[30];
		//≥ı ºªØø…“‘µ„ª˜
		MaoHao = Sprite::createWithSpriteFrameName("maohaowf.png");
		MaoHao->setPosition(Point(jiasuspr10->getContentSize().width/2,-MaoHao->getContentSize().height/2 + 5)); 
		jiasuspr10->addChild(MaoHao,100);

		cTimeMin = UserDefault::getInstance()->getIntegerForKey("ZaiXianMin");
		cTimeMiao = UserDefault::getInstance()->getIntegerForKey("ZaiXianMiao");
		lingj_time =  UserDefault::getInstance()->getIntegerForKey("ZaiXianTime");

		//≥ı ºªØ∑÷
		TimeMin = Label::createWithCharMap("img/clocknum.png",19,31,'0');
		sprintf(cNumTwo,"0%d",cTimeMin);
		TimeMin->setString(cNumTwo);  
		TimeMin->setAnchorPoint(Vec2(1,0.5));
		TimeMin->setPosition(Point(-5,MaoHao->getContentSize().height/2)); 
		TimeMin->setScale(0.8f);
		MaoHao->addChild(TimeMin);   

		//≥ı ºªØ√Î
		TimeMiao = Label::create();  
		TimeMiao->setCharMap("img/clocknum.png",19,31,'0'); 
		if(cTimeMiao < 10)
		{ 
			sprintf(cNumTwo,"0%d",cTimeMiao);
		}
		else
		{
			sprintf(cNumTwo,"%d",cTimeMiao);
		} 
		TimeMiao->setString(cNumTwo);  
		TimeMiao->setAnchorPoint(Vec2(0,0.5));
		TimeMiao->setScale(0.8f); 
		TimeMiao->setPosition(Point(MaoHao->getContentSize().width + 5,MaoHao->getContentSize().height/2)); 
		MaoHao->addChild(TimeMiao,100);

		if((preTime < currentTime && currentTime< (preTime +24*60*60)) ||  preTime == 0)  //24–° ±÷Æƒ⁄ ªÚ’ﬂ «µ⁄“ª¥Œ
		{ 
			if(((cTimeMin == 0 && cTimeMiao > 0) || (cTimeMin > 0 && cTimeMiao == 0) || (cTimeMin > 0 && cTimeMiao > 0)) && lingj_time != 3)  //»Áπ˚≤ªƒ‹µ„ª˜‘Ú ø™ ºº∆ ±
			{
				lingjiang_state = 0;  //ªπ√ªµΩ ±º‰
				this->schedule(schedule_selector(GameScene::updateBossTime),1.0f);

			}else if(lingj_time == 3)
			{
				TimeMin->setVisible(false);
				TimeMiao->setVisible(false);
				MaoHao->setVisible(false);
				m_zaixianGuang->setVisible(false);
				m_AddMoney->setVisible(false);
			}else if(cTimeMin == 0 && lingj_time == 0 && cTimeMiao == 0 && preTime == 0)
			{
				lingjiang_state = 0;  //ªπ√ªµΩ ±º‰
				cTimeMin = 0;
				cTimeMiao = 30; 

				sprintf(cNumTwo,"0%d",cTimeMin);
				TimeMin->setString(cNumTwo); 

				if(cTimeMiao < 10)
				{ 
					sprintf(cNumTwo,"0%d",cTimeMiao);
				}
				else
				{
					sprintf(cNumTwo,"%d",cTimeMiao);
				} 
				TimeMiao->setString(cNumTwo);

				this->schedule(schedule_selector(GameScene::updateBossTime),1.0f);
			}
			else
			{
				//ø…“‘¡ÏΩ±
				lingjiang_state = 1;
				TimeMin->setVisible(false);
				TimeMiao->setVisible(false);
				MaoHao->setVisible(false);
 
				m_zaixianGuang->setVisible(true);
				auto  sf = CCRotateBy::create(4.0f,360); 
				m_zaixianGuang->runAction(RepeatForever::create(sf)); 

				auto tishi = TiShi::create(4,GAME_DATA_STRING("LingJiang1"),GAME_DATA_STRING("LingJiang2"),3,0); 
				tishi->setPosition(Point(visibleSize.width - 120,visibleSize.height-220)); 
				this->addChild(tishi,120);   
			}			
		} 
		else if(currentTime >(preTime+24*60*60))//≥¨π˝1ÃÏ√ª¡Ï∏¸–¬ ±º‰
		{
			lingjiang_state = 0;
			cTimeMin = 0;
			cTimeMiao = 30; 
 
			sprintf(cNumTwo,"0%d",cTimeMin);
			TimeMin->setString(cNumTwo); 

			if(cTimeMiao < 10)
			{ 
				sprintf(cNumTwo,"0%d",cTimeMiao);
			}
			else
			{
				sprintf(cNumTwo,"%d",cTimeMiao);
			} 
			TimeMiao->setString(cNumTwo);    
 
			UserDefault::getInstance()->setIntegerForKey("ZaiXianTime",0);
			UserDefault::getInstance()->flush();  
			lingj_time =  UserDefault::getInstance()->getIntegerForKey("ZaiXianTime");
			this->schedule(schedule_selector(GameScene::updateBossTime),1.0f);
		}
	}
}

void GameScene::GetBossMoney()
{
	int AllBossXue[24]= {1000,2000,3000,4000,5000,6000,10000,20000,30000,50000,
		70000,90000,100000,150000,200000,250000,300000,340000,500000,600000,
		700000,800000,900000,1000000};
 
	UserDefault::getInstance()->setBoolForKey("is_boss_suc1",false);// «∑ÒÃÙ’Ω≥…π¶
	UserDefault::getInstance()->setIntegerForKey("boss_day_times",UserDefault::getInstance()->getIntegerForKey("boss_day_times") + 1);//ÃÙ’Ω ß∞‹µƒ¥Œ ˝
	UserDefault::getInstance()->flush();

	int wftype =  FishLayer::cNewBoss;
 
		 
	
	iBossXue= AllBossXue[wftype];
	BossTimeFen = 0;
	BossTimeMiao = 0;
	if(wftype == 0)
	{
		BossTimeFen = 5;
		BossMoney = 1050;
		BossZuanShi = 0;
	}
	else if(wftype == 1)
	{
		BossTimeFen = 5;
		BossMoney = 2100;
		BossZuanShi = 0;
	}	
	else if(wftype == 2)
	{
		BossTimeFen = 5;
		BossMoney = 3150;
		BossZuanShi = 10;
	}
	else if(wftype == 3)
	{
		BossTimeFen = 5;
		BossMoney = 4200;
		BossZuanShi = 10;
	}
	else if(wftype == 4)
	{
		BossTimeFen = 5;
		BossMoney = 5250;
		BossZuanShi = 10;
	}
	else if(wftype == 5)
	{
		BossTimeFen = 5;
		BossMoney = 6300;
		BossZuanShi = 15;
	}
	else if(wftype == 6)
	{
		BossTimeFen = 4;
		BossMoney = 9000+ CCRANDOM_0_1()*2000;
		BossZuanShi = 20;
	}
	else if(wftype == 7)
	{
		BossTimeFen = 4;
		BossMoney = 18000+ CCRANDOM_0_1()*4000;
		BossZuanShi = 20;
	}
	else if(wftype == 8)
	{
		BossTimeFen = 4;
		BossMoney = 27000+ CCRANDOM_0_1()*6000;
		BossZuanShi = 20;
	}
	else if(wftype == 9)
	{
		BossTimeFen = 4;
		BossMoney = 45000+ CCRANDOM_0_1()*10000;
		BossZuanShi = 20;
	}
	else if(wftype == 10)
	{
		BossTimeFen = 4;
		BossMoney = 65000+ CCRANDOM_0_1()*10000;
		BossZuanShi = 20;
	}
	else if(wftype == 11)
	{
		BossTimeFen = 4;
		BossMoney = 80000+ CCRANDOM_0_1()*20000;
		BossZuanShi = 20;
	}
	else if(wftype == 12)
	{
		BossTimeFen = 3;
		BossMoney = 80000+ CCRANDOM_0_1()*20000;
		BossZuanShi = 20 + CCRANDOM_0_1()*20;
	}
	else if(wftype == 13)
	{
		BossTimeFen = 3;
		BossMoney = 120000+ CCRANDOM_0_1()*40000;
		BossZuanShi = 20 + CCRANDOM_0_1()*20;
	}
	else if(wftype == 14)
	{
		BossTimeFen = 3;
		BossMoney = 150000+ CCRANDOM_0_1()*60000;
		BossZuanShi = 20 + CCRANDOM_0_1()*20;
	}
	else if(wftype == 15)
	{
		BossTimeFen = 3;
		BossMoney = 200000+ CCRANDOM_0_1()*70000;
		BossZuanShi = 20 + CCRANDOM_0_1()*20;
	}
	else if(wftype == 16)
	{
		BossTimeFen = 3;
		BossMoney = 250000+ CCRANDOM_0_1()*70000;
		BossZuanShi = 20 + CCRANDOM_0_1()*20;
	}
	else if(wftype == 17)
	{
		BossTimeFen = 3;
		BossMoney = 300000+ CCRANDOM_0_1()*70000;
		BossZuanShi = 20 + CCRANDOM_0_1()*20;
	}
	else if(wftype == 18)
	{
		BossTimeFen = 2;
		BossMoney = 450000+ CCRANDOM_0_1()*70000;
		BossZuanShi = 50 + CCRANDOM_0_1()*50;
	}
	else if(wftype == 19)
	{
		BossTimeFen = 1;
		BossTimeMiao = 30;
		BossMoney = 550000+ CCRANDOM_0_1()*70000;
		BossZuanShi = 50 + CCRANDOM_0_1()*50;
	}
	else if(wftype == 20)
	{ 
		BossTimeMiao = 60;
		BossMoney = 650000+ CCRANDOM_0_1()*70000;
		BossZuanShi = 50 + CCRANDOM_0_1()*50;
	}
	else if(wftype == 21)
	{ 
		BossTimeMiao = 50;
		BossMoney = 750000+ CCRANDOM_0_1()*70000;
		BossZuanShi = 50 + CCRANDOM_0_1()*50;
	}
	else if(wftype == 22)
	{ 
		BossTimeMiao = 40;
		BossMoney = 850000+ CCRANDOM_0_1()*70000;
		BossZuanShi = 50 + CCRANDOM_0_1()*50;
	}
	else if(wftype == 23)
	{
		BossTimeMiao = 20;
		BossMoney = 1100000;
		BossZuanShi = 200;
	} 

}
void GameScene::suiji_jiafen()
{
    float tmpGal = CCRANDOM_0_1()*100;
    if(tmpGal < GameScene::jia_gailv)
    {
        is_jiafen = true;
    }
    else
    {
        is_jiafen = false;
    }
}

void GameScene::first_match_reward(float dt)
{
    CannonLayer::GameCoinRefresh(2000);
    
    auto gongxi = Gongxi::create(4,GAME_DATA_STRING("frist_match_reward"));
    this->addChild(gongxi,20000);
}

void GameScene::init_bisai()
{
    
    
    if(UserDefault::getInstance()->getIntegerForKey("ishadmatch") == 0)
    {
        this->scheduleOnce(schedule_selector(GameScene::first_match_reward),2.0f);
        UserDefault::getInstance()->setIntegerForKey("ishadmatch",1);
        UserDefault::getInstance()->flush();
    }
    gailv_load_times = -1;
    
   
    for(int i=0; i< 4; i++)
    {
        AllRobot::readnetLeiji[i] = 0;
        AllRobot::readnetHuafeiQuan[i] = 0;
    }
    
    char cLoadGailvRoomType = 0;
  
    if(GameHallLayer::RoomType ==89)
    {
        cLoadGailvRoomType = 4;
        
    }
    else
    {
        cLoadGailvRoomType= GameHallLayer::RoomType-90;
    }
    load_gailv(cLoadGailvRoomType);
    
	paimingXX = Sprite::createWithSpriteFrameName("hall_ssxx_bg.png");
	paimingXX->setPosition(Vec2(visibleSize.width * 0.52,visibleSize.height * 0.89));
	paimingXX->setScale(0.5);
	paimingXX->setOpacity(0);
	this->addChild(paimingXX,MENULAYER);

	wodepaiming = Sprite::createWithSpriteFrameName("bs_wodepaiming.png");
	wodepaiming->setPosition(Vec2(visibleSize.width * 0.516,visibleSize.height * 0.89));
	wodepaiming->setAnchorPoint(Vec2(1,0.5));
	wodepaiming->setScale(0.8);
	this->addChild(wodepaiming,MENULAYER);
 
	wfRank = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');	
	wfRank->setAnchorPoint(Vec2(0,0.5));
	wfRank->setScale(0.7);
	wfRank->setPosition(Vec2(visibleSize.width* 0.525,visibleSize.height * 0.89)); 

	int ibisairenshu = UserDefault::getInstance()->getIntegerForKey("bisairenshu");

	char cRank[20];
	sprintf(cRank,"%d",ibisairenshu);
	wfRank->setString(cRank);
	this->addChild(wfRank,MENULAYER);

	wodepaiming1 = Sprite::createWithSpriteFrameName("bs_wodepaiming.png");
	wodepaiming1->setPosition(Vec2(visibleSize.width * 0.516,visibleSize.height * 0.89));
	wodepaiming1->setAnchorPoint(Vec2(1,0.5));
	wodepaiming1->setOpacity(0);
	wodepaiming1->setScale(2.4);
	this->addChild(wodepaiming1,MENULAYER);
 

	wfRank1 = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');	
	wfRank1->setAnchorPoint(Vec2(0,0.5));
	wfRank1->setScale(2.1);
	wfRank1->setOpacity(0);
	wfRank1->setPosition(Vec2(visibleSize.width* 0.525,visibleSize.height * 0.89)); 
	wfRank1->setString(cRank);
	this->addChild(wfRank1,MENULAYER);
 
    if(GameHallLayer::RoomType == 89)
    {
       	wfAllRobot.initplayer(ibisairenshu,4,UserDefault::getInstance()->getStringForKey("player_name"));
    }
    else
    {
        wfAllRobot.initplayer(ibisairenshu,GameHallLayer::bs_moshi - 1,UserDefault::getInstance()->getStringForKey("player_name"));
    //    wfAllRobot.setRobotWin();
        
    }

	cocos2d::log("bisai ren shu  =  %d",ibisairenshu);
 
	char tmp_jfb[100];
	//≥ı ºªØº∆∑÷∞Â
	auto bs_jifenban_sp = Sprite::createWithSpriteFrameName("bs_jifenban1.png");
	bs_jifenban = MenuItemSprite::create(bs_jifenban_sp,bs_jifenban_sp,CC_CALLBACK_0(GameScene::bs_jifenban_hs,this));
	bs_jifenban->setAnchorPoint(Vec2(0,1));
	bs_jifenban->setPosition(Vec2(0,visibleSize.height - 80));
	auto jifen_menu = Menu::create(bs_jifenban,nullptr);
	jifen_menu->setPosition(Vec2::ZERO);
	this->addChild(jifen_menu,MENULAYER + 10);
 
	bs_jifentime = 0;

	for(int i = 0; i < 4 ; i++)
	{
		bs_jfb_num[i] = 0;
		bs_jfb_l[i] = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
		bs_jfb_l[i]->setScale(0.4);
		bs_jfb_l[i]->setAnchorPoint(Vec2(0,0));
		bs_jfb_l[i]->setPosition(Vec2(18,18 + (3-i)*43));
		bs_jfb_l[i]->setString("0");

		bs_jifenban_sp->addChild(bs_jfb_l[i]);
	}
	bs_jfb_l[3]->setPosition(Vec2(18,13));

	sprintf(tmp_jfb,"robotNName%d",GameHallLayer::robot3[2]);

	bs_jfb_n[0] = LabelTTF::create(GAME_DATA_STRING(tmp_jfb),GameHallLayer::wordKind,18);

	bs_jfb_n[0]->setColor(Color3B(251,231,0));
	bs_jfb_n[0]->setAnchorPoint(Vec2(0,0));
	bs_jfb_n[0]->setPosition(Vec2(55,167));
	bs_jifenban_sp->addChild(bs_jfb_n[0]);
    string tmpStr =GAME_DATA_STRING(tmp_jfb);


	sprintf(tmp_jfb,"robotNName%d",GameHallLayer::robot1[2]);
	bs_jfb_n[1] = LabelTTF::create(GAME_DATA_STRING(tmp_jfb),GameHallLayer::wordKind,18);
	bs_jfb_n[1]->setAnchorPoint(Vec2(0,0));
	bs_jfb_n[1]->setColor(Color3B(193,193,193));
	bs_jfb_n[1]->setPosition(Vec2(55,167 - 1 * 41));
	bs_jifenban_sp->addChild(bs_jfb_n[1]);
    tmpStr =GAME_DATA_STRING(tmp_jfb);

	//sprintf(tmp_jfb,"robotNName%d",GameHallLayer::robot2[2]);
    sprintf(tmp_jfb,"robotNName%d",4);
	bs_jfb_n[2] = LabelTTF::create(GAME_DATA_STRING(tmp_jfb),GameHallLayer::wordKind,18);
	bs_jfb_n[2]->setAnchorPoint(Vec2(0,0));
	bs_jfb_n[2]->setColor(Color3B(226,130,83));
	bs_jfb_n[2]->setPosition(Vec2(55,167 - 2 * 41));
	bs_jifenban_sp->addChild(bs_jfb_n[2]);
    tmpStr =GAME_DATA_STRING(tmp_jfb);

	bs_jfb_n[3] = LabelTTF::create(UserDefault::getInstance()->getStringForKey("player_name"),GameHallLayer::wordKind,18);
	bs_jfb_n[3]->setAnchorPoint(Vec2(0,0));
	bs_jfb_n[3]->setPosition(Vec2(18,157 - 3 * 43));
	bs_jfb_n[3]->setVisible(false);
	bs_jifenban_sp->addChild(bs_jfb_n[3]);
 
	//…Ã≥«∫Õ‘⁄œﬂ¡ÏΩ±
	m_AddMoney->setVisible(false);
	m_zaixianGuang->setVisible(false);

  //  scene_jijin_anniu->setPosition(Point(visibleSize.width - 40,visibleSize.height - 205));
    
	scene_vip_anniu->setPosition(Vec2(visibleSize.width  - 40,visibleSize.height - 210));
	Guang1->setPosition(Point(visibleSize.width - 40,visibleSize.height - 210));

	m_Shop->setPosition(Point(visibleSize.width - 30,visibleSize.height - 120));  //∏ƒ±‰…Ã≥«∞¥≈•µƒŒª÷√
	Guang->setPosition(Point(visibleSize.width - 40,visibleSize.height - 130));
 
	cSelfPos = 8;

	for(int i=0; i< 4; i++)
	{
        bRobotVip[i] = false;
        bRobotPos[i] = false;
		iChangeRobotBaseTime[i] = 0;
		
		iChangeExPaoTime[i] = 0;
		iChangeExPaoRandTime[i] = 300+CCRANDOM_0_1()*2000;
		iChangeExPaoRandTimeEnd[i] = iChangeExPaoRandTime[i];
		
		iChangeRobotBaseRandTime[i] = 300+CCRANDOM_0_1()*2500;		
		/*char cTemp = CCRANDOM_0_1()*75;
		if(cTemp < 25)
		{
			iChangeRobotBaseRandTime[i] = 500+CCRANDOM_0_1()*1000;						 
		}
		else if(cTemp< 50)
		{
			iChangeRobotBaseRandTime[i] = 1500+CCRANDOM_0_1()*2000;			
		}
		else if(cTemp< 75)
		{
			iChangeRobotBaseRandTime[i] = 3500+CCRANDOM_0_1()*2000;			
		}
		else if(cTemp)
		{
			iChangeRobotBaseRandTime[i] = 6000+CCRANDOM_0_1()*3000;			
		}  
		*/
	}  
	ShootQuyu[0] = Rect(0,0,visibleSize.width/3,visibleSize.height/2);
	ShootQuyu[1] = Rect(visibleSize.width/3,0,visibleSize.width/3,visibleSize.height/2);
	ShootQuyu[2] = Rect(visibleSize.width*0.66,0,visibleSize.width/3,visibleSize.height/2);
	ShootQuyu[3] = Rect(0,visibleSize.height/2,visibleSize.width/3,visibleSize.height/2);
	ShootQuyu[4] = Rect(visibleSize.width/3,visibleSize.height/2,visibleSize.width/3,visibleSize.height/2);
	ShootQuyu[5] = Rect(visibleSize.width*0.66,visibleSize.height/2,visibleSize.width/3,visibleSize.height/2);

	int TempRandom =85;

	if(TempRandom < 40)
	{
		int iTempRandom2 = CCRANDOM_0_1()*400;
		if(iTempRandom2 < 100)
		{
			bRobotPos[1] = true;
			cRobotIQ[1] = GetRobotIQ();

			cSelfPos =  0;
		}
		else if(iTempRandom2 < 200)
		{
			bRobotPos[2] = true;
			cRobotIQ[2] = GetRobotIQ();
			if(CCRANDOM_0_1()*100 <50)
			{
				cSelfPos =  1;
			}
			else 
			{
				cSelfPos =  0;
			}

		}
		else if(iTempRandom2 < 300)
		{
			bRobotPos[3] = true;
			cRobotIQ[3] = GetRobotIQ();
			if(CCRANDOM_0_1()*100 <50)
			{
				cSelfPos =  1;
			}
			else 
			{
				cSelfPos =  0;
			}
		}
		else if(iTempRandom2 < 400)
		{
			bRobotPos[0] = true;
			cRobotIQ[0] = GetRobotIQ();
			cSelfPos =  1;
		}
	}
	else if(TempRandom  < 80)
	{
		int iTempRandom2 = CCRANDOM_0_1()*550;
		if(iTempRandom2 < 100)
		{
			bRobotPos[1] = true;
			cRobotIQ[1] = GetRobotIQ();
			bRobotPos[2] = true;
			cRobotIQ[2] = GetRobotIQ();
			cSelfPos =  0;
		}
		else if(iTempRandom2 < 200)
		{
			bRobotPos[2] = true;
			cRobotIQ[2] = GetRobotIQ();
			bRobotPos[3] = true;
			cRobotIQ[3] = GetRobotIQ();
			if(CCRANDOM_0_1()*100 <50)
			{
				cSelfPos =  1;
			}
			else 
			{
				cSelfPos =  0;
			}
		}
		else if(iTempRandom2 < 300)
		{
			bRobotPos[3] = true;
			cRobotIQ[3] = GetRobotIQ();
			bRobotPos[1] = true;
			cRobotIQ[1] = GetRobotIQ();
			cSelfPos = 0;
		}
		else if(iTempRandom2 < 400)
		{
			bRobotPos[0] = true;
			cRobotIQ[0] = GetRobotIQ();
			bRobotPos[2] = true;
			cRobotIQ[2] = GetRobotIQ();
			cSelfPos = 1;
		}
		else if(iTempRandom2 < 500)
		{
			bRobotPos[0] = true;
			cRobotIQ[0] = GetRobotIQ();
			bRobotPos[3] = true;
			cRobotIQ[3] = GetRobotIQ();
			cSelfPos = 1;
		}
		else if(iTempRandom2< 550) 
		{
			bRobotPos[2] = true;
			cRobotIQ[2] = GetRobotIQ();
			bRobotPos[3] = true;
			cRobotIQ[3] = GetRobotIQ();
			if(CCRANDOM_0_1()*100 <50)
			{
				cSelfPos =  1;
			}
			else 
			{
				cSelfPos =  0;
			}
		}
	}
	else 
	{
		bRobotPos[2] = true;
		cRobotIQ[2] = GetRobotIQ(); 			 
		bRobotPos[3] = true;
		cRobotIQ[3] = GetRobotIQ();
		
		cSelfPos = GameHallLayer::player_pos;
		if(cSelfPos == 1)
		{
			bRobotPos[0] = true;
			cRobotIQ[0] = GetRobotIQ();

		}
		else
		{ 
			bRobotPos[1] = true; 
			cRobotIQ[1] = GetRobotIQ();

		}
		CheckRobotIfVip();
	}
	memset(tmp_jfb,0,sizeof(tmp_jfb));
}

void GameScene::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
    GameBegin::removeSouce(1);
    GameBegin::removeSouce(2);
    
    TextureCache::getInstance()->removeUnusedTextures();
}

bool GameScene::init()
{ 
	if ( !Layer::init() )	
	{
		return false;
	}
    bOverBisai = false;
    
    iRoomType = GameHallLayer::RoomType;
    if(iRoomType == 89)
    {
        iRoomType = 90;
    }
  
    huidang_flag = 0;
    bShootSound = true;
    cUpdateShootSound = 0;
	GameBegin::curScene = 4;
    cUpdateSound = 0;
 
	cBeginTimeRobotShoot = 0;
	visibleSize = Director::getInstance()->getVisibleSize(); 
	origin = Director::getInstance()->getVisibleOrigin();
	Sprite* background;

    iPanziMoney = 0;
    bPlayPanzi = false;
    
    /*auto gonggao = Gonggao::create(1);
    gonggao->setPosition(Vec2(visibleSize.width/2 , visibleSize.height * 0.8));
    addChild(gonggao,1000);
    gonggao->setScale(0.8f);
    
    auto gonggao1 = Gonggao::create(2);
    gonggao1->setPosition(Vec2(visibleSize.width/2 , visibleSize.height * 0.7));
    addChild(gonggao1,1000);
    gonggao1->setScale(0.8f);
    
    auto gonggao2 = Gonggao::create(3);
    gonggao2->setPosition(Vec2(visibleSize.width/2 , visibleSize.height * 0.6));
    addChild(gonggao2,1000);
    gonggao2->setScale(0.8f);*/
    
    
 
         
	time_t current_t;
	time(&current_t);
	qiantaiTime = current_t;
	houtaiTime = current_t;
	 
	bTouch = true;
    bSound = true;
	bs_isjifen = true;

	iAddRobotTime = 0;
	stopBossTime = false;
	bShowShangCheng = false;

	haveQiongShen = false;
	bRed = false;

	cSelfPos = 8;
	wfsb = Sprite::create();
	this->addChild(wfsb);
	fTime = 0;
	m_iFishMoveTime = 0;
    
    for(int i=0; i< 4; i++)
    {
        cRobotShootTimeOverwf[i] = 1+CCRANDOM_0_1()*100;
        cRobotShootTimeWf[i] = 0;
    }
    

	GoNewSence = 0;
	bNoShoot = false;
	MoneyMoveUpdate = 0;
	MoneyMoveY[0] = -322; 
	MoneyMoveY[1] = -315; 
	MoneyMoveY[2] = -308; 
	MoneyMoveY[3] = -294; 
	MoneyMoveY[4] = -224; 
	MoneyMoveY[5] = -154;  
	MoneyMoveY[6] = -0; 
	char bgTmp[20];
    if(iRoomType < 3)
	{
        sprintf(bgTmp,"scene/scene%dBG.jpg",iRoomType + 1);
		background = Sprite::create(bgTmp);  
	}
	else if(iRoomType >2 && iRoomType < 12)
	{
        
        string fullLuJin = FileUtils::getInstance()->getWritablePath();
		sprintf(bgTmp,"scene%dBG.jpg",iRoomType + 1);
		background = Sprite::create(fullLuJin + bgTmp);  
	}
	else if(iRoomType > 89 && iRoomType < 94)
	{
 
            int iTemp =(CCRANDOM_0_1()*3);
            sprintf(bgTmp,"scene/scene%dBG.jpg",(iTemp%3) + 1);
            background = Sprite::create(bgTmp);
 
	}

	background->setPosition(Point(visibleSize.width*0.5,visibleSize.height*0.5));
	this->addChild(background); 
    
    m_SprBoss = Sprite::create();
    this->addChild(m_SprBoss);
    
	GameBegin::stopMusic();
	GameBegin::playMusic("bgmusic1.mp3",2);
 
	
	if(GameScene::cGameType != 2 && GameScene::cGameType != 1)
	{
		//»ŒŒÒ¥∞ø⁄**************
		mission = Mission::create();
		mission->setPosition(Vec2(100 * 0.833,visibleSize.height*0.8));
		this->addChild(mission,MENULAYER);
	}
	
	Animation* fishAnimation = AnimationCache::getInstance()->getAnimation("shuibo");
	Animate*  shuiboani[4];
	Sprite * shuibospr[4];

	for(int i=0; i< 4; i++)
	{
		bRobotPos[i] = false; 
		shuiboani[i] = Animate::create(fishAnimation);
		shuibospr[i] = Sprite::create(); 
		this->addChild(shuibospr[i]); 
		shuibospr[i]->setScale(2.0f);
		shuibospr[i]->setAnchorPoint(Vec2(0,0));
		shuibospr[i]->runAction(RepeatForever::create(shuiboani[i])); 
		shuibospr[i]->setOpacity(130);
		shuibospr[i]->setPosition(Vec2((i%4)*512,(i/2)*512));
	}  
 
	if(!UserDefault::getInstance()->getBoolForKey("IsBiSanUse"))
	{
		//Ω¯»Î±»»¸ƒ£ Ω
		auto hall_sprite_bs = Sprite::createWithSpriteFrameName("hall_bisai.png");
		hall_sprite_bs->setScale(0.7);
		hall_menu_bs = Menu::create(MenuItemSprite::create(hall_sprite_bs,hall_sprite_bs,CC_CALLBACK_0(GameScene::yindaoBiSai,this)),nullptr);
		hall_menu_bs->setPosition(Vec2( 60 + origin.x ,visibleSize.height*0.3 + origin.y));
		hall_menu_bs->setVisible(false);
		addChild(hall_menu_bs,ANNIULAYER+1);

		//±»»¸±≥æ∞π‚
		auto hall_bs_sp = Sprite::createWithSpriteFrameName("bgguang.png");
		hall_bs_sp->setPosition(Vec2(hall_sprite_bs->getContentSize().width * 0.5,hall_sprite_bs->getContentSize().height*0.55));
		hall_sprite_bs->addChild(hall_bs_sp,-1);
		hall_bs_sp->runAction(RepeatForever::create(RotateBy::create(1.0f,8)));

		//Àµ√˜Œƒ◊÷
		auto hall_bs_sm = Sprite::createWithSpriteFrameName("hall_bisai_ms1.png");
		auto hall_menu_bs_tishi = Menu::create(MenuItemSprite::create(hall_bs_sm,hall_bs_sm,CC_CALLBACK_0(GameScene::yindaoBiSai,this)),nullptr);
		hall_menu_bs_tishi->setPosition(Vec2(hall_sprite_bs->getContentSize().width * 2,hall_sprite_bs->getContentSize().height * 0.5));
		hall_sprite_bs->addChild(hall_menu_bs_tishi);
		hall_menu_bs_tishi->runAction(RepeatForever::create(Sequence::create(DelayTime::create(3.0f),FadeIn::create(0.5f),DelayTime::create(3.0f),FadeOut::create(0.5f),nullptr)));
	}
	
	float scaleTmp = 1;
	float tmp_x = visibleSize.width;
	float tmp_y = visibleSize.height*0.5;

	  //≤Àµ•∞¥≈•
	menu_shezhi_cl = Sprite::createWithSpriteFrameName("hall_menu_shezhi_1.png");
	menu_shezhi_cl->setScale(scaleTmp);
	m_GameMenu= Menu::create(MenuItemSprite::create(menu_shezhi_cl,menu_shezhi_cl,CC_CALLBACK_1(GameScene::GameSetox,this)),nullptr);
	m_GameMenu->setPosition(Vec2(tmp_x,tmp_y));  
	this->addChild(m_GameMenu,MENULAYER+110);

	//≤Àµ•…˝∆±Í ∂
	bGameSetShow = false;

	//”Œœ∑ÕÀ≥ˆ
	auto hall_sprite_tuichu = Sprite::createWithSpriteFrameName("hall_menu_tuichu.png");
	hall_sprite_tuichu->setScale(scaleTmp);
	auto hall_sprite_tuichu_d = Sprite::createWithSpriteFrameName("hall_menu_tuichu_d.png");
	hall_sprite_tuichu_d->setScale(scaleTmp);
	gameQuitMenu = Menu::create(MenuItemSprite::create(hall_sprite_tuichu,hall_sprite_tuichu_d,CC_CALLBACK_1(GameScene::GameQuit,this)),nullptr);
	gameQuitMenu->setPosition(Vec2(tmp_x,tmp_y));  
	gameQuitMenu->setVisible(false);
	gameQuitMenu->setEnabled(false);
	this->addChild(gameQuitMenu,MENULAYER+ 110- 1);

	//∞Ô÷˙
    auto hall_sprite_bangzhu = Sprite::createWithSpriteFrameName("hall_menu_kefu.png");
    hall_sprite_bangzhu->setScale(scaleTmp);
    auto hall_sprite_bangzhu_d = Sprite::createWithSpriteFrameName("hall_menu_kefu_d.png");
    hall_sprite_bangzhu_d->setScale(scaleTmp);
	gameHelpMenu = Menu::create(MenuItemSprite::create(hall_sprite_bangzhu,hall_sprite_bangzhu_d,CC_CALLBACK_1(GameScene::GameHelp,this)),nullptr);
	gameHelpMenu->setPosition(Vec2(tmp_x,tmp_y));
	gameHelpMenu->setVisible(false);
	gameHelpMenu->setEnabled(false);
	addChild(gameHelpMenu,MENULAYER+ 110 - 2);

	//…˘“Ù

    if(!GameHallLayer::hall_bShengyinShow)
    {
        hall_sprite_shengyin = Sprite::createWithSpriteFrameName("hall_menu_shengyin_g.png");
        hall_sprite_shengyin_d = Sprite::createWithSpriteFrameName("hall_menu_shengyin_g_d.png");
    }else
    {
        hall_sprite_shengyin = Sprite::createWithSpriteFrameName("hall_menu_shengyin_k.png");
        hall_sprite_shengyin_d = Sprite::createWithSpriteFrameName("hall_menu_shengyin_k_d.png");
    }
	hall_sprite_shengyin->setScale(scaleTmp);
	hall_sprite_shengyin_d->setScale(scaleTmp);
	gameSetMenu = Menu::create(MenuItemSprite::create(hall_sprite_shengyin,hall_sprite_shengyin_d,CC_CALLBACK_1(GameScene::GameSet,this)),nullptr);
	gameSetMenu->setPosition(Vec2(tmp_x,tmp_y));
	gameSetMenu->setVisible(false);
	gameSetMenu->setEnabled(false);
	addChild(gameSetMenu,MENULAYER+ 110 - 3);


	//¿Ò∆∑¬
	auto hall_sprite_lipin = Sprite::createWithSpriteFrameName("hall_menu_lipin.png");
	hall_sprite_lipin->setScale(scaleTmp);
	auto hall_sprite_lipin_d = Sprite::createWithSpriteFrameName("hall_menu_lipin_d.png");
	hall_sprite_lipin_d->setScale(scaleTmp);
	gameLipinmaMenu = Menu::create(MenuItemSprite::create(hall_sprite_lipin,hall_sprite_lipin_d,CC_CALLBACK_1(GameScene::GameLipin,this)),nullptr);
	gameLipinmaMenu->setPosition(Vec2(tmp_x,tmp_y));
	gameLipinmaMenu->setVisible(false);
	gameLipinmaMenu->setEnabled(false);
	addChild(gameLipinmaMenu,MENULAYER+ 110 - 4);

	float scene_scale = 0.9;
	//…Ã≥«∞¥≈•
	Guang = Sprite::createWithSpriteFrameName("bgguang.png");
	Guang->setScale(scene_scale -0.2);
	Guang->setPosition(Point(tmp_x - 40,visibleSize.height - 40));
	auto  sf = CCRotateBy::create(4.0f,360); 
	Guang->runAction(RepeatForever::create(sf)); 
	this->addChild(Guang,MENULAYER + 99);  

	auto shangcheng  = Sprite::createWithSpriteFrameName("shangcheng.png");  
	shangcheng->setScale(scene_scale);
	m_Shop = Menu::create(MenuItemSprite::create(shangcheng,shangcheng, shangcheng,CC_CALLBACK_1(GameScene::menuShop,this)),NULL); 
	m_Shop->setPosition(Point(tmp_x  - 35,visibleSize.height - 35));
	this->addChild(m_Shop,MENULAYER+ 100);
 
	//‘⁄œﬂ¡ÏΩ±∞¥≈•
	jiasuspr10 = Sprite::createWithSpriteFrameName("chongzhi.png"); 
	jiasuspr10->setScale(scene_scale);
	m_AddMoney = Menu::create(MenuItemSprite::create(jiasuspr10,jiasuspr10, jiasuspr10,CC_CALLBACK_1(GameScene::AddMoney,this)),nullptr); 
	m_AddMoney->setPosition(Point(tmp_x  - 35,visibleSize.height - 195));
	this->addChild(m_AddMoney,MENULAYER+ 100);
	if(GameScene::cGameType == 2 || GameScene::cGameType == 1)
	{
		m_AddMoney->setVisible(false);
	}


	m_zaixianGuang = Sprite::createWithSpriteFrameName("bgguang.png");
	m_zaixianGuang->setScale(scene_scale-0.2);
	m_zaixianGuang->setPosition(Point(tmp_x  - 40,visibleSize.height-200));
	this->addChild(m_zaixianGuang,MENULAYER +  99);
	m_zaixianGuang->setVisible(false);
  
    //基金
 //   auto jijin_sp = Sprite::createWithSpriteFrameName("jijin_icon.png");
 //   scene_jijin_anniu = Menu::create(MenuItemSprite::create(jijin_sp,jijin_sp,CC_CALLBACK_0(GameScene::menu_jijin,this)),nullptr);
 //   scene_jijin_anniu->setPosition(Vec2( tmp_x - 40 ,visibleSize.height - 120));
  //  scene_jijin_anniu->setVisible(false);
   // addChild(scene_jijin_anniu,MENULAYER + 99);
 
	//vip
	Guang1 = Sprite::createWithSpriteFrameName("bgguang.png");
	Guang1->setScale(scene_scale-0.2);
	Guang1->setPosition(Point(tmp_x - 40,visibleSize.height - 120));
	auto  sf1 = CCRotateBy::create(4.0f,360); 
	Guang1->runAction(RepeatForever::create(sf1)); 
	this->addChild(Guang1,MENULAYER + 99);  
	
	if(UserDefault::getInstance()->getIntegerForKey("player_vip")==0)
	{
		scene_vip_sp = Sprite::createWithSpriteFrameName("Vip_icon.png");
	}else
	{
		scene_vip_sp = Sprite::createWithSpriteFrameName("Vip_icon1.png");
	}
	auto vip_item = MenuItemSprite::create(scene_vip_sp,scene_vip_sp,CC_CALLBACK_0(GameScene::menu_viptequan,this));
	vip_item->setScale(0.56f);
	scene_vip_anniu = Menu::create(vip_item,nullptr);
	scene_vip_anniu->setPosition(Vec2( tmp_x - 40 ,visibleSize.height - 120));
	addChild(scene_vip_anniu,MENULAYER + 99);
 
    if(LogoLayer::dengluFlag && UserDefault::getInstance()->getIntegerForKey("player_vip")==1)
    {
        Guang1->setVisible(false);
        scene_vip_anniu->setVisible(false);
    }
	//√ø»’Ãÿ»®
	time_t currentTime;
	time(&currentTime);
	time_t prevTime = UserDefault::getInstance()->getIntegerForKey("vip_login_time");
    
	if(UserDefault::getInstance()->getIntegerForKey("player_vip")!=0 && currentTime > prevTime)
	{
		scene_vip_anniu->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f,Vec2(0,10)),MoveBy::create(0.25f,Vec2(0,-5)),MoveBy::create(0.25f,Vec2(0,5)),MoveBy::create(0.5f,Vec2(0,-10)),nullptr)));
    }
    else if(UserDefault::getInstance()->getIntegerForKey("player_vip")!=0 && currentTime < prevTime)
    {
        scene_vip_anniu->setVisible(false);
        Guang1->setVisible(false);
//        scene_jijin_anniu->setVisible(true);
    }
 
    
    if(UserDefault::getInstance()->getIntegerForKey("ios_dengluFlag") == 1)
    {
//        scene_jijin_anniu->setVisible(false);
    }
 
 
 
	m_pFishLayer = FishLayer::create();
	this->addChild(m_pFishLayer);

	cocos2d::log("oo3winitMap4");

	init_jishi();
		
	if(cGameType == 1)
	{
		init_bisai();
	}

	m_pCannonLayer =  CannonLayer::create();
	this->addChild(m_pCannonLayer,99); 

	cocos2d::log("gamescene init center");

	m_fRobotShootTime = 0;
	m_fUpdateTime = 0;
	m_fTime = 0;
	bCanShootDanji = true;
	bCanShoot = false;  

	m_fUpdateTimeDanJi =0;
	m_fTimeDanJi = 0; 
	cTouchNum = 0;
	iXunHuan = 0;

	//ooxx
	bSaJingbi = false;
	sajinbi = ParticleSystemQuad::create("jinbi.plist");
	sajinbi->retain();
	auto batch = ParticleBatchNode::createWithTexture(sajinbi->getTexture()); 
	batch->addChild(sajinbi); 
	sajinbi->stopSystem();
	addChild(batch);  
	m_BaoZha1 = NULL;
	if(GameScene::cGameType != 1)
	{

		m_BaoZha1 = ParticleSystemQuad::create("baoza04.plist");
		m_BaoZha1->retain();
		auto batch4 = ParticleBatchNode::createWithTexture(m_BaoZha1->getTexture()); 
		batch4->addChild(m_BaoZha1); 
		m_BaoZha1->stopSystem();
		addChild(batch4); 
	}

	m_BaoZha2 = ParticleSystemQuad::create("baoza05.plist");
	m_BaoZha2->retain();
	auto batch2 = ParticleBatchNode::createWithTexture(m_BaoZha2->getTexture()); 
	batch2->addChild(m_BaoZha2);
	m_BaoZha2->stopSystem();
	addChild(batch2); 

	m_BaoZha3 = ParticleSystemQuad::create("baoza02.plist");
	m_BaoZha3->retain();
	auto batch3 = ParticleBatchNode::createWithTexture(m_BaoZha3->getTexture()); 
	batch3->addChild(m_BaoZha3);
	m_BaoZha3->stopSystem();
	addChild(batch3); 
	 


	panziguang  = Sprite::create();
	this->addChild(panziguang);
	temp2 =  Sprite::createWithSpriteFrameName("bfishbgguang.png");
	this->addChild(temp2);
	temp2->setVisible(false);


	LabelFishNum = Label::create();  
	LabelFishNum->setCharMap("img/bfishnum.png",35,57,'0'); 
	this->addChild(LabelFishNum); 
	LabelFishNum->setVisible(false);
	//schedule(schedule_selector(GameScene::updateInfo),0.04f);


	EventListenerKeyboard* kblsnr = EventListenerKeyboard::create(); 
	kblsnr->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this); 
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(kblsnr, this); 

	scheduleOnce(schedule_selector(GameScene::OpenTouch),0.5f);

	cocos2d::log("scene init end");

	return true;
}

void GameScene::load_gailv(char cinfo)
{
    //÷¥––∏≈¬ œ¬‘ÿ
    CURL *curl;
    CURLcode res;
    std::string cc;
    curl=curl_easy_init();
    
    if(curl)
    {
        if(cinfo == 0)
        {
            
                curl_easy_setopt( curl, CURLOPT_URL, "http://dwby-hk.iyueyo.com/qpby2/iosfanti/gailv0_5.2.php"); //«Î«Ûµƒµÿ÷∑
        }
        else if(cinfo == 1)
        {
            
                curl_easy_setopt( curl, CURLOPT_URL, "http://dwby-hk.iyueyo.com/qpby2/iosfanti/gailv1_5.2.php"); //«Î«Ûµƒµÿ÷∑
        }
        else if(cinfo == 2)
        {
                curl_easy_setopt( curl, CURLOPT_URL, "http://dwby-hk.iyueyo.com/qpby2/iosfanti/gailv2_5.2.php"); //«Î«Ûµƒµÿ÷∑
        }
        else if(cinfo == 3)
        {
            
                curl_easy_setopt( curl, CURLOPT_URL, "http://dwby-hk.iyueyo.com/qpby2/iosfanti/gailv3_5.2.php"); //«Î«Ûµƒµÿ÷∑
        }
        else if(cinfo == 4)
        {
            
                curl_easy_setopt( curl, CURLOPT_URL, "http://dwby-hk.iyueyo.com/qpby2/iosfanti/gailv4_5.2.php"); //«Î«Ûµƒµÿ÷∑
        }
        
        
        curl_easy_setopt(curl,CURLOPT_TIMEOUT,3000);
        curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&load_gailv_call); //¥¶¿Ìµƒ∫Ø ˝
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

size_t GameScene::load_gailv_call(uint8_t *buffer,size_t size,size_t nmemb,void *stream)
{
    cocos2d::log("buffer jia = %s ", (const char *)buffer);
    
    
    char cLoadGailvRoomType = 0;
    
    if(GameHallLayer::RoomType ==89)
    {
        cLoadGailvRoomType = 4;
        
    }
    else
    {
        cLoadGailvRoomType= GameHallLayer::RoomType-90;
    }
    
    //¥Ú”° ’µΩµƒ ˝æ›
    char tmp[10]="";
    
    int gailv_tmp = 0;
    int i=0;
    int j=0;
    
    while(buffer[i]!='\0')
    {
        char c = buffer[i];
        if(c=='%')
        {
            if( gailv_tmp < 33)
            {
                GameScene::gailv_jian[gailv_tmp] = atof(tmp);
            }
            else if(gailv_tmp < 66)
            {
                GameScene::gailv_jia[gailv_tmp - 33] = atof(tmp);
            }
            else if(gailv_tmp == 66)
            {
                GameScene::jian_gailv = atof(tmp);
            }
            else if(gailv_tmp == 67)
            {
                GameScene::jia_gailv = atof(tmp);
            }
            else if(gailv_tmp == 68)
            {
                GameScene::gailv_shijian = atoi(tmp);
                gailv_tmp = 0 ;
                GameScene::is_success_load = true;
                break;
                
            }
            
            gailv_tmp++;
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

void GameScene::yindaoBiSai()
{
	if( GameBegin::getFileData("gameMaxPao.txt")< 4)
	{
		char tmpTmp[200];
		sprintf(tmpTmp,GAME_DATA_STRING("gamehall_beilv_low"),10);

		auto layer = Gongxi::create(2,tmpTmp);
		this->addChild(layer,MENULAYER);
	}else
	{
		UserDefault::getInstance()->setIntegerForKey("bisaimoshi",0);
		UserDefault::getInstance()->flush();
		queding();
	}
	
}

void GameScene::menu_viptequan()
{
	char hallCharTemp[100];
	if(UserDefault::getInstance()->getIntegerForKey("player_vip") == 0)
	{
		auto scene = Shop::create(5);
		this->addChild(scene,MENULAYER+10000);
	}else
	{
        scene_vip_anniu->stopAllActions();
        
        scene_vip_anniu->setVisible(false);
        Guang1->setVisible(false);
     //   scene_jijin_anniu->setVisible(true);
 
        sprintf(hallCharTemp,GAME_DATA_STRING("login_yubi"),20000,200);
        auto  gongxi = VIPgongxi::create(4);
        this->addChild(gongxi,MENULAYER + 100);

        CannonLayer::GameCoinRefresh(20000);
        CannonLayer::GameCoinZuanshi(200);

        int loginDays = UserDefault::getInstance()->getIntegerForKey("Vip_loginDays") + 1;
        
        time_t currentTime;
        time(&currentTime);
        
        struct tm *nowTime = gmtime(&currentTime);
        int hour=nowTime->tm_hour;
        int minute=nowTime->tm_min;
        int second=nowTime->tm_sec;
        time_t nextTime = currentTime + 24*60*60 - hour*60*60 - minute*60 - second;

        UserDefault::getInstance()->setIntegerForKey("vip_login_time",nextTime);
        UserDefault::getInstance()->setIntegerForKey("Vip_loginDays",loginDays);
        UserDefault::getInstance()->flush();
    }
 
}

void GameScene::menu_jijin()
{
    ShopJJ::come_kind_jj = 2;
    
    auto layer = ShopJJ::createScene();
    this->addChild(layer,MENULAYER * 2);
}

//ª˝∑÷∞Êœ‡πÿ∫Ø ˝
void GameScene::bs_jifenban_hs()
{
	if(bs_isjifen)
	{
		bs_isjifen = false;
		bs_jifenban->runAction(MoveBy::create(0.5f,Vec2(-160,0)));
	}else
	{
		bs_isjifen = true;
		bs_jifenban->runAction(MoveBy::create(0.5f,Vec2(160,0)));
	}
}

void GameScene::bs_jiafen(int i , int num)
{

	if(i== 3)
	{

		char tmp[50];
		bs_jfb_num[i] += num;
		sprintf(tmp,"%lld",bs_jfb_num[i]);
		bs_jfb_l[i]->setString(tmp);
	}


	/*char tmp[200];
	bs_jfb_num[i] += num;
	sprintf(tmp,"%lld",bs_jfb_num[i]);
	bs_jfb_l[i]->setString(tmp);

	FenShu tmp_int[4]; //±£¥Êµ±«∞µƒ∑÷ ˝ ˝◊È

	for(int i = 0 ; i < 4 ; i++)
	{
		tmp_int[i].fenshu = bs_jfb_num[i];
		tmp_int[i].flag = i;
	}
	//∂‘¡Ÿ ± ˝◊È≈≈–Ú
	FenShu tmp_fenshu;
	int tmp_int_t;
	for(int i = 0; i < 4 ; i++)
	{
		tmp_int_t = i;
		for(int j = i+1 ; j < 4; j++)
		{		
			if(tmp_int[tmp_int_t].fenshu < tmp_int[j].fenshu)
			{			
				tmp_int_t = j;
			}
		}
		tmp_fenshu.fenshu = tmp_int[tmp_int_t].fenshu;
		tmp_fenshu.flag = tmp_int[tmp_int_t].flag;

		tmp_int[tmp_int_t] = tmp_int[i];
		tmp_int[i] = tmp_fenshu;
		cocos2d::log("tmp_int . fenghsu = %lld  flag = %d ",tmp_int[i].fenshu , tmp_int[i].flag);
	}

	//∂‘∑÷ ˝label≈≈–Ú
	for(int i = 0 ; i < 4 ; i ++)
	{
		bs_jfb_l[tmp_int[i].flag]->runAction(MoveTo::create(0.2f,Vec2(18,8 + (3-i)*43)));
	}

	//∂‘√˚◊÷label≈≈–Ú
	for(int i = 0 ; i < 4 ; i ++)
	{
		bs_jfb_n[tmp_int[i].flag]->runAction(MoveTo::create(0.2f,Vec2(18,157 - i * 43)));
	}

	*/
}

void GameScene::bs_jifenban_sj(float dt)
{
	if(bs_isjifen)
	{
		bs_isjifen = false;
		bs_jifenban->runAction(MoveBy::create(0.5f,Vec2(-160,0)));
	}
}

void GameScene::CheckRobotIfVip()
{
	for(int i =0; i<4; i++)
	{
		if(bRobotPos[i] == true)
		{
			if(iRoomType == 93)
			{
				bRobotVip[i] = true;
			}
			else
			{
				if(cRobotIQ[i] == 1)
				{
					if(CCRANDOM_0_1()*100 < 10)
					{
						bRobotVip[i] = true;
					}				
				}
				else if(cRobotIQ[i] == 2)
				{
					if(CCRANDOM_0_1()*100 < 20)
					{
						bRobotVip[i] = true;
					}				
				}
				else if(cRobotIQ[i] == 3)
				{
					if(CCRANDOM_0_1()*100 < 30)
					{
						bRobotVip[i] = true;
					}	 
				} 
			}
			
		}
		cocos2d::log("robot[%d] is vip %d",i,bRobotVip[i]);
	}

	if(GameScene::cGameType == 1 &&iRoomType != 93)
	{

		int novip = 0;
		for(int i =0; i<4; i++)
		{
			if(bRobotPos[i] == true && bRobotVip[i]  == false)
			{
				novip ++;
			}
		}
		if(novip == 3)
		{
			char a ,b,c;
			a=b=c=66;

			for(int i =0; i<4; i++)
			{
				if(bRobotPos[i] == true && bRobotVip[i]  == false)		
				{
					if(a==66)
					{
						a= i;
					}
					else if(b == 66)
					{
						b= i;
					}
					else if(c == 66)
					{
						c =i;
					}
				}
			}

			int iTempRandom = CCRANDOM_0_1()*100;
			if(iTempRandom < 30)
			{
				bRobotVip[a] = true;
			}
			else if(iTempRandom <60)
			{
				bRobotVip[b] = true;
			}
			else
			{
				bRobotVip[c] = true;
			}
		}

	}

}

void GameScene::CheckRobotShoot(char cRobotPos)
{
	
	char cType = 0; 

	if(m_pCannonLayer->bChangeRobotBaseIfOver[cRobotPos] == true)
		return;
    for(int k =0; k< 2; k++)
    {
        for(int i = 0; i< 6; i++)
        {
            ShootOverPoint[i].x = ShootQuyu[i].origin.x + CCRANDOM_0_1()*ShootQuyu[i].size.width;
            ShootOverPoint[i].y = ShootQuyu[i].origin.y + CCRANDOM_0_1()*ShootQuyu[i].size.height;
            
            
            if (!m_pFishLayer->m_Fishes.empty())
            {
                for(int j = 0; j< m_pFishLayer->m_Fishes.size(); j++)
                {
                    if(m_pFishLayer->m_Fishes[j]->bDead == false)
                    {
                        if(m_pFishLayer->m_Fishes[j]->CheckRadius(ShootOverPoint[i],0))
                        {
                            if(cType<  m_pFishLayer->m_Fishes[j]->getType())
                            {
                                cType = m_pFishLayer->m_Fishes[j]->getType();
                                m_pFishLayer->ShootFish[cRobotPos] = m_pFishLayer->m_Fishes[j];
                                
                                if(GameScene::cRobotIQ[cRobotPos] == 1)
                                {
                                    cRobotShootTimeOverwf[cRobotPos] = 40+CCRANDOM_0_1()*30;
                                    cRobotShootTimeWf[cRobotPos] = 0;
                                    
                                }
                                else if(GameScene::cRobotIQ[cRobotPos] == 2)
                                {
                                    cRobotShootTimeOverwf[cRobotPos] = 20+CCRANDOM_0_1()*30;
                                    cRobotShootTimeWf[cRobotPos] = 0;
                                }
                                else if(GameScene::cRobotIQ[cRobotPos] == 3)
                                {
                                    cRobotShootTimeOverwf[cRobotPos] = 1+CCRANDOM_0_1()*30;
                                    cRobotShootTimeWf[cRobotPos] = 0;
                                }
                                
                            }
                        }
                    }
                }
            }
        }
    }
	
}
 
char GameScene::GetRobotIQ()
{

	char cIQ = CCRANDOM_0_1()*100;
	
	if(iRoomType == 90)
	{
		if(cIQ < 10)
		{
			return 3;
		}
		else if(cIQ < 50)
		{
			return 2;
		}
		else
		{
			return 1;
		}
	}
	else if(iRoomType == 91)
	{
		if(cIQ < 10)
		{
			return 3;
		}
		else if(cIQ < 70)
		{
			return 2;
		}
		else
		{
			return 1;
		}
	}
	else if(iRoomType == 92)
	{
		if(cIQ < 15)
		{
			return 3;
		}
		else if(cIQ < 90)
		{
			return 2;
		}
		else
		{
			return 1;
		}
	}
	else if(iRoomType == 93)
	{   
		if(cIQ < 20)
		{
			return 3;
		}
		else if(cIQ < 70)
		{
			return 2;
		}
		else
		{
			return 1;
		}
	}
	
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) 
{    
	switch(keyCode)     
	{     
		//º‡Ã˝∑µªÿº¸        
	case EventKeyboard::KeyCode::KEY_ESCAPE:     
		{

			if(!GameHallLayer::exitIsCun)
			{
				GameHallLayer::exitIsCun = true;
				GameBegin::buttonSound(); 
				GameBegin::baidu_qiehuan();
				//ÕÀ≥ˆ∑øº‰Ã· æ
				string exitTmp = GAME_DATA_STRING("fisheries_exit");
				auto gongxi = Gongxi::create(3,exitTmp);
				gongxi->setPosition(Point::ZERO);
				this->addChild(gongxi,MENULAYER + 111,1000);

				auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png");
				auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(GameScene::queding,this));

				btnMenu = Menu::create(quedingItem,nullptr);
				btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
				gongxi->getChildByTag(1)->addChild(btnMenu,100);
			}
 
		}
		break;        
		//º‡Ã˝menuº¸   
	case EventKeyboard::KeyCode::KEY_MENU:   
		GameBegin::baidu_qiehuan();
	case EventKeyboard::KeyCode::KEY_HOME:
		GameBegin::baidu_qiehuan();
		break;   
	}
}

void GameScene::AddMoney(Ref* pSender)
{
	GameBegin::buttonSound();
	char tmp[50];
	if(lingjiang_state == 1)
	{
		auto lingjian = OnlineReward::createScene((lingj_time%3 + 1));
		this->addChild(lingjian,MENULAYER + 1100);
	}
	if(lingjiang_state == 0)
	{
		auto gongxi = Gongxi::create(2,GAME_DATA_STRING("LingState0One"));
		this->addChild(gongxi,MENULAYER + 1100);
	}
}	

void GameScene::menuGo(Ref* pSender)
{
	this->removeAllChildrenWithCleanup(true);
	this->unscheduleAllSelectors();
 
    GameBegin::removeSouce(3);
    
	auto scene = GameBegin::createScene(); 
	Director::getInstance()->replaceScene(scene);
} 

void GameScene::changeRank()
{
	char cRank[20];
	sprintf(cRank,"%d",wfAllRobot.getmyrank());
	wfRank->setString(cRank);
	wfRank->setZOrder(MENULAYER + 100);
}

void GameScene::paimingAni(int rank)
{
	wfRank->setZOrder(MENULAYER - 1);
 
	char cRank[20];
	sprintf(cRank,"%d",rank);
	wfRank1->setString(cRank);
	wfRank1->setScale(2.1);
	wodepaiming1->setScale(2.4);

 
	paimingXX->runAction(Sequence::create(DelayTime::create(0.1f), Spawn::create(FadeIn::create(0.1f),RotateBy::create(0.2f,40),ScaleTo::create(0.1f,3),nullptr),Spawn::create(FadeOut::create(0.2f),ScaleTo::create(0.2f,1),nullptr),nullptr));
 
	auto pm_sp1 = Spawn::create(FadeIn::create(0.2f),ScaleTo::create(0.2f,0.7),nullptr);
	auto pm_sp2 = Spawn::create(Sequence::create(MoveBy::create(0.05f,Vec2(0,5)),MoveBy::create(0.05f,Vec2(0,-10)),MoveBy::create(0.05f,Vec2(0,5)),nullptr),ScaleTo::create(0.2f,0.8),nullptr);
	auto pm_sp3 = Spawn::create(ScaleBy::create(0.1f,1.4),FadeOut::create(0.1f),nullptr);
	wodepaiming1->runAction(Sequence::create(pm_sp1,pm_sp2 ,pm_sp3,nullptr));
 
	auto rk_sp1 = Spawn::create(FadeIn::create(0.2f),ScaleTo::create(0.2f,0.7),nullptr);
	auto rk_sp2 = Spawn::create(Sequence::create(MoveBy::create(0.05f,Vec2(0,5)),MoveBy::create(0.05f,Vec2(0,-10)),MoveBy::create(0.05f,Vec2(0,5)),nullptr),ScaleTo::create(0.2f,0.8),nullptr);
	auto rk_sp3 = Spawn::create(ScaleBy::create(0.1f,1.4),FadeOut::create(0.1f),nullptr);
	wfRank1->runAction(Sequence::create(rk_sp1,rk_sp2 ,rk_sp3,nullptr));

	wodepaiming->runAction(Sequence::create(FadeOut::create(0.1f),DelayTime::create(0.2),FadeIn::create(0.05f),nullptr));
	wfRank->runAction(Sequence::create(FadeOut::create(0.1f),DelayTime::create(0.2),FadeIn::create(0.05f),CallFunc::create(CC_CALLBACK_0(GameScene::changeRank,this)),nullptr));
}

void GameScene::updateBossTime(float delta)
{  
    if(huidang_flag > 30)
    {
        huidang_flag = 0;
        GameBegin::baidu_qiehuan();
    }
    huidang_flag++;
    
	cocos2d::log("scene init updateBossTime 1");

	if(false)
	{
		if(OnlineStateInt == 60)
		{
			OnlineStateInt = 0;
			//¡™Õ¯—È÷§
			CURL *curl;
			CURLcode res;
			curl = curl_easy_init();
			if(curl)
			{
				curl_easy_setopt(curl, CURLOPT_URL, "http://www.baidu.com");  //www.baidu.com 
				curl_easy_setopt(curl,CURLOPT_TIMEOUT,1000);
				curl_easy_setopt(curl,CURLOPT_POSTFIELDS,"R = 10");
				res=curl_easy_perform(curl);
				if(res!=CURLE_OK)
				{
					//¡™Õ¯ ß∞‹	
					auto gongxi = Gongxi::create(3,GAME_DATA_STRING("check_order_7"));
					gongxi->setPosition(Point::ZERO);
					this->addChild(gongxi,MENULAYER+1000,999);


					auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png");
					auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(GameScene::queding,this));

					btnMenu = Menu::create(quedingItem,nullptr);
					btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
					gongxi->getChildByTag(1)->addChild(btnMenu,100);

					this->unscheduleAllSelectors();
					return ;
				} 
				curl_easy_cleanup(curl);

			}
			else
			{
				//¡™Õ¯ ß∞‹	
				auto gongxi = Gongxi::create(7,GAME_DATA_STRING("check_order_7"));
				gongxi->setPosition(Point::ZERO);
				this->addChild(gongxi,MENULAYER+1000,999);


				auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png");
				auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(GameScene::queding,this));

				btnMenu = Menu::create(quedingItem,nullptr);
				btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
				gongxi->getChildByTag(1)->addChild(btnMenu,100);
				this->unscheduleAllSelectors();
				return ;
			}
		}
		OnlineStateInt++;
	}
	if(FishLayer::cNewBoss >= 24 && cGameType == 2)
	{


		UserDefault::getInstance()->setBoolForKey("is_boss_suc",true);// «∑ÒÃÙ’Ω≥…π¶
		UserDefault::getInstance()->setBoolForKey("is_boss_suc1",true);// «∑ÒÃÙ’Ω≥…π¶
		UserDefault::getInstance()->setIntegerForKey("boss_day_times",UserDefault::getInstance()->getIntegerForKey("boss_day_times") - 1);//ÃÙ’Ω ß∞‹µƒ¥Œ ˝
 
		char tmp_boss_name[30];
		//Ω±“
		sprintf(tmp_boss_name,"bossmoney%d",iRoomType);
		int bossJinbi = BossMoney;// ChallengeBOSS::randNum(GAME_DATA_STRING(tmp_boss_name));
		UserDefault::getInstance()->setIntegerForKey("boss_get_money",UserDefault::getInstance()->getIntegerForKey("boss_get_money") + bossJinbi);

		//◊Í «
		sprintf(tmp_boss_name,"bosszuanshi%d",iRoomType);
		int bossZuanshi = BossZuanShi; //ChallengeBOSS::randNum(GAME_DATA_STRING(tmp_boss_name));
		UserDefault::getInstance()->setIntegerForKey("boss_get_zuanshi",UserDefault::getInstance()->getIntegerForKey("boss_get_zuanshi") + bossZuanshi);

		//Ω±±≠
		int bossJiangbei = 0;
		if(iRoomType == 22 ||iRoomType == 23)
			bossJiangbei = 1;
		UserDefault::getInstance()->setIntegerForKey("boss_get_jiangbei",UserDefault::getInstance()->getIntegerForKey("boss_get_jiangbei") + bossJiangbei);
		UserDefault::getInstance()->flush();
 
		unschedule(schedule_selector(GameScene::updateBossTime));
		this->scheduleOnce(schedule_selector(GameScene::TiaoZhanChengGong),2.8f);
		return;
	}

	if(bs_jifentime < 5.0f && cGameType == 1)
	{
		bs_jifentime ++ ;
		if(bs_jifentime == 5)
		{
			if(bs_isjifen)
			{
				bs_isjifen = false;
				bs_jifenban->runAction(MoveBy::create(0.5f,Vec2(-160,0)));
			}
		}
	}

	if(GameScene::cGameType == 2)
	{
		if(stopBossTime == true)
			return;
	}
 
	cTimeMiao--;
   // if(cTimeMin >0) cTimeMin = 0;
	if(GameScene::cGameType == 1)
	{
		cBeginTimeRobotShoot++;
		if(cBeginTimeRobotShoot >= 5)
		{
			cBeginTimeRobotShoot=5;
			wfAllRobot.sortandshoot(bs_jfb_num[3]);
 
			if(AllRobot::shanshan)
			{
				AllRobot::	shanshan = false;
				paimingAni(wfAllRobot.getmyrank());
			}
			else
			{
				char cRank[20];
				sprintf(cRank,"%d",wfAllRobot.getmyrank());
				wfRank->setString(cRank);
			}
		}
        
        if((gailv_load_times == gailv_shijian && is_success_load)||(gailv_load_times == -1 && is_success_load))
        {
         
            suiji_jiafen();
        }
        if(is_success_load)
            gailv_load_times++;
        
	}


	if(cTimeMiao <= 0)
	{
		cTimeMiao = 60;
		if(cTimeMin == 1 && GameScene::cGameType == 1)
		{
             
            bOverBisai = true;
			GameBegin::stopMusic();
			GameBegin::playMusic("bgmusic.mp3",6);

			auto bs_one_min_sp = Sprite::createWithSpriteFrameName("bs_one_min.png");
			bs_one_min_sp->setPosition(Point(visibleSize.width * 0.50,visibleSize.height* 0.8));
			addChild(bs_one_min_sp,MENULAYER+100); 

			bs_one_min_sp->runAction(Sequence::create(ScaleTo::create(0.2f,1.6), DelayTime::create(6.0f),RemoveSelf::create(),nullptr));
		}
		cTimeMin--;   
		if(cTimeMin < 0)
		{
			if(GameScene::cGameType == 2)
			{
				//wf007 BOSS ±º‰µΩ
				//µØ≥ˆπßœ≤øÚ 
				UserDefault::getInstance()->setBoolForKey("is_boss_suc1",false);// «∑ÒÃÙ’Ω≥…π¶
				char level[100]; 
				sprintf(level,GAME_DATA_STRING("tiaozhan_shibai"),500);
				auto gongxi = Gongxi::create(7,level);
				gongxi->setPosition(Point::ZERO);
				this->addChild(gongxi,MENULAYER + 111,1000); 
				this->unscheduleAllSelectors(); 
 
				auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png");
				auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(GameScene::queding,this));

				auto btnMenu = Menu::create(quedingItem,nullptr);
				btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
				gongxi->getChildByTag(1)->addChild(btnMenu,100);

				return;
			}
			else if(GameScene::cGameType == 1)
			{ 
				GameBegin::stopMusic();

				TimeMiao->setString("00");
				TimeMin->setString("00");

				/*MaoHao->setVisible(false);
				TimeMiao->setVisible(false);
				TimeMin->setVisible(false); */

                bTouch = false;
                if(haveQiongShen)
                {
                    this->removeChildByTag(8787,true);
                    haveQiongShen = false;
                }
                
				m_pCannonLayer->ShowMatchOver();
				unscheduleAllSelectors(); 
				return;
				//unschedule(schedule_selector(GameScene::updateBossTime));
			}
			else 
			{
				m_zaixianGuang->setVisible(true);
				auto  sf = CCRotateBy::create(4.0f,360); 
				m_zaixianGuang->runAction(RepeatForever::create(sf)); 

				auto tishi = TiShi::create(3,GAME_DATA_STRING("LingJiang1"),GAME_DATA_STRING("LingJiang2"),3,0); 
				tishi->setPosition(Point(visibleSize.width - 150,visibleSize.height-250)); 
				this->addChild(tishi,120);   

				MaoHao->setVisible(false);
				TimeMiao->setVisible(false);
				TimeMin->setVisible(false); 
				lingjiang_state = 1; 
				unschedule(schedule_selector(GameScene::updateBossTime));
				return;
			}			
		}
	}
	char cTemp[20];
	if(cTimeMin < 10)
	{
		sprintf(cTemp,"0%d",cTimeMin);
	}
	else
	{
		sprintf(cTemp,"%d",cTimeMin);
	}
	TimeMin->setString(cTemp);

	memset(cTemp,0,sizeof(cTemp));

	if(cTimeMiao < 10)
	{

		sprintf(cTemp,"0%d",cTimeMiao);
	}
	else
	{

		sprintf(cTemp,"%d",cTimeMiao);
	}

	TimeMiao->setString(cTemp);

	cocos2d::log("scene init updateBossTime 2");

}

void GameScene::TiaoZhanChengGong(float dt)
{
	char level[100];
	sprintf(level,GAME_DATA_STRING("tiaozhan_chenggong"),500);
	auto gongxi = Gongxi::create(8,level);
	this->addChild(gongxi,MENULAYER + 111,1000); 
	this->unscheduleAllSelectors(); 

	auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png");
	auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(GameScene::queding,this));

	auto btnMenu = Menu::create(quedingItem,nullptr);
	btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
	gongxi->getChildByTag(1)->addChild(btnMenu,100);
}

bool  GameScene::SetTimeLingJiang() 
{
	int num = UserDefault::getInstance()->getIntegerForKey("ZaiXianTime");  

	 
	if(num == 0)
	{
		cTimeMin = 0;
		cTimeMiao = 30;
		LingMoney = 300;
	}
	else if(num == 1)
	{
		//cTimeMin = 0;
		cTimeMin = 0;
		cTimeMiao = 60;
		LingMoney =600;
	} 
	else if(num == 2)
	{
		//cTimeMin = 0;
		cTimeMin = 1;
		cTimeMiao = 30;  
		LingMoney =88;
	}
	else 
	{
		time_t currentTime;
		time(&currentTime);
		struct tm *nowTime = localtime(&currentTime);
		int hour=nowTime->tm_hour;  
		int minute=nowTime->tm_min;  
		int second=nowTime->tm_sec;
		time_t prevTime = currentTime + 24*60*60 - hour*60*60 - minute*60 - second; 
		UserDefault::getInstance()->setIntegerForKey("bendiTime",prevTime); 
		return false;
	}

	num++;
	UserDefault::getInstance()->setIntegerForKey("ZaiXianTime",num);
	UserDefault::getInstance()->flush(); 

	return true;

}

void GameScene::menuShop(Ref* pSender)
{
	auto scene = Shop::create(2);
	this->addChild(scene,MENULAYER + 111);
} 
 
void GameScene::exitRoom(float dt)
{
	this->removeAllChildrenWithCleanup(true);
	this->unscheduleAllSelectors(); 
 
    GameBegin::removeSouce(3);
    
	auto scene = GameHallLayer::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameScene::queding()
{
     
	if(GameScene::cGameType != 2)
	{
		//btnMenu->setEnabled(false);
	}
	if(GameScene::cGameType == 0)
	{
		 UserDefault::getInstance()->setIntegerForKey("ZaiXianMin",cTimeMin);
		 UserDefault::getInstance()->setIntegerForKey("ZaiXianMiao",cTimeMiao);
		 time_t currentTime;
		 time(&currentTime);
		 UserDefault::getInstance()->setDoubleForKey("preTime",currentTime);
		 UserDefault::getInstance()->flush();
	}

	GameBegin::baidu_qiehuan();
	GameHallLayer::exitIsCun = false;
 
	bNoShoot = true;
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects(); 


    m_pFishLayer->RemoveAllFish();

	this->removeAllChildrenWithCleanup(true);
	this->unscheduleAllSelectors(); 

	cocos2d::log("exit scene !");
 
	if(GameScene::cGameType == 2)
	{  
		GameBegin::removeSouce(3);
        
		auto scene = ChallengeBOSS::createScene();
		Director::getInstance()->replaceScene(scene);
		GameScene::cGameType = 0;

	}
	else
	{
        
        GameBegin::removeSouce(3);
		auto scene = GameHallLayer::createScene();
		Director::getInstance()->replaceScene(scene);
		GameScene::cGameType = 0;
 
	}


}

void GameScene::quxiao()
{
	this->removeChildByTag(1000);
}
 
 
GameScene::~GameScene()
{

	//ooxx
	CC_SAFE_RELEASE(sajinbi);

	 

		CC_SAFE_RELEASE(m_BaoZha1);
	CC_SAFE_RELEASE(m_BaoZha2);
	CC_SAFE_RELEASE(m_BaoZha3); 

	

	//CC_SAFE_RELEASE(m_pMenuLayer);
}

void GameScene::cannonAimAt(Point target)
{
	m_pCannonLayer->aimAt(target);
}
 
void GameScene::RobotcannonAimAt(Point target,char cPos)
{
	m_pCannonLayer->aimAtRobot(target,cPos);
}
 
void GameScene::RobotCannonShootTo(Point target,char cPos)
{ 
	if(m_pCannonLayer->RobotshootTo(target,cPos) == false)
	{
        
	}
} 

void GameScene::cannonShootTo(Point target)
{
	if(m_pCannonLayer->shootTo(target) == false)
	{  
		/*if(bShowShangCheng == false)
		{
			bShowShangCheng = true;	
			auto layer = Shop::create(2);
			layer->setPosition(Point::ZERO);
			this->addChild(layer,MENULAYER+101); 
		}*/

		if(!haveQiongShen) // GameBegin::getFileData("jywer.txt") == 0 &&
		{
 
			haveQiongShen = true; 
			auto qiongshenlayer = QiongShenLayer::createScene();
			qiongshenlayer->setPosition(Vec2::ZERO);
			this->addChild(qiongshenlayer,MENULAYER-1,8787);
		}
	}


} 

void GameScene::OpenTouch(float delta)
{  	
	cocos2d::log("scene init OpenTouch1");
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded,this);
	listener->setSwallowTouches(true);//≤ªœÚœ¬¥´µ›¥•√˛
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);


	  //µØ≥ˆ”„¿‡∞Ÿø∆
 
	  cUpdateTime = 0;
	schedule(schedule_selector(GameScene::updateScence),0.01f);

	cocos2d::log("scene init OpenTouch2");
		//schedule(schedule_selector(GameScene::checkOutCollision),0.05f);

}

void GameScene::updateInfo(float delta)
{  
	


}

void GameScene::menuGoSence(Ref* pSender)
{
	//÷ÿ÷√µ±«∞◊ÓµÕpao∫Õ ◊Ó∏ﬂpao
	char sceneLowRateTmp[20];
	sprintf(sceneLowRateTmp,"boss_low_odd_%d",1 + 1);
	char sceneHighRateTmp[20];
	sprintf(sceneHighRateTmp,"boss_high_%d",1 + 1);
	GameHallLayer::sceneLowPao = GAME_DATA_INT(sceneLowRateTmp);
	GameHallLayer::sceneHighPao = GAME_DATA_INT(sceneHighRateTmp);

	GameHallLayer::RoomType =1;

	this->removeAllChildrenWithCleanup(true);
	this->unscheduleAllSelectors(); 

	int containerLayerx = UserDefault::getInstance()->getIntegerForKey("hallDistance") + 318;
	UserDefault::getInstance()->setFloatForKey("hallDistance",containerLayerx) ;

	UserDefault::getInstance()->setIntegerForKey("ZaiXianMin",cTimeMin);
	UserDefault::getInstance()->setIntegerForKey("ZaiXianMiao",cTimeMiao);
	UserDefault::getInstance()->flush();
	 

    
    GameBegin::removeSouce(3);
    
	LoadRes::RoomType = 1;
	auto scene = LoadRes::createScene();	
	Director::getInstance()->replaceScene(scene);  

} 
 
void GameScene::menuGoSenceTwo(Ref* pSender)
{
 
	//÷ÿ÷√µ±«∞◊ÓµÕpao∫Õ ◊Ó∏ﬂpao
	char sceneLowRateTmp[20];
	sprintf(sceneLowRateTmp,"boss_low_odd_%d",1 + 2);
	char sceneHighRateTmp[20];
	sprintf(sceneHighRateTmp,"boss_high_%d",1 + 2);
	GameHallLayer::sceneLowPao = GAME_DATA_INT(sceneLowRateTmp);
	GameHallLayer::sceneHighPao = GAME_DATA_INT(sceneHighRateTmp);

	GameHallLayer::RoomType =2;

	this->removeAllChildrenWithCleanup(true);
	this->unscheduleAllSelectors(); 

	int containerLayerx = UserDefault::getInstance()->getIntegerForKey("hallDistance") + 318;
	UserDefault::getInstance()->setIntegerForKey("hallDistance",containerLayerx) ;

	UserDefault::getInstance()->setIntegerForKey("ZaiXianMin",cTimeMin);
	UserDefault::getInstance()->setIntegerForKey("ZaiXianMiao",cTimeMiao);
	UserDefault::getInstance()->flush();

    
    GameBegin::removeSouce(3);
    
	LoadRes::RoomType = 2;
	auto scene = LoadRes::createScene();	
	Director::getInstance()->replaceScene(scene);  
	 
} 
void GameScene::xiaxian()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void GameScene::updateScence(float delta)
{
    /*if(GameBegin::login_xiaxian)
    {
        GameBegin::login_xiaxian = false;
        
        auto zheZhao = LayerColor::create(ccc4(0,0,0,150),1024,768);
        zheZhao->setPosition(Point::ZERO);
        zheZhao->setScale(2.0f);
        this->addChild(zheZhao,1000,111);
        
        auto gongxi = Gongxi::create(7,GAME_DATA_STRING("dev_fail"));
        gongxi->setPosition(Point::ZERO);
        this->addChild(gongxi,MENULAYER,978);
        
        auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png" );
        auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(GameScene::xiaxian,this));
        auto btnMenu = Menu::create(quedingItem,nullptr);
        btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
        gongxi->getChildByTag(1)->addChild(btnMenu,100);
    }
*/
    
    char tmpqiong[20];
    sprintf(tmpqiong,"bljs_rate_%d",CannonLayer::_type + 1);
    if(haveQiongShen &&  GameBegin::getFileData("jywer.txt") >= GAME_DATA_INT(tmpqiong))
    {
        this->removeChildByTag(8787,true);
        haveQiongShen = false;
    }
    
	if(isqiehuan)
	{
		isqiehuan =  false;

        
		//queding();
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}

	if(isduankai && cGameType == 1)
	{
        this->unscheduleAllSelectors();
        bTouch = false;
        GameScene::isduankai = false;
        this->unschedule(schedule_selector(GameScene::updateBossTime));
        
        auto gongxi = Gongxi::create(7,GAME_DATA_STRING("bisai_over"));
        gongxi->setPosition(Point::ZERO);
        this->addChild(gongxi,10000,1000);
        
        auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png");
        auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(GameScene::queding,this));
        
        btnMenu = Menu::create(quedingItem,nullptr);
        btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
        gongxi->getChildByTag(1)->addChild(btnMenu,100);
 
	}
	if(isBiSaiVis)
	{
		isBiSaiVis = false;
        if(hall_menu_bs)
        {
            hall_menu_bs->runAction(Sequence::create(ToggleVisibility::create(),JumpBy::create(3.0f,Vec2(0,0),30,6),nullptr));
        }
		
		UserDefault::getInstance()->setBoolForKey("IsBiSanUse",true);
		UserDefault::getInstance()->flush();
	}
	if(lingjiangflag)
	{
		lingjiangflag = false;
		if(lingj_time == 0)
		{
			cTimeMiao = 60;
			cTimeMin = 0;
			lingjiang_state = 0;
			TimeMin->setVisible(true);
			TimeMiao->setVisible(true);
			MaoHao->setVisible(true);
			TimeMin->setString("00");
			TimeMiao->setString("60");
			m_zaixianGuang->setVisible(false);
			this->schedule(schedule_selector(GameScene::updateBossTime),1.0f);
		}
		if(lingj_time == 1)
		{
			cTimeMiao = 30;
			cTimeMin = 1;
			lingjiang_state = 0;
			TimeMin->setVisible(true);
			TimeMiao->setVisible(true);
			MaoHao->setVisible(true);
			TimeMin->setString("01");
			TimeMiao->setString("30");
			m_zaixianGuang->setVisible(false);
			this->schedule(schedule_selector(GameScene::updateBossTime),1.0f);
		}
		if(lingj_time == 2)
		{
			lingjiang_state = 0;
			TimeMin->setVisible(false);
			TimeMiao->setVisible(false);
			MaoHao->setVisible(false);
			m_AddMoney->setVisible(false);
			m_zaixianGuang->setVisible(false);
			unschedule(schedule_selector(GameScene::updateBossTime));
		}
		lingj_time++;
	}

   
    
    if( bCanShoot == true)
    {
        this->m_fUpdateTime += 1;
        if(this->m_fUpdateTime == m_fTime)
        {
            if(bShootSound == true)
            {
                bShootSound = false;
                GameBegin::playSound("shootok21.mp3");

            }
            bCanShootDanji = true;
            m_fUpdateTime = 0;
            m_fTime = 8;
            this->cannonShootTo(mTouchPos);
            this->cannonAimAt(mTouchPos);
        }
    }
    
    cUpdateSound ++;
    //if(cUpdateSound == 11)
    if(cUpdateSound == 15)
    {
        cUpdateSound = 0;
        bSound = true;
        
    }

    cUpdateShootSound ++;
    if(cUpdateShootSound == 16)
    {
        cUpdateShootSound = 0;
        bShootSound = true;
        
    }
    
    
    
	cUpdateTime ++;
	if(cUpdateTime == 2)
	{
        bTouch = true;
		cUpdateTime = 0;

			if(vip_goumai_flag)
			{
				vip_goumai_flag = false;

                if(!LogoLayer::dengluFlag)
                {
                    auto  gongxi = VIPgongxi::create(2);
                    this->addChild(gongxi,MENULAYER);
                }
				

				auto sp_frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Vip_icon1.png");
				scene_vip_sp->setDisplayFrame(sp_frame);

				scene_vip_anniu->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f,Vec2(0,10)),MoveBy::create(0.25f,Vec2(0,-5)),MoveBy::create(0.25f,Vec2(0,5)),MoveBy::create(0.5f,Vec2(0,-10)),nullptr)));
                
                if(LogoLayer::dengluFlag)
                {
                    menu_viptequan();
                    scene_vip_anniu->setVisible(false);
                }
			}
        if(GoNewSence == 1 || GoNewSence == 2)
        {
            char level[50];
            sprintf(level,GAME_DATA_STRING("gonewsence"),500);
            auto gongxi = Gongxi::create(7,level);
            gongxi->setPosition(Point::ZERO);
            this->addChild(gongxi,MENULAYER + 111,1000);
            this->unscheduleAllSelectors();
            
            auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png");
            auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(GameScene::queding,this));
            
            auto btnMenu = Menu::create(quedingItem,nullptr);
            btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
            gongxi->getChildByTag(1)->addChild(btnMenu,100);
        }
/*
			if(GoNewSence == 1)
			{
				GoNewSence = 0;
				bNoShoot = true; 
				FishLayer::bDingping = true;
				m_pCannonLayer->unscheduleAllSelectors();  
				auto zzLayer = LayerColor::create(ccc4(0,0,0,180),visibleSize.width,visibleSize.height);
				this->addChild(zzLayer,MENULAYER+102);   
				//∑øº‰µ◊≤ø±≥æ∞
				auto hall_room_bg = Sprite::createWithSpriteFrameName("hall_room_BG.png"); 
				hall_room_bg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
				//hall_room_bg->setScale(0.65);
				zzLayer->addChild(hall_room_bg);

				//∑øº‰Àı¬‘≥°æ∞±≥æ∞
				auto hall_room_slt_cj = Sprite::createWithSpriteFrameName("hall_scene_room2.png");	
				hall_room_slt_cj->setTag(100);
				hall_room_slt_cj->setScale(0.93);
				hall_room_slt_cj->setAnchorPoint(Vec2(0.5,1));
				hall_room_slt_cj->setPosition(Vec2(hall_room_bg->getContentSize().width/2, hall_room_bg->getContentSize().height - 30));
				hall_room_bg->addChild(hall_room_slt_cj);
 
				//Àı¬‘≥°æ∞÷–µƒboss
				auto hall_room_slt_boss = Sprite::createWithSpriteFrameName("fish_25_0 (1).png");
				hall_room_slt_boss->setPosition(Vec2(hall_room_slt_cj->getContentSize().width/2 , hall_room_slt_cj->getContentSize().height/2));
				float hall_room_bss_scale1 = hall_room_slt_cj->getContentSize().width * 0.7/ hall_room_slt_boss->getContentSize().width > 1 ?  1 : hall_room_slt_cj->getContentSize().width * 0.7/ hall_room_slt_boss->getContentSize().width;
				float hall_room_bss_scale2 = hall_room_slt_cj->getContentSize().height * 0.7/ hall_room_slt_boss->getContentSize().height > 1 ?  1 : hall_room_slt_cj->getContentSize().height * 0.7/ hall_room_slt_boss->getContentSize().height;
				float hall_room_bss_scale = hall_room_bss_scale1 > hall_room_bss_scale2 ? hall_room_bss_scale2 :hall_room_bss_scale1;
				hall_room_slt_boss->setTag(19);
				hall_room_slt_boss->setScale(hall_room_bss_scale);
				hall_room_slt_cj->addChild(hall_room_slt_boss);
				char tmp1[30];
				
				sprintf(tmp1,"fish_animationwf_%d_%d",LogoLayer::room,25);
				Animate * hall_boss_a = Animate::create(AnimationCache::getInstance()->getAnimation(tmp1));
				hall_room_slt_boss->runAction(RepeatForever::create(hall_boss_a));

				//∑øº‰µ◊≤ø–°±≥æ∞
				auto hall_room_slt = Sprite::createWithSpriteFrameName("hall_room_slt.png");
				hall_room_slt->setTag(104);
				hall_room_slt->setPosition(Vec2(hall_room_bg->getContentSize().width/2,hall_room_bg->getContentSize().height/2));
				hall_room_bg->addChild(hall_room_slt);



				//∑øº‰Ãı∑˘
				auto hall_room_tf = Sprite::createWithSpriteFrameName("hall_room_tf.png");
				hall_room_tf->setPosition(Vec2(hall_room_bg->getContentSize().width/2,hall_room_bg->getContentSize().height * 0.45));
				hall_room_bg->addChild(hall_room_tf);

				//∑øº‰√˚≥∆
				auto hall_room_name = Sprite::createWithSpriteFrameName("scenetitle2.png");
				hall_room_name->setPosition(Vec2(hall_room_tf->getContentSize().width/2,hall_room_tf->getContentSize().height * 0.68));
				hall_room_tf->addChild(hall_room_name);

				//∑øº‰¡¡π‚
				auto hall_room_lg = Sprite::createWithSpriteFrameName("hall_room_db_bjg.png");
				auto lg_fadeOut = FadeOut::create(0.4f);
				hall_room_lg->setPosition(Vec2(hall_room_bg->getContentSize().width/2,hall_room_bg->getContentSize().height - 40));
				hall_room_lg->setTag(101);		
				hall_room_lg->runAction(lg_fadeOut);
				hall_room_bg->addChild(hall_room_lg);

				//∑øº‰≥°æ∞À¯
				auto hall_room_suo = Sprite::createWithSpriteFrameName("lock_dh_8.png");
				hall_room_suo->setPosition(Vec2(35,hall_room_bg->getContentSize().height - 60));
				hall_room_suo->setTag(102);
				hall_room_bg->addChild(hall_room_suo);

				//Ω¯»Î≥°æ∞∞¥≈•
				auto hall_room_anniu = Sprite::createWithSpriteFrameName("hall_room_anniu.png");
				auto hall_room_item_anniu  = MenuItemSprite::create(hall_room_anniu,hall_room_anniu,CC_CALLBACK_1(GameScene::menuGoSence,this));
				auto hall_room_menu_anniu = Menu::create(hall_room_item_anniu,nullptr);
				hall_room_menu_anniu->setTag(103);
				hall_room_menu_anniu->setPosition(Vec2(hall_room_bg->getContentSize().width/2,hall_room_bg->getContentSize().height * 0.24));
				hall_room_bg->addChild(hall_room_menu_anniu);

				//Ω¯»Î”Ê≥°◊÷
				auto hall_room_jryc = Sprite::createWithSpriteFrameName("hall_room_jryc.png");
				hall_room_jryc->setTag(203);
				hall_room_jryc->setPosition(Vec2(hall_room_item_anniu->getContentSize().width/2,hall_room_item_anniu->getContentSize().height * 0.5));
				hall_room_item_anniu->addChild(hall_room_jryc,200);

				Animation* fishAnimation = AnimationCache::getInstance()->getAnimation("hand"); 
				Animate*  fishAnimate = Animate::create(fishAnimation);
				auto hand = Sprite::create();  

				hall_room_item_anniu->addChild(hand,200);
				hand->setTag(4);
				hand->runAction(RepeatForever::create(fishAnimate)); 
				hand->setPosition(Vec2(hall_room_item_anniu->getContentSize().width,hall_room_item_anniu->getContentSize().height - 50));

				auto sprxin = Sprite::createWithSpriteFrameName("gosencefont.png");
				sprxin->setPosition(Vec2(hall_room_bg->getContentSize().width/2,-40));
				sprxin->setTag(5);
				hall_room_bg->addChild(sprxin,200); 
			}
			else if(GoNewSence == 2)
			{
				GoNewSence = 0;
				bNoShoot = true;

				FishLayer::bDingping = true;
				m_pCannonLayer->unscheduleAllSelectors();  
				auto zzLayer = LayerColor::create(ccc4(0,0,0,180),visibleSize.width,visibleSize.height);
				this->addChild(zzLayer,MENULAYER+102);   
				//∑øº‰µ◊≤ø±≥æ∞
				auto hall_room_bg = Sprite::createWithSpriteFrameName("hall_room_BG.png"); 
				hall_room_bg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
				//hall_room_bg->setScale(0.65);
				zzLayer->addChild(hall_room_bg);

				//∑øº‰Àı¬‘≥°æ∞±≥æ∞
				auto hall_room_slt_cj = Sprite::createWithSpriteFrameName("hall_scene_room3.png");	
				hall_room_slt_cj->setTag(100);
				hall_room_slt_cj->setScale(0.93);
				hall_room_slt_cj->setAnchorPoint(Vec2(0.5,1));
				hall_room_slt_cj->setPosition(Vec2(hall_room_bg->getContentSize().width/2, hall_room_bg->getContentSize().height - 30));
				hall_room_bg->addChild(hall_room_slt_cj);



				//Àı¬‘≥°æ∞÷–µƒboss
				auto hall_room_slt_boss = Sprite::createWithSpriteFrameName("fish_27_0 (1).png");
				hall_room_slt_boss->setPosition(Vec2(hall_room_slt_cj->getContentSize().width/2 , hall_room_slt_cj->getContentSize().height/2));
				float hall_room_bss_scale1 = hall_room_slt_cj->getContentSize().width * 0.7/ hall_room_slt_boss->getContentSize().width > 1 ?  1 : hall_room_slt_cj->getContentSize().width * 0.7/ hall_room_slt_boss->getContentSize().width;
				float hall_room_bss_scale2 = hall_room_slt_cj->getContentSize().height * 0.7/ hall_room_slt_boss->getContentSize().height > 1 ?  1 : hall_room_slt_cj->getContentSize().height * 0.7/ hall_room_slt_boss->getContentSize().height;
				float hall_room_bss_scale = hall_room_bss_scale1 > hall_room_bss_scale2 ? hall_room_bss_scale2 :hall_room_bss_scale1;
				hall_room_slt_boss->setTag(19);
				hall_room_slt_boss->setScale(hall_room_bss_scale);
				hall_room_slt_cj->addChild(hall_room_slt_boss);

				char tmp1[40];
				sprintf(tmp1,"fish_animationwf_%d_%d",LogoLayer::room,27);
				Animate * hall_boss_a = Animate::create(AnimationCache::getInstance()->getAnimation(tmp1));
				hall_room_slt_boss->runAction(RepeatForever::create(hall_boss_a));
 

				//∑øº‰µ◊≤ø–°±≥æ∞
				auto hall_room_slt = Sprite::createWithSpriteFrameName("hall_room_slt.png");
				hall_room_slt->setTag(104);
				hall_room_slt->setPosition(Vec2(hall_room_bg->getContentSize().width/2,hall_room_bg->getContentSize().height/2));
				hall_room_bg->addChild(hall_room_slt);



				//∑øº‰Ãı∑˘
				auto hall_room_tf = Sprite::createWithSpriteFrameName("hall_room_tf.png");
				hall_room_tf->setPosition(Vec2(hall_room_bg->getContentSize().width/2,hall_room_bg->getContentSize().height * 0.45));
				hall_room_bg->addChild(hall_room_tf);

				//∑øº‰√˚≥∆
				auto hall_room_name = Sprite::createWithSpriteFrameName("scenetitle3.png");
				hall_room_name->setPosition(Vec2(hall_room_tf->getContentSize().width/2,hall_room_tf->getContentSize().height * 0.68));
				hall_room_tf->addChild(hall_room_name);

				//∑øº‰¡¡π‚
				auto hall_room_lg = Sprite::createWithSpriteFrameName("hall_room_db_bjg.png");
				auto lg_fadeOut = FadeOut::create(0.4f);
				hall_room_lg->setPosition(Vec2(hall_room_bg->getContentSize().width/2,hall_room_bg->getContentSize().height - 40));
				hall_room_lg->setTag(101);		
				hall_room_lg->runAction(lg_fadeOut);
				hall_room_bg->addChild(hall_room_lg);

				//∑øº‰≥°æ∞À¯
				auto hall_room_suo = Sprite::createWithSpriteFrameName("lock_dh_8.png");
				hall_room_suo->setPosition(Vec2(35,hall_room_bg->getContentSize().height - 60));
				hall_room_suo->setTag(102);
				hall_room_bg->addChild(hall_room_suo);

				//Ω¯»Î≥°æ∞∞¥≈•
				auto hall_room_anniu = Sprite::createWithSpriteFrameName("hall_room_anniu.png");
				auto hall_room_item_anniu  = MenuItemSprite::create(hall_room_anniu,hall_room_anniu,CC_CALLBACK_1(GameScene::menuGoSenceTwo,this));
				auto hall_room_menu_anniu = Menu::create(hall_room_item_anniu,nullptr);
				hall_room_menu_anniu->setTag(103);
				hall_room_menu_anniu->setPosition(Vec2(hall_room_bg->getContentSize().width/2,hall_room_bg->getContentSize().height * 0.24));
				hall_room_bg->addChild(hall_room_menu_anniu);

				//Ω¯»Î”Ê≥°◊÷
				auto hall_room_jryc = Sprite::createWithSpriteFrameName("hall_room_jryc.png");
				hall_room_jryc->setTag(203);
				hall_room_jryc->setPosition(Vec2(hall_room_item_anniu->getContentSize().width/2,hall_room_item_anniu->getContentSize().height * 0.5));
				hall_room_item_anniu->addChild(hall_room_jryc,200);

				Animation* fishAnimation = AnimationCache::getInstance()->getAnimation("hand"); 
				Animate*  fishAnimate = Animate::create(fishAnimation);
				auto hand = Sprite::create();  

				hall_room_item_anniu->addChild(hand,200);
				hand->setTag(4);
				hand->runAction(RepeatForever::create(fishAnimate)); 
				hand->setPosition(Vec2(hall_room_item_anniu->getContentSize().width,hall_room_item_anniu->getContentSize().height - 50));

				auto sprxin = Sprite::createWithSpriteFrameName("gosencefont.png");
				sprxin->setPosition(Vec2(hall_room_bg->getContentSize().width/2,-40));
				sprxin->setTag(5);
				hall_room_bg->addChild(sprxin,200); 
			}
*/
		

			if(stopBossTime)
			{
				stopBossTime = false;

				char textTmp[100];
				sprintf(textTmp,GAME_DATA_STRING("goumai_chenggong"),"10000","150");

				auto  gongxi = Gongxi::create(1,textTmp);
				gongxi->setPosition(Point::ZERO);
				this->addChild(gongxi,MENULAYER + 111);
			}
			/*fTime += delta;
			if(fTime >1)
			{
			fTime = 0;
			//m_pFishLayer->updateFishlayerBoss(delta);
			}

			if(m_iFishMoveTime == 1)
			{
			m_iFishMoveTime =0;
			m_pFishLayer->updateFishMove(delta);
			}
			else if(m_iFishMoveTime == 0)
			{


			m_iFishMoveTime =1;
			m_pFishLayer->updataFisDelDingPing(delta);
			m_pFishLayer->updateAddFish(delta);
			}*/


			if(FishMoney.size()> 0)
			{
				MoneyMoveUpdate++;
				if(MoneyMoveUpdate > 15)
				{
					MoneyMoveUpdate = 0;
					if(FishMoney[0]->getPosition().x >= visibleSize.width*0.34+50)
					{
						FishMoney[0]->stopAllActions(); 
						int CoinType = FishMoney[0]->getTag();
						/*if(CoinType ==  0)
						{ 

						GameBegin::playSound("music/uuuuuu.mp3");
						}
						else if(CoinType >0 && CoinType< 3)
						{
						GameBegin::playSound("music/uuuuuu.mp3");
						}

						else if(CoinType >2 && CoinType< 5)
						{
						GameBegin::playSound("music/uuuuuu.mp3");
						}
						else if(CoinType >4 )
						{
						GameBegin::playSound("music/uuuuuu.mp3");
						}*/
						auto scale = ScaleTo::create(0.55f,0);
						auto removesel = RemoveSelf::create();

						FishMoney[0]->runAction(Sequence::create(scale,removesel,nullptr));
						//this->removeChild(FishMoney[0]);
						FishMoney.erase(FishMoney.begin());
					}
					for(int i=0; i< FishMoney.size(); i++)
					{
						Point pTemp = FishMoney[i]->getPosition();
						pTemp.x += 25;   ///  + -> -
						auto move =	MoveTo::create(1.0,pTemp);
						ActionInterval * easeSineIn = EaseSineIn::create(move);  
						FishMoney[i]->runAction(easeSineIn); 
					}
				}
			}
			if(isbaoji)
			{
				isbaoji = false;
				auto gongxi = Gongxi::create(1,GAME_DATA_STRING("qiantaiduo"));
				gongxi->setPosition(Point::ZERO);
				this->addChild(gongxi,MENULAYER + 111);

				this->scheduleOnce(schedule_selector(GameScene::exitRoom),2.0f);
			}

			if(bSaJingbi == true)
			{
				bSaJingbi = false; 
				sajinbi->setPosition(Point(visibleSize.width*0.5,visibleSize.height* 0.45));
				sajinbi->resetSystem();
			}


			if(bBaoZha == true)
			{ 
				bBaoZha = false;	
				if(GameScene::cGameType != 1)
				{

					m_BaoZha1->setPosition(DeadFishPos);
					m_BaoZha1->resetSystem(); 

				}

				m_BaoZha2->setPosition(DeadFishPos); 
				m_BaoZha2->resetSystem();


				m_BaoZha3->setPosition(DeadFishPos);
				m_BaoZha3->resetSystem(); 


				this->stopAllActions();
				CCShake *p_shake = CCShake::createWithStrength(0.5f,5,5);
				this->runAction(p_shake);  

			}

			if(CannonLayer::bShowLiBao == true)
			{
				CannonLayer::bShowLiBao = false;

				auto layer = Shop::create(2);
				layer->setPosition(Point::ZERO);
				this->addChild(layer,MENULAYER + 111); 

			}


			updateTouchLayer(delta);

		}
		checkOutWall(); 
		checkOutCollision();
 
      /*  if(m_pCannonLayer->bFanHuiDating == true)
        {
            queding();
        }*/
	
} 

void GameScene::checkOutWall()
{
	
		for(int i=0; i< 5; i++)
		{

			if(i == 0)
			{
				if(bRobotPos[0] == false)
					continue;
			 
			} 
			if(i == 1)
			{
				if(bRobotPos[1] == false)
					continue;
				 
			}
			else if(i == 2)
			{
				if(bRobotPos[2] == false)
					continue;
				 
			}
			else if(i== 3)
			{
				if(bRobotPos[3] == false)
					continue;
				 
			}

			for(int j=0; j< m_pCannonLayer->getWeapon()->m_Bullet[i].size(); j++)
			{
				if(m_pCannonLayer->getWeapon()->m_Bullet[i][j]->isRunning()&& m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getType() > 19 
					&& m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getType() < 25)
				{

					float dis = ccpDistance(m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getPosition(),m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getEndPos());
					if(dis< 40)
					{
						m_pCannonLayer->getWeapon()->m_Bullet[i][j]->FanWeiMoveEnd();
					} 
				}
			}


			if (!m_pCannonLayer->getWeapon()->m_Bullet[i].empty()) 
			{
				for(int j=0; j< m_pCannonLayer->getWeapon()->m_Bullet[i].size();j++)
				{
					if(m_pCannonLayer->getWeapon()->m_Bullet[i][j]->isRunning()&& (m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getType()< 20||m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getType() ==30 )) 
					{  
						Point  bulletPos  =m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getPosition();
						Point BeginPos = m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getBeginPos();
						Size visibleSize = Director::getInstance()->getVisibleSize();

						if(bulletPos.x >visibleSize.width &&  m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getWallState() != 1)
						{   
							m_pCannonLayer->getWeapon()->m_Bullet[i][j]->setWallState(1); 
							Weapon* weapon = m_pCannonLayer->getWeapon(); 

							if(BeginPos.y < bulletPos.y)
							{
								weapon->OnWall(m_pCannonLayer->getWeapon()->m_Bullet[i][j],1,false); 
							}
							else
							{
								weapon->OnWall(m_pCannonLayer->getWeapon()->m_Bullet[i][j],1,true);  
							}

						} 
						else if(  bulletPos.y > visibleSize.height &&  m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getWallState() != 2)
						{ 

							m_pCannonLayer->getWeapon()->m_Bullet[i][j]->setWallState(2); 
							Weapon* weapon = m_pCannonLayer->getWeapon(); 

							if(BeginPos.x > bulletPos.x)
							{
								weapon->OnWall(m_pCannonLayer->getWeapon()->m_Bullet[i][j],2,false); 
							}
							else
							{
								weapon->OnWall(m_pCannonLayer->getWeapon()->m_Bullet[i][j],2,true);  
							}

						}
						else if(bulletPos.x < 0 &&  m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getWallState() != 3)
						{ 
							m_pCannonLayer->getWeapon()->m_Bullet[i][j]->setWallState(3); 
							Weapon* weapon = m_pCannonLayer->getWeapon(); 

							if(BeginPos.y > bulletPos.y)
							{
								weapon->OnWall(m_pCannonLayer->getWeapon()->m_Bullet[i][j],3,false); 
							}
							else
							{
								weapon->OnWall(m_pCannonLayer->getWeapon()->m_Bullet[i][j],3,true);  
							}
						}
						else if( bulletPos.y< 0 &&  m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getWallState() != 4)
						{ 

							m_pCannonLayer->getWeapon()->m_Bullet[i][j]->setWallState(4); 
							Weapon* weapon = m_pCannonLayer->getWeapon(); 
							if(BeginPos.x < bulletPos.x)
							{
								weapon->OnWall(m_pCannonLayer->getWeapon()->m_Bullet[i][j],4,false); 
							}
							else
							{
								weapon->OnWall(m_pCannonLayer->getWeapon()->m_Bullet[i][j],4,true);  
							}
						}
					}
					else if(m_pCannonLayer->getWeapon()->m_Bullet[i][j]->isRunning()&& m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getType() > 19 && m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getType() < 25)
					{

						float dis = ccpDistance(m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getPosition(),m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getEndPos());
						if(dis< 40)
						{
							m_pCannonLayer->getWeapon()->m_Bullet[i][j]->FanWeiMoveEnd();
						} 
					}
					else if(m_pCannonLayer->getWeapon()->m_Bullet[i][j]->isRunning())
					{ 
						Point BeginPos = m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getBeginPos();
						Size visibleSize = Director::getInstance()->getVisibleSize();

						if(BeginPos.x >visibleSize.width  )
						{  

							m_pCannonLayer->getWeapon()->m_Bullet[i][j]->FanWeiMoveEnd();

						} 
						else if(  BeginPos.y > visibleSize.height  )
						{  
							m_pCannonLayer->getWeapon()->m_Bullet[i][j]->FanWeiMoveEnd();
						}
						else if(BeginPos.x < 0 )
						{ 

							m_pCannonLayer->getWeapon()->m_Bullet[i][j]->FanWeiMoveEnd();
						}
						else if( BeginPos.y< 0  )
						{
							m_pCannonLayer->getWeapon()->m_Bullet[i][j]->FanWeiMoveEnd();
						}



						if(m_pCannonLayer->getWeapon()->m_Bullet[i][j]->bMoveEnd == true)
						{ 
							if(GameScene::cGameType != 1)
							{
                                CannonLayer::GameCoinRefresh(-CannonLayer::cBeiShu[m_pCannonLayer->getWeapon()->m_Bullet[i][j]->buletBeiShu],true,false);
                                
                                /*
								if( GameBegin::getFileData("jywer.txt") < m_pCannonLayer->getWeapon()->m_Bullet[i][j]->iNetNum *CannonLayer::cBeiShu[m_pCannonLayer->getWeapon()->m_Bullet[i][j]->buletBeiShu])
								{ 
									CannonLayer::GameCoinRefresh(-GameBegin::getFileData("jywer.txt"),true,false);
								}
								else 
								{
									CannonLayer::GameCoinRefresh(-m_pCannonLayer->getWeapon()->m_Bullet[i][j]->iNetNum *CannonLayer::cBeiShu[m_pCannonLayer->getWeapon()->m_Bullet[i][j]->buletBeiShu],true,false);
								}*/
							} 
							else if(GameScene::cGameType == 1 && i == 4)
							{
								
                                CannonLayer::GameCoinRefresh(-CannonLayer::cBeiShu[m_pCannonLayer->getWeapon()->m_Bullet[4][j]->buletBeiShu],false,false);
                                
                                /*if( GameBegin::getFileData("jywer.txt") < m_pCannonLayer->getWeapon()->m_Bullet[4][j]->iNetNum *CannonLayer::cBeiShu[m_pCannonLayer->getWeapon()->m_Bullet[4][j]->buletBeiShu])
								{ 
									CannonLayer::GameCoinRefresh(-GameBegin::getFileData("jywer.txt"),false,false);
								}
								else 
								{
									CannonLayer::GameCoinRefresh(-m_pCannonLayer->getWeapon()->m_Bullet[4][j]->iNetNum *CannonLayer::cBeiShu[m_pCannonLayer->getWeapon()->m_Bullet[4][j]->buletBeiShu],false,false);
								}
                                 */
							} 

						} 

					}

				}
			}  


		}
}
   

void GameScene::checkOutCollision( )
{ 
    this->checkOutCollisionBetweenFishesAndBullet();		 
	this->checkOutCollisionBetweenFishesAndFishingNet();
}

void  GameScene::checkOutCollisionBetweenFishesAndBullet()
{ 
	for(int j=0; j< 5; j++)
	{
		if(j == 0)
		{
			if(bRobotPos[0] == false)
				continue;

		} 
		if(j == 1)
		{
			if(bRobotPos[1] == false)
				continue;

		}
		else if(j == 2)
		{
			if(bRobotPos[2] == false)
				continue;

		}
		else if(j== 3)
		{
			if(bRobotPos[3] == false)
				continue;

		} 
	 if(!m_pCannonLayer->getWeapon()->m_Bullet[j].empty())
	 {
		 for(int i =0; i< m_pCannonLayer->getWeapon()->m_Bullet[j].size(); i++)
		 {
			 if(m_pCannonLayer->getWeapon()->m_Bullet[j][i]->isRunning() && m_pCannonLayer->getWeapon()->m_Bullet[j][i]->bDead == false 
				 &&m_pCannonLayer->getWeapon()->m_Bullet[j][i]->getType()>19 && m_pCannonLayer->getWeapon()->m_Bullet[j][i]->getType()<31 
				 && m_pCannonLayer->getWeapon()->m_Bullet[j][i]->bMoveEnd ==true)
			 { 
				 m_pFishLayer->addNet(m_pCannonLayer->getWeapon()->m_Bullet[j][i]->getType(),m_pCannonLayer->getWeapon()->m_Bullet[j][i]->getPosition(),
					 m_pCannonLayer->getWeapon()->m_Bullet[j][i]->buletBeiShu,j); 
				 Weapon* weapon = m_pCannonLayer->getWeapon(); 
				 weapon->end(i,m_pCannonLayer->getWeapon()->m_Bullet[j][i]->getType(),j);

			 }
		 }
	 }
	}
	  
	  
	if (!m_pFishLayer->m_Fishes.empty()) 
	{ 


		int iFishIndex =0; 
		
		for(int k =0; k< m_pFishLayer->m_Fishes.size();k++)
		{   
			 
			if(m_pFishLayer->m_Fishes[k]->bDead == false) //Norobot
			{   
				if(m_pFishLayer->m_Fishes[k]->getType()< 26)
				{
					Vec2 TempPoint = m_pFishLayer->m_Fishes[k]->getFishSprite()->getPosition();
					Size TempSize = m_pFishLayer->m_Fishes[k]->getFishSprite()->getContentSize();
					if(TempPoint.x > (0 - TempSize.width) && TempPoint.x < (visibleSize.width + TempSize.width)&& 
						TempPoint.y > (0 - TempSize.height) && TempPoint.y < (visibleSize.height+ TempSize.height))
					{
						 
					}
					else 
					{
						 continue;
					}
				}
				for(int i =0; i<5; i++)
				{ 
					if(i == 0)
					{
						if(bRobotPos[0] == false)
							continue;
						 
					} 
					if(i == 1)
					{
						if(bRobotPos[1] == false)
							continue;
					 
					}
					else if(i == 2)
					{
						if(bRobotPos[2] == false)
							continue;
					 
					}
					else if(i== 3)
					{
						if(bRobotPos[3] == false)
							continue;
					 
					} 
					 
					if (!m_pCannonLayer->getWeapon()->m_Bullet[i].empty())  
					{
						for(int j =0; j< m_pCannonLayer->getWeapon()->m_Bullet[i].size(); j++)						 
						{
							//isRunnning≈–∂œfish «∑Ò“—æ≠‘⁄∆¡ƒª…œœ‘ æ
							if(m_pCannonLayer->getWeapon()->m_Bullet[i][j]->isRunning()&&m_pCannonLayer->getWeapon()->m_Bullet[i][j]->bDead == false
								&&(m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getType()<20 ||m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getType()>24)
								&& m_pCannonLayer->getWeapon()->m_Bullet[i][j]->bMoreFish == false )  
							{ 
								if(m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getType()>24 && m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getType() < 30)
								{ 
									bool bCanShoot = true;
									for(int e= 0; e< m_pCannonLayer->getWeapon()->m_Bullet[i][j]->NowShootFishId.size(); e++)
									{
										if(iFishIndex == m_pCannonLayer->getWeapon()->m_Bullet[i][j]->NowShootFishId[e])
										{
											bCanShoot = false;
											break;
										}
									}
									if(bCanShoot == false)
									{
										iFishIndex++;
										continue; 
									} 


									Point fishingnetpos = m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getCollisionPoint(); 
									if(m_pFishLayer->m_Fishes[k]->CheckRadius(fishingnetpos,m_pCannonLayer->getWeapon()->m_Bullet[i][j]->fRadius))
									{   
										m_pCannonLayer->getWeapon()->m_Bullet[i][j]->NowShootFishId.push_back(iFishIndex);   
										bool bSuperPao = false;
										if(m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getType() == 29) 
										{
											bSuperPao = true;
										} 
										if(m_pCannonLayer->getWeapon()->m_Bullet[i][j]->iNetNum >= m_pCannonLayer->iFanWeiNum[m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getType()-25])
										{
											m_pCannonLayer->getWeapon()->m_Bullet[i][j]->bMoreFish = true;
											break;
										}
										m_pCannonLayer->getWeapon()->m_Bullet[i][j]->iNetNum++; 

										if(m_pFishLayer->m_Fishes[k]->beCaught(true,m_pCannonLayer->getWeapon()->m_Bullet[i][j]->buletBeiShu,false,bSuperPao,i))
										{
											MoveyMove(m_pFishLayer->m_Fishes[k]->EndNum,m_pFishLayer->m_Fishes[k]->getType());
											if(m_pFishLayer->m_Fishes[k]->getType() == 18 || m_pFishLayer->m_Fishes[k]->getType() == 19|| m_pFishLayer->m_Fishes[k]->getType() == 20)
											{
                                                PlayPanZia =m_pFishLayer->m_Fishes[k]->EndNum ;
                                                PlayPanZib = m_pFishLayer->m_Fishes[k]->FishNum;
                                                PlayPanZic = i;
                                                scheduleOnce(schedule_selector(GameScene::PlayPanZi),0.6f);
                                                
											}
											if(GameScene::cGameType != 2 && GameScene::cGameType != 1)
											{
												//»ŒŒÒΩ¯––÷–‘Ú
												if(mission->getIsMission())
												{
													mission->changeMisson(m_pFishLayer->m_Fishes[k]->getType());
												}
											}
											 
											if(m_pFishLayer->m_Fishes[k]->bSpc == true)
											{
                                                
												for(int  p = 0; p < m_pFishLayer->m_Fishes.size(); p++)
												{
													
													if(  m_pFishLayer->m_Fishes[p]->bDead == false && m_pFishLayer->m_Fishes[p]->bSpc == true)
													{  
														m_pFishLayer->m_Fishes[p]->beCaught(false,m_pCannonLayer->getWeapon()->m_Bullet[i][j]->buletBeiShu,true,false,i);
                                                        
													}
												}
                                               
                                                
											}

											if(m_pFishLayer->m_Fishes[k]->bSpcTwo == true)
											{ 
												for(int  p = 0; p < m_pFishLayer->m_Fishes.size(); p++)
												{

													if(  m_pFishLayer->m_Fishes[p]->bDead == false && m_pFishLayer->m_Fishes[p]->bSpcTwo == true)
													{  
														m_pFishLayer->m_Fishes[p]->beCaught(false,m_pCannonLayer->getWeapon()->m_Bullet[i][j]->buletBeiShu,true,false,i);
													}
												}

											} 
										}  

										if(m_pFishLayer->m_Fishes[k]->getType() > 19 && GameScene::cGameType == 2)
										{ 
											bool bCanShoot = true;
											for(int e= 0; e< m_pCannonLayer->getWeapon()->m_Bullet[i][j]->NowShootFishId.size(); e++)
											{
												if((FishLayer::cNewBoss+20) == m_pCannonLayer->getWeapon()->m_Bullet[i][j]->NowShootFishId[e])
												{
													bCanShoot = false;
													break;
												}
											}
											if(bCanShoot == false)
											{ 
												continue; 
											} 

											m_pCannonLayer->getWeapon()->m_Bullet[i][j]->NowShootFishId.push_back(FishLayer::cNewBoss+20); 
											iBossXue -= CannonLayer::cBeiShu[m_pCannonLayer->getWeapon()->m_Bullet[i][j]->buletBeiShu];//  *CannonLayer::iJiGuangCoin[CannonLayer::typeJiGuang]/2;
											_progressBossBar->setValue(iBossXue);

											if(iBossXue <= 0)
											{
												m_pFishLayer->m_Fishes[k]->BossDead(BossMoney);
												BossAddMoneyZuan(FishLayer::cNewBoss);
                                                int test = FishLayer::cNewBoss;
												if(FishLayer::cNewBoss != 24)
												{
                                                    if(this->getChildByTag((FishLayer::cNewBoss+20)))
                                                        this->getChildByTag((FishLayer::cNewBoss+20))->setVisible(false);
												} 
												 FishLayer::cNewBoss = 24;

												auto mmm = TiShi::create(9,"","",6,0);
												this->addChild(mmm,210);
												BossGuanOne->setVisible(false);
												BossMoneyOne->setVisible(false);
												BossMoneyTwo->setVisible(false);
                                                mGoldLabel->setVisible(false);
                                                mDiamondLabel->setVisible(false);
												GameBegin::playSound("Bigdie01.mp3");
												/*if(FishLayer::cNewBoss < 10)
												{
													m_SprBoss->stopAllActions();
													auto ac1 = DelayTime::create(3.0f);
													auto ac2 = CCCallFunc::create(this,callfunc_selector(GameScene::ShowNextGuan));
													auto seq = Sequence::create(ac1,ac2,nullptr);
													m_SprBoss->runAction(seq);

													this->getChildByTag((FishLayer::cNewBoss+20))->setVisible(true);
													_progressBossBar->setMaximumValue(BossXue[FishLayer::cNewBoss]);
													_progressBossBar->setValue(BossXue[FishLayer::cNewBoss]);
													iBossXue = BossXue[FishLayer::cNewBoss];
												}*/
											}
										} 
									}  
								} 
								else
								{
									Point fishingnetpos = m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getCollisionPoint();
                                   
                                    if(m_pFishLayer->m_Fishes[k]->noupdate == true)
                                    {
                                        int sd= 33;
                                    }
									if(m_pFishLayer->m_Fishes[k]->CheckRadius(fishingnetpos,m_pCannonLayer->getWeapon()->m_Bullet[i][j]->fRadius))
									{ 
										if(m_pFishLayer->m_Fishes[k]->getType() > 19 && GameScene::cGameType == 2)
										{ 
											iBossXue -= CannonLayer::cBeiShu[m_pCannonLayer->getWeapon()->m_Bullet[i][j]->buletBeiShu];
											_progressBossBar->setValue(iBossXue); 
											if(iBossXue <= 0)
											{
												m_pFishLayer->m_Fishes[k]->BossDead(BossMoney ); 
												BossAddMoneyZuan(FishLayer::cNewBoss); 

												auto mmm = TiShi::create(9,"","",6,0);
												this->addChild(mmm,210); 
												BossGuanOne->setVisible(false);
												BossMoneyOne->setVisible(false);
												BossMoneyTwo->setVisible(false);
                                                mGoldLabel->setVisible(false);
                                                mDiamondLabel->setVisible(false);
												GameBegin::playSound("Bigdie01.mp3");

												FishLayer::cNewBoss = 24;

												/*if(FishLayer::cNewBoss < 10)
												{ 
													m_SprBoss->stopAllActions();
													auto ac1 = DelayTime::create(3.0f);
													auto ac2 = CCCallFunc::create(this,callfunc_selector(GameScene::ShowNextGuan)); 
													auto seq = Sequence::create(ac1,ac2,nullptr); 
													m_SprBoss->runAction(seq);  
													_progressBossBar->setMaximumValue(BossXue[FishLayer::cNewBoss]); 
													_progressBossBar->setValue(BossXue[FishLayer::cNewBoss]);
													this->getChildByTag((FishLayer::cNewBoss+20))->setVisible(true);

													iBossXue = BossXue[FishLayer::cNewBoss]; 
												}*/
												
											}

										}
										else
										{ 
											
                                            
                                            if(bSound == true && i == 4)
                                            {
                                                bSound = false;
                                                GameBegin::playSound("shootpia.mp3");
                                                
                                            }
											if(m_pFishLayer->m_Fishes[k]->beCaught(false,m_pCannonLayer->getWeapon()->m_Bullet[i][j]->buletBeiShu,false,false,i) == true )
											{  
												MoveyMove(m_pFishLayer->m_Fishes[k]->EndNum,m_pFishLayer->m_Fishes[k]->getType());
												if(m_pFishLayer->m_Fishes[k]->getType() == 18 || m_pFishLayer->m_Fishes[k]->getType() == 19|| m_pFishLayer->m_Fishes[k]->getType() == 20)
												{
                                                    if(m_pFishLayer->m_Fishes[k]->noupdate == true)
                                                    {
                                                        int sd= 33;
                                                    }
                                                    
                                                    PlayPanZia =m_pFishLayer->m_Fishes[k]->EndNum ;
                                                    PlayPanZib = m_pFishLayer->m_Fishes[k]->FishNum;
                                                    PlayPanZic = i;
                                                    scheduleOnce(schedule_selector(GameScene::PlayPanZi),0.6f);
                                                    
 
												}

												//»ŒŒÒΩ¯––÷–‘Ú
												if(GameScene::cGameType != 2 && GameScene::cGameType != 1)
												{
													//»ŒŒÒΩ¯––÷–‘Ú
													if(mission->getIsMission())
													{
														mission->changeMisson(m_pFishLayer->m_Fishes[k]->getType());
													}
												}
												 

												if(m_pFishLayer->m_Fishes[k]->bSpc == true)
												{ 
													for(int  p = 0; p < m_pFishLayer->m_Fishes.size(); p++)
													{

														if( m_pFishLayer->m_Fishes[p]->bDead == false && m_pFishLayer->m_Fishes[p]->bSpc == true)
														{  
															m_pFishLayer->m_Fishes[p]->beCaught(false,m_pCannonLayer->getWeapon()->m_Bullet[i][j]->buletBeiShu,true,false,i);
														}
													}
                                                    //EndNum= cFishBase[_type]* CannonLayer::cBeiShu[cBeiShu];
                                                    
                                                    PlayPanZia =m_pFishLayer->m_Fishes[k]->EndNum ;
                                                    PlayPanZib = m_pFishLayer->m_Fishes[k]->FishNum;
                                                    PlayPanZic = i;
                                                    scheduleOnce(schedule_selector(GameScene::PlayPanZi),0.6f);
                                                    

												}

												if(m_pFishLayer->m_Fishes[k]->bSpcTwo == true)
												{ 
													for(int  p = 0; p < m_pFishLayer->m_Fishes.size(); p++)
													{

														if(  m_pFishLayer->m_Fishes[p]->bDead == false && m_pFishLayer->m_Fishes[p]->bSpcTwo == true)
														{  
															m_pFishLayer->m_Fishes[p]->beCaught(false,m_pCannonLayer->getWeapon()->m_Bullet[i][j]->buletBeiShu,true,false,i);
														}
													}
                                                   // EndNum= cFishBase[_type]* CannonLayer::cBeiShu[cBeiShu];
                                                    
                                                    PlayPanZia =m_pFishLayer->m_Fishes[k]->EndNum ;
                                                    PlayPanZib = m_pFishLayer->m_Fishes[k]->FishNum;
                                                    PlayPanZic = i;
                                                    scheduleOnce(schedule_selector(GameScene::PlayPanZi),0.6f);
                                                    

												}  
												  
												/*if(m_pFishLayer->ShootFish[i] ==  m_pFishLayer->m_Fishes[k] &&  i < 4)
													CheckRobotShoot(i);*/
											}  
										}
										m_pFishLayer->addNet(m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getType(),m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getPosition(),
											m_pCannonLayer->getWeapon()->m_Bullet[i][j]->buletBeiShu,i);

										Weapon* weapon = m_pCannonLayer->getWeapon(); 
										weapon->end(j,m_pCannonLayer->getWeapon()->m_Bullet[i][j]->getType(),i); 
										break;
									}

								}//◊”µØ¿‡–Õµƒ≈–∂œ  
							}
						}
					}//◊”µØµƒ—≠ª∑


				}
			}
		} 
	  
	} 
}

void GameScene::ShowNextGuan()
{
	auto mmm = TiShi::create(8,"","",10,FishLayer::cNewBoss);
	this->addChild(mmm,600); 

	m_SprBoss->stopAllActions();
	auto ac1 = DelayTime::create(5.0f);
	auto ac2 = CCCallFunc::create(this,callfunc_selector(GameScene::ShowBossJiangli)); 
	auto seq = Sequence::create(ac1,ac2,nullptr); 
	m_SprBoss->runAction(seq);  


}

void GameScene::ShowBossJiangli()
{

	char cNum[20];
	sprintf(cNum,"%d",BossMoney );  
	BossMoneyOne->setString(cNum);

	memset(cNum,0,sizeof(cNum));
	sprintf(cNum,"%d",BossZuanShi );  
	BossMoneyTwo->setString(cNum);



	BossGuanOne->setVisible(true);
	BossMoneyTwo->setVisible(true);
	BossMoneyOne->setVisible(true);
    mGoldLabel->setVisible(true);
    mDiamondLabel->setVisible(true);
}

 

void GameScene::BossAddMoneyZuan(char cType)
{
	CannonLayer::GameCoinRefresh(BossMoney );
	CannonLayer::GameCoinZuanshi(BossZuanShi );
}
 
 void GameScene::checkOutCollisionBetweenFishesAndFishingNet()
{   
	if (!m_pFishLayer->m_FishingNet.empty())  
	{
		for(int i=0; i<m_pFishLayer->m_FishingNet.size(); i++)
		{ 
			if(m_pFishLayer->m_FishingNet[i]->getType() == 30)
			{
				int asdf = 34;
			}
            //isRunnning≈–∂œfish «∑Ò“—æ≠‘⁄∆¡ƒª…œœ‘ æ
            if(m_pFishLayer->m_FishingNet[i]->isRunning() && (m_pFishLayer->m_FishingNet[i]->getType()<20 || m_pFishLayer->m_FishingNet[i]->getType() == 30)&& m_pFishLayer->m_FishingNet[i]->bShoot == false)
            { 
				if (!m_pFishLayer->m_Fishes.empty())
				{
					for(int j=0; j<m_pFishLayer->m_Fishes.size(); j++)
					{
						if( m_pFishLayer->m_Fishes[j]->bDead == false)
						{
						 
							Point fishingnetpos = m_pFishLayer->m_FishingNet[i]->getCollisionPoint(); 
							if(m_pFishLayer->m_Fishes[j]->CheckRadius(fishingnetpos,m_pFishLayer->m_FishingNet[i]->fRadius))
							{
								bool bVip = false;
								if(m_pFishLayer->m_FishingNet[i]->getType()  == 30)
								{
									bVip = true;
								} 
								m_pFishLayer->m_Fishes[j]->NetShan(bVip);
							}
						} 
					} 
                }
                m_pFishLayer->m_FishingNet[i]->bShoot = true;
                m_pFishLayer->m_FishingNet[i]->bOver = true; 
            }
			//isRunnning≈–∂œfish «∑Ò“—æ≠‘⁄∆¡ƒª…œœ‘ æ 
			if(m_pFishLayer->m_FishingNet[i]->isRunning() &&m_pFishLayer->m_FishingNet[i]->getType()>19 && m_pFishLayer->m_FishingNet[i]->getType()<25 && m_pFishLayer->m_FishingNet[i]->bShoot == false)
			{
				if (!m_pFishLayer->m_Fishes.empty())
				{
					for(int j=0; j<m_pFishLayer->m_Fishes.size(); j++)
					{
						if(  m_pFishLayer->m_Fishes[j]->bDead == false)
						{
						
							Point fishingnetpos = m_pFishLayer->m_FishingNet[i]->getCollisionPoint(); 
							if(m_pFishLayer->m_Fishes[j]->CheckRadius(fishingnetpos,m_pFishLayer->m_FishingNet[i]->fRadius))
							{    
								if(m_pFishLayer->m_Fishes[j]->getType() > 19 && GameScene::cGameType == 2)
								{ 
									iBossXue -= CannonLayer::cBeiShu[CannonLayer::_type];// *CannonLayer::iFanWeiCoin[CannonLayer::typeFanWei]/2;
									_progressBossBar->setValue(iBossXue);
									if(iBossXue <= 0)
									{
										m_pFishLayer->m_Fishes[j]->BossDead(BossMoney);  
										BossAddMoneyZuan(FishLayer::cNewBoss);
                                        if(this->getChildByTag((FishLayer::cNewBoss+20)))
                                            this->getChildByTag((FishLayer::cNewBoss+20))->setVisible(false);
										FishLayer::cNewBoss = 24;

										auto mmm = TiShi::create(9,"","",6,0);
										this->addChild(mmm,210); 

										BossGuanOne->setVisible(false);
										BossMoneyOne->setVisible(false);
										BossMoneyTwo->setVisible(false);
                                        mDiamondLabel->setVisible(false);
                                        mGoldLabel->setVisible(false);
										GameBegin::playSound("Bigdie01.mp3");
										/*if(FishLayer::cNewBoss < 10)
										{

											m_SprBoss->stopAllActions();
											auto ac1 = DelayTime::create(3.0f);
											auto ac2 = CCCallFunc::create(this,callfunc_selector(GameScene::ShowNextGuan)); 
											auto seq = Sequence::create(ac1,ac2,nullptr); 
											m_SprBoss->runAction(seq);  
											_progressBossBar->setMaximumValue(BossXue[FishLayer::cNewBoss]); 
											_progressBossBar->setValue(BossXue[FishLayer::cNewBoss]);
											this->getChildByTag((FishLayer::cNewBoss+20))->setVisible(true);

											iBossXue = BossXue[FishLayer::cNewBoss]; 
										}*/
									}

								} 


								bool bCanMove = false; 
								if(m_pFishLayer->m_FishingNet[i]->getType() == 24) 
								{
									bCanMove = true;
								}
								 
								if(m_pFishLayer->m_FishingNet[i]->iNetNum >= m_pCannonLayer->iFanWeiNum[m_pFishLayer->m_FishingNet[i]->getType()-20])
								{
										break;
								}
								m_pFishLayer->m_FishingNet[i]->iNetNum++;  


								if(m_pFishLayer->m_Fishes[j]->beCaught(true,CannonLayer::_type,false,bCanMove,m_pFishLayer->m_FishingNet[i]->cNetPosRobot ))
								{   

									MoveyMove(m_pFishLayer->m_Fishes[j]->EndNum,m_pFishLayer->m_Fishes[j]->getType());

									if(m_pFishLayer->m_Fishes[j]->getType() == 18 || m_pFishLayer->m_Fishes[j]->getType() == 19|| m_pFishLayer->m_Fishes[j]->getType() == 20)
									{
                                        
                                        PlayPanZia =m_pFishLayer->m_Fishes[j]->EndNum ;
                                        PlayPanZib = m_pFishLayer->m_Fishes[j]->FishNum;
                                        PlayPanZic = i;
                                        scheduleOnce(schedule_selector(GameScene::PlayPanZi),0.6f);
                                        
									} 
									//»ŒŒÒΩ¯––÷–‘Ú
									if(GameScene::cGameType != 2 && GameScene::cGameType != 1)
									{
										//»ŒŒÒΩ¯––÷–‘Ú
										if(mission->getIsMission())
										{
											mission->changeMisson(m_pFishLayer->m_Fishes[j]->getType());
										}
									}
									 
									if(m_pFishLayer->m_Fishes[j]->getType() == 37)
									{
 
									}  
									 

									if(m_pFishLayer->m_Fishes[j]->bSpc == true)
									{ 
										for(int  p = 0; p < m_pFishLayer->m_Fishes.size(); p++)
										{

											if(  m_pFishLayer->m_Fishes[p]->bDead == false && m_pFishLayer->m_Fishes[p]->bSpc == true)
											{  
												m_pFishLayer->m_Fishes[p]->beCaught(false,CannonLayer::_type,true,false, m_pFishLayer->m_FishingNet[i]->cNetPosRobot);
											}
										} 
									}

									if(m_pFishLayer->m_Fishes[j]->bSpcTwo == true)
									{ 
										for(int  p = 0; p < m_pFishLayer->m_Fishes.size(); p++)
										{

											if( m_pFishLayer->m_Fishes[p]->bDead == false && m_pFishLayer->m_Fishes[p]->bSpcTwo == true)
											{  
												m_pFishLayer->m_Fishes[p]->beCaught(false,CannonLayer::_type,true,false, m_pFishLayer->m_FishingNet[i]->cNetPosRobot);
											}
										}

									}  
									 


								} 
							}

						}

						 
					} 
				}
                m_pFishLayer->m_FishingNet[i]->bOver = true;
				m_pFishLayer->m_FishingNet[i]->bShoot = true;

				if(GameScene::cGameType == 0 || m_pFishLayer->m_FishingNet[i]->cNetPosRobot== 4 )
				{
                    
                    CannonLayer::GameCoinRefresh(-CannonLayer::cBeiShu[m_pFishLayer->m_FishingNet[i]->buletBeiShu],true,false);
                    
					/*if( GameBegin::getFileData("jywer.txt") < m_pFishLayer->m_FishingNet[i]->iNetNum *CannonLayer::cBeiShu[m_pFishLayer->m_FishingNet[i]->buletBeiShu])
					{ 
						CannonLayer::GameCoinRefresh(-GameBegin::getFileData("jywer.txt"),true,false);
					}
					else 
					{
						CannonLayer::GameCoinRefresh(-m_pFishLayer->m_FishingNet[i]->iNetNum *CannonLayer::cBeiShu[m_pFishLayer->m_FishingNet[i]->buletBeiShu],true,false);
					}
                     */
				}
                /*
				else
				{
					if( GameBegin::getFileData("jywer.txt") < m_pFishLayer->m_FishingNet[i]->iNetNum *CannonLayer::cBeiShu[m_pFishLayer->m_FishingNet[i]->buletBeiShu])
					{ 
						CannonLayer::GameCoinRefresh(-GameBegin::getFileData("jywer.txt"),true,true);
					}
					else 
					{
						CannonLayer::GameCoinRefresh(-m_pFishLayer->m_FishingNet[i]->iNetNum *CannonLayer::cBeiShu[m_pFishLayer->m_FishingNet[i]->buletBeiShu],true,true);
					}
				}*/
				

			}  
		}
	} 
	 
}
 
void GameScene::GameSetox(Ref* pSender)
{  
	GameBegin::buttonSound();
 
	gameLipinmaMenu->setEnabled(false);
	gameSetMenu->setEnabled(false);
	gameHelpMenu->setEnabled(false);
	gameQuitMenu->setEnabled(false);

	float x[4];
	float y[4];
	float jdt[4] = {18,66,114,162};
	for(int  i = 0 ; i < 4 ; i++)
	{
		float jd = ((jdt[i] + 180.0f)/180.0f )* 3.1415926;
		cocos2d::log("jd = %f " , jd);
		x[i] = 90 * sin(jd);
		y[i] = 90 * cos(jd);

		cocos2d::log("x[%d] = %f , y[%d] = %f",i,x[i],i,y[i]);
	}
	if(bGameSetShow==true)
	{
		m_GameMenu->setEnabled(false);

		Animate  * hall_menu_cl_dh  = Animate::create(AnimationCache::getInstance()->getAnimation("hall_set"));
		menu_shezhi_cl->runAction(RepeatForever::create(hall_menu_cl_dh->reverse()));

		//ÕÀ≥ˆ∞¥≈•∂Ø◊˜
		auto moveBy1 = MoveBy::create(0.5f,Point(-x[0],-y[0]));
		auto easy1 = EaseBackInOut::create(moveBy1);	  
		auto cal = CallFunc::create(CC_CALLBACK_0(GameScene::MoveOver,this));
		auto seq = Sequence::create(easy1,cal,nullptr);
		gameQuitMenu->runAction(seq);

		//∞Ô÷˙∞¥≈•∂Ø◊˜
		auto moveBy2 = MoveBy::create(0.5f,Point(-x[1],-y[1]));
		auto easy2 = EaseBackInOut::create(moveBy2);	
		gameHelpMenu->runAction(easy2);

		//…Ë÷√∞¥≈•∂Ø◊˜
		auto moveBy3 = MoveBy::create(0.5f,Point(-x[2],-y[2]));
		auto easy3 = EaseBackInOut::create(moveBy3);	
		gameSetMenu->runAction(easy3);

		//…Ë÷√∞¥≈•∂Ø◊˜
		auto moveBy4 = MoveBy::create(0.5f,Point(-x[3],-y[3]));
		auto easy4 = EaseBackInOut::create(moveBy4);	
		gameLipinmaMenu->runAction(easy4);

		bGameSetShow =false;
	}
	else
	{
		Animate  * hall_menu_cl_dh  = Animate::create(AnimationCache::getInstance()->getAnimation("hall_set"));
		menu_shezhi_cl->runAction(RepeatForever::create(hall_menu_cl_dh)); 
		m_GameMenu->setEnabled(false); 
		gameQuitMenu->setVisible(true);
		gameHelpMenu->setVisible(true);
		gameSetMenu->setVisible(true);
		gameLipinmaMenu->setVisible(true);
        
        if(LogoLayer::dengluFlag)
        {
            gameLipinmaMenu->setVisible(false);
        }
 
		//ÕÀ≥ˆ∞¥≈•∂Ø◊˜
		auto moveBy1 = MoveBy::create(0.5f,Point(x[0],y[0]));
		auto easy1 = EaseBackInOut::create(moveBy1);	  
		auto cal = CallFunc::create(CC_CALLBACK_0(GameScene::MoveOver,this));
		auto seq = Sequence::create(easy1,cal,nullptr);
		gameQuitMenu->runAction(seq);

		//∞Ô÷˙∞¥≈•∂Ø◊˜
		auto moveBy2 = MoveBy::create(0.5f,Point(x[1],y[1]));
		auto easy2 = EaseBackInOut::create(moveBy2);	
		gameHelpMenu->runAction(easy2);

		//…Ë÷√∞¥≈•∂Ø◊˜
		auto moveBy3 = MoveBy::create(0.5f,Point(x[2],y[2]));
		auto easy3 = EaseBackInOut::create(moveBy3);	
		gameSetMenu->runAction(easy3);

		//¿Ò∞¸∞¥≈•∂Ø◊˜
		auto moveBy4 = MoveBy::create(0.5f,Point(x[3],y[3]));
		auto easy4 = EaseBackInOut::create(moveBy4);	
		gameLipinmaMenu->runAction(easy4);

		bGameSetShow =true;
	}
} 

void GameScene::MoveOver()
{
	m_GameMenu->setEnabled(true);
	menu_shezhi_cl->stopAllActions();

	if(!bGameSetShow)
	{
		gameQuitMenu->setVisible(false);
		gameHelpMenu->setVisible(false);
		gameSetMenu->setVisible(false);
		gameLipinmaMenu->setVisible(false);
	}
	else
	{
		gameQuitMenu->setEnabled(true);
		gameHelpMenu->setEnabled(true);
		gameSetMenu->setEnabled(true);
		gameLipinmaMenu->setEnabled(true);
	}
}

void GameScene::GameQuit(Ref* pSender)
{   
	if(!GameHallLayer::exitIsCun)
	{
		GameHallLayer::exitIsCun = true;

		GameSetox(this);
		//GameBegin::buttonSound(); 

		//ÕÀ≥ˆ∑øº‰Ã· æ
		string exitTmp;
		if(cGameType != 1)
		{
			exitTmp = GAME_DATA_STRING("fisheries_exit");
		}else
		{
			exitTmp = GAME_DATA_STRING("bs_exit");
		}
		
		auto gongxi = Gongxi::create(3,exitTmp);
		gongxi->setPosition(Point::ZERO);
		this->addChild(gongxi,10000,1000);

		auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png");
		auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(GameScene::queding,this));

		btnMenu = Menu::create(quedingItem,nullptr);
		btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
		gongxi->getChildByTag(1)->addChild(btnMenu,100);
	}

} 

void GameScene::GameHelp(Ref* pSender)
{  
 
	GameSetox(this);
 
	auto gameHelp = GameHelp::createScene();
	this->addChild(gameHelp,MENULAYER + 1000);
} 

void GameScene::GameLipin(Ref* pSender)
{  
	//GameBegin::buttonSound();
 
	GameSetox(this);

	GameTextIn::libaoInt = 2;
	auto scene = GameTextIn::create();
	this->addChild(scene,MENULAYER + 1000);
} 

void GameScene::GameSet(Ref* pSender)
{  
	//GameBegin::buttonSound(); 
	GameSetox(this);

    if(GameHallLayer::hall_bShengyinShow)
    {
        GameHallLayer::hall_bShengyinShow = false;
        
        GameSet::yinyueIsON = false;
        GameSet::yinxiaoIsON = false;
        
        auto spriteFrame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hall_menu_shengyin_g.png");
        auto spriteFrame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hall_menu_shengyin_g_d.png");
        hall_sprite_shengyin->setSpriteFrame(spriteFrame1);
        hall_sprite_shengyin_d->setSpriteFrame(spriteFrame2);
        
        GameBegin::canPlayMusic = false;
        GameBegin::canPlaySound = false;
        GameBegin::stopMusic();
        
    }else
    {
        GameHallLayer::hall_bShengyinShow = true;
        
        GameSet::yinyueIsON = true;
        GameSet::yinxiaoIsON = true;
        
        auto spriteFrame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hall_menu_shengyin_k.png");
        auto spriteFrame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hall_menu_shengyin_k_d.png");
        hall_sprite_shengyin->setSpriteFrame(spriteFrame1);
        hall_sprite_shengyin_d->setSpriteFrame(spriteFrame2);
        
        GameBegin::canPlayMusic = true;
        GameBegin::canPlaySound = true;
        GameBegin::playMusic("",GameBegin::musicNum);		
    }
}
 
void GameScene::updateTouchLayer(float delta)
{

	if(GameScene::cGameType == 1)
	{

        
        for(int i= 0; i<4; i++)
        {
            if(m_pFishLayer->ShootFish[i] == NULL && GameScene::bRobotPos[i] == true)
            {
                cRobotShootTimeWf[i]++;
                if(cRobotShootTimeWf[i] == cRobotShootTimeOverwf[i])
                {
                    CheckRobotShoot(i);
                }
            }
        }

		
		for(int i=0; i<4; i++)
		{
			if(GameScene::bRobotPos[i] == true)
			{
				iChangeRobotBaseTime[i]++;
				if(iChangeRobotBaseTime[i] == iChangeRobotBaseRandTime[i])
				{				 
					m_pCannonLayer->bChangeRobotBaseIfOver[i] = true;
                    if(GameHallLayer::RoomType != 89)
                    {
                        m_pCannonLayer->changeRobotBase(i);
                    }
					
				}
				else if(iChangeRobotBaseTime[i] == iChangeRobotBaseRandTime[i]+ 100)
				{
					iChangeRobotBaseTime[i] = 0;
					m_pCannonLayer->bChangeRobotBaseIfOver[i] = false;
					iChangeRobotBaseRandTime[i] = 300+CCRANDOM_0_1()*2500;						 
					/*
					char cTemp = CCRANDOM_0_1()*50;
					if(cTemp < 25)
					{
						iChangeRobotBaseRandTime[i] = 300+CCRANDOM_0_1()*1000;						 
					}
					else if(cTemp< 50)
					{
						iChangeRobotBaseRandTime[i] = 1500+CCRANDOM_0_1()*2000;			
					}
					else if(cTemp< 75)
					{
						iChangeRobotBaseRandTime[i] = 3500+CCRANDOM_0_1()*2000;			
					}
					else if(cTemp)
					{
						iChangeRobotBaseRandTime[i] = 6000+CCRANDOM_0_1()*3000;			
					}*/
				}  
				if(bRobotVip[i] == true)
				{
					iChangeExPaoTime[i]++;
					
					if(iChangeExPaoTime[i] == iChangeExPaoRandTime[i])
					{ 
						char cTemprand = CCRANDOM_0_1()*75; 
						if(cTemprand <25)
						{
							m_pCannonLayer->changeRobotEx(i,true,0); 
							iChangeExPaoRandTimeEnd[i] = iChangeExPaoRandTime[i]+m_pCannonLayer->iFanWeiShootcd[m_pCannonLayer->cRobotTypeFanWei[i]]*60;
						}
						else if(cTemprand <50 )
						{
							m_pCannonLayer->changeRobotEx(i,true,1); 
							iChangeExPaoRandTimeEnd[i] = iChangeExPaoRandTime[i]+m_pCannonLayer->iJiGuangShootcd[m_pCannonLayer->cRobotTypeJiGuang[i]]*60;
						}
						else if(cTemprand < 75)
						{
							m_pCannonLayer->changeRobotEx(i,true,2); 
							iChangeExPaoRandTimeEnd[i] =iChangeExPaoRandTime[i]+ 5*60;
						}
						else 
						{
							iChangeExPaoTime[i] =0;
							iChangeExPaoRandTime[i] = 500+CCRANDOM_0_1()*1500;
						}

					}
					if(iChangeExPaoTime[i] == iChangeExPaoRandTimeEnd[i])
					{

						iChangeExPaoTime[i] =0;
						iChangeExPaoRandTime[i] = 500+CCRANDOM_0_1()*1500;
						m_pCannonLayer->changeRobotEx(i,false,66);  
					}
				}
			}
		}
		/*
		if(iAddRobotTime == 500)
		{
			iAddRobotTime = 0;
			
			for(int i= 0; i<4; i++)
			{ 
				if( GameScene::bRobotPos[i] == false && GameScene::cSelfPos != i)
				{
					if(CCRANDOM_0_1() > 0.5f)
					{
						GameScene::bRobotPos[i] = true;
						cRobotIQ[i] = GetRobotIQ();
						m_pCannonLayer->AddRobot(i);
					} 
					break;
				}
			}			
		}*/
	}

    
    
	iXunHuan++;
	if(iXunHuan == 2)
	{
		iXunHuan = 0;

		if(GameScene::cGameType == 1)
		{ 
			this->m_fRobotShootTime += 1;
			if(this->m_fRobotShootTime == 3)
			{ 
				this->m_fRobotShootTime = 0;
				for(int i=0; i< 4; i++)
				{
					if(m_pFishLayer->ShootFish[i] != NULL &&m_pCannonLayer->bChangeRobotBaseIfOver[i] == false)
					{
						if(m_pFishLayer->ShootFish[i]->bDead == false)
						{
							Point TempPos = m_pFishLayer->ShootFish[i]->getFishSprite()->getPosition();
							if(TempPos.x > 100 && TempPos.x < (visibleSize.width -100) && TempPos.y > 100 && TempPos.y < (visibleSize.height - 100))
							{
								if(m_pCannonLayer->bPoChan[i] ==  false)
								{ 
									RobotCannonShootTo(TempPos,i);
									RobotcannonAimAt(TempPos,i); 
								}
							}
							else
							{
								CheckRobotShoot(i);
							}
						}
						else
						{

						}

					}
				} 
			} 
		}





		if( bCanShootDanji == false)
		{   
			this->m_fUpdateTimeDanJi += 1;
			if(this->m_fUpdateTimeDanJi == m_fTimeDanJi)
			{ 
				bCanShootDanji = true;
			} 
		} 

	} 

} 

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{ 
	if(bTouch == true)
	{
      
		bTouch = false;
		mTouchPos = Director::getInstance()->convertToGL(touch->getLocationInView());
		if(bNoShoot == false)
		{
            if(bShootSound == true)
            {
                bShootSound = false;
                GameBegin::playSound("shootok21.mp3");
                
            }
            
            /*
            if(iShootNumChoose == 0)
            {
                GameBegin::playSound("shootok21.mp3");
            }
            else if(iShootNumChoose == 1)
            {
                
                GameBegin::playSound("shootok22.mp3");
            }
            else if(iShootNumChoose == 2)
            {
                GameBegin::playSound("shootok23.mp3");
            }
            iShootNumChoose ++;
            if(iShootNumChoose ==3)
                iShootNumChoose = 0;
            
            */
            
			this->cannonShootTo(mTouchPos); 
			this->cannonAimAt(mTouchPos);  
			if( bCanShootDanji == true)
			{
				m_fUpdateTime = 0;
				bCanShoot = true;
				m_fTime = 8;
				bCanShootDanji = false;

				cTouchNum++; 

				m_fUpdateTimeDanJi = 0;
				m_fTimeDanJi = 3;

			}

			return true;
		}
	}

}

void GameScene::onTouchMoved(Touch* touch, Event* event)
{

	mTouchPos = Director::getInstance()->convertToGL(touch->getLocationInView());

}

void GameScene::onTouchEnded(Touch* touch, Event* event)
{
	cTouchNum--;
	if(cTouchNum <= 0)
		bCanShoot = false;
} 

void GameScene::PlayPanZi(float delat)
{
    /*int PlayPanZia;
     int PlayPanZib;
     int PlayPanZic;
     int money,int fishnum,char cPos
     
     PlayPanZia = money;
     PlayPanZib = fishnum;
     PlayPanZic = cPos;*/
    int money = PlayPanZia ;
    int fishnum = PlayPanZib;
    int cPos = PlayPanZic ;


	LabelFishNum->setRotation(0);
	LabelFishNum->stopAllActions();
	LabelFishNum->setVisible(false);
	panziguang->stopAllActions();
	panziguang->setVisible(false);
	temp2->stopAllActions();
	temp2->setVisible(false); 
	 
	Vec2 pos;
	if(GameScene::cGameType == 1)
	{
		if(cPos == 0||(cPos == 4 && GameScene::cSelfPos == 0))
		{
			pos = Vec2(CannonLayer::robotPos1,visibleSize.height*0.37);
		}
		else if(cPos == 1||(cPos == 4 && GameScene::cSelfPos == 1))
		{
			pos = Vec2(CannonLayer::robotPos2,visibleSize.height*0.37);
		}
		else if(cPos == 2)
		{
			pos = Vec2(CannonLayer::robotPos1,visibleSize.height*0.67);
		}
		else if(cPos == 3)
		{
			pos = Vec2(CannonLayer::robotPos2,visibleSize.height*0.67);
		}

	}
	else
	{
		pos = Point(visibleSize.width/2,visibleSize.height/2+5);  
	}




	int tempChoose = CCRANDOM_0_1()*100;
	if(tempChoose <50)
	{
		
		Animation* fishAnimation1 = AnimationCache::getInstance()->getAnimation("panziguang"); 
		Animate*  fishAnimate1 = Animate::create(fishAnimation1); 
		
		panziguang->setPosition(pos);
		panziguang->runAction(RepeatForever::create(fishAnimate1)); 

	 
        ScaleTo * wfsc1;
        ScaleTo * wfsc2;
        if(GameScene::cGameType == 1)
        {
          wfsc1  =  ScaleTo::create(0.1f,0.85f);
          wfsc2  = ScaleTo ::create(0.3f,0.50f);
        }
        else
        {
            wfsc1  =  ScaleTo::create(0.1f,1.3f);
            wfsc2  = ScaleTo ::create(0.3f,0.8f);
        }


		auto * wfsc3 = CCDelayTime::create(2.5);
		auto call = CallFunc::create(CC_CALLBACK_0(GameScene::CallPanZiOver,this));


		auto * wfsc4 = Sequence::create(wfsc1,wfsc2,wfsc3,call,NULL);
		panziguang->runAction(wfsc4);
		panziguang->setVisible(true);
		 

		LabelFishNum->setVisible(true);

		LabelFishNum->setPosition(Point(pos.x,pos.y));
		char cTmepNum[15] = {0};
		sprintf(cTmepNum,"%d",money* fishnum);
		LabelFishNum->setString( cTmepNum);  
		LabelFishNum->setScale(0.9f);

        if(GameScene::cGameType == 1)
        { 
            LabelFishNum->setScale(0.7f);
        }
		RotateTo *r1=RotateTo::create(0.3f, 20);
		RotateTo *r2=RotateTo::create(0.3f, -20);
		RotateTo *r3=RotateTo::create(0.3f, 20);
		RotateTo *r4=RotateTo::create(0.3f, -20);
		RotateTo *r5=RotateTo::create(0.3f, 20);
        RotateTo *r6=RotateTo::create(0.3f, -20);
		RotateTo *r7=RotateTo::create(0.3f, 20);
        RotateTo *r8=RotateTo::create(0.4f,-20);
		auto* seq = Sequence::create(r1,r2,r3,r4,r5,r6, r7,r8,NULL);
		LabelFishNum->runAction(seq);

     
        
			 
	}
	else
	{  
		temp2->setVisible(true);
	    temp2->setPosition(pos);
        
        
        ScaleTo * wfsc1;
        ScaleTo * wfsc2;
        if(GameScene::cGameType == 1)
        {
            wfsc1  =  ScaleTo::create(0.1f,0.9f);
            wfsc2  = ScaleTo ::create(0.3f,0.60f);
        }
        else
        {
            wfsc1  =  ScaleTo::create(0.1f,1.3f);
            wfsc2  = ScaleTo ::create(0.3f,0.8f);
        }
        
        
		RotateBy *ac9=RotateBy::create(3.0, 2000);

		auto sewf11= Sequence::create(wfsc1,wfsc2,NULL);

		CCSpawn *spawn=CCSpawn::create(sewf11,ac9,NULL); 

		 

		auto call = CallFunc::create(CC_CALLBACK_0(GameScene::CallPanZiOver,this)); 
		auto se = Sequence::create(spawn,call,NULL);

		temp2->runAction(se); 
		 

		LabelFishNum->setVisible(true);

		LabelFishNum->setPosition(Point(pos.x,pos.y));
		char cTmepNum[15] = {0};
		sprintf(cTmepNum,"%d",money* fishnum);
		LabelFishNum->setString( cTmepNum);   

		auto * wfsc11 =  ScaleTo::create(0.2f,1.2f);
		auto * wfsc22 = ScaleTo ::create(0.2f,0.7f);
		//auto se1 = Sequence::create(wfsc11,wfsc22,NULL);

        RotateTo *r1=RotateTo::create(0.3f, 20);
        RotateTo *r2=RotateTo::create(0.3f, -20);
        RotateTo *r3=RotateTo::create(0.3f, 20);
        RotateTo *r4=RotateTo::create(0.3f, -20);
        RotateTo *r5=RotateTo::create(0.4f, 20);
        RotateTo *r6=RotateTo::create(0.7f, -20);
        auto* seq = Sequence::create(wfsc11,wfsc22,r1,r2,r3,r4,r5,r6, NULL);
        
		LabelFishNum->runAction(seq);
        
        if(GameScene::cGameType == 1)
        {
            
            LabelFishNum->setScale(0.75f);
        }
 
	} 
}

void GameScene::CallPanZiOver()
{
	LabelFishNum->stopAllActions();
	LabelFishNum->setVisible(false);
	panziguang->stopAllActions();
	panziguang->setVisible(false);
	temp2->stopAllActions();
	temp2->setVisible(false);
}

void GameScene::MoveyMove(int iMoney,char cFishType)
{
	if(GameScene::cGameType == 1)
	{
		return;
	}
	if(FishMoney.size() > 7)
	{
		return;
	}
	int yPos;
	if(cFishType < 4)
	{
		yPos = 0;  
	}
	else if(cFishType < 8)
	{
		yPos = 1;
	}
	else if(cFishType <11)
	{
		yPos = 2;
	}
	else if(cFishType < 13)
	{
		yPos = 3;
	}
	else if(cFishType < 15)
	{
		yPos = 4;
	}
	else if(cFishType < 17)
	{
		yPos = 5;
	}
	else if(cFishType < 33)
	{
		yPos = 6;
	} 
	else
	{
		yPos = 3;
	}
	Sprite* Money;
	if(bRed == true)
	{
		bRed = false;
		Money = Sprite::create("img/red.png",CCRectMake(0,0,21,yPos * 10 + 23));
		Money->setAnchorPoint(Vec2(1,0)); 
		this->addChild(Money); 
	}
	else
	{
		bRed = true;
		Money = Sprite::create("img/greed.png",CCRectMake(0,0,21,yPos * 10 + 23));
		Money->setAnchorPoint(Vec2(1,0));
		this->addChild(Money); 
	} 
 	
	Money->setTag(yPos); 
	Money->setPosition(visibleSize.width*0.34 - FishMoney.size()*Money->getContentSize().width,50);
	//Money->setPosition(Vec2(0,0));
 	char cNum[20];
	Money->setVisible(true);
	sprintf(cNum,"%d",iMoney);
	auto fuck =  Label::create();         //≈⁄µƒ±∂ ˝
	fuck->setCharMap("img/smallfont.png",8,13,'0'); 
	fuck->setString(cNum);
	fuck->setAnchorPoint(Vec2(0.5,1));
	
	fuck->setPosition(12,yPos * 10 + 23);
	Money->addChild(fuck); 

	JumpTo *jump  = JumpTo::create(0.2f,Money->getPosition(),5,2);
	Money->runAction(jump);
	FishMoney.push_back(Money);	
}
