#include "Gongxi.h" 
#include "GameScene.h"
#include "GameData.h"
#include "GameBegin.h"
#include "GameHallLayer.h"

USING_NS_CC; 
Gongxi * Gongxi::create(int btnKind,std::string word)
{
	Gongxi * gongxi = new Gongxi();
	gongxi->init(btnKind,word);
	gongxi->autorelease();
	return gongxi;
}

bool Gongxi::init(int btnKind,std::string word)
{  
	if ( !Layer::init() )	
	{
		return false;
	}
	kind = btnKind;
	this->setScale(0.1f);
	ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.1f, 1.0);  
	this->runAction(Sequence::create(ac7,ac8,nullptr)); 

	gongxiTime = 2.0f;
	visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();
		
	
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Gongxi::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(Gongxi::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(Gongxi::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触�?
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	//背景�?
	auto gongxiBg = Scale9Sprite::createWithSpriteFrameName( "bs_kuang.png",Rect(95,95,10,10) );
	gongxiBg->setContentSize(Size(400,300));
	gongxiBg->setTag(1);
	gongxiBg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(gongxiBg,10);
 

	//文字
	int iiii = (int)std::strlen(word.c_str());
	int enterNum = std::count(word.c_str(),word.c_str() + (int)std::strlen(word.c_str()),'#') ;
	char * tmpChar = (char *)word.c_str();
	string text1 =  strtok(tmpChar,"#");
	for(int i =0 ; i< enterNum+1 ; i++)
	{ 
		if(text1!="")
		{
			wordTTF = LabelTTF::create(text1,GameHallLayer::wordKind,26);
			wordTTF->setAnchorPoint(Point(0.5,1));
			gongxiBg->addChild(wordTTF,1000);
		}
		if(btnKind == 3 || btnKind == 7 || btnKind == 99 )
		{
			if(wordTTF)
				wordTTF->setPosition(Point(gongxiBg->getContentSize().width/2,gongxiBg->getContentSize().height*(0.75 + ((float)((enterNum-2)/2)) * 0.1 - i*0.12)));
			
			if(i == enterNum)
			break;
			text1 = strtok(NULL,"#");
		}else
		{
			if(btnKind == 1)
			{
				if(wordTTF)
					wordTTF->setColor(Color3B(255,227,80));	
			}
			if(wordTTF)
            {
                wordTTF->setPosition(Point(gongxiBg->getContentSize().width/2,gongxiBg->getContentSize().height*(0.65 + ((float)((enterNum-1)/2)) * 0.1 - i*0.12)));
                if (btnKind ==8 && enterNum == 2) {
                    wordTTF->setPositionY(wordTTF->getPositionY() + 25);

                }
				
            }
 
			if(i == enterNum)
				break;
			text1 = strtok(NULL,"#");
		}
		}
			
	

	//第一种类型框 恭喜�?1s后消�?
	if(btnKind == 1 || btnKind == 4)
	{
		//恭喜翅膀
		auto gongxichi = Sprite::createWithSpriteFrameName("gongxi_chibang.png" );	 
		gongxichi->setAnchorPoint(Point(0.5,0));
		gongxichi->setPosition(Point(gongxiBg->getContentSize().width/2,gongxiBg->getContentSize().height - 5));
		gongxiBg->addChild(gongxichi,-1);

		//恭喜字
		auto gongxifont = Sprite::createWithSpriteFrameName("gongxizi.png" );	 
		gongxifont->setPosition(Point(gongxiBg->getContentSize().width/2,gongxiBg->getContentSize().height));
		gongxiBg->addChild(gongxifont,100);

	 
		if(btnKind == 4)
		{
			auto sajinbi = ParticleSystemQuad::create("jinbi.plist");
			sajinbi->retain();
			batch = ParticleBatchNode::createWithTexture(sajinbi->getTexture()); 
			batch->addChild(sajinbi); 
			addChild(batch); 
			sajinbi->setPosition(Point(visibleSize.width*0.5,visibleSize.height* 0.45));
			sajinbi->resetSystem();
		}else
		{
			GameScene::bSaJingbi = true;		
		}

		this->schedule(schedule_selector(Gongxi::gongxiCD),1.5f);

		return true;
	}

	//第二种类型框 提示 1s后消�?
	if(btnKind == 2)
	{
		//恭喜翅膀
		auto gongxichi = Sprite::createWithSpriteFrameName("gongxi_title1.png" );	 
		gongxichi->setPosition(Point(gongxiBg->getContentSize().width/2,gongxiBg->getContentSize().height));
		gongxiBg->addChild(gongxichi,100);

		listener->setSwallowTouches(true);
		this->schedule(schedule_selector(Gongxi::gongxiCD),1.5f);
		return true;
	}

	//第三种类型框  带叉�?
	if(btnKind == 3)
	{
		//提示
		auto gongxichi = Sprite::createWithSpriteFrameName("gongxi_title1.png" );	 
		gongxichi->setPosition(Point(gongxiBg->getContentSize().width/2,gongxiBg->getContentSize().height));
		gongxiBg->addChild(gongxichi,100);

		listener->setSwallowTouches(true);

		auto exitSprite = Sprite::createWithSpriteFrameName("hall_menu_X.png");
		auto exitSprited = Sprite::createWithSpriteFrameName("hall_menu_X_d.png");
		auto exitBtn = Menu::create(MenuItemSprite::create(exitSprite,exitSprited,exitSprite,CC_CALLBACK_0(Gongxi::exit,this)),nullptr);
		exitBtn->setPosition(Point(gongxiBg->getContentSize().width - 10,gongxiBg->getContentSize().height - 10));
		gongxiBg->addChild(exitBtn,100);
	}


	//第三种类型框 带确定 带恭喜
	if(btnKind == 5)
	{  
		//恭喜翅膀
		auto gongxichi = Sprite::createWithSpriteFrameName("gongxi_chibang.png" );	 
		gongxichi->setAnchorPoint(Point(0.5,0));
		gongxichi->setPosition(Point(gongxiBg->getContentSize().width/2,gongxiBg->getContentSize().height- 10));
		gongxiBg->addChild(gongxichi,100);

		//恭喜字
		auto gongxifont = Sprite::createWithSpriteFrameName("gongxizi.png" );	 
		gongxifont->setPosition(Point(gongxiBg->getContentSize().width/2,gongxiBg->getContentSize().height));
		gongxiBg->addChild(gongxifont,100);

		GameScene::bSaJingbi = true; 
		listener->setSwallowTouches(true);

		auto exitSprite = Sprite::createWithSpriteFrameName("XR_qd.png");
		auto exitBtn = Menu::create(MenuItemSprite::create(exitSprite,exitSprite,exitSprite,CC_CALLBACK_0(Gongxi::exit,this)),nullptr);
		exitBtn->setPosition(Point(gongxiBg->getContentSize().width/2,gongxiBg->getContentSize().height * 0.14));
		gongxiBg->addChild(exitBtn,100); 

	}

	//第三种类型框  带确定  带确定 带切换场景
	if(btnKind == 6)
	{ 
		//恭喜翅膀
		auto gongxichi = Sprite::createWithSpriteFrameName("gongxi_chibang.png" );	 
		gongxichi->setAnchorPoint(Point(0.5,0));
		gongxichi->setPosition(Point(gongxiBg->getContentSize().width/2,gongxiBg->getContentSize().height- 10));
		gongxiBg->addChild(gongxichi,100);

		//恭喜字
		auto gongxifont = Sprite::createWithSpriteFrameName("gongxizi.png" );	 
		gongxifont->setPosition(Point(gongxiBg->getContentSize().width/2,gongxiBg->getContentSize().height));
		gongxiBg->addChild(gongxifont,100);

		GameScene::bSaJingbi = true; 
		listener->setSwallowTouches(true);



		auto exitSprite = Sprite::createWithSpriteFrameName("XR_qd.png");
		auto exitBtn = Menu::create(MenuItemSprite::create(exitSprite,exitSprite,exitSprite,CC_CALLBACK_0(Gongxi::exit1,this)),nullptr);
		exitBtn->setPosition(Point(gongxiBg->getContentSize().width/2,gongxiBg->getContentSize().height * 0.14));


		gongxiBg->addChild(exitBtn,100);  

		auto sajinbi = ParticleSystemQuad::create("jinbi.plist");
		sajinbi->retain();
		batch = ParticleBatchNode::createWithTexture(sajinbi->getTexture()); 
		batch->addChild(sajinbi); 
		addChild(batch); 
		sajinbi->setPosition(Point(visibleSize.width*0.5,visibleSize.height* 0.45));
		sajinbi->resetSystem();
	}


	if(btnKind == 7)
	{ 
			//提示
		auto gongxichi = Sprite::createWithSpriteFrameName("gongxi_title1.png" );	 
		gongxichi->setPosition(Point(gongxiBg->getContentSize().width/2,gongxiBg->getContentSize().height));
		gongxiBg->addChild(gongxichi,100);
 
	}
	if(btnKind == 8)
	{ 
		//恭喜翅膀
		auto gongxichi = Sprite::createWithSpriteFrameName("gongxi_chibang.png" );	 
		gongxichi->setAnchorPoint(Point(0.5,0));
		gongxichi->setPosition(Point(gongxiBg->getContentSize().width/2,gongxiBg->getContentSize().height- 10));
		gongxiBg->addChild(gongxichi,100);

		//恭喜字
		auto gongxifont = Sprite::createWithSpriteFrameName("gongxizi.png" );	 
		gongxifont->setPosition(Point(gongxiBg->getContentSize().width/2,gongxiBg->getContentSize().height));
		gongxiBg->addChild(gongxifont,100);
        
       
	}

	 return true;
}

bool Gongxi::onTouchBegan(Touch* touch, Event* event) 
{ 
	p1 = touch->getLocation();
	return true;
}

void Gongxi::onTouchMoved(Touch* touch, Event* event) 
{

}

void Gongxi::onTouchEnded(Touch* touch, Event* event)
{
	 p2 = touch->getLocation();
	 if(abs(p2.x - p1.x) < 4 && kind < 7)
	{
		exit();			
	}
}

void Gongxi::gongxiCD(float fdelta)
{
	gongxiTime--;
	if(gongxiTime == 0)
	{
		this->unschedule(schedule_selector(Gongxi::gongxiCD));
		ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
		ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
		this->runAction(Sequence::create(ac7,ac8,RemoveSelf::create(),nullptr) ); 
	}
}
 
void Gongxi::exit()
{
	 
	GameBegin::buttonSound();

	GameHallLayer::exitIsCun = false;

	ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
	this->runAction(Sequence::create(ac7,ac8,RemoveSelf::create(),nullptr) ); 
 
}
 
void Gongxi::exit1()
{
	 
	if(GameHallLayer::RoomType == 0 )//&& FishLayer::bBoss == false)
	{
		GameScene::GoNewSence =1;
	}

	
	ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
	this->runAction(Sequence::create(ac7,ac8,RemoveSelf::create(),nullptr) ); 
}

void Gongxi::setColor(Color3B color)
{
	wordTTF->setColor(color);
}
