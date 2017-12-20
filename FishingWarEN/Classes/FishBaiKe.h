#ifndef _FISHBAIKE_
#define _FISHBAIKE_
#include "cocos2d.h"
#include <string.h>
#include "cocos-ext.h"

USING_NS_CC; 
USING_NS_CC_EXT;
  
class FishBaiKe: public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	void exit();			 //退出

	bool onTouchBegan(Touch * touch,Event * event);
	void onTouchMoved(Touch * touch,Event * event);
	void onTouchEnded(Touch * touch,Event * event);


	CREATE_FUNC(FishBaiKe);
	Size visibleSize;		
 
private:
	Scale9Sprite * controlBg;
 
};

#endif
