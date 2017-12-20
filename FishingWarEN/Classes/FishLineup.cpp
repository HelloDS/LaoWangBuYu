#include "FishLineup.h"

#include "FishLayer.h"
#include<algorithm>
#ifdef _WIN32
#include <windows.h>

#else
#include <sys/stat.h> 
#include <unistd.h>
#include <dirent.h> 
#endif 
 
map<int,LineupInfoDef>FishLineup::m_mapVCFishInLineup;

FishLineup::FishLineup()
{
	m_iNowFrmameIndex = 0;
	m_iNowLineupID = 0;
}

FishLineup::~FishLineup(void)
{
}

 //1�Ǻ��ŵ����󣬣������ã�����ɾ��  2 ���ŵ�����15���ŵ���Ѳ�񣨿����ã� ��һ��
 //3 ����ԲȦ���� ѭ��3��ʱ������������ã�  4�����ߵ�ԲȦ���� ���ã������ã�  
void FishLineup::Reset(int iLineupID,int iNowActFrame)
{
	m_iNowFrmameIndex = iNowActFrame;
	m_iNowLineupID =iLineupID;  // iLineupID	;
} 

bool  FishLineup::Update(vector<int> &ooo)
{
	m_iNowFrmameIndex++;

 	std::map<int,LineupInfoDef>::iterator pos = m_mapVCFishInLineup.find(m_iNowLineupID);
	if(pos != m_mapVCFishInLineup.end())
	{
		LineupInfoDef tempVcLineup = pos->second; 
		if(m_iNowFrmameIndex >= (tempVcLineup.iEndFrame-80))
		{
			m_iNowLineupID = 0;
			m_iNowFrmameIndex = 0;
			FishLayer::m_fUpdateFishYuZheng = 0;
			FishLayer::bYuZheng = false;
			FishLayer::bMoveFast = false;
			 


			return false;
		}
		if(m_iNowFrmameIndex >= tempVcLineup.iStartFrame && m_iNowFrmameIndex <= tempVcLineup.iEndFrame)
		{ 
			for(int j = 0;j<tempVcLineup.vcFishLineup.size();j++)
			{
				if(tempVcLineup.vcFishLineup[j].iActFrame == m_iNowFrmameIndex)
				{
					 ooo.push_back(tempVcLineup.vcFishLineup[j].iScriptID);
				} 
			}
		} 
	}
	if(ooo.size()!=0)
		return true;
	return false;
}

int FishLineup::GetOneRandFixedLineupID()
{

	if(!m_mapVCFishInLineup.empty())
	{
		int iRand = CCRANDOM_0_1()*m_mapVCFishInLineup.size()-0.001; //;

	 
		
		std::map<int,LineupInfoDef>::iterator pos = m_mapVCFishInLineup.begin();

		for(int i = 0;i<iRand;i++)
		{
			pos++;
		}
		if(pos != m_mapVCFishInLineup.end())
		{
			return pos->first;
		}
	}
	return 0;
}

void FishLineup::LoadAllFishLieupData()
{

	if(m_mapVCFishInLineup.size() > 0)//��ֻ֤��ʼ��һ��
		return;


	char token[50] = {0};
	std::string mimi = "mimi.zip"; 
	std::string fullminizip =  FileUtils::getInstance()->getWritablePath()+mimi; 

	//ȡ��mimi.zip�����.dat�ļ�·��
	char cLujin [50];
	sprintf(cLujin,"LineUp/%s.dat","LineUp"); 

	ssize_t fZize ;
	unsigned char * DatBuf = NULL;  

	DatBuf =FileUtils::getInstance()->getFileDataFromZip(fullminizip,cLujin,&fZize);//��ȡ.dat�ļ�����

	char * DatBuf2 = (char *)DatBuf;

	char *line;
	int temp = 0;
	int index = 0;
	line = strtok( DatBuf2,"\n");//��ȡ.dat�ļ����ݵ�ÿһ��


	LineupInfoDef  TempLineupInfo;
	FishInLineupDef tempFishInLineup;

	TempLineupInfo.iStartFrame = 0;
	TempLineupInfo.vcFishLineup.clear();

	int Index = 0;
	while(line[0] != '?')
	{
		temp = 0;
		int tempFlag = 0;
		memset(token,0,sizeof(token));	
		if(line[0] == '{')
		{ 

			if(!TempLineupInfo.vcFishLineup.empty())
			{
				m_mapVCFishInLineup.insert(std::make_pair<int,LineupInfoDef>((int&&)Index,(LineupInfoDef&&)TempLineupInfo));
			}


			TempLineupInfo.iStartFrame = 0;
			TempLineupInfo.vcFishLineup.clear();

			Index++;
			for(int i = 1 ; i < strlen(line) ;i++)
			{
				if((line[i]=='-'||line[i]=='}')&&token!=NULL)
				{
					switch (tempFlag)
					{
					case 0:TempLineupInfo.iStartFrame = atoi(token);break;
					case 1:TempLineupInfo.iEndFrame = atoi(token);break;
					default:
						break;
					}
					memset(token,0,sizeof(token));
					temp = 0;
					tempFlag++;
					continue;
				}

				char c = line[i];
				token[temp] = c;
				temp++;
			}


		}


		if(line[0] == '(')
		{
			memset(&tempFishInLineup,0,sizeof(FishInLineupDef));					
			for(int i = 1 ; i < strlen(line) ;i++)
			{
				if((line[i]==','||line[i]==')')&&token!=NULL)
				{
					switch (tempFlag)
					{
					case 0:tempFishInLineup.iScriptID = atoi(token);break;
					case 1:tempFishInLineup.iActFrame = atoi(token);break;
					default:
						break;
					}
					memset(token,0,sizeof(token));
					temp = 0;
					tempFlag++;
					continue;
				}
				char c = line[i];
				token[temp] = c;
				temp++;
			}
			if(TempLineupInfo.iStartFrame >0 && TempLineupInfo.iEndFrame >= TempLineupInfo.iStartFrame)
			{
				TempLineupInfo.vcFishLineup.push_back(tempFishInLineup); 
			}

		} 
		line = strtok(NULL,"\n");//��ȡ.dat�ļ�����һ���ļ�
	}

	if(!TempLineupInfo.vcFishLineup.empty())
	{
		m_mapVCFishInLineup.insert(std::make_pair<int,LineupInfoDef>((int&&)Index,(LineupInfoDef&&)TempLineupInfo));
	}	
}