#include "HongBao.h" 
 
#include "GameBegin.h"
#include "GameData.h"
#include <math.h>

USING_NS_CC; 
Scene * HongBao::createScene()
{
	auto scene = Scene::create();
	auto layer = HongBao::create();
	scene->addChild(layer);
	return scene;
}

bool HongBao::init()
{  
	if ( !Layer::init() )	
	{
		return false;
	}

	auto zheZhao = LayerColor::create(ccc4(0,0,0,150),1024,768);
	zheZhao->setPosition(Point::ZERO);
	zheZhao->setScale(2.0f);
	this->addChild(zheZhao);

	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();
	isKaishi = false;
	zTime = 0;
	shuzhiTmp = 0;
	srand(time(NULL));
	zuiTime = 0;

    int leijichongzhi = GameBegin::getFileData("wflei.txt");
	if(leijichongzhi == 0)
	{
		zuidizhi = 500;
		zuigaozhi = 2000;
	}
	if(leijichongzhi > 0 && leijichongzhi<= 20)
	{
		zuidizhi = 2000;
		zuigaozhi = 6000;
	}
	if(leijichongzhi > 20 && leijichongzhi< 50)
	{
		zuidizhi = 3000;
		zuigaozhi = 8000;
	}
	if(leijichongzhi >= 50 && leijichongzhi< 100)
	{
		zuidizhi = 3000;
		zuigaozhi = 10000;
	}
	if(leijichongzhi > 100 && leijichongzhi< 500)
	{
		zuidizhi = 4000;
		zuigaozhi = 15000;
	}
	if(leijichongzhi > 500)
	{
		zuidizhi = 5000;
		zuigaozhi = 30000;
	}

	//背景
	denglong = Sprite::createWithSpriteFrameName("HB_bg1.png");
	denglong->setPosition(Vec2(visibleSize/2));
	addChild(denglong,100);

	denglong->setScale(0.1f);
	ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.1f, 1.0);  
	denglong->runAction(Sequence::create(ac7,ac8,nullptr)); 
 
	//恭喜字
	gongxi = Sprite::createWithSpriteFrameName("gongxizi.png");
	gongxi->setPosition(Vec2(denglong->getContentSize().width*0.5,denglong->getContentSize().height + 30));
	denglong->addChild(gongxi,10);
	gongxi->setScale(0.1);
	gongxi->setVisible(false);

	//返回按钮
	auto fanhui  = Sprite::createWithSpriteFrameName("HB_xx.png");
	auto fanhuiItem = MenuItemSprite::create(fanhui,fanhui,CC_CALLBACK_1(HongBao::exit,this));
	auto fabhuiMenu = Menu::create(fanhuiItem,nullptr);
	fabhuiMenu->setPosition(Vec2(denglong->getContentSize().width - 10,denglong->getContentSize().height - 10));
	denglong->addChild(fabhuiMenu);

	//跑马灯
	auto hb_paodeng = Sprite::createWithSpriteFrameName("HB_paodeng1.png");
	hb_paodeng->setPosition(Vec2(denglong->getContentSize().width/2,denglong->getContentSize().height * 0.71635));
	denglong->addChild(hb_paodeng);

	auto paodengA = AnimationCache::getInstance()->getAnimation("hb_paomadeng");
	auto *  pdAnimate = Animate::create(paodengA);
	hb_paodeng->runAction(RepeatForever::create(pdAnimate)); 

	hb_shuzhi = Label::createWithCharMap("img/HB_word.png",40,61,'0');
	hb_shuzhi->setString("999999");
	hb_shuzhi->setPosition(Vec2(denglong->getContentSize().width/2,denglong->getContentSize().height * 0.715));
	denglong->addChild(hb_shuzhi);

	//分享
	auto fenxiang = Sprite::createWithSpriteFrameName("HB_queding.png");
    Item_fx = MenuItemSprite::create(fenxiang,fenxiang,CC_CALLBACK_1(HongBao::exit,this));
	Item_fx->setOpacity(0);
	auto fxMenu = Menu::create(Item_fx,nullptr);
	fxMenu->setPosition(Vec2(denglong->getContentSize().width/2,denglong->getContentSize().height * 0.359));
	denglong->addChild(fxMenu);


	//抢鱼币
	auto beginAN = Sprite::createWithSpriteFrameName("HB_qiang.png");
	Item_qyb = MenuItemSprite::create(beginAN,beginAN,CC_CALLBACK_1(HongBao::qianghongbao,this));
	auto beginMenu = Menu::create(Item_qyb,nullptr);
	beginMenu->setPosition(Vec2(denglong->getContentSize().width/2,denglong->getContentSize().height * 0.359));
	denglong->addChild(beginMenu);
 
	//领取详情
	auto beginAN1 = Sprite::createWithSpriteFrameName("HB_xiangqing.png");
	auto beginItem1 = MenuItemSprite::create(beginAN1,beginAN1,CC_CALLBACK_1(HongBao::xiangqing,this));
	auto beginMenu1 = Menu::create(beginItem1,nullptr);
	beginMenu1->setPosition(Vec2(denglong->getContentSize().width/2,denglong->getContentSize().height * 0.166));
	denglong->addChild(beginMenu1);

	//添加触摸事件
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HongBao::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(HongBao::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(HongBao::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
 
	return true;
}

void HongBao::update(float dt)
{
	if(isKaishi && zTime < 3.1)
	{
		zTime += dt;
		shuzhiTmp = CCRANDOM_0_1() * 999999;
		sprintf(hb_tmpchar,"%d",shuzhiTmp);
		hb_shuzhi->setString(hb_tmpchar);
		if(zTime>1)
		{

			sprintf(hb_tmpchar,"0%d",zuidizhi);
			if(zuidizhi<10000)
			{
				sprintf(hb_tmpchar,"00%d",zuidizhi);
			}
			if(zuidizhi<1000)
			{
				sprintf(hb_tmpchar,"000%d",zuidizhi);
			}
			if(zuidizhi<100)
			{
				sprintf(hb_tmpchar,"0000%d",zuidizhi);
			}
			if(zuidizhi<10)
			{
				sprintf(hb_tmpchar,"00000%d",zuidizhi);
			}
			hb_shuzhi->setString(hb_tmpchar);
			zTime = 0;
			isKaishi = false;
			this->unscheduleUpdate();

			

			gongxi->setVisible(true);
			auto scaleTo = ScaleTo::create(0.2f,1);
			gongxi->runAction(scaleTo);
 		
			auto sajinbi = ParticleSystemQuad::create("jinbi.plist");
			auto batch = ParticleBatchNode::createWithTexture(sajinbi->getTexture()); 
			batch->addChild(sajinbi); 
			sajinbi->setPosition(Point(visibleSize.width*0.2,visibleSize.height* 0.75));
			sajinbi->resetSystem();
			addChild(batch);

			auto sajinbi1 = ParticleSystemQuad::create("jinbi.plist");
			auto batch1 = ParticleBatchNode::createWithTexture(sajinbi1->getTexture()); 
			batch1->addChild(sajinbi1); 
			sajinbi1->setPosition(Point(visibleSize.width*0.7,visibleSize.height* 0.75));
			sajinbi1->resetSystem();
			addChild(batch1);

			auto sajinbi2 = ParticleSystemQuad::create("jinbi.plist");
			auto batch2 = ParticleBatchNode::createWithTexture(sajinbi2->getTexture()); 
			batch2->addChild(sajinbi2); 
			sajinbi2->setPosition(Point(visibleSize.width*0.3,visibleSize.height* 0.75));
			sajinbi2->resetSystem();
			addChild(batch2);
		}
	}
}
  
void HongBao::exit(Ref * serder)
{
	//移除转盘
	this->stopAllActions();
	ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
	denglong->runAction(Sequence::create(ac7,ac8,nullptr)); 

	this->runAction(Sequence::create(DelayTime::create(0.3f),RemoveSelf::create(),nullptr));
}

void HongBao::qianghongbao(Ref * serder)
{
    GameBegin::playSound("goumai_suc.mp3");
    
	GameHallLayer::hall_hb_times = 7200;
    
    
    time_t currentTime;
    time(&currentTime);
    
    GameBegin::setFileData("hb_last_lq_time.txt", (int)currentTime);
    //time_t timeTmp =  currentTime - 365*24*60*60*(2014 - 1970) + 28800  ;//因为之后用的是gmtime  所以这里加了8小时
    
    //GameHallLayer::hall_hb_time_t = timeTmp;
	GameHallLayer::hall_hb_kaiguan = true;

	zuidizhi = CCRANDOM_0_1() * (zuigaozhi - zuidizhi) + zuidizhi;

	zuiTime = currentTime;
	GameHallLayer::RefreshCoin(zuidizhi);

	//写进txt文档
	//FILE * tmpFile1;
	string moneypath = FileUtils::getInstance()->getWritablePath() + "hongbao.txt";	
	FILE * tmpFile2; 
	char sdf1[200];// = "(522200,3224)\r\n"; 
	sprintf(sdf1,"(%d,%d)\r\n",(int)zuiTime,zuidizhi);
	tmpFile2 = fopen(moneypath.c_str(),"a+"); 
	fputs(sdf1,tmpFile2);  
	fclose(tmpFile2);

	//写入数据
	UserDefault::getInstance()->setDoubleForKey("hb_leiji",UserDefault::getInstance()->getDoubleForKey("hb_leiji") + zuidizhi);
	UserDefault::getInstance()->flush();

	this->scheduleUpdate(); 
	isKaishi = true;

	Item_qyb->setEnabled(false);
	auto qyuFadeOut =  FadeOut::create(1.0f);
	auto qybDelete = RemoveSelf::create();
	Item_qyb->runAction(Sequence::create(qyuFadeOut,qybDelete,nullptr));

	auto fxDelay = DelayTime::create(1.0f);
	auto fxFadeIn = FadeIn::create(0.5f);
	Item_fx->runAction(Sequence::create( fxDelay,fxFadeIn,nullptr));

	//this->scheduleOnce(schedule_selector(HongBao::jieping),1.15f);
}

void HongBao::jieping(float dt)
{
	 utils::captureScreen(CC_CALLBACK_2(HongBao::afterCaptured,this),"hongbao1.png");
 

}

void HongBao::afterCaptured(bool succeed, const std::string& outputFile)
{
    if (succeed)
    {
 
    }
    else
    {
        log("Capture screen failed.");
    }
}
 
void HongBao::fenxiang(Ref * serder)
{
    std::string ere = "Icon-180.png";
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(ere);
    
     
}

void HongBao::xiangqing(Ref * serder)
{
	//领取详情 TODO
	auto scene = HongBaoXQ::createScene();
	this->addChild(scene,10000);
}
 
bool HongBao::onTouchBegan(Touch* touch, Event* event) 
{ 
	return true;
}

void HongBao::onTouchMoved(Touch* touch, Event* event) 
{

}

void HongBao::onTouchEnded(Touch* touch, Event* event)
{

}

Scene * HongBaoXQ::createScene()
{
	auto scene = Scene::create();
	auto layer = HongBaoXQ::create();
	scene->addChild(layer);
	return scene;
}

void HongBaoXQ::readXiangq()
{
	FILE * tmpFile;  

	string moneypath = FileUtils::getInstance()->getWritablePath() + "hongbao.txt";	
	tmpFile = fopen(moneypath.c_str(),"rb"); 
	char  DatBuf2[2000];

	memset(DatBuf2,0,sizeof(DatBuf2));
	if(tmpFile)
	{
		fread(DatBuf2,2000,1,tmpFile); 
		fclose(tmpFile); 
	}   


	char  token[50];   
	char *line;
	int temp = 0; 
	
	line = strtok( DatBuf2,"\n");//获取.dat文件内容的每一行
  
	if(line != NULL) 
	{
		while(line[0] == '(')//对.dat文件接下来的数据逐行读取,并取得相关数据存入相应变量当中
		{

			if(line == NULL)
				break;
			if (strcmp(line,"\r\n")==0 || strcmp(line,"\n")==0) 
				continue;

			int tempFlag = 0;
			temp = 0;
			if(line[0]=='(')
			{
				for(int i = 1 ; i < strlen(line) ;i++)
				{
					if((line[i]==','||line[i]=='\r')&&token!=NULL)
					{
						switch (tempFlag)
						{
						case 0:wf1.push_back(atoi(token)) ;break;
						case 1:wf2.push_back(atoi(token));break; 
						default:
							break;
						}
						memset(token,0,sizeof(token));
						temp = 0;
						tempFlag++;
						continue;
					} 
					char c = line[i];
					token[temp] = c;
					temp++;
				}
			} 
			line = strtok(NULL,"\n");//获取.dat文件的下一行文件 
			if(line == NULL)
				break;
		}
	}
	
}

string returnRiQi(int riqi)
{
	char tmpTTT[20];
	time_t tmpT = riqi + 365*24*60*60*(2014 - 1970);
	struct tm *nowTime = gmtime(&tmpT);
	int year = nowTime->tm_year + 1900;
	int mon = nowTime->tm_mon + 1;
	int day = nowTime->tm_mday;
	int hour = nowTime->tm_hour;
	int min = nowTime->tm_min;
	sprintf(tmpTTT,"%d.%d.%d %d%d:%d%d",year,mon,day,hour/10,hour%10,min/10,min%10);

	return tmpTTT;
}

bool HongBaoXQ::init()
{  
	if ( !Layer::init() )	
	{
		return false;
	}
 
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();
 
	this->setScale(0.1f);
	ScaleTo *ac7=ScaleTo::create(0.2f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.1f, 1.0);  
	this->runAction(Sequence::create(ac7,ac8,nullptr)); 

	if(wf1.size() == 0)
		readXiangq();
 
	//背景
	auto denglong = Sprite::createWithSpriteFrameName("HB_bg2.png");
	denglong->setScale(1.1);
	denglong->setPosition(Vec2(visibleSize/2));
	addChild(denglong);
 
	auto hb_ljhd = Sprite::createWithSpriteFrameName("HB_huode.png");
	hb_ljhd->setPosition(Vec2(denglong->getContentSize().width/2,denglong->getContentSize().height * 0.862));
	denglong->addChild(hb_ljhd);

	char ljhdTmp[20];
	int leijiTmp = UserDefault::getInstance()->getDoubleForKey("hb_leiji");
	sprintf(ljhdTmp,"%d%d%d%d%d%d%d%d",leijiTmp/10000000,(leijiTmp/1000000)%10,(leijiTmp/100000)%10,(leijiTmp/10000)%10,(leijiTmp/1000)%10,(leijiTmp/100)%10,(leijiTmp/10)%10,leijiTmp%10);

	auto hb_ljsz = Label::createWithCharMap("img/HB_word.png",40,61,'0');
	hb_ljsz->setString(ljhdTmp);
	hb_ljsz->setScale(0.9);
	hb_ljsz->setPosition(Vec2(denglong->getContentSize().width/2,denglong->getContentSize().height * 0.74));
	denglong->addChild(hb_ljsz);

	//详情 296 * 172  296 * 27  5 5
	xqSize = Size(296,27);
	int xqSizeNum = wf1.size();
	//设置层
	containerLayer = Layer::create();//创建视图的容器
	containerLayer->ignoreAnchorPointForPosition(false);
	containerLayer->setAnchorPoint(Vec2(0,1));
	containerLayer->setPosition(Point(0,( 6-xqSizeNum ) * xqSize.height));
	containerLayer->setContentSize(CCSizeMake(296,xqSize.height * xqSizeNum + 10));
 
	//创建一个滚动视图
	scrollView = ScrollView::create();	
	scrollView->setViewSize(CCSizeMake(296,172));//设置view的大小 (roomSpaceLenth + roomSize.width)*3
	scrollView->setContentOffset(Vec2::ZERO);
	scrollView->setContainer(containerLayer); //设置需要滚动的内容
	scrollView->ignoreAnchorPointForPosition(false);
	scrollView->setAnchorPoint(Vec2(0.5,0));
	scrollView->setPosition(Point(denglong->getContentSize().width/2,100));
	scrollView->setTouchEnabled(true);
	scrollView->setDirection(ScrollView::Direction::VERTICAL);
	scrollView->setDelegate(this);
	denglong->addChild(scrollView,100);

	char hb_tmp_xq[200];
	char hb_tmp_xq1[50];

	for(int i = 0 ; i < xqSizeNum ; i++)
	{
		sprintf(hb_tmp_xq1,GAME_DATA_STRING("hall_hb_xq"),wf2.at(i));
		sprintf(hb_tmp_xq,"%s",hb_tmp_xq1);

		auto xq_label = LabelTTF::create(hb_tmp_xq,"Arial",16);
		xq_label->setColor(Color3B(217,217,217));
		xq_label->setPosition(Vec2(containerLayer->getContentSize().width/2,5 + xqSize.height * (i + 0.5)));
		containerLayer->addChild(xq_label);
	}
 
	//返回 ,分享按钮
	auto fenxiang = Sprite::createWithSpriteFrameName("HB_queding.png");
	Item_fx = MenuItemSprite::create(fenxiang,fenxiang,CC_CALLBACK_1(HongBaoXQ::exit,this));
	Item_fx->setScale(0.6);

	auto fanhui  = Sprite::createWithSpriteFrameName("HB_fanhui.png");
	Item_fanhui = MenuItemSprite::create(fanhui,fanhui,CC_CALLBACK_1(HongBaoXQ::exit,this));

	auto fxMenu = Menu::create(Item_fx,Item_fanhui,nullptr);
	fxMenu->alignItemsHorizontallyWithPadding(15);
	fxMenu->setPosition(Vec2(denglong->getContentSize().width/2,denglong->getContentSize().height * 0.136));
	denglong->addChild(fxMenu);

	//添加触摸事件
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HongBaoXQ::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(HongBaoXQ::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(HongBaoXQ::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
 
	return true;
}
 
void HongBaoXQ::exit(Ref * serder)
{
	//移除转盘
	this->stopAllActions();
	ScaleTo *ac7=ScaleTo::create(0.1f, 1.05f);  
	ScaleTo *ac8=ScaleTo::create(0.2f, 0.1f);  
	this->runAction(Sequence::create(ac7,ac8,RemoveSelf::create(),nullptr)); 
}
 
void HongBaoXQ::fenxiang(Ref * serder)
{
	utils::captureScreen(CC_CALLBACK_2(HongBaoXQ::afterCaptured,this),"hongbao2.jpg");
	cocos2d::log("order 9");
}

void HongBaoXQ::afterCaptured(bool succeed, const std::string& outputFile)
{
    if (succeed)
    {
		   //TODO
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
       JniMethodInfo minfo;
		jobject jobj;
		if( JniHelper::getStaticMethodInfo(minfo,"org.cocos2dx.cpp.AppActivity","startLoginWithType","(I)V") )
		{	
			jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID,22);//3
			minfo.env->DeleteLocalRef(minfo.classID);		
		}
#endif  
    }
    else
    {
        log("Capture screen failed.");
    }
}
 
 
 //滑动板函数
void HongBaoXQ::scrollViewDidScroll(extension::ScrollView* view) 
{
 
}

void HongBaoXQ::scrollViewDidZoom(ScrollView* view) 
{
}

bool HongBaoXQ::onTouchBegan(Touch* touch, Event* event) 
{ 
	return true;
}

void HongBaoXQ::onTouchMoved(Touch* touch, Event* event) 
{

}

void HongBaoXQ::onTouchEnded(Touch* touch, Event* event)
{

}
