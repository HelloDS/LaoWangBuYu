 
#ifndef _SHOPJJ_
#define _SHOPJJ_

#include "cocos-ext.h"
#include "cocos2d.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IOSiAP_Bridge.h"
#endif
USING_NS_CC; 
USING_NS_CC_EXT;
 
using namespace std; 
class ShopJJ: public cocos2d::Layer 
{
public:
	static  Scene * createScene();
	virtual bool init(); 
	CREATE_FUNC(ShopJJ);		  //¥¥Ω®≤„

	void exit();									//ÕÀ≥ˆ
 
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
 
    static void yanZhengOrderJJ(string defineData,string tradeID);//验证订单
    static size_t iosPossItJJ(uint8_t *buffer,size_t size,size_t nmemb,void *stream);//验证订单的处理函数
    
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IOSiAP_Bridge * bridge;
#endif
    
    
    
    void buyYuBi(int room);						//π∫¬Ú”„±“
    void buyYuBiSuc(int flag);
    
    void init60jj(int time);// 0 ªπ√ªπ∫¬Ú  1-7 “—¡Ï»°œ‡”¶ÃÏ ˝  8 ªπ√ª¡Ï»°
	void init90jj(int time);
 
	void menu_liujj(Ref * sender);//π∫¬Úª˘Ω
	void menu_jiujj(Ref * sender);

	void qiehuan_60jj(Ref * sender);  //«–ªª±Í«©
	void qiehuan_90jj(Ref * sender);

	void lingqu_liujj(Ref * sender);  //¡Ï»°∞¥≈•
	void lingqu_jiujj(Ref * sender);

	void update(float dt);
    
    static bool fail_buy_flag;
    static bool suc_buy_flag;
    static int come_kind_jj;

    int order_flag;
private:				
	Size visibleSize;	
	Point origin;
	
	Sprite * jijin_bg;//ª˘Ω±≥æ∞
	Sprite * jijin_60_bg;  
	Sprite * jijin_90_bg;

	Sprite * jijin_60_gm;	//ª˘Ω¡Ï»°ªÚπ∫¬Ú
	Sprite * jijin_90_gm;

	Menu * bq_60_gm_menu;	//¡Ï»°ªÚπ∫¬Ú∞¥≈•
	Menu * bq_90_gm_menu;

	Sprite * jijin_60_bq;	//ª˘Ω±Í«©
	Sprite * jijin_90_bq;

	Menu * bq_60_menu;	//±Í«©∞¥≈•
	Menu * bq_90_menu;

	bool jijin_60_flag; //∞¥≈• «∑Òø…“‘µ„ª˜
	bool jijin_90_flag;

	int jj_num_60[7];
	int jj_num_90[7];
	Vec2 jj_item_pos[7];
	Vec2 ylq_item_pos[7];

	char jj_chartmp[100];

};

#endif
