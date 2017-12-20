#include "InitPlayer.h"
#include "GameHallLayer.h"
#include "GameBegin.h"
#include "GameData.h"
#include "Gongxi.h"

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





char InitPlayer::cCheckMaOk = 0;
Scene* InitPlayer::createScene()
{
	auto scene = Scene::create();
	auto layer = InitPlayer::create();
	scene->addChild(layer);
	return scene;
}
 
bool InitPlayer::init()
{  
	if ( !Layer::init() )	
	{
		return false;
	}
 
    cCheckMaOk = 0;
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameHall2.plist","gameHall2.png");
    
	srand(time(NULL));
	visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	cur_tx_index = UserDefault::getInstance()->getIntegerForKey("player_touxiang");

	ip_dianguo = false;
	is_moving = false;
	auto hallBackground = Sprite::create("hall_BG.png");
	hallBackground->setPosition(Point(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
	this->addChild(hallBackground);

	//øÿ÷∆√Ê∞Â
	controlBg = Scale9Sprite::createWithSpriteFrameName( "bs_kuang.png",CCRectMake(50,50,50,50));
	controlBg->setContentSize(CCSizeMake(910,562));
	controlBg->setScale(0.85);
	controlBg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	this->addChild(controlBg);

	//ÕÀ≥ˆ∞¥≈•
	auto ip_sprite_tc = Sprite::createWithSpriteFrameName("hall_menu_X.png");
	auto ip_sprite_tc_d = Sprite::createWithSpriteFrameName("hall_menu_X_d.png");
	auto ip_menu_tc = Menu::create(MenuItemSprite::create(ip_sprite_tc,ip_sprite_tc_d,CC_CALLBACK_0(InitPlayer::exit,this)),nullptr);
	ip_menu_tc->setPosition(Vec2(controlBg->getContentSize().width - 10,controlBg->getContentSize().height - 10));
	controlBg->addChild(ip_menu_tc,100);
 
    //Ã· æŒƒ◊÷
    auto ip_title = Sprite::createWithSpriteFrameName("XR_title.png");
    ip_title->setAnchorPoint(Vec2(0,0.5));
    ip_title->setPosition(Vec2(60,controlBg->getContentSize().height * 0.9));
    controlBg->addChild(ip_title,100);
    
    
    //√˚≥∆±‡º≠øÚ
    hall_name_bg = EditBox::create(Size(300,55),Scale9Sprite::createWithSpriteFrameName("kuang_3.png"),Scale9Sprite::createWithSpriteFrameName("kuang_3.png"),nullptr);
    hall_name_bg->setAnchorPoint(Vec2(0,0.5));
    hall_name_bg->setPosition(Vec2(60,controlBg->getContentSize().height * 0.79));
    hall_name_bg->setFont("minijianling.ttf", 30);
    hall_name_bg->setFontColor(Color3B::WHITE);
    hall_name_bg->setPlaceHolder(UserDefault::getInstance()->getStringForKey("player_name").c_str());
    hall_name_bg->setPlaceholderFontColor(Color3B::WHITE);
    hall_name_bg->setMaxLength(7);
    hall_name_bg->setInputMode(EditBox::InputMode::SINGLE_LINE);
    hall_name_bg->setReturnType(EditBox::KeyboardReturnType::DONE);
    hall_name_bg->setDelegate(this);
    controlBg->addChild(hall_name_bg,100);
    
    //ÀÊª˙∞¥≈•
    auto suiji_sp = Sprite::createWithSpriteFrameName("XR_suiji.png");
    auto suiji_item = MenuItemSprite::create(suiji_sp,suiji_sp,CC_CALLBACK_1(InitPlayer::suijiName,this));
    auto suiji_menu = Menu::create(suiji_item,nullptr);
    suiji_menu->setPosition(Vec2(controlBg->getContentSize().width * 0.48,controlBg->getContentSize().height * 0.79));
    //suiji_menu->setVisible(false);
    controlBg->addChild(suiji_menu,100);

	//÷–º‰±≥æ∞
	auto centerBg = Scale9Sprite::createWithSpriteFrameName("kuang_8.png",CCRectMake(30,30,40,40));
	centerBg->setContentSize(CCSizeMake(859,306));
	centerBg->setPosition(Vec2(controlBg->getContentSize().width/2,controlBg->getContentSize().height * 0.4448));
	controlBg->addChild(centerBg,100);
 
	//¥ÛÕ∑œÒ
	auto ip_dtx_bg = Sprite::createWithSpriteFrameName("XR_heidi.png");
	ip_dtx_bg->setScale(0.9);
	ip_dtx_bg->setPosition(Vec2(150,centerBg->getContentSize().height/2));
	centerBg->addChild(ip_dtx_bg,98);

	auto ip_dtx_k = Sprite::createWithSpriteFrameName("XR_txk.png");
	ip_dtx_k->setPosition(Vec2(ip_dtx_bg->getContentSize().width/2,ip_dtx_bg->getContentSize().height/2));
	ip_dtx_bg->addChild(ip_dtx_k,100);
 
	auto ip_dtx_stencil = Sprite::createWithSpriteFrameName("XR_heidi.png");
	auto ip_dtx_clipper = ClippingNode::create();
	ip_dtx_clipper->setStencil(ip_dtx_stencil);//…Ë÷√≤√ºÙƒ£∞Â //3
	ip_dtx_clipper->setInverted(false);//…Ë÷√µ◊∞Â≤ªø…º˚
	ip_dtx_clipper->setPosition(Vec2(ip_dtx_stencil->getContentSize()/2));
	ip_dtx_clipper->setAlphaThreshold(0);//…Ë÷√ªÊ÷∆µ◊∞ÂµƒAlpha÷µŒ™0
	ip_dtx_bg->addChild(ip_dtx_clipper);//4

	sprintf(IP_tmpchar,"tou%d.png",cur_tx_index);
	ip_datouxiang = Sprite::createWithSpriteFrameName(IP_tmpchar);
	ip_datouxiang->setPosition(Vec2(-10,ip_dtx_clipper->getContentSize().height/2));
	ip_dtx_clipper->addChild(ip_datouxiang);

	sprintf(IP_tmpchar,"tou%d.png",cur_tx_index);
	ip_datouxiang2 = Sprite::createWithSpriteFrameName(IP_tmpchar);
	ip_datouxiang2->setPosition(Vec2(390,ip_dtx_clipper->getContentSize().height/2));
	ip_dtx_clipper->addChild(ip_datouxiang2);

	//ip_datouxiang->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.0f,Vec2(150,0)),MoveBy::create(1.0f,Vec2(-300,0)),MoveBy::create(1.0f,Vec2(150,0)),nullptr)));
	//ip_datouxiang2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.0f,Vec2(150,0)),MoveBy::create(1.0f,Vec2(-300,0)),MoveBy::create(1.0f,Vec2(150,0)),nullptr)));


	//8∏ˆ–°Õ∑œÒ
	for(int i = 0; i < 8 ; i++)
	{
		//“ı”∞±≥æ∞
		auto ip_xtx_yy_bg = Sprite::createWithSpriteFrameName("XR_yy.png");
		ip_xtx_yy_bg->setAnchorPoint(Vec2(0,1));
		ip_xtx_yy_bg->setPosition(Vec2(285 + i % 4 * 145,285 - i/4 * 137));
		centerBg->addChild(ip_xtx_yy_bg,97);

		auto ip_xtx_bg = Sprite::createWithSpriteFrameName("XR_heidi.png");
		ip_xtx_bg->setScale(0.45 * 0.9);
		ip_xtx_bg->setPosition(Vec2(350 + i % 4 * 145,220 - i/4 * 137));
		centerBg->addChild(ip_xtx_bg,98);

		auto ip_xtx_k = Sprite::createWithSpriteFrameName("XR_txk.png");
		auto xtx_item = MenuItemSprite::create(ip_xtx_k,ip_xtx_k,CC_CALLBACK_1(InitPlayer::xz_touxiang,this));
		xtx_item->setTag(i+1);
		auto xtx_menu = Menu::create(xtx_item,nullptr);
		xtx_menu->setPosition(Vec2(ip_xtx_bg->getContentSize().width/2,ip_xtx_bg->getContentSize().height/2));
		ip_xtx_bg->addChild(xtx_menu,100);

		auto ip_xtx_stencil = Sprite::createWithSpriteFrameName("XR_heidi.png");
		auto ip_xtx_clipper = ClippingNode::create();
		ip_xtx_clipper->setStencil(ip_xtx_stencil);//…Ë÷√≤√ºÙƒ£∞Â //3
		ip_xtx_clipper->setInverted(false);//…Ë÷√µ◊∞Â≤ªø…º˚
		ip_xtx_clipper->setPosition(Vec2(ip_dtx_stencil->getContentSize()/2));
		ip_xtx_clipper->setAlphaThreshold(0);//…Ë÷√ªÊ÷∆µ◊∞ÂµƒAlpha÷µŒ™0
		ip_xtx_bg->addChild(ip_xtx_clipper);//4

		sprintf(IP_tmpchar,"tou%d.png",i+1);
		auto ip_xxiang = Sprite::createWithSpriteFrameName(IP_tmpchar);
		ip_xxiang->setPosition(Vec2(-10,ip_xtx_clipper->getContentSize().height/2));
		ip_xtx_clipper->addChild(ip_xxiang);
        
		touxiang_sp.pushBack(ip_xxiang);

		//touxiang_sp.at(i)->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.0f,Vec2(150,0)),MoveBy::create(1.0f,Vec2(-300,0)),MoveBy::create(1.0f,Vec2(150,0)),nullptr)));

	}

	//∫⁄∏«
	ip_heigai = Sprite::createWithSpriteFrameName("XR_huidi.png");
	ip_heigai->setAnchorPoint(Vec2(0,0.5));
	ip_heigai->setPosition(Vec2(289 + (cur_tx_index - 1) % 4 * 145,220 - (cur_tx_index - 1)/4 * 137));
	centerBg->addChild(ip_heigai,100);

	//–«–«
	ip_xingxing = Sprite::createWithSpriteFrameName("hall_ssxx_1.png");
	ip_xingxing->setAnchorPoint(Vec2(0,0.5));
	ip_xingxing->setPosition(Vec2(350 + (cur_tx_index - 1) % 4 * 145,275 - (cur_tx_index - 1)/4 * 137));
	centerBg->addChild(ip_xingxing,101);
 
	//»∑∂®
	auto ip_sprite_qd = Sprite::createWithSpriteFrameName("XR_qd.png");
	auto ip_menu_qd = Menu::create(MenuItemSprite::create(ip_sprite_qd,ip_sprite_qd,CC_CALLBACK_0(InitPlayer::exit,this)),nullptr);
	ip_menu_qd->setPosition(Vec2(controlBg->getContentSize().width/2,controlBg->getContentSize().height*0.1));
	controlBg->addChild(ip_menu_qd,100);
 
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(InitPlayer::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(InitPlayer::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(InitPlayer::onTouchEnded,this);
	listener->setSwallowTouches(true);//≤ªœÚœ¬¥´µ›¥•√˛
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
 
    //∞Û∂®’ ∫≈
   /* if(UserDefault::getInstance()->getStringForKey("login_phone_num") == "")
    {
        if(UserDefault::getInstance()->getIntegerForKey("ios_dengluFlag") != 1)
        {
            iden_time = 60;
            auto bing_sp = Sprite::createWithSpriteFrameName("zh_bangding.png");
            bing_item = Menu::create(MenuItemSprite::create(bing_sp,bing_sp,CC_CALLBACK_0(InitPlayer::bind_acount,this)),nullptr);
            bing_item->setPosition(Vec2(controlBg->getContentSize().width * 0.78,controlBg->getContentSize().height*0.85));
            controlBg->addChild(bing_item,100,101);
            
            auto acount_sp = LabelTTF::create(GAME_DATA_STRING("bindwf"),GameHallLayer::wordKind,33);
            acount_sp->setPosition(Vec2(controlBg->getContentSize().width * 0.78,controlBg->getContentSize().height*0.75));
            controlBg->addChild(acount_sp,100);
            
        }
       
    }else
    {
        auto bing_sp = Sprite::createWithSpriteFrameName("zh_myacount.png");
        bing_sp->setPosition(Vec2(controlBg->getContentSize().width * 0.78,controlBg->getContentSize().height*0.9));
        controlBg->addChild(bing_sp,100);
        
        auto acount_sp = LabelTTF::create(UserDefault::getInstance()->getStringForKey("login_phone_num"),GameHallLayer::wordKind,33);
        acount_sp->setPosition(Vec2(controlBg->getContentSize().width * 0.78,controlBg->getContentSize().height*0.78));
        controlBg->addChild(acount_sp,100);
    }*/
    
    
    //ÃÌº”◊‘∂®“Â ¬º˛
    auto listen1 = EventListenerCustom::create("bind_succ",CC_CALLBACK_0(InitPlayer::bind_success,this));
    _eventDispatcher->addEventListenerWithFixedPriority(listen1,1);
    
    auto listen2 = EventListenerCustom::create("bind_fail",CC_CALLBACK_0(InitPlayer::bind_fail,this));
    _eventDispatcher->addEventListenerWithFixedPriority(listen2,1);
    

    
    return true;
}


//∞Û∂®’ ∫≈******************
void InitPlayer::bind_success()
{
    log("bind_suc");
    
 
    
    
    this->removeChildByTag(124);
    
    hall_name_bg->setText(UserDefault::getInstance()->getStringForKey("player_name").c_str());

    
    auto phone_edit = (EditBox *)(this->getChildByTag(123)->getChildByTag(1));
    string phone_s = phone_edit->getText();
    UserDefault::getInstance()->setStringForKey("login_phone_num" , phone_s);
    //ø™ ºdown ˝æ› downÕÍ÷Æ∫Û Ω¯»Î≥°æ∞
    //TO DO
    controlBg->getChildByTag(101)->setVisible(false);
    
    auto bing_sp = Sprite::createWithSpriteFrameName("zh_myacount.png");
    bing_sp->setPosition(Vec2(controlBg->getContentSize().width * 0.78,controlBg->getContentSize().height*0.9));
    controlBg->addChild(bing_sp,100);
    
    auto acount_sp = LabelTTF::create(UserDefault::getInstance()->getStringForKey("login_phone_num"),GameHallLayer::wordKind,33);
    acount_sp->setPosition(Vec2(controlBg->getContentSize().width * 0.78,controlBg->getContentSize().height*0.78));
    controlBg->addChild(acount_sp,100);
    
    int tmpMonty = GameBegin::getFileData("jywer.txt") + 10000;
    GameBegin::setFileData("jywer.txt",tmpMonty);
    
    auto  gongxi = Gongxi::create(4,GAME_DATA_STRING("bind_success"));
    gongxi->setPosition(Point::ZERO);
    addChild(gongxi,1000);
    
    this->removeChildByTag(121);
    
    this->unscheduleAllSelectors();
    ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);
    ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);
    
    this->getChildByTag(123)->runAction(Sequence::create(ac7,ac8,RemoveSelf::create(),nullptr));
}

void InitPlayer::bind_fail()
{
    log("bind_fail");
    bing_item->setEnabled(true);
    
    auto phone_edit = (Menu *)(this->getChildByTag(123)->getChildByTag(5));
    phone_edit->setEnabled(true);
    auto iden_item = (MenuItemSprite *)(phone_edit->getChildByTag(1));
    iden_item->setEnabled(true) ;
    
    auto times_edit = (LabelTTF *)(this->getChildByTag(123)->getChildByTag(6));
    times_edit->setVisible(false);
 
    
    this->unschedule(schedule_selector(InitPlayer::bind_update_iden));
    this->removeChildByTag(124);
    
    //Ã· æ≥ˆ¥Ì–≈œ¢
    char  tmpfail[50];
    sprintf(tmpfail,"login_wrong%d",GameBegin::login_fail_flag);
    auto gongxi = Gongxi::create(2,GAME_DATA_STRING(tmpfail));
    this->addChild(gongxi,1000);
    
    this->removeChildByTag(121);
    
    this->unscheduleAllSelectors();
    ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);
    ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);
    
    this->getChildByTag(123)->runAction(Sequence::create(ac7,ac8,RemoveSelf::create(),nullptr));
    
}

void InitPlayer::bind_acount()
{
    bing_item->setEnabled(false);
    
    this->scheduleUpdate();
    auto zheZhao = LayerColor::create(ccc4(0,0,0,150),1024,768);
    zheZhao->setPosition(Point::ZERO);
    zheZhao->setScale(2.0f);
    this->addChild(zheZhao,1000,121);
    
    //±≥æ∞
    auto login_bg = Scale9Sprite::createWithSpriteFrameName( "bs_kuang.png",CCRectMake(99,99,20,20));
    login_bg->setContentSize(CCSizeMake(700,400));
    login_bg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    this->addChild(login_bg,1000,123);
    
    login_bg->setScale(0.1f);
    ScaleTo *ac7=ScaleTo::create(0.2f, 1.35f);
    ScaleTo *ac8=ScaleTo::create(0.1f, 1.3);
    login_bg->runAction(Sequence::create(ac7,ac8,nullptr));
    
    //∂•≤ø
    auto bind_top_label = Sprite::createWithSpriteFrameName("bind_top.png");
    bind_top_label->setAnchorPoint(Vec2(0.5,1));
    bind_top_label->setPosition(Vec2(login_bg->getContentSize().width * 0.5,login_bg->getContentSize().height*0.96));
    login_bg->addChild(bind_top_label,100);
    
    // ÷ª˙∫≈£∫
    auto bind_phone_label = LabelTTF::create(GAME_DATA_STRING("bind_acount"),GameHallLayer::wordKind,20);
    bind_phone_label->setAnchorPoint(Vec2(1,0.5));
    bind_phone_label->setPosition(Vec2(220,300));
    login_bg->addChild(bind_phone_label,100);
    
    // ÷ª˙∫≈±‡º≠øÚ
    auto login_phone_edit = EditBox::create(Size(240,35),Scale9Sprite::createWithSpriteFrameName("kuang_3.png"),Scale9Sprite::createWithSpriteFrameName("kuang_3.png"),nullptr);
    login_phone_edit->setAnchorPoint(Vec2(0.5,0.5));
    login_phone_edit->setPosition(Vec2(350,300));
    login_phone_edit->setFont("minijianling.ttf", 24);
    login_phone_edit->setFontColor(Color3B::WHITE);
    login_phone_edit->setPlaceHolder("");
    login_phone_edit->setPlaceholderFontColor(Color3B::WHITE);
    login_phone_edit->setInputMode(EditBox::InputMode::SINGLE_LINE);
    login_phone_edit->setReturnType(EditBox::KeyboardReturnType::DONE);
    login_phone_edit->setDelegate(this);
    login_bg->addChild(login_phone_edit,100,1);
    
    // ‰»Î√‹¬Î£∫
    auto bind_pwd_label = LabelTTF::create(GAME_DATA_STRING("bind_password"),GameHallLayer::wordKind,20);
    bind_pwd_label->setAnchorPoint(Vec2(1,0.5));
    bind_pwd_label->setPosition(Vec2(220,260));
    login_bg->addChild(bind_pwd_label,100);
    
    // ‰»Î√‹¬ÎÀµ√˜£∫
    auto bind_pwd_label1 = LabelTTF::create(GAME_DATA_STRING("bind_password_shuo"),GameHallLayer::wordKind,18);
    bind_pwd_label1->setAnchorPoint(Vec2(0,0.5));
    bind_pwd_label1->setPosition(Vec2(480,260));
    login_bg->addChild(bind_pwd_label1,100);
    
    // ‰»Î√‹¬Î±‡º≠øÚ
    auto login_pwd_edit = EditBox::create(Size(240,35),Scale9Sprite::createWithSpriteFrameName("kuang_3.png"),Scale9Sprite::createWithSpriteFrameName("kuang_3.png"),nullptr);
    login_pwd_edit->setAnchorPoint(Vec2(0.5,0.5));
    login_pwd_edit->setPosition(Vec2(350,260));
    login_pwd_edit->setFont("minijianling.ttf", 24);
    login_pwd_edit->setFontColor(Color3B::WHITE);
    login_pwd_edit->setPlaceHolder("");
    login_pwd_edit->setPlaceholderFontColor(Color3B::WHITE);
    login_pwd_edit->setInputMode(EditBox::InputMode::SINGLE_LINE);
    login_pwd_edit->setReturnType(EditBox::KeyboardReturnType::DONE);
    login_pwd_edit->setDelegate(this);
    login_bg->addChild(login_pwd_edit,100,2);
    
    //»∑»œ√‹¬Î£∫
    auto bind_pwd_conf_label = LabelTTF::create(GAME_DATA_STRING("bind_pwd_confirm"),GameHallLayer::wordKind,20);
    bind_pwd_conf_label->setAnchorPoint(Vec2(1,0.5));
    bind_pwd_conf_label->setPosition(Vec2(220,220));
    login_bg->addChild(bind_pwd_conf_label,100);
    
    //»∑»œ√‹¬Î±‡º≠øÚ
    auto login_pwd_conf_edit = EditBox::create(Size(240,35),Scale9Sprite::createWithSpriteFrameName("kuang_3.png"),Scale9Sprite::createWithSpriteFrameName("kuang_3.png"),nullptr);
    login_pwd_conf_edit->setAnchorPoint(Vec2(0.5,0.5));
    login_pwd_conf_edit->setPosition(Vec2(350,220));
    login_pwd_conf_edit->setFont("minijianling.ttf", 24);
    login_pwd_conf_edit->setFontColor(Color3B::WHITE);
    login_pwd_conf_edit->setPlaceHolder("");
    login_pwd_conf_edit->setPlaceholderFontColor(Color3B::WHITE);
    login_pwd_conf_edit->setInputMode(EditBox::InputMode::SINGLE_LINE);
    login_pwd_conf_edit->setReturnType(EditBox::KeyboardReturnType::DONE);
    login_pwd_conf_edit->setDelegate(this);
    login_bg->addChild(login_pwd_conf_edit,100,3);
    
    //—È÷§¬Î£∫
    auto bind_identify_label = LabelTTF::create(GAME_DATA_STRING("bind_identify_code"),GameHallLayer::wordKind,20);
    bind_identify_label->setAnchorPoint(Vec2(1,0.5));
    bind_identify_label->setPosition(Vec2(220,180));
    login_bg->addChild(bind_identify_label,100);
    
    //—È÷§¬Î±‡º≠øÚ
    auto login_identify_edit = EditBox::create(Size(240,35),Scale9Sprite::createWithSpriteFrameName("kuang_3.png"),Scale9Sprite::createWithSpriteFrameName("kuang_3.png"),nullptr);
    login_identify_edit->setAnchorPoint(Vec2(0.5,0.5));
    login_identify_edit->setPosition(Vec2(350,180));
    login_identify_edit->setFont("minijianling.ttf", 24);
    login_identify_edit->setFontColor(Color3B::WHITE);
    login_identify_edit->setPlaceHolder("");
    login_identify_edit->setPlaceholderFontColor(Color3B::WHITE);
    login_identify_edit->setInputMode(EditBox::InputMode::SINGLE_LINE);
    login_identify_edit->setReturnType(EditBox::KeyboardReturnType::DONE);
    login_identify_edit->setDelegate(this);
    login_bg->addChild(login_identify_edit,100,4);
    
    //—È÷§¬Î∞¥≈•
    /*auto bind_identify_sp = Sprite::createWithSpriteFrameName("bind_identi.png");
    auto bind_identify_sp_n = Sprite::createWithSpriteFrameName("bind_identi_d.png");
    auto bind_identify_item = MenuItemSprite::create(bind_identify_sp,bind_identify_sp,bind_identify_sp_n,CC_CALLBACK_1(InitPlayer::bind_identyfy,this));
    bind_identify_item->setTag(1);
    auto bind_identify_menu = Menu::create(bind_identify_item,nullptr);
    bind_identify_menu->setPosition(Vec2(570,180));
    login_bg->addChild(bind_identify_menu,100,5);
    */
    //—È÷§¬Îµπº∆ ±
    auto bind_iden_time_label = LabelTTF::create("60",GameHallLayer::wordKind,40);
    bind_iden_time_label->setColor(Color3B::BLACK);
    bind_iden_time_label->setVisible(false);
    bind_iden_time_label->setPosition(Vec2(570,180));
    login_bg->addChild(bind_iden_time_label,100,6);
    
    //∞Û∂®∞¥≈•
    auto login_login_sp = Sprite::createWithSpriteFrameName("bind_queding.png");
    auto login_cancel_sp = Sprite::createWithSpriteFrameName("zh_quxiao.png");
    auto login_login_item = MenuItemSprite::create(login_login_sp,login_login_sp,CC_CALLBACK_0(InitPlayer::bind_queding,this));
    auto login_cancel_item = MenuItemSprite::create(login_cancel_sp,login_cancel_sp,CC_CALLBACK_0(InitPlayer::bind_cancel,this));
    auto login_menu = Menu::create(login_login_item,login_cancel_item,nullptr);
    login_menu->alignItemsHorizontallyWithPadding(130);
    login_menu->setPosition(Vec2(350,115));
    login_bg->addChild(login_menu,100);
    
    //¡Ω‘ÚÀµ√˜
    auto bind_caption_label_1 = LabelTTF::create(GAME_DATA_STRING("bind_caption_1"),GameHallLayer::wordKind,20);
    bind_caption_label_1->setAnchorPoint(Vec2(0,0.5));
    bind_caption_label_1->setPosition(Vec2(50,70));
    login_bg->addChild(bind_caption_label_1,100);
    
    auto bind_caption_label_2 = LabelTTF::create(GAME_DATA_STRING("bind_caption_2"),GameHallLayer::wordKind,20);
    bind_caption_label_2->setAnchorPoint(Vec2(0,0.5));
    bind_caption_label_2->setPosition(Vec2(50,40));
    login_bg->addChild(bind_caption_label_2,100);
}

void InitPlayer::bind_identyfy(Ref* pSender)
{
    log("identify");
    
 
    auto phone_edit = (EditBox *)(this->getChildByTag(123)->getChildByTag(1));
    string phone_s = phone_edit->getText();
    if(!GameBegin::isPhoneNum(phone_s))
    {
        auto gongxi = Gongxi::create(2,GAME_DATA_STRING("login_phone"));
        this->addChild(gongxi,1000);
        return;
    }
    //Fuck::GetMa(phone_s);
    
    auto iden_item = (MenuItemSprite *)pSender;
    auto iden_edit = (Menu *)(this->getChildByTag(123)->getChildByTag(5));
    iden_edit->setEnabled(false);
    iden_item->setEnabled(false);
    iden_time = 60;
    
    auto times_edit = (LabelTTF *)(this->getChildByTag(123)->getChildByTag(6));
    times_edit->setVisible(true);
    this->schedule(schedule_selector(InitPlayer::bind_update_iden),1.0f);
}

void InitPlayer::bind_update_iden(float dt)
{
    iden_time--;
    if(iden_time <= 0)
    {
        auto phone_edit = (Menu *)(this->getChildByTag(123)->getChildByTag(5));
        phone_edit->setEnabled(true);
        auto iden_item = (MenuItemSprite *)(phone_edit->getChildByTag(1));
        iden_item->setEnabled(true) ;
        
        auto times_edit = (LabelTTF *)(this->getChildByTag(123)->getChildByTag(6));
        times_edit->setVisible(false);
        this->unschedule(schedule_selector(InitPlayer::bind_update_iden));
    }else
    {
        sprintf(IP_tmpchar,"%d",iden_time);
        auto times_edit = (LabelTTF *)(this->getChildByTag(123)->getChildByTag(6));
        times_edit->setString(IP_tmpchar);
    }
}

void InitPlayer::bind_queding()
{
    log("bind_queding");
    
    GameBegin::buttonSound();
    
    auto phone_edit = (EditBox *)(this->getChildByTag(123)->getChildByTag(1));
    auto pwd_edit = (EditBox *)(this->getChildByTag(123)->getChildByTag(2));
    auto pwd_conf_edit = (EditBox *)(this->getChildByTag(123)->getChildByTag(3));
    auto identi_edit = (EditBox *)(this->getChildByTag(123)->getChildByTag(4));
    
    string phone_s		= phone_edit->getText();
    string pwd_s		= pwd_edit->getText();
    string pwd_conf_s	= pwd_conf_edit->getText();
    string identy_s		= identi_edit->getText();
    string deviceId		= UserDefault::getInstance()->getStringForKey("DeviceNo");
    
    if(!GameBegin::isPhoneNum(phone_s))
    {
        auto gongxi = Gongxi::create(2,GAME_DATA_STRING("login_phone"));
        this->addChild(gongxi,1000);
        return;
    }
    
    if(pwd_s.length() < 6 || pwd_s.length() > 12 )
    {
        auto tishi = Gongxi::create(2, GAME_DATA_STRING("login_pwd"));
        this->addChild(tishi,1000);
        return;
    }
    
    if(pwd_s != pwd_conf_s )
    {
        auto tishi = Gongxi::create(2, GAME_DATA_STRING("login_conf"));
        this->addChild(tishi,1000);
        return;
    }
    
    if(identy_s == "")
    {
        auto tishi = Gongxi::create(2, GAME_DATA_STRING("bind_ident_wrong"));
        this->addChild(tishi,1000);
        return;
    }
   // Fuck::CheckMa(identy_s, phone_s);
    
    auto waiting = Waiting::create();
    this->addChild(waiting,1000,124);

    
    
}


void InitPlayer::update(float dt)
{
    if(cCheckMaOk == 3)
    {
        cCheckMaOk = 0;
        QueDingOver();
        return;
    }
    else  if(cCheckMaOk == 4)
    {
        cCheckMaOk = 0;
        auto tishi = Gongxi::create(2, GAME_DATA_STRING("bind_ident_wrong"));
        this->addChild(tishi,1000);
        this->removeChildByTag(124);
        
        return;
    }
    else  if(cCheckMaOk == 1)
    {
        cCheckMaOk = 0;
        auto tishi = Gongxi::create(2, GAME_DATA_STRING("getidentok"));
        this->addChild(tishi,1000);
       
        return;
    }
    else  if(cCheckMaOk == 2)
    {
        cCheckMaOk = 0;
        auto tishi = Gongxi::create(2, GAME_DATA_STRING("getidentnook"));
        this->addChild(tishi,1000);
        this->unscheduleUpdate();
        return;
    }

}
void InitPlayer::QueDingOver()
{
    
    auto phone_edit = (EditBox *)(this->getChildByTag(123)->getChildByTag(1));
    auto pwd_edit = (EditBox *)(this->getChildByTag(123)->getChildByTag(2));
    auto pwd_conf_edit = (EditBox *)(this->getChildByTag(123)->getChildByTag(3));
    auto identi_edit = (EditBox *)(this->getChildByTag(123)->getChildByTag(4));
    
    string phone_s		= phone_edit->getText();
    string pwd_s		= pwd_edit->getText();
    string pwd_conf_s	= pwd_conf_edit->getText();
    string identy_s		= identi_edit->getText();
    string deviceId		= UserDefault::getInstance()->getStringForKey("DeviceNo");
    
    //Ω¯––µ«¬º
    CURL *curl;
    CURLcode res;
    std::string cc;
    curl=curl_easy_init();
    
    char postFields[200];
    
    sprintf(postFields,"phone_s=%s&pwd_s=%s&pwd_conf_s=%s&identy_s=%s&deviceId=%s",
            phone_s.c_str(),pwd_s.c_str(),pwd_conf_s.c_str(),identy_s.c_str(),deviceId.c_str());
    
    cocos2d::log("login:: postFields %s",postFields);
    
    if(curl)
    {
        curl_easy_setopt( curl, CURLOPT_URL, "http://buyu2.iyueyo.com/qpby2/ios/login/bind.php");
        curl_easy_setopt(curl, CURLOPT_POST, true);           //∆Ù”√POSTÃ·Ωª
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields); //∑¢ÀÕµƒ ˝æ›
        curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&bind_poss); //¥¶¿Ìµƒ∫Ø ˝
        curl_easy_setopt(curl, CURLOPT_TIMEOUT,2000);
        
        res=curl_easy_perform(curl);
        if(res!=CURLE_OK)
        {
            auto gongxi = Gongxi::create(2,GAME_DATA_STRING("netwrong"));
            this->addChild(gongxi,1000);
            this->removeChildByTag(124);
            
        }
        curl_easy_cleanup(curl);
    }
    else
    {
        auto gongxi = Gongxi::create(2,GAME_DATA_STRING("netwrong"));
        this->addChild(gongxi,1000);
        this->removeChildByTag(124);
        return ;
    }
}

size_t InitPlayer::bind_poss(uint8_t *buffer,size_t size,size_t nmemb,void *stream)
{
    cocos2d::log("≤πµ•∑µªÿ ˝æ›£∫ %s ", (const char *)buffer);
    
    string tmpstring = (const char *)buffer;
    if(tmpstring == "success")
    {		 
        //∑¢ÀÕ≥…π¶ ¬º˛
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("bind_succ");
    }else
    {
        //∑¢ÀÕ ß∞‹ ¬º˛
         if(tmpstring == "haveuser")
            GameBegin::login_fail_flag = 4;
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("bind_fail");
    }
    
    size_t sizes = size*nmemb;
    return sizes;
}

void InitPlayer::bind_cancel()
{
    log("bind_cancel");
    
    bing_item->setEnabled(true);
   this->unscheduleAllSelectors();
    
    GameBegin::buttonSound();
    this->removeChildByTag(121);
    
    ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
    ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
    
    this->getChildByTag(123)->runAction(Sequence::create(ac7,ac8,RemoveSelf::create(),nullptr)); 
    
}

//**********************************



void InitPlayer::exit()
{
	GameBegin::buttonSound();

	this->stopAllActions();
	this->removeAllChildrenWithCleanup(true);
	this->unscheduleAllSelectors();

	auto scene = GameHallLayer::createScene();
	Director::getInstance()->replaceScene(scene);
}

void InitPlayer::xz_touxiang(Ref * pSender)
{
	if(cur_tx_index != ((MenuItemSprite *)pSender)->getTag() && !is_moving)
	{
		GameBegin::buttonSound();
		is_moving = true;
		cur_tx_index = ((MenuItemSprite *)pSender)->getTag();

		ip_xingxing->runAction(MoveTo::create(0.3f,Vec2(350 + (cur_tx_index - 1) % 4 * 145,275 - (cur_tx_index - 1)/4 * 137)));
		ip_heigai->runAction(Place::create(Vec2(289 + (cur_tx_index - 1) % 4 * 145,220 - (cur_tx_index - 1)/4 * 137)));

		if(!ip_dianguo)
		{
			ip_dianguo = true;
			sprintf(IP_tmpchar,"tou%d.png",cur_tx_index);
			auto sp_frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(IP_tmpchar);
			ip_datouxiang2->setDisplayFrame(sp_frame);
			ip_datouxiang2->runAction(MoveTo::create(0.3f,Vec2(-10,0)));
			ip_datouxiang->runAction(Sequence::create(MoveBy::create(0.3f,Vec2(-400,0)),Place::create(Vec2(390,0)),nullptr));
		}else
		{
			ip_dianguo = false;
			sprintf(IP_tmpchar,"tou%d.png",cur_tx_index);
			auto sp_frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(IP_tmpchar);
			ip_datouxiang->setDisplayFrame(sp_frame);
			ip_datouxiang->runAction(MoveTo::create(0.3f,Vec2(-10,0)));
			ip_datouxiang2->runAction(Sequence::create(MoveBy::create(0.3f,Vec2(-400,0)),Place::create(Vec2(390,0)),nullptr));
		}
		

		UserDefault::getInstance()->setIntegerForKey("player_touxiang",cur_tx_index);
		UserDefault::getInstance()->flush();
		this->scheduleOnce(schedule_selector(InitPlayer::jinzhi),0.5f);
	}
	
}

void InitPlayer::jinzhi(float dt)
{
	is_moving = false;
}

void InitPlayer::suijiName(Ref * pSender)
{
	GameBegin::buttonSound();
	int name_index = CCRANDOM_0_1() * 499 + 1;
	sprintf(IP_tmpchar,"robotNName%d",name_index);
	//hall_name_bg->setPlaceHolder(GAME_DATA_STRING(IP_tmpchar));
	hall_name_bg->setText(GAME_DATA_STRING(IP_tmpchar));
	cocos2d::log("IP_tmpchar = %s",GAME_DATA_STRING(IP_tmpchar));

	UserDefault::getInstance()->setStringForKey("player_name",GAME_DATA_STRING(IP_tmpchar));
	UserDefault::getInstance()->flush();
	log("suiji name = %s",GAME_DATA_STRING(IP_tmpchar));
}

void InitPlayer::editBoxReturn(EditBox *editBox)
{	
	string tmpString  = editBox->getText();
	char tmpMin[50];
	for(int i = 1 ; i < 313 ; i++)  //minganku1
	{
		sprintf(tmpMin,"minganku%d",i);
        string tmpMingankuStr =((string)GAME_DATA_STRING(tmpMin));
		if(((string)GAME_DATA_STRING(tmpMin)) != "" && strstr(tmpString.c_str() ,((string)GAME_DATA_STRING(tmpMin)).c_str()))
		{
			sprintf(IP_tmpchar,GAME_DATA_STRING("init_feifa"),GAME_DATA_STRING(tmpMin));//init_feifa
			auto tishi = Gongxi::create(2,IP_tmpchar);
			this->addChild(tishi,100);
			editBox->setText(UserDefault::getInstance()->getStringForKey("player_name").c_str());
			return;
		}
	}
	UserDefault::getInstance()->setStringForKey("player_name",editBox->getText());
	UserDefault::getInstance()->flush();
	log("editBox name = %s",editBox->getText());
}
  
bool InitPlayer::onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	log("touchedBegan");
	return true;
}

void InitPlayer::onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	log("touchesMoved");
}

void InitPlayer::onTouchEnded(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	log("touchesEnded");
}
