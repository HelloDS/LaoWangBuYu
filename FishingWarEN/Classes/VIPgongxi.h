 #ifndef _VIPgongxi_
#define _VIPgongxi_ 
#include "cocos2d.h"

USING_NS_CC;  
class VIPgongxi: public cocos2d::Layer
{
public:
	static VIPgongxi * create(int btnKind);

	virtual bool init(int btnKind);
	void init_1();  //初始化1
	void init_2();  //初始化2

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 

	void exit();
	void VIP_xuanyao();
 
	Size visibleSize;		
	static bool gamehall_re;
	void afterCaptured(bool succeed, const std::string& outputFile);
private:
	int Vip_leixing; 
	LabelTTF * wordTTF;

	Sprite  * r_bg;
};

#endif
