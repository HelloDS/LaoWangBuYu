 #ifndef _GAME_BEGIN_SET_
#define _GAME_BEGIN_SET_
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC; 
  
class GameSet: public cocos2d::Layer,public CocosDenshion::SimpleAudioEngine
{
public:
	static GameSet * create( );
	virtual bool init( );
	void exit();									//退出
	void musicControl();							//音乐控制
	void soundControl();							//音量控制

	static bool yinyueIsON;
	static bool yinxiaoIsON;

	bool onTouchBegan(Touch * touch,Event * event);
	void onTouchMoved(Touch * touch,Event * event);
	void onTouchEnded(Touch * touch,Event * event);


	Size visibleSize;								
private:
	MenuItemSprite * soundItem;
	MenuItemSprite * musicItem;
 
	Sprite *soundKaiguan;
	Sprite *musicKaiguan;

};

#endif
