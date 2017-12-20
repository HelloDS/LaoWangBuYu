#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "FishLayer.h"
#include "CannonLayer.h"  
#include "FishTrack.h" 
#include "Mission.h"
#include "Shop.h"
#include "AllRobot.h"

#define MENULAYER 1000

USING_NS_CC; 
USING_NS_CC_EXT; 

typedef enum{
	k_Operate_Pause = 0,
	k_Operate_Resume
}OperateFlag;

struct FenShu
{
	long long fenshu;
	int flag;
};
//wftishikuang
class GameScene : public cocos2d::Layer
{
public:
    void xiaxian();
    void onEnterTransitionDidFinish();
 
    int huidang_flag;
	static cocos2d::Scene* createScene(); 
	virtual bool init(); 
	void init_jishi();
	void init_bisai();
	~GameScene();

	CREATE_FUNC(GameScene);


	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 


    //ji jin
 //   Menu * scene_jijin_anniu;
    void menu_jijin();
    
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);

	int OnlineStateInt; //ºÏ≤‚Õ¯¬Á◊¥Ã¨µƒ¡Ÿ ±±‰¡ø
	int OnlineTimes;	//÷ÿ¡¨¥Œ ˝
 
	Menu* m_Shop; 

	Menu* m_RobotShoot;
	Size visibleSize;
	Point origin;

	Sprite * paimingXX;
	Sprite * wodepaiming;
	Label * wfRank;
	Sprite * wodepaiming1;
	Label * wfRank1;

	int cBeginTimeRobotShoot;
	AllRobot wfAllRobot;
	static bool isqiehuan;

	//±»»¸ «∑Ò∂œø™≈–∂œ
	static bool isduankai;			// «∑Ò∂œø™
	static time_t houtaiTime;		//«–µΩ∫ÛÃ®µƒµ±«∞ ±º‰
	static time_t qiantaiTime;		//ªÿµΩ«∞Ã®µƒµ±«∞ ±º‰
 
    static bool bPlayPanzi;
    static int iPanziMoney;
 
	//”Œœ∑≤Àµ•∞¥≈•
	Sprite * menu_shezhi_cl;
	Sprite * hall_sprite_shengyin;
	Sprite * hall_sprite_shengyin_d;
	Menu * m_GameMenu;
	Menu *  gameQuitMenu;
	Menu *  gameHelpMenu;
	Menu *  gameSetMenu;
	Menu *  gameLipinmaMenu;
	bool bGameSetShow;

	void GameSetox(cocos2d::Ref* pSender);
	void GameQuit(cocos2d::Ref* pSender);
	void GameHelp(cocos2d::Ref* pSender);
	void GameLipin(cocos2d::Ref* pSender);
	void GameSet(cocos2d::Ref* pSender);
	void exitRoom(float dt);
	void MoveOver();

	static bool bRobotVip[4];				//ª˙∆˜»À «∑ÒŒ™vip
	void CheckRobotIfVip();
	static bool bRobotPos[4];
	static char cRobotIQ[4];			//1 «–›œ–£¨2 «æ´√˜£¨3 «Õ¡∫¿
	static char cSelfPos;
	static float game_zhenlv;

	char GetRobotIQ();
	void CheckRobotShoot(char cRobotPos);
	
	//ooxx
	ParticleSystemQuad * sajinbi;
	static bool bSaJingbi; 
	void OpenTouch(float delta); 

	cocos2d::CCParticleSystemQuad* m_BaoZha1;
	cocos2d::CCParticleSystemQuad* m_BaoZha2; 
	cocos2d::CCParticleSystemQuad* m_BaoZha3;   
	static bool bBaoZha;
	static Vec2 DeadFishPos;
	  
	//≥°æ∞“—±©ª˜
	static bool isbaoji;
	 
	Sprite* wfsb; 

	//»ŒŒÒœ‡πÿ
	Mission * mission;
	   
	void menuMax(cocos2d::Ref* pSender);
	void menuMin(cocos2d::Ref* pSender);

	void menuShop(Ref* pSender);  

	void queding();
	void quxiao();
    
    
    char cRobotShootTimeWf[4];
    char cRobotShootTimeOverwf[4];
    
 
	int iAddRobotTime;
	int iChangeRobotBaseTime[4];		
	int iChangeRobotBaseRandTime[4];	
	
	int iChangeExPaoTime[4];		
	int iChangeExPaoRandTime[4];		
	int iChangeExPaoRandTimeEnd[4];

	//¥•√˛“≥√Êœ‡πÿµƒ∫Ø ˝
	void cannonAimAt(cocos2d::Point target);
	void RobotcannonAimAt(cocos2d::Point target,char cPos);

	void cannonShootTo(cocos2d::Point target);
	void RobotCannonShootTo(cocos2d::Point target,char cPos);
 
	void GetBossMoney();
	static bool stopBossTime;
	void BossAddMoneyZuan(char cType);
 
	int iBossXue; 
	int BossMoney ;
	int BossZuanShi ; 
	char  BossTimeFen;
	char BossTimeMiao;
	ControlSlider* _progressBossBar;

	static char GoNewSence;
 
 
	void ShowNextGuan();
	void ShowBossJiangli();

	//0Œ™’˝≥£1Œ™±»»¸2Œ™ÃÙ’ΩBOSS
	static char cGameType;
    int iRoomType;

	Sprite* BossGuanOne;
	Label * BossMoneyOne;
	Label * BossMoneyTwo;
    LabelTTF* mDiamondLabel;
    LabelTTF* mGoldLabel;
	Sprite* m_SprBoss;
	static bool bShowShangCheng;
	void TiaoZhanChengGong(float dt);
	Menu * btnMenu; 
	bool bNoShoot;

	void menuGoSence(Ref* pSender);
	void menuGoSenceTwo(Ref* pSender);
 
	static FILE * moneyTXT;
	static FILE * expTXT;
	static FILE * zuanshiTXT;
	//static bool updateData(string Item,int data);
	//static sqlite3 *pdb;

    int PlayPanZia;
    int PlayPanZib;
    int PlayPanZic;
    
    void PlayPanZi(float delat);
     
	void CallPanZiOver();
	Sprite * temp2;
	Label * LabelFishNum;
	Sprite * panziguang; 
 
	static Label * bs_jfb_l[4]; //ª˝∑÷∞Ê—° ÷ª˝∑÷ 0 player  1°¢2°¢3ª˙∆˜»À
	static LabelTTF * bs_jfb_n[4]; //ª˝∑÷∞Ê—° ÷ª˝∑÷ 0 player  1°¢2°¢3ª˙∆˜»À
	static long long bs_jfb_num[4];	//—° ÷µƒª˝∑÷   0 player  1°¢2°¢3ª˙∆˜»À
	void bs_jifenban_hs();
	static void bs_jiafen(int i , int num); //∏¯—° ÷º”∑÷ i 0 player 1/2/3 ª˙∆˜»À   num º”∑÷ ˝¡ø
	void bs_jifenban_sj(float dt);   //ÀıΩ¯ª˝∑÷∞Ê


	void updateTouchLayer(float delat);
	void menu_viptequan();  //vipÃÿ»®
	static bool vip_goumai_flag;  //vipπ∫¬Ú≥…π¶ ±Í÷æ

	//‘⁄œﬂ¡ÏΩ±
	Menu* m_AddMoney;
	Sprite * m_zaixianGuang;
	void AddMoney(Ref* pSender);

	Label *TimeMin;
	Sprite* MaoHao;
	Label *TimeMiao;   //∑÷√Î √∞∫≈

	int cTimeMin;
	int cTimeMiao;
	int lingj_time;

	int lingjiang_state; //µ±«∞¡ÏΩ±◊¥Ã¨  0£¨≤ª“™◊≈º±    1£¨ø…“‘¡ÏΩ±
	bool bTouch;
    bool bSound;
    bool bShootSound;
    
	int LingMoney;
	bool SetTimeLingJiang();
	static bool lingjiangflag;  // «∑Ò∏¸–¬‘⁄œﬂ¡ÏΩ±
 
	//“˝µºΩ¯±»»¸ΩÁ√Ê
	void yindaoBiSai();
	void paimingAni(int rank); // ≈≈√˚∂Øª≠
	void changeRank();
	static bool isBiSaiVis;// «∑ÒµØ≥ˆ±»»¸“˝µº
    
    void load_gailv(char cinfo);
    static size_t load_gailv_call(uint8_t *buffer,size_t size,size_t nmemb,void *stream) ;
    static float gailv_jia[33];			//∏≈¬ º”∑÷ ˝◊È
    static float gailv_jian[33];		//∏≈¬ ºı∑÷ ˝◊È
    static float jia_gailv;				//∏≈¬ º”∑÷±»
    static float jian_gailv;			//∏≈¬ ºı∑÷±»
    static bool is_success_load;		// «∑Ò≥…π¶∏¸–¬∏≈¬
    static int gailv_shijian;			//∏≈¬ ‘§‘º ±º‰¿‡
     
    int gailv_load_times;   //µ±«∞‘§‘º ±º‰
    //void load_yuyue(float dt);
    static bool bOverBisai;
    void first_match_reward(float dt);
    void suiji_jiafen();
    static bool is_jiafen; 
private: 
	Menu * hall_menu_bs;			//±»»¸∞¥≈•

	bool haveQiongShen;
 
	Sprite * jiasuspr10;
	Sprite * Guang;
	Sprite * Guang1;

	MenuItemSprite * bs_jifenban; //±»»¸º∆∑÷∞Â
	bool bs_isjifen; //ª˝∑÷∞Ê «∑Òœ‘ æ
	float bs_jifentime;  //5s∫Û æÕ≥∑

 
	Menu * scene_vip_anniu;  //vip Ãÿ»®
	Sprite * scene_vip_sp;

	FishLayer* m_pFishLayer;
	CannonLayer* m_pCannonLayer;  

	void updateScence(float delat);
	void updateInfo(float delat);
	char cUpdateTime;
    char cUpdateSound;
    
    char cUpdateShootSound;
    
	void updateBossTime(float delat);


	bool CanTouch;
	float fTime;
	int m_iFishMoveTime;
	bool bFirst5Lv;
	bool bTwo5Lv;


	Vec2 ShootOverPoint[6];
	Rect ShootQuyu[6];
	//«Ω±⁄≈ˆ◊≤
	void checkOutWall();
	//≈ˆ◊≤ºÏ≤‚œ‡πÿ
	void checkOutCollision();
	void checkOutCollisionBetweenFishesAndBullet();
	void checkOutCollisionBetweenFishesAndFishingNet();  

	Shop * ShopLayer;
	Menu* m_Go;
	void menuGo(Ref* pSender); 

	bool bCanShoot;
	bool bCanShootDanji;
	int m_fUpdateTime; 
	int m_fRobotShootTime;

	int m_fTime;

	int cTouchNum; 
	int m_fUpdateTimeDanJi;
	int m_fTimeDanJi;

	int iXunHuan;

	cocos2d::Point mTouchPos; 

	vector<Sprite* > FishMoney;
	void MoveyMove(int iMoney,char cFishType);
	bool bRed; 
	int MoneyMoveY[7];
	int MoneyMoveUpdate;
};

class QiongShenLayer: public cocos2d::Layer
{
public:
	static Layer*  createScene();

	virtual bool init();

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 
 
	CREATE_FUNC(QiongShenLayer);

private:
 
};
