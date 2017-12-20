 #ifndef _GONGGAO_
#define _GONGGAO_
#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocos\ui\UIRichText.h"

USING_NS_CC;
USING_NS_CC_EXT; 
using namespace ui;
class Gonggao: public cocos2d::Node
{
public:
	static Gonggao * create(int i);   //1、比赛名词公告 2、话费兑换公告 3、购买VIP公告
	virtual bool init(int j);
private:
	//任务相关
	ui::RichText * game_label;
    int iType;
};

#endif
