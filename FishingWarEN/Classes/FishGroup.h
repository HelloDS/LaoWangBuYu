#ifndef __FISH_GROUP__
#define __FISH_GROUP__



#include <vector>
#include "FishLayer.h"
#include "FishScript.h"
using namespace std;
 

const int MAX_SUB_NUM = 31;
 class FishLayer;
 class FishScript;
class FishGroup 	//��Ⱥ������
{
public:
	FishGroup(FishLayer *pFishManage,int iGroupMainID,int iScriptID,int iTarckID,int iNowFrameIndex);
	virtual ~FishGroup(void);

	char m_cSubLiveFlag[MAX_SUB_NUM];//SubID��Ӧ0-31����������Ƕ�Ӧ��SubID�����Ƿ����
	
	bool Update(int iSubFlag = -1,int iFrameVal = 0);//����,�����Ƿ�Ҫ���������Լ������ɵ����Ƿ�Ҫ��֡
	bool IsAllFishCreate(){return m_bAllFishCreate;}
	void Reset(int iGroupMainID,int iScriptID,int iTarckID,int iNowFrameIndex);
    
	void CreateFishForClient(int iNowFrameIndex,int iMultiFishFlag); //�ͻ��˸����յ��ĵ�ǰ��������ָ���켣��

	int m_iGroupMainID;//��ǰ��Ⱥ������m_vcFish�е�ID,��Ⱥ�����е����㶼��ͬһ��m_iMainID,m_iSubID����m_iNowSubFishID
	int m_iFishScriptID;//��ǰ��Ⱥִ�еĽű�ID
	int m_iTrackID;//������Ⱥ���ߵĹ켣ID��Ϊ0�Ļ�ֱ���߽ű�ָ����ID
	int m_iCreateFrame;

	int GetNowFrameIndex(){return m_fishScript.GetNowFrameIndex();}
private:
	FishLayer *m_pFishManage;//���ڻ��FreeFish	
	int m_iNowSubFishID;//��ǰ�����iD,�����ɵ�����iD�ڴ������ӣ����ܳ���MAX_SUB_NUM

	int m_iFishNumInScript;//�ű��ڹ��ж�������
	
	bool m_bAllFishCreate;//�Ƿ�ű������е��㶼�Ѿ�����
	FishScript m_fishScript;//��Ӧ�Ľű���

	

};
 

#endif