#include "Bullet.h"
#include "StaticData.h"
#include "GameScene.h"
#include "GameBegin.h"
#include "FishLayer.h"
enum{
    k_Bullet_Action = 0
};
 
 
 

Bullet* Bullet::create(unsigned char  type,char myBeiShu,char cRobotPos)
{

	Bullet* bullet = new Bullet();
	bullet->init(type,myBeiShu,cRobotPos);
	bullet->autorelease();
	return bullet;
}
 
Bullet::~Bullet()
{
	

}
bool Bullet::init(unsigned char  type,char myBeiShu,char cRobotPos)
{  
	 
	Size winSize = Director::getInstance()->getWinSize(); 
	 
     bBulletOk = false;
    if(FishLayer::bBulletShan == true)
    {
        FishLayer::bBulletShan = false;
        
        
        cFrameNum =1;
    }
    else
    {
        FishLayer::bBulletShan = true;
        
        cFrameNum = 0;
        
    }
    cFrameNumBullet = 0;

	bDead = false;
	char  typeTemp = 0;

	Vec2  mPointOffSet;

	mPointOffSet = Vec2(winSize.width*0.5f,50); 
	buletBeiShu = myBeiShu;

	 
	if(type < GameBegin::WangW[0])
	{ 
		typeTemp = 1;
	}
	else if(type < GameBegin::WangW[1])
	{
		typeTemp = 2;
	}
	else if(type< GameBegin::WangW[3])
	{
		typeTemp = 3;
	} 
	else if(type< GameBegin::WangW[4])
	{
		typeTemp = 33;
	} 
	else if(type< GameBegin::WangW[5])
	{
		typeTemp = 34;
	}  
	else if(type< 22)
	{ 
		//初级范围跑
		mPointOffSet = Point(winSize.width*0.5f,50-17);
		typeTemp = 4; 
	} 
	else if(type< 24)
	{
		//中级范围跑
		mPointOffSet = Point(winSize.width*0.5f,50-24);
		typeTemp = 5; 
	} 
	else if(type< 25)
	{
		//高级范围跑
		mPointOffSet = Point(winSize.width*0.5f,50-15);	
		typeTemp = 6;
	} 
	else if(type< 27)
	{
		//初级激光炮
			mPointOffSet = Point(winSize.width*0.5f,50-17);	
		typeTemp = 7;
	} 
	else if(type< 29)
	{
		//中级激光炮
		mPointOffSet = Point(winSize.width*0.5f,50-15);	
		typeTemp = 8;

	} 
	else if(type< 30)
	{

		//搞级激光炮
		mPointOffSet = Point(winSize.width*0.5f,50-13);	
		typeTemp = 9;
	}
	else if(type< 31)
	{
		typeTemp = 35;
	}
	 



	if(cRobotPos == 0)
	{	 
		mPointOffSet.x = CannonLayer::robotPos1; 
	}
	if(cRobotPos == 1)
	{
			mPointOffSet.x = CannonLayer::robotPos2; 
	}
	else if(cRobotPos == 2)
	{
		mPointOffSet.x = CannonLayer::robotPos1; 
		mPointOffSet.y = winSize.height - mPointOffSet.y; 
	}
	else if(cRobotPos == 3)
	{
		mPointOffSet.x = CannonLayer::robotPos2; 
		mPointOffSet.y = winSize.height - mPointOffSet.y; 
	}
	else if(cRobotPos == 4)
	{
		if(GameScene::cGameType == 1)
		{
			if(GameScene::cSelfPos == 0)
			{
				mPointOffSet.x = CannonLayer::robotPos1; 
			}
			else
			{
				mPointOffSet.x = CannonLayer::robotPos2; 
			}
		} 
	}


 
	fRadius = 0;
	if(typeTemp == 7)
	{
		fRadius = 12;
	}
	else if(typeTemp == 8)
	{
		fRadius = 50;
	}
	else if(typeTemp == 9)
	{
		fRadius = 80;
	}
	iNetNum =1;
	_type = type;
	
	if(typeTemp == 8)
	{
		Animation* fishAnimation = AnimationCache::getInstance()->getAnimation("JiGuangFrameTwo"); 
		Animate*  fishAnimate = Animate::create(fishAnimation);
		//    fishAnimate->setTag(k_Action_Animate);
		_bulletSprite = Sprite::create(); 
		_bulletSprite->runAction(RepeatForever::create(fishAnimate));
	}
	else if(typeTemp == 9)
	{ 
		Animation* fishAnimation = AnimationCache::getInstance()->getAnimation("JiGuangFrameThree");

		Animate*  fishAnimate = Animate::create(fishAnimation);
		//    fishAnimate->setTag(k_Action_Animate);
		 _bulletSprite = Sprite::create(); 
		_bulletSprite->runAction(RepeatForever::create(fishAnimate));
	} 
	else
	{
        if(typeTemp == 1 )
        {
            _bulletSpriteTwo = Sprite::createWithSpriteFrameName("bullet_11wf.png");
            _bulletSpriteTwo->setAnchorPoint(Point(0.5, 0.5));
            bBulletOk = true;
            
            _bulletSpriteTwo->setTag(5);
            this->addChild(_bulletSpriteTwo);
            
            if(cRobotPos>1 &&cRobotPos != 4)
            {
                _bulletSpriteTwo->setFlippedY(true);
                
                
            }
        }
        
        if(typeTemp == 2 )
        {
            _bulletSpriteTwo = Sprite::createWithSpriteFrameName("bullet_22wf.png");
            _bulletSpriteTwo->setAnchorPoint(Point(0.5, 0.5));
            bBulletOk = true;
            
            _bulletSpriteTwo->setTag(5);
            this->addChild(_bulletSpriteTwo);
            
            if(cRobotPos>1 &&cRobotPos != 4)
            {
                _bulletSpriteTwo->setFlippedY(true);
                
                
            }
        }
        if(typeTemp == 3 )
        {
            _bulletSpriteTwo = Sprite::createWithSpriteFrameName("bullet_33wf.png");
            _bulletSpriteTwo->setAnchorPoint(Point(0.5, 0.5));
            bBulletOk = true;
            
            _bulletSpriteTwo->setTag(5);
            this->addChild(_bulletSpriteTwo);
            
            if(cRobotPos>1 &&cRobotPos != 4)
            {
                _bulletSpriteTwo->setFlippedY(true);
                
                
            }
        }
        if(typeTemp == 33 )
        {
            _bulletSpriteTwo = Sprite::createWithSpriteFrameName("bullet_333wf.png");
            _bulletSpriteTwo->setAnchorPoint(Point(0.5, 0.5));
            bBulletOk = true;
            
            _bulletSpriteTwo->setTag(5);
            this->addChild(_bulletSpriteTwo);
            
            if(cRobotPos>1 &&cRobotPos != 4)
            {
                _bulletSpriteTwo->setFlippedY(true);
                
                
            }
        }
        if(typeTemp == 34 )
        {
            _bulletSpriteTwo = Sprite::createWithSpriteFrameName("bullet_344wf.png");
            _bulletSpriteTwo->setAnchorPoint(Point(0.5, 0.5));
            bBulletOk = true;
            
            _bulletSpriteTwo->setTag(5);
            this->addChild(_bulletSpriteTwo);
            
            if(cRobotPos>1 &&cRobotPos != 4)
            {
                _bulletSpriteTwo->setFlippedY(true);
                
                
            }
        }
        if(typeTemp == 35 )
        {
            _bulletSpriteTwo = Sprite::createWithSpriteFrameName("bullet_355wf.png");
            _bulletSpriteTwo->setAnchorPoint(Point(0.5, 0.5));
            bBulletOk = true;
            
            _bulletSpriteTwo->setTag(5);
            this->addChild(_bulletSpriteTwo);
            
            if(cRobotPos>1 &&cRobotPos != 4)
            {
                _bulletSpriteTwo->setFlippedY(true);
                
                
            }
        }
        
		char name[20];
		sprintf(name,"bullet_%d.png",typeTemp);
        int itemp =typeTemp;
		_bulletSprite = Sprite::createWithSpriteFrameName(name); 
		_bulletSprite->setAnchorPoint(Point(0.5, 0.5));
        
        if(itemp == 3)
        {
            _bulletSprite->setScale(0.87f);
            _bulletSpriteTwo->setScale(0.87f);
        }
        else if(itemp  == 33)
        {
            _bulletSprite->setScale(0.9f);
            _bulletSpriteTwo->setScale(0.9f);
        }
        else if(itemp  == 34)
        {
            _bulletSprite->setScale(1.2,0.9);
            _bulletSpriteTwo->setScale(1.2,0.9f);
        }
        
	}
	if(cRobotPos>1 &&cRobotPos != 4)
	{
		_bulletSprite->setFlippedY(true);
        
        
	}
	if(typeTemp == 6)
	{
		_bulletSprite->setScale(0.7f);
	} 
	_bulletSprite->setTag(5);   
	this->addChild(_bulletSprite); 

	_iWallState = 0;
	bMoveEnd = false; 

	this->setPosition(mPointOffSet); 


	bMoreFish = false;
    return true;
} 
void Bullet::MoveBullet()
{
    if(bBulletOk == true)
    {
        cFrameNumBullet ++;
        if(cFrameNumBullet == 4)
        {
            cFrameNumBullet = 0;
            if(cFrameNum == 0)
            {
                _bulletSprite->setVisible(true);
                _bulletSpriteTwo->setVisible(false);
            }
            else if(cFrameNum == 1)
            {
                _bulletSprite->setVisible(false);
                _bulletSpriteTwo->setVisible(true);
                
            }
            
            
            if(cFrameNum == 1)
                cFrameNum = 0;
            else if(cFrameNum == 0)
                cFrameNum = 1;
            
            
        }
    }
  
    
    
	setBeginPos(this->getPosition());
	Point Temp = this->getPosition()+Ver; 
	this->setPosition(Temp); 
	
}

void Bullet::flyTo(Point targetInWorldSpace)
{
    //点的转换和角度的计算  
   
	Ver = targetInWorldSpace;
    Point Temp = getPosition()+Ver; 
    this->setPosition(Temp); 
    
    //设置子弹固定的飞行速度
  /*  float speed = 1200.0f;
    float duration = ccpDistance(this->getPosition(), targetInWorldSpace) / speed;
    CCMoveTo* moveTo = CCMoveTo::create(duration, targetInWorldSpace);

	moveTo->setTag(k_Bullet_Action); 

	if(_type > 19 && _type< 30)
	{
		auto call = CallFunc::create(CC_CALLBACK_0(Bullet::FanWeiMoveEnd,this));
		auto seq = Sequence::create(moveTo,call,NULL); 
		this->runAction(seq);
	}
	else
		this->runAction(moveTo);
    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(Bullet::end));
    
    CCFiniteTimeAction* seq = CCSequence::create(moveTo, callFunc, NULL);
    seq->setTag(k_Bullet_Action);
   */
}


void Bullet::FanWeiMoveEnd()
{
	bMoveEnd =true;
}
void Bullet::stopAction()
{ 
    this->stopAllActions(); 
    this->setVisible(true);
}
Point Bullet::getCollisionPoint()
{
    return this->getParent()->convertToWorldSpace(this->getPosition());
}  
