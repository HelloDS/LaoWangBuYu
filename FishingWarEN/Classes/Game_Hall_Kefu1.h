#ifndef _GAME_HUAFEI_H
#define _GAME_HUAFEI_H
 
#include "cocos2d.h"
#include "cocos-ext.h"
#include "LogoLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

//��ȡ����ȯ
class Game_Hall_Kefu3: public cocos2d::Layer , public ScrollViewDelegate
{
public:
    static cocos2d::Scene * createScene();
    virtual bool init();
    void exit();									//�˳�
    
    virtual void scrollViewDidScroll(ScrollView * view);
    virtual void scrollViewDidZoom(ScrollView * view);
    
    bool onTouchBegan(Touch * touch,Event * event);
    void onTouchMoved(Touch * touch,Event * event);
    void onTouchEnded(Touch * touch,Event * event);
    
    void duiHuaFei(int room);
    void huodeHF(Ref * psender);
    
    void tanchuVip(Ref * psender);
    CREATE_FUNC(Game_Hall_Kefu3);
    
    
private:
    Scale9Sprite * shopCenterBg;
    
    Size visibleSize;
    Size winSize;
    
    ScrollView * yubiView;							//������
    Layer * yubiLayer;								//�����ʯ��
    Vector <Sprite *> sp_yubi;				//�����ʯ����
    
    int cur_room;
    Point p1;
    Point p2;
    float layer_x;
    Size roomSize;
};
#endif
