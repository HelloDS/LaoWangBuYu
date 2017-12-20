#include "FishGroup.h"
 
#include "Fish.h"
#include <math.h> 
#include <stdlib.h> 
 
FishGroup::FishGroup(FishLayer *pFishManage,int iGroupMainID,int iScriptID,int iTarckID,int iNowFrameIndex):m_fishScript(0)
{
	memset(m_cSubLiveFlag,0,sizeof(m_cSubLiveFlag));
	m_pFishManage = pFishManage;
	m_iGroupMainID = iGroupMainID;
	m_iFishScriptID = iScriptID;
	m_iTrackID = iTarckID;
	m_iNowSubFishID = 0;
	m_bAllFishCreate = false;
	m_fishScript.Reset(iScriptID,iNowFrameIndex);

	m_iFishNumInScript = 0;
	VectorScriptFrame vcScriptAll;
	FishScript::GetScriptInfoByID(m_iFishScriptID,vcScriptAll);
	m_iFishNumInScript = vcScriptAll.size();
}


void FishGroup::Reset(int iGroupMainID,int iScriptID,int iTarckID,int iNowFrameIndex)
{
	memset(m_cSubLiveFlag,0,sizeof(m_cSubLiveFlag));
	m_iGroupMainID = iGroupMainID;
	m_iFishScriptID = iScriptID;
	m_iNowSubFishID = 0;
	m_bAllFishCreate = false;
	m_iTrackID = iTarckID;
	m_fishScript.Reset(iScriptID,iNowFrameIndex);

	m_iFishNumInScript = 0;
	VectorScriptFrame vcScriptAll;
	FishScript::GetScriptInfoByID(m_iFishScriptID,vcScriptAll);
	m_iFishNumInScript = vcScriptAll.size();
}
FishGroup::~FishGroup(void)
{
}

void FishGroup::CreateFishForClient(int iNowFrameIndex,int iMultiFishFlag)
{
	m_fishScript.Reset(m_iFishScriptID,0);  //应该从第一帧开始重新生成，不然对应的subid是错的
	//printf("客户端:now[%d]--子鱼[%d],index[%d]\n",iNowFrameIndex,iMultiFishFlag,m_fishScript.GetNowFrameIndex());
	int i;
	for(i = 0;i<iNowFrameIndex;i++)
	{
		Update(iMultiFishFlag,iNowFrameIndex);
	}
	//printf("当前运行[%d]\n",m_fishScript.GetNowFrameIndex());

	
}

bool FishGroup::Update(int iSubFlag,int iFrameVal)
{	
	VectorScriptFrame vcScriptTemp;
	if(m_bAllFishCreate)
	{
		m_fishScript.GetNextFrame(vcScriptTemp);
		return false;//所有鱼都已经生成了就不用再判断了
	}	
	m_fishScript.GetNextFrame(vcScriptTemp);	
	//printf("need[%d],iSubFlag[%d],index[%d],iFrameVal[%d]\n",vcScriptTemp.size(),iSubFlag,m_fishScript.GetNowFrameIndex(),iFrameVal);
	if(!vcScriptTemp.empty())//需要产生新的轨迹鱼
	{
		//printf("Group script:ID[%d]Sc[%d],nowFrame[%d],cFish[%d]\n",m_iGroupMainID,m_iFishScriptID,m_fishScript.GetNowFrameIndex(),vcScriptTemp.size());
		for(int i = 0;i<vcScriptTemp.size();i++)
		{

			if(vcScriptTemp[i].iFishType >18)
			{ 
				vcScriptTemp[i].iFishType =16;
			}	 
			m_iNowSubFishID++;
			//判断是否要生成子鱼
		
			
			int iTrackID = 0;
		
			iTrackID = vcScriptTemp[i].iTrackID;
			 
			Point mPoint  = Point(vcScriptTemp[i].iX,vcScriptTemp[i].iY);
			m_pFishManage->GroupAddTrackFish(vcScriptTemp[i].iFishType,vcScriptTemp[i].bBigFish,m_iGroupMainID,
				m_iNowSubFishID,iTrackID,0,0,mPoint);
			 
			
		 
			//判断所有的鱼是否都已经生成
			if((m_iFishNumInScript<= MAX_SUB_NUM && m_iNowSubFishID == m_iFishNumInScript)
				 ||(m_iNowSubFishID > MAX_SUB_NUM && m_iNowSubFishID == MAX_SUB_NUM))
			{
				m_bAllFishCreate = true;
				break;
			}
		}
	} 
	return true;
	
}
