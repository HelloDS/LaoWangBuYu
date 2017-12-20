#pragma once

#include "cocos2d.h"  
using namespace std;

USING_NS_CC;

class CoinAndAni : public cocos2d::CCNode
{
public:  
	static CoinAndAni* create(unsigned char type,char cShootPos ); 
	bool init( unsigned char type ,char cShootPos); 
     Sprite * _coinSprite; 
	 bool bOver;
	  
	 void CoinMove(Point pTemp);
	 void MoveOver();
	 Point BeginPos;
	 Size winSize ;

};
 