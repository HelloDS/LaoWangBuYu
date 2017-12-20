

#include "FishingNet.h"
#include "StaticData.h"
#include "GameBegin.h"
#include "CannonLayer.h"
USING_NS_CC;

 

bool FishingNet::init(unsigned char type,char cNetPos)
{
	_type = type;
	cNetPosRobot = cNetPos;
	  
	bShoot = false;
	int typeTemp = 0; 
    fRadius = 0; 
	bOver =false;
    

if(type <GameBegin::WangW[0])
    {
        typeTemp = 11;
        
        auto _fishingNetSprite = Sprite::createWithSpriteFrameName("net_1.png");
        this->addChild(_fishingNetSprite);
		

        fRadius = 40;
        
		//auto yw_texiao_animation = AnimationCache::getInstance()->getAnimation("yuwang_texiao_2");
		//auto yw_texiao_animate = Animate::create(yw_texiao_animation);
		//auto _fishingNet_texiao = Sprite::createWithSpriteFrameName("yw_texiao_2_1.png");
		//_fishingNet_texiao->setPosition(Vec2(_fishingNetSprite->getContentSize()/2));
  //      _fishingNetSprite->addChild(_fishingNet_texiao);
		//_fishingNet_texiao->runAction(yw_texiao_animate);   //Sequence::create(yw_texiao_animate,yw_texiao_animate->reverse(),nullptr)
        
    }
    else if(type <GameBegin::WangW[1])
    {
        typeTemp = 12;
        
        auto _fishingNetSprite = Sprite::createWithSpriteFrameName("net_1.png");
        _fishingNetSprite->setPosition(Point(-45,10));
		_fishingNetSprite->setScale(0.95f);
        this->addChild(_fishingNetSprite);
        
        auto _fishingNetSprite1 = Sprite::createWithSpriteFrameName("net_1.png");
        _fishingNetSprite1->setPosition(Point(45,10));
        this->addChild(_fishingNetSprite1);
        _fishingNetSprite->setScale(1.05f);
        
        int iRot = -20 + CCRANDOM_0_1()*40;
        this->setRotation(iRot);
        fRadius = 70;
        
    }
    else if(type < GameBegin::WangW[2])
    {
        
        char cShowType;
        char cRandom = CCRANDOM_0_1()*100;
        if(cRandom<35)
        {
            cShowType = 1;
        }
        else if(cRandom < 70)
        {
            cShowType = 2;
        }
        else
        {
            cShowType = 3;
        }
        
        if(cShowType == 1)
        {
            auto _fishingNetSprite = Sprite::createWithSpriteFrameName("net_1.png");
            _fishingNetSprite->setPosition(Point(-45,20));
            _fishingNetSprite->setScale(0.8f);
            this->addChild(_fishingNetSprite);
            
            
            auto _fishingNetSprite2 = Sprite::createWithSpriteFrameName("net_1.png");
            _fishingNetSprite2->setPosition(Point(0,90));
			_fishingNetSprite2->setScale(0.9f);
            this->addChild(_fishingNetSprite2);
            
            auto _fishingNetSprite1 = Sprite::createWithSpriteFrameName("net_1.png");
            _fishingNetSprite1->setPosition(Point(45,20));
            this->addChild(_fishingNetSprite1);
        }
        else if(cShowType == 2)
        { 
            auto _fishingNetSprite2 = Sprite::createWithSpriteFrameName("net_1.png");
            _fishingNetSprite2->setPosition(Point(0,90));
            this->addChild(_fishingNetSprite2);
            _fishingNetSprite2->setScale(0.8f);
            
            auto _fishingNetSprite1 = Sprite::createWithSpriteFrameName("net_1.png");
            _fishingNetSprite1->setPosition(Point(45,20)); 
            this->addChild(_fishingNetSprite1);
            _fishingNetSprite1->setScale(0.9f);
            
            auto _fishingNetSprite = Sprite::createWithSpriteFrameName("net_1.png");
            _fishingNetSprite->setPosition(Point(-45,20));
            this->addChild(_fishingNetSprite);
        }
        else if(cShowType == 3)
        {
            
            auto _fishingNetSprite1 = Sprite::createWithSpriteFrameName("net_1.png");
            _fishingNetSprite1->setPosition(Point(45,20)); 
            this->addChild(_fishingNetSprite1);
            _fishingNetSprite1->setScale(0.8f);
            
            auto _fishingNetSprite = Sprite::createWithSpriteFrameName("net_1.png");
            _fishingNetSprite->setPosition(Point(-45,20));
            this->addChild(_fishingNetSprite);
            _fishingNetSprite->setScale(0.9f);
            
            auto _fishingNetSprite2 = Sprite::createWithSpriteFrameName("net_1.png");
            _fishingNetSprite2->setPosition(Point(0,90));
            this->addChild(_fishingNetSprite2);
            
        }
        
        fRadius = 100;
         int iRot = -50 + CCRANDOM_0_1()*40;
        this->setRotation(iRot); 
        
    }
    else if(type < GameBegin::WangW[3])
    {
        typeTemp = 13;
        
        
        
        char cShowType;
        char cRandom = CCRANDOM_0_1()*100;
        if(cRandom<35)
        {
            cShowType = 1;
        }
        else if(cRandom < 70)
        {
            cShowType = 2;
        }
        else
        {
            cShowType = 3;
        }
        
        if(cShowType == 1)
        {
            auto _fishingNetSprite = Sprite::createWithSpriteFrameName("net2wf.png");
            _fishingNetSprite->setPosition(Point(-45,20));
            _fishingNetSprite->setScale(0.7f);
            this->addChild(_fishingNetSprite);
            
            
            auto _fishingNetSprite2 = Sprite::createWithSpriteFrameName("net2wf.png");
            _fishingNetSprite2->setPosition(Point(0,90));
            _fishingNetSprite2->setScale(0.8f);

            this->addChild(_fishingNetSprite2);
            
            auto _fishingNetSprite1 = Sprite::createWithSpriteFrameName("net2wf.png");
            _fishingNetSprite1->setPosition(Point(45,20));
            _fishingNetSprite1->setScale(0.9f);
            this->addChild(_fishingNetSprite1);
        }
        else if(cShowType == 2)
        {
            
            
            auto _fishingNetSprite2 = Sprite::createWithSpriteFrameName("net2wf.png");
            _fishingNetSprite2->setPosition(Point(0,90));
            _fishingNetSprite2->setScale(0.7f);
             //_fishingNetSprite2->setScale(0.8f);
            this->addChild(_fishingNetSprite2);
            
            auto _fishingNetSprite1 = Sprite::createWithSpriteFrameName("net2wf.png");
            _fishingNetSprite1->setPosition(Point(45,20));
            _fishingNetSprite1->setScale(0.8f);
            //_fishingNetSprite1->setScale(0.9f);
            this->addChild(_fishingNetSprite1);
            
            auto _fishingNetSprite = Sprite::createWithSpriteFrameName("net2wf.png");
            _fishingNetSprite->setPosition(Point(-45,20));
            _fishingNetSprite->setScale(0.9f);
           // _fishingNetSprite->setScale(0.7f);
            this->addChild(_fishingNetSprite);
        }
        else if(cShowType == 3)
        {
            auto _fishingNetSprite1 = Sprite::createWithSpriteFrameName("net2wf.png");
            _fishingNetSprite1->setPosition(Point(45,20));
            _fishingNetSprite1->setScale(0.7f);
           // _fishingNetSprite1->setScale(0.9f);
            this->addChild(_fishingNetSprite1);
            
            auto _fishingNetSprite = Sprite::createWithSpriteFrameName("net2wf.png");
            _fishingNetSprite->setPosition(Point(-45,20));
            _fishingNetSprite->setScale(0.8f);
            //_fishingNetSprite->setScale(0.7f);
            this->addChild(_fishingNetSprite);
            
            
            auto _fishingNetSprite2 = Sprite::createWithSpriteFrameName("net2wf.png");
            _fishingNetSprite2->setPosition(Point(0,90));
            _fishingNetSprite2->setScale(0.9f);
            //_fishingNetSprite2->setScale(0.8f);
            this->addChild(_fishingNetSprite2);
            
            
        }
        
        
        fRadius = 110;
        
          int iRot = -50 + CCRANDOM_0_1()*40;
        this->setRotation(iRot); 
        
        
        /*
         auto _fishingNetSprite = Sprite::createWithSpriteFrameName("net5.png");
         _fishingNetSprite->setPosition(Point(-50,20));
         this->addChild(_fishingNetSprite);
         
         
         auto _fishingNetSprite2 = Sprite::createWithSpriteFrameName("net5.png");
         _fishingNetSprite2->setPosition(Point(0,97));
         this->addChild(_fishingNetSprite2);
         
         auto _fishingNetSprite1 = Sprite::createWithSpriteFrameName("net5.png");
         _fishingNetSprite1->setPosition(Point(50,20));
         this->addChild(_fishingNetSprite1);
         */
        
    }
    else if(type < GameBegin::WangW[4])
    {
        
        
        char cShowType;
        char cRandom = CCRANDOM_0_1()*100;
        if(cRandom<35)
        {
            cShowType = 1;
        }
        else if(cRandom < 70)
        {
            cShowType = 2;
        }
        else
        {
            cShowType = 3;
        }
        
        if(cShowType == 1)
        {
            auto _fishingNetSprite = Sprite::createWithSpriteFrameName("net_2.png");
            _fishingNetSprite->setPosition(Point(-45,20));
            _fishingNetSprite->setScale(0.85f);
            this->addChild(_fishingNetSprite);
            
            
            auto _fishingNetSprite2 = Sprite::createWithSpriteFrameName("net_2.png");
            _fishingNetSprite2->setPosition(Point(0,90));
            this->addChild(_fishingNetSprite2);
            
            auto _fishingNetSprite1 = Sprite::createWithSpriteFrameName("net_2.png");
            _fishingNetSprite1->setPosition(Point(45,20));
            _fishingNetSprite1->setScale(0.9f);
            this->addChild(_fishingNetSprite1);
        }
        else if(cShowType == 2)
        {
            
            
            
            auto _fishingNetSprite2 = Sprite::createWithSpriteFrameName("net_2.png");
            _fishingNetSprite2->setPosition(Point(0,90));
            _fishingNetSprite2->setScale(0.85f);
            this->addChild(_fishingNetSprite2);
            
            auto _fishingNetSprite1 = Sprite::createWithSpriteFrameName("net_2.png");
            _fishingNetSprite1->setPosition(Point(45,20));
            this->addChild(_fishingNetSprite1);
            
            auto _fishingNetSprite = Sprite::createWithSpriteFrameName("net_2.png");
            _fishingNetSprite->setPosition(Point(-45,20));
            _fishingNetSprite->setScale(0.9f);
            this->addChild(_fishingNetSprite);
        }
        else if(cShowType == 3)
        {
            
            auto _fishingNetSprite1 = Sprite::createWithSpriteFrameName("net_2.png");
            _fishingNetSprite1->setPosition(Point(45,20));
            _fishingNetSprite1->setScale(0.85f);
            this->addChild(_fishingNetSprite1);
            
            auto _fishingNetSprite = Sprite::createWithSpriteFrameName("net_2.png");
            _fishingNetSprite->setPosition(Point(-45,20));
            this->addChild(_fishingNetSprite);
            
            
            auto _fishingNetSprite2 = Sprite::createWithSpriteFrameName("net_2.png");
            _fishingNetSprite2->setPosition(Point(0,90));
            _fishingNetSprite1->setScale(0.9f);
            this->addChild(_fishingNetSprite2);
            
            
        }
        
        
        fRadius = 100;
        
        int iRot = -50 + CCRANDOM_0_1()*40;
        this->setRotation(iRot); 
        typeTemp = 14;
        
    }
    else if(type< GameBegin::WangW[5])
    {
        
        char cShowType;
        char cRandom = CCRANDOM_0_1()*100;
        if(cRandom<35)
        {
            cShowType = 1;
        }
        else if(cRandom < 70)
        {
            cShowType = 2;
        }
        else
        {
            cShowType = 3;
        }
        
        if(cShowType == 1)
        {
            auto _fishingNetSprite = Sprite::createWithSpriteFrameName("net_3.png"); 
            _fishingNetSprite->setPosition(Point(-45,20));
            _fishingNetSprite->setScale(0.9f);
            this->addChild(_fishingNetSprite);
            
            
            auto _fishingNetSprite2 = Sprite::createWithSpriteFrameName("net_3.png"); 
            _fishingNetSprite2->setPosition(Point(0,90));
            this->addChild(_fishingNetSprite2);
            
            auto _fishingNetSprite1 = Sprite::createWithSpriteFrameName("net_3.png"); 
            _fishingNetSprite1->setPosition(Point(45,20));
            _fishingNetSprite1->setScale(0.85f);
            this->addChild(_fishingNetSprite1);
        }
        else if(cShowType == 2)
        {
            
            
            
            auto _fishingNetSprite2 = Sprite::createWithSpriteFrameName("net_3.png"); 
            _fishingNetSprite2->setPosition(Point(0,90));
            _fishingNetSprite2->setScale(0.9f);
            this->addChild(_fishingNetSprite2);
            
            auto _fishingNetSprite1 = Sprite::createWithSpriteFrameName("net_3.png"); 
            _fishingNetSprite1->setPosition(Point(45,20));
            this->addChild(_fishingNetSprite1);
            
            auto _fishingNetSprite = Sprite::createWithSpriteFrameName("net_3.png"); 
            _fishingNetSprite->setPosition(Point(-45,20)); 
            _fishingNetSprite->setScale(0.85f);
            this->addChild(_fishingNetSprite);
        }
        else if(cShowType == 3)
        {
            
            auto _fishingNetSprite1 = Sprite::createWithSpriteFrameName("net_3.png"); 
            _fishingNetSprite1->setPosition(Point(45,20)); 
            _fishingNetSprite1->setScale(0.9f);
            this->addChild(_fishingNetSprite1);
            
            auto _fishingNetSprite = Sprite::createWithSpriteFrameName("net_3.png"); 
            _fishingNetSprite->setPosition(Point(-45,20));
            this->addChild(_fishingNetSprite);
            
            
            auto _fishingNetSprite2 = Sprite::createWithSpriteFrameName("net_3.png"); 
            _fishingNetSprite2->setPosition(Point(0,90));
            _fishingNetSprite2->setScale(0.85f);
            this->addChild(_fishingNetSprite2);
            
            
        }
        
        fRadius = 120;
           int iRot = -50 + CCRANDOM_0_1()*40;
        this->setRotation(iRot); 
        typeTemp = 15;
    } 
    else if(type< 22)
    {
        bOver =true;
        typeTemp = 4;
    } 
    else if(type< 24)
    {
        bOver =true;
        typeTemp = 5;
    } 
    else if(type< 25)
    {
        bOver =true;
        typeTemp = 6;
    } 
    else if(type< 27)
    {
        bOver =true;
        typeTemp = 7;
    } 
    else if(type< 29)
    {
        bOver =true;
        typeTemp = 8;
    } 
    else if(type< 30)
    {
        bOver =true;
        typeTemp = 9;
    } 
	else if(typeTemp < 31)
	{
		  char cShowType;
        char cRandom = CCRANDOM_0_1()*100;
        if(cRandom<40)
        {
            cShowType = 1;
        }
        else if(cRandom < 80)
        {
            cShowType = 2;
        }
        else
        {
            cShowType = 3;
        }
        
        if(cShowType == 1)
        {
            auto _fishingNetSprite = Sprite::createWithSpriteFrameName("net_vip.png"); 
            _fishingNetSprite->setPosition(Point(-45,20));
            _fishingNetSprite->setScale(1.1f);
            this->addChild(_fishingNetSprite);
            
            
            auto _fishingNetSprite2 = Sprite::createWithSpriteFrameName("net_vip.png"); 
            _fishingNetSprite2->setPosition(Point(0,90));
            this->addChild(_fishingNetSprite2);
            
            auto _fishingNetSprite1 = Sprite::createWithSpriteFrameName("net_vip.png"); 
            _fishingNetSprite1->setPosition(Point(45,20));
            _fishingNetSprite1->setScale(1.2f);
            this->addChild(_fishingNetSprite1);
        }
        else if(cShowType == 2)
        {
            auto _fishingNetSprite2 = Sprite::createWithSpriteFrameName("net_vip.png"); 
            _fishingNetSprite2->setPosition(Point(0,90));
            _fishingNetSprite2->setScale(1.1f);
            this->addChild(_fishingNetSprite2);
            
            auto _fishingNetSprite1 = Sprite::createWithSpriteFrameName("net_vip.png"); 
            _fishingNetSprite1->setPosition(Point(45,20));
            this->addChild(_fishingNetSprite1);
            
            auto _fishingNetSprite = Sprite::createWithSpriteFrameName("net_vip.png"); 
            _fishingNetSprite->setPosition(Point(-45,20)); 
            _fishingNetSprite->setScale(1.2f);
            this->addChild(_fishingNetSprite);
        }
        else if(cShowType == 3)
        {
            
            auto _fishingNetSprite1 = Sprite::createWithSpriteFrameName("net_vip.png"); 
            _fishingNetSprite1->setPosition(Point(45,20)); 
            _fishingNetSprite1->setScale(1.1f);
            this->addChild(_fishingNetSprite1);
            
            auto _fishingNetSprite = Sprite::createWithSpriteFrameName("net_vip.png"); 
            _fishingNetSprite->setPosition(Point(-45,20));
            this->addChild(_fishingNetSprite);
            
            
            auto _fishingNetSprite2 = Sprite::createWithSpriteFrameName("net_vip.png"); 
            _fishingNetSprite2->setPosition(Point(0,90));
            _fishingNetSprite2->setScale(1.2f);
            this->addChild(_fishingNetSprite2);
            
            
        }
        
        fRadius = 110;
        int iRot = -50 + CCRANDOM_0_1()*40;
        this->setRotation(iRot);
        typeTemp = 15;
	}
	 
	 if(typeTemp == 4)
	 {
		 fRadius = 100;
	 }
	 else if(typeTemp == 5)
	 {
		  fRadius = 142;
	 }
	 else if(typeTemp == 6)
	 {
		  fRadius = 188;
	 }  

	 iNetNum = 1; 
    
    return true;
}
void FishingNet::SetPar(Point Pos)
{  
}
FishingNet* FishingNet::create(unsigned char type ,char cNetPos)
{
	FishingNet* fishingnet = new FishingNet();
	fishingnet->init(type,cNetPos);
	fishingnet->autorelease();
	return fishingnet;
}
void FishingNet::NetEnd()
{
	bOver = true; 
}

void FishingNet::showAt(Point pos)
{
 

		this->setPosition(pos); 
		this->setScale(0.8f);
		this->setVisible(true);
		this->stopAllActions();




		//auto ac15 =  DelayTime::create(0.5f); 
		//CCTintTo *ac11=CCTintTo::create(2.0f, 0, 234, 255);  
		ScaleTo *ac8=ScaleTo::create(0.07f, 1.0f);
		ScaleTo *ac9=ScaleTo::create(0.07f, 0.8f);
		//ScaleTo *ac10=ScaleTo::create(0.1f, 0.9);
		//ScaleTo *ac11=ScaleTo::create(0.05f, 0.8);  

		Hide   *ac14=Hide::create();  

		 
		auto * seq = Sequence::create(ac8,ac9,ac14, NULL);

		this->runAction(seq);
 

}
 

Point FishingNet::getCollisionPoint()
{
	return this->getParent()->convertToWorldSpace(this->getPosition());
}  