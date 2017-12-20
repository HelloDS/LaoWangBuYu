#include "GameBegin.h"
#include "UIWebViewTest.h"
#include "ui/CocosGUI.h"
#include "LoadRes.h"
#include "GameData.h"
#include "Gongxi.h"
#include "GameEmail.h"
#include "GameSet.h"
#include "GameHelp.h"
#include "ZuanPan.h"
#include "GameHallLayer.h"
#include "FishLayer.h"
#include "smShop.h"
#include "InitPlayer.h"
#include "LogoLayer.h"
#include "GameScene.h"
#include "Waiting.h"
#include "ChallengeBOSS.h"
#include "Shop.h"
#include "Gonggao.h"
//#include "CannonLayer.cpp"
#include "json/rapidjson.h"
#include "json/document.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "../cocos2d/external/curl/include/ios/curl/curl.h"
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#endif



#if(CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) 
#include "../cocos2d/external/curl/include/android/curl/curl.h"
#include <sys/stat.h> 
#include <unistd.h>
#include <dirent.h> 
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include "..\cocos2d\external\curl\include\win32\curl\curl.h"
#endif

#include <regex>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <regex.h>
#endif

USING_NS_CC;

using namespace std;

char GameBegin::ifOldZhangHao = 0;
bool GameBegin::login_xiaxian = false;
int GameBegin::login_fail_flag = 1;
bool GameBegin::login_success = false;
bool GameBegin::login_fail = false;

int GameBegin::dengluint = 0;
bool GameBegin::dengluios = false;
bool GameBegin::is_ios_yueyu = false;

bool GameBegin::canPlaySound = true;
bool GameBegin::canPlayMusic = true;
bool GameBegin::dengluCheng = false;
bool GameBegin::dengluShi = false;

bool GameBegin::isJinRu = false;
int GameBegin::curScene = 1;
char GameBegin::cGetDev = 0;

char GameBegin::cjingxipingbi = 0;
string GameBegin::baiduID="";
int GameBegin::musicNum = 1;
float GameBegin::scaleYNum = 0.9*0.85;
int GameBegin::WangW[6] = {3,5,7,9,14,20};
int GameBegin::gb_fish_num[12] = {1,1,1,1,1,2,2,1,1,2,2,3};

Scene* GameBegin::createScene()
{
    
    
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	auto layer =  GameBegin::create() ;
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void GameBegin::removeSouce(int i)
{
    
    
    
    if(i == 1) //大厅的资源
    {
        /*
        AnimationCache::getInstance()->removeAnimation("hall_shuichao") ;
        AnimationCache::getInstance()->removeAnimation("hall_ssxx") ;
        AnimationCache::getInstance()->removeAnimation("hall_room_suo") ;
        AnimationCache::getInstance()->removeAnimation("hall_jineng") ;
        AnimationCache::getInstance()->removeAnimation("hall_shangcheng") ;
        AnimationCache::getInstance()->removeAnimation("hall_jiesuo") ;
        AnimationCache::getInstance()->removeAnimation("hall_tiaozhan") ;
        AnimationCache::getInstance()->removeAnimation("hall_bsjiantou") ;
        AnimationCache::getInstance()->removeAnimation("hb_paomadeng") ;
        
        SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("gameHall2.plist");
        TextureCache::getInstance()->removeTextureForKey("gameHall2.png");*/
        
        SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("gameHall3.plist");
        TextureCache::getInstance()->removeTextureForKey("gameHall3.png");
       
        TextureCache::getInstance()->removeTextureForKey("hall_BG.png");
        TextureCache::getInstance()->removeTextureForKey("hall_yangguang.png");
        TextureCache::getInstance()->removeTextureForKey("Ranklight1.png");
        TextureCache::getInstance()->removeTextureForKey("boss_map.png");
        TextureCache::getInstance()->removeTextureForKey("guanchoosetwo.png");
        
        
    }else if(i == 2)//远征的资源
    {
        AnimationCache::getInstance()->removeAnimation("boss_small_pass") ;
        AnimationCache::getInstance()->removeAnimation("boss_big_pass") ;
        
        
        SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("bossChange.plist");
        TextureCache::getInstance()->removeTextureForKey("bossChange.png");
        TextureCache::getInstance()->removeTextureForKey("boss_map.png");
    }
    else if(i == 3 ) //场景的资源
    {
        
        TextureCache::getInstance()->removeTextureForKey("bossbgguangwf.png");
        TextureCache::getInstance()->removeTextureForKey("exptiao.png");
        TextureCache::getInstance()->removeTextureForKey("exp.png");
        TextureCache::getInstance()->removeTextureForKey("bossexp.png");
        TextureCache::getInstance()->removeTextureForKey("bossexptiao.png");
        TextureCache::getInstance()->removeTextureForKey("fanweitexiaotwo.png");
        
        
 
        char bgTmp[20];
        string fullLuJin = FileUtils::getInstance()->getWritablePath();
        for(int i =0; i< 12; i++)
        {
            
            sprintf(bgTmp,"scene%dBG.jpg",i + 1);
            if(i< 3)
            TextureCache::getInstance()->removeTextureForKey(bgTmp);
            else
            TextureCache::getInstance()->removeTextureForKey(fullLuJin + bgTmp);

        }
        
        
        
        
         AnimationCache::getInstance()->removeAnimation("coinwf") ; 
         AnimationCache::getInstance()->removeAnimation("paoTexiao") ;
        AnimationCache::getInstance()->removeAnimation("shuibo") ;
        AnimationCache::getInstance()->removeAnimation("fish_animation_ship") ;
        AnimationCache::getInstance()->removeAnimation("jineng_g") ; 
        AnimationCache::getInstance()->removeAnimation("fanweioneani") ;
       AnimationCache::getInstance()->removeAnimation("jiguanganione") ;
       AnimationCache::getInstance()->removeAnimation("jiguanganitwo") ;
      AnimationCache::getInstance()->removeAnimation("jiguanganithree") ;
      AnimationCache::getInstance()->removeAnimation("jb_") ;
       AnimationCache::getInstance()->removeAnimation("yb_") ;
     
        AnimationCache::getInstance()->removeAnimation("JiGuangFrameTwo") ;
        AnimationCache::getInstance()->removeAnimation("JiGuangFrameThree") ;
       AnimationCache::getInstance()->removeAnimation("baozaframe") ;
        AnimationCache::getInstance()->removeAnimation("panziguang") ;
        AnimationCache::getInstance()->removeAnimation("bulletComb0") ;
       AnimationCache::getInstance()->removeAnimation("bulletComb1") ;
      AnimationCache::getInstance()->removeAnimation("bulletComb2") ;
        AnimationCache::getInstance()->removeAnimation("bulletComb3") ;
        
        
        
        SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("gameScene1.plist");
        SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("gameScene3.plist");
        
        SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("bullet_comp.plist");
        
        
        TextureCache::getInstance()->removeTextureForKey("gameScene1.png");
        TextureCache::getInstance()->removeTextureForKey("gameScene3.png");
        TextureCache::getInstance()->removeTextureForKey("bullet_comp.png");
        
        
        
        
        int dele  = 0;
         dele =GameHallLayer::RoomType;
       if( GameHallLayer::RoomType == 89)
           dele =LoadRes::RoomType;
        
        char tmpAnima[40];
        for(int j = 0 ; j < 26 ; j++)
        {
            sprintf(tmpAnima,"fish_animation_%d_%d",dele,j);
            AnimationCache::getInstance()->removeAnimation(tmpAnima);
            
            sprintf(tmpAnima,"dfish_animation_%d",j);
            AnimationCache::getInstance()->removeAnimation(tmpAnima);
            
        }

        //清除普通场景缓存
        //if(StaticData::roomread != GameHallLayer::RoomType)   //rootType;  普通 0-11  挑战 65  比赛  90 91 92  93
      string resourceRoad = FileUtils::getInstance()->getWritablePath();
     
	  if(GameHallLayer::RoomType == 89)
	  {

		  char plistname[60];
		  char pngname[60];
		  int m = LoadRes::RoomType;
		  m = m - 88;
		  if(m == 5) m = 4;

		  sprintf(plistname,"BSscene/BSscene%dfishlist1.plist",m);
		  sprintf(pngname,"BSscene/BSscene%dfishlist1.png",m);

		  SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(plistname);
		  TextureCache::getInstance()->removeTextureForKey(pngname);


	  }
	  else
	  {
		  int j =GameHallLayer::RoomType;
		  if(j < 3)
		  {
			  for(int i = 0; i<GameBegin::gb_fish_num[j];i++)
			  {
				  char plistname[60];
				  char pngname[60];

				  sprintf(plistname,"scene/scene%dfishlist%d.plist",j+1,i+1);
				  sprintf(pngname,"scene/scene%dfishlist%d.png",j+1,i+1);

				  SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(plistname );
				  TextureCache::getInstance()->removeTextureForKey(pngname);
			  }

		  }else if(GameHallLayer::RoomType < 12)
		  {
			  for(int i = 0; i<GameBegin::gb_fish_num[j];i++)
			  {
				  char plistname[60];
				  char pngname[60];

				  sprintf(plistname,"scene%dfishlist%d.plist",j+1,i+1);
				  sprintf(pngname,"scene%dfishlist%d.png",j+1,i+1);

				  SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(resourceRoad + plistname );
				  TextureCache::getInstance()->removeTextureForKey(resourceRoad + pngname);

			  }
		  }else
		  {
			  char plistname[60];
			  char pngname[60];

			  j = j - 88;
			  if(j == 5) j = 4;

			  sprintf(plistname,"BSscene/BSscene%dfishlist1.plist",j);
			  sprintf(pngname,"BSscene/BSscene%dfishlist1.png",j);

			  SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(plistname);
			  TextureCache::getInstance()->removeTextureForKey(pngname);
		  }

	  }
          
         
    }
    
}

bool GameBegin::init()
{

	// 1. super init first
	if ( !Layer::init() )	
	{
		return false;
	}
  
    ifOldZhangHao = 0;
    cGetDev = 0;
    TextureCache::getInstance()->removeTextureForKey("logopng.png");
    
	// GameBegin::get_Test(2);
  
    // int a  = UserDefault::getInstance()->getIntegerForKey("firstdenglu");
    if(UserDefault::getInstance()->getIntegerForKey("firstdenglu") < 1)
    {
        auto waiting = Waiting::create();
        waiting->setString(GAME_DATA_STRING("begin_login"));
        this->addChild(waiting,1000,977);
        GameBegin::get_deviceNo(2);
    }
    else
    {
        GameBiginInit();
    }
    
     this->scheduleUpdate();
	return true;
}



void GameBegin::GameBiginInit()
{
    
    
    GameBegin::curScene = 1;
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameHall/gameHall1.plist","gameHall/gameHall1.png");
    wait_time = 0;
    
    //Application::getInstance()->openURL("http://www.baidu.com");
    srand(time(NULL));
    int tx = CCRANDOM_0_1()*7 + 1;
    cocos2d::log(" tx index = %d",tx);
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
 //   UserDefault::getInstance()->setIntegerForKey("firstdenglu" ,0);
    
    if(UserDefault::getInstance()->getIntegerForKey("player_touxiang") == 0)
        UserDefault::getInstance()->setIntegerForKey("player_touxiang",tx);
    if(UserDefault::getInstance()->getIntegerForKey("firstdenglu") == 0)
    {
        UserDefault::getInstance()->setIntegerForKey("first_fenxiang", 0);
        UserDefault::getInstance()->setIntegerForKey("gameMoney_hd",1000);
        UserDefault::getInstance()->setIntegerForKey("gameZuanshi_hd",0);
        
        
        UserDefault::getInstance()->setIntegerForKey("gonggao_version",0);
        UserDefault::getInstance()->setStringForKey("gg_title","");
        UserDefault::getInstance()->setStringForKey("gg_content","");
        UserDefault::getInstance()->setIntegerForKey("gg_yubi",0);
        UserDefault::getInstance()->setIntegerForKey("gg_zuanshi",0);
        UserDefault::getInstance()->setIntegerForKey("gg_huafeiquan",0);
        UserDefault::getInstance()->setIntegerForKey("gg_lingqu",0);
        
        UserDefault::getInstance()->setIntegerForKey("huafei_kind",0);
        
        
        UserDefault::getInstance()->setIntegerForKey("jijin_60_time",0);
        UserDefault::getInstance()->setIntegerForKey("jijin_90_time",0);
        UserDefault::getInstance()->setIntegerForKey("jijin_60_days",0);
        UserDefault::getInstance()->setIntegerForKey("jijin_90_days",0);
        
        UserDefault::getInstance()->setIntegerForKey("yiyuangoumai",0);
        UserDefault::getInstance()->setIntegerForKey("ishadmatch",0);
        
        
        //UserDefault::getInstance()->setStringForKey("DeviceNo","49857623123459");
        
        UserDefault::getInstance()->setIntegerForKey("boss_later_time",0);
        UserDefault::getInstance()->setIntegerForKey("cur_boss_num",0);//ÃÙ’Ω Ω‚À¯µƒboss
        UserDefault::getInstance()->setBoolForKey("is_boss_suc",false);// «∑ÒÃÙ’Ω≥…π¶
        UserDefault::getInstance()->setIntegerForKey("boss_day_times",0);//ÃÙ’Ω ß∞‹µƒ¥Œ ˝
        UserDefault::getInstance()->setIntegerForKey("boss_get_money",0);
        UserDefault::getInstance()->setIntegerForKey("boss_get_zuanshi",0);
        UserDefault::getInstance()->setIntegerForKey("boss_get_jiangbei",0);
        
        
        UserDefault::getInstance()->setIntegerForKey("vip_login_time",0);
        UserDefault::getInstance()->setIntegerForKey("Vip_loginDays",0);
        UserDefault::getInstance()->setIntegerForKey("player_vip",0);
        UserDefault::getInstance()->setIntegerForKey("player_vip_time",0);
        
        UserDefault::getInstance()->setIntegerForKey("bisaimoshi",0);
        UserDefault::getInstance()->setIntegerForKey("BS_moshi",1);
        UserDefault::getInstance()->setIntegerForKey("xuanzetouxiang",0);
        UserDefault::getInstance()->setIntegerForKey("player_touxiang",tx);
        UserDefault::getInstance()->setStringForKey("player_name",GAME_DATA_STRING("player_name"));
        UserDefault::getInstance()->setBoolForKey("IsBiSanUse",false);
        
        UserDefault::getInstance()->setDoubleForKey("preTime",0);
        UserDefault::getInstance()->setIntegerForKey("ZaiXianMin",0);
        UserDefault::getInstance()->setIntegerForKey("ZaiXianMiao",0);
        UserDefault::getInstance()->setIntegerForKey("ZaiXianTime",0);  
        
        UserDefault::getInstance()->setFloatForKey("hallDistance",0);
        UserDefault::getInstance()->setBoolForKey("firstdingping",false);
        UserDefault::getInstance()->setBoolForKey("firstjiasu",false);
        UserDefault::getInstance()->setBoolForKey("firstfanwei",false);
        UserDefault::getInstance()->setBoolForKey("firstjiguang",false);
        UserDefault::getInstance()->setBoolForKey("LoginDays",false);
        
        UserDefault::getInstance()->setIntegerForKey("missionNum",0);
        UserDefault::getInstance()->setIntegerForKey("missionKind",0);
        UserDefault::getInstance()->setIntegerForKey("fishKind",0);
        UserDefault::getInstance()->setIntegerForKey("prevTime",0);
        UserDefault::getInstance()->setIntegerForKey("firstdenglu",10);
        UserDefault::getInstance()->setIntegerForKey("LoginDays",0);
        UserDefault::getInstance()->setBoolForKey("firstJihuo",true);
        UserDefault::getInstance()->setBoolForKey("bXinShou",true);
        UserDefault::getInstance()->setIntegerForKey("unlockRoomNum",7);
        UserDefault::getInstance()->setIntegerForKey("laserLevel",1);
        UserDefault::getInstance()->setIntegerForKey("scopeLevel",1);
        
        
        
        UserDefault::getInstance()->setBoolForKey("Room4Has",false);
        UserDefault::getInstance()->setBoolForKey("Room5Has",false);
        UserDefault::getInstance()->setBoolForKey("Room6Has",false);
        UserDefault::getInstance()->setBoolForKey("Room7Has",false);
        UserDefault::getInstance()->setBoolForKey("Room8Has",false);
        UserDefault::getInstance()->setBoolForKey("Room9Has",false);
        UserDefault::getInstance()->setBoolForKey("Room10Has",false);
        UserDefault::getInstance()->setBoolForKey("Room11Has",false);
        UserDefault::getInstance()->setBoolForKey("Room12Has",false);
        UserDefault::getInstance()->setBoolForKey("Room66Has",false);
        
        UserDefault::getInstance()->setBoolForKey("leijichongzhi0",false);
        
        UserDefault::getInstance()->setBoolForKey("sc20_shouchong.png",false);
        UserDefault::getInstance()->setBoolForKey("sc10_shouchong.png",false);
        UserDefault::getInstance()->setBoolForKey("sc6_shouchong.png",false);
        UserDefault::getInstance()->setIntegerForKey("tiaozhanBoss",0);
        UserDefault::getInstance()->flush();
        
        FishLayer :: bFirstBaoXiang = false;
        GameBegin::setFileData("jywer.txt",1000);
        GameBegin::setFileData("gamePlayerlv.txt",1);
        GameBegin::setFileData("gameExp.txt",0);
        GameBegin::setFileData("jywopl.txt",0);
        GameBegin::setFileData("typeJiGuang.txt",1);
        GameBegin::setFileData("typeFanWei.txt",1);
        GameBegin::setFileData("gameMaxPao.txt",1);
        GameBegin::setFileData("wflei.txt",0);
        GameBegin::setFileData("wfsound.txt",0);
        
        //GameBegin::setFileData("hb_last_time.txt",0);
        //GameBegin::setFileData("hb_times.txt",0);
        GameBegin::setFileData("hb_last_lq_time.txt",0);
 
    }
    else if(UserDefault::getInstance()->getIntegerForKey("firstdenglu") < 10)
    {
        
        UserDefault::getInstance()->setIntegerForKey("gameMoney_hd",GameBegin::getFileData("jywer.txt"));
        UserDefault::getInstance()->setIntegerForKey("gameZuanshi_hd",GameBegin::getFileData("jywopl.txt"));
        
        GameBegin::setFileData("jywer.txt",getFileData("gameMoney.txt"));
        GameBegin::setFileData("jywopl.txt",getFileData("gameZuanshi.txt"));
        UserDefault::getInstance()->setIntegerForKey("huafei_kind",0);
        UserDefault::getInstance()->setIntegerForKey("ishadmatch",1);
        
        UserDefault::getInstance()->setIntegerForKey("vip_login_time",0);
        UserDefault::getInstance()->setIntegerForKey("Vip_loginDays",0);
        UserDefault::getInstance()->setIntegerForKey("bisaimoshi",0);
        UserDefault::getInstance()->setIntegerForKey("BS_moshi",1);
        UserDefault::getInstance()->setIntegerForKey("xuanzetouxiang",1);
        UserDefault::getInstance()->setBoolForKey("IsBiSanUse",false);
        
        UserDefault::getInstance()->setDoubleForKey("preTime",0);
        UserDefault::getInstance()->setIntegerForKey("ZaiXianMin",0);
        UserDefault::getInstance()->setIntegerForKey("ZaiXianMiao",0);
        UserDefault::getInstance()->setIntegerForKey("ZaiXianTime",0);
        
        GameBegin::setFileData("wflei.txt",UserDefault::getInstance()->getIntegerForKey("leijichongzhibisai"));
        
        UserDefault::getInstance()->setIntegerForKey("firstdenglu",10);
        UserDefault::getInstance()->setIntegerForKey("boss_later_time",0);
        UserDefault::getInstance()->setIntegerForKey("cur_boss_num",0);//ÃÙ’Ω Ω‚À¯µƒboss
        UserDefault::getInstance()->setBoolForKey("is_boss_suc",false);// «∑ÒÃÙ’Ω≥…π¶
        UserDefault::getInstance()->setIntegerForKey("boss_day_times",0);//ÃÙ’Ω ß∞‹µƒ¥Œ ˝
        UserDefault::getInstance()->setIntegerForKey("boss_get_money",0);
        UserDefault::getInstance()->setIntegerForKey("boss_get_zuanshi",0);
        UserDefault::getInstance()->setIntegerForKey("boss_get_jiangbei",0);
        
        GameBegin::setFileData("hb_last_lq_time.txt",0);
        
        UserDefault::getInstance()->flush();
    }
    
    
    
    srand((unsigned)time(NULL));
    GameBegin::stopMusic();
    playMusic("bgmusic.mp3",1);
    baiyun1Zeng = false;
    baiyun2Zeng = true;
    
    
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
    
    ////雅黑
    //auto hall_heise_s9p = Scale9Sprite::create("hall_yahei.png");
    //hall_heise_s9p->setCapInsets( CCRectMake(3, 3, 3, 327) );
    //hall_heise_s9p->setContentSize( CCSizeMake(1024,333) );
    //hallBackground->addChild(hall_heise_s9p,20);
    //
    //hall_heise_s9p->runAction(RepeatForever::create(Sequence::create(FadeTo::create(2.0f,0),FadeTo::create(2.0f,255),nullptr)));
    //
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
    
    
    //中间logo
    GB_logo = Sprite::create("logo.png");
    GB_logo->setPosition(Vec2(visibleSize.width/2 + origin.x,visibleSize.height * 0.62 + origin.y));
    GB_logo->setRotation(-180);
    GB_logo->setScale(0.01);
    GB_logo->setOpacity(0);
    addChild(GB_logo,ANNIULAYER);
    
    auto logo_fade = FadeIn::create(0.8f);
    auto logo_Rotate = RotateBy::create(0.5f,180);
    auto logo_Scale = ScaleTo::create(0.5f,0.65);
    GB_logo->runAction(Spawn::create(logo_fade,logo_Rotate,logo_Scale,nullptr));
    
    
    //ø™ º∞¥≈•
    GB_kaishi = Sprite::createWithSpriteFrameName("game_begin_dj.png");
    GB_kaishi->setScale(0.85);
    auto kaishiMenuItem = MenuItemSprite::create(GB_kaishi,GB_kaishi,CC_CALLBACK_1( GameBegin::menuGo,this));
    kaishiMenuItem->setTag(0);
    
    GB_kaishid = Sprite::createWithSpriteFrameName("game_begin_bs.png");
    GB_kaishid->setScale(0.85);
    auto kaishiMenuItem1 = MenuItemSprite::create(GB_kaishid,GB_kaishid,CC_CALLBACK_1( GameBegin::menuGo,this));
    kaishiMenuItem1->setTag(1);
    
    kaishiMenu = Menu::create(kaishiMenuItem,kaishiMenuItem1,nullptr);
    kaishiMenu->alignItemsHorizontallyWithPadding(100);
    kaishiMenu->setPosition(Vec2(visibleSize.width/2 + 4 + origin.x,visibleSize.height * 0 + origin.y));
    addChild(kaishiMenu,ANNIULAYER);
    
    auto item_move = MoveTo::create(1.0f,Vec2(visibleSize.width/2 +  4 + origin.x,visibleSize.height * 0.2 + origin.y));
    kaishiMenu->runAction(item_move);
    
    auto tixingzi = LabelTTF::create(GAME_DATA_STRING("game_version"),GameHallLayer::wordKind,20);
    tixingzi->setAnchorPoint(Vec2(0,0));
    tixingzi->setPosition(Vec2(10, 10));
    addChild(tixingzi);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameBegin::onTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(GameBegin::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(GameBegin::onTouchEnded,this);
    dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    EventListenerKeyboard* kblsnr = EventListenerKeyboard::create();
    kblsnr->onKeyReleased = CC_CALLBACK_2(GameBegin::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(kblsnr, this);
    
    
    //baidu_qiehuan();
  /*  if(LogoLayer::dengluFlag)
    {
        auto layer = GameLogin::createScene();
        this->addChild(layer,MENULAYER + 1,888);
    }*/
    //pinglun daima
    int delucishu = UserDefault::getInstance()->getIntegerForKey("denglucishu");
    if(delucishu >= 0)
    {
        UserDefault::getInstance()->setIntegerForKey("denglucishu",delucishu + 1);
    }
    
    
    if(delucishu > 2 && !LogoLayer::dengluFlag)
    {
        auto gongxi =Gongxi::create(99,GAME_DATA_STRING("denglucishu"));
        gongxi->setPosition(Point::ZERO);
        this->addChild(gongxi,1000,1003);
        
        auto quedingSprite =  Sprite::createWithSpriteFrameName("XR_qd.png");
        auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(GameBegin::pinglun,this));
        auto btnMenu = Menu::create(quedingItem,nullptr);
        btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
        gongxi->getChildByTag(1)->addChild(btnMenu,100);
        
        auto tuichuSprite =  Sprite::createWithSpriteFrameName("hall_menu_X.png");
        auto xquedingItem = MenuItemSprite::create(tuichuSprite,tuichuSprite,tuichuSprite,CC_CALLBACK_0(GameBegin::fanhuiGame,this));
        auto xbtnMenu = Menu::create(xquedingItem,nullptr);
        xbtnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2 + 200,0.95*gongxi->getChildByTag(1)->getContentSize().height));
        gongxi->getChildByTag(1)->addChild(xbtnMenu,100);
        
    }
    
    
    
    //string tmpLoing = UserDefault::getInstance()->getStringForKey("login_phone_num");
    //帐号登录
  /*  if((UserDefault::getInstance()->getStringForKey("login_phone_num") == "")&& !LogoLayer::dengluFlag)
    {
        auto login_icon = Sprite::createWithSpriteFrameName("zh_denglu_icon.png");
        
          login_icon->setScale(0.7f);
        auto login_item = MenuItemSprite::create(login_icon,login_icon,CC_CALLBACK_0(GameBegin::login_system,this));
        auto login_menu = Menu::create(login_item,nullptr);
        login_menu->setPosition(Vec2(visibleSize.width - 110,visibleSize.height - 60));
      
        addChild(login_menu,ANNIULAYER);
    }*/
    
    
}
//*********** 登录系统 *********************
void GameBegin::cal_lastTime()
{
    int start_time = UserDefault::getInstance()->getIntegerForKey("start_login_time");//start_login_time
    int last_time = UserDefault::getInstance()->getIntegerForKey("last_game_time");
    time_t cur_time;
    time(&cur_time);
    
    if(cur_time > start_time)
    {
        last_time += cur_time - start_time;
        UserDefault::getInstance()->setIntegerForKey("last_game_time",last_time);
        UserDefault::getInstance()->flush();
    }
}


void GameBegin::login_system()
{
    auto zheZhao = LayerColor::create(ccc4(0,0,0,150),1024,768);
    zheZhao->setPosition(Point::ZERO);
    zheZhao->setScale(2.0f);
    this->addChild(zheZhao,MENULAYER,121);
    
    //背景
    auto login_bg = cocos2d::ui::Scale9Sprite::createWithSpriteFrameName( "bs_kuang.png",CCRectMake(99,99,20,20));
    login_bg->setContentSize(CCSizeMake(550,300));
    login_bg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    
    this->addChild(login_bg,MENULAYER,123);
    
    login_bg->setScale(0.1f);
    ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);
    ScaleTo *ac8=ScaleTo::create(0.1f, 1.0);
    login_bg->runAction(Sequence::create(ac7,ac8,nullptr));
    
    //手机号 label
    auto login_sj_label = Sprite::createWithSpriteFrameName("zh_sj_label.png");
    login_sj_label->setPosition(Vec2(100,190));
    login_bg->addChild(login_sj_label,100);
    
    //名称编辑框
    auto login_phone_edit = cocos2d::ui::EditBox::create(Size(315,35),cocos2d::ui::Scale9Sprite::createWithSpriteFrameName("kuang_3.png"),cocos2d::ui::Scale9Sprite::createWithSpriteFrameName("kuang_3.png"),nullptr);
    login_phone_edit->setAnchorPoint(Vec2(0.5,0.5));
    login_phone_edit->setPosition(Vec2(350,227));
    login_phone_edit->setFont("minijianling.ttf", 24);
    login_phone_edit->setFontColor(Color3B::WHITE);
    login_phone_edit->setPlaceHolder("请输入绑定的电话号码");
    login_phone_edit->setPlaceholderFontColor(Color3B::WHITE);
    login_phone_edit->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
    login_phone_edit->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
    login_phone_edit->setDelegate(this);
    login_bg->addChild(login_phone_edit,100,1);
    
    //密码编辑框
    auto login_pwd_edit = cocos2d::ui::EditBox::create(Size(315,35),cocos2d::ui::Scale9Sprite::createWithSpriteFrameName("kuang_3.png"),cocos2d::ui::Scale9Sprite::createWithSpriteFrameName("kuang_3.png"),nullptr);
    login_pwd_edit->setAnchorPoint(Vec2(0.5,0.5));
    login_pwd_edit->setPosition(Vec2(350,155));
    login_pwd_edit->setFont("minijianling.ttf", 24);
    login_pwd_edit->setFontColor(Color3B::WHITE);
    login_pwd_edit->setPlaceHolder("test");
    login_pwd_edit->setPlaceholderFontColor(Color3B::WHITE);
    login_pwd_edit->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
    login_pwd_edit->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
    login_pwd_edit->setDelegate(this);
    login_bg->addChild(login_pwd_edit,100,2);
    
   /* auto login_login_sp = Sprite::createWithSpriteFrameName("zh_denglu.png");
    auto login_cancel_sp = Sprite::createWithSpriteFrameName("zh_quxiao.png");
    auto login_login_item = MenuItemSprite::create(login_login_sp,login_login_sp,CC_CALLBACK_0(GameBegin::login_login,this));
    auto login_cancel_item = MenuItemSprite::create(login_cancel_sp,login_cancel_sp,CC_CALLBACK_0(GameBegin::login_cancel,this));
    auto login_menu = Menu::create(login_login_item,login_cancel_item,nullptr);
    login_menu->alignItemsHorizontallyWithPadding(130);
    login_menu->setPosition(Vec2(275,50));
    login_bg->addChild(login_menu,100);*/
}

bool GameBegin::isPhoneNum(const std::string& strIp)
{
    
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
}


void GameBegin::editBoxReturn(cocos2d::ui::EditBox *editBox)
{
    log("editBox %p was returned.", editBox->getText());
}

void GameBegin::login_cancel()
{
    buttonSound();
    this->removeChildByTag(121);
    
    ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);
    ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);
    
    this->getChildByTag(123)->runAction(Sequence::create(ac7,ac8,RemoveSelf::create(),nullptr));
    
}


void GameBegin::get_deviceNo(float dt)
{
     log("get_deviceNo");
    CURL *curl;
    CURLcode res;
    std::string cc;
    curl=curl_easy_init();
    char postFields[600];
    
    if(curl)
    {
        curl_easy_setopt( curl, CURLOPT_URL, "http://dwby-hk.iyueyo.com/qpby2/iosfanti/login/deviceno.php");
        curl_easy_setopt(curl,CURLOPT_TIMEOUT,3000);
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&deviceNo_poss);
        res=curl_easy_perform(curl);
        if(res!=CURLE_OK)
        {
            get_devi_fail();
        }
        curl_easy_cleanup(curl);
    }
    else
    {
        //log("curl fail");
        get_devi_fail();
        return ;
    }
}
void GameBegin::get_Test(float dt)
{
	log("get_deviceNo");
	CURL *curl;
	CURLcode res;
	std::string cc;
	curl = curl_easy_init();
	char postFields[600];

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/index.php");
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3000);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &deviceNo_poss);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			get_devi_fail();
		}
		curl_easy_cleanup(curl);
	}
	else
	{
		//log("curl fail");
		get_devi_fail();
		return;
	}
}
size_t GameBegin::deviceNo_poss(uint8_t *buffer,size_t size,size_t nmemb,void *stream)
{
    cocos2d::log("补单返回数据： %s ", (const char *)buffer);
    
    string tmpstring = (const char *)buffer;
    int temp_length = tmpstring.length();
    if(temp_length == 32)
    {
        UserDefault::getInstance()->setStringForKey("DeviceNo",tmpstring);
        UserDefault::getInstance()->flush();
        
        cGetDev = 1;
    }else
    {
        cGetDev = 2;
    }
    
    size_t sizes = size*nmemb;
    return sizes;
}

void GameBegin::get_devi_fail()
{
    auto gongxi = Gongxi::create(7,GAME_DATA_STRING("dev_fail"));
    gongxi->setPosition(Point::ZERO);
    this->addChild(gongxi,MENULAYER,978);
    
    auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png" );
    auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(GameBegin::reget_deviceNo,this));
    auto btnMenu = Menu::create(quedingItem,nullptr);
    btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
    gongxi->getChildByTag(1)->addChild(btnMenu,100);
}

void GameBegin::get_devi_succ()
{
    this->removeChildByTag(977);
}

void GameBegin::reget_deviceNo()
{
      exit(0);
}

//*********** end *******************************


void GameBegin::pinglun()
{
   this->removeChildByTag(1003);
    Application::getInstance()->openURL("https://play.google.com/store/apps/details?id=com.deedeefun.fishingwar");
    GameBegin::setFileData("jywer.txt",GameBegin::getFileData("jywer.txt") + 2000);
    UserDefault::getInstance()->setIntegerForKey("denglucishu",-1);
    
    GameBegin::baidu_qiehuan();
}
void GameBegin::fanhuiGame()
{
    this->removeChildByTag(1003);
}
void GameBegin::baidu_denglu(int i)
{
	if(!LogoLayer::dengluFlag)
	{
        if(getFileData("jywer.txt") <= 0)
        {
            setFileData("jywer.txt", UserDefault::getInstance()->getIntegerForKey("gameMoney_hd"));
            setFileData("jywopl.txt", UserDefault::getInstance()->getIntegerForKey("gameZuanshi_hd"));
        }
		return;
	}

	 
    
}

size_t  GameBegin::possText(uint8_t *buffer,size_t size,size_t nmemb,void *stream)
{
	cocos2d::log("buffer =  %s ", (const char *)buffer);		
 
	string userid =  strtok((char *)buffer,"-");
	string gamemoney = strtok(NULL,"-");
	string gamezuanshi = strtok(NULL,"-");
	string isVip = strtok(NULL,"-");
	string gamename = strtok(NULL,"-");
	string gameicon = strtok(NULL,"-");
	string unlockRoomNum = strtok(NULL,"-");
	string gameplayerlv = strtok(NULL,"-");
	string gameExp = strtok(NULL,"-");
	string gameMaxPao = strtok(NULL,"-");

	string vip_login_time = strtok(NULL,"-");
	string Vip_loginDays = strtok(NULL,"-");
	string player_vip_time = strtok(NULL,"-");
	string prevTime = strtok(NULL,"-");
	string LoginDays = strtok(NULL,"-");
	string typeJiGuang = strtok(NULL,"-");
	string typeFanWei = strtok(NULL,"-");
	string hb_last_time = strtok(NULL,"-");
	string hb_times = strtok(NULL,"-");
 
	cocos2d::log("moreGameFlag = %d",LogoLayer::moreGameFlag);

	cocos2d::log("userid = %s , gamemoney = %s ,  gamezuanshi = %s , isVip = %s , gamename = %s , gameicon = %s , unlockRoomNum = %s , gameplayerlv = %s , gameExp = %s ,gameMaxPao = %s  "
		"vip_login_time = %s , Vip_loginDays = %s ,  player_vip_time = %s , prevTime = %s , LoginDays = %s , typeJiGuang = %s , typeFanWei = %s , hb_last_time = %s , hb_times = %s  "
		,userid.c_str(),gamemoney.c_str(),gamezuanshi.c_str(),isVip.c_str(),gamename.c_str(),gameicon.c_str(),unlockRoomNum.c_str(),gameplayerlv.c_str(),gameExp.c_str(),gameMaxPao.c_str()
		,vip_login_time.c_str(),Vip_loginDays.c_str(),player_vip_time.c_str(),prevTime.c_str(),LoginDays.c_str(),typeJiGuang.c_str(),typeFanWei.c_str(),hb_last_time.c_str(),hb_times.c_str());

	GameBegin::setFileData("jywer.txt",atoi(gamemoney.c_str()));
	cocos2d::log("gameMoney");		

	GameBegin::setFileData("jywopl.txt",atoi(gamezuanshi.c_str()));
	cocos2d::log("gameZuanshi");	

	GameBegin::setFileData("gamePlayerlv.txt",atoi(gameplayerlv.c_str()));
	cocos2d::log("gamePlayerlv");	

	GameBegin::setFileData("gameExp.txt",atoi(gameExp.c_str()));
	cocos2d::log("gameExp");	

	GameBegin::setFileData("gameMaxPao.txt",atoi(gameMaxPao.c_str()));
	cocos2d::log("gameMaxPao");	

	GameBegin::setFileData("typeJiGuang.txt",atoi(typeJiGuang.c_str()));            
	GameBegin::setFileData("typeFanWei.txt",atoi(typeFanWei.c_str()));

	GameBegin::setFileData("hb_last_time.txt",atoi(hb_last_time.c_str()));
	GameBegin::setFileData("hb_last_lq_time.txt",atoi(hb_times.c_str()));

	UserDefault::getInstance()->setIntegerForKey("vip_login_time",atoi(vip_login_time.c_str()));
	UserDefault::getInstance()->setIntegerForKey("Vip_loginDays",atoi(Vip_loginDays.c_str()));
	UserDefault::getInstance()->setIntegerForKey("player_vip_time",atoi(player_vip_time.c_str()));

	UserDefault::getInstance()->setIntegerForKey("prevTime",atoi(prevTime.c_str()));		
	UserDefault::getInstance()->setIntegerForKey("LoginDays",atoi(LoginDays.c_str()));
	cocos2d::log("LoginDays = %d ",atoi(LoginDays.c_str()));	

	UserDefault::getInstance()->setStringForKey("userid",userid);
	UserDefault::getInstance()->setIntegerForKey("player_vip",atoi(isVip.c_str()));
	UserDefault::getInstance()->setIntegerForKey("player_touxiang",atoi(gameicon.c_str()));
	UserDefault::getInstance()->setStringForKey("player_name",gamename);
	UserDefault::getInstance()->setIntegerForKey("unlockRoomNum",atoi(unlockRoomNum.c_str()));
	UserDefault::getInstance()->flush();
    
    cocos2d::log("gameicon = %d ",atoi(gameicon.c_str()));
 
	cocos2d::log("tmpBegin  2");	
	  
	size_t sizes = size*nmemb;
	return sizes;
}

void GameBegin::baidu_qiehuan()
{
	if(!LogoLayer::dengluFlag )
	{
        UserDefault::getInstance()->setIntegerForKey("gameMoney_hd",getFileData("jywer.txt"));
        UserDefault::getInstance()->setIntegerForKey("gameZuanshi_hd",getFileData("jywopl.txt"));
        UserDefault::getInstance()->flush();
		return;
	}

}

void GameBegin::randomFish()
{
    //随机鱼的种类1-6
    int fish_kind = (int)(CCRANDOM_0_1() * 100000) % 3 + 1;
    char hallCharTemp[100];
    
    //fish_kind = 8;
    if(fish_kind ==3)//水母
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
            fish_sp->runAction(Sequence::create(MoveBy::create(speed ,moveWitd ),RemoveSelf::create(),nullptr));
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
        
        if(CCRANDOM_0_1() > 0.9)
        {
            high = CCRANDOM_0_1() * 199.99 + 100;
        }else
        {
            high = CCRANDOM_0_1() * 150 + 320;
        }
        
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
            scale = 1;
        }
        float spped = scale * 10 * speed_xi;
        
        sprintf(hallCharTemp,"hall_fish_%d (1).png",fish_kind);
        auto fish_sp = Sprite::createWithSpriteFrameName(hallCharTemp);
        fish_sp->setPosition(Vec2(width,high));
        fish_sp->setScale(scale);
        hallBackground->addChild(fish_sp,8);
        
        fish_sp->setOpacity(255 * scale);
        //fish_sp->setColor(Color3B(255*scale,255*scale,255*scale));
        if(scale != 1)
        {
            fish_sp->setZOrder(7);
        }
        if(!fangxiang)
        {
            fish_sp->setFlippedX(true);
        }
        
        sprintf(hallCharTemp,"hall_fish_animate_%d",fish_kind);
        fish_sp->runAction(RepeatForever::create( Animate::create(AnimationCache::getInstance()->getAnimation(hallCharTemp))));
        fish_sp->runAction(Sequence::create(MoveBy::create(200.0f/spped,moveWitd),RemoveSelf::create(),nullptr));
    }
    
    
}

size_t  GameBegin::possText1(uint8_t *buffer,size_t size,size_t nmemb,void *stream)
{
	cocos2d::log("≤πµ•∑µªÿ ˝æ›22222222222222222£∫ %s ", (const char *)buffer);
 
	size_t sizes = size*nmemb;
	return sizes;
}


bool GameBegin::inituserid(char * deviceNo,int i)
{
	cocos2d::log("success:phonedeviceNo is : %s",deviceNo);
 
	UserDefault::getInstance()->setStringForKey("userdata",deviceNo);
	UserDefault::getInstance()->flush();

	//baidu_denglu(1);

	return true;
}

void GameBegin::jieping(float dt)
{
 
    if(ifOldZhangHao == 0)
    {
        this->stopAllActions();
		this->removeAllChildrenWithCleanup(true);
		this->unscheduleAllSelectors();

		if(UserDefault::getInstance()->getIntegerForKey("xuanzetouxiang") == 0)
		{
			auto layer = InitPlayer::createScene();
			Director::getInstance()->replaceScene(layer);

			UserDefault::getInstance()->setIntegerForKey("xuanzetouxiang",1);
			UserDefault::getInstance()->flush();
		}else
		{
			auto scene = GameHallLayer::createScene();
			Director::getInstance()->replaceScene(scene);

		}
    }
    else
    {
        exit(0);
    }
	 
 
}

void GameBegin::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) 
{    
	switch(keyCode)     
	{     
		//º‡Ã˝∑µªÿº¸        
	case EventKeyboard::KeyCode::KEY_ESCAPE:     
		Director::getInstance()->end();           
		break;        
		//º‡Ã˝menuº¸   
	case EventKeyboard::KeyCode::KEY_MENU:   
		break;   
	}
}


void GameBegin::buttonSound()
{
	int iTemp = CCRANDOM_0_1()* 100;
	if(iTemp < 25)
	{
		iTemp = 1;
	}
	else if(iTemp < 50)
	{
		iTemp = 2;
	}
	else if(iTemp < 75)
	{
		iTemp = 3;
	}
	else 
	{
		iTemp = 4;
	}
	char cSoundBtn[20]; 
	sprintf(cSoundBtn,"button%d.mp3",iTemp);
	GameBegin::playSound(cSoundBtn);
}

//¥ÊŒƒº˛ ˝æ›
void GameBegin::setFileData(string tmpPath,int tmpIntData)
{
	FILE * tmpFile;
	string moneypath;
	char  tmpData[20];
	

    if(strstr( "wfsound.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "wfsound.txt";
        
    }
    else if(strstr( "wflei.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "wflei.txt";
        
    }
    else if(strstr( "jywer.txt",tmpPath.c_str()))
	{
		moneypath = FileUtils::getInstance()->getWritablePath() + "jywer.txt";
		
	}
    
    
    else if(strstr( "gameMoney.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "gameMoney.txt";
        
    }
    else if(strstr( "gameZuanshi.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "gameZuanshi.txt";
        
    }
     
	else if(strstr( "gameExp.txt",tmpPath.c_str()))
	{
		moneypath = FileUtils::getInstance()->getWritablePath() + "gameExp.txt";
	}
	else if(strstr( "jywopl.txt",tmpPath.c_str()))
	{
		moneypath = FileUtils::getInstance()->getWritablePath() + "jywopl.txt";
		
	}
	else if(strstr( "gamePlayerlv.txt",tmpPath.c_str()))
	{
		moneypath = FileUtils::getInstance()->getWritablePath() + "gamePlayerlv.txt";	
		
	}
	else if(strstr( "gameMaxPao.txt",tmpPath.c_str()))
	{
		moneypath = FileUtils::getInstance()->getWritablePath() + "gameMaxPao.txt";	
		
	}
	else if(strstr( "typeJiGuang.txt",tmpPath.c_str()))
	{
		moneypath = FileUtils::getInstance()->getWritablePath() + "typeJiGuang.txt";	
		
	}
	else if(strstr( "typeFanWei.txt",tmpPath.c_str()))
	{
		moneypath = FileUtils::getInstance()->getWritablePath() + "typeFanWei.txt";			
	}
	else if(strstr( "hb_last_time.txt",tmpPath.c_str()))
	{
		moneypath = FileUtils::getInstance()->getWritablePath() + "hb_last_time.txt";			
	}
	else if(strstr( "hb_last_lq_time.txt",tmpPath.c_str()))
	{
		moneypath = FileUtils::getInstance()->getWritablePath() + "hb_last_lq_time.txt";
	}
	else if(strstr( "hongbao.txt",tmpPath.c_str()))
	{
		moneypath = FileUtils::getInstance()->getWritablePath() + "hongbao.txt";			
	}
    else if(strstr( "opla.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "opla.txt";
    }
    else if(strstr( "opta.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "opta.txt";
    }
    else if(strstr( "oplb.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "oplb.txt";
    }
    else if(strstr( "optb.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "optb.txt";
    }
    else if(strstr( "oplc.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "oplc.txt";
    }
    else if(strstr( "optc.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "optc.txt";
    }
    else if(strstr( "opld.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "opld.txt";
    }
    else if(strstr( "optd.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "optd.txt";
    }
    else if(strstr( "ople.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "ople.txt";
    }
    else if(strstr( "opte.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "opte.txt";
    }
    
    
    
	sprintf(tmpData,"%d",tmpIntData);
    
    if(tmpIntData == 0)
    {
      //  tmpData[0]--;
    }
    
	int tmpi = 0;
	while(tmpData[tmpi])
	{
		tmpData[tmpi]= tmpData[tmpi] + 30;
		tmpi++;
	}

	//1.¥Úø™Œƒº˛¡˜
	tmpFile = fopen(moneypath.c_str(),"wb");

	//2.Ω¯–– ˝æ›–¥
	//rewind(tmpFile);
	fputs(tmpData,tmpFile);

	//3.πÿ±’Œƒº˛¡˜
	fclose(tmpFile);
}

//∂¡Œƒº˛ ˝æ›
int GameBegin::getFileData(string tmpPath)
{
	FILE * tmpFile;
	int result = 0 ;
	string moneypath = FileUtils::getInstance()->getWritablePath() + tmpPath.c_str();

	//1.¥Úø™Œƒº˛¡˜
    if(strstr( "wflei.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "wflei.txt";
    }
    else if(strstr( "wfsound.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "wfsound.txt";
        
    }
	else if(strstr( "jywer.txt",tmpPath.c_str()))
	{
		moneypath = FileUtils::getInstance()->getWritablePath() + "jywer.txt";	
	}
    
    
    else if(strstr( "gameMoney.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "gameMoney.txt";
        
    }
    else if(strstr( "gameZuanshi.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "gameZuanshi.txt";
        
    }
    
	else if(strstr( "gameExp.txt",tmpPath.c_str()))
	{
		moneypath = FileUtils::getInstance()->getWritablePath() + "gameExp.txt";
	}
	else if(strstr( "jywopl.txt",tmpPath.c_str()))
	{
		moneypath = FileUtils::getInstance()->getWritablePath() + "jywopl.txt";
	}
	else if(strstr( "gamePlayerlv.txt",tmpPath.c_str()))
	{
		moneypath = FileUtils::getInstance()->getWritablePath() + "gamePlayerlv.txt";
	}
	else if(strstr( "gameMaxPao.txt",tmpPath.c_str()))
	{
		moneypath = FileUtils::getInstance()->getWritablePath() + "gameMaxPao.txt";	
	}
	else if(strstr( "typeJiGuang.txt",tmpPath.c_str()))
	{
		moneypath = FileUtils::getInstance()->getWritablePath() + "typeJiGuang.txt";	
		
	}
	else if(strstr( "typeFanWei.txt",tmpPath.c_str()))
	{
		moneypath = FileUtils::getInstance()->getWritablePath() + "typeFanWei.txt";	
		
	}
	else if(strstr( "hb_last_time.txt",tmpPath.c_str()))
	{
		moneypath = FileUtils::getInstance()->getWritablePath() + "hb_last_time.txt";			
	}
	else if(strstr( "hb_last_lq_time.txt",tmpPath.c_str()))
	{
		moneypath = FileUtils::getInstance()->getWritablePath() + "hb_last_lq_time.txt";			
	}
	else if(strstr( "hongbao.txt",tmpPath.c_str()))
	{
		moneypath = FileUtils::getInstance()->getWritablePath() + "hongbao.txt";			
	}
    else if(strstr( "hongbao.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "hongbao.txt";
    }
    else if(strstr( "opla.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "opla.txt";
    }
    else if(strstr( "opta.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "opta.txt";
    }
    else if(strstr( "oplb.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "oplb.txt";
    }
    else if(strstr( "optb.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "optb.txt";
    }
    else if(strstr( "oplc.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "oplc.txt";
    }
    else if(strstr( "optc.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "optc.txt";
    }
    else if(strstr( "opld.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "opld.txt";
    }
    else if(strstr( "optd.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "optd.txt";
    }
    else if(strstr( "ople.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "ople.txt";
    }
    else if(strstr( "opte.txt",tmpPath.c_str()))
    {
        moneypath = FileUtils::getInstance()->getWritablePath() + "opte.txt";
    }
    

	tmpFile = fopen(moneypath.c_str(),"rb");
	 
	//2.Ω¯–– ˝æ›∂¡–¥
    if(tmpFile)
    {
        char  tmpData[20];
        fgets(tmpData,100,tmpFile);
        if(tmpData[0] == 'M')
        {
            result = -1;
        }else
        {
            int tmpi = 0;
            while(tmpData[tmpi])
            {
                //CCLOG("tmpE[%d] = %c" , tmpi , tmpData[tmpi]);
                tmpData[tmpi]= tmpData[tmpi] - 30;
                //CCLOG("tmpData[%d] + 30 = %c" , tmpi , tmpData[tmpi]);
                tmpi++;
            }
            result = atoi(tmpData);   
        }	
    }
	else
	{
		tmpFile = fopen(moneypath.c_str(),"wb");
		cocos2d::log("********333333333333************");
		string tmpData;
		tmpData = "0";
		result = 0;
		if(tmpPath == "jywer.txt")
		{
			tmpData = "200";
			result = 200;
		}
		if(tmpPath == "gamePlayerlv.txt")
		{
			tmpData = "1";
			result = 1;
		}
		fputs(tmpData.c_str(),tmpFile);
	} 
	//3.πÿ±’Œƒº˛¡˜
	fclose(tmpFile);

	return result;
}

int GameBegin::playSound(string soundPath)
{
	int tmp = 0;
	if(canPlaySound)
	{
		tmp = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundPath.c_str());
	}
	return tmp;
}

void GameBegin::playMusic(string soundPath,char cType)
{
    
    if(canPlayMusic )
    {
        musicNum = cType;
        if( cType == 0)
        {
            int BgRandom =   CCRANDOM_0_1()*100;
            if(BgRandom < 50)
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bosscome.mp3",true);
            }
            else
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bosscome2.mp3",true);
            }
            
        }
        else if(cType == 1)
        {
            int BgRandom =   CCRANDOM_0_1()*100;
            if(BgRandom< 50)
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgmusic6.mp3",true);
            }
            else
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgmusic8.mp3",true);
            }
        }
        else if(cType == 2)
        {
            
            int BgRandom =   CCRANDOM_0_1()*70;
            if(BgRandom < 10)
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgmusic1.mp3",true);
            }
            else if(BgRandom < 20)
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgmusic2.mp3",true);
            }
            else if(BgRandom < 30)
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgmusic3.mp3",true);
            }
            else if(BgRandom < 40)
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgmusic5.mp3",true);
            }
            else if(BgRandom < 50)
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgmusic10.mp3",true);
            }
            else if(BgRandom < 60)
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgmusic11.mp3",true);
            }
            else if(BgRandom < 70)
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgmusic8.mp3",true);
            }
            
        }
        else if( cType == 4)
        {
            
            int BgRandom =   CCRANDOM_0_1()*100;
            if(BgRandom < 33)
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Match_baoming.mp3",true);
            }
            else if(BgRandom< 66)
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("yuanzhengbgm.mp3",true);
            }
            else 
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgmusic8.mp3",true);
            }
            
            
        } 
        else if( cType == 5)
        { 
            CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Match_loading.mp3",false);
        }
        else if(cType == 6)
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("matchtimeover.mp3",true);
        }
        else if(cType == 7)
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("yuanzhengbgm.mp3",true);
        }
    }
    
}
 
void GameBegin::stopMusic()
{
	 
	 CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	 
}

void GameBegin::update(float dt)
{
   
 
    if(cGetDev == 1)
    {
       
        this->removeChildByTag(977);
        if(UserDefault::getInstance()->getIntegerForKey("firstdenglu")  <9  && UserDefault::getInstance()->getIntegerForKey("firstdenglu") != 0)
        {
             cGetDev = 8;
        }
        else
        {
             cGetDev = 0;
             GameBiginInit();
        }
       

    }
    else if(cGetDev == 2)
    {
        cGetDev = 0;
        auto gongxi = Gongxi::create(7,GAME_DATA_STRING("dev_fail"));
        gongxi->setPosition(Point::ZERO);
        this->addChild(gongxi,MENULAYER,978);
        
        auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png" );
        auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(GameBegin::reget_deviceNo,this));
        auto btnMenu = Menu::create(quedingItem,nullptr);
        btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
        gongxi->getChildByTag(1)->addChild(btnMenu,100);
       
        this->unscheduleAllSelectors();
         return;
    }
    else if(cGetDev == 3)
    {
        cGetDev = 0;
        GameBiginInit();
    }
    if(cGetDev != 0)
    {
        return;
    }
    if(login_success)
    {
        this->removeChildByTag(124);
        
        auto phone_edit = (cocos2d::ui::EditBox *)(this->getChildByTag(123)->getChildByTag(1));
        string phone_s = phone_edit->getText();
        UserDefault::getInstance()->setStringForKey("login_phone_num" , phone_s);
        UserDefault::getInstance()->flush();
        login_success = false;
        fangjian = 0;
        dengluCheng = true;
    }
    
    if(login_fail)
    {
        this->removeChildByTag(124);
        login_fail = false;
        //开始down数据 down完之后 进入场景
        //TO DO
        char tmpbegin[50];
        sprintf(tmpbegin,"login_wrong%d",login_fail_flag);
        auto gongxi = Gongxi::create(2,GAME_DATA_STRING(tmpbegin));
        this->addChild(gongxi,MENULAYER);
    }
    
    yutime += dt;
    if(yutime > 2)
    {
        yutime = 0;
        randomFish();
    }
    
    
    if(dengluCheng)
    {
        
        wait_time ++;
        if(wait_time == 1)
        {
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common/commons2.plist","common/commons2.png");
            
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameHall/gameHall2.plist","gameHall/gameHall2.png");
            
			
          
            
            
        }
        else if(wait_time == 5)
        {
            
            baidu_denglu(2);
             
        }
        else if(wait_time == 10)
        {
            
            if(ifOldZhangHao == 1)
            {
                
                auto tishi = Gongxi::create(2, GAME_DATA_STRING("login_wrongwf"));
                this->addChild(tishi,MENULAYER);
            }
            if(ifOldZhangHao == 2)
            {
                
                auto tishi = Gongxi::create(2, GAME_DATA_STRING("login_wrongwf2"));
                this->addChild(tishi,MENULAYER);
            }
            if(ifOldZhangHao == 3)
            {
                
                
                auto tishi = Gongxi::create(2, GAME_DATA_STRING("login_wrongwf3"));
                this->addChild(tishi,MENULAYER);
            }
            
            
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameHall/gameHall3.plist","gameHall/gameHall3.png");
        }else if(wait_time == 15)
        {
            
            Vector<SpriteFrame*> sp_vec;
            //跑马灯动画
            if(AnimationCache::getInstance()->getAnimation("hb_paomadeng") == NULL)
            {
                sp_vec.clear();
                for(int j = 1;j < 3;j++)
                {
                    char cTempFishSprite[30];
                    sprintf(cTempFishSprite,"HB_paodeng%d.png" ,j);
                    SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                    sp_vec.pushBack(spriteFrame);
                }
                auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
                JiGuangFrameTwo->setDelayPerUnit(0.1f);
                AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "hb_paomadeng");
            }
        }
        else if(wait_time == 20)
        {
            Vector<SpriteFrame*> sp_vec;
            //水草动画
            if(AnimationCache::getInstance()->getAnimation("hall_shuichao") == NULL)
            {
                sp_vec.clear();
                for(int j = 1;j < 13;j++)
                {
                    char cTempFishSprite[30];
                    sprintf(cTempFishSprite,"hall_shuicao_%d.png" ,j);
                    SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                    sp_vec.pushBack(spriteFrame);
                }
                auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
                JiGuangFrameTwo->setDelayPerUnit(0.1f);
                AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "hall_shuichao");
            }
            //星星动画
            if(AnimationCache::getInstance()->getAnimation("hall_ssxx") == NULL)
            {
                sp_vec.clear();
                for(int j = 1;j < 6;j++)
                {
                    char cTempFishSprite[30];
                    sprintf(cTempFishSprite,"hall_ssxx_%d.png" ,j);
                    SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                    sp_vec.pushBack(spriteFrame);
                }
                auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
                JiGuangFrameTwo->setDelayPerUnit(0.25f);
                AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "hall_ssxx");
            }
            
            //设置解锁动画
            if(AnimationCache::getInstance()->getAnimation("hall_room_suo") == NULL)
            {
                sp_vec.clear();
                for(int j = 1;j < 9;j++)
                {
                    char cTempFishSprite[30];
                    sprintf(cTempFishSprite,"lock_dh_%d.png" ,j);
                    SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                    sp_vec.pushBack(spriteFrame);
                }
                auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
                JiGuangFrameTwo->setDelayPerUnit(0.1f);
                AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "hall_room_suo");
            }
            
            //设置技能旋转动画
            if(AnimationCache::getInstance()->getAnimation("hall_jineng") == NULL)
            {
                sp_vec.clear();
                for(int j = 1;j < 7;j++)
                {
                    char cTempFishSprite[30];
                    sprintf(cTempFishSprite,"hall_jineng%d.png" ,j);
                    SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                    sp_vec.pushBack(spriteFrame);
                }
                auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
                JiGuangFrameTwo->setDelayPerUnit(0.1f);
                AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "hall_jineng");
            }
            
            //设置商城旋转动画
            if(AnimationCache::getInstance()->getAnimation("hall_shangcheng") == NULL)
            {
                sp_vec.clear();
                for(int j = 1;j < 7;j++)
                {
                    char cTempFishSprite[30];
                    sprintf(cTempFishSprite,"hall_shangcheng%d.png" ,j);
                    SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                    sp_vec.pushBack(spriteFrame);
                }
                auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
                JiGuangFrameTwo->setDelayPerUnit(0.1f);
                AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "hall_shangcheng");
            }
            
            //设置解锁倍率旋转动画
            if(AnimationCache::getInstance()->getAnimation("hall_jiesuo") == NULL)
            {
                sp_vec.clear();
                for(int j = 1;j < 7;j++)
                {
                    char cTempFishSprite[30];
                    sprintf(cTempFishSprite,"hall_jiesuo%d.png" ,j);
                    SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                    sp_vec.pushBack(spriteFrame);
                }
                auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
                JiGuangFrameTwo->setDelayPerUnit(0.1f);
                AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "hall_jiesuo");
            }
            
            //设置挑战旋转动画
            if(AnimationCache::getInstance()->getAnimation("hall_tiaozhan") == NULL)
            {
                sp_vec.clear();
                for(int j = 1;j < 7;j++)
                {
                    char cTempFishSprite[30];
                    sprintf(cTempFishSprite,"hall_tiaozhan%d.png" ,j);
                    SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                    sp_vec.pushBack(spriteFrame);
                }
                auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
                JiGuangFrameTwo->setDelayPerUnit(0.1f);
                AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "hall_tiaozhan");
            }
            
            //比赛箭头动画
            if(AnimationCache::getInstance()->getAnimation("hall_bsjiantou") == NULL)
            {
                sp_vec.clear();
                for(int j = 1;j < 5;j++)
                {
                    char cTempFishSprite[30];
                    sprintf(cTempFishSprite,"bs_jt_%d.png" ,j);
                    SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                    sp_vec.pushBack(spriteFrame);
                }
                auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
                JiGuangFrameTwo->setDelayPerUnit(0.14f);
                AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "hall_bsjiantou");
            }
        }
        else if(wait_time == 25)
        {
            Vector<SpriteFrame*> sp_vec;
            //24个boss动画
            if(AnimationCache::getInstance()->getAnimation("hall_boss_1") == NULL)
            {
                char bossnumtmp[30];
                int bossnum;
                
                
                float temRand = CCRANDOM_0_1();
                if(temRand < (float)1/3)
                {
                    LogoLayer::room = 0;
                    GameHallLayer::boss_fish_room = 0;
                    UserDefault::getInstance()->setIntegerForKey("ios_room", 0);
                }else if(temRand < (float)2/3)
                {
                    LogoLayer::room = 1;
                    GameHallLayer::boss_fish_room = 1;
                    UserDefault::getInstance()->setIntegerForKey("ios_room", 1);
                }else if(temRand <= 1.0f)
                {
                    LogoLayer::room = 2;
                    GameHallLayer::boss_fish_room = 2;
                    UserDefault::getInstance()->setIntegerForKey("ios_room", 2);
                }
                UserDefault::getInstance()->flush();
                
                for(int i = 0; i< 24 ; i++)
                {
                    sprintf(bossnumtmp,"hall_boss_%d_num",i+1);
                    bossnum = GAME_DATA_INT(bossnumtmp);
                    sp_vec.clear();
                    for(int j = 1;j < bossnum + 1;j++)
                    {
                        char cTempFishSprite[30];
                        sprintf(cTempFishSprite,"fish_%d_0 (%d).png" ,i+22,j);
                        SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
                        sp_vec.pushBack(spriteFrame);
                    }
                    Animation* fishAnimation = Animation::createWithSpriteFrames(sp_vec);
                    fishAnimation->setDelayPerUnit(0.1f);
                    
                    char cTempFishAniName[40];
                    sprintf(cTempFishAniName,"fish_animationwf_%d_%d",LogoLayer::room,i+22);
                    AnimationCache::getInstance()->addAnimation(fishAnimation, cTempFishAniName);
                    
                    //加载死鱼动画
                    Animation* dfishAnimation = Animation::createWithSpriteFrames(sp_vec);
                    dfishAnimation->setDelayPerUnit(0.015f);
                    
                    char dcTempFishAniName[50];
                    sprintf(dcTempFishAniName,"dfish_animationwf_%d",i+22);
                    AnimationCache::getInstance()->addAnimation(dfishAnimation, dcTempFishAniName);
                }
            }
        }
        else if(wait_time == 30)
        {
            if(ifOldZhangHao == 0)
            {
                dengluCheng =false;
                if(fangjian == 0)
                {
                    buttonSound();
                    UserDefault::getInstance()->setIntegerForKey("bisaimoshi",0);
                    kaishiMenu->setEnabled(false);
                    
                    this->scheduleOnce(schedule_selector(GameBegin::jieping),0.01f);
                    
                }else
                {
                    buttonSound();
                    if(GameBegin::getFileData("gamePlayerlv.txt") < 5)
                    {
                        char tmp[50];
                        sprintf(tmp,GAME_DATA_STRING("gamehall_level_low"),5);
                        auto qiantaiduo = Gongxi::create(2,tmp);
                        qiantaiduo->setPosition(Vec2::ZERO);
                        addChild(qiantaiduo,1000);
                    }else
                    {
                        UserDefault::getInstance()->setIntegerForKey("bisaimoshi",1);
                        
                        kaishiMenu->setEnabled(false);
                        
                        this->scheduleOnce(schedule_selector(GameBegin::jieping),0.01f);
                    }
                }
                
                
            }
            else if(ifOldZhangHao == 3)
            {
                ifOldZhangHao = 0;
                this->scheduleOnce(schedule_selector(GameBegin::jieping),4);
            }
            else
            {
                this->scheduleOnce(schedule_selector(GameBegin::jieping),5);
            }
            
            
        }
 
    }
    
    if(dengluios)
    {
        //this->removeChildByTag(1003);
        dengluios = false;
        char gongxiTmp[100];
        sprintf(gongxiTmp,"check_order_%d",dengluint);
        auto gongxi = Gongxi::create(2,GAME_DATA_STRING(gongxiTmp));
        gongxi->setPosition(Point::ZERO);
        addChild(gongxi,1003);
        if(dengluint == 17 )
        {
            this->removeChildByTag(888);
        }
    }
}

void GameBegin::menuGo(Ref* pSender)
{
    
 /*    auto scene = WebViewTest::createScene();
    
    
    this->addChild(scene);
     */
    
    
    
    fangjian =((MenuItemSprite * ) pSender)->getTag();
    if(fangjian == 0)
    {
        
        
    }else
    {
        buttonSound();
        if(GameBegin::getFileData("gamePlayerlv.txt") < 5)
        {
            char tmp[50];
            sprintf(tmp,GAME_DATA_STRING("gamehall_level_low"),5);
            auto qiantaiduo = Gongxi::create(2,tmp);
            qiantaiduo->setPosition(Vec2::ZERO);
            addChild(qiantaiduo,1000);
            return;
        }
    }
    
    
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	GameBegin::dengluCheng = true;
#endif
 GameBegin::dengluCheng = true;
    
    
    auto waitingQQ = Waiting::create();
    waitingQQ->setString(GAME_DATA_STRING("begin_login"));
    addChild(waitingQQ,1000,1001);
   
} 

void GameBegin::afterCaptured(bool succeed, const std::string& outputFile)
{
    if (succeed)
    {
 
    }
    else
    {
        log("Capture screen failed.");
    }
}

bool GameBegin::onTouchBegan(Touch* touch, Event* event) 
{  
	return true;
}

void GameBegin::onTouchEnded(Touch* touch, Event* event)
{

}	

void GameBegin::onTouchMoved(Touch* touch, Event* event)
{
}

Scene* GameLogin::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    auto layer =  GameLogin::create() ;
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool GameLogin::init()
{
    
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    name_so[0] = 'a'; name_so[1] = 'b'; name_so[2] = 'c'; name_so[3] = 'd'; name_so[4] = 'e'; name_so[5] = 'f'; name_so[6] = 'g'; name_so[7] = 'h';
    name_so[8] = 'i'; name_so[9] = 'j'; name_so[10] = 'k';name_so[11] = 'l';name_so[12] = 'm';name_so[13] = 'n';name_so[14] = 'o';name_so[15] = 'p';
    name_so[16] = 'q';name_so[17] = 'r';name_so[18] = 's';name_so[19] = 't';name_so[20] = 'u';name_so[21] = 'v';name_so[22] = 'w';name_so[23] = 'x';
    name_so[24] = 'y';name_so[25] = 'z';name_so[26] = '1';name_so[27] = '2';name_so[28] = '3';name_so[29] = '4';name_so[30] = '5';name_so[31] = '6';
    name_so[32] = '7';name_so[33] = '8';name_so[34] = '9';name_so[35] = '0';
    
    auto zheZhao = LayerColor::create(ccc4(0,0,0,200),1024,768);
    zheZhao->setPosition(Point::ZERO);
    this->addChild(zheZhao);
    
    //控制面板
    
    //控制面板
    controlBg = cocos2d::ui::Scale9Sprite::createWithSpriteFrameName("bs_kuang.png",CCRectMake(50,50,50,50));
    controlBg->setContentSize(CCSizeMake(600,400));
    controlBg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    this->addChild(controlBg);
    
    controlBg->setScale(0.1f);
    ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);
    ScaleTo *ac8=ScaleTo::create(0.1f, 1);
    controlBg->runAction(Sequence::create(ac7,ac8,nullptr));
    
    auto submarineTitle = Sprite::create("denglu_title.png");
    submarineTitle->setPosition(Point(controlBg->getContentSize().width/2,controlBg->getContentSize().height));
    controlBg->addChild(submarineTitle,100);
    
    //帐号
    
    auto id_label = LabelTTF::create(GAME_DATA_STRING("user_id"),GameHallLayer::wordKind,24);
    id_label->setPosition(Vec2(controlBg->getContentSize().width * 0.2,controlBg->getContentSize().height * 0.7));
    controlBg->addChild(id_label,100);
    
    //密码
    auto psw_label = LabelTTF::create(GAME_DATA_STRING("user_psw"),GameHallLayer::wordKind,24);
    psw_label->setPosition(Vec2(controlBg->getContentSize().width * 0.2,controlBg->getContentSize().height * 0.5));
    controlBg->addChild(psw_label,100);
    
    //帐号编辑框
    id_kuang = cocos2d::ui::EditBox::create(Size(300,50),cocos2d::ui::Scale9Sprite::create("ios_kuang.png"),cocos2d::ui::Scale9Sprite::create("ios_kuang.png"),nullptr);
    id_kuang->setPosition(Vec2(controlBg->getContentSize().width*0.6,controlBg->getContentSize().height * 0.7));
    id_kuang->setFont("minijianling.ttf", 24);
    id_kuang->setFontColor(Color3B::WHITE);
    id_kuang->setText(UserDefault::getInstance()->getStringForKey("userid").c_str());
    id_kuang->setPlaceholderFontColor(Color3B::WHITE);
    id_kuang->setMaxLength(100);
    id_kuang->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
    id_kuang->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
    id_kuang->setDelegate(this);
    controlBg->addChild(id_kuang,10);
    
    //密码编辑框
    pwd_kuang = cocos2d::ui::EditBox::create(Size(300,50),cocos2d::ui::Scale9Sprite::create("ios_kuang.png"),cocos2d::ui::Scale9Sprite::create("ios_kuang.png"),nullptr);
    pwd_kuang->setPosition(Vec2(controlBg->getContentSize().width*0.6,controlBg->getContentSize().height * 0.5));
    pwd_kuang->setFont("minijianling.ttf", 24);
    pwd_kuang->setFontColor(Color3B::WHITE);
    pwd_kuang->setText(UserDefault::getInstance()->getStringForKey("userpwd").c_str());
    pwd_kuang->setPlaceholderFontColor(Color3B::WHITE);
    pwd_kuang->setMaxLength(100);
    pwd_kuang->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
    pwd_kuang->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
    pwd_kuang->setDelegate(this);
    controlBg->addChild(pwd_kuang,10);
    
    //auto suijiSprite = Sprite::create( "XR_suiji.png");
    //suijiItem = MenuItemSprite::create(suijiSprite,suijiSprite,CC_CALLBACK_0(GameLogin::init_zhuce,this));
    
    auto zhuceSprite = Sprite::create( "ios_zc.png");
    zhuceItem = MenuItemSprite::create(zhuceSprite,zhuceSprite,CC_CALLBACK_0(GameLogin::init_zhuce,this));
    
    auto dengluSprite = Sprite::create( "ios_dl.png");
    dengluItem = MenuItemSprite::create(dengluSprite,dengluSprite,CC_CALLBACK_0(GameLogin::denglu,this));
    
    auto menu = Menu::create(zhuceItem,dengluItem,nullptr);
    menu->alignItemsHorizontallyWithPadding(50);
    menu->setPosition(Vec2(controlBg->getContentSize().width*0.5,controlBg->getContentSize().height * 0.2));
    controlBg->addChild(menu,10);
    
   /* string id_tmp = id_kuang->getText();
    if(id_tmp != "" )
    {
        suijiItem->setEnabled(false);
        suijiItem->setColor(Color3B(127,127,127));
        
        zhuceItem->setEnabled(false);
        zhuceItem->setColor(Color3B(127,127,127));
    }*/
    
    //控制面板
    controlBg1 = cocos2d::ui::Scale9Sprite::createWithSpriteFrameName("bs_kuang.png",CCRectMake(50,50,50,50));
    controlBg1->setContentSize(CCSizeMake(600,450));
    controlBg1->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    this->addChild(controlBg1,10);
 
    controlBg1->setVisible(false);
    
    auto exitSprite = Sprite::createWithSpriteFrameName("hall_menu_X.png");
    auto exitSprited = Sprite::createWithSpriteFrameName("hall_menu_X_d.png");
    auto exitBtn = Menu::create(MenuItemSprite::create(exitSprite,exitSprited,exitSprite,CC_CALLBACK_0(GameLogin::exit,this)),nullptr);
    exitBtn->setPosition(Point(controlBg1->getContentSize().width - 10,controlBg1->getContentSize().height - 10));
    controlBg1->addChild(exitBtn,100);
    
    auto submarineTitle1 = Sprite::create("zhuce_title.png");
    submarineTitle1->setPosition(Point(controlBg1->getContentSize().width/2,controlBg1->getContentSize().height));
    controlBg1->addChild(submarineTitle1,100);
    
    //帐号
    
    auto id_label1 = LabelTTF::create(GAME_DATA_STRING("user_id"),GameHallLayer::wordKind,24);
    id_label1->setPosition(Vec2(controlBg1->getContentSize().width * 0.2,controlBg1->getContentSize().height * 0.75));
    controlBg1->addChild(id_label1,100);
    
    //密码
    auto psw_label1 = LabelTTF::create(GAME_DATA_STRING("user_psw"),GameHallLayer::wordKind,24);
    psw_label1->setPosition(Vec2(controlBg1->getContentSize().width * 0.2,controlBg1->getContentSize().height * 0.55));
    controlBg1->addChild(psw_label1,100);
    
    auto psw_label2 = LabelTTF::create(GAME_DATA_STRING("user_psw"),GameHallLayer::wordKind,24);
    psw_label2->setPosition(Vec2(controlBg1->getContentSize().width * 0.2,controlBg1->getContentSize().height * 0.35));
    controlBg1->addChild(psw_label2,100);
    
    //帐号编辑框
    id_kuang1 = cocos2d::ui::EditBox::create(Size(300,50),cocos2d::ui::Scale9Sprite::create("ios_kuang.png"),cocos2d::ui::Scale9Sprite::create("ios_kuang.png"),nullptr);
    id_kuang1->setPosition(Vec2(controlBg1->getContentSize().width*0.6,controlBg1->getContentSize().height * 0.75));
    id_kuang1->setFont("minijianling.ttf", 24);
    id_kuang1->setFontColor(Color3B::WHITE);
    //id_kuang1->setText(UserDefault::getInstance()->getStringForKey("userid").c_str());
    id_kuang1->setPlaceholderFontColor(Color3B::WHITE);
    id_kuang1->setMaxLength(100);
    id_kuang1->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
    id_kuang1->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
    id_kuang1->setDelegate(this);
    controlBg1->addChild(id_kuang1,10);
    
    //密码编辑框
    pwd_kuang1 = cocos2d::ui::EditBox::create(Size(300,50),cocos2d::ui::Scale9Sprite::create("ios_kuang.png"),cocos2d::ui::Scale9Sprite::create("ios_kuang.png"),nullptr);
    pwd_kuang1->setPosition(Vec2(controlBg1->getContentSize().width*0.6,controlBg1->getContentSize().height * 0.55));
    pwd_kuang1->setFont("minijianling.ttf", 24);
    pwd_kuang1->setFontColor(Color3B::WHITE);
   // pwd_kuang1->setText(UserDefault::getInstance()->getStringForKey("userpwd").c_str());
    pwd_kuang1->setPlaceholderFontColor(Color3B::WHITE);
    pwd_kuang1->setMaxLength(100);
    pwd_kuang1->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
    pwd_kuang1->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
    pwd_kuang1->setDelegate(this);
    controlBg1->addChild(pwd_kuang1,10);
    
    //密码编辑框
    pwd_kuang2 = cocos2d::ui::EditBox::create(Size(300,50),cocos2d::ui::Scale9Sprite::create("ios_kuang.png"),cocos2d::ui::Scale9Sprite::create("ios_kuang.png"),nullptr);
    pwd_kuang2->setPosition(Vec2(controlBg1->getContentSize().width*0.6,controlBg1->getContentSize().height * 0.35));
    pwd_kuang2->setFont("minijianling.ttf", 24);
    pwd_kuang2->setFontColor(Color3B::WHITE);
    //pwd_kuang2->setText(UserDefault::getInstance()->getStringForKey("userpwd").c_str());
    pwd_kuang2->setPlaceholderFontColor(Color3B::WHITE);
    pwd_kuang2->setMaxLength(100);
    pwd_kuang2->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
    pwd_kuang2->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
    pwd_kuang2->setDelegate(this);
    controlBg1->addChild(pwd_kuang2,10);
 
    
    auto zhuceSprite1 = Sprite::create( "ios_ct.png");
    auto zhuceItem1 = MenuItemSprite::create(zhuceSprite1,zhuceSprite1,CC_CALLBACK_0(GameLogin::qingchu,this));
    
    auto dengluSprite1 = Sprite::create("ios_qd.png");
    //dengluSprite1->setScale(108.0f/dengluSprite1->getContentSize().width, 51.0f/dengluSprite1->getContentSize().height);
  /*  auto  dengluItem1 = MenuItemSprite::create(dengluSprite1,dengluSprite1,CC_CALLBACK_0(GameLogin::zhuce,this));
   
    auto menu1 = Menu::create(zhuceItem1,dengluItem1,nullptr);
    menu1->alignItemsHorizontallyWithPadding(50);
    menu1->setPosition(Vec2(controlBg1->getContentSize().width*0.5,controlBg1->getContentSize().height * 0.15));
    controlBg1->addChild(menu1,10);

     */
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameLogin::onTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(GameLogin::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLogin::onTouchEnded,this);
    listener->setSwallowTouches(true);
    dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    return true;
}

void GameLogin::exit()
{
    ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);
    ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);
    controlBg1->runAction(Sequence::create(ac7,ac8,ToggleVisibility::create(),nullptr));
    
    controlBg->setScale(0.1f);
    ScaleTo *ac1=ScaleTo::create(0.2f, 1.05f);
    ScaleTo *ac2=ScaleTo::create(0.1f, 1);
    controlBg->runAction(Sequence::create(ToggleVisibility::create(),ac1,ac2,nullptr));
}

void GameLogin::qingchu()
{
    id_kuang1->setText("");
    pwd_kuang1->setText("");
    pwd_kuang2->setText("");
}

void GameLogin::init_zhuce()
{
    /*int id_tmp ;
    char tmpName[10] = "";
    //随机id
    for(int i = 0 ; i < 6 ; i ++)
    {
        id_tmp = (int)(CCRANDOM_0_1() * 35);
        tmpName[i] = name_so[id_tmp];
    }
    id_kuang->setText(tmpName);
    //随机pwd
    for(int i = 0 ; i < 6 ; i ++)
    {
        id_tmp = (int)(CCRANDOM_0_1() * 9 + 26);
        tmpName[i] = name_so[id_tmp];
    }
    pwd_kuang->setText(tmpName);
    
    UserDefault::getInstance()->setStringForKey("userid",id_kuang->getText());
    UserDefault::getInstance()->setStringForKey("userpwd",pwd_kuang->getText());
    UserDefault::getInstance()->flush();*/
    
    //controlBg->setScale(0.1f);
    ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);
    ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);
    controlBg->runAction(Sequence::create(ac7,ac8,ToggleVisibility::create(),nullptr));
    
    controlBg1->setScale(0.1f);
    ScaleTo *ac1=ScaleTo::create(0.2f, 1.05f);
    ScaleTo *ac2=ScaleTo::create(0.1f, 1);
    controlBg1->runAction(Sequence::create(ToggleVisibility::create(),ac1,ac2,nullptr));
}


void GameLogin::denglu()
{
    //auto layer = Waiting::create();
    //this->getParent()->addChild(layer,1003,1003);
    
    cocos2d::log("id = %s",id_kuang->getText());
    
    string useridtmp = id_kuang->getText();
    string userpwdtmp = pwd_kuang->getText();
    
    if(useridtmp.length() < 6 || useridtmp.length() > 12)
    {
        auto tishi = Gongxi::create(2, GAME_DATA_STRING("check_order_25"));
        this->addChild(tishi,100);
        return;
    }
    if(userpwdtmp.length() < 6 || userpwdtmp.length() > 12)
    {
        auto tishi = Gongxi::create(2, GAME_DATA_STRING("check_order_26"));
        this->addChild(tishi,100);
        return;
    }
    
    UserDefault::getInstance()->setStringForKey("userid",id_kuang->getText());
    UserDefault::getInstance()->setStringForKey("userpwd",pwd_kuang->getText());
    UserDefault::getInstance()->flush();
    
    CURL *curl;
    CURLcode res;
    std::string cc;
    curl=curl_easy_init();
    char postFields[100];
    
    sprintf(postFields,"userid=%s&password=%s",useridtmp.c_str(),userpwdtmp.c_str());
    
    if(curl)
    {
        if(GameBegin::is_ios_yueyu)
        {
            curl_easy_setopt( curl, CURLOPT_URL, "http://buyu2.iyueyo.com/qpby2/ios_yueyu/ios_user_denglu.php");
        }else
            curl_easy_setopt( curl, CURLOPT_URL, "http://buyu2.iyueyo.com/qpby2/ios/ios_user_denglu.php"); //请求的地址
        curl_easy_setopt(curl, CURLOPT_POST, true);                     //启用POST提交
        curl_easy_setopt(curl,CURLOPT_TIMEOUT,3000);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields); //发送的数据
        curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&possText); //处理的函数
        res=curl_easy_perform(curl);
        if(res!=CURLE_OK)
        {
            log("联网超时 %i",res);
            
        }
        curl_easy_cleanup(curl);
    }
    else
    {
        log("返回错误");
        return ;
    }
}

size_t  GameLogin::possText(uint8_t *buffer,size_t size,size_t nmemb,void *stream)
{
    cocos2d::log("补单返回数据： %s ", (const char *)buffer);
    string tmpstring = (const char *)buffer;
    
    if(tmpstring =="0")//注册成功
    {
        GameBegin::dengluios = true;
        GameBegin::dengluint = 21;
    }
    else if(tmpstring =="1")//登录成功
    {
        GameBegin::dengluios = true;
        GameBegin::dengluint = 17;
        
    }
    else if( tmpstring =="2000")//用户名为空
    {
        //
        GameBegin::dengluios = true;
        GameBegin::dengluint = 18;
    }
    else if( tmpstring =="2001")//用户名或密码不正确
    {
        //
        GameBegin::dengluios = true;
        GameBegin::dengluint = 20;
    }
    else if( tmpstring =="2002" )//用户名或密码不正确
    {
        //
        GameBegin::dengluios = true;
        GameBegin::dengluint = 19;
    }
    else if(tmpstring =="2004")//用户名不存在
    {
        //
        GameBegin::dengluios = true;
        GameBegin::dengluint = 22;
    }
    else //数据库异常
    {
        //
        GameBegin::dengluios = true;
        GameBegin::dengluint = 12;
    }
    
    size_t sizes = size*nmemb;
    return sizes;
}

bool GameLogin::onTouchBegan(Touch* touch, Event* event) 
{  
    return true;
}

void GameLogin::onTouchEnded(Touch* touch, Event* event)
{
    
}	

void GameLogin::onTouchMoved(Touch* touch, Event* event)
{
}

void GameLogin::editBoxReturn(cocos2d::ui::EditBox *editBox)
{
    
}