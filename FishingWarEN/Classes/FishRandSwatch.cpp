#include "FishRandSwatch.h"
#include "cocos2d.h"
#include<algorithm>

#ifdef _WIN32
#include <windows.h>

#else
#include <sys/stat.h> 
#include <unistd.h>
#include <dirent.h>
#endif
 
USING_NS_CC;

map<int,vcFishInSwatch>FishRandSwatch::m_mapVCFishInSwatch;

bool sortFishByActFrame(FishInSwatchDef pFirstFish,FishInSwatchDef pSecondFish)  //按鱼出现顺序排序
{
	if(pFirstFish.iActFrame < pSecondFish.iActFrame)
	{
		return true;
	}
	return false;
}

FishRandSwatch::FishRandSwatch()
{
	m_iNowSwatchID = 0;
	m_iNowFrmameIndex = 0;
	m_ivcIndexInSwatch = 0;
}

FishRandSwatch::~FishRandSwatch(void)
{

}



void FishRandSwatch::Reset()
{
	int iIndex = CCRANDOM_0_1()*100;
	if(iIndex > 80)
	{
		m_iNowSwatchID = 1;
	}
	else if(iIndex > 60)
	{
		m_iNowSwatchID = 2;
	}
	else if(iIndex > 40)
	{
		m_iNowSwatchID = 3;
	}
	else if(iIndex > 20)
	{
		m_iNowSwatchID = 4;
	}
	else
	{
		m_iNowSwatchID = 5;
	}  
	m_ivcIndexInSwatch = 0;
	m_iNowFrmameIndex = CCRANDOM_0_1()*20000;
}

void FishRandSwatch::update(bool bNeedCraeteFish,vcFishInSwatch &vcNeedCreateFish)
{
	m_iNowFrmameIndex++;
	if(bNeedCraeteFish)
	{
		std::map<int,vcFishInSwatch>::iterator pos = m_mapVCFishInSwatch.find(m_iNowSwatchID);
		if(pos != m_mapVCFishInSwatch.end())
		{
			vcFishInSwatch vcTempFish = pos->second;
			for(int i = m_ivcIndexInSwatch;i<vcTempFish.size();i++)
			{
				if(vcTempFish[i].iActFrame == m_iNowFrmameIndex)
				{
					vcNeedCreateFish.push_back(vcTempFish[i]);
				}
				if(vcTempFish[i].iActFrame > m_iNowFrmameIndex)
				{
					break;
				}
				m_ivcIndexInSwatch++;
			} 
			if(m_ivcIndexInSwatch >= (vcTempFish.size()-1))
			{
				Reset();
			}
		}
	}
}

FishInSwatchDef* FishRandSwatch::JudgeIfHaveFish(int iSwatchID,int iFishMainID)
{
 
	return NULL;
}

int FishRandSwatch::GetOneRandSwatchID()
{
	if(!m_mapVCFishInSwatch.empty())
	{
		int iRand = rand()%m_mapVCFishInSwatch.size();
		std::map<int,vcFishInSwatch>::iterator pos = m_mapVCFishInSwatch.begin();
		
		for(int i = 0;i<iRand;i++)
		{
			pos++;
		}
		if(pos != m_mapVCFishInSwatch.end())
		{

		}

		return pos->first;
	}
	return 0;
}

void FishRandSwatch::ParseFishRandSwatchFile()
{
 
}


void FishRandSwatch::ClearAllRandSwatchData()
{
	m_mapVCFishInSwatch.clear();
}

void FishRandSwatch::GetAllFishRandSwatchInfoNomal()//正常读取鱼群信息
{

}

void FishRandSwatch::LoadAllRandSwatchData()
{
	if(m_mapVCFishInSwatch.size() > 0)//保证只初始化一次
		return;
 //声明要用的变量
		char  token[50];
		std::string mimi = "mimi.zip"; 
		std::string fullminizip =  FileUtils::getInstance()->getWritablePath()+mimi; 

		//取得mimi.zip里面的.dat文件路径
		char cLujin [50] = {0};
		sprintf(cLujin,"randSwatch/%s.dat","randSwatch"); 

		ssize_t fZize ;
		unsigned char * DatBuf = NULL;  

		DatBuf =FileUtils::getInstance()->getFileDataFromZip(fullminizip,cLujin,&fZize);//获取.dat文件内容
		if(!DatBuf)
		{
			return;
		}
		char * DatBuf2 = (char *)DatBuf;
 
		char *line;
		int temp = 0;
		int index = 0;
		line = strtok( DatBuf2,"\n");//获取.dat文件内容的每一行
		while(isdigit(line[0]))
		{
			vcFishInSwatch vecTemp;
			FishInSwatchDef tempInfo;
 
			line = strtok(NULL,"\n");

			while(line[0] == '(')//对.dat文件接下来的数据逐行读取,并取得相关数据存入相应变量当中
			{
				 
				if(line == NULL)
					break;
				if (strcmp(line,"\r\n")==0 || strcmp(line,"\n")==0) 
					continue;
 
				memset(&tempInfo,0,sizeof(tempInfo));

				int tempFlag = 0;
				temp = 0;
				if(line[0]=='(')
				{
					for(int i = 1 ; i < strlen(line) ;i++)
					{
						if((line[i]==','||line[i]=='\r')&&token!=NULL)
						{
							switch (tempFlag)
							{
							case 0:tempInfo.iFishType = atoi(token);break;
							case 1:tempInfo.iActFrame = atoi(token);break;
							case 2:tempInfo.iTrackOrScriptID = atoi(token);break;
							case 3:tempInfo.iExistFramesOrTrack = atoi(token);break;
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
			
				vecTemp.push_back(tempInfo);

				line = strtok(NULL,"\n");//获取.dat文件的下一行文件
				 
				if(line[0] == '?')
				{
 
					break;
				}
			}

			if(vecTemp.size() > 0)
			{
				m_mapVCFishInSwatch.insert(make_pair<int,vcFishInSwatch>((int&&) RandSwatchIndex[index],(vcFishInSwatch&&)vecTemp));
			}
			index++;

			if(line[0] == '?')
			{
				break;
			}

		 
		}
 
	if(m_mapVCFishInSwatch.size() == 0)
	{ 
		exit(0);
	}

	printf("FishRandSwatch:size[%d]\n",m_mapVCFishInSwatch.size());
}

void FishRandSwatch::WriteRandSwatchData(
	int iFishType,//鱼类型(0-7单鱼,100鱼群)
	int iActFrame,//第几帧出现(从第一帧算起,第0帧不会产生鱼)
	int iTrackOrScriptID,//轨迹或脚本ID(为0表示自由生成的鱼,>0时会根据iFishType决定是轨迹还是脚本ID)
	int iExistFrames//自由鱼总共存在多少帧
)
{
#ifdef _WIN32
	FILE *file;
	char path[100];
	sprintf_s(path,100,"randSwatch\\%d.dat",iActFrame/12000+1);
	file = fopen(path,"a");
	if (file != NULL)
	{
		char buf[100];
		memset(buf,0,sizeof(buf));
		sprintf_s(buf,100,"(%d,%d,%d,%d)\n",iFishType,iActFrame%12000,iTrackOrScriptID,iExistFrames);
		fwrite(buf,strlen(buf),1,file);
		fclose(file);
	}
	else
	{
		printf("打开文件失败 FishRandSwatch::WriteRandSwatchData");
	}
#endif
}