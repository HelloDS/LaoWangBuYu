#include "GameSet.h"
#include "cocos-ext.h"
#include "GameScene.h"
#include "GameData.h"
#include "GameBegin.h"
#include "cocos2d.h"
USING_NS_CC;
USING_NS_CC_EXT;

using namespace CocosDenshion;

bool GameSet::yinyueIsON = true;
bool GameSet::yinxiaoIsON = true;


GameSet * GameSet::create()
{
	GameSet * gameset = new GameSet();
	gameset->init();
	gameset->autorelease();
	return gameset;
}


bool GameSet::init()
{  
	if ( !Layer::init() )	
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();

	auto zheZhao = LayerColor::create(ccc4(0,0,0,100),1024,768);
	zheZhao->setPosition(Point::ZERO);
	this->addChild(zheZhao);

	//控制面板
	auto controlBg = Scale9Sprite::createWithSpriteFrameName( "kuang_1.png",CCRectMake(109,109,20,20));
	controlBg->setContentSize(CCSizeMake(530,350));
	controlBg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(controlBg);

	//顶部
	auto topBg = Scale9Sprite::createWithSpriteFrameName("btl.png",CCRectMake(20,20,30,30));
	topBg->setContentSize(Size(515,70));
	topBg->setAnchorPoint(Point(0.5,1));
	topBg->setPosition(Point(controlBg->getContentSize().width/2,controlBg->getContentSize().height));
	controlBg->addChild(topBg,100);

	/*auto exitSprite = Sprite::createWithSpriteFrameName("cha.png");
	auto exitSprited = Sprite::createWithSpriteFrameName("cha down.png");
	auto exitBtn = Menu::create(MenuItemSprite::create(exitSprite,exitSprited,exitSprite,CC_CALLBACK_0(GameSet::exit,this)),NULL);
	exitBtn->setPosition(Point(topBg->getContentSize().width - 30,topBg->getContentSize().height - 30));
	topBg->addChild(exitBtn,100);*/

	auto exitSprite = Sprite::createWithSpriteFrameName("wfxx.png");
	auto exitSprited = Sprite::createWithSpriteFrameName("wfxx2.png");
	auto exitBtn = Menu::create(MenuItemSprite::create(exitSprite,exitSprited,exitSprite,CC_CALLBACK_0(GameSet::exit,this)),nullptr);
	exitBtn->setPosition(Point(topBg->getContentSize().width - 30,topBg->getContentSize().height - 30));
	topBg->addChild(exitBtn,100);

	auto submarineTitle = Sprite::createWithSpriteFrameName("btl_1.png");
	submarineTitle->setPosition(Point(topBg->getContentSize().width/2,topBg->getContentSize().height/2));
	topBg->addChild(submarineTitle,100);

	//音效控制
	auto sound = Sprite::createWithSpriteFrameName("yinxiaokongzhi.png");
	sound->setPosition(Point(40,110));
	sound->setAnchorPoint(Point(0,0.5));
	controlBg->addChild(sound,100);

	if(yinxiaoIsON)
	{
		soundKaiguan = Sprite::createWithSpriteFrameName("setON.png");
	}
	else
	{
		soundKaiguan = Sprite::createWithSpriteFrameName("setOFF.png");
	}
	soundItem = MenuItemSprite::create(soundKaiguan,soundKaiguan,soundKaiguan,CC_CALLBACK_0(GameSet::soundControl,this));
	soundItem->setPosition(Point(0,-50));


	//音乐控制
	auto music = Sprite::createWithSpriteFrameName("yinyuekongzhi.png");
	music->setPosition(Point(40,210));
	music->setAnchorPoint(Point(0,0.5));
	controlBg->addChild(music,100);

	if(yinyueIsON)
		musicKaiguan = Sprite::createWithSpriteFrameName("setON.png");
	else
		musicKaiguan = Sprite::createWithSpriteFrameName("setOFF.png");
	musicItem = MenuItemSprite::create(musicKaiguan,musicKaiguan,musicKaiguan,CC_CALLBACK_0(GameSet::musicControl,this));
	musicItem->setPosition(Point(0,50));

	auto menuTmp = Menu::create(soundItem,musicItem,nullptr);
	menuTmp->setPosition(Point(380,160));
	menuTmp->setAnchorPoint(Point(0,0.5));
	controlBg->addChild(menuTmp,100);

	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(GameSet::onTouchBegan,this);

	listener->onTouchMoved = CC_CALLBACK_2(GameSet::onTouchMoved,this);

	listener->onTouchEnded = CC_CALLBACK_2(GameSet::onTouchEnded,this);

	listener->setSwallowTouches(true);//不向下传递触摸

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);



    return true;
}


void GameSet::exit()
{
	GameBegin::buttonSound(); 
	//Director::getInstance()->getEventDispatcher()->re
	this->removeFromParent();
}

void GameSet::soundControl()
{
	if(yinxiaoIsON)
	{
		GameBegin::canPlaySound = false;

		SpriteFrame * tmp1 = SpriteFrameCache::getInstance()->spriteFrameByName("setOFF.png");
		soundKaiguan->setDisplayFrame(tmp1);

		yinxiaoIsON = false;
	}
	else
	{
		GameBegin::canPlaySound = true;

		SpriteFrame * tmp1 = SpriteFrameCache::getInstance()->spriteFrameByName("setON.png");
		soundKaiguan->setDisplayFrame(tmp1);

		yinxiaoIsON = true;
	}

}

void GameSet::musicControl()
{
	if(yinyueIsON)
	{
		GameBegin::canPlayMusic = false;
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

		SpriteFrame * tmp1 = SpriteFrameCache::getInstance()->spriteFrameByName("setOFF.png");
		musicKaiguan->setDisplayFrame(tmp1);

		yinyueIsON = false;
	}
	else
	{
		GameBegin::canPlayMusic = true;

		char tmpMusic[30];
		sprintf(tmpMusic,"bgmusic%d.mp3",GameBegin::musicNum);
 
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(tmpMusic);
		 
		SpriteFrame * tmp1 = SpriteFrameCache::getInstance()->spriteFrameByName("setON.png");
		musicKaiguan->setDisplayFrame(tmp1);

		yinyueIsON = true;
	}
}

bool GameSet::onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	log("touchedBegan");
	return true;
}

void GameSet::onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	log("touchesMoved");
}

void GameSet::onTouchEnded(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	log("touchesEnded");
}
