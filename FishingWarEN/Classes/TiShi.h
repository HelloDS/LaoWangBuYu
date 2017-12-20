 #ifndef __TISHI__
#define __TISHI__ 
#include "cocos2d.h"

USING_NS_CC;  
  
class TiShi: public cocos2d::Node
{
public:
	static TiShi* create(int btnKind,std::string word,std::string wordtwo,int time,int GuanKaNum,bool ShouDong = false);//参数：1、提示框类型[1、2]①上点下框②上框下点//2、提示内容(***/n***,*****)有两行。//		3、要显示的时间
																
														

	virtual bool init(int btnKind,std::string word,std::string wordtwo,int time,int GuanKaNum,bool ShouDong);

	void tishiCD(float fdelta);
	void exit();

	void yuyue();
	//CREATE_FUNC(Gongxi);
	Size visibleSize;		
private:
	int tishiTime;
	bool bShouDong;

};

#endif
