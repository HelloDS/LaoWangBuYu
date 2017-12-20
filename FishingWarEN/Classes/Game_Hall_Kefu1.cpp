
#include "Game_Hall_Kefu1.h"
#include "GameBegin.h"
#include "GameData.h"
#include "GameHallLayer.h"
#include "Gongxi.h"
 
Scene* Game_Hall_Kefu3::createScene()
{
    auto scene = Scene::create();
    auto layer = Game_Hall_Kefu3::create();
    scene->addChild(layer);
    
    return scene;
}

bool Game_Hall_Kefu3::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    Size winSize = Director::getInstance()->getWinSize();
    
    auto zheZhao = LayerColor::create(ccc4(0,0,0,150),1024,768);
    zheZhao->setPosition(Point::ZERO);
    zheZhao->setScale(2.0f);
    this->addChild(zheZhao);
    
    
    //升级板
    shopCenterBg = Scale9Sprite::createWithSpriteFrameName( "bs_kuang.png",CCRectMake(99,99,20,20));
    shopCenterBg->setContentSize(CCSizeMake(983,450));
    shopCenterBg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    this->addChild(shopCenterBg);
    
    auto shopCenterBg1 = Sprite::createWithSpriteFrameName("HF_huo_title.png");
    shopCenterBg1->setPosition(Point(shopCenterBg->getContentSize().width/2,shopCenterBg->getContentSize().height));
    shopCenterBg->addChild(shopCenterBg1,100);
    
    auto shangchengxx = MenuItemSprite::create(Sprite::createWithSpriteFrameName("hall_menu_X.png"),Sprite::createWithSpriteFrameName("hall_menu_X_d.png"), CC_CALLBACK_0(Game_Hall_Kefu3::exit,this));
    auto m_ShangChengXX= Menu::create(shangchengxx, nullptr);
    m_ShangChengXX->setPosition(Vec2(shopCenterBg->getContentSize().width - 10,shopCenterBg->getContentSize().height - 10));
    shopCenterBg->addChild(m_ShangChengXX,100);
    
    if(shopCenterBg)
    {
        shopCenterBg->setScale(0.1f);
        ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);
        ScaleTo *ac8=ScaleTo::create(0.1f, 1.0);
        shopCenterBg->runAction(Sequence::create(ac7,ac8,nullptr));
    }
    
    //滑板
    yubiLayer = Layer::create();
    yubiLayer->setPosition(Point::ZERO);
    yubiLayer->setAnchorPoint(Point::ZERO);
    layer_x = 0;
    yubiLayer->setContentSize(Size(960,400));
    
    yubiView = ScrollView::create(Size(960,400),yubiLayer);
    yubiView->setDelegate(this);
    yubiView->ignoreAnchorPointForPosition(false);
    yubiView->setAnchorPoint(Vec2(0.5,0.5));
    yubiView->setDirection(ScrollView::Direction::HORIZONTAL);
    yubiView->setPosition(Vec2(shopCenterBg->getContentSize().width/2 + 1,shopCenterBg->getContentSize().height/2));
    shopCenterBg->addChild(yubiView,100);
    
    roomSize = Size(238,336);
    int spaceW = 85;
    
    float speed = 1500;
    float distans;
    
    auto shop_diguang = Sprite::createWithSpriteFrameName("shop_diguang.png");
    shop_diguang->setAnchorPoint(Vec2(0.5,0));
    shop_diguang->setPosition(Vec2(shopCenterBg->getContentSize().width/2 - roomSize.width - spaceW ,11));
    shopCenterBg->addChild(shop_diguang,100);
    
    auto shop_diguang1 = Sprite::createWithSpriteFrameName("shop_diguang.png");
    shop_diguang1->setAnchorPoint(Vec2(0.5,0));
    shop_diguang1->setPosition(Vec2( shopCenterBg->getContentSize().width / 2,11));
    shopCenterBg->addChild(shop_diguang1,100);
    
    auto shop_diguang2 = Sprite::createWithSpriteFrameName("shop_diguang.png");
    shop_diguang2->setAnchorPoint(Vec2(0.5,0));
    shop_diguang2->setPosition(Vec2(shopCenterBg->getContentSize().width/2 + roomSize.width + spaceW ,11));
    shopCenterBg->addChild(shop_diguang2,100);
    
    char moneyTmp[30];
    for(int i = 0; i<3 ; i++)
    {
        sprintf(moneyTmp,"HF_huo_%d.png",i+1);
        auto yubiObg = Sprite::createWithSpriteFrameName(moneyTmp);
        yubiObg->setZOrder(9-i);
        yubiObg->setPosition(Point(yubiLayer->getContentSize().width * 1.5,yubiLayer->getContentSize().height/2 + 10));
        yubiLayer->addChild(yubiObg);
        
        sp_yubi.pushBack(yubiObg);
        
        distans = yubiLayer->getContentSize().width * 1.5 - (yubiLayer->getContentSize().width/2 + (i-1) *  (roomSize.width + spaceW));
        auto moveTo = MoveBy::create(distans/speed,Vec2(-distans,0));
        auto moveBy = MoveBy::create(0.3f,Vec2(0,-10));
        yubiObg->runAction(Sequence::create(moveTo,CCCallFunc::create([&]{GameBegin::playSound("bs_fapai.mp3");}),moveBy,nullptr));
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Game_Hall_Kefu3::onTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(Game_Hall_Kefu3::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(Game_Hall_Kefu3::onTouchEnded,this);
    listener->setSwallowTouches(true);//不向下传递触摸
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
    
    return true;
}

void Game_Hall_Kefu3::exit()
{
    GameBegin::buttonSound();
    
    ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);
    ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);
    shopCenterBg->runAction(Sequence::create(ac7,ac8,nullptr));
    
    this->runAction(Sequence::create(DelayTime::create(0.3f),RemoveSelf::create(),nullptr));
}

void Game_Hall_Kefu3::duiHuaFei(int room)
{
    log("room = %d",room);
    switch (room)
    {
        case 1:
        {
            //to do 跳红包界面
            std::string ere = "Icon-180.png";
            std::string fullpath = FileUtils::getInstance()->fullPathForFilename(ere) ;
            
            
            if(UserDefault::getInstance()->getIntegerForKey("first_fenxiang") == 0)
            {
                UserDefault::getInstance()->setIntegerForKey("first_fenxiang",1);
                GameBegin::setFileData("jywer.txt" ,GameBegin::getFileData("jywer.txt")+5000);
                UserDefault::getInstance()->flush();
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(kCUSTEVENT_XGHFQ);
            }
            
        }break;
        case 2:
        {
            exit();
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(kCUSTEVENT_HDHF_CS);
        }break;
        case 3:
        {
            if( UserDefault::getInstance()->getIntegerForKey("player_vip") == 0)
            {
                auto gongxi = Gongxi::create(3,GAME_DATA_STRING("bushi_vip"));
                gongxi->setPosition(Point::ZERO);
                this->addChild(gongxi,1000,999);
                
                auto quedingSprite = Sprite::createWithSpriteFrameName("XR_qd.png" );
                auto quedingItem = MenuItemSprite::create(quedingSprite,quedingSprite,quedingSprite,CC_CALLBACK_1(Game_Hall_Kefu3::tanchuVip,this));
                auto btnMenu = Menu::create(quedingItem,nullptr);
                btnMenu->setPosition(Point(gongxi->getChildByTag(1)->getContentSize().width/2,0.18*gongxi->getChildByTag(1)->getContentSize().height));
                gongxi->getChildByTag(1)->addChild(btnMenu,100);
            }
            else
            {
                int lv = GameBegin::getFileData("gamePlayerlv.txt");
                int jinbi = GameBegin::getFileData("jywer.txt");
                int beilv = GameBegin::getFileData("gameMaxPao.txt");
                
                //判断当前属于哪个级别
                if(jinbi<=GAME_DATA_INT("bs_room_3_jinbi"))
                {
                    auto gongxi = Gongxi::create(2,GAME_DATA_STRING("jinbibuzu"));
                    gongxi->setPosition(Point::ZERO);
                    this->addChild(gongxi,1000,999);
                    
                }else
                {
                    exit();
                    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(kCUSTEVENT_HDHF_CS);
                }
                
            }
            
            
        }break;
        default:
            break;
    }
}

void Game_Hall_Kefu3::tanchuVip(Ref * psender)
{
    this->removeChildByTag(999);
    exit();
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(kCUSTEVENT_HDHF_VIP);
}

void Game_Hall_Kefu3::huodeHF(Ref * psender)
{
    log("huode hua fei");
}

bool Game_Hall_Kefu3::onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
    p1 = touch->getLocation();
    
    if(p1.y < visibleSize.height/2 + roomSize.height/2 * kHF_SCALE_HD_L && p1.y > visibleSize.height/2 - roomSize.height/2 * kHF_SCALE_HD_L)
    {
        float yubiWidth =  yubiView->getViewSize().width;
        float room_x = p1.x -(visibleSize.width - yubiWidth)/2;
        
        if (room_x > 0 && room_x < yubiWidth)
        {
            room_x = room_x + layer_x;
            if(room_x >sp_yubi.at(0)->getPositionX() -  roomSize.width * kHF_SCALE_HD_L/2 && room_x < sp_yubi.at(0)->getPositionX() + roomSize.width * kHF_SCALE_HD_L/2)
            {
                cur_room = 1;
                sp_yubi.at(0)->setScale(kHF_SCALE_HD_H);
            }
            
            if(room_x >sp_yubi.at(1)->getPositionX() -  roomSize.width * kHF_SCALE_HD_L/2 && room_x < sp_yubi.at(1)->getPositionX() + roomSize.width * kHF_SCALE_HD_L/2)
            {
                cur_room = 2;
                sp_yubi.at(1)->setScale(kHF_SCALE_HD_H);
            }
            
            if(room_x >sp_yubi.at(2)->getPositionX() -  roomSize.width * kHF_SCALE_HD_L/2 && room_x < sp_yubi.at(2)->getPositionX() + roomSize.width * kHF_SCALE_HD_L/2)
            {
                cur_room = 3;
                sp_yubi.at(2)->setScale(kHF_SCALE_HD_H);
            }
        }
    }
    
    return true;
}

void Game_Hall_Kefu3::onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
    
}

void Game_Hall_Kefu3::onTouchEnded(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
    p2 = touch->getLocation();
    cocos2d::log("offset pos is %f ",p2.x);  
    if(cur_room > 0 &&abs(p2.x - p1.x) < 8     )
    {
        duiHuaFei(cur_room);
    }
    if(cur_room > 0)
    {
        sp_yubi.at(cur_room - 1)->setScale(kHF_SCALE_HD_L);
        cur_room = 0;
    }
    log("touchesEnded");
}

void Game_Hall_Kefu3::scrollViewDidScroll(extension::ScrollView* view)
{
    
    layer_x = abs(view->getContentOffset().x);//获得偏移X坐标(向右移动，偏移量为正数，向左则为负数）  
    cocos2d::log("offset pos is %f ",layer_x);  
    
}

void Game_Hall_Kefu3::scrollViewDidZoom(extension::ScrollView* view)
{
}