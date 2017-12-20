 
#ifndef _SHOP_
#define _SHOP_

#include "cocos-ext.h"
#include "cocos2d.h"
#include "Waiting.h"
#include "sqlite3.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IOSiAP_Bridge.h"
#endif

 
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#ifdef __cplusplus
extern "C"{
#endif

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_buySuccess(JNIEnv * env, jclass ); 
JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_buyFail(JNIEnv * env, jclass );
JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_buyIng(JNIEnv * env, jclass ); 


#ifdef __cplusplus
}
#endif

#endif

USING_NS_CC; 
USING_NS_CC_EXT;
#define  YUBINUM 7
#define  SHOP_ROOM_H 0.9
#define  SHOP_ROOM_L 0.85
// struct budan_data
// {
//     string recive_data;
//     string tradeno;
//     string productid;
//     int rmb;
// };
using namespace std; 
class Shop: public cocos2d::Layer,public ScrollViewDelegate
{
public:
	Shop();
	~Shop();
	static   Shop * create(int btnKind);
	virtual bool init(int btnKind); 
	void init_shop();
	void init_vip();
    void init_yiyuan();
	void exit();									//ÕÀ≥ˆ
 
    bool otherpay;
	bool mIsMSMPay;
	void shopMsg();
    void shopapp();
    void shopmol();
    void shoptrue();
    //ios 补单
    void ios_budan();
    void ios_budan_yy(float dt);   //预约0.1s后执行
    void ios_budan_curl(string recipeData,string tradeNo,string productID,int rmb);
    static size_t ios_budan_poss(uint8_t *buffer,size_t size,size_t nmemb,void *stream);//验证订单的处理函数
    
  //  vector<budan_data> ios_daibudan;
    void get_budan_data();
    static void insert_budan_data(string recipeData,string tradeID,string productID,int rmb);  //receipt-data=%s&tradeId=%s&deviceId=%s&productId=%s&rmb=%d&version=%s
    static void delete_budan_data(string tradeno);
    
	virtual void scrollViewDidScroll(ScrollView * view);		
	virtual void scrollViewDidZoom(ScrollView * view);		
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    Sprite * m_SprShopApp;
    Sprite * m_SprShopTrue;
    Sprite * m_SprShopMol;
	Sprite * m_SprShopSMS;
    
    static bool iosBuyFailFlag;
    static string iosDefineData;
    static string iosTradeID;
    static bool yanzhangFlag;
    
    void menu_yiyuan();
 
	void buyYuBi(int room);						//π∫¬Ú”„±“
	void buyYuBiSuc(int flag);  

	void buyYuBiBySMS(int room);
	void buyYuBiSucBySMS(int flag);

	void budan(float dt);   //◊‘∂Ø≤πµ•
	static int budan_times;

	Size visibleSize;	
	Point origin;
    
    void huifugoumai();
    static bool huifuFlag;

	void webPayFinish( cocos2d::Ref* pRef );
	void webPayFinishTimer(float dt);
	void webPayCallbackTimer(float dt);

	//add by zxf
	bool isWebPaySuccess;


	// 新的谷歌充值函数 
	void onPayChanged(EventCustom* event);
	static size_t GooglePay_poss(uint8_t *buffer, size_t size, size_t nmemb, void *stream);
	EventListenerCustom*       _event;
	static Shop * pStaticShop;
	static const char * GOOGLE_PAY;


#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IOSiAP_Bridge * bridge;
#endif
    
    
    static void yanZhengOrder(string defineData,string tradeID);//验证订单
    static size_t iosPossIt(uint8_t *buffer,size_t size,size_t nmemb,void *stream);//验证订单的处理函数
    
    static bool isCeShi;
    static bool budanFlag;
    static bool budanFlag1;
    static bool budanFlag2;
    static bool successFlag;
    static bool yanZhengFlag;
    static bool failFlag;
	static bool yanzhengFailFlag;
	static int yanzhengInt;
	static   bool bFeiFa;
	static float yubi_num[YUBINUM];
	static float yubiNumMSM[4];  //短代的鱼币数量
	static float zuanshi_num[YUBINUM];
	static float zuanshiNumMSM[4];  //短代的钻石数量
    static float sPrice[YUBINUM];
	static int sPriceMSM[4];		//短代的价格

    static bool BigPay;
    static bool BigPaySuccess;

 
	static int orderShopKind;//π∫¬Ú÷÷¿‡£®1°¢2°¢3°¢4°¢5°¢6°¢7°¢£©
 
	void shanchu(float dt);
	void shanchu1(float dt);
    void MenuVip(Ref* pSender);  //”µ”–vip

	int zengsong_sz[6];
	static float sale_percent[4];
	
 
	static string goumaileixing;//π∫¬Ú¿‡–Õ
	static string defineData;  //∑¢ÀÕ∏¯adroidµƒ◊‘∂®“Â ˝æ› 
 
	void yanZhengOrder(string tradeID);//—È÷§∂©µ• «∑ÒÕ®π˝
	static size_t possIt(uint8_t *buffer,size_t size,size_t nmemb,void *stream) ;
	static size_t possIt1(uint8_t *buffer,size_t size,size_t nmemb,void *stream) ;
    
    void hide_jinguang(float dt);
    
    static int  comeKind;
private:
	ScrollView * yubiView;							//”„±“√Ê∞Â
    Vector <Sprite *> sp_yubi;				//”„±“◊Í Ø»›∆˜
    Vector <ParticleBatchNode *> node_jinguang;	//”„±“◊Í Ø»›∆˜
	Layer * yubiLayer;								//”„±“◊Í Ø≤„
					
	cocos2d::ui::Scale9Sprite * shopCenterBg;
	void update(float delta);

	int cur_room;
	Point p1;
	Point p2;
	float layer_x;
	Size roomSize;
	
	int shanchuTmp;
	int shop_sale_tag;
    
    Sprite * m_SprLiBao;


	float mWebPayWaitTime;
	std::vector<Sprite*> mYubiObgs;
	void resetYubiObg();
};

#endif
