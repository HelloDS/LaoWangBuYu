 #ifndef __TISHI__
#define __TISHI__ 
#include "cocos2d.h"

USING_NS_CC;  
  
class TiShi: public cocos2d::Node
{
public:
	static TiShi* create(int btnKind,std::string word,std::string wordtwo,int time,int GuanKaNum,bool ShouDong = false);//������1����ʾ������[1��2]���ϵ��¿���Ͽ��µ�//2����ʾ����(***/n***,*****)�����С�//		3��Ҫ��ʾ��ʱ��
																
														

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
