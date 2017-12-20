#include "VIPgongxi.h" 
#include "GameScene.h"
#include "GameData.h"
#include "GameBegin.h"
#include "GameHallLayer.h"

USING_NS_CC; 
bool VIPgongxi::gamehall_re = false;
VIPgongxi * VIPgongxi::create(int btnKind )
{
	VIPgongxi * gongxi = new VIPgongxi();
	gongxi->init(btnKind );
	gongxi->autorelease();
	return gongxi;
}

void VIPgongxi::init_1()
{
	char tmp_char[50];
	//背景
	r_bg =  Sprite:: createWithSpriteFrameName("vip_js_bg.png");
	r_bg->setPosition(Vec2(visibleSize.width/2 , visibleSize.height * 0.5));
	r_bg->setScale(0.45);
	this->addChild(r_bg,MENULAYER);

	//圆盘
	sprintf(tmp_char,"RankYuan%d.png",1);
	auto r_bg_yp =  Sprite:: createWithSpriteFrameName(tmp_char);
	r_bg_yp->setPosition(Vec2(r_bg->getContentSize().width/2 ,r_bg->getContentSize().height * 0.79));
	r_bg->addChild(r_bg_yp,10);

	//圆盘后面的光
	/*sprintf(tmp_char,"Ranklight%d.png",1);
	auto r_bg_yp_g =  Sprite:: createWithSpriteFrameName(tmp_char);
	r_bg_yp_g->setScale(0.5);
	r_bg_yp_g->setVisible(false);
	r_bg_yp_g->setPosition(Vec2(r_bg_yp->getContentSize().width/2 ,r_bg_yp->getContentSize().height * 0.5));
	r_bg_yp->addChild(r_bg_yp_g,-2);
 
	//背景光执行动画
	r_bg_yp_g->runAction(Sequence::create(DelayTime::create(0.1f),ToggleVisibility::create(),ScaleTo::create(0.1f,1),nullptr));
	r_bg_yp_g->runAction(RepeatForever::create(RotateBy::create(1.0f,5)));
*/
	//光上散的字
	auto r_bg_yp_gzi =  Sprite:: createWithSpriteFrameName("vip_js_saikai.png");
	r_bg_yp_gzi->setScale(0.2);
	r_bg_yp_gzi->setVisible(false);
	r_bg_yp_gzi->setPosition(Vec2(r_bg_yp->getContentSize().width/2 ,r_bg_yp->getContentSize().height));
	r_bg_yp->addChild(r_bg_yp_gzi,-1);

	r_bg_yp_gzi->runAction(Sequence::create(DelayTime::create(0.1f),ToggleVisibility::create(),ScaleTo::create(0.1f,1),nullptr));

	r_bg->runAction(ScaleTo::create(0.2f,1));

	float tx_time = 0.15f;
	//翅膀1
	sprintf(tmp_char,"Rankchibang%d.png",1);
	auto chibang1 =  Sprite:: createWithSpriteFrameName(tmp_char);
	chibang1->setScale(0.2);
	chibang1->setVisible(false);
	chibang1->setRotation(-30);
	chibang1->setPosition(Vec2(r_bg_yp->getContentSize().width/2 ,r_bg_yp->getContentSize().height * 0.3));
	r_bg_yp->addChild(chibang1,-1);

	chibang1->runAction(Sequence::create(DelayTime::create(0.5f),ToggleVisibility::create(),Spawn::create(ScaleTo::create(tx_time,0.8),RotateBy::create(tx_time,30),MoveBy::create(tx_time,Vec2(70,20)),nullptr),nullptr));

	//翅膀2
	sprintf(tmp_char,"Rankchibang%d.png",1);
	auto chibang2 =  Sprite:: createWithSpriteFrameName(tmp_char);
	chibang2->setFlippedX(true);
	chibang2->setScale(0.2);
	chibang2->setRotation(30);
	chibang2->setVisible(false);
	chibang2->setPosition(Vec2(r_bg_yp->getContentSize().width/2 ,r_bg_yp->getContentSize().height * 0.3));
	r_bg_yp->addChild(chibang2,-1);

	chibang2->runAction(Sequence::create(DelayTime::create(0.5f),ToggleVisibility::create(),Spawn::create(ScaleTo::create(tx_time,0.8),RotateBy::create(tx_time,-30),MoveBy::create(tx_time,Vec2(-70,20)),nullptr),nullptr));

	//恭喜条幅
	auto hudiejie =  Sprite:: createWithSpriteFrameName("vip_gongxi.png");
	hudiejie->setScale(0.0001);
	hudiejie->setVisible(false);
	hudiejie->setPosition(Vec2(r_bg_yp->getContentSize().width/2 ,r_bg_yp->getContentSize().height * 0.1));
	r_bg_yp->addChild(hudiejie,5);

	hudiejie->runAction(Sequence::create(DelayTime::create(0.5f),ToggleVisibility::create(),ScaleTo::create(tx_time,1),nullptr));
	
	 //vip字
	auto dijiming =  Sprite:: createWithSpriteFrameName("vip_js_vip.png");
	dijiming->setScale(3);
	dijiming->setOpacity(0);
	dijiming->setPosition(Vec2(r_bg_yp->getContentSize().width/2 ,r_bg_yp->getContentSize().height * 0.5));
	r_bg_yp->addChild(dijiming,4);

	dijiming->runAction(Sequence::create(DelayTime::create(0.1f),FadeIn::create(0.1f),ScaleTo::create(0.1f,1),nullptr));
  //jywsb
	/*//星星2
	auto xingxing2 =  Sprite:: createWithSpriteFrameName("rewardstar2.png");
	xingxing2->setScale(0.8);
	xingxing2->setVisible(false);
	xingxing2->setPosition(Vec2(r_bg->getContentSize().width/2 ,r_bg->getContentSize().height * 0.8));
	r_bg->addChild(xingxing2,20);

	xingxing2->runAction(Sequence::create(DelayTime::create(0.5f),ToggleVisibility::create(),ScaleTo::create(tx_time,2),nullptr));

	//星星3
	auto xingxing3 =  Sprite:: createWithSpriteFrameName("rewardstar1.png");
	xingxing3->setScale(0.8);
	xingxing3->setVisible(false);
	xingxing3->setPosition(Vec2(r_bg->getContentSize().width/2 ,r_bg->getContentSize().height * 0.8));
	r_bg->addChild(xingxing3,20);

	xingxing3->runAction(Sequence::create(DelayTime::create(0.5f),ToggleVisibility::create(),ScaleTo::create(tx_time,1),nullptr));
	xingxing3->runAction(RepeatForever::create(Sequence::create(FadeOut::create(2.0f),FadeIn::create(2.0f),nullptr)));
	*/
	//获得奖励title
	auto r_hd_bg =  Sprite:: createWithSpriteFrameName("vip_js_neirong.png");
	r_hd_bg->setVisible(false);
	r_hd_bg->setPosition(Vec2(r_bg->getContentSize().width/2 , r_bg->getContentSize().height * 0.44));
	r_bg->addChild(r_hd_bg,10);
 
	r_hd_bg->runAction(Sequence::create(DelayTime::create(1.05f),ToggleVisibility::create(),nullptr));
 
	//炫耀按钮
	auto xuanyao = Sprite:: createWithSpriteFrameName("XR_qd.png");
	auto xuanyao_item = MenuItemSprite::create(xuanyao,xuanyao,CC_CALLBACK_0(VIPgongxi::exit,this));
	auto xuanyao_menu = Menu::create(xuanyao_item,nullptr);
	xuanyao_menu->setVisible(false);
	xuanyao_menu->setPosition(Vec2(r_bg->getContentSize().width/2,55));
	r_bg->addChild(xuanyao_menu);
 
	xuanyao_menu->runAction(Sequence::create(DelayTime::create(1.5f),ToggleVisibility::create(),nullptr));

	//exit按钮
	auto exit_sp = Sprite:: createWithSpriteFrameName("hall_menu_X.png");
	auto exit_sp_d = Sprite:: createWithSpriteFrameName("hall_menu_X_d.png");
	auto exit_item = MenuItemSprite::create(exit_sp,exit_sp_d,CC_CALLBACK_0(VIPgongxi::exit,this));
	auto exit_menu = Menu::create(exit_item,nullptr);
	exit_menu->setPosition(Vec2(r_bg->getContentSize().width - 12,r_bg->getContentSize().height * 0.85));
	r_bg->addChild(exit_menu,10);
}

void VIPgongxi::init_2()
{
	char tmp_char[50];
	//背景
	r_bg =  Sprite:: createWithSpriteFrameName("vip_js_bg.png");
	r_bg->setPosition(Vec2(visibleSize.width/2 , visibleSize.height * 0.5));
	r_bg->setScale(0.45);
	this->addChild(r_bg,MENULAYER);

	//圆盘
	sprintf(tmp_char,"RankYuan%d.png",1);
	auto r_bg_yp =  Sprite:: createWithSpriteFrameName(tmp_char);
	r_bg_yp->setPosition(Vec2(r_bg->getContentSize().width/2 ,r_bg->getContentSize().height * 0.795));
	r_bg->addChild(r_bg_yp,10);

	//圆盘后面的光
	/*sprintf(tmp_char,"Ranklight%d.png",1);
	auto r_bg_yp_g =  Sprite:: createWithSpriteFrameName(tmp_char);
	r_bg_yp_g->setScale(0.5);
	r_bg_yp_g->setVisible(false);
	r_bg_yp_g->setPosition(Vec2(r_bg_yp->getContentSize().width/2 ,r_bg_yp->getContentSize().height * 0.5));
	r_bg_yp->addChild(r_bg_yp_g,-2);

	//背景光执行动画
	r_bg_yp_g->runAction(Sequence::create(DelayTime::create(0.1f),ToggleVisibility::create(),ScaleTo::create(0.1f,1),nullptr));
 */
	//光上散的字
	auto r_bg_yp_gzi =  Sprite:: createWithSpriteFrameName("vip_js_saikai.png");
	r_bg_yp_gzi->setScale(0.2);
	r_bg_yp_gzi->setVisible(false);
	r_bg_yp_gzi->setPosition(Vec2(r_bg_yp->getContentSize().width/2 ,r_bg_yp->getContentSize().height));
	r_bg_yp->addChild(r_bg_yp_gzi,-1);
	r_bg_yp_gzi->runAction(Sequence::create(DelayTime::create(0.1f),ToggleVisibility::create(),ScaleTo::create(0.1f,1),nullptr));

	r_bg->runAction(ScaleTo::create(0.2f,1));

	float tx_time = 0.15f;
	//翅膀1
	sprintf(tmp_char,"Rankchibang%d.png",1);
	auto chibang1 =  Sprite:: createWithSpriteFrameName(tmp_char);
	chibang1->setScale(0.8);
	chibang1->setVisible(false);
	chibang1->setRotation(-30);
	chibang1->setPosition(Vec2(r_bg_yp->getContentSize().width/2 ,r_bg_yp->getContentSize().height * 0.3));
	r_bg_yp->addChild(chibang1,-1);

	chibang1->runAction(Sequence::create(DelayTime::create(0.5f),ToggleVisibility::create(),Spawn::create(ScaleTo::create(tx_time,0.8),RotateBy::create(tx_time,30),MoveBy::create(tx_time,Vec2(70,20)),nullptr),nullptr));

	//翅膀2
	sprintf(tmp_char,"Rankchibang%d.png",1);
	auto chibang2 =  Sprite:: createWithSpriteFrameName(tmp_char);
	chibang2->setFlippedX(true);
	chibang2->setScale(0.8);
	chibang2->setRotation(30);
	chibang2->setVisible(false);
	chibang2->setPosition(Vec2(r_bg_yp->getContentSize().width/2 ,r_bg_yp->getContentSize().height * 0.3));
	r_bg_yp->addChild(chibang2,-1);

	chibang2->runAction(Sequence::create(DelayTime::create(0.5f),ToggleVisibility::create(),Spawn::create(ScaleTo::create(tx_time,0.8),RotateBy::create(tx_time,-30),MoveBy::create(tx_time,Vec2(-70,20)),nullptr),nullptr));

	//蝴蝶结
	auto hudiejie =  Sprite:: createWithSpriteFrameName("vip_gongxi.png");
	hudiejie->setScale(0.0001);
	hudiejie->setVisible(false);
	hudiejie->setPosition(Vec2(r_bg_yp->getContentSize().width/2 ,r_bg_yp->getContentSize().height * 0.1));
	r_bg_yp->addChild(hudiejie,5);

	hudiejie->runAction(Sequence::create(DelayTime::create(0.5f),ToggleVisibility::create(),ScaleTo::create(tx_time,1),nullptr));
	 
	 //1字
	auto dijiming =  Sprite:: createWithSpriteFrameName("vip_js_vip.png");
	dijiming->setScale(3);
	dijiming->setOpacity(0);
	dijiming->setPosition(Vec2(r_bg_yp->getContentSize().width/2 ,r_bg_yp->getContentSize().height * 0.5));
	r_bg_yp->addChild(dijiming,4);

	dijiming->runAction(Sequence::create(DelayTime::create(0.1f),FadeIn::create(0.1f),ScaleTo::create(0.1f,1),nullptr));
  
	////星星2
	//auto xingxing2 =  Sprite:: createWithSpriteFrameName("rewardstar2.png");
	//xingxing2->setScale(0.8);
	//xingxing2->setVisible(false);
	//xingxing2->setPosition(Vec2(r_bg->getContentSize().width/2 ,r_bg->getContentSize().height * 0.8));
	//r_bg->addChild(xingxing2,20);

	//xingxing2->runAction(Sequence::create(DelayTime::create(0.5f),ToggleVisibility::create(),ScaleTo::create(tx_time,2),nullptr));

	//星星3
    /*
	auto xingxing3 =  Sprite:: createWithSpriteFrameName("rewardstar1.png");
	xingxing3->setScale(0.8);
	xingxing3->setVisible(false);
	xingxing3->setPosition(Vec2(r_bg->getContentSize().width/2 ,r_bg->getContentSize().height * 0.8));
	r_bg->addChild(xingxing3,20);

	xingxing3->runAction(Sequence::create(DelayTime::create(0.5f),ToggleVisibility::create(),ScaleTo::create(tx_time,1),nullptr));
*/
	//获得奖励title
	auto r_hd_bg =  Sprite:: createWithSpriteFrameName("VIP_dayR.png");
	r_hd_bg->setVisible(false);
	r_hd_bg->setPosition(Vec2(r_bg->getContentSize().width/2 , r_bg->getContentSize().height * 0.44));
	r_bg->addChild(r_hd_bg,10);
 
	r_hd_bg->runAction(Sequence::create(DelayTime::create(1.05f),ToggleVisibility::create(),nullptr));
 
	//确定按钮
	auto xuanyao = Sprite:: createWithSpriteFrameName("XR_qd.png");
	auto xuanyao_item = MenuItemSprite::create(xuanyao,xuanyao,CC_CALLBACK_0(VIPgongxi::exit,this));
	auto xuanyao_menu = Menu::create(xuanyao_item,nullptr);
	xuanyao_menu->setVisible(false);
	xuanyao_menu->setPosition(Vec2(r_bg->getContentSize().width/2,55));
	r_bg->addChild(xuanyao_menu);
 
	xuanyao_menu->runAction(Sequence::create(DelayTime::create(1.5f),ToggleVisibility::create(),nullptr));
 
}

bool VIPgongxi::init(int btnKind )
{  
	if ( !Layer::init() )	
	{
		return false;
	}
	Vip_leixing = btnKind;  //1, 来自大厅  2.来自场景内  ，3 来自大厅的每日领取 , 4 来自场景内的每日领取

	/*this->setScale(0.1f);
	ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.1f, 1.0);  
	this->runAction(Sequence::create(ac7,ac8,nullptr)); */

	auto zheZhao = LayerColor::create(ccc4(0,0,0,120),1024,768);
 	zheZhao->setPosition(Point::ZERO);
	zheZhao->setScale(2.0f);
	this->addChild(zheZhao);
 
	visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();
		
	
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(VIPgongxi::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(VIPgongxi::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(VIPgongxi::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触�?
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
 
	if(Vip_leixing == 1 || Vip_leixing == 2)
	{
		init_1();
	}
 
	if(Vip_leixing == 3 || Vip_leixing == 4)
	{
		init_2();
	}

	auto sajinbi = ParticleSystemQuad::create("jinbi.plist");
	sajinbi->retain();
	auto batch = ParticleBatchNode::createWithTexture(sajinbi->getTexture()); 
	batch->addChild(sajinbi); 
	addChild(batch); 
	sajinbi->setPosition(Point(visibleSize.width*0.5,visibleSize.height* 0.45));
	sajinbi->resetSystem();

	 return true;
}

void VIPgongxi::VIP_xuanyao()
{
	utils::captureScreen(CC_CALLBACK_2(VIPgongxi::afterCaptured,this),"vipGongxi.jpg");
 
}

void VIPgongxi::afterCaptured(bool succeed, const std::string& outputFile)
{
    if (succeed)
    {
		   //TODO
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
       JniMethodInfo minfo;
		jobject jobj;
		if( JniHelper::getStaticMethodInfo(minfo,"org.cocos2dx.cpp.AppActivity","startLoginWithType","(I)V") )
		{	
			jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID,23);//3
			minfo.env->DeleteLocalRef(minfo.classID);		
		}
#endif  
    }
    else
    {
        log("Capture screen failed.");
    }

	if(gamehall_re)
	{
		gamehall_re = false;
		GameBegin::setFileData("gameMaxPao.txt",8);
		this->removeAllChildrenWithCleanup(true);
		this->stopAllActions();

		auto scene = GameHallLayer::createScene();
		Director::getInstance()->replaceScene(scene);
	}
}

bool VIPgongxi::onTouchBegan(Touch* touch, Event* event) 
{ 

	return true;
}

void VIPgongxi::onTouchMoved(Touch* touch, Event* event) 
{

}

void VIPgongxi::onTouchEnded(Touch* touch, Event* event)
{

}
 
void VIPgongxi::exit()
{	 
	GameBegin::buttonSound();
	ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
	r_bg->runAction(Sequence::create(ac7,ac8,RemoveSelf::create(),nullptr) ); 

	this->runAction(Sequence::create(DelayTime::create(0.3f),RemoveSelf::create(),nullptr));
	if(gamehall_re)
	{
		gamehall_re = false;
		GameBegin::setFileData("gameMaxPao.txt",8);
		this->removeAllChildrenWithCleanup(true);
		this->stopAllActions();
        
        
		auto scene = GameHallLayer::createScene();
		Director::getInstance()->replaceScene(scene);
	}
}
 
 