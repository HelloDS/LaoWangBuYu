#include "Waiting.h"
#include "GameData.h"
#include "GameHallLayer.h"

Waiting * Waiting::create()
{
    Waiting * gongxi = new Waiting();
    gongxi->init();
    gongxi->autorelease();
    
    return gongxi;
}

bool Waiting::init()
{  
	if ( !Layer::init() )	
	{
		return false;
	}

    auto zheZhao = LayerColor::create(ccc4(0,0,0,200),1024,768);
    zheZhao->setPosition(Point::ZERO);
    zheZhao->setScale(2.0f);
    this->addChild(zheZhao);
    

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();
    
    
    auto Lquan = Sprite::createWithSpriteFrameName("loadingQQ.png");
    Lquan->setPosition(Point(visibleSize.width/2 + origin.x,visibleSize.height/2 + origin.y));
    addChild(Lquan);
    
    auto Lword = Sprite::createWithSpriteFrameName("loadingWZ.png");
    Lword->setPosition(Point(visibleSize.width/2 + origin.x,visibleSize.height/2 + origin.y));
    addChild(Lword);
    
    auto zhuanquan = RotateBy::create(1.0f, 360);
    Lquan->runAction(RepeatForever::create(zhuanquan));
    
    word = Label::create(GAME_DATA_STRING("wait_word"),GameHallLayer::wordKind,24);
    word->setPosition(Vec2(visibleSize.width/2 , visibleSize.height * 0.3));
    addChild(word,10 );

	auto dispatcher = Director::getInstance()->getEventDispatcher();

	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(Waiting::onTouchBegan,this);

	listener->onTouchMoved = CC_CALLBACK_2(Waiting::onTouchMoved,this);

	listener->onTouchEnded = CC_CALLBACK_2(Waiting::onTouchEnded,this);

	listener->setSwallowTouches(true);//不向下传递触摸

	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

    this->scheduleOnce(schedule_selector(Waiting::removeIt), 3.0f);

	return true;
}
void Waiting::setString(std::string name)
{
    word->setString(name);
}
void Waiting::removeIt(float dt)
{
    //this->removeFromParent();
}

bool Waiting::onTouchBegan(Touch* touch, Event* event)
{ 

	return true;
}

void Waiting::onTouchMoved(Touch* touch, Event* event)
{

}


void Waiting::onTouchEnded(Touch* touch, Event* event)
{

}
