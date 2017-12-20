#ifndef __FISH_TRACK__
#define __FISH_TRACK__

#include <vector>
#include <map>
#include "cocos2d.h"
using namespace std;
USING_NS_CC;
const int BigTrackIndex[44] = {4000,4001,4002,4003,4004,4005,4006,4007,4008,4009,4010,4011,4012,4013,4014,4015,4016,4017,4018,4019,4020,4021,
	4500,4501,4502,4503,4504,4505,4506,4507,4508,4509,4510,4511,4512,4513,4514,4515,4516,4517,4518,4519,4520,4521};

const int SmallTrackIndex[75] = {1000,1001,1003,1004,1005,1008,1010,1013,1014,1015,1016,1017,1018,1019,1020,1500,1502,1503,1504,1505,1506,1507,1508,
	2000,2001,2002,2003,2004,2005,2007,2010,2015,2016,2017,2022,2500,2501,2502,2503,3000,3001,3002,3003,3004,3005,3006,3007,3008,3009,3010,3011,3012,
	3013,3014,3015,3016,3017,3500,3501,3502,3503,3504,3505,3506,3507,3508,3509,3510,3511,3512,3513,3514,3515,3516,3517};

const int TaskTrackIndex[16] = {7000,7001,7002,7003,7004,7005,7006,7007,7500,7501,7502,7503,7504,7505,7506,7507};
/*
const int BigTrackIndex[51] = {10001,10002,10003,10004,10005,10011,10012,10013,10014,10015,10016,
	10110,20000,30008,30009,30010,30011,30012,30013,30014,30015,30016,30017,30018,30019,30020,30021,30022,30023,
	30050,30051,30052,30053,30054,30055,30056,40000,50001,50002,50003,50004,50005,50011,50012,50013,50014,50015,50016,
	50027,50110,51001};

const int SmallTrackIndex[151] = {101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,
	1001,1002,1003,1004,1005,1006,1007,1008,1009,1010,1011,1012,1013,1014,1015,1016,1017,1018,1019,1020,1021,1022,1023,1024,1025,1026,1027,1028,1029,1030,
	2001,2002,2003,2004,2005,2006,2007,2008,2009,2010,2011,
	3001,3002,3003,3004,3005,3006,3007,3008,3009,3010,
	4001,4002,4003,4004,4005,4006,4007,
	11101,11102,11103,11104,11105,11106,11107,11108,11109,11110,11111,11112,11113,11114,11115,
	20000,20001,20002,
	30000,30001,30002,30003,30004,30005,30006,30007,30013,30014,30015,30016,30017,30018,30020,30021,30022,30023,30051,30053,30054,30055,30056,30057,30058,30059,30060,30061,30062,30063,30064,30065,30066,30067,
	50027,50028,50029,50030,
	51001,51002,51003,51004,51005,51006,51007,51008,51009,51010,
	52001,52002,52003,52004,52005,52006,52007,52008,52009,
	53001,53002,53003};
const int TaskTrackIndex[8] = {10006,10007,10008,10009,50006,50007,50008,50009};*/
typedef struct TrackPoint
{ 
	cocos2d::Point	mPoint;
	double	dAngleValue;	//�Ƕ�
	int		iSpeFrame;		//-2,������-1�����ű���֡��>=0����ָ��֡
}TrackPointDef;

struct  VectorTrackInfo
{
	vector<int>				vFishType;
	vector<TrackPointDef>	vTrackPoint;
};

//typedef vector<TrackPointDef> VectorTrackPoint;

class FishTrack	//��Ĺ켣�˶���Ϣ������ܶ��TrackPointDef�켣��
{
public:
	FishTrack(int iTrackID = 0, bool bBigFish = true);
	~FishTrack(void);

	TrackPointDef* GetNextTrackPoint(bool bIni = false);	//��ȡ��һ���켣�㣬��ʼ����õ�һ�����ʱ��Ҫ���ݲ�����������ΪҪ���ǿͻ����յ�����������������Ϣ��ʼ����ʱ�����Ҫ�õ�
	
 

	int GetNowTrackIndex(){return m_iNowTrackIndex;}		

	int GetTrackID(){return m_iTrackID;}

	int GetTrackPointSize();

	void Reset(int iTrackID, bool bBigFish, int iNowTrackIndex = -1);		//���ö���

	static void LoadAllTrackData();							//һ���Լ������й켣�ļ���Ϣ

	enum TrackType{TRACK_UNKNOW = 0,TRACK_BIG,TRACK_SMALL,TRACK_SPECIAL,TRACK_MONSTER,TRACK_GRAMPUS};
	//static int  CreatNewTrackID();
	static int  GetNowTackNum(){return m_mapVcBigTrackPoint.size();}
	static bool GetTrackInfoByID(int iTrackID,bool bBigFish,VectorTrackInfo &vecInfo);
	
	static void GetTrackIDByFishType(int iFishType, vector<int> &vTrackID);//ȡ��ָ����������й켣
	static int GetTrackIDByFishTaskType(int iFishType);//ȡ��ָ����������й켣
	static void GetAllTrackIDByFishType(int iFishType, int iTrackType, vector<int> &vTrackID);//ȡ��ָ��������й켣
	static int  GetRandTrackID(int iFishType);//���ָ������Ĺ켣,����-1Ϊ����û�ж�Ӧ�켣

	static int  GetRandGroupFishTrackID(vector<int> vcLimitTrackIDD); //���ȡ��һ����Ⱥ�켣ID ��SmallTrackID

	static int GetRandMonsterTrackID();//���һ�����ֹ켣
	static int GetRandGrampusTrackID();//���һ�������켣

	static vector<int> m_vcTrackID;
	static vector<int> m_vcSmallTrackID;
	static vector<int> m_vcSpeTrackID;
	static vector<int> m_vcMonsterTrackID;//���ֹ켣
	static vector<int> m_vcGrampusTrackID;//�����켣

	//VectorTrackInfo initTrackVec(int trackID,string kindPage);//ͨ��.dat�ļ���VectorTrackInfo��ʼ��
	static void initMap(string kindPage); 
	bool bFanZhuan;

private:
	static map<int,VectorTrackInfo> m_mapVcSpeTrackPoint;//������map���������ƶ�ά�����ˣ���̬��һ���Լ������й켣��Ϣ����Ϊ���涼��ֻ���Ķ��̲߳�����������Ҫ�����̳߳�ͻ��
	static map<int,VectorTrackInfo> m_mapVcBigTrackPoint;//������map���������ƶ�ά�����ˣ���̬��һ���Լ������й켣��Ϣ����Ϊ���涼��ֻ���Ķ��̲߳�����������Ҫ�����̳߳�ͻ��
	static map<int,VectorTrackInfo> m_mapVcSmallTrackPoint;//������map���������ƶ�ά�����ˣ���̬��һ���Լ������й켣��Ϣ����Ϊ���涼��ֻ���Ķ��̲߳�����������Ҫ�����̳߳�ͻ��
	static map<int,VectorTrackInfo> m_mapVcMonsterTrackPoint;//������map���������ƶ�ά�����ˣ���̬��һ���Լ������й켣��Ϣ����Ϊ���涼��ֻ���Ķ��̲߳�����������Ҫ�����̳߳�ͻ��
	static map<int,VectorTrackInfo> m_mapVcGrampusTrackPoint;//������map���������ƶ�ά�����ˣ���̬��һ���Լ������й켣��Ϣ����Ϊ���涼��ֻ���Ķ��̲߳�����������Ҫ�����̳߳�ͻ��
	int m_iNowTrackIndex;
	int m_iTrackID;
	bool m_bBigFish;
		TrackType m_trackType;
};



#endif