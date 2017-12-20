
#ifndef __FishingJoy__Weapon__
#define __FishingJoy__Weapon__
#include "cocos2d.h"
#include "Cannon.h"
#include "Bullet.h"
#include "FishingNet.h"
#include "CoinAndAni.h"
#include <vector>
using namespace std;


USING_NS_CC;

class Weapon : public cocos2d::CCNode
{
public:
    static Weapon* create(unsigned char type);
    bool init(unsigned char type);
    
    //控制函数
    bool shootTo(cocos2d::Point touchLocation,char cbulletType );
    bool RobotshootTo(cocos2d::Point touchLocation,char cbulletType ,char cRobotPos, char cRobotBeishu );
    Bullet* bullet;
    ~Weapon(void);
    void end(int Pos ,char cNetType,char cRobotPos = 0 );
    void netEndFanWei(char cNetType);
    void OnWall(Bullet * pTempBullet,unsigned char ucWallState,bool bFanZhuan);
    
    /*CC_SYNTHESIZE_READONLY(cocos2d::Vector<Bullet*>, m_Bullet, Bullet);
     CC_SYNTHESIZE_READONLY(cocos2d::Vector<Bullet*>, m_Bullet2, Bullet2);
     CC_SYNTHESIZE_READONLY(cocos2d::Vector<Bullet*>, m_Bullet3, Bullet3);
     CC_SYNTHESIZE_READONLY(cocos2d::Vector<Bullet*>, m_Bullet1, Bullet1);
     CC_SYNTHESIZE_READONLY(cocos2d::Vector<Bullet*>, m_Bullet0, Bullet0);
     */
    void CreateBullet(unsigned char type ,char myBeiShu,char cRobotPos);
    
    vector<Bullet*> m_Bullet[5];
    
    
    void updateWeapon(float dt);
protected:
    //通过ParticleDesigner加载的粒子效果
    ParticleSystemQuad* m_Particle;
    Sprite * bullet_texiao;
    Animate *yw_texiao_animate;
    
    
    ParticleSystemQuad* m_ParticleFanWei3;
    ParticleSystemQuad* m_ParticleFanWei3two;
    ParticleSystemQuad* m_ParticleFanWei1;
    ParticleSystemQuad* m_ParticleFanWei2;
    
    cocos2d::CCParticleSystemQuad* m_ParticleFanWei22;
    
    float distance ;
    Sprite*  _fishingNetSprite;
    bool bShowFanWeiThreePar;
    
};

#endif /* defined(__FishingJoy__Weapon__) */
