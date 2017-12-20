#include "GameHallLayer.h" 
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CannonLayer.h"
#include "smShop.h"
#include "VIPgongxi.h"
#include "GameScene.h"
#include "GameTextIn.h"
#include "GameSet.h"
#include "GameBegin.h"
#include "GameHelp.h"
#include "ChallengeBOSS.h"
#include "SimpleAudioEngine.h"
#include "Gongxi.h"
#include "TiShi.h"
#include "LogoLayer.h"
#include "Shop.h"
#include "CannonUpgrade.h"
#include "LoginReward.h"
#include "UnLockLayer.h"
#include "GameData.h"
#include "LoadRes.h"
#include "GameEmail.h"
#include "HongBao.h"
#include "MatchPlayer.h"
#include "InitPlayer.h"
#include "ShopJJ.h"
#include "Game_Hall_Kefu1.h"

// add by zxf
#include "JNative/JNativeToJavaUtil.h"

#include <regex> 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
	#include <regex.h>  
#endif
#include <string.h>

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "../cocos2d/external/curl/include/ios/curl/curl.h"
#include <sys/stat.h> 
#include <unistd.h>
#include <dirent.h> 



#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 

#include "../cocos2d/external/curl/include/android/curl/curl.h"
#include <sys/stat.h> 
#include <unistd.h>
#include <dirent.h> 
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include "..\cocos2d\external\curl\include\win32\curl\curl.h"
#endif

USING_NS_CC;
 
bool GameHallLayer::gonggao_vis_flag = false;
bool GameHallLayer::isqiehuan = false;
bool GameHallLayer::exitIsCun = false;
bool GameHallLayer::failFlag = false;
bool GameHallLayer::isSaleVis = false;
bool GameHallLayer::checkRedPoing = true;
bool GameHallLayer::hall_bShengyinShow = true;
bool GameHallLayer::hall_hb_kaiguan = true;
bool GameHallLayer::is_bs_xianshi= false;
bool GameHallLayer::vip_goumai_flag = false;
bool GameHallLayer::isCheckBS = false;
int GameHallLayer::failInt = 0;
 
time_t GameHallLayer::hall_hb_time_t = 0;   //¿Îø™¥ÛÃ¸µƒ ±º‰
int GameHallLayer::hall_hb_times = 0;
int GameHallLayer::boss_fish_room = 0;

 
int GameHallLayer::RoomType = 0;
int GameHallLayer::sceneLowPao = 0;
int GameHallLayer::sceneHighPao = 0;
string GameHallLayer::wordKind = "minijianling.ttf"; 

Label *GameHallLayer::yubiLabel=nullptr;
Label *GameHallLayer::zuanshiLabel=nullptr;


int GameHallLayer::bs_moshi = 1;
int GameHallLayer::bs_RenShu[4] = {0};
int GameHallLayer::player_pos = 1;
int GameHallLayer::robot1[3] = {0};
int GameHallLayer::robot2[3] = {0};
int GameHallLayer::robot3[3] = {0};

//*****************   π§æﬂ∫Ø ˝  *****************************
string returnString(int tmp)
{
	char tmpTmpTmp[50];
	int miaoT = tmp%60;
	char miaoTT[5];
	if(miaoT < 10)
		sprintf(miaoTT,"0%d",miaoT);
	else
		sprintf(miaoTT,"%d",miaoT);

	int fenT = (tmp - miaoT)/60 % 60;
	char fenTT[5];
	if(fenT < 10)
		sprintf(fenTT,"0%d",fenT);
	else
		sprintf(fenTT,"%d",fenT);

	int shiT = tmp/3600;
	sprintf(tmpTmpTmp,"0%d:%s:%s",shiT,fenTT,miaoTT);
	return tmpTmpTmp;
}
 
//*****************   ∂“ªªª∞∑—≤„  *****************************
Scene* Game_Hall_Kefu::createScene()
{
	auto scene = Scene::create();
	auto layer = Game_Hall_Kefu::create();
	scene->addChild(layer);

	return scene;
}

bool Game_Hall_Kefu::init()
{
	if ( !Layer::init() )	
	{
		return false;
	}
 
	visibleSize = Director::getInstance()->getVisibleSize();//ªÒµ√ø… ”«¯”Úµƒ¥Û–°
	winSize = Director::getInstance()->getWinSize();
	Point origin = Director::getInstance()->getVisibleOrigin();//ªÒµ√ø… ”«¯”Úµƒ∆ º◊¯±Íori
 
	this->setScale(0.1f);
	ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.1f, 1.0f); 
	this->runAction(Sequence::create(ac7,ac8 ,nullptr) ); 

	//øÿ÷∆√Ê∞Â
	auto callBg = Sprite::create( "HF_bg.jpg");
	callBg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(callBg);

	//ÕÀ≥ˆ∞¥≈•
	auto boss_exit = Sprite::createWithSpriteFrameName("cannon_exit.png");
	auto boss_exit_d = Sprite::createWithSpriteFrameName("cannon_exit_down.png");
	auto boss_exit_menu = Menu::create(MenuItemSprite::create(boss_exit,boss_exit_d,CC_CALLBACK_0(Game_Hall_Kefu::exit,this)),nullptr);
	boss_exit_menu->setPosition(Vec2(visibleSize.width - 48,visibleSize.height -  46 ));
	this->addChild(boss_exit_menu);

	//title
	auto hf_dui_title = Sprite::createWithSpriteFrameName( "HF_dui_title.png");
	hf_dui_title->setPosition(Point(visibleSize.width/2,visibleSize.height * 0.9));
	hf_dui_title->setScale(0.85);
	this->addChild(hf_dui_title,100);

	//ªÒ»°ª∞∑—»Ø∞¥≈•
	//Ω±±≠ ˝¡ø
	auto hall_jb_sp1 = Sprite::createWithSpriteFrameName("hall_jb_k.png");
	auto hall_jb_sp2 = Sprite::createWithSpriteFrameName("hall_jb_kd.png");
	MenuItemSprite * hall_jb_item = MenuItemSprite::create(hall_jb_sp1,hall_jb_sp2,CC_CALLBACK_1(Game_Hall_Kefu::huodeHF,this));
	auto hall_jb_menu = Menu::create(hall_jb_item,nullptr);
	hall_jb_menu->setPosition(Vec2(visibleSize.width*0.5,30));
	addChild(hall_jb_menu);

	cocos2d::log("hallCharTemp 3" );
/*
	//Ω±±≠icon
	auto hall_jb_icon = Sprite::createWithSpriteFrameName("huafeiquan.png");
	hall_jb_icon->setScale(0.33);
	hall_jb_icon->setPosition(Vec2(hall_jb_item->getContentSize().width * 0.083,hall_jb_item->getContentSize().height * 0.52));
	hall_jb_item->addChild(hall_jb_icon);
*/
	//Ω±±≠ ˝¡ølabel
	char hf_tmp[30];
	auto jiangbeiLayer = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
	sprintf(hf_tmp,"%d",GameBegin::getFileData("wfsound.txt"));
	jiangbeiLayer->setString(hf_tmp);
	jiangbeiLayer->setScale(0.55);
	jiangbeiLayer->setPosition(Point(hall_jb_item->getContentSize().width/2,hall_jb_item->getContentSize().height/2));
	hall_jb_item->addChild(jiangbeiLayer);

	cocos2d::log("hallCharTemp 4" );
    
    //免责声明
    auto mianze_label = LabelTTF::create(GAME_DATA_STRING("huafei_mianze"),"Arial",24);
    mianze_label->setPosition(Vec2(visibleSize.width*0.5,70));
    addChild(mianze_label);

	//ª¨∞Â
	yubiLayer = Layer::create();
	yubiLayer->setPosition(Point::ZERO);
	yubiLayer->setAnchorPoint(Point::ZERO);
	layer_x = 0;
	yubiLayer->setContentSize(Size(visibleSize.width,440));

	yubiView = ScrollView::create(Size(visibleSize.width,440),yubiLayer);
	yubiView->setDelegate(this);
	yubiView->ignoreAnchorPointForPosition(false);
	yubiView->setAnchorPoint(Vec2(0.5,0.5));
	yubiView->setDirection(ScrollView::Direction::HORIZONTAL);
	yubiView->setPosition(Point(visibleSize.width/2 + 1,visibleSize.height/2));
	this->addChild(yubiView,10);

	roomSize = Size(238,403);
	int spaceW = 85;

	float speed = 1500;
	float distans;

	char moneyTmp[30];
	for(int i = 0; i<3 ; i++)
	{
		sprintf(moneyTmp,"HF_dui_%d.png",i+1);
		auto yubiObg = Sprite::createWithSpriteFrameName(moneyTmp);
		yubiObg->setScale(0.9);
		yubiObg->setZOrder(9-i);
		yubiObg->setPosition(Point(yubiLayer->getContentSize().width * 1.5 ,yubiLayer->getContentSize().height/2 + 10));
		yubiLayer->addChild(yubiObg);
 
		sp_yubi.pushBack(yubiObg);  //yubiLayer->getContentSize().width/2 + (i-1) *  (roomSize.width + spaceW)
		distans = yubiLayer->getContentSize().width * 1.5 - (yubiLayer->getContentSize().width/2 + (i-1) *  (roomSize.width + spaceW));
		auto moveTo = MoveBy::create(distans/speed,Vec2(-distans,0));	
		auto moveBy = MoveBy::create(0.3f,Vec2(0,-10));
		yubiObg->runAction(Sequence::create(moveTo,CCCallFunc::create([&]{GameBegin::playSound("bs_fapai.mp3");}),moveBy,nullptr));
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Game_Hall_Kefu::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(Game_Hall_Kefu::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(Game_Hall_Kefu::onTouchEnded,this);
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}

void Game_Hall_Kefu::exit()
{
	GameBegin::buttonSound(); 

	ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
	this->runAction(Sequence::create(ac7,ac8,RemoveSelf::create(),nullptr) ); 
}

void Game_Hall_Kefu::duiHuaFei(int room)
{
	log("room = %d",room);

	int huafeiquan = GameBegin::getFileData("wfsound.txt");
 
	switch (room)
	{
	case 1:
            
		{
			if(huafeiquan < 1000)
			{
                
				auto tishi = Gongxi::create(3,GAME_DATA_STRING("huafei_2"));
				this->addChild(tishi,MENULAYER);

				auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png" );
				auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_1(Game_Hall_Kefu::huodeHF,this));
				auto btnMenu = Menu::create(quedingItem,nullptr);
				btnMenu->setPosition(Point(tishi->getChildByTag(1)->getContentSize().width/2,0.18*tishi->getChildByTag(1)->getContentSize().height));
				tishi->getChildByTag(1)->addChild(btnMenu,100);

				return;
			}
			
		};
        break;
	case 2:
		{
			if(huafeiquan < 2000)
			{
				auto tishi = Gongxi::create(3,GAME_DATA_STRING("huafei_2"));
				this->addChild(tishi,MENULAYER);

				auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png" );
				auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_1(Game_Hall_Kefu::huodeHF,this));
				auto btnMenu = Menu::create(quedingItem,nullptr);
				btnMenu->setPosition(Point(tishi->getChildByTag(1)->getContentSize().width/2,0.18*tishi->getChildByTag(1)->getContentSize().height));
				tishi->getChildByTag(1)->addChild(btnMenu,100);
				return;
			}

		};break;
	case 3:
		{
			if(huafeiquan < 3000)
			{
				auto tishi = Gongxi::create(3,GAME_DATA_STRING("huafei_2"));
				this->addChild(tishi,MENULAYER,999);

				auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png" );
				auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_1(Game_Hall_Kefu::huodeHF,this));
				auto btnMenu = Menu::create(quedingItem,nullptr);
				btnMenu->setPosition(Point(tishi->getChildByTag(1)->getContentSize().width/2,0.18*tishi->getChildByTag(1)->getContentSize().height));
				tishi->getChildByTag(1)->addChild(btnMenu,100);
				return;
			}
			
		};break;
	default:
		break;
	}
	exit();
	UserDefault::getInstance()->setIntegerForKey("huafei_kind",room);
	UserDefault::getInstance()->flush();
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(kCUSTEVENT_DHHF);
}

void Game_Hall_Kefu::huodeHF(Ref * psender)
{
	log("huode hua fei");
	this->removeChildByTag(999);
	exit();
	auto layer = Game_Hall_Kefu3::createScene();
	this->getParent()->addChild(layer,ANNIULAYER);
}

bool Game_Hall_Kefu::onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	p1 = touch->getLocation();

	if(p1.y < visibleSize.height/2 + roomSize.height/2 * kHF_SCALE_L && p1.y > visibleSize.height/2 - roomSize.height/2 * kHF_SCALE_L)
	{
		float yubiWidth =  yubiView->getViewSize().width;
		float room_x = p1.x -(visibleSize.width - yubiWidth)/2;

		if (room_x > 0 && room_x < yubiWidth)
		{
			room_x = room_x + layer_x;
			if(room_x >sp_yubi.at(0)->getPositionX() -  roomSize.width * kHF_SCALE_L/2 && room_x < sp_yubi.at(0)->getPositionX() + roomSize.width * kHF_SCALE_L/2)
			{
				cur_room = 1;
				sp_yubi.at(0)->setScale(kHF_SCALE_H);
			}

			if(room_x >sp_yubi.at(1)->getPositionX() -  roomSize.width * kHF_SCALE_L/2 && room_x < sp_yubi.at(1)->getPositionX() + roomSize.width * kHF_SCALE_L/2)
			{
				cur_room = 2;
				sp_yubi.at(1)->setScale(kHF_SCALE_H);
			}

			if(room_x >sp_yubi.at(2)->getPositionX() -  roomSize.width * kHF_SCALE_L/2 && room_x < sp_yubi.at(2)->getPositionX() + roomSize.width * kHF_SCALE_L/2)
			{
				cur_room = 3;
				sp_yubi.at(2)->setScale(kHF_SCALE_H);
			}
		}
	}

	return true;
}

void Game_Hall_Kefu::onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	
}
 
void Game_Hall_Kefu::onTouchEnded(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	p2 = touch->getLocation();
	cocos2d::log("offset pos is %f ",p2.x);  
	if(cur_room > 0 &&abs(p2.x - p1.x) < 8     )
	{
		duiHuaFei(cur_room);
	}
	if(cur_room > 0)
	{
		sp_yubi.at(cur_room - 1)->setScale(kHF_SCALE_L);
		cur_room = 0;
	}
	log("touchesEnded");
}
 
void Game_Hall_Kefu::scrollViewDidScroll(extension::ScrollView* view) 
{

	layer_x = abs(view->getContentOffset().x);//ªÒµ√∆´“∆X◊¯±Í(œÚ”““∆∂Ø£¨∆´“∆¡øŒ™’˝ ˝£¨œÚ◊Û‘ÚŒ™∏∫ ˝£©  
	cocos2d::log("offset pos is %f ",layer_x);  

}

void Game_Hall_Kefu::scrollViewDidZoom(extension::ScrollView* view) 
{
}

 
//*****************   ∫Ï∞¸≤„  *****************************
Scene* Game_Hall_Kefu2::createScene()
{
	auto scene = Scene::create();
	auto layer = Game_Hall_Kefu2::create();
	scene->addChild(layer);

	return scene;
}

bool Game_Hall_Kefu2::init()
{
	if ( !Layer::init() )	
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	Size winSize = Director::getInstance()->getWinSize();
 
	auto zheZhao = LayerColor::create(ccc4(0,0,0,150),1024,768);
	zheZhao->setPosition(Point::ZERO);
	zheZhao->setScale(2.0f);
	this->addChild(zheZhao,-1,991);
 
	
	//…˝º∂∞Â
	shopCenterBg = Scale9Sprite::createWithSpriteFrameName( "bs_kuang.png",CCRectMake(99,99,20,20));
	shopCenterBg->setContentSize(CCSizeMake(983,450));
	shopCenterBg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(shopCenterBg);
 
	auto shopCenterBg1 = Sprite::createWithSpriteFrameName("HB_title.png");
	shopCenterBg1->setPosition(Point(shopCenterBg->getContentSize().width/2,shopCenterBg->getContentSize().height));
	shopCenterBg->addChild(shopCenterBg1,100);
 
	auto shangchengxx = MenuItemSprite::create(Sprite::createWithSpriteFrameName("hall_menu_X.png"),Sprite::createWithSpriteFrameName("hall_menu_X_d.png"), CC_CALLBACK_0(Game_Hall_Kefu2::exit,this));	
	auto m_ShangChengXX= Menu::create(shangchengxx, nullptr);
	m_ShangChengXX->setPosition(Vec2(shopCenterBg->getContentSize().width - 10,shopCenterBg->getContentSize().height - 10));
	shopCenterBg->addChild(m_ShangChengXX,100);

	if(shopCenterBg)
	{
		shopCenterBg->setScale(0.1f);
		ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);  
		ScaleTo *ac8=ScaleTo::create(0.1f, 1.0);  
		shopCenterBg->runAction(Sequence::create(ac7,ac8,nullptr)); 
	}

	//ª¨∞Â
	yubiLayer = Layer::create();
	yubiLayer->setPosition(Point::ZERO);
	yubiLayer->setAnchorPoint(Point::ZERO);
	layer_x = 0;
	yubiLayer->setContentSize(Size(960,400));

	yubiView = ScrollView::create(Size(960,400),yubiLayer);
	yubiView->setDelegate(this);
	yubiView->ignoreAnchorPointForPosition(false);
	yubiView->setAnchorPoint(Vec2(0.5,0.5));
	yubiView->setDirection(ScrollView::Direction::HORIZONTAL);
	yubiView->setPosition(Vec2(shopCenterBg->getContentSize().width/2 + 1,shopCenterBg->getContentSize().height/2));
	shopCenterBg->addChild(yubiView,100);

	roomSize = Size(238,286);
	int spaceW = 80;

	float speed = 1500;
	float distans;
 
	char moneyTmp[30];
	for(int i = 0; i<3 ; i++)
	{
		//item π‚
		auto shop_diguang = Sprite::createWithSpriteFrameName("shop_diguang.png");
		shop_diguang->setAnchorPoint(Vec2(0.5,0));
		shop_diguang->setPosition(Vec2(shopCenterBg->getContentSize().width/2 - (i - 1) * (roomSize.width + spaceW) ,11));
		shopCenterBg->addChild(shop_diguang,100);

		sprintf(moneyTmp,"HB_item_%d.png",i+1);
		auto yubiObg = Sprite::createWithSpriteFrameName(moneyTmp);
		yubiObg->setZOrder(9-i);
		yubiObg->setPosition(Point(yubiLayer->getContentSize().width * 1.5,yubiLayer->getContentSize().height/2 + 10));
		yubiLayer->addChild(yubiObg);
 
		sp_yubi.pushBack(yubiObg);

		distans = yubiLayer->getContentSize().width * 1.5 - (yubiLayer->getContentSize().width/2 + (i-1) *  (roomSize.width + spaceW));
		auto moveTo = MoveBy::create(distans/speed,Vec2(-distans,0));	
		auto moveBy = MoveBy::create(0.3f,Vec2(0,-10));
		yubiObg->runAction(Sequence::create(moveTo,CCCallFunc::create([&]{GameBegin::playSound("bs_fapai.mp3");}),moveBy,nullptr));
	}
 
	daojishi_sp = Sprite::createWithSpriteFrameName("HB_daojishi_bg.png");
	daojishi_sp->setAnchorPoint(Vec2(0.5,1));
	daojishi_sp->setPosition(Vec2(roomSize.width/2 , roomSize.height - 10 ));
	sp_yubi.at(2)->addChild(daojishi_sp);

	daojishi_lb = LabelTTF::create("",GameHallLayer::wordKind,24);
	daojishi_lb->setPosition(Vec2(daojishi_sp->getContentSize().width * 0.7 , daojishi_sp->getContentSize().height / 2 ));
	daojishi_sp->addChild(daojishi_lb);
 
	if(GameHallLayer::hall_hb_times > 0)
	{
		//ø…º˚
		daojishi_is_vis = true;
		sprintf(tmpHonbao,"%s",returnString( GameHallLayer::hall_hb_times).c_str());
		daojishi_lb->setString(tmpHonbao);
		schedule(schedule_selector(Game_Hall_Kefu2::updateHB),1.0f);		
	}else
	{
		//≤ªø…º˚
		daojishi_is_vis = false;
		daojishi_sp->setVisible(false);
	}

	//∑÷œÌøÚ
	fenxiang_is_vis = false;
	fenxiang_tck_bg = Scale9Sprite::createWithSpriteFrameName( "bs_kuang.png",CCRectMake(99,99,20,20));
	fenxiang_tck_bg->setVisible(false);
	fenxiang_tck_bg->setScale(0.1f);
	fenxiang_tck_bg->setContentSize(CCSizeMake(560,350));
	fenxiang_tck_bg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(fenxiang_tck_bg,10);

	//∑÷œÌÕÀ≥ˆ
	auto fenxiangxx = MenuItemSprite::create(Sprite::createWithSpriteFrameName("hall_menu_X.png"),Sprite::createWithSpriteFrameName("hall_menu_X_d.png"), CC_CALLBACK_0(Game_Hall_Kefu2::fenxiang_tck_tc,this));	
	auto m_fenxiangXX= Menu::create(fenxiangxx, nullptr);
	m_fenxiangXX->setPosition(Vec2(fenxiang_tck_bg->getContentSize().width - 10,fenxiang_tck_bg->getContentSize().height - 10));
	fenxiang_tck_bg->addChild(m_fenxiangXX,100);

	//≤Àµ•
	auto fenxiang_item_1 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("HB_fenxiang_wx.png"),Sprite::createWithSpriteFrameName("HB_fenxiang_wx.png"), CC_CALLBACK_0(Game_Hall_Kefu2::fenxiang_tck_wx,this));
	auto fenxiang_item_2 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("HB_fenxiang_pyq.png"),Sprite::createWithSpriteFrameName("HB_fenxiang_pyq.png"), CC_CALLBACK_0(Game_Hall_Kefu2::fenxiang_tck_pyq,this));
	auto fenxiang_menu = Menu::create(fenxiang_item_1,fenxiang_item_2,nullptr);
	fenxiang_menu->alignItemsHorizontallyWithPadding(30);
	fenxiang_menu->setPosition(Vec2(fenxiang_tck_bg->getContentSize().width / 2,fenxiang_tck_bg->getContentSize().height * 0.4));
	fenxiang_tck_bg->addChild(fenxiang_menu,100);

	//ÃÌº”¥•√˛ ¬º˛
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Game_Hall_Kefu2::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(Game_Hall_Kefu2::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(Game_Hall_Kefu2::onTouchEnded,this);
	listener->setSwallowTouches(true);//≤ªœÚœ¬¥´µ›¥•√˛
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
	
	
	return true;
}

void Game_Hall_Kefu2::fenxiang_tck_tc()
{
	GameBegin::buttonSound(); 
	fenxiang_is_vis = false;

	ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
	fenxiang_tck_bg->runAction(Sequence::create(ac7,ac8,Hide::create(),nullptr)); 
 
}
void Game_Hall_Kefu2::fenxiang_tck_pyq()
{
    
	fenxiang_tck_tc();
    std::string ere = "Icon-180.png";
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(ere) ;

    
    
    if(UserDefault::getInstance()->getIntegerForKey("first_fenxiang") == 0)
    {
        UserDefault::getInstance()->setIntegerForKey("first_fenxiang",1);
         GameBegin::setFileData("jywer.txt" ,GameBegin::getFileData("jywer.txt")+5000);
        UserDefault::getInstance()->flush();
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(kCUSTEVENT_XGHFQ);
    }
}
 
void Game_Hall_Kefu2::fenxiang_tck_wx()
{
	fenxiang_tck_tc();
    std::string ere = "Icon-180.png";
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(ere) ;
    
     
    if(UserDefault::getInstance()->getIntegerForKey("first_fenxiang") == 0)
    {
        UserDefault::getInstance()->setIntegerForKey("first_fenxiang",1);
        GameBegin::setFileData("jywer.txt" ,GameBegin::getFileData("jywer.txt")+5000);
        
        UserDefault::getInstance()->flush();
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(kCUSTEVENT_XGHFQ);
    }
    
}

void Game_Hall_Kefu2::updateHB(float dt)
{
	if(GameHallLayer::hall_hb_times > 0)
	{
		sprintf(tmpHonbao,"%s",returnString(GameHallLayer::hall_hb_times).c_str());
		daojishi_lb->setString(tmpHonbao);
	}else
	{
		daojishi_sp->setVisible(false);
		daojishi_is_vis = false;
		this->unschedule(schedule_selector(GameHallLayer::updateHB));
	}
}

void Game_Hall_Kefu2::exit()
{
	GameBegin::buttonSound(); 
 
	ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
	shopCenterBg->runAction(Sequence::create(ac7,ac8,nullptr)); 

	this->runAction(Sequence::create(DelayTime::create(0.3f),RemoveSelf::create(),nullptr));
}

void Game_Hall_Kefu2::clickItem(int room)
{
    if(fenxiang_is_vis)
    {
        return;
    }
	log("room = %d",room);
	GameBegin::buttonSound();
	switch (room)
	{
	case 1:
		{
			duihongbao();
		}break;
	case 2:
		{
			fahongbao();
		}break;
	case 3:
		{
			if(daojishi_is_vis)
			{
				auto gongxi = Gongxi::create(2,GAME_DATA_STRING("hall_hb_time_low"));
				this->addChild(gongxi,MENULAYER);
			}else
			{
				qianghongbao();		 
			}
			
		}break;
	default:
		break;
	}
}

void Game_Hall_Kefu2::duihongbao()
{
	log("duihongbao");
 
	exit();

	GameTextIn::libaoInt = 1;
	auto gameHelp = GameTextIn::createScene();
	this->getParent()->addChild(gameHelp,MENULAYER + 100);
 
 
}
 
void Game_Hall_Kefu2::fahongbao()
{
 
	log("fahongbao"); 
	fenxiang_is_vis = true;

	ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.1f, 1.0);  
	fenxiang_tck_bg->runAction(Sequence::create(Show::create(),ac7,ac8,nullptr)); 
 
}

void Game_Hall_Kefu2::qianghongbao()
{
	log("qianghongbao");
 

	exit();
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(kCUSTEVENT_HB_JS);

	auto layer = HongBao::createScene();
	this->getParent()->addChild(layer,MENULAYER+100);
}

bool Game_Hall_Kefu2::onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	p1 = touch->getLocation();

	if(p1.y < visibleSize.height/2 + roomSize.height/2 * kHF_SCALE_HD_L && p1.y > visibleSize.height/2 - roomSize.height/2 * kHF_SCALE_HD_L)
	{
		float yubiWidth =  yubiView->getViewSize().width;
		float room_x = p1.x -(visibleSize.width - yubiWidth)/2;

		if (room_x > 0 && room_x < yubiWidth)
		{
			room_x = room_x + layer_x;
			if(room_x >sp_yubi.at(0)->getPositionX() -  roomSize.width * kHF_SCALE_HD_L/2 && room_x < sp_yubi.at(0)->getPositionX() + roomSize.width * kHF_SCALE_HD_L/2)
			{
				cur_room = 1;
				sp_yubi.at(0)->setScale(kHF_SCALE_HD_H);
			}

			if(room_x >sp_yubi.at(1)->getPositionX() -  roomSize.width * kHF_SCALE_HD_L/2 && room_x < sp_yubi.at(1)->getPositionX() + roomSize.width * kHF_SCALE_HD_L/2)
			{
				cur_room = 2;
				sp_yubi.at(1)->setScale(kHF_SCALE_HD_H);
			}

			if(room_x >sp_yubi.at(2)->getPositionX() -  roomSize.width * kHF_SCALE_HD_L/2 && room_x < sp_yubi.at(2)->getPositionX() + roomSize.width * kHF_SCALE_HD_L/2)
			{
				cur_room = 3;
				sp_yubi.at(2)->setScale(kHF_SCALE_HD_H);
			}
		}
	}

	return true;
}

void Game_Hall_Kefu2::onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	
}
 
void Game_Hall_Kefu2::onTouchEnded(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	p2 = touch->getLocation();
	cocos2d::log("offset pos is %f ",p2.x);  
	if(cur_room > 0 &&abs(p2.x - p1.x) < 8     )
	{
		clickItem(cur_room);
	}
	if(cur_room > 0)
	{
		sp_yubi.at(cur_room - 1)->setScale(kHF_SCALE_HD_L);
		cur_room = 0;
	}
	log("touchesEnded");
}
 
void Game_Hall_Kefu2::scrollViewDidScroll(extension::ScrollView* view) 
{

	layer_x = abs(view->getContentOffset().x);//ªÒµ√∆´“∆X◊¯±Í(œÚ”““∆∂Ø£¨∆´“∆¡øŒ™’˝ ˝£¨œÚ◊Û‘ÚŒ™∏∫ ˝£©  
	cocos2d::log("offset pos is %f ",layer_x);  

}

void Game_Hall_Kefu2  ::scrollViewDidZoom(extension::ScrollView* view) 
{
}
 
//*****************   ±»»¸œÍ«È≤„  *****************************
Scene* Game_BS_XiangQ::createScene()
{
	auto scene = Scene::create();
	auto layer = Game_BS_XiangQ::create();
	scene->addChild(layer);

	return scene;
}

bool Game_BS_XiangQ::init()
{
	if ( !Layer::init() )	
	{
		return false;
	}
 
	auto visibleSize = Director::getInstance()->getVisibleSize();//ªÒµ√ø… ”«¯”Úµƒ¥Û–°
	Point origin = Director::getInstance()->getVisibleOrigin();//ªÒµ√ø… ”«¯”Úµƒ∆ º◊¯±Íori
	yb_pos[0] = Vec2(200,165);yb_pos[1] = Vec2(200,137);yb_pos[2] = Vec2(200,109);yb_pos[3] = Vec2(200,79);
	zs_pos[0] = Vec2(295,165);zs_pos[1] = Vec2(295,137);zs_pos[2] = Vec2(295,109);zs_pos[3] = Vec2(295,79);

	auto zheZhao = LayerColor::create(ccc4(0,0,0,90),1024,768);
	zheZhao->setPosition(Point::ZERO);
	this->addChild(zheZhao);
 
	//øÿ÷∆√Ê∞Â
	callBg = Sprite::createWithSpriteFrameName( "BS_room_xq_bg.png");
	callBg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(callBg);

	callBg->setScale(0.1f);	 
	ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.1f, 1.0f); 
	callBg->runAction(Sequence::create(ac7,ac8 ,nullptr) ); 

	char tmp_bs_xq[50];
	// ˝÷µ
	for(int i = 0; i < 4 ;i++)
	{
			auto jinbiL = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
			sprintf(tmp_bs_xq,"bs_room_%d_jiangli_jb_%d",GameHallLayer::bs_moshi,i+4);
			jinbiL->setString(GAME_DATA_STRING(tmp_bs_xq));
			jinbiL->setScale(0.4);
			jinbiL->setPosition(yb_pos[i]);
			callBg->addChild(jinbiL);
   
			auto zuanshiL = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
			sprintf(tmp_bs_xq,"bs_room_%d_jiangli_zs_%d",GameHallLayer::bs_moshi,i+4);

			zuanshiL->setString(GAME_DATA_STRING(tmp_bs_xq));
			zuanshiL->setScale(0.35);
			zuanshiL->setPosition(zs_pos[i]);
			callBg->addChild(zuanshiL);
	}
 
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Game_BS_XiangQ::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(Game_BS_XiangQ::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(Game_BS_XiangQ::onTouchEnded,this);
	listener->setSwallowTouches(true);//≤ªœÚœ¬¥´µ›¥•√˛
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}

void Game_BS_XiangQ::exit()
{
	GameBegin::buttonSound(); 

	ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
	callBg->runAction(Sequence::create(ac7,ac8,RemoveSelf::create(),CallFunc::create([&]{this->removeFromParentAndCleanup(true);}),nullptr) ); 
}

bool Game_BS_XiangQ::onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	exit();
	return true;
}

void Game_BS_XiangQ::onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	
}
 
void Game_BS_XiangQ::onTouchEnded(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	log("touchesEnded");
}
 
//*****************   ¥ÛÃ¸≥°æ∞  *****************************
Scene* GameHallLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameHallLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void GameHallLayer::initRoom()
{
	
}
 
void GameHallLayer::initDingbu()
{
	hall_dingbu_bg = Sprite::createWithSpriteFrameName("hall_dbbg.png");
	hall_dingbu_bg->setScale(scaleTmp);
	hall_dingbu_bg->setPosition(Vec2(visibleSize.width/2 + origin.x,visibleSize.height + origin.y));
	hall_dingbu_bg->setAnchorPoint(Vec2(0.5,1));
	addChild(hall_dingbu_bg,ANNIULAYER + 10);

	isEditTx = false;
	//Õ∑œÒ—°‘Ò
	auto hall_touxiang_bg = Sprite::createWithSpriteFrameName("manquan.png");
	auto hall_menu_tx = Menu::create(MenuItemSprite::create(hall_touxiang_bg,hall_touxiang_bg,CC_CALLBACK_1(GameHallLayer::xzTouxiang,this)),nullptr);
	hall_menu_tx->setPosition(Vec2(hall_dingbu_bg->getContentSize().width*0.1,hall_dingbu_bg->getContentSize().height * 0.57));
	hall_dingbu_bg->addChild(hall_menu_tx,2);

	sprintf(hallCharTemp,"tou%d.png",UserDefault::getInstance()->getIntegerForKey("player_touxiang"));
	cocos2d::log("hallCharTemp = %s" ,hallCharTemp);
	auto touxiang = Sprite::createWithSpriteFrameName(hallCharTemp);
	touxiang->setScale(0.2518f);
	touxiang->setPosition(Vec2(hall_dingbu_bg->getContentSize().width*0.1,hall_dingbu_bg->getContentSize().height * 0.57));
	hall_dingbu_bg->addChild(touxiang);
 
	cocos2d::log("hallCharTemp 1");
	cocos2d::log("player_name = %s", UserDefault::getInstance()->getStringForKey("player_name").c_str());
	//√˚≥∆±‡º≠øÚ
	auto hall_name_bg = EditBox::create(Size(194,31),Scale9Sprite::createWithSpriteFrameName("hall_mz_k.png"),Scale9Sprite::createWithSpriteFrameName("hall_mz_kd.png"),nullptr);
	hall_name_bg->setPosition(Vec2(hall_dingbu_bg->getContentSize().width*0.335,hall_dingbu_bg->getContentSize().height * 0.76));
	hall_name_bg->setFont("minijianling.ttf", 20);
    hall_name_bg->setFontColor(Color3B::WHITE);
	hall_name_bg->setPlaceHolder(UserDefault::getInstance()->getStringForKey("player_name").c_str());
	hall_name_bg->setPlaceholderFontColor(Color3B::WHITE);
    hall_name_bg->setMaxLength(7);
	hall_name_bg->setEnabled(false);
	//hall_name_bg->setInputFlag(EditBox::InputFlag::SENSITIVE);
    hall_name_bg->setInputMode(EditBox::InputMode::SINGLE_LINE);
	hall_name_bg->setReturnType(EditBox::KeyboardReturnType::DONE);
    hall_name_bg->setDelegate(this);
    hall_dingbu_bg->addChild(hall_name_bg);
	cocos2d::log("hallCharTemp 2" );
    
    //话费券背景
	auto hall_jb_sp1 = Sprite::createWithSpriteFrameName("hall_jb_k.png");
	auto hall_jb_sp2 = Sprite::createWithSpriteFrameName("hall_jb_kd.png");
	MenuItemSprite * hall_jb_item = MenuItemSprite::create(hall_jb_sp1,hall_jb_sp2,CC_CALLBACK_1(GameHallLayer::hall_jiangbei_func,this));
	auto hall_jb_menu = Menu::create(hall_jb_item,nullptr);
	hall_jb_menu->setPosition(Vec2(hall_dingbu_bg->getContentSize().width*0.335,hall_dingbu_bg->getContentSize().height * 0.38));
	hall_dingbu_bg->addChild(hall_jb_menu);
 
    if( UserDefault::getInstance()->getIntegerForKey("ios_dengluFlag") == 1)
    {
        hall_jb_item->setVisible(false);
    }
        
	cocos2d::log("hallCharTemp 3" );

	/*//Ω±±≠icon
	auto hall_jb_icon = Sprite::createWithSpriteFrameName("huafeiquan.png");
	hall_jb_icon->setScale(0.33);
	hall_jb_icon->setPosition(Vec2(hall_jb_item->getContentSize().width * 0.083,hall_jb_item->getContentSize().height * 0.52));
	hall_jb_item->addChild(hall_jb_icon);

     */
	//Ω±±≠ ˝¡ølabel
	jiangbeiLayer = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
	sprintf(hallCharTemp,"%d",GameBegin::getFileData("wfsound.txt"));
	jiangbeiLayer->setString(hallCharTemp);
	jiangbeiLayer->setScale(0.55);
	jiangbeiLayer->setPosition(Point(hall_jb_item->getContentSize().width/2,hall_jb_item->getContentSize().height/2));
	hall_jb_item->addChild(jiangbeiLayer);

	cocos2d::log("hallCharTemp 4" );

	//”„±“ ˝÷µ±≥æ∞
	auto hall_db_yb_bg1 = Sprite::createWithSpriteFrameName("hall_jia_kuang_1.png");
	auto hall_db_yb_bg2 = Sprite::createWithSpriteFrameName("hall_jia_kuang_2.png");
	MenuItemSprite * hall_db_yb_bg = MenuItemSprite::create(hall_db_yb_bg1,hall_db_yb_bg2,CC_CALLBACK_1(GameHallLayer::hall_shangcheng_func1,this));

    //”„±“icon
	auto hall_db_yb_icon = Sprite::createWithSpriteFrameName("yubi.png");
	hall_db_yb_icon->setScale(0.8);
	hall_db_yb_icon->setPosition(Vec2(hall_db_yb_bg->getContentSize().width * 0.083,hall_db_yb_bg->getContentSize().height * 0.52));
	hall_db_yb_bg->addChild(hall_db_yb_icon);

				//”„±“ ˝¡ølabel
	yubiLabel = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
	sprintf(hallCharTemp,"%d",GameBegin::getFileData("jywer.txt"));
	yubiLabel->setString(hallCharTemp);
	yubiLabel->setScale(0.55);
	yubiLabel->setPosition(Point(hall_db_yb_bg->getContentSize().width/2,hall_db_yb_bg->getContentSize().height/2));
	hall_db_yb_bg->addChild(yubiLabel);

				//◊Í Ø ˝÷µ±≥æ∞
	auto hall_db_zs_bg1 = Sprite::createWithSpriteFrameName("hall_jia_kuang_1.png");
	auto hall_db_zs_bg2 = Sprite::createWithSpriteFrameName("hall_jia_kuang_2.png");
	MenuItemSprite * hall_db_zs_bg = MenuItemSprite::create(hall_db_zs_bg1,hall_db_zs_bg2,CC_CALLBACK_1(GameHallLayer::hall_shangcheng_func1,this));
				//◊Í Øicon
	auto hall_db_zs_icon = Sprite::createWithSpriteFrameName("diamond.png");
	hall_db_zs_icon->setScale(0.8);
	hall_db_zs_icon->setPosition(Vec2(hall_db_zs_bg->getContentSize().width * 0.083,hall_db_zs_bg->getContentSize().height * 0.52));
	hall_db_zs_bg->addChild(hall_db_zs_icon);

				//◊Í Ø ˝¡ølabel
	zuanshiLabel = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
	zuanshiLabel->setScale(0.55);
	sprintf(hallCharTemp,"%d",GameBegin::getFileData("jywopl.txt"));
	zuanshiLabel->setString(hallCharTemp);
	zuanshiLabel->setPosition(Point(hall_db_zs_bg->getContentSize().width/2,hall_db_zs_bg->getContentSize().height/2));
	hall_db_zs_bg->addChild(zuanshiLabel);

	auto hall_db_menu = Menu::create(hall_db_yb_bg,hall_db_zs_bg,nullptr);
	hall_db_menu->alignItemsVerticallyWithPadding(10);
	hall_db_menu->setPosition(Vec2(hall_dingbu_bg->getContentSize().width*0.733,hall_dingbu_bg->getContentSize().height * 0.55));
	hall_dingbu_bg->addChild(hall_db_menu);

	cocos2d::log("hallCharTemp 5" );
}

void GameHallLayer::editBoxReturn(EditBox *editBox)
{
	log("editBox %p was returned.", editBox->getText());
	UserDefault::getInstance()->setStringForKey("player_name",editBox->getText());
	UserDefault::getInstance()->flush();
}

void GameHallLayer::initCaiDan()
{
	//**********∂•≤ø
		//∂“ªªª∞∑—
	/*auto hall_sprite_kf = Sprite::createWithSpriteFrameName("HF_icon1.png");
	auto hall_sprite_kf1 = Sprite::createWithSpriteFrameName("HF_icon2.png");
	hall_sprite_kf->setScale(0.7);
	hall_sprite_kf1->setScale(0.71);
	hall_menu_kf = Menu::create(MenuItemSprite::create(hall_sprite_kf,hall_sprite_kf1,CC_CALLBACK_1(GameHallLayer::hall_kefu_func,this)),nullptr);
	hall_menu_kf->setPosition(Vec2( 65 + origin.x , 65 + origin.y));
	
	addChild(hall_menu_kf,ANNIULAYER,kHFIconTag);

    if( UserDefault::getInstance()->getIntegerForKey("ios_dengluFlag") == 1  || GameBegin :: cjingxipingbi == 1 )
    {
        hall_menu_kf->setVisible(false);
    }
        
	auto hall_hf_bgguang = Sprite::createWithSpriteFrameName("hall_ssxx_bg.png");
	hall_hf_bgguang->setScale(1.6f);
	hall_hf_bgguang->setPosition(Vec2(hall_sprite_kf->getContentSize()/2));
	auto  hf_ro = RotateBy::create(4.0f,360); 
	hall_hf_bgguang->runAction(RepeatForever::create(hf_ro)); 
	hall_sprite_kf->addChild(hall_hf_bgguang,-1); 


	float time_xq = 0.5f;
	//œÍ«È∞¥≈•
	auto jump1  = JumpBy::create(time_xq,Vec2::ZERO,30,1);
	auto jump2  = JumpBy::create(time_xq-0.2f,Vec2::ZERO,15,1);
	auto jump3  = JumpBy::create(time_xq-0.3f,Vec2::ZERO,5,1);

	hall_menu_kf->runAction(Repeat::create(Sequence::create(DelayTime::create(1.0f), 
		jump1,CallFunc::create([&]{GameBegin::playSound("bs_room_xiangq.mp3");}),
		jump2, 
		jump3, 
		nullptr),3));
    
    */
 
	//ÕÀ≥ˆ±»»¸ƒ£ Ω
	auto hall_sprite_bsT = Sprite::createWithSpriteFrameName("bs_anniu.png");
	hall_sprite_bsT->setScale(scaleTmp);
	hall_menu_bsT = Menu::create(MenuItemSprite::create(hall_sprite_bsT,hall_sprite_bsT,CC_CALLBACK_1(GameHallLayer::hall_bisaiT_func,this)),nullptr);
	hall_menu_bsT->setPosition(Vec2(60 + origin.x ,visibleSize.height - 50 + origin.y));
	hall_menu_bsT->setVisible(false);
	addChild(hall_menu_bsT,ANNIULAYER+1);

	//Ω¯»Î±»»¸ƒ£ Ω
	auto hall_sprite_bs = Sprite::createWithSpriteFrameName("hall_bisai.png");
	hall_sprite_bs->setScale(scaleTmp - 0.1);
	hall_menu_bs = Menu::create(MenuItemSprite::create(hall_sprite_bs,hall_sprite_bs,CC_CALLBACK_1(GameHallLayer::hall_bisai_func,this)),nullptr);
	hall_menu_bs->setPosition(Vec2( 60 + origin.x ,visibleSize.height - 50 + origin.y));
	addChild(hall_menu_bs,ANNIULAYER+1);

		//±»»¸±≥æ∞π‚
	auto hall_bs_sp = Sprite::createWithSpriteFrameName("bgguang.png");
	hall_bs_sp->setPosition(Vec2(hall_sprite_bs->getContentSize().width * 0.5,hall_sprite_bs->getContentSize().height*0.55));
	hall_sprite_bs->addChild(hall_bs_sp,-1);
	hall_bs_sp->runAction(RepeatForever::create(RotateBy::create(1.0f,8)));

		//Àµ√˜Œƒ◊÷
	auto hall_bs_sm = Sprite::createWithSpriteFrameName("hall_bisai_ms1.png");
	hall_menu_bs_tishi = Menu::create(MenuItemSprite::create(hall_bs_sm,hall_bs_sm,CC_CALLBACK_1(GameHallLayer::hall_bisai_func,this)),nullptr);
	hall_menu_bs_tishi->setPosition(Vec2(hall_sprite_bs->getContentSize().width * 2,hall_sprite_bs->getContentSize().height * 0.5));
	hall_sprite_bs->addChild(hall_menu_bs_tishi);
	hall_menu_bs_tishi->runAction(RepeatForever::create(Sequence::create(DelayTime::create(3.0f),FadeIn::create(0.5f),DelayTime::create(3.0f),FadeOut::create(0.5f),nullptr)));
 
		//«¿∫Ï∞¸∞¥≈•
	auto hall_sprite_hb = Sprite::createWithSpriteFrameName("HB_anniu.png");
	hall_sprite_hb->setScale(scaleTmp);
	hall_hb_anniu = Menu::create(MenuItemSprite::create(hall_sprite_hb,hall_sprite_hb,CC_CALLBACK_1(GameHallLayer::menuQianghongbao,this)),nullptr);
	hall_hb_anniu->setPosition(Vec2( 50 + origin.x ,visibleSize.height - 150 + origin.y));
	addChild(hall_hb_anniu,ANNIULAYER);
    
    
    
    auto hall_sprite_jiujisai = Sprite::createWithSpriteFrameName("helpme.png");
    hall_sprite_jiujisai->setScale(scaleTmp-0.1);
    hall_jiujisai_anniu = Menu::create(MenuItemSprite::create(hall_sprite_jiujisai,hall_sprite_jiujisai,CC_CALLBACK_1(GameHallLayer::menujiujisai,this)),nullptr);
	hall_jiujisai_anniu->setPosition(Vec2(visibleSize.width - 35 + origin.x, visibleSize.height - 150 + origin.y));
    addChild(hall_jiujisai_anniu,ANNIULAYER);
    
    
   /* if(UserDefault::getInstance()->getIntegerForKey("ios_dengluFlag") == 1)
    {
        hall_hb_anniu->setVisible(false);
    }*/
  

	hall_sp_hb_k = Sprite::createWithSpriteFrameName("HB_timek.png");
	hall_sp_hb_k->setPosition(Vec2(45 + origin.x ,visibleSize.height - 192 + origin.y));
	hall_sp_hb_k->setVisible(false);
	addChild(hall_sp_hb_k,ANNIULAYER);

	cocos2d::log("init caidan  hongbao ");

	//hall_hb_time_t = GameBegin::getFileData("hb_last_time.txt");
	//hall_hb_times =  GameBegin::getFileData("hb_times.txt");
    
    time_t hb_last_lq_time = GameBegin::getFileData("hb_last_lq_time.txt");
	 
    time_t wfwf;
    time(&wfwf);
    
    if(hb_last_lq_time == 0 || hb_last_lq_time + 2 * 3600 <  wfwf)////第一次进入游戏 或者 距离上次领取红包已经过了两小时  均可领取红包
    {
        hall_hb_times = 0;
    }else//否则显示计时器
    {
        hall_hb_times = 7200 - (wfwf - hb_last_lq_time);
        if(hall_hb_times < 0 || hall_hb_times > 7200)
        {
            hall_hb_times = 7200;
        }
    }
    
    /*time_t timetmp =  wfwf - 365*24*60*60*(2014 - 1970) + 28800  ;//因为之后用的是gmtime  所以这里加了8小时
    
    
	cocos2d::log("  hongbao hall_hb_time_t = %d ,hall_hb_times = %d",hall_hb_time_t,hall_hb_times);

	if(hall_hb_time_t == 0)
	{
		hall_hb_times = 0;		
		sprintf(hallCharTemp,"00:00:00");
	}else
	{
		int timeTmp1 = timetmp - hall_hb_time_t;
		if(timeTmp1 > hall_hb_times)
		{
			hall_hb_times = 0;		
			sprintf(hallCharTemp,"00:00:00");
		}else
		{
			hall_hb_times -= timeTmp1;		
			sprintf(hallCharTemp,"%s",returnString(hall_hb_times).c_str());
		}
	}
    */
	sprintf(hallCharTemp,"%s",returnString(hall_hb_times).c_str());
	hall_hb_time_l = Label::createWithSystemFont(hallCharTemp,"",14);
	hall_hb_time_l->setPosition(Vec2(hall_sp_hb_k->getContentSize()/2));
	hall_sp_hb_k->addChild(hall_hb_time_l);

	if(hall_hb_times == 0)
	{
		auto moveBy1 = MoveBy::create(0.5f,Vec2(0,10));
		auto movenBy2 = MoveBy::create(0.25f,Vec2(0,-5));
		auto movenBy3 = MoveBy::create(0.25f,Vec2(0,5));
		auto moveBy4 = MoveBy::create(0.5f,Vec2(0,-10));

		hall_hb_anniu->runAction(RepeatForever::create(Sequence::create(moveBy1,movenBy2,movenBy3,moveBy4,nullptr)));

		//GameBegin::setFileData("hb_last_time.txt",0);
		//GameBegin::setFileData("hb_times.txt",0);
	}
    this->schedule(schedule_selector(GameHallLayer::updateHB),1.0f);
	cocos2d::log("init caidan  hongbao end ");

    /*
	//“ª‘™¿Ò∞¸
	if(UserDefault::getInstance()->getIntegerForKey("yiyuangoumai")==0)
	{
		auto yiyuan_sp = Sprite::createWithSpriteFrameName("yiyuan_button.png");
		auto hall_yiyuan_anniu = Menu::create(MenuItemSprite::create(yiyuan_sp,yiyuan_sp,CC_CALLBACK_1(GameHallLayer::menu_yiyuan,this)),nullptr);
		hall_yiyuan_anniu->setPosition(Vec2(visibleSize.width - 150 + origin.x ,visibleSize.height - 68 + origin.y));
		addChild(hall_yiyuan_anniu,ANNIULAYER-10,611);
	} 
 */
	//vipÃÿ»®∞¥≈•
	if(UserDefault::getInstance()->getIntegerForKey("player_vip")==0)
	{
		hall_vip_sp = Sprite::createWithSpriteFrameName("Vip_icon.png");
	}else
	{
		hall_vip_sp = Sprite::createWithSpriteFrameName("Vip_icon1.png");
	}

	hall_vip_sp->setScale(scaleTmp - 0.1f);
	hall_vip_anniu = Menu::create(MenuItemSprite::create(hall_vip_sp, hall_vip_sp, CC_CALLBACK_1(GameHallLayer::menu_viptequan, this)), nullptr);
	hall_vip_anniu->setPosition(Vec2(visibleSize.width - 38 + origin.x, visibleSize.height - 50 + origin.y));
	addChild(hall_vip_anniu, ANNIULAYER - 10);

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (true) {
		auto sprite = Sprite::createWithSpriteFrameName("bgguang.png");
		sprite->setPosition(Vec2(47 + origin.x, visibleSize.height - 240 + origin.y));
		sprite->setScale(0.7);
		sprite->runAction(RepeatForever::create(RotateBy::create(1.0f, 8)));
		addChild(sprite);

		auto sprite_GoogleAds = Sprite::createWithSpriteFrameName("free.png");
		auto btn_GoogleAds = MenuItemSprite::create(sprite_GoogleAds, sprite_GoogleAds, CC_CALLBACK_1(GameHallLayer::showAds, this));
		btn_GoogleAds->setScale(0.6);
		auto menu_GoogleAds = Menu::create(btn_GoogleAds, NULL);
		menu_GoogleAds->setPosition(Vec2(47 + origin.x, visibleSize.height - 240 + origin.y));
		addChild(menu_GoogleAds);
	}
#endif

	//√ø»’Ãÿ»®
	time_t currentTime;
	time(&currentTime);
	time_t prevTime = UserDefault::getInstance()->getIntegerForKey("vip_login_time");
	if(UserDefault::getInstance()->getIntegerForKey("player_vip")!=0 && currentTime > prevTime + 24*60*60)
	{
		hall_vip_anniu->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f,Vec2(0,10)),MoveBy::create(0.25f,Vec2(0,-5)),MoveBy::create(0.25f,Vec2(0,5)),MoveBy::create(0.5f,Vec2(0,-10)),nullptr)));
	}
    if(UserDefault::getInstance()->getIntegerForKey("ios_dengluFlag") == 1)
    {
        hall_vip_anniu->setVisible(false);
    }

	//ª˘Ω∞¥≈•
	/*auto jijin_sp = Sprite::createWithSpriteFrameName("jijin_icon.png");
	auto hall_jijin_anniu = Menu::create(MenuItemSprite::create(jijin_sp,jijin_sp,CC_CALLBACK_1(GameHallLayer::menu_jijin,this)),nullptr);
	hall_jijin_anniu->setPosition(Vec2(visibleSize.width - 60 + origin.x ,visibleSize.height - 160 + origin.y));
	addChild(hall_jijin_anniu,ANNIULAYER-10);
    
    if(UserDefault::getInstance()->getIntegerForKey("ios_dengluFlag") == 1)
    {
        hall_jijin_anniu->setVisible(false);
    }*/
 
	//…Ã≥«∞¥≈•
	hall_sc_bgguang = Sprite::createWithSpriteFrameName("hall_ssxx_bg.png");
	hall_sc_bgguang->setScale(1.3f);
	hall_sc_bgguang->setPosition(Vec2(visibleSize.width - 60 + origin.x ,visibleSize.height - 270 + origin.y));
	auto  sf = CCRotateBy::create(4.0f,360); 
	hall_sc_bgguang->runAction(RepeatForever::create(sf)); 
	this->addChild(hall_sc_bgguang,ANNIULAYER-10);  

	auto shangcheng  = Sprite::createWithSpriteFrameName("shangcheng.png");  
	hall_Shop = Menu::create(MenuItemSprite::create(shangcheng,shangcheng, shangcheng,CC_CALLBACK_1(GameHallLayer::hall_shangcheng_func1,this)),NULL); 
	hall_Shop->setPosition(Vec2(visibleSize.width - 60 + origin.x ,visibleSize.height - 270 + origin.y));
	this->addChild(hall_Shop,ANNIULAYER-10);

	time_t prevTime1 = UserDefault::getInstance()->getIntegerForKey("prevTime");
	//int curDay = UserDefault::getInstance()->getIntegerForKey("LoginDays");
	hall_dibu_shop_xing1 = Sprite::create();

    int leijiChongzhi = GameBegin::getFileData("wflei.txt");

	if((curDay ==3 || curDay == 5 ||curDay == 7) && currentTime < prevTime && leijiChongzhi == 0 )
	{
		sprintf(hallCharTemp,"sale_persent_up_%d.png",(curDay-1)/2);
		hall_dibu_shop_xing1->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hallCharTemp));
	} 		
	hall_dibu_shop_xing1->setScale(0.7);
	hall_dibu_shop_xing1->setPosition(Vec2(shangcheng->getContentSize().width/2,shangcheng->getContentSize().height));
	shangcheng->addChild(hall_dibu_shop_xing1);



	////◊Ûœ¬Ω«∏¸∂‡”Œœ∑
	//auto hall_sprite_more = Sprite::create("moreGame.png");
	//auto hall_sprite_more_d = Sprite::create("moreGame_d.png");
	//hall_sprite_more->setScale(scaleTmp);
	//hall_sprite_more_d->setScale(scaleTmp);
	//hall_menu_more = Menu::create(MenuItemSprite::create(hall_sprite_more,hall_sprite_more_d,CC_CALLBACK_1(GameHallLayer::hall_more_func,this)),nullptr);
	//hall_menu_more->setPosition(Vec2( 50 + origin.x ,50 + origin.y));
	//addChild(hall_menu_more,ANNIULAYER);
	//hall_menu_more->setVisible(false);

	float tmp_h = 50;
	//…Ë÷√∞¥≈•	
	hall_menu_shezhi_cl = Sprite::createWithSpriteFrameName("hall_menu_shezhi_1.png");
	hall_menu_shezhi_cl->setScale(scaleTmp);
	hall_menu_shezhi = Menu::create(MenuItemSprite::create(hall_menu_shezhi_cl,hall_menu_shezhi_cl,CC_CALLBACK_1(GameHallLayer::hall_shezhi_func,this)),nullptr);
	hall_menu_shezhi->setPosition(Vec2(visibleSize.width - 50 + origin.x , tmp_h + origin.y));
	addChild(hall_menu_shezhi,ANNIULAYER + 5);	

			//≤‡±ﬂøÚ∞¥≈•
	auto hall_sprite_lipin = Sprite::createWithSpriteFrameName("hall_menu_lipin.png");
	hall_sprite_lipin->setScale(scaleTmp);
	auto hall_sprite_lipin_d = Sprite::createWithSpriteFrameName("hall_menu_lipin_d.png");
	hall_sprite_lipin_d->setScale(scaleTmp);
	hall_menu_lipin = Menu::create(MenuItemSprite::create(hall_sprite_lipin,hall_sprite_lipin_d,CC_CALLBACK_1(GameHallLayer::hall_lipin_func,this)),nullptr);
	hall_menu_lipin->setPosition(Vec2(visibleSize.width - 50 + origin.x ,  tmp_h + origin.y));
	hall_menu_lipin->setVisible(false);
	hall_menu_lipin->setEnabled(false);
	addChild(hall_menu_lipin,ANNIULAYER + 4);


	if(!GameHallLayer::hall_bShengyinShow)
	{
		hall_sprite_shengyin = Sprite::createWithSpriteFrameName("hall_menu_shengyin_g.png");
		hall_sprite_shengyin_d = Sprite::createWithSpriteFrameName("hall_menu_shengyin_g_d.png");	
	}else
	{
		hall_sprite_shengyin = Sprite::createWithSpriteFrameName("hall_menu_shengyin_k.png");
		hall_sprite_shengyin_d = Sprite::createWithSpriteFrameName("hall_menu_shengyin_k_d.png");
	}
	
	hall_sprite_shengyin->setScale(scaleTmp);
	hall_sprite_shengyin_d->setScale(scaleTmp);
	hall_menu_shengyin = Menu::create(MenuItemSprite::create(hall_sprite_shengyin,hall_sprite_shengyin_d,CC_CALLBACK_1(GameHallLayer::hall_shengyin_func,this)),nullptr);
	hall_menu_shengyin->setPosition(Vec2(visibleSize.width - 50 + origin.x , tmp_h + origin.y));
	hall_menu_shengyin->setVisible(false);
	hall_menu_shengyin->setEnabled(false);
	addChild(hall_menu_shengyin,ANNIULAYER + 4);

	auto hall_sprite_bangzhu = Sprite::createWithSpriteFrameName("hall_menu_kefu.png");
	hall_sprite_bangzhu->setScale(scaleTmp);
	auto hall_sprite_bangzhu_d = Sprite::createWithSpriteFrameName("hall_menu_kefu_d.png");
	hall_sprite_bangzhu_d->setScale(scaleTmp);
	hall_menu_wenhao = Menu::create(MenuItemSprite::create(hall_sprite_bangzhu,hall_sprite_bangzhu_d,CC_CALLBACK_1(GameHallLayer::hall_bangzhu_func,this)),nullptr);
	hall_menu_wenhao->setPosition(Vec2(visibleSize.width - 50 + origin.x ,  tmp_h + origin.y));
	hall_menu_wenhao->setVisible(false);
	hall_menu_wenhao->setEnabled(false);
	addChild(hall_menu_wenhao,ANNIULAYER + 4);

	auto hall_sprite_youjian = Sprite::createWithSpriteFrameName("hall_menu_youjian.png");
	hall_sprite_youjian->setScale(scaleTmp);
	auto hall_sprite_youjian_d = Sprite::createWithSpriteFrameName("hall_menu_youjian_d.png");
	hall_sprite_youjian_d->setScale(scaleTmp);
	hall_menu_youjian = Menu::create(MenuItemSprite::create(hall_sprite_youjian,hall_sprite_youjian_d,CC_CALLBACK_1(GameHallLayer::hall_youjian_func,this)),nullptr);
	hall_menu_youjian->setPosition(Vec2(visibleSize.width - 50 + origin.x , tmp_h + origin.y));
	hall_menu_youjian->setVisible(false);
	hall_menu_youjian->setEnabled(false);
	addChild(hall_menu_youjian,ANNIULAYER + 4);

	auto hall_sprite_tuichu = Sprite::createWithSpriteFrameName("hall_menu_tuichu.png");
	hall_sprite_tuichu->setScale(scaleTmp);
	auto hall_sprite_tuichu_d = Sprite::createWithSpriteFrameName("hall_menu_tuichu_d.png");
	hall_sprite_tuichu_d->setScale(scaleTmp);
	hall_menu_tuichu = Menu::create(MenuItemSprite::create(hall_sprite_tuichu,hall_sprite_tuichu_d,CC_CALLBACK_1(GameHallLayer::hall_tuichu_func,this)),nullptr);
	hall_menu_tuichu->setPosition(Vec2(visibleSize.width - 50 + origin.x ,tmp_h + origin.y));
	hall_menu_tuichu->setVisible(false);
	hall_menu_tuichu->setEnabled(false);
	addChild(hall_menu_tuichu,ANNIULAYER + 4);
}

// add by zxf

void GameHallLayer::showAds(Ref* pSender)
{
	CCLOG("GameHallLayer::showAds");
	JNativeToJavaUtil::ShowChartboostAds();
}

void GameHallLayer::initZhongJian()
{
    
    int unlockRoom1 = UserDefault::getInstance()->getIntegerForKey("unlockRoomNum");
    
    int tmpRoom1[11] = {0};
    for(int i =0 ; i < 11 ; i++)
    {
        tmpRoom1[i] = unlockRoom1%2;
        unlockRoom1 = unlockRoom1/2;
    }
    
    int roomSeq1 = 2;
    bool roomHas ;
    int paoLv1;
    int paoLv2;
    char tmpChar[50];
    int maxPao =  GameBegin::getFileData("gameMaxPao.txt");
    
    
    for(int i = 11 ; i >= 0 ; i--)
    {
        sprintf(tmpChar,"Room%dHas",i+1);
        roomHas = UserDefault::getInstance()->getBoolForKey(tmpChar);
        sprintf(tmpChar,"boss_low_odd_%d",i+1);
        paoLv1 =  GAME_DATA_INT(tmpChar);
        sprintf(tmpChar,"boss_high_%d",i+1);
        paoLv2 =  GAME_DATA_INT(tmpChar);
        
        if(i < 3)
        {
            roomHas = true;
        }
        
       
        if(tmpRoom1[i] == 1 && roomHas && paoLv1 <= maxPao && maxPao <= paoLv2)
        {
            roomSeq1 = i;
            break;
        }
        
        
    }
    
    cocos2d::log("RoomType = %d  ",roomSeq1);
    
    GameHallLayer::RoomType = roomSeq1;
    
    UserDefault::getInstance()->setFloatForKey("hallDistance", ( - roomSeq1  )*318);
    UserDefault::getInstance()->flush();
    
    
    //¥¥Ω®∑øº‰÷Æ«∞µƒ±‰¡ø
    roomSize = Size(318,454);
	roomSpaceLenth = 0;
	sv_offset = (visibleSize.width - (roomSpaceLenth + roomSize.width)*3 ) / 2;

	//…Ë÷√≤„
	containerLayer = Layer::create();//¥¥Ω® ”Õºµƒ»›∆˜
	//initRoom();
	int containerLayerx = UserDefault::getInstance()->getFloatForKey("hallDistance");
	containerLayer->setPosition(Point(containerLayerx,0));
	containerLayer->setContentSize(CCSizeMake(sv_offset*2 + (roomSpaceLenth + roomSize.width)*(SCENENUM + 2),roomSize.height));

	//¥¥Ω®“ª∏ˆπˆ∂Ø ”Õº
	scrollView = ScrollView::create();	
	scrollView->setViewSize(CCSizeMake(visibleSize.width, roomSize.height + 10));//…Ë÷√viewµƒ¥Û–° (roomSpaceLenth + roomSize.width)*3
	scrollView->setContentOffset(Vec2::ZERO);
	scrollView->setContainer(containerLayer); //…Ë÷√–Ë“™πˆ∂Øµƒƒ⁄»›
	scrollView->ignoreAnchorPointForPosition(false);
	scrollView->setAnchorPoint(Vec2(0.5,0.5));
	scrollView->setPosition(Point(visibleSize.width/2 + origin.x,visibleSize.height * 0.55 + origin.y ));
	scrollView->setTouchEnabled(true);
	scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	scrollView->setDelegate(this);
	addChild(scrollView,ANNIULAYER);
	
	int unlockRoom = UserDefault::getInstance()->getIntegerForKey("unlockRoomNum");  //Ω‚À¯∑øº‰∂˛Ω¯÷∆ ˝∫Õ
	int roomSeq;//¡Ÿ ±¥Ê∑≈ ∑øº‰Ω‚À¯±Í÷æ ±Í¡ø

	//¥¥Ω®”Ê≥°∑øº‰
	for(int i =0 ; i < 11 ; i++)
	{
        
		roomSeq = unlockRoom%2;
		roomFlag[i] = roomSeq;			//≥ı ºªØ∑øº‰Ω‚À¯±Í÷æ ˝◊È
        unlockRoom = unlockRoom/2;

		 //∑øº‰µ◊≤ø±≥æ∞
		auto hall_room_bg = Sprite::createWithSpriteFrameName("hall_room_BG.png"); 
		hall_room_bg->setPosition(Vec2(sv_offset + (i + 1.5)*(roomSpaceLenth+roomSize.width),roomSize.height/2));
		hall_room_bg->setScale(HALL_ROOM_SCALE_LOW);
		containerLayer->addChild(hall_room_bg);
		//push∑øº‰±≥æ∞ »•vec
		hall_room_spec.pushBack(hall_room_bg); 

		//∑øº‰Àı¬‘≥°æ∞±≥æ∞
		auto hall_room_slt_cj = Sprite::createWithSpriteFrameName(roomPhotoName[i]);
		hall_room_slt_cj->setTag(100);
		hall_room_slt_cj->setScale(0.93);
		hall_room_slt_cj->setAnchorPoint(Vec2(0.5,1));
		hall_room_slt_cj->setPosition(Vec2(hall_room_bg->getContentSize().width/2, hall_room_bg->getContentSize().height - 30));
		hall_room_bg->addChild(hall_room_slt_cj);

		auto hall_slt_stencil = Sprite::createWithSpriteFrameName(roomPhotoName[i]);
		auto hall_slt_clipper = ClippingNode::create();
		hall_slt_clipper->setStencil(hall_slt_stencil);
		hall_slt_clipper->setInverted(true);
		hall_slt_clipper->setAlphaThreshold(0);
		hall_room_slt_cj->addChild(hall_slt_clipper);
 
		//Àı¬‘≥°æ∞÷–µƒboss
		auto hall_room_slt_boss = Sprite::createWithSpriteFrameName(roomBossName[i]);
		hall_room_slt_boss->setPosition(Vec2(hall_room_slt_cj->getContentSize().width/2 , hall_room_slt_cj->getContentSize().height/2));
		float hall_room_bss_scale1 = hall_room_slt_cj->getContentSize().width * 0.7/ hall_room_slt_boss->getContentSize().width ;
		float hall_room_bss_scale2 = hall_room_slt_cj->getContentSize().height * 0.7/ hall_room_slt_boss->getContentSize().height;
		float hall_room_bss_scale = hall_room_bss_scale1 > hall_room_bss_scale2 ? hall_room_bss_scale2 :hall_room_bss_scale1;
		hall_room_slt_boss->setTag(19);
		hall_room_slt_boss->setScale(hall_room_bss_scale);
		hall_room_slt_cj->addChild(hall_room_slt_boss);

		if(i == 0 || i == 3 || i == 5 || i == 6 || i == 9 )
		{
			hall_room_slt_boss->setRotation(90);
		}
		if(i == 1 )
		{
			hall_room_slt_boss->setRotation(180);
		}

		//∑øº‰µ◊≤ø–°±≥æ∞
		auto hall_room_slt = Sprite::createWithSpriteFrameName("hall_room_slt.png");
		hall_room_slt->setTag(104);
		hall_room_slt->setPosition(Vec2(hall_room_bg->getContentSize().width/2,hall_room_bg->getContentSize().height/2));
		hall_room_bg->addChild(hall_room_slt);

			//∞¥≈•…œµƒÀÆ≤›1
		auto hall_room_shuicao_1 = Sprite::createWithSpriteFrameName("hall_shuicao_1.png");
		hall_room_shuicao_1->setAnchorPoint(Vec2(0.5,0));
		hall_room_shuicao_1->setPosition(Vec2(hall_room_slt->getContentSize().width * 0.2,hall_room_slt->getContentSize().height * 0.1 - 10));
		hall_room_shuicao_1->setTag(16);
		hall_room_shuicao_1->setScale(0.8);
		hall_room_slt->addChild(hall_room_shuicao_1);

		//∞¥≈•…œµƒÀÆ≤›2
		auto hall_room_shuicao_2 = Sprite::createWithSpriteFrameName("hall_shuicao_10.png");
		hall_room_shuicao_2->setAnchorPoint(Vec2(0.5,0));
		hall_room_shuicao_2->setPosition(Vec2(hall_room_slt->getContentSize().width * 0.8,hall_room_slt->getContentSize().height * 0.1 - 10));
		hall_room_shuicao_2->setTag(17);
		//hall_room_shuicao_2->setScale(0.6);
		hall_room_slt->addChild(hall_room_shuicao_2);

		//∆¯≈›–ßπ˚
		auto hall_room_slt_Particle = ParticleSystemQuad::create("qipao.plist");
		hall_room_slt_Particle->setPosition(Point(hall_room_slt->getContentSize().width * 0.1 , hall_room_slt->getContentSize().height * 0.1));
		hall_room_slt_Particle->retain();
		auto hall_room_slt_batch = ParticleBatchNode::createWithTexture(hall_room_slt_Particle->getTexture()); 
		hall_room_slt_batch->setVisible(false);
		hall_room_slt_batch->addChild(hall_room_slt_Particle); 
		hall_room_slt_batch->setTag(14);
		hall_room_slt->addChild(hall_room_slt_batch); 
 
		auto hall_room_slt_Particle1 = ParticleSystemQuad::create("qipao.plist");
		hall_room_slt_Particle1->setPosition(Point(hall_room_slt->getContentSize().width * 0.8 , hall_room_slt->getContentSize().height * 0.1));
		hall_room_slt_Particle1->retain();
		auto hall_room_slt_batch1 = ParticleBatchNode::createWithTexture(hall_room_slt_Particle1->getTexture()); 
		hall_room_slt_batch1->addChild(hall_room_slt_Particle1); 
		hall_room_slt_batch1->setVisible(false);
		hall_room_slt_batch1->setTag(15);
		hall_room_slt->addChild(hall_room_slt_batch1); 
		
    

		//∑øº‰¡¡π‚
		auto hall_room_lg = Sprite::createWithSpriteFrameName("hall_room_db_bjg.png");
		auto lg_fadeOut = FadeOut::create(0.4f);
		hall_room_lg->setPosition(Vec2(hall_room_bg->getContentSize().width/2,hall_room_bg->getContentSize().height - 40));
		hall_room_lg->setTag(101);		
		hall_room_lg->runAction(lg_fadeOut);
		hall_room_bg->addChild(hall_room_lg);

		//∑øº‰≥°æ∞À¯
		auto hall_room_suo = Sprite::createWithSpriteFrameName("lock_dh_8.png");
		hall_room_suo->setPosition(Vec2(35,hall_room_bg->getContentSize().height - 60));
		hall_room_suo->setTag(102);
		hall_room_bg->addChild(hall_room_suo);

		//Ω¯»Î≥°æ∞∞¥≈•
		auto hall_room_anniu = Sprite::createWithSpriteFrameName("hall_room_anniu.png");
		hall_room_anniu->setTag(201);
		hall_room_anniu->setPosition(Vec2(hall_room_bg->getContentSize().width/2,hall_room_bg->getContentSize().height * 0.24));
		hall_room_bg->addChild(hall_room_anniu);

		/*auto hall_room_item_anniu  = MenuItemSprite::create(hall_room_anniu,hall_room_anniu,CC_CALLBACK_1(GameHallLayer::enterFishManage,this));		
		hall_room_item_anniu->setTag(i + 1);
		auto hall_room_menu_anniu = Menu::create(hall_room_item_anniu,nullptr);
		hall_room_menu_anniu->setTag(i + 1);
		hall_room_menu_anniu->setPosition(Vec2(hall_room_bg->getContentSize().width/2,hall_room_bg->getContentSize().height * 0.24));
		hall_room_bg->addChild(hall_room_menu_anniu);*/

		//Ω¯»Î”Ê≥°◊÷
		auto hall_room_jryc = Sprite::createWithSpriteFrameName("hall_room_jryc.png");
		hall_room_jryc->setTag(203);
		hall_room_jryc->setPosition(Vec2(hall_room_anniu->getContentSize().width/2,hall_room_anniu->getContentSize().height * 0.5));
		hall_room_anniu->addChild(hall_room_jryc);

		//Ω‚À¯ ◊Í Ø
		auto hall_room__anniu_zuanshi = Sprite::createWithSpriteFrameName("diamond.png");
		hall_room__anniu_zuanshi->setTag(204);
		hall_room__anniu_zuanshi->setPosition(Vec2(hall_room_anniu->getContentSize().width * 0.2,hall_room_anniu->getContentSize().height * 0.5));
		hall_room_anniu->addChild(hall_room__anniu_zuanshi);

		//À˘–Ë◊Í Ø ˝¡ø
		memset(hallCharTemp,0,sizeof(hallCharTemp));
		sprintf(hallCharTemp,"boss_diamond_num_%d",i+1);
		sprintf(hallCharTemp,"%d",GAME_DATA_INT(hallCharTemp));
		auto hall_room__anniu_zuanshi_num = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
		hall_room__anniu_zuanshi_num->setTag(205);
		hall_room__anniu_zuanshi_num->setScale(0.7);
		hall_room__anniu_zuanshi_num->setString(hallCharTemp);
		hall_room__anniu_zuanshi_num->setPosition(Point(hall_room_anniu->getContentSize().width * 0.64,hall_room_anniu->getContentSize().height/2));
		hall_room_anniu->addChild(hall_room__anniu_zuanshi_num);

		if(roomSeq == 1)   //“—æ≠Ω‚À¯∑øº‰µƒ≥ı ºªØ
		{
			hall_room__anniu_zuanshi->setVisible(false);
			hall_room__anniu_zuanshi_num->setVisible(false);
			
		}else		//Œ¥Ω‚À¯∑øº‰µƒ≥ı ºªØ
		{
			 
			 //hall_room_anniu->setCallback(CC_CALLBACK_1(GameHallLayer::roomUnlockManage,this));
			 hall_room_jryc->setVisible(false);
			 SpriteFrame * lockTmp = SpriteFrameCache::getInstance()->getSpriteFrameByName("lock_dh_1.png");
			 hall_room_suo->setSpriteFrame(lockTmp);
		}
 
	}
}

void GameHallLayer::initBSRoom()
{
	
}

void GameHallLayer::init_BS1()
{
	pingTimes = 0;
	bs_jiangbei_xx[0][0] = Vec2(56,267);bs_jiangbei_xx[0][1] = Vec2(214,323);bs_jiangbei_xx[0][2] = Vec2(382,267);
	bs_jiangbei_xx[1][0] = Vec2(66,266);bs_jiangbei_xx[1][1] = Vec2(218,321);bs_jiangbei_xx[1][2] = Vec2(382,267);
	bs_jiangbei_xx[2][0] = Vec2(46,267);bs_jiangbei_xx[2][1] = Vec2(210,323);bs_jiangbei_xx[2][2] = Vec2(382,267);
	bs_jiangbei_xx[3][0] = Vec2(46,267);bs_jiangbei_xx[3][1] = Vec2(210,323);bs_jiangbei_xx[3][2] = Vec2(376,267);
    
    bs_huafeiquan_zz[0][0] = Vec2(84,122);bs_huafeiquan_zz[0][1] = Vec2(253,162);bs_huafeiquan_zz[0][2] = Vec2(424,122);
    bs_huafeiquan_zz[1][0] = Vec2(97,122);bs_huafeiquan_zz[1][1] = Vec2(256,161);bs_huafeiquan_zz[1][2] = Vec2(415,122);
    bs_huafeiquan_zz[2][0] = Vec2(97,120);bs_huafeiquan_zz[2][1] = Vec2(256,161);bs_huafeiquan_zz[2][2] = Vec2(413,120);
    bs_huafeiquan_zz[3][0] = Vec2(86,122);bs_huafeiquan_zz[3][1] = Vec2(252,162);bs_huafeiquan_zz[3][2] = Vec2(424,122);
    
	//¥¥Ω®∑øº‰÷Æ«∞µƒ±‰¡ø
	bs_jiangbei_name[0] = "BS_room1_jb.png";bs_jiangbei_name[1] = "BS_room2_jb.png";bs_jiangbei_name[2] = "BS_room3_jb.png";bs_jiangbei_name[3] = "BS_room4_jb.png";
	bs_duandai_name[0] = "BS_room1_dd.png";bs_duandai_name[1] = "BS_room2_dd.png";bs_duandai_name[2] = "BS_room3_dd.png";bs_duandai_name[3] = "BS_room4_dd.png";
	
	bs_room_is_moving = false;
	roomSize1 = Size(905,465);
	bs1_room_bgg_flag_rotate = 1;

	bs_moshi = UserDefault::getInstance()->getIntegerForKey("BS_moshi");

	//∑øº‰µ◊≤ø±≥æ∞
	bs1_room_bg = Sprite::createWithSpriteFrameName("BS_room_bg.png");
	bs1_room_bg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2 + 10));
	bs1_room_bg->setScale(scaleTmp - 0.05f);
	this->addChild(bs1_room_bg,ANNIULAYER + 100);

	//∑øº‰±»»¸»À ˝
	auto bs_title_renshu = Sprite::createWithSpriteFrameName("BS_room_guize_bg.png");
	bs_title_renshu->setPosition(Vec2(393,389));
	bs1_room_bg->addChild(bs_title_renshu,ANNIULAYER);

	auto stencil11 = Sprite::createWithSpriteFrameName("BS_room_bg.png");
	auto clipper11 = ClippingNode::create();
	clipper11->setStencil(stencil11);//…Ë÷√≤√ºÙƒ£∞Â //3
	clipper11->setInverted(false);//…Ë÷√µ◊∞Â≤ªø…º˚
	//clipper->setAnchorPoint(Vec2(0.5,0.5));
	clipper11->setPosition(Vec2(bs1_room_bg->getContentSize().width/2,bs1_room_bg->getContentSize().height/2 + 10));
	clipper11->setContentSize(bs1_room_bg->getContentSize());
	clipper11->setAlphaThreshold(0);//…Ë÷√ªÊ÷∆µ◊∞ÂµƒAlpha÷µŒ™0
	bs1_room_bg->addChild(clipper11,8);//4

	auto sajinbi1 = ParticleSystemQuad::create("zm_yubi.plist");
	bs_room_bg_yb = ParticleBatchNode::createWithTexture(sajinbi1->getTexture()); 
	bs_room_bg_yb->setPosition(Point(-250,0));
	bs_room_bg_yb->addChild(sajinbi1); 
	bs_room_bg_yb->setVisible(false);
	clipper11->addChild(bs_room_bg_yb); 
	sajinbi1->resetSystem();

	auto sajinbi2 = ParticleSystemQuad::create("zm_huanfeiquan.plist");
	bs_room_bg_hfq = ParticleBatchNode::createWithTexture(sajinbi2->getTexture()); 
	bs_room_bg_hfq->setPosition(Point(-250,0));
	bs_room_bg_hfq->addChild(sajinbi2); 
	bs_room_bg_hfq->setVisible(false);
	clipper11->addChild(bs_room_bg_hfq); 
	sajinbi1->resetSystem();
 
	auto stencil = Sprite::createWithSpriteFrameName("BS_room_bg.png");
	auto clipper = ClippingNode::create();
	clipper->setStencil(stencil);//…Ë÷√≤√ºÙƒ£∞Â //3
	clipper->setInverted(false);//…Ë÷√µ◊∞Â≤ªø…º˚
	//clipper->setAnchorPoint(Vec2(0.5,0.5));
	clipper->setPosition(Vec2(bs1_room_bg->getContentSize().width/2,bs1_room_bg->getContentSize().height/2 + 10));
	clipper->setContentSize(bs1_room_bg->getContentSize());
	clipper->setAlphaThreshold(0);//…Ë÷√ªÊ÷∆µ◊∞ÂµƒAlpha÷µŒ™0
	bs1_room_bg->addChild(clipper,10,21);//4
 
	

	//ÀÊª˙–«–«
	int xx_num = CCRANDOM_0_1() * 20 + 20;
	for(int k = 0 ; k < xx_num ; k++)
	{
		float sclae_tmp = CCRANDOM_0_1() * 0.4 + 0.1;
		auto xx_pos =Vec2( CCRANDOM_0_1()*700 + 30,CCRANDOM_0_1()*350 + 60);
		auto xiao_xx = Sprite::createWithSpriteFrameName("BS_xingxing.png");
		xiao_xx->setPosition(xx_pos);
		xiao_xx->setScale(sclae_tmp);
		xiao_xx->setOpacity(sclae_tmp*255);
		//xiao_xx->setRotation((int)(90*CCRANDOM_0_1()));
		bs1_room_bg->addChild(xiao_xx);

		auto delay11 = DelayTime::create(k * CCRANDOM_0_1() * 0.5);
		auto spawn1 = Spawn::create(FadeOut::create(0.5f),ScaleTo::create(0.5f,0.01),nullptr);
		auto spawn11 = Spawn::create(FadeTo::create(0.5f,sclae_tmp*400),ScaleTo::create(0.5f,sclae_tmp),nullptr);
		auto delay12 = DelayTime::create((xx_num - k) * CCRANDOM_0_1() * 0.5);

		xiao_xx->runAction(RepeatForever::create(Sequence::create(delay11,spawn1,spawn11,delay12,nullptr)));
	}
 
	//bs1_room_bgg
	bs1_room_bgg = Sprite::create("Ranklight1.png");
	bs1_room_bgg->setScale(1.2);
	bs1_room_bgg->setPosition(Vec2(bs1_room_bg->getContentSize().width/2,bs1_room_bg->getContentSize().height * 0.51));
	bs1_room_bg->addChild(bs1_room_bgg,9);

	float time_r = CCRANDOM_0_1() * 10 + 5.0f;
	auto  seq = Sequence::create(RotateBy::create(time_r,360 * bs1_room_bgg_flag_rotate),CallFunc::create(this,callfunc_selector(GameHallLayer::bs1_bgg_call)),nullptr);
	bs1_room_bgg->runAction(seq);
 
	//ÃÌº”±»»¸»À ˝chipnode  to do
	auto stencil1 = Sprite::createWithSpriteFrameName("BS_renshu_bgk.png");
	auto clipper1 = ClippingNode::create();
	clipper1->setStencil(stencil1);//…Ë÷√≤√ºÙƒ£∞Â //3
	clipper1->setInverted(false);//…Ë÷√µ◊∞Â≤ªø…º˚
	clipper1->setPosition(Vec2(350,389));
	clipper1->setContentSize(stencil1->getContentSize());
	clipper1->setAlphaThreshold(0);//…Ë÷√ªÊ÷∆µ◊∞ÂµƒAlpha÷µŒ™0
	bs1_room_bg->addChild(clipper1,ANNIULAYER+1);//4

	//ø™»¸»À ˝æ´¡È
	bs1_room_ksrs = Sprite::create();
	bs1_room_ksrs->setContentSize(Size(50,80));
	bs1_room_ksrs->setAnchorPoint(Vec2(0.5,0));
	bs1_room_ksrs->setPosition(Vec2(0,-10));
	clipper1->addChild(bs1_room_ksrs);

	//±»»¸ ±º‰
	auto bs_shijian = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
	sprintf(hallCharTemp,"%d",5);
	bs_shijian->setString(hallCharTemp);
	bs_shijian->setScale(0.34);
	bs_shijian->setPosition(Vec2(533,389));
	bs1_room_bg->addChild(bs_shijian,ANNIULAYER+1);
 
	//±»»¸œÍ«È∞¥≈•
	auto bsroom_xq = Sprite::createWithSpriteFrameName("BS_xiangqing.png");
	auto bsroom_xq_item = MenuItemSprite::create(bsroom_xq,bsroom_xq,CC_CALLBACK_1(GameHallLayer::hall_bs_xiangqing_func,this));
	bs1_room_xiangq = Menu::create(bsroom_xq_item,nullptr);
	bs1_room_xiangq->setPosition(Vec2(721,75));
	bs1_room_bg->addChild(bs1_room_xiangq,100);

	bs1_room_xiangq_heidi = Sprite::createWithSpriteFrameName("bs_xiangq_yy.png");
	bs1_room_xiangq_heidi->setPosition(Vec2(721,56));
	bs1_room_bg->addChild(bs1_room_xiangq_heidi,100);

	bs1_room_xiangq_yingzi = Sprite::createWithSpriteFrameName("BS_xiangqing.png");
	bs1_room_xiangq_yingzi->setFlippedY(true);
	bs1_room_xiangq_yingzi->setOpacity(90);
	bs1_room_xiangq_yingzi->setPosition(Vec2(329,-208));
	clipper->addChild(bs1_room_xiangq_yingzi,100);  // 

	//Ω¯»Î±»»¸∞¥≈•
	auto hall_room_anniu = Sprite::createWithSpriteFrameName("bs_baoming.png");
	auto hall_item_baoming = MenuItemSprite::create(hall_room_anniu,hall_room_anniu,CC_CALLBACK_1(GameHallLayer::hall_baoming_func,this));
	hall_item_baoming->setScale(0.8);
	auto hall_menu_baoming = Menu::create(hall_item_baoming,nullptr);
	hall_menu_baoming->setPosition(Vec2(bs1_room_bg->getContentSize().width/2,35));
	bs1_room_bg->addChild(hall_menu_baoming,100,101);
 
	auto sajinbi = ParticleSystemQuad::create("zm_huang.plist");
	auto batch = ParticleBatchNode::createWithTexture(sajinbi->getTexture()); 
	batch->addChild(sajinbi); 
	bs1_room_bg->addChild(batch,ANNIULAYER,301); 
	sajinbi->setPosition(Point(bs1_room_bg->getContentSize().width/2,bs1_room_bg->getContentSize().height));
	sajinbi->resetSystem();

	//¥¥Ω®±»»¸∑øº‰
	for(int i =0 ; i < 4 ; i++)
	{ 
		//∑øº‰∂–¥¯
		auto bs1_room_dd = Sprite::createWithSpriteFrameName(bs_duandai_name[i]);
		bs1_room_dd->setPosition(Vec2(bs1_room_bg->getContentSize().width/2,bs1_room_bg->getContentSize().height + 50));
		bs1_room_dd->setOpacity(0);
		bs1_room_bg->addChild(bs1_room_dd,10);
		bs1_duandai_vec.pushBack(bs1_room_dd);
 
		
		//ø™»¸»À ˝
		auto bs_renshu = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
		int tmpRS;
		if(i == 0)
		{
			tmpRS = CCRANDOM_0_1()*1000 + 2000;
		}else if(i == 1)
		{
			tmpRS = CCRANDOM_0_1()*1500 + 1500;
		}else
		{
			tmpRS = CCRANDOM_0_1()*2000 + 1000;
		}
		bs_RenShu[i] = tmpRS;
		sprintf(hallCharTemp,"%d",tmpRS);
		bs_renshu->setString(hallCharTemp);
		bs_renshu->setScale(0.34);
		bs_renshu->setPosition(Vec2(25,10+i*20));
		bs1_room_ksrs->addChild(bs_renshu);
 
		//∑øº‰Ω±±≠
		auto hall_bs_jiangli = Sprite::createWithSpriteFrameName(bs_jiangbei_name[i]);
		hall_bs_jiangli->setAnchorPoint(Vec2(0.5,0));
		hall_bs_jiangli->setScale(1.05);
		hall_bs_jiangli->setPosition(Vec2(0,-bs1_room_bg->getContentSize().height*1.5 - 20));
		clipper->addChild(hall_bs_jiangli,10);

		bs1_jiangbei_vec.pushBack(hall_bs_jiangli);
        
        //这书
        if( UserDefault::getInstance()->getIntegerForKey("ios_dengluFlag") == 1)
        {
            for(int j = 0 ; j < 3 ; j ++)
            {
              
            }
        }

		//Ω±±≠…œµƒ–«–«1
		auto bs_room_xx1 = Sprite::createWithSpriteFrameName("BS_xingxing.png");
		bs_room_xx1->setPosition(bs_jiangbei_xx[i][0]);
		bs_room_xx1->setScale(0.7);
		hall_bs_jiangli->addChild(bs_room_xx1);

		auto delay1 = DelayTime::create(2.0f);
		auto spawn1 = Spawn::create(FadeOut::create(0.5f),ScaleTo::create(0.5f,0.2),nullptr);
		auto spawn11 = Spawn::create(FadeIn::create(0.5f),ScaleTo::create(0.5f,0.7),nullptr);
		auto delay12 = DelayTime::create(13.0f);

		bs_room_xx1->runAction(RepeatForever::create(Sequence::create(delay1,spawn1,spawn11,delay12,nullptr)));

		//Ω±±≠…œµƒ–«–«2
		auto bs_room_xx2 = Sprite::createWithSpriteFrameName("BS_xingxing.png");
		bs_room_xx2->setPosition(bs_jiangbei_xx[i][1]);

		hall_bs_jiangli->addChild(bs_room_xx2);

		auto delay21 = DelayTime::create(4.0f);
		auto spawn2 = Spawn::create(FadeOut::create(0.5f),ScaleTo::create(0.5f,0.2),nullptr);
		auto spawn21 = Spawn::create(FadeIn::create(0.5f),ScaleTo::create(0.5f,1),nullptr);
		auto rotate2 = RotateBy::create(1.0f,180);
		auto delay22 = DelayTime::create(10.0f);

		bs_room_xx2->runAction(RepeatForever::create(Sequence::create(delay21,spawn2,spawn21,rotate2,delay22,nullptr)));

		//Ω±±≠…œµƒ–«–«3
		auto bs_room_xx3 = Sprite::createWithSpriteFrameName("BS_xingxing.png");
		bs_room_xx3->setPosition(bs_jiangbei_xx[i][2]);
		bs_room_xx3->setScale(0.6);
		hall_bs_jiangli->addChild(bs_room_xx3);

		auto delay31 = DelayTime::create(7.0f);
		auto spawn3 = Spawn::create(FadeOut::create(0.5f),ScaleTo::create(0.5f,0.2),nullptr);
		auto spawn31 = Spawn::create(FadeIn::create(0.5f),ScaleTo::create(0.5f,0.6),nullptr);
		auto delay33 = DelayTime::create(8.0f);
		bs_room_xx3->runAction(RepeatForever::create(Sequence::create(delay31,spawn3,spawn31,delay33,nullptr)));

	}

	//bs1_display(bs_moshi);
}

void GameHallLayer::bs1_bgg_call()
{
	float time_r = CCRANDOM_0_1() * 3 + 3.0f;
	bs1_room_bgg_flag_rotate = CCRANDOM_0_1()* 2 - 1;
	cocos2d::log("bs1_room_bgg_flag_rotate = %f ", bs1_room_bgg_flag_rotate);

	auto  seq = Sequence::create(RotateBy::create(time_r,360 * bs1_room_bgg_flag_rotate),CallFunc::create(this,callfunc_selector(GameHallLayer::bs1_bgg_call)),nullptr);//
	bs1_room_bgg->runAction(seq);
}

void GameHallLayer::bs1_display(int num)
{
	//≈–∂œµ±«∞œ‘ æ  «∑Ò’˝≥£
 
	cocos2d::log("%d",(int)bs1_jiangbei_vec.at(num - 1)->getPositionY());
	cocos2d::log("%d",(int)-bs1_room_bg->getContentSize().height/2 - 20);
	if(bs1_jiangbei_vec.at(num - 1)->getPositionY() >= -bs1_room_bg->getContentSize().height/2 - 20 || bs_room_is_moving)
	{
		//“—æ≠≈≤∫√¡À
		cocos2d::log("no need to dischange");
		return;
	}
	
	bs_room_is_moving = true;
	cocos2d::log("bs_room_is_moving = true");
	bs1_yinxiao_flag = 0;
	for(int i = 0; i < 4 ; i++)
	{
		if( i == num - 1 )
		{
			auto delay = DelayTime::create(0.5f);
			auto moveBy = MoveTo::create(0.5f,Vec2(0,-bs1_room_bg->getContentSize().height/2 - 20));
			bs1_jiangbei_vec.at(i)->runAction(Sequence::create(delay,CallFunc::create([&]{if(isBiSai)GameBegin::playSound("LeftAndRightGlueScreenPopUp.mp3");}),moveBy,CallFunc::create([&]{ bs_room_is_moving = false;cocos2d::log("bs_room_is_moving = false");}),nullptr));
		}else
		{
			auto delay = DelayTime::create(0.5f);
			auto moveTo = MoveTo::create(0.5f,Vec2(0,-bs1_room_bg->getContentSize().height * 1.5 - 20));
			bs1_jiangbei_vec.at(i)->runAction(Sequence::create(CallFunc::create([&]{if(isBiSai && bs1_yinxiao_flag==0){GameBegin::playSound("LeftAndRightGlueScreenPopDown.mp3");cocos2d::log("j = %d",bs1_yinxiao_flag);bs1_yinxiao_flag++;}}),moveTo,nullptr));
		}
	}
    
    //左提示字
    char tmpword[30];
    char tmpword1[30];
    sprintf(tmpword,"bs_room_word%d.png",num-1);
    sprintf(tmpword1,"bs_room_word%d.png",num+1);
    if(num == 1)
    {
        bs1_zuozi->setVisible(false);
        bs1_youzi->setVisible(true);
        bs1_youzi->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(tmpword1));
    }
    else if(num == 2 || num == 3)
    {
        bs1_zuozi->setVisible(true);
        bs1_youzi->setVisible(true);
        bs1_zuozi->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(tmpword));
        bs1_youzi->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(tmpword1));
    }
    else if(num == 4)
    {
        bs1_zuozi->setVisible(true);
        bs1_youzi->setVisible(false);
        bs1_zuozi->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(tmpword));

    }
 
	//±»»¸±≥æ∞π‚
	auto fadeout = FadeOut::create(0.2f);
	auto delay = DelayTime::create(0.6f);
	auto fadein = FadeIn::create(0.2f);
	auto  seq = Sequence::create(fadeout,delay,fadein,nullptr);//
	bs1_room_bgg->runAction(seq);

	//±»»¸±®√˚∞¥≈•
	auto fadeout1 = FadeOut::create(0.2f);
	auto delay1 = DelayTime::create(0.6f);
	auto fadein1 = FadeIn::create(0.2f);
	auto  seq1 = Sequence::create(fadeout1,delay1,fadein1,nullptr);//
	bs1_room_bg->getChildByTag(101)->runAction(seq1);
	

	//µ±«∞∂–¥¯
	for(int i = 0; i < 4 ; i++)
	{
		if( i == num - 1 )
		{
			bs1_duandai_vec.at(i)->setZOrder(11);
			auto delay = DelayTime::create(0.5f);
			auto moveBy = MoveTo::create(0.5f,Vec2(bs1_room_bg->getContentSize().width/2,bs1_room_bg->getContentSize().height - 40));
			auto fadein = FadeIn::create(0.25f);
			auto spawn = Spawn::create(moveBy,fadein,nullptr);
			bs1_duandai_vec.at(i)->runAction(Sequence::create(spawn,nullptr));
		}else
		{
			bs1_duandai_vec.at(i)->setZOrder(10);
			auto delay = DelayTime::create(0.5f);
			auto moveTo = MoveTo::create(0.5f,Vec2(bs1_room_bg->getContentSize().width/2,bs1_room_bg->getContentSize().height));
			auto fadein = FadeOut::create(0.25f);
			auto spawn = Spawn::create(moveTo,fadein,nullptr);
			bs1_duandai_vec.at(i)->runAction(Sequence::create(spawn,nullptr));
		}
	}

	//ø™»¸»À ˝
	bs1_room_ksrs->runAction(MoveTo::create(0.5f,Vec2(0, -num * 20 + 10)));

	float time_xq = 0.5f;
	//œÍ«È∞¥≈•
	auto jump1  = JumpBy::create(time_xq,Vec2::ZERO,30,1);
	auto jump2  = JumpBy::create(time_xq-0.2f,Vec2::ZERO,15,1);
	auto jump3  = JumpBy::create(time_xq-0.3f,Vec2::ZERO,5,1);

	bs1_room_xiangq->runAction(Sequence::create(DelayTime::create(1.0f), 
		jump1,CallFunc::create([&]{GameBegin::playSound("bs_room_xiangq1.mp3");}),
		jump2, 
		jump3, 
		nullptr));

	//œÍ«È∞¥≈•µπ”∞
	auto jump11  = JumpBy::create(time_xq,Vec2::ZERO,-30,1);
	auto jump21  = JumpBy::create(time_xq-0.2f,Vec2::ZERO,-15,1);
	auto jump31 = JumpBy::create(time_xq-0.3f,Vec2::ZERO,-5,1);
	bs1_room_xiangq_yingzi->runAction(Sequence::create(DelayTime::create(1.0f),jump11,jump21,jump31,nullptr));

	//œÍ«È∫⁄µ◊
	auto scale1 = ScaleTo::create(time_xq/2,0.3);
	auto scale11 = ScaleTo::create(time_xq/2,1);
	auto scale2 = ScaleTo::create(0.15f,0.7);
	auto scale21 = ScaleTo::create(0.15f,1);
	auto scale3 = ScaleTo::create(0.1f,0.9);
	auto scale31 = ScaleTo::create(0.1f,1);
	bs1_room_xiangq_heidi->runAction(Sequence::create(DelayTime::create(1.0f),scale1,scale11,scale2,scale21,scale3,scale31,nullptr));

	//∂–¥¯…œµƒΩπ‚
	if(num > 2)
	{
		bs1_room_bg->getChildByTag(301)->setVisible(true);
	}
	else
	{
		bs1_room_bg->getChildByTag(301)->setVisible(false);
	}

    if(num > 3 && UserDefault::getInstance()->getIntegerForKey("ios_dengluFlag") != 1)
	{
		bs_room_bg_yb->runAction(Sequence::create(DelayTime::create(1.0f),Show::create(),nullptr));
		bs_room_bg_hfq->runAction(Sequence::create(DelayTime::create(1.0f),Show::create(),nullptr));
	}
	else
	{
		bs_room_bg_yb->setVisible(false);
		bs_room_bg_hfq->setVisible(false);
	}
}

void GameHallLayer::initDibu()
{
	float dibu_tmp_f = 0.7f;
	//≥ı ºªØ¥ÛÃ¸µ◊◊˘±≥æ∞
	auto hall_dibu_bg = Sprite::createWithSpriteFrameName("hall_dibu_bg.png");
	hall_dibu_bg->setAnchorPoint(Vec2(0.5,0));
	hall_dibu_bg->setScale(dibu_tmp_f);
	hall_dibu_bg->setPosition(Vec2(visibleSize.width/2 + origin.x,origin.y));
	addChild(hall_dibu_bg,ANNIULAYER+2);

		//Ω‚À¯∞¥≈•
	hall_dibu_sprite_jiesuo = Sprite::createWithSpriteFrameName("hall_jiesuo1.png");
	hall_dibu_sprite_jiesuo->setScale(dibu_tmp_f);
	auto hall_dibu_menu_jiesuo = Menu::create(MenuItemSprite::create(hall_dibu_sprite_jiesuo,hall_dibu_sprite_jiesuo,CC_CALLBACK_1(GameHallLayer::hall_jiesuo_func,this)),nullptr);
	hall_dibu_menu_jiesuo->setPosition(Vec2(visibleSize.width * 0.325,hall_dibu_bg->getContentSize().height  - 10));
	addChild(hall_dibu_menu_jiesuo,ANNIULAYER+2);

		//…Ã≥«∞¥≈•
	hall_dibu_sprite_shangcheng = Sprite::createWithSpriteFrameName("hall_shangcheng1.png");
	hall_dibu_sprite_shangcheng->setScale(dibu_tmp_f);
	hall_dibu_menu_shangcheng = Menu::create(MenuItemSprite::create(hall_dibu_sprite_shangcheng,hall_dibu_sprite_shangcheng,CC_CALLBACK_1(GameHallLayer::hall_shangcheng_func,this)),nullptr);
	hall_dibu_menu_shangcheng->setPosition(Vec2(visibleSize.width * 0.325 + 187 * dibu_tmp_f,hall_dibu_bg->getContentSize().height  - 10));
	addChild(hall_dibu_menu_shangcheng,ANNIULAYER+2);

		//ººƒ‹∞¥≈•
	hall_dibu_sprite_jineng = Sprite::createWithSpriteFrameName("hall_jineng1.png");
	hall_dibu_sprite_jineng->setScale(dibu_tmp_f);
	auto hall_dibu_menu_jineng = Menu::create(MenuItemSprite::create(hall_dibu_sprite_jineng,hall_dibu_sprite_jineng,CC_CALLBACK_1(GameHallLayer::hall_jineng_func,this)),nullptr);
	hall_dibu_menu_jineng->setPosition(Vec2(visibleSize.width * 0.325 + 187 * 2 * dibu_tmp_f,hall_dibu_bg->getContentSize().height  - 10));
	addChild(hall_dibu_menu_jineng,ANNIULAYER+2);

		//ÃÙ’Ω∞¥≈•
	hall_dibu_sprite_tiaozhan = Sprite::createWithSpriteFrameName("hall_tiaozhan1.png");
	hall_dibu_sprite_tiaozhan->setScale(dibu_tmp_f);
	auto hall_dibu_menu_tiaozhan = Menu::create(MenuItemSprite::create(hall_dibu_sprite_tiaozhan,hall_dibu_sprite_tiaozhan,CC_CALLBACK_1(GameHallLayer::hall_tiaozhan_func,this)),nullptr);
	hall_dibu_menu_tiaozhan->setPosition(Vec2(visibleSize.width * 0.325 + 187 * 3 * dibu_tmp_f,hall_dibu_bg->getContentSize().height - 10));
	addChild(hall_dibu_menu_tiaozhan,ANNIULAYER+2);

	/*Animate  * hall_menu_cl_dh1  = Animate::create(AnimationCache::getInstance()->getAnimation("hall_tiaozhan"));
	hall_dibu_sprite_tiaozhan->runAction(RepeatForever::create(hall_menu_cl_dh1));*/

	//…Ã≥«µƒ–«–«
	time_t prevTime = UserDefault::getInstance()->getIntegerForKey("prevTime");
	time_t currentTime;
	time(&currentTime);
	hall_dibu_shop_xing = Sprite::create();
	int leijiChongzhi = UserDefault::getInstance()->getIntegerForKey("leijichongzhi");

	if((curDay ==3 || curDay == 5 ||curDay == 7) && currentTime < prevTime && leijiChongzhi == 0 )
	{
		sprintf(hallCharTemp,"sale_persent_up_%d.png",(curDay-1)/2);
		hall_dibu_shop_xing->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hallCharTemp));
		UserDefault::getInstance()->setIntegerForKey("shop_sele_tag",curDay / 2);
	}else
	{
		UserDefault::getInstance()->setIntegerForKey("shop_sele_tag",0);
	}
	UserDefault::getInstance()->flush();
	hall_dibu_shop_xing->setPosition(Vec2(hall_dibu_sprite_shangcheng->getContentSize().width/2,hall_dibu_sprite_shangcheng->getContentSize().height + 20));
	hall_dibu_sprite_shangcheng->addChild(hall_dibu_shop_xing);
 
	//±∂¬ Ω‚À¯µƒ–«–«
	hall_dibu_beilv_xing = Sprite::createWithSpriteFrameName ( "hall_ssxx_1.png");
	hall_dibu_beilv_xing->setPosition(Vec2(hall_dibu_sprite_jiesuo->getContentSize().width/2,hall_dibu_sprite_jiesuo->getContentSize().height + 20));
	hall_dibu_sprite_jiesuo->addChild(hall_dibu_beilv_xing);

	auto hall_dibu_sprite_jiesuo_xing = Sprite::createWithSpriteFrameName("hall_ssxx_bg.png");
	hall_dibu_sprite_jiesuo_xing->setPosition(Vec2(hall_dibu_beilv_xing->getContentSize().width/2,hall_dibu_beilv_xing->getContentSize().height/2));
	hall_dibu_beilv_xing->addChild(hall_dibu_sprite_jiesuo_xing,-1);

	auto beilv_xxdh_A = AnimationCache::getInstance()->getAnimation("hall_ssxx");
	auto beilv_xxdh = Animate::create(beilv_xxdh_A);
	hall_dibu_beilv_xing->runAction(RepeatForever::create(beilv_xxdh));

			//ººƒ‹…˝º∂µƒ–«–«
	hall_dibu_dapao_xing = Sprite::createWithSpriteFrameName ( "hall_ssxx_1.png");
	hall_dibu_dapao_xing->setPosition(Vec2(hall_dibu_sprite_jiesuo->getContentSize().width/2,hall_dibu_sprite_jiesuo->getContentSize().height + 20));
	hall_dibu_sprite_jineng->addChild(hall_dibu_dapao_xing);

	auto hall_dibu_sprite_jineng_xing = Sprite::createWithSpriteFrameName("hall_ssxx_bg.png");
	hall_dibu_sprite_jineng_xing->setPosition(Vec2(hall_dibu_dapao_xing->getContentSize().width/2,hall_dibu_dapao_xing->getContentSize().height/2));
	hall_dibu_dapao_xing->addChild(hall_dibu_sprite_jineng_xing,-1);

	auto jineng_xxdh_A = AnimationCache::getInstance()->getAnimation("hall_ssxx");
	auto jineng_xxdh = Animate::create(jineng_xxdh_A);
	hall_dibu_dapao_xing->runAction(RepeatForever::create(jineng_xxdh));

	//±»»¸Œª÷√Ã· æµ∆
	for(int k = 0 ; k < 4 ; k++)
	{
		auto hall_tishi_bs = Sprite::createWithSpriteFrameName ( "bs_jt_1.png");
		hall_tishi_bs->setPosition(Vec2(hall_dibu_bg->getContentSize().width * 0.226 + 187 * k,hall_dibu_bg->getContentSize().height * 2));
		hall_dibu_bg->addChild(hall_tishi_bs);

		auto jiantou_tishi = AnimationCache::getInstance()->getAnimation("hall_bsjiantou");
		auto jiantou_tishi_A = Animate::create(jiantou_tishi);
		hall_tishi_bs->runAction(RepeatForever::create(jiantou_tishi_A));
		hall_tishi_vec.pushBack(hall_tishi_bs);
	}
 
	char tiaozhanTmp[10];
	sprintf(tiaozhanTmp,"%d",tiaozhanShu);

	tiaozhanHongQ = Sprite::createWithSpriteFrameName("hall_ssxx_bg.png");
	tiaozhanHongQ->setPosition(Vec2(hall_dibu_sprite_tiaozhan->getContentSize().width * 0.5,hall_dibu_sprite_tiaozhan->getContentSize().height + 20));
	hall_dibu_sprite_tiaozhan->addChild(tiaozhanHongQ);

	tiaozhanShuZi = Label::createWithCharMap("img/hall_suoxiaozi.png",27,37,'0');
	tiaozhanShuZi->setScale(0.75);
	tiaozhanShuZi->setPosition(Vec2(hall_dibu_sprite_tiaozhan->getContentSize().width/2+1,hall_dibu_sprite_tiaozhan->getContentSize().height + 20));
	hall_dibu_sprite_tiaozhan->addChild(tiaozhanShuZi);
}

void GameHallLayer::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();

	JNativeToJavaUtil::CreateGoogleHelper();



   // GameBegin::removeSouce(2);
   // GameBegin::removeSouce(3);
    
   // TextureCache::getInstance()->removeUnusedTextures();
}

bool GameHallLayer::init()
{
	// 1. super init first
	if ( !Layer::init() )	
	{
		return false;
	}
    TextureCache::getInstance()->removeTextureForKey("logo.png");
    
  
	cocos2d::log("init start");
	GameBegin::curScene = 2;
	checkbudan = true;

    //取得Room Sokcet
		TcpClientSocket *ptempHallSocket = LogoLayer::GetSocket();
	ptempHallSocket->CloseSocket();

	ptempHallSocket->ConnectServer((char*)LogoLayer::gHIpStr.data(), LogoLayer::gHPortStr);

	if(ptempHallSocket->IsConnect() == false)
	{

	}
	else
	{
		ChongZhiSend ChongZhiSendMsg;
		int id =CCUserDefault::getInstance()->getIntegerForKey("myid");
		cocos2d::log("id = %d",id);
		ChongZhiSendMsg.account =  htonl(id);
		ptempHallSocket->SendMsgToSocket(&ChongZhiSendMsg, CHONGZHISEND, sizeof(ChongZhiSend));

	}
 
   // SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameHall2.plist","gameHall2.png");
    
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameHall/gameHall3.plist","gameHall/gameHall3.png");
  
	visibleSize = Director::getInstance()->getVisibleSize();//ªÒµ√ø… ”«¯”Úµƒ¥Û–°
	origin = Director::getInstance()->getVisibleOrigin();//ªÒµ√ø… ”«¯”Úµƒ∆ º◊¯±Íori
	curDay = UserDefault::getInstance()->getIntegerForKey("LoginDays");
	cocos2d::log("curDay = %d",curDay);
 
	cocos2d::log("init start 1");

	for(int i = 0 ; i < 11 ; i++)
	{
        //去掉第七关 即钓鱼岛
        int tmpIdx = i;
        if(tmpIdx >= 7)
            tmpIdx += 1;
		sprintf(hallCharTemp,"scenetitle%d.png",tmpIdx+1);
		roomTitleName[i] = hallCharTemp;

		sprintf(hallCharTemp,"hall_scene_room%d.png",tmpIdx+1);
		roomPhotoName[i] = hallCharTemp;

		sprintf(hallCharTemp,"fish_%d_0 (1).png",tmpIdx*2+23);
		roomBossName[i] = hallCharTemp;
	}
 
	//≥ı ºªØ±‰¡ø
	isEnterYu = true;
	isBiSai = false;
	hall_room_direct = true;
	hall_bSetShow = false;			//≤Àµ• «∑Òœ‘ æ
	hall_room_is_moveing = false;	//≈–∂œ∂Øª≠ «∑Ò’˝‘⁄
	scaleTmp = 0.8;				//Àı–°µƒ÷µ
	isDit = true;

	hall_sv_space1 = -1;			//svµƒŒª÷√
	hall_sv_space2 = -1;
	scrollview_begin_m = false;
	dianji_begin_m = false;
	tiaozhanShu = 10 - UserDefault::getInstance()->getIntegerForKey("boss_day_times"); 
	//subLv = UserDefault::getInstance()->getIntegerForKey("subLevel"); 
	laserLv = GameBegin::getFileData("typeJiGuang.txt");           
	scopeLv = GameBegin::getFileData("typeFanWei.txt"); 
	unlockRoomNum = UserDefault::getInstance()->getIntegerForKey("unlockRoomNum"); 
 
	cocos2d::log("init start");
 
    yutime = 0;
    //背景
    hallBackground = Sprite::create("hall_BG.png");
    hallBackground->setPosition(Point(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
    this->addChild(hallBackground); 
    
    
    //背景下方波浪
    auto hallBackground1 = Sprite::createWithSpriteFrameName("hall_bolang.png");
    hallBackground1->setAnchorPoint(Vec2(0,0));
    hallBackground1->setPosition(Vec2(0,0));
    hallBackground->addChild(hallBackground1);
    
    hallBackground1->runAction(RepeatForever::create(Sequence::create(FadeTo::create(2.0f,0),FadeTo::create(2.0f,255),nullptr)));
    
    
    //假山
    auto hallBackground2 = Sprite::createWithSpriteFrameName("hall_jiaoshi.png");
    hallBackground2->setAnchorPoint(Vec2(0,0));
    hallBackground2->setPosition(Vec2(0,0));
    hallBackground->addChild(hallBackground2,10);
    
    auto hall_dating_pl1 = ParticleSystemQuad::create("qipao.plist");
    hall_dating_pl1->retain();
    auto hall_dating_b1 = ParticleBatchNode::createWithTexture(hall_dating_pl1->getTexture());
    hall_dating_b1->addChild(hall_dating_pl1);
    hall_dating_b1->setScale(0.8);
    hall_dating_b1->setPosition(Vec2(hallBackground2->getContentSize().width * 0.1 , hallBackground2->getContentSize().height * 0.5));
    hallBackground2->addChild(hall_dating_b1,-1);
    
    auto hall_dating_pl2 = ParticleSystemQuad::create("qipao.plist");
    hall_dating_pl2->retain();
    auto hall_dating_b2 = ParticleBatchNode::createWithTexture(hall_dating_pl2->getTexture());
    hall_dating_b2->addChild(hall_dating_pl2);
    hall_dating_b2->setPosition(Vec2(hallBackground2->getContentSize().width * 0.05 , hallBackground2->getContentSize().height * 0.6));
    hallBackground2->addChild(hall_dating_b2);
    
    auto hall_dating_pl3 = ParticleSystemQuad::create("qipao.plist");
    hall_dating_pl3->retain();
    auto hall_dating_b3 = ParticleBatchNode::createWithTexture(hall_dating_pl3->getTexture());
    hall_dating_b3->addChild(hall_dating_pl3);
    hall_dating_b3->setPosition(Vec2(hallBackground2->getContentSize().width * 0.95 , hallBackground2->getContentSize().height * 0.3));
    hall_dating_b3->setScale(0.9);
    hallBackground2->addChild(hall_dating_b3,-1);
    
    //雅黑
   /* auto hall_heise_s9p = Scale9Sprite::create("hall_yahei.png");
    hall_heise_s9p->setCapInsets( CCRectMake(3, 3, 3, 327) );
    hall_heise_s9p->setContentSize( CCSizeMake(1024,333) );
    hallBackground->addChild(hall_heise_s9p,20);
    
    hall_heise_s9p->runAction(RepeatForever::create(Sequence::create(FadeTo::create(2.0f,0),FadeTo::create(2.0f,255),nullptr)));
    */
    //太阳光
    auto hall_taiyangguang1 = Sprite::create("hall_yangguang.png");
    hall_taiyangguang1->setPosition(Vec2(visibleSize.width/2,visibleSize.height));
    //hall_taiyangguang1->setScale(0.9);
    this->addChild(hall_taiyangguang1,10);
    
    hall_taiyangguang1->runAction(RepeatForever::create(RotateBy::create(30.0f,360)));
    hall_taiyangguang1->runAction(RepeatForever::create(Sequence::create(FadeTo::create(2.5f,125),FadeTo::create(2.5f,255),nullptr)));
    
    auto hall_taiyangguang2 = Sprite::create("hall_yangguang.png");
    hall_taiyangguang2->setPosition(Vec2(visibleSize.width/2,visibleSize.height));
    hall_taiyangguang2->setOpacity(125);
    //hall_taiyangguang2->setScale(0.9);
    this->addChild(hall_taiyangguang2,10);
    
    hall_taiyangguang2->runAction(RepeatForever::create(RotateBy::create(30.0f,-360)));
    hall_taiyangguang2->runAction(RepeatForever::create(Sequence::create(FadeTo::create(2.5f,255),FadeTo::create(2.5f,125),nullptr)));
 
    randomFish();
    randomFish();
    
	//≥ı ºªØ∞¥≈•
	cocos2d::log("init caidan start");
	initCaiDan();

	cocos2d::log("init caidan");
	//∂•≤ø±≥æ∞
	initDingbu();
	cocos2d::log("init initDingbu");

	//÷–º‰≤ø∑÷*****************
	initZhongJian();
	cocos2d::log("init initZhongJian");

	init_BS1();
	cocos2d::log("init initBSRoom");
 
	//◊Û±ﬂº˝Õ∑
	hall_zuojiantou = Sprite::createWithSpriteFrameName("hall_jitou.png");
	hall_zuojiantou->setPosition(Vec2(visibleSize.width * 0.05 + origin.x,visibleSize.height*0.32 + origin.y));
	addChild(hall_zuojiantou,ANNIULAYER);

	auto moveBt1_1 = MoveBy::create(1.1f,Vec2(-3,0));
	auto scaleTo1_1 = ScaleTo::create(1.1f,0.9);
	auto fadeIn1_1 = FadeOut::create(1.1f);
	auto spanw1_1 = Spawn::create(moveBt1_1,scaleTo1_1,fadeIn1_1,nullptr);

	auto moveBt1_2 = MoveBy::create(1.1f,Vec2(3,0));
	auto scaleTo1_2 = ScaleTo::create(1.1f,1);
	auto fadeIn1_2 = FadeIn::create(1.1f);
	auto spanw1_2 = Spawn::create(moveBt1_2,scaleTo1_2,fadeIn1_2,nullptr);
	hall_zuojiantou->runAction(RepeatForever::create(Sequence::create(spanw1_1,spanw1_2,DelayTime::create(1),nullptr)));

	//”“º˝Õ∑
	hall_youjiantou = Sprite::createWithSpriteFrameName("hall_jitou.png");
	hall_youjiantou->setFlippedX(true);
	hall_youjiantou->setPosition(Vec2(visibleSize.width * 0.95 + origin.x,visibleSize.height*0.32 + origin.y));
	addChild(hall_youjiantou,ANNIULAYER);

	auto moveBt2_1 = MoveBy::create(1.1f,Vec2(3,0));
	auto scaleTo2_1 = ScaleTo::create(1.1f,0.9);
	auto fadeIn2_1 = FadeOut::create(1.1f);
	auto spanw2_1 = Spawn::create(moveBt2_1,scaleTo2_1,fadeIn2_1,nullptr);

	auto moveBt2_2 = MoveBy::create(1.1f,Vec2(-3,0));
	auto scaleTo2_2 = ScaleTo::create(1.1f,1);
	auto fadeIn2_2 = FadeIn::create(1.1f);
	auto spanw2_2 = Spawn::create(moveBt2_2,scaleTo2_2,fadeIn2_2,nullptr);
	hall_youjiantou->runAction(RepeatForever::create(Sequence::create(spanw2_1,spanw2_2,DelayTime::create(1),nullptr)));

    bs1_zuozi = Sprite::createWithSpriteFrameName("bs_room_word1.png");
    bs1_zuozi->setPosition(Vec2(65,20));
    bs1_zuozi->setAnchorPoint(Vec2(0,0.5));
    bs1_zuozi->setScale(0.8);
    bs1_zuozi->setVisible(false);
    hall_zuojiantou->addChild(bs1_zuozi);

    bs1_youzi = Sprite::createWithSpriteFrameName("bs_room_word1.png");
    bs1_youzi->setPosition(Vec2(0,20));
    bs1_youzi->setScale(0.8);
    bs1_youzi->setAnchorPoint(Vec2(1,0.5));
    bs1_youzi->setVisible(false);
    hall_youjiantou->addChild(bs1_youzi);
    
	//*********¥ÛÃ¸µ◊≤ø
	cocos2d::log("init initDibu1");
	initDibu();
	cocos2d::log("init initDibu");

	int tmpScrollView = UserDefault::getInstance()->getIntegerForKey("bisaimoshi");  //0 ,µ•ª˙ƒ£ Ω   1£¨±»»¸ƒ£ Ω
	if(tmpScrollView == 0)
	{
		//µØ≥ˆ±»»¸Ã· æ
		if(UserDefault::getInstance()->getIntegerForKey("ishadmatch") == 0 && GameBegin::getFileData("gamePlayerlv.txt") > 5)
		{
			auto gongxi = Gongxi::create(3,GAME_DATA_STRING("frist_match_tishi"));
			gongxi->setPosition(Point::ZERO);
			this->addChild(gongxi,MENULAYER + 1000,777);

			auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png" );
			auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(GameHallLayer::first_match_tishi,this));
			auto btnMenu = Menu::create(quedingItem,nullptr);
			btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
			gongxi->getChildByTag(1)->addChild(btnMenu,100);
		}
		

		isBiSai = false;
		
		//bs1_room_bg->setOpacity(0);
		bs1_room_bg->setVisible(false);
		bs1_room_bg->setScale(0.1);
		bs1_room_bg->setZOrder(ANNIULAYER - 1);

		/*scrollView1->setOpacity(0);
		scrollView1->setVisible(false);
		scrollView1->setScale(0.1);
		scrollView1->setZOrder(ANNIULAYER - 1);*/

		hall_sc_bgguang->setVisible(false);
		hall_Shop->setVisible(false);
		GameBegin::stopMusic();
		GameBegin::playMusic("bgmusic.mp3",1);
	}
	if(tmpScrollView == 1)
	{
		isBiSai = true;

		//scrollView->setOpacity(0);
		scrollView->setVisible(false);
		scrollView->setScale(0.1);
		scrollView->setZOrder(ANNIULAYER - 1);

		hall_sc_bgguang->setVisible(true);
		hall_Shop->setVisible(true);

		GameBegin::stopMusic();
        if(CCRANDOM_0_1() < 0.5)
            GameBegin::playMusic("bgmusic.mp3",4);
        else
            GameBegin::playMusic("",7);
	}
	/*auto hall_room_Particle1 = ParticleSystemQuad::create("qipao.plist");
	hall_room_Particle1->setPosition(Vec2(visibleSize.width * 0.1 , visibleSize.height * 0.1));
	hall_room_Particle1->retain();
	auto hall_room_batch1 = ParticleBatchNode::createWithTexture(hall_room_Particle1->getTexture()); 
	hall_room_batch1->addChild(hall_room_Particle1); 
	hall_room_batch1->setOpacity(255);
	this->addChild(hall_room_batch1); */

	auto hall_room_Particle3 = ParticleSystemQuad::create("qipao.plist");
	hall_room_Particle3->setPosition(Vec2(visibleSize.width * 1.56, visibleSize.height * 0.5));
	hall_room_Particle3->retain();
	auto hall_room_batch3 = ParticleBatchNode::createWithTexture(hall_room_Particle3->getTexture()); 
	hall_room_batch3->addChild(hall_room_Particle3); 
	hall_room_batch3->setScale(0.5);
	hall_room_batch3->setOpacity(200);
	this->addChild(hall_room_batch3); 

	auto hall_room_Particle2 = ParticleSystemQuad::create("qipao.plist");
	hall_room_Particle2->setOpacity(100);
	hall_room_Particle2->setPosition(Vec2(visibleSize.width * 0.58 , visibleSize.height * 1.2));
	hall_room_Particle2->retain();
	auto hall_room_batch2 = ParticleBatchNode::createWithTexture(hall_room_Particle2->getTexture()); 
	hall_room_batch2->addChild(hall_room_Particle2); 
	hall_room_batch2->setScale(0.3);
	hall_room_batch3->setOpacity(150);
	this->addChild(hall_room_batch2); 


	//√ø»’µ«¬º
	//int logindasTmp = UserDefault::getInstance()->getIntegerForKey("LoginDays");
	cocos2d::log("init LoginDays logindasTmp = %d" , curDay);
	if(curDay == 0)
	{
		cocos2d::log("init LoginDays");
		LoginReward* loginscene = LoginReward::create(1);
		loginscene->setPosition(Point::ZERO);
		this->addChild(loginscene,MENULAYER);
		cocos2d::log("init LoginDays end");
	}
	else
	{
		cocos2d::log("init LoginDays 1");
		time_t prevTime = UserDefault::getInstance()->getIntegerForKey("prevTime");
		int loginDays = UserDefault::getInstance()->getIntegerForKey("LoginDays")%7;
		time_t currentTime;
		time(&currentTime);
		if(currentTime>prevTime ) //&& currentTime<prevTime + 24*60*60
		{
            
            LoginReward* loginscene = LoginReward::create(loginDays+1);
			loginscene->setPosition(Point::ZERO);
			this->addChild(loginscene,MENULAYER);
		}
		cocos2d::log("init LoginDays 1 end");
	}

	
	 cocos2d::log("init LoginReward  end ");

	 //≥ı ºªØ ∂Øª≠∂Ø◊˜
	for(int k = 0 ; k < 11; k ++)
	{
        int tmpIdx = k;
        if(tmpIdx >= 7)
            tmpIdx += 1;
		//boss∂Øª≠ 
		sprintf(hallCharTemp,"fish_animationwf_%d_%d",UserDefault::getInstance()->getIntegerForKey("ios_room"),2*tmpIdx+23);
		hall_boss_a.pushBack(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(hallCharTemp)))) ;

		//ÀÆ≤›∂Øª≠
		hall_shuicao1_a.pushBack(RepeatForever::create( Animate::create(AnimationCache::getInstance()->getAnimation("hall_shuichao"))));
		hall_shuicao2_a.pushBack(RepeatForever::create( Animate::create(AnimationCache::getInstance()->getAnimation("hall_shuichao"))->reverse()));

		//¡¡π‚
		lg_fadeIn.pushBack(FadeIn::create(0.4f));
		lg_fadeOut.pushBack( FadeOut::create(0.4f));
	}

	this->scheduleOnce(schedule_selector(GameHallLayer::init_1),0.1f);
 
    randomFish();
    randomFish();
	return true;
} 

void GameHallLayer::randomFish()
{
    //随机鱼的种类1-6
    int fish_kind = (int)(CCRANDOM_0_1() * 100000) % 3 + 1;
    //fish_kind = 8;
    if(fish_kind == 3)//水母
    {
        sprintf(hallCharTemp,"hall_fish_shang_%d (1).png",1);
        auto fish_sp = Sprite::createWithSpriteFrameName(hallCharTemp);
        //fish_sp->setOpacity(50);
        //fish_sp->setScale(0.01);
        hallBackground->addChild(fish_sp,10);
        
        sprintf(hallCharTemp,"hall_fish_shang_animate_%d",1);
        fish_sp->runAction(RepeatForever::create( Animate::create(AnimationCache::getInstance()->getAnimation(hallCharTemp))));
        
        float speed = (CCRANDOM_0_1() + 1) * 15;    //速度
        if(CCRANDOM_0_1() < 1.1)
        {
            float width  = CCRANDOM_0_1() * 1423.99 - 200;	//x值
            float heigh = -30.0f;								//y值
            Vec2 moveWitd;									//要移动的vec
            bool fangxiang = CCRANDOM_0_1() > 0.5 ? true : false;  //方向
            float thda = CCRANDOM_0_1() * M_PI/3;
            if(width < 300)
            {
                fangxiang = true;
                
            }
            if( width > 700)
            {
                fangxiang = false;
            }
            if(!fangxiang)
            {
                thda = -thda;
            }
            fish_sp->setRotation(thda * 180 / M_PI);
            moveWitd = Vec2(tan(thda) * 800 , 800);
            fish_sp->setPosition(Vec2(width,heigh));
            fish_sp->runAction(Sequence::create(MoveBy::create(speed ,moveWitd),RemoveSelf::create(),nullptr));
        }
        
    }else if(fish_kind == 2)//斜鱼
    {
        sprintf(hallCharTemp,"hall_fish_ce_%d_1.png",1);
        auto fish_sp = Sprite::createWithSpriteFrameName(hallCharTemp);
        //fish_sp->setOpacity(50);
        fish_sp->setScale(0.01);
        hallBackground->addChild(fish_sp,10);
        
        sprintf(hallCharTemp,"hall_fish_ce_animate_%d",1);
        fish_sp->runAction(RepeatForever::create( Animate::create(AnimationCache::getInstance()->getAnimation(hallCharTemp))));
        
        
        float speed = (CCRANDOM_0_1() + 1) * 15;   //速度
        float width  = CCRANDOM_0_1() * 1024.99;	//x值
        float heigh = 350.0f;						//y值
        Vec2 moveWitd;								//要移动的vec
        bool fangxiang = CCRANDOM_0_1() > 0.5 ? true : false;  //方向
        
        if(width < 612)
        {
            fish_sp->setFlippedX(true);
            moveWitd = Vec2(tan(1.0f/4.0f * M_PI) * 420 , -420);
        }else
        {
            moveWitd = Vec2(-tan(1.0f/4.0f * M_PI) * 420 , -420);
        }
        
        fish_sp->setPosition(Vec2(width,heigh));
        fish_sp->runAction(Sequence::create(Spawn::create(EaseExponentialIn::create(MoveBy::create(speed ,moveWitd)),EaseExponentialIn::create(ScaleTo::create(speed , 1.7)),nullptr),RemoveSelf::create(),nullptr));
        
    }else
    {
        return;
        //随机鱼的速度系数 1，1.2，1.4，1.6
        int speed_xi = CCRANDOM_0_1() + 1;
        //随机高度
        float high;
        float width;
        Vec2 moveWitd;
 
        high = CCRANDOM_0_1() * 300 + 150;
 
        //随机方向
        bool fangxiang = CCRANDOM_0_1() > 0.5 ? true : false;
        if(fangxiang)
        {
            width = -50;
            moveWitd = Vec2(1200,0);
        }else
        {
            width = 1075;
            moveWitd = Vec2(-1200,0);
        }
        
        //高度决定大小（0.2-1）和速度（2-10）
        float scale;
        if(high > 300)
        {
            scale = (high - 300.0f) / 400.0f;
            if(scale < 0.1)
                scale = 0.1;
        }else
        {
            scale = 0.3;
        }
        float spped = scale * 10 * speed_xi;
        
 
        auto fish_sp = Sprite::create();
        fish_sp->setPosition(Vec2(width,high));
        if(fish_kind != 1)
        {
            fish_sp->setRotation(90);
        }else
        {
            fish_sp->setRotation(-90);
        }
        
        fish_sp->setScale(scale);
        hallBackground->addChild(fish_sp,8);
        
        fish_sp->setOpacity(255 * scale);
        
        if(scale != 1)
        {
            fish_sp->setZOrder(7);
        }
        if(!fangxiang)
        {
            fish_sp->setFlippedX(true);
        }
        
        sprintf(hallCharTemp,"fish_animationwf_%d_%d",GameHallLayer::boss_fish_room,fish_kind+22);
        fish_sp->runAction(RepeatForever::create( Animate::create(AnimationCache::getInstance()->getAnimation(hallCharTemp))));
        fish_sp->runAction(Sequence::create(MoveBy::create(200.0f/spped,moveWitd),RemoveSelf::create(),nullptr));
    }
}

void GameHallLayer::first_match_tishi()
{
	this->removeChildByTag(777);
    
    GameHallLayer::RoomType = 90;
    
	hall_bisai_func(this);
	hall_baoming_func1(0.1f);
}

void GameHallLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) 
{    
	switch(keyCode)     
	{     
		//º‡Ã˝∑µªÿº¸        
    case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			if(false ) //!GameHallLayer::exitIsCun
			{
				GameHallLayer::exitIsCun = true;
				//ÕÀ≥ˆ∑øº‰Ã· æ
				string exitTmp = GAME_DATA_STRING("gamehall_exit");
				auto gongxi = Gongxi::create(3,exitTmp);
				gongxi->setPosition(Point::ZERO);
				this->addChild(gongxi,MENULAYER + 1000,1000);

				auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png");
				auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(GameHallLayer::queding,this));

				auto btnMenu = Menu::create(quedingItem,nullptr);
				btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
				gongxi->getChildByTag(1)->addChild(btnMenu,100);

			}
            this->removeAllChildrenWithCleanup(true);
            this->unscheduleAllSelectors();
            this->stopAllActions();
            
            Scene* scene = GameBegin::createScene();
            Director::getInstance()->replaceScene(scene);
		}
		break;        
 
	default:break;
	}
}

void  GameHallLayer::init_1(float dt)
{
	cocos2d::log("init_1 LoginDays 1");
 
	//ÃÙ’Ω∞¥≈•∂Ø◊˜
	auto scaleTo_tz1 = ScaleTo::create(0.5f,0.6);
	auto scaleTo_tz2 = ScaleTo::create(0.5f,0.75);
	tiaozhanShuZi->runAction(RepeatForever::create(Sequence::create(scaleTo_tz1,scaleTo_tz2,DelayTime::create(0.5f),nullptr)));
 
	//∏¸–¬Œª÷√
	if(!isBiSai )  //0 ,µ•ª˙ƒ£ Ω   1£¨±»»¸ƒ£ Ω
	{		
		hall_gengzheng();
		for(int k = 0 ; k < 4 ; k++)
		{
			hall_tishi_vec.at(k)->setVisible(false);
		}
		//ø™ º∫Ïµ„ºÏ≤‚
		checkRedPoing = true;
	}		
	else
	{
		hall_menu_bs->setVisible(false);
		hall_menu_bsT->setVisible(true);
		tiaozhanHongQ->setVisible(false);
		tiaozhanShuZi->setVisible(false);
		hall_dibu_beilv_xing->setVisible(false);
		hall_dibu_dapao_xing->setVisible(false);
		hall_dibu_shop_xing->setVisible(false);
		checkRedPoing = false;

        hall_zuojiantou->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bs_jiantou.png"));
        hall_youjiantou->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bs_jiantou.png"));
        bs1_zuozi->setVisible(true);
        bs1_youzi->setVisible(true);
        
		//BS_gengzheng();
		isCheckBS = true;
	}
		
	//≈–∂œ «∑Ò≥ˆœ÷…Ò√ÿ…Ã»À
	chuxianShop();
 
	//ÃÌº”¥•√˛ ¬º˛
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameHallLayer::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(GameHallLayer::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(GameHallLayer::onTouchEnded,this);
	listener->setSwallowTouches(true);//≤ªœÚœ¬¥´µ›¥•√˛
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	//ÃÌº”º¸≈Ã ¬º˛
	EventListenerKeyboard* kblsnr = EventListenerKeyboard::create(); 
	kblsnr->onKeyReleased = CC_CALLBACK_2(GameHallLayer::onKeyReleased, this); 
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(kblsnr, this); 
	this->scheduleUpdate();
	cocos2d::log("init_1 LoginDays 2");

	//ÃÌº”◊‘∂®“Â ¬º˛
	auto myEvent = EventListenerCustom::create(kCUSTEVENT_HDHF_CS,CC_CALLBACK_0(GameHallLayer::oters_to_bsroom,this));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(myEvent,1);

	auto myEvent1 = EventListenerCustom::create(kCUSTEVENT_HDHF_VIP,CC_CALLBACK_0(GameHallLayer::tanchuVip,this));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(myEvent1,1);

    
	auto myEvent2 = EventListenerCustom::create(kCUSTEVENT_DHHF,CC_CALLBACK_0(GameHallLayer::duihuanHuanfei,this));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(myEvent2,1);

	auto myEvent3 = EventListenerCustom::create(kCUSTEVENT_HB_JS,CC_CALLBACK_0(GameHallLayer::hb_onclick_jishi,this));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(myEvent3,1);
    
    auto myEvent4 = EventListenerCustom::create(kCUSTEVENT_XGHFQ,CC_CALLBACK_0(GameHallLayer::duihuan_xiugai_huanfeiquan,this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(myEvent4,1);
	
}



size_t  GameHallLayer::gonggao_return(uint8_t *buffer,size_t size,size_t nmemb,void *stream)
{
	//¥Ú”° ’µΩµƒ ˝æ›
	cocos2d::log("SHOP::*****possIt_____%s____",(const char *)buffer);	
	string userTmp = (const char *)buffer;
	if(userTmp == "null")
	{
		return size*nmemb;
	}

	char tmp1[255]= ""; //title
	char tmp2[255]= ""; //content
 
	char tmp3[10] = ""; //yubi
	char tmp4[10] = ""; //zuanshi
	char tmp5[10] = ""; //huafeiquan
	char tmp6[10] = ""; //version
 
	int i=0;
	int j=0;
	int m = 0;

	while(buffer[i]!='\0')
	{
		char c = buffer[i];
		if(c=='-')
		{
			j++;	
			m = 0;
		}
		else
		{
			if(j == 0)
			{
				tmp1[m] = c;				
			}
			if(j == 1)
			{
				tmp2[m] = c;
			}
			if(j == 2)
			{
				tmp3[m] = c;
			}

			if(j == 3)
			{
				tmp4[m] = c;
			}
			if(j == 4)
			{
				tmp5[m] = c;
			}
			if(j == 5)
			{
				tmp6[m] = c;
			} 
			m++;
		}
		i++;
	}

	int version_cur = atoi((const char *)tmp6);
	int version_pro = UserDefault::getInstance()->getIntegerForKey("gonggao_version");

	if(version_cur > version_pro)
	{
		gonggao_vis_flag = true;
		UserDefault::getInstance()->setIntegerForKey("gonggao_version",version_cur);
		UserDefault::getInstance()->setStringForKey("gg_title",(const char *)tmp1);
		UserDefault::getInstance()->setStringForKey("gg_content",(const char *)tmp2);
		UserDefault::getInstance()->setIntegerForKey("gg_yubi",atoi((const char *)tmp3));
		UserDefault::getInstance()->setIntegerForKey("gg_zuanshi",atoi((const char *)tmp4));
		UserDefault::getInstance()->setIntegerForKey("gg_huafeiquan",atoi((const char *)tmp5));
		UserDefault::getInstance()->setIntegerForKey("gg_lingqu",1);
		UserDefault::getInstance()->flush();
	}
 
	//∑µªÿ ˝æ›≥§∂»
	size_t sizes = size*nmemb;
	return sizes;
}


//◊‘∂®“Â ¬º˛
void GameHallLayer::oters_to_bsroom()
{
	hall_bisai_func(this);
}

void GameHallLayer::duihuan_xiugai_huanfeiquan()
{
    sprintf(hallCharTemp,"%d",GameBegin::getFileData("wfsound.txt"));
    jiangbeiLayer->setString(hallCharTemp);
}
 
void GameHallLayer::tanchuVip()
{
	auto scene = Shop::create(4);
	this->addChild(scene,MENULAYER);
}

void GameHallLayer::duihuanHuanfei()
{
    
	auto gongxi = Game_Hall_Huafei::createScene();
	this->addChild(gongxi,MENULAYER);
}
 
void GameHallLayer::hb_onclick_jishi()
{
    if(hall_hb_anniu)
    {
        hall_hb_anniu->setPosition(Vec2(50 + origin.x ,visibleSize.height - 140 + origin.y));
        hall_hb_anniu->stopAllActions();
        hall_hb_kaiguan =false;
        this->schedule(schedule_selector(GameHallLayer::updateHB),1.0f);
    }
}
 
//±‡º≠–≈œ¢∫Ø ˝
void GameHallLayer::xzTouxiang(Ref* pSender)
{
	this->stopAllActions();
	this->removeAllChildrenWithCleanup(true);
	this->unscheduleAllSelectors();
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
    
 
	auto scene = InitPlayer::createScene();
	Director::getInstance()->replaceScene(scene);
	/*if(!isEditTx)
	{
		isEditTx = true;
		for(int i = 0 ; i < 8 ; i++)
		{
			Touxiang.at(i)->setVisible(true);
			Touxiang.at(i)->runAction(MoveBy::create(0.5f,Vec2(0,-(i+1)*75)));
		}
	}else
	{
		isEditTx = false;
		for(int i = 0 ; i < 8 ; i++)
		{
			Touxiang.at(i)->setVisible(true);
			Touxiang.at(i)->runAction(MoveBy::create(0.5f,Vec2(0,(i+1)*75)));
		}
		this->scheduleOnce(schedule_selector(GameHallLayer::qd_jiesu),0.5f);
	}*/	
}

void GameHallLayer::qdTouxiang(Ref* pSender)
{
	if(isEditTx)
	{
		isEditTx = false;
		int tx = ((MenuItemSprite *)(pSender))->getTag();
		for(int i = 0 ; i < 8 ; i++)
		{
			Touxiang.at(i)->setZOrder(0);
			Touxiang.at(i)->runAction(MoveBy::create(0.5f,Vec2(0,(i+1)*75)));
		}
		Touxiang.at(tx-1)->setZOrder(1);
		UserDefault::getInstance()->setIntegerForKey("player_touxiang",tx);
		UserDefault::getInstance()->flush();
		this->scheduleOnce(schedule_selector(GameHallLayer::qd_jiesu),0.5f);
	}
}

void GameHallLayer::qd_jiesu(float dt)
{
	for(int i = 0 ; i < 8 ; i++)
	{
		if(i != UserDefault::getInstance()->getIntegerForKey("player_touxiang")-1)
			Touxiang.at(i)->setVisible(false);
	}
}

//∂“ª∞∑—
void GameHallLayer::hall_kefu_func(Ref* pSender)
{
	GameBegin::buttonSound(); 
 
	auto layer = Game_Hall_Kefu::createScene();
	this->addChild(layer,MENULAYER);
}

void GameHallLayer::hall_more_func(Ref* pSender)
{
	GameBegin::buttonSound(); 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	//Application::getInstance()->moreGame("www.baidu.com");
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
		jobject jobj;
		if( JniHelper::getStaticMethodInfo(minfo,"org.cocos2dx.cpp.AppActivity","startLoginWithType","(I)V") )
		{	
			jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID,98); //98
			minfo.env->DeleteLocalRef(minfo.classID);		
		}
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//Application::getInstance()->moreGame( );
#endif
}

void GameHallLayer::hall_bisai_func(Ref* pSender)
{
	if(isDit && !isBiSai)
	{
		isDit = false;
		this->scheduleOnce(schedule_selector(GameHallLayer::BS_anniu_dit),0.71f);

		GameBegin::buttonSound(); 
		GameBegin::stopMusic();
        if(CCRANDOM_0_1() < 0.5)
            GameBegin::playMusic("bgmusic.mp3",4);
        else
            GameBegin::playMusic("",7);
		isBiSai = true;
		hall_sc_bgguang->setVisible(true);
		hall_Shop->setVisible(true);
		UserDefault::getInstance()->setIntegerForKey("bisaimoshi",1);  //0 ,µ•ª˙ƒ£ Ω   1£¨±»»¸ƒ£ Ω
		UserDefault::getInstance()->flush();

		BS_qiehuan();
        
        hall_zuojiantou->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bs_jiantou.png"));
        hall_youjiantou->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bs_jiantou.png"));
        bs1_zuozi->setVisible(true);
        bs1_youzi->setVisible(true);

		this->scheduleOnce(schedule_selector(GameHallLayer::BS_gengzheng),0.71f);

		for(int k = 0 ; k < 4 ; k++ )
		{
			if(k + 1 == bs_moshi)
			{
				hall_tishi_vec.at(k)->setVisible(true);
				break;
			}	
		}

		hall_menu_bs->setVisible(false);
		hall_menu_bsT->setVisible(true);
		tiaozhanHongQ->setVisible(false);
		tiaozhanShuZi->setVisible(false);
		hall_dibu_beilv_xing->setVisible(false);
		hall_dibu_dapao_xing->setVisible(false);
		hall_dibu_shop_xing->setVisible(false);
		checkRedPoing = false;
		isCheckBS = true;

		Animate  * hall_menu_cl_dh1  = Animate::create(AnimationCache::getInstance()->getAnimation("hall_jiesuo"));
		hall_dibu_sprite_jiesuo->runAction(hall_menu_cl_dh1);
		Animate  * hall_menu_cl_dh2  = Animate::create(AnimationCache::getInstance()->getAnimation("hall_shangcheng"));
		hall_dibu_sprite_shangcheng->runAction(hall_menu_cl_dh2);
		Animate  * hall_menu_cl_dh3  = Animate::create(AnimationCache::getInstance()->getAnimation("hall_jineng"));
		hall_dibu_sprite_jineng->runAction(hall_menu_cl_dh3);
		Animate  * hall_menu_cl_dh4  = Animate::create(AnimationCache::getInstance()->getAnimation("hall_tiaozhan"));
		hall_dibu_sprite_tiaozhan->runAction(hall_menu_cl_dh4);
	}else
    {
        BS_checkAll();
    }
}
 
void GameHallLayer::hall_bisaiT_func(Ref* pSender)
{
	if(isDit && isBiSai)
	{
		isDit = false;
		this->scheduleOnce(schedule_selector(GameHallLayer::BS_anniu_dit),0.71f);

		GameBegin::buttonSound(); 
		GameBegin::stopMusic();
		GameBegin::playMusic("bgmusic.mp3",1);

		isBiSai = false;
		hall_sc_bgguang->setVisible(false);
		hall_Shop->setVisible(false);
		UserDefault::getInstance()->setIntegerForKey("bisaimoshi",0);  //0 ,µ•ª˙ƒ£ Ω   1£¨±»»¸ƒ£ Ω
		UserDefault::getInstance()->flush();

		BS_qiehuan();
        
        hall_zuojiantou->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hall_jitou.png"));
        hall_youjiantou->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hall_jitou.png"));
        bs1_zuozi->setVisible(false);
        bs1_youzi->setVisible(false);

		for(int k = 0 ; k < 4 ; k++ )
		{
			hall_tishi_vec.at(k)->setVisible(false);
		}

		hall_menu_bsT->setVisible(false);
		hall_menu_bs->setVisible(true);
		tiaozhanHongQ->setVisible(true);
		tiaozhanShuZi->setVisible(true);
		hall_dibu_shop_xing->setVisible(true);
		checkRedPoing = true;

		Animate  * hall_menu_cl_dh1  = Animate::create(AnimationCache::getInstance()->getAnimation("hall_jiesuo"));
		hall_dibu_sprite_jiesuo->runAction(hall_menu_cl_dh1->reverse());
		Animate  * hall_menu_cl_dh2  = Animate::create(AnimationCache::getInstance()->getAnimation("hall_shangcheng"));
		hall_dibu_sprite_shangcheng->runAction(hall_menu_cl_dh2->reverse());
		Animate  * hall_menu_cl_dh3  = Animate::create(AnimationCache::getInstance()->getAnimation("hall_jineng"));
		hall_dibu_sprite_jineng->runAction(hall_menu_cl_dh3->reverse());
		Animate  * hall_menu_cl_dh4  = Animate::create(AnimationCache::getInstance()->getAnimation("hall_tiaozhan"));
		hall_dibu_sprite_tiaozhan->runAction(hall_menu_cl_dh4->reverse());
	}
}

void GameHallLayer::BS_anniu_dit(float dt)
{
	isDit = true;
}

void GameHallLayer::BS_qiehuan()
{
	bs1_room_bg->setVisible(true);
	scrollView->setVisible(true);
	float q_time = 0.35f;
	if(!isBiSai)
	{
		auto spawn1 = Spawn::create(ScaleTo::create(q_time,1/2),MoveBy::create(q_time,Vec2(-roomSize1.width/2,0)),nullptr);
		auto cal1 = CCCallFunc::create(CC_CALLBACK_0(GameHallLayer::BS_qh_order,this));
		auto spawn2 = Spawn::create(MoveBy::create(q_time,Vec2(roomSize1.width/2,0)),ScaleTo::create(q_time,1),nullptr);
		auto visible1 = Show::create();
		auto seq1 = Sequence::create(spawn1,cal1,spawn2,visible1,nullptr);

		auto spawn11 = Spawn::create(ScaleTo::create(q_time,scaleTmp/2),MoveBy::create(q_time,Vec2(roomSize1.width/2,0)),nullptr);
		auto cal11 = CCCallFunc::create(CC_CALLBACK_0(GameHallLayer::BS_qh_order,this));
		auto spawn21 = Spawn::create(MoveBy::create(q_time,Vec2(-roomSize1.width/2,0)),ScaleTo::create(q_time,0.1),nullptr);
		auto visible2 = Hide::create();
		auto seq2 = Sequence::create(spawn11,cal11,spawn21,visible2,nullptr);
 
		scrollView->runAction(seq1);
		bs1_room_bg->runAction(seq2);
	}else
	{
		auto spawn1 = Spawn::create(ScaleTo::create(q_time,scaleTmp/2),MoveBy::create(q_time,Vec2(roomSize1.width/2,0)),nullptr);
		auto cal1 = CCCallFunc::create(CC_CALLBACK_0(GameHallLayer::BS_qh_order,this));
		auto spawn2 = Spawn::create(MoveBy::create(q_time,Vec2(-roomSize1.width/2,0)),ScaleTo::create(q_time,scaleTmp - 0.05f),nullptr);
		auto visible1 = Show::create();
		auto seq1 = Sequence::create(spawn1,cal1,spawn2,visible1,nullptr);

		auto spawn11 = Spawn::create(ScaleTo::create(q_time,1/2),MoveBy::create(q_time,Vec2(-roomSize1.width/2,0)),nullptr);
		auto cal11 = CCCallFunc::create(CC_CALLBACK_0(GameHallLayer::BS_qh_order,this));
		auto spawn21 = Spawn::create(MoveBy::create(q_time,Vec2(roomSize1.width/2,0)),ScaleTo::create(q_time,0.1),nullptr);
		auto visible2 = Hide::create();
		auto seq2 = Sequence::create(spawn11,cal11,spawn21,visible2,nullptr);

		bs1_room_bg->runAction(seq1);
		scrollView->runAction(seq2);
	}
}

void GameHallLayer::BS_qh_order()
{
	if(isBiSai)
	{
		scrollView->setZOrder(ANNIULAYER);
		bs1_room_bg->setZOrder(ANNIULAYER+1);
	}
	else
	{
		scrollView->setZOrder(ANNIULAYER + 1);
		bs1_room_bg->setZOrder(ANNIULAYER);
	}
}

void GameHallLayer::hall_bs_xiangqing_func(Ref* pSender)
{
	GameBegin::buttonSound(); 
	int i =  UserDefault::getInstance()->getIntegerForKey("BS_moshi");  //1 - 4

	sprintf(hallCharTemp,"di %d room info",i);
	auto gongxi = Game_BS_XiangQ::createScene();
	this->addChild(gongxi,MENULAYER);
}
 
void GameHallLayer::hall_baoming_func(Ref* pSender)
{
	GameBegin::buttonSound(); 
 
//	int i = UserDefault::getInstance()->getIntegerForKey("BS_moshi");  // 1- 4
 
	GameHallLayer::RoomType = 89 + bs_moshi;

	//Ω¯»Îvipœﬁ÷∆
	if(bs_moshi == 4 && UserDefault::getInstance()->getIntegerForKey("player_vip") == 0)
	{
		auto gongxi = Gongxi::create(3,GAME_DATA_STRING("bushi_vip"));
		gongxi->setPosition(Point::ZERO);
		this->addChild(gongxi,1000,999);

		auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png" );
		auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_1(GameHallLayer::baoming_vip,this));
		auto btnMenu = Menu::create(quedingItem,nullptr);
		btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
		gongxi->getChildByTag(1)->addChild(btnMenu,100);
		return;
	}

	//Ω¯»Îœﬁ÷∆µ»º∂
	sprintf(hallCharTemp,"bs_room_%d_dengji",bs_moshi);
	int bs_dengji = GAME_DATA_INT(hallCharTemp);

	if(GameBegin::getFileData("gamePlayerlv.txt") < bs_dengji)
	{
		sprintf(hallCharTemp,GAME_DATA_STRING("gamehall_level_low"),bs_dengji);
		auto qiantaiduo = Gongxi::create(2,hallCharTemp);
		qiantaiduo->setPosition(Vec2::ZERO);
		addChild(qiantaiduo,1000);
		return;
	}
    

	//Ω¯»Îœﬁ÷∆±∂¬ 
	/*sprintf(hallCharTemp,"bs_room_%d_jsbeilv",bs_moshi);
	int bs_beilv = GAME_DATA_INT(hallCharTemp);
	int bs_pao = GameBegin::getFileData("gameMaxPao.txt");
	if(bs_pao < bs_beilv)
	{
		sprintf(hallCharTemp,"bljs_rate_%d",bs_beilv);
		int beilv = GAME_DATA_INT(hallCharTemp);
		sprintf(hallCharTemp,GAME_DATA_STRING("gamehall_beilv_low"),beilv);
		auto qiantaiduo = Gongxi::create(2,hallCharTemp);
		qiantaiduo->setPosition(Vec2::ZERO);
		addChild(qiantaiduo,1000);
		return;
	}*/

	//Ω¯»Îœﬁ÷∆Ω±“
	sprintf(hallCharTemp,"bs_room_%d_jinbi",bs_moshi);
	int bs_jinbi = GAME_DATA_INT(hallCharTemp);
	if(GameBegin::getFileData("jywer.txt") < bs_jinbi)
	{
		sprintf(hallCharTemp,GAME_DATA_STRING("gamehall_yubi_low"),bs_jinbi);
		auto qiantaiduo = Gongxi::create(2,hallCharTemp);
		qiantaiduo->setPosition(Vec2::ZERO);
		addChild(qiantaiduo,1000);
		return;
	}
	if(bs_moshi == 1 || bs_moshi == 2)
	{
		sprintf(hallCharTemp,"bs_room_%d_jinbi1",bs_moshi);
		int bs_jinbi = GAME_DATA_INT(hallCharTemp);
		if(GameBegin::getFileData("jywer.txt") > bs_jinbi)
		{ 
			auto qiantaiduo = Gongxi::create(2,GAME_DATA_STRING("qiantaiduo"));
			qiantaiduo->setPosition(Vec2::ZERO);
			addChild(qiantaiduo,1000);
			return;
		}
	}
	

	auto gongxi = Gongxi::create(3,GAME_DATA_STRING("baoming_ing"));
	this->addChild(gongxi,1010,998);

	this->scheduleOnce(schedule_selector(GameHallLayer::hall_baoming_func1),0.5f);
 
}

void GameHallLayer::hall_baoming_func1(float dt)
{
	//¡™Õ¯—È÷§

/*	CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
	if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "www.baidu.com");  //www.baidu.com
		curl_easy_setopt(curl,CURLOPT_TIMEOUT,1000);
		curl_easy_setopt(curl,CURLOPT_POSTFIELDS,"R = 10");
        res=curl_easy_perform(curl);
        if(res!=CURLE_OK)
        {
			if(pingTimes == 5)
			{
				this->removeChildByTag(998);
				 
				//¡™Õ¯ ß∞‹	
				auto gongxi = Gongxi::create(2,GAME_DATA_STRING("check_order_13"));
				gongxi->setPosition(Point::ZERO);
				this->addChild(gongxi,1000,999);
			}else
			{
				pingTimes++;
				GameHallLayer::hall_baoming_func1(0);
			}
			cocos2d::log("pingTimes = %d",pingTimes);
			return ;
        } 
        curl_easy_cleanup(curl);
    }
    else
    {
		if(pingTimes == 5)
		{
			pingTimes = 0;
			this->removeChildByTag(998);
			//¡™Õ¯ ß∞‹	
			auto gongxi = Gongxi::create(2,GAME_DATA_STRING("check_order_13"));
			gongxi->setPosition(Point::ZERO);
			this->addChild(gongxi,1000,999);
		}else
		{
			pingTimes++;	
			GameHallLayer::hall_baoming_func1(0);
		}
		cocos2d::log("pingTimes = %d",pingTimes);
        return ;
    }*/

	this->removeChildByTag(998);
 
	//÷ÿ÷√µ±«∞◊ÓµÕpao∫Õ ◊Ó∏ﬂpao
	char sceneLowRateTmp[20];
	sprintf(sceneLowRateTmp,"bs_room_%d_zdbeilv",bs_moshi);
	char sceneHighRateTmp[20];
	sprintf(sceneHighRateTmp,"bs_room_%d_zgbeilv",bs_moshi);
	GameHallLayer::sceneLowPao = GAME_DATA_INT(sceneLowRateTmp);
	GameHallLayer::sceneHighPao = GAME_DATA_INT(sceneHighRateTmp);


    
    LoadRes::RoomType =GameHallLayer::RoomType;
    
    
	auto layer = MatchPlayer::createScene();
	this->addChild(layer,MENULAYER + 100);
    
	bs1_room_bg->setVisible(false);
	GameHallLayer::is_bs_xianshi= false;
 
	cocos2d::log("room tag = %d",bs_moshi);
	//ÕÊº“Ω¯»Îƒƒ∏ˆ∑øº‰µƒ¥Œ ˝
    sprintf(hallCharTemp,"bisai_room_%d",bs_moshi);
   // DCEvent::onEvent(hallCharTemp);
	 
}

//yiyuan
void GameHallLayer::menu_yiyuan(Ref * pSender)
{
    GameBegin::buttonSound();
	auto scene = Shop::create(6);
	this->addChild(scene,10000);
}

//jijin
void GameHallLayer::menu_jijin(Ref * pSender)
{
    GameBegin::buttonSound();
    
    ShopJJ::come_kind_jj = 1;
	auto scene = ShopJJ::createScene();
	this->addChild(scene,10000);
}

//vip
void GameHallLayer::menu_viptequan(Ref * pSender)
{
     GameBegin::buttonSound();
	if(UserDefault::getInstance()->getIntegerForKey("player_vip") == 0)
	{
		auto scene = Shop::create(4);
		this->addChild(scene,10000);
	}else
	{
		hall_vip_anniu->stopAllActions();
		time_t currentTime;
		time(&currentTime);
		//√ø»’µ«¬º
		if(UserDefault::getInstance()->getIntegerForKey("Vip_loginDays")==0)
		{
			sprintf(hallCharTemp,GAME_DATA_STRING("login_yubi"),20000,200);
			auto  gongxi = VIPgongxi::create(3);
			this->addChild(gongxi,ANNIULAYER + 100);

			RefreshCoin(20000);
			RefreshDiamond(200);
			struct tm *nowTime = gmtime(&currentTime);
			int hour=nowTime->tm_hour;  
			int minute=nowTime->tm_min;  
			int second=nowTime->tm_sec;
			time_t nextTime = currentTime + 24*60*60 - hour*60*60 - minute*60 - second; 

			UserDefault::getInstance()->setIntegerForKey("vip_login_time",nextTime);
			UserDefault::getInstance()->setIntegerForKey("Vip_loginDays",1);
			UserDefault::getInstance()->flush();
		}
		else
		{
			time_t prevTime = UserDefault::getInstance()->getIntegerForKey("vip_login_time");
			int loginDays = UserDefault::getInstance()->getIntegerForKey("Vip_loginDays") + 1;
			
			if(currentTime<prevTime)
			{
				auto  gongxi = Gongxi::create(2,GAME_DATA_STRING("LingState1One"));
				this->addChild(gongxi,MENULAYER + 100);
			}
			else if(currentTime>prevTime)
			{
				sprintf(hallCharTemp,GAME_DATA_STRING("login_yubi"),20000,200);
				auto  gongxi = VIPgongxi::create(3);
				this->addChild(gongxi,ANNIULAYER + 100);

				RefreshCoin(20000);
				RefreshDiamond(200);

				struct tm *nowTime = gmtime(&currentTime);
				int hour=nowTime->tm_hour;  
				int minute=nowTime->tm_min;  
				int second=nowTime->tm_sec;
				time_t nextTime = currentTime + 24*60*60 - hour*60*60 - minute*60 - second; 

				UserDefault::getInstance()->setIntegerForKey("vip_login_time",nextTime);
				UserDefault::getInstance()->setIntegerForKey("Vip_loginDays",loginDays);
				UserDefault::getInstance()->flush();
			}
		}


	}	
}

void GameHallLayer::baoming_vip(Ref * pSender)
{
	this->removeChildByTag(999);
 
    auto shop = Shop::create(4);
    this->addChild(shop,10000);
}

//«¿∫Ï∞¸
void GameHallLayer::menuQianghongbao(Ref* pSender)
{
    GameBegin::buttonSound();
    
    /* auto layer = HongBao::createScene();
     this->addChild(layer,MENULAYER+100);
     */
    
    GameBegin::buttonSound();
    if(hall_hb_times > 0)
    {
        auto gongxik = Gongxi::create(2,GAME_DATA_STRING("hall_hb_time_low"));
        gongxik->setPosition(Point::ZERO);
        this->addChild(gongxik,MENULAYER+100);
        
    }else
    {
        hall_hb_anniu->setPosition(Vec2(50 + origin.x ,visibleSize.height - 140 + origin.y));
        hall_hb_anniu->stopAllActions();
        hall_hb_kaiguan =false;
        
        auto layer = HongBao::createScene();
        this->addChild(layer,MENULAYER+100);
    }
    
    /*	auto layer = Game_Hall_Kefu2::createScene();
     addChild(layer , MENULAYER);*/
}

void GameHallLayer::menujiujisai(Ref* pSender)
{
    GameBegin::buttonSound();
    
    
    if(GameBegin::getFileData("gamePlayerlv.txt") < 5)
    {
        sprintf(hallCharTemp,GAME_DATA_STRING("gamehall_level_low"),5);
        auto qiantaiduo = Gongxi::create(2,hallCharTemp);
        qiantaiduo->setPosition(Vec2::ZERO);
        addChild(qiantaiduo,1000);
        return;
    }
    
        if(GameBegin::getFileData("jywer.txt") > 1000)
        {
            auto qiantaiduo = Gongxi::create(2,GAME_DATA_STRING("qiantaiduo"));
            qiantaiduo->setPosition(Vec2::ZERO);
            addChild(qiantaiduo,1000);
            return;
        }
    GameScene::cGameType = 1;
    
    
    GameHallLayer::sceneLowPao = 2;
    GameHallLayer::sceneHighPao = 3;
    
    
    
    
    GameBegin::removeSouce(1);
    GameHallLayer::RoomType = 89;
    
    LoadRes::RoomType =90;
   
    
    auto layer = MatchPlayer::createScene();
    this->addChild(layer,MENULAYER + 100);
    bs1_room_bg->setVisible(false);
    GameHallLayer::is_bs_xianshi= false;
    
    cocos2d::log("room tag = %d",66);
    //ÕÊº“Ω¯»Îƒƒ∏ˆ∑øº‰µƒ¥Œ ˝
    sprintf(hallCharTemp,"bisai_room_%d",66);
    //DCEvent::onEvent(hallCharTemp);
    
}


void GameHallLayer::updateHB(float dt)
{
    if(hall_hb_kaiguan)
    {
        if(hall_hb_times > 0)
        {
            //GameBegin::setFileData("hb_last_time.txt",++hall_hb_time_t);
            //GameBegin::setFileData("hb_times.txt",--hall_hb_times);
            --hall_hb_times;
            
            hall_hb_anniu->stopAllActions();
            hall_hb_anniu->setPosition(Vec2( 50 + origin.x ,visibleSize.height - 140 + origin.y));
            sprintf(hallCharTemp,"%s",returnString(hall_hb_times).c_str());
            
            hall_hb_time_l->setString(hallCharTemp);
            if(!hall_sp_hb_k->isVisible())
            {
                hall_sp_hb_k->setVisible(true);
            }
        }else
        {
            hall_sp_hb_k->setVisible(false);
            
            //this->unschedule(schedule_selector(GameHallLayer::updateHB));
        }
    }
}

//*****≤‡±ﬂ¿∏¥¶¿Ì∫Ø ˝
//¥¶¿Ì…Ë÷√
void GameHallLayer::hall_shezhi_func(Ref* pSender)
{
	GameBegin::buttonSound(); 

	hall_menu_lipin->setEnabled(false);
	hall_menu_shengyin->setEnabled(false);
	hall_menu_wenhao->setEnabled(false);
	hall_menu_youjian->setEnabled(false);
	hall_menu_tuichu->setEnabled(false);
	if( hall_bSetShow == true)
	{
		hall_menu_shezhi->setEnabled(false);

		//…Ë÷√–˝◊™180
		Animate  * hall_menu_cl_dh  = Animate::create(AnimationCache::getInstance()->getAnimation("hall_set"));
		hall_menu_shezhi_cl->runAction(RepeatForever::create(hall_menu_cl_dh->reverse()));

		//ÕÀ≥ˆ∞¥≈•∂Ø◊˜
		auto moveBy1 = MoveBy::create(0.5f,Point(0,-310));
		auto easy1 = EaseIn::create(moveBy1,2);	  
		auto cal = CallFunc::create(CC_CALLBACK_0(GameHallLayer::shezhi_MoveOver,this));
		auto seq = Sequence::create(easy1,cal,nullptr);
		hall_menu_tuichu->runAction(seq);

		//” º˛∞¥≈•∂Ø◊˜
		auto moveBy2 = MoveBy::create(0.5f,Point(0,-250));
		auto easy2 = EaseIn::create(moveBy2,2);	
		hall_menu_youjian->runAction(easy2);

		//∞Ô÷˙∞¥≈•∂Ø◊˜
		auto moveBy3 = MoveBy::create(0.5f,Point(0,-190));
		auto easy3 = EaseIn::create(moveBy3,2);	
		hall_menu_wenhao->runAction(easy3);

		//…˘“Ù∞¥≈•∂Ø◊˜
		auto moveBy4 = MoveBy::create(0.5f,Point(0,-130));
		auto easy4 = EaseIn::create(moveBy4,2);	
		hall_menu_shengyin->runAction(easy4);

		//…˘“Ù∞¥≈•∂Ø◊˜
		auto moveBy5 = MoveBy::create(0.5f,Point(0,-70));
		auto easy5 = EaseIn::create(moveBy5,2);	
		hall_menu_lipin->runAction(easy5);

		hall_bSetShow =false;
	}
	else
	{
		hall_menu_shezhi->setEnabled(false);

		//…Ë÷√∞¥≈•ø…º˚
		hall_menu_lipin->setVisible(true);
		hall_menu_shengyin->setVisible(true);
		hall_menu_wenhao->setVisible(true);
		hall_menu_youjian->setVisible(true);
		hall_menu_tuichu->setVisible(true);
        
        if(UserDefault::getInstance()->getIntegerForKey("ios_dengluFlag") == 1)
        {
            hall_menu_lipin->setVisible(false);
        }

		//…Ë÷√–˝◊™180
		Animate  * hall_menu_cl_dh  = Animate::create(AnimationCache::getInstance()->getAnimation("hall_set"));
		hall_menu_shezhi_cl->runAction(RepeatForever::create(hall_menu_cl_dh));

		//ÕÀ≥ˆ∞¥≈•∂Ø◊˜
		auto moveBy1 = MoveBy::create(0.5f,Point(0,310));
		auto easy1 = EaseOut::create(moveBy1,2);	  
		auto cal = CallFunc::create(CC_CALLBACK_0(GameHallLayer::shezhi_MoveOver,this));
		auto seq = Sequence::create(easy1,cal,nullptr);
		hall_menu_tuichu->runAction(seq);

		//” º˛∞¥≈•∂Ø◊˜
		auto moveBy2 = MoveBy::create(0.5f,Point(0,250));
		auto easy2 = EaseOut::create(moveBy2,2);	
		hall_menu_youjian->runAction(easy2);

		//∞Ô÷˙∞¥≈•∂Ø◊˜
		auto moveBy3 = MoveBy::create(0.5f,Point(0,190));
		auto easy3 = EaseOut::create(moveBy3,2);	
		hall_menu_wenhao->runAction(easy3);

		//…˘“Ù∞¥≈•∂Ø◊˜
		auto moveBy4 = MoveBy::create(0.5f,Point(0,130));
		auto easy4 = EaseOut::create(moveBy4,2);	
		hall_menu_shengyin->runAction(easy4);

		//…˘“Ù∞¥≈•∂Ø◊˜
		auto moveBy5 = MoveBy::create(0.5f,Point(0,70));
		auto easy5 = EaseOut::create(moveBy5,2);	
		hall_menu_lipin->runAction(easy5);

		hall_bSetShow =true;
	}
}

void GameHallLayer::shezhi_MoveOver()
{
	hall_menu_shezhi->setEnabled(true);
	hall_menu_shezhi_cl->stopAllActions();

	if(!hall_bSetShow)
	{
		hall_menu_lipin->setVisible(false);
		hall_menu_shengyin->setVisible(false);
		hall_menu_wenhao->setVisible(false);
		hall_menu_youjian->setVisible(false);
		hall_menu_tuichu->setVisible(false);
	}else
	{
		hall_menu_lipin->setEnabled(true);
		hall_menu_shengyin->setEnabled(true);
		hall_menu_wenhao->setEnabled(true);
		hall_menu_youjian->setEnabled(true);
		hall_menu_tuichu->setEnabled(true);
	}
}

//¥¶¿Ì¿Ò∆∑
void GameHallLayer::hall_lipin_func(Ref* pSender)
{ 
	hall_shezhi_func(this);

	GameTextIn::libaoInt = 1;
	auto gameHelp = GameTextIn::createScene();
	this->addChild(gameHelp,ANNIULAYER + 100);
}

//¥¶¿Ì…˘“Ù
void GameHallLayer::hall_shengyin_func(Ref* pSender)
{ 
	hall_shezhi_func(this);

	if(hall_bShengyinShow)
	{
		hall_bShengyinShow = false;

		GameSet::yinyueIsON = false;
		GameSet::yinxiaoIsON = false;

		auto spriteFrame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hall_menu_shengyin_g.png");
		auto spriteFrame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hall_menu_shengyin_g_d.png");
		hall_sprite_shengyin->setSpriteFrame(spriteFrame1);
		hall_sprite_shengyin_d->setSpriteFrame(spriteFrame2);

		GameBegin::canPlayMusic = false;
		GameBegin::canPlaySound = false;
		GameBegin::stopMusic();
		
	}else
	{
		hall_bShengyinShow = true;

		GameSet::yinyueIsON = true;
		GameSet::yinxiaoIsON = true;

		auto spriteFrame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hall_menu_shengyin_k.png");
		auto spriteFrame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hall_menu_shengyin_k_d.png");
		hall_sprite_shengyin->setSpriteFrame(spriteFrame1);
		hall_sprite_shengyin_d->setSpriteFrame(spriteFrame2);

		GameBegin::canPlayMusic = true;
		GameBegin::canPlaySound = true;
		GameBegin::playMusic("",GameBegin::musicNum);		
	}
}

//¥¶¿Ì∞Ô÷˙
void GameHallLayer::hall_bangzhu_func(Ref* pSender)
{ 
	hall_shezhi_func(this);

	auto gameHelp = GameHelp::createScene();
	this->addChild(gameHelp,ANNIULAYER + 100);
}

//¥¶¿Ì” œ‰
void GameHallLayer::hall_youjian_func(Ref* pSender)
{
	hall_shezhi_func(this);
	//¥¥Ω®π´∏Ê∂‘œÛ
	auto gonggaoScene = GameEmail::createScene();
	this->addChild(gonggaoScene,ANNIULAYER + 100);

}

//¥¶¿ÌÕÀ≥ˆ
void GameHallLayer::hall_tuichu_func(Ref* pSender)
{
	if(true) // !GameHallLayer::exitIsCun
	{
		hall_shezhi_func(this);
		GameHallLayer::exitIsCun = true;
		cocos2d::log("diaoyong tuichu ");
		//ÕÀ≥ˆ∑øº‰Ã· æ
		string exitTmp = GAME_DATA_STRING("gamehall_exit");
		auto gongxi = Gongxi::create(3,exitTmp);
		gongxi->setPosition(Point::ZERO);
		this->addChild(gongxi,MENULAYER + 1000,1000);

		auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png");
		auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(GameHallLayer::queding,this));

		auto btnMenu = Menu::create(quedingItem,nullptr);
		btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
		gongxi->getChildByTag(1)->addChild(btnMenu,100);
		cocos2d::log("diaoyong tuichu over");

	}
    
    /*
    this->removeAllChildrenWithCleanup(true);
    this->unscheduleAllSelectors();
    this->stopAllActions();
    
    Scene* scene = GameBegin::createScene();
    Director::getInstance()->replaceScene(scene);*/
    
}


//*********µ◊≤ø¥¶¿Ì∫Ø ˝
//‘ˆº”Ω±±≠ ˝¡ø
void GameHallLayer::hall_jiangbei_func(Ref* pSender)
{
	GameBegin::buttonSound();
 
    string exitTmp = GAME_DATA_STRING("wfqidai");
    auto gongxi = Gongxi::create(3,exitTmp);
    gongxi->setPosition(Point::ZERO);
    this->addChild(gongxi,MENULAYER + 1000,1000);
	/*auto layer = Game_Hall_Kefu3::createScene();
	this->addChild(layer,MENULAYER);*/
}

//±∂¬ Ω‚À¯
void GameHallLayer::hall_jiesuo_func(Ref* pSender)
{

	GameBegin::buttonSound();
	if(!isBiSai)
	{
        GameBegin::buttonSound();
		if(this->getChildByTag(995))
		{
			this->removeChildByTag(995);
		}	
		if( GameBegin::getFileData("gameMaxPao.txt") == 20)
		{
			auto gongxi = Gongxi::create(1,GAME_DATA_STRING("shop_buy_libao_1"));
			gongxi->setPosition(Point::ZERO);
			this->addChild(gongxi,ANNIULAYER + 100);
		}
		else
		{
			auto scene = UnLockLayer::create(1);
			//scene->setPosition(Point::ZERO);
			this->addChild(scene,MENULAYER + 101);
		}
	}else
	{
        if(isDit)
        {
            GameBegin::buttonSound();
            isDit = false;
            this->runAction(Sequence::create(DelayTime::create(1.2f),CCCallFunc::create([&]{isDit = true;}),nullptr));
            bs_moshi = 1;
            BS_gengzheng();
            cocos2d::log("fangjian = %d",bs_moshi);		
        }
	}
}

//…Ã≥«
void GameHallLayer::hall_shangcheng_func(Ref* pSender)
{
	
 
	if(!isBiSai)
	{
        GameBegin::buttonSound();
		auto scene = Shop::create(1);
		this->addChild(scene,1000);
	}else
	{
        if(isDit)
        {
            GameBegin::buttonSound();
            isDit = false;
            this->runAction(Sequence::create(DelayTime::create(1.2f),CCCallFunc::create([&]{isDit = true;}),nullptr));
            bs_moshi = 2;
            BS_gengzheng();
            cocos2d::log("fangjian = %d",bs_moshi);		
        }
	}
} 

void GameHallLayer::hall_shangcheng_func1(Ref* pSender)
{
	GameBegin::buttonSound();

	auto scene = Shop::create(1);
	this->addChild(scene,1000);
} 

//«øªØ¥Û≈⁄
void GameHallLayer::hall_jineng_func(Ref* pSender)
{

 

	if(!isBiSai)
	{
        GameBegin::buttonSound();
		if( GameBegin::getFileData("gamePlayerlv.txt")<3)
		{
			auto gongxi = Gongxi::create(2,GAME_DATA_STRING("gamehall_level_3"));
			gongxi->setPosition(Point::ZERO);
			this->addChild(gongxi,1000);
		}
		else
		{
            this->stopAllActions();
            this->removeAllChildrenWithCleanup(true);
            this->unscheduleAllSelectors();
            Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
            
			auto scene = CannonUpgrade::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	}else
	{
        if(isDit)
        {
            GameBegin::buttonSound();
            isDit = false;
            this->runAction(Sequence::create(DelayTime::create(1.2f),CCCallFunc::create([&]{isDit = true;}),nullptr));
            bs_moshi = 3;
            BS_gengzheng();
            cocos2d::log("fangjian = %d",bs_moshi);		
        }
	}
	
}

//ÃÙ’ΩBOSS
void GameHallLayer::hall_tiaozhan_func(Ref* pSender)
{
 
	if(!isBiSai)
	{
        GameBegin::buttonSound();
        
        this->stopAllActions();
        this->removeAllChildrenWithCleanup(true);
        this->unscheduleAllSelectors();
        Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
        
        GameBegin::removeSouce(1);
        
		auto scene = ChallengeBOSS::createScene();
		Director::getInstance()->replaceScene(scene);
	}else
	{
        if(isDit)
        {
            GameBegin::buttonSound();
            isDit = false;
            this->runAction(Sequence::create(DelayTime::create(1.2f),CCCallFunc::create([&]{isDit = true;}),nullptr));
            bs_moshi = 4;
            BS_gengzheng();
            cocos2d::log("fangjian = %d",bs_moshi);		
        }
	}
}
 
//*******÷–º‰¥¶¿Ì∫Ø ˝
//Ω¯»Î”Ê≥°
void GameHallLayer::enterFishManage()
{
	if(isEnterYu)
	{
		 
		GameBegin::buttonSound(); 
		RoomType = hall_room_index - 1;
        if(RoomType>=7)
            RoomType += 1;

		//÷ÿ÷√µ±«∞◊ÓµÕpao∫Õ ◊Ó∏ﬂpao
		char sceneLowRateTmp[20];
		sprintf(sceneLowRateTmp,"boss_low_odd_%d",RoomType + 1);
		char sceneHighRateTmp[20];
		sprintf(sceneHighRateTmp,"boss_high_%d",RoomType + 1);
		GameHallLayer::sceneLowPao = GAME_DATA_INT(sceneLowRateTmp);
		GameHallLayer::sceneHighPao = GAME_DATA_INT(sceneHighRateTmp);
        
        if(UserDefault::getInstance()->getIntegerForKey("yiyuangoumai") == 1 && hall_room_index < 4)
        {
            GameHallLayer::sceneHighPao = 15;
        }

		//≈–∂œµ±«∞ «∑Ò∑˚∫œΩ¯»Î≥°æ∞Ãıº˛
		if((RoomType == 0 && GameBegin::getFileData("jywer.txt") > 10000)||(RoomType == 1 && GameBegin::getFileData("jywer.txt") > 80000))
		{
			auto qiantaiduo = Gongxi::create(2,GAME_DATA_STRING("qiantaiduo"));
			qiantaiduo->setPosition(Vec2::ZERO);
			addChild(qiantaiduo,1000);

		}else if(GameBegin::getFileData("gameMaxPao.txt") < GameHallLayer::sceneLowPao)
		{
			auto qiantaiduo = Gongxi::create(3,GAME_DATA_STRING("paotaidi"));
			qiantaiduo->setPosition(Vec2::ZERO);
			addChild(qiantaiduo,1000,995);

			auto quedingSprite = Scale9Sprite::createWithSpriteFrameName("XR_qd.png");
			auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_1(GameHallLayer::hall_jiesuo_func,this));

			auto btnMenu = Menu::create(quedingItem,nullptr);
			btnMenu->setPosition(Point(qiantaiduo->getChildByTag(1)->getContentSize().width/2,0.18*qiantaiduo->getChildByTag(1)->getContentSize().height));
			qiantaiduo->getChildByTag(1)->addChild(btnMenu,100);
		}else
		{
            this->stopAllActions();
            this->removeAllChildrenWithCleanup(true);
            this->unscheduleAllSelectors();
            Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
            
            GameBegin::removeSouce(1);
            
            isEnterYu = false;

			GameScene::cGameType = 0;
			LoadRes::RoomType =   RoomType;
			auto scene = LoadRes::createScene();	
			Director::getInstance()->replaceScene(scene);
            
    

			//ÕÊº“Ω¯»Îƒƒ∏ˆ∑øº‰µƒ¥Œ ˝
			sprintf(hallCharTemp,"danji_room_%d",RoomType + 1);
            //DCEvent::onEvent(hallCharTemp);
			 
		}	
	}
}
 
void GameHallLayer::queding()
{
	cocos2d::log("diaoyong end ");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    GameBegin::cal_lastTime();

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameHallLayer::hall_gengzheng()
{ 
	float hall_layer_x = containerLayer->getPosition().x > 0?0:abs(containerLayer->getPosition().x);  
	float layer_x = hall_layer_x+ (roomSize.width + roomSpaceLenth)/4;
	float layer_X = (roomSize.width+ roomSpaceLenth)/2;
	int index_tmp = layer_x/layer_X;//0°¢1°¢2°¢.....°¢24
	hall_room_index = index_tmp/2 + 1; //µ±«∞∑øº‰µƒÀ˜“˝
	//hall_room_index =  layer_x/layer_X + 1;
	if(index_tmp % 2 == 1)
	{
		if(hall_room_direct)
		{
			hall_room_index++;
		}else
		{
			hall_room_index;
		}
	} 
 
	if(hall_room_index > 11)
		hall_room_index = 11;
	if(hall_room_index < 1)
		hall_room_index = 1;

	if( hall_room_index == 1)
	{
		hall_zuojiantou->setVisible(false);
		
	}else if(hall_room_index == 11)
	{		
		hall_youjiantou->setVisible(false);
	}else
	{
		hall_youjiantou->setVisible(true);
		hall_zuojiantou->setVisible(true);
	}

	auto moveOne = MoveTo::create(0.2f,Vec2(-(hall_room_index-1)*(roomSize.width + roomSpaceLenth),0));
	containerLayer->runAction(moveOne);

	auto scaleTo1 = ScaleTo::create(0.2f,HALL_ROOM_SCALE_HIGH);
	hall_room_spec.at(hall_room_index - 1)->runAction(scaleTo1);

	if(hall_room_index - 2 > 0)
	{
		auto scaleTo2 = ScaleTo::create(0.2f,HALL_ROOM_SCALE_LOW);
		hall_room_spec.at(hall_room_index - 2)->runAction(scaleTo2);
	}
	
	if(hall_room_index < 11)
	{
		auto scaleTo3 = ScaleTo::create(0.2f,HALL_ROOM_SCALE_LOW);
		hall_room_spec.at(hall_room_index)->runAction(scaleTo3);
	}

	hall_room_moveUp();
}

//Ω‚À¯∑øº‰
void GameHallLayer::roomUnlockManage()
{
	GameBegin::buttonSound();

	//MenuItemSprite * item = (MenuItemSprite *)pSender;
	//hall_room_index = item->getTag() ;

	sprintf(hallCharTemp,"boss_diamond_num_%d",hall_room_index);
	int zuanshiHuaFei = GAME_DATA_INT(hallCharTemp); //Ω‚À¯À˘–Ë◊Í Ø

	memset(hallCharTemp,0,sizeof(hallCharTemp));
	sprintf(hallCharTemp,"boss_low_level_%d",hall_room_index);
	int zuidiLevel = GAME_DATA_INT(hallCharTemp); //Ω‚À¯À˘–Ëµ»º∂
	if( GameBegin::getFileData("gamePlayerlv.txt") < zuidiLevel)
	{
		char level[40];
		sprintf(level,GAME_DATA_STRING("gamehall_level_low"),zuidiLevel);
		auto gongxi = Gongxi::create(3,level);
		gongxi->setPosition(Point::ZERO);
		this->addChild(gongxi,1000,1000);

		auto quedingSprite = Scale9Sprite::createWithSpriteFrameName("XR_qd.png");
        auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(GameHallLayer::shengjilv,this));
        
        auto btnMenu = Menu::create(quedingItem,nullptr);
        btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
        gongxi->getChildByTag(1)->addChild(btnMenu,100);

		return;
	}
	if(zuanshiHuaFei > GameBegin::getFileData("jywopl.txt") )
	{
		auto gongxi = Gongxi::create(3,GAME_DATA_STRING("gamehall_zuanshi_low"));
		gongxi->setPosition(Point::ZERO);
		this->addChild(gongxi,1000,1000);

		auto quedingSprite = Scale9Sprite::createWithSpriteFrameName("XR_qd.png");
		auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(GameHallLayer::quShop,this));

		auto btnMenu = Menu::create(quedingItem,nullptr);
		btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
		gongxi->getChildByTag(1)->addChild(btnMenu,100);
		return;
	}
 
	sprintf(hallCharTemp,GAME_DATA_STRING("gamehall_zuanshi_xiaohao"),zuanshiHuaFei);
	auto gongxi = Gongxi::create(3,hallCharTemp);
	gongxi->setPosition(Point::ZERO);
	this->addChild(gongxi,1000,1000);

	auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png");
	auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(GameHallLayer::quJiesuo,this));

	auto btnMenu = Menu::create(quedingItem,nullptr);
	btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
	gongxi->getChildByTag(1)->addChild(btnMenu,100);

}

void GameHallLayer::quJiesuo()
{
	GameBegin::buttonSound(); 

	//…æ≥˝πßœ≤øÚ
	if(this->getChildByTag(1000))
	{
		this->removeChildByTag(1000);
	}
	
	GameBegin::playSound("jiesuo.mp3");

	Sprite * hall_room_bg_tmp = hall_room_spec.at(hall_room_index - 1);	//À˘—°∑øº‰±≥æ∞
	//≤•∑≈Ω‚À¯∂Øª≠
	Sprite * hall_room_suo = (Sprite * )hall_room_bg_tmp->getChildByTag(102);//µ√µΩÀ¯Õº∆¨
	Animate * hall_room_suo_a = Animate::create(AnimationCache::getInstance()->getAnimation("hall_room_suo"));
	hall_room_suo->runAction(hall_room_suo_a);
 
	//∏¸–¬◊Í Ø ˝¡ø
	sprintf(hallCharTemp,"boss_diamond_num_%d",hall_room_index);
	int zuanshiHuaFei = GAME_DATA_INT(hallCharTemp); //Ω‚À¯À˘–Ë◊Í Ø
	RefreshDiamond(-zuanshiHuaFei);
 
	roomFlag[hall_room_index - 1] = 1;//º«¬º∑øº‰µƒΩ‚À¯±Í÷æ
	int unlockRoomNum = 0;
	for(int i=0;i<SCENENUM;i++)
	{
		unlockRoomNum += roomFlag[i] * std::pow(2,i); 
	}
	UserDefault::getInstance()->setIntegerForKey("unlockRoomNum",unlockRoomNum);
	UserDefault::getInstance()->flush();

	//Ω¯»Î”Ê≥°∞¥≈•≥ˆœ÷
	Sprite * hall_room_anniu = ( Sprite * ) hall_room_bg_tmp->getChildByTag(201);
	hall_room_anniu->getChildByTag(204)->setVisible(false);
	hall_room_anniu->getChildByTag(205)->setVisible(false);
	hall_room_anniu->getChildByTag(203)->setVisible(true);
}

//»•…Ã≥«
void GameHallLayer::quShop()
{
	GameBegin::buttonSound(); 
	this->removeChildByTag(1000);

	auto scene = Shop::create(1);
	this->addChild(scene,10000);
}

//»•…Ã≥«
void GameHallLayer::shengjilv()
{
    GameBegin::buttonSound();
    this->removeChildByTag(1000);
    
	initRoom();

    char sceneLowRateTmp[20];
    sprintf(sceneLowRateTmp,"boss_low_odd_%d",GameHallLayer::RoomType + 1);
    char sceneHighRateTmp[20];
    sprintf(sceneHighRateTmp,"boss_high_%d",GameHallLayer::RoomType + 1);
    GameHallLayer::sceneLowPao = GAME_DATA_INT(sceneLowRateTmp);
    GameHallLayer::sceneHighPao = GAME_DATA_INT(sceneHighRateTmp);
    
    this->stopAllActions();
    this->removeAllChildrenWithCleanup(true);
    this->unscheduleAllSelectors();
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
    
    GameBegin::removeSouce(1);
    
	LoadRes::RoomType = GameHallLayer:: RoomType;
	auto scene = LoadRes::createScene();	
	Director::getInstance()->replaceScene(scene);  
	 
}
 
void GameHallLayer::hall_room_moveUp()
{
	if(!hall_room_is_moveing)
	{
		hall_room_is_moveing = true;
		Sprite * hall_room_bg_tmp = hall_room_spec.at(hall_room_index - 1);	//À˘—°∑øº‰±≥æ∞

		Sprite * hall_room_slt_bg_tmp = (Sprite *)hall_room_bg_tmp->getChildByTag(100); //À˘—°∑øº‰Àı¬‘Õºæ´¡È

		//≥°æ∞Àı¬‘Õºµƒ∫¢◊”√«
		//boss
		Sprite * hall_boss = (Sprite *)hall_room_slt_bg_tmp->getChildByTag(19) ;
		hall_boss->stopAllActions();
		hall_boss->runAction( hall_boss_a.at(hall_room_index - 1));

		//∆¯≈›
		Sprite * hall_room_db_bg_tmp = (Sprite *)hall_room_bg_tmp->getChildByTag(104); //À˘—°∑øº‰µ◊≤øÕº		
		hall_room_db_bg_tmp->getChildByTag(14)->setVisible(true);
		hall_room_db_bg_tmp->getChildByTag(15)->setVisible(true);

		//ÀÆ≤›∂Øª≠
		Sprite * hall_shuicao1 = (Sprite *)hall_room_db_bg_tmp->getChildByTag(16) ;
		hall_shuicao1->stopAllActions();
		hall_shuicao1->runAction( hall_shuicao1_a.at(hall_room_index - 1));

		Sprite * hall_shuicao2 = (Sprite *)hall_room_db_bg_tmp->getChildByTag(17) ;
		hall_shuicao2->stopAllActions();
		hall_shuicao2->runAction( hall_shuicao2_a.at(hall_room_index - 1));

		//¡¡π‚
		Sprite * hall_room_lg = (Sprite *)hall_room_bg_tmp->getChildByTag(101); //±≥æ∞π‚
		hall_room_lg->stopAllActions();
		hall_room_lg->runAction(lg_fadeIn.at(hall_room_index - 1));
	}
	
}

void GameHallLayer::hall_room_moveDown()
{
	if(hall_room_is_moveing)
	{
		hall_room_is_moveing = false;

		for(int i = 0 ; i < 11 ; i++)
		{
            
			Sprite * hall_room_bg_tmp = hall_room_spec.at(i);	//À˘—°∑øº‰±≥æ∞

			Sprite * hall_room_slt_bg_tmp = (Sprite *)hall_room_bg_tmp->getChildByTag(100); //À˘—°∑øº‰Àı¬‘Õºæ´¡È
			//≥°æ∞Àı¬‘Õºµƒ∫¢◊”√«
			Sprite * hall_boss = (Sprite *)hall_room_slt_bg_tmp->getChildByTag(19) ;
			hall_boss->stopAllActions();

			Sprite * hall_room_db_bg_tmp = (Sprite *)hall_room_bg_tmp->getChildByTag(104); //À˘—°∑øº‰µ◊≤øÕº
			//∆¯≈›
			hall_room_db_bg_tmp->getChildByTag(14)->setVisible(false);
			hall_room_db_bg_tmp->getChildByTag(15)->setVisible(false);
			//∞¥≈•
			Sprite * hall_shuicao1 = (Sprite *)hall_room_db_bg_tmp->getChildByTag(16);
			hall_shuicao1->stopAllActions();

			Sprite * hall_shuicao2 = (Sprite *)hall_room_db_bg_tmp->getChildByTag(17);
			hall_shuicao2->stopAllActions();

			////¡¡π‚Ω•“˛
			Sprite * hall_room_lg = (Sprite *)hall_room_bg_tmp->getChildByTag(101); //±≥æ∞π‚s
			hall_room_lg->stopAllActions();
			hall_room_lg->runAction(lg_fadeOut.at(i));
		}
		
	}
	
}

void GameHallLayer::moveToLeft( )
{ 	
	if(hall_room_index < 11)
	{
		GameBegin::buttonSound();
 
		hall_room_direct = false;
		scrollview_begin_m = true;

		auto moveOne = MoveBy::create(0.2f,Point(-roomSpaceLenth - roomSize.width - 1,0));
		auto action =  EaseOut::create(moveOne,2);
		auto cal = CallFunc::create(CC_CALLBACK_0(GameHallLayer::canMove,this));
		auto seq = Sequence::create(action,cal,nullptr);

		containerLayer->runAction(seq);

		auto scaleTo1 = ScaleTo::create(0.1f,HALL_ROOM_SCALE_LOW);
		hall_room_spec.at(hall_room_index - 1)->runAction(scaleTo1);

		auto scaleTo2 = ScaleTo::create(0.1f,HALL_ROOM_SCALE_HIGH);
		hall_room_spec.at(hall_room_index)->runAction(scaleTo2);
	}

	
}

void GameHallLayer::moveToRight( )
{
	if(hall_room_index > 1)
	{
		GameBegin::buttonSound();
 
		scrollview_begin_m = true;
		hall_room_direct = true;

		auto moveOne = MoveBy::create(0.2f,Point(roomSpaceLenth + roomSize.width + 1,0));
		auto action =  EaseOut::create(moveOne,2);
		auto cal = CallFunc::create(CC_CALLBACK_0(GameHallLayer::canMove,this));
		auto seq = Sequence::create(action,cal,nullptr);
		containerLayer->runAction(seq);

		auto scaleTo1 = ScaleTo::create(0.1f,HALL_ROOM_SCALE_LOW);
		hall_room_spec.at(hall_room_index - 1)->runAction(scaleTo1);

		auto scaleTo2 = ScaleTo::create(0.1f,HALL_ROOM_SCALE_HIGH);
		hall_room_spec.at(hall_room_index - 2)->runAction(scaleTo2);
	}
	
}

void GameHallLayer::canMove()
{
	scrollview_begin_m = false;
	hall_gengzheng();
}

//±»»¸∑øº‰ª¨∂Ø
void GameHallLayer::moveBSLeft()
{
	if(bs_moshi < 4 && !bs_room_is_moving)
	{
		bs_moshi++;
 
		GameBegin::buttonSound();
 
		bs1_display(bs_moshi);

		this->scheduleOnce(schedule_selector(GameHallLayer::canBSMove),1.02f);
	}
}

void GameHallLayer::moveBSRight()
{
	if(bs_moshi > 1 && !bs_room_is_moving)
	{
		bs_moshi--;
 
		GameBegin::buttonSound();
		bs1_display(bs_moshi);
 
		this->scheduleOnce(schedule_selector(GameHallLayer::canBSMove),1.02f);
		
	}
}

void GameHallLayer::canBSMove(float dt)
{
	bs_room_is_moving = false;
	BS_gengzheng();
}

void GameHallLayer::BS_checkAll()
{
	int lv = GameBegin::getFileData("gamePlayerlv.txt");
	int jinbi = GameBegin::getFileData("jywer.txt");
	int beilv = GameBegin::getFileData("gameMaxPao.txt");
	//≈–∂œµ±«∞ Ù”⁄ƒƒ∏ˆº∂±
	if(jinbi<=GAME_DATA_INT("bs_room_2_jinbi"))
	{
		bs_moshi = 1;
		BS_gengzheng();
	}else if(jinbi>GAME_DATA_INT("bs_room_2_jinbi") && jinbi<GAME_DATA_INT("bs_room_3_jinbi"))
	{
		bs_moshi = 2;
		BS_gengzheng();
	}else
	{
		if(UserDefault::getInstance()->getIntegerForKey("player_vip") == 0)
		{
			bs_moshi = 3;
		}else
		{
			bs_moshi = 4;
		}
		BS_gengzheng();
	}
	 
}

void GameHallLayer::BS_gengzheng(float dt)
{
    if(hall_youjiantou)
    {
	if( bs_moshi == 1)
	{
		hall_zuojiantou->setVisible(false);
        hall_youjiantou->setVisible(true);
		
	}else if(bs_moshi == 4)
	{		
		hall_youjiantou->setVisible(false);
        hall_zuojiantou->setVisible(true);
	}else
	{
		hall_youjiantou->setVisible(true);
		hall_zuojiantou->setVisible(true);
	}
    }

	bs1_display(bs_moshi);
	UserDefault::getInstance()->setIntegerForKey("BS_moshi",bs_moshi);
	UserDefault::getInstance()->flush();
 
	//Àƒ∏ˆ∞¥≈•œ‘ æ
	BS_bianliang(bs_moshi);
 
}

void GameHallLayer::BS_MoveOver()
{
	/*auto moveOne = MoveTo::create(0.1f,Vec2(-(bs_moshi-1)*roomSize1.width,30));
	containerLayer1->runAction(moveOne);*/
 
	/*auto moveOne1 = MoveTo::create(0.1f,Vec2(1040 * 0.226 + 187 *( bs_moshi - 1),154));
	hall_tishi_bs->runAction(moveOne1);*/
}

void GameHallLayer::BS_bianliang(int i)
{

	for(int k = 0 ; k < 4 ; k++ )
	{
		hall_tishi_vec.at(k)->setVisible(false);
	}
	hall_tishi_vec.at(i - 1)->setVisible(true);

	auto sprite_jiesuo_f = SpriteFrameCache::getInstance()->getSpriteFrameByName("hall_jiesuo_a.png");
	auto sprite_shangcheng_f = SpriteFrameCache::getInstance()->getSpriteFrameByName("hall_shangcheng_a.png");
	auto sprite_jineng_f = SpriteFrameCache::getInstance()->getSpriteFrameByName("hall_jineng_a.png");
	auto sprite_tiaozhan_f = SpriteFrameCache::getInstance()->getSpriteFrameByName("hall_tiaozhan_a.png");

	auto sprite_jiesuo_f1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hall_jiesuo6.png");
	auto sprite_shangcheng_f1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hall_shangcheng6.png");
	auto sprite_jineng_f1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hall_jineng6.png");
	auto sprite_tiaozhan_f1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hall_tiaozhan6.png");

	hall_dibu_sprite_jiesuo->setDisplayFrame(sprite_jiesuo_f);     //µ◊≤ø±∂¬ Ω‚À¯∞¥≈•
	hall_dibu_sprite_shangcheng->setDisplayFrame(sprite_shangcheng_f);     //µ◊≤ø…Ã≥«∞¥≈•
	hall_dibu_sprite_jineng->setDisplayFrame(sprite_jineng_f);     //µ◊≤øººƒ‹∞¥≈•
	hall_dibu_sprite_tiaozhan->setDisplayFrame(sprite_tiaozhan_f);     //µ◊≤øÃÙ’Ω∞¥≈•
 
	switch (i)
	{
	case 1:hall_dibu_sprite_jiesuo->setDisplayFrame(sprite_jiesuo_f1);  break;
	case 2:hall_dibu_sprite_shangcheng->setDisplayFrame(sprite_shangcheng_f1);  break;
	case 3:hall_dibu_sprite_jineng->setDisplayFrame(sprite_jineng_f1);  break;
	case 4:hall_dibu_sprite_tiaozhan->setDisplayFrame(sprite_tiaozhan_f1);  break;
	default:
		break;
	}
}


//***********ºÃ≥–µƒ∫Ø ˝ µœ÷
//ª¨∂Ø∞Â∫Ø ˝
void GameHallLayer::scrollViewDidScroll(extension::ScrollView* view) 
{
}

void GameHallLayer::scrollViewDidZoom(ScrollView* view) 
{
}

void GameHallLayer::scrollViewMoveOver(ScrollView* view)  
{  
    //do something  
	if(!isBiSai)
		hall_gengzheng();
}

//¥•√˛∫Ø ˝
bool GameHallLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	dianji_begin_m = true;
	mouse_p1 = touch->getLocation();
	return true;
}

void GameHallLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	float y = touch->getLocation().y;
	if(y < visibleSize.height * 0.6 + scrollView->getContentSize().height/2 && y > visibleSize.height * 0.6 - scrollView->getContentSize().height/2)
	{		
		if(!scrollview_begin_m)
		{
			scrollview_begin_m = true;
		}
	}
	
}

void GameHallLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	mouse_p2 = touch->getLocation();

	if(isBiSai)
	{
		if(mouse_p2.y - mouse_p1.y < -30 )
		{
			//”“±ﬂ“∆∂Ø
			moveBSRight();			
		}

		if(mouse_p2.y - mouse_p1.y > 30)
		{
			//◊Û±ﬂ“∆∂Ø			
			moveBSLeft();
		}
	}

	if(mouse_p2.x > mouse_p1.x)
	{
		hall_room_direct = false;
	}else
	{
		hall_room_direct = true;
	}
	dianji_begin_m = false;

	if(abs(mouse_p2.x - mouse_p1.x) < 7 )
	{
		float x =  scrollView->getPositionX() - roomSize.width/2 * HALL_ROOM_SCALE_HIGH;
		float y = scrollView->getPositionY() - roomSize.height/2 * HALL_ROOM_SCALE_HIGH;

		float y1 = hall_zuojiantou->getPositionY() - 1.5 * hall_zuojiantou->getContentSize().height;
		Rect zuojtRect = Rect(0,y1,3*hall_zuojiantou->getContentSize().width,3*hall_zuojiantou->getContentSize().height);
		Rect youjtRect = Rect(visibleSize.width - 3*hall_zuojiantou->getContentSize().width,y1,3*hall_zuojiantou->getContentSize().width,3*hall_zuojiantou->getContentSize().height);
		Rect roomLeftRect = Rect(scrollView->getPositionX() - roomSize.width - roomSize.width/2 * HALL_ROOM_SCALE_LOW ,
			scrollView->getPositionY() - roomSize.height/2 * HALL_ROOM_SCALE_LOW ,roomSize.width * HALL_ROOM_SCALE_LOW,roomSize.height * HALL_ROOM_SCALE_LOW);

		Rect roomRightRect = Rect(scrollView->getPositionX() + roomSize.width - roomSize.width/2 * HALL_ROOM_SCALE_LOW ,
			scrollView->getPositionY() - roomSize.height/2 * HALL_ROOM_SCALE_LOW ,roomSize.width * HALL_ROOM_SCALE_LOW,roomSize.height * HALL_ROOM_SCALE_LOW);

		Rect roomRect = Rect(x, y, roomSize.width * HALL_ROOM_SCALE_HIGH,roomSize.height * HALL_ROOM_SCALE_HIGH );
		if(roomRect.containsPoint(mouse_p2) && !isBiSai)
		{
			if(roomFlag[hall_room_index - 1] == 1)
			{				
				enterFishManage();
			}else
			{
				roomUnlockManage();
			}			
		}

		if(zuojtRect.containsPoint(mouse_p2) || roomLeftRect.containsPoint(mouse_p2))
		{
			if(isBiSai)
				moveBSRight();
			else
				moveToRight();
		}

		if(youjtRect.containsPoint(mouse_p2) || roomRightRect.containsPoint(mouse_p2))
		{
			
			if(isBiSai)
				moveBSLeft();
			else
				moveToLeft();
		}
	}

	log("touchesEnded");
}

//****************‘§‘º∫Ø ˝
void GameHallLayer::update(float dt)
{

	if(checkbudan == true)
	{
			// 取得 Game Sokcet
		TcpClientSocket *ptempHallSocket = LogoLayer::GetSocket();
		 
		int tempRecvLength; 
		char *pRecvBuffer;

		ptempHallSocket->RecvPack(&pRecvBuffer, tempRecvLength);
		fishHead dataHead={0};
		//已处理封包长度
		int tempPackLength = 0;

		// 检查有无资料
		if(tempRecvLength > 0)
		{
			fishHead dataHead={0};
			memcpy(&dataHead,pRecvBuffer,sizeof(fishHead));
			dataHead.len=ntohl(dataHead.len);
			if(dataHead.type==CHONGZHIBAK)
			{
				ChongZhiBak* ChongZhiBakMsg = (ChongZhiBak*)(pRecvBuffer+sizeof(fishHead));

				int zengjiagold =ntohl(ChongZhiBakMsg->coin);
				int zengjiazuanshi =ntohl(ChongZhiBakMsg->diamond);

				if(zengjiagold > 0)
				{
					cocos2d::log("zengjiagold = %d, zengjiazuanshi = %d", zengjiagold, zengjiazuanshi);
					cocos2d::log("Shop::comeKind  = %d",Shop::comeKind );		 

					GameHallLayer::RefreshCoin(zengjiagold);
					GameHallLayer::RefreshDiamond(zengjiazuanshi);	 

				
					char textTmp[200];
					sprintf(textTmp,GAME_DATA_STRING("goumai_chenggong"),zengjiagold,zengjiazuanshi);


					cocos2d::log("11111111111111111111111111111111111");

				

					cocos2d::log("22222222222222222222222222222222222222222222");

					auto  gongxi = Gongxi::create(4,textTmp);
					gongxi->setPosition(Point::ZERO);
					this->addChild(gongxi,ANNIULAYER + 100); 


					cocos2d::log("33333333333333333333333333333"); 
				}
				checkbudan =false;
				ptempHallSocket->CleanRecvBuffer(tempRecvLength);
				ptempHallSocket->CloseSocket();  
			}
		}

	}
	

 
    /*if(GameBegin::login_xiaxian)
    {
        GameBegin::login_xiaxian = false;
        
        auto zheZhao = LayerColor::create(ccc4(0,0,0,150),1024,768);
        zheZhao->setPosition(Point::ZERO);
        zheZhao->setScale(2.0f);
        this->addChild(zheZhao,1000,111);
        
        auto gongxi = Gongxi::create(7,GAME_DATA_STRING("dev_fail"));
        gongxi->setPosition(Point::ZERO);
        this->addChild(gongxi,MENULAYER,978);
        
        auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png" );
        auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(GameHallLayer::queding,this));
        auto btnMenu = Menu::create(quedingItem,nullptr);
        btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
        gongxi->getChildByTag(1)->addChild(btnMenu,100);
    }*/
    yutime += dt;
    if(yutime > 3)
    {
        yutime = 0;
        randomFish();
    }
    
	if(gonggao_vis_flag)
	{
		gonggao_vis_flag = false;
		//¥¥Ω®π´∏Ê∂‘œÛ

		auto gonggaoScene = GameEmail::createScene();
		this->addChild(gonggaoScene,MENULAYER);
	}

	if(isSaleVis)
	{
		isSaleVis = false;
		curDay = UserDefault::getInstance()->getIntegerForKey("LoginDays");
		if(curDay ==3 || curDay == 5 ||curDay == 7)
		{
			sprintf(hallCharTemp,"sale_persent_up_%d.png",(curDay-1)/2);
			hall_dibu_shop_xing->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hallCharTemp));
			hall_dibu_shop_xing1->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hallCharTemp));
			UserDefault::getInstance()->setIntegerForKey("shop_sele_tag",curDay / 2);
			UserDefault::getInstance()->flush();
		}else
		{
			UserDefault::getInstance()->setIntegerForKey("shop_sele_tag",0);
			UserDefault::getInstance()->flush();
		}
		//hall_dibu_menu_shangcheng->setZOrder(MENULAYER+100);
		auto layer = Game_Hall_Sale::createScene();
		this->addChild(layer,MENULAYER);
 
	}
	if(isCheckBS)
	{
		isCheckBS = false;
        sprintf(hallCharTemp,"%d",GameBegin::getFileData("wfsound.txt"));
        jiangbeiLayer->setString(hallCharTemp);
		BS_checkAll();
	}
	if(vip_goumai_flag)
	{
		vip_goumai_flag = false;

		auto  gongxi = VIPgongxi::create(1);
		this->addChild(gongxi,MENULAYER);

		auto sp_frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Vip_icon1.png");
		hall_vip_sp->setDisplayFrame(sp_frame);

		hall_vip_anniu->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f,Vec2(0,10)),MoveBy::create(0.25f,Vec2(0,-5)),MoveBy::create(0.25f,Vec2(0,5)),MoveBy::create(0.5f,Vec2(0,-10)),nullptr)));
	}
	if(scrollview_begin_m)
	{	
		if(hall_sv_space1 == -1 )
		{
			hall_sv_space1 = containerLayer->getPositionX();
		}else
		{
			hall_sv_space2 = containerLayer->getPositionX();
			//cocos2d::log("hall_sv_space1 = %f , hall_sv_space2 = %f , scrollview_begin_m = %b",hall_sv_space1,hall_sv_space2,scrollview_begin_m);
			if(abs(hall_sv_space1 - hall_sv_space2) < 0.1 && hall_sv_space2 <= 0 && hall_sv_space2 >= - roomSize.width * 11)
			{
				scrollview_begin_m = false;
			}else
			{
				hall_sv_space1 = hall_sv_space2;

				hall_room_moveDown();
				hall_scroll_offset = hall_sv_space1;//ªÒµ√∆´“∆X◊¯±Í(œÚ”““∆∂Ø£¨∆´“∆¡øŒ™’˝ ˝£¨œÚ◊Û‘ÚŒ™∏∫ ˝£©  
				cocos2d::log("offset pos is %f ",hall_scroll_offset);  

				//for —≠ª∑±È¿˙»›∆˜÷–µƒ√ø∏ˆæ´¡È  
				for( auto e : hall_room_spec )  
				{  
					auto pointX = e->getPositionX();//ªÒµ√µ±«∞∂‘œÛµƒX◊¯±Í£®≤ªπ‹‘ı√¥πˆ∂Ø£¨’‚∏ˆ◊¯±Í∂º «≤ª±‰µƒ£©  
					float endPosX = pointX + hall_scroll_offset;//Ω´æ´¡Èµƒ X◊¯±Í + ∆´“∆X◊¯±Í  

					//µ±endPosX‘⁄ ◊Û∞Î±ﬂ ∑∂Œß£¨‘Ú∂‘œÛµƒ¥Û–°¥”◊ÛœÚ”“µ›‘ˆ  
					if( endPosX >= sv_offset + roomSpaceLenth/2 + roomSize.width  && endPosX <=   sv_offset + (roomSpaceLenth + roomSize.width) * 1.5 )  
					{  
						float x = (endPosX - sv_offset - roomSpaceLenth/2 - roomSize.width)/(roomSize.width * 2 + 2 * roomSpaceLenth );//∑≈¥Û±∂ ˝ 0-0.5

						e->setScale(x>(HALL_ROOM_SCALE_HIGH - HALL_ROOM_SCALE_LOW)?HALL_ROOM_SCALE_HIGH:HALL_ROOM_SCALE_LOW+x);  
						log("x = %f",x);  
					}  
					//µ±endPosX‘⁄ ”“∞Î±ﬂ ∑∂Œß£¨‘Ú∂‘œÛµƒ¥Û–°¥”◊ÛœÚ”“µ›ºı  
					else if( endPosX >   sv_offset + (roomSpaceLenth + roomSize.width) * 1.5 && endPosX <=   sv_offset + 2.5 * roomSpaceLenth + roomSize.width * 2 )   
					{  
						float a = endPosX  - sv_offset - (roomSpaceLenth + roomSize.width) * 1.5;  //0-100
						float x = a / (roomSize.width * 2 + 2 * roomSpaceLenth);
						e->setScale(x > (HALL_ROOM_SCALE_HIGH - HALL_ROOM_SCALE_LOW) ? HALL_ROOM_SCALE_LOW : HALL_ROOM_SCALE_HIGH - x);  
					}  
					else  
					{  
						//≤ª «‘⁄…œ√Êµƒ∑∂Œß£¨‘Ú…Ë÷√Œ™’˝≥£¥Û–°  
						e->setScale(HALL_ROOM_SCALE_LOW);  
					}  
				}     
				UserDefault::getInstance()->setFloatForKey("hallDistance",hall_scroll_offset);
				UserDefault::getInstance()->flush();
			}
		}
	
	}
	
	if(!scrollview_begin_m && !dianji_begin_m && !hall_room_is_moveing && !isBiSai)  //¬˙◊„Ãıº˛≤≈∏¸–¬
	{
		hall_gengzheng();
	}

	if(GameHallLayer::is_bs_xianshi)
	{
		GameHallLayer::is_bs_xianshi= false;
		bs1_room_bg->setVisible(true);
	}

	if(failFlag)
	{
		failFlag = false;

		char gongxiTmp[30];
		sprintf(gongxiTmp,"check_order_%d",failInt);
		auto gongxi = Gongxi::create(2,GAME_DATA_STRING(gongxiTmp));
		gongxi->setPosition(Point::ZERO);
		this->addChild(gongxi,1000);		

		if(failInt == 24)
		{
			sprintf(hallCharTemp,"%d",GameBegin::getFileData("wfsound.txt"));
			jiangbeiLayer->setString(hallCharTemp);
		}
	}

	if(checkRedPoing)
	{
		checkRedPoing = false;

		int paoLv = GameBegin::getFileData("gameMaxPao.txt");
		int playerLv =  GameBegin::getFileData("gamePlayerlv.txt");
		int zuanshiNum = GameBegin::getFileData("jywopl.txt");
		int jinbiNum = GameBegin::getFileData("jywer.txt");
		tiaozhanShu  = 10 - UserDefault::getInstance()->getIntegerForKey("boss_day_times"); 

		sprintf(hallCharTemp,"%d",GameBegin::getFileData("wfsound.txt"));
		jiangbeiLayer->setString(hallCharTemp);

		//±∂¬ Ω‚À¯≈–∂œ
		if(paoLv<20)
		{
			hall_dibu_beilv_xing->setVisible(true);

			char beilvTmpC[30];
			sprintf(beilvTmpC,"bljs_zuanshi_%d",paoLv+1);
			int sxZuanShiNum = GAME_DATA_INT(beilvTmpC);

			memset(beilvTmpC,0,sizeof(beilvTmpC));
			sprintf(beilvTmpC,"bljs_dj_%d",paoLv+1);
			int sxDengJi = GAME_DATA_INT(beilvTmpC);

			if(playerLv >= sxDengJi && zuanshiNum >= sxZuanShiNum)
			{
				hall_dibu_beilv_xing->setVisible(true);
			}else
			{
				hall_dibu_beilv_xing->setVisible(false);
			}
		}else
		{
			hall_dibu_beilv_xing->setVisible(false);
		}

		//…˝º∂¥Û≈⁄≈–∂œ
		//∑∂Œß≈⁄
		bool fanweiX = false;
		if(scopeLv < 5)
		{
			char dapaoTmpC[30];
			sprintf(dapaoTmpC,"fwp_zuanshi_%d",scopeLv + 1);
			int fansxZuanShiNum = GAME_DATA_INT(dapaoTmpC);

			memset(dapaoTmpC,0,sizeof(dapaoTmpC));
			sprintf(dapaoTmpC,"fwp_time_%d",scopeLv);
			int fansxDengJi = GAME_DATA_INT(dapaoTmpC);
			
			if(playerLv > fansxDengJi && fansxZuanShiNum < zuanshiNum )
			{
				fanweiX = true;
			}
		}
		
		//jiguang≈⁄
		bool jiguangX = false;
		if(laserLv < 5)
		{
			char jiguangTmpC[30];
			sprintf(jiguangTmpC,"fwp_zuanshi_%d",laserLv + 1);
			int jisxZuanShiNum = GAME_DATA_INT(jiguangTmpC);

			memset(jiguangTmpC,0,sizeof(jiguangTmpC));
			sprintf(jiguangTmpC,"fwp_time_%d",laserLv + 1);
			int jisxDengJi = GAME_DATA_INT(jiguangTmpC);
			
			if(playerLv > jisxDengJi && jisxZuanShiNum < zuanshiNum )
			{
				jiguangX = true;
			}
		}
	
		if(fanweiX || jiguangX)
		{
			hall_dibu_dapao_xing->setVisible(true);
		}else
		{
			hall_dibu_dapao_xing->setVisible(false);
		}

		//ÃÙ’Ωboss≈–∂œ
		char tiaozanTmpc[20];
		sprintf(tiaozanTmpc,"%d",tiaozhanShu);
		tiaozhanShuZi->setString(tiaozanTmpc);
	}
}

//**************…Ò√ÿ…Ã»À
void GameHallLayer::chuxianShop()
{
    int ljchongzhi = GameBegin::getFileData("wflei.txt");
	int dqjinbi = GameBegin::getFileData("jywer.txt");
	//int dqzuanshi = GameBegin::getFileData("jywopl.txt");
	bool lingyuanChongZhi = UserDefault::getInstance()->getBoolForKey("leijichongzhi0");

	if(ljchongzhi == 0 && dqjinbi < 100 && !lingyuanChongZhi)
	{
		shenmiShop(1);
	}

	/*if(ljchongzhi > 20 && dqjinbi < 1000 && dqzuanshi>1000)
	{
		shenmiShop(10);
	}*/
}

void GameHallLayer::shenmiShop(int kind)
{
	Vector<SpriteFrame*> sp_vec;  
	if(AnimationCache::getInstance()->getAnimation("hand") == NULL)
	{ 
		sp_vec.clear(); 
		for(int j = 1;j < 3;j++)	
		{ 
			char cTempFishSprite[30];
			sprintf(cTempFishSprite,"hand%d.png" ,j); 
			SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite); 
			sp_vec.pushBack(spriteFrame); 
		}
		auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
		JiGuangFrameTwo->setDelayPerUnit(1.0f);  
		AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "hand");  
	}
	if(AnimationCache::getInstance()->getAnimation("smShop_icon") == NULL)
	{
		sp_vec.clear(); 
		for(int j = 1;j < 9;j++)	
		{ 
			char cTempFishSprite[30];
			sprintf(cTempFishSprite,"zpdh%d.png" ,j); 
			SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite); 
			sp_vec.pushBack(spriteFrame); 
		}
		auto jiguangthree = Animation::createWithSpriteFrames(sp_vec);
		jiguangthree->setDelayPerUnit(0.1f); 
		AnimationCache::getInstance()->addAnimation(jiguangthree, "smShop_icon");  
	} 

	if(AnimationCache::getInstance()->getAnimation("smShop_icong") == NULL)
	{
		sp_vec.clear(); 
		for(int j = 1;j < 4;j++)	
		{ 
			char cTempFishSprite[30];
			sprintf(cTempFishSprite,"zpdh_g%d.png" ,j); 
			SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite); 
			sp_vec.pushBack(spriteFrame); 
		}
		auto jiguangthree = Animation::createWithSpriteFrames(sp_vec);
		jiguangthree->setDelayPerUnit(0.1f); 
		AnimationCache::getInstance()->addAnimation(jiguangthree, "smShop_icong");  
	} 



	if(!UserDefault::getInstance()->getBoolForKey("isFirstSmShop"))
	{
		auto zheZhao = LayerColor::create(ccc4(0,0,0,120),1024,768);
		zheZhao->setTag(197);
		zheZhao->setPosition(Point::ZERO);
		zheZhao->setScale(2.0f);
		this->addChild(zheZhao,MENULAYER - 1);

		Animation* handAnimation = AnimationCache::getInstance()->getAnimation("hand"); 
		Animate*  handAnimate = Animate::create(handAnimation);

		auto hand = Sprite::create();  
		addChild(hand,MENULAYER + 1);
		hand->setTag(198);
		hand->runAction(RepeatForever::create(handAnimate)); 
		hand->setPosition(Vec2(155 + origin.x ,visibleSize.height - 60 + origin.y));

		hand->setScale(0.7f);
	}

	

	auto smIcon = Sprite::createWithSpriteFrameName("zpdh1.png");
	smIcon->setScale(0.8);

	auto smIconItem = MenuItemSprite::create(smIcon,smIcon,smIcon,CC_CALLBACK_1(GameHallLayer::menuShenmiShop,this));
	smIconItem->setTag(kind);
	auto smMenu = Menu::create(smIconItem,nullptr);
	smMenu->setPosition(Vec2(150 + origin.x ,visibleSize.height - 50 + origin.y));
	addChild(smMenu,MENULAYER,199);

	auto smIcon_a = AnimationCache::getInstance()->getAnimation("smShop_icon");
	auto smIcon_an = Animate::create(smIcon_a);
	smIcon->runAction(RepeatForever::create(smIcon_an));

	auto smIcong = Sprite::createWithSpriteFrameName("zpdh_g1.png");
	smIcong->setPosition(Vec2(smIcon->getContentSize().width/2,smIcon->getContentSize().height/2));
	smIcon->addChild(smIcong);

	auto smIcong_a = AnimationCache::getInstance()->getAnimation("smShop_icong");
	auto smIcong_an = Animate::create(smIcong_a);
	smIcong->runAction(RepeatForever::create(smIcong_an));
}

void GameHallLayer::menuShenmiShop(Ref* pSender)
{
	this->removeChildByTag(199);
	this->removeChildByTag(198);
	this->removeChildByTag(197);

	auto item = (MenuItemSprite *)pSender;
    
    this->stopAllActions();
    this->removeAllChildrenWithCleanup(true);
    this->unscheduleAllSelectors();
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
    
	auto layer = smShop::createScene(item->getTag());
	Director::getInstance()->replaceScene(layer);
}


//**************π´”√µƒ∫Ø ˝
//∏¸–¬”„±“
void GameHallLayer::RefreshCoin(int coinNum)
{

	int tmpMonty = GameBegin::getFileData("jywer.txt") + coinNum;

	char tmpCoinNum[40];
	sprintf(tmpCoinNum,"%d",tmpMonty);
	yubiLabel->setString(tmpCoinNum);  

	GameBegin::setFileData("jywer.txt",tmpMonty);
    GameBegin::baidu_qiehuan();
	if(UserDefault::getInstance()->getIntegerForKey("bisaimoshi") == 1)
		isCheckBS = true;
 
}

//∏¸–¬◊Í Ø
void GameHallLayer::RefreshDiamond(int diamondNum)
{
	int tmpMonty = GameBegin::getFileData("jywopl.txt") + diamondNum;

	char tmpCoinNum[40];
	sprintf(tmpCoinNum,"%d",tmpMonty);
	zuanshiLabel->setString(tmpCoinNum);  

	GameBegin::setFileData("jywopl.txt",tmpMonty);
    GameBegin::baidu_qiehuan();
	if(UserDefault::getInstance()->getIntegerForKey("bisaimoshi") == 0)
		GameHallLayer::checkRedPoing = true;
}



//**************** SALE ***********************
Scene* Game_Hall_Sale::createScene()
{
	auto scene = Scene::create();
	auto layer = Game_Hall_Sale::create();
	scene->addChild(layer);

	return scene;
}

bool Game_Hall_Sale::init()
{
	if ( !Layer::init() )	
	{
		return false;
	}
 
	auto visibleSize = Director::getInstance()->getVisibleSize();//ªÒµ√ø… ”«¯”Úµƒ¥Û–°
	Point origin = Director::getInstance()->getVisibleOrigin();//ªÒµ√ø… ”«¯”Úµƒ∆ º◊¯±Íori

	curDay = UserDefault::getInstance()->getIntegerForKey("LoginDays");
	curDay = curDay < 3 ? 3 : curDay;

	auto zheZhao = LayerColor::create(ccc4(0,0,0,150),1024,768);
	zheZhao->setPosition(Point::ZERO);
	this->addChild(zheZhao);
 
	//–«–«±≥æ∞
	auto box_baby_bg = Sprite::createWithSpriteFrameName("hall_ssxx_bg.png");
	box_baby_bg->setScale(4.0f);
	box_baby_bg->setVisible(false);
	box_baby_bg->setPosition(Point(visibleSize.width*0.5,visibleSize.height*0.7));
	addChild(box_baby_bg);

	box_baby_bg->runAction(Sequence::create(DelayTime::create(1.7f),ToggleVisibility::create(),nullptr));
	box_baby_bg->runAction(RepeatForever::create(RotateBy::create(1.0f,10)));
	//±¶œ‰1
	sprintf(sale_tmp,"sale_buff_%d.png",(curDay-1)/2);
	box_baby = Sprite::createWithSpriteFrameName(sale_tmp);
	box_baby->setScale(0.9);
	box_baby->setPosition(Vec2(visibleSize.width*0.5,visibleSize.height*1.3));
	addChild(box_baby);

	auto action1 = EaseBounceIn::create(MoveTo::create(0.3f,Vec2(visibleSize.width*0.5,visibleSize.height*0.7)));
	auto action2 = Repeat::create(Sequence::create(RotateBy::create(0.1f,10),RotateBy::create(0.2f,-20),RotateBy::create(0.1f,10),DelayTime::create(0.2f),nullptr),2);
	//auto action3 = RemoveSelf::create();
	box_baby->runAction(Sequence::create(action1,action2,nullptr));
	this->scheduleOnce(schedule_selector(Game_Hall_Sale::vis_box),1.7f);

	//±¶œ‰2
	//sprintf(sale_tmp,"sale_buff_%d_1.png",(curDay-1)/2);
	//auto box_babyo = Sprite::createWithSpriteFrameName(sale_tmp);
	//box_babyo->setScale(0.9);
	//box_babyo->setVisible(false);
	//box_babyo->setPosition(Point(visibleSize.width*0.5,visibleSize.height*0.7));
	//addChild(box_babyo);

	//box_babyo->runAction(Sequence::create(DelayTime::create(1.2f),ToggleVisibility::create(),nullptr));

	//word
	auto box_word = Sprite::createWithSpriteFrameName("sale_buff_word.png");
	box_word->setScale(0.9);
	box_word->setVisible(false);
	box_word->setPosition(Point(visibleSize.width*0.5,visibleSize.height*0.434));
	addChild(box_word);

	box_word->runAction(Sequence::create(DelayTime::create(1.7f),ToggleVisibility::create(),nullptr));
 
	//percent
	sprintf(sale_tmp,"sale_persent_%d.png",(curDay-1)/2);
	auto box_percent = Sprite::createWithSpriteFrameName(sale_tmp);
	box_percent->setPosition(Point(110,50));
    box_percent->setScale(0.9f);
	box_word->addChild(box_percent);

	auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png" );
	auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(Game_Hall_Sale::exit,this));
	auto btnMenu = Menu::create(quedingItem,nullptr);
	btnMenu->setPosition(Point(visibleSize.width/2,visibleSize.height * 0.25));
	btnMenu->setVisible(false);
	addChild(btnMenu,100);
 
	btnMenu->runAction(Sequence::create(DelayTime::create(1.7f),ToggleVisibility::create(),nullptr));
 
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Game_Hall_Sale::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(Game_Hall_Sale::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(Game_Hall_Sale::onTouchEnded,this);
	listener->setSwallowTouches(true);//≤ªœÚœ¬¥´µ›¥•√˛
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}

void Game_Hall_Sale::vis_box(float dt)
{
	sprintf(sale_tmp,"sale_buff_%d_1.png",(curDay-1)/2);
	box_baby->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(sale_tmp));
}

void Game_Hall_Sale::exit()
{
	GameBegin::buttonSound(); 

	ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
	this->runAction(Sequence::create(ac7,ac8,RemoveSelf::create(),nullptr) ); 
}

bool Game_Hall_Sale::onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	
	return true;
}

void Game_Hall_Sale::onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	
}
 
void Game_Hall_Sale::onTouchEnded(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	//exit();
	log("touchesEnded");
}
 


//**************************************&&&&&&&&&&&&&&&&&&&&&&&&&
Scene * Game_Hall_Huafei::createScene()
{
	auto scene = Scene::create();
	auto layer = Game_Hall_Huafei::create();
	scene->addChild(layer);

	return scene;
}

bool Game_Hall_Huafei::init()
{  
	if ( !Layer::init() )	
	{
		return false;
	}
	curHuafeiKind = UserDefault::getInstance()->getIntegerForKey("huafei_kind");

	visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();

	auto zheZhao = LayerColor::create(ccc4(0,0,0,150),1024,768);
	zheZhao->setPosition(Point::ZERO);
	this->addChild(zheZhao);

	//øÿ÷∆√Ê∞Â
	controlBg = Sprite::createWithSpriteFrameName("vip_js_bg.png");
	controlBg->setVisible(false);
	controlBg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(controlBg);
 
	controlBg->setScale(0.1f);
	ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.1f, 1.0);  
	controlBg->runAction(Sequence::create(ac7,ac8,nullptr)); 
 
	auto shopCenterBg = Sprite::createWithSpriteFrameName("hall_ssxx_bg.png");
	shopCenterBg->setScale(4);
	shopCenterBg->setPosition(Point(controlBg->getContentSize().width/2,controlBg->getContentSize().height * 0.55));
	controlBg->addChild(shopCenterBg,100);

	shopCenterBg->runAction(RepeatForever::create(RotateBy::create(1.0f,5)));
 
	/*auto shopCenterBg1 = Sprite::createWithSpriteFrameName("huafei_title.png");
	shopCenterBg1->setPosition(Point(controlBg->getContentSize().width/2,controlBg->getContentSize().height));
	controlBg->addChild(shopCenterBg1,100);

	auto shopCenterBg2 = Sprite::createWithSpriteFrameName("huafei_logo.png");
	shopCenterBg2->setPosition(Point(controlBg->getContentSize().width/2,controlBg->getContentSize().height * 0.55));
	controlBg->addChild(shopCenterBg2,100);
 */
	

	auto tishi = LabelTTF::create(GAME_DATA_STRING("huafei_3"),"Arial",20);
	tishi->setPosition(Vec2(controlBg->getContentSize().width/2,controlBg->getContentSize().height * 0.27));
	controlBg->addChild(tishi,100);
 
	/*auto gongxiSprite = Sprite::createWithSpriteFrameName("c");
	auto gongxiItem = MenuItemSprite::create(gongxiSprite,gongxiSprite,gongxiSprite,CC_CALLBACK_0(Game_Hall_Huafei::duihuan,this));
	auto gongxiMenu = Menu::create(gongxiItem,nullptr);
	gongxiMenu->setPosition(controlBg->getContentSize().width/2,0.15*controlBg->getContentSize().height);
	controlBg->addChild(gongxiMenu,100);
*/
	// ‰»ÎøÚ

	//øÿ÷∆√Ê∞Â
	controlBg1 = Scale9Sprite::createWithSpriteFrameName( "bs_kuang.png",CCRectMake(50,50,20,20));
	controlBg1->setContentSize(CCSizeMake(600,400));
	//controlBg1->setVisible(false);
	controlBg1->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(controlBg1);
    
    auto shangchengxx = MenuItemSprite::create(Sprite::createWithSpriteFrameName("hall_menu_X.png"),Sprite::createWithSpriteFrameName("hall_menu_X_d.png"), CC_CALLBACK_0(Game_Hall_Huafei::exit,this));
    auto m_ShangChengXX= Menu::create(shangchengxx, nullptr);
    m_ShangChengXX->setPosition(Vec2(controlBg1->getContentSize().width - 10,controlBg1->getContentSize().height - 10));
    controlBg1->addChild(m_ShangChengXX,100);

	shurukuang = EditBox::create(Size(400,45),Scale9Sprite::createWithSpriteFrameName("match_diren_mzk.png"),Scale9Sprite::createWithSpriteFrameName("match_diren_mzk.png"),nullptr);
	shurukuang->setPosition(Vec2(controlBg1->getContentSize().width*0.5,controlBg1->getContentSize().height * 0.82));
	shurukuang->setFont("Arial", 28);
    shurukuang->setFontColor(Color3B::WHITE);
	shurukuang->setPlaceHolder(GAME_DATA_STRING("huafei_4"));
	shurukuang->setPlaceholderFontColor(Color3B::WHITE);
    shurukuang->setMaxLength(100);
    shurukuang->setInputMode(EditBox::InputMode::SINGLE_LINE);
	shurukuang->setReturnType(EditBox::KeyboardReturnType::DONE);
    shurukuang->setDelegate(this);
    controlBg1->addChild(shurukuang,100);

	shurukuang1 = EditBox::create(Size(400,45),Scale9Sprite::createWithSpriteFrameName("match_diren_mzk.png"),Scale9Sprite::createWithSpriteFrameName("match_diren_mzk.png"),nullptr);
	shurukuang1->setPosition(Vec2(controlBg1->getContentSize().width*0.5,controlBg1->getContentSize().height * 0.7));
	shurukuang1->setFont("Arial", 28);
    shurukuang1->setFontColor(Color3B::WHITE);
	shurukuang1->setPlaceHolder(GAME_DATA_STRING("huafei_10"));
	shurukuang1->setPlaceholderFontColor(Color3B::WHITE);
    shurukuang1->setMaxLength(100);
    shurukuang1->setInputMode(EditBox::InputMode::SINGLE_LINE);
	shurukuang1->setReturnType(EditBox::KeyboardReturnType::DONE);
    shurukuang1->setDelegate(this);
    controlBg1->addChild(shurukuang1,100);

	auto tishi1 = LabelTTF::create(GAME_DATA_STRING("huafei_5"),"Arial",16);
	tishi1->setAnchorPoint(Vec2(0,0.5));
	tishi1->setPosition(Vec2(50,controlBg1->getContentSize().height * 0.6));
	controlBg1->addChild(tishi1,100);

	auto tishi2 = LabelTTF::create(GAME_DATA_STRING("huafei_6"),"Arial",16);
	tishi2->setAnchorPoint(Vec2(0,0.5));
	tishi2->setPosition(Vec2(50,controlBg1->getContentSize().height * 0.5));
	controlBg1->addChild(tishi2,100);

	auto tishi3 = LabelTTF::create(GAME_DATA_STRING("huafei_7"),"Arial",16);
	tishi3->setAnchorPoint(Vec2(0,0.5));
	tishi3->setPosition(Vec2(50,controlBg1->getContentSize().height * 0.4));
	controlBg1->addChild(tishi3,100);

	auto tishi4 = LabelTTF::create(GAME_DATA_STRING("huafei_8"),"Arial",16);
	tishi4->setAnchorPoint(Vec2(0,0.5));
	tishi4->setPosition(Vec2(50,controlBg1->getContentSize().height * 0.3));
	controlBg1->addChild(tishi4,100);

	/*auto tishi5 = LabelTTF::create(GAME_DATA_STRING("huafei_9"),"Arial",16);
	tishi5->setAnchorPoint(Vec2(0,0.5));
	tishi5->setPosition(Vec2(50,controlBg1->getContentSize().height * 0.255));
	controlBg1->addChild(tishi5,100);*/

	auto queding_sp = Sprite::createWithSpriteFrameName("XR_qd.png");
	auto quedingItem = MenuItemSprite::create(queding_sp,queding_sp,CC_CALLBACK_0(Game_Hall_Huafei::queding,this));
	auto quedingMenu = Menu::create(quedingItem,nullptr);
	quedingMenu->setPosition(controlBg1->getContentSize().width/2,0.13*controlBg1->getContentSize().height);
	controlBg1->addChild(quedingMenu,100);
 
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Game_Hall_Huafei::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(Game_Hall_Huafei::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(Game_Hall_Huafei::onTouchEnded,this);
	listener->setSwallowTouches(true);//≤ªœÚœ¬¥´µ›¥•√˛
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

    return true;
}

bool Game_Hall_Huafei::onTouchBegan(Touch* touch, Event* event) 
{  
	return true;
}

void Game_Hall_Huafei::onTouchMoved(Touch* touch, Event* event) 
{ 

}

void Game_Hall_Huafei::onTouchEnded(Touch* touch, Event* event)
{
	//exit();
}

void Game_Hall_Huafei::editBoxReturn(EditBox *editBox)
{
	log("editBox %p was returned.", editBox->getText());
}

void Game_Hall_Huafei::duihuan()
{
 
	int huafeiquan = GameBegin::getFileData("wfsound.txt");
	//int lejichongzhi = UserDefault::getInstance()->getIntegerForKey("leijichongzhi");

	if(huafeiquan  == 0)
	{
		auto tishi = Gongxi::create(2,GAME_DATA_STRING("huafei_1"));
		this->addChild(tishi,MENULAYER);
		return;
	}
 
	if(huafeiquan < 1000)
	{
		auto tishi = Gongxi::create(2,GAME_DATA_STRING("huafei_2"));
		this->addChild(tishi,MENULAYER);
		return;
	}
 
	controlBg->setVisible(false);
	controlBg1->setVisible(true);

}

bool isPhoneNum(const std::string& strIp)  
{  
    //—È÷§IPµÿ÷∑µƒƒ£ Ω£¨’‚¿Ô"\."÷–µƒ"\" «◊™“Â◊÷∑˚,±Ì æ’‚ «“ª∏ˆ.  
   

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
         const std::regex pattern("^[1][358][0-9]{9}$");  
		 return std::regex_match(strIp, pattern);  
#endif  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
 
		 char ss[100] = {};  
		 sprintf(ss,"%s",strIp.c_str());  
		 regmatch_t pmatch[4];  
		 regex_t match_regex;  

		 regcomp( &match_regex,  
			 "^[1][358][0-9]{9}$",  
			 REG_EXTENDED );  
		 if ( regexec( &match_regex, ss, 4, pmatch, 0 ) != 0 )  
		 {  			  
			 return false;  
		 }  
		 regfree( &match_regex ); 
		 return true;
#endif
    //∆•≈‰—È÷§  
    
}  

void Game_Hall_Huafei::queding()
{
	//÷¥––≤πµ•≤Ÿ◊˜
	//µØ≥ˆøÚ «Î…‘∫Û 
	GameBegin::buttonSound(); 
 
	string phone = shurukuang->getText();
	string phone1 = shurukuang1->getText();
    
    string phone3 = UserDefault::getInstance()->getStringForKey("login_phone_num");

    if(phone3  == "")
    {
        auto gongxi = Gongxi::create(2,GAME_DATA_STRING("huafei_13"));
        this->addChild(gongxi,MENULAYER);
        return;
    }
   
    if(!isPhoneNum(phone))
    {
        auto gongxi = Gongxi::create(2,GAME_DATA_STRING("huafei_12"));
        this->addChild(gongxi,MENULAYER);
        return;
    }
	if(phone != phone1)
	{
		auto gongxi = Gongxi::create(2,GAME_DATA_STRING("huafei_11"));
		this->addChild(gongxi,MENULAYER);
		return;
	}
    
    if(phone3  != phone1)
    {
        auto gongxi = Gongxi::create(2,GAME_DATA_STRING("huafei_14"));
        this->addChild(gongxi,MENULAYER);
        return;
    }
    

	string DeviceNo = UserDefault::getInstance()->getStringForKey("DeviceNo");
 
    int leijichongzhi = GameBegin::getFileData("wflei.txt");
	int duihuanhuafei;
	int huafeiKind = UserDefault::getInstance()->getIntegerForKey("huafei_kind");

	if(huafeiKind == 1) duihuanhuafei = 100;
	if(huafeiKind == 2) duihuanhuafei = 200;
	if(huafeiKind == 3) duihuanhuafei = 300;
  
    int huafeiquan = GameBegin::getFileData("wfsound.txt");
 

	CURL *curl;
    CURLcode res;
    std::string cc;
    curl=curl_easy_init();
	
	char postFields[200];
 
	sprintf(postFields,"deviceNo=%s&phone=%s&qudao=%s&duihuanhuafei=%d",DeviceNo.c_str(),phone.c_str(),"ios_v6.0",duihuanhuafei);
	cocos2d::log("Game_Hall_Huafei:: ª∞∑—«Î«Û∞¸£∫ %s",postFields); 
    if(curl)
    {
        curl_easy_setopt( curl, CURLOPT_URL, "http://buyu2.iyueyo.com/qpby2/huafei/huafei_duihua_6.0.php"); //«Î«Ûµƒµÿ÷∑
        curl_easy_setopt(curl, CURLOPT_POST, true);                     //∆Ù”√POSTÃ·Ωª 
		curl_easy_setopt(curl,CURLOPT_TIMEOUT,3000);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields); //∑¢ÀÕµƒ ˝æ›
		curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L); 
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&possText); //¥¶¿Ìµƒ∫Ø ˝
        res=curl_easy_perform(curl);
        if(res!=CURLE_OK)
        {
 
        } 
        curl_easy_cleanup(curl);
    }
    else
    { 
        return ;
    } 
	exit();
}

size_t  Game_Hall_Huafei::possText(uint8_t *buffer,size_t size,size_t nmemb,void *stream)
{
	//¥Ú”° ’µΩµƒ ˝æ›
	cocos2d::log("SHOP::*****possIt_____%s____",(const char *)buffer);	
	
  
    
    string tmpstring = (const char *)buffer;
 
    
	if(tmpstring == "success")
	{
		int huafeiKind = UserDefault::getInstance()->getIntegerForKey("huafei_kind");
 
        int huafeiquan = GameBegin::getFileData("wfsound.txt");
		if(huafeiKind == 1)
        {
            huafeiquan -= 1000;
           
        }
		else if(huafeiKind == 2)
        {
            huafeiquan -= 2000;
            
        }
		else if(huafeiKind == 3)
        {
            huafeiquan -= 3000;
            
        }
        if(huafeiquan < 0)
        {
            huafeiquan = 0;
        } 
       
        
        GameBegin::setFileData("wfsound.txt", huafeiquan);
        
		UserDefault::getInstance()->flush();

		GameHallLayer::failFlag = true;
		GameHallLayer::failInt = 24;
	}
    else if(tmpstring == "error1")
	{
		GameHallLayer::failFlag = true;
		GameHallLayer::failInt = 29;
	}
    else if(tmpstring == "error2")
    {
        GameHallLayer::failFlag = true;
        GameHallLayer::failInt = 30;
    }
    else if(tmpstring == "error3")
    {
        GameHallLayer::failFlag = true;
        GameHallLayer::failInt = 31 ;
    }

	//∑µªÿ ˝æ›≥§∂»
	size_t sizes = size*nmemb;
	return sizes;
}
 
void Game_Hall_Huafei::exit()
{
//	GameBegin::buttonSound(); 
	ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
	if(controlBg->isVisible())
		controlBg->runAction(Sequence::create(ac7,ac8,nullptr)); 
	else
		controlBg1->runAction(Sequence::create(ac7,ac8,nullptr)); 

	this->runAction(Sequence::create(DelayTime::create(0.3f),RemoveSelf::create(),nullptr));
}

