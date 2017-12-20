#ifndef __FishingJoy__Bullet__
#define __FishingJoy__Bullet__
#include "cocos2d.h" 

using namespace std;

USING_NS_CC;

class Bullet : public cocos2d::CCNode
{
public:  
	~Bullet();

	//4是玩家。0123是机器人子弹位置
	static Bullet* create(unsigned char type ,char myBeiShu,char cRobotPos); 
	bool init( unsigned char type,char myBeiShu ,char cRobotPos); 
    CC_SYNTHESIZE_READONLY(unsigned char, _type, Type);
	CC_SYNTHESIZE(unsigned char, _iWallState, WallState);
	CC_SYNTHESIZE(cocos2d::Point, _iBeginPos, BeginPos);
	CC_SYNTHESIZE(cocos2d::Point, _EndPos, EndPos);
	 
	char buletBeiShu;
    //子弹飞行
    void flyTo(cocos2d::Point target);
    //使子弹结束飞行
    void stopAction(); 
  
	bool bDead;
	cocos2d::Point getCollisionPoint();
	void MoveBullet();
	void FanWeiMoveEnd();
	bool bMoveEnd; 
	int iNetNum; 
	int iDaNum;
	float fRadius; 
	ParticleSystemQuad * m_ParJinbi1 ; 

    char cFrameNumBullet;
    
    bool bBulletOk;
    char cFrameNum;
	bool bMoreFish; 
	Point Ver;
	vector<int> NowShootFishId;
	cocos2d::Sprite* _bulletSprite;
    
    cocos2d::Sprite* _bulletSpriteTwo;
protected:
};

#endif /* defined(__FishingJoy__Bullet__) */
