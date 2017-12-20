 
#ifndef _WAITING_
#define _WAITING_
#include "cocos2d.h"

USING_NS_CC;
class Waiting: public cocos2d::Layer
{
public:
	static Waiting * create();
	virtual bool init();
 
    Label * word;
    void setString(std::string name);
    
    void removeIt(float dt);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 

	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);

	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
};

#endif
