#include "GameBegin.h"
#include "CannonUpgrade.h"
#include "cocos-ext.h"
#include "GameHallLayer.h"
#include "GameData.h"
#include "Gongxi.h"
#include "shop.h"
#include "LoadRes.h"

USING_NS_CC;
USING_NS_CC_EXT;

Label *CannonUpgrade::yubiLabel=nullptr;
Label *CannonUpgrade::zuanshiLabel=nullptr;

Scene * CannonUpgrade::createScene()
{
	auto scene = Scene::create();
	auto layer = CannonUpgrade::create();
	scene->addChild(layer);

	return scene;
}

bool CannonUpgrade::init()
{  	
	isScope = true;
	
	visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();

	laserLv =GameBegin::getFileData("typeFanWei.txt");
	scopeLv =GameBegin::getFileData("typeJiGuang.txt"); 

	char timeText [30];
	for(int i = 1 ; i <= 5 ;i++)
	{
		sprintf(timeText,"fwp_time_%d",i);
		scopeChijiu[i-1] = GAME_DATA_INT(timeText);

		memset(timeText,0,sizeof(timeText));
		sprintf(timeText,"fwp_fanwei_%d",i);
		scopeFanwei[i-1] = GAME_DATA_INT(timeText);

		memset(timeText,0,sizeof(timeText));
		sprintf(timeText,"fwp_weili_%d",i);
		scopeWeili[i-1] = GAME_DATA_INT(timeText);

		memset(timeText,0,sizeof(timeText));
		sprintf(timeText,"jgp_time_%d",i);
		laserChijiu[i-1] = GAME_DATA_INT(timeText);

		memset(timeText,0,sizeof(timeText));
		sprintf(timeText,"fwp_fanwei_%d",i);
		laserFanwei[i-1] = GAME_DATA_INT(timeText);

		memset(timeText,0,sizeof(timeText));
		sprintf(timeText,"fwp_weili_%d",i);
		laserWeili[i-1] = GAME_DATA_INT(timeText);
	}
	memset(timeText,0,sizeof(timeText));
	sprintf(timeText,"fwp_zuanshi_%d",scopeLv+1);

	needDiamond  = GAME_DATA_INT(timeText);//升级所需钻石

	needLevel  = scopeLv + 3;//升级所需玩家等级
	scopetemplevel = scopeLv<5?scopeLv+1:5;//初始化等级

	string shuoming1 = GAME_DATA_STRING("can_shuoming_1");
	string shuoming2 = GAME_DATA_STRING("can_shuoming_2");
	string shuoming3 = GAME_DATA_STRING("can_shuoming_3");
	string shuoming4 = GAME_DATA_STRING("can_shuoming_4");


	//背景
	auto cannonUpgradeBg = Sprite::create("hall_BG.png");

	cannonUpgradeBg->setPosition(Point(winSize.width/2,winSize.height/2));
	this->addChild(cannonUpgradeBg); 

	auto topBg = Sprite::createWithSpriteFrameName("hall_db_bg.png");
	//topBg->setScale(0.85);
	topBg->setAnchorPoint(Point(0.5,1));
	topBg->setPosition(Point(visibleSize.width/2,visibleSize.height));
	this->addChild(topBg,100);

	auto cannonTitle = Sprite::createWithSpriteFrameName("dapao_title.png");
	cannonTitle->setPosition(Point(topBg->getContentSize().width/2,topBg->getContentSize().height/2 + 10));
	topBg->addChild(cannonTitle,100);

	auto exitSprite = Sprite::createWithSpriteFrameName("cannon_exit.png");
	auto exitSprite1 = Sprite::createWithSpriteFrameName("cannon_exit_down.png");
	//exitSprite->setScale(0.8f);
	auto exitBtn = Menu::create(MenuItemSprite::create(exitSprite,exitSprite1,exitSprite,CC_CALLBACK_0(CannonUpgrade::exit,this)),nullptr);
	exitBtn->setPosition(Point(visibleSize.width - 50,visibleSize.height - 50));
	this->addChild(exitBtn,100);

	//炮系列bg
	auto CannonBG = Sprite::createWithSpriteFrameName("model_bgg.png");
	CannonBG->setPosition(Point(visibleSize.width/2,visibleSize.height*0.74));
	this->addChild(CannonBG,9);
	///CannonBG->setScale(GameBegin::scaleYNum);

	//炮系列
	auto scopeCannon = Sprite::createWithSpriteFrameName("scopemodel.png");
	auto scopeCannonItem = MenuItemSprite::create(scopeCannon,scopeCannon,scopeCannon,CC_CALLBACK_0(CannonUpgrade::scopeCannonSwitch,this));
	scopeCannonItem->setPosition(Point(-120*GameBegin::scaleYNum ,0));
	scopeCannonItem->setAnchorPoint(Point(0.5 ,0));
	scopeCannonItem->setScale(GameBegin::scaleYNum);

	auto laserCannon = Sprite::createWithSpriteFrameName("lasermodel.png");
	auto laserCannonItem = MenuItemSprite::create(laserCannon,laserCannon,laserCannon,CC_CALLBACK_0(CannonUpgrade::laserCannonSwitch,this));
	laserCannonItem->setPosition(Point(120*GameBegin::scaleYNum, 0));
	laserCannonItem->setAnchorPoint(Point(0.5 ,0));
	laserCannonItem->setScale(GameBegin::scaleYNum);


	auto CannonMenu = Menu::create(scopeCannonItem,laserCannonItem,nullptr);
	CannonMenu->setAnchorPoint(Point(0.5,0));
	CannonMenu->setPosition(Point(visibleSize.width/2,visibleSize.height*0.66));
	this->addChild(CannonMenu,100);

	scopeStyle = Sprite::createWithSpriteFrameName("scopestyle.png");
	scopeStyle->setAnchorPoint(Point(1,0));
	scopeStyle->setPosition(Point(visibleSize.width/2 - (scopeCannonItem->getContentSize().width)*GameBegin::scaleYNum + 10,0.725*visibleSize.height));
	scopeStyle->setScale(GameBegin::scaleYNum);
	this->addChild(scopeStyle,10);

	laserStyle = Sprite::createWithSpriteFrameName("laserstyle.png");
	laserStyle->setAnchorPoint(Point(0,1));
	laserStyle->setPosition(Point(visibleSize.width/2 + laserCannonItem->getContentSize().width*GameBegin::scaleYNum - 10,0.8*visibleSize.height));
	laserStyle->setScale(GameBegin::scaleYNum);
	laserStyle->setVisible(false);
	this->addChild(laserStyle,10);
 
	//炮升级
	scopeUpgradeBg = Scale9Sprite::createWithSpriteFrameName("kuang_1.png", CCRectMake(109,109,20,20));
	scopeUpgradeBg->setContentSize(Size(764,300));
	//scopeUpgradeBg->setScale(GameBegin::scaleYNum);
	//scopeUpgradeBg->setScaleX(GameHallLayer::scaleXNum);
	scopeUpgradeBg->setPosition(Point(visibleSize.width/2,0.65*visibleSize.height));
	scopeUpgradeBg->setAnchorPoint(Point(0.5,1));
	this->addChild(scopeUpgradeBg);


	//边沿亮点
	auto leftLight = Sprite::createWithSpriteFrameName("bglight.png");
	leftLight->setPosition(Point(scopeUpgradeBg->getContentSize().width/2,scopeUpgradeBg->getContentSize().height));
	leftLight->setAnchorPoint(Point(1,0.5));
	scopeUpgradeBg->addChild(leftLight,100);

	auto rightLight = Sprite::createWithSpriteFrameName("bglight.png");
	rightLight->setRotation(180);
	rightLight->setPosition(Point(scopeUpgradeBg->getContentSize().width/2,scopeUpgradeBg->getContentSize().height));
	rightLight->setAnchorPoint(Point(1,0.5));
	rightLight->setFlippedY(true);
	scopeUpgradeBg->addChild(rightLight,100);

	scopeLevelBg = Sprite::createWithSpriteFrameName("scopebg.png");
	scopeLevelBg->setAnchorPoint(Point(0,0));
	scopeLevelBg->setPosition(Point(30,215));
	scopeUpgradeBg->addChild(scopeLevelBg,100);

	
	char sclTemp[30];
	sprintf(sclTemp,"gold%d.png",scopetemplevel);
	scopeCannonLevel = Sprite::createWithSpriteFrameName(sclTemp);
	scopeCannonLevel->setAnchorPoint(Point(0.5,0));
	scopeCannonLevel->setPosition(Point(250,7));
	scopeLevelBg->addChild(scopeCannonLevel);

	//升级共享精灵
	char tempCannonName[30];
	for(int i = 4; i >=0 ; i--)
	{
		sprintf(tempCannonName,"exp_lv%d.png",i);
		auto cannonLevelBg = Scale9Sprite::createWithSpriteFrameName(tempCannonName);
		cannonLevelBg->setContentSize(Size(58,38));
		MenuItemSprite * cannonLevelMenuItem= MenuItemSprite::create(cannonLevelBg,cannonLevelBg,cannonLevelBg,CC_CALLBACK_1(CannonUpgrade::cannonLevelSelect,this));
		cannonLevelMenuItem->setTag(i); 
		auto cannonLevelMenu = Menu::create(cannonLevelMenuItem,nullptr);
		cannonLevelMenu->setPosition(Point(72 + i*94,180));
		scopeUpgradeBg->addChild(cannonLevelMenu,1);
		memset(tempCannonName,0,sizeof(tempCannonName));

		auto cannonLevelLight = Sprite::createWithSpriteFrameName("shineframe.png");
		cannonLevelLight->setPosition(Point(72 + i*94,192));
		cannonLevelLight->setVisible(false);
		scopeUpgradeBg->addChild(cannonLevelLight,1);

		light_Tree.pushBack(cannonLevelLight);

		sprintf(tempCannonName,"level%d.png",i+1);
		auto cannonLevel1Num = Sprite::createWithSpriteFrameName(tempCannonName);
		cannonLevel1Num->setPosition(Point(72 + i*94,180));
		scopeUpgradeBg->addChild(cannonLevel1Num,1);
		memset(tempCannonName,0,sizeof(tempCannonName));

		if(i >0)
		{
			auto evolution = Sprite::createWithSpriteFrameName("evolution.png");
			evolution->setAnchorPoint(Point(0,0.5));
			evolution->setPosition(Point(6 + i*94,180));
			evolution->setScaleY(0.5);
			evolution->setScaleX(0.7);
			scopeUpgradeBg->addChild(evolution,1);
		}
	}
	shineFrameSwitch(scopetemplevel);

	//数值标签显示
	auto chijiuWordLable = LabelTTF::create(shuoming1,"minijianling.ttf",18);
	chijiuWordLable->setPosition(Point(27,scopeUpgradeBg->getContentSize().height*0.37));
	chijiuWordLable->setAnchorPoint(Point(0,0.5));
	scopeUpgradeBg->addChild(chijiuWordLable,100);

	auto fanweiWordLable = LabelTTF::create(shuoming2,"minijianling.ttf",18);
	fanweiWordLable->setPosition(Point(scopeUpgradeBg->getContentSize().width*0.38,scopeUpgradeBg->getContentSize().height*0.37));
	fanweiWordLable->setAnchorPoint(Point(0,0.5));
	scopeUpgradeBg->addChild(fanweiWordLable,100);

	auto weiliWordLable = LabelTTF::create(shuoming3,"minijianling.ttf",18);
	weiliWordLable->setPosition(Point(27,scopeUpgradeBg->getContentSize().height*0.19));
	weiliWordLable->setAnchorPoint(Point(0,0.5));
	scopeUpgradeBg->addChild(weiliWordLable,100);

	jinengLabel = LabelTTF::create(shuoming4,"minijianling.ttf",18);
	jinengLabel->setPosition(Point(scopeUpgradeBg->getContentSize().width*0.35,scopeUpgradeBg->getContentSize().height*0.19));
	jinengLabel->setAnchorPoint(Point(0,0.5));
	scopeUpgradeBg->addChild(jinengLabel,100);
	if(scopetemplevel < 5)
	{
		jinengLabel->setVisible(false);
	}
	

	

	//比例条
	float sliderScale = (float)scopeChijiu[scopetemplevel-1]/scopeChijiu[4];
	chijiuSlider = ControlSlider::create("exp1.png","exptiao1.png","img/33.png");
	chijiuSlider->setValue(100);
	chijiuSlider->setEnabled(false);
	chijiuSlider->setPosition(Point(scopeUpgradeBg->getContentSize().width*0.22,scopeUpgradeBg->getContentSize().height*0.37));
	chijiuSlider->setAnchorPoint(Point(0,0.5));
    chijiuSlider->setScale(0.8f);
	scopeUpgradeBg->addChild(chijiuSlider,100);

	sliderScale = (float)scopeFanwei[scopetemplevel-1]/scopeFanwei[4];
	fanweiSlider = ControlSlider::create("exp1.png","exptiao1.png","img/33.png");
	fanweiSlider->setValue(sliderScale);
	fanweiSlider->setEnabled(false);
	fanweiSlider->setPosition(Point(scopeUpgradeBg->getContentSize().width*0.47,scopeUpgradeBg->getContentSize().height*0.37));
	fanweiSlider->setAnchorPoint(Point(0,0.5));
    fanweiSlider->setScale(0.8f);
	scopeUpgradeBg->addChild(fanweiSlider,100);

	sliderScale = (float)scopeWeili[scopetemplevel-1]/scopeWeili[4];
	weiliSlider = ControlSlider::create("exp1.png","exptiao1.png","img/33.png");
	weiliSlider->setValue(sliderScale);
	weiliSlider->setEnabled(false);
	weiliSlider->setPosition(Point(scopeUpgradeBg->getContentSize().width*0.22,scopeUpgradeBg->getContentSize().height*0.19));
	weiliSlider->setAnchorPoint(Point(0,0.5));
    weiliSlider->setScale(0.8f);
	scopeUpgradeBg->addChild(weiliSlider,100);


	//数值
	memset(sclTemp,0,sizeof(sclTemp));
	sprintf(sclTemp,"%d",scopeChijiu[scopetemplevel-1]);
	chijiuLabel = LabelTTF::create(sclTemp,"minijianling.ttf",18);
	chijiuLabel->setPosition(Point(chijiuSlider->getContentSize().width*0.5,chijiuSlider->getContentSize().height*0.5));
	chijiuLabel->setAnchorPoint(Point(0,0.5));
	chijiuSlider->addChild(chijiuLabel,101);

	memset(sclTemp,0,sizeof(sclTemp));
	sprintf(sclTemp,"%d",scopeFanwei[scopetemplevel-1]);
	fanweiLabel = LabelTTF::create(sclTemp,"minijianling.ttf",18);
	fanweiLabel->setPosition(Point(fanweiSlider->getContentSize().width*0.5,fanweiSlider->getContentSize().height*0.5));
	fanweiLabel->setAnchorPoint(Point(0,0.5));
	fanweiSlider->addChild(fanweiLabel,101);

	memset(sclTemp,0,sizeof(sclTemp));
	sprintf(sclTemp,"%d",scopeWeili[scopetemplevel-1]);
	weiliLabel = LabelTTF::create(sclTemp,"minijianling.ttf",18);
	weiliLabel->setPosition(Point(weiliSlider->getContentSize().width*0.5,weiliSlider->getContentSize().height*0.5));
	weiliLabel->setAnchorPoint(Point(0,0.5));
	weiliSlider->addChild(weiliLabel,101);




	//炮模型显示背景
	auto cannonModelBg = Scale9Sprite::createWithSpriteFrameName("kuang_4.png" , CCRectMake(38,38,8,8));
	cannonModelBg->setContentSize(Size(225,240));
	cannonModelBg->setAnchorPoint(Point(1,0.5));
	cannonModelBg->setPosition(Point(scopeUpgradeBg->getContentSize().width-30,scopeUpgradeBg->getContentSize().height/2+10));
	scopeUpgradeBg->addChild(cannonModelBg,100);

	//炮模型
	if(scopeLv==1)
	{
		cannonModel = Sprite::createWithSpriteFrameName("scope1.png");
	}
	if(scopeLv==2||scopeLv==3)
	{
		cannonModel = Sprite::createWithSpriteFrameName("scope2.png");
	}
	if(scopeLv==4||scopeLv==5)
	{
		cannonModel = Sprite::createWithSpriteFrameName("scope3.png");
	}
	cannonModel->setPosition(Point(cannonModelBg->getContentSize().width/2,cannonModelBg->getContentSize().height/2));
	cannonModelBg->addChild(cannonModel,100);

	//底座
	auto bottomBg = Sprite::createWithSpriteFrameName("hall_dibu_bg.png");
	bottomBg->setPosition(Point(visibleSize.width/2,0));
	bottomBg->setAnchorPoint(Point(0.5,0));
	bottomBg->setScale(0.85);
	this->addChild(bottomBg);

	auto hall_db_yb_bg1 = Sprite::createWithSpriteFrameName("hall_jia_kuang_1.png");
	auto hall_db_yb_bg2 = Sprite::createWithSpriteFrameName("hall_jia_kuang_2.png");
	MenuItemSprite * hall_db_yb_bg = MenuItemSprite::create(hall_db_yb_bg1,hall_db_yb_bg2,CC_CALLBACK_0(CannonUpgrade::quedingShop,this));

	//鱼币icon
	auto hall_db_yb_icon = Sprite::createWithSpriteFrameName("yubi.png");
	hall_db_yb_icon->setScale(0.8);
	hall_db_yb_icon->setPosition(Vec2(hall_db_yb_bg->getContentSize().width * 0.083,hall_db_yb_bg->getContentSize().height * 0.5));
	hall_db_yb_bg->addChild(hall_db_yb_icon);

	//鱼币数量label
	char cTemp[30];
	yubiLabel = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
	sprintf(cTemp,"%d",GameBegin::getFileData("jywer.txt"));
	yubiLabel->setString(cTemp);
	yubiLabel->setScale(0.56);
	yubiLabel->setPosition(Point(hall_db_yb_bg->getContentSize().width/2,hall_db_yb_bg->getContentSize().height/2));
	hall_db_yb_bg->addChild(yubiLabel);

	//钻石数值背景
	auto hall_db_zs_bg1 = Sprite::createWithSpriteFrameName("hall_jia_kuang_1.png");
	auto hall_db_zs_bg2 = Sprite::createWithSpriteFrameName("hall_jia_kuang_2.png");
	MenuItemSprite * hall_db_zs_bg = MenuItemSprite::create(hall_db_zs_bg1,hall_db_zs_bg2,CC_CALLBACK_0(CannonUpgrade::quedingShop,this));
	
	//钻石icon
	auto hall_db_zs_icon = Sprite::createWithSpriteFrameName("diamond.png");
	hall_db_zs_icon->setScale(0.8);
	hall_db_zs_icon->setPosition(Vec2(hall_db_zs_bg->getContentSize().width * 0.083,hall_db_zs_bg->getContentSize().height * 0.5));
	hall_db_zs_bg->addChild(hall_db_zs_icon);

	//钻石数量label
	zuanshiLabel = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
	zuanshiLabel->setScale(0.56);
	sprintf(cTemp,"%d",GameBegin::getFileData("jywopl.txt"));
	zuanshiLabel->setString(cTemp);
	zuanshiLabel->setPosition(Point(hall_db_zs_bg->getContentSize().width/2,hall_db_zs_bg->getContentSize().height/2));
	hall_db_zs_bg->addChild(zuanshiLabel);

	auto hall_db_menu = Menu::create(hall_db_yb_bg,hall_db_zs_bg,nullptr);
	hall_db_menu->alignItemsHorizontallyWithPadding(20);
	hall_db_menu->setPosition(Vec2(bottomBg->getContentSize().width*0.365,bottomBg->getContentSize().height * 0.5  - 5));
	bottomBg->addChild(hall_db_menu);  
 



	auto upgradeBtn = Sprite::createWithSpriteFrameName("shengji_anniu.png");
	upgradeBtnMenu = Menu::create(MenuItemSprite::create(upgradeBtn,upgradeBtn,upgradeBtn,CC_CALLBACK_1(CannonUpgrade::upgradeCannon,this)),nullptr);
	upgradeBtnMenu->setPosition(Point(bottomBg->getContentSize().width*0.77,bottomBg->getContentSize().height/2  - 5));
	bottomBg->addChild(upgradeBtnMenu,100);
 
	zuanshiUpgrade = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
	sprintf(cTemp,"%d",needDiamond);
	zuanshiUpgrade->setString(cTemp);
	zuanshiUpgrade->setPosition(Point(bottomBg->getContentSize().width*0.77+20,bottomBg->getContentSize().height/2  - 5));
	zuanshiUpgrade->setScale(0.56);
	bottomBg->addChild(zuanshiUpgrade,101);

	if(needDiamond)
	{
		
	}
	else
	{
		upgradeBtnMenu->setVisible(false);
		zuanshiUpgrade->setVisible(false);
	}

	EventListenerKeyboard* kblsnr = EventListenerKeyboard::create(); 
	kblsnr->onKeyReleased = CC_CALLBACK_2(CannonUpgrade::onKeyReleased, this); 
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(kblsnr, this); 


    return true;
}

void CannonUpgrade::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) 
{    
	switch(keyCode)     
	{     
		//监听返回键        
	case EventKeyboard::KeyCode::KEY_ESCAPE:     
		{
			GameBegin::buttonSound(); 
 
			auto scene = GameHallLayer::createScene();
			Director::getInstance()->replaceScene(scene);

		}
		break;        
		//监听menu键   
	case EventKeyboard::KeyCode::KEY_MENU:   
		break;   
	}
}
 
void CannonUpgrade::scopeCannonSwitch()
{
	GameBegin::buttonSound(); 

	isScope = true;

	//更换成范围炮
	SpriteFrame * tmp1 = SpriteFrameCache::getInstance()->spriteFrameByName("scopebg.png");
	scopeLevelBg->setDisplayFrame(tmp1);

	change(scopeLv + 1);
}

void CannonUpgrade::laserCannonSwitch()
{
	GameBegin::buttonSound(); 

	isScope = false;

	//更换成激光炮
	SpriteFrame * tmp1 = SpriteFrameCache::getInstance()->spriteFrameByName("laserbg.png");
	scopeLevelBg->setDisplayFrame(tmp1);

	char sclTemp[30];

	change(laserLv + 1);
}

void CannonUpgrade::shineFrameSwitch(int level)
{
	if (!light_Tree.empty()) 
		{
			int temp =1; 
			for(auto sp1 : light_Tree)
			{   
				Sprite * sprite = sp1;
				sp1->setVisible(false);
				if(temp + level == 6)
				{
					sp1->setVisible(true);
				}
				temp++;
			}	
		}
}

String CannonUpgrade::getCannonLevelName(int level)
{
	string fileName ;
	switch(level)
	{
	case 1:return "goldD.png";
	case 2:return "goldC.png";
	case 3:return "goldB.png";
	case 4:return "goldA.png";
	case 5:return "goldS.png";
	default:return "";
	}
}

void CannonUpgrade::exit()
{
	GameBegin::buttonSound(); 
 
	auto scene = GameHallLayer::createScene();
	Director::getInstance()->replaceScene(scene);
}


//升级大炮操作
void CannonUpgrade::upgradeCannon(Ref * sender)
{
	GameBegin::buttonSound(); 

	if(needLevel > GameBegin::getFileData("gamePlayerlv.txt"))
	{
		char level[40];
		sprintf(level,GAME_DATA_STRING("gamehall_level_low"),needLevel);
		auto gongxi = Gongxi::create(3,level);
		gongxi->setPosition(Point::ZERO);
		this->addChild(gongxi,1000);

		auto quedingSprite = Scale9Sprite::createWithSpriteFrameName("XR_qd.png");
        auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(CannonUpgrade::shengjilv,this));
        
        auto btnMenu = Menu::create(quedingItem,nullptr);
        btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
        gongxi->getChildByTag(1)->addChild(btnMenu,100);

		return;
	}
	if(GameBegin::getFileData("jywopl.txt")<needDiamond)
	{
		auto gongxi = Gongxi::create(3,GAME_DATA_STRING("gamehall_zuanshi_low"));
		gongxi->setPosition(Point::ZERO);
		this->addChild(gongxi,1000,1000);

		auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png" );
		auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(CannonUpgrade::quedingShop,this));
 
		auto btnMenu = Menu::create(quedingItem,nullptr);
		btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
		gongxi->getChildByTag(1)->addChild(btnMenu,100);
		return;
	}
	
	quedingShengji();
}

//去商城
void CannonUpgrade::shengjilv()
{
    GameBegin::buttonSound();
    this->removeChildByTag(1000);

	GameHallLayer::initRoom();

    char sceneLowRateTmp[20];
    sprintf(sceneLowRateTmp,"boss_low_odd_%d",GameHallLayer::RoomType + 1);
    char sceneHighRateTmp[20];
    sprintf(sceneHighRateTmp,"boss_high_%d",GameHallLayer::RoomType + 1);
    GameHallLayer::sceneLowPao = GAME_DATA_INT(sceneLowRateTmp);
    GameHallLayer::sceneHighPao = GAME_DATA_INT(sceneHighRateTmp);
    
    this->removeAllChildrenWithCleanup(true);
    this->unscheduleAllSelectors();
    
	LoadRes::RoomType = GameHallLayer:: RoomType;
	auto scene = LoadRes::createScene();	
	Director::getInstance()->replaceScene(scene);  
}

void CannonUpgrade::quedingShop()
{
	GameBegin::buttonSound(); 
	this->removeChildByTag(1000);

	auto scene = Shop::create(3);
	this->addChild(scene,100);
}

void CannonUpgrade::quedingShengji()
{

	this->removeChildByTag(1000);
	GameBegin::playSound("jiesuo.mp3");
 
	auto gongxi = Gongxi::create(1,GAME_DATA_STRING("gamehall_jiesuo_chenggong"));
	gongxi->setPosition(Point::ZERO);
	this->addChild(gongxi,1000);

	if(isScope)
	{
		scopeLv = needLevel - 2;  
		GameBegin::setFileData("typeJiGuang",scopeLv);
		int tmpZuanshi = GameBegin::getFileData("jywopl.txt") - needDiamond;
		GameBegin::setFileData("jywopl.txt",tmpZuanshi);

		char temp[30];
		sprintf(temp,"%d",tmpZuanshi);
		zuanshiLabel->setString(temp);
		scopeCannonSwitch();
	}
	else
	{
		laserLv = needLevel - 3;
		 GameBegin::setFileData("typeFanWei",laserLv);
		int tmpZuanshi = GameBegin::getFileData("jywopl.txt") - needDiamond;
		GameBegin::setFileData("jywopl.txt",tmpZuanshi);

		char temp[30];
		sprintf(temp,"%d",tmpZuanshi);
		zuanshiLabel->setString(temp);

		laserCannonSwitch();
	}

}

void CannonUpgrade::change(int level)
{
	level = level<6?level:5;

	if(level<5)
	{
		jinengLabel->setVisible(false);
	}
	if(level == 5)
	{
		jinengLabel->setVisible(true);
	}

	char sclTemp[30];
	sprintf(sclTemp,"gold%d.png",level);
	SpriteFrame * tmp2 = SpriteFrameCache::getInstance()->spriteFrameByName(sclTemp);
	scopeCannonLevel->setDisplayFrame(tmp2);


	//等级亮背景
	shineFrameSwitch(level);

	if(isScope)
	{
		scopeStyle->setVisible(true);
		laserStyle->setVisible(false);

		//更新数值
		memset(sclTemp,0,sizeof(sclTemp));
		sprintf(sclTemp,"%d",scopeChijiu[level-1]);
		chijiuLabel->setString(sclTemp);

		float sclScale = (float)scopeChijiu[level-1]/scopeChijiu[4];
		chijiuSlider->setValue(sclScale);

		memset(sclTemp,0,sizeof(sclTemp));
		sprintf(sclTemp,"%d",scopeFanwei[level-1]);
		fanweiLabel->setString(sclTemp);

		sclScale = (float)scopeFanwei[level-1]/scopeFanwei[4];
		fanweiSlider->setValue(sclScale);

		memset(sclTemp,0,sizeof(sclTemp));
		sprintf(sclTemp,"%d",scopeWeili[level-1]);
		weiliLabel->setString(sclTemp);

		sclScale = (float)scopeWeili[level-1]/scopeWeili[4];
		weiliSlider->setValue(sclScale);


		//更换显示模型
		if(level==1||level==2)
		{
			SpriteFrame * tmp3 = SpriteFrameCache::getInstance()->spriteFrameByName("scope1.png");
			cannonModel->setDisplayFrame(tmp3);
		}
		if(level==3||level==4)
		{
			SpriteFrame * tmp3 = SpriteFrameCache::getInstance()->spriteFrameByName("scope2.png");
			cannonModel->setDisplayFrame(tmp3);
		}
		if(level==5)
		{
			SpriteFrame * tmp3 = SpriteFrameCache::getInstance()->spriteFrameByName("scope3.png");
			cannonModel->setDisplayFrame(tmp3);
		}

		if(level > scopeLv)
		{
			
			upgradeBtnMenu->setVisible(true);
			zuanshiUpgrade->setVisible(true);
			char zuanshiTmp[20];
			needDiamond = 0;
			needLevel = scopeLv + 2;
			for(int i =  scopeLv ; i< level ; i++)
			{
				sprintf(zuanshiTmp,"fwp_zuanshi_%d",i + 1 );
				needDiamond += GAME_DATA_INT(zuanshiTmp);
				needLevel++;
			}
			memset(zuanshiTmp,0,sizeof(zuanshiTmp));
			sprintf(zuanshiTmp,"%d",needDiamond);
			zuanshiUpgrade->setString(zuanshiTmp);

		}
		else
		{
			
			upgradeBtnMenu->setVisible(false);
			zuanshiUpgrade->setVisible(false);
		}
	}
	else
	{
		scopeStyle->setVisible(false);
		laserStyle->setVisible(true);

		//更新数值
		memset(sclTemp,0,sizeof(sclTemp));
		sprintf(sclTemp,"%d",laserChijiu[level-1]);
		chijiuLabel->setString(sclTemp);

		float sclScale = (float)laserChijiu[level-1]/laserChijiu[4];
		chijiuSlider->setValue(sclScale);

		memset(sclTemp,0,sizeof(sclTemp));
		sprintf(sclTemp,"%d",laserFanwei[level-1]);
		fanweiLabel->setString(sclTemp);

		sclScale = (float)laserFanwei[level-1]/laserFanwei[4];
		fanweiSlider->setValue(sclScale);

		memset(sclTemp,0,sizeof(sclTemp));
		sprintf(sclTemp,"%d",laserWeili[level-1]);
		weiliLabel->setString(sclTemp);

		sclScale = (float)laserWeili[level-1]/laserWeili[4];
		weiliSlider->setValue(sclScale);


		//更换显示模型
		if(level==1||level==2)
		{
			SpriteFrame * tmp3 = SpriteFrameCache::getInstance()->spriteFrameByName("laser1.png");
			cannonModel->setDisplayFrame(tmp3);
		}
		if(level==3||level==4)
		{
			SpriteFrame * tmp3 = SpriteFrameCache::getInstance()->spriteFrameByName("laser2.png");
			cannonModel->setDisplayFrame(tmp3);
		}
		if(level==5)
		{
			SpriteFrame * tmp3 = SpriteFrameCache::getInstance()->spriteFrameByName("laser3.png");
			cannonModel->setDisplayFrame(tmp3);
		}

		if(level > laserLv)
		{
			
			upgradeBtnMenu->setVisible(true);
			zuanshiUpgrade->setVisible(true);
			char zuanshiTmp[20];
			needDiamond = 0;
			needLevel = laserLv + 3;
			for(int i = laserLv ; i< level ; i++)
			{
				sprintf(zuanshiTmp,"fwp_zuanshi_%d",i + 1 );
				needDiamond += GAME_DATA_INT(zuanshiTmp);
				needLevel++;
			}
			memset(zuanshiTmp,0,sizeof(zuanshiTmp));
			sprintf(zuanshiTmp,"%d",needDiamond);
			zuanshiUpgrade->setString(zuanshiTmp);
		}
		else
		{
		
			upgradeBtnMenu->setVisible(false);
			zuanshiUpgrade->setVisible(false);
		}
	}
	
	
}

void CannonUpgrade::cannonLevelSelect(Ref * sender)
{
	GameBegin::buttonSound(); 

	MenuItemSprite * tempSprItem = (MenuItemSprite *)sender;
	int selectLevel = tempSprItem->getTag()+1;

	change(selectLevel);
}

//**************公用的函数
//更新鱼币
void CannonUpgrade::RefreshCoin(int coinNum)
{
	int tmpMonty = GameBegin::getFileData("jywer.txt") + coinNum;

	char tmpCoinNum[40];
	sprintf(tmpCoinNum,"%d",tmpMonty);
	yubiLabel->setString(tmpCoinNum);  

	GameBegin::setFileData("jywer.txt",tmpMonty); 
}

//更新钻石
void CannonUpgrade::RefreshDiamond(int diamondNum)
{
	int tmpMonty = GameBegin::getFileData("jywopl.txt") + diamondNum;

	char tmpCoinNum[40];
	sprintf(tmpCoinNum,"%d",tmpMonty);
	zuanshiLabel->setString(tmpCoinNum);  

	GameBegin::setFileData("jywopl.txt",tmpMonty); 
}
