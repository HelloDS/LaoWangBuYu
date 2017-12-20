
#include "UIWebViewTest.h"

#include "TcpClientSocket.h"
#include"LogoLayer.h"
#include"GameBegin.h" 
#include "Shop.h"
#include "Gongxi.h"


#include "CannonUpgrade.h"
#include "GameScene.h"
#include "ChallengeBOSS.h"
#include "GameHallLayer.h"

WebViewTest * WebViewTest::create(int iType,int iHeight,int Weight)
{
    WebViewTest * lr = new WebViewTest();
    
    lr->init(iType, iHeight, Weight);
    
    lr->autorelease();
    
    return lr;
}

//add by zxf 
void WebViewTest::showTitle()
{
	auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto quit = MenuItemImage::create("back.png", "back.png", CC_CALLBACK_0(WebViewTest::quit, this));
	auto quitMenu = Menu::create(quit, nullptr);
	quitMenu->setPosition(Vec2(visibleSize.width - 30, visibleSize.height - 30));
	layer->addChild(quitMenu);
	this->addChild(layer);
}

void WebViewTest::quit()
{
	cocos2d::log("WebViewTest::quit");
	this->unscheduleAllSelectors();
	this->removeAllChildren();
	this->removeFromParentAndCleanup(true);
}


bool WebViewTest::init(int iType,int iHeight,int Weight)
{
    
    if ( !Layer::init() )
    {
        return false;
    }

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	showTitle();
    Size winSize = Director::getInstance()->getVisibleSize();
	
	 _webView = cocos2d::experimental::ui::WebView::create();
	 
	//cocos2d::experimental::ui::WebView *webView = cocos2d::experimental::ui::WebView::create();
	//_webView->setPosition(winSize/2);
	 _webView->setPosition(Vec2(winSize.width/2, winSize.height/2 - 25));

	//winSize.width = Weight; //* 0.95;
	//winSize.height = iHeight;//* 0.95;
	 _webView->setContentSize(Size(winSize.width, winSize.height -50));
	 char cUrl[2000];
	 //
	if(iType == 1)
		sprintf(cUrl,"http://true.iyueyo.com/dwbygoogle.php/home/molpay?AccountID=%d&Version=1.2&Channel=mol3",CCUserDefault::getInstance()->getIntegerForKey("myid"));
	else if(iType == 2)
		sprintf(cUrl,"http://true.iyueyo.com/dwbygoogle.php/home/Truepay?AccountID=%d&Version=1.2&Channel=true3",CCUserDefault::getInstance()->getIntegerForKey("myid"));;

	_webView->loadURL(cUrl);
	_webView->setScalesPageToFit(true);

	_webView->setOnShouldStartLoading(CC_CALLBACK_2(WebViewTest::onWebViewShouldStartLoading, this));
	_webView->setOnDidFinishLoading(CC_CALLBACK_2(WebViewTest::onWebViewDidFinishLoading, this));
	_webView->setOnDidFailLoading(CC_CALLBACK_2(WebViewTest::onWebViewDidFailLoading, this));
	/*webView->setOnShouldStartLoading([](cocos2d::experimental::ui::WebView *sender, const std::string &url){

		cocos2d::log("onWebViewShouldStartLoading url.size() = %d",url.size());
		cocos2d::log("onWebViewShouldStartLoading, url is %s", url.c_str());
		//asdfsdfasdfsdfIAP?IAPResult=success

		char *ptr=strrchr(url.c_str(),'?');
		if(ptr !=NULL && !strcmp(ptr+1,"IAPResult=success") )
		{


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
				ChongZhiSendMsg.account =  htonl(id);
				ptempHallSocket->SendMsgToSocket(&ChongZhiSendMsg, CHONGZHISEND, sizeof(ChongZhiSend));

			}

			
			NotificationCenter::sharedNotificationCenter()->postNotification("openUpdateTimer", NULL);

		}

		return true;

	});
	webView->setOnDidFinishLoading([](cocos2d::experimental::ui::WebView *sender, const std::string &url){
		cocos2d::log("setOnDidFinishLoading url.size() = %d",url.size());
		cocos2d::log("setOnDidFinishLoading, url is %s", url.c_str());
	});
	webView->setOnDidFailLoading([](cocos2d::experimental::ui::WebView *sender, const std::string &url){
		cocos2d::log("setOnDidFailLoading url.size() = %d",url.size());
		cocos2d::log("setOnDidFailLoading, url is %s", url.c_str());
	});*/
	this->addChild(_webView);
    
#endif
   /* 

    _webView = cocos2d::experimental::ui::WebView::create();
    _webView->setPosition(winSize/2);
    winSize.width = Weight * 0.95;
    winSize.height = iHeight* 0.95;
    _webView->setContentSize(winSize );
    char cUrl[2000];
    
    if(iType == 1)
            sprintf(cUrl,"http://true.iyueyo.com/dwby.php/home/molpay?AccountID=%d&Version=1.2&Channel=mol2",CCUserDefault::getInstance()->getIntegerForKey("myid"));
    else if(iType == 2)
          sprintf(cUrl,"http://true.iyueyo.com/dwby.php/home/Truepay?AccountID=%d&Version=1.2&Channel=true2",CCUserDefault::getInstance()->getIntegerForKey("myid"));;
    
    
    _webView->loadURL(cUrl);
    
    
    _webView->setScalesPageToFit(true);
    
    
    _webView->setOnShouldStartLoading(CC_CALLBACK_2(WebViewTest::onWebViewShouldStartLoading, this));
    _webView->setOnDidFinishLoading(CC_CALLBACK_2(WebViewTest::onWebViewDidFinishLoading, this));
    _webView->setOnDidFailLoading(CC_CALLBACK_2(WebViewTest::onWebViewDidFailLoading, this));
    
    this->addChild(_webView);
    */
    return true;
    
}

bool WebViewTest::onWebViewShouldStartLoading(experimental::ui::WebView *sender, const std::string &url)
{
	cocos2d::log("onWebViewShouldStartLoading");
	cocos2d::log("onWebViewShouldStartLoading, url is %s", url.c_str());

	bool isPayFinish = false;
	bool isPaySuccess = false;
	int successPos = url.find("IAPResult=success", 0);
	int failPos = url.find("IAPResult=false", 0);

	cocos2d::log("successPos = %d \n failPos = %d", successPos, failPos);
	if (successPos > 0)
	{
		cocos2d::log("pay success");
		isPayFinish = true;
		isPaySuccess = true;
	}
	else if (failPos > 0)
	{
		cocos2d::log("pay fail");
		isPayFinish = true;
	}

	cocos2d::log("isPayFinish = %d", isPayFinish);
	cocos2d::log("isPaySuccess = %d", isPaySuccess);
	if (isPayFinish)
	{
		NotificationCenter::getInstance()->postNotification("webPayFinish", (Ref*)&isPaySuccess);
	}
       //asdfsdfasdfsdfIAP?IAPResult=success
  /*   
    const char *ptr=strrchr(url.c_str(),'?');
    if(ptr !=NULL && !strcmp(ptr+1,"IAPResult=success") )
    {
        
        
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
            ChongZhiSendMsg.account =  htonl(id);
            ptempHallSocket->SendMsgToSocket(&ChongZhiSendMsg, CHONGZHISEND, sizeof(ChongZhiSend));
            
        }
        
        schedule(schedule_selector(WebViewTest::updataDisplay), 0.01);
        
        
    }*/
    
    return true;

}











void WebViewTest::updataDisplay(float dt)
{
    
    
    
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
            if(Shop::comeKind == 1)
            {
                GameHallLayer::RefreshCoin(zengjiagold);
                GameHallLayer::RefreshDiamond(zengjiazuanshi);
                
                this->removeChild( _webView);
                char textTmp[100];
                sprintf(textTmp,GAME_DATA_STRING("goumai_chenggong"),zengjiagold,zengjiazuanshi);
                
                auto  gongxi = Gongxi::create(4,textTmp);
                gongxi->setPosition(Point::ZERO);
                this->addChild(gongxi);

                
            }
            if(Shop::comeKind == 2 )
            {
               
                CannonLayer::GameCoinRefresh(zengjiagold);
                CannonLayer::GameCoinZuanshi(zengjiazuanshi);
                this->removeChild( _webView);
                char textTmp[100];
                sprintf(textTmp,GAME_DATA_STRING("goumai_chenggong"),zengjiagold,zengjiazuanshi);
                
                auto  gongxi = Gongxi::create(4,textTmp);
                gongxi->setPosition(Point::ZERO);
                this->addChild(gongxi);

            }
            
            if(Shop::comeKind == 3  )
            {
                CannonUpgrade::RefreshCoin(zengjiagold);
                CannonUpgrade::RefreshDiamond(zengjiazuanshi);
                this->removeChild( _webView);
                char textTmp[100];
                sprintf(textTmp,GAME_DATA_STRING("goumai_chenggong"),zengjiagold,zengjiazuanshi);
                
                auto  gongxi = Gongxi::create(4,textTmp);
                gongxi->setPosition(Point::ZERO);
                this->addChild(gongxi);
      
            }
            if(Shop::comeKind == 8  )
            {
                ChallengeBOSS::RefreshCoin(zengjiagold);
                ChallengeBOSS::RefreshDiamond(zengjiazuanshi);
                
                
                
                this->removeChild( _webView);
                char textTmp[100];
                sprintf(textTmp,GAME_DATA_STRING("goumai_chenggong"),zengjiagold,zengjiazuanshi);
                
                auto  gongxi = Gongxi::create(4,textTmp);
                gongxi->setPosition(Point::ZERO);
                this->addChild(gongxi);
                
                
                
            }
            ptempHallSocket->CloseSocket();
            this->unscheduleAllSelectors();
            
            
        }
    }
    
            
}

void WebViewTest::openUpdateTimer( cocos2d::Ref* pRef )
{
	schedule(schedule_selector(WebViewTest::updataDisplay), 0.01);
}

WebViewTest::WebViewTest()
{
	NotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(WebViewTest::openUpdateTimer), "openUpdateTimer", NULL);
}

WebViewTest::~WebViewTest()
{
	NotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}




            
            
            
            
void WebViewTest::onWebViewDidFinishLoading(experimental::ui::WebView *sender, const std::string &url)
{
	cocos2d::log("onWebViewDidFinishLoading");
    cocos2d::log("onWebViewDidFinishLoading, url is %s", url.c_str());

	//std::string targetUrl = "https://wallet.gg.in.th/FillUp/TrueMoney/TrueMoneyFrm.aspx?";
	//std::string targetUrl = "http://payment.gg.in.th/payment_gateway/paymentservice/completepayment.aspx?";
	//std::string tmpUrl = url;

	//std::string::iterator tmpIt = tmpUrl.begin();
	//std::string::iterator targetIt = targetUrl.begin();

	//bool isPayFinish = true;
	//for (; tmpIt != tmpUrl.end() && targetIt != targetUrl.end(); tmpIt++, targetIt++)
	//{
	//	if (*tmpIt != *targetIt)
	//	{
	//		isPayFinish = false;
	//		break;
	//	}
	//}

	//cocos2d::log("isPayFinish = %d",isPayFinish);
	//if (isPayFinish)
	//{

	///*	//取得Room Sokcet
	//	TcpClientSocket *ptempHallSocket = LogoLayer::GetSocket();
	//	ptempHallSocket->CloseSocket();

	//	ptempHallSocket->ConnectServer((char*)LogoLayer::gHIpStr.data(), LogoLayer::gHPortStr);

	//	if(ptempHallSocket->IsConnect() == false)
	//	{

	//	}
	//	else
	//	{
	//		ChongZhiSend ChongZhiSendMsg;
	//		int id =CCUserDefault::getInstance()->getIntegerForKey("myid");
	//		ChongZhiSendMsg.account =  htonl(id);
	//		ptempHallSocket->SendMsgToSocket(&ChongZhiSendMsg, CHONGZHISEND, sizeof(ChongZhiSend));

	//	}

	//	schedule(schedule_selector(WebViewTest::updataDisplay), 0.01);*/
	//	NotificationCenter::sharedNotificationCenter()->postNotification("webPayFinish", NULL);
	//	this->unscheduleAllSelectors();
	//	this->removeFromParent();
	//	
	//}
	
}

void WebViewTest::onWebViewDidFailLoading(experimental::ui::WebView *sender, const std::string &url)
{
	cocos2d::log("onWebViewDidFailLoading");
    cocos2d::log("onWebViewDidFailLoading, url is %s", url.c_str());

	
}

