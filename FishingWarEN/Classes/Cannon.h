 

#ifndef __FishingJoy__Cannon__
#define __FishingJoy__Cannon__
#include "cocos2d.h" 


class Cannon : public cocos2d::CCNode
{ 
public:
    Cannon();
    ~Cannon();
    static Cannon* create(unsigned char type ,int beishu ,char cPos);
    bool init(unsigned char type,int beishu,char cPos); 

	void aimAt(float angle,cocos2d::Point cMoveDis,bool sound = true);
	void setRot(float angle);
	char _type; 

    int iShootNumChoose;

	
protected: 
	void updateCannon(float delta);
	float m_fUpdateTime;
	float m_fTime; 
	char cFair;
	cocos2d::Sprite * mPao;
	cocos2d::Sprite * mFire;
	cocos2d::Sprite * mFire1;
	cocos2d::Sprite * mFire2; 

	int TempTest;

	cocos2d::Point cMoveDisPos;
	cocos2d::Point cMoveBegPos;
	cocos2d::MoveTo* moveTo;

	cocos2d::Sprite * FanWeiAni;
	cocos2d::Sprite * JiGuangTwoOne;
	cocos2d::Sprite * JiGuangTwoTwo;
	cocos2d::Sprite * JiGuangTwoThree;

	cocos2d::Sprite * JiGuangThree;

	cocos2d::Label *	fengshunum;

	void ShowFire(bool bFire);
	int iCannonTime;
	bool bCannonAni;
};

#endif /* defined(__FishingJoy__Cannon__) */
