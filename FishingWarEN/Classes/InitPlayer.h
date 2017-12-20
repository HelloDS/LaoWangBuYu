 #ifndef _INITPLAYER_
#define _INITPLAYER_
#include "cocos2d.h"
#include "Waiting.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;
class InitPlayer: public cocos2d::Layer,public EditBoxDelegate
{
public:
    //******20151026 by jyw
    void bind_acount();
    void bind_identyfy(Ref* pSender);
    void bind_cancel();
    void bind_queding();
    
    void bind_update_iden(float dt);
    int iden_time;
    
    static size_t bind_poss(uint8_t *buffer,size_t size,size_t nmemb,void *stream);
    void bind_success();//绑定成功
    void bind_fail(); //绑定失败
    Menu * bing_item;
    //******end
	static Scene * createScene();
	CREATE_FUNC(InitPlayer);
	virtual void editBoxReturn(EditBox *editBox);
	virtual bool init();
 
	bool onTouchBegan(Touch * touch,Event * event);
	void onTouchMoved(Touch * touch,Event * event);
	void onTouchEnded(Touch * touch,Event * event);
 
	void exit();		//退出函数
	void suijiName(Ref * pSender);   //随机一个名字
	void xz_touxiang(Ref * pSender);		//选择头像
    
    void update(float dt);
	void jinzhi(float dt);   //开启头像触摸
    CCSize visibleSize;
    static char cCheckMaOk;
    void QueDingOver();
private:

	char IP_tmpchar[100];
	int cur_tx_index;   //当前所选头像的序号
	EditBox * hall_name_bg; //输入框

	Scale9Sprite * controlBg ;	//背景

	Sprite * ip_xingxing;		//星星
	Sprite * ip_heigai;			//头像黑盖

	Sprite * ip_datouxiang;		//大头像1	
	Sprite * ip_datouxiang2;	//大头像2	

	bool ip_dianguo;   //是否切换过
	bool is_moving;		//头像是否正在移动

    
	Vector <Sprite *> touxiang_sp;		//小头像容器
 
 
};

#endif
