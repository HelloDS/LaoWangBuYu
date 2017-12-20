#include "FishBaiKe.h"
#include "cocos2d.h"
#include "GameBegin.h"
#include "GameData.h"
#include "GameHallLayer.h"

Scene * FishBaiKe::createScene()
{
	auto scene = Scene::create();

	auto layer = FishBaiKe::create();

	scene->addChild(layer);

	return scene;
}

bool FishBaiKe::init()
{  
	if ( !Layer::init() )	
	{
		return false;
	} 
	visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();
	
	auto zheZhao = LayerColor::create(ccc4(0,0,0,150),1024,768);
	zheZhao->setPosition(Point::ZERO);
	this->addChild(zheZhao);

	//控制面板
	controlBg = Scale9Sprite::createWithSpriteFrameName( "bs_kuang1.png",CCRectMake(99,99,20,20));
	controlBg->setContentSize(CCSizeMake(950,390));
	controlBg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(controlBg);

	controlBg->setScale(0.1f);
	ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.1f, 1.0);  
	controlBg->runAction(Sequence::create(ac7,ac8,nullptr)); 

	//顶部
	auto shopCenterBg1 = Sprite::createWithSpriteFrameName("yulei_title.png");
	shopCenterBg1->setPosition(Point(controlBg->getContentSize().width/2,controlBg->getContentSize().height));
	controlBg->addChild(shopCenterBg1,100);
 
	auto shangchengxx = MenuItemSprite::create(Sprite::createWithSpriteFrameName("hall_menu_X.png"),Sprite::createWithSpriteFrameName("hall_menu_X_d.png"), CC_CALLBACK_0(FishBaiKe::exit,this));	
	auto m_ShangChengXX= Menu::create(shangchengxx, nullptr);
	m_ShangChengXX->setPosition(Vec2(controlBg->getContentSize().width - 10,controlBg->getContentSize().height - 10));
	controlBg->addChild(m_ShangChengXX,100);
	 
	char fishNameTmp[50];
    int iTempRoomType  =GameHallLayer::RoomType;
    if(iTempRoomType == 89)
    {
        iTempRoomType = 90;
    }
	//鱼层
	for(int i = 0;i<24 ; i++)
	{
		//鱼动画
		memset(fishNameTmp,0,sizeof(fishNameTmp));
		sprintf(fishNameTmp,"fish_animation_%d_%d",iTempRoomType,i);
 
		Animation* fishAnimation = AnimationCache::getInstance()->getAnimation(fishNameTmp);
		Animate*  fishAnimate = Animate::create(fishAnimation);

		auto fishSprite = Sprite::create();  
		fishSprite->setRotation(90);
		fishSprite->setPosition(Vec2(70 + (i%9) * 100,300 - (i/9)*100));		
		controlBg->addChild(fishSprite,100);
		fishSprite->runAction(RepeatForever::create(fishAnimate)); 

		Size tmps = fishAnimation->getFrames().getRandomObject()->getSpriteFrame()->getOriginalSize();
		float scaleX = tmps.height > 95.0f?95.0f/tmps.height:1;
		float scaleY = tmps.width > 70.0f?70.0f/tmps.width:1;
		fishSprite->setScale(scaleX>scaleY?scaleY:scaleX);


		//倍率
		memset(fishNameTmp,0,sizeof(fishNameTmp));
		sprintf(fishNameTmp,"fish_baike_%d_name", i); 
		auto fishBeilv = LabelTTF::create(GAME_DATA_STRING(fishNameTmp),"",24);
		fishBeilv->setPosition(Vec2(75 + (i%9) * 100 , 250 - (i/9)*100));
		controlBg->addChild(fishBeilv,100);
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(FishBaiKe::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(FishBaiKe::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(FishBaiKe::onTouchEnded,this);
	listener->setSwallowTouches(true);		//不向下传递触摸
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

    return true;
}

void FishBaiKe::exit()
{
	GameBegin::buttonSound(); 

	ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
	controlBg->runAction(Sequence::create(ac7,ac8,nullptr)); 

	this->runAction(Sequence::create(DelayTime::create(0.3f),RemoveSelf::create(),nullptr));
}


bool FishBaiKe::onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	log("touchedBegan");
	exit();
	return true;
}

void FishBaiKe::onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	log("touchesMoved");
}

void FishBaiKe::onTouchEnded(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	log("touchesEnded");
}
 