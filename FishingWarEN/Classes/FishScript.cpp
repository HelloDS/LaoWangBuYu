#include "FishScript.h"
#include "FishTrack.h"

#ifdef _WIN32
#include <windows.h>
//#include "Encrypt.h"
using namespace std;
#else
#include <sys/stat.h> 
#include <unistd.h>
#include <dirent.h> 
#endif


map<int,VectorScriptFrame> FishScript::m_mapVcScriptFrame;
vector<int> FishScript::m_vcScriptID;
vector<RandScriptInfoDef> FishScript::m_vecRandScriptID;
vector<RandScriptInfoDef> FishScript::m_vecRandScriptID2;

FishScript::FishScript(int iScriptID)
{
	m_iScriptID = iScriptID;

	m_iNowFrameIndex = 0;

	m_iNowActIndex = 0;
	Reset(iScriptID, 0);
}

FishScript::~FishScript(void)
{
}

void FishScript::ParseFishScriptFile()
{/*
#ifdef _WIN32
	std::string theSrcPath = StrFormat("100.dat");
	// 打开源文件
	FILE *fpSrc = 0;
	errno_t err   = fopen_s(&fpSrc, theSrcPath.c_str(), "rb");
	if (err != 0)
	{
		printf("can.t find %s\n",theSrcPath.c_str());
		return;
	}
	// 获取源文件长度
	fseek(fpSrc, 0, SEEK_END);
	__int64 filesize = _ftelli64(fpSrc);
	fseek(fpSrc, 0, SEEK_SET);

	char *pBuffer = new char[filesize];
	fread(pBuffer, sizeof(char),filesize, fpSrc);
	fclose(fpSrc);

	int iScriptID = 0;

	VectorScriptFrame vecTemp;	
	vecTemp.clear();
	ScriptFrameDef tempInfo;
	memset(&tempInfo,0,sizeof(ScriptFrameDef));

	char szNum[16];
	memset(szNum,0,sizeof(szNum));

	char line[256];
	memset(line, 0, sizeof(line));

	char *token;
	bool bNewTrack = false;
	bool bFirst = true;

	int iTableIndex = 0;
	//解密并解析

	if(iScriptID > 0 && !vecTemp.empty())
	{
		m_mapVcScriptFrame.insert(make_pair<int,VectorScriptFrame>((int&&)iScriptID,(VectorScriptFrame&&)vecTemp));
		vecTemp.clear();
	}

	delete [] pBuffer;
	pBuffer  = NULL;
	printf("--------------test2[%d]-[%d]-[%d]------------\n",m_mapVcScriptFrame.size(),m_vecRandScriptID.size(),m_vecRandScriptID2.size());
#endif*/
}

void FishScript::GetAllScriptInfoNomal()//正常读取鱼群信息
{/*
#ifdef _WIN32
	HANDLE hfile;//查找文件句柄   
	WIN32_FIND_DATA wfdata;//文件信息结构 
	BOOL IsOver=false;
	std::string strname;//文件名   
	hfile=FindFirstFile((LPCTSTR)("script\\*.dat"),&wfdata);//查找第一个文件   
	if(hfile==INVALID_HANDLE_VALUE)   
		IsOver=true;
	while(!IsOver)   
	{   
		strname=StrFormat("script\\%s",wfdata.cFileName);//获取找到的文件名
		char *token;
		token = strtok(wfdata.cFileName, ".");
		int iScriptID = atoi(token);
		VectorScriptFrame vecTemp;
		ScriptFrameDef tempInfo;
		FILE *fp = fopen(strname.c_str(), "rb+");
		if(fp)
		{
			char line[256];
			memset(line, 0, sizeof(line));
			if (fgets(line, sizeof(line), fp) == NULL)
			{
				IsOver=!FindNextFile(hfile,&wfdata);//查找下一个文件
				continue;
			}

			int iScriptType	= atoi(line);
			RandScriptInfoDef RandScriptInfoTemp;
			if (iScriptType > 0)
			{
				RandScriptInfoTemp.iScriptID = iScriptID;
			}
			while(!feof(fp))
			{	
				memset(line, 0, sizeof(line));
				if(fgets(line, sizeof(line), fp) == NULL)
					break;
				if ((strcmp(line, "\r\n") == 0) || (strcmp(line, "\n") == 0)) 
					continue;
				if(vecTemp.size() > 31)
				{
					break;
				}
				memset(&tempInfo,0,sizeof(ScriptFrameDef));
				if(line[0] == '(')
				{
					token = strtok(line+1, ",");
					if(token != NULL)
					{					
						tempInfo.bBigFish = (bool)atoi(token);				
						token = strtok(NULL, ",");
						if(token != NULL)
						{
							tempInfo.iFishType = atoi(token);
							RandScriptInfoTemp.iFishType = atoi(token);
						}
						token = strtok(NULL, ",");
						if(token != NULL)
						{
							tempInfo.iActFrameIndex = atoi(token);
						}
						token = strtok(NULL, ",");
						if(token != NULL)
						{
							tempInfo.iTrackID = atoi(token);
						}
						token = strtok(NULL, ",");
						if(token != NULL)
						{
							tempInfo.iX = atoi(token);
						}
						token = strtok(NULL, ")");
						if(token != NULL)
						{
							tempInfo.iY = atoi(token);
						}
					}
					vecTemp.push_back(tempInfo);
				}
			}
			fclose(fp);
			if(vecTemp.size() > 0)
			{
				m_mapVcScriptFrame.insert(make_pair<int,VectorScriptFrame>((int&&)iScriptID,(VectorScriptFrame&&)vecTemp));			
			}
			if (iScriptType == 1)
			{
				m_vecRandScriptID.push_back(RandScriptInfoTemp);
			}
			else if(iScriptType == 2)
			{
				m_vecRandScriptID2.push_back(RandScriptInfoTemp);
			}
		}
		IsOver=!FindNextFile(hfile,&wfdata);//查找下一个文件   
	}   
	FindClose(hfile);//关闭句柄  

	if(m_mapVcScriptFrame.size() == 0)
	{
		printf("LoadAllScriptData:size == 0\n");
		//exit(0);
	}
	else
	{
		printf("LoadAllScriptData--OK--size[%d]\n",m_mapVcScriptFrame.size());
	}
	printf("--------------test[%d]-[%d]-[%d]------------\n",m_mapVcScriptFrame.size(),m_vecRandScriptID.size(),m_vecRandScriptID2.size());
#endif*/
}

void FishScript::ClearAllScriptData()
{
	m_mapVcScriptFrame.clear();
	m_vecRandScriptID.clear();
	m_vecRandScriptID2.clear();
}
 
void FishScript::LoadAllScriptData()
{
	if(m_mapVcScriptFrame.size() > 0)//保证只初始化一次
		return;
 
		//声明要用的变量
		char  token[50];
		std::string mimi = "mimi.zip"; 
		std::string fullminizip =  FileUtils::getInstance()->getWritablePath()+mimi; 

		//取得mimi.zip里面的.dat文件路径
		char cLujin [50] = {0};
		sprintf(cLujin,"script/%s.dat","script"); 

		ssize_t fZize ;
		unsigned char * DatBuf = NULL;  

		DatBuf =FileUtils::getInstance()->getFileDataFromZip(fullminizip,cLujin,&fZize);//获取.dat文件内容

		//DatBuf = FileUtils::getInstance()->getFileData(fullminizip,"r",&fZize);
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
			VectorScriptFrame vecTemp;
			ScriptFrameDef tempInfo;
			int iScriptType = atoi(line);
			RandScriptInfoDef RandScriptInfoTemp;
			if (iScriptType > 0)
			{
				RandScriptInfoTemp.iScriptID = ScriptIndex[index];
			}

			line = strtok(NULL,"\n");

			while(line[0] == '(')//对.dat文件接下来的数据逐行读取,并取得相关数据存入相应变量当中
			{
				 
				if(line == NULL)
					break;
				if (strcmp(line,"\r\n")==0 || strcmp(line,"\n")==0) 
					continue;
				if(vecTemp.size() > 31)
				{
					break;
				}
				memset(&tempInfo,0,sizeof(ScriptFrameDef));

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
							case 0:tempInfo.bBigFish = (bool)atoi(token);break;
							case 1:tempInfo.iFishType = atoi(token);
								RandScriptInfoTemp.iFishType = atoi(token);break;
							case 2:tempInfo.iActFrameIndex = atoi(token);break;
							case 3:tempInfo.iTrackID = atoi(token);break;
							case 4:tempInfo.iX = atoi(token);break;
							case 5:tempInfo.iY = atoi(token);break;
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
			
			 
			if (iScriptType == 1)
			{
				m_vecRandScriptID.push_back(RandScriptInfoTemp);
			}
			else if (iScriptType == 2)
			{
				m_vecRandScriptID2.push_back(RandScriptInfoTemp);
			}

			if(vecTemp[0].iFishType  < 3)
			{

				int a = CCRANDOM_0_1()*11;
				for(int i=0; i< vecTemp.size(); i++)
				{
					vecTemp[i].iFishType = a;
				}

			}

			if(vecTemp[0].iFishType  >3 &&vecTemp[0].iFishType < 10)
			{ 
				int a = 4+ CCRANDOM_0_1()*11;
				for(int i=0; i< vecTemp.size(); i++)
				{
					vecTemp[i].iFishType = a;
				} 
			}


			if(vecTemp.size() > 0)
			{
				m_mapVcScriptFrame.insert(make_pair<int,VectorScriptFrame>((int&&) ScriptIndex[index],(VectorScriptFrame&&)vecTemp));
			}
			index++;

			if(line[0] == '?')
			{
				break;
			}

		 
		}
 
	if(m_mapVcScriptFrame.size() == 0)
	{ 
		exit(0);
	}
	else
	{
		 
	}
	if (m_vecRandScriptID.size() == 0)
	{
  
		exit(0);
	}
 
}
 
void FishScript::GetNextFrame(VectorScriptFrame &vecScript)
{
	if(m_mapVcScriptFrame.find(m_iScriptID) == m_mapVcScriptFrame.end())
	{
		return;
	}

	m_iNowFrameIndex++;

	for(int i = m_iNowActIndex;i<m_mapVcScriptFrame[m_iScriptID].size();i++)
	{
		if(m_mapVcScriptFrame[m_iScriptID][i].iActFrameIndex == m_iNowFrameIndex)
		{
			vecScript.push_back(m_mapVcScriptFrame[m_iScriptID][i]);
		}
	}
}	

VectorScriptFrame FishScript::GetAllFrameBeforeIndex(int iFrameIndex)
{
	VectorScriptFrame vecScript;
	if(m_mapVcScriptFrame.find(m_iScriptID) == m_mapVcScriptFrame.end())
	{
		return vecScript;
	}
    for(int i = m_iNowActIndex;i<m_mapVcScriptFrame[m_iScriptID].size();i++)
	{
		if(m_mapVcScriptFrame[m_iScriptID][i].iActFrameIndex <= iFrameIndex)
		{
			vecScript.push_back(m_mapVcScriptFrame[m_iScriptID][i]);
		}
	}
	return vecScript;
}

void FishScript::Reset(int iScriptID,int iNowFrameIndex)
{
	m_iScriptID = iScriptID;
	
	m_iNowFrameIndex = iNowFrameIndex;

	m_iNowActIndex = 0;

	if (m_iScriptID <= 0)
	{
		m_iScriptType = -1;
		return;
	}
	int i;
	for (i=0; i<m_vecRandScriptID.size(); i++)
		if (m_iScriptID == m_vecRandScriptID[i].iScriptID)
		{
			m_iScriptType = 1;
			return;
		}

	for (i=0; i<m_vecRandScriptID2.size(); i++)
		if (m_iScriptID == m_vecRandScriptID2[i].iScriptID)
		{
			m_iScriptType = 2;
			return;
		}
	m_iScriptType = 0;

}

bool FishScript::IfScriptOver()
{
	if(m_mapVcScriptFrame.find(m_iScriptID) == m_mapVcScriptFrame.end())
		return true;
	if (GetLastFrame() >= m_iNowFrameIndex)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void FishScript::AddOneScriptToMap( int iScriptID,VectorScriptFrame vecInfo )
{
	m_mapVcScriptFrame.insert(make_pair<int,VectorScriptFrame>((int&&)iScriptID,(VectorScriptFrame&&)vecInfo));
}

bool FishScript::GetScriptInfoByID( int iScriptID,VectorScriptFrame &vecInfo )
{
	bool bFind = false;
	std::map<int,VectorScriptFrame>::iterator pos;

	pos = m_mapVcScriptFrame.find(iScriptID);
	if (pos != m_mapVcScriptFrame.end())
	{
		bFind = true;
		vecInfo = pos->second;
	}
	return bFind;
}

void FishScript::SetOneScript( int iScriptID,VectorScriptFrame vecInfo )
{
	m_mapVcScriptFrame[iScriptID] = vecInfo;
}
 
bool FishScript::IsScriptID(int iScriptID)
{
	bool bFind = false;
	std::map<int,VectorScriptFrame>::iterator pos;
	pos = m_mapVcScriptFrame.find(iScriptID);
	if (pos != m_mapVcScriptFrame.end())
	{
		bFind = true;
	}
	return bFind;
}

int FishScript::GetLastFrame()
{
	VectorScriptFrame vecScript;
	GetScriptInfoByID(m_iScriptID,vecScript);
	VectorTrackInfo vecTrack;
	int	iMaxFrame = 0;

	for (int i=0; i<vecScript.size(); i++)
	{
		if (FishTrack::GetTrackInfoByID(vecScript[i].iTrackID,vecScript[i].bBigFish,vecTrack))
		{
			//vecTrack.vTrackPoint.size() 是 vecScript[i].iTrackID 轨迹的总帧数
			if (iMaxFrame < vecTrack.vTrackPoint.size() + vecScript[i].iActFrameIndex)
			{
				iMaxFrame = vecTrack.vTrackPoint.size() + vecScript[i].iActFrameIndex;
			}
		}	
	}
	return iMaxFrame;
}

int FishScript::GetNowFrameIndex()
{
	return m_iNowFrameIndex;
}

int FishScript::GetLastFrameNum(int iScriptID)
{
	VectorScriptFrame vecScript;
	GetScriptInfoByID(iScriptID,vecScript);
	VectorTrackInfo vecTrack;
	int	iMaxFrame = 0;

	for (int i=0; i<vecScript.size(); i++)
	{
		if (FishTrack::GetTrackInfoByID(vecScript[i].iTrackID,vecScript[i].bBigFish,vecTrack))
		{
			//vecTrack.vTrackPoint.size() 是 vecScript[i].iTrackID 轨迹的总帧数
			if (iMaxFrame < vecTrack.vTrackPoint.size() + vecScript[i].iActFrameIndex)
			{
				iMaxFrame = vecTrack.vTrackPoint.size() + vecScript[i].iActFrameIndex;
			}
		}		
	}
	return iMaxFrame;
}
 
int FishScript::GetRandFishScript()
{
	if (m_vecRandScriptID2.size() == 0)
		return -1;
	int iRand = CCRANDOM_0_1()*m_vecRandScriptID2.size()-0.001;
	int iScriptID = m_vecRandScriptID2[iRand].iScriptID;
	return iScriptID;
}
 
int FishScript::GetFishTypeByScriptID( int iScriptID )
{
	for(int i=0; i<m_vecRandScriptID.size(); i++)
	{
		if (m_vecRandScriptID[i].iScriptID == iScriptID)
		{
			return m_vecRandScriptID[i].iFishType;
		}
	}
	return -1;
}

int FishScript::GetRandGroupFishScript( int iFishType,int &iTrackID , const vector<int> &vNoRandTrackID)
{
	//vector<int> vec;
	iTrackID = FishTrack::GetRandGroupFishTrackID(vNoRandTrackID);
	int iScriptID = -1;
	int iFishNum = 0;//指定鱼的脚本个数
	int index = -1;
	int iRand;

	
	for (int i=0; i<m_vecRandScriptID.size(); i++)
	{
		if (m_vecRandScriptID[i].iFishType == iFishType)
		{
			iFishNum++;
		}
	}
	if (iFishNum == 0)
	{
		//printf("该鱼没有可随机的脚本 iFishType = [%d]\n",iFishType);
		printf("no fish track  iFishType = [%d]\n",iFishType);
		return -1;
	}
	iRand = CCRANDOM_0_1()*iFishNum;

	for (int i=0; i<m_vecRandScriptID.size(); i++)
	{
		if (m_vecRandScriptID[i].iFishType == iFishType)
		{
			index++;
		}
		if (index == iRand)
		{
			iScriptID = m_vecRandScriptID[i].iScriptID;
			break;
		}
	}
	if (iScriptID == -1)
	{
		//printf("没有找到该鱼的轨迹 iFishType = [%d] iRand = [%d]\n",iFishType, iRand);
		printf("no fish track iFishType = [%d] iRand = [%d]\n",iFishType, iRand);
		return -1;
	}

	return iScriptID;
}