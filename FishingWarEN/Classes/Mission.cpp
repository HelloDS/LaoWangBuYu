#include "GameScene.h"
#include "GameData.h"
#include "CannonLayer.h"
#include "Mission.h"
#include "cocos2d.h"
#include "MissionSuc.h"
#include "ZuanPan.h"
#include "GameHallLayer.h"
#include "LogoLayer.h"

USING_NS_CC;


Mission * Mission::create()
{
	Mission * mission = new Mission();
	mission->init();
	mission->autorelease();
	return mission;
}


bool Mission::init()
{  
	if ( !Node::init() )	
	{
		return false;
	}
	cocos2d::log(" Mission::init() 1");
	srand((unsigned)time(NULL));
	isMissionIng = false;

	//»ŒŒÒ¥∞ø⁄**************
	//µ»µΩ»ŒŒÒµ±«∞µƒ÷÷¿‡∫ÕÕÍ≥…µƒ ˝¡ø
	missionNum = UserDefault::getInstance()->getIntegerForKey("missionNum");
	missionKind = UserDefault::getInstance()->getIntegerForKey("missionKind");
	fishKind = UserDefault::getInstance()->getIntegerForKey("fishKind");

	cocos2d::log(" Mission::init() 2");
	double testTIME =  UserDefault::getInstance()->getDoubleForKey("missionTime");
	cocos2d::log("fishKind = %d , missioNnum = %d , missionKind = %d",fishKind,missionNum,missionKind);
	cocos2d::log("testTIME = %f", testTIME);

/*	missionKind = 3;
	missionNum = 0;*/
	if(!missionNum&&!missionKind)
	{
		missionNum = 0;
		missionKind = 0;
		fishKind = 0;
		cocos2d::log("1 fishKind = %d , missioNnum = %d , missionKind = %d",fishKind,missionNum,missionKind);
	}
	if(!(missionNum>=1 && missionKind>= 3))
	{
		isMissionIng = true;

		char odd[50];
		sprintf(odd,"boss_low_odd_%d",GameHallLayer::RoomType + 1);

		char odd2[50];
		sprintf(odd2,"bljs_rate_%d",GAME_DATA_INT(odd));
		roomBeilv = (int)(GAME_DATA_INT(odd2)/100) + 1;

		time_t nowTime = LogoLayer::getTime();

		//±≥æ∞
		missionBG = Sprite::createWithSpriteFrameName("renwukuang1.png");
		addChild(missionBG);

		char tmpMission[50];
		scaleNum = 0.8;

		if((missionNum == 0 && missionKind == 0 )|| nowTime > UserDefault::getInstance()->getDoubleForKey("missionTime"))
		{
			//ÀÊª˙“ª∏ˆ”„”Œ∂Ø
			missionKind = 1;			
			missionNum = 0;
			fishKind = CCRANDOM_0_1()*11;
			sprintf(tmpMission,"%d/20",0);
            
            auto diamond = Sprite::createWithSpriteFrameName("diamond.png");
            diamond->setPosition(ccp(missionBG->getContentSize().width*0.275f,missionBG->getContentSize().height*0.25));
            diamond->setScale(0.55f);
            missionBG->addChild(diamond);
            diamond->setTag(11);

			char mis_tmp[50];
			sprintf(mis_tmp,GAME_DATA_STRING("mission_1"),30 * roomBeilv);
            sprintf(mis_tmp,":%d",30 * roomBeilv);
			missionB = LabelTTF::create(mis_tmp,GameHallLayer::wordKind,24);
			missionB->setPosition(Vec2(missionBG->getContentSize().width*0.5,missionBG->getContentSize().height*0.25));
			missionBG->addChild(missionB,100);

			UserDefault::getInstance()->setIntegerForKey("missionKind",1);
			UserDefault::getInstance()->setIntegerForKey("fishKind",fishKind);
			UserDefault::getInstance()->flush();
		}
		else
		{
			if(missionKind == 1)
			{
				//scaleNum = 0.7;
				sprintf(tmpMission,"%d/20",missionNum);

				char mis_tmp[50];
				sprintf(mis_tmp,GAME_DATA_STRING("mission_1"),30 * roomBeilv);
                sprintf(mis_tmp,":%d",30 * roomBeilv);

                
                
                auto diamond = Sprite::createWithSpriteFrameName("diamond.png");
                diamond->setPosition(ccp(missionBG->getContentSize().width*0.275f,missionBG->getContentSize().height*0.25));
                diamond->setScale(0.55f);
                missionBG->addChild(diamond);
                diamond->setTag(11);

				missionB = LabelTTF::create(mis_tmp,GameHallLayer::wordKind,24);
				missionB->setPosition(Vec2(missionBG->getContentSize().width*0.55f,missionBG->getContentSize().height*0.25));
				missionBG->addChild(missionB,100);
			}
			if(missionKind == 2)
			{
				scaleNum = 0.4;
				sprintf(tmpMission,"%d/10",missionNum);

				char mis_tmp[50];
				sprintf(mis_tmp,GAME_DATA_STRING("mission_2"),300 * roomBeilv);
                sprintf(mis_tmp,":%d",300 * roomBeilv);
                
                
                
                auto goldImg = Sprite::createWithSpriteFrameName("yubi.png");
                goldImg->setPosition(ccp(missionBG->getContentSize().width*0.275f,missionBG->getContentSize().height*0.25));
                goldImg->setScale(0.5f);
                missionBG->addChild(goldImg);
                goldImg->setTag(12);
                

				missionB = LabelTTF::create(mis_tmp,GameHallLayer::wordKind,24);
				missionB->setPosition(Vec2(missionBG->getContentSize().width*0.55,missionBG->getContentSize().height*0.25));
				missionBG->addChild(missionB,100);
			}
			if(missionKind == 3)
			{
				scaleNum = 0.3;
				sprintf(tmpMission,"%d/1",missionNum);

				missionB = LabelTTF::create(GAME_DATA_STRING("mission_3"),GameHallLayer::wordKind,20);
				missionB->setPosition(Vec2(missionBG->getContentSize().width*0.5,missionBG->getContentSize().height*0.25));
				missionBG->addChild(missionB,100);
                missionB->setScale(0.8f);
			}
			//µ±«∞ ˝¡øfishdeadnum
			
		}
		cocos2d::log("fishKind = %d , missioNnum = %d , missionKind = %d",fishKind,missionNum,missionKind);

		//ÀÊª˙“ª∏ˆ”„”Œ∂Ø
		char cTempAni[50];
		sprintf(cTempAni,"fish_animation_%d_%d",GameHallLayer::RoomType,fishKind); 
		Animation* fishAnimation1 = AnimationCache::getInstance()->getAnimation(cTempAni);
		Animate*  fishAnimate = Animate::create(fishAnimation1);
		fish = Sprite::create(); 
		missionBG->addChild(fish,100);
		fish->runAction(RepeatForever::create(fishAnimate)); 
		fish->setPosition(Vec2(missionBG->getContentSize().width*0.25,missionBG->getContentSize().height*0.71));
		fish->setRotation(90);
		fish->setScale(scaleNum);
		

		//µ±«∞ ˝¡øfishdeadnum
		missionLabel = LabelTTF::create(tmpMission,GameHallLayer::wordKind,24);
		missionLabel->setPosition(Vec2(missionBG->getContentSize().width*0.73,missionBG->getContentSize().height*0.71));
		missionBG->addChild(missionLabel,100);

		//–¥»Îµ±ÃÏµƒ00:00
		struct tm *nowTimeS = gmtime(&nowTime);
		int hour=nowTimeS->tm_hour;  
		int minute=nowTimeS->tm_min;  
		int second=nowTimeS->tm_sec;
		time_t nextTime = nowTime + 24*60*60 - hour*60*60 - minute*60 - second; 
		UserDefault::getInstance()->setDoubleForKey("missionTime",nextTime);
	}
	
    return true;
}

void Mission::changeMisson(int fishtype)
{
	//»Áπ˚»ŒŒÒ’˝‘⁄÷¥––
	char tmpMisionLabel[50];
	if(isMissionIng && fishtype == fishKind)
	{
		//»ŒŒÒC
		if(missionKind == 3)
		{
			missionNum++;
			sprintf(tmpMisionLabel,"%d/1",missionNum);
			missionLabel->setString(tmpMisionLabel);

			if(missionNum == 1)
			{
				fish->stopAllActions();
				isMissionIng = false;
				//ÕÍ≥…»ŒŒÒA µØøÚÃ· æ+◊™≈Ã
				this->scheduleOnce(schedule_selector(Mission::zhuanpan),4.0f);
				auto layer = this->getParent();
				missionA = LabelTTF::create(GAME_DATA_STRING("mission_a"),GameHallLayer::wordKind,48);
				missionA->setColor(Color3B(191,28,23));
				missionA->setPosition(Vec2(layer->getContentSize().width/2,layer->getContentSize().height/2));
				layer->addChild(missionA,MENULAYER);
			}
			
		}

		//»ŒŒÒB
		if(missionKind == 2)
		{
			missionNum++;
			sprintf(tmpMisionLabel,"%d/10",missionNum);
			missionLabel->setString(tmpMisionLabel);	
			if(missionNum == 10)
			{
				fish->stopAllActions();
				scaleNum = 0.3;
				fish->setScale(scaleNum);
				//ÀÊª˙“ª∏ˆ”„”Œ∂Ø
			    fishKind =  CCRANDOM_0_1() + 20;
				char cTempAni[200];
				sprintf(cTempAni,"fish_animation_%d_%d",GameHallLayer::RoomType,fishKind); 
				Animation* fishAnimation = AnimationCache::getInstance()->getAnimation(cTempAni);
				Animate*  fishAnimate = Animate::create(fishAnimation);
				fish->runAction(RepeatForever::create(fishAnimate));

				missionKind = 3;
				missionNum = 0;

				//ÕÍ≥…»ŒŒÒB µØøÚÃ· æ+300Ω±“
				auto layer = this->getParent();
				auto gongxi = MissionSuc::create(1,300 * roomBeilv);
				gongxi->setPosition(Point::ZERO);
				layer->addChild(gongxi,MENULAYER);
				CannonLayer::GameCoinRefresh(300 * roomBeilv);

				sprintf(tmpMisionLabel,"%d/1",missionNum);
				missionLabel->setString(tmpMisionLabel);

				missionB->setString(GAME_DATA_STRING("mission_3"));
                missionB->setScale(0.8f);
                missionB->setFontSize(20);
				missionB->setPosition(Vec2(missionBG->getContentSize().width*0.5,missionBG->getContentSize().height*0.25));

                Sprite* goldImage = (Sprite*)missionBG->getChildByTag(12);
                if (goldImage) {
                    goldImage->removeFromParent();
                }
			}		
		}

		//»ŒŒÒA
		if(missionKind == 1 )
		{
			missionNum++;
			sprintf(tmpMisionLabel,"%d/20",missionNum);
			missionLabel->setString(tmpMisionLabel);

			if(missionNum == 20)
			{
				//ÀÊª˙“ª∏ˆ”„”Œ∂Ø
				fish->stopAllActions();
				scaleNum = 0.4;
				fish->setScale(scaleNum);

				fishKind =  CCRANDOM_0_1()*7 + 12;
				char cTempAni[100];
				sprintf(cTempAni,"fish_animation_%d_%d",GameHallLayer::RoomType,fishKind);
				Animation* fishAnimation = AnimationCache::getInstance()->getAnimation(cTempAni);
				Animate*  fishAnimate = Animate::create(fishAnimation);
				fish->runAction(RepeatForever::create(fishAnimate));
				missionKind = 2;
				missionNum = 0;

				//ÕÍ≥…»ŒŒÒC µØøÚÃ· æ+30◊Í Ø
 
				auto layer = this->getParent();
				auto gongxi = MissionSuc::create(2,30 * roomBeilv);
				gongxi->setPosition(Point::ZERO);
				layer->addChild(gongxi,MENULAYER);
				CannonLayer::GameCoinZuanshi(30 * roomBeilv);

				sprintf(tmpMisionLabel,"%d/10",missionNum);
				missionLabel->setString(tmpMisionLabel);

				
				char mis_tmp[50];
				sprintf(mis_tmp,GAME_DATA_STRING("mission_2"),300 * roomBeilv);
                sprintf(mis_tmp,":%d",300 * roomBeilv);
                
                Sprite* diamond = (Sprite*)missionBG->getChildByTag(11);
                if (diamond) {
                    diamond->removeFromParent();
                }
                
                auto goldImg = Sprite::createWithSpriteFrameName("yubi.png");
                goldImg->setPosition(ccp(missionBG->getContentSize().width*0.275f,missionBG->getContentSize().height*0.25));
                goldImg->setScale(0.5f);
                missionBG->addChild(goldImg);
                goldImg->setTag(12);
                
				missionB->setString(mis_tmp);
				missionB->setPosition(Vec2(missionBG->getContentSize().width*0.55,missionBG->getContentSize().height*0.25));
			}
			
		}

		UserDefault::getInstance()->setIntegerForKey("missionKind",missionKind);
		UserDefault::getInstance()->setIntegerForKey("missionNum",missionNum);
		UserDefault::getInstance()->setIntegerForKey("fishKind",fishKind);
		UserDefault::getInstance()->flush();		
	}
}

void Mission::zhuanpan(float dt)
{
	//“∆≥˝Ã· ælabel ∫Õ »ŒŒÒ¥∞ø⁄
	missionA->removeFromParent();
	missionBG->setVisible(false);

	auto layer = this->getParent();
	auto zhuanpan = ZuanPan::create(roomBeilv);
	zhuanpan->setPosition(Point::ZERO);
	layer->addChild(zhuanpan,MENULAYER);
}

bool Mission::getIsMission()
{
	return isMissionIng;
}