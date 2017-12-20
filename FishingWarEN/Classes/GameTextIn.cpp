#include "GameTextIn.h"
#include "GameScene.h"
#include "GameData.h"
#include "GameBegin.h"
#include "Gongxi.h"
#include "GameHallLayer.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "../cocos2d/external/curl/include/ios/curl/curl.h"
#include <sys/stat.h> 
#include <unistd.h>
#include <dirent.h> 
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 

#include "../cocos2d/external/curl/include/android/curl/curl.h"
#include <sys/stat.h> 
#include <unistd.h>
#include <dirent.h> 
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include "..\cocos2d\external\curl\include\win32\curl\curl.h"
#endif

bool GameTextIn::duihuanFlag = false;
bool GameTextIn::fenxiang_dh_Flag = false;
 
int GameTextIn::duihuanvip = -1;
int GameTextIn::duihuanjinbi = -1;
int GameTextIn::duihuanhuafeiquan = -1;

int GameTextIn::duihuanzuanshi = -1;
int GameTextIn::duihuan_1yuan = -1;
int GameTextIn::duihuan_60jj = -1;
int GameTextIn::duihuan_90jj = -1;

int GameTextIn::libaoInt = 1;
Scene * GameTextIn::createScene()
{
	auto scene = Scene::create();
	auto layer = GameTextIn::create();
	scene->addChild(layer);

	return scene;
}

bool GameTextIn::init()
{  
	if ( !Layer::init() )	
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();

	auto zheZhao = LayerColor::create(ccc4(0,0,0,150),1024,768);
	zheZhao->setPosition(Point::ZERO);
	this->addChild(zheZhao);

	//øÿ÷∆√Ê∞Â
	controlBg = Scale9Sprite::createWithSpriteFrameName( "bs_kuang.png",CCRectMake(50,50,20,20));
	controlBg->setContentSize(CCSizeMake(600,250));
	controlBg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(controlBg);

	controlBg->setScale(0.1f);
	ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.1f, 1.0);  
	controlBg->runAction(Sequence::create(ac7,ac8,nullptr)); 
 
	auto shopCenterBg1 = Sprite::createWithSpriteFrameName("duihuama_title.png");
	shopCenterBg1->setPosition(Point(controlBg->getContentSize().width/2,controlBg->getContentSize().height));
	controlBg->addChild(shopCenterBg1,100);
 
	auto shangchengxx = MenuItemSprite::create(Sprite::createWithSpriteFrameName("hall_menu_X.png"),Sprite::createWithSpriteFrameName("hall_menu_X_d.png"), CC_CALLBACK_0(GameTextIn::exit,this));	
	auto m_ShangChengXX= Menu::create(shangchengxx, nullptr);
	m_ShangChengXX->setPosition(Vec2(controlBg->getContentSize().width - 10,controlBg->getContentSize().height - 10));
	controlBg->addChild(m_ShangChengXX,100);

	//∂“ªª¬Î±‡º≠øÚ
	shurukuang = EditBox::create(Size(550,45),Scale9Sprite::createWithSpriteFrameName("match_diren_mzk.png"),Scale9Sprite::createWithSpriteFrameName("match_diren_mzk.png"),nullptr);
	shurukuang->setPosition(Vec2(controlBg->getContentSize().width*0.5,controlBg->getContentSize().height * 0.6));
	shurukuang->setFont("Arial", 28);
    shurukuang->setFontColor(Color3B::WHITE);
	shurukuang->setPlaceHolder(GAME_DATA_STRING("shuruduihuanma"));
	shurukuang->setPlaceholderFontColor(Color3B::WHITE);
    shurukuang->setMaxLength(100);
    
    shurukuang->setInputMode(EditBox::InputMode::SINGLE_LINE);
	shurukuang->setReturnType(EditBox::KeyboardReturnType::DONE);
    shurukuang->setDelegate(this);
    controlBg->addChild(shurukuang,100);
	
	auto gongxiSprite = Sprite::createWithSpriteFrameName("XR_qd.png");
	auto gongxiItem = MenuItemSprite::create(gongxiSprite,gongxiSprite,gongxiSprite,CC_CALLBACK_0(GameTextIn::queding,this));
	auto gongxiMenu = Menu::create(gongxiItem,nullptr);
	gongxiMenu->setPosition(controlBg->getContentSize().width/2,0.23*controlBg->getContentSize().height);
	controlBg->addChild(gongxiMenu,100);
	this->scheduleUpdate();

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameTextIn::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(GameTextIn::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(GameTextIn::onTouchEnded,this);
	listener->setSwallowTouches(true);//≤ªœÚœ¬¥´µ›¥•√˛
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

    return true;
}

bool GameTextIn::onTouchBegan(Touch* touch, Event* event) 
{  
	return true;
}

void GameTextIn::onTouchMoved(Touch* touch, Event* event) 
{ 

}

void GameTextIn::onTouchEnded(Touch* touch, Event* event)
{

}
 
void GameTextIn::update(float dt)
{
	if(duihuanFlag)
	{
		duihuanFlag = false;
		float detime = 0;
		if(duihuanjinbi > 0 || duihuanzuanshi > 0 || duihuanhuafeiquan>0 || duihuanvip > 0 || duihuan_1yuan > 0 || duihuan_60jj > 0 || duihuan_90jj > 0)
		{
			if(duihuanjinbi > 0 || duihuanzuanshi > 0 || duihuanhuafeiquan > 0 )
			{
				duihuan_suc(1);
				detime+=1;
			}
			if(duihuan_1yuan > 0)
			{
				detime+=1;
				this->runAction(Sequence::create(DelayTime::create(detime),CCCallFunc::create([&]{duihuan_suc(3);}),nullptr));
			}
			if(duihuan_60jj > 0)
			{
				detime+=1;
				this->runAction(Sequence::create(DelayTime::create(detime),CCCallFunc::create([&]{duihuan_suc(4);}),nullptr));
			}
			if(duihuan_90jj > 0)
			{
				detime+=1;
				this->runAction(Sequence::create(DelayTime::create(detime),CCCallFunc::create([&]{duihuan_suc(5);}),nullptr));
			}	
			if(duihuanvip > 0)
			{	
				detime+=1;
				this->runAction(Sequence::create(DelayTime::create(detime),CCCallFunc::create([&]{duihuan_suc(2);}),nullptr));
			}
		}else
		{
			auto layer = this->getParent();
			auto gongxi = Gongxi::create(2,GAME_DATA_STRING("duihuanshibai"));
			gongxi->setPosition(Point::ZERO);
			layer->addChild(gongxi,1000);
		}
	
		this->runAction(Sequence::create(Hide::create(), DelayTime::create(detime+0.1f),CCCallFunc::create([&]{this->removeFromParentAndCleanup(true);}),nullptr));
	}

	if(fenxiang_dh_Flag)
	{
		fenxiang_dh_Flag = false;

		auto gongxi = Gongxi::create(2,GAME_DATA_STRING("duihuan_used"));
		this->getParent()->addChild(gongxi,1000);
		exit();
	}
}

void GameTextIn::duihuan_suc(int flag)
{
	int zengjiagold = 0;
	int zengjiazuanshi = 0;
	int zengjiahuafeiquan = 0;


	int yanzhengRMB = 0;
 
	GameBegin::playSound("goumai_suc.mp3");
	switch(flag)
	{
		case 1:	{
            
					zengjiagold = duihuanjinbi;	zengjiazuanshi = duihuanzuanshi; zengjiahuafeiquan = duihuanhuafeiquan; 
 
					UserDefault::getInstance()->flush();
				}break;
		case 2:	{
					yanzhengRMB = 30;	
					if(libaoInt == 1 )
					{
						GameHallLayer::vip_goumai_flag = true;					
					}else
					{
						GameScene::vip_goumai_flag = true;
					}

					UserDefault::getInstance()->setIntegerForKey("player_vip",1);
					time_t timevip= LogoLayer::getTime();
					UserDefault::getInstance()->setIntegerForKey("player_vip_time",timevip);
					 
					UserDefault::getInstance()->flush();
					return;

				}break;
		case 3:	{
					yanzhengRMB = 1;	
					zengjiagold = 20000;
					GameBegin::setFileData("gameMaxPao.txt",20);
					if(libaoInt == 1)
					{
						GameHallLayer::checkRedPoing = true;
						string paoname_tmp[4] = {"paothree.png","paofour.png","paofive.png","paosix.png"};
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
							this->getParent()->addChild(pao_sp,MENULAYER + 1);

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
					}
			}break;
		case 4:	{
					yanzhengRMB = 60;	
					UserDefault::getInstance()->setIntegerForKey("jijin_60_days",8);		
					UserDefault::getInstance()->flush();
				}break;
		case 5:	{
					yanzhengRMB = 90;	
					UserDefault::getInstance()->setIntegerForKey("jijin_90_days",8);
					UserDefault::getInstance()->flush();
				}break;
		default:break;
	}

	 
	UserDefault::getInstance()->flush();

	if(GameTextIn::libaoInt == 1)
	{
		GameHallLayer::RefreshCoin(zengjiagold);
		GameHallLayer::RefreshDiamond(zengjiazuanshi);
	}
	else
	{
		CannonLayer::GameCoinRefresh(zengjiagold);
		CannonLayer::GameCoinZuanshi(zengjiazuanshi);
	}
 
	if(flag < 4)
	{
		char gongxiTmp[100];
		sprintf(gongxiTmp,GAME_DATA_STRING("duihuanchenggong"),zengjiagold,zengjiazuanshi,zengjiahuafeiquan);

		auto gongxi = Gongxi::create(4,gongxiTmp);
		this->getParent()->addChild(gongxi,MENULAYER + 1);
	}
	if(flag == 4)
	{
		auto  gongxi = Gongxi::create(4,GAME_DATA_STRING("jijin_60_huode"));	 
		this->getParent()->addChild(gongxi,MENULAYER + 1);
	}
	if(flag == 5)
	{
		auto  gongxi = Gongxi::create(4,GAME_DATA_STRING("jijin_90_huode"));	 
		this->getParent()->addChild(gongxi,MENULAYER + 1);
	}
	
	 
	cocos2d::log("budan cheng  gong ");
}
 
void GameTextIn::editBoxReturn(EditBox *editBox)
{
	log("editBox %p was returned.", editBox->getText());
}

void GameTextIn::exit()
{
	GameBegin::buttonSound(); 
	ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
	controlBg->runAction(Sequence::create(ac7,ac8,nullptr)); 

	this->runAction(Sequence::create(DelayTime::create(0.3f),RemoveSelf::create(),nullptr));
}

void GameTextIn::queding()
{
    
    std::string duihuama= shurukuang->getText();

    if(duihuama == "")
    {
        auto gongxi = Gongxi::create(2,GAME_DATA_STRING("shuruduihuanma"));
        this->addChild(gongxi);
        return;
    }
    
    auto waitingQQ = Waiting::create();
    addChild(waitingQQ,1001,1001);
    cocos2d::log("Waiting::create()");
   
    this->scheduleOnce(schedule_selector(GameTextIn::duihuanUpdate), 0.5f);
    
}


void GameTextIn::duihuanUpdate(float dt)
{
    std::string duihuama= shurukuang->getText();
    
    if(duihuama.length() > 80)
    {
        duihuama = duihuama.substr(0,80);
    }
    
    
    string DeviceNo = UserDefault::getInstance()->getStringForKey("DeviceNo");
    CURL *curl;
    CURLcode res;
    
    curl=curl_easy_init();
    char postFields[200];
    sprintf(postFields,"code=%s&deviceId=%s",duihuama.c_str(),DeviceNo.c_str());
    cocos2d::log("SHOP::####### ****postFields:%s  ****",postFields);
    
    


    
    if(curl)
    {
        
        
        cocos2d::log("SHOP::####### *duihuan update 1 ****");
        
        curl_easy_setopt( curl, CURLOPT_URL, "http://dwby-hk.iyueyo.com/qpby2/iosfanti/ios_gift_en_v6.php"); //«Î«Ûµƒµÿ÷∑
         cocos2d::log("SHOP::####### *duihuan update 2 ****");
        curl_easy_setopt(curl, CURLOPT_POST, true);           //∆Ù”√POSTÃ·Ωª
        
         cocos2d::log("SHOP::####### *duihuan update 3 ****");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields); //∑¢ÀÕµƒ ˝æ›
        
         cocos2d::log("SHOP::####### *duihuan update 4 ****");
        curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L);
        
         cocos2d::log("SHOP::####### *duihuan update 5 ****");
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&possText); //¥¶¿Ìµƒ∫Ø ˝
        
         cocos2d::log("SHOP::####### *duihuan update 6 ****");
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
 //       curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1);
        
         cocos2d::log("SHOP::####### *duihuan update 7 ****");
        res=curl_easy_perform(curl);
        
         cocos2d::log("SHOP::####### *duihuan update 8 ****");
        if(res!=CURLE_OK)
        {
            // log("¡™Õ¯≥¨ ± %i",res);
            duihuanjinbi = 0;
            duihuanFlag = true;
        }
        curl_easy_cleanup(curl);
    }
    else
    {
        cocos2d::log("curl shi kong de ");
        return ;
    }
}

size_t  GameTextIn::possText(uint8_t *buffer,size_t size,size_t nmemb,void *stream)
{
	//¥Ú”° ’µΩµƒ ˝æ›
	cocos2d::log("SHOP::*****possIt_____%s____",(const char *)buffer);	
	string userTmp = (const char *)buffer;
	if( userTmp  == "used" /*|| userTmp  == "null"*/)
	{
		GameTextIn::fenxiang_dh_Flag = true;
		return size*nmemb;
	}
	
	char tmp1[30]= ""; //Ω±“
	char tmp2[30]= ""; //◊Í Ø
	char tmp[30] = ""; //ª∞∑—»Ø

	char tmp3[4] = ""; //vip
	char tmp4[4] = ""; //“ª‘™¿Ò∞¸
	char tmp5[4] = ""; //60ª˘Ω
	char tmp6[4] = ""; //90ª˘Ω
 
	int i=0;
	int j=0;
	int m = 0;

	while(buffer[i]!='\0')
	{
		char c = buffer[i];
		if(c=='-')
		{
			j++;	
			m = 0;
		}
		else
		{
			if(j == 0)
			{
				tmp1[m] = c;				
			}
			if(j == 1)
			{
				tmp2[m] = c;
			}
			if(j == 2)
			{
				tmp[m] = c;
			}

			if(j == 3)
			{
				tmp3[0] = c;
			}
			if(j == 4)
			{
				tmp4[0] = c;
			}
			if(j == 5)
			{
				tmp5[0] = c;
			}
			if(j == 6)
			{
				tmp6[0] = c;
			}
			m++;
		}
		i++;
	}

	duihuanjinbi = atoi((const char *)tmp1);	
	duihuanzuanshi = atoi((const char *)tmp2);
	duihuanhuafeiquan = atoi((const char *)tmp);

	duihuanvip = atoi((const char *)tmp3);
	duihuan_1yuan = atoi((const char *)tmp4);
	duihuan_60jj = atoi((const char *)tmp5);
	duihuan_90jj = atoi((const char *)tmp6);

	if(duihuanjinbi > 0 || duihuanzuanshi > 0 || duihuanhuafeiquan>0 || duihuanvip > 0 || duihuan_1yuan > 0 || duihuan_60jj > 0 || duihuan_90jj > 0)
	{
		duihuanFlag = true;
	}
	else
	{
	//	log("∂©µ• ß∞‹£°");
		duihuanjinbi = -1;
		duihuanzuanshi = -1;
		duihuanhuafeiquan = -1;

		duihuanvip = -1;
		duihuan_1yuan = -1;
		duihuan_60jj = -1;
		duihuan_90jj = -1;

		duihuanFlag = true;
	}

	//∑µªÿ ˝æ›≥§∂»
	size_t sizes = size*nmemb;
	return sizes;
}
