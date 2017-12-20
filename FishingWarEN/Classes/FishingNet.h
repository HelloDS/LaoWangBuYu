 

#ifndef __FishingJoy__FishingNet__
#define __FishingJoy__FishingNet__
#include "cocos2d.h" 
#include "Cannon.h"
#include <vector>

using namespace std;

class FishingNet : public cocos2d::CCNode
{
public:
	static FishingNet* create(unsigned char type ,char cNetPos);

	bool init(unsigned char type ,char cNetPos);

	char cNetPosRobot;
	 
	CC_SYNTHESIZE_READONLY(int, _type, Type);
    //使FishingNet在屏幕上出现
    void showAt(cocos2d::Point pos);
	cocos2d::Point getCollisionPoint();
	 float fRadius;
	 void NetEnd();
	 bool bOver; 
	 int iNetNum; 
	  
	 
    
	 char buletBeiShu;
	 void SetPar(cocos2d::Point Pos);
	 bool bShoot;
	 vector<int> NowShootFishId;
protected:  
};
#endif /* defined(__FishingJoy__FishingNet__) */
