#include "LoginReward.h"
#include "GameData.h"
#include "cocos2d.h"
#include "GameBegin.h"
#include "GameScene.h"
#include "Gongxi.h"
#include "LogoLayer.h"
#include "GameBegin.h"
#include "CannonLayer.h"
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
 

LoginReward * LoginReward::create(int rewardDays)
{
	LoginReward * lr = new LoginReward();

	lr->init(rewardDays);

	lr->autorelease();

	return lr;
}

Sequence * LoginReward::returnAction(int i)
{
	auto delayT1 = DelayTime::create(0.15f * i);
	auto visib = Show::create();
	auto scale1 = ScaleTo::create(0.2f,0.92);
	auto fade1 = FadeIn::create(0.2f);
	auto moveBy1 = MoveBy::create(0.2f,Vec2(0,120));
	auto spawn1 = Spawn::create(scale1,moveBy1,nullptr);
	auto delayT = DelayTime::create(0.1f);
	auto scale2 = ScaleTo::create(0.2f,0.9);
	auto moveBy2 = MoveBy::create(0.2f,Vec2(0,-120));
	auto spawn2 = Spawn::create(scale2,moveBy2,nullptr);
	

	auto moveBy11 = MoveBy::create(0.5f,Vec2(0,20));
	auto movenBy21 = MoveBy::create(0.25f,Vec2(0,-10));
	auto movenBy31 = MoveBy::create(0.25f,Vec2(0,10));
	auto moveBy41 = MoveBy::create(0.5f,Vec2(0,-20));
	auto action = Repeat::create(Sequence::create(moveBy11,movenBy21,movenBy31,moveBy41,nullptr),15);

	Sequence * seq;
	if(i + 1 == loginDays)
	{
		seq = Sequence::create(delayT1,visib,spawn1,delayT,spawn2,action,nullptr);
	}else
	{
		seq = Sequence::create(delayT1,visib,spawn1,delayT,spawn2,nullptr);
	}
	
	return seq;

}

bool LoginReward::init(int rewardDays)
{  
	if ( !Layer::init() )	
	{
		return false;
	}
	cocos2d::log("init LoginReward::init");
	loginDays = rewardDays;
	visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();
    int leijiChongzhi = GameBegin::getFileData("wflei.txt");

	cocos2d::log("init LoginReward::init1");
	auto zheZhao = LayerColor::create(ccc4(0,0,0,150),1024,768);
	zheZhao->setPosition(Point::ZERO);
	this->addChild(zheZhao,10);

	//控制面板
	auto controlBg = Sprite::createWithSpriteFrameName( "dengluBG.png");
	controlBg->setPosition(Point(visibleSize.width/2,visibleSize.height*0.75 + controlBg->getContentSize().height/2));
	this->addChild(controlBg,100);

	auto exitSprite = Sprite::createWithSpriteFrameName("hall_menu_X.png");
	auto exitSprited = Sprite::createWithSpriteFrameName("hall_menu_X_d.png");
	auto exitBtn = Menu::create(MenuItemSprite::create(exitSprite,exitSprited,exitSprite,CC_CALLBACK_0(LoginReward::exit,this)),NULL);
	exitBtn->setPosition(Point(controlBg->getContentSize().width + exitSprite->getContentSize().width/2,controlBg->getContentSize().height /2));
	controlBg->addChild(exitBtn,100);
  
	char tmpDay[30];

	cocos2d::log("init LoginReward::init 2");
	for(int i = 0 ; i<7 ; i++)
	{
		auto buttonBg = Sprite::createWithSpriteFrameName("denglu_guang.png");
		auto buttonItem = MenuItemSprite::create(buttonBg,buttonBg,CC_CALLBACK_1(LoginReward::addYubi,this));
		buttonItem->setTag(i);
		auto buttonMenu = Menu::create(buttonItem,nullptr);
		buttonMenu->setPosition(Point(212 + i%4* 200 ,visibleSize.height * 0.6 - i/4 * 200));
		buttonItem->setEnabled(false);
		this->addChild(buttonMenu,100);

		buttonItem->runAction(returnAction(i));

		/*auto anbeijing = LayerColor::create(ccc4(0,0,0,90),buttonBg->getContentSize().width,buttonBg->getContentSize().height);
		anbeijing->setPosition(Point::ZERO);
		buttonBg->addChild(anbeijing,100);*/
		if(i<rewardDays-1)
		{
			auto titleDays = LabelTTF::create(GAME_DATA_STRING("login_reward"), GameHallLayer::wordKind, 22);
			titleDays->setAnchorPoint(Point(0.5,0.5));
			titleDays->setPosition(Point(buttonBg->getContentSize().width/2,buttonBg->getContentSize().height*0.84));
			buttonBg->addChild(titleDays);

			auto yubiPng = Sprite::createWithSpriteFrameName("yubi.png");
			yubiPng->setAnchorPoint(Point(1,0.5));
			yubiPng->setPosition(Point(buttonBg->getContentSize().width*0.37,buttonBg->getContentSize().height*0.54));
			yubiPng->setScale(0.85);
			buttonBg->addChild(yubiPng);

			auto jinbiNum = Label::createWithCharMap("img/goldword.png",36,44,'0');
			jinbiNum->setAnchorPoint(Point(0,0.5));
			memset(tmpDay,0,sizeof(tmpDay));
			sprintf(tmpDay,"%d",100+100*i);
			jinbiNum->setString(tmpDay);
			jinbiNum->setPosition(Point(buttonBg->getContentSize().width*0.43,buttonBg->getContentSize().height*0.54));
			jinbiNum->setScale(0.85);
			buttonBg->addChild(jinbiNum);

			auto zuanshiPng = Sprite::createWithSpriteFrameName("diamond.png");
			zuanshiPng->setAnchorPoint(Point(1,0.5));
			zuanshiPng->setPosition(Point(buttonBg->getContentSize().width*0.37,buttonBg->getContentSize().height*0.24));
			buttonBg->addChild(zuanshiPng);
			zuanshiPng->setScale(0.7);

			auto zuanshiNum = Label::createWithCharMap("img/goldword.png",36,44,'0');
			memset(tmpDay,0,sizeof(tmpDay));
			sprintf(tmpDay,"%d",10+10*i);
			zuanshiNum->setString(tmpDay);
			zuanshiNum->setAnchorPoint(Point(0,0.5));
			zuanshiNum->setPosition(Point(buttonBg->getContentSize().width*0.43,buttonBg->getContentSize().height*0.24));
			buttonBg->addChild(zuanshiNum);
			zuanshiNum->setScale(0.7);
 
			if(i % 2 == 0 && i != 0 && leijiChongzhi == 0 )
			{
				auto beijing_guang = Sprite::createWithSpriteFrameName("hall_ssxx_bg.png");
				beijing_guang->setPosition(Vec2(buttonBg->getContentSize().width*0.95,buttonBg->getContentSize().height*0.15));
				beijing_guang->setScale(1.3);
			//	beijing_guang->setOpacity(125);
				buttonBg->addChild(beijing_guang);

				sprintf(tmpDay,"sale_buff_%d_1.png",i/2);
				auto beijing_baoxiang = Sprite::createWithSpriteFrameName(tmpDay);
				beijing_baoxiang->setPosition(Vec2(buttonBg->getContentSize().width*0.95,buttonBg->getContentSize().height*0.2));
				beijing_baoxiang->setScale(0.23);
				buttonBg->addChild(beijing_baoxiang);
			}
		}
		else
		{
			
			sprintf(tmpDay,"login_day_%d",i+1);
			auto titleDays = LabelTTF::create(GAME_DATA_STRING(tmpDay), GameHallLayer::wordKind, 26);
			titleDays->setAnchorPoint(Point(0.5,0.5));
			titleDays->setPosition(Point(buttonBg->getContentSize().width/2,buttonBg->getContentSize().height*0.84));
			buttonBg->addChild(titleDays);
            titleDays->setScale(0.8f);

			auto yubiPng = Sprite::createWithSpriteFrameName("yubi.png");
			yubiPng->setAnchorPoint(Point(1,0.5));
			yubiPng->setPosition(Point(buttonBg->getContentSize().width*0.37,buttonBg->getContentSize().height*0.54));
			yubiPng->setScale(0.85);
			buttonBg->addChild(yubiPng);

			auto jinbiNum = Label::createWithCharMap("img/goldword.png",36,44,'0');
			
			memset(tmpDay,0,sizeof(tmpDay));
			sprintf(tmpDay,"%d",100+100*i);
			jinbiNum->setString(tmpDay);
			jinbiNum->setAnchorPoint(Point(0,0.5));
			jinbiNum->setPosition(Point(buttonBg->getContentSize().width*0.43,buttonBg->getContentSize().height*0.54));
			jinbiNum->setScale(0.85);
			buttonBg->addChild(jinbiNum);

			auto zuanshiPng = Sprite::createWithSpriteFrameName("diamond.png");
			zuanshiPng->setAnchorPoint(Point(1,0.5));
			zuanshiPng->setPosition(Point(buttonBg->getContentSize().width*0.37,buttonBg->getContentSize().height*0.24));
			buttonBg->addChild(zuanshiPng);
			zuanshiPng->setScale(0.7);

			auto zuanshiNum = Label::createWithCharMap("img/goldword.png",36,44,'0');
			memset(tmpDay,0,sizeof(tmpDay));
			sprintf(tmpDay,"%d",10+10*i);
			zuanshiNum->setString(tmpDay);
			zuanshiNum->setAnchorPoint(Point(0,0.5));
			zuanshiNum->setPosition(Point(buttonBg->getContentSize().width*0.43,buttonBg->getContentSize().height*0.24));
			buttonBg->addChild(zuanshiNum);
			zuanshiNum->setScale(0.7);
 
			Sprite * beijing_baoxiang;
			if(i % 2 == 0 && i != 0  && leijiChongzhi == 0)
			{
 
				sprintf(tmpDay,"sale_buff_%d.png",i/2);
				beijing_baoxiang = Sprite::createWithSpriteFrameName(tmpDay);
				beijing_baoxiang->setScale(0.23);
				beijing_baoxiang->setPosition(Vec2(buttonBg->getContentSize().width*0.95,buttonBg->getContentSize().height*0.2));
				buttonBg->addChild(beijing_baoxiang,2);
			}

			if(i+1 == rewardDays)
			{		
				buttonItem->setEnabled(true);
				buttonBg->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("denglu_guang_1.png"));
				sprintf(tmpDay,"sale_buff_%d_1.png",i/2);

				if(i % 2 == 0 && i != 0  && leijiChongzhi == 0)
				{
					beijing_baoxiang->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(tmpDay));

					auto beijing_guang = Sprite::createWithSpriteFrameName("hall_ssxx_bg.png");
					beijing_guang->setScale(1.3);
				//	beijing_guang->setOpacity(125);
					beijing_guang->setPosition(Vec2(buttonBg->getContentSize().width*0.95,buttonBg->getContentSize().height*0.15));
					buttonBg->addChild(beijing_guang);
				}
				
			}else
			{
				/*for(int i = 0 ; i<buttonBg->getChildrenCount(); i++)
				{
					buttonBg->getChildren().at(i)->setColor(Color3B(127,127,127));					
				}*/
				buttonMenu->setZOrder(0);
				
			}
 
		}	

		if(i>3)
		{
			buttonMenu->setPosition(Point(312+ i%4* 200 ,visibleSize.height * 0.6 - i/4 * 200));
		}
 
	} 

	cocos2d::log("init LoginReward::init 3");

	//auto dispatcher = Director::getInstance()->getEventDispatcher();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(LoginReward::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(LoginReward::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(LoginReward::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触摸
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
 
	return true;
}

void LoginReward::addYubi(Object* pSender)
{
	GameBegin::buttonSound(); 
 
	time_t currentTime;
	time(&currentTime);
	cocos2d::log("loginreward:: currentTime = %ld",currentTime);

	struct tm *nowTime = gmtime(&currentTime);
	int hour=nowTime->tm_hour;  
	int minute=nowTime->tm_min;  
	int second=nowTime->tm_sec;
	time_t nextTime = currentTime + 24*60*60 - hour*60*60 - minute*60 - second; 

	Sprite * tmpSprite = (Sprite *)pSender;
	int i = tmpSprite->getTag();
   
	GameHallLayer::RefreshCoin(100+i*100);
	GameHallLayer::RefreshDiamond(10 + i*10);

	UserDefault::getInstance()->setIntegerForKey("prevTime",nextTime);
	UserDefault::getInstance()->setIntegerForKey("LoginDays",i+1);
	UserDefault::getInstance()->flush();

    int leijiChongzhi = GameBegin::getFileData("wflei.txt");
	if(i % 2 == 0 && i != 0 && leijiChongzhi == 0)
		GameHallLayer::isSaleVis = true;

	//弹出恭喜狂
	char tmp[200];
	sprintf(tmp,GAME_DATA_STRING("login_yubi"),100+i*100,10+10*i);
	auto gongxi = Gongxi::create(4,tmp);
	gongxi->setScale(0.8);
	gongxi->setPosition(Point::ZERO);

	this->getParent()->addChild(gongxi,MENULAYER);
 
	this->removeFromParent();
}

void LoginReward::exit()
{
	GameBegin::buttonSound(); 

	this->removeFromParent();

}

bool LoginReward::onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	log("touchedBegan");
	return true;
}

void LoginReward::onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	log("touchesMoved");
}

void LoginReward::onTouchEnded(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	log("touchesEnded");
}
