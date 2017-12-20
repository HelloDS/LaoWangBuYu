#include "FishTrack.h"
#include "cocos2d.h"
#include <fstream>
#include "FishLayer.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
#include <windows.h>

using namespace std;
#else
#include <sys/stat.h> 
#include <unistd.h>
#include <dirent.h> 
#endif 
map<int,VectorTrackInfo> FishTrack::m_mapVcBigTrackPoint;
map<int,VectorTrackInfo> FishTrack::m_mapVcSmallTrackPoint;
map<int,VectorTrackInfo> FishTrack::m_mapVcSpeTrackPoint;
map<int,VectorTrackInfo> FishTrack::m_mapVcMonsterTrackPoint;
map<int,VectorTrackInfo> FishTrack::m_mapVcGrampusTrackPoint;

vector<int> FishTrack::m_vcTrackID;
vector<int> FishTrack::m_vcSmallTrackID;
vector<int> FishTrack::m_vcSpeTrackID;
vector<int> FishTrack::m_vcMonsterTrackID;
vector<int> FishTrack::m_vcGrampusTrackID;


FishTrack::FishTrack(int iTrackID, bool bBigFish)
{
	Reset(iTrackID, bBigFish);
}

FishTrack::~FishTrack(void)
{

}

void FishTrack::Reset(int iTrackID, bool bBigFish, int iNowTrackIndex )
{
	bFanZhuan = false;
	m_iNowTrackIndex = iNowTrackIndex;
	
	
	m_iTrackID = iTrackID;
	m_bBigFish = bBigFish;
	bool bFind = false;
	if(m_bBigFish)
	{
		if(m_mapVcBigTrackPoint.find(m_iTrackID) != m_mapVcBigTrackPoint.end())
		{
			bFind = true;
			m_trackType = TRACK_BIG;
			/*TrackPointDef mTempPoint = m_mapVcBigTrackPoint[m_iTrackID].vTrackPoint[0];
			if(mTempPoint.mPoint.x < 0 && FishLayer::bYuZheng == false )
			{
				int iRandom  = CCRANDOM_0_1()*100;
				if(iRandom< 30)
				{
					bFanZhuan = true;
					m_iNowTrackIndex =m_mapVcBigTrackPoint[m_iTrackID].vTrackPoint.size() -1;
				} 
			} */
		}
	}
	else
	{

		if(m_mapVcSmallTrackPoint.find(m_iTrackID) != m_mapVcSmallTrackPoint.end())
		{
			bFind = true;
			m_trackType = TRACK_SMALL;
		 
		}
	}

	//没找到就到其他里找
	/*if(!bFind && m_mapVcSpeTrackPoint.find(m_iTrackID) != m_mapVcSpeTrackPoint.end())
	{
		bFind = true;
		m_trackType = TRACK_SPECIAL;
	}
	if(!bFind && m_mapVcMonsterTrackPoint.find(m_iTrackID) != m_mapVcMonsterTrackPoint.end())
	{
		bFind = true;
		m_trackType = TRACK_MONSTER;
	}
	if(!bFind && m_mapVcGrampusTrackPoint.find(m_iTrackID) != m_mapVcGrampusTrackPoint.end())
	{
		bFind = true;
		m_trackType = m_trackType;
	}*/
	if(!bFind)
	{
		m_trackType = TRACK_UNKNOW;
	}
}

//VectorTrackInfo FishTrack::initTrackVec(int trackID,string kindPage)
//{
//		VectorTrackInfo vecTemp;
//		TrackPointDef tempTrackPoint;
//
//		//声明要用的变量  
//		char  token[50];
//		std::string mimi = "mimi.zip"; 
//		std::string fullminizip =  FileUtils::getInstance()->getWritablePath()+mimi; 
//
//		//取得mimi.zip里面的.dat文件路径
//		char cLujin [50] = {0};
//		sprintf(cLujin,"track/%s/%d.dat",kindPage.c_str(),trackID); 
//
//		ssize_t fZize ;
//		unsigned char * DatBuf = NULL;  
//
//		DatBuf =FileUtils::getInstance()->getFileDataFromZip(fullminizip,cLujin,&fZize);//获取.dat文件内容
//
//		char * DatBuf2 = (char *)DatBuf;
//
//	    //char line[256];
//		//memset(line, 0, sizeof(line));
//
//		char *line;
//		int temp = 0;
//		line = strtok( DatBuf2,"\n");//获取.dat文件内容的每一行
//		for(int i = 0 ; i < strlen(line) ;i++)//将第一行的数字，以逗号分开分别存进vecTemp.vFishType中
//		{
//			if((line[i]==','||line[i]=='\r')&&token!=NULL)
//			{
//				vecTemp.vFishType.push_back(atoi(token));
//				memset(token,0,sizeof(token));
//				temp = 0;
//				continue;
//			}
//			char c = line[i];
//			token[temp] = c;
//			temp++;
//		}
//		memset(token,0,sizeof(token));//将token清零
//
//		
//		while(line != NULL)//对.dat文件接下来的数据逐行读取,并取得相关数据存入相应变量当中
//		{
//			line = strtok(NULL,"\n");//获取.dat文件的下一行文件
//			if(line == NULL)
//				break;
//			if (strcmp(line,"\r\n")==0 || strcmp(line,"\n")==0) 
//				continue;
//			memset(&tempTrackPoint,0,sizeof(TrackPointDef));
//
//			int tempFlag = 0;
//			temp = 0;
//			if(line[0]=='(')
//			{
//				for(int i = 1 ; i < strlen(line) ;i++)
//				{
//					if((line[i]==','||line[i]=='\r')&&token!=NULL)
//					{
//						switch (tempFlag)
//						{
//						case 0:tempTrackPoint.mPoint.x = atoi(token);break;
//						case 1:tempTrackPoint.mPoint.y = atoi(token);;break;
//						case 2:tempTrackPoint.dAngleValue = atof(token);break;
//						case 3:tempTrackPoint.iSpeFrame = atoi(token);break;
//						default:
//							break;
//						}
//						memset(token,0,sizeof(token));
//						temp = 0;
//						tempFlag++;
//						continue;
//					}
//				
//					char c = line[i];
//					token[temp] = c;
//					temp++;
//				}
//			}
//			
//			vecTemp.vTrackPoint.push_back(tempTrackPoint);
//		}
//
//		return vecTemp;
//
//}

void FishTrack::initMap(string kindPage)
{
		//声明要用的变量
		std::string mimi = "mimi.zip"; 
		std::string fullminizip =  FileUtils::getInstance()->getWritablePath()+mimi; 

		//取得mimi.zip里面的.dat文件路径
		char cLujin [50] = {0};
		if(kindPage == "big")
			sprintf(cLujin,"track/big/%s.dat","big");
		if(kindPage == "small")
			sprintf(cLujin,"track/small/%s.dat","small"); 
		if(kindPage == "task")
			sprintf(cLujin,"track/task/%s.dat","task");


		ssize_t fZize ;
		unsigned char * DatBuf = NULL;  
		 cocos2d::log("```````````qinitMap4");
		DatBuf =FileUtils::getInstance()->getFileDataFromZip(fullminizip,cLujin,&fZize);//获取.dat文件内容
		 cocos2d::log("````````````qinitMap4");
		char * DatBuf2 = (char *)DatBuf;

	    //char line[256];
		//memset(line, 0, sizeof(line));
		if(DatBuf == NULL)
		{
			cocos2d::log("``````wfwfwf``````qinitMap4"); 
		}
		 
		char *line;
		int temp = 0;
		char  token[50];
		line = strtok( DatBuf2,"\n");//获取.dat文件内容的每一行
		int index=0;
		 cocos2d::log("````````````qinitMap4wf %s",line);
		while(line[0]!='\n'&&isdigit(line[0]))
		{
			 
			VectorTrackInfo tempVec;
			TrackPointDef tempTrackPoint;
			// cocos2d::log("```````index %d````qinitMap4",index);
			 
			for(int i = 0 ; i < strlen(line) ;i++)//将第一行的数字，以逗号分开分别存进vecTemp.vFishType中
			{
				if((line[i]==','||line[i]=='\r')&&token!=NULL)
				{
					tempVec.vFishType.push_back(atoi(token));
					memset(token,0,sizeof(token));
					temp = 0;
					continue;
				}
				char c = line[i];
				token[temp] = c;
				temp++;
			}
			memset(token,0,sizeof(token));//将token清零
			line = strtok(NULL,"\n");//获取.dat文件的下一行文件
	 
    			while(line[0] == '(')//对.dat文件接下来的数据逐行读取,并取得相关数据存入相应变量当中
			{
				 
				if(line == NULL)
					break;
				if (strcmp(line,"\r\n")==0 || strcmp(line,"\n")==0) 
					continue;
				memset(&tempTrackPoint,0,sizeof(TrackPointDef));
				
				 
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
							case 0:tempTrackPoint.mPoint.x = atoi(token);break;
							case 1:tempTrackPoint.mPoint.y = atoi(token);;break;
							case 2:tempTrackPoint.dAngleValue = atof(token);break;
							case 3:tempTrackPoint.iSpeFrame = atoi(token);break;
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
				tempVec.vTrackPoint.push_back(tempTrackPoint);

				   
				line = strtok(NULL,"\n");//获取.dat文件的下一行文件
				if(line[0] == '?')
				{  
					break;
				}
 
				
			}
			 
			if(tempVec.vTrackPoint.size() > 0 && kindPage == "big")
			{
				m_mapVcBigTrackPoint.insert(make_pair<int,VectorTrackInfo>((int&&)BigTrackIndex[index],(VectorTrackInfo&&)tempVec));
				m_vcTrackID.push_back(BigTrackIndex[index]);

			}
			if(tempVec.vTrackPoint.size() > 0 && kindPage == "small")
			{
				m_mapVcSmallTrackPoint.insert(make_pair<int,VectorTrackInfo>((int&&)SmallTrackIndex[index],(VectorTrackInfo&&)tempVec));
				m_vcSmallTrackID.push_back(SmallTrackIndex[index]);
			}

			if(tempVec.vTrackPoint.size() > 0 && kindPage == "task")
			{
				m_mapVcSpeTrackPoint.insert(make_pair<int,VectorTrackInfo>((int&&)BigTrackIndex[index],(VectorTrackInfo&&)tempVec));
				m_vcTrackID.push_back(BigTrackIndex[index]);

			} 
			index++;
			if(line[0] == '?')
			{
				cocos2d::log("````wf````````qinitMap4");
				break;
			}
		} 

}

void FishTrack::LoadAllTrackData()
{

	if(m_mapVcBigTrackPoint.size() > 0)//保证只初始化一次
		return;

/*#ifdef _WIN32
	
	HANDLE hfile;//查找文件句柄   
	WIN32_FIND_DATA wfdata;//文件信息结构 
	BOOL IsOver=false;
	std::string strname;//文件名   
	hfile=FindFirstFile((LPCTSTR)("track\\big\\*.dat"),&wfdata);//查找第一个文件   
	if(hfile==INVALID_HANDLE_VALUE)   
		IsOver=true;
	while(!IsOver)   
	{   
		strname=StrFormat("track\\big\\%s",wfdata.cFileName);//获取找到的文件名
		char *token;
		token = strtok(wfdata.cFileName, ".");
		int iTrackID = atoi(token);
		VectorTrackInfo vecTemp;
		TrackPointDef tempTrackPoint;
		FILE *fp = fopen(strname.c_str(), "rb+");
		if(fp)
		{
			char line[256];
			memset(line, 0, sizeof(line));
			if(fgets(line, sizeof(line), fp) == NULL)
			{
				IsOver=!FindNextFile(hfile,&wfdata);//查找下一个文件
				continue;
			}
			token = strtok(line, ",");
			while (token != NULL)
			{
				
				vecTemp.vFishType.push_back(atoi(token));
				token = strtok(NULL, ",");
			}
			while(!feof(fp))
			{
				memset(line, 0, sizeof(line));
				if(fgets(line, sizeof(line), fp) == NULL)
					break;
				if ((strcmp(line, "\r\n") == 0) || (strcmp(line, "\n") == 0)) 
					continue;
				memset(&tempTrackPoint,0,sizeof(TrackPointDef));
				if(line[0] == '(')
				{
					token = strtok(line+1, ",");
					if(token != NULL)
					{					
						tempTrackPoint.mPoint.x = atoi(token);				
						token = strtok(NULL, ",");
						if(token != NULL)
						{
							tempTrackPoint.mPoint.y = atoi(token);
						}
						token = strtok(NULL, ",");
						if(token != NULL)
						{
							tempTrackPoint.dAngleValue = atof(token);
						}
						token = strtok(NULL, ")");
						if(token != NULL)
						{
							tempTrackPoint.iSpeFrame = atoi(token);
						}
					}
					vecTemp.vTrackPoint.push_back(tempTrackPoint);
				}
			}
			fclose(fp);
			if(vecTemp.vTrackPoint.size() > 0)
			{
				m_mapVcBigTrackPoint.insert(make_pair<int,VectorTrackInfo>((int&&)iTrackID,(VectorTrackInfo&&)vecTemp));

				m_vcTrackID.push_back(iTrackID);
			}
		}
		IsOver=!FindNextFile(hfile,&wfdata);//查找下一个文件   
	}   
	FindClose(hfile);//关闭句柄

	IsOver=false;
	hfile=FindFirstFile((LPCTSTR)("track\\small\\*.dat"),&wfdata);//查找第一个文件   
	if(hfile==INVALID_HANDLE_VALUE)   
		IsOver=true;
	while(!IsOver)   
	{   
		strname=StrFormat("track\\small\\%s",wfdata.cFileName);//获取找到的文件名
		char *token;
		token = strtok(wfdata.cFileName, ".");
		int iTrackID = atoi(token);
		VectorTrackInfo vecTemp;
		TrackPointDef tempTrackPoint;
		FILE *fp = fopen(strname.c_str(), "rb+");
		if(fp)
		{
			char line[256];
			memset(line, 0, sizeof(line));
			if(fgets(line, sizeof(line), fp) == NULL)
			{
				IsOver=!FindNextFile(hfile,&wfdata);//查找下一个文件
				continue;
			}
			token = strtok(line, ",");
			while (token != NULL)
			{

				vecTemp.vFishType.push_back(atoi(token));
				token = strtok(NULL, ",");
			}
			while(!feof(fp))
			{
				memset(line, 0, sizeof(line));
				if(fgets(line, sizeof(line), fp) == NULL)
					break;
				if ((strcmp(line, "\r\n") == 0) || (strcmp(line, "\n") == 0)) 
					continue;
				memset(&tempTrackPoint,0,sizeof(TrackPointDef));
				if(line[0] == '(')
				{
					token = strtok(line+1, ",");
					if(token != NULL)
					{					
						tempTrackPoint.mPoint.x = atoi(token);				
						token = strtok(NULL, ",");
						if(token != NULL)
						{
							tempTrackPoint.mPoint.y = atoi(token);
						}
						token = strtok(NULL, ",");
						if(token != NULL)
						{
							tempTrackPoint.dAngleValue = atof(token);
						}
						token = strtok(NULL, ")");
						if(token != NULL)
						{
							tempTrackPoint.iSpeFrame = atoi(token);
						}
					}
					vecTemp.vTrackPoint.push_back(tempTrackPoint);
				}
			}
			fclose(fp);
			if(vecTemp.vTrackPoint.size() > 0)
			{
				m_mapVcSmallTrackPoint.insert(make_pair<int,VectorTrackInfo>((int&&)iTrackID,(VectorTrackInfo&&)vecTemp));

				//m_vcTrackID.push_back(iTrackID);
				m_vcSmallTrackID.push_back(iTrackID);
			}
		}
		IsOver=!FindNextFile(hfile,&wfdata);//查找下一个文件   
	}   
	FindClose(hfile);//关闭句柄

	
	***********************************以下是注释掉的手机处理
	IsOver=false;
	hfile=FindFirstFile((LPCTSTR)("track\\special\\*.dat"),&wfdata);//查找第一个文件   
	if(hfile==INVALID_HANDLE_VALUE)   
		IsOver=true;
	while(!IsOver)   
	{   
		strname=StrFormat("track\\special\\%s",wfdata.cFileName);//获取找到的文件名
		char *token;
		token = strtok(wfdata.cFileName, ".");
		int iTrackID = atoi(token);
		VectorTrackInfo vecTemp;
		TrackPointDef tempTrackPoint;
		FILE *fp = fopen(strname.c_str(), "rb+");
		if(fp)
		{
			char line[256];
			memset(line, 0, sizeof(line));
			if(fgets(line, sizeof(line), fp) == NULL)
			{
				IsOver=!FindNextFile(hfile,&wfdata);//查找下一个文件
				continue;
			}
			token = strtok(line, ",");
			while (token != NULL)
			{

				vecTemp.vFishType.push_back(atoi(token));
				token = strtok(NULL, ",");
			}
			while(!feof(fp))
			{
				memset(line, 0, sizeof(line));
				if(fgets(line, sizeof(line), fp) == NULL)
					break;
				if ((strcmp(line, "\r\n") == 0) || (strcmp(line, "\n") == 0)) 
					continue;
				memset(&tempTrackPoint,0,sizeof(TrackPointDef));
				if(line[0] == '(')
				{
					token = strtok(line+1, ",");
					if(token != NULL)
					{					
						tempTrackPoint.mPoint.x = atoi(token);				
						token = strtok(NULL, ",");
						if(token != NULL)
						{
							tempTrackPoint.mPoint.y = atoi(token);
						}
						token = strtok(NULL, ",");
						if(token != NULL)
						{
							tempTrackPoint.dAngleValue = atof(token);
						}
						token = strtok(NULL, ")");
						if(token != NULL)
						{
							tempTrackPoint.iSpeFrame = atoi(token);
						}
					}
					vecTemp.vTrackPoint.push_back(tempTrackPoint);
				}
			}
			fclose(fp);
			if(vecTemp.vTrackPoint.size() > 0)
			{
				m_vcSpeTrackID.push_back(iTrackID);
				m_mapVcSpeTrackPoint.insert(make_pair<int,VectorTrackInfo>((int&&)iTrackID,(VectorTrackInfo&&)vecTemp));
			}
		}
		IsOver=!FindNextFile(hfile,&wfdata);//查找下一个文件   
	}   
	FindClose(hfile);//关闭句柄  


	IsOver=false;
	hfile=FindFirstFile((LPCTSTR)("track\\monster\\*.dat"),&wfdata);//查找第一个文件   
	if(hfile==INVALID_HANDLE_VALUE)   
		IsOver=true;
	while(!IsOver)   
	{   
		strname=StrFormat("track\\monster\\%s",wfdata.cFileName);//获取找到的文件名
		char *token;
		token = strtok(wfdata.cFileName, ".");
		int iTrackID = atoi(token);
		VectorTrackInfo vecTemp;
		TrackPointDef tempTrackPoint;
		FILE *fp = fopen(strname.c_str(), "rb+");
		if(fp)
		{
			char line[256];
			memset(line, 0, sizeof(line));
			if(fgets(line, sizeof(line), fp) == NULL)
			{
				IsOver=!FindNextFile(hfile,&wfdata);//查找下一个文件
				continue;
			}
			token = strtok(line, ",");
			while (token != NULL)
			{ 
				vecTemp.vFishType.push_back(atoi(token));
				token = strtok(NULL, ",");
			}
			while(!feof(fp))
			{
				memset(line, 0, sizeof(line));
				if(fgets(line, sizeof(line), fp) == NULL)
					break;
				if ((strcmp(line, "\r\n") == 0) || (strcmp(line, "\n") == 0)) 
					continue;
				memset(&tempTrackPoint,0,sizeof(TrackPointDef));
				if(line[0] == '(')
				{
					token = strtok(line+1, ",");
					if(token != NULL)
					{					
						tempTrackPoint.mPoint.x = atoi(token);				
						token = strtok(NULL, ",");
						if(token != NULL)
						{
							tempTrackPoint.mPoint.y = atoi(token);
						}
						token = strtok(NULL, ",");
						if(token != NULL)
						{
							tempTrackPoint.dAngleValue = atof(token);
						}
						token = strtok(NULL, ")");
						if(token != NULL)
						{
							tempTrackPoint.iSpeFrame = atoi(token);
						}
					}
					vecTemp.vTrackPoint.push_back(tempTrackPoint);
				}
			}
			fclose(fp);
			if(vecTemp.vTrackPoint.size() > 0)
			{
				m_vcMonsterTrackID.push_back(iTrackID);
				m_mapVcMonsterTrackPoint.insert(make_pair<int,VectorTrackInfo>((int&&)iTrackID,(VectorTrackInfo&&)vecTemp));
			}
		}
		IsOver=!FindNextFile(hfile,&wfdata);//查找下一个文件   
	}   
	FindClose(hfile);//关闭句柄  

	IsOver=false;
	hfile=FindFirstFile((LPCTSTR)("track\\grampus\\*.dat"),&wfdata);//查找第一个文件   
	if(hfile==INVALID_HANDLE_VALUE)   
		IsOver=true;
	while(!IsOver)   
	{   
		strname=StrFormat("track\\grampus\\%s",wfdata.cFileName);//获取找到的文件名
		char *token;
		token = strtok(wfdata.cFileName, ".");
		int iTrackID = atoi(token);
		VectorTrackInfo vecTemp;
		TrackPointDef tempTrackPoint;
		FILE *fp = fopen(strname.c_str(), "rb+");
		if(fp)
		{
			char line[256];
			memset(line, 0, sizeof(line));
			if(fgets(line, sizeof(line), fp) == NULL)
			{
				IsOver=!FindNextFile(hfile,&wfdata);//查找下一个文件
				continue;
			}
			token = strtok(line, ",");
			while (token != NULL)
			{

				vecTemp.vFishType.push_back(atoi(token));
				token = strtok(NULL, ",");
			}
			while(!feof(fp))
			{
				memset(line, 0, sizeof(line));
				if(fgets(line, sizeof(line), fp) == NULL)
					break;
				if ((strcmp(line, "\r\n") == 0) || (strcmp(line, "\n") == 0)) 
					continue;
				memset(&tempTrackPoint,0,sizeof(TrackPointDef));
				if(line[0] == '(')
				{
					token = strtok(line+1, ",");
					if(token != NULL)
					{					
						tempTrackPoint.mPoint.x = atoi(token);				
						token = strtok(NULL, ",");
						if(token != NULL)
						{
							tempTrackPoint.mPoint.y = atoi(token);
						}
						token = strtok(NULL, ",");
						if(token != NULL)
						{
							tempTrackPoint.dAngleValue = atof(token);
						}
						token = strtok(NULL, ")");
						if(token != NULL)
						{
							tempTrackPoint.iSpeFrame = atoi(token);
						}
					}
					vecTemp.vTrackPoint.push_back(tempTrackPoint);
				}
			}
			fclose(fp);
			if(vecTemp.vTrackPoint.size() > 0)
			{
				m_vcGrampusTrackID.push_back(iTrackID);
				m_mapVcGrampusTrackPoint.insert(make_pair<int,VectorTrackInfo>((int&&)iTrackID,(VectorTrackInfo&&)vecTemp));
			}
		}
		IsOver=!FindNextFile(hfile,&wfdata);//查找下一个文件   
	}   
	FindClose(hfile);//关闭句柄  
	

	//取得小轨迹集合
	for(int i =0; i< 51; i++)
	{
		m_vcSmallTrackID.push_back(SmallTrackIndex[i]);
	}
	//初始化map
	for(int i = 0;i<m_vcSmallTrackID.size();i++)
	{
		VectorTrackInfo smallVec = initTrackVec(m_vcSmallTrackID[i],"small");

		if(smallVec.vTrackPoint.size() > 0)
		{
			m_mapVcSmallTrackPoint.insert(make_pair<int,VectorTrackInfo>((int&&)m_vcSmallTrackID[i],(VectorTrackInfo&&)smallVec));
		}
	  
	}

	//取得大轨迹集合
	for(int i =0; i< 51; i++)
	{
		m_vcTrackID.push_back(BigTrackIndex[i]);
	}

	for(int i = 0;i<m_vcTrackID.size();i++)
	{
		VectorTrackInfo bigVec = initTrackVec(m_vcTrackID[i],"big");

		if(bigVec.vTrackPoint.size() > 0)
		{
			m_mapVcBigTrackPoint.insert(make_pair<int,VectorTrackInfo>((int&&)m_vcTrackID[i],(VectorTrackInfo&&)bigVec));
		}
	  
	}*/

//#else
	//初始化bigMap
	initMap("big");
	//初始化smallMap
	initMap("small");

	initMap("task");

/*
 
if(m_mapVcBigTrackPoint.size() > 0 || m_mapVcSmallTrackPoint.size() > 0)//保证只初始化一次
{
	printf("FishTrack::LoadAllTrackData 已经初始化过\n");
	return;
}


for(int i =0; i< 51; i++)
{
	m_vcTrackID.push_back(BigTrackIndex[i]);
}
  
char *token; 
std::string mimi = "mimi.zip"; 
std::string fullminizip =  FileUtils::getInstance()->getWritablePath()+mimi; 

for(int i = 0;i<m_vcTrackID.size();i++)
{
	  
	VectorTrackInfo vecTemp;
	TrackPointDef tempTrackPoint;

	char cLujin [50] = {0};
	sprintf(cLujin,"track/big/%d.dat",m_vcTrackID[i]); 
	string TrackLujin =FileUtils::getInstance()->getWritablePath()+cLujin;
	FILE *checkfp = fopen(TrackLujin.c_str(), "rb+"); 
	bool bHave = false;
	if(checkfp ==NULL)
	{
		 
		ssize_t fZize ;
		unsigned char * DatBuf = NULL;  

		DatBuf =FileUtils::getInstance()->getFileDataFromZip(fullminizip,cLujin,&fZize);
		if(DatBuf == NULL)
		{
			cocos2d::log("Dont in mimizip %d",m_vcTrackID[i] );
			continue;
		}
		else
		{ 
			FILE *fp = fopen(TrackLujin.c_str(),"w+");  
			fwrite(DatBuf,sizeof(char), fZize,fp);
			fclose(fp);
			cocos2d::log("Writeok%s",TrackLujin.c_str());
		}

	}
	else
	{ 
		cocos2d::log("track have %d",m_vcTrackID[i] );
		bHave = true;
	}


	FILE *fp;
	if(bHave = true)
	{
		fp = checkfp;
	}
	else
	{
		fp = fopen(TrackLujin.c_str(), "rb+"); 
	}
	
	if(fp)
	{
  

		char line[256];
		memset(line, 0, sizeof(line));
		if(fgets(line, sizeof(line), fp) == NULL)
		{
			continue;
		}
		token = strtok(line, ",");
		while (token != NULL)
		{

		 
			vecTemp.vFishType.push_back(atoi(token));
			token = strtok(NULL, ",");
		}
		while(!feof(fp))
		{
			memset(line, 0, sizeof(line));
			if(fgets(line, sizeof(line), fp) == NULL)
				break;
			if ((strcmp(line, "\r\n") == 0) || (strcmp(line, "\n") == 0)) 
				continue;
			memset(&tempTrackPoint,0,sizeof(TrackPointDef));
			if(line[0] == '(')
			{
				token = strtok(line+1, ",");
				if(token != NULL)
				{			
				 
					tempTrackPoint.mPoint.x = atoi(token);				
					token = strtok(NULL, ",");
					if(token != NULL)
					{
						 
						tempTrackPoint.mPoint.y = atoi(token);
					}
					token = strtok(NULL, ",");
					if(token != NULL)
					{
						 
						tempTrackPoint.dAngleValue = atof(token);
					}
					token = strtok(NULL, ")");
					if(token != NULL)
					{
						 
						tempTrackPoint.iSpeFrame = atoi(token);
					}
				}
				vecTemp.vTrackPoint.push_back(tempTrackPoint);
			}
		}
		fclose(fp);
		if(vecTemp.vTrackPoint.size() > 0)
		{
			m_mapVcBigTrackPoint.insert(make_pair<int,VectorTrackInfo>((int&&)m_vcTrackID[i],(VectorTrackInfo&&)vecTemp));

		}
	} 
}

cocos2d::log("openefefefefefefend,,,,,,,,,,cool");



for(int i =0; i< 151; i++)
{
	m_vcSmallTrackID.push_back(SmallTrackIndex[i]);
}

for(int i = 0;i<m_vcSmallTrackID.size();i++)
{
	VectorTrackInfo vecTemp;
	TrackPointDef tempTrackPoint;
	 

	char cLujin [50] = {0};
	sprintf(cLujin,"track/small/%d.dat",m_vcSmallTrackID[i]); 
	string TrackLujin =FileUtils::getInstance()->getWritablePath()+cLujin;
	FILE *checkfp = fopen(TrackLujin.c_str(), "rb+"); 
	bool bHave = false;
	if(checkfp ==NULL)
	{

		ssize_t fZize ;
		unsigned char * DatBuf = NULL;  

		DatBuf =FileUtils::getInstance()->getFileDataFromZip(fullminizip,cLujin,&fZize);
		if(DatBuf == NULL)
		{
			cocos2d::log("Dont in mimizip small %d",m_vcSmallTrackID[i] );
			continue;
		}
		else
		{ 
			FILE *fp = fopen(TrackLujin.c_str(),"w+");  
			fwrite(DatBuf,sizeof(char), fZize,fp);
			fclose(fp);
			cocos2d::log("Writeok%s",TrackLujin.c_str());
		}

	}
	else
	{ 
		cocos2d::log("track have %d",m_vcSmallTrackID[i] );
		bHave = true;
	}

	FILE *fp;
	if(bHave = true)
	{
		fp = checkfp;
	}
	else
	{
		fp = fopen(TrackLujin.c_str(), "rb+"); 
	}
	 
	if(fp)
	{
		char line[256];
		memset(line, 0, sizeof(line));
		if(fgets(line, sizeof(line), fp) == NULL)
		{
			continue;
		}
		token = strtok(line, ",");
		while (token != NULL)
		{

			vecTemp.vFishType.push_back(atoi(token));
			token = strtok(NULL, ",");
		}
		while(!feof(fp))
		{
			memset(line, 0, sizeof(line));
			if(fgets(line, sizeof(line), fp) == NULL)
				break;
			if ((strcmp(line, "\r\n") == 0) || (strcmp(line, "\n") == 0)) 
				continue;
			memset(&tempTrackPoint,0,sizeof(TrackPointDef));
			if(line[0] == '(')
			{
				token = strtok(line+1, ",");
				if(token != NULL)
				{					
					tempTrackPoint.mPoint.x = atoi(token);				
					token = strtok(NULL, ",");
					if(token != NULL)
					{
						tempTrackPoint.mPoint.y = atoi(token);
					}
					token = strtok(NULL, ",");
					if(token != NULL)
					{
						tempTrackPoint.dAngleValue = atof(token);
					}
					token = strtok(NULL, ")");
					if(token != NULL)
					{
						tempTrackPoint.iSpeFrame = atoi(token);
					}
				}
				vecTemp.vTrackPoint.push_back(tempTrackPoint);
			}
		}
		fclose(fp);
		if(vecTemp.vTrackPoint.size() > 0)
		{
			m_mapVcSmallTrackPoint.insert(make_pair<int,VectorTrackInfo>((int&&)m_vcSmallTrackID[i],(VectorTrackInfo&&)vecTemp));
		}
	} 
}
*/
/*
pDir=opendir("track/special"); 
if(pDir)
{
	while((dirlist=readdir(pDir))!=NULL)   
	{
		sprintf(indir, "%s\\%s","track\\special",dirlist->d_name); 

		if(strstr(indir,".dat"))   
		{ 
			token = strtok(dirlist->d_name, ".");
			int iTrackID = atoi(token);
			m_vcSpeTrackID.push_back(iTrackID);
		} 
	}
}
closedir(pDir);

for(int i = 0;i<m_vcSpeTrackID.size();i++)
{
	VectorTrackInfo vecTemp;
	TrackPointDef tempTrackPoint;
	sprintf(szFile,"./track/special/%d.dat",m_vcSpeTrackID[i]);

	FILE *fp = fopen(szFile, "rb+");
	if(fp)
	{
		char line[256];
		memset(line, 0, sizeof(line));
		if(fgets(line, sizeof(line), fp) == NULL)
		{
			continue;
		}
		token = strtok(line, ",");
		while (token != NULL)
		{

			vecTemp.vFishType.push_back(atoi(token));
			token = strtok(NULL, ",");
		}
		while(!feof(fp))
		{
			memset(line, 0, sizeof(line));
			if(fgets(line, sizeof(line), fp) == NULL)
				break;
			if ((strcmp(line, "\r\n") == 0) || (strcmp(line, "\n") == 0)) 
				continue;
			memset(&tempTrackPoint,0,sizeof(TrackPointDef));
			if(line[0] == '(')
			{
				token = strtok(line+1, ",");
				if(token != NULL)
				{					
					tempTrackPoint.mPoint.x = atoi(token);				
					token = strtok(NULL, ",");
					if(token != NULL)
					{
						tempTrackPoint.mPoint.y = atoi(token);
					}
					token = strtok(NULL, ",");
					if(token != NULL)
					{
						tempTrackPoint.dAngleValue = atof(token);
					}
					token = strtok(NULL, ")");
					if(token != NULL)
					{
						tempTrackPoint.iSpeFrame = atoi(token);
					}
				}
				vecTemp.vTrackPoint.push_back(tempTrackPoint);
			}
		}
		fclose(fp);
		if(vecTemp.vTrackPoint.size() > 0)
		{
			m_mapVcSpeTrackPoint.insert(make_pair<int,VectorTrackInfo>((int&&)m_vcSpeTrackID[i],(VectorTrackInfo&&)vecTemp));
		}
	}
	else
	{
		printf("fopen error--[%s]\n",szFile);
	}
}


pDir=opendir("track/monster"); 
if(pDir)
{
	while((dirlist=readdir(pDir))!=NULL)   
	{
		sprintf(indir, "%s\\%s","track\\monster",dirlist->d_name); 

		if(strstr(indir,".dat"))   
		{ 
			token = strtok(dirlist->d_name, ".");
			int iTrackID = atoi(token);
			m_vcMonsterTrackID.push_back(iTrackID);
		} 
	}
}
closedir(pDir);

for(int i = 0;i<m_vcMonsterTrackID.size();i++)
{
	VectorTrackInfo vecTemp;
	TrackPointDef tempTrackPoint;
	sprintf(szFile,"./track/monster/%d.dat",m_vcMonsterTrackID[i]);

	FILE *fp = fopen(szFile, "rb+");
	if(fp)
	{
		char line[256];
		memset(line, 0, sizeof(line));
		if(fgets(line, sizeof(line), fp) == NULL)
		{
			continue;
		}
		token = strtok(line, ",");
		while (token != NULL)
		{

			vecTemp.vFishType.push_back(atoi(token));
			token = strtok(NULL, ",");
		}
		while(!feof(fp))
		{
			memset(line, 0, sizeof(line));
			if(fgets(line, sizeof(line), fp) == NULL)
				break;
			if ((strcmp(line, "\r\n") == 0) || (strcmp(line, "\n") == 0)) 
				continue;
			memset(&tempTrackPoint,0,sizeof(TrackPointDef));
			if(line[0] == '(')
			{
				token = strtok(line+1, ",");
				if(token != NULL)
				{					
					tempTrackPoint.mPoint.x = atoi(token);				
					token = strtok(NULL, ",");
					if(token != NULL)
					{
						tempTrackPoint.mPoint.y = atoi(token);
					}
					token = strtok(NULL, ",");
					if(token != NULL)
					{
						tempTrackPoint.dAngleValue = atof(token);
					}
					token = strtok(NULL, ")");
					if(token != NULL)
					{
						tempTrackPoint.iSpeFrame = atoi(token);
					}
				}
				vecTemp.vTrackPoint.push_back(tempTrackPoint);
			}
		}
		fclose(fp);
		if(vecTemp.vTrackPoint.size() > 0)
		{
			m_mapVcMonsterTrackPoint.insert(make_pair<int,VectorTrackInfo>((int&&)m_vcMonsterTrackID[i],(VectorTrackInfo&&)vecTemp));
		}
	}
	else
	{
		printf("fopen error--[%s]\n",szFile);
	}
}


pDir=opendir("track/grampus"); 
if(pDir)
{
	while((dirlist=readdir(pDir))!=NULL)   
	{
		sprintf(indir, "%s\\%s","track\\grampus",dirlist->d_name); 

		if(strstr(indir,".dat"))   
		{ 
			token = strtok(dirlist->d_name, ".");
			int iTrackID = atoi(token);
			m_vcGrampusTrackID.push_back(iTrackID);
		} 
	}
}
closedir(pDir);

for(int i = 0;i<m_vcGrampusTrackID.size();i++)
{
	VectorTrackInfo vecTemp;
	TrackPointDef tempTrackPoint;
	sprintf(szFile,"./track/grampus/%d.dat",m_vcGrampusTrackID[i]);

	FILE *fp = fopen(szFile, "rb+");
	if(fp)
	{
		char line[256];
		memset(line, 0, sizeof(line));
		if(fgets(line, sizeof(line), fp) == NULL)
		{
			continue;
		}
		token = strtok(line, ",");
		while (token != NULL)
		{

			vecTemp.vFishType.push_back(atoi(token));
			token = strtok(NULL, ",");
		}
		while(!feof(fp))
		{
			memset(line, 0, sizeof(line));
			if(fgets(line, sizeof(line), fp) == NULL)
				break;
			if ((strcmp(line, "\r\n") == 0) || (strcmp(line, "\n") == 0)) 
				continue;
			memset(&tempTrackPoint,0,sizeof(TrackPointDef));
			if(line[0] == '(')
			{
				token = strtok(line+1, ",");
				if(token != NULL)
				{					
					tempTrackPoint.mPoint.x = atoi(token);				
					token = strtok(NULL, ",");
					if(token != NULL)
					{
						tempTrackPoint.mPoint.y = atoi(token);
					}
					token = strtok(NULL, ",");
					if(token != NULL)
					{
						tempTrackPoint.dAngleValue = atof(token);
					}
					token = strtok(NULL, ")");
					if(token != NULL)
					{
						tempTrackPoint.iSpeFrame = atoi(token);
					}
				}
				vecTemp.vTrackPoint.push_back(tempTrackPoint);
			}
		}
		fclose(fp);
		if(vecTemp.vTrackPoint.size() > 0)
		{
			m_mapVcGrampusTrackPoint.insert(make_pair<int,VectorTrackInfo>((int&&)m_vcGrampusTrackID[i],(VectorTrackInfo&&)vecTemp));
		}
	}
	else
	{
		printf("fopen error--[%s]\n",szFile);
	}
}	*/
//#endif
	printf("----trackSize:big[%d],small[%d],spec[%d],monster[%d],grampus[%d]-----\n",m_mapVcBigTrackPoint.size(),m_mapVcSmallTrackPoint.size(),m_mapVcSpeTrackPoint.size(),m_mapVcMonsterTrackPoint.size(),m_mapVcGrampusTrackPoint.size());
	return;
}	

TrackPointDef* FishTrack::GetNextTrackPoint(bool bIni)
{
	if(m_trackType == TRACK_UNKNOW)
	{
		return NULL;
	}
	if(m_trackType == TRACK_BIG)
	{
		if((bIni == false || m_iNowTrackIndex == -1)&& bFanZhuan == false)
		{
			m_iNowTrackIndex++;	
		}
		else if(bFanZhuan ==true && bIni == false)
		{
			m_iNowTrackIndex--;	
		}
		if(m_iNowTrackIndex >= m_mapVcBigTrackPoint[m_iTrackID].vTrackPoint.size() ||m_iNowTrackIndex < 0)
		{
			return NULL;
		}
		return &(m_mapVcBigTrackPoint[m_iTrackID].vTrackPoint[m_iNowTrackIndex]);
	}
	if(m_trackType == TRACK_SMALL)
	{
		if((bIni == false || m_iNowTrackIndex == -1)&& bFanZhuan == false)
		{
			m_iNowTrackIndex++;	
		}
		else if(bFanZhuan == true && bIni == false)
		{
			m_iNowTrackIndex--;	
		}

		if(m_iNowTrackIndex >= m_mapVcSmallTrackPoint[m_iTrackID].vTrackPoint.size())
		{
			return NULL;
		}
		return &(m_mapVcSmallTrackPoint[m_iTrackID].vTrackPoint[m_iNowTrackIndex]);
	}
	if(m_trackType == TRACK_SPECIAL)
	{
		if(bIni == false || m_iNowTrackIndex == -1)
		{
			m_iNowTrackIndex++;	
		}
		if(m_iNowTrackIndex >= m_mapVcSpeTrackPoint[m_iTrackID].vTrackPoint.size())
		{
			return NULL;
		}
		return &(m_mapVcSpeTrackPoint[m_iTrackID].vTrackPoint[m_iNowTrackIndex]);
	}
	if(m_trackType == TRACK_MONSTER)
	{
		if(bIni == false || m_iNowTrackIndex == -1)
		{
			m_iNowTrackIndex++;	
		}
		if(m_iNowTrackIndex >= m_mapVcMonsterTrackPoint[m_iTrackID].vTrackPoint.size())
		{
			return NULL;
		}

		return &(m_mapVcMonsterTrackPoint[m_iTrackID].vTrackPoint[m_iNowTrackIndex]);
	}
	if(m_trackType == TRACK_GRAMPUS)
	{
		if(bIni == false || m_iNowTrackIndex == -1)
		{
			m_iNowTrackIndex++;	
		}
		if(m_iNowTrackIndex >= m_mapVcGrampusTrackPoint[m_iTrackID].vTrackPoint.size())
		{
			return NULL;
		}
		return &(m_mapVcGrampusTrackPoint[m_iTrackID].vTrackPoint[m_iNowTrackIndex]);
	}
	return NULL;
}


 
bool FishTrack::GetTrackInfoByID(int iTrackID,bool bBigFish,VectorTrackInfo &vecInfo)
{
	bool bFind = false;
	std::map<int,VectorTrackInfo>::iterator pos;
	if (bBigFish)
	{
		for (pos=m_mapVcBigTrackPoint.begin(); pos!=m_mapVcBigTrackPoint.end();pos++)
		{
			if(iTrackID == pos->first)
			{
				bFind = true;
				vecInfo = pos->second;
				break;
			}
		}
	}
	else
	{
		for (pos=m_mapVcSmallTrackPoint.begin(); pos!=m_mapVcSmallTrackPoint.end();pos++)
		{
			if(iTrackID == pos->first)
			{
				bFind = true;
				vecInfo = pos->second;
				break;
			}
		}
	}

	for (pos=m_mapVcSpeTrackPoint.begin(); pos!=m_mapVcSpeTrackPoint.end();pos++)
	{
		if(iTrackID == pos->first)
		{
			bFind = true;
			vecInfo = pos->second;
			break;
		}
	}

	for (pos=m_mapVcMonsterTrackPoint.begin(); pos!=m_mapVcMonsterTrackPoint.end();pos++)
	{
		if(iTrackID == pos->first)
		{
			bFind = true;
			vecInfo = pos->second;
			break;
		}
	}
	for (pos=m_mapVcGrampusTrackPoint.begin(); pos!=m_mapVcGrampusTrackPoint.end();pos++)
	{
		if(iTrackID == pos->first)
		{
			bFind = true;
			vecInfo = pos->second;
			break;
		}
	}

	return bFind;
}



void FishTrack::GetTrackIDByFishType( int iFishType, vector<int> &vTrackID )
{
	std::map<int,VectorTrackInfo>::iterator pos;
	vTrackID.clear();
	for (pos=m_mapVcBigTrackPoint.begin(); pos!=m_mapVcBigTrackPoint.end();pos++)
	{
		for (int i=0; i<pos->second.vFishType.size(); i++)
		{
			if (pos->second.vFishType[i] == iFishType)
			{
				vTrackID.push_back(pos->first);
				break;
			}
		}
	} 
	 
}


int  FishTrack::GetTrackIDByFishTaskType( int iFishType  )
{
	std::map<int,VectorTrackInfo>::iterator pos;
	  vector<int> vTrackID;
	for (pos=m_mapVcSpeTrackPoint.begin(); pos!=m_mapVcSpeTrackPoint.end();pos++)
	{
		for (int i=0; i<pos->second.vFishType.size(); i++)
		{
			if (pos->second.vFishType[i] == iFishType)
			{
				vTrackID.push_back(pos->first);
				break;
			}
		}
	} 

	if (vTrackID.size() == 0)
	{
		return -1;
	}
	else
	{
		int iRandTrackID;
		iRandTrackID = CCRANDOM_0_1()*vTrackID.size()-0.001;
		return vTrackID[iRandTrackID];
	}



}




void FishTrack::GetAllTrackIDByFishType( int iFishType, int iTrackType, vector<int> &vTrackID )
{
	std::map<int,VectorTrackInfo>::iterator pos;
	vTrackID.clear();
	if(iTrackType == 1)
	{
		for (pos=m_mapVcSmallTrackPoint.begin(); pos!=m_mapVcSmallTrackPoint.end();pos++)
		{
			for (int i=0; i<pos->second.vFishType.size(); i++)
			{
				if (pos->second.vFishType[i] == iFishType)
				{
					vTrackID.push_back(pos->first);
					break;
				}
			}
		}

	}
	else if(iTrackType == 2)
	{
		for (pos=m_mapVcBigTrackPoint.begin(); pos!=m_mapVcBigTrackPoint.end();pos++)
		{
			for (int i=0; i<pos->second.vFishType.size(); i++)
			{
				if (pos->second.vFishType[i] == iFishType)
				{
					vTrackID.push_back(pos->first);
					break;
				}
			}
		}
	}
	else if (iTrackType == 3)
	{
		for (pos=m_mapVcSpeTrackPoint.begin(); pos!=m_mapVcSpeTrackPoint.end();pos++)
		{
			for (int i=0; i<pos->second.vFishType.size(); i++)
			{
				if (pos->second.vFishType[i] == iFishType)
				{
					vTrackID.push_back(pos->first);
					break;
				}
			}
		}
	}
	else if (iTrackType == 4)
	{

		for (pos=m_mapVcMonsterTrackPoint.begin(); pos!=m_mapVcMonsterTrackPoint.end();pos++)
		{
			for (int i=0; i<pos->second.vFishType.size(); i++)
			{
				if (pos->second.vFishType[i] == iFishType)
				{
					vTrackID.push_back(pos->first);
					break;
				}
			}
		}
	}
	else if (iTrackType == 5)
	{
		for (pos=m_mapVcGrampusTrackPoint.begin(); pos!=m_mapVcGrampusTrackPoint.end();pos++)
		{
			for (int i=0; i<pos->second.vFishType.size(); i++)
			{
				if (pos->second.vFishType[i] == iFishType)
				{
					vTrackID.push_back(pos->first);
					break;
				}
			}
		}
	}
}




int FishTrack::GetRandGroupFishTrackID(vector<int> vcLimitTrackIDD)
{
	if (m_vcSmallTrackID.size() == 0)
	{
		return -1;
	}
	else
	{
		vector<int> vcTrackID;
		vcTrackID = m_vcSmallTrackID;

		int i,j;
		for (i=0; i<vcTrackID.size();)
		{
			for (j=0; j<vcLimitTrackIDD.size(); j++)
			{
				if (vcLimitTrackIDD[j] == vcTrackID[i])
				{
					vcTrackID.erase(vcTrackID.begin()+i);
					break;
				}
			}
			if (j == vcLimitTrackIDD.size())
			{
				i++;
			}
		}

		if (vcTrackID.size() == 0)
		{
			return -1;
		}
		else
		{
			int iRandTrackID;
			iRandTrackID = CCRANDOM_0_1()*vcTrackID.size()-0.001;
			return vcTrackID[iRandTrackID];
		}

 
	}
}


int FishTrack::GetRandMonsterTrackID()
{
	if (m_vcMonsterTrackID.size() == 0)
	{
		return -1;
	}
	else
	{
		int iRandTrackID;
		iRandTrackID = CCRANDOM_0_1()*m_vcMonsterTrackID.size()-0.001;
		return m_vcMonsterTrackID[iRandTrackID];
	}
}

int FishTrack::GetRandGrampusTrackID()
{
	if (m_vcGrampusTrackID.size() == 0)
	{
		return -1;
	}
	else
	{
		int iRandTrackID;
		iRandTrackID = CCRANDOM_0_1()*m_vcGrampusTrackID.size()-0.001;
		return m_vcGrampusTrackID[iRandTrackID];
	}
}


int FishTrack::GetRandTrackID( int iFishType )
{
	vector<int> vTrackID;
	GetTrackIDByFishType(iFishType, vTrackID);
	
	 
	if (vTrackID.size() == 0)
	{
		return -1;
	}
	else
	{
		int iRandTrackID;
		iRandTrackID = CCRANDOM_0_1()*vTrackID.size()-0.001;
		return vTrackID[iRandTrackID];
	}
}


int FishTrack::GetTrackPointSize()
{
	if(m_trackType == TRACK_UNKNOW)
	{
		return 0;
	}
	if(m_trackType == TRACK_BIG)
	{		
		return m_mapVcBigTrackPoint[m_iTrackID].vTrackPoint.size();		
	}
	if(m_trackType == TRACK_SMALL)
	{	
		return m_mapVcSmallTrackPoint[m_iTrackID].vTrackPoint.size();
	}
	if(m_trackType == TRACK_SPECIAL)
	{
		return m_mapVcSpeTrackPoint[m_iTrackID].vTrackPoint.size();
	}
	if(m_trackType == TRACK_MONSTER)
	{
		return m_mapVcMonsterTrackPoint[m_iTrackID].vTrackPoint.size();
	}
	if(m_trackType == TRACK_GRAMPUS)
	{
		return m_mapVcGrampusTrackPoint[m_iTrackID].vTrackPoint.size();
	}
	return 0;	
}