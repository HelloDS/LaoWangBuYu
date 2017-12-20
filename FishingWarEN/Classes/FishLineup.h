#ifndef __FISH_LINEUP_H__
#define __FISH_LINEUP_H__
#include "cocos2d.h"
USING_NS_CC;

#include <vector>
#include <map>

using namespace std;
 
	  
	typedef struct FishInLineup
	{
		int iScriptID;  //脚本ID
		int iActFrame;  //第几帧出现,相对于这群阵型鱼出现的开始帧,即下面的iStartFrame
	}FishInLineupDef;



	typedef struct LineupInfo
	{
		int iStartFrame;
		int iEndFrame;
		vector<FishInLineupDef> vcFishLineup;
	}LineupInfoDef; 
	 
	class FishLineup		   //某关卡内所有固定阵列鱼
	{
	public:
		FishLineup();
		~FishLineup(void);

		void Reset(int iLineupID,int iNowActFrame);
		bool Update(vector<int> &ooo);

		static int GetOneRandFixedLineupID();
		static void LoadAllFishLieupData();		
	private:
		int m_iNowFrmameIndex;
		int m_iNowLineupID; 
		static map<int,LineupInfoDef>m_mapVCFishInLineup;
	}; 

#endif