#ifndef __FISH_RAND_SWATCH__
#define __FISH_RAND_SWATCH__


#include <vector>
#include <map>
 
using namespace std;

const int g_iMaxSwatchFishID = 100000;
const int RandSwatchIndex[5] = {1,2,3,4,5,};
typedef struct FishInSwatch   //随机样本内鱼信息
{
	int iFishType;//鱼类型(0-7单鱼,100鱼群)
	int iActFrame;//第几帧出现(从第一帧算起,第0帧不会产生鱼)
	int iTrackOrScriptID;//轨迹或脚本ID(为0表示自由生成的鱼,>0时会根据iFishType决定是轨迹还是脚本ID)
	int iExistFramesOrTrack;//自由鱼总共存在多少帧(鱼群时表示鱼群所走轨迹ID)
}FishInSwatchDef;
typedef vector<FishInSwatchDef> vcFishInSwatch;
class FishRandSwatch		
{
public:
	FishRandSwatch();
	~FishRandSwatch(void);

	void Reset();
	void update(bool bNeedCraeteFish,vcFishInSwatch &vcNeedCreateFish);//根据bNeedCraeteFish,决定是否获取vcNeedCreateFish

	static FishInSwatchDef* JudgeIfHaveFish(int iSwatchID,int iFishMainID);
	static int  GetOneRandSwatchID();
	static void LoadAllRandSwatchData();	
	static void ClearAllRandSwatchData();
	static void WriteRandSwatchData(
		int iFishType,//鱼类型(0-7单鱼,100鱼群)
		int iActFrame,//第几帧出现(从第一帧算起,第0帧不会产生鱼)
		int iTrackOrScriptID,//轨迹或脚本ID(为0表示自由生成的鱼,>0时会根据iFishType决定是轨迹还是脚本ID)
		int iExistFrames = 0//自由鱼总共存在多少帧
		);
private:
	int m_iNowFrmameIndex;
	int m_iNowSwatchID;
	int m_ivcIndexInSwatch;

	static map<int,vcFishInSwatch>m_mapVCFishInSwatch;

	static void ParseFishRandSwatchFile();
	static void GetAllFishRandSwatchInfoNomal();//正常读取鱼群信息
};

#endif