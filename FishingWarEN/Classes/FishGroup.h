#ifndef __FISH_GROUP__
#define __FISH_GROUP__



#include <vector>
#include "FishLayer.h"
#include "FishScript.h"
using namespace std;
 

const int MAX_SUB_NUM = 31;
 class FishLayer;
 class FishScript;
class FishGroup 	//鱼群管理类
{
public:
	FishGroup(FishLayer *pFishManage,int iGroupMainID,int iScriptID,int iTarckID,int iNowFrameIndex);
	virtual ~FishGroup(void);

	char m_cSubLiveFlag[MAX_SUB_NUM];//SubID对应0-31，这个数组标记对应的SubID的鱼是否存在
	
	bool Update(int iSubFlag = -1,int iFrameVal = 0);//更新,决定是否要生成新鱼以及新生成的鱼是否要跳帧
	bool IsAllFishCreate(){return m_bAllFishCreate;}
	void Reset(int iGroupMainID,int iScriptID,int iTarckID,int iNowFrameIndex);
    
	void CreateFishForClient(int iNowFrameIndex,int iMultiFishFlag); //客户端根据收到的当前索引生成指定轨迹鱼

	int m_iGroupMainID;//当前鱼群在整个m_vcFish中的ID,此群里所有的子鱼都用同一个m_iMainID,m_iSubID依据m_iNowSubFishID
	int m_iFishScriptID;//当前鱼群执行的脚本ID
	int m_iTrackID;//整个鱼群所走的轨迹ID，为0的话直接走脚本指定的ID
	int m_iCreateFrame;

	int GetNowFrameIndex(){return m_fishScript.GetNowFrameIndex();}
private:
	FishLayer *m_pFishManage;//用于获得FreeFish	
	int m_iNowSubFishID;//当前子鱼的iD,新生成的子鱼iD在此上增加，不能超过MAX_SUB_NUM

	int m_iFishNumInScript;//脚本内共有多少条鱼
	
	bool m_bAllFishCreate;//是否脚本里所有的鱼都已经生成
	FishScript m_fishScript;//对应的脚本类

	

};
 

#endif