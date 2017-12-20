#include "MatchPlayer.h"
#include "GameHallLayer.h"
#include "LoadRes.h"
#include "GameBegin.h"
#include "GameData.h"
#include "GameScene.h"
 
Scene* MatchPlayer::createScene()
{
	auto scene = Scene::create();
	auto layer = MatchPlayer::create();
	scene->addChild(layer);
	return scene;
}

void MatchPlayer::init_shuzhi()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	int bs_room_renshu = GameHallLayer::bs_RenShu[GameHallLayer::bs_moshi-1]; 
	float MP_kaishi_renshu = bs_room_renshu * (1+ CCRANDOM_0_1());//开赛所需人数
	UserDefault::getInstance()->setIntegerForKey("bisairenshu",(int)MP_kaishi_renshu);
	UserDefault::getInstance()->flush();

	float totalZhen = MatchTimeTotal/0.014f;   //总变化帧数
	init_renshu_num = bs_room_renshu * 0.9;  //初始在线人数
	MP_renshu_sl = (MP_kaishi_renshu-init_renshu_num)/totalZhen;
	MP_renshu_tmp = 0;
	MP_time_num[0] = CCRANDOM_0_1()+1.0;
	MP_time_num[1] = CCRANDOM_0_1()+1.5;
	MP_time_num[2] = CCRANDOM_0_1();

	MP_renshu_sl_total = 0;

	MP_jiantou_jd = atan(15.0f/20.0f) * 180 / 3.1415927;

	//头像减速过程
	for(int i = 0 ; i < 3 ; i ++)
	{
		is_jiansu_flag[i] = false;   	

		tx_v1[i] = 15.87;			//初速度
		tx_a[i] = 0.263;			//减速度
		tx_lucheng[i] = -34;		//总路程

		mc_v1[i] = 9.9;			//初速度
		mc_a[i] = 0.165;			//减速度
		mc_lucheng[i] = -10;		//总路程
	}
	

	//随机玩家的位置
	if(CCRANDOM_0_1()*100 < 50)
	{
		GameHallLayer::player_pos = 0;
		GameHallLayer::robot1[0] = 1;
	}else
	{
		GameHallLayer::player_pos = 1;
		GameHallLayer::robot1[0] = 0;
	}
	GameHallLayer::robot2[0] = 2;
	GameHallLayer::robot3[0] = 3;

	//随机机器人的头像
	GameHallLayer::robot1[1] = CCRANDOM_0_1()* ( MatchTouxiang -1 ) + 1;
	GameHallLayer::robot2[1] = (GameHallLayer::robot1[1] + 1)%MatchTouxiang + 1;
	GameHallLayer::robot3[1] = (GameHallLayer::robot1[1] + 3)%MatchTouxiang + 1;
	cocos2d::log("robo1 t = %d , robo2 t = %d , robo3 t = %d ",GameHallLayer::robot1[1], GameHallLayer::robot2[1], GameHallLayer::robot3[1]);
	//初始化头像条
	for(int i = 0 ; i< 3 ;i++)
	{
		auto touxiang_BG_tiao =  Sprite::createWithSpriteFrameName("match_tx_tiao.jpg");
		touxiang_BG_tiao->setAnchorPoint(Vec2(0.5,0));
		for(int j = 1 ; j <= MatchTouxiang ; j++)
		{
			sprintf(MP_tmpchar,"tou%d.png",j);
			auto mp_tx = Sprite::createWithSpriteFrameName(MP_tmpchar);
			mp_tx->setScale(68.0f/270.0f);
			mp_tx->setPosition(Vec2(touxiang_BG_tiao->getContentSize().width/2,68*(8-(((j - GameHallLayer::robot1[1] - i*2 + 16))%MatchTouxiang + 0.5))));
			touxiang_BG_tiao->addChild(mp_tx);
		}
		
		match_tx_tiao.pushBack(touxiang_BG_tiao);
	}

	//随机机器人的姓名
    GameHallLayer::robot1[2] = CCRANDOM_0_1()*499 + 1;
    GameHallLayer::robot2[2] = CCRANDOM_0_1()*499 + 1;
    GameHallLayer::robot3[2] = CCRANDOM_0_1()*499 + 1;
    cocos2d::log("robo1 n = %d , robo2 n = %d , robo3 n = %d ",GameHallLayer::robot1[2], GameHallLayer::robot2[2], GameHallLayer::robot3[2]);
    
    int iTempRan = CCRANDOM_0_1()*90;
    if(iTempRan< 30)
    {
        if(CCRANDOM_0_1()*100<50)
            GameHallLayer::robot1[2] = CCRANDOM_0_1()*218+1;
    }
    else if(iTempRan< 60)
    {
        if(CCRANDOM_0_1()*100<50)
            GameHallLayer::robot2[2] = CCRANDOM_0_1()*218+1;
    }
    else
    {
        if(CCRANDOM_0_1()*100<50)
            GameHallLayer::robot3[2] = CCRANDOM_0_1()*218+1;
    }
	//初始化名称条
	for(int i = 0 ; i< 3 ;i++)
	{
		auto mc_BG_tiao =  Sprite::createWithSpriteFrameName("match_mc_tiao.jpg");
		mc_BG_tiao->setAnchorPoint(Vec2(0.5,0));
		for(int j = 0 ; j < 10 ; j++)
		{
			if(i == 0)
				sprintf(MP_tmpchar,"robotNName%d",(GameHallLayer::robot1[2] -1 + j)%500 + 1);
			if(i == 1)
				sprintf(MP_tmpchar,"robotNName%d",(GameHallLayer::robot2[2] -1 + j)%500 + 1);
			if(i == 2)
				sprintf(MP_tmpchar,"robotNName%d",(GameHallLayer::robot3[2] -1 + j)%500 + 1);

			auto mp_mc = LabelTTF::create(GAME_DATA_STRING(MP_tmpchar),GameHallLayer::wordKind,16);
			mp_mc->setPosition(Vec2(mc_BG_tiao->getContentSize().width/2,33*(9.5 - j)));
			mc_BG_tiao->addChild(mp_mc);
		}
		match_mc_tiao.pushBack(mc_BG_tiao);
	}

	//初始化箭头
	for(int i = 0 ; i< 3 ;i++)
	{
		auto mc_BG_tiao =  Sprite::createWithSpriteFrameName("match_jiantou.png");	
		mc_BG_tiao->setRotation(-MP_jiantou_jd);
		mc_BG_tiao->setAnchorPoint(Vec2(0.74,0.5));
		match_jiantou.pushBack(mc_BG_tiao);
	}
	//初始化火花
	for(int i = 0 ; i< 3 ;i++)
	{
		//auto mc_BG_tiao =  Sprite::createWithSpriteFrameName("baoming_hh1.png");
		//match_huohua.pushBack(mc_BG_tiao);
	}
}

bool MatchPlayer::init()
{  
	if ( !Layer::init() )	
	{
		return false;
	}
 
	GameBegin::stopMusic();
	GameBegin::playMusic("bgmusic.mp3",5);

	init_shuzhi();

	auto zheZhao = LayerColor::create(ccc4(0,0,0,100),1024,768);
	zheZhao->setPosition(Vec2::ZERO);
	this->addChild(zheZhao);

	//控制面板
	controlBg = Scale9Sprite::createWithSpriteFrameName( "bs_kuang.png",CCRectMake(50,50,50,50));
	controlBg->setContentSize(CCSizeMake(755,485));
	controlBg->setScale(0.85);
	controlBg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	this->addChild(controlBg);
 
	//退出按钮
	auto mp_sprite_tc = Sprite::createWithSpriteFrameName("hall_menu_X.png");
	auto mp_sprite_tc_d = Sprite::createWithSpriteFrameName("hall_menu_X_d.png");
	auto mp_menu_tc = Menu::create(MenuItemSprite::create(mp_sprite_tc,mp_sprite_tc_d,CC_CALLBACK_0(MatchPlayer::exit,this)),nullptr);
	mp_menu_tc->setPosition(Vec2(controlBg->getContentSize().width - 10,controlBg->getContentSize().height - 10));
	controlBg->addChild(mp_menu_tc,100);

	//背景光
	auto bg_guang = Sprite::createWithSpriteFrameName("match_bg_guang.png");
	bg_guang->setPosition(Vec2(controlBg->getContentSize().width/2,controlBg->getContentSize().height * 0.45));
	controlBg->addChild(bg_guang,100);

	bg_guang->runAction(RepeatForever::create(RotateBy::create(1.0f,180)));

	//中间比赛
	auto macth_kaishi = Sprite::createWithSpriteFrameName("match_word.png");
	macth_kaishi->setPosition(Vec2(controlBg->getContentSize().width/2,controlBg->getContentSize().height * 0.45));
	controlBg->addChild(macth_kaishi,100);

	macth_kaishi->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.25f,0.98),ScaleTo::create(0.25f,1.02),nullptr)));

	//跑马灯
	MP_paomadeng = Sprite::createWithSpriteFrameName("MP_paomadeng.png");
	MP_paomadeng->setPosition(Vec2(controlBg->getContentSize().width/2,controlBg->getContentSize().height * 0.45));
	controlBg->addChild(MP_paomadeng,100);

	//顶部
	auto topBg = Sprite::createWithSpriteFrameName("match_ppds.png");
	topBg->setPosition(Vec2(controlBg->getContentSize().width/2,controlBg->getContentSize().height));
	controlBg->addChild(topBg,100);

	//在线人数
	auto mp_zaixian = Sprite::createWithSpriteFrameName("match_renshu.png");
	mp_zaixian->setPosition(Vec2(controlBg->getContentSize().width*0.55,controlBg->getContentSize().height - 55));
	controlBg->addChild(mp_zaixian,100);

	sprintf(MP_tmpchar,"%d",init_renshu_num);
	RS_label = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
	RS_label->setScale(0.4);
    RS_label->setString("9999");
	RS_label->setPosition(Vec2(-RS_label->getContentSize().width * 0.3f,mp_zaixian->getContentSize().height/2));
	mp_zaixian->addChild(RS_label);

	//四个走马灯
	for(int i = 0; i < 4 ; i++)
	{
		/*auto zoumadeng = Sprite::createWithSpriteFrameName("HB_paodeng1.png");
		zoumadeng->setPosition(Vec2(203 + i%2 * 350,107 + i/2*216));
		controlBg->addChild(zoumadeng,100);

		if(i != GameHallLayer::player_pos)
		{
			auto pdA_M = AnimationCache::getInstance()->getAnimation("hb_paomadeng");
			pdA_M->setDelayPerUnit(0.2f);
			auto *  pdAnimate = Animate::create(pdA_M);
			zoumadeng->runAction(RepeatForever::create(pdAnimate)); 
		}*/
		init_robot(i);
	}
 
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MatchPlayer::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(MatchPlayer::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(MatchPlayer::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触摸
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

	scheduleUpdate();
	schedule(schedule_selector(MatchPlayer::updatePao),0.2f);
    return true;
}

void MatchPlayer::init_robot(int i)   //i = 1, 2, 3 分别代表1，2，3机器人
{
	//对手背景框
	auto robot_bg = Sprite::createWithSpriteFrameName("match_diren_k.png");
	robot_bg->setPosition(Vec2(238 + i%2 * 320,117 + i/2*196));
	controlBg->addChild(robot_bg,100);

	//头像框
	auto robot_trx_k = Sprite::createWithSpriteFrameName("manquan.png");
	robot_trx_k->setPosition(Vec2(0 ,robot_bg->getContentSize().height/2));
	robot_bg->addChild(robot_trx_k,10);
 
	if(i>0)
	{
		//名字框
		auto robot_mz_k = Sprite::createWithSpriteFrameName("match_diren_mzk.png");
		robot_mz_k->setPosition(Vec2(100 ,robot_bg->getContentSize().height/2));
		robot_bg->addChild(robot_mz_k,10);

		auto robot_heidi = Sprite::createWithSpriteFrameName("match_tx_heidi.png");
		robot_heidi->setPosition(Vec2(0 ,robot_bg->getContentSize().height/2));
		robot_bg->addChild(robot_heidi);

		auto stencil = Sprite::createWithSpriteFrameName("match_tx_heidi.png");
		auto clipper = ClippingNode::create();
		clipper->setStencil(stencil);//设置裁剪模板 //3
		clipper->setInverted(false);//设置底板不可见
		clipper->setPosition(Vec2(robot_heidi->getContentSize()/2));
		clipper->setAlphaThreshold(0);//设置绘制底板的Alpha值为0
		robot_heidi->addChild(clipper);//4

		match_tx_tiao.at(i-1)->setPosition(Vec2(0,-clipper->getContentSize().height/2));
		clipper->addChild(match_tx_tiao.at(i-1));

		
		auto moveBy = MoveBy::create(0.5f,Vec2(0,-68 * 8));
		auto place = Place::create(Vec2(0,-clipper->getContentSize().height/2));

		match_tx_tiao.at(i-1)->runAction(RepeatForever::create(Sequence::create(moveBy,place,nullptr)));
 
		auto robot_mc_heidi = Sprite::createWithSpriteFrameName("match_mc_heidi.png");
		robot_mc_heidi->setPosition(Vec2(100 ,robot_bg->getContentSize().height/2));
		robot_bg->addChild(robot_mc_heidi);

		auto stencil1 = Sprite::createWithSpriteFrameName("match_mc_heidi.png");
		auto clipper1 = ClippingNode::create();
		clipper1->setStencil(stencil1);//设置裁剪模板 //3
		clipper1->setInverted(false);//设置底板可见
		clipper1->setPosition(Vec2(robot_mc_heidi->getContentSize()/2));
		clipper1->setAlphaThreshold(0);//设置绘制底板的Alpha值为0
		robot_mc_heidi->addChild(clipper1);//4

		match_mc_tiao.at(i-1)->setPosition(Vec2(0,16));
		clipper1->addChild(match_mc_tiao.at(i-1));

		auto moveBy1 = MoveBy::create(0.5f,Vec2(0,-33 * 9));
		auto place1 = Place::create(Vec2(0,-16));
		match_mc_tiao.at(i-1)->runAction(RepeatForever::create(Sequence::create(moveBy1,place1,nullptr)));
 
		//箭头
		match_jiantou.at(i-1)->setPosition(Vec2(robot_bg->getContentSize().width ,robot_bg->getContentSize().height/2));
		robot_bg->addChild(match_jiantou.at(i-1),10);

		auto rotate1 = RotateBy::create(0.05f,MP_jiantou_jd*0.5);
		auto rotate2 = RotateTo::create(0.01f,-MP_jiantou_jd);
		match_jiantou.at(i-1)->runAction(RepeatForever::create(Sequence::create(rotate1,rotate2,nullptr)));

		//火花执行动画
		/*match_huohua.at(i-1)->setPosition(Vec2(robot_bg->getContentSize().width - 20 ,robot_bg->getContentSize().height/2 - 13));
		robot_bg->addChild(match_huohua.at(i-1),10);

		auto huohua = AnimationCache::getInstance()->getAnimation("hh_baoming");
		auto huohua_A = Animate::create(huohua);
		match_huohua.at(i-1)->runAction(RepeatForever::create(huohua_A));*/
	}else
	{
		auto spirteF = SpriteFrameCache::getInstance()->getSpriteFrameByName("match_player_k.png");

		robot_bg->setDisplayFrame(spirteF);

		int tx_n = UserDefault::getInstance()->getIntegerForKey("player_touxiang");
		sprintf(MP_tmpchar,"tou%d.png",tx_n);
		auto player_toux = Sprite::createWithSpriteFrameName(MP_tmpchar);
		player_toux->setScale(68.0f/270.0f);
		player_toux->setPosition(Vec2(0 ,robot_bg->getContentSize().height/2));
		robot_bg->addChild(player_toux,9);

		auto player_name = LabelTTF::create(UserDefault::getInstance()->getStringForKey("player_name"),GameHallLayer::wordKind,16);
		player_name->setPosition(Vec2(104 ,robot_bg->getContentSize().height/2));
		robot_bg->addChild(player_name,10);
	}
 
	if(GameHallLayer::robot1[0] == 0 && i == 1)
	{
		robot_bg->setPosition(Vec2(238 ,117 + i/2*196));
	}

	if(GameHallLayer::player_pos == 1 && i == 0)
	{
		robot_bg->setPosition(Vec2(558 ,117 + i/2*196));
	}
}

void MatchPlayer::update(float dt)
{
	MP_time_num[0] += dt;
	MP_time_num[1] += dt;
	MP_time_num[2] += dt;
	MP_renshu_tmp += dt;
	//r
	if(MP_renshu_tmp <= MatchTimeTotal)
	{
		MP_renshu_sl_total += MP_renshu_sl;
		sprintf(MP_tmpchar,"%d",(int)(init_renshu_num + MP_renshu_sl_total));
		RS_label->setString(MP_tmpchar);
	}

	if(MP_time_num[0] <= MatchTimeTotal  && MP_time_num[0] > MatchTimeTotal - 1.0f)
	{
		if(!is_jiansu_flag[0])
		{
			cocos2d::log("dao le 3 miao");
			is_jiansu_flag[0] = true;
			tx_restart(0);
		}else
		{	//开始减速
			tx_jiansu(0);
		}
	}
	if(MP_time_num[1] <= MatchTimeTotal  && MP_time_num[1] > MatchTimeTotal - 1.0f)
	{
		if(!is_jiansu_flag[1])
		{
			cocos2d::log("dao le 3 miao");
			is_jiansu_flag[1] = true;
			tx_restart(1);
		}else
		{	//开始减速
			tx_jiansu(1);
		}
	}
	if(MP_time_num[2] <= MatchTimeTotal  && MP_time_num[2] > MatchTimeTotal - 1.0f)
	{
		if(!is_jiansu_flag[2])
		{
			cocos2d::log("dao le 3 miao");
			is_jiansu_flag[2] = true;
			tx_restart(2);
		}else
		{	//开始减速
			tx_jiansu(2);
		}
	}
	if(MP_time_num[0] > MatchTimeTotal)
	{
		is_jiansu_flag[0] = false;

		match_jiantou.at(0)->stopAllActions();
		match_jiantou.at(0)->setRotation(0);
		match_tx_tiao.at(0)->stopAllActions();
		match_tx_tiao.at(0)->setPosition(Vec2(0,-34 - 68*7));
		match_mc_tiao.at(0)->stopAllActions();
		match_mc_tiao.at(0)->setPosition(Vec2(0,-16 - 33*9));

	}
	if(MP_time_num[1] > MatchTimeTotal)
	{
		is_jiansu_flag[1] = false;

		match_jiantou.at(1)->stopAllActions();
		match_jiantou.at(1)->setRotation(0);
		match_tx_tiao.at(1)->stopAllActions();
		match_tx_tiao.at(1)->setPosition(Vec2(0,-34 - 68*7));
		match_mc_tiao.at(1)->stopAllActions();
		match_mc_tiao.at(1)->setPosition(Vec2(0,-16 - 33*9));
	}
	if(MP_time_num[2] > MatchTimeTotal)
	{
		is_jiansu_flag[2] = false;
		match_jiantou.at(2)->stopAllActions();
		match_jiantou.at(2)->setRotation(0);
		match_tx_tiao.at(2)->stopAllActions();
		match_tx_tiao.at(2)->setPosition(Vec2(0,-34 - 68*7));
		match_mc_tiao.at(2)->stopAllActions();
		match_mc_tiao.at(2)->setPosition(Vec2(0,-16 - 33*9));
		//进入场景
		scheduleOnce(schedule_selector(MatchPlayer::jinru_bs),1.0f);
	}
}

void MatchPlayer::tx_restart(int i)
{
	match_jiantou.at(i)->stopAllActions();
	match_jiantou.at(i)->setRotation(-MP_jiantou_jd);
	auto rotate1 = RotateBy::create(0.2f,MP_jiantou_jd*0.5);
	auto rotate2 = RotateTo::create(0.05f,-MP_jiantou_jd);
	match_jiantou.at(i)->runAction(Repeat::create(Sequence::create(rotate1,rotate2,nullptr),4));

	match_tx_tiao.at(i)->stopAllActions();
	match_tx_tiao.at(i)->setPosition(Vec2(0,-34));
	match_mc_tiao.at(i)->stopAllActions();
	match_mc_tiao.at(i)->setPosition(Vec2(0,-16));
}

void MatchPlayer::jinru_bs(float dt)
{
	this->stopAllActions();
	this->removeAllChildrenWithCleanup(true);
	this->unscheduleAllSelectors();
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
    
	GameScene::cGameType = 1;
    
    GameBegin::removeSouce(1);

	auto scene = LoadRes::createScene();	
	Director::getInstance()->replaceScene(scene);  
	 

}

void MatchPlayer::updatePao(float dt)
{
	if(MP_paomadeng->isFlippedY())
	{
		MP_paomadeng->setFlippedY(false);
	}else
	{
		MP_paomadeng->setFlippedY(true);
	}
}

void MatchPlayer::tx_jiansu(int i)
{
	//头像减速过程
	tx_lucheng[i] -= tx_v1[i];	//行驶的总路程
	tx_v1[i] -= tx_a[i];			//此时的速率

	//cocos2d::log("sudu v1 = %f , s = %f " , tx_v1 , tx_lucheng);

	match_tx_tiao.at(i)->setPosition(Vec2(0,tx_lucheng[i]));

	//名称减速过程
	mc_lucheng[i] -= mc_v1[i];	//行驶的总路程
	mc_v1[i] -= mc_a[i];			//此时的速率

	//cocos2d::log("sudu v1 = %f , s = %f " , mc_v1 , mc_lucheng);

	match_mc_tiao.at(i)->setPosition(Vec2(0,mc_lucheng[i]));
 
}

void MatchPlayer::exit()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameHall/gameHall3.plist","gameHall/gameHall3.png");
	GameBegin::buttonSound();
	GameBegin::stopMusic();
	GameBegin::playMusic("bgmusic.mp3",4);
	this->removeAllChildren();
	this->removeFromParentAndCleanup(true);
	GameHallLayer::is_bs_xianshi= true;
}
  
bool MatchPlayer::onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	log("touchedBegan");
	return true;
}

void MatchPlayer::onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	log("touchesMoved");
}

void MatchPlayer::onTouchEnded(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	log("touchesEnded");
}
