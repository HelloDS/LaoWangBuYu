 #ifndef _GAME_EMAIL_
#define _GAME_EMAIL_
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC; 
USING_NS_CC_EXT;
  
class GameEmail: public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	void exit();			//ÍË³ö

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 

	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);

	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 

	void lingqu();
	CREATE_FUNC(GameEmail);

	Size visibleSize;		
 
private:	

	Scale9Sprite * controlBg ; 

	int gg_yubi		  ;
	int gg_zuanshi	  ;
	int gg_huafeiquan ;
};


#endif
