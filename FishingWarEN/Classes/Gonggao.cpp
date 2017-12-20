#include "GameData.h"
#include "Gonggao.h"

Gonggao * Gonggao::create(int i)
{
	Gonggao * mission = new Gonggao();
	mission->init(i);
	mission->autorelease();
	return mission;
}


bool Gonggao::init(int i)
{
    
	if ( !Node::init() )	
	{
		return false;
	}
	//srand((unsigned)time(NULL));
	auto gonggao_bg = Sprite::createWithSpriteFrameName("gonggao_bg.png");
	addChild(gonggao_bg);

	auto gonggao_bg_guang1 = Sprite::createWithSpriteFrameName("gonggao_bg_guang.png");
	gonggao_bg_guang1->setPosition(Vec2(gonggao_bg->getContentSize().width * 0.2 , gonggao_bg->getContentSize().height));
	gonggao_bg->addChild(gonggao_bg_guang1,10);
	gonggao_bg_guang1->runAction(MoveBy::create(10,Vec2(gonggao_bg->getContentSize().width * 0.6,0)));

	auto gonggao_bg_guang2 = Sprite::createWithSpriteFrameName("gonggao_bg_guang.png");
	gonggao_bg_guang2->setPosition(Vec2(gonggao_bg->getContentSize().width * 0.8 , gonggao_bg->getContentSize().height * 0));
	gonggao_bg->addChild(gonggao_bg_guang2,10);
	gonggao_bg_guang2->runAction(MoveBy::create(10,Vec2(-gonggao_bg->getContentSize().width * 0.6,0)));

	/*auto sajinbi = ParticleSystemQuad::create("zm_huang.plist");
	auto batch = ParticleBatchNode::createWithTexture(sajinbi->getTexture()); 
	batch->addChild(sajinbi); 
	gonggao_bg->addChild(batch,100); 
	sajinbi->setPosition(Point(gonggao_bg->getContentSize().width/2,gonggao_bg->getContentSize().height/2));
	sajinbi->resetSystem();*/

	auto stencil11 = Sprite::createWithSpriteFrameName("gonggao_clip.png");
	auto clipper11 = ClippingNode::create();
	clipper11->setStencil(stencil11);//设置裁剪模板 //3
	clipper11->setInverted(false);//设置底板不可见
	//clipper->setAnchorPoint(Vec2(0.5,0.5));
	clipper11->setPosition(Vec2(gonggao_bg->getContentSize().width/2+ 13 ,gonggao_bg->getContentSize().height/2));
	clipper11->setContentSize(gonggao_bg->getContentSize());
	clipper11->setAlphaThreshold(0);//设置绘制底板的Alpha值为0
	gonggao_bg->addChild(clipper11);//4
 
	//label
	char tmpchar[200];
	//随机名称 robotNName1 - 3000
    int nameid = CCRANDOM_0_1() * 499;
    
    
	sprintf(tmpchar,"robotNName%d",nameid);

	game_label = RichText::create();
	game_label->setAnchorPoint(Vec2(0.5,0.5));
	game_label->setPosition(Vec2(clipper11->getContentSize().width * 1.2,clipper11->getContentSize().height * 0.05));
	clipper11->addChild(game_label);

	auto moveby1 = MoveBy::create(15,Vec2(-clipper11->getContentSize().width * 2.2,0));
	game_label->runAction(RepeatForever::create(Sequence::create(moveby1,CCCallFunc::create([&](){this->removeFromParentAndCleanup(true);
    }),nullptr)));

	auto re1 = RichElementText::create(1,Color3B(131,255,240), 255, GAME_DATA_STRING(tmpchar),"minijianling.ttf", 28);
	game_label->pushBackElement(re1);

	if(i == 1)
	{
		//喇叭
		auto gonggao_lb = Sprite::createWithSpriteFrameName("gonggao_laba1.png");
		gonggao_lb->setPosition(Vec2(gonggao_bg->getContentSize().width * 0.05,gonggao_bg->getContentSize().height * 0.5));
		gonggao_bg->addChild(gonggao_lb,10);
		gonggao_lb->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.25f,0.9),ScaleTo::create(0.25f,0.8),nullptr)));

		std::string jiangli[4][3] = {"  20  ","  30000  ","  500  ","  50  ","  200000  ","  2000  ","  100  ","  300000  ","  3000  ","  300  ","  600000  ","  6000  "};
		Color3B colorV[4] = {Color3B::GREEN,Color3B(107,138,246),Color3B(163,75,177),Color3B(255,168,45)};
		//比赛房间
		int roomid = CCRANDOM_0_1() * 4 + 1;
		if(roomid == 5)
			roomid = 4;
		sprintf(tmpchar,"gonggao_balx_%d",roomid);
		//具体奖励
		auto re2 = RichElementText::create(1, Color3B::WHITE, 255, GAME_DATA_STRING("gonggao_zkh_3"), "minijianling.ttf", 28);
		auto re3 = RichElementText::create(1, colorV[roomid-1], 255, GAME_DATA_STRING(tmpchar), "minijianling.ttf", 28);
		auto re4 = RichElementText::create(1, Color3B::WHITE, 255, GAME_DATA_STRING("gonggao_zkh_4"), "minijianling.ttf", 28);
 
        auto re5 = RichElementText::create(1, Color3B::YELLOW, 255, jiangli[roomid-1][1], "Arial", 30);
		auto re6 = RichElementImage::create(1,Color3B::WHITE,255,"yubi.png");
		auto re7 = RichElementText::create(1, Color3B::YELLOW, 255, jiangli[roomid-1][2], "Arial", 30);
		auto re8 = RichElementImage::create(1,Color3B::WHITE,255,"diamond.png");
	//	auto re9 = RichElementText::create(1, Color3B::YELLOW, 255, jiangli[roomid-1][0], "Arial", 30);
	//	auto re10 = RichElementImage::create(1,Color3B::WHITE,255,"huafeiquan.png");
 
		game_label->pushBackElement(re2);game_label->pushBackElement(re3);game_label->pushBackElement(re4);
		game_label->pushBackElement(re5);game_label->pushBackElement(re6);game_label->pushBackElement(re7);
		game_label->pushBackElement(re8);
        
        if(UserDefault::getInstance()->getIntegerForKey("ios_dengluFlag") == 0)
        {
       //     game_label->pushBackElement(re9);
    //        game_label->pushBackElement(re10);

        }
        

	}else if(i == 2)
	{
		//喇叭
	/*	auto gonggao_lb = Sprite::createWithSpriteFrameName("gonggao_laba2.png");
		gonggao_lb->setPosition(Vec2(gonggao_bg->getContentSize().width * 0.05,gonggao_bg->getContentSize().height * 0.5));
		gonggao_bg->addChild(gonggao_lb,10);
		gonggao_lb->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.25f,0.9),ScaleTo::create(0.25f,0.8),nullptr)));

        
		//话费类型
		int huafei_gl = CCRANDOM_0_1() ;
        if(huafei_gl < 0.5) huafei_gl = 1;
		else if(huafei_gl < 0.8) huafei_gl = 2;
        else huafei_gl = 3;
		sprintf(tmpchar,"gonggao_hflx_%d",huafei_gl);

		auto re2 = RichElementText::create(1, Color3B::WHITE, 255, GAME_DATA_STRING("gonggao_zkh_5"), "minijianling.ttf", 28);
		auto re3 = RichElementText::create(1, Color3B::YELLOW, 255, GAME_DATA_STRING(tmpchar), "minijianling.ttf", 28);
		game_label->pushBackElement(re2);game_label->pushBackElement(re3);*/
	}else
	{
		//喇叭
		auto gonggao_lb = Sprite::createWithSpriteFrameName("gonggao_laba3.png");
		gonggao_lb->setPosition(Vec2(gonggao_bg->getContentSize().width * 0.05,gonggao_bg->getContentSize().height * 0.5));
		gonggao_bg->addChild(gonggao_lb,10);
		gonggao_lb->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.25f,0.9),ScaleTo::create(0.25f,0.8),nullptr)));


		auto re2 = RichElementText::create(1, Color3B::YELLOW, 255, GAME_DATA_STRING("gonggao_zkh_6"), "minijianling.ttf", 28);
		game_label->pushBackElement(re2);
	}

    return true;
}
