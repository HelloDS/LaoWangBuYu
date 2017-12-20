
#ifndef __cocos2d_tests__UIWebViewTest__
#define __cocos2d_tests__UIWebViewTest__

#include"cocos2d.h"
#include "cocos-ext.h"
using namespace std;

#include "ui/CocosGUI.h"
#include "cocos/ui/UIWebView.h"
USING_NS_CC; 
USING_NS_CC_EXT;

class WebViewTest : public cocos2d::Layer
{
public: 
	WebViewTest();
	~WebViewTest();
    static WebViewTest * create(int iType,int iHeight,int Weight);
    virtual bool init(int iType,int iHeight,int Weight);
    
    bool onWebViewShouldStartLoading(cocos2d::experimental::ui::WebView *sender, const std::string &url);
    void onWebViewDidFinishLoading(cocos2d::experimental::ui::WebView *sender, const std::string &url);
    void onWebViewDidFailLoading(cocos2d::experimental::ui::WebView *sender, const std::string &url);
    
    void openUpdateTimer(cocos2d::Ref* pRef);
    void updataDisplay(float dt);

	//add by zxf
	void showTitle();
	void quit();

private:
    cocos2d::experimental::ui::WebView *_webView;
    
};

#endif /* defined(__cocos2d_tests__UIWebViewTest__) */
