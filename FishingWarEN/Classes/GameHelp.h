 #ifndef _GAME_HELP_
#define _GAME_HELP_
#include "cocos2d.h"
#include <string.h>
#include "DialogText.h"
#include "cocos-ext.h"

USING_NS_CC; 
USING_NS_CC_EXT;
  
class GameHelp: public cocos2d::Layer 
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	void exit();									//退出

	bool onTouchBegan(Touch * touch,Event * event);
	void onTouchMoved(Touch * touch,Event * event);
	void onTouchEnded(Touch * touch,Event * event);
 
	static size_t  possText(uint8_t *buffer,size_t size,size_t nmemb,void *stream);//服务器请求回调函数
 
	void queding();
	static bool tianxieFlag;
 
	CREATE_FUNC(GameHelp);
	Size visibleSize;		
 
private:
	DialogText * shurukuang;
	Scale9Sprite * controlBg;
	Scale9Sprite * watchBg;
 
};

#endif
