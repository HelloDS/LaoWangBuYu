 #ifndef _ZUANPAN_
#define _ZUANPAN_ 
#include "cocos2d.h"

USING_NS_CC;  
class ZuanPan: public cocos2d::Layer
{
public:
	static ZuanPan* create(int roomNum);

	virtual bool init( int roomNum );

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 

	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);

	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 

	void exit(float dt);
	//CREATE_FUNC(Gongxi);
	void beginZ(Ref* pSender);
    
    void beginmatchover(Ref* pSender);

	
private:
	Sprite * zuanpan; //���̾���
	Label * jinbiNum;//��ý������
	Label * zuanshiNum;//�����ʯ����
	MenuItemSprite * beginItem;//��ʼ��ť

	int zuanpanNum[8]; //ת���ϵ�����
	bool isZuanDong; //ת���Ƿ���ת��
	void update(float dt);
	float zpJiaoDu; //ת��ת�ĽǶ�
	float zptmp; //ת��ÿ֡ת�ĽǶ�
	float zpZongDu; //ת��ת���ܽǶ�
	bool isjiasu; //�Ƿ����ת����
	int jiasuZhen;//���ٵ�֡��
	int maxJiaSuZhen;//�����ٵ�֡��

	int jiangliNum; //��ý�����ֵ
	int roomBeilv; //����ϵ��
	bool isJinbi; //��õ��ǽ�ң�

	int xuhao; //��ǰ��ý��������
	Size visibleSize;		
};

#endif
