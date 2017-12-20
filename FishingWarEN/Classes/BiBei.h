#ifndef _BIBEI_H_
#define _BIBEI_H_

#include"cocos2d.h" 

USING_NS_CC;
using namespace std;
  
class BiBei : public cocos2d::Layer
{
public:
	 
	static BiBei* create(int PaoMoney);

	virtual bool init(int PaoMoney); 
	 
private:
	  
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event);  
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 


	
	Menu* m_ChaCha;
	Menu* m_ChooseBig;
	Menu* m_ChooseSmall;

	void MoveEnd();

	Sprite * m_pChouMa;
	Sprite * m_pGuang;

	int iBiBeiMoney;
	Point ChouMaPos[3];
	Point GuangPos[2];
	int bibeiTime;
	char cPos;

	char m_cNowTime;
	char m_cTime;
	Sprite * m_pNum[3];
	Label * MoneyLabel;

	int MoveTime;
	int bibeiTimeTwo;

	bool bMoverOver;
	int OverTimeNum;

	char cChooseTime;
	char cChoose;
	void updateBiBei(float delat);
	void menuCha(Ref* pSender);
	void menuBig(Ref* pSender);
	void menuSmall(Ref* pSender);

	void ShowKuangOne();
	void ShowKuangTwo();
};

#endif

