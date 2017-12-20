 
#ifndef _CANNON_UPGRATE_
#define _CANNON_UPGRATE_
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC; 
USING_NS_CC_EXT;
  
class CannonUpgrade : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	virtual bool init();
	void exit();									//退出
	String getCannonLevelName(int level);			//得到等级名字
	void upgradeCannon(Ref * sender);				//升级大炮
	void scopeCannonSwitch();						//切换到范围炮
	void laserCannonSwitch();						//切换到激光炮
	void shineFrameSwitch(int level);				//发光框
	void cannonLevelSelect(Ref * sender);			//选择大炮等级
	void change(int level);							//改变参数
	void quedingShop();
	void quedingShengji();

	void shengjilv();
	int scopeLv;
	int laserLv;

	static void RefreshCoin(int Num);
	static void RefreshDiamond(int Num);

	CREATE_FUNC(CannonUpgrade);
	cocos2d::Vector<Sprite *> light_Tree;			//背景树
	Size visibleSize;							
private:
	bool isScope;

	Sprite * scopeStyle;
	Sprite * laserStyle;
	cocos2d::ui::Scale9Sprite * scopeUpgradeBg;
	Sprite * scopeLevelBg;
	Sprite * scopeCannonLevel;						//范围炮等级
	Sprite * shineFrame;							//发光框
	Sprite * cannonModel;							//大炮模型

	int scopeChijiu[5];
	int scopeFanwei[5];
	int scopeWeili[5];

	int laserChijiu[5];
	int laserFanwei[5];
	int laserWeili[5];

	LabelTTF * chijiuLabel;							//持久数值
	ControlSlider * chijiuSlider;					//持久比例条
	LabelTTF * fanweiLabel;							//范围数值
	ControlSlider * fanweiSlider;					//范围比例条
	LabelTTF * weiliLabel;								//威力数值
	LabelTTF * jinengLabel;								//技能
	ControlSlider * weiliSlider;					//威力比例条
	//Label * jinengLabel;							//特殊技能

	static Label * yubiLabel;								//金币数值
	static Label * zuanshiLabel;							//钻石数值

	int needDiamond;
	int needLevel;
	int scopetemplevel;
	Menu * upgradeBtnMenu;
	Label * zuanshiUpgrade;							//升级所需钻石
};

#endif /* defined(__FishingJoy__Weapon__) */
