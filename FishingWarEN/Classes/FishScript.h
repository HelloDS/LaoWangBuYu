#ifndef __FISH_SCRIPT__
#define __FISH_SCRIPT__

#include <vector>
#include <map>

using namespace std;
 
const int ScriptIndex[285] = {4000,4001,4002,4003,4004,4010,4011,4012,4013,4014,4015,4016,4030,4031,4032,4040,4041,4042,4043,4050,4051,4052,4070,4071,4073
,4080,4081,4090,4091,4092,4093,4094,4095,4096,4100,4101,4102,4103,4104,4105,4110,4111,4112,4113,4114,4115,4120,4121,4122,4123,4130,4131,4132,4133,4134,4135,4140,4141,4142,4143,4150
,4151,4152,4153,4160,4161,4162,4163,4170,4173,4174,4175,4176,4180,4181,4182,4183,4184,4185,4186,4187,4189,4200,4201,4202,4210,4211,4212,4213,4214,4215,4216,4220,4221,4222,4223,4224,4225
,4230,4231,4232,4233,4234,4235,4236,4237,4240,4241,4242,4243,4244,4245,4246,4250,4251,4252,4260,4261,4262,4263,4264,4265,4270,4271,4272,4273,4274,4275,4276,4277,4278,4280,4281,4282,4283
,4284,4290,4291,4292,4293,4294,4295,4296,4297,4298,4301,4302,4303,4304,5000,5001,5002,5003,5004,5005,5006,5007,5008,5009,5010,5011,5012,5013,5014,5015,5016,5017,5018,5019,5020,5021,5022
,5023,5024,5025,5026,5027,5028,5029,5030,5031,5032,5033,5034,5035,5036,5037,5038,5039,5040,5041,5042,5043,5044,5045,5046,5047,5048,5049,5050,5051,5052,5053,5054,5055,5056,5057,5058,5059,5060,5061,5062
,5063,5064,5065,5066,5067,5068,5069,5070,5071,5072,5073,5074,5075,5076,5077,5078,5079,5080,5081,5082,5083,5084,5085,5086,5087,5088,5089,5090,5091,5092,5093,5094,5095,5096,5097,5098,5099,5100,5101,5102
,5103,5104,5105,5106,5107,5108,5109,5110,5111,5112,5113,5114,5115,5116,5117,5118,5119,5120,5121,5122,5123,5124,5125,5126,5127,5128,5129,5130,5131,5132,5133,5134,5135};
 
/*
const int ScriptIndex[284] = {
	1,2,3,4,5,6,7,8,
	11,12,13,14,15,16,17,18,
	21,22,23,24,25,26,27,28,31,32,33,34,35,36,37,38,41,42,43,44,45,46,47,48,51,52,53,54,55,56,57,58,61,62,63,64,65,66,67,68,71,72,73,74,75,76,77,78,81,82,83,84,85,86,87,
	88,91,92,93,94,95,96,97,98,101,102,103,104,105,106,107,108,111,112,113,114,115,116,117,118,121,122,123,124,125,126,127,128,131,132,133,134,135,136,137,138,141,142,143,144,145,146,147,148,
	800,801,848,849,850,851,852,853,854,855,856,857,
	1001,1002,1003,1004,1005,1006,1007,1008,1009,1010,1011,1012,1013,1014,1015,1016,1017,1018,1019,1020,1021,1022,1023,1024,1025,1026,1027,1028,1029,1030,
	1113,1201,1202,1203,1204,1205,1206,
	7002,7004,7005,7006,7007,7009,7011,7012,7013,7014,
	9696,11105,11106,11107,11108,11109,11110,11111,11112,
	20000,20001,20002,20004,20005,20007,20008,20009,20010,
	30000,30001,30002,30005,30006,30007,30008,30009,30010,30011,30012,30013,30014,30015,30016,30017,30018,30019,30020,30021,30022,30023,30024,30025,30026,30027,30028,
	30029,30030,30031,30032,30033,30034,30035,30036,30037,30040,30044,30049,30050,30051,30052,30055,30056,30057,30058,30059,30060,30061,30062,30063,30064,30065,30066,
	30067,30068,30070,30071,30072,30073,30074,30075,30076,30077,30078,30079,30080,30081,30082,30083,30084,30085,30086,30087,30088,30089,30090,
	51001,51002,51003,51004,51005,51006,51007,51008,51009,51010
};*/
typedef struct ScriptFrame
{
	bool bBigFish;		//是否为大鱼
	int iActFrameIndex;	//第几帧生效	
	int iTrackID;		//对应生效的轨迹
	int iFishType;		//鱼类型
	int iX;				//相对轨迹的X轴偏移量
	int iY;				//相对轨迹的Y轴偏移量
}ScriptFrameDef;



typedef vector<ScriptFrameDef> VectorScriptFrame;

typedef struct RandScriptInfo
{
	int iScriptID;
	int iFishType;

}RandScriptInfoDef;

class FishScript		//关卡脚本管理类，主要用于控制按规则产生多个轨迹鱼以组成一个关卡效果
{
public:
	FishScript(int iScriptID = 0);
	~FishScript(void);


	VectorScriptFrame GetAllFrameBeforeIndex(int iFrameIndex); 
	void GetNextFrame(VectorScriptFrame &vecScript);	//获得下一帧，需要外部每帧都调用
	bool IfScriptOver();				//是否脚本播放完毕
	int  GetLastFrame();				//返回总帧数
	void Reset(int iScriptID,int iNowFrameIndex = 0);			//重置脚本
	int  GetNowFrameIndex();			//返回当前运行的帧数
	int  GetScriptID(){return m_iScriptID;}
	int  GetScriptType(){return m_iScriptType;}//脚本类型 (0为固定阵型脚本 1为单类型鱼脚本 2为多类型鱼脚本)

	static int  GetRandGroupFishScript(int iFishType,int &iTrackID , const vector<int> &vNoRandTrackID); //随机取得指定鱼的脚本ID和轨迹ID
	static void SetOneScript(int iScriptID,VectorScriptFrame vecInfo);
	static bool GetScriptInfoByID(int iScriptID,VectorScriptFrame &vecInfo);
	static void LoadAllScriptData();//一次读取所有的脚本文件信息
	static void ClearAllScriptData();
	static void AddOneScriptToMap(int iScriptID,VectorScriptFrame vecInfo);
	static bool IsScriptID(int iScriptID);
	static int  GetLastFrameNum(int iScriptID);
	static int  GetRandFishScript(); //随机取得的脚本ID(出错返回-1)
	static int  GetFishTypeByScriptID(int iScriptID);//根据单类型鱼脚本ID 获取鱼类型
	

	static vector<int> m_vcScriptID;

	VectorScriptFrame initScriptVec(int trackID);//初始化一个.dat文件的内容
	

private:
	int m_iNowFrameIndex;		//当前脚本的运行帧

	int m_iNowActIndex;			//当前执行的实际脚本帧

	static map<int,VectorScriptFrame> m_mapVcScriptFrame;//向量的map，就是二维数组了，静态的一次性加载所有脚本信息，因为后面都是只读的多线程操作，都不需要考虑线程冲突了

	static vector<RandScriptInfoDef>	m_vecRandScriptID;	//可以随机生成的脚本ID(单类型鱼)

	static vector<RandScriptInfoDef>	m_vecRandScriptID2;	//可以随机生成的脚本ID(多类型鱼)

	int m_iScriptID;
	int m_iScriptType;

	static void ParseFishScriptFile();
	static void GetAllScriptInfoNomal();//正常读取鱼群信息
};
 
#endif