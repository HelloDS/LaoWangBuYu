#include "GameEmail.h"
#include "cocos-ext.h"
#include "GameBegin.h"
#include "GameData.h"
#include "GameHallLayer.h"
#include "Gongxi.h"
#include "cocos2d.h"

#if(CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) 

#include "../cocos2d/external/curl/include/ios/curl/curl.h"
#include <sys/stat.h> 
#include <unistd.h>
#include <dirent.h> 
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include "..\cocos2d\external\curl\include\win32\curl\curl.h"
#endif
USING_NS_CC;
USING_NS_CC_EXT;
 
Scene * GameEmail::createScene()
{
	auto scene = Scene::create();

	auto layer = GameEmail::create();

	scene->addChild(layer);

	return scene;
}

bool GameEmail::init()
{  
	if ( !Layer::init() )	
	{
		return false;
	}

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameEmail::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(GameEmail::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(GameEmail::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
 
	visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();

	string gg_title   = UserDefault::getInstance()->getStringForKey("gg_title");
	string gg_content = UserDefault::getInstance()->getStringForKey("gg_content");

	gg_yubi		  = UserDefault::getInstance()->getIntegerForKey("gg_yubi");
	gg_zuanshi	  = UserDefault::getInstance()->getIntegerForKey("gg_zuanshi");
	gg_huafeiquan = UserDefault::getInstance()->getIntegerForKey("gg_huafeiquan");

	int gg_lingqu     = UserDefault::getInstance()->getIntegerForKey("gg_lingqu");
	int gg_version	  = UserDefault::getInstance()->getIntegerForKey("gonggao_version");

	char gg_tmpchar[50];
	auto zheZhao = LayerColor::create(ccc4(0,0,0,100),1024,768);
	zheZhao->setPosition(Point::ZERO);
	this->addChild(zheZhao);

	//控制面板
	controlBg = Scale9Sprite::createWithSpriteFrameName( "bs_kuang.png",CCRectMake(50,50,50,50));
	controlBg->setContentSize(CCSizeMake(800,450));
	controlBg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(controlBg);

	controlBg->setScale(0.1f);
	ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.1f, 1.0);  
	controlBg->runAction(Sequence::create(ac7,ac8,nullptr)); 

	//顶部
	auto exitSprite = Sprite::createWithSpriteFrameName("hall_menu_X.png");
	auto exitSprited = Sprite::createWithSpriteFrameName("hall_menu_X_d.png");
	auto exitBtn = Menu::create(MenuItemSprite::create(exitSprite,exitSprited,exitSprite,CC_CALLBACK_0(GameEmail::exit,this)),nullptr);
	exitBtn->setPosition(Point(controlBg->getContentSize().width - 10,controlBg->getContentSize().height - 10));
	controlBg->addChild(exitBtn,100);

	auto submarineTitle = Sprite::createWithSpriteFrameName("gonggao_title.png");
	submarineTitle->setPosition(Point(controlBg->getContentSize().width/2,controlBg->getContentSize().height));
	controlBg->addChild(submarineTitle,100);
 
	if(gg_version == 0)
	{
		auto gonggao = LabelTTF::create(GAME_DATA_STRING("zanwugonggao"),GameHallLayer::wordKind,30);
		gonggao->setPosition(controlBg->getContentSize()/2);
		//gonggao->setColor(Color3B(246,235,0));
		//gonggao->setDimensions(Size(controlBg->getContentSize().width * 0.8,controlBg->getContentSize().height * 5));
		controlBg->addChild(gonggao,100);
		return true;
	}else
	{
		//公告title
		auto gonggao_title = Label::create(gg_title,GameHallLayer::wordKind,30);
		gonggao_title->setPosition(Vec2(controlBg->getContentSize().width/2,controlBg->getContentSize().height * 0.837));
		gonggao_title->setColor(Color3B(246,235,0));
		//gonggao->setDimensions(Size(controlBg->getContentSize().width * 0.8,controlBg->getContentSize().height * 5));
		controlBg->addChild(gonggao_title,100);

		auto title_hua_1 = Sprite::createWithSpriteFrameName("email_01.png");
		//title_hua_1->setAnchorPoint(Vec2(1,0.5));
		title_hua_1->setPosition(Vec2((controlBg->getContentSize().width - gonggao_title->getContentSize().width)/2 - 50,controlBg->getContentSize().height * 0.837));
		controlBg->addChild(title_hua_1,100);

		auto title_hua_2 = Sprite::createWithSpriteFrameName("email_01.png");
		//title_hua_2->setAnchorPoint(Vec2(1,0.5));
		title_hua_2->setFlippedX(true);
		title_hua_2->setPosition(Vec2((controlBg->getContentSize().width + gonggao_title->getContentSize().width)/2 + 50,controlBg->getContentSize().height * 0.837));
		controlBg->addChild(title_hua_2,100);

		//公告内容
		string tmpContent  =  gg_content;
		int iiii = (int)std::strlen(tmpContent.c_str());
		int enterNum = std::count(tmpContent.c_str(),tmpContent.c_str() + (int)std::strlen(tmpContent.c_str()),'#') ;
		char * tmpChar = (char *)tmpContent.c_str();
		string text1 =  strtok(tmpChar,"#");
		int tmpLine = 0;
		for(int i =0 ; i< enterNum+1 ; i++)
		{ 
			auto wordTTF = Label::create(text1,GameHallLayer::wordKind,20);

			if(wordTTF)
			{
				Size tmpsize = wordTTF->getContentSize();
				wordTTF->setDimensions(600,400);
				float tmpHeight = 0.075 * controlBg->getContentSize().height;
				wordTTF->setLineHeight(tmpHeight);
				wordTTF->setAnchorPoint(Point(0,1));
				wordTTF->setPosition(Point(controlBg->getContentSize().width * 0.12,controlBg->getContentSize().height*(0.7 - i * 0.075)));
				int a = (int)(tmpsize.width)/700;
				tmpLine += a;
				controlBg->addChild(wordTTF,100);
			}

			
			if(i == enterNum)
				break;
			text1 = strtok(NULL,"#");
		}
 
		if(gg_lingqu == 0 ||( gg_yubi == 0 && gg_zuanshi == 0 && gg_huafeiquan == 0 ))
		{
			return true;
		}

		//金币icon
		auto gg_yb_icon = Sprite::createWithSpriteFrameName("yubi.png");
		gg_yb_icon->setScale(0.7);
		gg_yb_icon->setPosition(Vec2(controlBg->getContentSize().width * 0.12,controlBg->getContentSize().height * 0.175));
		controlBg->addChild(gg_yb_icon,100);

		//鱼币label
		auto yubiLabel = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
		sprintf(gg_tmpchar,"%d",gg_yubi);
		yubiLabel->setString(gg_tmpchar);
		yubiLabel->setAnchorPoint(Vec2(0,0.5));
		yubiLabel->setScale(0.55);
		yubiLabel->setPosition(Point(controlBg->getContentSize().width * 0.15,controlBg->getContentSize().height * 0.175));
		controlBg->addChild(yubiLabel,100);

		//钻石icon 
		auto gg_zs_icon = Sprite::createWithSpriteFrameName("diamond.png");
		gg_zs_icon->setScale(0.7);
		gg_zs_icon->setPosition(Vec2(controlBg->getContentSize().width * 0.3,controlBg->getContentSize().height * 0.175));
		controlBg->addChild(gg_zs_icon,100);

		//钻石label
		auto zuanshiLabel = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
		sprintf(gg_tmpchar,"%d",gg_zuanshi);
		zuanshiLabel->setString(gg_tmpchar);
		zuanshiLabel->setAnchorPoint(Vec2(0,0.5));
		zuanshiLabel->setScale(0.55);
		zuanshiLabel->setPosition(Point(controlBg->getContentSize().width * 0.33,controlBg->getContentSize().height * 0.175));
		controlBg->addChild(zuanshiLabel,100);
/*
		//话费券icon
		auto gg_hfq_icon = Sprite::createWithSpriteFrameName("huafeiquan.png");
		gg_hfq_icon->setScale(0.33);
		gg_hfq_icon->setPosition(Vec2(controlBg->getContentSize().width * 0.48,controlBg->getContentSize().height * 0.175));
		controlBg->addChild(gg_hfq_icon,100);
*/
		//话费券label
		auto hfqLabel = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
		sprintf(gg_tmpchar,"%d",gg_huafeiquan);
		hfqLabel->setString(gg_tmpchar);
		hfqLabel->setAnchorPoint(Vec2(0,0.5));
		hfqLabel->setScale(0.55);
		hfqLabel->setPosition(Point(controlBg->getContentSize().width * 0.51,controlBg->getContentSize().height * 0.175));
		controlBg->addChild(hfqLabel,100);

		auto lq_sp   = Sprite::createWithSpriteFrameName("zaixianlj_lq1.png");
		auto lq_sp1  = Sprite::createWithSpriteFrameName("zaixianlj_lq2.png");
		auto lq_item = MenuItemSprite::create(lq_sp,lq_sp1, CC_CALLBACK_0(GameEmail::lingqu,this));
		auto lq_menu = Menu::create(lq_item, nullptr);
		lq_menu->setPosition(Vec2(controlBg->getContentSize().width * 0.75,controlBg->getContentSize().height * 0.175));
		controlBg->addChild(lq_menu,100);
 	
	}
 
    return true;
}

void GameEmail::lingqu()
{
	char gongxiTmp[100];
	sprintf(gongxiTmp,GAME_DATA_STRING("duihuanchenggong"),gg_yubi,gg_zuanshi,gg_huafeiquan);

	auto gongxi = Gongxi::create(4,gongxiTmp);
	this->getParent()->addChild(gongxi,1001);

	UserDefault::getInstance()->setIntegerForKey("gg_lingqu",0);
  
	UserDefault::getInstance()->flush();

	GameHallLayer::RefreshCoin(gg_yubi);
	GameHallLayer::RefreshDiamond(gg_zuanshi);
 
	exit();
}

bool GameEmail::onTouchBegan(Touch* touch, Event* event) 
{ 

	return true;
}

void GameEmail::onTouchMoved(Touch* touch, Event* event) 
{

}

void GameEmail::onTouchEnded(Touch* touch, Event* event)
{

}

void GameEmail::exit()
{
	GameBegin::buttonSound(); 
	ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
	controlBg->runAction(Sequence::create(ac7,ac8,nullptr)); 

	this->runAction(Sequence::create(DelayTime::create(0.3f),RemoveSelf::create(),nullptr));
}