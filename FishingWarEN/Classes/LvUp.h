 #ifndef _LVUP_
#define _LVUP_ 
#include "cocos2d.h"

USING_NS_CC;  
class LvUp: public cocos2d::Layer
{
public:
	static LvUp* create(int btnKind,int num1,int num2,int num3);

	virtual bool init(int btnKind,int num1,int num2,int num3);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 

	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);

	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 

	void LvUpCD(float fdelta);
	void exit();
	//CREATE_FUNC(Gongxi);
	Size visibleSize;		
private:
	int gongxiTime;
	//ParticleSystemQuad * sajinbi;
};

#endif
