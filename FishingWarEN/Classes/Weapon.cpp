
#include "Weapon.h"
#include "StaticData.h"
#include <vector>
#include "CannonLayer.h"
#include "GameScene.h"


using namespace std;


USING_NS_CC;
Weapon* Weapon::create(unsigned char type)
{
    Weapon* weapon = new Weapon();
    weapon->init(type);
    weapon->autorelease();
    return weapon;
}
bool Weapon::init(unsigned char type)
{
    cocos2d::log("wapon init start");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    
    distance = 22;
    
    m_ParticleFanWei1 = ParticleSystemQuad::create("particlefanwei1.plist");
    m_ParticleFanWei1->stopSystem();
    this->addChild(m_ParticleFanWei1);
    
    m_ParticleFanWei2 = ParticleSystemQuad::create( "particlefanwei2.plist");
    m_ParticleFanWei2->stopSystem();
    this->addChild(m_ParticleFanWei2);
    
    m_ParticleFanWei22 = ParticleSystemQuad::create( "fanwei02.plist");
    m_ParticleFanWei22->stopSystem();
    this->addChild(m_ParticleFanWei22);
    
    _fishingNetSprite = Sprite::createWithSpriteFrameName("net_4.png");
    _fishingNetSprite->setPosition(Point(-300,-300));
    this->addChild(_fishingNetSprite);
    
    
    m_ParticleFanWei3two = ParticleSystemQuad::create("oooo.plist");
    m_ParticleFanWei3two->retain();
    auto batch2 = ParticleBatchNode::createWithTexture(m_ParticleFanWei3two->getTexture());
    batch2->addChild(m_ParticleFanWei3two);
    m_ParticleFanWei3two->stopSystem();
    addChild(batch2);
    
    
    m_ParticleFanWei3 = ParticleSystemQuad::create("particlefanwei3.plist");
    m_ParticleFanWei3->retain();
    m_ParticleFanWei3->stopSystem();
    auto batch1 = ParticleBatchNode::createWithTexture(m_ParticleFanWei3->getTexture());
    batch1->addChild(m_ParticleFanWei3);
    addChild(batch1);
    
    
    //m_Particle = ParticleSystemQuad::create("bullet.plist");
    //m_Particle->retain();
    //auto batch = ParticleBatchNode::createWithTexture(m_Particle->getTexture());
    //batch->addChild(m_Particle);
    //addChild(batch);
    
    
    cocos2d::log("weapon init end");
    
    //schedule(schedule_selector(Weapon::updateWeapon),0.01f);
    return true;
}

Weapon::~Weapon(void)
{
    //CC_SAFE_RELEASE(m_Particle);
    CC_SAFE_RELEASE(m_ParticleFanWei3two);
    CC_SAFE_RELEASE(m_ParticleFanWei3);
}

void Weapon::updateWeapon(float dt)
{
    //cocos2d::log("scene init updateWeapon1");
    
    for(int i=0; i< 5; i++)
    {
        if(!m_Bullet[i].empty())
        {
            for(int j=0; j< m_Bullet[i].size(); j++)
            {
                
                //isRunnning判断fish是否已经在屏幕上显示
                if(m_Bullet[i][j]->isRunning())
                {
                    m_Bullet[i][j]->MoveBullet();
                }
            }
            
        }
    }
    //cocos2d::log("scene init updateWeapon2");
    
}
void Weapon::CreateBullet(unsigned char type ,char myBeiShu,char cRobotPos)
{
    
}
bool Weapon::shootTo(Point touchLocation ,char cbulletType )
{
    
    //激光25
    bullet = Bullet::create( cbulletType,CannonLayer::_type,4);
    m_Bullet[4].push_back(bullet);
    this->addChild(bullet,100);
    Size winSize = Director::getInstance()->getWinSize();
    
    bullet->setBeginPos(bullet->getPosition());
    
    
    if(cbulletType > 19 && cbulletType< 25)
    {
        
        bullet->setEndPos(touchLocation);
        
    }
    
    Point normal = ccpNormalize(ccpSub(touchLocation ,bullet->getPosition()));
    Point target = ccpMult(normal, distance);
    
    Point location;
    if(GameScene::cGameType == 1)
    {
        
        if(GameScene::cSelfPos == 0)
        {
            location= Point(CannonLayer::robotPos1,50);
        }
        else
        {
            location= Point(CannonLayer::robotPos2,50);
        }
    }
    else
    {
        location= Point(winSize.width*0.5f,50);
    }
    
    
    float angle = CC_RADIANS_TO_DEGREES(ccpAngleSigned(ccpSub(touchLocation, location), Point(0, 1)));
    
    bullet->setRotation(angle);
    bullet->flyTo(target);
    return true;
    
}

bool Weapon::RobotshootTo(Point touchLocation ,char cbulletType ,char cRobotPos, char cRobotBeishu )
{
    //激光25
    bullet = Bullet::create( cbulletType,cRobotBeishu,cRobotPos);
    
    
    m_Bullet[cRobotPos ].push_back(bullet);
    
    
    this->addChild(bullet,100);
    Size winSize = Director::getInstance()->getWinSize();
    
    bullet->setBeginPos(bullet->getPosition());
    if(cbulletType > 19 && cbulletType< 25)
    {
        bullet->setEndPos(touchLocation);
    }
    
    Point normal = ccpNormalize(ccpSub(touchLocation ,bullet->getPosition()));
    Point target = ccpMult(normal, distance);
    
    if(cRobotPos == 0)
    {
        Point location = Point(CannonLayer::robotPos1,50);
        float angle = CC_RADIANS_TO_DEGREES(ccpAngleSigned(ccpSub(touchLocation, location), Point(0, 1)));
        
        bullet->setRotation(angle);
        bullet->flyTo(target);
    }
    else if(cRobotPos == 1)
    {
        Point location = Point(CannonLayer::robotPos2,50);
        float angle = CC_RADIANS_TO_DEGREES(ccpAngleSigned(ccpSub(touchLocation, location), Point(0, 1)));
        
        bullet->setRotation(angle);
        bullet->flyTo(target);
        
    }
    else if(cRobotPos == 2)
    {
        Point location = Point(CannonLayer::robotPos1,winSize.height-50);
        float angle = CC_RADIANS_TO_DEGREES(ccpAngleSigned(ccpSub(touchLocation, location), Point(0, -1)));
        
        bullet->setRotation(angle);
        bullet->flyTo(target);
        
    }
    else if(cRobotPos == 3)
    {
        Point location = Point(CannonLayer::robotPos2,winSize.height-50);
        float angle = CC_RADIANS_TO_DEGREES(ccpAngleSigned(ccpSub(touchLocation, location), Point(0, -1)));
        
        bullet->setRotation(angle);
        bullet->flyTo(target);
        
    }
    
    return true;
    
}

void Weapon::OnWall(Bullet * pTempBullet,unsigned char ucWallState,bool bFanZhuan)
{
    
    
    Point BeginPos = pTempBullet->getBeginPos();
    
    Point NowPos = pTempBullet->getPosition();
    
    if(ucWallState == 1)
    {
        if(bFanZhuan == false)
        {
            BeginPos.y =   BeginPos.y + (NowPos.y - BeginPos.y)*2;
        }
        else
        {
            BeginPos.y = BeginPos.y - (BeginPos.y - NowPos.y)*2;
        }
        
    }
    else if(ucWallState == 2)
    {
        if(bFanZhuan == false)
        {
            BeginPos.x = BeginPos.x - (BeginPos.x - NowPos.x)*2;
        }
        else
        {
            BeginPos.x = BeginPos.x+(NowPos.x-BeginPos.x)*2;
        }
    }
    else if(ucWallState == 3)
    {
        
        if(bFanZhuan == false)
        {
            BeginPos.y = BeginPos.y - (BeginPos.y - NowPos.y)*2;
        }
        else
        {
            BeginPos.y = BeginPos.y + (NowPos.y - BeginPos.y)*2;
        }
    }
    else if(ucWallState == 4)
    {
        if(bFanZhuan == false)
        {
            BeginPos.x = BeginPos.x+ (NowPos.x - BeginPos.x)*2;
        }
        else
        {
            BeginPos.x = BeginPos.x- (BeginPos.x - NowPos.x)*2;
        }
    }
    
    Point normal = ccpNormalize(ccpSub(BeginPos ,NowPos));
    Point vector = ccpMult(normal, distance);
    
    
    
    float angle = CC_RADIANS_TO_DEGREES(ccpAngleSigned(ccpSub( BeginPos,NowPos), Point(0, 1)));
    
    pTempBullet->setRotation(angle);
    
    pTempBullet->setBeginPos(NowPos);
    pTempBullet->flyTo(vector);
    
}

void Weapon::end(int Pos,char cNetType ,char cRobotPos)
{
    Point pos = m_Bullet[cRobotPos][Pos]->getPosition();
    m_Bullet[cRobotPos][Pos]->bDead = true;
    m_Bullet[cRobotPos][Pos]->stopAllActions();
    
    m_Bullet[cRobotPos][Pos]->removeAllChildren();
    
    this->removeChild(m_Bullet[cRobotPos][Pos],true);
    //m_Bullet[cRobotPos][Pos]->release();
    m_Bullet[cRobotPos].erase(m_Bullet[cRobotPos].begin()+Pos);
    /*
     if(cRobotPos == 1)
     {
     if(pTempBullet != NULL)
     {
     pTempBullet->stopAllActions();
     this->removeChild(pTempBullet,true);
     }
     }
     else if(cRobotPos == 2)
     {
     if(pTempBullet != NULL)
     {
     
     pTempBullet->stopAllActions();
     this->removeChild(pTempBullet,true);
     if (!m_Bullet2.empty())
     {
     m_Bullet2.eraseObject(pTempBullet,true);
     }
     
     }
     }
     else if(cRobotPos == 3)
     {
     if(pTempBullet != NULL)
     {
     
     pTempBullet->stopAllActions();
     this->removeChild(pTempBullet,true);
     if (!m_Bullet3.empty())
     {
     m_Bullet3.eraseObject(pTempBullet,true);
     }
     
     }
     }
     else if(cRobotPos == 0)
     {
     if(pTempBullet != NULL)
     {
     
     pTempBullet->stopAllActions();
     this->removeChild(pTempBullet,true);
     if (!m_Bullet.empty())
     {
     m_Bullet.eraseObject(pTempBullet,true);
     }
     
     }
     }*/
    
    if(cNetType >24)
        return;
    
    char  typeTemp = 0;
    if(cNetType <3)
    {
        typeTemp = 1;
    }
    else if(cNetType < 7)
    {
        typeTemp = 2;
    }
    else if(cNetType< 20)
    {
        typeTemp = 3;
    }
    else if(cNetType< 22)
    {
        typeTemp = 4;
    }
    else if(cNetType< 24)
    {
        typeTemp = 5;
    }
    else if(cNetType< 25)
    {
        typeTemp = 6;
    }
    else if(cNetType< 27)
    {
        typeTemp = 7;
    }
    else if(cNetType< 29)
    {
        typeTemp = 8;
    }
    else if(cNetType< 30)
    {
        typeTemp = 9;
    }
    
    if(typeTemp == 4)
    {
        m_ParticleFanWei1->setPosition(pos);
        m_ParticleFanWei1->resetSystem();
        
        m_ParticleFanWei22->setPosition(pos);
        m_ParticleFanWei22->resetSystem();
    }
    else if(typeTemp == 5)
    {
        m_ParticleFanWei2->setPosition(pos);
        m_ParticleFanWei2->resetSystem();
        
        m_ParticleFanWei22->setPosition(pos);
        m_ParticleFanWei22->resetSystem();
        _fishingNetSprite->stopAllActions();
        _fishingNetSprite->setVisible(true);
        
        FadeIn *ac13=FadeIn::create(0.01f);
        
        FadeOut *ac14=FadeOut::create(0.5f);
        _fishingNetSprite->setPosition(pos);
        RotateBy* ac15 = RotateBy::create(0.5f,80);
        Spawn *spawn=Spawn::create(ac14,ac15 ,NULL);
        
        Sequence *seq=Sequence::create(ac13,spawn,NULL);
        _fishingNetSprite->runAction(seq);
        
        
    }
    else if(typeTemp == 6)
    {
        m_ParticleFanWei3->setPosition(pos);
        m_ParticleFanWei3->resetSystem();  
        m_ParticleFanWei3two->setPosition(pos);
        m_ParticleFanWei3two->resetSystem();	
        
    }  
    else
    {
       // if(cRobotPos == 4)
       // {
            Vec2 posTemp = pos;
            posTemp.x =posTemp.x -5;
            posTemp.y = posTemp.y+42;
            //m_Particle->setPosition(posTemp);
            //m_Particle->resetSystem();
            //1,2,5,9,14,20
            Animate *yw_texiao_animate;
            if(cNetType < 5)
            {
                yw_texiao_animate = Animate::create(AnimationCache::getInstance()->getAnimation("bulletComb1"));
            }else if(cNetType < 9)
            {
                yw_texiao_animate = Animate::create(AnimationCache::getInstance()->getAnimation("bulletComb2"));
            }else if(cNetType < 14)
            {
                yw_texiao_animate = Animate::create(AnimationCache::getInstance()->getAnimation("bulletComb3"));
            }else
            {
                yw_texiao_animate = Animate::create(AnimationCache::getInstance()->getAnimation("bulletComb0"));
            }
            
            int suiji_jiaodu = CCRANDOM_0_1() * 360;
            Vec2 suiji_pos = Vec2(CCRANDOM_0_1() * 20 - 5,CCRANDOM_0_1() * 20 +5);
        
            float suiji_scale ;
            if(cNetType > 1)
            {
                suiji_scale =  CCRANDOM_0_1() * 0.3 + 0.9;
            }
            else
            suiji_scale =  CCRANDOM_0_1() * 0.4 + 0.8;
        
            auto _fishingNet_texiao = Sprite::create();
            _fishingNet_texiao->setScale(suiji_scale);
            _fishingNet_texiao->setRotation(suiji_jiaodu);
            if(cNetType > 1)
            {
                _fishingNet_texiao->setPosition(pos+Vec2(-20,20)+suiji_pos);
            }
        
            else
                _fishingNet_texiao->setPosition(pos+suiji_pos);
            this->getParent()->addChild(_fishingNet_texiao,1001);
            _fishingNet_texiao->runAction(Sequence::create(yw_texiao_animate,RemoveSelf::create(),nullptr));//
            //_fishingNet_texiao->runAction();
        //}
    }
}