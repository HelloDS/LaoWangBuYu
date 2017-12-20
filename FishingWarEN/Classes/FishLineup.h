#ifndef __FISH_LINEUP_H__
#define __FISH_LINEUP_H__
#include "cocos2d.h"
USING_NS_CC;

#include <vector>
#include <map>

using namespace std;
 
	  
	typedef struct FishInLineup
	{
		int iScriptID;  //�ű�ID
		int iActFrame;  //�ڼ�֡����,�������Ⱥ��������ֵĿ�ʼ֡,�������iStartFrame
	}FishInLineupDef;



	typedef struct LineupInfo
	{
		int iStartFrame;
		int iEndFrame;
		vector<FishInLineupDef> vcFishLineup;
	}LineupInfoDef; 
	 
	class FishLineup		   //ĳ�ؿ������й̶�������
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