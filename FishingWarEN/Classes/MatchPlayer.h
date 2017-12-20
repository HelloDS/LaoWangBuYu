 #ifndef _MATCHPLAYER_
#define _MATCHPLAYER_
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC; 
USING_NS_CC_EXT;
const float MatchTimeTotal = 4;
const int MatchTouxiang = 8;
class MatchPlayer: public cocos2d::Layer
{
public:
	static Scene * createScene( );
	CREATE_FUNC(MatchPlayer);
	virtual bool init();
 
	bool onTouchBegan(Touch * touch,Event * event);
	void onTouchMoved(Touch * touch,Event * event);
	void onTouchEnded(Touch * touch,Event * event);

	void update(float dt);
	void updatePao(float dt);

	void init_shuzhi();  //初始化数值
	void exit();		//退出函数
	void init_robot(int i); //初始化机器人

	void tx_jiansu(int i);			//机器人减速过程
	void tx_restart(int i);    //机器人摆正位置
	void jinru_bs(float dt);	//进入比赛					
private:
	Size visibleSize;
	char MP_tmpchar[50];

	Scale9Sprite * controlBg ;	//背景
	Sprite * MP_paomadeng;		//跑马灯
	Label * RS_label;			//人数label
	float MP_renshu_sl;			//人数标签的增加速率
	float MP_renshu_tmp;			//人数标签的增加tmp
	float MP_renshu_sl_total;	//人数标签总数
	int init_renshu_num;		//初始化进来的房间人数

	float MP_time_num[3];			//匹配时长
	float MP_jiantou_jd;		//箭头偏离角度
 
	Vector <Sprite *> match_jiantou;	//箭头精灵
	Vector <Sprite *> match_huohua;		//箭头火花精灵
	Vector <Sprite *> match_tx_tiao;	//头像匹配长条精灵
	Vector <Sprite *> match_mc_tiao;	//名称匹配长条精灵

	bool is_jiansu_flag[3];	//是否开始减速
	//头像减速过程
	float tx_v1[3];		//初速度
	float tx_a[3];			//减速度
	float tx_lucheng[3];	//总路程
	//名称减速过程
	float mc_v1[3];		//初速度
	float mc_a[3];			//减速度
	float mc_lucheng[3];	//总路程
};

#endif
