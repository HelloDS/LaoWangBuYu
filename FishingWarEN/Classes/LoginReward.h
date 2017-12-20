#ifndef _LOING_REWARD_
#define _LOING_REWARD_
#include "cocos2d.h"
USING_NS_CC; 

#define SBEISHU 1
class LoginReward: public cocos2d::Layer
{
public:
	static LoginReward * create(int i);
	virtual bool init(int i);
	void exit();									//退出
	void addYubi(Object* pSender);

	bool onTouchBegan(Touch * touch,Event * event);
	void onTouchMoved(Touch * touch,Event * event);
	void onTouchEnded(Touch * touch,Event * event);

	Size visibleSize;	

	Sequence * returnAction(int i);

private:
	int  loginDays;
};

#endif
