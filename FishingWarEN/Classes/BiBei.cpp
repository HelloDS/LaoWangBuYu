#include "BiBei.h"
#include "Gongxi.h"
#include "GameData.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
#include "CannonLayer.h"



BiBei* BiBei::create(int PaoMoney)
{
	// 'scene' is an autorelease object

	BiBei* loadres = new BiBei();

	loadres->init(PaoMoney);
	loadres->autorelease(); 

	// return the scene
	return loadres;
	 
}

bool BiBei::init(int PaoMoney)
{

	// 1. super init first
	if ( !Layer::init() )	
	{
		return false;
	}

	Size winSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	 


	//遮罩层
	CCLayerColor *zzLayer = CCLayerColor::create(ccc4(0,0,0,180),winSize.width,winSize.height);
	this->addChild(zzLayer);

	auto BeiJin = Sprite::createWithSpriteFrameName("bibeibg.png");
	BeiJin->setPosition(winSize.width*0.5f,winSize.height*0.6f);
	this->addChild(BeiJin);



	cChoose = 0;
	cChooseTime = 0;
	
	Sprite * cBig = Sprite::createWithSpriteFrameName("big.png");

	auto BigItem = MenuItemSprite::create(cBig,cBig,cBig,CC_CALLBACK_1(BiBei::menuBig,this));
	m_ChooseBig = Menu::create(BigItem,nullptr);
	BeiJin->addChild(m_ChooseBig,100);
	m_ChooseBig->setPosition(Point(120,133));
	ChouMaPos[0] = Point(120,133-55);
	GuangPos[0] = Point(120,133);
	 



	m_pNum[0] = Sprite::createWithSpriteFrameName("bibeione.png");
	m_pNum[1] = Sprite::createWithSpriteFrameName("bibeitwo.png");
	m_pNum[2] = Sprite::createWithSpriteFrameName("bibeithree.png");

	m_pNum[0]->setPosition(Point(205,125));
	m_pNum[1]->setPosition(Point(205,125));
	m_pNum[2]->setPosition(Point(205,125));
	BeiJin->addChild(m_pNum[0],100);	
	BeiJin->addChild(m_pNum[1],100); 
	BeiJin->addChild(m_pNum[2],100); 

	m_pNum[0]->setVisible(false);
	m_pNum[1]->setVisible(false);
	m_pNum[2]->setVisible(false);



	iBiBeiMoney = PaoMoney;

	MoneyLabel = Label::create();  
	MoneyLabel->setCharMap("fengshunum.png",11,17,'0');
	char cTmepNum[30] = {0};
	sprintf(cTmepNum,"%d", PaoMoney);
	MoneyLabel->setString( cTmepNum);   
	MoneyLabel->setPosition(Point(250,270));
	MoneyLabel->setScale(1.5f);
	BeiJin->addChild(MoneyLabel,100); 
	 

	Sprite * cSmall = Sprite::createWithSpriteFrameName("small.png");

	auto SmallItem = MenuItemSprite::create(cSmall,cSmall,cSmall,CC_CALLBACK_1(BiBei::menuSmall,this));
	m_ChooseSmall = Menu::create(SmallItem,nullptr);
	BeiJin->addChild(m_ChooseSmall,100);
	m_ChooseSmall->setPosition(Point(300,133));
	ChouMaPos[1] = Point(300,133-55);
	GuangPos[1] = Point(300,133);

	m_pChouMa = Sprite::createWithSpriteFrameName("chouma.png");
	BeiJin->addChild(m_pChouMa,201);
	m_pChouMa->setPosition(Point(380,41)); 
	ChouMaPos[2] = Point(380,41);

	m_pGuang = Sprite::createWithSpriteFrameName("guangquan.png");
	BeiJin->addChild(m_pGuang,200);
	m_pGuang->setPosition(Point(120,133));
	m_pGuang->setVisible(false);



	/*Sprite * cCha = Sprite::createWithSpriteFrameName("wfxx.png");

	auto ChaItem = MenuItemSprite::create(cCha,cCha,cCha,CC_CALLBACK_1(BiBei::menuCha,this));
	m_ChaCha = Menu::create(ChaItem,nullptr);
	BeiJin->addChild(m_ChaCha,210); */
	
	Point sb = m_ChaCha->getPosition();

	m_ChaCha->setPosition(Point(370,340));


	


	auto dispatcher = Director::getInstance()->getEventDispatcher();

	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(BiBei::onTouchBegan,this);

	listener->onTouchMoved = CC_CALLBACK_2(BiBei::onTouchMoved,this);

	listener->onTouchEnded = CC_CALLBACK_2(BiBei::onTouchEnded,this);

	listener->setSwallowTouches(true);//不向下传递触摸

	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	bibeiTimeTwo = 5;
	OverTimeNum = 7;
	MoveTime = 0;
	bibeiTime = 0;
	bMoverOver = false;
	cPos = 0;
	m_cNowTime= 2;
	m_cTime = 0;
	 schedule(schedule_selector(BiBei::updateBiBei),0.03f);
	return true;
}


void BiBei::updateBiBei(float delta)
{  



	/*m_cTime++
	if(m_cTime == 30)
	{
		if(m_cNowTime>= 0 )
		{
			m_pNum
		}
		 
	}*/
	if(bMoverOver == true)
	{
		bibeiTime++;
		if(bibeiTime == bibeiTimeTwo)
		{
			bibeiTime = 0;
			if(cPos == 0)
			{
				cPos = 1;
			}
			else if(cPos == 1)
			{
				cPos = 0;
			}
			m_pGuang->setPosition(GuangPos[cPos]);

			MoveTime++;
			if(MoveTime == OverTimeNum)
			{
				if(bibeiTimeTwo == 10)
				{   
					if(cChoose == cPos)
					{
						cChooseTime ++;

						iBiBeiMoney = iBiBeiMoney*2;

					 
						char cTmepNum[20] = {0};
						sprintf(cTmepNum,"%d", iBiBeiMoney);
						MoneyLabel->setString( cTmepNum);    





						auto ac1 = DelayTime::create(1.0f);
						auto ac2 = CCCallFunc::create(this,callfunc_selector(BiBei::ShowKuangOne));


						auto seq = Sequence::create(ac1,ac2,nullptr);
						 
						this->runAction(seq);


						
					}
					else
					{
						auto ac1 = DelayTime::create(1.0f);
						auto ac2 = CCCallFunc::create(this,callfunc_selector(BiBei::ShowKuangTwo));


						auto seq = Sequence::create(ac1,ac2,nullptr);

						this->runAction(seq);

						
					}
					bMoverOver = false;
					return;
				}
				MoveTime = 0;
				OverTimeNum =4+CCRANDOM_0_1()*4;
				bibeiTimeTwo  =  10;

				
				int iRandom = CCRANDOM_0_1()*100;
				if(cChooseTime == 0 )
				{
					if(iRandom >60 )
 					{
						if(OverTimeNum%2 != cChoose)
						{
							OverTimeNum++;

						}
					}
					else
					{
 						if(OverTimeNum%2 == cChoose)
						{
							OverTimeNum++;
						}
					}
				}
				else if(cChooseTime == 1)
				{
					if(iRandom >70 )
					{
						if(OverTimeNum%2 != cChoose)
						{
							OverTimeNum++;

						}
					}
					else
					{
						if(OverTimeNum%2 == cChoose)
						{
							OverTimeNum++;
						}
					}
				}
				else if(cChooseTime == 2)
				{
					if(iRandom >70 )
					{
						if(OverTimeNum%2 != cChoose)
						{
							OverTimeNum++;

						}
					}
					else
					{
						if(OverTimeNum%2 == cChoose)
						{
							OverTimeNum++;
						}
					}
				}
				else if(cChooseTime == 3)
				{
					if(iRandom >80 )
					{
						if(OverTimeNum%2 != cChoose)
						{
							OverTimeNum++;

						}
					}
					else
					{
						if(OverTimeNum%2 == cChoose)
						{
							OverTimeNum++;
						}
					}
				}
				else if(cChooseTime == 4)
				{
					if(iRandom >90 )
					{
						if(OverTimeNum%2 != cChoose)
						{
							OverTimeNum++;

						}
					}
					else
					{
						if(OverTimeNum%2 == cChoose)
						{
							OverTimeNum++;
						}
					}
				}
				else if(cChooseTime == 5)
				{
					if(iRandom >95 )
					{
						if(OverTimeNum%2 != cChoose)
						{
							OverTimeNum++;

						}
					}
					else
					{
						if(OverTimeNum%2 == cChoose)
						{
							OverTimeNum++;
						}
					}
				}
				else if(cChooseTime == 6)
				{
					if(iRandom >98 )
					{
						if(OverTimeNum%2 != cChoose)
						{
							OverTimeNum++;

						}
					}
					else
					{
						if(OverTimeNum%2 == cChoose)
						{
							OverTimeNum++;
						}
					}
				}
				else if(cChooseTime == 7)
				{
					if(iRandom >99 )
					{
						if(OverTimeNum%2 != cChoose)
						{
							OverTimeNum++;

						}
					}
					else
					{
						if(OverTimeNum%2 == cChoose)
						{
							OverTimeNum++;
						}
					}
				}
				else if(cChooseTime == 8)
				{
					if(iRandom >100 )
					{
						if(OverTimeNum%2 != cChoose)
						{
							OverTimeNum++;

						}
					}
					else
					{
						if(OverTimeNum%2 == cChoose)
						{
							OverTimeNum++;
						}
					}
				} 
				cChooseTime++;
			}

		}
	}
	
}
void BiBei::menuCha(Ref* pSender)
{

	CannonLayer::GameCoinRefresh(iBiBeiMoney);


	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this,true);
	this->getParent()->removeChild(this,true);

}

void BiBei::ShowKuangOne()
{
	bibeiTimeTwo = 5;
	OverTimeNum = 10;
	MoveTime = 0;
	bibeiTime = 0;
	bMoverOver = false;
	cPos = 0;
	 
	m_pGuang->setVisible(false);
	m_ChooseBig->setEnabled(true);
	m_ChooseSmall->setEnabled(true);  

	m_pChouMa->setPosition(ChouMaPos[2]);
	auto gongxi = Gongxi::create(1,GAME_DATA_STRING("bibeihuosheng"));
	gongxi->setPosition(Point(0,0));
	this->addChild(gongxi); 
}

void BiBei::ShowKuangTwo()
{

	iBiBeiMoney = 0; 
	MoneyLabel->setString("0");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();

	string text =  GAME_DATA_STRING("bibeishibai");
	auto wordTTF = Label::createWithSystemFont(text,"",26);
	wordTTF->setColor(Color3B(233,227,205));
	wordTTF->setPosition(Point(visibleSize.width/2,visibleSize.height*0.53));
	this->addChild(wordTTF,1000);

	m_ChaCha->setEnabled(false);
	//弹出框

	auto gongxiBg = Scale9Sprite::createWithSpriteFrameName( "gongxibg.png",Rect(95,95,10,10) );
	gongxiBg->setContentSize(Size(504,413));
	gongxiBg->setTag(1);
	gongxiBg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(gongxiBg,10);

	auto gongxiSprite = Sprite::createWithSpriteFrameName("XR_qd.png" ); 
	auto gongxiItem = MenuItemSprite::create(gongxiSprite,gongxiSprite,gongxiSprite,CC_CALLBACK_1(BiBei::menuCha,this)); 
	auto gongxiMenu = Menu::create(gongxiItem,nullptr);
	gongxiMenu->setPosition(gongxiBg->getContentSize().width/2,0.18*gongxiBg->getContentSize().height);
	gongxiBg->addChild(gongxiMenu,100); 
	 
}
void BiBei::menuBig(Ref* pSender)
{
  

	cChoose = 0;
	auto ac1  = MoveTo::create(0.5f,ChouMaPos[0]);
	auto ac2 = CCCallFunc::create(this,callfunc_selector(BiBei::MoveEnd));


	auto seq = Sequence::create(ac1,ac2,nullptr);

	m_pChouMa->runAction(seq);

}


void BiBei::menuSmall(Ref* pSender)
{
	cChoose = 1;

	auto ac1  = MoveTo::create(0.5f,ChouMaPos[1]);
	auto ac2 = CCCallFunc::create(this,callfunc_selector(BiBei::MoveEnd));


	auto seq = Sequence::create(ac1,ac2,nullptr);

	m_pChouMa->runAction(seq);
}

void BiBei::MoveEnd()
{
	bMoverOver = true;
	m_ChooseBig->setEnabled(false);
	m_ChooseSmall->setEnabled(false);
	m_pGuang->setVisible(true);
}


bool BiBei::onTouchBegan(Touch* touch, Event* event) 
{ 
	 
	return true;
}

void BiBei::onTouchMoved(Touch* touch, Event* event) 
{

}


void BiBei::onTouchEnded(Touch* touch, Event* event)
{
}