#ifndef _JNATIVETOJAVAUTIL_H_
#define _JNATIVETOJAVAUTIL_H_

#include "cocos2d.h"
using namespace cocos2d;

class JNativeToJavaUtil
{
public:
	//计费
	static void QQLogin();
	static void WxLogin();
	static void DoPay(int indx);
	static void DoPayBySMS(int price);

	//create google helper
	static void CreateGoogleHelper();

	//显示Chartboost广告-激励视频
	static void ShowChartboostAds();
};

#endif // !_JNATIVETOJAVAUTIL_H_