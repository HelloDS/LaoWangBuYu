#include "MissionSuc.h" 
#include "GameScene.h"
#include "GameData.h"
#include "GameBegin.h"

USING_NS_CC; 
MissionSuc * MissionSuc::create(int btnKind,int num1 )
{
	MissionSuc * missionSuc = new MissionSuc();
	missionSuc->init(btnKind,num1 );
	missionSuc->autorelease();
	return missionSuc;
}

bool MissionSuc::init(int btnKind,int num1 )
{  
	if ( !Layer::init() )	
	{
		return false;
	} 
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
	listener->onTouchBegan = CC_CALLBACK_2(MissionSuc::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(MissionSuc::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(MissionSuc::onTouchEnded,this);
	listener->setSwallowTouches(false);//不向下传递触�?
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	//背景�?
	auto lvupBG = Scale9Sprite::createWithSpriteFrameName( "mission_suc_BG.png");
	lvupBG->setTag(1);
	//lvupBG->setScale(GameBegin::scaleYNum);
	lvupBG->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(lvupBG,10);

	if(btnKind == 1)
	{
		//钻石奖励背景
		auto lvZuanShiBg = Sprite::createWithSpriteFrameName("yubi.png" );
		lvZuanShiBg->setPosition(Point(lvupBG->getContentSize().width * 0.4,lvupBG->getContentSize().height * 0.43));
		lvupBG->addChild(lvZuanShiBg,1000);

		//钻石奖励
		auto lvZuanLabel = Label::createWithCharMap("img/lvupnum.png",25,30,'0');
        lvZuanLabel->setAnchorPoint(Vec2(0,0.5f));
		char lvZuanTmp[10];
		sprintf(lvZuanTmp,"%d",num1);
		lvZuanLabel->setString(lvZuanTmp);
		lvZuanLabel->setPosition(Vec2(lvZuanShiBg->getContentSize().width*1.4,lvZuanShiBg->getContentSize().height*0.5));
		lvZuanShiBg->addChild(lvZuanLabel,100);
	}else
	{
		//钻石奖励背景
		auto lvZuanShiBg = Sprite::createWithSpriteFrameName("diamond.png" );
		lvZuanShiBg->setPosition(Point(lvupBG->getContentSize().width * 0.4,lvupBG->getContentSize().height * 0.43));
		lvupBG->addChild(lvZuanShiBg,1000);

		//钻石奖励
		auto lvZuanLabel = Label::createWithCharMap("img/lvupnum.png",25,30,'0');
        lvZuanLabel->setAnchorPoint(Vec2(0,0.5f));
		char lvZuanTmp[10];
		sprintf(lvZuanTmp,"%d",num1);
		lvZuanLabel->setString(lvZuanTmp);
		lvZuanLabel->setPosition(Vec2(lvZuanShiBg->getContentSize().width*1.4,lvZuanShiBg->getContentSize().height*0.5));
		lvZuanShiBg->addChild(lvZuanLabel,100);
	}

	/*auto sajinbi = ParticleSystemQuad::create("jinbi.plist");
	sajinbi->retain();
	auto batch = ParticleBatchNode::createWithTexture(sajinbi->getTexture()); 
	batch->addChild(sajinbi); 
	addChild(batch); 
	sajinbi->setPosition(Point(visibleSize.width*0.5,visibleSize.height* 0.45));
	sajinbi->resetSystem();
	*/
	GameScene::bSaJingbi = true;

	this->schedule(schedule_selector(MissionSuc::LvUpCD),1.3f);

	 return true;
}
bool MissionSuc::onTouchBegan(Touch* touch, Event* event) 
{ 

	return true;
}

void MissionSuc::onTouchMoved(Touch* touch, Event* event) 
{

}

void MissionSuc::onTouchEnded(Touch* touch, Event* event)
{

}

void MissionSuc::LvUpCD(float fdelta)
{
	gongxiTime--;
	if(gongxiTime == 0)
	{
		this->unschedule(schedule_selector(MissionSuc::LvUpCD));
		this->removeFromParent();
	}
}


void MissionSuc::exit()
{

	GameBegin::buttonSound();
	this->removeFromParent();
}
