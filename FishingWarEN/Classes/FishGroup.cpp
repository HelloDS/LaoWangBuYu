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
	m_fishScript.Reset(m_iFishScriptID,0);  //Ӧ�ôӵ�һ֡��ʼ�������ɣ���Ȼ��Ӧ��subid�Ǵ��
	//printf("�ͻ���:now[%d]--����[%d],index[%d]\n",iNowFrameIndex,iMultiFishFlag,m_fishScript.GetNowFrameIndex());
	int i;
	for(i = 0;i<iNowFrameIndex;i++)
	{
		Update(iMultiFishFlag,iNowFrameIndex);
	}
	//printf("��ǰ����[%d]\n",m_fishScript.GetNowFrameIndex());

	
}

bool FishGroup::Update(int iSubFlag,int iFrameVal)
{	
	VectorScriptFrame vcScriptTemp;
	if(m_bAllFishCreate)
	{
		m_fishScript.GetNextFrame(vcScriptTemp);
		return false;//�����㶼�Ѿ������˾Ͳ������ж���
	}	
	m_fishScript.GetNextFrame(vcScriptTemp);	
	//printf("need[%d],iSubFlag[%d],index[%d],iFrameVal[%d]\n",vcScriptTemp.size(),iSubFlag,m_fishScript.GetNowFrameIndex(),iFrameVal);
	if(!vcScriptTemp.empty())//��Ҫ�����µĹ켣��
	{
		//printf("Group script:ID[%d]Sc[%d],nowFrame[%d],cFish[%d]\n",m_iGroupMainID,m_iFishScriptID,m_fishScript.GetNowFrameIndex(),vcScriptTemp.size());
		for(int i = 0;i<vcScriptTemp.size();i++)
		{

			if(vcScriptTemp[i].iFishType >18)
			{ 
				vcScriptTemp[i].iFishType =16;
			}	 
			m_iNowSubFishID++;
			//�ж��Ƿ�Ҫ��������
		
			
			int iTrackID = 0;
		
			iTrackID = vcScriptTemp[i].iTrackID;
			 
			Point mPoint  = Point(vcScriptTemp[i].iX,vcScriptTemp[i].iY);
			m_pFishManage->GroupAddTrackFish(vcScriptTemp[i].iFishType,vcScriptTemp[i].bBigFish,m_iGroupMainID,
				m_iNowSubFishID,iTrackID,0,0,mPoint);
			 
			
		 
			//�ж����е����Ƿ��Ѿ�����
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
