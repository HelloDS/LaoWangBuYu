#include "cocos2d.h" 
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class UnLockLayer:public cocos2d::Layer ,public ScrollViewDelegate 
{
public:
	UnLockLayer(void);
	~UnLockLayer(void);
	static Layer * create(int lockKind);
	virtual bool init(int lockKind);
 
	virtual void scrollViewDidScroll(ScrollView * view);		
	virtual void scrollViewDidZoom(ScrollView * view);	
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 

	//******************
	void spriteBegin(cocos2d::Ref* pSender);
	void MoveOver(); 
	
	void quShengji();
	void FadeIn();
	void ShanShuo();
	void quShengji2();
	void shengjilv();
	void goumaizuanshi();
	void goumaiwuqi();
	static bool ul_success;
	Rect BgRect;

	//新版
	void ditFunc(int i);  //解锁某个炮
	void update(float delta);
	void  Exit() ;

	int cWuqiLv[20];
	int cWuqiXiaoHao[20];
	int cWuqiXiaoHaoJinBi[20];
	int cBeiLv[20];

	Sprite * createSprite(int i);

	int blockKind;
	std::string jiesuopaoBg[20];
	std::string jiesuopao[20];

	Size visibleSize;
	int myJieSuoNum;
	Size roomSize;
	float paoBeginPos;
	float spacePaoLength;

	int cur_room;
	Point p1;
	Point p2;
	float layer_x;
 
	Point Pos[20];
	cocos2d::Vector<Sprite*> m_Tree;
	Scale9Sprite *paoBG;

	Layer* containerLayer; 
	ScrollView * scrollview;

	float m_frameUpdate;
	float m_frameTime;

	//发光；
	Sprite* faGuangBG;
	bool hitFlag;
	bool CanBtn;
private:
 
	
 
};

