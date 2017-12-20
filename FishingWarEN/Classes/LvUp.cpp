#include "LvUp.h" 
#include "GameScene.h"
#include "GameData.h"
#include "GameBegin.h"

USING_NS_CC; 
LvUp * LvUp::create(int btnKind,int num1,int num2,int num3)
{
	LvUp * lvup = new LvUp();
	lvup->init(btnKind,num1,num2,num3);
	lvup->autorelease();
	return lvup;
}

bool LvUp::init(int btnKind,int num1,int num2,int num3)
{  
    if ( !Layer::init() )	
	{
        return false;
    }
    
    /*auto zheZhao = LayerColor::create(ccc4(0,0,0,120),1024,768);
     zheZhao->setPosition(Point::ZERO);
     zheZhao->setScale(2.0f);
     this->addChild(zheZhao);
     */
    
    
    //动态出现
    this->setScale(0.7);
    CCScaleTo *ac8=CCScaleTo::create(0.5f, 1.0f);
    auto action =  EaseExponentialOut::create(ac8);
    this->runAction(action);
    
    gongxiTime = 2.0f;
    visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    Size winSize = Director::getInstance()->getWinSize();
    
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(LvUp::onTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(LvUp::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(LvUp::onTouchEnded,this);
    listener->setSwallowTouches(false);//不向下传递触 ?
    dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    //背景 ?
    auto lvupBG = Sprite::createWithSpriteFrameName( "lvupBG.png");
    lvupBG->setTag(1);
    //lvupBG->setScale(GameBegin::scaleYNum);
    lvupBG->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    this->addChild(lvupBG,10);
    /*
     //升到多少级
     auto lvNumLabel = Label::createWithCharMap("img/lvupnum.png",25,30,'0');
     char lvNumTmp[10];
     sprintf(lvNumTmp,"%d",num1);
     lvNumLabel->setString(lvNumTmp);
     lvNumLabel->setPosition(Vec2(lvupBG->getContentSize().width*0.55,lvupBG->getContentSize().height*0.52));
     lvupBG->addChild(lvNumLabel);
     */
    
    
    //奖励金币
    
    auto goldImg = Sprite::createWithSpriteFrameName("yubi.png");
    goldImg->setPosition(ccp(lvupBG->getContentSize().width*0.35f,lvupBG->getContentSize().height*0.35f));
    lvupBG->addChild(goldImg);
    
    
    auto lvCoinLabel = Label::createWithCharMap("img/lvupnum.png",25,30,'0');
    char lvCoinTmp[10];
    sprintf(lvCoinTmp,"%d",num2);
    lvCoinLabel->setString(lvCoinTmp);
    lvCoinLabel->setPosition(Vec2(goldImg->getPositionX() + goldImg->getContentSize().width + lvCoinLabel->getContentSize().width/2,goldImg->getPosition().y));
    lvupBG->addChild(lvCoinLabel);
    
    
    
    
    
    
    
    if(btnKind == 2)
    {
        goldImg->setPosition(ccp(lvupBG->getContentSize().width*0.35f,lvupBG->getContentSize().height*0.45f));
        lvCoinLabel->setPosition(Vec2(goldImg->getPositionX() + goldImg->getContentSize().width + lvCoinLabel->getContentSize().width/2,goldImg->getPosition().y));
        cocos2d::log("goldImg->setPositiony = %f,lvCoinLabel->setPosition = %f",goldImg->getPosition().y,lvCoinLabel->getPosition().y);
        
        //钻石奖励背景
        auto lvZuanShiBg = Sprite::createWithSpriteFrameName("diamond.png" );
        lvZuanShiBg->setPosition(Point(lvupBG->getContentSize().width*0.35f,lvupBG->getContentSize().height * 0.2));
        lvupBG->addChild(lvZuanShiBg,1000);
        
        //钻石奖励
        auto lvZuanLabel = Label::createWithCharMap("img/lvupnum.png",25,30,'0');
        char lvZuanTmp[10];
        sprintf(lvZuanTmp,"%d",num3);
        lvZuanLabel->setString(lvZuanTmp);
        lvZuanLabel->setPosition(Vec2(lvZuanShiBg->getPositionX() + lvZuanShiBg->getContentSize().width + lvZuanLabel->getContentSize().width/2,lvZuanShiBg->getPosition().y));
        lvupBG->addChild(lvZuanLabel,100);
        
    }else
    {
        /*	//解锁倍炮背景
         auto lvJieSuoBg = Sprite::createWithSpriteFrameName("lvupjiesuo.png" );
         lvJieSuoBg->setPosition(Point(lvupBG->getContentSize().width/2,lvupBG->getContentSize().height * 0.3));
         lvupBG->addChild(lvJieSuoBg,1000);
         
         //解锁倍炮
         auto lvSuoLabel = Label::createWithCharMap("img/lvupnum.png",25,30,'0');
         char lvSuoTmp[10];
         sprintf(lvSuoTmp,"%d",num3);
         lvSuoLabel->setString(lvSuoTmp);
         lvSuoLabel->setPosition(Vec2(lvJieSuoBg->getContentSize().width*0.61,lvJieSuoBg->getContentSize().height*0.5));
         lvJieSuoBg->addChild(lvSuoLabel,100);*/
    }
    
    
    
    GameScene::bSaJingbi = true;
    
    
    this->schedule(schedule_selector(LvUp::LvUpCD),1.3f);
    
    return true;

}
bool LvUp::onTouchBegan(Touch* touch, Event* event) 
{ 

	return true;
}

void LvUp::onTouchMoved(Touch* touch, Event* event) 
{

}

void LvUp::onTouchEnded(Touch* touch, Event* event)
{

}

void LvUp::LvUpCD(float fdelta)
{
	gongxiTime--;
	if(gongxiTime == 0)
	{
		this->unschedule(schedule_selector(LvUp::LvUpCD));
		this->removeFromParent();
	}
}


void LvUp::exit()
{

	GameBegin::buttonSound();
	this->removeFromParent();
}
