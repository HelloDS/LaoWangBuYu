#include "ZuanPan.h" 
#include "GameScene.h"
#include "CannonLayer.h"
#include "Gongxi.h"
#include "GameBegin.h"
#include <math.h>

USING_NS_CC; 

ZuanPan * ZuanPan::create( int roomNum )
{
	ZuanPan * lvup = new ZuanPan();
	lvup->init( roomNum );
	lvup->autorelease();
	return lvup;
}

bool ZuanPan::init( int roomNum )
{  
	if ( !Layer::init() )	
	{
		return false;
	}

	zuanpan = NULL;

    if(roomNum > 9999)
    {
        zuanpanNum[0] =  (int)roomNum *0.10 ;
        zuanpanNum[1] =  (int)roomNum *0.15 ;
        zuanpanNum[2] =  (int)roomNum *0.20 ;
        zuanpanNum[3] =  (int)roomNum *0.25 ;
        zuanpanNum[4] =  (int)roomNum *0.30 ;
        zuanpanNum[5] =  (int)roomNum *0.35 ;
        zuanpanNum[6] =  (int)roomNum *0.40 ;
        zuanpanNum[7] =  (int)roomNum;
    }
    else
    {
        zuanpanNum[0] = 100 ;
        zuanpanNum[1] = 300 ;
        zuanpanNum[2] = 500 ;
        zuanpanNum[3] = 1000;
        zuanpanNum[4] = 10 ;
        zuanpanNum[5] = 50;
        zuanpanNum[6] = 100 ;
        zuanpanNum[7] = 300;
        
        roomBeilv = roomNum;
        
        for(int i = 0 ; i < 8 ; i++)
        {
            zuanpanNum[i] = zuanpanNum[i] * roomBeilv;
        }
    }
	

	auto zheZhao = LayerColor::create(ccc4(0,0,0,170),1024,768);
 	zheZhao->setPosition(Point::ZERO);
	zheZhao->setScale(2.0f);
	this->addChild(zheZhao);

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
	listener->onTouchBegan = CC_CALLBACK_2(ZuanPan::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(ZuanPan::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(ZuanPan::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触�?
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

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
		numLabel->setPosition(Vec2(zuanpanR + 0.85*zuanpanR * sin((22.5 + i*45)*3.14/180),zuanpanR + 0.85*zuanpanR * cos((22.5 + i*45)*3.14/180)));
		zuanpan->addChild(numLabel);
		numLabel->setString(tmpNum);
		numLabel->setRotation(22.5 + i*45 );

		//金币或钻石
		Sprite * jinbiTag;
		if(i<4)
		{
            
            jinbiTag = Sprite::createWithSpriteFrameName("yubi.png");
            
			
		}else
		{
            if(roomNum > 9999)
            {
                jinbiTag = Sprite::createWithSpriteFrameName("yubi.png");
            }
            else
            {
                jinbiTag = Sprite::createWithSpriteFrameName("diamond.png");
            }
            
		}
		jinbiTag->setPosition(Vec2(zuanpanR + 0.7*zuanpanR * sin((22.5 + i*45)*3.14/180),zuanpanR + 0.7*zuanpanR * cos((22.5 + i*45)*3.14/180)));
		zuanpan->addChild(jinbiTag);
		jinbiTag->setRotation(22.5 + i*45 );
		
	}

	//侧边 金币和钻石
    if(roomNum > 9999)
    {
        
    }
    else
    {
        auto zuanshiT = Sprite::createWithSpriteFrameName("diamond.png");
        zuanshiT->setPosition(Vec2(zpBG->getContentSize().width,zpBG->getContentSize().height));
        zpBG->addChild(zuanshiT);
        
        zuanshiNum = Label::createWithCharMap("img/zpwenzi.png",20,23,'0');
        zuanshiNum->setPosition(Vec2(zuanshiT->getContentSize().width * 1.5,zuanshiT->getContentSize().height/2));
        zuanshiNum->setAnchorPoint(Vec2(0,0.5));
        zuanshiNum->setString("0");
        zuanshiT->addChild(zuanshiNum);
    }
	

	auto jinbiT = Sprite::createWithSpriteFrameName("yubi.png");
	jinbiT->setPosition(Vec2(zpBG->getContentSize().width*1,zpBG->getContentSize().height*0.9));
	zpBG->addChild(jinbiT);

	jinbiNum = Label::createWithCharMap("img/zpwenzi.png",20,23,'0');
	jinbiNum->setPosition(Vec2(jinbiT->getContentSize().width * 1.5,jinbiT->getContentSize().height/2));
	jinbiNum->setAnchorPoint(Vec2(0,0.5));
	jinbiNum->setString("0");
	jinbiT->addChild(jinbiNum);

	//灯笼
	auto denglong = Sprite::createWithSpriteFrameName("zpshang.png");
	denglong->setPosition(Vec2(zpBG->getContentSize().width*0.5,zpBG->getContentSize().height*0.43+5));
	zpBG->addChild(denglong);

	//开始按钮
	auto beginAN = Sprite::createWithSpriteFrameName("zpanniu.png");
	auto beginAN_d = Sprite::createWithSpriteFrameName("zpanniu_d.png");
    
    if(roomNum > 9999)
    {
        beginItem = MenuItemSprite::create(beginAN,beginAN_d,CC_CALLBACK_1(ZuanPan::beginmatchover,this));
    }
    else
    {
        beginItem = MenuItemSprite::create(beginAN,beginAN_d,CC_CALLBACK_1(ZuanPan::beginZ,this));
    }
    
	
	auto beginMenu = Menu::create(beginItem,nullptr);
	beginMenu->setPosition(Vec2(zpBG->getContentSize().width/2,zpBG->getContentSize().height/2));
	zpBG->addChild(beginMenu);

	 return true;
}

void ZuanPan::beginZ(Ref * pSender) 
{
	GameBegin::buttonSound();
	//开始钻盘
	if(!isZuanDong)
	{
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
		if(randomI<=10)//100鱼币
		{
			zpZongDu += 25;
			jiangliNum = zuanpanNum[0];
			isJinbi = true;
			xuhao = 1;
 
		}		
		else if(randomI<=30)//300鱼币
		{
			zpZongDu +=  25 + 45*1;
			jiangliNum = zuanpanNum[1];
			isJinbi = true;
			xuhao = 2;
			maxJiaSuZhen -= 1;
		}
		else if(randomI<=40)//500鱼币
		{
			zpZongDu += 25 + 45*2;
			jiangliNum = zuanpanNum[2];
			isJinbi = true;
			xuhao = 3;
			maxJiaSuZhen += 2;
		}
		else if(randomI<=45)//1000鱼币
		{
			zpZongDu += 25 + 45*3;
			jiangliNum = zuanpanNum[3];
			isJinbi = true;
			xuhao = 4;
			maxJiaSuZhen +=4;
		}
		else if(randomI<=55)//10钻石
		{
			zpZongDu +=25 + 45*4;
			jiangliNum = zuanpanNum[4];
			isJinbi = false;
			xuhao = 5;
			maxJiaSuZhen += 6;
		}
		else if(randomI<=80)//50钻石
		{
			zpZongDu +=25 + 45*5;
			jiangliNum = zuanpanNum[5];
			isJinbi = false;
			xuhao = 6;
			maxJiaSuZhen += 9;
		}
		else if(randomI<=95)//100钻石
		{
			zpZongDu +=25 + 45*6;
			jiangliNum = zuanpanNum[6];
			isJinbi = false;
			xuhao = 7;
			maxJiaSuZhen += 11;
		}
		else//300钻石
		{
			zpZongDu +=25 + 45*7 ;
			jiangliNum = zuanpanNum[7];
			isJinbi = false;
			xuhao = 8;
			maxJiaSuZhen += 13;
		}
		cocos2d::log("jiangli %d",xuhao);
		this->scheduleUpdate();
		GameBegin::playSound("zuanpan.mp3");
	}
}


void ZuanPan::beginmatchover(Ref * pSender)
{
    GameBegin::buttonSound();
    //开始钻盘
    if(!isZuanDong)
    {
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
        if(randomI<=26)//100鱼币
        {
            zpZongDu += 25;
            jiangliNum = zuanpanNum[0];
            isJinbi = true;
            xuhao = 1;
            
        }
        else if(randomI<=51)//300鱼币
        {
            zpZongDu +=  25 + 45*1;
            jiangliNum = zuanpanNum[1];
            isJinbi = true;
            xuhao = 1;
            maxJiaSuZhen -= 1;
        }
        else if(randomI<=61)//500鱼币
        {
            zpZongDu += 25 + 45*2;
            jiangliNum = zuanpanNum[2];
            isJinbi = true;
            xuhao = 2;
            maxJiaSuZhen += 2;
        }
        else if(randomI<=71)//1000鱼币
        {
            zpZongDu += 25 + 45*3;
            jiangliNum = zuanpanNum[3];
            isJinbi = true;
            xuhao = 2;
            maxJiaSuZhen +=4;
        }
        else if(randomI<=81)//10钻石
        {
            zpZongDu +=25 + 45*4;
            jiangliNum = zuanpanNum[4];
            isJinbi = true;
            xuhao = 3;
            maxJiaSuZhen += 6;
        }
        else if(randomI<=91)//50钻石
        {
            zpZongDu +=25 + 45*5;
            jiangliNum = zuanpanNum[5];
            isJinbi = true;
            xuhao = 3;
            maxJiaSuZhen += 9;
        }
        else if(randomI<=100)//100钻石
        {
            zpZongDu +=25 + 45*6;
            jiangliNum = zuanpanNum[6];
            isJinbi = true;
            xuhao = 4;
            maxJiaSuZhen += 11;
        }
        else//300钻石
        {
            zpZongDu +=25 + 45*7 ;
            jiangliNum = zuanpanNum[7];
            isJinbi = true;
            xuhao = 4;
            maxJiaSuZhen += 13;
        }
        cocos2d::log("jiangli %d",xuhao);
        this->scheduleUpdate();
        GameBegin::playSound("zuanpan.mp3");
    }
}
void ZuanPan::update(float dt) 
{
	if(zpJiaoDu < zpZongDu)
	{
		cocos2d::log("jiaodu = %f",zpJiaoDu);
		zuanpan->setRotation(-zpJiaoDu);//设置转盘的角度
		zpJiaoDu += zptmp;//到现在位置转动的角度
		if(isjiasu)//加速过程
		{
			if(jiasuZhen >= maxJiaSuZhen)
			{
				isjiasu = false;
			}

			cocos2d::log("jisu");
			zptmp = 20;
			jiasuZhen++;
			
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

		//开始按钮可以点击
		//beginItem->setEnabled(true);
		//beginItem->unselected();

		//修改奖励标签并弹出恭喜框
		char tmpnum[10];
		sprintf(tmpnum,"%d",jiangliNum);
		char jiangliTmp[100];
		sprintf(jiangliTmp,"zhuanpan_%d",xuhao);
		
		if(isJinbi)
		{
			jinbiNum->setString(tmpnum);
			CannonLayer::GameCoinRefresh(jiangliNum);			
		}else
		{
			zuanshiNum->setString(tmpnum);
			CannonLayer::GameCoinZuanshi(jiangliNum);			
		}
		
		auto layer = this->getParent();
		char charTmp[100];
		sprintf(charTmp,GAME_DATA_STRING(jiangliTmp),jiangliNum);
		//弹出恭喜框
		auto gongxi = Gongxi::create(1,charTmp);
		layer->addChild(gongxi,MENULAYER);
		this->scheduleOnce(schedule_selector(ZuanPan::exit),3.5f);
 
	}
}

void ZuanPan::exit(float dt)
{
	//移除转盘
    CannonLayer::zuanpanover = 1;
	this->removeFromParent();
}

bool ZuanPan::onTouchBegan(Touch* touch, Event* event) 
{ 

	return true;
}

void ZuanPan::onTouchMoved(Touch* touch, Event* event) 
{

}

void ZuanPan::onTouchEnded(Touch* touch, Event* event)
{

}
