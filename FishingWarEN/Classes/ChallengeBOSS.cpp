#include "ChallengeBOSS.h"
#include "cocos-ext.h"
#include "GameScene.h"
#include "GameData.h"
#include "GameHallLayer.h"
#include "Gongxi.h"
#include "GameBegin.h"
#include "Shop.h"
#include "LogoLayer.h"
#include "GameHallLayer.h"
#include "SimpleAudioEngine.h"
#include "LoadRes.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
 
Label *ChallengeBOSS::yubiLabel=nullptr;
Label *ChallengeBOSS::zuanshiLabel=nullptr;
bool ChallengeBOSS::isqiehuan = false;

Scene* ChallengeBOSS::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ChallengeBOSS::create();

    // add layer as a child to scene
    scene->addChild(layer);


    // return the scene
    return scene;
}

void ChallengeBOSS::onExit()
{
    Node::onExit();
    
    
}

ChallengeBOSS::~ChallengeBOSS()
{
    
}

void ChallengeBOSS::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
    
    GameBegin::removeSouce(1);
    GameBegin::removeSouce(2);
    TextureCache::getInstance()->removeUnusedTextures();
}


bool ChallengeBOSS::init()
{  
	GameBegin::stopMusic();
	GameBegin::playMusic("",7);
	if ( !Layer::init() )	
	{
		return false;
	}
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("boss/bossChange.plist","boss/bossChange.png");
    Vector<SpriteFrame *> sp_vec;
    
    //远征小boss动画
    if(AnimationCache::getInstance()->getAnimation("boss_small_pass") == NULL)
    {
        sp_vec.clear();
        for(int j = 0;j < 6;j++)
        {
            char cTempFishSprite[30];
            sprintf(cTempFishSprite,"boss_small_passed_%d.png" ,j);
            SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
            sp_vec.pushBack(spriteFrame);
        }
        auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
        JiGuangFrameTwo->setDelayPerUnit(0.1f);
        AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "boss_small_pass");
    }
    //远征大boss动画
    if(AnimationCache::getInstance()->getAnimation("boss_big_pass") == NULL)
    {
        sp_vec.clear();
        for(int j = 0;j < 7;j++)
        {
            char cTempFishSprite[30];
            sprintf(cTempFishSprite,"boss_big_passed_%d.png" ,j);
            SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite);
            sp_vec.pushBack(spriteFrame);
        }
        auto JiGuangFrameTwo = Animation::createWithSpriteFrames(sp_vec);
        JiGuangFrameTwo->setDelayPerUnit(0.1f);
        AnimationCache::getInstance()->addAnimation(JiGuangFrameTwo, "boss_big_pass");
    }

	GameBegin::curScene = 3;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();
 
	cocos2d::log("boss 1");
	time_t currentTime;
	time(&currentTime);
 
	time_t later_time = UserDefault::getInstance()->getIntegerForKey("boss_later_time");
	if(later_time == 0 || currentTime > later_time + 24*60*60)
	{
		cur_boss_num = 0;
		is_boss_suc = false;
		is_boss_suc1 = true;
		day_times = 0;

		struct tm *nowTime = gmtime(&currentTime);
		int hour=nowTime->tm_hour;  
		int minute=nowTime->tm_min;  
		int second=nowTime->tm_sec;
		time_t boss_later_time = currentTime - hour*60*60 - minute*60 - second;

		UserDefault::getInstance()->setIntegerForKey("cur_boss_num",0);//挑战 解锁的boss
		UserDefault::getInstance()->setBoolForKey("is_boss_suc",false);//是否挑战成功
		UserDefault::getInstance()->setIntegerForKey("boss_day_times",0);//挑战失败的次数
		UserDefault::getInstance()->setIntegerForKey("boss_get_money",0);
		UserDefault::getInstance()->setIntegerForKey("boss_get_zuanshi",0);
		UserDefault::getInstance()->setIntegerForKey("boss_get_jiangbei",0);
		UserDefault::getInstance()->setIntegerForKey("boss_later_time",(int)boss_later_time);
		UserDefault::getInstance()->flush();
	}else
	{
		cur_boss_num = UserDefault::getInstance()->getIntegerForKey("cur_boss_num");
		is_boss_suc = UserDefault::getInstance()->getBoolForKey("is_boss_suc");
		is_boss_suc1 = UserDefault::getInstance()->getBoolForKey("is_boss_suc1");
		day_times = UserDefault::getInstance()->getIntegerForKey("boss_day_times");
	}
	cocos2d::log("boss 1");
		  
	//上半部分背景
	auto boss_top_bg = Sprite::createWithSpriteFrameName("boss_top_bg.png");
	boss_top_bg->setAnchorPoint(Vec2(0.5,1));
	boss_top_bg->setPosition(Point(visibleSize.width/2,visibleSize.height));
	this->addChild(boss_top_bg); 

	//啤酒盖
	auto boss_beer_gai = Sprite::createWithSpriteFrameName("boss_beer_gai.png");
	boss_beer_gai->setPosition(Point(boss_top_bg->getContentSize().width * 0.1,boss_top_bg->getContentSize().height* 0.8));
	boss_top_bg->addChild(boss_beer_gai,2); 

	//退出按钮
	auto boss_exit = Sprite::createWithSpriteFrameName("cannon_exit.png");
	auto boss_exit_d = Sprite::createWithSpriteFrameName("cannon_exit_down.png");
	auto boss_exit_menu = Menu::create(MenuItemSprite::create(boss_exit,boss_exit_d,CC_CALLBACK_0(ChallengeBOSS::boss_exit,this)),nullptr);
	boss_exit_menu->setPosition(Vec2(boss_top_bg->getContentSize().width - 48,boss_top_bg->getContentSize().height -  46 ));
	boss_top_bg->addChild(boss_exit_menu,-1);

	cocos2d::log("boss 2");

	//鱼币背景
	auto hall_db_yb_bg1 = Sprite::createWithSpriteFrameName("boss_top_kuang.png");
	auto hall_db_yb_bg2 = Sprite::createWithSpriteFrameName("boss_top_kuang_d.png");
	MenuItemSprite * hall_db_yb_bg = MenuItemSprite::create(hall_db_yb_bg1,hall_db_yb_bg2,CC_CALLBACK_0(ChallengeBOSS::quShop,this));
	hall_db_yb_bg->setScale(0.85);

	//鱼币icon
	auto hall_db_yb_icon = Sprite::createWithSpriteFrameName("yubi.png");
	hall_db_yb_icon->setPosition(Vec2(hall_db_yb_bg->getContentSize().width * 0.1,hall_db_yb_bg->getContentSize().height * 0.5));
	hall_db_yb_bg->addChild(hall_db_yb_icon);

	//鱼币数量label
	char cTemp[30];
	yubiLabel = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
	sprintf(cTemp,"%d",GameBegin::getFileData("jywer.txt"));
	yubiLabel->setString(cTemp);
	yubiLabel->setScale(0.8);
	yubiLabel->setPosition(Point(hall_db_yb_bg->getContentSize().width/2,hall_db_yb_bg->getContentSize().height/2));
	hall_db_yb_bg->addChild(yubiLabel);

	//钻石数值背景
	auto hall_db_zs_bg1 = Sprite::createWithSpriteFrameName("boss_top_kuang.png");
	auto hall_db_zs_bg2 = Sprite::createWithSpriteFrameName("boss_top_kuang_d.png");
	MenuItemSprite * hall_db_zs_bg = MenuItemSprite::create(hall_db_zs_bg1,hall_db_zs_bg2,CC_CALLBACK_0(ChallengeBOSS::quShop,this));
	hall_db_zs_bg->setScale(0.85);

	//钻石icon
	auto hall_db_zs_icon = Sprite::createWithSpriteFrameName("diamond.png");
	hall_db_zs_icon->setPosition(Vec2(hall_db_zs_bg->getContentSize().width * 0.1,hall_db_zs_bg->getContentSize().height * 0.5));
	hall_db_zs_bg->addChild(hall_db_zs_icon);

	//钻石数量label
	zuanshiLabel = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
	zuanshiLabel->setScale(0.8);
	sprintf(cTemp,"%d",GameBegin::getFileData("jywopl.txt"));
	zuanshiLabel->setString(cTemp);
	zuanshiLabel->setPosition(Point(hall_db_zs_bg->getContentSize().width/2,hall_db_zs_bg->getContentSize().height/2));
	hall_db_zs_bg->addChild(zuanshiLabel);

	auto boss_shop_anniu = Menu::create(hall_db_yb_bg,hall_db_zs_bg,nullptr);
	boss_shop_anniu->alignItemsHorizontallyWithPadding(20);
	boss_shop_anniu->setPosition(Vec2(boss_top_bg->getContentSize().width * 0.5,boss_top_bg->getContentSize().height * 0.88));
	boss_top_bg->addChild(boss_shop_anniu,2);

	cocos2d::log("boss 3");

	//中间部分
	initCenter(); 

	cocos2d::log("boss 6");
	//底座
	auto boss_bottomBg = Sprite::createWithSpriteFrameName("boss_buttom_bg.png");
	boss_bottomBg->setPosition(Point(visibleSize.width/2,-15));
	boss_bottomBg->setAnchorPoint(Point(0.5,0));
	this->addChild(boss_bottomBg);

	//挑战按钮
	auto boss_c = Sprite::createWithSpriteFrameName("boss_change.png");
	auto boss_c_d = Sprite::createWithSpriteFrameName("boss_change_d.png");
	auto boss_c_menu = Menu::create(MenuItemSprite::create(boss_c,boss_c_d,CC_CALLBACK_0(ChallengeBOSS::challenge,this)),nullptr);
	boss_c_menu->setPosition(Vec2(boss_bottomBg->getContentSize().width/2,61 ));
	boss_bottomBg->addChild(boss_c_menu,-1);
 
	//啤酒被
	auto boss_beer = Sprite::createWithSpriteFrameName("boss_beer.png");
	boss_beer->setScale(0.85);
	boss_beer->setAnchorPoint(Vec2(0,0));
	boss_beer->setPosition(Point(visibleSize.width * 0,visibleSize.height * 0));
	this->addChild(boss_beer,2); 

	//任务说明
	auto boss_mission_word = Sprite::createWithSpriteFrameName("boss_mission_word.png");
	boss_mission_word->setScale(0.85);
	boss_mission_word->setPosition(Point(visibleSize.width * 0.5,visibleSize.height * 0.25));
	this->addChild(boss_mission_word,2); 

	//剩余挑战次数
	sprintf(tmp_name,"%d",10 - day_times);
	auto boss_day_times = LabelTTF::create(tmp_name,GameHallLayer::wordKind,24);
	boss_day_times->setColor(Color3B(77,50,33));
	boss_day_times->setPosition(Vec2(250,90));
	boss_mission_word->addChild(boss_day_times);

	cocos2d::log("boss 7");

	//奖励金币
	sprintf(tmp_name,"%d",UserDefault::getInstance()->getIntegerForKey("boss_get_money"));
	auto boss_jinbi = LabelTTF::create(tmp_name,GameHallLayer::wordKind,24);
	boss_jinbi->setColor(Color3B(77,50,33));
	boss_jinbi->setPosition(Vec2(200,53));
	boss_mission_word->addChild(boss_jinbi);

	//奖励钻石
	sprintf(tmp_name,"%d",UserDefault::getInstance()->getIntegerForKey("boss_get_zuanshi"));
	auto boss_zuanshi = LabelTTF::create(tmp_name,GameHallLayer::wordKind,24);
	boss_zuanshi->setColor(Color3B(77,50,33));
	boss_zuanshi->setPosition(Vec2(303,53));
	boss_mission_word->addChild(boss_zuanshi);

	////奖励奖杯
	//sprintf(tmp_name,"%d",UserDefault::getInstance()->getIntegerForKey("boss_get_jiangbei"));
	//auto boss_jiangbei = LabelTTF::create(tmp_name,GameHallLayer::wordKind,24);
	//boss_jiangbei->setColor(Color3B(77,50,33));
	//boss_jiangbei->setPosition(Vec2(408,53));
	//boss_mission_word->addChild(boss_jiangbei);
 

	//羽毛
	auto boss_yumao = Sprite::createWithSpriteFrameName("boss_maobi.png");
	boss_yumao->setScale(0.85);
	boss_yumao->setAnchorPoint(Vec2(0,1));
	boss_yumao->setPosition(Point(boss_mission_word->getContentSize().width * 0.9,boss_mission_word->getContentSize().height * 0.2));
	boss_mission_word->addChild(boss_yumao); 

	//绳子
	auto boss_rop = Sprite::createWithSpriteFrameName("boss_rop.png");
	boss_rop->setScale(0.85);
	boss_rop->setAnchorPoint(Vec2(1,0));
	boss_rop->setPosition(Point(visibleSize.width,visibleSize.height * 0));
	this->addChild(boss_rop,3); 
 
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ChallengeBOSS::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(ChallengeBOSS::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(ChallengeBOSS::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	EventListenerKeyboard* kblsnr = EventListenerKeyboard::create(); 
	kblsnr->onKeyReleased = CC_CALLBACK_2(ChallengeBOSS::onKeyReleased, this); 
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(kblsnr, this); 

	this->scheduleUpdate();

	cocos2d::log("boss 8");
    return true;
}

void ChallengeBOSS::update(float)
{
	if(isqiehuan)
	{
		isqiehuan =  false;

		this->stopAllActions();
		this->removeAllChildrenWithCleanup(true);
		this->unscheduleAllSelectors();	

        GameBegin::removeSouce(2);
        
		auto scene = ChallengeBOSS::createScene();
		Director::getInstance()->replaceScene(scene);
	}
}

void ChallengeBOSS::initCenter()
{
	pos[0]  = Vec2(205,92);		pos[1]  = Vec2(283,66);		pos[2]  = Vec2(374,114);
	pos[3]  = Vec2(353,222);	pos[4]  = Vec2(277,280);	pos[5]  = Vec2(301,352);
	pos[6]  = Vec2(432,398);	pos[7]  = Vec2(512,333);	pos[8]  = Vec2(503,228);
	pos[9]  = Vec2(513,118);	pos[10] = Vec2(618,84);		pos[11] = Vec2(710,157);
	pos[12] = Vec2(755,275);	pos[13] = Vec2(872,287);	pos[14] = Vec2(913,188);
	pos[15] = Vec2(960,86);		pos[16] = Vec2(1072,83);	pos[17] = Vec2(1106,168);
	pos[18] = Vec2(1119,315);	pos[19] = Vec2(1193,376);	pos[20] = Vec2(1263,318);
	pos[21] = Vec2(1288,209);	pos[22] = Vec2(1344,118);	pos[23] = Vec2(1458,91);
 
	//设置层
	containerLayer = Layer::create();//创建视图的容器
	containerLayer->setScale(0.85);
	int tmp_x;
	if(cur_boss_num < 9)
	{
		tmp_x = pos[cur_boss_num].x - pos[0].x;
	}else
	{
		tmp_x = pos[9].x - pos[0].x;
	}
	containerLayer->setPosition(Point(-tmp_x,30));
	containerLayer->setContentSize(CCSizeMake(1550,480));
 
	//创建一个滚动视图
	scrollView = ScrollView::create();	
	scrollView->setViewSize(CCSizeMake(visibleSize.width, 500));//设置view的大小 (roomSpaceLenth + roomSize.width)*3
	scrollView->setContentOffset(Vec2::ZERO);
	scrollView->setContainer(containerLayer); //设置需要滚动的内容
	scrollView->ignoreAnchorPointForPosition(false);
	scrollView->setAnchorPoint(Vec2(0.5,0.5));
	scrollView->setPosition(Point(visibleSize.width/2 + origin.x,visibleSize.height * 0.62 + origin.y ));
	scrollView->setTouchEnabled(true);
	scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	scrollView->setDelegate(this);
	addChild(scrollView,1);
 
	auto boss_map = Sprite::create("boss_map.png");
	boss_map->setPosition(Point(containerLayer->getContentSize().width * (-0.5),containerLayer->getContentSize().height/2));
	containerLayer->addChild(boss_map); 
	if(!is_boss_suc)
	{
		boss_map->runAction(MoveTo::create(0.5f,Vec2(containerLayer->getContentSize().width * 0.5,containerLayer->getContentSize().height/2)));
	}else
	{
		boss_map->setPosition(Point(containerLayer->getContentSize().width * 0.5,containerLayer->getContentSize().height/2));
	}
	
	my_ship = Sprite::createWithSpriteFrameName("boss_my_ship.png");
	my_ship->setPosition(pos[cur_boss_num]);
	my_ship->setAnchorPoint(Vec2(0.5,0));
	//my_ship->setColor(Color3B(127,127,127));
	boss_map->addChild(my_ship,1);

	auto moveBy1 = MoveBy::create(0.5f,Vec2(0,5));
	auto movenBy2 = MoveBy::create(0.25f,Vec2(0,-3));
	auto movenBy3 = MoveBy::create(0.25f,Vec2(0,3));
	auto moveBy4 = MoveBy::create(0.5f,Vec2(0,-5));

	my_ship->runAction(RepeatForever::create(Sequence::create(moveBy1,movenBy2,movenBy3,moveBy4,nullptr)));

	cocos2d::log("boss 4");

	for(int i = 0 ; i < 24 ; i++)
	{
		//每一关的精灵
		Sprite * pos_tm_sp;
		if((i+1) % 6 == 0)
		{					
			if(i < cur_boss_num)
			{
				pos_tm_sp = Sprite::createWithSpriteFrameName("boss_big_passed_0.png");

				auto donghuaA = AnimationCache::getInstance()->getAnimation("boss_big_pass");
				auto *  pdAnimate = Animate::create(donghuaA);
				pos_tm_sp->runAction(RepeatForever::create(Sequence::create(DelayTime::create(i * 3.0f),pdAnimate,DelayTime::create((cur_boss_num-i) * 3.0f),nullptr)));
			}else
			{
				pos_tm_sp = Sprite::createWithSpriteFrameName("boss_big_pass.png");
			}
		}else
		{
			if(i < cur_boss_num)
			{
				pos_tm_sp = Sprite::createWithSpriteFrameName("boss_small_passed_0.png");
				auto donghuaA = AnimationCache::getInstance()->getAnimation("boss_small_pass");
				auto *  pdAnimate = Animate::create(donghuaA);
				pos_tm_sp->runAction(RepeatForever::create(Sequence::create(DelayTime::create(i * 3.0f),pdAnimate,DelayTime::create((cur_boss_num-i) * 3.0f),nullptr)));
			}else
			{
				pos_tm_sp = Sprite::createWithSpriteFrameName("boss_small_pass.png");
			}			
		}
		if(i == cur_boss_num)
		{
			if(is_boss_suc)
			{
				UserDefault::getInstance()->setIntegerForKey("cur_boss_num",cur_boss_num + 1);				
				UserDefault::getInstance()->setBoolForKey("is_boss_suc",false);
				UserDefault::getInstance()->flush();

				is_boss_suc = false;
				cur_boss_num ++; 
				my_ship->runAction(MoveTo::create(1.0f,pos[i+1]));

				if((i+1) % 6 == 0)
				{
					pos_tm_sp = Sprite::createWithSpriteFrameName("boss_big_passed_0.png");

					auto donghuaA = AnimationCache::getInstance()->getAnimation("boss_big_pass");
					auto *  pdAnimate = Animate::create(donghuaA);
					pos_tm_sp->runAction(RepeatForever::create(Sequence::create(DelayTime::create(i * 3.0f),pdAnimate,DelayTime::create((cur_boss_num-i) * 3.0f),nullptr)));
				}else
				{
					pos_tm_sp = Sprite::createWithSpriteFrameName("boss_small_passed_0.png");
					auto donghuaA = AnimationCache::getInstance()->getAnimation("boss_small_pass");
					auto *  pdAnimate = Animate::create(donghuaA);
					pos_tm_sp->runAction(RepeatForever::create(Sequence::create(DelayTime::create(i * 3.0f),pdAnimate,DelayTime::create((cur_boss_num-i) * 3.0f),nullptr)));
				}
				
			}else
			{			
				pos_tm_sp = Sprite::createWithSpriteFrameName("boss_cur_pos.png");
			}
		}
 

		//小管卡
		//pos_sp.pushBack(pos_tm_sp);
		if(i == cur_boss_num)
		{
			pos_tm_sp->setZOrder(2);
		}

		//24个按钮
		auto boss_pass_item = MenuItemSprite::create(pos_tm_sp,pos_tm_sp,CC_CALLBACK_1(ChallengeBOSS::boss_pass_info,this));
		boss_pass_item->setTag(i);
		auto boss_pass_menu = Menu::create(boss_pass_item,nullptr);
		boss_pass_menu->setPosition(pos[i]);
		boss_map->addChild(boss_pass_menu);
		if(i == cur_boss_num)
		{
			pos_tm_sp->setZOrder(2);
		}

	}

	cocos2d::log("boss 6");
 
}

void ChallengeBOSS::boss_pass_info(Ref * psender)
{
	GameBegin::buttonSound(); 
	if(cur_boss_num >= 24)
	{
		auto gong = Gongxi::create(1,GAME_DATA_STRING("boss_change_success_all"));
		this->addChild(gong,MENULAYER);
		return;
	}

	if(day_times == 10)
	{
		auto gong = Gongxi::create(2,GAME_DATA_STRING("boss_change_fail_all"));
		this->addChild(gong,MENULAYER);
		return;
	}

	int tag = ((MenuItemSprite *)psender)->getTag();
	auto bosslayer = BossInfo::create(tag,!is_boss_suc1);
	this->addChild(bosslayer,MENULAYER);

}

void ChallengeBOSS::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) 
{    
	switch(keyCode)     
	{     
		//监听返回键        
	case EventKeyboard::KeyCode::KEY_ESCAPE:     
		{
			GameBegin::buttonSound();
            this->removeAllChildrenWithCleanup(true);
 
            GameBegin::removeSouce(2);
            
			auto scene = GameHallLayer::createScene();
			Director::getInstance()->replaceScene(scene);
		}
		break;        
		//监听menu键   
	case EventKeyboard::KeyCode::KEY_MENU:   
		break;   
	}
}
 
bool ChallengeBOSS::onTouchBegan(Touch* touch, Event* event) 
{ 
	return true;
}

void ChallengeBOSS::onTouchMoved(Touch* touch, Event* event) 
{

}

void ChallengeBOSS::onTouchEnded(Touch* touch, Event* event)
{

}

//***********继承的函数实现
//滑动板函数
void ChallengeBOSS::scrollViewDidScroll(ScrollView* view) 
{
}

void ChallengeBOSS::scrollViewDidZoom(ScrollView* view) 
{
}

void ChallengeBOSS::boss_exit()
{
	GameBegin::buttonSound();
    
    this->removeAllChildrenWithCleanup(true);
    
    GameBegin::removeSouce(2);
 
	auto scene = GameHallLayer::createScene();
	Director::getInstance()->replaceScene(scene);

}
 
void ChallengeBOSS::challenge()
{
	//TO DO
	GameBegin::buttonSound(); 
	if(cur_boss_num >= 24)
	{
		auto gong = Gongxi::create(1,GAME_DATA_STRING("boss_change_success_all"));
		this->addChild(gong,MENULAYER);
		return;
	}

	if(day_times == 10)
	{
		auto gong = Gongxi::create(2,GAME_DATA_STRING("boss_change_fail_all"));
		this->addChild(gong,MENULAYER);
		return;
	}

	auto bosslayer = BossInfo::create(cur_boss_num,!is_boss_suc1);
	this->addChild(bosslayer,MENULAYER);
 
}

void ChallengeBOSS::quShop()
{
	GameBegin::buttonSound(); 

	this->removeChildByTag(1000);

	auto scene = Shop::create(8);
	this->addChild(scene,1000);
}

void ChallengeBOSS::quShengji()
{
	GameBegin::buttonSound(); 

	this->removeChildByTag(1000);
 
	//进入boss场景
	GameScene::cGameType = 2;  
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true); 
	 
    this->removeAllChildrenWithCleanup(true);
    
    GameHallLayer::RoomType = 1;
    GameBegin::removeSouce(2);
    
	GameHallLayer::RoomType = 65; 


	LoadRes::RoomType =   GameHallLayer::RoomType ;
	auto scene = LoadRes::createScene();	
	Director::getInstance()->replaceScene(scene);  
}

//**************公用的函数
//更新鱼币
void ChallengeBOSS::RefreshCoin(int coinNum)
{
	int tmpMonty = GameBegin::getFileData("jywer.txt") + coinNum;

	char tmpCoinNum[40];
	sprintf(tmpCoinNum,"%d",tmpMonty);
	yubiLabel->setString(tmpCoinNum);  

	GameBegin::setFileData("jywer.txt",tmpMonty); 
}

//更新钻石
void ChallengeBOSS::RefreshDiamond(int diamondNum)
{
	int tmpMonty = GameBegin::getFileData("jywopl.txt") + diamondNum;

	char tmpCoinNum[40];
	sprintf(tmpCoinNum,"%d",tmpMonty);
	zuanshiLabel->setString(tmpCoinNum);  

	GameBegin::setFileData("jywopl.txt",tmpMonty); 
}

//随机一个int
int ChallengeBOSS::randNum(string tmp)
{
	if(tmp == "")
	{
		return 0;
	}else
	{
		char tmp_name[30];
		if(tmp.find("-") != tmp.npos)
		{
			char * stringTmp = (char *)tmp.c_str();
			//随机两个之间的数值
			char * tmpSmp1;
			char * tmpSmp2;
			int tmpInt1;
			int tmpInt2;

			tmpSmp1 = strtok(stringTmp,"-");
			tmpSmp2 = strtok(NULL,"-");
			memset(tmp_name,0,sizeof(tmp_name));
			for(int i = 0 ; i < strlen(tmpSmp1) ;i++)
			{
				char c = tmpSmp1[i];
				tmp_name[i] = c;
			}
			tmpInt1 = atoi(tmp_name);

			memset(tmp_name,0,sizeof(tmp_name));
			for(int i = 0 ; i < strlen(tmpSmp2) ;i++)
			{
				char c = tmpSmp2[i];
				tmp_name[i] = c;
			}
			tmpInt2 = atoi(tmp_name);

			return CCRANDOM_0_1()*(tmpInt2 - tmpInt1) + tmpInt1;

		}else
		{		
			int tmptmp = atoi(tmp.c_str());
			return tmptmp;
		}
	}
}

//**************************************BossInfo
BossInfo * BossInfo::create(int btnKind,bool huaqian)
{
	BossInfo * gongxi = new BossInfo();
	gongxi->init(btnKind,huaqian);
	gongxi->autorelease();
	return gongxi;
}

bool BossInfo::init(int btnKind,bool huaqian)
{  
	if ( !Layer::init() )	
	{
		return false;
	}
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("boss/bossChange.plist","boss/bossChange.png");
	kind = btnKind;
	huaqianfou = huaqian;
 
	//srand(time(NULL));
	visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();

	auto zheZhao = LayerColor::create(ccc4(0,0,0,150),1024,768);
	zheZhao->setPosition(Point::ZERO);
	this->addChild(zheZhao);
 
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(BossInfo::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(BossInfo::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(BossInfo::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触�?
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	//背景图
	bossInfoBG = Sprite::createWithSpriteFrameName( "boss_arrest_bg.png");
	bossInfoBG->setPosition(Point(visibleSize.width * 0.533,visibleSize.height * 0.6));
	this->addChild(bossInfoBG);

	bossInfoBG->setScale(0.1f);
	ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.1f, 1.0);  
	bossInfoBG->runAction(Sequence::create(ac7,ac8,nullptr)); 

	//第几关
	char cTemp[30];
	auto boss_num_pass = Label::createWithCharMap("img/boss_num.png",27,38,'0');
	sprintf(cTemp,"%d",kind + 1);
	boss_num_pass->setString(cTemp);
	boss_num_pass->setPosition(Point(165,368));
	bossInfoBG->addChild(boss_num_pass);
 
	auto ip_dtx_stencil = Sprite::createWithSpriteFrameName("boss_arrest_map.png");
	auto ip_dtx_clipper = ClippingNode::create();
	ip_dtx_clipper->setStencil(ip_dtx_stencil);//设置裁剪模板 //3
	ip_dtx_clipper->setInverted(false);//设置底板不可见
	//ip_dtx_clipper->setPosition(Vec2(ip_dtx_stencil->getContentSize()/2));
	ip_dtx_clipper->setPosition(Vec2(166,251));
	ip_dtx_clipper->setAlphaThreshold(0);//设置绘制底板的Alpha值为0
	bossInfoBG->addChild(ip_dtx_clipper);//4
 
	//boss 动画
	sprintf(tmp_boss_name,"fish_%d_0 (1).png",kind+22);
	auto hall_room_slt_boss = Sprite::createWithSpriteFrameName(tmp_boss_name);
	hall_room_slt_boss->setPosition(Vec2(-150,ip_dtx_clipper->getContentSize().height/2));
	ip_dtx_clipper->addChild(hall_room_slt_boss);
 
	float hall_room_bss_scale1 = 235.0f/ hall_room_slt_boss->getContentSize().width ;
	float hall_room_bss_scale2 = 120.0f / hall_room_slt_boss->getContentSize().height;
	float hall_room_bss_scale = hall_room_bss_scale1 > hall_room_bss_scale2 ? hall_room_bss_scale2 :hall_room_bss_scale1;
	hall_room_slt_boss->setScale(hall_room_bss_scale);
 
	if(kind == 0 || kind == 1 || kind == 2 || kind == 6 || kind == 7 || kind == 8 || kind == 10 || kind == 11 || kind == 12 || kind == 13 || kind == 15||kind == 20|| kind == 22|| kind == 21) 
	{
		hall_room_slt_boss->setRotation(90);
		hall_room_slt_boss->setScale(hall_room_bss_scale + 0.2);
		////boss 移动路线
		//auto ac1 = MoveBy::create(4.0f,Vec2(200,0));
		//auto ac2 = FlipY::create(true);
		//auto ac3 = MoveBy::create(8.0f,Vec2(-400,0));
		//auto ac4 = FlipY::create(false);
		//auto ac5 = MoveBy::create(4.0f,Vec2(200,0));
		//auto seq = Sequence::create(ac1,ac2,ac3,ac4,ac5,DelayTime::create(4.0f),nullptr);
		//hall_room_slt_boss->runAction(RepeatForever::create(seq));
	}else
	{
		//boss 移动路线
		/*auto ac1 = MoveBy::create(4.0f,Vec2(200,0));
		auto ac2 = FlipX::create(true);
		auto ac3 = MoveBy::create(8.0f,Vec2(-400,0));
		auto ac4 = FlipX::create(false);
		auto ac5 = MoveBy::create(4.0f,Vec2(200,0));
		auto seq = Sequence::create(ac1,ac2,ac3,ac4,ac5,DelayTime::create(4.0f),nullptr);
		hall_room_slt_boss->runAction(RepeatForever::create(seq));*/
	}
 
	auto ac1 = MoveBy::create(3.0f,Vec2(150,0));
	hall_room_slt_boss->runAction(ac1);
	//boss动画 
	sprintf(tmp_boss_name,"fish_animationwf_%d_%d",LogoLayer::room,kind+22);
	hall_room_slt_boss->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(tmp_boss_name)))) ;
 
	//23  19 18 17 16 14 9 3 4
	//难度等级
	char tmp_name[30];
	sprintf(tmp_name,"boss_level%d.png",(kind/6) + 1);
	auto boss_name = Sprite::createWithSpriteFrameName(tmp_name);
	boss_name->setPosition(Vec2(60,308));
	bossInfoBG->addChild(boss_name);

	//名字背景
	auto boss_name_bg = Sprite::createWithSpriteFrameName("boss_name_bg.png");
	boss_name_bg->setAnchorPoint(Vec2(1,0));
	boss_name_bg->setPosition(Vec2(285,178));
	bossInfoBG->addChild(boss_name_bg);
/*
	//boss名字
	sprintf(tmp_name,"bossname%d",kind+1);
	auto boss_name_tag = LabelTTF::create(GAME_DATA_STRING(tmp_name),GameHallLayer::wordKind,24);
	boss_name_tag->setAnchorPoint(Vec2(1,0.5));
	boss_name_tag->setPosition(Vec2(boss_name_bg->getContentSize().width * 0.97,boss_name_bg->getContentSize().height/2));
	boss_name_bg->addChild(boss_name_tag);
*/
	//奖励金币
	sprintf(tmp_name,"bossmoney%d",kind+1);
	auto boss_jinbi = Label::createWithCharMap("img/boss_num.png",27,38,'0');
	sprintf(tmp_name,"%d",atoi(((string)GAME_DATA_STRING(tmp_name)).c_str()));
	boss_jinbi->setString(tmp_name);
	boss_jinbi->setScale(0.5);
	boss_jinbi->setAnchorPoint(Vec2(0,0.5));
	boss_jinbi->setPosition(Vec2(162,128));
	bossInfoBG->addChild(boss_jinbi);

	//奖励钻石
	sprintf(tmp_name,"bosszuanshi%d",kind+1);
	auto boss_zuanshi = Label::createWithCharMap("img/boss_num.png",27,38,'0');
	sprintf(tmp_name,"%d",atoi(((string)GAME_DATA_STRING(tmp_name)).c_str()));
	boss_zuanshi->setString(tmp_name);
	boss_zuanshi->setScale(0.5);
	boss_zuanshi->setAnchorPoint(Vec2(0,0.5));
	boss_zuanshi->setPosition(Vec2(162,92));
	bossInfoBG->addChild(boss_zuanshi);

	////奖励奖杯
	//sprintf(tmp_name,"bossjiangbei%d",kind+1);
	//auto boss_jiangbei = LabelTTF::create(GAME_DATA_STRING(tmp_name),GameHallLayer::wordKind,14);
	//boss_jiangbei->setColor(Color3B(77,50,33));
	//boss_jiangbei->setPosition(Vec2(195,65));
	//bossInfoBG->addChild(boss_jiangbei);
 
	auto bossInfoBG_guang = Sprite::createWithSpriteFrameName( "boss_change_bg.png");
	bossInfoBG_guang->setPosition(Point(bossInfoBG->getContentSize().width * 0.42,-bossInfoBG_guang->getContentSize().height * 0.3));
	//bossInfoBG_guang->setScale(1.5);
	bossInfoBG->addChild(bossInfoBG_guang,-1);	
	bossInfoBG_guang->runAction(RepeatForever::create(RotateBy::create(1.0f,2)));

	//挑战按钮
	auto boss_exit = Sprite::createWithSpriteFrameName("boss_change_o.png");
	auto boss_exit_d = Sprite::createWithSpriteFrameName("boss_change_o_d.png");
	auto boss_exit_n = Sprite::createWithSpriteFrameName("boss_change_o_n.png");
	auto boss_exit_item = MenuItemSprite::create(boss_exit,boss_exit_d,boss_exit_n,CC_CALLBACK_0(BossInfo::tiaozhan,this));
	auto boss_exit_menu = Menu::create(boss_exit_item,nullptr);
	boss_exit_menu->setPosition(Vec2(bossInfoBG->getContentSize().width * 0.42,-bossInfoBG_guang->getContentSize().height*0.25));
	bossInfoBG->addChild(boss_exit_menu);

	auto bossInfoBG_xiaohao = Sprite::createWithSpriteFrameName( "boss_xiaohao.png");
	bossInfoBG_xiaohao->setPosition(Point(bossInfoBG->getContentSize().width * 0.42,10));
	bossInfoBG->addChild(bossInfoBG_xiaohao);
 
	int daytimes = UserDefault::getInstance()->getIntegerForKey("boss_day_times");
	sprintf(tmp_boss_name,"boss_tiaozhan_cishu_%d",daytimes - 1);
	auto daytimesLabel = Label::create();
	if(huaqianfou)
		daytimesLabel->setString(GAME_DATA_STRING(tmp_boss_name));
	else
		daytimesLabel->setString("0");
	daytimesLabel->setScale(0.7);
	daytimesLabel->setPosition(Point(140,28));
	bossInfoBG_xiaohao->addChild(daytimesLabel);


	if(UserDefault::getInstance()->getIntegerForKey("cur_boss_num") != kind )
	{
		boss_exit_item->setEnabled(false);
		daytimesLabel->setCharMap("img/hall_huangjinzi_h.png",34,41,'0');
		bossInfoBG_guang->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("boss_change_bg_h.png"));
		bossInfoBG_xiaohao->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("boss_xiaohao_h.png"));
		
	}else
	{
		daytimesLabel->setCharMap("img/hall_huangjinzi.png",34,41,'0');
	}

	return true;
}
 
void BossInfo::tiaozhan()
{
	
	GameBegin::buttonSound();
   // DCEvent::onEvent("tiaozhan_Boss");

	this->removeChildByTag(1000);

	int daytimes = UserDefault::getInstance()->getIntegerForKey("boss_day_times");
	sprintf(tmp_boss_name,"boss_tiaozhan_cishu_%d",daytimes - 1);

	if(GameBegin::getFileData("jywopl.txt") < GAME_DATA_INT(tmp_boss_name) & huaqianfou)
	{
		auto gongxi = Gongxi::create(3,GAME_DATA_STRING("gamehall_zuanshi_low"));
		gongxi->setPosition(Point::ZERO);
		this->addChild(gongxi,1000,1000);

		auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png");
		auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_0(BossInfo::quShop,this));

		auto btnMenu = Menu::create(quedingItem,nullptr);
		btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
		gongxi->getChildByTag(1)->addChild(btnMenu,100);

		return;
	}
	if(huaqianfou)
		ChallengeBOSS::RefreshDiamond(-GAME_DATA_INT(tmp_boss_name));

    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("bossChange.plist");
    AnimationCache::getInstance()->removeAnimation("boss_small_pass");
    AnimationCache::getInstance()->removeAnimation("boss_big_pass");
    
	//进入boss场景
	GameScene::cGameType = 2;  
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true); 
	FishLayer::cNewBoss = kind;
 
	this->unscheduleAllSelectors();
    this->removeAllChildrenWithCleanup(true);
    GameHallLayer::RoomType = 1;
    GameBegin::removeSouce(2);
    
    
    GameHallLayer::RoomType = 65;
	LoadRes::RoomType =   GameHallLayer::RoomType ;
	auto scene = LoadRes::createScene();	
	Director::getInstance()->replaceScene(scene);
}

void BossInfo::quShop()
{
	GameBegin::buttonSound(); 

	this->removeChildByTag(1000);

	auto scene = Shop::create(8);
	this->addChild(scene,1000);
}

void BossInfo::quehuan(float dt)
{
	auto scene = ChallengeBOSS::createScene();
	Director::getInstance()->replaceScene(scene);
}
 
bool BossInfo::onTouchBegan(Touch* touch, Event* event) 
{ 
	p1 = touch->getLocation();
	return true;
}

void BossInfo::onTouchMoved(Touch* touch, Event* event) 
{

}

void BossInfo::onTouchEnded(Touch* touch, Event* event)
{
	 p2 = touch->getLocation();
	 if(abs(p2.x - p1.x) < 4 && kind != 99)
	{
		exit();			
	}
}
 
void BossInfo::exit()
{	 
	GameBegin::buttonSound();

	ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
	bossInfoBG->runAction(Sequence::create(ac7,ac8,nullptr)); 

	this->runAction(Sequence::create(DelayTime::create(0.3f),RemoveSelf::create(),nullptr));
}
 