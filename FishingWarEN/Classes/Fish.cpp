 
#include "Fish.h"
#include <math.h> 
#include <stdlib.h>  
#include "StaticData.h"
#include "GameBegin.h"
#include "SimpleAudioEngine.h"
#include "FishLayer.h"
#include "CannonLayer.h"
#include "GameScene.h"
#include "LoadRes.h"
#include "GameHallLayer.h" 
USING_NS_CC;
 


Fish* Fish::create(unsigned char type ,char cSpc,char cFishNum )
{
    Fish* fish = new Fish();
    fish->init(type,cSpc,cFishNum);
     
    fish->autorelease();  
    return fish;
} 
void Fish::randomFish()
{
    
    noupdate = true;
    
    
    
    winSize = Director::sharedDirector()->getWinSize();
    
    BossType = 0;
    
    cFishBossTime = 0;
    bDead = false;
    bSlow = false;
    mMovePos.x =0;
    mMovePos.y =0;
    iShootPos = 5;
    bBaoJi= false;
    bSpcTwo= false;
    bSpc = false;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    m_iMainID = 0;
    
    
    m_iSubID = 0;
    m_iTrackID = 0;
    //	m_trackFish.Reset(m_iTrackID,false);
    
    bPanziDeadFish = false;
    
    /*int sdf[50];
     
     char cCC[30];
     for(int i=0; i< 50; i++)
     {
     memset(cCC,sizeof(cCC),0);
     sprintf(cCC,"fish_%d_opp",i);
     sdf[i] =  GAME_DATA_INT(cCC);
     }*/
    
    
    
    
    FishNum = 1;
    m_iX = 0;
    m_iY = 0; 
    m_iSpeed = 0;
   
    m_iSpacTime = 0;
    
    
    int beilv[8] = {20,17,18,14,13,15,17,16};
 
    int fish_kind  = 0;
    //随机鱼的种类1-6
   // fish_kind = (int)(CCRANDOM_0_1() * 100000) % 8 + 1;
    
    
    if(CCRANDOM_0_1()*100 < 50)
    {
        fish_kind = 8;
    }
    else
    {
        fish_kind = 7;
    }
    
    
    
    char hallCharTemp[100];
    
    m_iFishType = beilv[fish_kind - 1];
    _type = beilv[fish_kind - 1];
    iPanziType = fish_kind;
    //fish_kind = 8;
 
    if(fish_kind ==8)//水母
    {
        sprintf(hallCharTemp,"hall_fish_shang_%d (1).png",1);
          _fishSprite = Sprite::createWithSpriteFrameName(hallCharTemp);
        //fish_sp->setOpacity(50);
        //fish_sp->setScale(0.01);
        this->addChild(_fishSprite,10);
        
        sprintf(hallCharTemp,"hall_fish_shang_animate_%d",1);
        _fishSprite->runAction(RepeatForever::create( Animate::create(AnimationCache::getInstance()->getAnimation(hallCharTemp))));
        
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
            _fishSprite->setRotation(thda * 180 / M_PI);
            moveWitd = Vec2(tan(thda) * 800 , 800);
            _fishSprite->setPosition(Vec2(width,heigh));
            _fishSprite->runAction(Sequence::create(MoveBy::create(speed ,moveWitd ),CCCallFunc::create([&]{bDead = true;}),RemoveSelf::create(),nullptr));
        }
        
        
        float a = _fishSprite->getContentSize().width;
        float b = _fishSprite->getContentSize().height;
        
        
        fRadius = a > b ? b/2 : a/2;
        
        
    }else if(fish_kind == 7)//斜鱼
    {
        sprintf(hallCharTemp,"hall_fish_ce_%d_1.png",1);
          _fishSprite = Sprite::createWithSpriteFrameName(hallCharTemp);
        //fish_sp->setOpacity(50);
        _fishSprite->setScale(0.01);
        this->addChild(_fishSprite,10);
        
        sprintf(hallCharTemp,"hall_fish_ce_animate_%d",1);
        _fishSprite->runAction(RepeatForever::create( Animate::create(AnimationCache::getInstance()->getAnimation(hallCharTemp))));
        
        
        float speed = (CCRANDOM_0_1() + 1) * 15;   //速度
        float width  = CCRANDOM_0_1() * 1024.99;	//x值
        float heigh = 350.0f;						//y值
        Vec2 moveWitd;								//要移动的vec
        bool fangxiang = CCRANDOM_0_1() > 0.5 ? true : false;  //方向
        
        if(width < 612)
        {
            _fishSprite->setFlippedX(true);
            moveWitd = Vec2(tan(1.0f/4.0f * M_PI) * 420 , -420);
        }else
        {
            moveWitd = Vec2(-tan(1.0f/4.0f * M_PI) * 420 , -420);
        }
        
        _fishSprite->setPosition(Vec2(width,heigh));
        _fishSprite->runAction(Sequence::create(Spawn::create(EaseExponentialIn::create(MoveBy::create(speed ,moveWitd)),EaseExponentialIn::create(ScaleTo::create(speed , 1.7)),nullptr),CCCallFunc::create([&]{bDead = true;}),RemoveSelf::create(),nullptr));
        
        
        
        float a = _fishSprite->getContentSize().width;
        float b = _fishSprite->getContentSize().height;
        
        
        fRadius = a > b ? b/2 : a/2;
        
    }
    /*else
    {
        //随机鱼的速度系数 1，1.2，1.4，1.6
        int speed_xi = CCRANDOM_0_1() + 1;
        //随机高度
        float high  = CCRANDOM_0_1() * 540.99 + 100;
        float width;
        Vec2 moveWitd;
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
            scale = (high - 320.0f) / 320.0f;
            if(scale < 0.3)
                scale = 0.3;
            
        }else
        {
            scale = 1;
        }
        float spped = scale * 10 * speed_xi;
        
        sprintf(hallCharTemp,"hall_fish_%d (1).png",fish_kind);
          _fishSprite = Sprite::createWithSpriteFrameName(hallCharTemp);
        _fishSprite->setPosition(Vec2(width,high));
        _fishSprite->setScale(scale);
        this->addChild(_fishSprite,8);
        
        if(CCRANDOM_0_1() > 0.15)
        {
            if(CCRANDOM_0_1() > 0.5)
            {
                _fishSprite->setZOrder(11);
            }
        }else
        {
            _fishSprite->setScale(1);
            scale = 1;
        }
        
       // _fishSprite->setOpacity(255 * scale);
        
        if(scale != 1)
        {
            _fishSprite->setZOrder(7);
        }
        if(!fangxiang)
        {
            _fishSprite->setFlippedX(true);
        }
        
        //jywsb
        //设置bDead 为true
        
        sprintf(hallCharTemp,"hall_fish_animate_%d",fish_kind);
        _fishSprite->runAction(RepeatForever::create( Animate::create(AnimationCache::getInstance()->getAnimation(hallCharTemp))));
        _fishSprite->runAction(Sequence::create(MoveBy::create(200.0f/spped,moveWitd),CCCallFunc::create([&]{bDead = true;}),RemoveSelf::create(),nullptr));
    }
    */
   
    
    
}

bool Fish::init(unsigned char type,char cSpc,char cFishNum  )
{
    if(type == 150)
    {
        randomFish();
        return true;
    }
    
    
    iRoomType = GameHallLayer::RoomType;
    if(GameHallLayer ::RoomType == 89)
    {
        iRoomType = 90;
    }
   
    iHuaFeiNum = 0;
    iHuaFeiType = 0;
    bsuperpao = false;
    noupdate = false;
    mMovePos.x =0;
    mMovePos.y =0;
    iShootPos = 5;
    bBaoJi= false;
    bSpcTwo= false;
    bSpc = false;
    if(cSpc == 10)
    {
        bSpc = true;
    }
    if(cSpc <6&& cSpc!= -1)
    {
        bSpcTwo = true;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    m_iMainID = 0;
    
    
    m_iSubID = 0;
    m_iTrackID = 0;
    //	m_trackFish.Reset(m_iTrackID,false);
    
    bPanziDeadFish = false;
    
    /*int sdf[50];
     
     char cCC[30];
     for(int i=0; i< 50; i++)
     {
     memset(cCC,sizeof(cCC),0);
     sprintf(cCC,"fish_%d_opp",i);
     sdf[i] =  GAME_DATA_INT(cCC);
     }*/
    
    
  
    
    FishNum = cFishNum;
    
    m_iX = 0;
    m_iY = 0;
    m_iSpeed = 0;
    _type = type;
    iPanziType = type;
    m_iFishType = type;
    m_iSpacTime = 0;
    
    
   
    if(_type == 37 && GameScene::cGameType != 2)
    {
        //_fishkong = Sprite::createWithSpriteFrameName("guangyun.png");
        _fishSprite = Sprite::createWithSpriteFrameName("bibei.png");
        
        int TempX = 200 + CCRANDOM_0_1()*600;
        int TempY = 150 + CCRANDOM_0_1()*350;
        
        //_fishkong->setPosition(Point(TempX,TempY));
        //_fishkong->setOpacity(50);
        _fishSprite->setPosition(Point(TempX,TempY));
        //_fishSprite->setOpacity(50);
        //this->addChild(_fishkong);
        this->addChild(_fishSprite);
        
        
        //CCFadeIn   *ac13=CCFadeIn  ::create(1.5f);
        //_fishkong->runAction(ac13);
        //_fishSprite->runAction(ac13);
        
        
        Point Tempdis = Point(100*0.5f,100*0.5f);
        
        fRadius = ccpDistance(Point(0,0),Tempdis);
        
    }
    else if(_type == 46)
    {
    /*    _fishSprite = Sprite::createWithSpriteFrameName("huafeiquan.png");
        this->addChild(_fishSprite);
        _fishSprite->setScale(0.7);
        fRadius = 50;
        if( UserDefault::getInstance()->getIntegerForKey("ios_dengluFlag") == 1 )
        {
            _fishSprite->setVisible(false);
        }*/
    }
    else if(_type == 45 &&GameScene::cGameType!= 2)
    {
        m_iLeiJiChongZhi = UserDefault::getInstance()->getIntegerForKey("leijichongzhicaijin") ;
        Point Tempdis = Point(225,100);
        fRadius = 300;
        
        Animation* fishAnimation = AnimationCache::getInstance()->getAnimation("fish_animation_ship");
        Animate*  fishAnimate = Animate::create(fishAnimation);
        //    fishAnimate->setTag(k_Action_Animate);
        fishAnimate->setTag(FishAniTag);
        _fishSprite = Sprite::create();
        this->addChild(_fishSprite);
        _fishSprite->runAction(RepeatForever::create(fishAnimate));
        _fishSprite->setRotation(180);
        _fishSprite->setScale(1.3f);
        ShipGailv = 0;
        
        
        
        //ShipNum = Label::createWithCharMap("HB_word.png",40,61,'0');
        
        ShipNum = Label::create();
        ShipNum->setCharMap("img/bfishnum.png",35,57, '0');
        if(m_iLeiJiChongZhi == 0)
        {
            m_iShipNum = 10000 + CCRANDOM_0_1()*10000;
        }
        else
        {
            m_iShipNum = m_iLeiJiChongZhi*3000 + CCRANDOM_0_1()*(m_iLeiJiChongZhi*20000 - m_iLeiJiChongZhi*3000);
        }
        
        
        char cTempNum[30];
        sprintf(cTempNum,"%d",(int)m_iShipNum);
        ShipNum->setString(cTempNum);
        ShipNum->setRotation(-90);
        ShipNum->setPosition(Vec2(0,160));
        ShipNum->setScale(0.7);
        //ShipNum->setPosition(Vec2(ShipNum->getContentSize().width/2,ShipNum->getContentSize().height * 0.715));
        _fishSprite->addChild(ShipNum);
        m_iShipIndex = 0;
        m_iShipMax = 40;
    }
    else if(_type > 29 && _type< 32 && GameScene::cGameType != 2)
    {
        
        char one  =  CCRANDOM_0_1()*10;
        char two  =  CCRANDOM_0_1()*10;
        
        iPanziType = one;
        _fishSprite  = Sprite::createWithSpriteFrameName("shuangdiao.png");
        this->addChild(_fishSprite);
        
        _fishSprite->setScale(1.3f);
        RotateBy *ac9=RotateBy::create(3.5f, 200);
        auto* seq1 = Sequence::create(ac9, NULL);
        _fishSprite->runAction(RepeatForever::create(seq1));
        
        
        
        _fishkong = Sprite::create();
        _fishkong->setPosition(500,500);
        this->addChild(_fishkong);
        
        
        char cTempAni[40];
        sprintf(cTempAni,"fish_animation_%d_%d",iRoomType,one);
        Animation* fishAnimation = AnimationCache::getInstance()->getAnimation(cTempAni);
        
        Animate*  fishAnimate = Animate::create(fishAnimation);
        //    fishAnimate->setTag(k_Action_Animate); 
        _fishthree = Sprite::create(); 
        
        _fishkong->addChild(_fishthree);
        _fishthree->setPosition(Point(-18,0)); 
        _fishthree->runAction(RepeatForever::create(fishAnimate));
        
        
        memset(cTempAni,0,sizeof(cTempAni)); ; 
        sprintf(cTempAni,"fish_animation_%d_%d",iRoomType,two);
        
        Animation* fishAnimation1 = AnimationCache::getInstance()->getAnimation(cTempAni);
        
        Animate*  fishAnimate1 = Animate::create(fishAnimation1);
		//    fishAnimate->setTag(k_Action_Animate); 
		_fishSpriteTwo = Sprite::create(); 
		 
		_fishkong->addChild(_fishSpriteTwo);
		_fishSpriteTwo->setPosition(Point(18,0)); 
		_fishSpriteTwo->runAction(RepeatForever::create(fishAnimate1));

	}
	else if(_type >31 && _type < 37 && GameScene::cGameType != 2)
	{
		
        
		if(_type < 35)
		{
			if(cSpc == 0)
			{
				mMovePos = Point(0,150);
			}
			else if(cSpc == 2 )
			{
				mMovePos = Point(0,-150);
			}
            
            _fishSprite  = Sprite::createWithSpriteFrameName("smallthree.png");
            this->addChild(_fishSprite);
            RotateBy *ac9=RotateBy::create(6.0f, 720);
            _fishSprite->runAction(RepeatForever::create(ac9));
              //_fishSprite->setScale(0.7f);
		}
		else if(_type == 35)
		{
			if(cSpc == 0)
			{
				mMovePos = Point(150,150);
			}
			else if(cSpc == 1 )
			{
				mMovePos = Point(150,-150);
			}  
			else if(cSpc == 2 )
			{
				mMovePos = Point(-150,-150);
			}  
			else if(cSpc == 3)
			{
				mMovePos = Point(-150,150 );
			}
            
            _fishSprite  = Sprite::createWithSpriteFrameName("bigfour.png");
            this->addChild(_fishSprite);
            RotateBy *ac9=RotateBy::create(6.0f, 720);
            _fishSprite->runAction(RepeatForever::create(ac9));
            //_fishSprite->setScale(0.55f);

		}
		else if(_type == 36)
		{
			if(cSpc == 0)
			{
				mMovePos = Point(0,0);
			}
			else if(cSpc == 1 )
			{
				mMovePos = Point(0,150);
			}  
			else if(cSpc == 2 )
			{
				mMovePos = Point(0,-150);
			} 
			else if(cSpc == 3)
			{
				mMovePos = Point(150,0);
			} 
			else if(cSpc == 4)
			{
				mMovePos = Point(-150,0);
			}
            
            _fishSprite  = Sprite::createWithSpriteFrameName("allcatch.png");
            this->addChild(_fishSprite);
            RotateBy *ac9=RotateBy::create(6.0f, 720);
            _fishSprite->runAction(RepeatForever::create(ac9));
             _fishSprite->setScale(0.69f);
		}
        int iTempType =  10 + CCRANDOM_0_1()*9;
        iPanziType = iTempType;
        bPanziDeadFish = true;
        char cTempAni[40];
        sprintf(cTempAni,"fish_animation_%d_%d",iRoomType,iTempType);
        Animation* fishAnimation = AnimationCache::getInstance()->getAnimation(cTempAni);
        Animate*  fishAnimate = Animate::create(fishAnimation);
        //    fishAnimate->setTag(k_Action_Animate);
        _fishSpriteTwo = Sprite::create();
        this->addChild(_fishSpriteTwo);
        _fishSpriteTwo->runAction(RepeatForever::create(fishAnimate));
        _fishSpriteTwo->setScale(1.0);
        
        /*quanPar = ParticleSystemQuad::create("quan.plist");
        quanPar->retain();
        auto batch = ParticleBatchNode::createWithTexture(quanPar->getTexture());
        batch->addChild(quanPar);
        quanPar->resetSystem();
        _fishSpriteTwo->addChild(batch);*/
	}
	else if(_type > 37&& _type < 43 && GameScene::cGameType != 2)
	{
        
        if(_type < 41)
        {
            
            _fishSprite  = Sprite::createWithSpriteFrameName("smallthree.png");
            this->addChild(_fishSprite);
            RotateBy *ac9=RotateBy::create(6.0f, 720);
            _fishSprite->runAction(RepeatForever::create(ac9));
         // _fishSprite->setScale(0.7f);
        }
        else if(_type == 41)
        {
            
            
            _fishSprite  = Sprite::createWithSpriteFrameName("bigfour.png");
            this->addChild(_fishSprite);
            RotateBy *ac9=RotateBy::create(6.0f, 720);
            _fishSprite->runAction(RepeatForever::create(ac9));
           //   _fishSprite->setScale(0.55f);
            
        }
        else if(_type == 42)
        {
            
            _fishSprite  = Sprite::createWithSpriteFrameName("allcatch.png");
            this->addChild(_fishSprite);
            RotateBy *ac9=RotateBy::create(6.0f, 720);
            _fishSprite->runAction(RepeatForever::create(ac9));
            _fishSprite->setScale(0.69f);
        }
        
        
        
		//_fishSprite  = Sprite::createWithSpriteFrameName("panzi38.png");
		//this->addChild(_fishSprite);
		//RotateBy *ac9=RotateBy::create(6.0f, 400);
		//_fishSprite->runAction(RepeatForever::create(ac9));
		 
		int iTempType =  10 + CCRANDOM_0_1()*9;

		  iPanziType = iTempType;
        bPanziDeadFish = true;
		char cTempAni[40]; 
		sprintf(cTempAni,"fish_animation_%d_%d",iRoomType,iTempType);
		Animation* fishAnimation = AnimationCache::getInstance()->getAnimation(cTempAni); 
		Animate*  fishAnimate = Animate::create(fishAnimation);
		//    fishAnimate->setTag(k_Action_Animate); 
		_fishSpriteTwo = Sprite::create();  
		this->addChild(_fishSpriteTwo); 

		_fishSpriteTwo->setScale(1.3f);
		_fishSpriteTwo->runAction(RepeatForever::create(fishAnimate));
        
        
       /* quanPar = ParticleSystemQuad::create("quan.plist");
        quanPar->retain();
        auto batch = ParticleBatchNode::createWithTexture(quanPar->getTexture());
        batch->addChild(quanPar);
        quanPar->resetSystem();
        _fishSpriteTwo->addChild(batch);*/
        
	}
	else 
	{ 
		char cTempAni[40]; 
		if(GameScene::cGameType == 2 && type > 20)
		{
			sprintf(cTempAni,"fish_animationwf_%d_%d",iRoomType,type);
		}
		else if(type > 60)
		{
			sprintf(cTempAni,"fish_animationwf_%d_%d",LogoLayer::room,type-40); 
		}
		else
		{
			sprintf(cTempAni,"fish_animation_%d_%d",iRoomType,type);
		}

		Animation* fishAnimation = AnimationCache::getInstance()->getAnimation(cTempAni);

		Animate*  fishAnimate = Animate::create(fishAnimation);
		//    fishAnimate->setTag(k_Action_Animate);
		fishAnimate->setTag(FishAniTag);
		_fishSprite = Sprite::create();  
		this->addChild(_fishSprite);
		_fishSprite->runAction(RepeatForever::create(fishAnimate)); 
		 if(type > 20 &&GameScene::cGameType == 2)
		 { 
			 _fishSprite->setScale(1.5);
		 }  
		 else if(type > 60)
		 {
			 _fishSprite->setScale(1.3);
		 }
	}
	vcSprPoint.clear();
	vcRadius.clear();

	if(GameScene::cGameType == 2)
	{
		char cTempQuan[10];
		char cTempType =  _type;
		if(_type  > 20)
		{
			cTempType =  _type +10;
		}
		 
		sprintf(cTempQuan,"QuanNum%d",cTempType);
		  
		char cQuanNum = STATIC_DATA_INT(cTempQuan);
	 
		if(cTempType < 60 && cQuanNum > 0)
		{ 
			for(int i =1; i<= cQuanNum; i++)
			{
				char cTempX[15];
				sprintf(cTempX,"Dian%dx%d",cTempType,i);
				char cTempY[15];
				sprintf(cTempY,"Dian%dy%d",cTempType,i);
				Point TempPoint;
				TempPoint.x = STATIC_DATA_INT(cTempX);
				TempPoint.y = STATIC_DATA_INT(cTempY);
				auto TempSpr = Sprite::create();
				TempSpr->setPosition(TempPoint);
				_fishSprite->addChild(TempSpr);
				vcSprPoint.push_back(TempSpr); 


				char cRadius[20];
				sprintf(cRadius,"Radius%d_%d",cTempType,i);
				int TempRadius = STATIC_DATA_INT(cRadius);
				vcRadius.push_back(TempRadius);		

			}
		}
		else
		{
			char cTexWeight[20];
			char cTexHeight[20];
			int iTempWeight = 0;
			int iTempHeight = 0;
		 
			sprintf(cTexWeight,"weight%d",cTempType);
			iTempWeight = STATIC_DATA_INT(cTexWeight);
			sprintf(cTexHeight,"height%d",cTempType);
			iTempHeight =STATIC_DATA_INT(cTexHeight); 
 

			Point Tempdis = Point(iTempWeight*0.5,iTempHeight*0.5);

			fRadius = ccpDistance(Point(0,0),Tempdis);


		}
	}
	else
	{
		char cTempQuan[10];
		sprintf(cTempQuan,"QuanNum%d",_type);


		char cQuanNum = STATIC_DATA_INT(cTempQuan);
		if(_type == 37)
		{
			int a = 0;
		}
		else if(_type < 30 && cQuanNum > 0)
		{ 
			for(int i =1; i<= cQuanNum; i++)
			{
				char cTempX[15];
				sprintf(cTempX,"Dian%dx%d",_type,i);
				char cTempY[15];
				sprintf(cTempY,"Dian%dy%d",_type,i);
				Point TempPoint;
				TempPoint.x = STATIC_DATA_INT(cTempX);
				TempPoint.y = STATIC_DATA_INT(cTempY);
				auto TempSpr = Sprite::create();
				TempSpr->setPosition(TempPoint);
				_fishSprite->addChild(TempSpr);
				vcSprPoint.push_back(TempSpr); 


				char cRadius[20];
				sprintf(cRadius,"Radius%d_%d",_type,i);
				int TempRadius = STATIC_DATA_INT(cRadius);
				vcRadius.push_back(TempRadius);		

			}
		} 
		else if(_type >60)
		{
			cQuanNum = GAME_DATA_INT(cTempQuan);
            float iTempWeight = _fishSprite->getContentSize().width;
            float iTempHeight = _fishSprite->getContentSize().height;
            char cTexWeight[20];
            char cTexHeight[20];
            
            
            sprintf(cTexWeight,"weight%d",_type);
            iTempWeight = GAME_DATA_INT(cTexWeight);
            sprintf(cTexHeight,"height%d",_type);
            iTempHeight = GAME_DATA_INT(cTexWeight);
            
           // float scaleTmp = iTempWeight > iTempHeight ? iTempWeight*2 / 370.0f : iTempHeight * 2 / 370;
            
			if(cQuanNum == 0)
			{
				
				iTempHeight =GAME_DATA_INT(cTexHeight);
				 

				Point Tempdis = Point(iTempWeight*0.5,iTempHeight*0.5);
				fRadius = ccpDistance(Point(0,0),Tempdis);
			}
			else
			{
				for(int i =1; i<= cQuanNum; i++)
				{
					char cTempX[15];
					sprintf(cTempX,"Dian%dx%d",_type,i);
					char cTempY[15];
					sprintf(cTempY,"Dian%dy%d",_type,i);
					Point TempPoint;
					TempPoint.x = GAME_DATA_INT(cTempX);
					TempPoint.y = GAME_DATA_INT(cTempY);
					auto TempSpr = Sprite::create();
					TempSpr->setPosition(TempPoint);
					_fishSprite->addChild(TempSpr);
					vcSprPoint.push_back(TempSpr); 

					char cRadius[20];
					sprintf(cRadius,"Radius%d_%d",_type,i);
					int TempRadius = GAME_DATA_INT(cRadius);
					vcRadius.push_back(TempRadius);		

				}
			}
            if(_type %2 == 0)
            {
                m_iFishType = 24;
                _type = 24;
            }
            else
            {
                m_iFishType = 25;
                _type = 25;
            }
            
            
            /*_fishSpriteTwo  = Sprite::create("bossquanwf.png");
            _fishSpriteTwo->setScale(scaleTmp);
            _fishSprite->addChild(_fishSpriteTwo);
            RotateBy *ac9=RotateBy::create(6.0f, 720);
            _fishSpriteTwo->runAction(RepeatForever::create(ac9));*/
           
		}
		else
		{
			char cTexWeight[20];
			char cTexHeight[20];
			int iTempWeight = 0;
			int iTempHeight = 0;
			if(_type >29)
			{
				iTempWeight = 138;
				iTempHeight = 138;
			}
			else if(_type > 37)
			{
				iTempWeight = 256;
				iTempHeight = 256;
			}
			else
			{
				sprintf(cTexWeight,"weight%d",m_iFishType);
				iTempWeight = STATIC_DATA_INT(cTexWeight);
				sprintf(cTexHeight,"height%d",m_iFishType);
				iTempHeight =STATIC_DATA_INT(cTexHeight);
			} 

			 

			Point Tempdis = Point(iTempWeight*0.5,iTempHeight*0.5);

			fRadius = ccpDistance(Point(0,0),Tempdis);


		}
	}
	
	
	_fishSprite->setPosition(Vec2(-200,-200));
	winSize = Director::sharedDirector()->getWinSize();
	   
	BossType = 0;
		
	cFishBossTime = 0; 
	bDead = false;
	bSlow = false;
	 
    return true;
}
 
 
Point Fish::getCollisionPoint()
{ 
	 return _fishSprite->getPosition();
}
void Fish::CanMove()
{
	bSlow = false;
}
void Fish::NetShan(bool bVip)
{
	if(bVip == true)
	{
		bSlow = true;
	//	auto DelayTimewf = DelayTime::create(0.5f);
		auto ac2 = CCCallFunc::create(this,callfunc_selector(Fish::CanMove)); 
		TintTo *ac11=TintTo::create(0.3f, 100, 100,100);
		TintTo*  ac12 = TintTo::create(0.3f, 255, 255,255);
		auto seq = Sequence::create(ac11,ac12,ac2,NULL);
		//bSlow = true;
		_fishSprite->runAction(seq);
	}
    else if(bsuperpao == false)
	{
         _fishSprite->stopActionByTag(33);
        
		TintTo *ac11=TintTo::create(0.1f, 100, 100,100);
		TintTo*  ac12 = TintTo::create(0.1f, 255, 255,255);
		auto seq = Sequence::create(ac11,ac12,NULL);
        seq->setTag(33);
		//bSlow = true;
		_fishSprite->runAction(seq);
	}

}
bool Fish::beCaught(bool bShow ,char cBeiShu,bool bSpcDead,bool bSuperPao,char cPos,bool bNew)
{
	if(bSuperPao == true)
	{
        _fishSprite->stopActionByTag(33);
		TintTo *ac11=TintTo::create(0.2f,100, 100,100);
		TintTo*  ac12 = TintTo::create(0.15f, 255, 255,255);  
        bsuperpao = true;
		auto ac2 = CCCallFunc::create(this,callfunc_selector(Fish::CanMove)); 
		auto seq = Sequence::create(ac11,ac12,ac2,NULL);
		bSlow = true;
		seq->setTag(33);
		_fishSprite->runAction(seq);
	} 
	else if(bShow == true)
	{

		TintTo *ac11=TintTo::create(0.08f, 100, 100,100);
		TintTo*  ac12 = TintTo::create(0.08f, 255, 255,255);   
		auto seq = Sequence::create(ac11,ac12,NULL);
		//bSlow = true; 
		_fishSprite->runAction(seq); 
	} 

	FishLayer::iBossChiFen += CannonLayer::cBeiShu[cBeiShu]; 
 
	

	if(ifCatchJ(cPos,CannonLayer::cBeiShu[cBeiShu],bNew)||bSpcDead == true)
	{
		
		iShootPos = cPos;
		bDead = true;

		if(bSpcDead == false)
		{
			if(GameScene::cGameType == 1 && cPos == 4)
			{
				GameBegin::playSound("coin1.mp3");
			}
			else if(GameScene::cGameType != 1)
			{
				GameBegin::playSound("coin1.mp3");
			} 
			 
		}
		this->getParent()->reorderChild(this,51); 

		if(GameScene::cGameType == 1)
		{
			if(_type == 46)
			{
				Vec2 pos;
				if(iShootPos == 0||(iShootPos == 4 && GameScene::cSelfPos == 0))
				{
					pos = Vec2( CannonLayer::robotPos1,visibleSize.height*0.37);
				}
				else if(iShootPos == 1||(iShootPos == 4 && GameScene::cSelfPos == 1))
				{
					pos = Vec2( CannonLayer::robotPos2,visibleSize.height*0.37);
				}
				else if(iShootPos == 2)
				{
					pos = Vec2(  CannonLayer::robotPos1,visibleSize.height*0.73);
				}
				else if(iShootPos == 3)
				{
					pos = Vec2(  CannonLayer::robotPos2,visibleSize.height*0.73);
                    
				}
				if(cPos == 4 )
				{
                   
                    if(GameBegin::getFileData("oplb.txt") == 0)
                    {
                        GameBegin::setFileData("oplb.txt", iHuaFeiNum);
                        GameBegin::setFileData("optb.txt", iHuaFeiType);
                    }
                    else if(GameBegin::getFileData("oplc.txt") == 0)
                    {
                        GameBegin::setFileData("oplc.txt", iHuaFeiNum);
                        GameBegin::setFileData("optc.txt", iHuaFeiType);
                    }
                    else if(GameBegin::getFileData("opld.txt") == 0)
                    {
                        GameBegin::setFileData("opld.txt", iHuaFeiNum);
                        GameBegin::setFileData("optd.txt", iHuaFeiType);
                    }
                    else if(GameBegin::getFileData("ople.txt") == 0)
                    {
                        GameBegin::setFileData("ople.txt", iHuaFeiNum);
                        GameBegin::setFileData("opte.txt", iHuaFeiType);
                    }
				}
                else
                {
                    iHuaFeiNum =1+CCRANDOM_0_1()*15;
                }
				//’‚¿Ôª≠ΩÁ√Ê;
				auto huafeiSuc = Sprite::createWithSpriteFrameName("huode_huafei.png");
				huafeiSuc->setPosition(pos);
				huafeiSuc->setTag(48);
				addChild(huafeiSuc,MENULAYER+10);

				char tmp_huafei[20] ;
				sprintf(tmp_huafei,"%d",iHuaFeiNum);
				auto huafei_label = LabelTTF::create(tmp_huafei,GameHallLayer::wordKind,28);
				huafei_label->setPosition(Vec2(142,45));
				huafeiSuc->addChild(huafei_label);
  
				_fishSprite->setVisible(false); 
				scheduleOnce(schedule_selector(Fish::FishTeXiaoOver),4.5f);  
				return true; 
			}
			else
			{ 
                
                if(cFishBase[_type] == 520  )
                {
                    iRandomBase = 250+CCRANDOM_0_1()*250;
                    EndNum= iRandomBase * CannonLayer::cBeiShu[cBeiShu];
                }
                else if(cFishBase[_type] == 525)
                {
                    iRandomBase = 250;
                    EndNum= iRandomBase * CannonLayer::cBeiShu[cBeiShu];
                }
				else
				{
					if(_type == 45)
					{
						EndNum = m_iShipNum;
					} 
					else if(_type > 37)
					{ 
						EndNum= cMatchBase[_type-10]* CannonLayer::cBeiShu[cBeiShu]; 
					}
					else if(_type > 29)
					{ 
						EndNum= cMatchBase[_type -4]* CannonLayer::cBeiShu[cBeiShu]; 
					}	
					else  
					{ 
						EndNum= cMatchBase[_type]* CannonLayer::cBeiShu[cBeiShu]; 
					}
				}  
			}
		}
		else if( GameScene::cGameType == 0)
		{
			if(cFishBase[_type] == 520  )
			{ 
				iRandomBase = 250+CCRANDOM_0_1()*250;
				EndNum= iRandomBase * CannonLayer::cBeiShu[cBeiShu];
			}
            else if(cFishBase[_type] == 525)
            {
                iRandomBase = 250;
                EndNum= iRandomBase * CannonLayer::cBeiShu[cBeiShu];
            }
			else
			{
				if(_type == 45)
				{
					EndNum = m_iShipNum;
				} 
				else if(_type > 37)
				{ 
					EndNum= cFishBase[_type-10]* CannonLayer::cBeiShu[cBeiShu]; 
				}
				else if(_type > 29)
				{

					EndNum= cFishBase[_type -4]* CannonLayer::cBeiShu[cBeiShu]; 
				}	
				else  
				{ 
					EndNum= cFishBase[_type]* CannonLayer::cBeiShu[cBeiShu]; 
				}
			}  
		}
		else
		{
			EndNum= cFishBase[_type]* CannonLayer::cBeiShu[cBeiShu]; 
		}
		
		
		if(_type != 46)
		CannonLayer::GameCoinRefresh(EndNum,false,false,iShootPos);
		if(GameScene::cGameType == 1)
		{
			 if(cPos == 4)
			{
				GameScene::bs_jiafen(3,EndNum);
			}

		} 
		_fishSprite->removeAllChildren();
		if(vcSprPoint.size() != 0 )
		{
			for(int i =0; i< vcSprPoint.size(); i++)
			{
				_fishSprite->removeChild(vcSprPoint[i],false);
			}
			vcSprPoint.clear();
			vcRadius.clear();
		}
			
			  
		if(GameScene::cGameType == 1)
		{
			if(_type == 24 || _type == 25|| _type == 45)		
				bBaoJi= true;
		}
		else
		{
			if(_type == 24 ||_type == 25|| _type == 45)
			{
				bBaoJi= true;
			}
		}

		if(bBaoJi == true)
		{
			CannonLayer::GameCoinZuanshi(cAddDimand[cBeiShu]);			
		}


		char cTempAni[50];
		if(iPanziType > 60) 
		{
			sprintf(cTempAni,"dfish_animationwf_%d",iPanziType-40);  
		}
		else if(noupdate == true)
        {
            //jywsb
            sprintf(cTempAni,"hall_dfish_animate_%d",iPanziType);
        }
        else
		{
			sprintf(cTempAni,"dfish_animation_%d",iPanziType);  
		}
		Animation* dfishAnimation = AnimationCache::getInstance()->getAnimation(cTempAni);

		if(dfishAnimation != NULL) 
		{
			Animate* dfishAnimate = Animate::create(dfishAnimation); 
			dFish = Sprite::create();
			this->addChild(dFish);
			dFish->setPosition(_fishSprite->getPosition()); 
			dFish->setRotation(_fishSprite->getRotation());
            
			Repeat *repeatwf=Repeat::create(dfishAnimate, 25);
            FadeOut *ac14;
            if(bPanziDeadFish == true)
                ac14 =FadeOut::create(5.0f);
            else
                ac14 =FadeOut::create(4.0f);
			Spawn *spawn=Spawn::create(repeatwf,ac14,NULL);
			dFish->runAction(spawn);
            
            if(iPanziType == 7  && noupdate == true)
            {
                dFish->setScale(0.7);
            }
		}
        
        
        
        
        
		if(_type > 29 && _type< 32 && GameScene::cGameType != 2)
		{   
			this->removeChild(_fishthree,true);
			this->removeChild(_fishSpriteTwo,true);
			this->removeChild(_fishkong,true);

		}	 

		else if(_type > 31 && _type <37 && GameScene::cGameType != 2)
		{  
			this->removeChild(_fishSpriteTwo,true);
		}

		else if(_type > 37 &&_type<44 && GameScene::cGameType != 2)
		{  

			this->removeChild(_fishSpriteTwo,true);
		} 

		if(_type<16 && bBaoJi == false)
		{
			scheduleOnce(schedule_selector(Fish::FishTeXiaoOver),4.5f);  
		}
		else
		{
            if(_type > 19)
            GameBegin::playSound("boom.mp3");
		}
        scheduleOnce(schedule_selector(Fish::FishBeginTexiao),0.7f);
        
		return true;
	}
	return false;
	
    
}

void Fish::BossDead(int iNum)
{
	this->getParent()->reorderChild(this,51);
	this->removeChild(_fishSprite,false); 
	
	



		int iTemp = CCRANDOM_0_1()* 100;

		if(iTemp < 33)
		{
			GameBegin::playSound("Bigdie01.mp3");

		}
		else if(iTemp < 66)
		{
			//GameBegin::playSound("panzi.mp3");
			GameBegin::playSound("die03.mp3");


		}
		else 
		{
			//GameBegin::playSound("panzi.mp3");
			GameBegin::playSound("die06.mp3");

		} 



	char cTempAni[20];
	sprintf(cTempAni,"dfish_animation_%d",_type);  
	Animation* dfishAnimation = AnimationCache::getInstance()->getAnimation(cTempAni); 

	bDead = true;
	if(dfishAnimation != NULL) 
	{ 

		Animate* dfishAnimate = Animate::create(dfishAnimation); 
		auto dFish = Sprite::create();
		this->addChild(dFish);
		dFish->setPosition(_fishSprite->getPosition()); 
		dFish->setRotation(_fishSprite->getRotation()); 

		CCRepeat *repeatwf=CCRepeat::create(dfishAnimate, 3);  

		FadeOut *ac14=FadeOut::create(1.0f); 
		Spawn *spawn=Spawn::create(ac14,repeatwf,NULL);  
		dFish->runAction(spawn);
	} 


	AddCoin(_fishSprite->getPosition(),m_iFishType,6);
	LabelFishNum = Label::create();  
	LabelFishNum->setCharMap("fishdeadnum.png",20,33 ,'0'); 
	this->addChild(LabelFishNum); 


	Point cTempPos = _fishSprite->getPosition();
	LabelFishNum->setPosition(cTempPos);
	char cTmepNum[15] = {0};
	sprintf(cTmepNum,"%d",iNum);
	LabelFishNum->setString( cTmepNum);   


	MoveTo *labelmove = MoveTo::create(1.5f,Point(cTempPos.x,cTempPos.y+60));
	FadeOut *ac14=FadeOut::create(0.3f); 
	CCFiniteTimeAction* seq = CCSequence::create(labelmove, ac14, NULL);  
	LabelFishNum->runAction(seq);

	if(_type>11 && _type != 13)
	{
		ShowBigFishFrame(iNum);
	} 
	scheduleOnce(schedule_selector(Fish::FishTeXiaoOver),3.0f);
}

bool Fish::CheckRadius(Point BulletPos,float iBulletRadius)
{
	if(vcRadius.size() == 0)
	{
		float fDis;
		fDis = ccpDistance( _fishSprite->getPosition(),BulletPos);

		if(fDis < (fRadius+iBulletRadius))
			return true;
		else
			return false;	
	}
	else
	{
		for(int i=0; i<vcRadius.size(); i++)
		{
			Point fishPos = _fishSprite->getPosition();
			Point TempPoint1 = vcSprPoint[i]->getPosition();
			int type = _type;
			Point TempPoint = vcSprPoint[i]->getParent()->convertToWorldSpace(vcSprPoint[i]->getPosition()); 
			float TempRadius = vcRadius[i];

			float fDis;
			fDis = ccpDistance( TempPoint,BulletPos);


			if(fDis < (TempRadius+iBulletRadius))
				return true; 

		}
 
		return false;	

	} 
}




void Fish::AddCoin(Point Pos,char cFishType,char cShootPos,bool bBoss )
{
    
    if(bBaoJi == true)
    {
        AddCoinToVector(Pos,0,88,cShootPos,bBoss);
    }
    else if(cFishType < 2)
    {
        AddCoinToVector(Pos,2,0,cShootPos,bBoss);
    }
    else if(cFishType < 5)
    {
        AddCoinToVector(Pos,3,0,cShootPos,bBoss);
    }
    else if(cFishType <8)
    {
        AddCoinToVector(Pos,4,0,cShootPos,bBoss);
    }
    else if(cFishType < 11)
    {
        AddCoinToVector(Pos,0,3,cShootPos,bBoss);
    }
    else if(cFishType < 14)
    {
        AddCoinToVector(Pos,0,4,cShootPos,bBoss);
    }
    else if(cFishType < 15)
    {
        AddCoinToVector(Pos,0,6,cShootPos,bBoss);
    }
    else if(cFishType < 18)
    {
        AddCoinToVector(Pos,0,8,cShootPos,bBoss);
    }
    else if(cFishType < 21)
    {
        AddCoinToVector(Pos,0, 60,cShootPos,bBoss);
    }
    else if(cFishType < 30)
    {
        AddCoinToVector(Pos,0, 80,cShootPos,bBoss);
    }
    else if(cFishType < 50)
    {
        AddCoinToVector(Pos,0, 70,cShootPos,bBoss);
    }
}

void Fish::AddCoinToVector(Point Pos,char cYinNum, char cJinNum,char cShootPos,bool bBoss)
{
    if(bBoss == true)
    {
        //60是小怪，80是大怪，88BOSS
        if(cJinNum == 60)
        {
            
            int ibegin = cYinNum - cYinNum/2;
            Vec2 BeginPos = Pos;
            int cHeight = 100;
            //得到起始点
            BeginPos.x -=  (cHeight/2 +cHeight);
            BeginPos.y +=  cHeight/2;
            //Rect cNowRect[9];
            Vec2 vPos[9];
            for(int i=0; i< 3; i++)
            {
                for(int j=0; j<3; j++)
                {
                    vPos[i*3+j].x = BeginPos.x + (j%3)*cHeight  + CCRANDOM_0_1()*cHeight;
                    vPos[i*3+j].y = BeginPos.y - (i%3)*cHeight  + CCRANDOM_0_1()*cHeight;
                }
            }
            for(int i =0; i< 9 ;i++)
            {
                CoinAndAni* coinandani = CoinAndAni::create(3,cShootPos);
                m_CoinAndAni.pushBack(coinandani);
                this->addChild(coinandani);
                
                // coinandani->setPosition(vPos[i]);
                coinandani->setPosition(Pos);
                coinandani->setScale(0.5f);
                
                CCScaleTo* pScaleTo = CCScaleTo::create(0.9f,1.3f);
                CCMoveTo* pMoveTo = CCMoveTo::create(0.9f,vPos[i]);
                
                CCScaleTo* pReScaleTo = CCScaleTo::create(0.2f,1.0f);
                
                CCSpawn* pSpawan = CCSpawn::create(pScaleTo, pMoveTo, NULL);
                
                DelayTime * dealy = DelayTime::create(1.3f);
                float speed =380;
                float duration = ccpDistance(coinandani->getPosition(), coinandani->BeginPos) / speed;
                MoveTo* moveTo = MoveTo::create(duration ,coinandani->BeginPos);
                auto ac2 = CallFunc::create(this,callfunc_selector(Fish::MoveOver1));
                
                
                if(i == (9-1))
                {
                    auto ac2 = CallFunc::create(this,callfunc_selector(Fish::MoveOver1));
                    auto seq = Sequence::create(pSpawan,pReScaleTo,dealy,moveTo,ac2,NULL);
                    coinandani->runAction(seq);
                }
                else
                {
                    auto seq = Sequence::create(pSpawan,pReScaleTo,dealy,moveTo ,NULL);
                    coinandani->runAction(seq);
                }
            }
        }
        
        
        if(cJinNum == 80)
        {
            int ibegin = cYinNum - cYinNum/2;
            Vec2 BeginPos = Pos;
            int cHeight = 120;
            //得到起始点
            BeginPos.x -=  (cHeight/2 +cHeight);
            BeginPos.y +=  cHeight/2;
            //Rect cNowRect[9];
            Vec2 vPos[18];
            for(int i=0; i< 3; i++)
            {
                for(int j=0; j<3; j++)
                {
                    vPos[i*3+j].x = BeginPos.x + (j%3)*cHeight  + CCRANDOM_0_1()*cHeight;
                    vPos[i*3+j].y = BeginPos.y - (i%3)*cHeight  + CCRANDOM_0_1()*cHeight;
                }
            }
            
            for(int i=0; i< 3; i++)
            {
                for(int j=0; j<3; j++)
                {
                    vPos[9+i*3+j].x = BeginPos.x + (j%3)*cHeight  + CCRANDOM_0_1()*cHeight;
                    vPos[9+i*3+j].y = BeginPos.y - (i%3)*cHeight  + CCRANDOM_0_1()*cHeight;
                }
            }
            
            
            for(int i =0; i< 18 ;i++)
            {
                CoinAndAni* coinandani = CoinAndAni::create(3,cShootPos);
                m_CoinAndAni.pushBack(coinandani);
                this->addChild(coinandani);
                //coinandani->CoinMove(Point(Pos.x+i*55,Pos.y+70));
                
                //auto  pTemp = Point(Pos.x+i*55,Pos.y+120);
                //coinandani->setPosition(vPos[i]);
                coinandani->setPosition(Pos);
                coinandani->setScale(0.5f);
                
                CCScaleTo* pScaleTo = CCScaleTo::create(0.8f,1.3f);
                CCMoveTo* pMoveTo = CCMoveTo::create(0.8f,vPos[i]);
                
                CCScaleTo* pReScaleTo = CCScaleTo::create(0.2f,1.0f);
                
                CCSpawn* pSpawan = CCSpawn::create(pScaleTo, pMoveTo, NULL);
                
                DelayTime * dealy = DelayTime::create(1.3f);
                JumpTo *jump3  = JumpTo::create(0.8,vPos[i],50,1);
                float speed =380;
                float duration = ccpDistance(coinandani->getPosition(), coinandani->BeginPos) / speed;
                MoveTo* moveTo = MoveTo::create(duration ,coinandani->BeginPos);
                auto ac2 = CallFunc::create(this,callfunc_selector(Fish::MoveOver1));
                
                
                if(i == (18-1))
                {
                    auto ac2 = CallFunc::create(this,callfunc_selector(Fish::MoveOver1));
                    auto seq = Sequence::create(pSpawan,pReScaleTo,dealy ,moveTo,ac2,NULL);
                    coinandani->runAction(seq);
                }
                else
                {
                    auto seq = Sequence::create(pSpawan,pReScaleTo,dealy,moveTo ,NULL);
                    coinandani->runAction(seq);
                }
            }
        }
        
        if(cJinNum == 88)
        {
            int ibegin = cYinNum - cYinNum/2;
            Vec2 BeginPos;
            int cHeight = (winSize.width/2-50);
            //得到起始点
            BeginPos.x =  (winSize.width/2 - cHeight);
            BeginPos.y =  winSize.height/2;
            //Rect cNowRect[9];
            Vec2 vPos[56];
            for(int k =0; k<14; k++)
            {
                for(int i=0; i< 2; i++)
                {
                    for(int j=0; j<2; j++)
                    {
                        vPos[k*4+i*2+j].x = BeginPos.x + (j%2)*cHeight  + CCRANDOM_0_1()*cHeight;
                        vPos[k*4+i*2+j].y = BeginPos.y - (i%2)*cHeight  + CCRANDOM_0_1()*cHeight;
                    }
                }
            }
            
            
            for(int i =0; i< 56 ;i++)
            {
                CoinAndAni* coinandani = CoinAndAni::create(3,cShootPos);
                m_CoinAndAni.pushBack(coinandani);
                this->addChild(coinandani);
                //coinandani->CoinMove(Point(Pos.x+i*55,Pos.y+70));
                
                //auto  pTemp = Point(Pos.x+i*55,Pos.y+120);
                //coinandani->setPosition(vPos[i]);
                coinandani->setPosition(Pos);
                coinandani->setScale(0.5f);
                
                CCScaleTo* pScaleTo = CCScaleTo::create(0.7f,1.3f);
                CCMoveTo* pMoveTo = CCMoveTo::create(0.7f,vPos[i]);
                
                CCScaleTo* pReScaleTo = CCScaleTo::create(0.2f,1.0f);
                
                CCSpawn* pSpawan = CCSpawn::create(pScaleTo, pMoveTo, NULL);
                
                DelayTime * dealy = DelayTime::create(2.1f);
                
                //MoveTo* moveTo = MoveTo::create(1.0f ,BeginPos);
                float speed =380;
                
                DelayTime * dealy1 = DelayTime::create(0.9f);
                
                float duration = ccpDistance(coinandani->getPosition(), coinandani->BeginPos) / speed;
                MoveTo* moveTo = MoveTo::create(duration ,coinandani->BeginPos);
                auto ac2 = CallFunc::create(this,callfunc_selector(Fish::MoveOver1));
                
                
                if(i == 1)
                {
                    auto ac2 = CallFunc::create(this,callfunc_selector(Fish::MoveOver1));
                    auto seq = Sequence::create(pScaleTo,pReScaleTo,dealy1,moveTo,ac2,NULL);
                    coinandani->runAction(seq);
                }
                else
                {
                    auto seq = Sequence::create(pScaleTo,pReScaleTo,dealy,moveTo ,NULL);
                    coinandani->runAction(seq);
                }
            }
        }
        
        
        
        if(cJinNum == 70)
        {
            int ibegin = cYinNum - cYinNum/2;
            Vec2 BeginPos = Pos;
            int cHeight = 50;
            //得到起始点
            BeginPos.x -=   cHeight;
            
            //Rect cNowRect[9];
            Vec2 vPos[4];
            
            for(int i=0; i< 2; i++)
            {
                for(int j=0; j<2; j++)
                {
                    vPos[i*2+j].x = BeginPos.x + (j%2)*cHeight  + CCRANDOM_0_1()*cHeight;
                    vPos[i*2+j].y = BeginPos.y - (i%2)*cHeight  + CCRANDOM_0_1()*cHeight;
                }
            }
            
            for(int i =0; i< 4 ;i++)
            {
                CoinAndAni* coinandani = CoinAndAni::create(3,cShootPos);
                m_CoinAndAni.pushBack(coinandani);
                this->addChild(coinandani);
                //coinandani->CoinMove(Point(Pos.x+i*55,Pos.y+70));
                
                //auto  pTemp = Point(Pos.x+i*55,Pos.y+120);
                coinandani->setPosition(vPos[i]);
                DelayTime * dealy = DelayTime::create(2.1f);
                
                float speed =380;
                
                DelayTime * dealy1 = DelayTime::create(0.6f);
                
                float duration = ccpDistance(coinandani->getPosition(), coinandani->BeginPos) / speed;
                MoveTo* moveTo = MoveTo::create(duration ,coinandani->BeginPos);
                auto ac2 = CallFunc::create(this,callfunc_selector(Fish::MoveOver1));
                if(i == 1)
                {
                    auto ac2 = CallFunc::create(this,callfunc_selector(Fish::MoveOver1));
                    auto seq = Sequence::create(dealy ,moveTo,dealy1,ac2,NULL);
                    coinandani->runAction(seq);
                }
                else
                {
                    auto seq = Sequence::create(dealy,moveTo ,NULL);
                    coinandani->runAction(seq);
                }
            }
        }
        
        
    }
    else
    {
        
        if(cYinNum !=0)
        {
            int ibegin = cYinNum - cYinNum/2;
            
            Pos.x -= ibegin* 55;
            for(int i =0; i< cYinNum; i++)
            {
                CoinAndAni* coinandani = CoinAndAni::create(1,cShootPos);
                m_CoinAndAni.pushBack(coinandani);
                this->addChild(coinandani);
                //coinandani->CoinMove(Point(Pos.x+i*55,Pos.y+70));
                
                auto  pTemp = Point(Pos.x+i*55,Pos.y+120);
                coinandani->setPosition(pTemp);
                
                JumpTo *jump1  = JumpTo::create(0.5f,pTemp,60,1);
                JumpTo *jump2  = JumpTo::create(0.6f,pTemp,50,1);
                //JumpTo *jump3  = JumpTo::create(0.5f,pTemp,35,1);
                //MoveTo* moveTo = MoveTo::create(1.0f ,BeginPos);
                float speed =480;
                float duration = ccpDistance(coinandani->getPosition(), coinandani->BeginPos) / speed;
                MoveTo* moveTo = MoveTo::create(duration ,coinandani->BeginPos);
                auto ac2 = CallFunc::create(this,callfunc_selector(Fish::MoveOver1));
                
                
                if(i == (cYinNum-1))
                {
                    auto ac2 = CallFunc::create(this,callfunc_selector(Fish::MoveOver1));
                    auto seq = Sequence::create(jump1,jump2,moveTo,ac2,NULL);
                    coinandani->runAction(seq);
                }
                else
                {
                    auto seq = Sequence::create(jump1,jump2,moveTo,NULL);
                    coinandani->runAction(seq);
                }
            }
        }
        else
        {
            int ibegin = cJinNum - cJinNum/2;
            
            Pos.x -= ibegin* 42;
            for(int i =0; i< cJinNum; i++)
            {
                CoinAndAni* coinandani = CoinAndAni::create(2,cShootPos);
                m_CoinAndAni.pushBack(coinandani);
                this->addChild(coinandani);
                //coinandani->CoinMove(Point(Pos.x+i*55,Pos.y+70));
                
                
                auto  pTemp = Point(Pos.x+i*55,Pos.y+120);
                coinandani->setPosition(pTemp);
                
                JumpTo *jump1  = JumpTo::create(0.5f,pTemp,60,1);
                JumpTo *jump2  = JumpTo::create(0.6f,pTemp,50,1);
                //JumpTo *jump3  = JumpTo::create(0.5f,pTemp,35,1);
                //MoveTo* moveTo = MoveTo::create(1.0f ,BeginPos);
                float speed =480;
                float duration = ccpDistance(coinandani->getPosition(), coinandani->BeginPos) / speed;
                MoveTo* moveTo = MoveTo::create(duration ,coinandani->BeginPos);
                
                
                if(i == (cJinNum-1))
                {
                    auto ac2 = CallFunc::create(this,callfunc_selector(Fish::MoveOver1));
                    
                    auto seq = Sequence::create(jump1,jump2,moveTo,ac2,NULL);
                    coinandani->runAction(seq);
                }
                else
                {
                    auto seq = Sequence::create(jump1,jump2,moveTo,NULL);
                    coinandani->runAction(seq);
                } 
            }
        } 
    }
    
    
    
}






void Fish::MoveOver1()
{  
    for(int i=0; i< m_CoinAndAni.size(); i++)
    {
        m_CoinAndAni.at(i)->stopAllActions();
        this->removeChild(m_CoinAndAni.at(i),true);
    } 
    m_CoinAndAni.clear();
    
    int cTempNum = 22;
    if(GameScene::cGameType == 1)
    {
        if(iShootPos == 4)
        {
            if(cTempNum<60)
            {

				GameBegin::playSound("wfcoin3.mp3");
			}
			else
			{
				GameBegin::playSound("wfcoin4.mp3");
			}
		}
		
	}
	else
	{
		if(cTempNum<60)
		{

			GameBegin::playSound("wfcoin3.mp3");
		}
		else
		{

			GameBegin::playSound("wfcoin4.mp3");
		}
	} 

}

void Fish::FishTeXiaoOver(float delat)
{

	for(int i=40; i<49; i++)
	{
		if(this->getChildByTag(i) != NULL)
		{
			this->getChildByTag(i)->setVisible(false);
		}
	} 
} 

 
 
void Fish::FishBeginTexiao(float delat)
{
 
    if(_type< 18)
    {
        AddCoin(_fishSprite->getPosition(),m_iFishType,iShootPos);
       // this->removeChild(_fishSprite,false);
        _fishSprite->setVisible(false);
        
        LabelFishNum = Label::create();
        LabelFishNum->setCharMap("img/goldword.png",36,44 ,'0');
        this->addChild(LabelFishNum,50);
        LabelFishNum->setScale(0.6f);
        
        Point cTempPos = _fishSprite->getPosition();
     
            cTempPos.y += 77;
        
        LabelFishNum->setPosition(cTempPos);
        char cTmepNum[15] = {0};
        sprintf(cTmepNum,"%d",EndNum);
        LabelFishNum->setString( cTmepNum);
        
        LabelFishNum->setOpacity(220);
        MoveTo *labelmove = MoveTo::create(1.5f,Point(cTempPos.x,cTempPos.y+60));
        ScaleTo *ac8=CCScaleTo::create(0.3f, 1.0);
        ScaleTo *ac9=CCScaleTo::create(0.3f, 0.9);
        FadeOut *ac14=FadeOut::create(1.5f);
        CCSpawn *spawn=CCSpawn::create(labelmove,ac14,NULL);
        
        CCFiniteTimeAction* seq = CCSequence::create(ac8,ac9,spawn, NULL);  
        LabelFishNum->runAction(seq);  
        
    }
    else
    {
        
        AddCoin(_fishSprite->getPosition(),m_iFishType,iShootPos,true);
      //  this->removeChild(_fishSprite,false);
        _fishSprite->setVisible(false);
        
        LabelFishNum = Label::create();
        LabelFishNum->setCharMap("img/goldword.png",36,44 ,'0');
        this->addChild(LabelFishNum,50);
        LabelFishNum->setScale(0.6f);
        
        Point cTempPos = _fishSprite->getPosition();
        
        
        cTempPos.y += 60;
        
        LabelFishNum->setPosition(cTempPos);
        char cTmepNum[15] = {0};
        sprintf(cTmepNum,"%d",EndNum);
        LabelFishNum->setString( cTmepNum);
        
        LabelFishNum->setOpacity(220);
        MoveTo *labelmove = MoveTo::create(1.5f,Point(cTempPos.x,cTempPos.y+60));
        ScaleTo *ac8=CCScaleTo::create(0.3f, 1.0);
        ScaleTo *ac9=CCScaleTo::create(0.3f, 0.9);
        FadeOut *ac14=FadeOut::create(1.5f);
        CCSpawn *spawn=CCSpawn::create(labelmove,ac14,NULL);
        
        CCFiniteTimeAction* seq = CCSequence::create(ac8,ac9,spawn, NULL);
        LabelFishNum->runAction(seq);
        Point pos = _fishSprite->getPosition();
        
        if(bBaoJi == true)
        {
            GameBegin::playSound("Bigdie01.mp3");
            GameScene::bSaJingbi = true;
            GameScene::bBaoZha = true;
            GameScene::DeadFishPos = _fishSprite->getPosition();
            
            auto FishNumFontBoss = Label::create();
            FishNumFontBoss->setCharMap("img/bfishnum.png",35,57, '0');
            
            char cBigBossNum[15];
            sprintf(cBigBossNum,"%d",EndNum);
            FishNumFontBoss->setString(cBigBossNum);
            FishNumFontBoss->setTag(40);
            FishNumFontBoss->setAnchorPoint(Vec2(0.5f,0.5f));
            
            auto Baoji = Sprite::createWithSpriteFrameName("baoji.png");
            Baoji->setPosition(Point(winSize.width*0.5,winSize.height*0.6));
            this->addChild(Baoji);
            Baoji->setScale(1.21);
            Blink *ac10=Blink::create(2.0f, 2);
            Baoji->runAction(ac10);
            Baoji->setTag(41);
            
            
            
            Vec2 pos;
            Vec2 posnum;
            if(GameScene::cGameType == 1)
            {
                
                AllRobot::shanshan = true;
                Baoji->addChild(FishNumFontBoss);
                FishNumFontBoss->setScale(2.0f);
                FishNumFontBoss->setPosition(Vec2(280,-50));
                
                if(iShootPos == 0||(iShootPos == 4 && GameScene::cSelfPos == 0))
                {
                    pos = Vec2(  CannonLayer::robotPos1,visibleSize.height*0.36);
                    
                }
                else if(iShootPos == 1||(iShootPos == 4 && GameScene::cSelfPos == 1))
                {
                    pos = Vec2(  CannonLayer::robotPos2,visibleSize.height*0.36);
                }
                else if(iShootPos == 2)
                {
                    pos = Vec2(  CannonLayer::robotPos1,visibleSize.height*0.72);
                    
                }
                else if(iShootPos == 3)
                {
                    pos = Vec2(  CannonLayer::robotPos2,visibleSize.height*0.72);
                }
                
                Baoji->runAction(Sequence::create(DelayTime::create(3.0f),Spawn::create(MoveTo::create(0.5f,pos),ScaleTo::create(0.5f,0.5),nullptr),nullptr));
                
            }
            else
            {
                
                this->addChild(FishNumFontBoss);
                FishNumFontBoss->setScale(2.0f);
                FishNumFontBoss->setPosition(winSize.width * 0.5,winSize.height* 0.3);
                Baoji->setPosition(Point(winSize.width*0.5,winSize.height*0.6));
            }  
            
        }
        else
        { 
            if(_type > 29 && _type < 45  && GameScene::cGameType != 2)
            {
                _type = 17;
            }
            if(_type>16 )
            {
                if(GameScene::cGameType == 1)
                {
                    if(_type == 21)
                    {
                        _type = 23;
                    }						
                    else if( _type == 22)
                    {
                        _type = 21;
                    }
                    else if(_type == 23)
                    {
                        _type = 22;
                    }
                    
                } 
                
                if(noupdate == true)
                {
                    int a =33;
                }
                ShowBigFishFrame(EndNum);
            } 
            
        }  
        
        
        
        if(bBaoJi == true && GameScene::cGameType == 1)
        {
            scheduleOnce(schedule_selector(Fish::FishTeXiaoOver),7.5f);
        }
        else
        {
            scheduleOnce(schedule_selector(Fish::FishTeXiaoOver),4.5f);  
        }
        
    }
	

} 

void Fish::beCaught_CallFunc()
{ 
	 
	bDead = true;
	if(_type > 29 && _type< 32 && GameScene::cGameType != 2)
	{ 
		_fishSpriteTwo->setVisible(false);
		_fishthree->setVisible(false);
		_fishkong->setVisible(false);

		_fishthree->stopAllActions();
		_fishSpriteTwo->stopAllActions();
		_fishkong->stopAllActions();
	}	

	else if(_type > 31 && _type< 37 && GameScene::cGameType != 2)
	{
		_fishSpriteTwo->setVisible(false);
		_fishSprite->setVisible(false); 

		_fishSprite->stopAllActions(); 
		_fishSpriteTwo->stopAllActions(); 

	}  

	for(int i=40; i<48; i++)
	{
		if(this->getChildByTag(i) != NULL)
		{
			this->getChildByTag(i)->setVisible(false);
		} 

	}

	_fishSprite->stopAllActions();   
	FadeOut *ac14=FadeOut::create(1.0f);  
	_fishSprite->runAction(ac14);


} 
 
void Fish::ShowBigFishFrame(int num)
{
 
	Vec2 pos;

    
    if(m_iFishType == 20)
    {
        if(iShootPos == 4)
            AllRobot::shanshan = true;
        GameBegin::playSound("deadgirl.mp3");
        //return  true;
    }
    else if(m_iFishType == 21)
    {
        if(iShootPos == 4)
            AllRobot::shanshan = true;
        GameBegin::playSound("die03.mp3");
        //return  true;
    }
    else if(m_iFishType == 22)
    {
        if(iShootPos == 4)
            AllRobot::shanshan = true;
        GameBegin::playSound("deadgirl.mp3");
       // return  true;
    }
   else  if(m_iFishType == 23)
    {
        if(iShootPos == 4)
            AllRobot::shanshan = true;
        //GameBegin::playSound("panzi.mp3");
        GameBegin::playSound("die06.mp3");
        //return  true;
    }
    else if(m_iFishType == 24 ||  m_iFishType == 25)
    {
        GameBegin::playSound("Bigdie01.mp3");
        //return  true;
    }
    
    if(m_iFishType > 29)
    {
        //GameBegin::playSound("panzi.mp3");
        if(m_iFishType == 30)
        {
            GameBegin::playSound("die03.mp3");
        }
        if(m_iFishType == 31)
        {
            GameBegin::playSound("die06.mp3");
        }
        if(m_iFishType > 31)
        {
            if(iShootPos == 4)
                AllRobot::shanshan = true;
            if(CCRANDOM_0_1()*100 > 50)
            {
                GameBegin::playSound("threekillone.mp3");
            }else
            {
                GameBegin::playSound("threekilltwo.mp3");
            }
        }
    }
        
        
	float matchsc = 0.7;
	if(GameScene::cGameType == 1)
	{
		if(iShootPos == 0||(iShootPos == 4 && GameScene::cSelfPos == 0))
		{
			pos = Vec2( CannonLayer::robotPos1,visibleSize.height*0.37);
		}
		else if(iShootPos == 1||(iShootPos == 4 && GameScene::cSelfPos == 1))
		{
			pos = Vec2( CannonLayer::robotPos2,visibleSize.height*0.37);
		}
		else if(iShootPos == 2)
		{
			pos = Vec2(  CannonLayer::robotPos1,visibleSize.height*0.73);
		}
		else if(iShootPos == 3)
		{
			pos = Vec2(  CannonLayer::robotPos2,visibleSize.height*0.73);
		} 
	}
	else
	{
		 pos = _fishSprite->getPosition();
	}
		//≈Ã◊”∫Õ±¶œ‰Ω¯¿¥∂º «fishtypeŒ™12£ª 
	if(_type>20)
	{  
		GameScene::bBaoZha = true; 
		GameScene::DeadFishPos =  _fishSprite->getPosition(); 
		if(GameScene::cGameType != 1)
		pos = Point(visibleSize.width/2,visibleSize.height/2+10);  
		

		auto star3 = Sprite::createWithSpriteFrameName("bfisguang.png");
		star3->setPosition(Point(pos.x,pos.y));
		this->addChild(star3);
        star3->setScale(1.21);
		if(_type < 19)
		{ 
			star3->setScale(0.6);
		} 
		if(GameScene::cGameType == 1)
		{
			star3->setScale(0.7);
		}
		star3->setTag(42);
	}  
	if(_type< 21 )
	{
		 
        Animation* fishAnimation = AnimationCache::getInstance()->getAnimation("baozaframe"); 
		Animate*  fishAnimate = Animate::create(fishAnimation);
        auto * anispr = Sprite::create();
        
        anispr->setPosition(_fishSprite->getPosition());
        this->addChild(anispr);
        anispr->runAction(fishAnimate);
        //anispr->setScale(1.2f);
        anispr->setTag(43);
        anispr->setRotation(CCRANDOM_0_1()*360);
        auto * wfsc1 =  ScaleTo::create(0.1f,1.6f);
        auto * wfsc2 = DelayTime::create(0.25f);
        auto * wfsc3 = ScaleTo ::create(0.1f,1.3f);
        auto * wfsc5 = DelayTime::create(0.25f);
        auto * wfsc4 = Sequence::create(wfsc1,wfsc2,wfsc3,wfsc5,RemoveSelf::create(), NULL);
        anispr->runAction(wfsc4);

	}
	else 
	{
        string tmpImgPath = "bfishbgguang.png";
        bool isZp = false;
        if((_type ==21 && (iRoomType == 90 || iRoomType == 2)) || (_type ==22 && (iRoomType == 93 || iRoomType == 90|| iRoomType == 92 || iRoomType == 2)))
        {
            tmpImgPath = "zp2.png";
            isZp = true;
        }
		auto temp2 = Sprite::createWithSpriteFrameName(tmpImgPath.c_str());
		temp2->setPosition(pos);
		this->addChild(temp2);

		if(GameScene::cGameType == 1 && !isZp)
		{
			temp2->setScale(0.75);
		}

		RotateBy *ac9=RotateBy::create(3.5f, 720);  
		auto* seq1 = Sequence::create(ac9, NULL);
		temp2->runAction(seq1);   
		temp2->setTag(44);


		auto LabelFishNum = Label::create();  
		LabelFishNum->setCharMap("img/bfishnum.png",35,57,'0');
		this->addChild(LabelFishNum,200); 

	
		LabelFishNum->setPosition(Point(pos.x,pos.y));
		char cTmepNum[15] = {0};
		sprintf(cTmepNum,"%d",num);
		LabelFishNum->setString( cTmepNum);  
		LabelFishNum->setScale(1.2f);
	
		if(_type > 18)
		{
			LabelFishNum->setPosition(Point(pos.x,pos.y+15));

		} 
		if(GameScene::cGameType == 1  )
		{
			LabelFishNum->setScale(0.73f);
			LabelFishNum->setPosition(Point(pos.x,pos.y-5));
		}
		RotateTo *r1=RotateTo::create(0.5f, 20); 
		RotateTo *r2=RotateTo::create(0.5f, -20); 
		RotateTo *r3=RotateTo::create(0.5f, 20); 
		RotateTo *r4=RotateTo::create(0.5f, -20); 
		RotateTo *r5=RotateTo::create(0.5f, 20); 
		RotateTo *r6=RotateTo::create(0.5f, -20);  
		RotateTo *r7=RotateTo::create(0.5f, 20);  
		RotateTo *r8=RotateTo::create(0.5f, -20);  
		RotateTo *r9=RotateTo::create(0.5f, 20); 
		auto* seq = Sequence::create(r1,r2,r3,r4,r5,r6,r7,r8,r9,NULL);
		LabelFishNum->runAction(seq);
		LabelFishNum->setTag(45);

	}
	if(_type <25 && _type >20 )
	{
		auto star = Sprite::createWithSpriteFrameName("bfishstar.png");
		star->setPosition(Point(pos.x,pos.y+90));
		this->addChild(star);
		star->setTag(46);

		if(GameScene::cGameType == 1   )
		{
			star->setScale(matchsc);
		}
        if((_type ==21 && (iRoomType == 90 || iRoomType == 2)) || (_type ==22 && (iRoomType == 93 || iRoomType == 90 || iRoomType == 92 || iRoomType == 2)))
        {
            star->setVisible(false);
        }
        
	}  
	if(_type <21)
		return;
	
	char cTempNum2[30];

	int iTempRoom  = iRoomType;
	if(iTempRoom  < 2 )
	{
		iTempRoom = 0;
	}
	if(_type ==21)
	{ 
		if(iRoomType == 90)
		{
            auto imageBG = Sprite::createWithSpriteFrameName("zp2_2.png");
            imageBG->setPosition(Point(pos.x,pos.y-60));
            imageBG->setTag(48);
            this->addChild(imageBG);
            
			sprintf(cTempNum2,"bfishfont8_2.png");
		}
		else if(iRoomType == 91)
		{
			sprintf(cTempNum2,"bfishfont10_2.png");
		}
		else if(iRoomType== 92)
		{
			sprintf(cTempNum2,"bfishfont10_2.png");
		}
		else if(iRoomType== 93)
		{
			sprintf(cTempNum2,"bfishfont10_2.png");
		}
        else if(iRoomType == 2)
        {
            auto imageBG = Sprite::createWithSpriteFrameName("zp2_2.png");
            imageBG->setPosition(Point(pos.x,pos.y-60));
            imageBG->setTag(48);
            sprintf(cTempNum2,"bfishfont2_1.png");
        }
		else
		{
		//	sprintf(cTempNum2,"bfishfont%d_%d.png",iTempRoom,1);
            sprintf(cTempNum2,"bfishfont5.png");
		} 
	}
	else if(_type == 22)
	{
		if(iRoomType == 90)
		{
            auto imageBG = Sprite::createWithSpriteFrameName("zp2_2.png");
            imageBG->setPosition(Point(pos.x,pos.y-60));
            imageBG->setTag(48);
            this->addChild(imageBG);

			sprintf(cTempNum2,"bfishfont0_2.png");
		}
		else if(iRoomType == 91)
		{
			sprintf(cTempNum2,"bfishfontwf.png");
		}
		else if(iRoomType  == 92)
		{
            
            auto imageBG = Sprite::createWithSpriteFrameName("zp2_2.png");
            imageBG->setPosition(Point(pos.x,pos.y-60));
            imageBG->setTag(48);
            this->addChild(imageBG);
            
			sprintf(cTempNum2,"bfishfont9_2.png");
		 
		}
		else if(iRoomType== 93)
		{
            auto imageBG = Sprite::createWithSpriteFrameName("zp2_2.png");
            imageBG->setPosition(Point(pos.x,pos.y-60));
            imageBG->setTag(48);
			sprintf(cTempNum2,"bfishfont9_2.png"); 
		}
        else if(iRoomType == 2)
        {
            auto imageBG = Sprite::createWithSpriteFrameName("zp2_2.png");
            imageBG->setPosition(Point(pos.x,pos.y-60));
            imageBG->setTag(48);
            sprintf(cTempNum2,"bfishfont2_2.png");
        }
		else
		{
		//	sprintf(cTempNum2,"bfishfont%d_%d.png",iTempRoom,2);
            sprintf(cTempNum2,"bfishfont5.png");
		}
		
	} 
	else
	{ 
		memcpy(cTempNum2,"bfishfont5.png",20);
	}

	auto star1 = Sprite::createWithSpriteFrameName(cTempNum2); 
	star1->setPosition(Point(pos.x,pos.y-90));
	this->addChild(star1);

	if(GameScene::cGameType == 1)
	{
		star1->setScale(matchsc);
		if(_type != 21 &&_type!=22)
		star1->setPosition(Point(pos.x,pos.y-30));
	}
	star1->setTag(47);
    
    Sprite* imageBG = (Sprite*)this->getChildByTag(48);
    if(imageBG)
    {
        star1->setPositionY(imageBG->getPositionY());
    }
}

 
void Fish::Reset(int iFishType)
{
	m_iMainID = 0;
  
	m_iSubID = 0;
	m_iTrackID = 0;
 

	m_trackFish.Reset(m_iTrackID,false);

	m_iX = 0;
	m_iY = 0;
	m_iSpeed = 0;
} 

bool Fish::SetGroupFishInfo( int iMainID,int iSubID,int iFishType,int iTrackID,bool bBigFish, Point pPoint , int iNowTrackIndex )
{
	m_iMainID = iMainID;
	m_iSubID = iSubID;
	
  
 


	mMovePos = pPoint;
	m_iSpeed = 0;
	m_iTrackID = iTrackID;
	m_trackFish.Reset(m_iTrackID,bBigFish,iNowTrackIndex);
	TrackPointDef *pTrackPt = m_trackFish.GetNextTrackPoint(true);
	 

	m_iX =pTrackPt->mPoint.x;
			
	if(m_iX > 1024)
	{
		_fishSprite->setFlipX(true);
	}
	m_iY =  768-pTrackPt->mPoint.y; 
	if(pTrackPt)
	{

	}
	else
	{
		return false;
	}


	// this->setRotation(-180);
	//GoMove();
	m_fTime = 0;
	m_fUpdateTime = 0; 
	//schedule(schedule_selector(Fish::UpdateFishwf),_GAME_LOOP_TICK_);
		  

	return true;
}

bool Fish::SetFishInfo( int iMainID,int iSubID,int iFishType,int iTrackID,bool bBigFish, int iNowTrackIndex /*= -1*/  )
{
	m_iMainID = iMainID;
	m_iSubID = iSubID;
	  
 
	_fishSprite->setFlipX(false);
	_fishSprite->setFlipY(false);
	

	  
	m_iSpeed = 0; 
	m_iTrackID = iTrackID;
	m_trackFish.Reset(m_iTrackID,bBigFish,iNowTrackIndex);
	TrackPointDef *pTrackPt = m_trackFish.GetNextTrackPoint(true);


	m_iX =pTrackPt->mPoint.x;

	
	if(m_iX > 1024 && m_trackFish.bFanZhuan == false && GameScene::cGameType != 2)
	{
		if(_type == 45)
		{
			ShipNum->setRotation(90);
		}
		if(_type > 29 && _type< 32 && GameScene::cGameType != 2)
		{
			_fishSpriteTwo->setFlipX(true);
			_fishthree->setFlipX(true);
			_fishkong->setFlipX(true);
		}
		else if(_type > 31 && _type <  45&& GameScene::cGameType != 2)
		{
			_fishSpriteTwo->setFlipX(true);
		}
		else if(_type != 45)
		{
			_fishSprite->setFlipX(false);
			_fishSprite->setFlipY(false); 
		} 
	}

	if(m_trackFish.bFanZhuan == true)
	{
		if(_type > 29 && _type< 32 && GameScene::cGameType != 2)
		{
			_fishSpriteTwo->setFlipY(true);
			_fishthree->setFlipY(true);
			_fishkong->setFlipY(true); 
		}
		else if(_type > 31 && _type <45  && GameScene::cGameType != 2)
		{
			_fishSpriteTwo->setFlipY(true);
		}
		else
		{
			_fishSprite->setFlipX(true);
			_fishSprite->setFlipY(true); 
		}
	}
	if(pTrackPt)
	{
	/*
		if(_type > 29 && _type< 32 && GameScene::cGameType == 0)
		{
			this->_fishSprite->setPosition(Point(m_iX,m_iY));

		 	_fishkong->setPosition(Point(m_iX,m_iY));
			float dAngle =  pTrackPt->dAngleValue;
			 this->_fishkong->setRotation(dAngle);
		}
		else if(_type > 31 && GameScene::cGameType == 0)
		{
			this->_fishSprite->setPosition(Point(m_iX,m_iY));

			_fishSpriteTwo->setPosition(Point(m_iX,m_iY));
			float dAngle =  pTrackPt->dAngleValue;
			this->_fishSpriteTwo->setRotation(dAngle); 

		} 
		else
		{
			this->_fishSprite->setPosition(Point(m_iX,m_iY));
			float dAngle =  pTrackPt->dAngleValue;
			this->_fishSprite->setRotation(dAngle);
		}
	
		 
		 */
	}
	else
	{
		return false;
	}  

	 

	// this->setRotation(-180);
	//GoMove();
	m_fTime = 0;
	m_fUpdateTime = 0;
	if(m_iFishType >22)
	BossType = m_iFishType - 20;




	if(_type >8&&GameScene::cGameType == 1 )
	{
		if(GameScene::cSelfPos == 0)
		{
			int iTrackID = -1; 
			TrackPointDef *pTrackPt = m_trackFish.GetNextTrackPoint(); 
			if(pTrackPt->mPoint.x <  winSize.width/2 && pTrackPt->mPoint.x > 0 &&pTrackPt->mPoint.y <300)
			{
				iTrackID = FishTrack::GetRandTrackID(12);
				m_iTrackID = iTrackID; 
				SetFishInfo(0,0,_type,iTrackID,true); 
			}
			pTrackPt = m_trackFish.GetNextTrackPoint(); 
			if(pTrackPt->mPoint.x <  winSize.width/2 && pTrackPt->mPoint.x > 0 &&pTrackPt->mPoint.y <300)
			{
				iTrackID = FishTrack::GetRandTrackID(12);
				m_iTrackID = iTrackID; 
				SetFishInfo(0,0,_type,iTrackID,true); 
			}

		}
		else 
		{
			int iTrackID = -1; 
			TrackPointDef *pTrackPt = m_trackFish.GetNextTrackPoint(); 
			if(pTrackPt->mPoint.x <  winSize.width && pTrackPt->mPoint.x > winSize.width/2 &&pTrackPt->mPoint.y <200)
			{
				iTrackID = FishTrack::GetRandTrackID(12);
				m_iTrackID = iTrackID; 
				SetFishInfo(0,0,_type,iTrackID,true); 
			}
			pTrackPt = m_trackFish.GetNextTrackPoint(); 
			if(pTrackPt->mPoint.x <  winSize.width && pTrackPt->mPoint.x > winSize.width/2 &&pTrackPt->mPoint.y <200)
			{
				iTrackID = FishTrack::GetRandTrackID(12);
				m_iTrackID = iTrackID; 
				SetFishInfo(0,0,_type,iTrackID,true); 
			}
		}

	}


	 
	//	schedule(schedule_selector(Fish::UpdateFishwf),_GAME_LOOP_TICK_); 
	return true;
}

 


void Fish::UpdateFishwf(float delta)
{ 
	//cocos2d::log("scene init UpdateFishwf1");
    if(this->bDead == false)
	{
        if(noupdate == true)
            return;
		if(_type == 45 &&  GameScene::cGameType != 2)
		{
			m_iShipIndex++;
			if(m_iShipIndex >= m_iShipMax)
			{
				m_iShipIndex = 0;
				m_iShipMax =20 + CCRANDOM_0_1()* 40;
				if(m_iLeiJiChongZhi == 0)
				{
					m_iShipNum += CCRANDOM_0_1()*500;
					char cNum [20];
					sprintf(cNum,"%d",(int)m_iShipNum);
					ShipNum->setString(cNum);
				} 
				else 
				{
					int iBase = CannonLayer::cBeiShu[GameHallLayer::sceneHighPao-1];
					//int oo = iBase/2 + CCRANDOM_0_1()*(iBase -iBase/2 );
					m_iShipNum += iBase/2 + CCRANDOM_0_1()*(iBase -iBase/2 );

					char cNum [20];
					sprintf(cNum,"%d",(int)m_iShipNum);
					ShipNum->setString(cNum);					
				}
			} 
		}
		if(_type == 37 && GameScene::cGameType != 2)
		{
			m_iSpacTime++;
			if(m_iSpacTime >700)
			{
				 bDead = true;
				_fishSprite->setVisible(false); 

				//CCFadeOut *ac14=CCFadeOut::create(2.0f);  
				//_fishkong->runAction(ac14);
				//_fishSprite->runAction(ac14);

				_type = 40;
				this->getParent()->removeChild(this, true);
				return;
			}
			else if(m_iSpacTime >800)
			{
				//_fishSprite->stopAllActions();
				//_fishkong->stopAllActions();

				//_fishSprite->setVisible(false);
				//_fishkong->setVisible(false);
				//bDead = true;
				_type = 40;
				this->getParent()->removeChild(this, true);
			}
			return;
		}
		if(bSlow == true)
		{
			return;
		} 

			if(m_iTrackID == 0) //◊‘”…”„
			{
		  

			/*	Point start = this->getParent()->convertToWorldSpace(this->getPosition());
				float speed = ccpDistance(destination, start) / 200;
				CCMoveTo* moveTo = CCMoveTo::create(speed ,destination);
				CCCallFunc* callfunc = CCCallFunc::create(this, callfunc_selector(Fish::moveEnd));

				CCFiniteTimeAction* seq = CCSequence::create(moveTo, callfunc, NULL);
				seq->setTag(FishAniTag);
				this->runAction(seq);*/
			} 
			else
			{ 
			 
			
				TrackPointDef *pTrackPt = m_trackFish.GetNextTrackPoint(); 
				if(FishLayer::bMoveFast == true && FishLayer::bYuZheng == false)
				{
					if(pTrackPt == NULL)
					{
						beCaught_CallFunc();	
						return;
					}
					else 
					{
						pTrackPt = m_trackFish.GetNextTrackPoint(); 
						if(pTrackPt == NULL)
						{
							beCaught_CallFunc();
							return;
						}
						else
						{
							pTrackPt = m_trackFish.GetNextTrackPoint(); 
							if(pTrackPt == NULL)
							{
								beCaught_CallFunc();
								return;
							}
							else
							{
								pTrackPt = m_trackFish.GetNextTrackPoint(); 
								if(pTrackPt == NULL)
								{
									beCaught_CallFunc();
									return;
								}
							}
						}
					}
				}
				if(pTrackPt == NULL)
				{
                 
 
					if(_type>29 && _type< 45&& GameScene::cGameType != 2)
					{
						beCaught_CallFunc();
						return;

					} 
					if(_type > 17)
					{
						if(_type>29 && GameScene::cGameType != 2)
						{
							beCaught_CallFunc();
							return;

						} 
						if(GameScene::cGameType != 2)
						{
							//”„”Œ∂Ø2¥ŒBOSS
							cFishBossTime++;
							if(cFishBossTime >1)
							{
								beCaught_CallFunc();
								return;
							}
						}
						int iTrackID = -1; 
						iTrackID = FishTrack::GetRandTrackID(12);
						m_iTrackID = iTrackID; 
						SetFishInfo(0,0,_type,iTrackID,true); 
					}
					else 
					{
						beCaught_CallFunc();
					} 
					return;
				}
				Point pPoint = pTrackPt->mPoint + mMovePos; 
			  
                if(FishLayer::Fishnodown == false)
                {
                    pPoint.y =  pPoint.y - 100;
                }
                else
                {
                    pPoint.y =  pPoint.y + 40;
                }
			 
				 
			 

				if(_type > 29 && _type< 32 && GameScene::cGameType != 2)
				{
					_fishSprite->setPosition(pPoint); 
					_fishkong->setPosition(pPoint); 
					_fishkong->setRotation(pTrackPt->dAngleValue);
				}
				else if(_type > 31 &&_type < 45&& GameScene::cGameType != 2)
				{
					_fishSprite->setPosition(pPoint); 
					_fishSpriteTwo->setPosition(pPoint); 
					_fishSpriteTwo->setRotation(pTrackPt->dAngleValue);
				}
				else
				{
					_fishSprite->setPosition(pPoint);
					_fishSprite->setRotation(pTrackPt->dAngleValue);
				}
		}
	}

	//cocos2d::log("scene init UpdateFishwf2");

}
 
 
 
 



bool Fish::CreateTrackFish(Fish* pFish,int iFishType,bool boss,int  spc)
{
	int iTrackID = -1; //”…”„¿‡–Õ’“µΩ÷∏∂®µƒπÏº£	
	if(spc != 0)
	{
		iTrackID = spc;
		pFish->m_iTrackID = iTrackID;

		pFish->m_trackFish.Reset(iTrackID,true); //ÀÊª˙…˙≥…µƒøœ∂® «¥Û”„
		return true;

	}
 
	if(iFishType == -1)
	{
		int iSpeed = 0;
		pFish->m_iFishType = 0;
	}
	
	if(boss == false)
	{
		iTrackID = FishTrack::GetRandTrackID(iFishType);//ÀÊª˙÷∏∂®”„µƒπÏº£,∑µªÿ-1Œ™¥À”„√ª”–∂‘”¶πÏº£
	}
	else if(boss == true && iFishType >=15)	
	{
		iTrackID = FishTrack::GetTrackIDByFishTaskType(12);//ÀÊª˙÷∏∂®”„µƒπÏº£,∑µªÿ-1Œ™¥À”„√ª”–∂‘”¶πÏº£
	}
	if(iTrackID == -1)
	{
		return false;
	}

	//iTrackID = 5555;

	pFish->m_iTrackID = iTrackID;

	pFish->m_trackFish.Reset(iTrackID,true); //ÀÊª˙…˙≥…µƒøœ∂® «¥Û”„
	return true;
}
 

bool Fish::ifCatchJ(int iPos,float PaoBase,bool bNew)
{   
	if(m_iFishType > 14 &&  GameScene::cGameType == 2)
	{
		return false;
	}
    
	if(m_iFishType == 46)
	{
        
		if(iPos != 4)
		{
			if(CCRANDOM_0_1()*100 < 1.5)
			{
				return true;
			}
		}
		else
		{
            /*int iHuafeiNum = GameBegin::getFileData("wfsound.txt");
            if(iHuafeiNum > 1000)
            {
                if(CCRANDOM_0_1()*100 < 0.05)
                {
                    return true;
                }
                else 
                {
                    return false;
                }
             
            }*/
            if(AllRobot::iRobotWinNum >99)
            {
                return false;
            }
            
            int iLeiji = GameBegin::getFileData("wflei.txt");
            if(iLeiji < 50)
            {
                if(PaoBase < 5000)
                {
                    if(CCRANDOM_0_1()*100 < 0.6)
                    {
                        iHuaFeiNum = 2;
                        iHuaFeiType = 116;
                        return true;
                    }
                }
                if(PaoBase >=  5000 && PaoBase <= 7000)
                {
                    if(CCRANDOM_0_1()*100 < 0.8)
                    {
                        iHuaFeiNum = 2;
                        iHuaFeiType = 116;
                        return true;
                    }
                }
                else if(PaoBase == 8000 || PaoBase == 9000)
                {
                    if(CCRANDOM_0_1()*100 < 0.9)
                    {
                        iHuaFeiNum = 2;
                        iHuaFeiType = 116;
                        return true;
                    }
                }
                else if(PaoBase == 10000)
                {
                    if(CCRANDOM_0_1()*100 < 1.2)
                    {
                        iHuaFeiNum = 3;
                        iHuaFeiType = 117;
                        return true;
                    }
                }
                else
                {
                    
                    return false;
                }
            }
            else if(iLeiji < 500)
            {
                if(PaoBase == 2000)
                {
                    if(CCRANDOM_0_1()*100 < 0.5)
                    {
                        iHuaFeiNum = 6;
                        iHuaFeiType = 122;
                        return true;
                    }
                }
                else if(PaoBase == 3000)
                {
                    if(CCRANDOM_0_1()*100 < 1)
                    {
                        iHuaFeiNum = 7;
                        iHuaFeiType = 123;
                        return true;
                    }
                }
                else if(PaoBase == 4000)
                {
                    if(CCRANDOM_0_1()*100 < 1.5)
                    {
                        iHuaFeiNum = 8;
                        iHuaFeiType = 124;
                        return true;
                    }
                }
                else if(PaoBase >=  5000 && PaoBase <= 7000)
                {
                    if(CCRANDOM_0_1()*100 < 2)
                    {
                        iHuaFeiNum = 9;
                        iHuaFeiType = 125;
                        return true;
                    }
                }
                else if(PaoBase == 8000 || PaoBase == 9000)
                {
                    if(CCRANDOM_0_1()*100 < 2.5)
                    {
                        iHuaFeiNum = 10;
                        iHuaFeiType = 126;
                        return true;
                    }
                }
                else if(PaoBase == 10000)
                {
                    if(CCRANDOM_0_1()*100 < 3)
                    {
                        iHuaFeiNum = 15;
                        iHuaFeiType = 127;
                        return true;
                    }
                }
                else
                {
                    return  false;
                }
            }
            else if(iLeiji < 1000)
            {
             
                
                if(PaoBase == 1000)
                {
                    if(CCRANDOM_0_1()*100 < 1)
                    {
                         iHuaFeiNum = 5;
                        iHuaFeiType = 131;
                        return true;
                    }
                }
                if(PaoBase == 2000)
                {
                    if(CCRANDOM_0_1()*100 < 1.5)
                    {
                        iHuaFeiNum = 6;
                        iHuaFeiType = 132;
                        return true;
                    }
                }
                else if(PaoBase == 3000)
                {
                    if(CCRANDOM_0_1()*100 < 2)
                    {
                        iHuaFeiNum = 7;
                        iHuaFeiType = 133;
                        return true;
                    }
                }
                else if(PaoBase == 4000)
                {
                    if(CCRANDOM_0_1()*100 < 2.5)
                    {
                        iHuaFeiNum = 8;
                        iHuaFeiType = 134;
                        return true;
                    }
                }
                
                
                else if(PaoBase >=  5000 && PaoBase <= 7000)
                {
                    if(CCRANDOM_0_1()*100 < 3)
                    {
                        iHuaFeiNum = 9;
                        iHuaFeiType = 135;
                        return true;
                    }
                }
                else if(PaoBase == 8000 || PaoBase == 9000)
                {
                    if(CCRANDOM_0_1()*100 < 3.5)
                    {
                        iHuaFeiNum = 10;
                        iHuaFeiType = 136;
                        return true;
                    }
                }
                else if(PaoBase == 10000)
                {
                    if(CCRANDOM_0_1()*100 < 4)
                    {
                        iHuaFeiNum = 15;
                        iHuaFeiType = 137;
                        return true;
                    }
                }
                else
                {
                    return  false;
                }
            }
            else
            {
                if(PaoBase == 1000)
                {
                    if(CCRANDOM_0_1()*100 < 2)
                    {
                        iHuaFeiNum = 5;
                        iHuaFeiType = 141;
                        return true;
                    }
                }
                if(PaoBase == 2000)
                {
                    if(CCRANDOM_0_1()*100 < 2.5)
                    {
                        iHuaFeiNum = 6;
                        iHuaFeiType = 142;
                        return true;
                    }
                }
                else if(PaoBase == 3000)
                {
                    if(CCRANDOM_0_1()*100 < 3)
                    {
                        iHuaFeiNum = 7;
                        iHuaFeiType = 143;
                        return true;
                    }
                }
                else if(PaoBase == 4000)
                {
                    if(CCRANDOM_0_1()*100 < 3.5)
                    {
                        iHuaFeiNum = 8;
                        iHuaFeiType = 144;
                        return true;
                    }
                }
                else if(PaoBase >=  5000 && PaoBase <= 7000)
                {
                    if(CCRANDOM_0_1()*100 < 4)
                    {
                        iHuaFeiNum = 9;
                        iHuaFeiType = 145;
                        return true;
                    }
                }
                else if(PaoBase == 8000 || PaoBase == 9000)
                {
                    if(CCRANDOM_0_1()*100 < 4.5)
                    {
                        iHuaFeiNum = 10;
                        iHuaFeiType = 146;
                        return true;
                    }
                }
                else if(PaoBase == 10000)
                {
                    if(CCRANDOM_0_1()*100 < 5)
                    {
                        iHuaFeiNum = 15;
                        iHuaFeiType = 147;
                        return true;
                    }
                }
                else
                {
                    return  false;
                }
            }
            
            
		} 
		return false;
	}
	if(m_iFishType == 45)
	{

        if(PaoBase < 10)
            return false;
		if(m_iLeiJiChongZhi == 0)
		{
            float tmpGailv = CCRANDOM_0_1() * 100;
            if(PaoBase == 10 && tmpGailv < 0.08f)
            {
                UserDefault::getInstance()->setIntegerForKey("leijichongzhicaijin",0);
                m_iLeiJiChongZhi = 0;
                return true;
            }
            else if(tmpGailv < 0.13f)
            {
				UserDefault::getInstance()->setIntegerForKey("leijichongzhicaijin",0);
				m_iLeiJiChongZhi = 0; 
                return true;
            }
			return false;
		}
		else
		{ 
			if(ShipGailv == 0)
			{
				float cTemp = 10+CCRANDOM_0_1()*50;
				double a = (m_iShipNum/m_iLeiJiChongZhi);
				double b = (PaoBase/(float)CannonLayer::cBeiShu[GameHallLayer::sceneHighPao-1]);
				ShipGailv = 1/ a*b* cTemp *100;
			} 
			float tmpGailv = CCRANDOM_0_1() * 100; 
			if(ShipGailv< 0.1f)
			{
				ShipGailv = 0.1f;
			}
			if(tmpGailv < ShipGailv )
			{
                if(GameScene::cGameType == 1&& iPos != 4)
                {
                   return true;
                }
				UserDefault::getInstance()->setIntegerForKey("leijichongzhicaijin",0);
				m_iLeiJiChongZhi = 0;
				return true;
			}
			else
				return false;
		}
	}

	//return false;
	float tmpGailv = CCRANDOM_0_1() * 100;
	int tmpFishType = m_iFishType;
	
  
	if(tmpFishType > 36)
	{
		tmpFishType -= 10;
	}

	else if(tmpFishType > 29)
	{
		tmpFishType -= 4; 
	}
	
	float tmpTTTT = 0;


	if(bNew ==  true && GameScene::cGameType == 0 && tmpFishType < 15 )
	{
		if(PaoBase <  100)
		{
			tmpTTTT = cTeShuPuTong[0][tmpFishType];
		}
		else if(PaoBase < 500)
		{
			tmpTTTT = cTeShuPuTong[1][tmpFishType];
		}
		else 
		{
			tmpTTTT = cTeShuPuTong[2][tmpFishType];
		}
	}
	else if(bNew ==  true && GameScene::cGameType == 1 &&tmpFishType < 18)
	{
		if(PaoBase <  100)
		{
			tmpTTTT = cTeShuBiSai[0][tmpFishType];
		}
		else if(PaoBase < 500)
		{
			tmpTTTT = cTeShuBiSai[1][tmpFishType];
		}
		else 
		{
			tmpTTTT = cTeShuBiSai[2][tmpFishType];
		}
		 
	}
	else if(GameScene::cGameType == 1)
	{
        if(iPos == 4)
        {
            if(GameHallLayer::RoomType !=  89)
            {
                if( GameScene::is_success_load)
                {
                    if(tmpFishType== 23)
                    {
                        int a = 3;
                    }
                    if(tmpFishType== 24)
                    {
                        int a = 3;
                    }
                    if(tmpFishType== 22)
                    {
                        int a = 3;
                    }
                    if(tmpFishType== 21)
                    {
                        int a = 3;
                    }
                    if(tmpFishType== 20)
                    {
                        int a = 3;
                    }
                    if(GameScene::is_jiafen == true)
                    {
                        tmpTTTT = GameScene::gailv_jia[tmpFishType];
                    }
                    else
                    {
                        tmpTTTT = GameScene::gailv_jian[tmpFishType];
                    }
                }
                else
                {
                    tmpTTTT = cMatchRoomGailv[GameHallLayer::bs_moshi - 1][tmpFishType];
                }
            }
            else
            {
                if( GameScene::is_success_load)
                {
                    if(GameScene::is_jiafen == true)
                    {
                        tmpTTTT = GameScene::gailv_jia[tmpFishType];
                    }
                    else
                    {
                        tmpTTTT = GameScene::gailv_jian[tmpFishType];
                    }
                }
                else
                {
                    tmpTTTT = JiuJiSai[tmpFishType];
                }
            }
            
        }
        else
        {
            tmpTTTT = cMatchRoomGailv[GameHallLayer::bs_moshi - 1][tmpFishType];
        }
        
        
	}
	else if(GameScene::cGameType == 0||GameScene::cGameType == 2)
	{
		//tmpTTTT = cFishGailv[2][tmpFishType];
        tmpTTTT = cFishGailv[FishLayer::fishlayerPeriod - 1][tmpFishType];
	}	
	if(iPos == 4)
	{
		
		int iTempMoney = GameBegin::getFileData("jywer.txt");
		
        if(iTempMoney >80000000)
        {
            if(PaoBase < 5000)
            {
               tmpTTTT = tmpTTTT*0.5;
            }
            else
            {
                if(CCRANDOM_0_1()*100< 70)
                {
                    tmpTTTT = tmpTTTT*0.5;
                }
            }
            
        }
		if(LoadRes::bFirstFanWei == true)
		{ 
			if(CannonLayer::xinshoutimefanwei == 250)
			{ 
				tmpTTTT = tmpTTTT*2;
			}
		}
		if(LoadRes::bFirstJiGuang == true)
		{ 
			if(CannonLayer::xinshoutimejiguang == 250)
			{ 
				tmpTTTT = tmpTTTT*2;
			}
		}
		
	}
	if(false)
	{
        if(tmpFishType > 25)
        {
		FishLayer::ifCatchJnum = FishLayer::catchLabel.size();
		char tmplabeltmp[300] ;
		sprintf(tmplabeltmp,"Rate: %f -- FishType: %d -- FishRate: %f",tmpGailv,tmpFishType,tmpTTTT);
		auto tmplabel1 = LabelTTF::create(tmplabeltmp,GameHallLayer::wordKind,22);
		tmplabel1->setPosition(Vec2(winSize.width * 0.5,winSize.height * 0.75 - FishLayer::ifCatchJnum * 30));
		this->getParent()->addChild(tmplabel1,10000);
		FishLayer::catchLabel.pushBack(tmplabel1);

		if(FishLayer::ifCatchJnum > 10)
		{

			FishLayer::catchLabel.at(0)->setVisible(false);

			for(int i = 0; i < FishLayer::catchLabel.size() ; i ++)
			{
				auto fadeOut = MoveBy::create(0.5f,Vec2(0,30));
				FishLayer::catchLabel.at(i)->runAction(fadeOut); 
			}
			FishLayer::catchLabel.erase(0);
		}
        }
	}
 
	if(tmpGailv < tmpTTTT)
	{
			if(m_iFishType >0 && m_iFishType <4)
			{
                if(CCRANDOM_0_1() * 100 < 50)
                {
                    return true;
                }
				GameBegin::playSound("die11.mp3");
				return  true;
			}
			else if(m_iFishType < 6)
			{
                if(CCRANDOM_0_1() * 100 < 50)
                {
                    return true;
                }
				GameBegin::playSound("die33.mp3");
				return  true;
			}
			else if(m_iFishType < 9)
			{
                if(CCRANDOM_0_1() * 100 < 50)
                {
                    return true;
                }
				GameBegin::playSound("die44.mp3");
				return  true;
			}
           else  if(m_iFishType < 12)
            {
                if(CCRANDOM_0_1() * 100 < 50)
                {
                    return true;
                }
                GameBegin::playSound("die22.mp3");
                return  true;
            }
			 
            else if(m_iFishType == 12 || m_iFishType == 14)
            {
               // GameBegin::playSound("panzi.mp3");
                GameBegin::playSound("die555.mp3");
                return  true;
            }
            else if(m_iFishType == 13 || m_iFishType == 15)
            {
               // GameBegin::playSound("panzi.mp3");
                GameBegin::playSound("die600.mp3");
                return  true;
            }
           else  if(m_iFishType == 16 || m_iFishType == 18)
            {
               // GameBegin::playSound("panzi.mp3");
                GameBegin::playSound("die05.mp3");
                return  true;
            }
           else  if(m_iFishType == 17 || m_iFishType == 19)
            {
               // GameBegin::playSound("panzi.mp3");
                GameBegin::playSound("die08.mp3");
                return  true;
            }
            return  true;
            /*
            if(m_iFishType == 16)
            {
                if(iPos == 4)
                    AllRobot::shanshan = true;
                //GameBegin::playSound("panzi.mp3");
                GameBegin::playSound("die555.mp3");
                return  true;
            }
            if(m_iFishType == 17)
            {
                if(iPos == 4)
                    AllRobot::shanshan = true;
                //GameBegin::playSound("panzi.mp3");
                GameBegin::playSound("die600.mp3");
                return  true;
            }

          
			if(m_iFishType == 18)
			{
				if(iPos == 4)
					AllRobot::shanshan = true;
				//GameBegin::playSound("panzi.mp3");
				GameBegin::playSound("die05.mp3");
				return  true;
			}
			if(m_iFishType == 19)
			{
				if(iPos == 4)
					AllRobot::shanshan = true;
			//	GameBegin::playSound("panzi.mp3");
				GameBegin::playSound("die08.mp3");
				return  true;
			}
			if(m_iFishType == 20)
			{
				if(iPos == 4)
					AllRobot::shanshan = true;
				GameBegin::playSound("deadgirl.mp3");
				return  true;
			}
			if(m_iFishType == 21)
			{
				if(iPos == 4)
					AllRobot::shanshan = true;
				GameBegin::playSound("die03.mp3");
				return  true;
			}
			if(m_iFishType == 22)
			{
				if(iPos == 4)
					AllRobot::shanshan = true;
				GameBegin::playSound("deadgirl.mp3");
				return  true;
			}
			if(m_iFishType == 23)
			{
				if(iPos == 4)
					AllRobot::shanshan = true;
				//GameBegin::playSound("panzi.mp3");
				GameBegin::playSound("die06.mp3");
				return  true;
			} 
			if(m_iFishType == 24 ||  m_iFishType == 25)
			{
				GameBegin::playSound("Bigdie01.mp3");
				return  true;
			}

			if(m_iFishType > 29)
			{
				//GameBegin::playSound("panzi.mp3");
				if(m_iFishType == 30)
				{
					GameBegin::playSound("die05.mp3");
				}
				if(m_iFishType == 31)
				{
					GameBegin::playSound("die06.mp3");
				}
				if(m_iFishType > 31)
				{
					if(iPos == 4)
						AllRobot::shanshan = true;
					if(CCRANDOM_0_1()*100 > 50)
					{
						GameBegin::playSound("threekillone.mp3");
					}else
					{
						GameBegin::playSound("threekilltwo.mp3");
					}
				}
				return  true;
			} 	*/
		 
        /*
		else
		{
			if(m_iFishType >1 && m_iFishType <7)
			{
				GameBegin::playSound("die11.mp3");
				return  true;
			}
			if(m_iFishType < 9)
			{
				GameBegin::playSound("die33.mp3");
				return  true;
			}
			if(m_iFishType < 14)
			{
				GameBegin::playSound("die44.mp3");
				return  true;
			} 

			if(m_iFishType == 14 || m_iFishType == 16)
			{
				GameBegin::playSound("panzi.mp3");
				GameBegin::playSound("die555.mp3");
				return  true;
			}
			if(m_iFishType == 15 || m_iFishType == 17)
			{
				GameBegin::playSound("panzi.mp3");
				GameBegin::playSound("die600.mp3");
				return  true;
			}
			if(m_iFishType == 18)
			{
				GameBegin::playSound("panzi.mp3");
				GameBegin::playSound("die05.mp3");
				return  true;
			}
			if(m_iFishType == 19)
			{
				GameBegin::playSound("panzi.mp3");
				GameBegin::playSound("die08.mp3");
				return  true;
			}
			if(m_iFishType == 20)
			{
				GameBegin::playSound("deadgirl.mp3");
				return  true;
			}
			if(m_iFishType == 21)
			{
				GameBegin::playSound("die03.mp3");
				return  true;
			}
			if(m_iFishType == 22)
			{
				GameBegin::playSound("deadgirl.mp3");
				return  true;
			}
			if(m_iFishType == 23)
			{
				GameBegin::playSound("panzi.mp3");
				GameBegin::playSound("die06.mp3");
				return  true;
			} 
			if(m_iFishType == 24 ||  m_iFishType == 25)
			{
				GameBegin::playSound("Bigdie01.mp3");
				return  true;
			}

			if(m_iFishType > 29)
			{
				GameBegin::playSound("panzi.mp3");
				if(m_iFishType == 30)
				{
					GameBegin::playSound("die05.mp3");
				}
				if(m_iFishType == 31)
				{
					GameBegin::playSound("die06.mp3");
				}
				if(m_iFishType > 31)
				{
					if(CCRANDOM_0_1()*100 > 50)
					{
						GameBegin::playSound("threekillone.mp3");
					}else
					{
						GameBegin::playSound("threekilltwo.mp3");
					}
				}
				return  true;
			} 	
		}*/
	
		return  true;
	}
	return false;
}
