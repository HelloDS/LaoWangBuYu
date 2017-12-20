#include "ShopJJ.h"
#include "GameData.h"
#include "Gongxi.h"
#include "GameBegin.h"
#include "LogoLayer.h"
#include "GameHallLayer.h"
#include "CannonLayer.h"
#include "Waiting.h"
#include "VIPgongxi.h"
#include <string.h>
//#include "IOS/DCAgent.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "../cocos2d/external/curl/include/ios/curl/curl.h"
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#endif


#if(CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) 
#include "../cocos2d/external/curl/include/android/curl/curl.h"
#include <sys/stat.h> 
#include <unistd.h>
#include <dirent.h> 
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include "..\cocos2d\external\curl\include\win32\curl\curl.h"
#endif

bool ShopJJ::fail_buy_flag;
bool ShopJJ::suc_buy_flag;
int ShopJJ::come_kind_jj = 1;


Scene * ShopJJ::createScene()
{
    auto scene = Scene::create();
    
    auto layer = ShopJJ::create();
    
    scene->addChild(layer);
    
    return scene;
}

void ShopJJ::init60jj(int time)
{
    //背景
    jijin_60_bg = Sprite::create();
    jijin_60_bg->setContentSize(jijin_bg->getContentSize());
    jijin_60_bg->setPosition(Vec2(visibleSize.width * 0.45,visibleSize.height * 0.48));
    jijin_60_bg->setVisible(false);
    addChild(jijin_60_bg,99);
 
    //60元字
    sprintf(jj_chartmp,"%d",60);
    auto zishu_label_6 = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
    zishu_label_6->setPosition(Vec2(200,588));
    zishu_label_6->setScale(0.85);
    //zishu_label_6->setOpacity(0);
    zishu_label_6->setString(jj_chartmp);
    jijin_60_bg->addChild(zishu_label_6);
    
    if(time == 0)
    {
        auto repeat_a =  Repeat::create(Sequence::create(ScaleTo::create(0.25f,1.05),ScaleTo::create(0.25f,0.85),nullptr),5);
        zishu_label_6->runAction(RepeatForever::create(Sequence::create(repeat_a,DelayTime::create(5.0f),nullptr)));
    }
   // zishu_label_6->runAction(Sequence::create(DelayTime::create(0.3f),FadeIn::create(0.3f),nullptr));
    
    //总数值
    auto zongshu_6 = Sprite::createWithSpriteFrameName("jijin_90.png");
    zongshu_6->setPosition(Vec2(547,588));
    //zongshu_6->setOpacity(0);
    jijin_60_bg->addChild(zongshu_6);
    
    if(time == 0)
    {
        auto repeat_b =  Repeat::create(Sequence::create(ScaleTo::create(0.25f,1.2),ScaleTo::create(0.25f,1),nullptr),5);
        zongshu_6->runAction(RepeatForever::create(Sequence::create(DelayTime::create(3.5f),repeat_b,DelayTime::create(1.5f),nullptr)));
    }
    //zongshu_6->runAction(Sequence::create(DelayTime::create(0.3f),FadeIn::create(0.3f),nullptr));
    
    //柱子背景光
    auto zhuzi_bgg = Sprite::createWithSpriteFrameName("jijin_bg_guang.png");
    zhuzi_bgg->setPosition(Vec2(250,125));
    zhuzi_bgg->setOpacity(0);
    zhuzi_bgg->setAnchorPoint(Vec2(0,0));
    jijin_60_bg->addChild(zhuzi_bgg);
    
    zhuzi_bgg->runAction(RepeatForever::create(Sequence::create(DelayTime::create(1.0f),FadeIn::create(0.5f),DelayTime::create(1.0f),FadeOut::create(0.5f),nullptr)));
    
    //中间的数值
    for(int i = 0 ; i < 7 ; i++)
    {
        sprintf(jj_chartmp,"%d",jj_num_60[i]);
        auto yubi_label = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
        yubi_label->setPosition(jj_item_pos[i]);
        yubi_label->setScale(0.42);
        yubi_label->setOpacity(0);
        yubi_label->setString(jj_chartmp);
        jijin_60_bg->addChild(yubi_label);
        if(time != 8 && time > i )
        {
            yubi_label->setColor(Color3B(127,127,127));
        }
        yubi_label->runAction(Sequence::create(DelayTime::create(0.3f),FadeIn::create(0.3f),nullptr));
    }
    
    //已领取
    if(time < 8)
    {
        for(int i = 0 ; i < time ; i++)
        {
            auto yilingqu = Sprite::createWithSpriteFrameName("jijin_yilingqu.png");
            yilingqu->setPosition(ylq_item_pos[i]);
            jijin_60_bg->addChild(yilingqu);
        }
        
    }
    
    //购买按钮
    if(time == 0)
    {
        jijin_60_gm = Sprite::createWithSpriteFrameName("ANG_0000.png");
        auto vioButton = MenuItemSprite::create(jijin_60_gm,jijin_60_gm, CC_CALLBACK_1(ShopJJ::menu_liujj,this));
        vioButton->setTag(1);
        bq_60_gm_menu = Menu::create(vioButton, nullptr);
        bq_60_gm_menu->setPosition(Vec2(480,43));
        jijin_60_bg->addChild(bq_60_gm_menu,100);
        
        auto yiyuan_goumai_A = Animate::create(AnimationCache::getInstance()->getAnimation("yiyuan_goumai"));
        jijin_60_gm->runAction(RepeatForever::create(Sequence::create(yiyuan_goumai_A,DelayTime::create(2.0f),nullptr)));
    }else
    {
        jijin_60_gm = Sprite::createWithSpriteFrameName("zaixianlj_lq1.png");
        auto  yiyuan_goumai1 = Sprite::createWithSpriteFrameName("zaixianlj_lq2.png");
        auto vioButton = MenuItemSprite::create(jijin_60_gm,yiyuan_goumai1, CC_CALLBACK_1(ShopJJ::lingqu_liujj,this));
        vioButton->setTag(time%8 + 1);
        bq_60_gm_menu = Menu::create(vioButton, nullptr);
        bq_60_gm_menu->setPosition(Vec2(480,43));
        jijin_60_bg->addChild(bq_60_gm_menu,100);
        
        if(!jijin_60_flag)
        {
            bq_60_gm_menu->setEnabled(false);
            jijin_60_gm->setColor(Color3B(127,127,127));
        }
    }
    
}

void ShopJJ::init90jj(int time)
{
    //背景
    jijin_90_bg = Sprite::create();
    jijin_90_bg->setVisible(false);
    jijin_90_bg->setContentSize(jijin_bg->getContentSize());
    jijin_90_bg->setPosition(Vec2(visibleSize.width * 0.45,visibleSize.height * 0.48));
    addChild(jijin_90_bg,99);
    
    jijin_90_bg->runAction(Sequence::create(DelayTime::create(0.3f),Show::create(),nullptr));
    
    //90元字
    sprintf(jj_chartmp,"%d",88);
    auto zishu_label_9 = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
    zishu_label_9->setPosition(Vec2(200,588));
    zishu_label_9->setScale(0.85);
    zishu_label_9->setString(jj_chartmp);
    jijin_90_bg->addChild(zishu_label_9);
    
    if(time == 0)
    {
        auto repeat_a1 =  Repeat::create(Sequence::create(ScaleTo::create(0.25f,1.05),ScaleTo::create(0.25f,0.85),nullptr),5);
        zishu_label_9->runAction(RepeatForever::create(Sequence::create(repeat_a1,DelayTime::create(5.0f),nullptr)));
        
    }
    
    //总数值
    auto zongshu_9 = Sprite::createWithSpriteFrameName("jijin_181.png");
    zongshu_9->setPosition(Vec2(547,588));
    jijin_90_bg->addChild(zongshu_9);
    
    if(time == 0)
    {
        auto repeat_b1 =  Repeat::create(Sequence::create(ScaleTo::create(0.25f,1.2),ScaleTo::create(0.25f,1),nullptr),5);
        zongshu_9->runAction(RepeatForever::create(Sequence::create(DelayTime::create(3.5f),repeat_b1,DelayTime::create(1.5f),nullptr)));
        
    }
    
    //柱子背景光
    auto zhuzi_bgg1 = Sprite::createWithSpriteFrameName("jijin_bg_guang.png");
    zhuzi_bgg1->setPosition(Vec2(250,125));
    zhuzi_bgg1->setAnchorPoint(Vec2(0,0));
    zhuzi_bgg1->setOpacity(0);
    jijin_90_bg->addChild(zhuzi_bgg1);
    
    zhuzi_bgg1->runAction(RepeatForever::create(Sequence::create(FadeIn::create(0.5f),DelayTime::create(1.0f),FadeOut::create(0.5f),DelayTime::create(1.0f),nullptr)));
    
    //中间的数值
    for(int i = 0 ; i < 7 ; i++)
    {
        sprintf(jj_chartmp,"%d",jj_num_90[i]);
        auto yubi_label = Label::createWithCharMap("img/hall_huangjinzi.png",34,41,'0');
        yubi_label->setPosition(jj_item_pos[i]);
        yubi_label->setScale(0.42);
        yubi_label->setString(jj_chartmp);
        //yubi_label->setOpacity(0);
        jijin_90_bg->addChild(yubi_label);
        if(time != 8 && time > i )
        {
            yubi_label->setColor(Color3B(127,127,127));
        }
        yubi_label->runAction(Sequence::create(DelayTime::create(0.3f),FadeIn::create(0.3f),nullptr));
    }
    
    //已领取
    if(time < 8)
    {
        for(int i = 0 ; i < time ; i++)
        {
            auto yilingqu = Sprite::createWithSpriteFrameName("jijin_yilingqu.png");
            yilingqu->setPosition(ylq_item_pos[i]);
            jijin_90_bg->addChild(yilingqu);
        }
    }
    
    //购买按钮
    if(time == 0)
    {
        jijin_90_gm = Sprite::createWithSpriteFrameName("ANG_0000.png");
        auto vioButton1 = MenuItemSprite::create(jijin_90_gm,jijin_90_gm, CC_CALLBACK_1(ShopJJ::menu_jiujj,this));
        vioButton1->setTag(1);
        bq_90_gm_menu= Menu::create(vioButton1, nullptr);
        bq_90_gm_menu->setPosition(Vec2(480,43));
        jijin_90_bg->addChild(bq_90_gm_menu,100);
        
        auto yiyuan_goumai_A1 = Animate::create(AnimationCache::getInstance()->getAnimation("yiyuan_goumai"));
        jijin_90_gm->runAction(RepeatForever::create(Sequence::create(yiyuan_goumai_A1,DelayTime::create(2.0f),nullptr)));
    }else
    {
        jijin_90_gm = Sprite::createWithSpriteFrameName("zaixianlj_lq1.png");
        auto  yiyuan_goumai12 = Sprite::createWithSpriteFrameName("zaixianlj_lq2.png");
        auto vioButton1 = MenuItemSprite::create(jijin_90_gm,yiyuan_goumai12, CC_CALLBACK_1(ShopJJ::lingqu_jiujj,this));
        vioButton1->setTag(time%8 + 1);
        bq_90_gm_menu= Menu::create(vioButton1, nullptr);
        bq_90_gm_menu->setPosition(Vec2(480,43));
        jijin_90_bg->addChild(bq_90_gm_menu,100);
        
        if(!jijin_90_flag)
        {
            bq_90_gm_menu->setEnabled(false);
            jijin_90_gm->setColor(Color3B(127,127,127));
        }
    }}

bool ShopJJ::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bridge = new IOSiAP_Bridge();
#endif
    
    //数值初始化
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    order_flag = 0;
    
    jj_num_60[0] = 50000; jj_num_60[1] = 60000; jj_num_60[2] = 70000; jj_num_60[3] = 80000; jj_num_60[4] = 120000;jj_num_60[5] = 220000;jj_num_60[6] = 300000;
    jj_num_90[0] = 100000;jj_num_90[1] = 120000;jj_num_90[2] = 140000;jj_num_90[3] = 160000;jj_num_90[4] = 240000;jj_num_90[5] = 450000;jj_num_90[6] = 600000;
    
    jj_item_pos[0] = Vec2(280,198); jj_item_pos[1] = Vec2(360,248); jj_item_pos[2] = Vec2(440,298); jj_item_pos[3] = Vec2(509,346); jj_item_pos[4] = Vec2(590,394);
    jj_item_pos[5] = Vec2(673,443); jj_item_pos[6] = Vec2(753,493);
    
    ylq_item_pos[0] = Vec2(280,85); ylq_item_pos[1] = Vec2(360,85); ylq_item_pos[2] = Vec2(440,85); ylq_item_pos[3] = Vec2(522,85); ylq_item_pos[4] = Vec2(601,85);
    ylq_item_pos[5] = Vec2(684,85); ylq_item_pos[6] = Vec2(767,85);
    
    time_t prevTime60 = UserDefault::getInstance()->getIntegerForKey("jijin_60_time");
    time_t prevTime90 = UserDefault::getInstance()->getIntegerForKey("jijin_90_time");
    int days_60 = UserDefault::getInstance()->getIntegerForKey("jijin_60_days");
    int days_90 = UserDefault::getInstance()->getIntegerForKey("jijin_90_days");
    time_t currentTime = LogoLayer::getTime();
    
    if(currentTime < prevTime60) //&& currentTime<prevTime + 24*60*60
    {
        jijin_60_flag = false;
    }else
    {
        jijin_60_flag = true;
        if(days_60 == 7)
        {
            days_60 = 0;
            UserDefault::getInstance()->setIntegerForKey("jijin_60_days",0);
            UserDefault::getInstance()->flush();
        }
        
    }
    
    
    if(currentTime < prevTime90) //&& currentTime<prevTime + 24*60*60
    {
        jijin_90_flag = false;
    }else
    {
        jijin_90_flag = true;
        if(days_90 == 7)
        {
            days_90 = 0;
            UserDefault::getInstance()->setIntegerForKey("jijin_90_days",0);
            UserDefault::getInstance()->flush();
        }
        
    }
    auto zheZhao = LayerColor::create(ccc4(0,0,0,150),1024,768);
    zheZhao->setPosition(Point::ZERO);
    zheZhao->setScale(2.0f);
    this->addChild(zheZhao);
    
    //背景
    jijin_bg = Sprite::createWithSpriteFrameName("jijin_bg.png");
    jijin_bg->setPosition(Vec2(visibleSize.width * 0.45,visibleSize.height * 0.48));
    addChild(jijin_bg,99);
    
    //退出
    auto shangchengxx = MenuItemSprite::create(Sprite::createWithSpriteFrameName("hall_menu_X.png"),Sprite::createWithSpriteFrameName("hall_menu_X_d.png"), CC_CALLBACK_0(ShopJJ::exit,this));
    auto m_ShangChengXX= Menu::create(shangchengxx, nullptr);
    m_ShangChengXX->setPosition(Vec2(jijin_bg->getContentSize().width - 10,jijin_bg->getContentSize().height - 10));
    jijin_bg->addChild(m_ShangChengXX,100);
    
    init60jj(days_60);
    init90jj(days_90);
    
    //标签6
    jijin_60_bq = Sprite::createWithSpriteFrameName("jijin_60_bq_an.png");
    auto bq_60_item = MenuItemSprite::create(jijin_60_bq,jijin_60_bq,CC_CALLBACK_1(ShopJJ::qiehuan_60jj,this));
    auto bq_60_menu = Menu::create(bq_60_item,nullptr);
    bq_60_menu->setPosition(Vec2(jijin_bg->getContentSize().width + jijin_60_bq->getContentSize().width/2,jijin_bg->getContentSize().height * 0.75));  //0.55
    jijin_bg->addChild(bq_60_menu,100,11);
    
    //标签9
    jijin_90_bq = Sprite::createWithSpriteFrameName("jijin_90_bq_liang.png");
    auto bq_90_item = MenuItemSprite::create(jijin_90_bq,jijin_90_bq,CC_CALLBACK_1(ShopJJ::qiehuan_90jj,this));
    auto bq_90_menu = Menu::create(bq_90_item,nullptr);
    bq_90_menu->setEnabled(false);
    bq_90_menu->setPosition(Vec2(jijin_bg->getContentSize().width + jijin_60_bq->getContentSize().width/2,jijin_bg->getContentSize().height * 0.6));  //0.55
    jijin_bg->addChild(bq_90_menu,100,12);
    
    jijin_bg->setScale(0.1f);
    ScaleTo *ac7=ScaleTo::create(0.2f, 0.9f);
    ScaleTo *ac8=ScaleTo::create(0.1f, 0.85);
    jijin_bg->runAction(Sequence::create(ac7,ac8,nullptr));
    
    jijin_60_bg->setScale(0.85);
    jijin_90_bg->setScale(0.85);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(ShopJJ::onTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(ShopJJ::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(ShopJJ::onTouchEnded,this);
    listener->setSwallowTouches(true);//不向下传递触摸
    dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    scheduleUpdate();
    return true;
}

void ShopJJ::update(float dt)
{
    if(fail_buy_flag)
    {
        fail_buy_flag = false;
        this->removeChildByTag(1003);
        
        
    }
    if(suc_buy_flag)
    {
        suc_buy_flag =  false;
        this->removeChildByTag(1003);
        
        buyYuBiSuc(order_flag);
    }
}

void ShopJJ::buyYuBiSuc(int flag)
{
    this->removeChildByTag(1001);
    
    GameBegin::playSound("goumai_suc.mp3");
    int yanzhengRMB;
    
    switch(flag)
    {
        case 1:	{
            yanzhengRMB = 60;
            if(LogoLayer::dengluFlag)
            {
                sprintf(jj_chartmp,GAME_DATA_STRING("mission_b"),900000);
                auto gongxi = Gongxi::create(4, jj_chartmp);
                this->addChild(gongxi,1000);
                
                GameHallLayer::RefreshCoin(900000);
            }else
            {
                UserDefault::getInstance()->setIntegerForKey("jijin_60_days",8);
                UserDefault::getInstance()->flush();
                
                jijin_60_gm->stopAllActions();
                bq_60_gm_menu->removeFromParentAndCleanup(true);
                jijin_60_gm= NULL;
                bq_60_gm_menu = NULL;
                
                jijin_60_gm = Sprite::createWithSpriteFrameName("zaixianlj_lq1.png");
                auto  yiyuan_goumai12 = Sprite::createWithSpriteFrameName("zaixianlj_lq2.png");
                auto vioButton1 = MenuItemSprite::create(jijin_60_gm,yiyuan_goumai12, CC_CALLBACK_1(ShopJJ::lingqu_liujj,this));
                vioButton1->setTag(1);
                bq_60_gm_menu= Menu::create(vioButton1, nullptr);
                bq_60_gm_menu->setPosition(Vec2(480,43));
                jijin_60_bg->addChild(bq_60_gm_menu,100);
                
                auto  gongxi = Gongxi::create(4,GAME_DATA_STRING("jijin_60_huode"));
                this->addChild(gongxi,ANNIULAYER + 100);
            }
            
            
        }break;
        case 2:	{
            yanzhengRMB = 88;
            if(LogoLayer::dengluFlag)
            {
                sprintf(jj_chartmp,GAME_DATA_STRING("mission_b"),1810000);
                auto gongxi = Gongxi::create(4, jj_chartmp);
                this->addChild(gongxi,1000);
                
                GameHallLayer::RefreshCoin(1810000);
            }else
            {
                UserDefault::getInstance()->setIntegerForKey("jijin_90_days",8);
                UserDefault::getInstance()->flush();
                
                jijin_90_gm->stopAllActions();
                bq_90_gm_menu->removeFromParentAndCleanup(true);
                jijin_90_gm= NULL;
                bq_90_gm_menu = NULL;
                
                jijin_90_gm = Sprite::createWithSpriteFrameName("zaixianlj_lq1.png");
                auto  yiyuan_goumai12 = Sprite::createWithSpriteFrameName("zaixianlj_lq2.png");
                auto vioButton1 = MenuItemSprite::create(jijin_90_gm,yiyuan_goumai12, CC_CALLBACK_1(ShopJJ::lingqu_jiujj,this));
                vioButton1->setTag(1);
                bq_90_gm_menu= Menu::create(vioButton1, nullptr);
                bq_90_gm_menu->setPosition(Vec2(480,43));
                jijin_90_bg->addChild(bq_90_gm_menu,100);
                
                auto  gongxi = Gongxi::create(4,GAME_DATA_STRING("jijin_90_huode"));
                this->addChild(gongxi,ANNIULAYER + 100);
            }
            
            
        }break;
            
        default:break;
    }
    
    cocos2d::log("goumai cheng  gong ");
 
    UserDefault::getInstance()->setIntegerForKey("leijichongzhicaijin",yanzhengRMB + UserDefault::getInstance()->getIntegerForKey("leijichongzhicaijin"));
    UserDefault::getInstance()->flush();
    
   // DCVirtualCurrency::paymentSuccess("wfgs","123",yanzhengRMB,"CNY","短代" );
}

void ShopJJ::buyYuBi(int iii)
{
    
    GameBegin::buttonSound();
    order_flag = iii;
    auto waitingQQ = Waiting::create();
    addChild(waitingQQ,1000,1003);
    
    bool bTempCeShi = false;
   // waitingQQ->runAction(Sequence::create(DelayTime::create(10),RemoveSelf::create(),nullptr));
 //  suc_buy_flag = true;
    if(order_flag == 1)
    {
    
        
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        //buyYuBiSuc(order_flag);
        if(bTempCeShi == true)
        {
           suc_buy_flag = true;
        }
        else
        bridge->requestProducts(60);
#endif  
        
    }
    if(order_flag == 2)
    {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
       
       // buyYuBiSuc(order_flag);

        if(bTempCeShi == true)
        {
            
            suc_buy_flag = true;
        }
        else
         bridge->requestProducts(90);
#endif
        
    }

    
}

void ShopJJ::menu_liujj(Ref * sender)
{
    buyYuBi(1);
}

void ShopJJ::menu_jiujj(Ref * sender)
{
    buyYuBi(2);
}

void ShopJJ::qiehuan_60jj(Ref * sender)
{
    GameBegin::buttonSound();
    auto menu60 = (Menu *)jijin_bg->getChildByTag(11);
    auto menu90 = (Menu *)jijin_bg->getChildByTag(12);
    bool enable = menu60->isEnabled();
    if(enable)
    {
        //更新60标签为亮色 90标签为暗色
        jijin_60_bg->setVisible(true);
        jijin_60_bq->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jijin_60_bq_liang.png"));
        menu60->setEnabled(false);
        
        jijin_90_bg->setVisible(false);
        jijin_90_bq->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jijin_90_bq_an.png"));
        menu90->setEnabled(true);
    }
}

void ShopJJ::qiehuan_90jj(Ref * sender)
{
    GameBegin::buttonSound();
    auto menu60 = (Menu *)jijin_bg->getChildByTag(11);
    auto menu90 = (Menu *)jijin_bg->getChildByTag(12);
    bool enable = menu90->isEnabled();
    if(enable)
    {
        //更新60标签为亮色 90标签为暗色
        jijin_90_bg->setVisible(true);
        jijin_90_bq->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jijin_90_bq_liang.png"));
        menu90->setEnabled(false);
        
        jijin_60_bg->setVisible(false);
        jijin_60_bq->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jijin_60_bq_an.png"));
        menu60->setEnabled(true);
    }
}

void ShopJJ::lingqu_liujj(Ref * sender)
{
    int days = ((MenuItemSprite *)sender)->getTag();
    cocos2d::log("days = %d",days);
    
    time_t currentTime = LogoLayer::getTime();
    cocos2d::log("loginreward:: currentTime = %ld",currentTime);
    
    struct tm *nowTime = gmtime(&currentTime);
    int hour=nowTime->tm_hour;
    int minute=nowTime->tm_min;
    int second=nowTime->tm_sec;
    time_t nextTime = currentTime + 24*60*60 - hour*60*60 - minute*60 - second;
    
    if(come_kind_jj == 1)
        GameHallLayer::RefreshCoin(jj_num_60[days-1]);
    else
        CannonLayer::GameCoinRefresh(jj_num_60[days-1]);
    
    UserDefault::getInstance()->setIntegerForKey("jijin_60_time",nextTime);
    UserDefault::getInstance()->setIntegerForKey("jijin_60_days",days);
    UserDefault::getInstance()->flush();
    
    sprintf(jj_chartmp,GAME_DATA_STRING("mission_b"),jj_num_60[days-1]);
    auto  gongxi = Gongxi::create(4,jj_chartmp);
    gongxi->setPosition(Point::ZERO);
    this->getParent()->addChild(gongxi,ANNIULAYER + 100);
    
    exit();
}

void ShopJJ::lingqu_jiujj(Ref * sender)
{
    
    int days = ((MenuItemSprite *)sender)->getTag();
    cocos2d::log("days = %d",days);
    
    time_t currentTime = LogoLayer::getTime();
    cocos2d::log("loginreward:: currentTime = %ld",currentTime);
    
    struct tm *nowTime = gmtime(&currentTime);
    int hour=nowTime->tm_hour;  
    int minute=nowTime->tm_min;  
    int second=nowTime->tm_sec;
    time_t nextTime = currentTime + 24*60*60 - hour*60*60 - minute*60 - second; 
 
    if(come_kind_jj == 1)
        GameHallLayer::RefreshCoin(jj_num_90[days-1]);
    else
        CannonLayer::GameCoinRefresh(jj_num_90[days-1]);
    
    UserDefault::getInstance()->setIntegerForKey("jijin_90_time",nextTime);
    UserDefault::getInstance()->setIntegerForKey("jijin_90_days",days);
    UserDefault::getInstance()->flush();
    
    sprintf(jj_chartmp,GAME_DATA_STRING("mission_b"),jj_num_90[days-1]);
    auto  gongxi = Gongxi::create(4,jj_chartmp);
    gongxi->setPosition(Point::ZERO);
    this->getParent()->addChild(gongxi,ANNIULAYER + 100);
    
    exit();
}

bool ShopJJ::onTouchBegan(Touch* touch, Event* event) 
{ 
    Rect roomRect = Rect(visibleSize.width * 0.75,visibleSize.height * 0.5, visibleSize.width * 0.25,200 );
    if(!roomRect.containsPoint(touch->getLocation()))
    {
        exit();
    }
    
    return true;
}

void ShopJJ::onTouchMoved(Touch* touch, Event* event) 
{
    
}

void ShopJJ::onTouchEnded(Touch* touch, Event* event)
{
    
}

void ShopJJ::yanZhengOrderJJ(string defineData,string tradeNO)
{
    /*
    CURL *curl;
    CURLcode res;
    std::string cc;
    curl=curl_easy_init();
    string DeviceNo = UserDefault::getInstance()->getStringForKey("DeviceNo");
    string version = GAME_DATA_STRING("game_version");
    if(IOSiAP_Bridge::productID  == 90)
    {
        IOSiAP_Bridge::productID = 88;
    }
    if(IOSiAP_Bridge::productID  == 11)
    {
        IOSiAP_Bridge::productID = 1;
    }
    
    char postFields[5000];
    sprintf(postFields,"receipt-data=%s&tradeId=%s&deviceId=%s&productId=%s&rmb=%d&version=%s",
            defineData.c_str(),tradeNO.c_str(),DeviceNo.c_str(),IOSiAP_Bridge::productIDPass.c_str(),IOSiAP_Bridge::productID,version.c_str());

    cocos2d::log("IOSiAP_Bridge:: ****postFields:%s  ****",postFields);
    if(curl)
    {
       
            curl_easy_setopt( curl, CURLOPT_URL, "http://dwby-hk.iyueyo.com/qpby2/iosfanti/shop/ios_iap.php"); //请求的地址
        curl_easy_setopt(curl, CURLOPT_POST, true);           //启用POST提交
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields); //发送的数据
        curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&iosPossItJJ); //处理的函数
        curl_easy_setopt(curl, CURLOPT_TIMEOUT,3000);
        res=curl_easy_perform(curl);
        if(res!=CURLE_OK)
        {
            log("联网超时 %i",res);
            fail_buy_flag = true;
        }
        curl_easy_cleanup(curl);
        return ;
    }
    else
    {
        cocos2d::log("curl shi kong de ");
        fail_buy_flag = true;
        return ;
    }*/
}


size_t  ShopJJ::iosPossItJJ(uint8_t *buffer,size_t size,size_t nmemb,void *stream)
{
    //打印收到的数据
    cocos2d::log("SHOP::*****possIt_____%s____",(const char *)buffer);
    int tmpRMB = atoi((const char *)buffer);
    if(tmpRMB == 1)//成功
    {
        suc_buy_flag = true;
    }
    else if(tmpRMB > 10)
    {
    //    CCLOG("订单失败！");
        fail_buy_flag = true;
    }
    else
    {
        fail_buy_flag = true;
    }
    
    //返回数据长度
    size_t sizes = size*nmemb;
    return sizes;
}


void ShopJJ::exit()
{
    GameBegin::buttonSound(); 
    
    jijin_60_bg->setVisible(false);
    jijin_90_bg->setVisible(false);
    
    ScaleTo *ac7=ScaleTo::create(0.1f, 0.9f);  
    ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
    jijin_bg->runAction(Sequence::create(ac7,ac8,nullptr)); 
    
    this->runAction(Sequence::create(DelayTime::create(0.3f),RemoveSelf::create(),nullptr));
}
