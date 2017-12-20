#ifndef _ONLINEREWARD_
#define _ONLINEREWARD_
#include "cocos-ext.h"
#include "cocos2d.h"
 
USING_NS_CC; 
USING_NS_CC_EXT;
using namespace std; 
class OnlineReward: public cocos2d::Layer
{
public:
	static  OnlineReward * createScene(int btnKind);
	virtual bool init(int btnKind); 
	void exit();									//ÍË³ö

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
  
	void buyYuBi();						//¹ºÂòÓã±Ò
 
	Size visibleSize;	
	Point origin;
 
private:
			
	Scale9Sprite * shopCenterBg;
	int curKind;
};

#endif
