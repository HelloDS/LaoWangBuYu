 #ifndef _HONGBAO_
#define _HONGBAO_ 
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameHallLayer.h"
 
USING_NS_CC;  
USING_NS_CC_EXT;
class HongBao: public cocos2d::Layer
{
public:
	static Scene*  createScene();
	virtual bool init();
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 

	void exit(Ref * serder);
	void qianghongbao(Ref * sender);
	void xiangqing(Ref * sender);
	void fenxiang(Ref * sender);
 
	void update(float dt);
	void jieping(float dt);
	void afterCaptured(bool succeed, const std::string& outputFile);
	CREATE_FUNC(HongBao); 

private:
	Size visibleSize;	
	Point origin;

	Sprite * denglong;

	Label * hb_shuzhi;
	Sprite * gongxi;
	bool isKaishi;
	float zTime;
	int shuzhiTmp;
	char hb_tmpchar[50];

	int zuidizhi;
	int zuigaozhi;
	time_t zuiTime;

	//抢鱼币按钮
	MenuItemSprite * Item_qyb;
	MenuItemSprite * Item_fx;
};
 

class HongBaoXQ: public cocos2d::Layer, public ScrollViewDelegate
{
public:
	static Scene*  createScene();

	virtual bool init();

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 

	//ScrollView中必须实现的2个虚函数方法
	virtual void scrollViewDidScroll(ScrollView* view);
	virtual void scrollViewDidZoom(ScrollView* view);
	void afterCaptured(bool succeed, const std::string& outputFile);

	void exit(Ref * serder);
	void fenxiang(Ref * sender);

	void readXiangq();

	CREATE_FUNC(HongBaoXQ);

private:
	Size visibleSize;	
	Point origin;

	std::vector <int> wf1;
	std::vector <int> wf2; 

	Layer* containerLayer;				//视图容器
	ScrollView *scrollView;				//滚动视图

	Size xqSize;

	//抢鱼币按钮
	MenuItemSprite * Item_fanhui;
	MenuItemSprite * Item_fx;
};

#endif
