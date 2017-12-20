#include "smShop.h" 
#include "GameHallLayer.h"
#include "GameBegin.h"
#include "Gongxi.h"
#include "GameData.h"
#include <math.h>

USING_NS_CC; 
Scene * smShop::createScene(int roomNum)
{
	auto scene = Scene::create();
	auto layer = smShop::create(roomNum);
	scene->addChild(layer);
	return scene;
}

smShop * smShop::create( int roomNum )
{
	smShop * lvup = new smShop();
	lvup->init( roomNum );
	lvup->autorelease();
	return lvup;
}

bool smShop::init( int roomNum )
{  
	if ( !Layer::init() )	
	{
		return false;
	}

	zuanpanNum[0] = 500 ;
	zuanpanNum[1] = 100000;
	zuanpanNum[2] = 1000 ;
	zuanpanNum[3] = 50000 ;
	zuanpanNum[4] = 2000 ;
	zuanpanNum[5] = 20000;
	zuanpanNum[6] = 5000;
	zuanpanNum[7] = 8000 ;
 
	roomBeilv = roomNum;

	for(int i = 0 ; i < 8 ; i++)
	{
		zuanpanNum[i] = zuanpanNum[i] * roomBeilv;
	}

	/*auto zheZhao = LayerColor::create(ccc4(0,0,0,170),1024,768);
 	zheZhao->setPosition(Point::ZERO);
	zheZhao->setScale(2.0f);
	this->addChild(zheZhao);
 */
	//动态出现
	this->setScale(0.7);
	CCScaleTo *ac8=CCScaleTo::create(0.5f, 1.0f);  
	auto action =  EaseExponentialOut::create(ac8);
	this->runAction(action);

	visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();

	isZuanDong = false;
	zpJiaoDu = 1.0f;	
	zptmp = 0.0f;
	isjiasu = true;
	jiasuZhen = 0;

	jiangliNum = 0;
	isJinbi = true;

	//设定随机种子
	srand((unsigned)time(NULL));

	
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(smShop::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(smShop::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(smShop::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触�?
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	auto hallBackground = Sprite::create("hall_BG.png");
	hallBackground->setPosition(Point(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
	this->addChild(hallBackground);

	//转盘底部
	auto zpBG = Sprite::createWithSpriteFrameName("zpBG.png");
	zpBG->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y + visibleSize.height/2));
	addChild(zpBG);

	//财神爷
	auto caishen = Sprite::createWithSpriteFrameName("zpcaishen.png");
	caishen->setPosition(Vec2(zpBG->getContentSize().width*0.225,zpBG->getContentSize().height*0.94));
	zpBG->addChild(caishen);

	//转盘
	zuanpan = Sprite::createWithSpriteFrameName("zpzhong.png");
	zuanpan->setPosition(Vec2(zpBG->getContentSize().width*0.5,zpBG->getContentSize().height*0.5));
	zpBG->addChild(zuanpan);

	//转盘上的数字
	float zuanpanR = zuanpan->getContentSize().width/2;
	for(int i =0 ; i< 8 ; i++)
	{
		//数字
		char tmpNum[10];
		sprintf(tmpNum,"%d",zuanpanNum[i]);
		auto numLabel = Label::createWithCharMap("img/zpwenzi.png",20,23,'0');
		numLabel->setPosition(Vec2(zuanpanR + 0.8*zuanpanR * sin((22.5 + i*45)*3.14/180),zuanpanR + 0.8*zuanpanR * cos((22.5 + i*45)*3.14/180)));
		zuanpan->addChild(numLabel);
		numLabel->setString(tmpNum);
		numLabel->setRotation(22.5 + i*45 );

		//金币或钻石
		Sprite * jinbiTag;
		jinbiTag = Sprite::createWithSpriteFrameName("yubi.png");
		jinbiTag->setPosition(Vec2(zuanpanR + 0.65*zuanpanR * sin((22.5 + i*45)*3.14/180),zuanpanR + 0.65*zuanpanR * cos((22.5 + i*45)*3.14/180)));
		zuanpan->addChild(jinbiTag);
        jinbiTag->setScale(0.8f);
		jinbiTag->setRotation(22.5 + i*45 );
		
	}

	//侧边 金币和钻石
	auto zuanshiT = Sprite::createWithSpriteFrameName("diamond.png");
	zuanshiT->setPosition(Vec2(zpBG->getContentSize().width,zpBG->getContentSize().height));
	zpBG->addChild(zuanshiT);

	zuanshiNum = Label::createWithCharMap("img/zpwenzi.png",20,23,'0');
	zuanshiNum->setPosition(Vec2(zuanshiT->getContentSize().width * 1.5,zuanshiT->getContentSize().height/2));
	zuanshiNum->setAnchorPoint(Vec2(0,0.5));
	char zsTmp[50];
	sprintf(zsTmp,"%d",GameBegin::getFileData("jywopl.txt"));
	zuanshiNum->setString(zsTmp);
	zuanshiT->addChild(zuanshiNum);

	auto jinbiT = Sprite::createWithSpriteFrameName("yubi.png");
	jinbiT->setPosition(Vec2(zpBG->getContentSize().width*1,zpBG->getContentSize().height*0.9));
	zpBG->addChild(jinbiT);

	jinbiNum = Label::createWithCharMap("img/zpwenzi.png",20,23,'0');
	jinbiNum->setPosition(Vec2(jinbiT->getContentSize().width * 1.5,jinbiT->getContentSize().height/2));
	jinbiNum->setAnchorPoint(Vec2(0,0.5));

	char jinbiTmp[50];
	sprintf(jinbiTmp,"%d",GameBegin::getFileData("jywer.txt"));
	jinbiNum->setString(jinbiTmp);
	jinbiT->addChild(jinbiNum);

	//灯笼
	auto denglong = Sprite::createWithSpriteFrameName("zpshang.png");
	denglong->setPosition(Vec2(zpBG->getContentSize().width*0.5,zpBG->getContentSize().height*0.43+5));
	zpBG->addChild(denglong);

	//开始按钮
	auto beginAN = Sprite::createWithSpriteFrameName("zpanniu.png");
	auto beginAN_d = Sprite::createWithSpriteFrameName("zpanniu_d.png");
	beginItem = MenuItemSprite::create(beginAN,beginAN_d,CC_CALLBACK_1(smShop::beginZ,this));
	auto beginMenu = Menu::create(beginItem,nullptr);
	beginMenu->setPosition(Vec2(zpBG->getContentSize().width/2,zpBG->getContentSize().height/2));
	zpBG->addChild(beginMenu);

	 return true;
}

void smShop::beginZ(Ref * pSender) 
{
	GameBegin::buttonSound();
	//开始钻盘
	if(!isZuanDong)
	{
		if(roomBeilv == 10)
		{
			int zsTmpi = GameBegin::getFileData("jywopl.txt") -  500;
			if(zsTmpi < 0)
			{
				auto layer = this->getParent();
				auto gongxi = Gongxi::create(2,GAME_DATA_STRING("gamehall_zuanshi_low"));
			    layer->addChild(gongxi,1000);

				this->removeFromParent();
				return;
			}
			char zsTmp[50];
			sprintf(zsTmp,"%d",zsTmpi);
			zuanshiNum->setString(zsTmp);
			 GameBegin::setFileData("jywopl.txt",zsTmpi);
			
		}
		if(roomBeilv == 1)
		{
			UserDefault::getInstance()->setBoolForKey("leijichongzhi0",true);
		}
		//开始按钮不能点，转动标识true
		beginItem->selected();
		beginItem->setEnabled(false);
		isZuanDong = true;	
		isjiasu = true;

		//得到转动的起始角度及所要转动的总角度大小
		zpJiaoDu = 0.0f;
		zptmp = 0.0f;
		jiasuZhen = 0;
		
		int randomI = CCRANDOM_0_1() * 100;
		zpZongDu = 3600 - 357;
		maxJiaSuZhen = 105;
        if(randomI<=45)//100鱼币
        {
            zpZongDu += 25;
            jiangliNum = zuanpanNum[0];
            isJinbi = true;
            xuhao = 1;
        }
        else if(randomI<=75)//300鱼币
        {
            zpZongDu += 25 + 45*2;
            jiangliNum = zuanpanNum[2];
            isJinbi = true;
            xuhao = 3;
            maxJiaSuZhen +=2;
        }
        else if(randomI<=90)//500鱼币
        {
            zpZongDu += 25 + 45*4;
            jiangliNum = zuanpanNum[4];
            isJinbi = false;
            xuhao = 5;
            maxJiaSuZhen +=6;
        }
        else if(randomI<=98)//1000鱼币
        {
            zpZongDu += 25 + 45*6;
            jiangliNum = zuanpanNum[6];
            isJinbi = false;
            xuhao = 7;
            maxJiaSuZhen +=11;
        }
        else if(randomI<=100)//10钻石
        {
            zpZongDu += 25 + 45*7 ;
            jiangliNum = zuanpanNum[7];
            isJinbi = false;
            xuhao = 8;
            maxJiaSuZhen +=13;
        }
        else if(randomI<=101)//50钻石
        {
            zpZongDu += 25 + 45*5;
            jiangliNum = zuanpanNum[5];
            isJinbi = false;
            xuhao = 6;
            maxJiaSuZhen +=9;
        }
        else if(randomI<=102)//100钻石
        {
            zpZongDu += 25 + 45*3;
            jiangliNum = zuanpanNum[3];
            isJinbi = true;
            xuhao = 4;
            maxJiaSuZhen +=4;
        }
        else//300钻石
        {
            zpZongDu +=  25 + 45*1;
            jiangliNum = zuanpanNum[1];
            isJinbi = true;
            xuhao = 2;
            maxJiaSuZhen -= 1;			
        }
		this->scheduleUpdate();
		GameBegin::playSound("zuanpan.mp3");
	}
}

void smShop::update(float dt) 
{
	if(zpJiaoDu < zpZongDu)
	{
		//cocos2d::log("jiaodu = %f",zpJiaoDu);
		zuanpan->setRotation(-zpJiaoDu);//设置转盘的角度
		zpJiaoDu += zptmp;//到现在位置转动的角度
		if(isjiasu)//加速过程
		{
			if(jiasuZhen >= maxJiaSuZhen)
			{
				isjiasu = false;
			}
			/*if(zptmp<=3)
			{
				zptmp += 0.03f;
			}else
			{
				zptmp += 0.7f;
			}
			if(zptmp>=20)
			{*/
				cocos2d::log("jiaodu = %f",zpJiaoDu);
				zptmp = 20;
				jiasuZhen++;
			//}
		}else//减速过程
		{
			
			if(zptmp < 0.5f)
			{
				zptmp -= 0.001f;
			}
			else if(zptmp < 5)
			{
				zptmp -= 0.02f;
			}
			else if(zptmp < 10)
			{
				zptmp -= 0.1f;
			}
			else if(zptmp < 15)
			{
				zptmp -= 0.5f;
			}
			else
			{
				zptmp -= 1.0f;
			}
		}
	}else
	{
		//结束转动
		this->unscheduleUpdate();
		isZuanDong = false;


		//修改奖励标签并弹出恭喜框
		char tmpnum[30];
		sprintf(tmpnum,"%d",GameBegin::getFileData("jywer.txt") + jiangliNum);
		jinbiNum->setString(tmpnum);

		GameBegin::setFileData("jywer.txt",GameBegin::getFileData("jywer.txt") + jiangliNum);
 
		char charTmp[100];
		sprintf(charTmp,GAME_DATA_STRING("mission_b"),jiangliNum);

		//弹出恭喜框
		auto gongxi = Gongxi::create(4,charTmp);
		addChild(gongxi, 1000);

		this->scheduleOnce(schedule_selector(smShop::exit),2.5f);

	}
}

void smShop::exit(float dt)
{
	//移除转盘
 
	auto scene = GameHallLayer::createScene();
	Director::getInstance()->replaceScene(scene);
	//this->removeFromParent();
}

bool smShop::onTouchBegan(Touch* touch, Event* event) 
{ 

	return true;
}

void smShop::onTouchMoved(Touch* touch, Event* event) 
{

}

void smShop::onTouchEnded(Touch* touch, Event* event)
{

}
