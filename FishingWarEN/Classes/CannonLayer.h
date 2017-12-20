 

#ifndef __FishingJoy__CannonLayer__
#define __FishingJoy__CannonLayer__
#include "cocos2d.h"
#include "Weapon.h" 
#include "GameData.h"
#include "TiShi.h" 
 

USING_NS_CC; 
 
const int  iJingYanDengJi[50] = {0,100,200,400,1000,4000,6000,8000,10000,30000,
	42420,56160,71940,90480,112500,138720,169860,206640,300000,600000,
	716040,849120,1000680,1172160,1365000,1580640,1820520,2086080,2378760,2700000,
	3051240,3433920,3849480,4299360,4785000,5307840,5869320,6470880,7113960,7800000,
	8530440,9306720,10130280,11002560,18000000,31498400,51498400,121498400,241498400,1207492000};

const int robot_add_money[4][3][7] = {   //比赛模式 0-3、机器人智商0-2、商城随机的概率 0-6
	{{70,100,100},				{0,100,100},			{100,0}			},
	{{50,90,100,0},			{0,60,90,100,0},		{90,100,0}		},
	{{0,0,0,30,90,100,0},	{0,0,0,20,65,95,100},	{0,0,0,100,0}	},
	{{0,0,0,30,90,100,0},	{0,0,0,20,65,95,100},	{0,0,0,100,0}	}
};


const int robot_add_money_kind[7] = {120000,330000,620000,820000,1280000,1550000,3350000};
 
class CannonLayer : public cocos2d::Layer
{
public: 


    CREATE_FUNC(CannonLayer);
    bool init();
    CC_SYNTHESIZE_READONLY(Weapon*, m_Weapon, Weapon); 
    
    void jieping(float dt);
    bool shootTo(cocos2d::Point touchLocation);
	bool RobotshootTo(cocos2d::Point touchLocation,char cRobotPos);
	void afterCaptured(bool succeed, const std::string& outputFile);

    void aimAt(cocos2d::Point target);  


	void aimAtRobot(cocos2d::Point target,char cRobotType); 
		
	bool bChangeRobotBaseIfOver[4];

	char cRobotType[4]; 
	Vec2 SelfPaoPos;
	static int _type;
	CC_SYNTHESIZE_READONLY(Cannon*, m_Cannon, Cannon);
	Cannon * m_CannonRobot[4];
	Size winSize;
	Size visibleSize;
	Point origin;
	static int cBeiShu[20];
	static int iFanWeiCoin[5];
	static int iJiGuangCoin[5];
	int iFanWeicd[5];
	int iJiGuangcd[5];
	int iFanWeiShootcd[5];
	int iJiGuangShootcd[5];
	int iFanWeiNum[5];
	int iFanWeiZuanShi[5];
	int iJiGuangZuanShi[5];

	float angle;
	int CannonBeiShu;  
 
  //  bool bFanHuiDating;
	static int  GameExp; 
	static int  GameLv; 

	Sprite * JieSuoPao;
 
	static bool bShowJieSuoXiaoShi;
	static bool bShowJieSuo;	
	static bool bLvUp;
	static int iLvMoney;
	static int iLvZuan;
	void ToMax();
	static bool bToMax; 

	LabelTTF* label ;
	 
	static bool bFirstChoose;
    
    bool bCheckHuaFeiUpdate;
    char cAddHuaFeiType;
    static char cYanZhengHuaFei;
  
    
	void changeRobotBase(char cPos);
	void changeRobotEx(char cPos,bool bEx,char choosetype);
	bool bShowWuQiTiShi;
	int iShowTiShiNum;
	static void GameCoinRefresh(int iNum,bool bExp = true,bool bJiangchiFen = false,char cPos = 4);
	static void GameCoinZuanshi(int iNum); 
	static void GameExpRefresh(int iNum);
	static Label *GameCoinLabel[5];
	static int RobotMoney[4];

	static Label *GameZuanshiLabel;
	static Label *GameExpLabel;
	static Sprite * GameChenghao;
	static Sprite * jingyanTiao;
	static Sprite * fanweifontLv;
	static Sprite * jiguangfontLv;
	static Sprite * pro1;
	static char cConinNum[14];
	static char cZuanShiNum[14];
	 
	static Label *CountDingPing;
	static Label *CountJiaSu;
	static Label *CountFanWei; 
	static Label *CountJiGuang;
	static Label *CountVipPao;

	//初始化机器人
	void initRobot(int i,bool isSelf);
	static float robotPos1;
	static float robotPos2;
/*
	static Label *NowGaiLv;

	static Label *BossJiangChiwf;
	static Label *JiangChiwf;
	static Label *JiangChiSend;
	static Label *JiangChiGet;
	*/
	//Label * SendFengTTf; 

	void AddRobot(char cPos);

	static bool bShowLiBao; 

	TiShi * TishiBulletMore;
	TiShi * TishiJieSuo;
	Label *LableJieSuoOne; 
	Label *LableJieSuoTwo;
	Label *LableJieSuoThree;

	Label* wordTTF;
	Label* wordTTF1;
	Sprite * dianjijiesuo;
    Sprite* mDiamondIcon;

	char cJiGuangXiaoHao[20];
	Label *LableJiGuangXiaoHao;
	  

	
	static bool isToMaxFlag;

	bool bLock;

	static bool bupdateJiesuo; 
	static int cNowMaxPao;

	static void updateDapao();
	void updateCannonLayer(float delta);

	static int iSoundId;
	static int typeFanWei;
	static int typeJiGuang;
	char cRobotTypeFanWei[4];
	char cRobotTypeJiGuang[4];
	 
	  
	static bool bxinShouFanWei;
	void updateJineng(float dt);
	int jineng_time_cd ;

		//比赛结束动画
	void Match_meirenyu();
	void Match_cup(int i); //i 1.2.3 名的动画
	void Match_rank(); //i 排名奖的动画
	void Match_xuanyao();  //炫耀
	void Match_exit();   //退出
	void ShowMatchOver(); 
	void MatchoverAni();
	int iRank;
	int MatchOverZuanShi;
	int MatchOverMoney;
    int MatchOverhuafeiquan;
    
    static char zuanpanover;
    static int iMoneyJiangchi;
    char czuanpanupdate;
    void jinruzuanpan();
    void tishizuanpan();
    
    
    
	void baoming_vip(Ref* pSender);

	static int xinshoutimefanwei;
	static int xinshoutimejiguang;
	bool bPoChan[4];
protected: 
    //切换炮台
    void switchCannon(cocos2d::Ref* sender);
    cocos2d::MenuItemSprite* m_SubItem;
	cocos2d::MenuItemSprite* m_AddItem;

	cocos2d::Menu* m_MinItemmenu;
	cocos2d::Menu* m_MaxItemmenu;
	cocos2d::Menu* m_JieSuomenu;
	cocos2d::Menu* m_JieSuoKuang;
	cocos2d::Sprite * m_MinItem;
	cocos2d::Sprite * m_MaxItem;
	cocos2d::Sprite * m_JieSuo; 
	 
	void hall_shangcheng_func(Ref* pSender);					//商城
	
	void menuMax(cocos2d::Ref* pSender);
	void menuMin(cocos2d::Ref* pSender);
	void menuJieSuo(cocos2d::Ref* pSender);

	void menuMoveOver();
	void menuMoveOverTwo();
	void menuMoveTrue(); 
	void menuMoveTrueTwo(); 

	Sprite * jiasu_Gs ;
	Sprite * dingping_Gs  ;
	Sprite * jiguang_Gs ;
	Sprite * fanwei_Gs ;
	Sprite * vippao_Gs ;

/*	Label* naocannum;
	char cNoNum;
	char cJiGuangNum;*/	

	bool bpaoTeXiao;
	Sprite* paoTexiaoSpr; 
	float m_fUpdateTime;
	float m_fTime; 

	Point menuPoint[3];
	Point menuPointTwo[2];
	void MoveOutOne();
	void MoveOutTwo();
	void MoveInOne();
	void MoveInTwo();
	Point menuPointBegin;

	bool bjiaSu;
	ProgressTimer *bjiaSupt;
	float m_fUpdateTimejiasu;
	float m_fTimejiasu; 
	float m_fjiaSucdnum;
	Menu * m_JiaSumenu;
	void menuJiasu(Ref* pSender);
 
	ProgressTimer *bDingpingpt;
	float m_fUpdateTimeDingping; 
	float m_fDingpingnum;
	Menu * m_Dingpingmenu;
	void menuDingping(Ref* pSender);
 

	bool bFanWeiRobotShoot[4];
	bool bJiGuangRobotShoot[4];
	bool bVipShoot[4];
	static bool bFanWeiShoot;
	bool bFanWei;
	ProgressTimer *bFanWeipt; 
	float m_fUpdateTimeFanWei;
	float m_fUpdateTimeShootFanWei;
	float m_fTimeFanWei;
	float m_fTimeFanWeiShoot;
	float m_fFanWeiNum;
	float m_fFanWeiShootNum;
	Menu * m_FanWeimenu;
	MenuItemSprite * FanWeiitem;
	void menuFanWei(Ref* pSender);
	static bool bFanweiyindao;


	MenuItemSprite * VipPaoIitem;
	Menu * m_VipPaomenu;
	ProgressTimer *bVipPaopt; 
	bool bVipPao;
	float m_fTimeVipPao;
	float m_fUpdateTimeVipPao;
	float m_fVipPaoNum;
	static bool bVipPaoShoot;
	float m_fShoot;
	float m_fTimeVipPaoShoot;
	float m_fUpdateTimeShootVipPao;
	float m_fVipPaoShootNum; 
	void menuVipPao(Ref* pSender);

	int m_iSelfVip;
	void AddRobotMoney(float dt);
	Sprite *PoChanSpr[4];

	LayerColor *zzLayer; 
	static bool bJiGuangShoot;
	bool bJiGuang;
	ProgressTimer *bJiGuangpt; 
	float m_fUpdateTimeJiGuang;
	float m_fUpdateTimeJiGuangShoot;
	float m_fTimeJiGuang;
	float m_fTimeJiGuangShoot;
	float m_fJiGuangNum;
	float m_fJiGuangShootNum;
	Menu *m_JiGuangmenu;
	MenuItemSprite * JiGuangitem;
	void menuJiGuang(Ref * pSender);  
	static bool bJiGuangyindao;
	 
	
	void callMoveOverFanWei(); 
	void callMoveOverJiGuang(); 
	static bool bCanJieSuo;
	void ShowGuangAni(char cPos,bool biSaiSelf);

	cocos2d::Point ShootPos;
	cocos2d::Menu* m_jiaSumenu; 
	bool bjiaSushoot;
	char cShootNum;
	float m_frameUpdate;
	float m_frameTime; 
	 
};  
#endif /* defined(__FishingJoy__Cannon__) */
