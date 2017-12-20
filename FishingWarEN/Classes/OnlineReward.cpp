#include "OnlineReward.h"
#include "GameScene.h"
#include "Gongxi.h"
#include "GameBegin.h"

OnlineReward * OnlineReward::createScene(int btnKind)  //btnkind 1,能领取第一个 2，第二个 3，第三个
{
	OnlineReward * shop = new OnlineReward();
	shop->init(btnKind );
	shop->autorelease();
	return shop;
}
 
bool OnlineReward::init(int btnKind)
{  
	if ( !Layer::init() )	
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();
	curKind = btnKind;

	auto zheZhao = LayerColor::create(ccc4(0,0,0,150),1024,768);
	zheZhao->setPosition(Point::ZERO);
	zheZhao->setScale(2.0f);
	this->addChild(zheZhao);
 
	//升级板
	shopCenterBg = Scale9Sprite::createWithSpriteFrameName( "bs_kuang.png",CCRectMake(99,99,20,20));
	shopCenterBg->setContentSize(CCSizeMake(950,500));
	shopCenterBg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	shopCenterBg->setScale(0.85);
	this->addChild(shopCenterBg);
 
	auto shopCenterBg1 = Sprite::createWithSpriteFrameName("lingjiang_title.png");
	shopCenterBg1->setPosition(Point(shopCenterBg->getContentSize().width/2,shopCenterBg->getContentSize().height));
	shopCenterBg->addChild(shopCenterBg1,100);
 
	auto shangchengxx = MenuItemSprite::create(Sprite::createWithSpriteFrameName("hall_menu_X.png"),Sprite::createWithSpriteFrameName("hall_menu_X_d.png"), CC_CALLBACK_0(OnlineReward::exit,this));	
	auto m_ShangChengXX= Menu::create(shangchengxx, nullptr);
	m_ShangChengXX->setPosition(Vec2(shopCenterBg->getContentSize().width - 10,shopCenterBg->getContentSize().height - 10));
	shopCenterBg->addChild(m_ShangChengXX,100);

	 
	shopCenterBg->setScale(0.1f);
	ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.1f, 1.0);  
	shopCenterBg->runAction(Sequence::create(ac7,ac8,nullptr)); 

	for(int i = 0 ; i < 3 ; i++)
	{
		//item背景
		char item_tmp[30];
		sprintf(item_tmp,"zaixianlj_%d.png",i+1);
		auto item_bg = Sprite::createWithSpriteFrameName(item_tmp);
		item_bg->setPosition(Point(shopCenterBg->getContentSize().width/2 + (i - 1) * 303,shopCenterBg->getContentSize().height * 0.56));
		shopCenterBg->addChild(item_bg,100);

		//item按钮
		auto item_sp1 = Sprite::createWithSpriteFrameName("zaixianlj_lq1.png");
		auto item_sp2 = Sprite::createWithSpriteFrameName("zaixianlj_lq2.png");
		auto item_sp3 = Sprite::createWithSpriteFrameName("zaixianlj_lq3.png");
		auto item_item = MenuItemSprite::create(item_sp1,item_sp2,item_sp3,CC_CALLBACK_0(OnlineReward::buyYuBi,this));
		auto item_menu = Menu::create(item_item,nullptr);
		item_menu->setPosition(Point(shopCenterBg->getContentSize().width/2 + (i - 1) * 303,shopCenterBg->getContentSize().height * 0.12));
		shopCenterBg->addChild(item_menu,100);

		if(i!= curKind -1)
		{			
			item_item->setEnabled(false);
		}
	}
 
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(OnlineReward::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(OnlineReward::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(OnlineReward::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	this->scheduleUpdate();

	return true;
}
 
void OnlineReward::buyYuBi()
{
	GameBegin::buttonSound(); 
	ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
	shopCenterBg->runAction(Sequence::create(ac7,ac8,nullptr)); 

	this->runAction(Sequence::create(DelayTime::create(0.3f),RemoveSelf::create(),nullptr));

	char tmpchar[100];
	string textTmp = GAME_DATA_STRING("ZaiXianLingJiang");
	sprintf(tmpchar,textTmp.c_str(),100*curKind,10*curKind);
	auto gongxi = Gongxi::create(4,tmpchar);
	this->getParent()->addChild(gongxi,MENULAYER + 111);

	CannonLayer::GameCoinRefresh(100*curKind);
	CannonLayer::GameCoinZuanshi(10*curKind);

	//当前时间
	time_t currentTime;
	time(&currentTime);
	UserDefault::getInstance()->setIntegerForKey("ZaiXianTime",curKind); //领奖次数
	UserDefault::getInstance()->setDoubleForKey("preTime",currentTime); //领奖时间
	UserDefault::getInstance()->flush();
	GameScene::lingjiangflag = true;
}
 
bool OnlineReward::onTouchBegan(Touch* touch, Event* event) 
{ 	 
	return true;
}

void OnlineReward::onTouchMoved(Touch* touch, Event* event) 
{

}

void OnlineReward::onTouchEnded(Touch* touch, Event* event)
{
	 
}

void OnlineReward::exit()
{
	GameBegin::buttonSound(); 
 
	ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
	shopCenterBg->runAction(Sequence::create(ac7,ac8,nullptr)); 

	this->runAction(Sequence::create(DelayTime::create(0.3f),RemoveSelf::create(),nullptr));
}