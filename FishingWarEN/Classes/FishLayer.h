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

const int g_iFrameTime = 50;//��֡ʱ��
 
class FishGroup;
typedef vector<Fish*> VectorFishBase;
 
typedef vector<FishGroup*> VecFishGroup;
 
#define MAX_FISH	22

const int g_iTollGateRestTime = 8;//������(���) 


typedef struct TollGateInfo 
{
	int      iTollGateBackID; //�����ؿ��ı���ID
	int      iTollGateConTime;//�Լ��ؿ��Ĳ���ʱ��
	int      iNextTollGateID; //�ؿ���������һ���ؿ���ID
	int      iFishRandSwatchID;//���ؿ��������ID
	int      iFishFixedLinupID;//���ؿ��̶�����������ID(������IDΪ0ʱ�ɷ��������,����ָ��ID����)
}TollGateInfoDef;

typedef struct ForbidFish    //��ֹ���ɵ���,�����Լ��ͻ��˻�δ����,�����������ɹ�����ɾ������
{
	int iMainID;
	int iSubID;
}ForbidFishDef;


typedef struct paomadeng    //��ֹ���ɵ���,�����Լ��ͻ��˻�δ����,�����������ɹ�����ɾ������
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

	float timeUpdate;			//֡��

	int GetRandTrack();
	void CreatFishGroupwf(int iScriptID,int iTrackID,int iMainID,int iNowFrameIndex,int iMultiFishFlag,int iCreateFrame);//������Ⱥ

	void JudgeIfNeedCreatSwatchFish(bool bNeedCreate,vcFishInSwatch &vcNeedCreateFish); //�Ƿ���Ҫ����������

	void updataFisDelDingPing(float dt); 
	void updateFishMove(float dt);
	void updateFishlayerBoss(float delat);
	void updateFishlayerPeriod(float dt);
	static int fishlayerPeriod;  //1.�ͷ��� 2.ƽ���� 3.�Է���
	static int ifCatchJnum;
	static Vector <LabelTTF *> catchLabel;
	bool  CheckOutBoard(cocos2d::Point TempPoint);
	 
	bool WfUpdate();//����������״̬ 
	void TollGateUpdate();//���¹ؿ� ��ϫ ��Ϯ������ 
	  
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
	Fish* GroupAddTrackFish(int iFishType,bool bBigFish,int iMainID,int iSubID,int iTrackID,int iNowFrameIndex,int iCreateFrame,Point mMove);//������,CreateSingleFish��CreatFishGroup����ͨ����������������

	Fish* AddTrackFish(Fish *pFish,int iFishType,bool bBigFish,int iMainID,int iSubID,int iTrackID,int iNowFrameIndex,int iCreateFrame);//������,CreateSingleFish��CreatFishGroup����ͨ����������������
	Fish* AddFreeFish(Fish *pFish,int iFishType,int iMainID,int iSubID,int iExistFrames,int iX,int iY,int iSpeed,double dAngleValue,double dAngleSpeed);//����������

	
	FishGroup* CreatFishGroup(int iScriptID,int iTrackID,int iMainID,int iNowFrameIndex = 0,int iGapTime = 0,int iMultiFishFlag = 0);//������Ⱥ,����˵�iGapTime��iNowFrameIndexΪ0,�ͻ���Ҫ����iGapTime��iNowFrameIndex����ȷ��λ��
		

	virtual bool CheckShotReqLegal(int iPos,int iShotType){return true;};//�ж��ӵ������Ƿ�Ϸ���SERVER��Ҫ����
	virtual void CallBackJudgeFishInNetFromClient(int iShotID,int iPos,VectorFishBase vcFishInNet){};//����������,�жϿͻ��˲������
 
	Fish* GetFishInfo(int iMainID,int iSubID);//����iMainID��iSubID��ȡ��Ӧ������Ϣ


	virtual void ShowBlockFishDead(VectorFishBase vcBlockDeadFish,int iPos){};//��ʾһ������
	Fish *ShowDeadFish(int iMainID,int iSubID,int iPos);	//��ʾ����Ч��

	virtual void ShowEnterFishRest(int iTollGateID){};//��ʾ������һ�ؿ�Ч��
	virtual void ShowStartNextTollGateID(int iTollGateID,int iTGNowFrameIndex,int iNowMaxFishID,int iTmGap){};//ֹͣ�ؿ�����Ч��������
 
	//����
	virtual void ShowTaskInfo(int iPos,unsigned char cTaskName,unsigned char cTaskSatus,unsigned int iTaskIndex,unsigned int iTaskReward){};//��������֪ͨ(�ͻ�����)
	virtual void SetLaserBeanInfo(int iPos,int iX,int iY,double dAngleValue){};

	virtual void ClearAllElement(bool bNeedClearTask =true);

	virtual void SetBackGroundID(unsigned char cBackGroundID,bool bFirstSet = false){m_cBackGroundID = cBackGroundID;}
	virtual void PlayShowNetMusic(int iNetType){};//���ų�������
	virtual int GetSelfPos(){return 0;};

	//test
	map<int,unsigned long>m_mapSelfShotTime;
	virtual void CallBackEraseShot(int iPos,int iShotType){}; ///�ͻ��˵���ͳ����Ӯ


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
	VecFishGroup m_vcFishGroup;//��Ⱥ


	unsigned char m_cBackGroundID;//�������
	bool m_bEnterRest;//�Ƿ����������
 
	void JudgeIfNeedEraseFishGroup(int iFishMainID,int iFishSubID); 
	FishGroup* GetFreeFishGroup(int iGroupMainID,int iScriptID,int iTrackID,int iNowFrameIndex);  //ȡ�ÿ�����Ⱥ
 
	unsigned int GetFishMainID();		//��ȡΨһ��MainID����������
	 
	int		m_iNowFrame;		//��ǰ֡�� 
	unsigned int m_iNowMaxFishMainID;	//��ǰ�����ID 
	int    m_iFishFrame;		//�������֡��
	 
protected:
	void addFish(float dt);
	void resetFish(Fish* fish);




	void Reset(); 
	void SetNowTollGateInfo(int iNowTollGateID,int iNowRandSwatchID,int iNowFishLineupID,int iNowFishMaxID = 0,int iNowFrameIndex = 0,int iGapTime = 0);
	void CreateFishForEnterInGame(vector<int>vcMainID,vector<int>vcMultiFishFlag,int iNowFrameIndex,int iTmGap);//��;��������������

	enum TollGateStaus{ NORMAL_STATUS = 1, REST_STATUS }; //�ؿ�״̬,��������״̬,������

	int GetNowTollGateStatus(){return m_iNowTollGateStatus;};
	int GetNowTollGateID(){return m_iNowTollGateID;}
	int GetNowTollGateFrameIndex(){return m_iNowTollGateFrameIndex;}
	int GetNowTollGateFishMaxID(){return m_iNowFishMaxMainID;}
	int GetNowTollGateRandSwatchID(){return m_iNowFishRandSwatchID;}
	int GetNowTollGateFixedLineupID(){return m_iNowFishFixedLineupID;}


	int GetNowTollGateBackID();

	bool JudgeIsForbidFish(int iMainID,int iSubID);
	void AddForbidFish(int iMainID,int iSubID); 
	int GetTollGateLeftTime();//�ؿ�ʣ������

	static void LoadAllTollGateData();//һ�ζ�ȡ���еĽű��ļ���Ϣ
	static int  GetTollGateBackID(int iTollGateID);//ȡ��ָ���ؿ��ı���id
	static int  GetNextTollGateID(int iTollGateID);//ȡ��ָ���ؿ�����һ�ؿ�id
	static int  GetFirstTollGateID();
private:
 
	static map<int,TollGateInfoDef> m_mapTollGate;//���йؿ���Ϣ

	FishRandSwatch m_fishRandSwatch;
	FishLineup m_fishLineUp; 


	int m_iNowTollGateID;//��ǰ�ؿ�ID
	int m_iNowTollGateStatus;//��ǰ�ؿ�״̬
	int m_iNowTollGateFrameIndex;//��ǰ�ؿ����е�����֡
	int m_iNowTollGateMaxFrame;//��ǰ�ؿ��ܹ�����֡
	int m_iNowFishMaxMainID; //�ؿ������id������
	int m_iNowFishRestConFrame;//�Ѿ����벶���ڶ��
	int m_iNowFishRandSwatchID;//�ؿ��������ID
	int m_iNowFishFixedLineupID;//�ؿ��̶�����ID

	vector<ForbidFishDef>m_vcForbidFish;

	bool m_bServerSendRestMsg;//�������Ƿ��͹�������
	void JudgeIfNeedCreatFish(vcFishInSwatch &vcNeedCreateFish,int iFrameIndex);
	Size winSize ;
	Size visibleSize;
 
}; 


#endif /* defined(__FishingJoy__FishLayer__) */
