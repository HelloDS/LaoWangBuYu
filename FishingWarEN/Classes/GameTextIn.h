#ifndef __GAME_TEXT_IN__
#define __GAME_TEXT_IN__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC; 
USING_NS_CC_EXT;
  
class GameTextIn: public cocos2d::Layer,public EditBoxDelegate
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	void exit();						//退出

	virtual void editBoxReturn(EditBox *editBox);
	CREATE_FUNC(GameTextIn);
	void queding();
	void update(float dt);
    void duihuanUpdate(float dt);
	void duihuan_suc(int flag);  // 1. 加金币  2. 加vip   3.加一元礼包  4.加60基金  5.加90基金

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 

	EditBox * shurukuang;
	Scale9Sprite * controlBg;
	Size visibleSize;		
	static size_t possText(uint8_t *buffer,size_t size,size_t nmemb,void *stream);//验证订单的处理函数

	static bool duihuanFlag;
	static bool fenxiang_dh_Flag;

	static int duihuanjinbi;
	static int duihuanzuanshi;
	static int duihuanhuafeiquan;

	static int duihuanvip;
	static int duihuan_1yuan;
	static int duihuan_60jj;
	static int duihuan_90jj;
	static int libaoInt;	//兑换礼包	

private:
};

#endif
