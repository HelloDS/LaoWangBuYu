#include "CannonLayer.h"	
#include "StaticData.h" 
#include "FishLayer.h"
#include "SimpleAudioEngine.h"
#include "Gongxi.h"
#include "TiShi.h"
#include "GameScene.h"
#include "LogoLayer.h"
#include "GameBegin.h"
#include "UnLockLayer.h" 
#include "LoadRes.h" 
#include "LvUp.h" 
#include "GameHallLayer.h"
#include "Shop.h"
#include "ZuanPan.h"

char CannonLayer::zuanpanover = 0;
bool CannonLayer::bLvUp;
bool CannonLayer::bupdateJiesuo; 
bool CannonLayer::bxinShouFanWei = false;
bool CannonLayer::bFanweiyindao = false; 
bool CannonLayer::bJiGuangyindao = false;  
bool CannonLayer::bToMax = false;
char  CannonLayer::cZuanShiNum[14];
char   CannonLayer::cConinNum[14];
 
float CannonLayer::robotPos1 = 0;
float CannonLayer::robotPos2 = 0;
int   CannonLayer::iFanWeiCoin[5];
int   CannonLayer::iJiGuangCoin[5];
 
int   CannonLayer::cBeiShu[20]; 
int   CannonLayer::GameExp = 0;
int   CannonLayer::GameLv = 1;
 
int CannonLayer::iLvMoney = 0; 
int CannonLayer::iLvZuan = 0;

int CannonLayer::typeFanWei = 0; 
int CannonLayer::typeJiGuang = 0;
Label *CannonLayer::GameCoinLabel[5]; 
Label *CannonLayer::GameZuanshiLabel=nullptr;
Label *CannonLayer::GameExpLabel=nullptr;
Sprite *CannonLayer::GameChenghao=nullptr; 
Sprite * CannonLayer::jingyanTiao=nullptr;
Sprite *CannonLayer::fanweifontLv=nullptr; 
Sprite * CannonLayer::jiguangfontLv=nullptr;
Sprite * CannonLayer::pro1=nullptr; 

Label *CannonLayer::CountDingPing=nullptr;
Label *CannonLayer::CountJiaSu=nullptr;
Label *CannonLayer::CountFanWei=nullptr; 
Label *CannonLayer::CountVipPao=nullptr; 
Label *CannonLayer::CountJiGuang=nullptr;
int CannonLayer::RobotMoney[4];



 /*
Label *CannonLayer::NowGaiLv=nullptr;
Label *CannonLayer::BossJiangChiwf=nullptr;
Label *CannonLayer::JiangChiwf=nullptr;   
Label *CannonLayer::JiangChiSend=nullptr;
Label *CannonLayer::JiangChiGet=nullptr;
*/
 
bool CannonLayer::bShowJieSuo;
bool CannonLayer::bFirstChoose;
bool CannonLayer::bShowLiBao = false; 

bool CannonLayer::bFanWeiShoot = false;
bool CannonLayer::bJiGuangShoot = false;  
bool CannonLayer::bCanJieSuo = false; 
bool CannonLayer::bVipPaoShoot = false;	
 
bool CannonLayer::isToMaxFlag = false;
bool CannonLayer::bShowJieSuoXiaoShi;
int CannonLayer::iSoundId = 0;
int CannonLayer::cNowMaxPao = 0;
int CannonLayer::_type = 0;
int CannonLayer::xinshoutimefanwei = 0;
int CannonLayer::xinshoutimejiguang = 0;


int CannonLayer::iMoneyJiangchi = 0;
char CannonLayer::cYanZhengHuaFei = 0;
bool CannonLayer::init()
{
	Layer::init();
    czuanpanupdate = 0;
    iMoneyJiangchi = 0;
	for(int i =1; i<= 20; i++)
	{
		char cTempName[20];
		sprintf(cTempName,"bljs_rate_%d",i);
		cBeiShu[i-1]=GAME_DATA_INT(cTempName); 
	} 
    zuanpanover = 0;
    bCheckHuaFeiUpdate = false;
    cAddHuaFeiType = 0;
    cYanZhengHuaFei = 0;
    
	bLock = false;
    xinshoutimefanwei= 0;
	xinshoutimejiguang = 0;

	bFanweiyindao  = false;
	bJiGuangyindao = false;
	
	bJiGuangShoot = false;
	TishiBulletMore = NULL;
	TishiJieSuo = NULL;
	bShowLiBao = false;
	bupdateJiesuo = false; 
	bShowJieSuoXiaoShi = false;
	// cocos2d::log("zipc22222py"); 

	bxinShouFanWei = false;

	m_iSelfVip = UserDefault::getInstance()->getIntegerForKey("player_vip");
	cNowMaxPao = GameBegin::getFileData("gameMaxPao.txt") - 1; 


	label = LabelTTF::create("",GameHallLayer::wordKind,28);
	label->setColor(Color3B::RED);
	label->setPosition(Vec2(550,510));
	this->addChild(label,1000);
   // bFanHuiDating = false;


	if(GameScene::cGameType ==2)
	{ 
		if(cNowMaxPao> 10)
		{
			_type = CCRANDOM_0_1()*11;
		}
		else
		{
			_type = CCRANDOM_0_1()*cNowMaxPao;
		}
		GameHallLayer::sceneHighPao = 20;
		GameHallLayer::sceneLowPao = 1;
	}
	else if(GameScene::cGameType ==0)
	{
		if(cNowMaxPao > GameHallLayer::sceneHighPao - 1   )
		{
			cNowMaxPao = GameHallLayer::sceneHighPao - 1 ;
		}

		if(GameHallLayer::RoomType == 0)
		{
			_type = 0;
		}
		else if(GameHallLayer::RoomType == 1)
		{
            _type = GameHallLayer::sceneLowPao;
			 
		}
		else
		{
            _type = GameHallLayer::sceneLowPao;
			 
		} 
	}
	else if(GameScene::cGameType == 1)
	{
		cNowMaxPao = GameHallLayer::sceneHighPao - 1 ;
	}
	 
	

	
	/*if(GameBegin::RoomType == 7)
	{
		bJiangChiKouMoney = false;
		bJiangChi = false;

	}*/

	

	typeJiGuang =  GameBegin::getFileData("typeFanWei")-1;
	 
	typeFanWei =   GameBegin::getFileData("typeJiGuang")-1; 
 
	 cocos2d::log("wfq1zipc22222py"); 
	
	 
	

	for(int i =1; i<= 5; i++)
	{
		char cTempName[20];
		sprintf(cTempName,"fwp_yb_%d",i);
		iFanWeiCoin[i-1]=GAME_DATA_INT(cTempName); 

	
		memset(cTempName,0,sizeof(cTempName));
		sprintf(cTempName,"jgp_yb_%d",i);
		iJiGuangCoin[i-1]=GAME_DATA_INT(cTempName); 
			

		memset(cTempName,0,sizeof(cTempName));
		sprintf(cTempName,"fwp_cdtime_%d",i);
		iFanWeicd[i-1]=GAME_DATA_INT(cTempName); 


		memset(cTempName,0,sizeof(cTempName));
		sprintf(cTempName,"jgp_cdtime_%d",i);
		iJiGuangcd[i-1]=GAME_DATA_INT(cTempName); 

		memset(cTempName,0,sizeof(cTempName));
		sprintf(cTempName,"fwp_time_%d",i);
		iFanWeiShootcd[i-1]=GAME_DATA_INT(cTempName); 

		memset(cTempName,0,sizeof(cTempName));
		sprintf(cTempName,"jgp_time_%d",i);
		iJiGuangShootcd[i-1]=GAME_DATA_INT(cTempName); 

		memset(cTempName,0,sizeof(cTempName));
		sprintf(cTempName,"fwp_fish_num_%d",i);
		iFanWeiNum[i-1]=GAME_DATA_INT(cTempName); 

		memset(cTempName,0,sizeof(cTempName));
		sprintf(cTempName,"fwp_zuanshi_%d",i);
		iFanWeiZuanShi[i-1]=GAME_DATA_INT(cTempName); 

		memset(cTempName,0,sizeof(cTempName));
		sprintf(cTempName,"jgp_zuanshi_%d",i);
		iJiGuangZuanShi[i-1]=GAME_DATA_INT(cTempName);   
	}
	


	GameLv = GameBegin::getFileData("gamePlayerlv.txt");
	winSize = Director::getInstance()->getWinSize();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	robotPos1 = visibleSize.width * 0.28;
	robotPos2 = visibleSize.width * 0.72;

	bShowWuQiTiShi = false;
	iShowTiShiNum = 0;
	bLvUp = false;


	char cTemp[100];

	if(GameScene::cGameType != 1 )
	{


		GameExp =  GameBegin::getFileData("gameExp.txt");


		char cTempName[20];
		sprintf(cTempName,"bljs_dj_%d",cNowMaxPao + 2);
		int iNeedDengJi = GAME_DATA_INT(cTempName);

		memset(cTempName,0,sizeof(cTempName));
		sprintf(cTempName,"bljs_zuanshi_%d",cNowMaxPao + 2);
		int iNeedZuanShi  = GAME_DATA_INT(cTempName);


		if(iNeedDengJi > 0 && iNeedZuanShi> 0 && cNowMaxPao < GameHallLayer::sceneHighPao - 1)
		{
			if(GameBegin::getFileData("gamePlayerlv.txt") >= iNeedDengJi  && GameBegin::getFileData("jywopl.txt") >= iNeedZuanShi )
			{ 
				bShowJieSuo = true;
			}
			else
			{
				bShowJieSuo = false;
			}
		}

		iSoundId = 0;

		auto menuspr4 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("renwukuang.png"),Sprite::createWithSpriteFrameName("renwukuang.png"), CC_CALLBACK_1(CannonLayer::menuJieSuo,this)); 
		m_JieSuoKuang= Menu::create(menuspr4, nullptr);  
		m_JieSuoKuang->setPosition(Point(winSize.width*0.1 * 0.833,winSize.height*0.6));  
		m_JieSuoKuang->setVisible(false);
		this->addChild(m_JieSuoKuang, 100);
        
        
        mDiamondIcon = Sprite::createWithSpriteFrameName("diamond.png");
        mDiamondIcon->setVisible(false);
        mDiamondIcon->setScale(0.6f);
        mDiamondIcon->setPosition(ccp(menuspr4->getContentSize().width/2 - mDiamondIcon->getContentSize().width*0.7f,menuspr4->getContentSize().height - mDiamondIcon->getContentSize().height/2));
        menuspr4->addChild(mDiamondIcon,100);

		wordTTF = Label::createWithSystemFont("","",24); 
		wordTTF->setVisible(false);
		wordTTF->setColor(Color3B(233,227,205));
		wordTTF->setPosition(Point(winSize.width*0.1* 0.833,winSize.height*0.6 + 40));
		this->addChild(wordTTF,100);

		wordTTF1 = Label::createWithSystemFont("","",24);
		wordTTF1->setVisible(false);
		wordTTF1->setColor(Color3B(233,227,205));
		wordTTF1->setPosition(Point(winSize.width*0.1* 0.833,winSize.height*0.6 + 15));
		this->addChild(wordTTF1,100);

		dianjijiesuo = Sprite::createWithSpriteFrameName("renwujiesuo.png");
		dianjijiesuo->setVisible(false);
		dianjijiesuo->setPosition(Vec2(winSize.width*0.1* 0.833,winSize.height*0.6 - 30));
		this->addChild(dianjijiesuo,100);
 
		cocos2d::log("wfq2zipc22222py"); 
		bupdateJiesuo= false;

		int tmpExp1 = GameBegin::getFileData("gameExp.txt");
		float exp = 0.f;
		for(int i =1; i<50 ; i++)
		{
			if(tmpExp1<iJingYanDengJi[i])
			{
				exp =(float)tmpExp1/iJingYanDengJi[i];
				break;
			}
			tmpExp1 -= iJingYanDengJi[i];
		}

		jingyanTiao = Sprite::create("img/exptiao.png");
		jingyanTiao->setPosition(Point(12,winSize.height*0.93 - 1));
		jingyanTiao->setAnchorPoint(Point(0,0.5));
		float widthTmp = exp*143;
		float heightTmp = 24;
		jingyanTiao->setTextureRect(Rect(0,0,widthTmp,heightTmp));
		this->addChild(jingyanTiao);

		pro1 = Sprite::create("img/exp.png"); 
		pro1->setPosition(Point(10,winSize.height*0.93));
		pro1->setAnchorPoint(Point(0,0.5));
		this->addChild(pro1,100);

		
		/*_progressBar = ControlSlider::create(pro1,pro2,pro3); 
		_progressBar->setPosition(Point(_progressBar->getContentSize().width/2+20,winSize.height*0.92));
		_progressBar->setMinimumValue(0.0f);
		_progressBar->setMaximumValue(1.0f);
		_progressBar->setValue(exp);
		_progressBar->setEnabled(false);
		this->addChild(_progressBar,2);*/

		//初始化称号
		char playerTitleTmp[30];
		int tmpLv = (int)((GameLv-1)/5) + 1;
		/*sprintf(playerTitleTmp,"chenghao%d.png",(int)((GameLv-1)/5) + 1);
		GameChenghao = Sprite::createWithSpriteFrameName(playerTitleTmp);
		GameChenghao->setPosition(Point(pro1->getContentSize().width/2,pro1->getContentSize().height * 1.5));
		pro1->addChild(GameChenghao,100);*/

		//等级LV
		Sprite * level = Sprite::createWithSpriteFrameName("Lv.png");
		level->setPosition(Point(pro1->getContentSize().width/3,pro1->getContentSize().height/2)); 
		pro1->addChild(level,100); 

		//等级NUM
		GameExpLabel = Label::create();
		GameExpLabel->setCharMap("img/Lvnum.png",30,30,'0');
		
		sprintf(cTemp,"%d",GameLv);
		GameExpLabel->setString(cTemp);
		GameExpLabel->setScale(0.9);
		GameExpLabel->setPosition(Point(pro1->getContentSize().width/3*2 - 8 ,pro1->getContentSize().height/2 + 6 )); 
		pro1->addChild(GameExpLabel,100); 
 
	 
		Sprite * bgbase = Sprite::createWithSpriteFrameName("bgbase.png");
		bgbase->setAnchorPoint(Vec2(0.5,0));
		bgbase->setPosition(Point(winSize.width*0.50 + origin.x,origin.y));
		this->addChild(bgbase,100);  

		auto hall_db_yb_bg1 = Sprite::createWithSpriteFrameName("hall_jia_kuang_1.png");
		//hall_db_yb_bg1->setScale(0.8);
		auto hall_db_yb_bg2 = Sprite::createWithSpriteFrameName("hall_jia_kuang_2.png");
		//hall_db_yb_bg2->setScale(0.8);
		MenuItemSprite * hall_db_yb_bg = MenuItemSprite::create(hall_db_yb_bg1,hall_db_yb_bg2,CC_CALLBACK_1(CannonLayer::hall_shangcheng_func,this));

		//鱼币icon
		auto hall_db_yb_icon = Sprite::createWithSpriteFrameName("yubi.png");
		hall_db_yb_icon->setScale(0.8);
		hall_db_yb_icon->setPosition(Vec2(hall_db_yb_bg->getContentSize().width * 0.083,hall_db_yb_bg->getContentSize().height * 0.5));
		hall_db_yb_bg->addChild(hall_db_yb_icon);

		//鱼币数量label
		GameCoinLabel[4] = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
		sprintf(cTemp,"%d",GameBegin::getFileData("jywer.txt"));
		GameCoinLabel[4]->setString(cTemp);
		GameCoinLabel[4]->setScale(0.7);
		GameCoinLabel[4]->setPosition(Point(hall_db_yb_bg->getContentSize().width/2,hall_db_yb_bg->getContentSize().height/2));
		hall_db_yb_bg->addChild(GameCoinLabel[4]);
		hall_db_yb_bg->setScale(0.64);
 
		//钻石数值背景
		auto hall_db_zs_bg1 = Sprite::createWithSpriteFrameName("hall_jia_kuang_1.png");
		hall_db_zs_bg1->setFlippedX(true);
	//	hall_db_zs_bg1->setScale(0.8);
		auto hall_db_zs_bg2 = Sprite::createWithSpriteFrameName("hall_jia_kuang_2.png");
		hall_db_zs_bg2->setFlippedX(true);
		//hall_db_zs_bg2->setScale(0.8);
		MenuItemSprite * hall_db_zs_bg = MenuItemSprite::create(hall_db_zs_bg1,hall_db_zs_bg2,CC_CALLBACK_1(CannonLayer::hall_shangcheng_func,this));
		//钻石icon
		auto hall_db_zs_icon = Sprite::createWithSpriteFrameName("diamond.png");
		hall_db_zs_icon->setScale(0.8);
		hall_db_zs_icon->setPosition(Vec2(hall_db_zs_bg->getContentSize().width * 0.917,hall_db_zs_bg->getContentSize().height * 0.5));
		hall_db_zs_bg->addChild(hall_db_zs_icon);

		//钻石数量label
		GameZuanshiLabel = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
		GameZuanshiLabel->setScale(0.7);
		sprintf(cTemp,"%d",GameBegin::getFileData("jywopl.txt"));
		GameZuanshiLabel->setString(cTemp);
		GameZuanshiLabel->setPosition(Point(hall_db_zs_bg->getContentSize().width/2,hall_db_zs_bg->getContentSize().height/2));
		hall_db_zs_bg->addChild(GameZuanshiLabel);
		hall_db_zs_bg->setScale(0.64); 
 
		auto hall_db_menu = Menu::create(hall_db_yb_bg,hall_db_zs_bg,nullptr);
		hall_db_menu->alignItemsHorizontallyWithPadding(300 * 0.833);
		hall_db_menu->setPosition(Vec2(bgbase->getContentSize().width*0.5,bgbase->getContentSize().height * 0.4));
		bgbase->addChild(hall_db_menu);  

	}
	else
	{
		for(int i = 0; i< 4; i++)
		{			 
			bChangeRobotBaseIfOver[i] = false;
			if(GameScene::cSelfPos == i)
			{
				initRobot(i,true);
			}
			else
			{
				if(GameScene::bRobotPos[i] == true)
				{
					initRobot(i,false);
				} 
			}
		}

		//初始化箭头
		auto hall_tishi_bs = Sprite::createWithSpriteFrameName ( "bs_jiantou_weizhi.png");  //bs_zhixiangjt
		hall_tishi_bs->setScale(1.9);
		if(GameScene::cSelfPos  == 0)
		{
			hall_tishi_bs->setPosition(Vec2(robotPos1,visibleSize.height * 0.24));
		}else
		{
			hall_tishi_bs->setPosition(Vec2(robotPos2,visibleSize.height * 0.24));
		}
		
		addChild(hall_tishi_bs);
 
		hall_tishi_bs->runAction(Sequence::create(Repeat::create(Sequence::create(Spawn::create(ScaleTo::create(0.25f,1.8),MoveBy::create(0.25f,Vec2(0,20)),nullptr),
		Spawn::create(ScaleTo::create(0.25f,1.9),MoveBy::create(0.25f,Vec2(0,-20)),nullptr),nullptr),10),RemoveSelf::create(),nullptr));
		 
	}

	  
	
	paoTexiaoSpr = Sprite::create(); 
	
	this->addChild(paoTexiaoSpr, 150);

	bpaoTeXiao = false;
	m_fUpdateTime = 0;
	m_fTime = 0;

	auto sub = Sprite::createWithSpriteFrameName("paoonejian.png");
	auto add = Sprite::createWithSpriteFrameName("paoonejia.png");
	m_SubItem = MenuItemSprite::create(sub,sub,sub, CC_CALLBACK_1(CannonLayer::switchCannon,this));
	m_AddItem = MenuItemSprite::create(add,add,add,  CC_CALLBACK_1(CannonLayer::switchCannon,this));
	CCMenu* menu = CCMenu::create(m_SubItem, m_AddItem, nullptr);
	menu->alignItemsHorizontallyWithPadding(77);

	if(GameScene::cGameType == 1)
	{
		if(GameScene::cSelfPos == 0 )
		{
			menu->setPosition(Point(robotPos1, m_SubItem->getContentSize().height*0.5)); 
		}
		else if(GameScene::cSelfPos == 1)
		{
			menu->setPosition(Point(robotPos2, m_SubItem->getContentSize().height*0.5)); 			
		}
		
	}
	else
	{
		menu->setPosition(Point(winSize.width*0.5, m_SubItem->getContentSize().height*0.5)); 
	}
	
	this->addChild(menu,100);  

	if(GameScene::cGameType == 1)
	{
		
		if(GameScene::cSelfPos == 0)
		{
			menuPointBegin = Point(robotPos1,35);
			menuPoint[0] = Point(robotPos1-100,170);
			menuPoint[1] = Point(robotPos1,170);
			menuPoint[2] = Point(robotPos1+100,170);
		}
		else if(GameScene::cSelfPos ==1)
		{
			menuPointBegin = Point(robotPos2,35);
			menuPoint[0] = Point(robotPos2-100,170);
			menuPoint[1] = Point(robotPos2,170);
			menuPoint[2] = Point(robotPos2+100,170);
		}
		
	}
	else
	{
		menuPointBegin = Point(winSize.width*0.5f,35);
		menuPoint[0] = Point(winSize.width*0.5f-100,170);
		menuPoint[1] = Point(winSize.width*0.5f,170);
		menuPoint[2] = Point(winSize.width*0.5f+100,170);
	}	
	auto menuspr1 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("min.png"),Sprite::createWithSpriteFrameName("min.png"), CC_CALLBACK_1(CannonLayer::menuMin,this)); 
	m_MinItemmenu= Menu::create(menuspr1, nullptr); 

	
	m_MinItemmenu->setPosition(menuPoint[0]);  
	m_MinItemmenu->setVisible(false);
	//m_MinItem->setScale(0.5f);
	this->addChild(m_MinItemmenu, 100); 

	auto menuspr2 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("max.png"),Sprite::createWithSpriteFrameName("max.png"), CC_CALLBACK_1(CannonLayer::menuMax,this)); 
	m_MaxItemmenu= Menu::create(menuspr2, nullptr); 
	
	m_MaxItemmenu->setPosition(menuPoint[1]);  
	m_MaxItemmenu->setVisible(false);
	this->addChild(m_MaxItemmenu, 100); 
	//m_MaxItem->setScale(0.5f);

	auto menuspr3 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("jiesuo.png"),Sprite::createWithSpriteFrameName("jiesuo.png"), CC_CALLBACK_1(CannonLayer::menuJieSuo,this)); 
	m_JieSuomenu= Menu::create(menuspr3, nullptr); 
	
	m_JieSuomenu->setPosition(menuPoint[2]);  
	m_JieSuomenu->setVisible(false);
	this->addChild(m_JieSuomenu, 100); 
	//m_JieSuo->setScale(0.5f);

	if(GameScene::cGameType == 1)
	{
		if(GameScene::cSelfPos == 0)
		{
			menuPointTwo[0]  = Point(robotPos1-65,170);
			menuPointTwo[1]  = Point(robotPos1+65,170);
		}
		else if(GameScene::cSelfPos == 1)
		{
			menuPointTwo[0]  = Point(robotPos2-65,170);
			menuPointTwo[1]  = Point(robotPos2+65,170);
		} 
	}
	else
	{
		menuPointTwo[0]  = Point(winSize.width*0.50-65,170);
		menuPointTwo[1]  = Point(winSize.width*0.50+65,170);
	}
	
	m_MinItem = Sprite::createWithSpriteFrameName("min.png");
	m_MaxItem = Sprite::createWithSpriteFrameName("max.png");
	m_JieSuo = Sprite::createWithSpriteFrameName("jiesuo.png");
	 
	m_MinItem->setPosition(menuPointBegin );
	m_MinItem->setScale(0.1f);
	m_MaxItem->setPosition(menuPointBegin );
	m_MaxItem->setScale(0.1f); 
	m_JieSuo->setPosition(menuPointBegin ); 
	m_JieSuo->setScale(0.1f);
	m_MinItem->setVisible(false);
	m_MaxItem->setVisible(false);
	m_JieSuo->setVisible(false);
	this->addChild(m_MinItem,100);
	this->addChild(m_MaxItem,100);
	this->addChild(m_JieSuo,100);

	bFirstChoose = true;  
	angle = 0;

	if(GameScene::cGameType == 1)
	{ 	
		if(GameScene::cSelfPos == 0)
		{
			SelfPaoPos = Vec2(robotPos1,0);
		}
		else
		{
			SelfPaoPos = Vec2(robotPos2,0);
		}

		
	}
	else
	{
		
		SelfPaoPos = Vec2(winSize.width*0.5f,0);
	}
	  
	 
	 


	

	//int adf=  GameHallLayer::sceneLowPao;
	//cNowMaxPao = GameHallLayer::sceneHighPao - 1;
	//cRobotType[i] = CCRANDOM_0_1()*5;
	//_type = CCRANDOM_0_1()*5;
//	int iTempSelfMoney = GameBegin::getFileData("jywer.txt")
	for(int i =0; i<4; i++)
	{
		RobotMoney[i] = 0;
		m_CannonRobot[i] = NULL;
		bFanWeiRobotShoot[i] = false;
		bJiGuangRobotShoot[i] = false;
		bVipShoot[i] = false;
        
		if(GameScene::bRobotPos[i] == true)
		{ 
			//金币
            if(GameHallLayer::RoomType == 89)
            {
                //int iRobotBase[20] = {1,2,5,10,20,50,80,100,200,500,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};
           
                RobotMoney[i] = 300+CCRANDOM_0_1()*700;
                if(CCRANDOM_0_1()* 100  <50)
                cRobotType[i] = 1;
                else
                 cRobotType[i] = 2;
                _type = 1;
                
            }
			if(GameHallLayer::RoomType == 90)
			{    //                     0 1 2 3  4  5  6  7   8    9    10   11  12  13   14    15   16  17  18    19
				//int iRobotBase[20] = {1,2,5,10,20,50,80,100,200,500,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};
				char cTemp  = CCRANDOM_0_1()*100;
				if(cTemp < 2)
				{ 
					RobotMoney[i] = 40000+CCRANDOM_0_1()*10000;
				}
				else if(cTemp< 10)
				{
					RobotMoney[i] = 30000+CCRANDOM_0_1()*15000;
				}
				else if(cTemp <20)
				{
					RobotMoney[i] = 20000+CCRANDOM_0_1()*15000;
				}
				else if(cTemp <40)
				{
					RobotMoney[i] = 10000+CCRANDOM_0_1()*10000;
				}
				else if(cTemp <80)
				{
					RobotMoney[i] = 3000+CCRANDOM_0_1()*7000;
				}
				else 
				{
					RobotMoney[i] = 1000+CCRANDOM_0_1()*2000;
				}
                if(GameBegin::getFileData("jywer.txt") > 5000)
                {
                    cRobotType[i] = 2+CCRANDOM_0_1()*5.99;
                }
                else
                {
                    cRobotType[i] = 3;
                }
                
				 	
				if(GameBegin::getFileData("jywer.txt") > 5000)
				{
					_type = 2+CCRANDOM_0_1()*4.99;
				}
				else
				{
					_type =3;
				}
			}
			else if(GameHallLayer::RoomType == 91)
			{
                 //                     0 1 2 3  4  5  6  7   8    9    10   11  12  13   14    15   16  17  18    19
                //int iRobotBase[20] = {1,2,5,10,20,50,80,100,200,500,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};
                
                
				char cTemp  = CCRANDOM_0_1()*100;
				if(cTemp < 2)
				{ 
					RobotMoney[i] = 180000+CCRANDOM_0_1()*20000;

					 
				}
				else if(cTemp< 10)
				{
					RobotMoney[i] = 150000+CCRANDOM_0_1()*30000;
					 
				}
				else if(cTemp <20)
				{
					RobotMoney[i] = 120000+CCRANDOM_0_1()*35000;
				}
				else if(cTemp <50)
				{
					RobotMoney[i] = 100000+CCRANDOM_0_1()*50000;
				}
				else if(cTemp <80)
				{
					RobotMoney[i] = 70000+CCRANDOM_0_1()*50000;
					 
				}
				else
				{
					RobotMoney[i] = 50000+CCRANDOM_0_1()*50000;
					 
				}

				cRobotType[i] = 7+CCRANDOM_0_1()*2.99;
				_type =8;


			}
			else if(GameHallLayer::RoomType == 92)
			{
                //                     0 1 2 3  4  5  6  7   8    9    10   11  12  13   14    15   16  17  18    19
                //int iRobotBase[20] = {1,2,5,10,20,50,80,100,200,500,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};
                
                char cTemp  = CCRANDOM_0_1()*100;
				
				if(cTemp <20)
				{
					RobotMoney[i] = 410000+CCRANDOM_0_1()*90000;
					 
				}
				else if(cTemp <50)
				{
					RobotMoney[i] = 320000+CCRANDOM_0_1()*90000;
					 
				}
				else if(cTemp <80)
				{
					RobotMoney[i] = 280000+CCRANDOM_0_1()*90000;
				 
				}
				else
				{
					RobotMoney[i] = 200000+CCRANDOM_0_1()*80000;
					 
				}


				cRobotType[i] = 9+CCRANDOM_0_1()*8.99;
				_type =12;

			}
			else if(GameHallLayer::RoomType == 93)
			{
                //                     0 1 2 3  4  5  6  7   8    9    10   11  12  13   14    15   16  17  18    19
                //int iRobotBase[20] = {1,2,5,10,20,50,80,100,200,500,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};
                

                char cTemp  = CCRANDOM_0_1()*100;
				if(cTemp < 2)
				{ 
					RobotMoney[i] = 3000000+CCRANDOM_0_1()*7000000; 
				}
				else if(cTemp< 7)
				{
					RobotMoney[i] = 1000000+CCRANDOM_0_1()*2000000; 
				}
				else if(cTemp <20)
				{
					RobotMoney[i] = 800000+CCRANDOM_0_1()*2000000;
				}
				else if(cTemp <50)
				{
					RobotMoney[i] = 700000+CCRANDOM_0_1()*1000000;
				}
				else if(cTemp <80)
				{
					RobotMoney[i] = 600000+CCRANDOM_0_1()*400000;
				}
				else
				{
					RobotMoney[i] = 500000+CCRANDOM_0_1()*300000;
				}
				cRobotType[i] = 10+CCRANDOM_0_1()*9.99;
				_type =12;

			}
			char cRobotMoney[20];				
			sprintf(cRobotMoney,"%d", RobotMoney[i]);
			GameCoinLabel[i]->setString(cRobotMoney);


			if(GameScene::cRobotIQ[i] == 1)
			{
				 
				char cRandomRobotFanWeiType = CCRANDOM_0_1()*50;
				if(cRandomRobotFanWeiType < 30)
				{
					cRobotTypeFanWei[i] = 0;
					cRobotTypeJiGuang[i] = 0;

				}
				else if(cRandomRobotFanWeiType <45)
				{
					cRobotTypeFanWei[i] = 1;
					cRobotTypeJiGuang[i] = 1;
				}
				else
				{
					cRobotTypeFanWei[i] = 2;
					cRobotTypeJiGuang[i] = 2;
				} 


			}
			else if(GameScene::cRobotIQ[i] == 2)
			{ 
				char cRandomRobotFanWeiType = CCRANDOM_0_1()*50;
				if(cRandomRobotFanWeiType < 5)
				{
					cRobotTypeFanWei[i] = 0;
					cRobotTypeJiGuang[i] = 0;

				}
				else if(cRandomRobotFanWeiType <15)
				{
					cRobotTypeFanWei[i] = 1;
					cRobotTypeJiGuang[i] = 1;
				}
				else if(cRandomRobotFanWeiType < 35)
				{
					cRobotTypeFanWei[i] = 2;
					cRobotTypeJiGuang[i] = 2;
				} 
				else if(cRandomRobotFanWeiType < 45)
				{
					cRobotTypeFanWei[i] = 3;
					cRobotTypeJiGuang[i] = 3;
				} 
				else 
				{
					cRobotTypeFanWei[i] = 4;
					cRobotTypeJiGuang[i] = 4;
				} 
			}
			else if(GameScene::cRobotIQ[i] == 3)
			{
			 
				char cRandomRobotFanWeiType = CCRANDOM_0_1()*50;
				if(cRandomRobotFanWeiType < 0)
				{
					cRobotTypeFanWei[i] = 0;
					cRobotTypeJiGuang[i] = 0;

				}
				else if(cRandomRobotFanWeiType <0)
				{
					cRobotTypeFanWei[i] = 1;
					cRobotTypeJiGuang[i] = 1;
				}
				else if(cRandomRobotFanWeiType <10)
				{
					cRobotTypeFanWei[i] = 2;
					cRobotTypeJiGuang[i] = 2;
				} 
				else if(cRandomRobotFanWeiType < 25)
				{
					cRobotTypeFanWei[i] = 3;
					cRobotTypeJiGuang[i] = 3;
				} 
				else 
				{
					cRobotTypeFanWei[i] = 4;
					cRobotTypeJiGuang[i] = 4;
				} 
			}
			m_CannonRobot[i] = Cannon::create(cRobotType[i],cBeiShu[cRobotType[i]],i); 
			if(i == 0 || i == 2)			
				m_CannonRobot[i]->setPosition(robotPos1,0);
			else
				m_CannonRobot[i]->setPosition(robotPos2,0);
			m_CannonRobot[i]->setRot(angle);
			this->addChild(m_CannonRobot[i],100);   	
		} 
	}
	 
	m_Cannon = Cannon::create(_type,cBeiShu[_type],0); 
	m_Cannon->setPosition(SelfPaoPos);
	m_Cannon->setRot(angle);
	this->addChild(m_Cannon,100);  

	int TempZuanShi = GameBegin::getFileData("jywopl.txt");
	int iTempTime = 0;

	float scaltTmp = 0.9;
	float anniu_with = visibleSize.width * 0.505;
	float anniu_hight = visibleSize.height * 0.93;
	float anniu_juli = visibleSize.width * 0.1;
	if(GameScene::cGameType != 1)
	{
		auto jiasuspr = Sprite::createWithSpriteFrameName("jiasu.png"); 
		auto jiasuitem = MenuItemSprite::create(jiasuspr,jiasuspr, jiasuspr,CC_CALLBACK_1(CannonLayer::menuJiasu,this)); 
		jiasuitem->setScale(scaltTmp);
		m_JiaSumenu = Menu::create(jiasuitem,nullptr); 
		this->addChild(m_JiaSumenu,100);
		m_JiaSumenu->setPosition(Point(anniu_with - anniu_juli * 2,anniu_hight));

		auto cd0 = Sprite::createWithSpriteFrameName("cd.png");
		bjiaSupt =ProgressTimer::create(cd0);  
		bjiaSupt->setScale(1.2);
		bjiaSupt->setPosition(Vec2(jiasuitem->getContentSize()/2)); 
		bjiaSupt->setReverseProgress(true);
		bjiaSupt->setPercentage(100);
		bjiaSupt->setVisible(false); 
		jiasuitem->addChild(bjiaSupt,100);
/*
		auto jiasufont = Sprite::createWithSpriteFrameName("jiasufont.png");
		jiasufont->setPosition(Point(jiasuitem->getContentSize().width*0.5,-10));
		jiasuitem->addChild(jiasufont,100);
*/
		CountJiaSu = Label::create();  
		CountJiaSu->setCharMap("fishdeadnum.png",18,28,'0'); 
		iTempTime = TempZuanShi/100; 
		if(LoadRes::bFirstJiaSu == true)
		{
			iTempTime++; 
		}
		memset(cTemp,0,sizeof(cTemp));
		sprintf(cTemp,"%d",iTempTime);  
		CountJiaSu->setString( cTemp);   
		CountJiaSu->setPosition(Vec2(jiasuitem->getContentSize()*0.8));
		jiasuitem->addChild(CountJiaSu,101); 

		bjiaSu = false; 
		m_fUpdateTimejiasu = 0;
		m_fTimejiasu = 0; 
		m_fjiaSucdnum = 150;
		cocos2d::log("wfwfpy000000000000");
 
		jiasu_Gs = Sprite::createWithSpriteFrameName("jineng_10.png"); 
		jiasu_Gs->setPosition(Vec2(jiasuspr->getContentSize().width*0.5,jiasuspr->getContentSize().height*0.5));
		jiasuspr->addChild(jiasu_Gs,101);


	}
	
	Sprite * cVipspr = Sprite::createWithSpriteFrameName("Vip_jineng1.png");
	VipPaoIitem = MenuItemSprite::create(cVipspr,cVipspr,cVipspr,CC_CALLBACK_1(CannonLayer::menuVipPao,this));   //ShowMatchOver  menuVipPao
	VipPaoIitem->setScale(scaltTmp);
	m_VipPaomenu = Menu::create(VipPaoIitem,nullptr);
	this->addChild(m_VipPaomenu,100);


	auto cd0= Sprite::createWithSpriteFrameName("cd.png");
	bVipPaopt = ProgressTimer::create(cd0);
	bVipPaopt->setScale(1.2);
	bVipPaopt->setPosition(Vec2(VipPaoIitem->getContentSize()/2));
	bVipPaopt->setReverseProgress(true);
	bVipPaopt->setPercentage(100);
	bVipPaopt->setVisible(false);
	VipPaoIitem->addChild(bVipPaopt,100);
	bVipPao = false;
	m_fTimeVipPao = (float)14*60/100;
	m_fUpdateTimeVipPao = 0;
	m_fVipPaoNum = 100;

	bVipPaoShoot = false;
	m_fTimeVipPaoShoot = 7*60/100;
	m_fUpdateTimeShootVipPao = 0;
	m_fVipPaoShootNum = 100;

	/*auto VipPaofont = Sprite::createWithSpriteFrameName("vipaofont1.png");
	VipPaofont->setPosition(Point(VipPaoIitem->getContentSize().width*0.5-7,-10)); 
	VipPaofont->setScale(0.8);
	VipPaoIitem->addChild(VipPaofont,101);*/

 
	CountVipPao = Label::create();  
	CountVipPao->setCharMap("fishdeadnum.png",18,28,'0'); 
	iTempTime = TempZuanShi/50;
	 
	memset(cTemp,0,sizeof(cTemp));
	sprintf(cTemp,"%d",iTempTime);  
	CountVipPao->setString( cTemp);   
	CountVipPao->setPosition(Vec2(VipPaoIitem->getContentSize()*0.8));
	VipPaoIitem->addChild(CountVipPao,101);  

	vippao_Gs = Sprite::createWithSpriteFrameName("jineng_10.png"); 
	vippao_Gs->setPosition(Vec2(cVipspr->getContentSize().width/2,cVipspr->getContentSize().height/2));
	cVipspr->addChild(vippao_Gs); 
	m_VipPaomenu->setPosition(Point(anniu_with + anniu_juli * 2,anniu_hight));
	m_VipPaomenu->setVisible(true);
	 
	if(GameScene::cGameType == 1)
	{
 
		CountVipPao->setPosition(Vec2(VipPaoIitem->getContentSize().width * 0.8 , VipPaoIitem->getContentSize().height * 0.2));
		CountVipPao->setScale(0.8);
		VipPaoIitem->setScale(0.7);
//		VipPaofont->setPosition(Point(VipPaoIitem->getContentSize().width*0.5-7,VipPaoIitem->getContentSize().height));
		if(GameScene::cSelfPos == 0)
		{
			m_VipPaomenu->setPosition(Point(robotPos1-180*0.833,108*0.833));		 
		}
		else if(GameScene::cSelfPos == 1)
		{ 
			m_VipPaomenu->setPosition(Point(robotPos2+180*0.833,108*0.833));
		}
	}  

	Sprite * cFanWeispr = Sprite::createWithSpriteFrameName("fanweiicon.png");
	 
	FanWeiitem = MenuItemSprite::create(cFanWeispr,cFanWeispr,cFanWeispr,CC_CALLBACK_1(CannonLayer::menuFanWei,this));
	FanWeiitem->setScale(scaltTmp);
	m_FanWeimenu = Menu::create(FanWeiitem,nullptr);
	this->addChild(m_FanWeimenu,100);
	
 
	auto cd1 = Sprite::createWithSpriteFrameName("cd.png");
	bFanWeipt = ProgressTimer::create(cd1);
	bFanWeipt->setScale(1.2);
	bFanWeipt->setPosition(Vec2(FanWeiitem->getContentSize()/2));
	bFanWeipt->setReverseProgress(true);
	bFanWeipt->setPercentage(100);
	bFanWeipt->setVisible(false);
	FanWeiitem->addChild(bFanWeipt,100);
	bFanWei = false;
	m_fTimeFanWei = (float)iFanWeicd[typeFanWei]*60/100;
	m_fUpdateTimeFanWei = 0;
	m_fFanWeiNum = 100;

	 
	bFanWeiShoot = false;
	m_fTimeFanWeiShoot = (float)iFanWeiShootcd[typeFanWei]*60/100;
	m_fUpdateTimeShootFanWei = 0;
	m_fFanWeiShootNum = 100;

	auto fanweifont = Sprite::createWithSpriteFrameName("fanweifont1.png"); 
	fanweifont->setPosition(Point(FanWeiitem->getContentSize().width*0.5-7,-10)); 
	FanWeiitem->addChild(fanweifont,101);

	char fanweilvTmp[20];
	sprintf(fanweilvTmp,"fanweilv_%d.png",typeFanWei+1);

	fanweifontLv = Sprite::createWithSpriteFrameName(fanweilvTmp);
 
	fanweifontLv->setPosition(Point(fanweifont->getContentSize().width,fanweifont->getContentSize().height/2));
	 
	fanweifont->addChild(fanweifontLv);

	CountFanWei = Label::create();  
	CountFanWei->setCharMap("fishdeadnum.png",18,28,'0'); CountFanWei = Label::create();  
	CountFanWei->setCharMap("fishdeadnum.png",18,28,'0'); 
	iTempTime = TempZuanShi/100;
	 
	if(LoadRes::bFirstFanWei == true)
	{
		iTempTime++;
	}
	memset(cTemp,0,sizeof(cTemp));
	sprintf(cTemp,"%d",iTempTime);  
	CountFanWei->setString( cTemp);   
	CountFanWei->setPosition(Vec2(FanWeiitem->getContentSize()*0.8));
	FanWeiitem->addChild(CountFanWei,101);  

	fanwei_Gs = Sprite::createWithSpriteFrameName("jineng_10.png"); 
	fanwei_Gs->setPosition(Vec2(cFanWeispr->getContentSize().width/2,cFanWeispr->getContentSize().height/2));
	cFanWeispr->addChild(fanwei_Gs);

	if(GameLv >=5)
	{

		m_FanWeimenu->setPosition(Point(anniu_with + anniu_juli ,anniu_hight));
		FanWeiitem->setVisible(true);
	}
	else
	{

		m_FanWeimenu->setPosition(Point(anniu_with + anniu_juli,winSize.height*0.43));
		FanWeiitem->setVisible(false);
	}
	if(GameScene::cGameType == 1)
	{
 
		CountFanWei->setPosition(Vec2(FanWeiitem->getContentSize().width * 0.8 , FanWeiitem->getContentSize().height * 0.2));
		CountFanWei->setScale(0.8);
		FanWeiitem->setScale(0.7);
		fanweifont->setPosition(Point(FanWeiitem->getContentSize().width*0.5-7,FanWeiitem->getContentSize().height)); 
		if(GameScene::cSelfPos == 0)
		{
			m_FanWeimenu->setPosition(Point(robotPos1-300*0.833,108*0.833));		 
		}
		else if(GameScene::cSelfPos == 1)
		{ 
			m_FanWeimenu->setPosition(Point(robotPos2+300*0.833,108*0.833));
		}
	}   
	
 
	Sprite * cJiGuangspr; 
	cJiGuangspr = Sprite::createWithSpriteFrameName("jiguangicon.png");

	JiGuangitem = MenuItemSprite::create(cJiGuangspr,cJiGuangspr,cJiGuangspr,CC_CALLBACK_1(CannonLayer::menuJiGuang,this));
	JiGuangitem->setScale(scaltTmp);
	m_JiGuangmenu = Menu::create(JiGuangitem,nullptr);
	this->addChild(m_JiGuangmenu,100);

	auto cd3= Sprite::createWithSpriteFrameName("cd.png");
	bJiGuangpt = ProgressTimer::create(cd3);
	bJiGuangpt->setScale(1.2);
	bJiGuangpt->setPosition(JiGuangitem->getContentSize()/2);
	bJiGuangpt->setReverseProgress(true);
	bJiGuangpt->setPercentage(100);
	bJiGuangpt->setVisible(false);
	JiGuangitem->addChild(bJiGuangpt,100); 
	bJiGuang = false;
	m_fTimeJiGuang = (float)iJiGuangcd[typeJiGuang]*60/100;
	m_fUpdateTimeJiGuang = 0;
	m_fJiGuangNum = 100; 
	 
	bJiGuangShoot = false;
	m_fTimeJiGuangShoot = (float)iJiGuangShootcd[typeJiGuang]*60/100;
	m_fUpdateTimeJiGuangShoot = 0;
	m_fJiGuangShootNum = 100;
	 

	auto jiguangfont = Sprite::createWithSpriteFrameName("jiguangfont1.png");
	jiguangfont->setPosition(Point(JiGuangitem->getContentSize().width*0.5-7,-10));
	JiGuangitem->addChild(jiguangfont,101);

	char jiguanglvTmp[20];
	sprintf(jiguanglvTmp,"jiguanglv_%d.png",typeJiGuang+1);

	jiguangfontLv = Sprite::createWithSpriteFrameName(jiguanglvTmp);
	jiguangfontLv->setPosition(Point(jiguangfont->getContentSize().width,jiguangfont->getContentSize().height/2));
	jiguangfont->addChild(jiguangfontLv);

	CountJiGuang = Label::create();  
	CountJiGuang->setCharMap("fishdeadnum.png",18,28,'0'); 
	iTempTime = TempZuanShi/100; 
	if(LoadRes::bFirstJiGuang == true)
	{
		iTempTime++; 
	}

	memset(cTemp,0,sizeof(cTemp));
	sprintf(cTemp,"%d",iTempTime);  
	CountJiGuang->setString( cTemp);   
	CountJiGuang->setPosition(Vec2(JiGuangitem->getContentSize()*0.8));
	JiGuangitem->addChild(CountJiGuang,101); 
 
	if(GameLv >= 2)
	{
		JiGuangitem->setVisible(true); 
		m_JiGuangmenu->setPosition(Point(anniu_with  ,anniu_hight));
	}
	else
	{
		JiGuangitem->setVisible(false); 
		m_JiGuangmenu->setPosition(Point(anniu_with  ,winSize.height*0.43));
	}
 
	if(GameScene::cGameType == 1)
	{
		for(int i=0; i< 4; i++)
		{
			bPoChan[i] = false;
			PoChanSpr[i] = Sprite::createWithSpriteFrameName("pochanfont.png");
			this->addChild(PoChanSpr[i]);
			PoChanSpr[i]->setVisible(false);
		}
		PoChanSpr[0]->setPosition(Vec2(robotPos1,150));
		PoChanSpr[1]->setPosition(Vec2(robotPos2,150));
		PoChanSpr[2]->setPosition(Vec2(robotPos1,winSize.height-150));
		PoChanSpr[3]->setPosition(Vec2(robotPos2,winSize.height-150));
		
		//CountJiGuang->setVisible(false);
		CountJiGuang->setPosition(Vec2(JiGuangitem->getContentSize().width * 0.8 , JiGuangitem->getContentSize().height * 0.2));
		CountJiGuang->setScale(0.8);
		JiGuangitem->setScale(0.7);
		jiguangfont->setPosition(Point(JiGuangitem->getContentSize().width*0.5-7,JiGuangitem->getContentSize().height));
		if(GameScene::cSelfPos == 0)
		{
			m_JiGuangmenu->setPosition(Point(robotPos1-240*0.833,108*0.833));

		}
		else if(GameScene::cSelfPos == 1)
		{ 
			m_JiGuangmenu->setPosition(Point(robotPos2+240*0.833,108*0.833));
		}
	} 
 

	jiguang_Gs = Sprite::createWithSpriteFrameName("jineng_10.png"); 
	jiguang_Gs->setPosition(Vec2(cJiGuangspr->getContentSize().width/2,cJiGuangspr->getContentSize().height/2));
	cJiGuangspr->addChild(jiguang_Gs);
	 

	bjiaSushoot = false; 
	m_frameTime = 0.08f;
	m_frameUpdate = 0;
	cShootNum = 0;
 

	if(GameScene::cGameType != 1)
	{

		auto dingpingspr = Sprite::createWithSpriteFrameName("dingping.png"); 
		auto dingpingitem = MenuItemSprite::create(dingpingspr,dingpingspr, dingpingspr,CC_CALLBACK_1(CannonLayer::menuDingping,this)); 
		dingpingitem->setScale(scaltTmp);
		m_Dingpingmenu = Menu::create(dingpingitem,nullptr);
		m_Dingpingmenu->setPosition(Point::ZERO);  
		this->addChild(m_Dingpingmenu,100);
		m_Dingpingmenu->setPosition(Point(anniu_with - anniu_juli  ,anniu_hight));


		bDingpingpt =ProgressTimer::create(Sprite::createWithSpriteFrameName("cd.png"));  
		bDingpingpt->setScale(1.2);
		bDingpingpt->setPosition(Vec2(dingpingitem->getContentSize()/2));
		bDingpingpt->setReverseProgress(true);
		bDingpingpt->setPercentage(100);
		bDingpingpt->setVisible(false); 
		dingpingitem->addChild(bDingpingpt,100);

	/*	auto dingpingfont = Sprite::createWithSpriteFrameName("dingpingfont.png");
		dingpingfont->setPosition(Vec2(dingpingitem->getContentSize().width*0.5,-10));
		dingpingitem->addChild(dingpingfont,101);
*/
		CountDingPing = Label::create();  
		CountDingPing->setCharMap("fishdeadnum.png",18,28,'0'); 
		iTempTime = TempZuanShi/50; 
		if(LoadRes::bFirtDingPing == true)
		{
			iTempTime++;

		}
		memset(cTemp,0,sizeof(cTemp));
		sprintf(cTemp,"%d",iTempTime);  
		CountDingPing->setString(cTemp);   
		CountDingPing->setPosition(Point(dingpingitem->getContentSize()*0.8));
		dingpingitem->addChild(CountDingPing,101); 

		dingping_Gs = Sprite::createWithSpriteFrameName("jineng_10.png"); 
		dingping_Gs->setPosition(Vec2(dingpingspr->getContentSize().width/2,dingpingspr->getContentSize().height/2));
		dingpingspr->addChild(dingping_Gs);
	} 
	
	jineng_time_cd = 0;
	schedule(schedule_selector(CannonLayer::updateJineng),1.0f); 
	 
	m_fUpdateTimeDingping = 0; 
	m_fDingpingnum = 150;  

	m_Weapon = Weapon::create(_type); 
	this->addChild(m_Weapon,99 );

	cocos2d::log("cannonlyaer  end init");
 
    schedule(schedule_selector(CannonLayer::updateCannonLayer),0.01f); 
	return true;  
} 

void CannonLayer::initRobot(int i,bool isSelf)
{
    iMoneyJiangchi = GameBegin::getFileData("jywer.txt");
	//圆圈
	auto RobotWfQuan = Sprite::createWithSpriteFrameName("manquan.png");
	RobotWfQuan->setScale(0.833);
	RobotWfQuan->setPosition(Vec2(robotPos1 - 307*0.85,visibleSize.height-38*0.833));
	this->addChild(RobotWfQuan,MENULAYER + 10);

	//vip
	auto Robot_vip = Sprite::createWithSpriteFrameName("vip_gj.png");
	Robot_vip->setAnchorPoint(Vec2(0.5,1));
	//Robot_vip->setScaleY(0.5);
	Robot_vip->setPosition(Vec2(RobotWfQuan->getContentSize().width/2,RobotWfQuan->getContentSize().height));
	RobotWfQuan->addChild(Robot_vip);

	if(!GameScene::bRobotVip[i])
	{
		Robot_vip->setVisible(false);
	}

	//头像 
	char cTouName[20];
	int TouId = 1;
	sprintf(cTouName,"tou%d.png",TouId );
	auto RobotWfTouXiang = Sprite::createWithSpriteFrameName(cTouName);		
	RobotWfTouXiang->setScale(68.0f/270.0f);
	RobotWfTouXiang->setPosition(Vec2(RobotWfQuan->getContentSize().width/2,RobotWfQuan->getContentSize().height/2));
	RobotWfQuan->addChild(RobotWfTouXiang,-1);

	//背景
	auto RobotWfBg = Sprite::createWithSpriteFrameName("bs_txfont.png");
	RobotWfBg->setAnchorPoint(Vec2(0,0.5));
	RobotWfBg->setPosition(Vec2(RobotWfQuan->getContentSize().width/2,RobotWfQuan->getContentSize().height/2));
	RobotWfQuan->addChild(RobotWfBg,-2); 

	


	
	
	
	GameCoinLabel[i] = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');

	GameCoinLabel[i]->setScale(0.4);
	GameCoinLabel[i]->setPosition(Vec2(98,27));				  
	RobotWfBg->addChild(GameCoinLabel[i]);




	//名称
	sprintf(cTouName,"robotNName%d",1);
	LabelTTF * RobotName = LabelTTF::create(GAME_DATA_STRING(cTouName), "minijianling.ttf", 18);
	RobotName->setPosition(Vec2(98,52));
	RobotWfBg->addChild(RobotName,10);  
	if(i == 2)
	{
		sprintf(cTouName,"tou%d.png",GameHallLayer::robot2[1]);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTouName);
		RobotWfTouXiang->setDisplayFrame(frame);
		
		
		sprintf(cTouName,"robotNName%d",GameHallLayer::robot2[2]);
		RobotName->setString(GAME_DATA_STRING(cTouName));
		return;
	}
	if(i == 3)
	{
		RobotWfQuan->setPosition(Vec2(robotPos2 + 307*0.85,visibleSize.height-38*0.833));
		RobotWfBg->setAnchorPoint(Vec2(1,0.5));
		RobotName->setPosition(Vec2(79,52));
		GameCoinLabel[i]->setPosition(Vec2(79,27));	
		RobotWfBg->setFlippedX(true);
		
		sprintf(cTouName,"tou%d.png",GameHallLayer::robot3[1]);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTouName);
		RobotWfTouXiang->setDisplayFrame(frame);
		RobotWfTouXiang->setFlipX(true);

		sprintf(cTouName,"robotNName%d",GameHallLayer::robot3[2]);
		RobotName->setString(GAME_DATA_STRING(cTouName));

		return;
	}
	if(i == 1)
	{
		RobotWfQuan->setPosition(Vec2(robotPos2 + 307*0.85,38*0.833));
		RobotWfBg->setAnchorPoint(Vec2(1,0.5));
		RobotName->setPosition(Vec2(79,52));
		GameCoinLabel[i]->setPosition(Vec2(79,27));	
		RobotWfBg->setFlippedX(true);

		sprintf(cTouName,"tou%d.png",GameHallLayer::robot1[1]);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTouName);
		RobotWfTouXiang->setDisplayFrame(frame);
		RobotWfTouXiang->setFlipX(true);

		sprintf(cTouName,"robotNName%d",GameHallLayer::robot1[2]);
		RobotName->setString(GAME_DATA_STRING(cTouName));
	}
	if(i == 0)
	{
		RobotWfQuan->setPosition(Vec2(robotPos1 - 307*0.85,38*0.833));

		sprintf(cTouName,"tou%d.png",GameHallLayer::robot1[1]);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTouName);
		RobotWfTouXiang->setDisplayFrame(frame);

		sprintf(cTouName,"robotNName%d",GameHallLayer::robot1[2]);
		RobotName->setString(GAME_DATA_STRING(cTouName));
 
	}
	if(isSelf)
	{
		if(UserDefault::getInstance()->getIntegerForKey("player_vip") == 1)
		{
			Robot_vip->setVisible(true);
		}

		GameCoinLabel[i]->setVisible(false);
		GameCoinLabel[4] = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
		sprintf(cTouName,"%d",GameBegin::getFileData("jywer.txt"));
		GameCoinLabel[4]->setString(cTouName);
		GameCoinLabel[4]->setScale(0.4);
		if(i==0)
		{
			GameCoinLabel[4]->setPosition(Vec2(98,27));	
		}
		else
		{
			GameCoinLabel[4]->setPosition(Vec2(79,27));	
			RobotName->setPosition(Vec2(79,52));
		}
		
		RobotWfBg->addChild(GameCoinLabel[4]);

		sprintf(cTouName,"tou%d.png",UserDefault::getInstance()->getIntegerForKey("player_touxiang"));
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTouName);
		RobotWfTouXiang->setDisplayFrame(frame);

		RobotName->setString(UserDefault::getInstance()->getStringForKey("player_name"));
	}
	
}

void CannonLayer::hall_shangcheng_func(Ref* pSender)
{
	GameBegin::buttonSound();

	auto scene = Shop::create(2);
	this->getParent()->addChild(scene,10000);
} 


void CannonLayer::updateJineng(float dt)
{
	if(GameScene::cGameType != 1)
	{	
		jineng_time_cd++;
		if(jineng_time_cd == 4)
		{
			jiasu_Gs->stopAllActions();
			jiasu_Gs->setVisible(true);
			auto jiasu_G = AnimationCache::getInstance()->getAnimation("jineng_g");
			auto jiasu_Ga = Animate::create(jiasu_G);
			jiasu_Gs->runAction(jiasu_Ga);

		}else if(jineng_time_cd ==8)
		{

			dingping_Gs->stopAllActions();
			auto dingping_G = AnimationCache::getInstance()->getAnimation("jineng_g");
			auto dingping_Ga =  Animate::create(dingping_G);
			dingping_Gs->runAction(dingping_Ga);

		}else if(jineng_time_cd == 12)
		{
			jiguang_Gs->stopAllActions();
			auto jiguang_G = AnimationCache::getInstance()->getAnimation("jineng_g");
			auto jiguang_Ga =  Animate::create(jiguang_G);
			jiguang_Gs->runAction(jiguang_Ga);

		}else if(jineng_time_cd == 16)
		{
			fanwei_Gs->stopAllActions();
			auto fanwei_G = AnimationCache::getInstance()->getAnimation("jineng_g");
			auto fanwei_Ga =  Animate::create(fanwei_G);
			fanwei_Gs->runAction(fanwei_Ga);
 
		} 
		else if(jineng_time_cd == 20)
		{
			vippao_Gs->stopAllActions();
			auto fanwei_G = AnimationCache::getInstance()->getAnimation("jineng_g");
			auto fanwei_Ga =  Animate::create(fanwei_G);
			vippao_Gs->runAction(fanwei_Ga);

			jineng_time_cd = 0;

		} 
	}
}


void CannonLayer::updateDapao()
{
	char fanweilvTmp[20];
	sprintf(fanweilvTmp,"fanweilv_%d.png",typeFanWei+1);

	SpriteFrame * fanweiLvIcon = SpriteFrameCache::getInstance()->getSpriteFrameByName(fanweilvTmp);
	fanweifontLv->setSpriteFrame(fanweiLvIcon);

	char jiguanglvTmp[20];
	sprintf(jiguanglvTmp,"jiguanglv_%d.png",typeJiGuang+1);

	SpriteFrame * jiguangLvIcon = SpriteFrameCache::getInstance()->getSpriteFrameByName(jiguanglvTmp);
	jiguangfontLv->setSpriteFrame(jiguangLvIcon);
}
 
void CannonLayer::menuDingping(Ref* pSender)
{
	 
	GameBegin::buttonSound();
	if(LoadRes::bFirtDingPing == true)
	{
		LoadRes::bFirtDingPing = false; 
		UserDefault::getInstance()->setBoolForKey("firstdingping",true);
	/*	auto tishi = TiShi::create(3,GAME_DATA_STRING("dingpinone"),GAME_DATA_STRING("dingpintwo"),3,0);
		tishi->setPosition(Point(winSize.width*0.34,winSize.height*0.84)); 
		this->addChild(tishi,120);  
*/


		CannonLayer::GameCoinZuanshi(0);
		FishLayer::bDingping = true;
		m_Dingpingmenu->setEnabled(false);
		m_fUpdateTimeDingping = 0;

		bDingpingpt->setVisible(true);
	}
	else if(GameBegin::getFileData("jywopl.txt") >=50	)
	{

	/*	auto tishi = TiShi::create(3,GAME_DATA_STRING("dingpinone"),GAME_DATA_STRING("dingpintwo"),3,0);
		tishi->setPosition(Point(winSize.width*0.34,winSize.height*0.84)); 
		this->addChild(tishi,120);   
*/
		CannonLayer::GameCoinZuanshi(-50);
		FishLayer::bDingping = true;
		m_Dingpingmenu->setEnabled(false);
		m_fUpdateTimeDingping = 0;
		 
		bDingpingpt->setVisible(true);
	}
	else
	{
		 bShowLiBao =  true;
		//wftishikuang
	}
  
}
 
void CannonLayer::menuJiasu(Ref* pSender) 
{
		GameBegin::buttonSound();
	if(LoadRes::bFirstJiaSu == true)
	{
		LoadRes::bFirstJiaSu = false; 
		UserDefault::getInstance()->setBoolForKey("firstjiasu",true);
		/*auto tishi = TiShi::create(3,GAME_DATA_STRING("jiasuone"),GAME_DATA_STRING("jiasutwo"),3,0);
		tishi->setPosition(Point(winSize.width*0.24,winSize.height*0.84)); 
		tishi->setAnchorPoint(Point(1,1));
		this->addChild(tishi,120);  */
		GameCoinZuanshi(0); 
		bjiaSu = true;
		m_JiaSumenu->setEnabled(false);
		m_fUpdateTimejiasu = 0;
		m_fTimejiasu = 0.15;
		bjiaSupt->setVisible(true); 

	}
	else if(GameBegin::getFileData("jywopl.txt") >= 100) 
	{
		 
	/*	auto tishi = TiShi::create(3,GAME_DATA_STRING("jiasuone"),GAME_DATA_STRING("jiasutwo"),3,0);
		tishi->setAnchorPoint(Point(1,1));
		tishi->setPosition(Point(winSize.width*0.24,winSize.height*0.84)); 
		this->addChild(tishi,120);   */

		GameCoinZuanshi(-100); 
		bjiaSu = true;
		m_JiaSumenu->setEnabled(false);
		m_fUpdateTimejiasu = 0;
		m_fTimejiasu = 0.15;
		bjiaSupt->setVisible(true); 
	}
	else
	{
		 bShowLiBao =  true;

		//wftishikuang
	} 
	 
}

void CannonLayer::menuFanWei(Ref* pSender)
{
	GameBegin::buttonSound(); 

	if(bLock == true)
	{
		if(TishiJieSuo == NULL)
		{
		/*	string oo = GAME_DATA_STRING("jiesuopaoone");
			TishiJieSuo = TiShi::create(2,oo,GAME_DATA_STRING("jiesuopaotwo"),3,0,true); 
			TishiJieSuo->setPosition(Point(723,238)); 
			this->addChild(TishiJieSuo); */
		}
		else
		{ 
			TishiJieSuo->setVisible(true);
			TishiJieSuo->yuyue();
		} 
		return ;
	}

	if(UserDefault::getInstance()->getIntegerForKey("player_vip") != 1 && GameScene::cGameType == 1)
	{
		//jywzuobiao   此处是VIP没买点了VIP炮按钮
		auto gongxi = Gongxi::create(3,GAME_DATA_STRING("bushi_vip"));
		gongxi->setPosition(Point::ZERO);
		this->addChild(gongxi,MENULAYER + 1000,999);

		auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png" );
		auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_1(CannonLayer::baoming_vip,this));
		auto btnMenu = Menu::create(quedingItem,nullptr);
		btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
		gongxi->getChildByTag(1)->addChild(btnMenu,100);

		return;
	}
	 
	if(LoadRes::bFirstFanWei == true)
	{ 
		if(xinshoutimefanwei >= 200)
		{ 
			 
            xinshoutimefanwei = 250;
			this->removeChild(zzLayer,true);
			typeFanWei = 4;
			bxinShouFanWei = true;
			m_fTimeFanWeiShoot = (float)iJiGuangShootcd[typeFanWei]*60/100;

			FanWeiitem->stopAllActions();
			for(int i=1; i< 6; i++)
			{
				FanWeiitem->removeChildByTag(i);
			}  
		}
		else
		{ 
			LoadRes::bFirstFanWei = false; 
			UserDefault::getInstance()->setBoolForKey("firstfanwei",true);
		} 
		//ShowGuangAni(); 
		this->removeChild(m_Cannon,true);

		m_Cannon = Cannon::create(20+typeFanWei,cBeiShu[_type],0); 
		m_Cannon->setPosition(SelfPaoPos);
		m_Cannon->setRot(angle);
		this->addChild(m_Cannon,100);  

		 
		bFanWei = true;
		bFanWeiShoot = true;
		m_FanWeimenu->setEnabled(false); 
		bFanWeipt->setVisible(true); 
		if(_type> cNowMaxPao)
		{ 
			MoveInTwo();
		}
		else
		{
			MoveInOne();
		}  
		m_SubItem->setVisible(false);
		m_AddItem->setVisible(false); 
		m_JiGuangmenu->setEnabled(false);
		m_VipPaomenu->setEnabled(false);


		bShowWuQiTiShi =false;
		iShowTiShiNum =0;
	}
	else if(GameBegin::getFileData("jywopl.txt") >= 100) 
	{
		//ShowGuangAni(); 
		this->removeChild(m_Cannon,true); 
		m_Cannon = Cannon::create(20+typeFanWei,cBeiShu[_type],0); 
		m_Cannon->setPosition(SelfPaoPos);
		m_Cannon->setRot(angle);
		this->addChild(m_Cannon,100);  

		GameCoinZuanshi(-100); 
		
		 
		bFanWei = true;
		bFanWeiShoot = true;
		m_FanWeimenu->setEnabled(false); 
		bFanWeipt->setVisible(true); 

		if(_type> cNowMaxPao)
		{ 
			MoveInTwo();
		}
		else
		{
			MoveInOne();
		} 

		m_SubItem->setVisible(false);
		m_AddItem->setVisible(false); 
		m_JiGuangmenu->setEnabled(false);
		m_VipPaomenu->setEnabled(false);


		bShowWuQiTiShi =false;
		iShowTiShiNum =0;

	}
	else
	{
		bShowLiBao =  true;
	}
		
}



void CannonLayer::menuVipPao(Ref* pSender)
{
	GameBegin::buttonSound(); 

	if(bLock == true)
	{
		if(TishiJieSuo == NULL)
		{
		/*	string oo = GAME_DATA_STRING("jiesuopaoone");
			TishiJieSuo = TiShi::create(2,oo,GAME_DATA_STRING("jiesuopaotwo"),3,0,true); 
			TishiJieSuo->setPosition(Point(723,238)); 
			this->addChild(TishiJieSuo); */
		}
		else
		{ 
			TishiJieSuo->setVisible(true);
			TishiJieSuo->yuyue();
		} 
		return ;
	}
	if(UserDefault::getInstance()->getIntegerForKey("player_vip") != 1)
	{
		//jywzuobiao   此处是VIP没买点了VIP炮按钮
		auto gongxi = Gongxi::create(3,GAME_DATA_STRING("bushi_vip"));
		gongxi->setPosition(Point::ZERO);
		this->addChild(gongxi,MENULAYER + 1000,999);

		auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png" );
		auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_1(CannonLayer::baoming_vip,this));
		auto btnMenu = Menu::create(quedingItem,nullptr);
		btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
		gongxi->getChildByTag(1)->addChild(btnMenu,100);
	}
	else
	{
		if(GameBegin::getFileData("jywopl.txt") >= 50) 
		{
			//ShowGuangAni(); 
			this->removeChild(m_Cannon,true); 
			m_Cannon = Cannon::create(30,cBeiShu[_type],0); 
			m_Cannon->setPosition(SelfPaoPos);
			m_Cannon->setRot(angle);
			this->addChild(m_Cannon,100);  

			GameCoinZuanshi(-50); 


			bVipPao = true;
			bVipPaoShoot = true;
			m_VipPaomenu->setEnabled(false); 
			bVipPaopt->setVisible(true); 

			if(_type> cNowMaxPao)
			{ 
				MoveInTwo();
			}
			else
			{
				MoveInOne();
			} 

			m_SubItem->setVisible(false);
			m_AddItem->setVisible(false); 
			m_JiGuangmenu->setEnabled(false);
			m_FanWeimenu->setEnabled(false);

			bShowWuQiTiShi =false;
			iShowTiShiNum =0;

		}
		else
		{
			bShowLiBao =  true;
		} 
	}


}

void CannonLayer::baoming_vip(Ref * pSender)
{
	this->removeChildByTag(999);
 
    auto shop = Shop::create(5);
    this->getParent()->addChild(shop,10000);
}

void CannonLayer::menuJiGuang(Ref* pSender)
{ 

	GameBegin::buttonSound();
	if(bLock == true)
	{
		if(TishiJieSuo == NULL)
		{
		/*	string oo = GAME_DATA_STRING("jiesuopaoone");
			TishiJieSuo = TiShi::create(2,oo,GAME_DATA_STRING("jiesuopaotwo"),3,0,true); 
			TishiJieSuo->setPosition(Point(723,238)); 
			this->addChild(TishiJieSuo); */
		}
		else
		{ 
			TishiJieSuo->setVisible(true);
			TishiJieSuo->yuyue();
		} 
		return ;
	}

	if(UserDefault::getInstance()->getIntegerForKey("player_vip") != 1 && GameScene::cGameType == 1)
	{
		//jywzuobiao   此处是VIP没买点了VIP炮按钮
		auto gongxi = Gongxi::create(3,GAME_DATA_STRING("bushi_vip"));
		gongxi->setPosition(Point::ZERO);
		this->addChild(gongxi,MENULAYER + 1000,999);

		auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png" );
		auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_1(CannonLayer::baoming_vip,this));
		auto btnMenu = Menu::create(quedingItem,nullptr);
		btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
		gongxi->getChildByTag(1)->addChild(btnMenu,100);

		return;
	}

		if(LoadRes::bFirstJiGuang == true)
		{ 
			if(xinshoutimejiguang >= 200)
			{ 
                xinshoutimejiguang = 250;
				this->removeChild(zzLayer,true);
				typeJiGuang = 4;

				m_fTimeJiGuangShoot = (float)iJiGuangShootcd[typeJiGuang]*60/100;

				JiGuangitem->stopAllActions();
				for(int i=1; i< 6; i++)
				{
					JiGuangitem->removeChildByTag(i);
				}  

				/*char cTempnonum[10]; 
				cJiGuangNum = iJiGuangShootcd[typeJiGuang];
				cNoNum  =  100/cJiGuangNum;
				sprintf(cTempnonum,"%d",cJiGuangNum);
				naocannum->setString(cTempnonum);
				cJiGuangNum--;*/


			}
			else
			{ 
				LoadRes::bFirstJiGuang = false; 
				UserDefault::getInstance()->setBoolForKey("firstjiguang",true);
			}



			//ShowGuangAni();
			GameCoinZuanshi(0); 
			this->removeChild(m_Cannon,true);

			m_Cannon = Cannon::create(25+typeJiGuang,cBeiShu[_type],0); 
			m_Cannon->setPosition(SelfPaoPos);
			m_Cannon->setRot(angle);
			this->addChild(m_Cannon,100);  

			 
			 
			bJiGuang = true;
			bJiGuangShoot = true;
			m_JiGuangmenu->setEnabled(false);
			m_VipPaomenu->setEnabled(false);
			bJiGuangpt->setVisible(true);
			 
			if(_type> cNowMaxPao)
			{ 
				MoveInTwo();
			}
			else
			{
				MoveInOne();
			} 

			m_SubItem->setVisible(false);
			m_AddItem->setVisible(false);
			m_FanWeimenu->setEnabled(false);	
			bShowWuQiTiShi =false;
			iShowTiShiNum =0;
		}
		else if(GameBegin::getFileData("jywopl.txt") >= 100) 
		{
			//ShowGuangAni();

			this->removeChild(m_Cannon,true);
			GameCoinZuanshi(-100); 
			m_Cannon = Cannon::create(25+typeJiGuang,cBeiShu[_type],0); 
			m_Cannon->setPosition(SelfPaoPos);
			m_Cannon->setRot(angle);
			this->addChild(m_Cannon,100);  


			 
			bJiGuang = true;
			bJiGuangShoot = true;
			m_JiGuangmenu->setEnabled(false); 
			bJiGuangpt->setVisible(true);

			 
			if(_type> cNowMaxPao)
			{ 
				MoveInTwo();
			}
			else
			{
				MoveInOne();
			} 

			m_SubItem->setVisible(false);
			m_AddItem->setVisible(false);
			m_FanWeimenu->setEnabled(false);
			m_VipPaomenu->setEnabled(false);
			bShowWuQiTiShi =false;
			iShowTiShiNum =0;
		}
		else
		{
			bShowLiBao =  true;
		}
		
}

void CannonLayer::menuMax(Ref* pSender)
{  
	 

	GameBegin::buttonSound();


	if(_type> cNowMaxPao)
	{ 
		MoveInTwo();
	}
	else
	{
		MoveInOne();
	} 
	_type = cNowMaxPao;
	bLock = false;
	bFirstChoose = true; 
	this->removeChild(m_Cannon,true); 
	m_Cannon = Cannon::create(_type,cBeiShu[_type],0); 
	m_Cannon->setPosition(SelfPaoPos);
	m_Cannon->setRot(angle);
	this->addChild(m_Cannon,100); 
	 
}

void CannonLayer::menuMin(Ref* pSender)
{  
	if(_type> cNowMaxPao)
	{
		 MoveInTwo();
	}
	else
	{
		MoveInOne();
	} 
	_type = GameHallLayer::sceneLowPao -1 ;
	bFirstChoose = true; 
	this->removeChild(m_Cannon,true); 
	m_Cannon = Cannon::create(_type,cBeiShu[_type],0); 
	m_Cannon->setPosition(SelfPaoPos);
	m_Cannon->setRot(angle);
	this->addChild(m_Cannon,100); 
	bLock = false; 
}

void CannonLayer::menuJieSuo(Ref* pSender)
{  

	GameBegin::buttonSound();

	if(_type > cNowMaxPao)
	{ 
		MoveInTwo();
	}
	else
	{
		MoveInOne();
	} 
	bFirstChoose =true;
	if(GameBegin::getFileData("gameMaxPao.txt") == 20)
	{
		auto gongxi = Gongxi::create(1,GAME_DATA_STRING("shop_buy_libao_1"));
		gongxi->setPosition(Point::ZERO);
		this->addChild(gongxi);
	}
	else
	{
		auto layer = this->getParent();
		auto scene = UnLockLayer::create(2);
		scene->setPosition(Point::ZERO);
		layer->addChild(scene,MENULAYER+101);
	}
}

 void CannonLayer::ToMax()
{
	 

	_type = cNowMaxPao;
	/*bLock = false;
	bFirstChoose = true; */
	this->removeChild(m_Cannon,true); 
	m_Cannon = Cannon::create(_type,cBeiShu[_type],0); 
	m_Cannon->setPosition(SelfPaoPos);
	m_Cannon->setRot(angle);
	this->addChild(m_Cannon,100); 
}


 void CannonLayer::callMoveOverFanWei()
 {
	 m_FanWeimenu->setEnabled(true); 
	 Animation* fishAnimation = AnimationCache::getInstance()->getAnimation("hand"); 
	 Animate*  fishAnimate = Animate::create(fishAnimation);
	 auto hand = Sprite::create();  

	 FanWeiitem->addChild(hand);
	 hand->setTag(4);
	 hand->runAction(RepeatForever::create(fishAnimate)); 
	 hand->setPosition(Vec2(75,15));

     return;
	 auto sprxin = Sprite::createWithSpriteFrameName("mianfeifont.png");
	 sprxin->setPosition(Vec2(30,-90));
	 sprxin->setTag(5);
	 FanWeiitem->addChild(sprxin);
 }

 void CannonLayer::callMoveOverJiGuang()
 {

	 m_JiGuangmenu->setEnabled(true); 
	 Animation* fishAnimation = AnimationCache::getInstance()->getAnimation("hand"); 
	 Animate*  fishAnimate = Animate::create(fishAnimation);
	 auto hand = Sprite::create();  

	 JiGuangitem->addChild(hand);
	 hand->setTag(4);
	 hand->runAction(RepeatForever::create(fishAnimate)); 
	 hand->setPosition(Vec2(75,15));

     return;
	 auto sprxin = Sprite::createWithSpriteFrameName("mianfeifont.png");
	 sprxin->setPosition(Vec2(30,-90));
	 sprxin->setTag(5);
	 JiGuangitem->addChild(sprxin);
 }
void CannonLayer::updateCannonLayer(float delta)
{ 
	m_Weapon->updateWeapon(delta);
 
    if(zuanpanover == 1)
    {
        this->unscheduleAllSelectors();
        zuanpanover = 0;
        Match_exit();
        return;
        
    }
    
    
	if(bShowWuQiTiShi == true && GameScene::cGameType == 0)
	{
		iShowTiShiNum++;
		if(iShowTiShiNum == 600)
		{
		/*	iShowTiShiNum = 0;
			char cTemp =  CCRANDOM_0_1()*100;
			if(cTemp < 33)
			{ 
				auto tishi = TiShi::create(3,GAME_DATA_STRING("fanweiok1"),GAME_DATA_STRING("fanweiok2"),8,0); 
				tishi->setPosition(Point(winSize.width*0.54,winSize.height*0.84)); 
				this->addChild(tishi,120);  
			}
			else if(cTemp < 66)
			{
				auto tishi = TiShi::create(3,GAME_DATA_STRING("jiguangok1"),GAME_DATA_STRING("jiguangok2"),8,0); 
				tishi->setPosition(Point(winSize.width*0.44,winSize.height*0.84)); 
				this->addChild(tishi,120);  
			}
			else  
			{
				auto tishi = TiShi::create(3,GAME_DATA_STRING("vippaook1"),GAME_DATA_STRING("vippaook2"),8,0);  
				tishi->setPosition(Point(winSize.width*0.44,winSize.height*0.84)); 
				this->addChild(tishi,120);  
			} */
		} 
	} 

	if(bFanweiyindao)
	{
		xinshoutimefanwei++;
		if(xinshoutimefanwei  > 200)
		{   
			bFanweiyindao = false; 
			  
			zzLayer = LayerColor::create(ccc4(0,0,0,180),winSize.width,winSize.height);
			this->addChild(zzLayer);  


			m_FanWeimenu->setEnabled(false);
			auto jiguangtwo = Sprite::create("fanweitexiaotwo.png");
			jiguangtwo->setPosition(Vec2(FanWeiitem->getContentSize().width/2,FanWeiitem->getContentSize().height/2));
            jiguangtwo->setScale(1.0);
			FanWeiitem->addChild(jiguangtwo,-1,1);
			//jiguangtwo->setScale(0.5f);

			auto wfsc1 = ScaleTo::create(0.0,1.0);
			auto wfsc2 = ScaleTo::create(0.6,0.2f);
			FadeOut *ac14=CCFadeOut::create(1.0f);  
			CCFadeIn  *ac13=CCFadeIn::create(0.1f); 
			Sequence *seq=Sequence::create(wfsc1,ac13,wfsc2,ac14,NULL);  

			auto spawn=Spawn::create( wfsc1,wfsc2,NULL);     
			jiguangtwo->runAction(RepeatForever::create(seq)); 
			auto jiguangone = Sprite::createWithSpriteFrameName("fanweitexiaoone.png");
			jiguangone->setPosition(Vec2(FanWeiitem->getContentSize().width/2,FanWeiitem->getContentSize().height/2));
			FanWeiitem->addChild(jiguangone,-1,2);
			auto wfro1 = RotateBy::create(2.0f,500); 
			jiguangone->runAction(RepeatForever::create(wfro1));




			auto huoyan  = Sprite::createWithSpriteFrameName("yindaoquan.png");
			huoyan->setAnchorPoint(Vec2(0.16,0.35));
			huoyan->setScale(1.5f);
			huoyan->setPosition(Vec2(FanWeiitem->getContentSize().width/2,FanWeiitem->getContentSize().height/2));
			FanWeiitem->addChild(huoyan,-1,3);

			auto zhuanquan_hy = RotateBy::create(3.0f,-800); 
			huoyan->runAction(RepeatForever::create(zhuanquan_hy));  



			FanWeiitem->setVisible(true); 
			auto moveto = MoveTo::create(3.0f,Vec2( 0,winSize.height*0.5)); 
			FadeIn *wfac13=FadeIn::create(1.0f);  
			 
			auto call = CallFunc::create(CC_CALLBACK_0(CannonLayer::callMoveOverFanWei,this));
			auto scwf2 =  Sequence::create(wfac13,moveto,call,NULL);
			FanWeiitem->runAction(scwf2);
		}
	}
	if(bJiGuangyindao)
	{
		xinshoutimejiguang++;
		if(xinshoutimejiguang  > 200)
		{ 
			bJiGuangyindao = false; 
			 

			zzLayer = LayerColor::create(ccc4(0,0,0,180),winSize.width,winSize.height);
			this->addChild(zzLayer);  

			 
			m_JiGuangmenu->setEnabled(false);
			auto jiguangtwo = Sprite::createWithSpriteFrameName("jiguangtexiaotwo.png");
			jiguangtwo->setPosition(Vec2(JiGuangitem->getContentSize().width/2,JiGuangitem->getContentSize().height/2));
			JiGuangitem->addChild(jiguangtwo,-1,1);
			//jiguangtwo->setScale(0.5f);

			auto wfsc1 = ScaleTo::create(0.0,1.0f);
			auto wfsc2 = ScaleTo::create(0.6,1.5f);
			FadeOut *ac14=CCFadeOut::create(1.0f);  
			CCFadeIn  *ac13=CCFadeIn::create(0.1f); 
			Sequence *seq=Sequence::create(wfsc1,ac13,wfsc2,ac14,NULL);  

			auto spawn=Spawn::create( wfsc1,wfsc2,NULL);     
			jiguangtwo->runAction(RepeatForever::create(seq)); 
			auto jiguangone = Sprite::createWithSpriteFrameName("jiguangtexiaoone.png");
			jiguangone->setPosition(Vec2(JiGuangitem->getContentSize().width/2,JiGuangitem->getContentSize().height/2));
			JiGuangitem->addChild(jiguangone,-1,2);
			auto wfro1 = RotateBy::create(2.0f,500); 
			jiguangone->runAction(RepeatForever::create(wfro1));




			auto huoyan  = Sprite::createWithSpriteFrameName("yindaoquan.png");
			huoyan->setAnchorPoint(Vec2(0.16,0.35));
			huoyan->setScale(1.5f);
			huoyan->setPosition(Vec2(JiGuangitem->getContentSize().width/2,JiGuangitem->getContentSize().height/2));
			JiGuangitem->addChild(huoyan,-1,3);

			auto zhuanquan_hy = RotateBy::create(3.0f,-800); 
			huoyan->runAction(RepeatForever::create(zhuanquan_hy));  

			
			 
			JiGuangitem->setVisible(true); 
			auto moveto = MoveTo::create(3.0f,Vec2( 0,winSize.height*0.5)); 
			FadeIn *wfac13=FadeIn::create(1.0f);  

			auto call = CallFunc::create(CC_CALLBACK_0(CannonLayer::callMoveOverJiGuang,this));
			auto scwf2 =  Sequence::create(wfac13,moveto,call,NULL);
			JiGuangitem->runAction(scwf2);
		}
	}
	if(bToMax == true)
	{
		bToMax = false; 
		bLock = false;
		ToMax();
	}

	if(bLvUp == true)
	{

		bLvUp = false;
		//弹出恭喜框

		auto lvup = LvUp::create(2,GameLv,iLvMoney,iLvZuan);
		lvup->setPosition(Point(0,0));
		this->addChild(lvup); 
	} 
	if(isToMaxFlag)
	{
		isToMaxFlag = false;
		//弹出恭喜框
		char tmpchar[300]; 
		char cTempName[20];
		sprintf(cTempName,"bljs_rate_%d",cNowMaxPao+1);
		int iTempBase =GAME_DATA_INT(cTempName);   
		 
		auto lvup = LvUp::create(1,GameLv,iLvMoney,iTempBase);
		lvup->setPosition(Point(0,0));
		this->addChild(lvup); 

		ToMax();
		if(GameBegin::getFileData("gameMaxPao.txt") + 1 > GameHallLayer::sceneHighPao)
		{
			bShowJieSuoXiaoShi = true;
			bShowJieSuo = false; 
		}
		else
		{
			memset(cTempName,0,sizeof(cTempName));
			sprintf(cTempName,"bljs_dj_%d",GameBegin::getFileData("gameMaxPao.txt") + 1);
			int iNeedDengJi = GAME_DATA_INT(cTempName);

			memset(cTempName,0,sizeof(cTempName));
			sprintf(cTempName,"bljs_zuanshi_%d",GameBegin::getFileData("gameMaxPao.txt") + 1);
			int iNeedZuanShi  = GAME_DATA_INT(cTempName);

			if(iNeedDengJi > 0 && iNeedZuanShi> 0)
			{
				 
				if(GameBegin::getFileData("gamePlayerlv.txt") >= iNeedDengJi  &&  GameBegin::getFileData("jywopl.txt") >= iNeedZuanShi )
				{ 
					CannonLayer::bShowJieSuo = true;
				}
				else
				{
					bShowJieSuoXiaoShi = true;
					bShowJieSuo = false; 
				}
			}
		}  
	}


	if(bShowJieSuo == true)
	{ 
		bShowJieSuo = false;
		m_JieSuoKuang->stopAllActions();

		m_JieSuoKuang->setVisible(true);
		wordTTF->setVisible(true);

		wordTTF1->setVisible(true);
		dianjijiesuo->setVisible(true);
        
        mDiamondIcon->setVisible(true);
		
		char cTempName[50];
		sprintf(cTempName,"bljs_zuanshi_%d",cNowMaxPao + 2);
		int zuanshiTmp =GAME_DATA_INT(cTempName);  
		sprintf(cTempName,"%d",zuanshiTmp);
		wordTTF->setString(cTempName);  

		sprintf(cTempName,"bljs_rate_%d",cNowMaxPao + 2);
		zuanshiTmp =GAME_DATA_INT(cTempName);  
		sprintf(cTempName,GAME_DATA_STRING("jiesuokuang_ttf2"),zuanshiTmp); 
		wordTTF1->setString(cTempName);
 
		CCFadeIn *ac13=CCFadeIn::create(1.0f);  
		CCFadeOut *ac14=CCFadeOut::create(1.0f); 
		CCSequence *seq=CCSequence::create(ac14,ac13,NULL);  
		CCRepeatForever *repeatForver=CCRepeatForever::create(seq);

		m_JieSuoKuang->runAction(repeatForver); 
	}
	if(bShowJieSuoXiaoShi == true)
	{
		bShowJieSuoXiaoShi= false;
		char cTempName[20];
		sprintf(cTempName,"bljs_dj_%d",cNowMaxPao + 2);
		int iNeedDengJi = GAME_DATA_INT(cTempName);  

		memset(cTempName,0,sizeof(cTempName));
		sprintf(cTempName,"bljs_zuanshi_%d",cNowMaxPao + 2);
		int iNeedZuanShi  = GAME_DATA_INT(cTempName);


		if(iNeedDengJi > 0 && iNeedZuanShi> 0 && cNowMaxPao < GameHallLayer::sceneHighPao - 1)
		{
			if(GameBegin::getFileData("gamePlayerlv.txt") >= iNeedDengJi  && GameBegin::getFileData("jywopl.txt") >= iNeedZuanShi )
			{ 		 
				bShowJieSuo = true;
			}
			else
			{				
				m_JieSuoKuang->stopAllActions();
				m_JieSuoKuang->setVisible(false);
				wordTTF->setVisible(false); 

				wordTTF1->setVisible(false);
				dianjijiesuo->setVisible(false);
			}
		}
		else
		{ 
			m_JieSuoKuang->stopAllActions();
			m_JieSuoKuang->setVisible(false);	 
			wordTTF->setVisible(false);

			wordTTF1->setVisible(false);
			dianjijiesuo->setVisible(false);
		}
		
	}
	 

	if(bupdateJiesuo == true)
	{
		bupdateJiesuo = false;
		bLock = false;
		if(cNowMaxPao!=_type)
		{

			_type = cNowMaxPao;
			//ShowGuangAni(); 
			this->removeChild(m_Cannon,true);

			m_Cannon = Cannon::create(_type,cBeiShu[_type],0); 
			m_Cannon->setPosition(SelfPaoPos);
			m_Cannon->setRot(angle);
			this->addChild(m_Cannon,100);  	
		}
	}

	if(bpaoTeXiao == true)
	{
		this->m_fUpdateTime += delta;
		if(this->m_fUpdateTime >m_fTime )
		{  
			bpaoTeXiao = false;
			paoTexiaoSpr->setVisible(false);
		}  
	}



	if(FishLayer::bDingping == true)
	{
		this->m_fUpdateTimeDingping += delta;
		if(this->m_fUpdateTimeDingping >0.048f )
		{ 
			m_fUpdateTimeDingping = 0;
			m_fDingpingnum--;
			bDingpingpt->setPercentage(m_fDingpingnum);

			if(m_fDingpingnum == 0)
			{	
				m_fDingpingnum = 150;

				bDingpingpt->setVisible(false);
				bDingpingpt->setPercentage(100);
				m_Dingpingmenu->setEnabled(true);
				FishLayer::bDingping = false;
			}
		}
	} 



	if(bjiaSushoot == true )
	{
		m_frameUpdate+= delta;
		if(m_frameUpdate >m_frameTime)
		{
			m_frameUpdate = 0;
			cShootNum++;

			shootTo(ShootPos);

			if(cShootNum == 1)
			{
				bjiaSushoot = false;
				cShootNum = 0;
			} 
		}
	} 

	if(bjiaSu == true)
	{
		this->m_fUpdateTimejiasu += delta;
		if(this->m_fUpdateTimejiasu >0.058f )
		{ 
			m_fUpdateTimejiasu = 0;
			m_fjiaSucdnum--;
			bjiaSupt->setPercentage(m_fjiaSucdnum);

			if(m_fjiaSucdnum == 0)
			{	
				m_fjiaSucdnum = 150;
				bjiaSupt->setVisible(false);
				bjiaSupt->setPercentage(100);
				m_JiaSumenu->setEnabled(true);
				bjiaSu = false;
			}
		}
	} 


	
	if(bFanWeiShoot == true)
	{
		this->m_fUpdateTimeShootFanWei += 1;
		if(this->m_fUpdateTimeShootFanWei >m_fTimeFanWeiShoot )
		{ 
			m_fUpdateTimeShootFanWei = 0;
			m_fFanWeiShootNum--; 

			if(m_fFanWeiShootNum == 0)
			{	
				m_fFanWeiShootNum = 100; 
				bFanWeiShoot = false;
				 
				if(bJiGuang == false)
				{ 
					m_JiGuangmenu->setEnabled(true); 
				}  
				if(bVipPao == false)
				{
					m_VipPaomenu->setEnabled(true);
				}

				if(xinshoutimefanwei >= 200)
				{ 
					bxinShouFanWei = false;
					xinshoutimefanwei = 0;
					typeFanWei =   GameBegin::getFileData("typeFanWei")-1; 
				}
			/*	auto tishi = TiShi::create(3,GAME_DATA_STRING("shootwenzi1"),GAME_DATA_STRING("shootwenzi2"),8,0);
				tishi->setPosition(Point(winSize.width*0.54,winSize.height*0.84)); 
				this->addChild(tishi,120);  */


				m_SubItem->setVisible(true);
				m_AddItem->setVisible(true);

				if(bCanJieSuo == true)
				{
					bCanJieSuo = false;
					char cTempName[20];
					sprintf(cTempName,"bljs_dj_%d",GameBegin::getFileData("gameMaxPao.txt") + 1);
					int iNeedDengJi = GAME_DATA_INT(cTempName);

					memset(cTempName,0,sizeof(cTempName));
					sprintf(cTempName,"bljs_zuanshi_%d",GameBegin::getFileData("gameMaxPao.txt") + 1);
					int iNeedZuanShi  = GAME_DATA_INT(cTempName);

					if(iNeedDengJi > 0 && iNeedZuanShi> 0)
					{
						if(GameBegin::getFileData("gamePlayerlv.txt") >= iNeedDengJi  && GameBegin::getFileData("jywopl.txt") >= iNeedZuanShi )
						{ 
							int iTemp = CannonLayer::cNowMaxPao+1; 
							if(iTemp <  20)
							{ 
								CannonLayer::cNowMaxPao = GameBegin::getFileData("gameMaxPao.txt") ; 
								
								GameBegin::setFileData("gameMaxPao.txt",CannonLayer::cNowMaxPao+1); 
								char zuanshiTmp[20]; 
								GameCoinZuanshi(-iNeedZuanShi);
								isToMaxFlag = true;
								bLvUp = false;

							} 
							else
							{
								bShowJieSuoXiaoShi = true;
								bShowJieSuo = false;
								bLvUp = true;
							}
							// bShowJieSuo = true; 
						}
					}
					else
					{

						this->removeChild(m_Cannon,true);  
						m_Cannon = Cannon::create(_type,cBeiShu[_type],0); 
						m_Cannon->setPosition(SelfPaoPos);
						m_Cannon->setRot(angle);
						this->addChild(m_Cannon,100);  
					}
				}
				else
				{
					this->removeChild(m_Cannon,true);  
					m_Cannon = Cannon::create(_type,cBeiShu[_type],0); 
					m_Cannon->setPosition(SelfPaoPos);
					m_Cannon->setRot(angle);
					this->addChild(m_Cannon,100);  
				}
				 
			
			}
		}
	} 

	
	if(bFanWei == true)
	{
		this->m_fUpdateTimeFanWei += 1;
		if(this->m_fUpdateTimeFanWei >m_fTimeFanWei )
		{ 
			m_fUpdateTimeFanWei = 0;
			m_fFanWeiNum--;
			bFanWeipt->setPercentage(m_fFanWeiNum);

			if(m_fFanWeiNum == 0)
			{	

				/*auto tishi = TiShi::create(3,GAME_DATA_STRING("fanweiok1"),GAME_DATA_STRING("fanweiok2"),4,0);
				tishi->setPosition(Point(winSize.width*0.54,winSize.height*0.84)); 
				this->addChild(tishi,120);  
*/
				if( bJiGuang  == false)
				{
					bShowWuQiTiShi =true; 
				} 
				if( bVipPao == false)
				{
					bShowWuQiTiShi =true; 
				}
				m_fFanWeiNum = 100;
				bFanWeipt->setVisible(false);
				bFanWeipt->setPercentage(100);
				m_FanWeimenu->setEnabled(true); 
				
				bFanWei = false;
			}
		}
	}  



	if(bVipPaoShoot == true)
	{
		this->m_fUpdateTimeShootVipPao += 1;
		if(this->m_fUpdateTimeShootVipPao >m_fTimeVipPaoShoot )
		{ 
			m_fUpdateTimeShootVipPao = 0;
			m_fVipPaoShootNum--; 

			if(m_fVipPaoShootNum == 0)
			{	
				m_fVipPaoShootNum = 100; 
				bVipPaoShoot = false;
				 
				if(bJiGuang == false)
				{ 
					m_JiGuangmenu->setEnabled(true); 
				}  
				if(bFanWei == false)
				{ 
					m_FanWeimenu->setEnabled(true); 
				}  

			
				//jywzuobiao
			/*	auto tishi = TiShi::create(3,GAME_DATA_STRING("shootwenzi1"),GAME_DATA_STRING("shootwenzi2"),8,0);
				tishi->setPosition(Point(winSize.width*0.54,winSize.height*0.84)); 
				this->addChild(tishi,120);  */


				m_SubItem->setVisible(true);
				m_AddItem->setVisible(true);

				if(bCanJieSuo == true)
				{
					bCanJieSuo = false;
					char cTempName[20];
					sprintf(cTempName,"bljs_dj_%d",GameBegin::getFileData("gameMaxPao.txt") + 1);
					int iNeedDengJi = GAME_DATA_INT(cTempName);

					memset(cTempName,0,sizeof(cTempName));
					sprintf(cTempName,"bljs_zuanshi_%d",GameBegin::getFileData("gameMaxPao.txt") + 1);
					int iNeedZuanShi  = GAME_DATA_INT(cTempName);

					if(iNeedDengJi > 0 && iNeedZuanShi> 0)
					{
						if(GameBegin::getFileData("gamePlayerlv.txt") >= iNeedDengJi  && GameBegin::getFileData("jywopl.txt") >= iNeedZuanShi )
						{ 
							int iTemp = CannonLayer::cNowMaxPao+1; 
							if(iTemp <  20)
							{ 
								CannonLayer::cNowMaxPao = GameBegin::getFileData("gameMaxPao.txt") ; 

								GameBegin::setFileData("gameMaxPao.txt",CannonLayer::cNowMaxPao+1); 
								char zuanshiTmp[20]; 
								GameCoinZuanshi(-iNeedZuanShi);
								isToMaxFlag = true;
								bLvUp = false;

							} 
							else
							{
								bShowJieSuoXiaoShi = true;
								bShowJieSuo = false;
								bLvUp = true;
							}
							// bShowJieSuo = true; 
						}
					}
					else
					{

						this->removeChild(m_Cannon,true);  
						m_Cannon = Cannon::create(_type,cBeiShu[_type],0); 
						m_Cannon->setPosition(SelfPaoPos);
						m_Cannon->setRot(angle);
						this->addChild(m_Cannon,100);  
					}
				}
				else
				{
					this->removeChild(m_Cannon,true);  
					m_Cannon = Cannon::create(_type,cBeiShu[_type],0); 
					m_Cannon->setPosition(SelfPaoPos);
					m_Cannon->setRot(angle);
					this->addChild(m_Cannon,100);  
				} 
			}
		}
	} 


	if(bVipPao == true)
	{
		this->m_fUpdateTimeVipPao += 1;
		if(this->m_fUpdateTimeVipPao >m_fTimeVipPao )
		{ 
			m_fUpdateTimeVipPao = 0;
			m_fVipPaoNum--;
			bVipPaopt->setPercentage(m_fVipPaoNum);

			if(m_fVipPaoNum == 0)
			{	

			/*	auto tishi = TiShi::create(3,GAME_DATA_STRING("vippaook1"),GAME_DATA_STRING("vippaook2"),4,0);
				tishi->setPosition(Point(winSize.width*0.54,winSize.height*0.84)); 
				this->addChild(tishi,120);
*/
				if( bJiGuang  == false)
				{
					bShowWuQiTiShi =true; 
				} 
				if( bFanWei  == false)
				{
					bShowWuQiTiShi =true; 
				} 

				m_fVipPaoNum = 100;
				bVipPaopt->setVisible(false);
				bVipPaopt->setPercentage(100);
				m_VipPaomenu->setEnabled(true); 

				bVipPao = false;
			}
		}
	}  





	if(bJiGuangShoot == true)
	{
		this->m_fUpdateTimeJiGuangShoot += 1;
		if(this->m_fUpdateTimeJiGuangShoot >m_fTimeJiGuangShoot )
		{ 
			m_fUpdateTimeJiGuangShoot = 0;
			m_fJiGuangShootNum--;
	 
			if(m_fJiGuangShootNum == 0)
			{	
				m_fJiGuangShootNum = 100;
			  
				bJiGuangShoot = false;

				if(xinshoutimejiguang >= 200)
				{ 
					xinshoutimejiguang = 0;
					typeJiGuang =   GameBegin::getFileData("typeJiGuang")-1; 
				}
				 
			/*	auto tishi = TiShi::create(3,GAME_DATA_STRING("shootwenzi1"),GAME_DATA_STRING("shootwenzi2"),8,0);
				tishi->setPosition(Point(winSize.width*0.44,winSize.height*0.84)); 
				this->addChild(tishi,120);  */
				if(bFanWei == false)
				{ 
					m_FanWeimenu->setEnabled(true); 
				}    
				if(bVipPao == false)
				{ 
					m_VipPaomenu->setEnabled(true); 
				}  
				m_SubItem->setVisible(true);
				m_AddItem->setVisible(true);
				 



				if(bCanJieSuo == true)
				{
					bCanJieSuo = false;
					char cTempName[20];
					sprintf(cTempName,"bljs_dj_%d",GameBegin::getFileData("gameMaxPao.txt") + 1);
					int iNeedDengJi = GAME_DATA_INT(cTempName);

					memset(cTempName,0,sizeof(cTempName));
					sprintf(cTempName,"bljs_zuanshi_%d",GameBegin::getFileData("gameMaxPao.txt") + 1);
					int iNeedZuanShi  = GAME_DATA_INT(cTempName);

					if(iNeedDengJi > 0 && iNeedZuanShi> 0)
					{
						if(GameBegin::getFileData("gamePlayerlv.txt") >= iNeedDengJi  && GameBegin::getFileData("jywopl.txt") >= iNeedZuanShi )
						{ 
							int iTemp = CannonLayer::cNowMaxPao+1; 
							if(iTemp <  20)
							{ 
								CannonLayer::cNowMaxPao = GameBegin::getFileData("gameMaxPao.txt") ; 
								GameBegin::setFileData("gameMaxPao.txt",CannonLayer::cNowMaxPao+1); 
								char zuanshiTmp[20]; 
								GameCoinZuanshi(-iNeedZuanShi);  
								isToMaxFlag = true;
								bLvUp = false;

							} 
							else
							{
								bShowJieSuoXiaoShi = true;
								bShowJieSuo = false;
								bLvUp = true;
							}
							// bShowJieSuo = true; 
						}
					}
					else
					{ 
						this->removeChild(m_Cannon,true);  
						m_Cannon = Cannon::create(_type,cBeiShu[_type],0); 
						m_Cannon->setPosition(SelfPaoPos);
						m_Cannon->setRot(angle);
						this->addChild(m_Cannon,100);  
					}
				}
				else
				{
					this->removeChild(m_Cannon,true);  
					m_Cannon = Cannon::create(_type,cBeiShu[_type],0); 
					m_Cannon->setPosition(SelfPaoPos);
					m_Cannon->setRot(angle);
					this->addChild(m_Cannon,100);  
				} 
			}
		}
	} 
	
	if(bJiGuang == true)
	{
		this->m_fUpdateTimeJiGuang += 1;
		if(this->m_fUpdateTimeJiGuang >m_fTimeJiGuang )
		{ 
			m_fUpdateTimeJiGuang = 0;
			  
			 
			m_fJiGuangNum--;
			bJiGuangpt->setPercentage(m_fJiGuangNum); 
			/*naocannum->setVisible(true);
			if(m_fJiGuangNum == cNoNum* cJiGuangNum)
			{
				
				char cTemp[10];
				sprintf(cTemp,"%d",cJiGuangNum);
				naocannum->setString(cTemp);

				cJiGuangNum--;

			} */
			if(m_fJiGuangNum == 0)
			{	


				if( bJiGuang  == false)
				{
					bShowWuQiTiShi =true; 
				} 
				if( bVipPao == false)
				{
					bShowWuQiTiShi =true; 
				} 

				m_fJiGuangNum = 100;
				bJiGuangpt->setVisible(false);
				bJiGuangpt->setPercentage(100); 
				m_JiGuangmenu->setEnabled(true); 
				bJiGuang = false; 
				if( bFanWei  == false)
				{
					bShowWuQiTiShi =true; 
				}

			}
		}
	} 
 
}

void CannonLayer::ShowGuangAni(char cPos,bool biSaiSelf)
{
	Animation* fishAnimation = AnimationCache::getInstance()->getAnimation("paoTexiao");
	Animate* fishAnimate = Animate::create(fishAnimation);

	if(biSaiSelf == false && cPos == 5)
	{
		paoTexiaoSpr->setPosition(Point(winSize.width*0.5f,55));
	}
	else 
	{
		if(cPos == 0 ||(biSaiSelf == true&&GameScene::cSelfPos == 0))
		{
			paoTexiaoSpr->setPosition(Point(robotPos1,55));
		}
		else if(cPos == 1||(biSaiSelf == true&&GameScene::cSelfPos == 0))
		{
			paoTexiaoSpr->setPosition(Point(robotPos2,55));
		}
		else if(cPos == 2)
		{
			paoTexiaoSpr->setPosition(Point(robotPos1,winSize.height-55));
		}
		else if(cPos == 3)
		{
			paoTexiaoSpr->setPosition(Point(robotPos2,winSize.height-55));
		}
	}
	
	m_fUpdateTime = 0;
	m_fTime = 0.4f;
	bpaoTeXiao = true;
	paoTexiaoSpr->runAction(fishAnimate);
	paoTexiaoSpr->setVisible(true);
}

void CannonLayer::switchCannon(Ref* sender)
{
	if(GameScene::cGameType == 1)
		ShowGuangAni(88,true);
	else
		ShowGuangAni(5,false);
	 GameBegin::playSound("changecannon.mp3");
    if(sender == m_AddItem)
	{
		_type++;
		bool oNo = false;
		if(_type >GameHallLayer::sceneHighPao - 1)
		{
			_type = GameHallLayer::sceneLowPao - 1;
			 if(bFirstChoose == false)
			 {
				 oNo = true;
				 MoveInTwo();
			 }
		}  
		if(_type > cNowMaxPao)
		{
			  
			char cTempName[20];
			sprintf(cTempName,"bljs_dj_%d",GameBegin::getFileData("gameMaxPao.txt") + 1);
			int iNeedDengJi = GAME_DATA_INT(cTempName);


			memset(cTempName,0,sizeof(cTempName));
			sprintf(cTempName,"bljs_zuanshi_%d",GameBegin::getFileData("gameMaxPao.txt") + 1);
			int iNeedZuanShi  = GAME_DATA_INT(cTempName);

			if(iNeedDengJi > 0 && iNeedZuanShi> 0)
			{
				if(GameBegin::getFileData("gamePlayerlv.txt") >= iNeedDengJi  && GameBegin::getFileData("jywopl.txt") >= iNeedZuanShi )
				{ 
					int iTemp = CannonLayer::cNowMaxPao+1; 
					if(iTemp <  GameHallLayer::sceneHighPao)
					{ 
						bFirstChoose = true; 
						MoveInOne();
						bLock = false;

						CannonLayer::cNowMaxPao = GameBegin::getFileData("gameMaxPao.txt") ; 
						GameBegin::setFileData("gameMaxPao.txt",CannonLayer::cNowMaxPao+1); 
						char zuanshiTmp[20]; 

						ToMax();

						if(GameScene::cGameType != 1)
						{
							GameCoinZuanshi(-iNeedZuanShi);  


							if(cNowMaxPao == GameHallLayer::sceneHighPao - 1)
							{
								bShowJieSuoXiaoShi = true;
								bShowJieSuo = false;
							}
							else
							{
								memset(cTempName,0,sizeof(cTempName));
								sprintf(cTempName,"bljs_dj_%d",GameBegin::getFileData("gameMaxPao.txt") + 1);
								int iNeedDengJi = GAME_DATA_INT(cTempName);

								memset(cTempName,0,sizeof(cTempName));
								sprintf(cTempName,"bljs_zuanshi_%d",GameBegin::getFileData("gameMaxPao.txt") + 1);
								int iNeedZuanShi  = GAME_DATA_INT(cTempName);

								if(iNeedDengJi > 0 && iNeedZuanShi> 0)
								{
									if(GameBegin::getFileData("gamePlayerlv.txt") >= iNeedDengJi  &&  GameBegin::getFileData("jywopl.txt") >= iNeedZuanShi )
									{ 
										CannonLayer::bShowJieSuo = true;
									}
									else
									{
										bShowJieSuo = false;
										bShowJieSuoXiaoShi = true;
									}
								}

							} 
						} 

					} 
					else
					{
						bShowJieSuoXiaoShi = true;
						bShowJieSuo = false;
						bLvUp = true;
					}
					 
					return;
				}
				else
				{ 
					if(bFirstChoose == true)
					{
						bFirstChoose = false;
						MoveOutTwo();

					}
					bLock = true;
				}
			}


		
		}
		else if(_type == cNowMaxPao)
		{

			 bFirstChoose = true; 
			 MoveInOne();
			 bLock = false;
			  
		}
		else
		{  
			if(bFirstChoose == true)
			{
				bFirstChoose = false;
				MoveOutOne(); 
			}
			 

			bLock = false;
		}  
		if(oNo == true)
		{
			bFirstChoose = true;
		}
    }
	else if(sender == m_SubItem)
	{
		_type--;
		bool oNo = false;
		if(_type < GameHallLayer::sceneLowPao - 1)
		{
			_type =GameHallLayer::sceneHighPao - 1;
			if(bFirstChoose == false)
			{
				oNo = true;				
				MoveInOne();
			}
		} 
		
		if(_type > cNowMaxPao)
		{
			bLock = true;

			if(bFirstChoose == true)
			{
				bFirstChoose = false;
				MoveOutTwo();  
			} 
		}
		else if(_type == cNowMaxPao)
		{

			 bFirstChoose = true;
				bLock = false;

				MoveInTwo();
			 
		}
		else if(_type == 0)
		{
			bFirstChoose = true;
			bLock = false;

			MoveInTwo(); 
		}
		else
		{
			if(bFirstChoose == true)
			{ 
				bFirstChoose = false;
				MoveOutOne(); 
			} 
			bLock = false;
		}  
		if(oNo == true)
		{
			 bFirstChoose = true;
		}
    }

	this->removeChild(m_Cannon,true);
	
	m_Cannon = Cannon::create(_type,cBeiShu[_type],0); 
	m_Cannon->setPosition(SelfPaoPos);
	m_Cannon->setRot(angle);
	this->addChild(m_Cannon,100);  

}

void CannonLayer::MoveOutOne()
{ 
	m_MinItem->setVisible(true);
	m_MaxItem->setVisible(true);
	auto minmove = MoveTo::create(0.2f,menuPointTwo[0]);  
	auto scale = ScaleTo::create(0.2f,1.0f);
	auto call = CallFunc::create(CC_CALLBACK_0(CannonLayer::menuMoveTrue,this));
	auto seq = Sequence::create(minmove,call,nullptr); 

	m_MinItem->runAction(seq);
	m_MinItem->runAction(scale);

	auto minmove2 = MoveTo::create(0.2f,menuPointTwo[1]);
	auto scale2 = ScaleTo::create(0.2f,1.0f);
	m_MaxItem->runAction(minmove2); 
	m_MaxItem->runAction(scale2); 
	 
}

void CannonLayer::MoveOutTwo()
{
	m_MinItem->setVisible(true);
	m_MaxItem->setVisible(true);
	m_JieSuo->setVisible(true);
	auto minmove = MoveTo::create(0.2f,menuPoint[0]);  
	auto scale = ScaleTo::create(0.2f,1.0f);
	auto call = CallFunc::create(CC_CALLBACK_0(CannonLayer::menuMoveTrueTwo,this));
	auto seq = Sequence::create(minmove,call,nullptr); 

	m_MinItem->runAction(seq);
	m_MinItem->runAction(scale);

	auto minmove2 = MoveTo::create(0.2f,menuPoint[1]);
	auto scale2 = ScaleTo::create(0.2f,1.0f);
	m_MaxItem->runAction(minmove2); 
	m_MaxItem->runAction(scale2);

	auto minmove3 = MoveTo::create(0.2f,menuPoint[2]);
	auto scale3 = ScaleTo::create(0.2f,1.0f);
	m_JieSuo->runAction(minmove3); 
	m_JieSuo->runAction(scale3);
}

void CannonLayer::MoveInOne()
{
	
	m_MinItemmenu->setVisible(false);
	m_MaxItemmenu->setVisible(false); 

	m_MinItem->stopAllActions();
	m_MaxItem->stopAllActions();
	m_MinItem->setVisible(true);
	m_MaxItem->setVisible(true);

	auto minmove = MoveTo::create(0.2f,menuPointBegin);  
	auto scale = ScaleTo::create(0.2f,0.1f);
	auto call = CallFunc::create(CC_CALLBACK_0(CannonLayer::menuMoveOver,this));
	auto seq = Sequence::create(minmove,call,nullptr); 

	m_MinItem->runAction(seq);
	m_MinItem->runAction(scale);

	auto minmove2 = MoveTo::create(0.2f,menuPointBegin);
	auto scale2 = ScaleTo::create(0.2f,0.1f);
	m_MaxItem->runAction(minmove2); 
	m_MaxItem->runAction(scale2);
	if(TishiJieSuo != NULL)
	TishiJieSuo->setVisible(false); 
}

void CannonLayer::MoveInTwo()
{

	m_MinItemmenu->setVisible(false);
	m_MaxItemmenu->setVisible(false);
	m_JieSuomenu->setVisible(false);
 

	m_MinItem->stopAllActions();
	m_MaxItem->stopAllActions();
	m_JieSuo->stopAllActions();

	m_MinItem->setVisible(true);
	m_MaxItem->setVisible(true);
	m_JieSuo->setVisible(true);

	auto minmove = MoveTo::create(0.2f,menuPointBegin);  
	auto scale = ScaleTo::create(0.2f,0.1f);
	auto call = CallFunc::create(CC_CALLBACK_0(CannonLayer::menuMoveOverTwo,this));
	auto seq = Sequence::create(minmove,call,nullptr); 

	m_MinItem->runAction(seq);
	m_MinItem->runAction(scale);

	auto minmove2 = MoveTo::create(0.2f,menuPointBegin);
	auto scale2 = ScaleTo::create(0.2f,0.1f);
	m_MaxItem->runAction(minmove2); 
	m_MaxItem->runAction(scale2);

	auto minmove3 = MoveTo::create(0.2f,menuPointBegin);
	auto scale3 = ScaleTo::create(0.2f,0.1f);
	m_JieSuo->runAction(minmove3); 
	m_JieSuo->runAction(scale3); 
	
	if(TishiJieSuo != NULL)
	TishiJieSuo->setVisible(false);

}

void CannonLayer::menuMoveOver()
{
	m_MinItem->setVisible(false);
	m_MaxItem->setVisible(false); 

}

void CannonLayer::menuMoveOverTwo()
{
	m_MinItem->setVisible(false);
	m_MaxItem->setVisible(false);
	m_JieSuo->setVisible(false);

}

void CannonLayer::menuMoveTrue()
{
	m_MinItem->setVisible(false);
	m_MaxItem->setVisible(false); 
	m_MinItemmenu->setPosition(menuPointTwo[0]);
	m_MinItemmenu->setVisible(true);
	m_MaxItemmenu->setPosition(menuPointTwo[1]);
	m_MaxItemmenu->setVisible(true); 

}

void CannonLayer::menuMoveTrueTwo()
{
	m_MinItem->setVisible(false);
	m_MaxItem->setVisible(false);
	m_JieSuo->setVisible(false);
	m_MinItemmenu->setVisible(true);
	m_MinItemmenu->setPosition(menuPoint[0]);
	m_MaxItemmenu->setVisible(true);
	m_MaxItemmenu->setPosition(menuPoint[1]);
	m_JieSuomenu->setVisible(true);
	m_JieSuomenu->setPosition(menuPoint[2]);

}

void CannonLayer::aimAt(Point target)
{ 

	Vec2 location;
	if(GameScene::cGameType == 1)
	{
		if(GameScene::cSelfPos == 0)
		{
			location = Vec2(robotPos1,50);
		}
		else if(GameScene::cSelfPos == 1)
		{
			location = Vec2(robotPos2,50);
		} 
	}
	else 
	{
		location = Vec2(winSize.width*0.5f,50);
	} 
	angle = CC_RADIANS_TO_DEGREES(ccpAngleSigned(ccpSub(target, location), Point(0, 1)));


	Point normal = ccpNormalize(ccpSub(target,location)); 
	Point vector = ccpMult(normal, 10);
	m_Cannon->aimAt(angle,vector);
}
void CannonLayer::aimAtRobot(cocos2d::Point target,char cRobotType)
{ 


	if(cRobotType == 0)
	{
		Point location = Point(robotPos1,50);
		angle = CC_RADIANS_TO_DEGREES(ccpAngleSigned(ccpSub(target, location), Point(0, 1)));


		Point normal = ccpNormalize(ccpSub(target,location)); 
		Point vector = ccpMult(normal, 8);
		m_CannonRobot[0]->aimAt(angle,vector,false);
	}
	else if(cRobotType == 1)
	{
		Point location = Point(robotPos2,50);
		angle = CC_RADIANS_TO_DEGREES(ccpAngleSigned(ccpSub(target, location), Point(0, 1)));


		Point normal = ccpNormalize(ccpSub(target,location)); 
		Point vector = ccpMult(normal, 8);
		m_CannonRobot[1]->aimAt(angle,vector,false);
	}
	else if(cRobotType == 2)
	{
		Point location = Point(robotPos1,winSize.height - 50);
		angle = CC_RADIANS_TO_DEGREES(ccpAngleSigned(ccpSub(target, location), Point(0, -1)));


		Point normal = ccpNormalize(ccpSub(target,location)); 
		Point vector = ccpMult(normal, 8);
		m_CannonRobot[2]->aimAt(angle,vector,false);
	}
	else if(cRobotType == 3)
	{
		Point location = Point(robotPos2,winSize.height - 50);
		angle = CC_RADIANS_TO_DEGREES(ccpAngleSigned(ccpSub(target, location), Point(0, -1)));


		Point normal = ccpNormalize(ccpSub(target,location)); 
		Point vector = ccpMult(normal, 8);
		m_CannonRobot[3]->aimAt(angle,vector,false);

	}
	
}
void CannonLayer::AddRobotMoney(float dt)
{
	for(int i=0; i< 4; i++)
	{
		if(GameScene::bRobotPos[i] == true)
		{ 
			if(bPoChan[i] == true)
			{
				char BeiTi  = 0;
				if(GameScene::cRobotIQ[i] ==1)
				{
					BeiTi = 30;
				}
				else if(GameScene::cRobotIQ[i] ==2)
				{
					BeiTi = 10;
				}
				if(CCRANDOM_0_1()*100 < BeiTi)
				{
				 return;
				} 
				else
				{
					for(int k = 0 ; k < 4 ; k++)  //对四个比赛模式循环
					{
						if(GameHallLayer::RoomType - 90 == k)//确定了k模式
						{
							for(int j = 0 ; j < 3 ; j ++) //对机器人智商循环
							{
								if(GameScene::cRobotIQ[i] == j + 1)//确定了j智商
								{
									//随机给机器人加钱
									int SuiJigailv  = CCRANDOM_0_1() * 100;
									for(int m = 0 ; m < 7 ; m++)
									{
										if(SuiJigailv <  robot_add_money[k][j][m])
										{
											//加钱 给第i个机器人加第m个钱
											RobotMoney[i] += robot_add_money_kind[m];

											char cConinNum[14];
											memset(cConinNum,0,14);
											sprintf(cConinNum,"%d",RobotMoney[i]);
											GameCoinLabel[i]->setString( cConinNum);  

											bChangeRobotBaseIfOver[i] = false;
											bPoChan[i] = false; 
											PoChanSpr[i]->setVisible(false);
											break;
										}						
									}
									break;
								}
								
							}
							break;
						}
					}
 			
				}
				
			}
		} 

	}
}

  bool CannonLayer::RobotshootTo(Point target,char cRobotPos)
{
	int iTypeTemp = cRobotType[cRobotPos];
	int iInet = cRobotType[cRobotPos];
	if(bFanWeiRobotShoot[cRobotPos] == true)
	{ 
		iTypeTemp = 20+cRobotTypeFanWei[cRobotPos]; 
		if(RobotMoney[cRobotPos] < cBeiShu[iInet] * iFanWeiCoin[cRobotTypeFanWei[cRobotPos]])
		{
			 bChangeRobotBaseIfOver[cRobotPos] = true;
			 bPoChan[cRobotPos] = true;
			 PoChanSpr[cRobotPos]->setVisible(true);
			 if(GameScene::cRobotIQ[cRobotPos] == 1 )
			 {
				  this->scheduleOnce(schedule_selector(CannonLayer::AddRobotMoney),11.0f);
			 }
			 else if(GameScene::cRobotIQ[cRobotPos] == 2)
			 {
				  this->scheduleOnce(schedule_selector(CannonLayer::AddRobotMoney),8.0f);
			 }
			 else if(GameScene::cRobotIQ[cRobotPos] == 3)
			 {
				  this->scheduleOnce(schedule_selector(CannonLayer::AddRobotMoney),5.0f);
			 }
			
			return false;
		}
		else
		{
			GameCoinRefresh(-(cBeiShu[iInet] * iFanWeiCoin[cRobotTypeFanWei[cRobotPos]]),false,false,cRobotPos);
		}
	}
	else if(bJiGuangRobotShoot[cRobotPos]== true)
	{  
		iTypeTemp = 25+cRobotTypeJiGuang[cRobotPos];
		if(RobotMoney[cRobotPos] < cBeiShu[iInet] * iJiGuangCoin[cRobotTypeJiGuang[cRobotPos]])
		{
			bChangeRobotBaseIfOver[cRobotPos] = true;
			bPoChan[cRobotPos] = true;
			PoChanSpr[cRobotPos]->setVisible(true);
			if(GameScene::cRobotIQ[cRobotPos] == 1 )
			{
				this->scheduleOnce(schedule_selector(CannonLayer::AddRobotMoney),11.0f);
			}
			else if(GameScene::cRobotIQ[cRobotPos] == 2)
			{
				this->scheduleOnce(schedule_selector(CannonLayer::AddRobotMoney),8.0f);
			}
			else if(GameScene::cRobotIQ[cRobotPos] == 3)
			{
				this->scheduleOnce(schedule_selector(CannonLayer::AddRobotMoney),5.0f);
			}

			// if(cRobotIQ[cRobotPos] 
			 //画张希的破产
			 //预约个函数 时间到后 冲钱 删除破产  bChangeRobotBaseIfOver  = false;
			return false;
		}
		else
		{
			GameCoinRefresh(-(cBeiShu[iInet] * iJiGuangCoin[cRobotTypeJiGuang[cRobotPos]]),false,false,cRobotPos);
		}

	}  
	else if(bVipShoot[cRobotPos] == true)
	{
		iTypeTemp = 30;
		if(RobotMoney[cRobotPos] < cBeiShu[iInet])
		{
			bChangeRobotBaseIfOver[cRobotPos] = true;
			bPoChan[cRobotPos] = true;
			PoChanSpr[cRobotPos]->setVisible(true);
			if(GameScene::cRobotIQ[cRobotPos] == 1 )
			{
				this->scheduleOnce(schedule_selector(CannonLayer::AddRobotMoney),11.0f);
			}
			else if(GameScene::cRobotIQ[cRobotPos] == 2)
			{
				this->scheduleOnce(schedule_selector(CannonLayer::AddRobotMoney),8.0f);
			}
			else if(GameScene::cRobotIQ[cRobotPos] == 3)
			{
				this->scheduleOnce(schedule_selector(CannonLayer::AddRobotMoney),5.0f);
			}
			return false;
		}
		else
		{
			GameCoinRefresh(cBeiShu[iInet],false,false,cRobotPos);
		}


	}
	else
	{
		if(RobotMoney[cRobotPos] < cBeiShu[iTypeTemp])
		{
			bChangeRobotBaseIfOver[cRobotPos] = true;
			bPoChan[cRobotPos] = true;
			PoChanSpr[cRobotPos]->setVisible(true);
			if(GameScene::cRobotIQ[cRobotPos] == 1 )
			{
				this->scheduleOnce(schedule_selector(CannonLayer::AddRobotMoney),11.0f);
			}
			else if(GameScene::cRobotIQ[cRobotPos] == 2)
			{
				this->scheduleOnce(schedule_selector(CannonLayer::AddRobotMoney),8.0f);
			}
			else if(GameScene::cRobotIQ[cRobotPos] == 3)
			{
				this->scheduleOnce(schedule_selector(CannonLayer::AddRobotMoney),5.0f);
			}

			return false;
		}
		else
		{
			GameCoinRefresh(-cBeiShu[iTypeTemp],false,false,cRobotPos);
		}
		
	} 
	return m_Weapon->RobotshootTo(target,iTypeTemp ,cRobotPos, iInet );  
}

bool CannonLayer::shootTo(Point target)
{
	 
	if(bLock == true)
	{ 
		//jyw007 修改子弹过多和未解锁炮的坐标 
		if(TishiJieSuo == NULL)
		{
		/*	string oo = GAME_DATA_STRING("jiesuopaoone");
			TishiJieSuo = TiShi::create(2,oo,GAME_DATA_STRING("jiesuopaotwo"),3,0,true); 
			TishiJieSuo->setPosition(Point(723,238)); 
			this->addChild(TishiJieSuo); */
		}
		else
		{ 
			TishiJieSuo->setVisible(true);
			TishiJieSuo->yuyue();
		}
		return true;
	}
	if(m_Weapon->m_Bullet[4].size() > 50 )
	{ 
		if(TishiBulletMore == NULL)
		{
			string oo = GAME_DATA_STRING("bulletmoreone");
			TishiBulletMore = TiShi::create(2,oo,GAME_DATA_STRING("bulletmoretwo"),3,0,true); 
			TishiBulletMore->setPosition(Point(723,238)); 
			this->addChild(TishiBulletMore); 
		}
		else
		{ 
			TishiBulletMore->setVisible(true);
			TishiBulletMore->yuyue(); 
		}
		return true;

	}

	int iTypeTemp = _type;
	if(bFanWeiShoot == true)
	{

		if(GameBegin::getFileData("jywer.txt") < cBeiShu[_type])
		{
			//wftishikuang
			return false;
		}
		else
		{
			iTypeTemp = 20+typeFanWei;
			
		}
	}
	else if(bJiGuangShoot == true)
	{
		if(GameBegin::getFileData("jywer.txt") < cBeiShu[_type])
		{
			//wftishikuang
			return false;
		}
		else
		{
			iTypeTemp = 25+typeJiGuang;
			
		}
	}
	else if(bVipPaoShoot == true)
	{
		if(GameBegin::getFileData("jywer.txt") < cBeiShu[_type])
		{
			//wftishikuang
			return false;
		}
		else
		{
			if(GameScene::cGameType == 1)
			{
				GameCoinRefresh(-cBeiShu[_type],false,false);
			}
			else 
			{
				GameCoinRefresh(-cBeiShu[_type],true,true);
			}
			iTypeTemp = 30;

		}
	}
	else if(GameBegin::getFileData("jywer.txt") < cBeiShu[_type] )
	{
		//wftishikuang
		return false;
	}
	else 
	{
		if(GameScene::cGameType == 1)
		{
			GameCoinRefresh(-cBeiShu[_type],false,false);
		}
		else 
		{
			GameCoinRefresh(-cBeiShu[_type],true,true);
		}
		

	}
	

	if(bFirstChoose == false)
	{ 
		bFirstChoose = true;
		if(_type>= cNowMaxPao)
		{ 
			MoveInTwo();
		}
		else
		{
			MoveInOne();
		}  
	}  
	  
	if(bjiaSushoot == false&& bjiaSu == true)
	{
		ShootPos = target;
		bjiaSushoot = true;
	}
	 
	  
   return m_Weapon->shootTo(target,iTypeTemp ); 

}


void CannonLayer::GameCoinRefresh(int iNum,bool bExp ,bool bJiangchiFen,char cPos)
{
	int tmpMonty;
	if(cPos == 4 || cPos == 5)
	{
		tmpMonty  = GameBegin::getFileData("jywer.txt") + iNum; 
		memset(cConinNum,0,14);
		sprintf(cConinNum,"%d",tmpMonty);
		GameCoinLabel[4]->setString( cConinNum);   
		GameBegin::setFileData("jywer.txt",tmpMonty); 
	}
	else
	{
		
		RobotMoney[cPos] += iNum; 
		memset(cConinNum,0,14);
		sprintf(cConinNum,"%d",RobotMoney[cPos]);
		GameCoinLabel[cPos]->setString( cConinNum);     
		return;
	}
	  

	 if(iNum<0 && GameLv<50 && bExp == true &&GameScene::cGameType != 1)
	 {
		 GameExpRefresh(abs(iNum));
	 }
	if(GameScene::cGameType == 0)
	{
		 
		if(GameHallLayer::RoomType == 0)//||(GameHallLayer::RoomType == 1 && tmpMonty > 50000))
		{
			
			if(  tmpMonty > 10000 )
			{ 

				int bb = GameBegin::getFileData("gameMaxPao.txt") ; 
				if(bb < 9)
				{
					GameBegin::setFileData("gameMaxPao.txt",8);

				}

					GameScene::GoNewSence =1; 
			}
			//暴击动画
			//GameScene::isbaoji = true;
		}
		if((GameHallLayer::RoomType == 1))//||(GameHallLayer::RoomType == 1 && tmpMonty > 50000))
		{ 
			if(  tmpMonty > 200000 )
			{ 
				int bb = GameBegin::getFileData("gameMaxPao.txt") ; 
				if(bb < 9)
				{
					GameBegin::setFileData("gameMaxPao.txt",8);

				}
				GameScene::GoNewSence =2; 
			} 
		}
	}
	
}

void CannonLayer::GameExpRefresh(int iNum)
  {
	   GameExp += iNum; 
	  GameBegin::setFileData("gameExp.txt",GameExp);
	

	  int lv;
	  float exp;
	  int tmpExp = GameExp;

	  //计算经验条比例
	  for(int i =1; i<50 ; i++)
	  {
		  if(tmpExp<iJingYanDengJi[i])
		  {
			  lv = i;
			  exp =(float)tmpExp/iJingYanDengJi[i];
			  break;
		  }
		  tmpExp -= iJingYanDengJi[i];
	  }
	  //判断是否升级了 升级了就增加金钱和钻石
	  if((lv - GameLv)>0)
	  { 
		  if(lv == 2)
		  {
			  bJiGuangyindao = true;
		  } 
		  if(lv == 5)
		  { 
			  bFanweiyindao = true;
		  } 
		  if(lv == 7)
		  {
			  GameScene::isBiSaiVis = true;
		  }

		 
 
		  CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(iSoundId);
		  iSoundId = GameBegin::playSound("lvup.mp3");
		  if(lv < 16)
		  {
			  int tmpMoney = GameBegin::getFileData("jywer.txt") + (lv-GameLv)*50 ;
			  GameBegin::setFileData("jywer.txt",tmpMoney);

			  memset(cConinNum,0,14);
			  sprintf(cConinNum,"%d",tmpMoney);
			  GameCoinLabel[4]->setString( cConinNum); 
			  bLvUp = true;
			    
			  iLvMoney = (lv-GameLv)*50; 
			  iLvZuan = (lv-GameLv)*5;  
		  }
		  else if(lv < 41)
		  {
			  int tmpMoney = GameBegin::getFileData("jywer.txt") + (lv-GameLv)*100 ;
			  GameBegin::setFileData("jywer.txt",tmpMoney);

			  memset(cConinNum,0,14);
			  sprintf(cConinNum,"%d",tmpMoney);
			  GameCoinLabel[4]->setString( cConinNum);

			  bLvUp = true;

			  iLvMoney = (lv-GameLv)*100;
			  iLvZuan = (lv-GameLv)*5;

		  }
		  else if(lv < 51)
		  {
			  int tmpMoney = GameBegin::getFileData("jywer.txt") + (lv-GameLv)*200 ;
			  GameBegin::setFileData("jywer.txt",tmpMoney);

			  memset(cConinNum,0,14);
			  sprintf(cConinNum,"%d",tmpMoney);
			  GameCoinLabel[4]->setString( cConinNum);  


			  bLvUp = true;

			  iLvMoney = (lv-GameLv)*200;
			  iLvZuan = (lv-GameLv)*5;
		  }
		  
		  if(lv < 21)
		  {
			  GameCoinZuanshi(5);  
		  }
		  else if(lv < 31)
		  {
			  GameCoinZuanshi(10);  
		  } 
		  else if(lv < 41)
		  {
			  GameCoinZuanshi(20);  
		  }
		  else if(lv < 60)
		  {
			  GameCoinZuanshi(30);  
		  }
		   
		  GameLv = lv;
		  GameBegin::setFileData("gamePlayerlv.txt",GameLv);  
		  
          int iMax = GameBegin::getFileData("gameMaxPao.txt") + 1;
          
          
          if(CannonLayer::cNowMaxPao< 7 && iMax < GameHallLayer::sceneHighPao + 1)
	 	 {
			  if(bFanWeiShoot == false &&  bJiGuangShoot == false  )
			  { 
				  char cTempName[20];
				  sprintf(cTempName,"bljs_dj_%d",GameBegin::getFileData("gameMaxPao.txt") + 1);
				  int iNeedDengJi = GAME_DATA_INT(cTempName);

				  memset(cTempName,0,sizeof(cTempName));
				  sprintf(cTempName,"bljs_zuanshi_%d",GameBegin::getFileData("gameMaxPao.txt") + 1);
				  int iNeedZuanShi  = GAME_DATA_INT(cTempName);

				  if(iNeedDengJi > 0 && iNeedZuanShi> 0)
				  {
					  if(GameBegin::getFileData("gamePlayerlv.txt") >= iNeedDengJi  && GameBegin::getFileData("jywopl.txt") >= iNeedZuanShi )
					  { 
						  int iTemp = CannonLayer::cNowMaxPao+1; 
						  if(iTemp <  GameHallLayer::sceneHighPao)
						  { 
							  CannonLayer::cNowMaxPao = GameBegin::getFileData("gameMaxPao.txt") ; 
							  GameBegin::setFileData("gameMaxPao.txt",CannonLayer::cNowMaxPao+1); 
							  char zuanshiTmp[20]; 
							  GameCoinZuanshi(-iNeedZuanShi);  
							  isToMaxFlag = true;
							  bLvUp = false;

						  } 
						  else
						  {
							  bShowJieSuoXiaoShi = true;
							  bShowJieSuo = false;
							  bLvUp = true;
						  }
						  // bShowJieSuo = true; 
					  }
				  }
			  }
			  else
			  {
				  bLvUp = false;
				  bCanJieSuo = true;
			  } 
		  
			} 
		   
	  }
	  //更新称号 
	  char playerTitleTmp[30]; 
	  int tmpLv = (int)((lv-1)/5) + 1;
	/*  sprintf(playerTitleTmp,"chenghao%d.png",tmpLv);
	  SpriteFrame * tmpFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(playerTitleTmp);
	  GameChenghao->setDisplayFrame(tmpFrame);*/

	  float widthTmp = exp*143;
	  float heightTmp = 24;
	  jingyanTiao->setTextureRect(Rect(0,0,widthTmp,heightTmp));
	  
	  char cTemp[10] = {0};
	  sprintf(cTemp,"%d",lv);
	  GameExpLabel->setString(cTemp);

  }

void CannonLayer::GameCoinZuanshi(int iNum)
 { 
	 //钻石文件
	 int tmpC = GameBegin::getFileData("jywopl.txt");
	 int tmpZuanshi = tmpC + iNum;
	 GameBegin::setFileData("jywopl.txt",tmpZuanshi);

	 if(GameScene::cGameType != 1)
	 {
		 char tmpZuanshiC[30];
		 sprintf(tmpZuanshiC,"%d",tmpZuanshi);
		 GameZuanshiLabel->setString( tmpZuanshiC);

	 }
	 
	 char cTemp[10];
	int iTempTime = 0;
	 iTempTime = tmpZuanshi/100; 
	 if(LoadRes::bFirstJiGuang == true)
	 {
		 iTempTime++; 
	 } 
	 memset(cTemp,0,sizeof(cTemp));
	 sprintf(cTemp,"%d",iTempTime);  
	 CountJiGuang->setString(cTemp);   


	 iTempTime = tmpZuanshi/100; 
	 if(LoadRes::bFirstFanWei == true)
	 {
		 iTempTime++;
		  
	 } 
	 memset(cTemp,0,sizeof(cTemp));
	 sprintf(cTemp,"%d",iTempTime);  
	 CountFanWei->setString( cTemp);   


	 iTempTime = tmpZuanshi/100; 
	 if(LoadRes::bFirstJiaSu  == true)
	 {
		 iTempTime++;

	 } 
	 if(GameScene::cGameType != 1)
	 {
		 memset(cTemp,0,sizeof(cTemp));
		 sprintf(cTemp,"%d",iTempTime);  
		 CountJiaSu->setString( cTemp);   
	 }
	 


	 iTempTime = tmpZuanshi/50;

	 memset(cTemp,0,sizeof(cTemp));
	 sprintf(cTemp,"%d",iTempTime);  
	 CountVipPao->setString( cTemp);  


	 iTempTime = tmpZuanshi/50;
	  
	 if(LoadRes::bFirtDingPing == true)
	 {
		 iTempTime++;
		  
	 }
	 if(GameScene::cGameType != 1)
	 {
		 memset(cTemp,0,sizeof(cTemp));
		 sprintf(cTemp,"%d",iTempTime);  
		 CountDingPing->setString( cTemp);   
	 }
 
 }

void CannonLayer::changeRobotBase(char cPos)
{
	if(m_CannonRobot[cPos] != NULL)
	{
		if(GameScene::bRobotPos[cPos] == true)
		{ 
			 
			if(CCRANDOM_0_1()*100 < 50)
			{
				cRobotType[cPos] = cRobotType[cPos]+1;
				if(cRobotType[cPos] > (GameHallLayer::sceneHighPao-1))
				{
					cRobotType[cPos] = GameHallLayer::sceneHighPao-1; 
				}
			}
			else
			{
				cRobotType[cPos] = cRobotType[cPos]-1;
				if(cRobotType[cPos] < GameHallLayer::sceneLowPao)
				{
					cRobotType[cPos] = GameHallLayer::sceneLowPao;
				}
			}

			this->removeChild(m_CannonRobot[cPos],true);
			 


			 GameBegin::playSound("changecannon.mp3");
			ShowGuangAni(cPos,false);
			m_CannonRobot[cPos] = Cannon::create(cRobotType[cPos],cBeiShu[cRobotType[cPos]],cPos); 
			if(cPos == 0 || cPos == 2)			
				m_CannonRobot[cPos]->setPosition(robotPos1,0);
			else
				m_CannonRobot[cPos]->setPosition(robotPos2,0);
			m_CannonRobot[cPos]->setRot(angle);
			this->addChild(m_CannonRobot[cPos],100);  
		} 
	} 
}


void CannonLayer::changeRobotEx(char cPos,bool bEx,char choosetype)
{
	if(m_CannonRobot[cPos] != NULL)
	{
		if(GameScene::bRobotPos[cPos] == true)
		{ 
			 if(bEx == true)
			 { 
				// return;
				 char cType = 0; 
				 if(choosetype == 0)
				 {
					 cType =20+ cRobotTypeFanWei[cPos];
					 bFanWeiRobotShoot[cPos] = true;
				 }
				 else if(choosetype == 1)
				 {
					 cType =25+ cRobotTypeJiGuang[cPos];
					 bJiGuangRobotShoot[cPos] = true;
				 }
					 else if(choosetype == 2)
				 {
					 cType =30;
					 bVipShoot[cPos] = true;

				 }
				 else
				 {
					 return;
				 } 
				  GameBegin::playSound("changecannon.mp3");
				 this->removeChild(m_CannonRobot[cPos]); 
				 ShowGuangAni(cPos,false);
				 m_CannonRobot[cPos] = Cannon::create(cType ,cBeiShu[cRobotType[cPos]],cPos); 
				 if(cPos == 0 || cPos == 2)			
					 m_CannonRobot[cPos]->setPosition(robotPos1,0);
				 else
					 m_CannonRobot[cPos]->setPosition(robotPos2,0);
				 m_CannonRobot[cPos]->setRot(angle);
				 this->addChild(m_CannonRobot[cPos],100);   	
			 }
			 else
			 {  
				 bFanWeiRobotShoot[cPos] = false;
				 bJiGuangRobotShoot[cPos] = false;
				 bVipShoot[cPos] = false;
				 this->removeChild(m_CannonRobot[cPos],true); 
				 ShowGuangAni(cPos,false);
				 m_CannonRobot[cPos] = Cannon::create(cRobotType[cPos],cBeiShu[cRobotType[cPos]],cPos); 
				 if(cPos == 0 || cPos == 2)			
					 m_CannonRobot[cPos]->setPosition(robotPos1,0);
				 else
					 m_CannonRobot[cPos]->setPosition(robotPos2,0);
				 m_CannonRobot[cPos]->setRot(angle);
				 this->addChild(m_CannonRobot[cPos],100);   	
			 } 
		} 
	} 
}
 
void CannonLayer::AddRobot(char cPos)
{
	if(m_CannonRobot[cPos] == NULL)
	{
		if(GameScene::bRobotPos[cPos] == true)
		{
			if(GameScene::cRobotIQ[cPos] == 1)
			{
				cRobotType[cPos] = GameHallLayer::sceneLowPao;
			}
			else if(GameScene::cRobotIQ[cPos] == 2)
			{
				cRobotType[cPos] = GameHallLayer::sceneLowPao+ CCRANDOM_0_1()*(GameHallLayer::sceneHighPao - GameHallLayer::sceneLowPao);
			}
			else if(GameScene::cRobotIQ[cPos] == 3)
			{
				//cRobotType[cPos] = GameHallLayer::sceneHighPao;
			}


			m_CannonRobot[cPos] = Cannon::create(cRobotType[cPos],cBeiShu[cRobotType[cPos]],cPos); 
			if(cPos == 0 || cPos == 2)			
				m_CannonRobot[cPos]->setPosition(robotPos1,0);
			else
				m_CannonRobot[cPos]->setPosition(robotPos2,0);
			m_CannonRobot[cPos]->setRot(angle);
			this->addChild(m_CannonRobot[cPos],100);   	
		}
	} 	
 
	RobotMoney[cPos] = 0; 
	if(GameScene::bRobotPos[cPos] == true)
	{
		initRobot(cPos,false);
	} 

}
 


void CannonLayer::ShowMatchOver()
{

    bLock = true;
    int huafeijuan[5][6]  ={ {20,10,5,4,3,2 },{30,20,10,8,5,3},{80,50,30,20,10,5},{150,100,80,50,30,20},{0,0,0,0,0,0}};
    
	int Money[5][7] ={{30000,
		20000,
		10000,
		8000,
		5000,
		3000,
		1000 },
	{200000,
	150000,
	100000,
	80000,
	25000,
	15000,
	10000 },
	{300000,
	200000,
	100000,
	80000,
	50000,
	30000,
	30000},
	{600000,
	400000,
	200000,
	160000,
	100000,
	60000,
	60000
    },
        {500,
            300,
            100,
            0,
            0,
            0,
            0
        }
    };

	int ZuanShi[5][7] ={{500,
		300,
		200,
		100,
		50,
		30,
		10
	}, 
	{1500,
	2000,
	1000,
	800,
	250,
	150,
	100
	},
	{3000,
	2000,
	1000,
	800,
	500,
	300,
	300
	},
	{6000,
	4000,
	2000,
	1600,
	1000,
	600,
	600}
        ,
        {0,
            0,
            0,
            0,
            0,
            0,
            0}
    };
		
	
    if(GameHallLayer :: RoomType == 89)
    {
        GameHallLayer::bs_moshi = 5;
    }
    else
    {
    /*    if(AllRobot::iRobotWinNum > AllRobot::myrank)
        {
            AllRobot::myrank =AllRobot::iRobotWinNum + CCRANDOM_0_1()*20;
        }*/
    }
    iRank =  AllRobot::myrank;
 
	for(int i = 0; i< 4; i++)
	{
		bChangeRobotBaseIfOver[i] = true;
		if(GameScene::bRobotPos[i] == false  )
		{
			 
                int iRand =  AllRobot::myrank;
				if(iRand ==1)
				{ 
					MatchOverMoney = Money[GameHallLayer::bs_moshi-1][0];
					MatchOverZuanShi = ZuanShi[GameHallLayer::bs_moshi-1][0];
                    //MatchOverhuafeiquan = huafeijuan[GameHallLayer::bs_moshi-1][0];
                    //GameBegin::setFileData("opla.txt", );
                   
                    GameBegin::setFileData("opta.txt",GameHallLayer::bs_moshi*10+1);
				}
				else if(iRand ==2)
				{ 
					MatchOverMoney = Money[GameHallLayer::bs_moshi-1][1];
					MatchOverZuanShi = ZuanShi[GameHallLayer::bs_moshi-1][1];
                    //MatchOverhuafeiquan = huafeijuan[GameHallLayer::bs_moshi-1][1];
               
                    //GameBegin::setFileData("opla.txt", MatchOverhuafeiquan);
                    GameBegin::setFileData("opta.txt",GameHallLayer::bs_moshi*10+2);
				}
				else  if(iRand ==3)
				{ 
					MatchOverMoney = Money[GameHallLayer::bs_moshi-1][2];
					MatchOverZuanShi = ZuanShi[GameHallLayer::bs_moshi-1][2];
                    //MatchOverhuafeiquan = huafeijuan[GameHallLayer::bs_moshi-1][2];
                    
                    //GameBegin::setFileData("opla.txt", MatchOverhuafeiquan);
                    GameBegin::setFileData("opta.txt",GameHallLayer::bs_moshi*10+3);
                    
               
				}
				else if(iRand >3 &&iRand< 11)
				{ 
					MatchOverMoney = Money[GameHallLayer::bs_moshi-1][3];
					MatchOverZuanShi = ZuanShi[GameHallLayer::bs_moshi-1][3];
                    //MatchOverhuafeiquan = huafeijuan[GameHallLayer::bs_moshi-1][3];
                    
                    //GameBegin::setFileData("opla.txt", MatchOverhuafeiquan);
                    GameBegin::setFileData("opta.txt",GameHallLayer::bs_moshi*10+4);
				}
				else if(iRand>10 && iRand< 51)
				{ 
					MatchOverMoney = Money[GameHallLayer::bs_moshi-1][4];
					MatchOverZuanShi = ZuanShi[GameHallLayer::bs_moshi-1][4];
                    //MatchOverhuafeiquan = huafeijuan[GameHallLayer::bs_moshi-1][4];
                    
                    //GameBegin::setFileData("opla.txt", MatchOverhuafeiquan);
                    GameBegin::setFileData("opta.txt",GameHallLayer::bs_moshi*10+5);

				}
				else if(iRand>50 && iRand< 101)
				{ 
					MatchOverMoney = Money[GameHallLayer::bs_moshi-1][5];
					MatchOverZuanShi = ZuanShi[GameHallLayer::bs_moshi-1][5];
                    //MatchOverhuafeiquan = huafeijuan[GameHallLayer::bs_moshi-1][5];
                    
                    //GameBegin::setFileData("opla.txt", MatchOverhuafeiquan);
                    GameBegin::setFileData("opta.txt",GameHallLayer::bs_moshi*10+6);
                    
				}
				else if(iRand>100 && iRand< 201)
				{  
					MatchOverMoney = Money[GameHallLayer::bs_moshi-1][6];
					MatchOverZuanShi = ZuanShi[GameHallLayer::bs_moshi-1][6];
				}
		}
	} 
 
   // int huafeijuan[5][6]  ={ {20,10,5,4,3,2 },{30,20,10,8,5,3},{80,50,30,20,10,5},{150,100,80,50,30,20},{0,0,0,0,0,0}};
    
    
   // GameBegin::setFileData("opla.txt", 20);
   // GameBegin::setFileData("opta.txt",11);
    
    /*GameBegin::setFileData("oplb.txt", 20);
    GameBegin::setFileData("optb.txt",11);
    
    GameBegin::setFileData("oplc.txt", 20);
    GameBegin::setFileData("optc.txt",11);
    
    GameBegin::setFileData("opld.txt", 20);
    GameBegin::setFileData("optd.txt",11);
    
    GameBegin::setFileData("ople.txt", MatchOverhuafeiquan);
    GameBegin::setFileData("opte.txt",11);
   */
    
        auto Matchover = Sprite:: createWithSpriteFrameName("Matchover.png");
        Matchover->setPosition(Vec2(winSize.width* 0.5f,winSize.height* 0.5f));
        Matchover->setScale(0.1f);
        Matchover->setTag(88);
        this->addChild(Matchover,MENULAYER);
        auto scto = ScaleTo::create(0.1f,1.0f);
        auto  delay = DelayTime::create(1.0f);
        auto scto1 = ScaleTo::create(0.1f,0.1f);
        
        auto * callfunc = CallFunc::create(this, callfunc_selector(CannonLayer::Match_meirenyu));
        auto * seq = CCSequence::create(scto, delay, scto1,callfunc, NULL);
        
        Matchover->runAction(seq);
 
  
}



void CannonLayer::Match_meirenyu()
{
    
    GameBegin::playSound("matchoverwf0.mp3");
    
	this->removeChildByTag(88);
	auto meirenyu = Sprite:: createWithSpriteFrameName("bs_meirenyu2.png");
	meirenyu->setScale(1.3f);
	meirenyu->setPosition(Vec2(visibleSize/2));
	meirenyu->setTag(88);
	addChild(meirenyu,MENULAYER);
 
	auto maohao1 = Sprite:: createWithSpriteFrameName("bs_meirenyu_dd.png");
	maohao1->setPosition(Vec2(meirenyu->getContentSize().width * 0.85,meirenyu->getContentSize().height*0.5));
	meirenyu->addChild(maohao1);

	auto seq1 = Sequence::create(MoveBy::create(0.1f,Vec2(0,maohao1->getContentSize().height * 1)),MoveBy::create(0.1f,Vec2(0,-maohao1->getContentSize().height * 1)),DelayTime::create(0.8f),nullptr);
    
 //   bCheckHuaFeiUpdate = true;
	auto * callfunc = CallFunc::create(this, callfunc_selector(CannonLayer::MatchoverAni));
	maohao1->runAction( Repeat::create(seq1,(int)CCRANDOM_0_1()*7 + 3));

	auto maohao2 = Sprite:: createWithSpriteFrameName("bs_meirenyu_dd.png");
	maohao2->setPosition(Vec2(meirenyu->getContentSize().width * 0.9,meirenyu->getContentSize().height*0.5));
	meirenyu->addChild(maohao2);

	auto seq2 = Sequence::create(DelayTime::create(0.1f),MoveBy::create(0.1f,Vec2(0,maohao1->getContentSize().height * 1)),MoveBy::create(0.1f,Vec2(0,-maohao1->getContentSize().height * 1)),DelayTime::create(0.7f),nullptr);
	maohao2->runAction(RepeatForever::create(seq2));

	auto maohao3 = Sprite:: createWithSpriteFrameName("bs_meirenyu_dd.png");
	maohao3->setPosition(Vec2(meirenyu->getContentSize().width * 0.95,meirenyu->getContentSize().height*0.5));
	meirenyu->addChild(maohao3);

	auto seq3 = Sequence::create(DelayTime::create(0.2f),MoveBy::create(0.1f,Vec2(0,maohao1->getContentSize().height * 1)),MoveBy::create(0.1f,Vec2(0,-maohao1->getContentSize().height * 1)),DelayTime::create(0.6f),nullptr);
	maohao3->runAction(RepeatForever::create(seq3));
    
    auto seq4 = Sequence::create(DelayTime::create(1.2f + CCRANDOM_0_1()*2), callfunc,nullptr);
    this->runAction(seq4);
    
}



void CannonLayer::MatchoverAni()
{
    
    
    this->removeChildByTag(88);
    
    int iTempOver = CCRANDOM_0_1()*100;
    if(iTempOver < 25)
    {
        GameBegin::playSound("matchoverwf1.mp3");
        
    }
    else if(iTempOver < 50)
    {
        GameBegin::playSound("matchoverwf2.mp3");
        
        
        
        
        
    }
    else if(iTempOver < 75)
    {
        GameBegin::playSound("matchoverwf3.mp3");
        
    }
    else
    {
        GameBegin::playSound("matchoverwf4.mp3");
        
    }
    
    GameCoinRefresh(MatchOverMoney);
    GameCoinZuanshi(MatchOverZuanShi);
    iMoneyJiangchi = iMoneyJiangchi - GameBegin::getFileData("jywer.txt");
 
    if(iRank<4)
    {
        
        Match_cup(iRank);
    }
    else if(iRank < 200)
    {
        Match_rank();
    }
    else
    {
        
        //背景
        auto r_bg =  Sprite:: createWithSpriteFrameName("Match_henyihan.png");
        r_bg->setPosition(Vec2(visibleSize.width/2 , visibleSize.height * 0.5));
        r_bg->setScale(0.01);
        this->addChild(r_bg,MENULAYER+15,666);
        
        char tmp_char[50];
        sprintf(tmp_char,"%d",iRank);
        
        //多少名
        auto label = Label::createWithCharMap("fishdeadnum.png",18,28,'0');
        label->setString(tmp_char);
        label->setPosition(Vec2(240,203));
        label->setScale(0.7f);
        
        label->setOpacity(0);
        r_bg->addChild(label);
        
        label->runAction(Sequence::create(DelayTime::create(0.3f),Spawn::create(FadeIn::create(0.2f),ScaleTo::create(0.2f,0.7f),nullptr),nullptr));
        
        auto xuanyao = Sprite:: createWithSpriteFrameName("Match_fanhui.png");
        
        
        
        MenuItemSprite* xuanyao_item ;
 
        
        if(iMoneyJiangchi > 9999)
        {
            xuanyao_item = MenuItemSprite::create(xuanyao,xuanyao,CC_CALLBACK_0(CannonLayer::tishizuanpan,this));
        }
        else
        {
            xuanyao_item = MenuItemSprite::create(xuanyao,xuanyao,CC_CALLBACK_0(CannonLayer::Match_exit,this));
        }
        
        
        auto xuanyao_menu = Menu::create(xuanyao_item,nullptr);
        xuanyao_menu->setVisible(false);
        xuanyao_menu->setPosition(Vec2(r_bg->getContentSize().width/2,60));
        r_bg->addChild(xuanyao_menu);
        
        xuanyao_menu->runAction(Sequence::create(DelayTime::create(0.5f),ToggleVisibility::create(),nullptr));
        
        r_bg->runAction(ScaleTo::create(0.2f,1.28));
    }
    
}

void CannonLayer::Match_cup(int i)
{
    char tmp_char[50];
    //背景
    auto r_bg =  Sprite:: createWithSpriteFrameName("rewardbg1.png");
	r_bg->setPosition(Vec2(visibleSize.width/2 , visibleSize.height * 0.5));
	r_bg->setScale(0.54);
	this->addChild(r_bg,MENULAYER+15);

	//圆盘
	sprintf(tmp_char,"RankYuan%d.png",i);
	auto r_bg_yp =  Sprite:: createWithSpriteFrameName(tmp_char);
	r_bg_yp->setPosition(Vec2(r_bg->getContentSize().width/2 ,r_bg->getContentSize().height * 0.795));
	r_bg->addChild(r_bg_yp,10);

	//圆盘后面的光
	sprintf(tmp_char,"Ranklight%d.png",1);
	auto r_bg_yp_g =  Sprite:: createWithSpriteFrameName(tmp_char);
	r_bg_yp_g->setScale(0.5);
	r_bg_yp_g->setVisible(false);
	r_bg_yp_g->setPosition(Vec2(r_bg_yp->getContentSize().width/2 ,r_bg_yp->getContentSize().height * 0.5));
	r_bg_yp->addChild(r_bg_yp_g,-2);

	//背景光执行动画
	r_bg_yp_g->runAction(Sequence::create(DelayTime::create(0.1f),ToggleVisibility::create(),ScaleTo::create(0.1f,1),nullptr));

	r_bg->runAction(ScaleTo::create(0.2f,1));

	float tx_time = 0.15f;
	//翅膀1
	sprintf(tmp_char,"Rankchibang%d.png",i);
	auto chibang1 =  Sprite:: createWithSpriteFrameName(tmp_char);
	chibang1->setScale(0.8);
	chibang1->setVisible(false);
	chibang1->setRotation(-30);
	chibang1->setPosition(Vec2(r_bg_yp->getContentSize().width/2 ,r_bg_yp->getContentSize().height * 0.5));
	r_bg_yp->addChild(chibang1,-1);

	chibang1->runAction(Sequence::create(DelayTime::create(0.5f),ToggleVisibility::create(),Spawn::create(ScaleTo::create(tx_time,1),RotateBy::create(tx_time,30),MoveBy::create(tx_time,Vec2(70,20)),nullptr),nullptr));

	//翅膀2
	sprintf(tmp_char,"Rankchibang%d.png",i);
	auto chibang2 =  Sprite:: createWithSpriteFrameName(tmp_char);
	chibang2->setFlippedX(true);
	chibang2->setScale(0.8);
	chibang2->setRotation(30);
	chibang2->setVisible(false);
	chibang2->setPosition(Vec2(r_bg_yp->getContentSize().width/2 ,r_bg_yp->getContentSize().height * 0.5));
	r_bg_yp->addChild(chibang2,-1);

	chibang2->runAction(Sequence::create(DelayTime::create(0.5f),ToggleVisibility::create(),Spawn::create(ScaleTo::create(tx_time,1),RotateBy::create(tx_time,-30),MoveBy::create(tx_time,Vec2(-70,20)),nullptr),nullptr));

	//蝴蝶结
	auto hudiejie =  Sprite:: createWithSpriteFrameName("Rankredsidai.png");
	hudiejie->setScale(0.0001);
	hudiejie->setVisible(false);
	hudiejie->setPosition(Vec2(r_bg_yp->getContentSize().width/2 ,r_bg_yp->getContentSize().height * 0.1));
	r_bg_yp->addChild(hudiejie,5);

	hudiejie->runAction(Sequence::create(DelayTime::create(0.5f),ToggleVisibility::create(),ScaleTo::create(tx_time,1),nullptr));

	//最后的光
	sprintf(tmp_char,"Match_xguang_%d.png",i);
	auto zuihoudguang =  Sprite:: createWithSpriteFrameName(tmp_char);
	zuihoudguang->setAnchorPoint(Vec2(0.5,1));
	zuihoudguang->setScale(0.1);
	zuihoudguang->setVisible(false);
	zuihoudguang->setOpacity(120);
	zuihoudguang->setPosition(Vec2(r_bg_yp->getContentSize().width/2 ,r_bg_yp->getContentSize().height * 0.3));
	r_bg_yp->addChild(zuihoudguang,10);

	zuihoudguang->runAction(Sequence::create(DelayTime::create(0.5f),ToggleVisibility::create(),ScaleTo::create(tx_time,1),nullptr));
	//1字
	sprintf(tmp_char,"Ranknum%d.png",i);
	auto dijiming =  Sprite:: createWithSpriteFrameName(tmp_char);
	dijiming->setScale(3);
	dijiming->setOpacity(0);
	dijiming->setPosition(Vec2(r_bg_yp->getContentSize().width/2 ,r_bg_yp->getContentSize().height * 0.8));
	r_bg_yp->addChild(dijiming,4);

	dijiming->runAction(Sequence::create(DelayTime::create(0.1f),FadeIn::create(0.1f),ScaleTo::create(0.1f,1),nullptr));

	//五星
	sprintf(tmp_char,"Rankstar%d.png",i);
	auto wujiaoxing =  Sprite:: createWithSpriteFrameName(tmp_char);
	wujiaoxing->setScale(3);
	wujiaoxing->setOpacity(0);
	wujiaoxing->setPosition(Vec2(r_bg_yp->getContentSize().width/2 ,r_bg_yp->getContentSize().height * 0.3));
	r_bg_yp->addChild(wujiaoxing,6);

	float tmp_scale = 0.7;
	if(i == 2)
		tmp_scale = 1;
	if(i == 3)
		tmp_scale = 1.55;
	wujiaoxing->runAction(Sequence::create(DelayTime::create(0.2f),FadeIn::create(0.1f),ScaleTo::create(0.1f,tmp_scale),nullptr));

	//星星1
	//sprintf(tmp_char,"Ranklight%d.png",i);
	auto xingxing1 =  Sprite:: createWithSpriteFrameName("RankMoney.png");
	xingxing1->setScale(0.8);
	xingxing1->setVisible(false);
	xingxing1->setPosition(Vec2(r_bg->getContentSize().width/2 ,r_bg->getContentSize().height * 0.92));
	r_bg->addChild(xingxing1,9);

	xingxing1->runAction(Sequence::create(DelayTime::create(0.5f),ToggleVisibility::create(),ScaleTo::create(tx_time,1),nullptr));
	//星星2
    //jywsb
	/*auto xingxing2 =  Sprite:: createWithSpriteFrameName("rewardstar2.png");
	xingxing2->setScale(0.8);
	xingxing2->setVisible(false);
	xingxing2->setPosition(Vec2(r_bg->getContentSize().width/2 ,r_bg->getContentSize().height * 0.8));
	r_bg->addChild(xingxing2,20);

	xingxing2->runAction(Sequence::create(DelayTime::create(0.5f),ToggleVisibility::create(),ScaleTo::create(tx_time,2),nullptr));

	//星星3
	auto xingxing3 =  Sprite:: createWithSpriteFrameName("rewardstar1.png");
	xingxing3->setScale(0.8);
	xingxing3->setVisible(false);
	xingxing3->setPosition(Vec2(r_bg->getContentSize().width/2 ,r_bg->getContentSize().height * 0.8));
	r_bg->addChild(xingxing3,20);

	xingxing3->runAction(Sequence::create(DelayTime::create(0.5f),ToggleVisibility::create(),ScaleTo::create(tx_time,1),nullptr));
*/
	//获得奖励title
	auto r_hd_bg =  Sprite:: createWithSpriteFrameName("rankfont1.png");
	r_hd_bg->setVisible(false);
	r_hd_bg->setPosition(Vec2(r_bg->getContentSize().width/2 - 20, r_bg->getContentSize().height * 0.55));
	r_bg->addChild(r_hd_bg,10);
 
	//第几名
	sprintf(tmp_char,"Ranknum%d.png",i);
	auto r_hd_mc =  Sprite:: createWithSpriteFrameName(tmp_char);
	r_hd_mc->setScale(0.3);
	r_hd_mc->setPosition(Vec2(r_hd_bg->getContentSize().width * 0.8 + 50, r_hd_bg->getContentSize().height * 0.5));
	r_hd_bg->addChild(r_hd_mc);

	r_hd_bg->runAction(Sequence::create(DelayTime::create(1.05f),ToggleVisibility::create(),nullptr));

	//获得奖励word
	/*auto r_hd_word =  Sprite:: createWithSpriteFrameName("rankreward.png");
	r_hd_word->setVisible(false);
	r_hd_word->setAnchorPoint(Vec2(0,0.5));
	r_hd_word->setPosition(Vec2(60 , r_bg->getContentSize().height * 0.4556));
	r_bg->addChild(r_hd_word,10);
 */
	//奖杯icon
/*	auto r_hd_jiangbei =  Sprite:: createWithSpriteFrameName("huafeiquan.png");
    r_hd_jiangbei->setScale(0.33);
	r_hd_jiangbei->setAnchorPoint(Vec2(0,0.5));
	r_hd_jiangbei->setPosition(Vec2(0 , -40));
//	r_hd_word->addChild(r_hd_jiangbei,10);
*/
	//奖杯数值
    sprintf(tmp_char,"%d",MatchOverhuafeiquan);
	auto r_hd_jb_n = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
	r_hd_jb_n->setAnchorPoint(Vec2(0,0.5));
	r_hd_jb_n->setString(tmp_char);
	r_hd_jb_n->setScale(0.7);
	r_hd_jb_n->setPosition(Vec2(50 , -40));
//	r_hd_word->addChild(r_hd_jb_n);
    
    if( UserDefault::getInstance()->getIntegerForKey("ios_dengluFlag") == 1 )
    {
   //     r_hd_jiangbei->setVisible(false);
        r_hd_jb_n->setVisible(false);
    }

	//钻石icon
	auto r_hd_zs =  Sprite:: createWithSpriteFrameName("diamond.png");
	r_hd_zs->setAnchorPoint(Vec2(0,0.5));
	r_hd_zs->setScale(0.7);
    r_hd_zs->setVisible(false);
	r_hd_zs->setPosition(Vec2(75 , r_bg->getContentSize().height/2 - 70));
	r_bg->addChild(r_hd_zs,10);

	//钻石数值
	sprintf(tmp_char,"%d",MatchOverZuanShi);
	auto r_hd_zs_n = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
	r_hd_zs_n->setAnchorPoint(Vec2(0,0.5));
	r_hd_zs_n->setString(tmp_char);
	r_hd_zs_n->setScale(0.7);
    r_hd_zs_n->setVisible(false);
	r_hd_zs_n->setPosition(Vec2(150, r_bg->getContentSize().height/2 - 70));
	r_bg->addChild(r_hd_zs_n);

	//金币icon
	auto r_hd_jinbi =  Sprite:: createWithSpriteFrameName("yubi.png");
	r_hd_jinbi->setScale(0.7);
	r_hd_jinbi->setAnchorPoint(Vec2(0,0.5));
    r_hd_jinbi->setVisible(false);
	r_hd_jinbi->setPosition(Vec2(75 ,r_bg->getContentSize().height/2 - 120));
	r_bg->addChild(r_hd_jinbi,10);

	//金币数值
	sprintf(tmp_char,"%d",MatchOverMoney);
	auto r_hd_jinbi_n = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
	r_hd_jinbi_n->setString(tmp_char);
    r_hd_jinbi_n->setVisible(false);
	r_hd_jinbi_n->setAnchorPoint(Vec2(0,0.5));
	r_hd_jinbi_n->setScale(0.75);
	r_hd_jinbi_n->setPosition(Vec2(125,r_bg->getContentSize().height/2 - 120));
	r_bg->addChild(r_hd_jinbi_n);

//	r_hd_word->runAction(Sequence::create(DelayTime::create(1.05f),ToggleVisibility::create(),nullptr));
    r_hd_jinbi_n->runAction(Sequence::create(DelayTime::create(1.05f),ToggleVisibility::create(),nullptr));
    r_hd_jinbi->runAction(Sequence::create(DelayTime::create(1.05f),ToggleVisibility::create(),nullptr));
    r_hd_zs_n->runAction(Sequence::create(DelayTime::create(1.05f),ToggleVisibility::create(),nullptr));
    r_hd_zs->runAction(Sequence::create(DelayTime::create(1.05f),ToggleVisibility::create(),nullptr));


	//炫耀按钮
	auto xuanyao = Sprite:: createWithSpriteFrameName("Match_fanhui.png");
	auto xuanyao_item = MenuItemSprite::create(xuanyao,xuanyao,CC_CALLBACK_0(CannonLayer::Match_xuanyao,this));
	auto xuanyao_menu = Menu::create(xuanyao_item,nullptr);
	xuanyao_menu->setVisible(false);
	xuanyao_menu->setPosition(Vec2(r_bg->getContentSize().width/2,55));
	r_bg->addChild(xuanyao_menu);
 
	xuanyao_menu->runAction(Sequence::create(DelayTime::create(1.5f),ToggleVisibility::create(),nullptr));

	//exit按钮
	auto exit_sp = Sprite:: createWithSpriteFrameName("hall_menu_X.png");
	auto exit_sp_d = Sprite:: createWithSpriteFrameName("hall_menu_X_d.png");
	auto exit_item = MenuItemSprite::create(exit_sp,exit_sp_d,CC_CALLBACK_0(CannonLayer::Match_exit,this));
	auto exit_menu = Menu::create(exit_item,nullptr);
	exit_menu->setPosition(Vec2(r_bg->getContentSize().width - 10,r_bg->getContentSize().height * 0.892));
	r_bg->addChild(exit_menu,10);
    
    this->scheduleOnce(schedule_selector(CannonLayer::jieping),1.6f);
}

void CannonLayer::jieping(float dt)
{
    utils::captureScreen(CC_CALLBACK_2(CannonLayer::afterCaptured,this),"bisaiGongxi.png");
}

void CannonLayer::Match_rank()
{
	char tmp_char[50];
	//背景
	auto r_bg =  Sprite:: createWithSpriteFrameName("rewardbg1.png");
	r_bg->setPosition(Vec2(visibleSize.width/2 , visibleSize.height * 0.5));
	r_bg->setScale(0.01);
	this->addChild(r_bg,MENULAYER+15,666);
 
    
	//获得奖励title
	auto r_hd_bg =  Sprite:: createWithSpriteFrameName("rank.png");
	r_hd_bg->setPosition(Vec2(r_bg->getContentSize().width/2 -  r_hd_bg->getContentSize().width *0.1f, r_bg->getContentSize().height * 0.79));
	r_bg->addChild(r_hd_bg,10);
 
    sprintf(tmp_char,"i%d.png",iRank);
    auto label = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
    label->setAnchorPoint(Vec2(0,0.5f));
    label->setString(tmp_char);
   // label->setScale(1.2);
    label->setPosition(Vec2(r_hd_bg->getContentSize().width * 0.7f, r_hd_bg->getContentSize().height * 0.5 - 5));
    r_hd_bg->addChild(label);
    
	 	//获得奖励word
/*	auto r_hd_word =  Sprite:: createWithSpriteFrameName("rankfont2.png");
	r_hd_word->setPosition(Vec2(r_bg->getContentSize().width/2 , r_bg->getContentSize().height * 0.587));
	r_bg->addChild(r_hd_word,10);
 */
	//奖杯icon
	auto r_hd_jiangbei =  Sprite:: createWithSpriteFrameName("diamond.png");
	r_hd_jiangbei->setPosition(Vec2(r_bg->getContentSize().width*0.3f , r_bg->getContentSize().height * 0.55f));
	r_bg->addChild(r_hd_jiangbei,10);

	//奖杯数值
	sprintf(tmp_char,"%d",MatchOverZuanShi);
	auto r_hd_jb_n = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
	r_hd_jb_n->setAnchorPoint(Vec2(0,0.5));
	r_hd_jb_n->setString(tmp_char);
	r_hd_jb_n->setScale(0.6);
	r_hd_jb_n->setPosition(Vec2(50,r_hd_jiangbei->getContentSize().height/2));
	r_hd_jiangbei->addChild(r_hd_jb_n);

	//钻石icon
	auto r_hd_zs =  Sprite:: createWithSpriteFrameName("diamond.png");
	r_hd_zs->setAnchorPoint(Vec2(0,0.5));
	r_hd_zs->setScale(0.7);
	r_hd_zs->setVisible(false);
	r_hd_zs->setPosition(Vec2(110 , r_hd_jiangbei->getContentSize().height/2));
	r_hd_jiangbei->addChild(r_hd_zs,10);

	//钻石数值
	sprintf(tmp_char,"%d",MatchOverZuanShi);
	auto r_hd_zs_n = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
	r_hd_zs_n->setAnchorPoint(Vec2(0,0.5));
	r_hd_zs_n->setString(tmp_char);
	r_hd_zs_n->setScale(0.6);
	r_hd_zs_n->setVisible(false);
	r_hd_zs_n->setPosition(Vec2(150,r_hd_jiangbei->getContentSize().height/2));
	r_hd_jiangbei->addChild(r_hd_zs_n);

	//金币icon
	auto r_hd_jinbi =  Sprite:: createWithSpriteFrameName("yubi.png");
	r_hd_jinbi->setScale(0.7);
	r_hd_jinbi->setPosition(Vec2(r_bg->getContentSize().width*0.3f , r_bg->getContentSize().height * 0.45f));
	r_bg->addChild(r_hd_jinbi,10);

	//金币数值
	sprintf(tmp_char,"%d",MatchOverMoney);
	auto r_hd_jinbi_n = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
	r_hd_jinbi_n->setString(tmp_char);
	r_hd_jinbi_n->setAnchorPoint(Vec2(0,0.5));
	r_hd_jinbi_n->setScale(0.8);
	r_hd_jinbi_n->setPosition(Vec2(70,r_hd_jinbi->getContentSize().height/2));
	r_hd_jinbi->addChild(r_hd_jinbi_n);
 
    
   /* auto r_hd_jiangbei2 =  Sprite:: createWithSpriteFrameName("huafeiquan.png");
    r_hd_jiangbei2->setScale(0.33);
    r_hd_jiangbei2->setAnchorPoint(Vec2(0,0.5));
    r_hd_jiangbei2->setPosition(Vec2(-10 , -145));
  //  r_hd_word->addChild(r_hd_jiangbei2,10);
    */
    //奖杯数值
    sprintf(tmp_char,"%d",MatchOverhuafeiquan);
    auto r_hd_jb_n2 = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
    r_hd_jb_n2->setAnchorPoint(Vec2(0,0.5));
    r_hd_jb_n2->setString(tmp_char);
    r_hd_jb_n2->setScale(0.7);
    r_hd_jb_n2->setPosition(Vec2(40 , -145));
 //   r_hd_word->addChild(r_hd_jb_n2);
    
    
    
	//炫耀按钮
	auto xuanyao = Sprite:: createWithSpriteFrameName("XR_qd.png");
    
    MenuItemSprite* xuanyao_item ;
  
    if(iMoneyJiangchi > 9999)
    {
        xuanyao_item = MenuItemSprite::create(xuanyao,xuanyao,CC_CALLBACK_0(CannonLayer::tishizuanpan,this));
    }
    else
    {
        xuanyao_item = MenuItemSprite::create(xuanyao,xuanyao,CC_CALLBACK_0(CannonLayer::Match_exit,this));
    }
	 
	auto xuanyao_menu = Menu::create(xuanyao_item,nullptr);
	xuanyao_menu->setPosition(Vec2(r_bg->getContentSize().width/2,55));
	r_bg->addChild(xuanyao_menu);
 
	//exit按钮
	auto exit_sp = Sprite:: createWithSpriteFrameName("hall_menu_X.png");
	auto exit_sp_d = Sprite:: createWithSpriteFrameName("hall_menu_X_d.png");
    
    MenuItemSprite* exit_item ;
 
    if(iMoneyJiangchi > 9999)
    {
       exit_item = MenuItemSprite::create(exit_sp,exit_sp_d,CC_CALLBACK_0(CannonLayer::tishizuanpan,this));
    }
    else
    {
        exit_item = MenuItemSprite::create(exit_sp,exit_sp_d,CC_CALLBACK_0(CannonLayer::Match_exit,this));
    }
    
	 
	auto exit_menu = Menu::create(exit_item,nullptr);
	exit_menu->setPosition(Vec2(r_bg->getContentSize().width - 10,r_bg->getContentSize().height * 0.892));
	r_bg->addChild(exit_menu,10);
    
    r_bg->runAction(ScaleTo::create(0.15f,1));
    
   
    
    
}


void CannonLayer::tishizuanpan()
{
    
    this->getChildByTag(666)->setVisible(false);
    auto gongxi =Gongxi::create(8,GAME_DATA_STRING("zuanpanwf"));
    gongxi->setPosition(Point::ZERO);
    this->addChild(gongxi,1020,1003);
    
    
    auto quedingSprite =  Sprite::createWithSpriteFrameName("XR_qd.png");
    auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(CannonLayer::jinruzuanpan,this));
    auto btnMenu = Menu::create(quedingItem,nullptr);
    btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
    gongxi->getChildByTag(1)->addChild(btnMenu,100);
    
    auto tuichuSprite =  Sprite::createWithSpriteFrameName("hall_menu_X.png");
    auto xquedingItem = MenuItemSprite::create(tuichuSprite,tuichuSprite,tuichuSprite,CC_CALLBACK_0(CannonLayer::jinruzuanpan,this));
    
    auto xbtnMenu = Menu::create(xquedingItem,nullptr);
    xbtnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2 + 200,0.95*gongxi->getChildByTag(1)->getContentSize().height));
    gongxi->getChildByTag(1)->addChild(xbtnMenu,100);
}
void CannonLayer::jinruzuanpan()
{
    this->removeChildByTag(1003);
    auto zhuanpan = ZuanPan::create(iMoneyJiangchi);
    zhuanpan->setPosition(Point::ZERO);
    this->addChild(zhuanpan,MENULAYER);
    
    
    
}
void CannonLayer::Match_exit()
{

   // bFanHuiDating = true;
    
	this->getParent()->stopAllActions();
	this->getParent()->unscheduleAllSelectors();
	this->getParent()->removeAllChildrenWithCleanup(true);
    
    GameBegin::removeSouce(3);
 
	auto scene = GameHallLayer::createScene();
	Director::getInstance()->replaceScene(scene);
    
}
 
void CannonLayer::Match_xuanyao()
{
    this->getParent()->stopAllActions();
    this->getParent()->unscheduleAllSelectors();
    this->getParent()->removeAllChildrenWithCleanup(true);
    
    GameBegin::removeSouce(3);
    
    auto scene = GameHallLayer::createScene();
    Director::getInstance()->replaceScene(scene);
     

}

void CannonLayer::afterCaptured(bool succeed, const std::string& outputFile)
{
    if (succeed)
    {

    }
    else
    {
        log("Capture screen failed.");
    }
}