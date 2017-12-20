 
#include "CoinAndAni.h" 
#include "GameScene.h"


CoinAndAni* CoinAndAni::create(unsigned char  type,char cShootPos)
{

	CoinAndAni* coinandani = new CoinAndAni();
	coinandani->init(type,cShootPos);
	coinandani->autorelease();
	return coinandani;
}
 
bool CoinAndAni::init(unsigned char  type,char cShootPos)
{   
	winSize = Director::getInstance()->getWinSize(); 
	if(type == 4)
	{
		_coinSprite =Sprite::createWithSpriteFrameName("bosszuanshi.png");
		this->addChild(_coinSprite);
	}
	else 
	{
		char cTempAni[20];

		_coinSprite = Sprite::create(); 
		if(type == 2)	 
		{
			memcpy(cTempAni,"coinwf",sizeof(cTempAni));
        
		}
		else if(type == 1)
		{
			memcpy(cTempAni,"yb_",sizeof(cTempAni));
			_coinSprite->setScale(0.8f);
			_coinSprite->setOpacity(210);
	 
		} 
		else if(type == 3)
		{
			memcpy(cTempAni,"coinwf",sizeof(cTempAni));
			_coinSprite->setScale(0.9f);
		}
		Animation* fishAnimation = AnimationCache::getInstance()->getAnimation(cTempAni);

		Animate*  fishAnimate = Animate::create(fishAnimation);
		//    fishAnimate->setTag(k_Action_Animate); 

		this->addChild(_coinSprite);
		_coinSprite->runAction(RepeatForever::create(fishAnimate));
	}
	
	
 	if(cShootPos == 0||(cShootPos == 4 && GameScene::cSelfPos == 0))
	{
		BeginPos = Vec2(  CannonLayer::robotPos1-315, 0); 
	}
	else if(cShootPos == 1||(cShootPos == 4 && GameScene::cSelfPos == 1))
	{
		BeginPos = Vec2(  CannonLayer::robotPos2+315, 0);  
	}
	else if(cShootPos == 2)
	{
		BeginPos = Vec2(  CannonLayer::robotPos1-315,winSize.height);

	}
	else if(cShootPos == 3)
	{
		BeginPos = Vec2(  CannonLayer::robotPos2+315,winSize.height);

	}
	else 
	{
		BeginPos = Point(winSize.width * 0.15,0);
	}

	bOver = false;

	return true ; 
}  

void CoinAndAni::MoveOver()
{ 
	_coinSprite->stopAllActions();
	this->getParent()->removeChild(this, true);

}


void CoinAndAni::CoinMove(Point pTemp)
{ 
   
	_coinSprite->setPosition(pTemp); 

	JumpTo *jump1  = JumpTo::create(0.5f,pTemp,60,1);
	JumpTo *jump2  = JumpTo::create(0.5f,pTemp,50,1);
	JumpTo *jump3  = JumpTo::create(0.5f,pTemp,15,1);
	//MoveTo* moveTo = MoveTo::create(1.0f ,BeginPos);
	float speed =350;	
	float duration = ccpDistance(_coinSprite->getPosition(), BeginPos) / speed; 
	MoveTo* moveTo = MoveTo::create(duration ,BeginPos);  
	auto ac2 = CallFunc::create(this,callfunc_selector(CoinAndAni::MoveOver));

	auto seq = Sequence::create(jump1,jump2,jump3,moveTo,ac2,NULL);  
	_coinSprite->runAction(seq);
	 
 	 
} 