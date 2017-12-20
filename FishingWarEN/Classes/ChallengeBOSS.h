 
#ifndef __CHALLENGEBOSS__
#define __CHALLENGEBOSS__
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC; 
USING_NS_CC_EXT;
  
class ChallengeBOSS: public cocos2d::Layer,public ScrollViewDelegate
{
public:
     void onEnterTransitionDidFinish();
	static  Scene * createScene();
	virtual bool init();
	void initCenter(); 
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	
    ~ChallengeBOSS();
    void onExit();
	void boss_exit();									//退出
	void challenge();									//退出
	void quShop();
	void quShengji();
	void tuichu();
 
	void boss_pass_info(Ref * psender);	//每个官卡的信息

	void update(float dt);
	static bool isqiehuan;    //是否切换帐号成功
	static int randNum(std::string tmp);
	static void RefreshCoin(int Num);
	static void RefreshDiamond(int Num);
	static Label * yubiLabel;								//金币数值
	static Label * zuanshiLabel;							//钻石数值
 
	CREATE_FUNC(ChallengeBOSS);
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 

	//ScrollView中必须实现的2个虚函数方法
	virtual void scrollViewDidScroll(ScrollView* view);
	virtual void scrollViewDidZoom(ScrollView* view);
 
private:
	Size visibleSize;
	Point origin;
	Vec2 pos[24];
	//Vector <Sprite *> pos_sp;
	//Vector <Menu *> pos_menu;

	int cur_boss_num;    //当前挑战序号 0，1，....，24
	bool is_boss_suc;	//是否上次挑战成功；
	bool is_boss_suc1;	//是否上次挑战成功；
	int day_times;		//当天挑战失败次数 0 1 2 3

	int boss_chall_num;  //可挑战boss次数
 
	Layer * containerLayer;					//视图容器
	ScrollView *scrollView;				//滚动视图

	Sprite * my_ship;			//我的船
	char tmp_name[30];

};

class BossInfo:public Layer
{
public :
	static BossInfo* create(int btnKind,bool huaqian);

	virtual bool init(int btnKind,bool huaqian);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 
 
	void exit();
	void tiaozhan();
	void quehuan(float dt);
	void quShop();
 	
private:
	Size visibleSize;	
	LabelTTF * wordTTF;
	Sprite* bossInfoBG;
	Point p1;
	Point p2;
	int kind;
	bool huaqianfou;
	char tmp_boss_name[30];
};
#endif