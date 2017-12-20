#ifndef __FishingJoy__FishLayer__
#define __FishingJoy__FishLayer__
#include "cocos2d.h"
#include "Fish.h"
#include <vector>
#include <map>
using namespace std;
USING_NS_CC;
#include <vector>
#include <map>
#include "FishScript.h"
#include "FishRandSwatch.h"
#include "FishLineup.h" 
#include "FishingNet.h" 
#include "FishGroup.h" 
#include "LogoLayer.h"

const int g_iFrameTime = 50;//单帧时间
 
class FishGroup;
typedef vector<Fish*> VectorFishBase;
 
typedef vector<FishGroup*> VecFishGroup;
 
#define MAX_FISH	22

const int g_iTollGateRestTime = 8;//休渔期(秒计) 


typedef struct TollGateInfo 
{
	int      iTollGateBackID; //包括关卡的背景ID
	int      iTollGateConTime;//以及关卡的播放时间
	int      iNextTollGateID; //关卡结束后下一个关卡的ID
	int      iFishRandSwatchID;//本关卡随机样本ID
	int      iFishFixedLinupID;//本关卡固定阵型鱼样本ID(这两个ID为0时由服务器随机,否则按指定ID运行)
}TollGateInfoDef;

typedef struct ForbidFish    //禁止生成的鱼,例如自己客户端还未生成,服务器已生成过并被删除的鱼
{
	int iMainID;
	int iSubID;
}ForbidFishDef;


typedef struct paomadeng    //禁止生成的鱼,例如自己客户端还未生成,服务器已生成过并被删除的鱼
{
    int ShowTime;
    int Type;
};


class FishLayer : public Layer
{
public:
    CREATE_FUNC(FishLayer);
    bool init();
  /*  CC_SYNTHESIZE_READONLY(cocos2d::Vector<Fish*>, m_Fishes, Fishes);
	CC_SYNTHESIZE_READONLY(cocos2d::Vector<FishingNet*>, m_FishingNet, FishingNet); 
	*/
  
	vector<Fish*> m_Fishes;
	vector<FishingNet*> m_FishingNet; 
  
	void addNet(char cBulletTypes,Point pos,char buletBeiShu,char cPos);
 

    static bool Fishnodown;
    void ClearNet();
    void RemoveAllFish();
    ~FishLayer(); 

    
    
    int  cBossThree[4];
    int iBossTime[4];
    
    int iRandomPanZi[5];
    int iRandomTime[5];
    void SetRandom();
    
    vector<paomadeng> paomadengwf;
    
    static bool bBulletShan;
	Fish* ShootFish[4];

	float timeUpdate;			//帧率

	int GetRandTrack();
	void CreatFishGroupwf(int iScriptID,int iTrackID,int iMainID,int iNowFrameIndex,int iMultiFishFlag,int iCreateFrame);//生成鱼群

	void JudgeIfNeedCreatSwatchFish(bool bNeedCreate,vcFishInSwatch &vcNeedCreateFish); //是否需要生成样本鱼

	void updataFisDelDingPing(float dt); 
	void updateFishMove(float dt);
	void updateFishlayerBoss(float delat);
	void updateFishlayerPeriod(float dt);
	static int fishlayerPeriod;  //1.送分期 2.平常期 3.吃分期
	static int ifCatchJnum;
	static Vector <LabelTTF *> catchLabel;
	bool  CheckOutBoard(cocos2d::Point TempPoint);
	 
	bool WfUpdate();//更新所有鱼状态 
	void TollGateUpdate();//更新关卡 潮汐 来袭休渔期 
	  
	float m_fUpdateTime; 
	int m_iFishMoveTime;

	int UpdateGroupTime;
	static int iBossChiFen;

	char cRandGroupTime;
	Label * FishNumFontBoss; 
	Sprite * SmallBossFont; 
	Sprite * BigBossFont;
    Sprite * BossBgGuang;
 
	static char cAddFishNum;
	bool bNetChoose; 
	int bosstype;
	float m_fUpdateTimeGroup;
	float m_fTimeGroup;

	float m_fUpdateFish;
	float m_fTimeFish;

	 int m_fUpdateFishBoss; 
	static int m_fUpdateFishYuZheng; 
	int m_fUpdateSmallBoss; 

	bool bFirstYuZhen;
	static bool bYuZheng;
	static bool bMoveFast;
	Fish* GroupAddTrackFish(int iFishType,bool bBigFish,int iMainID,int iSubID,int iTrackID,int iNowFrameIndex,int iCreateFrame,Point mMove);//增加鱼,CreateSingleFish和CreatFishGroup都是通过这个函数增加鱼的

	Fish* AddTrackFish(Fish *pFish,int iFishType,bool bBigFish,int iMainID,int iSubID,int iTrackID,int iNowFrameIndex,int iCreateFrame);//增加鱼,CreateSingleFish和CreatFishGroup都是通过这个函数增加鱼的
	Fish* AddFreeFish(Fish *pFish,int iFishType,int iMainID,int iSubID,int iExistFrames,int iX,int iY,int iSpeed,double dAngleValue,double dAngleSpeed);//增加自由鱼

	
	FishGroup* CreatFishGroup(int iScriptID,int iTrackID,int iMainID,int iNowFrameIndex = 0,int iGapTime = 0,int iMultiFishFlag = 0);//生成鱼群,服务端的iGapTime和iNowFrameIndex为0,客户端要根据iGapTime和iNowFrameIndex重新确定位置
		

	virtual bool CheckShotReqLegal(int iPos,int iShotType){return true;};//判断子弹请求是否合法，SERVER需要重载
	virtual void CallBackJudgeFishInNetFromClient(int iShotID,int iPos,VectorFishBase vcFishInNet){};//服务器调用,判断客户端捕获的鱼
 
	Fish* GetFishInfo(int iMainID,int iSubID);//根据iMainID和iSubID获取对应的鱼信息


	virtual void ShowBlockFishDead(VectorFishBase vcBlockDeadFish,int iPos){};//显示一批鱼死
	Fish *ShowDeadFish(int iMainID,int iSubID,int iPos);	//显示死鱼效果

	virtual void ShowEnterFishRest(int iTollGateID){};//显示进入下一关卡效果
	virtual void ShowStartNextTollGateID(int iTollGateID,int iTGNowFrameIndex,int iNowMaxFishID,int iTmGap){};//停止关卡播放效果，出鱼
 
	//任务
	virtual void ShowTaskInfo(int iPos,unsigned char cTaskName,unsigned char cTaskSatus,unsigned int iTaskIndex,unsigned int iTaskReward){};//处理任务通知(客户端用)
	virtual void SetLaserBeanInfo(int iPos,int iX,int iY,double dAngleValue){};

	virtual void ClearAllElement(bool bNeedClearTask =true);

	virtual void SetBackGroundID(unsigned char cBackGroundID,bool bFirstSet = false){m_cBackGroundID = cBackGroundID;}
	virtual void PlayShowNetMusic(int iNetType){};//播放出网声音
	virtual int GetSelfPos(){return 0;};

	//test
	map<int,unsigned long>m_mapSelfShotTime;
	virtual void CallBackEraseShot(int iPos,int iShotType){}; ///客户端调用统计输赢


	void GetNowNewFishType(vector<int>&vcNewFishType,char cFishType); 
	void PlayUpdate();
	void PlayFishUpdate();
	FishRandSwatch  *m_pFishRandSwatch; 

	static bool bDingping;
	
	static char cNewBoss;

	static bool bFirstBaoXiang;
	char cNowBoss;

	Sprite * sprBossFish;
protected: 
	Sprite * YuChao; 
	VecFishGroup m_vcFishGroup;//鱼群


	unsigned char m_cBackGroundID;//背景编号
	bool m_bEnterRest;//是否进入休鱼期
 
	void JudgeIfNeedEraseFishGroup(int iFishMainID,int iFishSubID); 
	FishGroup* GetFreeFishGroup(int iGroupMainID,int iScriptID,int iTrackID,int iNowFrameIndex);  //取得空闲鱼群
 
	unsigned int GetFishMainID();		//获取唯一的MainID，服务器用
	 
	int		m_iNowFrame;		//当前帧数 
	unsigned int m_iNowMaxFishMainID;	//当前最大鱼ID 
	int    m_iFishFrame;		//产生鱼的帧数
	 
protected:
	void addFish(float dt);
	void resetFish(Fish* fish);




	void Reset(); 
	void SetNowTollGateInfo(int iNowTollGateID,int iNowRandSwatchID,int iNowFishLineupID,int iNowFishMaxID = 0,int iNowFrameIndex = 0,int iGapTime = 0);
	void CreateFishForEnterInGame(vector<int>vcMainID,vector<int>vcMultiFishFlag,int iNowFrameIndex,int iTmGap);//中途进入的玩家生成鱼

	enum TollGateStaus{ NORMAL_STATUS = 1, REST_STATUS }; //关卡状态,正常出鱼状态,休渔期

	int GetNowTollGateStatus(){return m_iNowTollGateStatus;};
	int GetNowTollGateID(){return m_iNowTollGateID;}
	int GetNowTollGateFrameIndex(){return m_iNowTollGateFrameIndex;}
	int GetNowTollGateFishMaxID(){return m_iNowFishMaxMainID;}
	int GetNowTollGateRandSwatchID(){return m_iNowFishRandSwatchID;}
	int GetNowTollGateFixedLineupID(){return m_iNowFishFixedLineupID;}


	int GetNowTollGateBackID();

	bool JudgeIsForbidFish(int iMainID,int iSubID);
	void AddForbidFish(int iMainID,int iSubID); 
	int GetTollGateLeftTime();//关卡剩余秒数

	static void LoadAllTollGateData();//一次读取所有的脚本文件信息
	static int  GetTollGateBackID(int iTollGateID);//取得指定关卡的背景id
	static int  GetNextTollGateID(int iTollGateID);//取得指定关卡的下一关卡id
	static int  GetFirstTollGateID();
private:
 
	static map<int,TollGateInfoDef> m_mapTollGate;//所有关卡信息

	FishRandSwatch m_fishRandSwatch;
	FishLineup m_fishLineUp; 


	int m_iNowTollGateID;//当前关卡ID
	int m_iNowTollGateStatus;//当前关卡状态
	int m_iNowTollGateFrameIndex;//当前关卡运行到多少帧
	int m_iNowTollGateMaxFrame;//当前关卡总共多少帧
	int m_iNowFishMaxMainID; //关卡内鱼的id，递增
	int m_iNowFishRestConFrame;//已经进入捕鱼期多久
	int m_iNowFishRandSwatchID;//关卡随机样本ID
	int m_iNowFishFixedLineupID;//关卡固定阵型ID

	vector<ForbidFishDef>m_vcForbidFish;

	bool m_bServerSendRestMsg;//服务器是否发送过休渔期
	void JudgeIfNeedCreatFish(vcFishInSwatch &vcNeedCreateFish,int iFrameIndex);
	Size winSize ;
	Size visibleSize;
 
}; 


#endif /* defined(__FishingJoy__FishLayer__) */
