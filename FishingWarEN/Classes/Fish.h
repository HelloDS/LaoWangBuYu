

#ifndef __FishingJoy__Fish__
#define __FishingJoy__Fish__ 
#include "FishTrack.h"
#include "FishScript.h"
#include "CoinAndAni.h" 

const int FishAniTag = 88; 
const int FishAniTagMove = 89; 
const int FishAniTagRot = 90; 
const int g_iBoardW = 960; 
const int g_iBoardH = 640; 

const double Pi=(180/3.14159265358979); //PI值
//const double Pi=(180/3.14159265358979); //PI值
const int cFishBase[33] = {2,2,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,10,20,30,35,40,80,120,525,520,5,4,9,10,6,12,15};
const int cMatchBase[33] = {2,2,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,10,20,30,35,40,80,120,525,520,5,4,9,10,6,12,15};
const int cAddDimand[33] = {1,
2,
3,
5,
10,
15,
20,
25,
30,
45,
55,
60,
65,
70,
75,
100,
200,
300,
400,
500
};


#include "cocos2d.h"
USING_NS_CC;
typedef enum{
    k_Fish_Type_Red = 0,
    k_Fish_Type_Yellow,
    k_Fish_Type_Count
}FishType; 

#define  FISHSPEED 3
class Fish : public cocos2d::CCNode
{
public:
    static Fish* create(unsigned char type = 0,char cSpc = -1,char cFishNum = 1);
    bool init(unsigned char type = 0,char cSpc = -1,char cFishNum = 1);
    
    CC_SYNTHESIZE_READONLY(cocos2d::Sprite*, _fishSprite, FishSprite);
	CC_SYNTHESIZE_READONLY(cocos2d::Sprite*, _fishSpriteTwo, FishSpriteTwo);
	CC_SYNTHESIZE_READONLY(cocos2d::Sprite*, _fishthree, FishSpriteThree);
	CC_SYNTHESIZE_READONLY(cocos2d::Sprite*, _fishkong, FishSpriteKong);

    Sprite * dFish;
    CC_SYNTHESIZE_READONLY(int, _type, Type); 
	// Animate* fishAnimate;
    Size visibleSize ;
    Size winSize;
	bool bBaoJi; 
	int EndNum;
	int FishNum;
	int iRandomBase; 
	float ShipGailv;
    
	vector<Sprite*> vcSprPoint;
	vector<int> vcRadius;
	Label *ShipNum;
	float m_iShipNum;
	float m_iLeiJiChongZhi;
    void randomFish();
    bool noupdate;
    
    int iHuaFeiNum;
    int iHuaFeiType;
    
    bool bsuperpao;
	cocos2d::CCParticleSystemQuad* quanPar;
	int iShootPos;
	bool bSlow;
    bool bSpc;
    bool bSpcTwo;
    float fRadius;
    
    int m_iTrackID;			//轨迹ID,现在所有鱼都跑轨迹,这个不为0
    FishTrack m_trackFish;	//鱼的轨迹信息
    int m_iMainID;			//主ID标识,鱼群内的子鱼公用该MainID
    int m_iSubID;		   //子ID标识,为0表示单鱼,1-31表示是鱼群内的子鱼
    float m_fUpdateTime;
    float m_fTime;
    //45是采金船 46是花费卷
    int m_iFishType;		//鱼类型(何种鱼)
    float m_iX;				//X坐标位置，图片中心点
    float m_iY;				//Y坐标位置，图片中心点
    
    int iChiFen;
    int m_iSpeed;			    //鱼的运动速度，每100ms多少在方向上的位移，这两个值现在只用于鱼死亡时
    Point mMovePos;
    char cFishBossTime;
    Label *LabelFishNum;
    Vector<CoinAndAni*> m_CoinAndAni;
    
    
    
    bool bDead;
    bool bPanziDeadFish;
    int iPanziType;
    char BossType;
    int m_iShipIndex;
    int m_iShipMax;
    int m_iSpacTime;
    int iRoomType;
    
    
    bool CheckRadius(Point BulletPos,float iBulletRadius);
    void CanMove();
	Point getCollisionPoint();
    //播放被捕捉的动画
    bool beCaught(bool bShow ,char cBeiShu,bool bSpcDead = false,bool bSuperPao= false,char cPos = 4,bool bNew = false);  
	bool ifCatchJ(int iPos,float PaoBase = 0,bool bNew = false);
    void NetShan(bool bVip = false);
	bool CreateTrackFish(Fish* pFish,int iFishType,bool boss = false,int spc= 0);
	bool SetGroupFishInfo(int iMainID,int iSubID,int iFishType,int iTrackID,bool bBigFish , Point pPoint, int iNowTrackIndex = -1);//设定自由鱼信息
	bool SetFishInfo(int iMainID,int iSubID,int iFishType,int iTrackID,bool bBigFish, int iNowTrackIndex = -1);//设定轨迹鱼信息,返回是否有对应轨迹
	void Reset(int iFishType);
    
	void UpdateFishwf(float delat);
	 void MoveOver1();
     void AddCoin(Point Pos,char cFishType,char cShootPos,bool bBoss = false);
     void AddCoinToVector(Point Pos ,char cYinNum, char cJinNum,char cShootPos,bool bBoss = false);


 	 void FishTeXiaoOver(float delat);
	 void  FishBeginTexiao(float delat);
	 void ShowBigFishFrame(int num);
	 void BossDead(int iNum);
     void beCaught_CallFunc();
 


};



const float cMatchRoomGailv[4][33] = {{
    48.44,
    48.44,
    48.44,
    48.44,
    32.293,
    32.293,
    24.22,
    24.22,
    19.376,
    19.376,
    16.146,
    16.146,
    13.84,
    13.84,
    12.11,
    12.11,
    10.764,
    9.688,
    4.844,
    3.229,
    2.768,
    2.422,
    1.211,
    0.807,
    0.30,
    0.15,
    9.688,
    13.84,
    3.588,
    3.229,
    5.382,
    2.018,
    1.291},
    { 48.44,
        48.44,
        48.44,
        48.44,
        32.293,
        32.293,
        24.22,
        24.22,
        19.376,
        19.376,
        16.146,
        16.146,
        13.84,
        13.84,
        12.11,
        12.11,
        10.764,
        9.688,
        4.844,
        3.229,
        2.768,
        2.422,
        1.211,
        0.807,
        0.30,
        0.15,
        9.688,
        13.84,
        3.588,
        3.229,
        5.382,
        2.018,
        1.291},
{
    48.44,
    48.44,
    48.44,
    48.44,
    32.293,
    32.293,
    24.22,
    24.22,
    19.376,
    19.376,
    16.146,
    16.146,
    13.84,
    13.84,
    12.11,
    12.11,
    10.764,
    9.688,
    4.844,
    3.229,
    2.768,
    2.422,
    1.211,
    0.807,
    0.30,
    0.15,
    9.688,
    13.84,
    3.588,
    3.229,
    5.382,
    2.018,
    1.291},{48.44,
        48.44,
        48.44,
        48.44,
        32.293,
        32.293,
        24.22,
        24.22,
        19.376,
        19.376,
        16.146,
        16.146,
        13.84,
        13.84,
        12.11,
        12.11,
        10.764,
        9.688,
        4.844,
        3.229,
        2.768,
        2.422,
        1.211,
        0.807,
        0.30,
        0.15,
        9.688,
        13.84,
        3.588,
        3.229,
        5.382,
        2.018,
        1.291}};





		const float cTeShuPuTong[3][15] = {{50.450,
			50.450,
			33.633,
			25.225,
			20.180,
			16.817,
			14.414,
			14.414,
			16.817,
			14.414,
			12.613,
			12.613,
			11.211,
			11.211,
			10.090},
		{

			50.250,
				50.250,
				33.500,
				25.125,
				20.100,
				16.750,
				14.357,
				14.357,
				16.750,
				14.357,
				12.563,
				12.563,
				11.167,
				11.167,
				10.050

		},
		{

			50.000,
				50.000,
				33.333,
				25.000,
				20.000,
				16.583,
				14.214,
				14.214,
				16.583,
				14.214,
				12.438,
				12.438,
				11.056,
				11.056,
				9.950,
			}
		};



		const float cTeShuBiSai[3][18] = {{
			50.450,
				50.450,
				50.450,
				50.450,
				33.633,
				33.633,
				25.225,
				25.225,
				20.180,
				20.180,
				16.817,
				16.817,
				14.414,
				14.414,
				12.613,
				12.613,
				11.211,
				10.090},
		{



			50.250,
				50.250,
				50.250,
				50.250,
				33.500,
				33.500,
				25.125,
				25.125,
				20.100,
				20.100,
				16.750,
				16.750,
				14.357,
				14.357,
				12.563,
				12.563,
				11.167,
				10.050


		},
		{


			50.000,
				50.000,
				50.000,
				50.000,
				33.333,
				33.333,
				25.000,
				25.000,
				20.000,
				20.000,
				16.583,
				16.583,
				14.214,
				14.214,
				12.438,
				12.438,
				11.056,
				9.950
			}
		};


const float cFishGailv[3][33] = {
    {
        51.500,
        51.500,
        51.500,
        51.500,
        34.333,
        34.333,
        25.750,
        25.750,
        20.600,
        20.600,
        17.167,
        17.167,
        14.714,
        14.714,
        12.875,
        12.875,
        11.444,
        10.300,
        5.150,
        3.433,
        2.943,
        2.575,
        1.288,
        0.858,
        0.300,
        0.150,
        9.688,
        13.84,
        3.588,
        3.229,
        5.382,
        2.018,
        1.291
    },
    {
        
        
        
        48.500,
        48.500,
        48.500,
        48.500,
        32.333,
        32.333,
        24.250,
        24.250,
        19.400,
        19.400,
        16.167,
        16.167,
        13.857,
        13.857,
        12.125,
        12.125,
        10.778,
        9.700,
        4.850,
        3.233,
        2.771,
        2.425,
        1.213,
        0.808,
        0.300,
        0.150,
        9.688,
        13.84,
        3.588,
        3.229,
        5.382,
        2.018,
        1.291
        
    },
    {
        
        47.500,
        47.500,
        47.500,
        47.500,
        31.667,
        31.667,
        23.750,
        23.750,
        19.000,
        19.000,
        15.833,
        15.833,
        13.571,
        13.571,
        11.875,
        11.875,
        10.556,
        9.500,
        4.750,
        3.167,
        2.714,
        2.375,
        1.188,
        0.792,
        0.300,
        0.150,
        9.688,
        13.84,
        3.588,
        3.229,
        5.382,
        2.018,
        1.291
    }
};
const float JiuJiSai[33] =
{
    55.000,
    55.000,
    55.000,
    55.000,
    36.667,
    36.667,
    27.500,
    27.500,
    22.000,
    22.000,
    18.333,
    18.333,
    15.714,
    15.714,
    13.750,
    13.750,
    12.222,
    11.000,
    5.050,
    3.367,
    2.886,
    2.525,
    1.211,
    0.807,
    0.300,
    0.150,
    10.100,
    14.429,
    3.741,
    3.367,
    5.611,
    2.104,
    1.347
};

#endif /* defined(__FishingJoy__Fish__) */
