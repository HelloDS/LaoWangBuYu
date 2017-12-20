#include "GameHelp.h"
#include "GameHallLayer.h"
#include "GameData.h"
#include "GameBegin.h"
#include "cocos2d.h"
 
#include "GameScene.h"
#include "Shop.h"
#include "Gongxi.h"
 
#include "VIPgongxi.h"
#include "DialogText.h"
 
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include "..\cocos2d\external\curl\include\win32\curl\curl.h"
#endif
 
USING_NS_CC; 

 
Scene * GameHelp::createScene()
{
	auto scene = Scene::create();

	auto layer = GameHelp::create();

	scene->addChild(layer);

	return scene;
}

bool GameHelp::init()
{  
	//visibleSize = Director::getInstance()->getVisibleSize();
	//Point origin = Director::getInstance()->getVisibleOrigin();
	//Size winSize = Director::getInstance()->getWinSize();

	//auto zheZhao = LayerColor::create(ccc4(0,0,0,100),1024,768);
	//zheZhao->setPosition(Point::ZERO);
	//this->addChild(zheZhao);

	////控制面板
	//controlBg = Scale9Sprite::createWithSpriteFrameName( "bs_kuang.png",CCRectMake(50,50,50,50));
	////controlBg->setScale(0.85);
	//controlBg->setContentSize(CCSizeMake(900,500));
	//controlBg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	//this->addChild(controlBg);

	//controlBg->setScale(0.1f);
	//ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);  
	//ScaleTo *ac8=ScaleTo::create(0.1f, 1);  
	//controlBg->runAction(Sequence::create(ac7,ac8,nullptr)); 

	////顶部
	//auto exitSprite = Sprite::createWithSpriteFrameName("hall_menu_X.png");
	//auto exitSprited = Sprite::createWithSpriteFrameName("hall_menu_X_d.png");
	//auto exitBtn = Menu::create(MenuItemSprite::create(exitSprite,exitSprited,exitSprite,CC_CALLBACK_0(GameHelp::exit,this)),nullptr);
	//exitBtn->setPosition(Point(controlBg->getContentSize().width - 10,controlBg->getContentSize().height - 10));
	//controlBg->addChild(exitBtn,100);

	//auto submarineTitle = Sprite::createWithSpriteFrameName("order_title.png");
	//submarineTitle->setPosition(Point(controlBg->getContentSize().width/2,controlBg->getContentSize().height));
	//controlBg->addChild(submarineTitle,100);

	////中间框
	//auto callusContent = Label::createWithTTF(GAME_DATA_STRING("check_order_0"),"minijianling.ttf",38);
	//callusContent->setColor(Color3B(233,237,235));
	//callusContent->setPosition(Point(controlBg->getContentSize().width/2,controlBg->getContentSize().height*0.47));
	//controlBg->addChild(callusContent,100);
 // 
 //
	//auto listener = EventListenerTouchOneByOne::create();
	//listener->onTouchBegan = CC_CALLBACK_2(GameHelp::onTouchBegan,this);
	//listener->onTouchMoved = CC_CALLBACK_2(GameHelp::onTouchMoved,this);
	//listener->onTouchEnded = CC_CALLBACK_2(GameHelp::onTouchEnded,this);
	//listener->setSwallowTouches(true);//不向下传递触摸
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
	//this->scheduleUpdate();
 //   return true;

	if ( !Layer::init() )	
	{
		return false;
	}
 
	auto visibleSize = Director::getInstance()->getVisibleSize();//获得可视区域的大小
	Point origin = Director::getInstance()->getVisibleOrigin();//获得可视区域的起始坐标ori

	//auto zheZhao = LayerColor::create(ccc4(0,0,0,90),1024,768);
	//zheZhao->setPosition(Point::ZERO);
	//this->addChild(zheZhao);

	this->setScale(0.1f);
	 
	ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.1f, 1.0f); 
	this->runAction(Sequence::create(ac7,ac8 ,nullptr) ); 

	//控制面板
	auto callBg = Scale9Sprite::createWithSpriteFrameName( "bs_kuang.png",CCRectMake(50,50,50,50));
	callBg->setContentSize(CCSizeMake(400,300));
	callBg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(callBg);

	//顶部
	auto submarineTitle = Sprite::createWithSpriteFrameName("kefu_title.png");
	submarineTitle->setScale(0.8);
	submarineTitle->setPosition(Point(callBg->getContentSize().width/2,callBg->getContentSize().height));
	callBg->addChild(submarineTitle,100);

	auto exitSprite = Sprite::createWithSpriteFrameName("hall_menu_X.png");
	auto exitSprited = Sprite::createWithSpriteFrameName("hall_menu_X_d.png");
	auto exitBtn = Menu::create(MenuItemSprite::create(exitSprite,exitSprited,exitSprite,CC_CALLBACK_0(GameHelp::exit,this)),nullptr);
	exitBtn->setPosition(Point(callBg->getContentSize().width - 10,callBg->getContentSize().height - 10));
	callBg->addChild(exitBtn,100);
 
	string word = GAME_DATA_STRING("help_callUs");
	int iiii = (int)std::strlen(word.c_str());
	int enterNum = std::count(word.c_str(),word.c_str() + (int)std::strlen(word.c_str()),'#') ;
	char * tmpChar = (char *)word.c_str();
	string text1 =  strtok(tmpChar,"#");
	for(int i =0 ; i< enterNum+1 ; i++)
	{ 
		auto wordTTF = LabelTTF::create(text1,GameHallLayer::wordKind,28);
		wordTTF->setColor(Color3B(244,255,244));
		wordTTF->setAnchorPoint(Point(0.5,-1));
		wordTTF->setPosition(Point(callBg->getContentSize().width * 0.5,callBg->getContentSize().height*0.5));
		callBg->addChild(wordTTF,100);
		if(i == enterNum)
			break;
		text1 = strtok(NULL,"#");
	}


	word = GAME_DATA_STRING("help_callUs1");
	tmpChar = (char *)word.c_str();
    text1 =  strtok(tmpChar,"#");
	enterNum = std::count(word.c_str(),word.c_str() + (int)std::strlen(word.c_str()),'#') ;
	for(int i =0 ; i< enterNum+1 ; i++)
	{ 

			auto wordTTF = LabelTTF::create(text1,"Arial",24);
			wordTTF->setColor(Color3B(244,255,244));
			wordTTF->setAnchorPoint(Point(0.5,1));
			wordTTF->setPosition(Point(callBg->getContentSize().width * 0.5,callBg->getContentSize().height*0.5));
			callBg->addChild(wordTTF,100);
		
		
		if(i == enterNum)
			break;
		text1 = strtok(NULL,"#");
	}


 
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameHelp::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(GameHelp::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(GameHelp::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触摸
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}


 
void GameHelp::exit()
{
	GameBegin::buttonSound(); 
	ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
	this->runAction(Sequence::create(ac7,ac8,RemoveSelf::create(),nullptr)); 

	//this->runAction(Sequence::create(DelayTime::create(0.3f),RemoveSelf::create(),nullptr));
}

bool GameHelp::onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	log("touchedBegan");
	return true;
}

void GameHelp::onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	log("touchesMoved");
}

void GameHelp::onTouchEnded(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	log("touchesEnded");
}
 