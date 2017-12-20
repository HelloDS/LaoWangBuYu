#include "UnLockLayer.h" 
#include "CannonLayer.h"
#include "SimpleAudioEngine.h"
#include "GameData.h"
#include "Gongxi.h"
#include "GameBegin.h"
#include "GameScene.h"
#include "GameHallLayer.h"
#include "LoadRes.h"
#include "Shop.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

USING_NS_CC;
using namespace std;

bool UnLockLayer::ul_success = false;

UnLockLayer::UnLockLayer()
{
}
UnLockLayer::~UnLockLayer()
{
}

Layer* UnLockLayer::create(int lockKind)
{
	UnLockLayer * layer = new UnLockLayer();
	layer->init(lockKind);
	layer->autorelease();
	return layer;
}

bool UnLockLayer::init(int i)
{
	if ( !Layer::init() )	
	{
		return false;
	} 
	

	blockKind = i;
	hitFlag = 1;
	cur_room = -1;
	visibleSize = Director::getInstance()->getVisibleSize();
 
	ul_success = false;
 
	auto zheZhao = LayerColor::create(ccc4(0,0,0,150),1024,768);
 	zheZhao->setPosition(Point::ZERO);
	zheZhao->setScale(2.0f);
	this->addChild(zheZhao);

	CanBtn = true;
 
	for(int i =1; i<= 20; i++)
	{
		char cTempName[20];
		sprintf(cTempName,"bljs_dj_%d",i);
		cWuqiLv[i-1]=GAME_DATA_INT(cTempName);

		memset(cTempName,0,sizeof(cTempName));
		sprintf(cTempName,"bljs_zuanshi_%d",i);
		cWuqiXiaoHao[i-1] = GAME_DATA_INT(cTempName);
 	 
		memset(cTempName,0,sizeof(cTempName));
		sprintf(cTempName,"bljs_jinbi_%d",i);
		cWuqiXiaoHaoJinBi[i-1] = GAME_DATA_INT(cTempName);
 
		memset(cTempName,0,sizeof(cTempName));
		sprintf(cTempName,"bljs_rate_%d",i);
		cBeiLv[i-1] = GAME_DATA_INT(cTempName);

		if(i<=GameBegin::WangW[0])
		{
			jiesuopao[i-1] = "paoone.png";
			jiesuopaoBg[i-1] = "paoonebg.png";
			continue;
		}
		if(i<=GameBegin::WangW[1])
		{
			jiesuopao[i-1] = "paotwo.png";
			jiesuopaoBg[i-1] = "paoonebg.png";
			continue;
		}
		if(i<=GameBegin::WangW[2])
		{
			jiesuopao[i-1] = "paothree.png";
			jiesuopaoBg[i-1] = "paoonebg.png";
			continue;
		}
		if(i<=GameBegin::WangW[3])
		{
			jiesuopao[i-1] = "paofour.png";
			jiesuopaoBg[i-1] = "paofourbg.png";
			continue;
		}
		if(i <=GameBegin::WangW[4])
		{
			jiesuopao[i-1] = "paofive.png";
			jiesuopaoBg[i-1] = "paofivebg.png";
			continue;
		}
		if(i <= GameBegin::WangW[5])
		{
			jiesuopao[i-1] = "paosix.png";
			jiesuopaoBg[i-1] = "paosixbg.png";
			continue;
		}

	}
 
	//背景&叉叉
	paoBG = Scale9Sprite::createWithSpriteFrameName( "bs_kuang.png",CCRectMake(99,99,20,20));
	paoBG->setContentSize(CCSizeMake(820,400));
	paoBG->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	this->addChild(paoBG);

	paoBG->setScale(0.1f);
	ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.1f, 1.0);  
	paoBG->runAction(Sequence::create(ac7,ac8,nullptr)); 

	auto shopCenterBg1 = Sprite::createWithSpriteFrameName("beilv_title.png");
	shopCenterBg1->setPosition(Point(paoBG->getContentSize().width/2,paoBG->getContentSize().height));
	paoBG->addChild(shopCenterBg1,100);

	auto shangchengxx = MenuItemSprite::create(Sprite::createWithSpriteFrameName("hall_menu_X.png"),Sprite::createWithSpriteFrameName("hall_menu_X_d.png"), CC_CALLBACK_0(UnLockLayer::Exit,this));
	auto m_ShangChengXX= Menu::create(shangchengxx, nullptr);
	m_ShangChengXX->setPosition(Vec2(paoBG->getContentSize().width - 10,paoBG->getContentSize().height - 10));
	paoBG->addChild(m_ShangChengXX,100);

	//获得对象的size
	Size bgSize = Size(820,440);
	roomSize = Size(252,338);
	paoBeginPos = (bgSize.width-60-3*roomSize.width)/4;
	spacePaoLength = roomSize.width+paoBeginPos;

	for(int posi = 0 ;posi<20 ;posi++)
	{
		Pos[posi] = Point(paoBeginPos + (posi + 0.5) * spacePaoLength, bgSize.height/2);
	}
 

	auto shop_diguang = Sprite::createWithSpriteFrameName("shop_diguang.png");
	shop_diguang->setAnchorPoint(Vec2(0.5,0));
	shop_diguang->setPosition(Point( 0.5 * roomSize.width + paoBeginPos ,11));
	paoBG->addChild(shop_diguang,100);

	auto shop_diguang1 = Sprite::createWithSpriteFrameName("shop_diguang.png");
	shop_diguang1->setAnchorPoint(Vec2(0.5,0));
	shop_diguang1->setPosition(Point( 1.5 * roomSize.width + paoBeginPos ,11));
	paoBG->addChild(shop_diguang1,100);

	auto shop_diguang2 = Sprite::createWithSpriteFrameName("shop_diguang.png");
	shop_diguang2->setAnchorPoint(Vec2(0.5,0));
	shop_diguang2->setPosition(Point( 2.5 * roomSize.width + paoBeginPos,11));
	paoBG->addChild(shop_diguang2,100);
 
	//获得要初始化的炮的信息
	myJieSuoNum  = GameBegin::getFileData("gameMaxPao.txt");
	for(int i = myJieSuoNum ; i < 20 ; i++)
	{
		Sprite *sprite1 = createSprite(i+1);             
		m_Tree.pushBack(sprite1);    
	}

	//滑板
	containerLayer = Layer::create();
	containerLayer->setPosition(Point::ZERO);
	containerLayer->setAnchorPoint(Point::ZERO);
	layer_x = 0;
	containerLayer->setContentSize(Size((20 - myJieSuoNum) * spacePaoLength,bgSize.height));

	scrollview = ScrollView::create(bgSize - Size(24,20),containerLayer);
	scrollview->setDelegate(this);
	scrollview->ignoreAnchorPointForPosition(false);
	scrollview->setAnchorPoint(Vec2(0.5,0.5));
	scrollview->setDirection(ScrollView::Direction::HORIZONTAL);
	scrollview->setPosition(Point(paoBG->getContentSize().width/2 + 1,paoBG->getContentSize().height/2 - 20));
	paoBG->addChild(scrollview,100);
 
	if (!m_Tree.empty()) 
	{
		int temp =0; 
		for(auto sp1 : m_Tree)
		{   			
			Sprite * sprite = sp1;
			sprite->setPosition(Pos[temp]);
			sprite->setScale(SHOP_ROOM_L);
			containerLayer->addChild(sprite);
			temp++;			 
		}	
	}
 

	if(myJieSuoNum<20)
	{	  
		faGuangBG = Sprite::createWithSpriteFrameName("faguang.png");                                                       
		faGuangBG->setPosition(Pos[0]-Point(2,8));      
		faGuangBG->setScale(SHOP_ROOM_L);
		containerLayer->addChild(faGuangBG,1);   

		m_frameUpdate =0;
		m_frameTime = 0.2f;		
	}
 
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(UnLockLayer::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(UnLockLayer::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(UnLockLayer::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
 
	this->scheduleUpdate();
}

void  UnLockLayer::Exit() 
{ 
	CannonLayer::bToMax = true;
	GameBegin::buttonSound();
	ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
	paoBG->runAction(Sequence::create(ac7,ac8,nullptr)); 

	this->runAction(Sequence::create(DelayTime::create(0.3f),RemoveSelf::create(),nullptr));
}

Sprite * UnLockLayer::createSprite(int i)
{
	char cTempName[20];
	sprintf(cTempName,"bljs_rate_%d",i);

	Sprite *tempSprite = Sprite::createWithSpriteFrameName("BG_biaoqian.png");//房间背景       
                          
    auto *tempSpritePaoNum =  Label::create();         //炮的倍数                        
    tempSpritePaoNum->setCharMap("img/onedao9.png",30,40,'0');                         
	tempSpritePaoNum->setString(GAME_DATA_STRING(cTempName));                                          
	tempSpritePaoNum->setPosition(Point(90,roomSize.height*0.5));                                
    tempSpritePaoNum->setAnchorPoint(Point(0.5,0.5));                            
    tempSprite->addChild(tempSpritePaoNum);  

	if(i == 20) 
	{
		tempSpritePaoNum->setScaleX(0.7);
	}
                                         
	memset(cTempName,0,sizeof(cTempName));
	sprintf(cTempName,"bljs_zuanshi_%d",i);

    auto *tempSpriteDiaNum =  Label::create();                                 
    tempSpriteDiaNum->setCharMap("img/onedao9.png",30,40,'0');                         
	tempSpriteDiaNum->setString(GAME_DATA_STRING(cTempName));                                          
    tempSpriteDiaNum->setPosition(Point(roomSize.width/2,roomSize.height*0.18));                                
    tempSpriteDiaNum->setAnchorPoint(Point(0.5,0.5));  
	tempSpriteDiaNum->setTag(GAME_DATA_INT(cTempName));
    tempSprite->addChild(tempSpriteDiaNum);                                       
            
	memset(cTempName,0,sizeof(cTempName));
	sprintf(cTempName,"bljs_dj_%d",i);
    auto *tempSpriteUnLockNum =  Label::create();                              
    tempSpriteUnLockNum->setCharMap("img/bluenum.png",30,40,'0');                  
	tempSpriteUnLockNum->setString(GAME_DATA_STRING(cTempName));                                       
    tempSpriteUnLockNum->setPosition(Point(roomSize.width*0.781+10,roomSize.height*0.33));                          
    tempSpriteUnLockNum->setAnchorPoint(Point(0.5,0.5));                         
    tempSprite->addChild(tempSpriteUnLockNum);                                    
                                                                                  
	auto *tempSpritePaoBg = Sprite::createWithSpriteFrameName(jiesuopaoBg[i-1]); 
    tempSpritePaoBg->setAnchorPoint(Point(0.5,0));                               
    tempSpritePaoBg->setPosition(Point(roomSize.width/2,roomSize.height*0.58));                                 
    tempSprite->addChild(tempSpritePaoBg);                                        
                                                                                  
    auto *tempSpritePao = Sprite::createWithSpriteFrameName(jiesuopao[i-1]);     
    tempSpritePao->setAnchorPoint(Point(0.5,0));                                 
    tempSpritePao->setPosition(Point(roomSize.width/2,roomSize.height*0.58 + 35));    
    tempSprite->addChild(tempSpritePao);                                          
                        
	Sprite *tempSpritelock = Sprite::createWithSpriteFrameName("lock.png");//第二个炮加锁
	tempSpritelock->setAnchorPoint(Point(0.5,0.5));
	tempSpritelock->setTag(8);
	tempSpritelock->setPosition(Point(roomSize.width/2,roomSize.height*0.58 + 35));
	tempSprite->addChild(tempSpritelock);

	return tempSprite;
}

void UnLockLayer::ditFunc(int i)
{
	GameBegin::buttonSound();
	if(i != 0) 
	{ 	
		if(CanBtn == false)
			return;
		auto gongxi = Gongxi::create(2,GAME_DATA_STRING("jiesuo_dide"));
		this->addChild(gongxi);
	}
	
	if(i == 0)
	{
		if(CanBtn == false)
			return;
		int iTemp = GameBegin::getFileData("gameMaxPao.txt");
		if(iTemp == 20)
			return; 
		if(GameBegin::getFileData("gamePlayerlv.txt") < cWuqiLv[iTemp] )
		{
			char level[100];
			sprintf(level,GAME_DATA_STRING("gamehall_level_low"),cWuqiLv[iTemp]);
			auto gongxi = Gongxi::create(3,level);
			gongxi->setPosition(Point::ZERO);
			this->addChild(gongxi,1000,1000);

			auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png");
			auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(UnLockLayer::shengjilv,this));

			auto btnMenu = Menu::create(quedingItem,nullptr);
			btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
			gongxi->getChildByTag(1)->addChild(btnMenu,100);
			log("deng ji bu zu");
			return;
		}
		if( GameBegin::getFileData("jywopl.txt") < cWuqiXiaoHao[iTemp])
		{
			if(blockKind != 1)
			{
				 
				if(GameBegin::getFileData("jywer.txt") > cWuqiXiaoHaoJinBi[iTemp] && GameBegin::getFileData("gamePlayerlv.txt") > 4)
				{ 
					char money[100];
					sprintf(money,GAME_DATA_STRING("jiesuojinbi"),cWuqiXiaoHaoJinBi[iTemp]);  
					auto gongxi = Gongxi::create(3,money);
					gongxi->setPosition(Point::ZERO);
					this->addChild(gongxi,1000);

					auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png" );
					auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(UnLockLayer::goumaiwuqi,this));
					auto btnMenu = Menu::create(quedingItem,nullptr);
					btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
					gongxi->getChildByTag(1)->addChild(btnMenu,100);

				}
				else
				{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)	
					auto gongxi = Gongxi::create(3,GAME_DATA_STRING("gamehall_zuanshi_low"));
					gongxi->setPosition(Point::ZERO);
					this->addChild(gongxi,1000,999);

					auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png" );
                    auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(UnLockLayer::goumaizuanshi,this));
                    auto btnMenu = Menu::create(quedingItem,nullptr);
                    btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
                    gongxi->getChildByTag(1)->addChild(btnMenu,100);
#endif

				}
			}
			else
			{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)	
					auto gongxi = Gongxi::create(3,GAME_DATA_STRING("gamehall_zuanshi_low"));
					gongxi->setPosition(Point::ZERO);
					this->addChild(gongxi,1000,999);

					auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png" );
                    auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(UnLockLayer::goumaizuanshi,this));
                    auto btnMenu = Menu::create(quedingItem,nullptr);
                    btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
                    gongxi->getChildByTag(1)->addChild(btnMenu,100);
#endif
			}
			log("zuanshi bu zu");
			return;
		}
 
		char zuanshiTmp[20];
		sprintf(zuanshiTmp,"bljs_zuanshi_%d",GameBegin::getFileData("gameMaxPao.txt") + 1);
		if(blockKind == 1)
		{
			quShengji();

			GameBegin::setFileData("gameMaxPao.txt", GameBegin::getFileData("gameMaxPao.txt") + 1 );
			GameHallLayer::RefreshDiamond(-GAME_DATA_INT(zuanshiTmp)); 
		}else
		{
			if(CannonLayer::cNowMaxPao + 1 < GameHallLayer::sceneHighPao)
			{
				quShengji();
				CannonLayer::cNowMaxPao ++;
				GameBegin::setFileData("gameMaxPao.txt", GameBegin::getFileData("gameMaxPao.txt") + 1 );
				CannonLayer::GameCoinZuanshi(-GAME_DATA_INT(zuanshiTmp));


				CannonLayer::bupdateJiesuo = true;
				CannonLayer::bShowJieSuoXiaoShi = true;

				if(CannonLayer::cNowMaxPao == GameHallLayer::sceneHighPao - 1)
				{
					auto layer = this->getParent();
					auto beilv = Gongxi::create(1,GAME_DATA_STRING("beilvzuigao"));
					beilv->setPosition(Vec2::ZERO);
					layer->addChild(beilv,10000); 

					CannonLayer::bToMax = true;
					Exit();
				}
			}else
			{
				auto layer = this->getParent();
				auto beilv = Gongxi::create(2,GAME_DATA_STRING("beilvzuigao"));
				beilv->setPosition(Vec2::ZERO);
				layer->addChild(beilv,10000);

				CannonLayer::bToMax = true;
				this->removeFromParent();				
			}
			
		}
		

	}
}

void UnLockLayer::shengjilv()
{
    GameBegin::buttonSound();
	this->removeChildByTag(1000);

	if(blockKind == 1)
	{
		GameHallLayer::initRoom();

		char sceneLowRateTmp[20];
		sprintf(sceneLowRateTmp,"boss_low_odd_%d",GameHallLayer::RoomType + 1);
		char sceneHighRateTmp[20];
		sprintf(sceneHighRateTmp,"boss_high_%d",GameHallLayer::RoomType + 1);
		GameHallLayer::sceneLowPao = GAME_DATA_INT(sceneLowRateTmp);
		GameHallLayer::sceneHighPao = GAME_DATA_INT(sceneHighRateTmp);

		this->removeAllChildrenWithCleanup(true);
		this->unscheduleAllSelectors();
        
        GameBegin::removeSouce(1);

		LoadRes::RoomType = GameHallLayer:: RoomType;
		auto scene = LoadRes::createScene();	
		Director::getInstance()->replaceScene(scene);   
		 
	}else
	{
		this->removeFromParentAndCleanup(true);
	}
  
}

void UnLockLayer::goumaiwuqi()
{

	quShengji();

	CannonLayer::cNowMaxPao = GameBegin::getFileData("gameMaxPao.txt") ;

	GameBegin::setFileData("gameMaxPao.txt",CannonLayer::cNowMaxPao+1 );

	char zuanshiTmp[20];
	sprintf(zuanshiTmp,"bljs_jinbi_%d",GameBegin::getFileData("gameMaxPao.txt"));
	int tmpZuanshi = GameBegin::getFileData("jywer.txt") - GAME_DATA_INT(zuanshiTmp);
	GameBegin::setFileData("jywer.txt",tmpZuanshi);

	CannonLayer::bupdateJiesuo = true;
	CannonLayer::bShowJieSuoXiaoShi = true;

	char zuanshiTmp1[20];
	sprintf(zuanshiTmp1,"%d",tmpZuanshi);
	CannonLayer::GameCoinLabel[4]->setString(zuanshiTmp1);   
	this->removeFromParent(); 
}

void UnLockLayer::goumaizuanshi()
{
	this->removeChildByTag(999);
 
    auto shop = Shop::create(blockKind);
    this->getParent()->addChild(shop,10000);
   
    this->removeFromParent();
}

void UnLockLayer::update(float delta)
{
	if(ul_success)
	{
		ul_success = false;

		int bb = GameBegin::getFileData("gameMaxPao.txt") ; 
		if(bb < 11)
		{
			GameBegin::setFileData("gameMaxPao.txt",10);
		}


		char textTmp[100];
		sprintf(textTmp,GAME_DATA_STRING("goumai_chenggong"),10000,150);

		if(blockKind == 1)
		{
			GameHallLayer::RefreshCoin(10000);
			GameHallLayer::RefreshDiamond(150);
		}else
		{
			CannonLayer::GameCoinRefresh(10000);
			CannonLayer::GameCoinZuanshi(150);
		}
		auto layer = this->getParent();

		auto  gongxi = Gongxi::create(1,textTmp);
		gongxi->setPosition(Point::ZERO);
		layer->addChild(gongxi,1000);

		this->removeFromParent();
	}
	if(hitFlag == 1 )
	{
		m_frameUpdate+= delta;
		if(m_frameUpdate >m_frameTime)
		{
			m_frameUpdate = 0;
			
			if(faGuangBG->isVisible())
			{
				faGuangBG->setVisible(false);
			}	
			else 
			{
				faGuangBG->setVisible(true);	 
			}
		}
	}
 
}

void UnLockLayer::MoveOver()
{ 
 
	containerLayer->removeChild(m_Tree.at(0),true);
	m_Tree.eraseObject(m_Tree.at(0),true);	
	myJieSuoNum++; 

	if (!m_Tree.empty()) 
	{
		int temp =0; 
		for(auto sp1 : m_Tree)
		{   
			Sprite * sprite = sp1;
			{
				if(temp == 0)
				{
					auto move=  MoveTo::create(0.5f,Pos[temp]);
					auto cal  = CallFunc::create(CC_CALLBACK_0(UnLockLayer::ShanShuo,this));
					auto seq = Sequence::create(move,cal,nullptr);
					sprite->runAction(seq);
				}else
				{
					auto move=  MoveTo::create(0.5f,Pos[temp]);
					sprite->runAction(move);
				}
			}
			temp++;
		}
		containerLayer->setContentSize(CCSizeMake(paoBeginPos+temp*(roomSize.width+paoBeginPos), roomSize.height+50));
		
	}	
	else
	{ 
		auto gongxi = Gongxi::create(1,GAME_DATA_STRING("shop_buy_libao_1"));
		gongxi->setPosition(Point::ZERO);
	
		hitFlag=0;
		faGuangBG->setVisible(false);
		//return;
		this->unscheduleUpdate();

		auto parent = this->getParent();
		parent->addChild(gongxi,1000);

		Exit();
		return;
	}
}

void UnLockLayer::FadeIn()
{
	if (!m_Tree.empty()) 
	{
		int temp =0; 
		for(auto sp1 : m_Tree)
		{   
			if( temp == 2)
			{
				Sprite * sprite = sp1;
				sprite->setVisible(true);
				sprite->setOpacity(0);
				auto move=  FadeIn::create(0.5f);
				sprite->runAction(move);
				break;
			}
			temp++;
		}
	}
	
}

void UnLockLayer::ShanShuo()
{
	if(myJieSuoNum<20)
	{
		hitFlag = 1;
		CanBtn = true;
	}
}

bool UnLockLayer::onTouchBegan(Touch* touch, Event* event) 
{ 

	p1 = touch->getLocation();

	//首先判断是否在scrollview之内
	if(p1.y < visibleSize.height/2 + roomSize.height/2 * SHOP_ROOM_L  && p1.y > visibleSize.height/2 - roomSize.height/2 * SHOP_ROOM_L)
	{
		float yubiWidth =  scrollview->getViewSize().width;
		float room_x = p1.x -(visibleSize.width - yubiWidth)/2;

		if (room_x > 0 && room_x < yubiWidth)
		{
			room_x = room_x + layer_x;

			//判断在哪个炮内  就放大哪个炮
			for(int i = myJieSuoNum; i < 20 ; i++)
			{
				if(room_x - roomSize.width * (i-myJieSuoNum)> roomSize.width * (1 - SHOP_ROOM_L)/2 && room_x - roomSize.width * (i-myJieSuoNum) < roomSize.width * (1 - SHOP_ROOM_L)/2 + roomSize.width *  SHOP_ROOM_L)
				{
					cur_room = i-myJieSuoNum;
					m_Tree.at(cur_room)->setScale(SHOP_ROOM_H);
					if(cur_room == 0)
					{
						faGuangBG->setScale(SHOP_ROOM_H);
					}
					break;
				}
			}
		}
	}

	return true;
}

void UnLockLayer::onTouchMoved(Touch* touch, Event* event)
{
 
}
 
void UnLockLayer::onTouchEnded(Touch* touch, Event* event)
{
	p2 = touch->getLocation();
	cocos2d::log("offset pos is %f ",p2.x);  
	if(cur_room >= 0)
	{
		if(abs(p2.x - p1.x) < 8 )
		{
			ditFunc(cur_room);
		}
		m_Tree.at(cur_room)->setScale(SHOP_ROOM_L);
		if(cur_room == 0)
		{
			faGuangBG->setScale(SHOP_ROOM_L);
		}
		cur_room = -1;
	}
	
	
}
 
void UnLockLayer::quShengji()
{
	if (!m_Tree.empty()) 
	{
		CanBtn = false;
		int i =0; 
		for(auto sp : m_Tree)
		{   
			Sprite * sprite = sp;
			if(i==0)
			{
				auto move=  FadeOut::create(0.5f);
				auto cal  = CallFunc::create(CC_CALLBACK_0(UnLockLayer::MoveOver,this));
				auto seq = Sequence::create(move,cal,nullptr);
				sprite->runAction(seq);

				break;
			}
		}
	}

	faGuangBG->setVisible(false);
	hitFlag = 0;
}

void UnLockLayer::scrollViewDidScroll(ScrollView* view) 
{
	layer_x = abs(view->getContentOffset().x);//获得偏移X坐标(向右移动，偏移量为正数，向左则为负数）  
	cocos2d::log("offset pos is %f ",layer_x);  
}

void UnLockLayer::scrollViewDidZoom(ScrollView* view) 
{
}