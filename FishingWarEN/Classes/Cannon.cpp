 

#include "SimpleAudioEngine.h"
#include "Cannon.h"
#include "StaticData.h"
#include "GameBegin.h"

USING_NS_CC;
Cannon* Cannon::create(unsigned char type ,int beishu,char cPos)
{
    Cannon* cannon = new Cannon();
    cannon->init(type,beishu,cPos);
    cannon->autorelease();
    return cannon;
}
void Cannon::ShowFire(bool bFire)
{
	if(_type < 24)
	{
		if(_type < GameBegin::WangW[0])
		{
			mFire->setVisible(bFire); 
		}
		else if(_type < GameBegin::WangW[1])
		{
			mFire->setVisible(bFire);
			mFire1->setVisible(bFire);
		}
		else if(_type < 20)
		{
			mFire->setVisible(bFire);
			mFire1->setVisible(bFire);
			mFire2->setVisible(bFire);
		}  
		else if(_type < 22)
		{
			mFire->setVisible(bFire); 
		}  
	}
	if(_type == 66)
	{
		mFire->setVisible(bFire);
		mFire1->setVisible(bFire);
		mFire2->setVisible(bFire);
	}
	/*else if(_type == 30)
	{
		mFire->setVisible(bFire);
		mFire1->setVisible(bFire);
		mFire2->setVisible(bFire);
	}*/
}
bool Cannon::init(unsigned char type ,int beishu ,char cPos)
{   

	Size  winSize = Director::getInstance()->getWinSize();
    iShootNumChoose = 0;
	Point bgPoint;
	Point paoPoint;
	Point fengshuPoint;
	Point fengshuNum;


	if(cPos >1)
	{
		bgPoint = Point(0,winSize.height-35);
		paoPoint = Point(0,winSize.height- 50);
		fengshuPoint = Point(0,winSize.height-17);
		fengshuNum = Point(0,winSize.height-15);
	}
	else
	{
		bgPoint = Point(0,35);
		paoPoint = Point(0, 50);
		fengshuPoint = Point(0,17);
		fengshuNum = Point(0,15);
	} 

	int tmp_type = (int)type;
	if(type< GameBegin::WangW[2])
	{
		auto sprbg = Sprite::createWithSpriteFrameName("paoonebg.png");
		sprbg->setPosition(bgPoint);
		this->addChild(sprbg);
		if( type< GameBegin::WangW[0])
		{
			mPao = Sprite::createWithSpriteFrameName("paoone.png");
			mPao->setPosition(paoPoint);
			
			this->addChild(mPao); 
			mFire = Sprite::createWithSpriteFrameName("fire1.png"); 
			mPao->addChild(mFire); 
			if(cPos> 1)
			{ 
				mFire->setPosition(24,-64);//148
				mFire->setFlippedY(true);
			}
			else
			{
				mFire->setPosition(22,135);
			}
		}
		else if(type< GameBegin::WangW[1])
		{
			mPao = Sprite::createWithSpriteFrameName("paotwo.png");
			mPao->setPosition(paoPoint);
			this->addChild(mPao);

			   mFire = Sprite::createWithSpriteFrameName("fire1.png");
			
			mPao->addChild(mFire);

			   mFire1 = Sprite::createWithSpriteFrameName("fire1.png");
			
			mPao->addChild(mFire1);

			if(cPos> 1)
			{ 
				mFire->setPosition(26*0.8f,-72*0.8f);
				mFire1->setPosition(62*0.8f,-72*0.8f);
				mFire->setFlippedY(true);
				mFire1->setFlippedY(true);
			}
			else
			{
				mFire->setPosition(26*0.8f,163*0.8f);
				mFire1->setPosition(62*0.8f,163*0.8f);
			}

		}
		else if(type< GameBegin::WangW[2])
		{
			mPao = Sprite::createWithSpriteFrameName("paothree.png");
			mPao->setPosition(paoPoint);
			this->addChild(mPao); 

			mFire = Sprite::createWithSpriteFrameName("fire1.png"); 
			mPao->addChild(mFire);

		    mFire1 = Sprite::createWithSpriteFrameName("fire1.png"); 
			mPao->addChild(mFire1);

			mFire2 = Sprite::createWithSpriteFrameName("fire1.png"); 
			mPao->addChild(mFire2);
            mPao->setScale(0.92);

			if(cPos> 1)
			{ 

				mFire->setPosition(26*0.8f,-72*0.8f);
				mFire1->setPosition(58*0.8f,-72*0.8f);
				mFire2->setPosition(87*0.8f,-72*0.8f);

				mFire->setFlippedY(true);
				mFire1->setFlippedY(true);
				mFire2->setFlippedY(true);
			}
			else
			{
				mFire->setPosition(26*0.8f,165*0.8f);
				mFire1->setPosition(58*0.8f,165*0.8f);
				mFire2->setPosition(87*0.8f,165*0.8f);
			} 

		}
		auto fengshu = Sprite::createWithSpriteFrameName("paoongfenshu.png");
		fengshu->setPosition(fengshuPoint);
		this->addChild(fengshu);

		if(cPos >1)
		{ 
			fengshu->setFlippedY(true);
			sprbg->setFlippedY(true);
			mPao->setFlippedY(true);
		}

		
		auto fengshunum = Label::create();  
		fengshunum->setCharMap("fengshunum.png",11,17,'0');
		char cTmepNum[10] = {0};
		sprintf(cTmepNum,"%d",beishu);
		fengshunum->setString( cTmepNum); 
		fengshunum->setPosition(fengshuNum);
		this->addChild(fengshunum);   
	}
	else if(type< GameBegin::WangW[3])
	{
		auto sprbg = Sprite::createWithSpriteFrameName("paofourbg.png");
		sprbg->setPosition(bgPoint);
		this->addChild(sprbg);
	 
		mPao = Sprite::createWithSpriteFrameName("paofour.png");
		mPao->setPosition(paoPoint);
		this->addChild(mPao); 

        mPao->setScale(0.92);
		auto fengshu = Sprite::createWithSpriteFrameName("paofourfenshu.png");
		fengshu->setPosition(fengshuPoint);
		this->addChild(fengshu);

		auto fengshunum = Label::create();  
		fengshunum->setCharMap("fengshunum.png",11,17,'0');
		char cTmepNum[10] = {0};
		sprintf(cTmepNum,"%d",beishu);
		fengshunum->setString( cTmepNum); 
		fengshunum->setPosition(fengshuNum);
		this->addChild(fengshunum); 


		   mFire = Sprite::createWithSpriteFrameName("fire1.png");
	
		mPao->addChild(mFire);

		   mFire1 = Sprite::createWithSpriteFrameName("fire1.png");
		
		mPao->addChild(mFire1);

		   mFire2 = Sprite::createWithSpriteFrameName("fire1.png");
		
		mPao->addChild(mFire2);


		if(cPos >1)
		{  
			mFire1->setPosition(58*0.8f,-82*0.8f);
			mFire->setPosition(24*0.8f,-72*0.8f);
			mFire2->setPosition(90*0.8f,-72*0.8f);  

			fengshu->setFlippedY(true);
			sprbg->setFlippedY(true);
			mPao->setFlippedY(true);

			mFire->setFlippedY(true);
			mFire1->setFlippedY(true);
			mFire2->setFlippedY(true);
		}
		else
		{
			mFire1->setPosition(58*0.8f,172*0.8f);
			mFire->setPosition(24*0.8f,162*0.8f);
			mFire2->setPosition(93*0.8f,162*0.8f);

		}

	}
	else if(type< GameBegin::WangW[4])
	{
		auto sprbg = Sprite::createWithSpriteFrameName("paofivebg.png");
		sprbg->setPosition(bgPoint);
		this->addChild(sprbg); 

		mPao = Sprite::createWithSpriteFrameName("paofive.png");
		mPao->setPosition(paoPoint);
		this->addChild(mPao); 

		auto fengshu = Sprite::createWithSpriteFrameName("paofivefenshu.png");
		fengshu->setPosition(fengshuPoint);
		this->addChild(fengshu);

		auto fengshunum = Label::create();  
		fengshunum->setCharMap("fengshunum.png",11,17,'0');
		char cTmepNum[10] = {0};
		sprintf(cTmepNum,"%d",beishu);
		fengshunum->setString( cTmepNum); 
		fengshunum->setPosition(fengshuNum);
		this->addChild(fengshunum);  
		
		mFire = Sprite::createWithSpriteFrameName("fire1.png"); 
		mPao->addChild(mFire); 
		mFire1 = Sprite::createWithSpriteFrameName("fire1.png"); 
		mPao->addChild(mFire1); 
		mFire2 = Sprite::createWithSpriteFrameName("fire1.png"); 
		mPao->addChild(mFire2);

		if(cPos >1)
		{
			sprbg->setFlippedY(true);
			mPao->setFlippedY(true); 
			fengshu->setFlippedY(true);

			mFire->setFlippedY(true);
			mFire1->setFlippedY(true); 
			mFire2->setFlipY(true);


			mFire1->setPosition(56*0.8f,-72*0.8f);
			mFire->setPosition(24*0.8f,-76*0.8f);
			mFire2->setPosition(87*0.8f,-80*0.8f);

		
		}
		else
		{
			mFire1->setPosition(56*0.8f,174*0.8f);
			mFire->setPosition(24*0.8f,168*0.8f);
			mFire2->setPosition(87*0.8f,168*0.8f);

		}


	}
	else if(type < GameBegin::WangW[5])
	{
		auto sprbg = Sprite::createWithSpriteFrameName("paosixbg.png");
		sprbg->setPosition(bgPoint);
		this->addChild(sprbg);

		mPao = Sprite::createWithSpriteFrameName("paosix.png");
		mPao->setPosition(paoPoint);
		this->addChild(mPao); 

		auto fengshu = Sprite::createWithSpriteFrameName("paosixfenshu.png");
		fengshu->setPosition(fengshuPoint);
		this->addChild(fengshu);

		auto fengshunum = Label::create();  
		fengshunum->setCharMap("fengshunum.png",11,17,'0');
		char cTmepNum[10] = {0};
		sprintf(cTmepNum,"%d",beishu);
		fengshunum->setString( cTmepNum); 
		fengshunum->setPosition(fengshuNum);
		this->addChild(fengshunum); 

		   mFire = Sprite::createWithSpriteFrameName("fire1.png");
		
		mPao->addChild(mFire);

		   mFire1 = Sprite::createWithSpriteFrameName("fire1.png");
		
		mPao->addChild(mFire1);

		   mFire2 = Sprite::createWithSpriteFrameName("fire1.png");
		 
		mPao->addChild(mFire2);

		if(cPos >1)
		{
			sprbg->setFlippedY(true);
			mPao->setFlippedY(true); 
			fengshu->setFlippedY(true);

			mFire->setFlippedY(true);
			mFire1->setFlippedY(true); 
			mFire2->setFlipY(true);

			mFire1->setPosition(63*0.8f,-89*0.8f);
			mFire2->setPosition(93*0.8f,-82*0.8f);
			mFire->setPosition(27*0.8f,-82*0.8f);

		}
		else
		{
			mFire1->setPosition(63*0.8f,183*0.8f);
			mFire2->setPosition(93*0.8f,176*0.8f);
			mFire->setPosition(29*0.8f,176*0.8f);
		}

	}
	else if(type < 30)
	{
	
		if(type <22)
		{ 		
			
			auto sprbg = Sprite::createWithSpriteFrameName("fanweipaoonebg.png");
			
	 
			this->addChild(sprbg);


			mPao = Sprite::createWithSpriteFrameName("fanweipaoone.png");
			 
			this->addChild(mPao);  

			FanWeiAni = Sprite::create();
			mPao->addChild(FanWeiAni);
			

			fengshunum = Label::create();  
			fengshunum->setCharMap("fengshunum.png",11,17,'0');
			char cTmepNum[10] = {0};
			sprintf(cTmepNum,"%d",beishu);
			fengshunum->setString( cTmepNum); 
			
			//fengshunum->setPosition(Point(paoPoint.x-50,winSize.height- 50 )); 
			mPao->addChild(fengshunum);  

			mFire = Sprite::createWithSpriteFrameName("fire1.png");
			mFire->setPosition(Vec2(57,202));
			mPao->addChild(mFire);  
			if(cPos >1)
			{
				sprbg->setFlippedY(true);
				mPao->setFlippedY(true); 
				mFire->setFlippedY(true);
				mFire->setPosition(Vec2(57,-110));
				fengshunum->setPosition(Point(50,mPao->getContentSize().height-(50-25)));
				sprbg->setPosition(Point(paoPoint.x,paoPoint.y+23));
				mPao->setPosition(Point(paoPoint.x,paoPoint.y+17));
				FanWeiAni->setPosition(Point(paoPoint.x-60,paoPoint.y-20)); 
				
			}
			else
			{
				FanWeiAni->setPosition(Point(paoPoint.x+60,paoPoint.y+20)); 
				mPao->setPosition(Point(paoPoint.x,paoPoint.y-17));
				sprbg->setPosition(Point(paoPoint.x,paoPoint.y-23));
				mFire->setPosition(Vec2(57,202)); 
				fengshunum->setPosition(Point(50,50-25));

			}
			 

		}
		else if(type <24)
		{
			mPao = Sprite::createWithSpriteFrameName("fanweipaotwo.png");
			
		//	mPao->setScale(0.9f);
			this->addChild(mPao);

			fengshunum = Label::create();  
			fengshunum->setCharMap("fengshunum.png",11,17,'0');
			char cTmepNum[10] = {0};
			sprintf(cTmepNum,"%d",beishu);
			fengshunum->setString( cTmepNum); 
			
			mPao->addChild(fengshunum); 

			if(cPos >1)
			{
				 mPao->setPosition(Point(paoPoint.x,paoPoint.y+24)); 
				mPao->setFlippedY(true); 
				fengshunum->setPosition(Point(70,mPao->getContentSize().height-(50-9)));
							 
			} 
			else
			{ 
				mPao->setPosition(Point(paoPoint.x,paoPoint.y-24));
				fengshunum->setPosition(Point(70,50-9));
			}
 
		}
		else if(type <25)
		{
			mPao = Sprite::createWithSpriteFrameName("fanweipaothree.png");
			
			mPao->setScale(0.95f);
			this->addChild(mPao);
			 

			fengshunum = Label::create();  
			fengshunum->setCharMap("fengshunum.png",11,17,'0');
			char cTmepNum[10] = {0};
			sprintf(cTmepNum,"%d",beishu);
			fengshunum->setString( cTmepNum); 
		 
			mPao->addChild(fengshunum); 

			if(cPos >1)
			{
				mPao->setPosition(Point(paoPoint.x,paoPoint.y+15)); 
				mPao->setFlippedY(true); 
				fengshunum->setPosition(Point(80,mPao->getContentSize().height-(50+15)));
			} 
			else
			{				
				mPao->setPosition(Point(paoPoint.x,paoPoint.y-15));
				fengshunum->setPosition(Point(80,50+15));
			}
		}
		else if(type <27)
		{
			auto sprbg = Sprite::createWithSpriteFrameName("jiguangonebg.png");
			sprbg->setPosition(bgPoint);
		//	sprbg->setScale(0.9f);
			this->addChild(sprbg);

			mPao = Sprite::createWithSpriteFrameName("jiguangone.png");
			
	//		mPao->setScale(0.9f);
			this->addChild(mPao);
		 


			fengshunum = Label::create();  
			fengshunum->setCharMap("fengshunum.png",11,17,'0');
			char cTmepNum[10] = {0};
			sprintf(cTmepNum,"%d",beishu);
			fengshunum->setString( cTmepNum); 
		
			mPao->addChild(fengshunum); 




			if(cPos >1)
			{

				mPao->setFlippedY(true); 
				sprbg->setFlippedY(true); 
				mPao->setPosition(Point(paoPoint.x,paoPoint.y+17));
				fengshunum->setPosition(Point(30,mPao->getContentSize().height-(50-24)));

			} 
			else
			{
				mPao->setPosition(Point(paoPoint.x,paoPoint.y-17));
				fengshunum->setPosition(Point(30,50-24));
			}




		}
		else if(type <29)
		{
			auto sprbg = Sprite::createWithSpriteFrameName("jiguangtwobg.png");
			
		//	sprbg->setScale(0.9f); 
			this->addChild(sprbg);

			mPao = Sprite::createWithSpriteFrameName("jiguangtwo.png");
			mPao->setPosition(Point(paoPoint.x,paoPoint.y-15));
	//		mPao->setScale(0.9f);
			this->addChild(mPao);

			JiGuangTwoOne = Sprite::create();
			mPao->addChild(JiGuangTwoOne); 
			Animation* fishAnimation = AnimationCache::getInstance()->getAnimation("jiguanganitwo");
			Animate* fishAnimate = Animate::create(fishAnimation);
			
			JiGuangTwoOne->runAction(RepeatForever::create(fishAnimate)); 

			JiGuangTwoTwo = Sprite::create();
			mPao->addChild(JiGuangTwoTwo); 
			Animation* fishAnimation2 = AnimationCache::getInstance()->getAnimation("jiguanganione");
			Animate* fishAnimate2 = Animate::create(fishAnimation2);
			
			JiGuangTwoTwo->runAction(RepeatForever::create(fishAnimate2)); 

			JiGuangTwoThree = Sprite::create();
			mPao->addChild(JiGuangTwoThree); 
			
			JiGuangTwoThree->runAction(RepeatForever::create(fishAnimate2)); 
			JiGuangTwoThree->setFlipX(true);

			 
			fengshunum = Label::create();  
			fengshunum->setCharMap("fengshunum.png",11,17,'0');
			char cTmepNum[10] = {0};
			sprintf(cTmepNum,"%d",beishu);
			fengshunum->setString( cTmepNum); 
			
			mPao->addChild(fengshunum); 
			mPao->setScale(0.9f);



			if(cPos >1)
			{
				sprbg->setPosition(Point(paoPoint.x,paoPoint.y+2));
				mPao->setFlippedY(true); 
				sprbg->setFlippedY(true); 
				JiGuangTwoOne->setPosition(Point(paoPoint.x+69,paoPoint.y-63));
				JiGuangTwoTwo->setPosition(Point(paoPoint.x+28,paoPoint.y-53));
				JiGuangTwoThree->setPosition(Point(paoPoint.x+110,paoPoint.y-52));
				fengshunum->setPosition(Point(55,mPao->getContentSize().height-(50-14)));

			} 
			else
			{
				sprbg->setPosition(Point(paoPoint.x,paoPoint.y-2));
				JiGuangTwoOne->setPosition(Point(paoPoint.x+69,paoPoint.y+63));
				JiGuangTwoTwo->setPosition(Point(paoPoint.x+28,paoPoint.y+53));
				JiGuangTwoThree->setPosition(Point(paoPoint.x+110,paoPoint.y+52));
				fengshunum->setPosition(Point(55,50-14));
			}


		}
		else if(type <30)
		{
			auto sprbg = Sprite::createWithSpriteFrameName("jiguangthreebg.png");
			
		 
			this->addChild(sprbg);


			
			mPao = Sprite::createWithSpriteFrameName("jiguangthree.png");
			
			mPao->setScale(0.9f);
			this->addChild(mPao);
		 

			JiGuangThree = Sprite::create(); 
		
			

			mPao->addChild(JiGuangThree); 


			fengshunum = Label::create();  
			fengshunum->setCharMap("fengshunum.png",11,17,'0');
			char cTmepNum[10] = {0};
			sprintf(cTmepNum,"%d",beishu);
			fengshunum->setString( cTmepNum); 
			
			mPao->addChild(fengshunum); 


			if(cPos >1)
			{
				sprbg->setPosition(Point(bgPoint.x,bgPoint.y+8));
				mPao->setPosition(Point(paoPoint.x,paoPoint.y+13));
				JiGuangThree->setPosition(Point(paoPoint.x+48,paoPoint.y-95));
				fengshunum->setPosition(Point(37,mPao->getContentSize().height-30));
				mPao->setFlippedY(true); 
				sprbg->setFlippedY(true);  
			}  
			else
			{
				sprbg->setPosition(Point(bgPoint.x,bgPoint.y-8));
				mPao->setPosition(Point(paoPoint.x,paoPoint.y-13));
				JiGuangThree->setPosition(Point(paoPoint.x+48,paoPoint.y+95));
				fengshunum->setPosition(Point(37,50-20)); 
			}
		}
		
	}
	else if(type < 31)
	{ 

		auto sprbg = Sprite::createWithSpriteFrameName("vippaobg.png");
		sprbg->setPosition(bgPoint);
		this->addChild(sprbg);

		mPao = Sprite::createWithSpriteFrameName("vippao.png");
		mPao->setPosition(paoPoint);
		this->addChild(mPao); 

		auto fengshu = Sprite::createWithSpriteFrameName("vippaonum.png");
		fengshu->setPosition(fengshuPoint);
		this->addChild(fengshu);

		auto fengshunum = Label::create();  
		fengshunum->setCharMap("fengshunum.png",11,17,'0');
		char cTmepNum[10] = {0};
		sprintf(cTmepNum,"%d",beishu);
		fengshunum->setString( cTmepNum); 
		fengshunum->setPosition(fengshuNum);
		this->addChild(fengshunum); 


		/*mFire = Sprite::createWithSpriteFrameName("fire1.png");

		mPao->addChild(mFire);

		mFire1 = Sprite::createWithSpriteFrameName("fire1.png");

		mPao->addChild(mFire1);

		mFire2 = Sprite::createWithSpriteFrameName("fire1.png");

		mPao->addChild(mFire2);*/


		if(cPos >1)
		{ 

			/*mFire1->setPosition(58,-92);
			mFire->setPosition(24,-82);
			mFire2->setPosition(90,-82);

			*/
			fengshu->setFlippedY(true);
			sprbg->setFlippedY(true);
			mPao->setFlippedY(true);

			/*mFire->setFlippedY(true);
			mFire1->setFlippedY(true);
			mFire2->setFlippedY(true);*/
		}
		else
		{
			/*mFire1->setPosition(58,186);
			mFire->setPosition(24,176);
			mFire2->setPosition(90,176);*/

		}
	} 
 

	iCannonTime = 0;
	bCannonAni = false;
	if(cPos> 1)
	{
		mPao->setAnchorPoint(Point(0.5,0.8));
	}
	else
	{
		mPao->setAnchorPoint(Point(0.5,0.2));
	}

	cMoveBegPos = mPao->getPosition();
	
	_type = type; 

	m_fUpdateTime = 0;
	m_fTime = 0;
	cFair = 0;
	  
		
	ShowFire(false);
	schedule(schedule_selector(Cannon::updateCannon),0.01f);

    return true;
}
 
void Cannon::updateCannon(float delta)
{

	//cocos2d::log("scene init updateCannon1");

	if( cFair == 2)
	{
		this->m_fUpdateTime += 1;
		if(this->m_fUpdateTime == 5)
		{  
		 
			m_fUpdateTime = 0;
			m_fTime = 0;
			cFair =0; 

			Point sb = mPao->getPosition();
			//mPao->stopAction(moveTo);
			mPao->setPosition(cMoveBegPos);


			 ShowFire(false);
			Point tempPos  = mPao->getPosition();
			if(_type == 21 || _type == 20)
			{
				// FanWeiAni->setVisible(false);
			}
			
		}
		
	} 

	if(bCannonAni == true)
	{
		iCannonTime++;
		if(iCannonTime>19)
		{
			iCannonTime = 0;
			if(_type == 21 || _type == 20)
			{
				bCannonAni =false;
				FanWeiAni->setVisible(false);
			}
			else if(_type == 29)
			{
				bCannonAni =false;
				JiGuangThree->setVisible(false);
			}
		}
	}

	//cocos2d::log("scene init updateCannon2");
	 
}
void Cannon::aimAt(float angle,Point cMoveDis,bool sound)
{ 
	
    mPao->setRotation(angle);
	mPao->setPosition(cMoveBegPos);
	cMoveBegPos  = mPao->getPosition();
	cMoveDisPos =  cMoveBegPos-cMoveDis ;
	 
	if(_type < 20 && sound == true)
	{
       // GameBegin::playSound("shootpia.mp3");
       
       /* if(iShootNumChoose == 0)
        {
            GameBegin::playSound("shootok21.mp3");
        }
        else if(iShootNumChoose == 1)
        {
            
            GameBegin::playSound("shootok22.mp3");
        }
        else if(iShootNumChoose == 2)
        {
            GameBegin::playSound("shootok23.mp3");
        }
         iShootNumChoose ++;
        if(iShootNumChoose ==3)
            iShootNumChoose = 0;*/
        
		 
	}
	else if(_type < 25 && sound == true)
	{ 
        GameBegin::playSound("shootok1.mp3");
	}
	else if(sound == true)
	{
	 
		GameBegin::playSound("shootok3.mp3");
	}
	
	if(_type == 21 || _type == 20)
	{
		Animation* fishAnimation = AnimationCache::getInstance()->getAnimation("fanweioneani");
		Animate* fishAnimate = Animate::create(fishAnimation);
	
		FanWeiAni->runAction(fishAnimate);
		FanWeiAni->setVisible(true); 
		bCannonAni =true;
	}
	else if(_type == 29)
	{

		Animation* fishAnimation = AnimationCache::getInstance()->getAnimation("jiguanganithree");
		Animate* fishAnimate = Animate::create(fishAnimation);
		JiGuangThree->runAction(fishAnimate); 
		JiGuangThree->setVisible(true); 
		bCannonAni =true;
	}

	ShowFire(true);
	m_fUpdateTime = 0;
	m_fTime = 0.05f;
	cFair =2;
	mPao->setPosition(cMoveDisPos);
	//  moveTo = CCMoveTo::create(0.17f, cMoveDisPos);
//	mPao->runAction(moveTo);


}


void Cannon::setRot(float angle)
{
 
	mPao->setRotation(angle);
}

Cannon::Cannon()
{
    
}
Cannon::~Cannon()
{
   
}