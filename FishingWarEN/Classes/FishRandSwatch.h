#ifndef __FISH_RAND_SWATCH__
#define __FISH_RAND_SWATCH__


#include <vector>
#include <map>
 
using namespace std;

const int g_iMaxSwatchFishID = 100000;
const int RandSwatchIndex[5] = {1,2,3,4,5,};
typedef struct FishInSwatch   //�������������Ϣ
{
	int iFishType;//������(0-7����,100��Ⱥ)
	int iActFrame;//�ڼ�֡����(�ӵ�һ֡����,��0֡���������)
	int iTrackOrScriptID;//�켣��ű�ID(Ϊ0��ʾ�������ɵ���,>0ʱ�����iFishType�����ǹ켣���ǽű�ID)
	int iExistFramesOrTrack;//�������ܹ����ڶ���֡(��Ⱥʱ��ʾ��Ⱥ���߹켣ID)
}FishInSwatchDef;
typedef vector<FishInSwatchDef> vcFishInSwatch;
class FishRandSwatch		
{
public:
	FishRandSwatch();
	~FishRandSwatch(void);

	void Reset();
	void update(bool bNeedCraeteFish,vcFishInSwatch &vcNeedCreateFish);//����bNeedCraeteFish,�����Ƿ��ȡvcNeedCreateFish

	static FishInSwatchDef* JudgeIfHaveFish(int iSwatchID,int iFishMainID);
	static int  GetOneRandSwatchID();
	static void LoadAllRandSwatchData();	
	static void ClearAllRandSwatchData();
	static void WriteRandSwatchData(
		int iFishType,//������(0-7����,100��Ⱥ)
		int iActFrame,//�ڼ�֡����(�ӵ�һ֡����,��0֡���������)
		int iTrackOrScriptID,//�켣��ű�ID(Ϊ0��ʾ�������ɵ���,>0ʱ�����iFishType�����ǹ켣���ǽű�ID)
		int iExistFrames = 0//�������ܹ����ڶ���֡
		);
private:
	int m_iNowFrmameIndex;
	int m_iNowSwatchID;
	int m_ivcIndexInSwatch;

	static map<int,vcFishInSwatch>m_mapVCFishInSwatch;

	static void ParseFishRandSwatchFile();
	static void GetAllFishRandSwatchInfoNomal();//������ȡ��Ⱥ��Ϣ
};

#endif