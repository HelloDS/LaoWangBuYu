 #ifndef _GONGXI_
#define _GONGXI_ 
#include "cocos2d.h"

USING_NS_CC;  
class Gongxi: public cocos2d::Layer
{
public:
	static Gongxi* create(int btnKind,std::string word);

	virtual bool init(int btnKind,std::string word);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 

	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);

	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 

	void setColor(Color3B color);

	void gongxiCD(float fdelta);
	void exit();
	void exit1();
	//CREATE_FUNC(Gongxi);
	Size visibleSize;		
private:
	int gongxiTime; 
	LabelTTF * wordTTF;
	ParticleBatchNode * batch;
	Point p1;
	Point p2;
	int kind;
};

#endif
