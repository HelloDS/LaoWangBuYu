#include "JNativeToCPlusPlusUtil.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameHallLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>   
#include "platform/android/jni/JniHelper.h"  

#include "Shop.h"
#include "ShopJJ.h"
#endif

#define CLASS_NAME "org.cocos2dx.cpp.JniPlayBallHelper"

extern "C"  
{  
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)


    //Java _ 包名(cn_ufuns_game) _ 类名(JniPlayBallHelper) _ 函数名(setStorageFolderPath)
    void Java_org_cocos2dx_cpp_JniPlayBallHelper_LoginSuccess(JNIEnv *env, jobject thiz,jstring jopenid,jstring jopenkey,jstring jpay_token,jstring jpf,jstring jpfKey,jstring jplat)
    {

    }


	// _orderId _packageName _productId _purchaseTime _purchaseState _purchaseToken
	void Java_org_cocos2dx_cpp_JniPlayBallHelper_GooglePaySuccess(JNIEnv *env, jobject thiz,jstring _orderId,jstring _packageName,jstring _productId,jstring _purchaseTime,jstring _purchaseState,jstring _purchaseToken)
	{
		cocos2d::log("ssssqqqq11111=======");
		const char* sorderId;
		sorderId = env->GetStringUTFChars(_orderId, false);
		if (sorderId != NULL) {
			cocos2d::log("jopenid=======%s", sorderId);
		}
		env->ReleaseStringUTFChars(_orderId, sorderId);	


		struct GoogleData
		{
			const char * orderId;
			const char * packageName;
			const char * productId;
			const char * purchaseTime;
			const char * purchaseState;
			const char * purchaseToken;
		};

		GoogleData * pTempGoogleData = new GoogleData;
		pTempGoogleData->orderId = sorderId;

		cocos2d::log("ssssqqqq222222=======");
		// 从java充值成功返回到这里执行一个事件派发
		EventCustom * event = new EventCustom(Shop::GOOGLE_PAY);
		event->setUserData((void*)pTempGoogleData);
		auto dispatcher = Director::getInstance()->getEventDispatcher();
		dispatcher->dispatchEvent(event);
		delete event;
		cocos2d::log("ssssqqqq333=======");

	}


	void Java_org_cocos2dx_cpp_JniPlayBallHelper_WXLoginSuccess(JNIEnv *env, jobject thiz)
	{

	}

	void Java_org_cocos2dx_cpp_JniPlayBallHelper_LoginFail(JNIEnv *env, jobject thiz)
	{

	}


	void Java_org_cocos2dx_cpp_JniPlayBallHelper_buySuccess(JNIEnv * env,  jobject thiz/*, jstring jOrderStr*/)
	{
		cocos2d::log("Java_org_cocos2dx_cpp_JniPlayBallHelper_buySuccess");
		 Shop::yanZhengFlag = true;
	}

	void Java_org_cocos2dx_cpp_JniPlayBallHelper_buyFail(JNIEnv * env, jclass)
	{
		cocos2d::log("Java_org_cocos2dx_cpp_jjdwby_JniPlayBallHelper_buyFail");
		Shop::failFlag = true;
	}

	//add by zxf 
	void Java_org_cocos2dx_cpp_JniPlayBallHelper_onGoogleAdsRewarded(JNIEnv * env,  jobject thiz, jstring type, jint amount)
	{
		const char* str;
		str = env->GetStringUTFChars(type, false);
		if (str != NULL) {
			cocos2d::log("Java_org_cocos2dx_cpp_JniPlayBallHelper_onGoogleAdsRewarded type = %s, amount = %d", str, amount);
		}
		env->ReleaseStringUTFChars(type, str);	


		GameHallLayer::RefreshCoin(amount);



	}
#endif
}
