 #ifndef _ZUANPAN_
#define _ZUANPAN_ 
#include "cocos2d.h"

USING_NS_CC;  
class ZuanPan: public cocos2d::Layer
{
public:
	static ZuanPan* create(int roomNum);

	virtual bool init( int roomNum );

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 

	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);

	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 

	void exit(float dt);
	//CREATE_FUNC(Gongxi);
	void beginZ(Ref* pSender);
    
    void beginmatchover(Ref* pSender);

	
private:
	Sprite * zuanpan; //钻盘精灵
	Label * jinbiNum;//获得金币数量
	Label * zuanshiNum;//获得钻石数量
	MenuItemSprite * beginItem;//开始按钮

	int zuanpanNum[8]; //转盘上的数字
	bool isZuanDong; //转盘是否在转动
	void update(float dt);
	float zpJiaoDu; //转盘转的角度
	float zptmp; //转盘每帧转的角度
	float zpZongDu; //转盘转的总角度
	bool isjiasu; //是否加速转动中
	int jiasuZhen;//加速的帧数
	int maxJiaSuZhen;//最大加速的帧数

	int jiangliNum; //获得奖励数值
	int roomBeilv; //奖励系数
	bool isJinbi; //获得的是金币？

	int xuhao; //当前获得奖励的序号
	Size visibleSize;		
};

#endif
