#include "Shop.h"
#include "cocos-ext.h"
#include "GameData.h"
#include "Gongxi.h"
#include "GameBegin.h"
#include "CannonUpgrade.h"
#include "LogoLayer.h" 
#include "VIPgongxi.h"
#include "UIWebViewTest.h"

#include "GameTextIn.h"

#include "GameScene.h"
#include "ChallengeBOSS.h"
#include "GameHallLayer.h"
//#include "IOS/DCAgent.h"
#include "sqlite3.h"
#include <string.h>
#include "JNative/JNativeToJavaUtil.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif



#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "../cocos2d/external/curl/include/ios/curl/curl.h"
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#endif


#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include "..\cocos2d\external\curl\include\win32\curl\curl.h"
#endif

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

#include <regex>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <regex.h>
#endif


USING_NS_CC;
USING_NS_CC_EXT;


int Shop::comeKind = 0;


bool Shop::isCeShi = false;
int Shop::orderShopKind = 0;
bool Shop::successFlag = false;
bool Shop::failFlag = false;
bool Shop::yanzhengFailFlag = false;
bool Shop::yanzhangFlag = false;
bool Shop::yanZhengFlag = false;
bool Shop::budanFlag = false;
bool Shop::budanFlag1 = false;
bool Shop::budanFlag2 = false;

bool Shop::huifuFlag = false;


int Shop::budan_times = 0;
int Shop::yanzhengInt = 12;
float Shop::yubi_num[YUBINUM] = {6,12,33,82,155,335,40};
float Shop::zuanshi_num[YUBINUM] = {300,600,1500,4000,8000,15000,1000};
float Shop::sale_percent[4] = {1,1.5,1.8,2};
float Shop::sPrice[YUBINUM] = {0.99, 1.99, 4.99, 9.99, 19.99, 39.99, 50};

float Shop::yubiNumMSM[4] = {5, 10, 31, 55};
float Shop::zuanshiNumMSM[4] = {300, 600, 1500, 4000};
int Shop::sPriceMSM[4] = {25, 49, 150, 250};

 
string Shop::iosDefineData = "";
string Shop::iosTradeID= "";
string Shop::defineData = "";
string Shop::goumaileixing = "";

bool Shop::iosBuyFailFlag = false;
bool Shop::bFeiFa = false;
bool Shop::BigPay = false;

bool Shop::BigPaySuccess = false;




//2017 12月18日 谷歌充值添加   充值成功的事件派发
const char *Shop::GOOGLE_PAY = "google_pay_Success";
struct GoogleData
{
	char * orderId;
	char * packageName;
	char * productId;
	char * purchaseTime;
	char * purchaseState;
	char * purchaseToken;
};
Shop* Shop::pStaticShop = NULL;

Shop * Shop::create(int btnKind)   //1,来自大厅 2.来自场景内  3.来自大炮升级  4,大厅vip 5,场景vip  6大厅一元  8.来自挑战boss
{
	Shop * shop = new Shop();
	shop->init(btnKind );
	shop->autorelease();
	return shop;
}

void Shop::init_shop()
{
    cur_room = 0;
    get_budan_data();
    
    
    otherpay = false;
    mIsMSMPay = false;
    
    //升级板 
    shopCenterBg = Scale9Sprite::createWithSpriteFrameName( "bs_kuang.png",CCRectMake(99,99,20,20));
    shopCenterBg->setContentSize(CCSizeMake(900,400));
    shopCenterBg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    this->addChild(shopCenterBg);
 
    
    auto shangchengxx = MenuItemSprite::create(Sprite::createWithSpriteFrameName("hall_menu_X.png"),Sprite::createWithSpriteFrameName("hall_menu_X_d.png"), CC_CALLBACK_0(Shop::exit,this));
    auto m_ShangChengXX= Menu::create(shangchengxx, nullptr);
    m_ShangChengXX->setPosition(Vec2(shopCenterBg->getContentSize().width - 10,shopCenterBg->getContentSize().height - 10));
    shopCenterBg->addChild(m_ShangChengXX,100);
    
    
    
    auto  shopapp= MenuItemSprite::create(Sprite::create("gameHall/googlePlayPic.png"),Sprite::create("gameHall/googlePlayPic.png"), CC_CALLBACK_0(Shop::shopapp,this));
    auto shopappmenu= Menu::create(shopapp, nullptr);
    shopappmenu->setPosition(Vec2( 110 ,shopCenterBg->getContentSize().height + 39));
    shopCenterBg->addChild(shopappmenu,100);
    
    
    
    m_SprShopApp = Sprite::createWithSpriteFrameName("shopjiantou.png");
    m_SprShopApp->setPosition(Vec2( 110 ,shopCenterBg->getContentSize().height + 33));
    shopCenterBg->addChild(m_SprShopApp,100);
    
    
    if( UserDefault::getInstance()->getIntegerForKey("ios_dengluFlag") != 1)
    {

        auto shopmol = MenuItemSprite::create(Sprite::createWithSpriteFrameName("shopmol.png"),Sprite::createWithSpriteFrameName("shopmol.png"), CC_CALLBACK_0(Shop::shopmol,this));
        auto shopmolmenu= Menu::create(shopmol, nullptr);
        shopmolmenu->setPosition(Vec2(130+shopapp->getContentSize().width * 2,shopCenterBg->getContentSize().height + 39));
        shopCenterBg->addChild(shopmolmenu,100);
        
        
        auto shoptrue = MenuItemSprite::create(Sprite::createWithSpriteFrameName("shoptrue.png"),Sprite::createWithSpriteFrameName("shoptrue.png"), CC_CALLBACK_0(Shop::shoptrue,this));
        auto shoptruemenu= Menu::create(shoptrue, nullptr);
        shoptruemenu->setPosition(Vec2(140+shopapp->getContentSize().width*3,shopCenterBg->getContentSize().height + 39));
        shopCenterBg->addChild(shoptruemenu,100);

		
		auto shopSMS = MenuItemImage::create("gameHall/sms.png","gameHall/sms.png", CC_CALLBACK_0(Shop::shopMsg,this));
		auto shopSMSMenu= Menu::create(shopSMS, nullptr);
		shopSMSMenu->setPosition(Vec2(110,shopCenterBg->getContentSize().height + 39));
		shopCenterBg->addChild(shopSMSMenu,100);

		m_SprShopMol = Sprite::createWithSpriteFrameName("shopjiantou.png");
		m_SprShopMol->setPosition(Vec2(130 + shopapp->getContentSize().width * 2, shopCenterBg->getContentSize().height + 33));
		shopCenterBg->addChild(m_SprShopMol, 100);
		m_SprShopMol->setVisible(false);


		m_SprShopTrue = Sprite::createWithSpriteFrameName("shopjiantou.png");
		m_SprShopTrue->setPosition(Vec2(140 + shopapp->getContentSize().width * 3, shopCenterBg->getContentSize().height + 33));
		shopCenterBg->addChild(m_SprShopTrue, 100);
		m_SprShopTrue->setVisible(false);


		m_SprShopSMS = Sprite::createWithSpriteFrameName("shopjiantou.png");
		m_SprShopSMS->setPosition(Vec2(110, shopCenterBg->getContentSize().height + 33));
		shopCenterBg->addChild(m_SprShopSMS, 100);
		m_SprShopSMS->setVisible(false);


		m_SprShopApp->setPositionX(120+shopapp->getContentSize().width);
		shopappmenu->setPositionX(120+shopapp->getContentSize().width);
    }
    
    
 /*   auto sc_budan = MenuItemSprite::create(Sprite::createWithSpriteFrameName("help_budan.png"),Sprite::createWithSpriteFrameName("help_budan.png"), CC_CALLBACK_0(Shop::ios_budan,this));
    auto sc_budan_menu= Menu::create(sc_budan, nullptr);
    sc_budan_menu->setPosition(Vec2(shopCenterBg->getContentSize().width * 0.75,shopCenterBg->getContentSize().height));
    shopCenterBg->addChild(sc_budan_menu,100);*/
 /*
    auto huifugoumai =   MenuItemSprite::create(Sprite::create("huifugoumai.png"),Sprite::create("huifugoumai.png"), CC_CALLBACK_0(Shop::huifugoumai,this));
    auto m_huifugoumai= Menu::create(huifugoumai, nullptr);
    m_huifugoumai->setPosition(Vec2(shopCenterBg->getContentSize().width * 0.18,shopCenterBg->getContentSize().height));
    shopCenterBg->addChild(m_huifugoumai,100);
  
    if(UserDefault::getInstance()->getIntegerForKey("player_vip") == 0)
    {
        m_huifugoumai->setVisible(false);
    }
    if(LogoLayer::dengluFlag == false)
    {
         m_huifugoumai->setVisible(false);
    }
    */
    
 /*   if(ios_daibudan.size() == 0)
    {
        sc_budan_menu->setVisible(false);
    }*/
    if(shopCenterBg)
    {
        shopCenterBg->setScale(0.1f);
        ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);
        ScaleTo *ac8=ScaleTo::create(0.1f, 1.0);
        shopCenterBg->runAction(Sequence::create(ac7,ac8,nullptr));
    }
    
    
    int tmpNum = 6;
    if(LogoLayer::dengluFlag)
        tmpNum = 7;
    
    roomSize = Size(208,353);
    int spaceW = 20;
    
    //滑板
    yubiLayer = Layer::create();
    yubiLayer->setPosition(Point::ZERO);
    yubiLayer->setAnchorPoint(Point::ZERO);
    layer_x = 0;
    yubiLayer->setContentSize(Size((roomSize.width + 20 ) * tmpNum,400));
    
    yubiView = ScrollView::create(Size(840,400),yubiLayer);
    yubiView->setDelegate(this);
    yubiView->ignoreAnchorPointForPosition(false);
    yubiView->setAnchorPoint(Vec2(0.5,0.5));
    yubiView->setDirection(ScrollView::Direction::HORIZONTAL);
    yubiView->setPosition(Vec2(shopCenterBg->getContentSize().width/2 + 1,shopCenterBg->getContentSize().height/2));
    shopCenterBg->addChild(yubiView,100);
    
    
    
    auto shop_diguang = Sprite::createWithSpriteFrameName("shop_diguang.png");
    shop_diguang->setAnchorPoint(Vec2(0.5,0));
    shop_diguang->setPosition(Point( 0.5 * roomSize.width + 10 ,11));
    shopCenterBg->addChild(shop_diguang,100);
    
    auto shop_diguang1 = Sprite::createWithSpriteFrameName("shop_diguang.png");
    shop_diguang1->setAnchorPoint(Vec2(0.5,0));
    shop_diguang1->setPosition(Point( 1.5 * roomSize.width + 30 ,11));
    shopCenterBg->addChild(shop_diguang1,100);
    
    auto shop_diguang2 = Sprite::createWithSpriteFrameName("shop_diguang.png");
    shop_diguang2->setAnchorPoint(Vec2(0.5,0));
    shop_diguang2->setPosition(Point( 2.5 * roomSize.width + 50,11));
    shopCenterBg->addChild(shop_diguang2,100);
    
    float speed = 1500;
    float distans;
    
    char moneyTmp[30];
    char num_tmp[30];
    
    for(int i = 0; i< tmpNum ; i++)
    {
        if(tmpNum == 7 && i == tmpNum -1)
            sprintf(moneyTmp,"shop_item_%d.png",i);
        else
            sprintf(moneyTmp,"shop_item_%d.png",i+1);
        auto yubiObg = Sprite::createWithSpriteFrameName(moneyTmp);
        yubiObg->setScale(SHOP_ROOM_L);
        yubiObg->setZOrder(i);
        yubiObg->setPosition(Point(0,yubiLayer->getContentSize().height/2));
        yubiLayer->addChild(yubiObg);
        
        auto stencil11 = Sprite::createWithSpriteFrameName(moneyTmp);
        auto clipper11 = ClippingNode::create();
        clipper11->setStencil(stencil11);//设置裁剪模板 //3
        clipper11->setInverted(false);//设置底板不可见
        //clipper->setAnchorPoint(Vec2(0.5,0.5));
        clipper11->setPosition(Vec2(yubiObg->getContentSize()/2));
        clipper11->setContentSize(yubiObg->getContentSize());
        clipper11->setAlphaThreshold(0);//设置绘制底板的Alpha值为0
        yubiObg->addChild(clipper11,8);//4
        
        auto sajinbi = ParticleSystemQuad::create("zm_huang.plist");
        auto batch = ParticleBatchNode::createWithTexture(sajinbi->getTexture());
        batch->addChild(sajinbi);
        clipper11->addChild(batch);
        sajinbi->setPosition(Vec2::ZERO);
        sajinbi->resetSystem();
        batch->setVisible(false);
        node_jinguang.pushBack(batch);
        
        sp_yubi.pushBack(yubiObg);
        
        distans = ( i *  (roomSize.width + spaceW) + (roomSize.width + spaceW) * 0.5f );
        auto moveTo = MoveBy::create(distans/speed,Vec2(distans,0));
        auto moveBy = MoveBy::create(0.3f,Vec2(0,-10));
        yubiObg->runAction(Sequence::create(moveTo,CCCallFunc::create([&]{GameBegin::playSound("bs_fapai.mp3");}),moveBy,nullptr));
        
        if(i < 7)
        {
            
            if(shop_sale_tag != 0)
            {
                auto shop_tejia = Sprite::createWithSpriteFrameName("shop_sale_tag.png");
                shop_tejia->setScale(0.7);
                shop_tejia->setPosition(Point(yubiObg->getContentSize().width * 0.05,yubiObg->getContentSize().height* 0.95));
                yubiObg->addChild(shop_tejia,110);
            }
            sprintf(moneyTmp, "yiyuanbuffer%d",i+1);
            if(UserDefault::getInstance()->getIntegerForKey(moneyTmp) == 0 )// && UserDefault::getInstance()->getIntegerForKey("yiyuangoumai") != 0)
            {
                auto shop_tejia1 = Sprite::createWithSpriteFrameName("shop_yiyuan_buff_title.png");
                shop_tejia1->setPosition(Point(yubiObg->getContentSize().width * 0.5,yubiObg->getContentSize().height));
                yubiObg->addChild(shop_tejia1,110);
                
                auto shop_zs_bg = Sprite::createWithSpriteFrameName("shop_yiyuan_buff_bg.png");
                shop_zs_bg->setAnchorPoint(Vec2(0.5,0));
                shop_zs_bg->setPosition(Point(yubiObg->getContentSize().width * 0.5,87));
                yubiObg->addChild(shop_zs_bg,110);
               /*
                auto shop_percent = Sprite::createWithSpriteFrameName("shop_yiyuan_buff_percent.png");
                shop_percent->setPosition(Vec2(168,50));
                shop_zs_bg->addChild(shop_percent);
                
                shop_percent->runAction(Repeat::create(Sequence::create(ScaleTo::create(0.3f,1.3),ScaleTo::create(0.2f,1.0),ScaleTo::create(0.2f,1.1),DelayTime::create(0.3f),nullptr),5));
                */
              /*  sprintf(moneyTmp,"%.0f", (0.3 *  yubi_num[i] * 10000));
                auto yubizi_num1 = Label::createWithCharMap("shop_num_1.png",16,30,'0');
                yubizi_num1->setString(moneyTmp);
                yubizi_num1->setScale(0.8);
                yubizi_num1->setPosition(Vec2(95,20));
                shop_zs_bg->addChild(yubizi_num1);
                
                yubizi_num1->runAction(Repeat::create(Sequence::create(ScaleTo::create(0.3f,1),ScaleTo::create(0.2f,0.7),ScaleTo::create(0.2f,0.8),DelayTime::create(0.3f),nullptr),5));*/
            }

            sprintf(num_tmp,"img/shop_num_%d.png", 1);

        
            sprintf(moneyTmp,"%.0f", (sale_percent[shop_sale_tag] *  yubi_num[i] * 10000));
            auto yubizi_num = Label::createWithCharMap(num_tmp,16,30,'0');
            yubizi_num->setAnchorPoint(Vec2(0,0.5));
            yubizi_num->setString(moneyTmp);
            yubizi_num->setPosition(Vec2(80,320));
            yubiObg->addChild(yubizi_num);
			yubizi_num->setTag(1);
        
            sprintf(moneyTmp,"%d",(int)(sale_percent[shop_sale_tag] * (int)zuanshi_num[i]));
            auto zuanshizi_num = Label::createWithCharMap(num_tmp,16,30,'0');
            zuanshizi_num->setAnchorPoint(Vec2(0,0.5));
            zuanshizi_num->setString(moneyTmp);
            zuanshizi_num->setScale(0.9);
            zuanshizi_num->setPosition(Point(80,285));
            yubiObg->addChild(zuanshizi_num);
			zuanshizi_num->setTag(2);
            
            
			LabelTTF* pPriceLabe = LabelTTF::create("THB", "Consolas", 22);
            pPriceLabe->setAnchorPoint(Vec2(1, 0.5));
            pPriceLabe->setPosition(ccp(yubiObg->getContentSize().width - 12, yubiObg->getContentSize().height / 2 + 70));
            yubiObg->addChild(pPriceLabe);
			pPriceLabe->setTag(3);
            
            
            auto* pPayImage = Sprite::createWithSpriteFrameName("pay.png");
            pPayImage->cocos2d::Node::setPosition(Vec2(yubiObg->getContentSize().width/2, pPayImage->getContentSize().height/2 + 25));
            yubiObg->addChild(pPayImage);
            
            sprintf(moneyTmp,"%.2fusd", sPrice[i]);
            pPriceLabe->setString(moneyTmp);
            
        }
        mYubiObgs.push_back(yubiObg);
    }

	mWebPayWaitTime = 0;
    this->schedule(schedule_selector(Shop::hide_jinguang),1.5f);
}

void Shop::ios_budan()
{
    auto waitingQQ = Waiting::create();
    waitingQQ->setPosition(Point::ZERO);
    addChild(waitingQQ,1000,1001);

    this->scheduleOnce(schedule_selector(Shop::ios_budan_yy), 0.1f);
}

void Shop::ios_budan_yy(float dt)
{
  /*  string recive_data = ios_daibudan.at(ios_daibudan.size() - 1).recive_data;
    int size = ios_daibudan.size() - 1;
    ios_budan_curl(ios_daibudan.at(size).recive_data,ios_daibudan.at(size).tradeno,ios_daibudan.at(size).productid,ios_daibudan.at(size).rmb);*/
}

void Shop::ios_budan_curl(string recipeData,string tradeNo,string productID,int rmb)
{

}


size_t  Shop::ios_budan_poss(uint8_t *buffer,size_t size,size_t nmemb,void *stream)
{
 
    //返回数据长度
    size_t sizes = size*nmemb;
    return sizes;
}

//选择数据库中的数据
void Shop::get_budan_data()
{
 
}

//插入数据库
void Shop::insert_budan_data(string recipeData,string tradeNo,string productID,int rmb)//receipt-data=%s&tradeId=%s&deviceId=%s&productId=%s&rmb=%d&version=%s
{

}

void Shop::delete_budan_data(string tradeno)
{
 /*    //string tradeno1 = UserDefault::getInstance()->getStringForKey("budan_tradeID");
    int result;
    //1、打开数据库
    sqlite3 *pdb=NULL;//1
    string path= FileUtils::getInstance()->getWritablePath()+"save.db3";//2.不要漏了3
    
    result=sqlite3_open(path.c_str(),&pdb);//3
    if(result!=SQLITE_OK)
    {
        cocos2d::log("open database failed,  number%d",result);
    }else
    {
        cocos2d::log("open database success,  number%d",result);
    }
    //2.删除数据库
    char tmpSql[500];
    sprintf(tmpSql,"delete from GameOrder where tradeNo = %s",tradeno.c_str());
    result=sqlite3_exec(pdb,tmpSql, NULL,NULL,NULL);//6
    
    if(result!=SQLITE_OK)
        cocos2d::log("delete data failed!");
     cocos2d::log("delete data success,result = %d  ",result);
    
    //4、关闭数据库
    sqlite3_close(pdb);*/

}

void Shop::hide_jinguang(float dt)
{
    for(int i = 0 ; i < 5 ;i++)
    {
        if(CCRANDOM_0_1() > 0.5)
        {
            node_jinguang.at(i)->setVisible(true);
        }else
        {
            node_jinguang.at(i)->setVisible(false);
        }
    }
}

void Shop::init_vip()
{
    //控制面板
    shopCenterBg = Scale9Sprite::create( "HF_bg.jpg");
    shopCenterBg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    this->addChild(shopCenterBg);
    
    //退出按钮
    auto boss_exit = Sprite::createWithSpriteFrameName("cannon_exit.png");
    auto boss_exit_d = Sprite::createWithSpriteFrameName("cannon_exit_down.png");
    auto boss_exit_menu = Menu::create(MenuItemSprite::create(boss_exit,boss_exit_d,CC_CALLBACK_0(Shop::exit,this)),nullptr);
    boss_exit_menu->setPosition(Vec2(visibleSize.width - 48,visibleSize.height -  46 ));
    this->addChild(boss_exit_menu);
    
    //title
    auto hf_dui_title = Sprite::createWithSpriteFrameName( "vip_v2_title1.png");
    hf_dui_title->setPosition(Point(visibleSize.width/2,visibleSize.height * 0.88));
    hf_dui_title->setScale(0.85);
    this->addChild(hf_dui_title,10);
    
    //确定按钮
    auto hall_jb_sp1 = Sprite::createWithSpriteFrameName("vip_v2_queding.png");
    MenuItemSprite * hall_jb_item = MenuItemSprite::create(hall_jb_sp1,hall_jb_sp1,CC_CALLBACK_1(Shop::MenuVip,this));
    auto hall_jb_menu = Menu::create(hall_jb_item,nullptr);
    hall_jb_menu->setPosition(Vec2(visibleSize.width*0.5,visibleSize.height * 0.08));
    addChild(hall_jb_menu);
    
    cocos2d::log("hallCharTemp 3" );
    
    /*
    if(LogoLayer::dengluFlag)
    {
        auto hall_jb_icon = Sprite::create("vip_v2_price1.png");
        hall_jb_icon->setAnchorPoint(Vec2(1,0));
        hall_jb_icon->setPosition(Vec2(visibleSize.width - 10, 10));
        addChild(hall_jb_icon);
    }else
    {
        //price
        auto hall_jb_icon = Sprite::createWithSpriteFrameName("vip_v2_price.png");
        hall_jb_icon->setAnchorPoint(Vec2(1,0));
        hall_jb_icon->setPosition(Vec2(visibleSize.width - 10, 10));
        addChild(hall_jb_icon);
    }
    */
    auto priceLabel  = LabelTTF::create("5.99usd", "Consolas", 34);
    priceLabel->setAnchorPoint(Vec2(1,0));
    priceLabel->setPosition(Vec2(visibleSize.width - 30, 30));
    addChild(priceLabel);
    
    
    cocos2d::log("hallCharTemp 4" );
    
    
    roomSize = Size(208,403);
    int spaceW = 44;
    
    float speed = 1500;
    float distans;
    
    char moneyTmp[30];
    for(int i = 0; i< 4 ; i++)
    {
        sprintf(moneyTmp,"vip_v2_item_%d.png",i+1);
        auto yubiObg = Sprite::createWithSpriteFrameName(moneyTmp);
        yubiObg->setScale(0.9);
        yubiObg->setZOrder(9-i);
        yubiObg->setPosition(Point(visibleSize.width * 1.5 ,visibleSize.height/2 + 10));
        addChild(yubiObg);
 
        if( UserDefault::getInstance()->getIntegerForKey("ios_dengluFlag") == 1  )
        {
            if(i == 0){distans = visibleSize.width * 1.25;}
            if(i == 1){yubiObg->setVisible(false);distans = 0;}
            if(i == 2){distans = visibleSize.width * 1;}
            if(i == 3){distans = visibleSize.width * 0.75;}
            auto moveTo = MoveBy::create(distans/speed,Vec2(-distans,0));
            auto moveBy = MoveBy::create(0.3f,Vec2(0,-10));
            yubiObg->runAction(Sequence::create(moveTo,CCCallFunc::create([&]{GameBegin::playSound("bs_fapai.mp3");}),moveBy,nullptr));
        }else
        {
            distans = visibleSize.width * 1.5 - ((i*2 + 1) * (roomSize.width + spaceW)/2);
            auto moveTo = MoveBy::create(distans/speed,Vec2(-distans,0));
            auto moveBy = MoveBy::create(0.3f,Vec2(0,-10));
            yubiObg->runAction(Sequence::create(moveTo,CCCallFunc::create([&]{GameBegin::playSound("bs_fapai.mp3");}),moveBy,nullptr));
        }
        
    }
    this->removeChildByTag(111);
}

void Shop::init_yiyuan()
{
    //背景
    shopCenterBg = Scale9Sprite::createWithSpriteFrameName("yiyuan_bg.png");
    //mianbanBGG->setVisible(false);
    shopCenterBg->setScale(0.9);
    shopCenterBg->setPosition(Point(visibleSize.width/2,visibleSize.height * 0.5));
    this->addChild(shopCenterBg,99);
    
    auto shangchengxx = MenuItemSprite::create(Sprite::createWithSpriteFrameName("hall_menu_X.png"),Sprite::createWithSpriteFrameName("hall_menu_X_d.png"), CC_CALLBACK_0(Shop::exit,this));
    auto m_ShangChengXX= Menu::create(shangchengxx, nullptr);
    m_ShangChengXX->setPosition(Vec2(shopCenterBg->getContentSize().width - 25,shopCenterBg->getContentSize().height - 76));
    shopCenterBg->addChild(m_ShangChengXX,100);
    
    //光
    auto vip_guang = Sprite::createWithSpriteFrameName("yiyuan_shan.png");
    vip_guang->setPosition(Point(417,263));  //0.55
    shopCenterBg->addChild(vip_guang,100);
    
    vip_guang->runAction(Sequence::create(FadeOut::create(0.5f),DelayTime::create(0.5f),FadeIn::create(0.5f),DelayTime::create(0.5f) ,nullptr));
    
    //购买按钮
    auto  yiyuan_goumai = Sprite::createWithSpriteFrameName("ANG_0000.png");
    auto vioButton = MenuItemSprite::create(yiyuan_goumai,yiyuan_goumai, CC_CALLBACK_0(Shop::menu_yiyuan,this));
    auto vioButtonM= Menu::create(vioButton, nullptr);
    vioButtonM->setPosition(Vec2(430,81));
    shopCenterBg->addChild(vioButtonM,100);
    
    auto yiyuan_goumai_A = Animate::create(AnimationCache::getInstance()->getAnimation("yiyuan_goumai"));
    yiyuan_goumai->runAction(RepeatForever::create(Sequence::create(yiyuan_goumai_A,DelayTime::create(2.0f),nullptr)));
}

bool Shop::init(int btnKind)
{  
	if ( !Layer::init() )	
	{
		return false;
	}
    
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bridge = new IOSiAP_Bridge();
#endif
	shanchuTmp = 1;
	comeKind = btnKind;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();
	shop_sale_tag = UserDefault::getInstance()->getIntegerForKey("shop_sele_tag");

	auto zheZhao = LayerColor::create(ccc4(0,0,0,150),1024,768);
	zheZhao->setPosition(Point::ZERO);
	zheZhao->setScale(2.0f);
	this->addChild(zheZhao);

	BigPaySuccess = false;

	if(comeKind < 4 || comeKind == 8)
	{
		init_shop();
	}
	if(comeKind == 4 || comeKind == 5)
	{
		init_vip();
	}
    
    if(comeKind == 6)
    {
        init_yiyuan();
    }

    if(shopCenterBg)
    {
        shopCenterBg->setScale(0.1f);
        ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);
        ScaleTo *ac8=ScaleTo::create(0.1f, 1.0);
        shopCenterBg->runAction(Sequence::create(ac7,ac8,nullptr));
    }
    
	bFeiFa = false;
 
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Shop::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(Shop::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(Shop::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	this->scheduleUpdate();

	return true;
}

void Shop::MenuVip(Ref* pSender)
{ 
	buyYuBi(6);
}

void Shop::menu_yiyuan()
{
    buyYuBi(7);
}

void Shop::update(float dt)
{

    if(huifuFlag)
    {
        this->removeChildByTag(1001,true);
        huifuFlag = false;
        
        
        if(comeKind == 1)
            comeKind = 4;
        if(comeKind == 2 )
            comeKind = 5;
        
        time_t currentTime;
        time(&currentTime);
        time_t prevTime = UserDefault::getInstance()->getIntegerForKey("vip_login_time");
        if(currentTime<prevTime)
        {
            auto  gongxi = Gongxi::create(2,GAME_DATA_STRING("LingState1One"));
            this->addChild(gongxi,MENULAYER + 100);
            return;
        }
        
        buyYuBiSuc(10);
    }
	if(failFlag)
	{
        this->removeChildByTag(1001,true);
		failFlag = false;
        
        
    }
	if(yanZhengFlag)//||BigPaySuccess)
	{

        this->removeChildByTag(1001,true);

		yanZhengFlag = false;
		buyYuBiSuc(orderShopKind);
	}

	if(yanzhengFailFlag )
	{
		yanzhengFailFlag = false;

		char gongxiTmp[30];
		sprintf(gongxiTmp,"check_order_%d",yanzhengInt);
		auto gongxi = Gongxi::create(2,GAME_DATA_STRING(gongxiTmp));
		gongxi->setPosition(Point::ZERO);
		this->addChild(gongxi,1000);

	}
	if(bFeiFa == true)
	{
		bFeiFa = false;

        this->removeChildByTag(1001,true);

        auto gongxi = Gongxi::create(2, GAME_DATA_STRING("shop_budan"));
        this->addChild(gongxi, MENULAYER);

		auto layer = this->getParent();
		this->removeFromParentAndCleanup(true);       

	}
}


void Shop::huifugoumai()
{
    auto waitingQQ = Waiting::create();
    addChild(waitingQQ,1000,1001);
    
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bridge->requestProducts(88);
#endif
}
void Shop::buyYuBiSuc(int flag)
{

	int zengjiagold = 0;
	int zengjiazuanshi = 0;
	int yanzhengRMB = 0;

	GameScene::bShowShangCheng = false;
    GameBegin::playSound("goumai_suc.mp3");
    if(flag == 6  && LogoLayer::dengluFlag == true)
    {
        flag = 11;
    }

	switch(flag)
	{
        case 0:	{
					if(mIsMSMPay)
					{
						zengjiagold = yubiNumMSM[0] * 10000 ;zengjiazuanshi = zuanshi_num[0];	yanzhengRMB = 5;	
					}
					else
					{
						zengjiagold = yubi_num[0] * 10000 ;zengjiazuanshi = zuanshi_num[0];	yanzhengRMB = 6;	
					}
				}break;
		case 1:	{
					if (mIsMSMPay)
					{
						zengjiagold = yubiNumMSM[1] * 10000 ;	zengjiazuanshi = zuanshi_num[1];	yanzhengRMB = 10;	
					}
					else
					{
						zengjiagold = yubi_num[1] * 10000 ;	zengjiazuanshi = zuanshi_num[1];	yanzhengRMB = 12;	
					}
					
				}break;
		case 2:	{

					if (mIsMSMPay)
					{
						zengjiagold = yubiNumMSM[2] * 10000 ;	zengjiazuanshi = zuanshi_num[2];	yanzhengRMB = 28;	
					}
					else
					{
						zengjiagold = yubi_num[2] * 10000 ;	zengjiazuanshi = zuanshi_num[2];	yanzhengRMB = 30;	
					}
					
				}break;
		case 3:	{

					if (mIsMSMPay)
					{
						zengjiagold = yubiNumMSM[3] * 10000 ;	zengjiazuanshi = zuanshi_num[3];	yanzhengRMB = 47;	
					}
					else
					{
						zengjiagold = yubi_num[3] * 10000 ;	zengjiazuanshi = zuanshi_num[3];	yanzhengRMB = 68;	
					}
				}break;
		case 4:	{zengjiagold = yubi_num[4] * 10000 ;	zengjiazuanshi = zuanshi_num[4];	yanzhengRMB = 128;	}break;
		case 5:	{zengjiagold = yubi_num[5] * 10000 ;	zengjiazuanshi = zuanshi_num[5];	yanzhengRMB = 258;	}break;
        case 6:{zengjiagold = 0;		zengjiazuanshi = 0;		yanzhengRMB = 40;
            UserDefault::getInstance()->setIntegerForKey("player_vip",1);
            time_t timevip;
            time(&timevip);
            UserDefault::getInstance()->setIntegerForKey("player_vip_time",timevip);
            UserDefault::getInstance()->flush();}break;
        case 7: {zengjiagold = 20000;	zengjiazuanshi = 0;		yanzhengRMB = 1;
            UserDefault::getInstance()->setIntegerForKey("yiyuangoumai",1);
            UserDefault::getInstance()->flush();}break;
        case 8:
            {
                zengjiagold = 900000;
            }
            break;
        case 9:zengjiagold = 1810000;break;
        case 10:{zengjiagold = 20000 ;	zengjiazuanshi = 1000;	yanzhengRMB = 1;}break;
        case 11:{zengjiagold = 400000 ;	zengjiazuanshi = 1000;	yanzhengRMB = 40;}break;
		default:break;
	}
    if( flag+1 < 7 || flag+1 > 8)
    {
        zengjiagold = (int)zengjiagold * sale_percent[shop_sale_tag];
        zengjiazuanshi = (int)zengjiazuanshi * sale_percent[shop_sale_tag];
        
        char tmp_shop_buff_char[50];
        sprintf(tmp_shop_buff_char,"yiyuanbuffer%d",flag+1);
        if( UserDefault::getInstance()->getIntegerForKey(tmp_shop_buff_char) == 0) //UserDefault::getInstance()->getIntegerForKey("yiyuangoumai") != 0 &&
        {
            UserDefault::getInstance()->setIntegerForKey(tmp_shop_buff_char,1);
            zengjiagold = zengjiagold * 1.3;
        }
    }
	//modifyOrderFlag(defineData,1);
	cocos2d::log("budan cheng  gong ");
 
	 
	UserDefault::getInstance()->setIntegerForKey("leijichongzhicaijin",yanzhengRMB + UserDefault::getInstance()->getIntegerForKey("leijichongzhicaijin"));
    
	UserDefault::getInstance()->flush();
	//DCVirtualCurrency::paymentSuccess("wfgs","123",yanzhengRMB,"CNY","短代" );

	//GameBegin::baidu_qiehuan();//更新服务器数据

    if(comeKind == 6)
    {
        //DCEvent::onEvent("goumaiyiyuan");
        GameHallLayer::RefreshCoin(zengjiagold);
        GameHallLayer::checkRedPoing = true;
        GameBegin::setFileData("gameMaxPao.txt",20);
        
        this->getParent()->removeChildByTag(611);
        
        char textTmp[100];
        sprintf(textTmp,GAME_DATA_STRING("goumai_yiyuan"),zengjiagold);
        auto  gongxi = Gongxi::create(4,textTmp);
        gongxi->setPosition(Point::ZERO);
        this->getParent()->addChild(gongxi,ANNIULAYER + 100);
        
        string paoname_tmp[4] = {"paothree.png","paofour.png","paofive.png","paosix.png"};
        //string wangname_tmp[5] = {"net_1.png","net_1.png","net2wf.png","net_2.png","net_3.png"};
        float height = 0.35f;
        Vec2 pao_pos[4] = {Vec2(visibleSize.width * 0.38,visibleSize.height*height),Vec2(visibleSize.width * 0.46,visibleSize.height*height),Vec2(visibleSize.width * 0.54,visibleSize.height*height),Vec2(visibleSize.width * 0.62,visibleSize.height*height)};
        Vec2 BeginPos = Vec2(visibleSize.width * 0.31,visibleSize.height * 0.95);
        float time_space = 0.1f;
        float speed =400;
        for(int i = 0 ; i < 4 ; i++)
        {
            auto pao_sp = Sprite::createWithSpriteFrameName(paoname_tmp[i]);
            pao_sp->setPosition(pao_pos[i]);
            pao_sp->setScale(0.7);
            pao_sp->setVisible(false);
            this->getParent()->addChild(pao_sp,ANNIULAYER + 101);
            
            float duration = ccpDistance(pao_sp->getPosition(), BeginPos) / speed;
            
            auto wang_sp = Sprite::createWithSpriteFrameName("hall_ssxx_bg.png");
            wang_sp->setScale(2);
            wang_sp->setPosition(pao_sp->getContentSize()/2);
            pao_sp->addChild(wang_sp,-1);
            
            wang_sp->runAction(RepeatForever::create(RotateBy::create(1.0f,50)));
            wang_sp->runAction(Sequence::create(DelayTime::create(time_space),DelayTime::create(0.9f + duration),FadeOut::create(0.3f),RemoveSelf::create(),NULL));
            
            JumpTo *jump1  = JumpTo::create(0.3f,pao_pos[i],60,1);
            JumpTo *jump2  = JumpTo::create(0.3f,pao_pos[i],50,1);
            JumpTo *jump3  = JumpTo::create(0.3f,pao_pos[i],15,1);
            
            MoveTo* moveTo = MoveTo::create(duration ,BeginPos);
            auto seq = Sequence::create(DelayTime::create(time_space),ToggleVisibility::create(),jump1,jump2,jump3,moveTo,CallFunc::create([&]{GameBegin::buttonSound();}),FadeOut::create(0.3f),RemoveSelf::create(),NULL);
            pao_sp->runAction(seq);
            
            time_space+=0.1f;
            
        }
        
        ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
        ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
        shopCenterBg->runAction(Sequence::create(ac7,ac8,nullptr)); 
        
        this->runAction(Sequence::create(DelayTime::create(0.3f),RemoveSelf::create(),nullptr));
        //	this->scheduleOnce(schedule_selector(Shop::shanchu),1.5f);
        return;
    }
    
	if(comeKind == 5 )
	{

		GameScene::vip_goumai_flag = true;
		this->removeFromParentAndCleanup(true);

		return;
	}

	if(comeKind == 4 )
	{
		if(GameBegin::getFileData("gameMaxPao.txt") < 8)
		{
			auto  gongxi = VIPgongxi::create(1);
			this->getParent()->addChild(gongxi,ANNIULAYER + 100);
            
            if(LogoLayer::dengluFlag)
            {
                GameHallLayer::RefreshCoin(20000);
                GameHallLayer::RefreshDiamond(200);

            }
            
			VIPgongxi::gamehall_re = true;
			this->removeFromParentAndCleanup(true);
			//this->scheduleOnce(schedule_selector(Shop::shanchu),2.0f);
		}else
		{
			GameHallLayer::vip_goumai_flag = true;
			this->removeFromParentAndCleanup(true);
		}
		
		return;
	}

	if(comeKind == 1)
	{
        //DCEvent::onEvent("dating_goumai");
		GameHallLayer::RefreshCoin(zengjiagold);
		GameHallLayer::RefreshDiamond(zengjiazuanshi);
	}
	if(comeKind == 2 )
	{
        if(GameScene::cGameType == 1)
        {
             //DCEvent::onEvent("changjing_bisai_goumai");
        }else
        {
             //DCEvent::onEvent("changjing_danji_goumai");
        }
		CannonLayer::GameCoinRefresh(zengjiagold);
        CannonLayer::iMoneyJiangchi = GameBegin::getFileData("jywer.txt");
		CannonLayer::GameCoinZuanshi(zengjiazuanshi);
        GameBegin::baidu_qiehuan();
	}
	if(comeKind == 3  )
	{
        //DCEvent::onEvent("dapaoshengji_goumai");
		CannonUpgrade::RefreshCoin(zengjiagold);
		CannonUpgrade::RefreshDiamond(zengjiazuanshi);
	} 
	if(comeKind == 8  )
	{
        //DCEvent::onEvent("yuanzheng_goumai");
		ChallengeBOSS::RefreshCoin(zengjiagold);
		ChallengeBOSS::RefreshDiamond(zengjiazuanshi);
	} 

	if(GameBegin::getFileData("jywer.txt") > 10000  && comeKind == 1 && GameBegin::getFileData("gameMaxPao.txt") < 8)
	{
		char textTmp[100];
		sprintf(textTmp,GAME_DATA_STRING("goumai_chenggong"),zengjiagold,zengjiazuanshi);
		auto  gongxi = Gongxi::create(4,textTmp);
		gongxi->setPosition(Point::ZERO);
		addChild(gongxi,ANNIULAYER + 100);

		this->scheduleOnce(schedule_selector(Shop::shanchu),1.5f);
	}else
	{
		auto layer = this->getParent();
		char textTmp[100];
		sprintf(textTmp,GAME_DATA_STRING("goumai_chenggong"),zengjiagold,zengjiazuanshi);
		
		auto  gongxi = Gongxi::create(4,textTmp);
		gongxi->setPosition(Point::ZERO);
		layer->addChild(gongxi,ANNIULAYER + 100);
		this->removeFromParentAndCleanup(true);
	}
}
 
void Shop::shanchu(float dt)
{

	GameBegin::setFileData("gameMaxPao.txt",8);
    
    this->stopAllActions();
    this->removeAllChildrenWithCleanup(true);
    this->unscheduleAllSelectors();
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();

	auto scene = GameHallLayer::createScene();
	Director::getInstance()->replaceScene(scene);

}

void Shop::buyYuBi(int iii)
{
    //if(iii < 0)
    //    return;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	GameBegin::buttonSound(); 
	JNativeToJavaUtil::DoPay(iii);
	return;
#endif

	GameBegin::buttonSound(); 

	auto waitingQQ = Waiting::create();
	addChild(waitingQQ,1000,1001);
 
    bool bTempCeShi = false;

    //新增
    if(iii == 0)
    {
        orderShopKind = 0;
        goumaileixing = "6yuanyubi";
        

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        yanZhengFlag = true;
#endif
        
        
        
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        if(bTempCeShi == true)
        {
            
            Shop::yanZhengFlag = true;
        }
        else
            bridge->requestProducts(6);
#endif
    }
    
	//第一类鱼币
	if(iii == 1)
	{
		orderShopKind = 1;
		goumaileixing = "8yuanyubi";
 
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		yanZhengFlag = true;
#endif  

        
 
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		if(bTempCeShi == true)
        {
            
            Shop::yanZhengFlag = true;
        }
        else
        bridge->requestProducts(12);
#endif      		
	}

	//第二类鱼币
	if(iii == 2)
	{
		orderShopKind = 2;
		goumaileixing = "20yuanyubi";
	 
        
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		yanZhengFlag = true;
#endif  


#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	
        if(bTempCeShi == true)
        {
            
            Shop::yanZhengFlag = true;
        }
        else
        {
          bridge->requestProducts(30);
        }
      
#endif
	}

	//第三类鱼币
	if(iii == 3)
	{
		orderShopKind = 3;
		goumaileixing = "30yuanyubi";
		 
 
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		yanZhengFlag = true;
#endif  


#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		
        if(bTempCeShi == true)
        {
            
            Shop::yanZhengFlag = true;
        }
        else
        bridge->requestProducts(68);
#endif

	}

	//第四类鱼币
	if(iii == 4)
	{
		orderShopKind = 4;
		goumaileixing = "50yuanyubi";
	 

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		yanZhengFlag = true;
#endif  


#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		
        if(bTempCeShi == true)
        {
            
            Shop::yanZhengFlag = true;
        }
        else
        bridge->requestProducts(128);
#endif
	}

	//第五类鱼币
	if(iii == 5)
	{
		orderShopKind = 5;
		goumaileixing = "100yuanyubi";
	 
 
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		yanZhengFlag = true;
#endif  


#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		
         //Shop::yanZhengFlag = true;
        
        if(bTempCeShi == true)
        {
            
            Shop::yanZhengFlag = true;
        }
        else
        bridge->requestProducts(258);
#endif

	}

	//第六类 Vip
	if(iii == 6)
	{
		orderShopKind = 6;
		goumaileixing = "20yuanvip";
		 
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		yanZhengFlag = true;
#endif  

 

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        if(bTempCeShi == true)
        {
            Shop::yanZhengFlag = true;
        }
        else
        {
            
            bridge->requestProducts(40);
        }
        
#endif

	}
 

	//yiyuan
	if(iii == 7)
	{
        orderShopKind = 7;
		goumaileixing = "1yuanyubi";
		 
 
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		yanZhengFlag = true;
#endif  


#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        if(bTempCeShi == true)
        {
            
            Shop::yanZhengFlag = true;
        }
        else
        {
            if(LogoLayer::dengluFlag)
            {
                bridge->requestProducts(1);
            }else
            {
                bridge->requestProducts(11);
            }
        }
#endif

	}
    
    if(iii == 8)
    {
        orderShopKind = 8;
        goumaileixing = "60yuanjijin";
        if(bTempCeShi == true)
        {
            
            Shop::yanZhengFlag = true;
        }
        else
        {
        //    bridge->requestProducts(60);
        }
    }
    
    if(iii == 9)
    {
        orderShopKind = 9;
        goumaileixing = "88yuanjijin";
        if(bTempCeShi == true)
        {
            
            Shop::yanZhengFlag = true;
        }
        else
        {
       //     bridge->requestProducts(90);
        }
    }
    
    if(iii == 10)
    {
        orderShopKind = 10;
        goumaileixing = "1yuanyubi";
        if(bTempCeShi == true)
        {
            
            Shop::yanZhengFlag = true;
        }
        else
        {
       //     bridge->requestProducts(11);
        }
        
    }
    
    if(iii == 11)
    {
        orderShopKind = 11;
        goumaileixing = "40yuanyubi";
        if(bTempCeShi == true)
        {
            
            Shop::yanZhengFlag = true;
        }
        else
        {
        //    bridge->requestProducts(40);
        }
    }

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if(isCeShi)
	{
		yanZhengFlag = true;
	}else
	{
		JNativeToJavaUtil::DoPay(iii);
	}

#endif
    
}


void Shop::buyYuBiBySMS(int room)
{
	orderShopKind = room;


	auto waitingQQ = Waiting::create();
	addChild(waitingQQ,1000,1001);

	bool bTempCeShi = false;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	yanZhengFlag = true;
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if(isCeShi)
	{
		yanZhengFlag = true;
	}else
	{
		JNativeToJavaUtil::DoPayBySMS(sPriceMSM[room]);
	}

#endif
}


void Shop::buyYuBiSucBySMS(int flag)
{

}


 
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)	
JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_buySuccess(JNIEnv * env, jclass)
{
	Shop::successFlag = true;
}

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_buyFail(JNIEnv * env, jclass)
{
	Shop::failFlag = true;
}

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_buyIng(JNIEnv * env, jclass)
{
	Shop::budanFlag = true;
}
#endif

bool Shop::onTouchBegan(Touch* touch, Event* event) 
{
    if(otherpay == true)
    {
        return true;
    }
    if(comeKind < 4 || comeKind == 8)
    {
        p1 = touch->getLocation();
        
        if(p1.y < visibleSize.height/2 + roomSize.height/2 * SHOP_ROOM_L && p1.y > visibleSize.height/2 - roomSize.height/2 * SHOP_ROOM_L)
        {
            float yubiWidth =  yubiView->getViewSize().width;
            float room_x = p1.x -(visibleSize.width - yubiWidth)/2;
            
            if (room_x > 0 && room_x < yubiWidth)
            {
                room_x = room_x + layer_x;
                if(room_x >sp_yubi.at(0)->getPositionX() -  roomSize.width * SHOP_ROOM_L/2 && room_x < sp_yubi.at(0)->getPositionX() + roomSize.width * SHOP_ROOM_L/2)
                {
                    cur_room = 1;
                    sp_yubi.at(0)->setScale(SHOP_ROOM_H);
                }else if(room_x >sp_yubi.at(1)->getPositionX() -  roomSize.width * SHOP_ROOM_L/2 && room_x < sp_yubi.at(1)->getPositionX() + roomSize.width * SHOP_ROOM_L/2)
                {
                    cur_room = 2;
                    sp_yubi.at(1)->setScale(SHOP_ROOM_H);
                }else if(room_x >sp_yubi.at(2)->getPositionX() -  roomSize.width * SHOP_ROOM_L/2 && room_x < sp_yubi.at(2)->getPositionX() + roomSize.width * SHOP_ROOM_L/2)
                {
                    cur_room = 3;
                    sp_yubi.at(2)->setScale(SHOP_ROOM_H);
                }else if(room_x >sp_yubi.at(3)->getPositionX() -  roomSize.width * SHOP_ROOM_L/2 && room_x < sp_yubi.at(3)->getPositionX() + roomSize.width * SHOP_ROOM_L/2)
                {
                    cur_room = 4;
                    sp_yubi.at(3)->setScale(SHOP_ROOM_H);
                }else if(room_x >sp_yubi.at(4)->getPositionX() -  roomSize.width * SHOP_ROOM_L/2 && room_x < sp_yubi.at(4)->getPositionX() + roomSize.width * SHOP_ROOM_L/2)
                {
                    cur_room = 5;
                    sp_yubi.at(4)->setScale(SHOP_ROOM_H);
                }
                else if(room_x >sp_yubi.at(5)->getPositionX() -  roomSize.width * SHOP_ROOM_L/2 && room_x < sp_yubi.at(5)->getPositionX() + roomSize.width * SHOP_ROOM_L/2)
                {
                    cur_room = 6;
                    sp_yubi.at(5)->setScale(SHOP_ROOM_H);
                }
                if(LogoLayer::dengluFlag)
                {
                    if(room_x >sp_yubi.at(6)->getPositionX() -  roomSize.width * SHOP_ROOM_L/2 && room_x < sp_yubi.at(6)->getPositionX() + roomSize.width * SHOP_ROOM_L/2)
                    {
                        cur_room = 7;
                        sp_yubi.at(6)->setScale(SHOP_ROOM_H);
                    }
                }
 
                
            }
        }
    }
    
    return true;
}

void Shop::onTouchMoved(Touch* touch, Event* event) 
{

}

void Shop::onTouchEnded(Touch* touch, Event* event)
{
    
    if(otherpay == true)
    {
        return;
    }
    
	if(comeKind < 4
       || comeKind == 8)
	{
		p2 = touch->getLocation();
		cocos2d::log("offset pos is %f ",p2.x);  
		if(cur_room > 0 &&abs(p2.x - p1.x) < 8     )
		{
            if(cur_room < 8)
			{
				if (mIsMSMPay)
				{
					buyYuBiBySMS(cur_room-1);
				}
				else
				{
					 buyYuBi(cur_room-1);
				}
              
			}
        }
		if(cur_room > 0)
		{
			sp_yubi.at(cur_room - 1)->setScale(SHOP_ROOM_L);
			cur_room = 0;
		}
	}
}


void Shop::shopMsg()
{
	otherpay = false;
	mIsMSMPay = true;
	m_SprShopSMS->setVisible(true);
	m_SprShopMol->setVisible(false);
	m_SprShopTrue->setVisible(false);
	m_SprShopApp->setVisible(false);

	if(this->getChildByTag(150) != NULL)
		this->removeChild(this->getChildByTag(150));

	resetYubiObg();
}


void Shop::shoptrue()
{
    otherpay = true;
	mIsMSMPay = false;
    m_SprShopApp->setVisible(false);
    m_SprShopMol->setVisible(false);
    m_SprShopTrue->setVisible(true);
	m_SprShopSMS->setVisible(false);
    
    if(this->getChildByTag(150) != NULL)
    this->removeChild(this->getChildByTag(150));
    
    Size sf = shopCenterBg->getContentSize();
    WebViewTest* loginscene = WebViewTest::create(2,sf.height,sf.width);
    loginscene->setPosition(Point::ZERO);
    loginscene->setTag(150);
    this->addChild(loginscene,100);
 
    
}
void Shop::shopmol()
{
    otherpay = true;
	mIsMSMPay = false;
    m_SprShopApp->setVisible(false);
    m_SprShopMol->setVisible(true);
    m_SprShopTrue->setVisible(false);
	m_SprShopSMS->setVisible(false);
    
    if(this->getChildByTag(150) != NULL)
    this->removeChild(this->getChildByTag(150));
    
    Size sf = shopCenterBg->getContentSize();
    WebViewTest* loginscene = WebViewTest::create(1,sf.height,sf.width);
    loginscene->setPosition(Point::ZERO);
    loginscene->setTag(150);
    this->addChild(loginscene,100);
    


}
void Shop::shopapp()
{
     otherpay = false;
	 mIsMSMPay = false;
    m_SprShopApp->setVisible(true);
    m_SprShopMol->setVisible(false);
    m_SprShopTrue->setVisible(false);
	m_SprShopSMS->setVisible(false);
    
    if(this->getChildByTag(150) != NULL)
    this->removeChild(this->getChildByTag(150));
    
	resetYubiObg();

}
void Shop::exit()
{
    GameBegin::buttonSound();
    GameScene::bShowShangCheng = false;
    GameScene::stopBossTime = false;
    
    
    ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);
    ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);
    
    if(comeKind == 4 || comeKind == 5)
    {
        this->runAction(Sequence::create(ac7,ac8,RemoveSelf::create(),nullptr));
    }
    else
    {
        shopCenterBg->runAction(Sequence::create(ac7,ac8,nullptr));
        this->runAction(Sequence::create(DelayTime::create(0.3f),RemoveSelf::create(),nullptr));
    }
}

void Shop::scrollViewDidScroll(extension::ScrollView* view) 
{

	layer_x = abs(view->getContentOffset().x);//获得偏移X坐标(向右移动，偏移量为正数，向左则为负数）  
	cocos2d::log("offset pos is %f ",layer_x);  

}


void Shop::yanZhengOrder(string defineData,string tradeNO)
{
    //测试补单
    //insert_budan_data(defineData, tradeNO, IOSiAP_Bridge::productIDPass.c_str(),IOSiAP_Bridge::productID);
    //bFeiFa = true;
   // return;
  /*  
    CURL *curl;
    CURLcode res;
    std::string cc;
    curl=curl_easy_init();
    string DeviceNo =  UserDefault::getInstance()->getStringForKey("DeviceNo");
    string version = GAME_DATA_STRING("game_version");
    
    char postFields[5000];
    
    if(IOSiAP_Bridge::productID  == 90)
    {
        IOSiAP_Bridge::productID = 88;
    }
    if(IOSiAP_Bridge::productID  == 11)
    {
        IOSiAP_Bridge::productID = 1;
    }
    sprintf(postFields,"receipt-data=%s&tradeId=%s&deviceId=%s&productId=%s&rmb=%d&version=%s",
            defineData.c_str(),tradeNO.c_str(),DeviceNo.c_str(),IOSiAP_Bridge::productIDPass.c_str(),IOSiAP_Bridge::productID,version.c_str());
    cocos2d::log("IOSiAP_Bridge:: ****postFields:%s  ****",postFields);
    if(curl)
    {
        
            curl_easy_setopt( curl, CURLOPT_URL, "http://dwby-hk.iyueyo.com/qpby2/iosfanti/shop/ios_iap.php"); //请求的地址
        curl_easy_setopt(curl, CURLOPT_POST, true);           //启用POST提交
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields); //发送的数据
        curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&iosPossIt); //处理的函数
        curl_easy_setopt(curl, CURLOPT_TIMEOUT,3000);
        res=curl_easy_perform(curl);
        if(res!=CURLE_OK)
        {
            log("联网超时 %i",res);
            insert_budan_data(defineData, tradeNO, IOSiAP_Bridge::productIDPass.c_str(),IOSiAP_Bridge::productID);
            bFeiFa = true;
        }
        curl_easy_cleanup(curl);
        return ;
    }
    else
    {
        cocos2d::log("curl shi kong de ");
        insert_budan_data(defineData, tradeNO, IOSiAP_Bridge::productIDPass.c_str(),IOSiAP_Bridge::productID);
        
        bFeiFa = true;
        return ;
    }*/
}

size_t  Shop::iosPossIt(uint8_t *buffer,size_t size,size_t nmemb,void *stream)
{
 /*   //打印收到的数据
    cocos2d::log("SHOP::*****possIt_____%s____",(const char *)buffer);
    //string orderID = UserDefault::getInstance()->getStringForKey("orderID");
    int tmpRMB = atoi((const char *)buffer);
    if(tmpRMB == 1)//成功
    {
        Shop::yanZhengFlag = true;
        
      
    }
    else if(tmpRMB > 10)
    {
        CCLOG("订单失败！");
        failFlag = true;
        //   iosBuyFailFlag = true;
    }
    else
    {
        failFlag = true;
        // Shop::bFeiFa = true;
    }
    */
    //返回数据长度
    size_t sizes = size*nmemb;
    return sizes;
}


void Shop::webPayFinish( cocos2d::Ref* pRef )
{
	bool isPaySuccess = *(bool*)pRef;
	cocos2d::log("webPayFinish = %d", isPaySuccess);
	isWebPaySuccess = isPaySuccess;

	this->scheduleOnce(schedule_selector(Shop::webPayFinishTimer), 0.0f);	
	//this->schedule(schedule_selector(Shop::webPayFinishTimer), 0.05f);
}

void Shop::webPayFinishTimer(float dt)
{
	cocos2d::log("webPayFinishTimer");

	//add by zxf
	if (this->getChildByTag(150) != NULL)
		this->removeChild(this->getChildByTag(150));
	if (!isWebPaySuccess) return;

	auto waitingQQ = Waiting::create();
	addChild(waitingQQ,1000,1001);


	//取得Room Sokcet
		TcpClientSocket *ptempHallSocket = LogoLayer::GetSocket();
	ptempHallSocket->CloseSocket();

	ptempHallSocket->ConnectServer((char*)LogoLayer::gHIpStr.data(), LogoLayer::gHPortStr);

	if(ptempHallSocket->IsConnect() == false)
	{

	}
	else
	{
		ChongZhiSend ChongZhiSendMsg;
		int id =CCUserDefault::getInstance()->getIntegerForKey("myid");
		cocos2d::log("id = %d",id);
		ChongZhiSendMsg.account =  htonl(id);
		ptempHallSocket->SendMsgToSocket(&ChongZhiSendMsg, CHONGZHISEND, sizeof(ChongZhiSend));

	}
	this->schedule(schedule_selector(Shop::webPayCallbackTimer), 0.08f);
	
}


void Shop::webPayCallbackTimer(float dt)
{
	cocos2d::log("webPayCallbackTimer");

	mWebPayWaitTime += dt;
	if (mWebPayWaitTime > 10)
	{
		mWebPayWaitTime = 0;

		Waiting* waitingQQ = (Waiting*)this->getChildByTag(1001);
		if (waitingQQ)
		{
			waitingQQ->removeFromParent();
		}
		
		
		exit();
		return;
	}
	// 取得 Game Sokcet
	TcpClientSocket *ptempHallSocket = LogoLayer::GetSocket();



	int tempRecvLength;

	char *pRecvBuffer;

	ptempHallSocket->RecvPack(&pRecvBuffer, tempRecvLength);
	fishHead dataHead={0};
	//已处理封包长度
	int tempPackLength = 0;

	// 检查有无资料
	if(tempRecvLength > 0)
	{
		fishHead dataHead={0};
		memcpy(&dataHead,pRecvBuffer,sizeof(fishHead));
		dataHead.len=ntohl(dataHead.len);
		if(dataHead.type==CHONGZHIBAK)
		{
			ChongZhiBak* ChongZhiBakMsg = (ChongZhiBak*)(pRecvBuffer+sizeof(fishHead));

			int zengjiagold =ntohl(ChongZhiBakMsg->coin);
			int zengjiazuanshi =ntohl(ChongZhiBakMsg->diamond);

			

			cocos2d::log("zengjiagold = %d, zengjiazuanshi = %d", zengjiagold, zengjiazuanshi);
			cocos2d::log("Shop::comeKind  = %d",Shop::comeKind );
			//add by zxf
			//warn 由于后台无法判断充值是否成功，一律发充值成功信息过来
			//因此程序一直走充值成功逻辑，如果充值失败的话，增加的货币是0，所以这边做下保护，如果是0return掉
			if (zengjiagold <= 0)
			{ 
				Waiting* waitingQQ = (Waiting*)this->getChildByTag(1001);
				if (waitingQQ)
				{
					waitingQQ->removeFromParent();
				}
				return;
			}
			if(Shop::comeKind == 1)
			{

				GameHallLayer::RefreshCoin(zengjiagold);
				GameHallLayer::RefreshDiamond(zengjiazuanshi);

		//		this->removeChild( _webView);
				cocos2d::log("RefreshFinish");

				auto layer = this->getParent();
				char textTmp[100];
				sprintf(textTmp,GAME_DATA_STRING("goumai_chenggong"),zengjiagold,zengjiazuanshi);


				cocos2d::log("11111111111111111111111111111111111");

				ptempHallSocket->CloseSocket();
				this->unscheduleAllSelectors();

				cocos2d::log("22222222222222222222222222222222222222222222");

				auto  gongxi = Gongxi::create(4,textTmp);
				gongxi->setPosition(Point::ZERO);
				layer->addChild(gongxi,ANNIULAYER + 100);
				this->removeFromParentAndCleanup(true);


				cocos2d::log("33333333333333333333333333333");
				/*
				char textTmp[100];
				sprintf(textTmp,GAME_DATA_STRING("goumai_chenggong"),zengjiagold,zengjiazuanshi);

				auto  gongxi = Gongxi::create(4,textTmp);
				gongxi->setPosition(Point::ZERO);
				this->addChild(gongxi);
				*/

			}
			if(Shop::comeKind == 2 )
			{

				CannonLayer::GameCoinRefresh(zengjiagold);
				CannonLayer::GameCoinZuanshi(zengjiazuanshi);
			//	this->removeChild( _webView);
				auto layer = this->getParent();
				char textTmp[100];
				sprintf(textTmp,GAME_DATA_STRING("goumai_chenggong"),zengjiagold,zengjiazuanshi);


				ptempHallSocket->CloseSocket();
				this->unscheduleAllSelectors();

				auto  gongxi = Gongxi::create(4,textTmp);
				gongxi->setPosition(Point::ZERO);
				layer->addChild(gongxi,ANNIULAYER + 100);
				this->removeFromParentAndCleanup(true);

			}

			if(Shop::comeKind == 3  )
			{
				CannonUpgrade::RefreshCoin(zengjiagold);
				CannonUpgrade::RefreshDiamond(zengjiazuanshi);
			//	this->removeChild( _webView);
				auto layer = this->getParent();
				char textTmp[100];
				sprintf(textTmp,GAME_DATA_STRING("goumai_chenggong"),zengjiagold,zengjiazuanshi);

				ptempHallSocket->CloseSocket();
				this->unscheduleAllSelectors();

				auto  gongxi = Gongxi::create(4,textTmp);
				gongxi->setPosition(Point::ZERO);
				layer->addChild(gongxi,ANNIULAYER + 100);
				this->removeFromParentAndCleanup(true);

			}
			if(Shop::comeKind == 8  )
			{
				ChallengeBOSS::RefreshCoin(zengjiagold);
				ChallengeBOSS::RefreshDiamond(zengjiazuanshi);



			//	this->removeChild( _webView);
				auto layer = this->getParent();
				char textTmp[100];
				sprintf(textTmp,GAME_DATA_STRING("goumai_chenggong"),zengjiagold,zengjiazuanshi);


				ptempHallSocket->CloseSocket();
				this->unscheduleAllSelectors();

				auto  gongxi = Gongxi::create(4,textTmp);
				gongxi->setPosition(Point::ZERO);
				layer->addChild(gongxi,ANNIULAYER + 100);
				this->removeFromParentAndCleanup(true);
			}
		}
	}
	else
	{	
		ChongZhiSend ChongZhiSendMsg;
		int id =CCUserDefault::getInstance()->getIntegerForKey("myid");
		cocos2d::log("id = %d",id);
		ChongZhiSendMsg.account =  htonl(id);
		ptempHallSocket->SendMsgToSocket(&ChongZhiSendMsg, CHONGZHISEND, sizeof(ChongZhiSend));
	}
}

void Shop::scrollViewDidZoom(extension::ScrollView* view) 
{
}

Shop::Shop()
{
	Shop::pStaticShop = this;
	_event = Director::getInstance()->getEventDispatcher()->addCustomEventListener(Shop::GOOGLE_PAY, std::bind(&Shop::onPayChanged, this, std::placeholders::_1));
	_event->retain();
	NotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(Shop::webPayFinish), "webPayFinish", NULL);
}

Shop::~Shop()
{
	Shop::pStaticShop = NULL;
	Director::getInstance()->getEventDispatcher()->removeEventListener(_event);
	CC_SAFE_RELEASE(_event);
	NotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

void Shop::resetYubiObg()
{
	if (otherpay)
	{
		return;
	}
	if (mIsMSMPay)
	{
		for (int i=0; i<mYubiObgs.size(); i++)
		{
			Sprite* pTmpSprite = mYubiObgs[i];
			if (i<4)
			{
				
				pTmpSprite->setVisible(true);
				
				Label* yubizi_num = (Label*)pTmpSprite->getChildByTag(1);

				char moneyTmp[30];
				sprintf(moneyTmp,"%.0f", (sale_percent[shop_sale_tag] *  yubiNumMSM[i] * 10000));
				yubizi_num->setString(moneyTmp);


				LabelTTF* pPriceLabel =  (LabelTTF*)pTmpSprite->getChildByTag(3);
				sprintf(moneyTmp,"%dthb", sPriceMSM[i]);
				pPriceLabel->setString(moneyTmp);
			}
			else
			{
				pTmpSprite->setVisible(false);
			}
		}
		 yubiLayer->setContentSize(Size((roomSize.width + 20 ) * 4,400));
	}
	else
	{
		for (int i=0; i<mYubiObgs.size(); i++)
		{
			Sprite* pTmpSprite = mYubiObgs[i];
			pTmpSprite->setVisible(true);

			Label* yubizi_num = (Label*)pTmpSprite->getChildByTag(1);

			char moneyTmp[30];
			sprintf(moneyTmp,"%.0f", (sale_percent[shop_sale_tag] *  yubi_num[i] * 10000));
			yubizi_num->setString(moneyTmp);

			LabelTTF* pPriceLabel =  (LabelTTF*)pTmpSprite->getChildByTag(3);
			sprintf(moneyTmp,"%.2fusd", sPrice[i]);
			pPriceLabel->setString(moneyTmp);
		
		}
		 yubiLayer->setContentSize(Size((roomSize.width + 20 ) * mYubiObgs.size(),400));

		
	}
}

void Shop::onPayChanged(EventCustom* event)
{
	void *pTemp = event->getUserData();
	const char * porderId = ((GoogleData *)pTemp)->orderId;

	cocos2d::log("jni-in-Shop-class=======%s", porderId);
	// char postFields[100];
	// sprintf(postFields, "userid=%s&password=%s", useridtmp.c_str(), userpwdtmp.c_str());

	CURL *curl;
	CURLcode res;
	std::string cc;
	curl = curl_easy_init();
	char postFields[600];

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.199.178/index.php");
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3000);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &GooglePay_poss);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
		}
		curl_easy_cleanup(curl);
	}
	else
	{
		return;
	}
}
size_t Shop::GooglePay_poss(uint8_t *buffer, size_t size, size_t nmemb, void *stream)
{
	cocos2d::log("补单返回数据： %s ", (const char *)buffer);
	if (Shop::pStaticShop != NULL)
	{
		auto layer = Shop::pStaticShop->getParent();
		char textTmp[100];
		sprintf(textTmp, GAME_DATA_STRING("goumai_chenggong"), 8, 8);

		auto  gongxi = Gongxi::create(4, textTmp);
		gongxi->setPosition(Point::ZERO);
		layer->addChild(gongxi, ANNIULAYER + 100);
		Shop::pStaticShop->removeFromParentAndCleanup(true);

		GameHallLayer::RefreshCoin(8);
		GameHallLayer::RefreshDiamond(8);
	}
	else
	{
		cocos2d::log("Shop::pStaticShop======NULL");
	}

	string tmpstring = (const char *)buffer;
	int temp_length = tmpstring.length();
	if (temp_length == 32)
	{
	}
	else
	{
	}
	size_t sizes = size*nmemb;
	return sizes;
}