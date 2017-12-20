#ifndef _GAME_HALL_H
#define _GAME_HALL_H
 
#include "cocos2d.h"
#include "cocos-ext.h"
#include "LogoLayer.h"
 
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
const int SCENENUM = 11;			//≥°æ∞◊‹ ˝
const int PAONUM = 20;			//≈⁄◊‹ ˝
const int LASERLEVEL = 5;		//º§π‚≈⁄◊‹ ˝
const int SCOPELEVEL = 5;		//∑∂Œß≈⁄◊‹ ˝
const int SUBLEVEL =3;			//«±Õß◊‹ ˝
const float HALL_ROOM_SCALE_LOW = 0.65 * 0.85;
const float HALL_ROOM_SCALE_HIGH= 0.9 * 0.85;

#define kHFIconTag 501
#define kHF_SCALE_L 0.9
#define kHF_SCALE_H 1
#define kHF_SCALE_HD_L 1
#define kHF_SCALE_HD_H 1.05

#define kCUSTEVENT_HDHF_CS "kcustevent_hdhf_cs"
#define kCUSTEVENT_HDHF_VIP "kcustevent_hdhf_VIP"
#define kCUSTEVENT_DHHF "kcustevent_dhhf"

#define kCUSTEVENT_XGHFQ "kcustevent_xghfq"
#define kCUSTEVENT_HB_JS "kcustevent_hb_js"  //∫Ï∞¸º∆ ±

class GameHallLayer : public cocos2d::Layer, public ScrollViewDelegate,public cocos2d::ui::EditBoxDelegate
{
public:
    void onEnterTransitionDidFinish();
    
    static int boss_fish_room;
    Sprite * hallBackground;
    float yutime;
    void randomFish();
    
	//¥¥Ω®≥°æ∞
	static cocos2d::Scene * createScene();
	virtual bool init();              //≥ı ºªØ
	CREATE_FUNC(GameHallLayer);		  //¥¥Ω®≤„
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);

	virtual void editBoxReturn(cocos2d::extension::EditBox *editBox);

	//ScrollView÷–±ÿ–Î µœ÷µƒ2∏ˆ–È∫Ø ˝∑Ω∑®
	virtual void scrollViewDidScroll(ScrollView* view);
	virtual void scrollViewDidZoom(ScrollView* view);
	virtual void scrollViewMoveOver(ScrollView* view) ;
 
	//¥•√˛ ¬º˛
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 

	//◊‘∂®“Â ¬º˛
	void oters_to_bsroom();
	void tanchuVip();
	void duihuanHuanfei();
    void duihuan_xiugai_huanfeiquan();
	bool checkbudan;
	//‘§‘º∫Ø ˝
	void update(float dt);

	//π´∏ÊºÏ≤‚
	static bool gonggao_vis_flag;
	static size_t gonggao_return(uint8_t *buffer,size_t size,size_t nmemb,void *stream);

	//**********************–¬∞Ê±æ
	//∞¥≈•¥¶¿Ì∫Ø ˝
	void hall_kefu_func(Ref* pSender); //øÕ∑˛∫Ø ˝
	void hall_more_func(Ref* pSender); //∏¸∂‡”Œœ∑∫Ø ˝
	void hall_shezhi_func(Ref* pSender); //…Ë÷√∫Ø ˝
	void hall_bs_xiangqing_func(Ref* pSender); //±»»¸œÍ«È∫Ø ˝
	void hall_baoming_func(Ref* pSender); //±»»¸±®√˚∫Ø ˝
	void hall_baoming_func1(float dt); //±»»¸±®√˚∫Ø ˝

	
	//≤Àµ•∞¥≈•∫Ø ˝
	void hall_lipin_func(Ref* pSender);							//¿Ò∆∑¬Î∫Ø ˝
	void hall_shengyin_func(Ref* pSender);						//…˘“Ù∫Ø ˝
	void hall_bangzhu_func(Ref* pSender);						//∞Ô÷˙∫Ø ˝
	void hall_youjian_func(Ref* pSender);						//” º˛∫Ø ˝
	void hall_tuichu_func(Ref* pSender);						//ÕÀ≥ˆ∫Ø ˝
	void shezhi_MoveOver();

	//µ◊≤ø∞¥≈•∫Ø ˝
	void hall_jiesuo_func(Ref* pSender);						//±∂¬ Ω‚À¯
	void hall_shangcheng_func(Ref* pSender);					//…Ã≥«
	void hall_shangcheng_func1(Ref* pSender);					//…Ã≥«1
	void hall_jineng_func(Ref* pSender);						//…˝º∂¥Û≈⁄
	void hall_tiaozhan_func(Ref* pSender);						//ÃÙ’Ω
	void hall_jiangbei_func(Ref* pSender);					//Ω±±≠∫Ø ˝
	void hall_bisai_func(Ref * pSender);			//Ω¯»Î±»»¸
	void hall_bisaiT_func(Ref * pSender);			//ÕÀ≥ˆ±»»¸ƒ£ Ω
	
 
	//≥ˆœ÷…Ò√ÿ…Ã»À
	void chuxianShop();
	void shenmiShop(int kind);
	void menuShenmiShop(Ref* pSender);

	//≥ˆœ÷«¿∫Ï∞¸
	void hb_onclick_jishi();
	void menuQianghongbao(Ref* pSender);
	void updateHB(float dt);
	static time_t hall_hb_time_t;   //¿Îø™¥ÛÃ¸µƒ ±º‰
	static int hall_hb_times;     // £”‡«¿∫Ï∞¸√Î ˝

    
    void menujiujisai(Ref* pSender);
    
	//VIPÃÿ»®
	void menu_viptequan(Ref* pSender);			
	void baoming_vip(Ref* pSender);

	//add by zxf
	void showAds(Ref* pSender);

	//“ª‘™¿Ò∞¸
	void menu_yiyuan(Ref* pSender);

	//ª˘Ω∞¥≈•
	void menu_jijin(Ref * pSender);
 
	//÷–º‰≤ø∑÷
	void enterFishManage( );				//Ω¯»Î”Ê≥°
	void roomUnlockManage( );			//Ω‚À¯∑øº‰
	void hall_gengzheng();		//∏¸–¬srollviewµƒŒª÷√

	void hall_room_moveUp();   //»√≥°æ∞∂Ø∆¿¥
	void hall_room_moveDown();   //»√≥°æ∞æ≤œ¬¿¥

	void queding();
	void quShop();
	void quJiesuo();
	void shengjilv();

	void moveToLeft( );
	void moveToRight( );
	void canMove();

	void first_match_tishi();  // ◊¥Œ±»»¸Ã· æ

	//±»»¸∑øº‰“∆∂Ø
	void moveBSLeft();
	void moveBSRight();
	void canBSMove(float dt);
	void BS_gengzheng(float dt = 0.6f);		//∏¸–¬srollview1µƒŒª÷√
	void BS_bianliang(int i);
	void BS_qiehuan();   //«–ªª∑øº‰Ãÿ–ß
	void BS_qh_order();   //«–ªª∑øº‰≤„º∂
	void BS_checkAll();  //ºÏ≤‚µ±«∞±»»¸∑øº‰
	void BS_MoveOver();   //∏¸–¬ÕÍ≥… ‘ŸºÏ≤È“ª±È
	void BS_anniu_dit(float dt);


	//æ≤Ã¨±‰¡ø

	static bool isqiehuan;  // «∑Ò«–ªª’ ∫≈≥…π¶

	static int RoomType;
	static bool exitIsCun;
	static bool failFlag;
	static int failInt;
	static int sceneLowPao; //∑øº‰◊Ó∏ﬂ±∂¬ 
	static int sceneHighPao;	//∑øº‰µÕ±∂¬ 	
 
	static string wordKind; //◊÷ÃÂ÷÷¿‡
	static bool checkRedPoing;
	static bool hall_bShengyinShow;//…˘“Ù∞¥¡À∑Ò
	static bool hall_hb_kaiguan;
	static bool is_bs_xianshi;  //±»»¸√Ê∞Â «∑Òœ‘ æ¡À
	static bool vip_goumai_flag;  //vipπ∫¬Ú≥…π¶ ±Í÷æ
	static bool isCheckBS;		// «∑Ò–Ë“™∏¸–¬±»»¸∑øº‰
	static bool isSaleVis;		// «∑Òø™∆Ù¥Ÿœ˙…Ã≥«∂Øª≠
 
	static void RefreshCoin(int Num);
	static void RefreshDiamond(int Num);
	static void initRoom();
    
    
    static char cjingxipingbi;
 
	//±»»¸ÀÊª˙µƒ–≈œ¢
	static int bs_moshi;	//1-4
	static int bs_RenShu[4];   //∑øº‰±»»¸»À ˝
	static int robot1[3];	//ª˙∆˜»À1 µƒ–≈œ¢  Œª÷√ Õ∑œÒ  √˚◊÷
	static int robot2[3];	
	static int robot3[3];
	static int player_pos;  //ÕÊº“µƒŒª÷√

	//≥ı ºªØ 
	void init_1(float dt);  
	void initDingbu();
	void initCaiDan();
	void initZhongJian();
	void initBSRoom();
	void initDibu();

	//±‡º≠–≈œ¢
	void xzTouxiang(Ref* pSender);//—°‘ÒÕ∑œÒ
	void qdTouxiang(Ref* pSender);//»∑∂®Õ∑œÒ
	void qd_jiesu(float dt); //…Ë÷√Õ∑œÒµƒø…º˚∂»
	Vector<Menu *> Touxiang;//¥Ê∑≈Õ∑œÒvec
	bool isEditTx;  // «∑Ò’˝‘⁄±‡º≠Õ∑œÒ

	//±»»¸Ãÿ–ß2∫Ø ˝
	void init_BS1();
	void bs1_display(int num); //œ‘ æµ⁄º∏πÿ
	void bs1_bgg_call();   //±»»¸±≥æ∞π‚ ªÿµ˜
private:
 
	//±»»¸Ãÿ–ß2±‰¡ø
	int bs1_yinxiao_flag;
	Sprite * bs1_room_bgg;   //±»»¸∑øº‰µƒ±≥æ∞π‚
	float bs1_room_bgg_flag_rotate;  //±»»¸∑øº‰–˝◊™µƒ±Í÷æ(0  - 1)
	ParticleBatchNode * bs_room_bg_yb;  //±»»¸”„±“
	ParticleBatchNode * bs_room_bg_hfq;  //±»»¸ª∞∑—»Ø

	Sprite * bs1_room_bg;	//±»»¸±≥æ∞
	Sprite * bs1_room_ksrs;  //ø™»¸»À ˝æ´¡È

    
    Sprite * bs1_zuozi;		//左比赛房间提示
    Sprite * bs1_youzi;		//右比赛房间提示
    
    int pingTimes;			//pingµƒ¥Œ ˝
    string bs_jiangbei_name[4];
	string bs_duandai_name[4];

    Vec2 bs_huafeiquan_zz[4][3];
	//Ω±±≠…œ–«–«µƒŒª÷√
	Vec2 bs_jiangbei_xx[4][3];

	Vector <Sprite *> bs1_jiangbei_vec;   //Ω±±≠»›∆˜
	Vector <Sprite *> bs1_duandai_vec;   //±»»¸∂–¥¯»›∆˜
 
	Menu * bs1_room_xiangq;				//±»»¸œÍ«È∞¥≈•
	Sprite * bs1_room_xiangq_heidi;		//±»»¸œÍ«È∫⁄øÈ
	Sprite * bs1_room_xiangq_yingzi;	//±»»¸œÍ«È”∞◊”

	//vip
	Sprite * hall_vip_sp;
	Menu * hall_vip_anniu;
	

	//∫Ï∞¸∞¥≈•
	Menu * hall_hb_anniu;
	float hall_hb_time;
	Label * hall_hb_time_l;
	Sprite *hall_sp_hb_k;
 
    Menu * hall_jiujisai_anniu;
	//*****–¬∞Ê±æ
	Menu  * hall_menu_kf;			//øÕ∑˛≤Àµ•
	Menu * hall_menu_bs;			//±»»¸∞¥≈•
	Menu  * hall_menu_bs_tishi;		//≤Àµ•
	Menu * hall_menu_bsT;			//Õ∆≥ˆ±»»¸∞¥≈•
	Menu  * hall_menu_more;			//∏¸∂‡”Œœ∑
	Sprite * hall_menu_shezhi_cl;   //≤Àµ•≥›¬÷
	Menu  * hall_menu_shezhi;		//≤Àµ•
	Menu  * hall_menu_lipin;		//¿Ò∆∑¬Î
	Sprite * hall_sc_bgguang;       //…Ã≥«±≥æ∞π‚
	Menu  * hall_Shop ;				//…Ã≥«∞¥≈•

	Sprite * hall_sprite_shengyin;   //…˘“Ùæ´¡È
	Sprite * hall_sprite_shengyin_d;	//…˘“Ùæ´¡Èd
	Menu  * hall_menu_shengyin;		//…˘“Ù
	

	Menu  * hall_menu_wenhao;    //∞Ô÷˙
	Menu  * hall_menu_youjian;    //” º˛
	Menu  * hall_menu_tuichu;    //ÕÀ≥ˆ
	bool hall_bSetShow;   //…Ë÷√∞¥¡À∑Ò

	Sprite * hall_dibu_sprite_jiesuo;     //µ◊≤ø±∂¬ Ω‚À¯∞¥≈•
	Sprite * hall_dibu_sprite_shangcheng;     //µ◊≤ø…Ã≥«∞¥≈•
	Sprite * hall_dibu_sprite_jineng;     //µ◊≤øººƒ‹∞¥≈•
	Sprite * hall_dibu_sprite_tiaozhan;     //µ◊≤øÃÙ’Ω∞¥≈•

	Menu  * hall_dibu_menu_shangcheng;

	static Label * yubiLabel;		//”„±“ ˝¡ølabel
	static Label * zuanshiLabel;	//◊Í Ø ˝¡ølabel
	Label * jiangbeiLayer;			//Ω±±≠ ˝¡ølabel

	Sprite * hall_lt_sprite;   //∑øº‰œ¬∑Ω¡¡Ãı
	Sprite * hall_dingbu_bg; //∂•≤ø±≥æ∞
 
	//–«–«
	Sprite * hall_dibu_beilv_xing;
	Sprite * hall_dibu_dapao_xing;

	//…Ã≥«buff
	Sprite * hall_dibu_shop_xing;
	Sprite * hall_dibu_shop_xing1;

	//ÃÙ’Ω∫Ï»¶
	Sprite * tiaozhanHongQ;
	Label * tiaozhanShuZi;
	//Label * tiaozhanShuZi1;
	int tiaozhanShu;   

	//“ª–©±‰¡ø
	int  subLv;				//«±Õßµ»º∂£®1°¢2°¢3£©
	int  laserLv;			//º§π‚≈⁄µ»º∂£®1°¢2°¢3°¢4°¢5£©
	int  scopeLv;			//∑∂Œß≈⁄µ»º∂£®1°¢2°¢3°¢4°¢5£©
	int  unlockRoomNum;		//“—Ω‚À¯≥°æ∞ ˝£®1°¢2°¢3°¢4°¢5°¢6£©
	int roomFlag[12];			//Ω‚À¯∑øº‰±‡∫≈  
	int curDay;
	char hallCharTemp[100];  //◊÷∑˚±‰¡ø
	float scaleTmp;
	Size visibleSize;
	Point origin;

	//∂Øª≠
	Vector <RepeatForever * > hall_boss_a; //12∏ˆboss∂Øª≠ ˝◊È
	Vector <RepeatForever * > hall_shuicao1_a;   //12∏ˆÀÆ≤›∂Øª≠1
	Vector <RepeatForever * > hall_shuicao2_a;	//12∏ˆÀÆ≤›∂Øª≠2

	Vector <FadeIn  * > lg_fadeIn;	//12∏ˆ¡¡π‚fadeIn
	Vector <FadeOut * > lg_fadeOut;	//12∏ˆ¡¡π‚fadeOut

	//∑øº‰±‰¡ø
	Vector <Sprite * > hall_room_spec;   //∑øº‰»›∆˜
	Layer* containerLayer;				// ”Õº»›∆˜
	ScrollView *scrollView;				//πˆ∂Ø ”Õº
	int hall_scroll_offset;			//scrollViewµƒ∆´“∆¡ø
	Size roomSize;						//∑øº‰¥Û–°
	int roomSpaceLenth;					//∑øº‰º‰∏Ùæ‡¿Î
	int hall_room_index;				//µ±«∞œ‘ æ∑øº‰À˜“˝ 1°¢2°¢3.°£°£12
	bool hall_room_is_moveing;			//≈–∂œµ±«∞À˜“˝∑øº‰ «∑Ò’˝‘⁄≤•∑≈∂Øª≠
	int sv_offset;		//∑øº‰µƒ∆´“∆¡ø
	int hall_sv_space1;   //scrollview  “∆∂Øµƒº‰∏Ù1
	int hall_sv_space2;   //scrollview  “∆∂Øµƒº‰∏Ù2
	bool scrollview_begin_m; //scrollView  «∑Òø™ º“∆∂Ø¡À
	bool dianji_begin_m; // «∑Ò’˝‘⁄µ„ª˜
	bool hall_room_direct;    //∑øº‰“∆∂Øµƒ∑ΩœÚ   1.true  œÚ”“£¨2.false œÚ◊Û

	//±»»¸∑øº‰±‰¡ø
	//Vector <Sprite * > hall_bsroom_spec;   //∑øº‰»›∆˜
	//Layer* containerLayer1;				// ”Õº»›∆˜
	//ScrollView *scrollView1;				//πˆ∂Ø ”Õº
	Size roomSize1;						//∑øº‰¥Û–°
	//int bs_room_index;				//µ±«∞ «µ⁄º∏∏ˆ∑øº‰

	bool bs_room_is_moving;			//±»»¸∑øº‰ «∑Ò‘⁄“∆∂Ø
	

	Point mouse_p1;		// ÷÷∏ø™ ºµ„ª˜∆¡ƒªµƒµ„1
	Point mouse_p2;		// ÷÷∏¿Îø™∆¡ƒªµƒµ„2

	string roomTitleName[12];		//∑øº‰√˚≥∆
	string roomPhotoName[12];		//∑øº‰Õº∆¨
	string roomBossName[12];		//∑øº‰bossÕº∆¨

	bool isEnterYu;  // «∑ÒΩ¯»Î”„≥°
	bool isBiSai;    // «∑ÒŒ™±»»¸ƒ£ Ω
	bool isDit;		// «∑Òø…“‘µ„ª˜

	//Ã· ææ´¡È
	Vector <Sprite *> hall_tishi_vec;  //µ±«∞∑øº‰Œª÷√Ã· æ»›∆˜
	Sprite * hall_zuojiantou;		//◊Ûº˝Õ∑Ã· æ
	Sprite * hall_youjiantou;		//”“º˝Õ∑Ã· æ
};

class Game_BS_XiangQ:public Layer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	void exit();									//ÕÀ≥ˆ

	bool onTouchBegan(Touch * touch,Event * event);
	void onTouchMoved(Touch * touch,Event * event);
	void onTouchEnded(Touch * touch,Event * event);
 
	CREATE_FUNC(Game_BS_XiangQ);
	Size visibleSize;		
 
private:
	Sprite * callBg;
	Vec2 yb_pos[4];
	Vec2 zs_pos[4];
};

//∂“ªªª∞∑—
class Game_Hall_Kefu: public cocos2d::Layer , public ScrollViewDelegate
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	void exit();									//ÕÀ≥ˆ

	virtual void scrollViewDidScroll(ScrollView * view);		
	virtual void scrollViewDidZoom(ScrollView * view);		

	bool onTouchBegan(Touch * touch,Event * event);
	void onTouchMoved(Touch * touch,Event * event);
	void onTouchEnded(Touch * touch,Event * event);
 
	void duiHuaFei(int room);
	void huodeHF(Ref * psender);
	CREATE_FUNC(Game_Hall_Kefu);
		
 
private:
	Size visibleSize;	
	Size winSize;

	ScrollView * yubiView;							//”„±“√Ê∞Â
	Layer * yubiLayer;								//”„±“◊Í Ø≤„
	Vector <Sprite *> sp_yubi;				//”„±“◊Í Ø»›∆˜
 
	int cur_room;
	Point p1;
	Point p2;
	float layer_x;
	Size roomSize;
};

//ªÒ»°ª∞∑—»Ø
class Game_Hall_Kefu1: public cocos2d::Layer , public ScrollViewDelegate
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	void exit();									//ÕÀ≥ˆ

	virtual void scrollViewDidScroll(ScrollView * view);		
	virtual void scrollViewDidZoom(ScrollView * view);		

	bool onTouchBegan(Touch * touch,Event * event);
	void onTouchMoved(Touch * touch,Event * event);
	void onTouchEnded(Touch * touch,Event * event);
 
	void duiHuaFei(int room);
	void huodeHF(Ref * psender);

	void tanchuVip(Ref * psender);
	CREATE_FUNC(Game_Hall_Kefu1);
		
 
private:
	cocos2d::ui::Scale9Sprite * shopCenterBg;

	Size visibleSize;	
	Size winSize;

	ScrollView * yubiView;							//”„±“√Ê∞Â
	Layer * yubiLayer;								//”„±“◊Í Ø≤„
	Vector <Sprite *> sp_yubi;				//”„±“◊Í Ø»›∆˜
 
	int cur_room;
	Point p1;
	Point p2;
	float layer_x;
	Size roomSize;
};
  
//«¿∫Ï∞¸
class Game_Hall_Kefu2: public cocos2d::Layer , public ScrollViewDelegate
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	void exit();									//ÕÀ≥ˆ

	virtual void scrollViewDidScroll(ScrollView * view);		
	virtual void scrollViewDidZoom(ScrollView * view);		

	bool onTouchBegan(Touch * touch,Event * event);
	void onTouchMoved(Touch * touch,Event * event);
	void onTouchEnded(Touch * touch,Event * event);
 
	void clickItem(int room);

	void duihongbao();
	void fahongbao();
	void qianghongbao();
 
	CREATE_FUNC(Game_Hall_Kefu2);
	void updateHB(float dt);
		
	//∑÷œÌµØ≥ˆøÚ
	void fenxiang_tck_wx();  
	void fenxiang_tck_pyq();
	void fenxiang_tck_tc();
private:
	cocos2d::ui::Scale9Sprite * fenxiang_tck_bg;
	bool fenxiang_is_vis; //∑÷œÌøÚ «∑Òø…º˚
 
	cocos2d::ui::Scale9Sprite * shopCenterBg;

	Size visibleSize;	
	Size winSize;

	ScrollView * yubiView;							//”„±“√Ê∞Â
	Layer * yubiLayer;								//”„±“◊Í Ø≤„
	Vector <Sprite *> sp_yubi;				//”„±“◊Í Ø»›∆˜

	char tmpHonbao[50];
	Sprite * daojishi_sp;  //µπº∆ ±±≥æ∞
	LabelTTF * daojishi_lb;	//µπº∆ ±label
	bool daojishi_is_vis;
 
	int cur_room;
	Point p1;
	Point p2;
	float layer_x;
	Size roomSize;
};
 
class Game_Hall_Sale: public cocos2d::Layer 
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	void exit();									//ÕÀ≥ˆ

	bool onTouchBegan(Touch * touch,Event * event);
	void onTouchMoved(Touch * touch,Event * event);
	void onTouchEnded(Touch * touch,Event * event);
 
	CREATE_FUNC(Game_Hall_Sale);
	Size visibleSize;		
 
	int curDay;
	char sale_tmp[50];
	Sprite * box_baby;
	void vis_box(float dt);
private:
 
};

class Game_Hall_Huafei: public cocos2d::Layer ,public cocos2d::ui::EditBoxDelegate
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	void exit();									//ÕÀ≥ˆ

	bool onTouchBegan(Touch * touch,Event * event);
	void onTouchMoved(Touch * touch,Event * event);
	void onTouchEnded(Touch * touch,Event * event);
	virtual void editBoxReturn(cocos2d::ui::EditBox *editBox);

	Sprite * controlBg;
	cocos2d::ui::Scale9Sprite * controlBg1;
	CREATE_FUNC(Game_Hall_Huafei);

	void queding();
	static size_t possText(uint8_t *buffer,size_t size,size_t nmemb,void *stream);//—È÷§∂©µ•µƒ¥¶¿Ì∫Ø ˝

	void duihuan();
 
private:
	Size visibleSize;		
	char huafei_tmp[50];
	cocos2d::ui::EditBox * shurukuang;
	cocos2d::ui::EditBox * shurukuang1;

	int curHuafeiKind;
};
#endif