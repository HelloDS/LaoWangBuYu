
#include "JNativeToJavaUtil.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>   
#include "platform/android/jni/JniHelper.h"  
#endif

#define JAVA_CLASS_NAME "org.cocos2dx.cpp.JniPlayBallHelper"

void JNativeToJavaUtil::QQLogin()
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo jniInfo;
	if(JniHelper::getStaticMethodInfo(jniInfo, JAVA_CLASS_NAME, "QQLogin", "()V"))
	{
		//调用此函数
		jniInfo.env->CallStaticVoidMethod(jniInfo.classID, jniInfo.methodID);  
		jniInfo.env->DeleteLocalRef(jniInfo.classID);		
	}
#endif
}

void JNativeToJavaUtil::WxLogin()
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo jniInfo;
	if(JniHelper::getStaticMethodInfo(jniInfo, JAVA_CLASS_NAME, "WxLogin", "()V"))
	{
		//调用此函数
		jniInfo.env->CallStaticVoidMethod(jniInfo.classID, jniInfo.methodID);  
		jniInfo.env->DeleteLocalRef(jniInfo.classID);		
	}
#endif
}

void JNativeToJavaUtil::DoPay(int indx)
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo jniInfo;
	if(JniHelper::getStaticMethodInfo(jniInfo, JAVA_CLASS_NAME, "DoPay", "(I)V"))
	{
		//调用此函数
		jniInfo.env->CallStaticVoidMethod(jniInfo.classID, jniInfo.methodID, indx);  
		jniInfo.env->DeleteLocalRef(jniInfo.classID);		
	}
	#endif
}


void JNativeToJavaUtil::DoPayBySMS(int price)
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo jniInfo;
	if(JniHelper::getStaticMethodInfo(jniInfo, JAVA_CLASS_NAME, "DoPayBySMS", "(I)V"))
	{
		//调用此函数
		jniInfo.env->CallStaticVoidMethod(jniInfo.classID, jniInfo.methodID, price);  
		jniInfo.env->DeleteLocalRef(jniInfo.classID);		
	}
#endif
}

void JNativeToJavaUtil::CreateGoogleHelper()
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo jniInfo;	
	if(JniHelper::getStaticMethodInfo(jniInfo, JAVA_CLASS_NAME, "CreateGoogleHelper", "()V"))
	{
		//调用此函数
		jniInfo.env->CallStaticVoidMethod(jniInfo.classID, jniInfo.methodID);
		jniInfo.env->DeleteLocalRef(jniInfo.classID);
	}
#endif
}


void JNativeToJavaUtil::ShowChartboostAds()
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo jniInfo;
	if (JniHelper::getStaticMethodInfo(jniInfo, JAVA_CLASS_NAME, "ShowChartboostAds", "()V"))
	{
		//调用此函数
		jniInfo.env->CallStaticVoidMethod(jniInfo.classID, jniInfo.methodID);
		jniInfo.env->DeleteLocalRef(jniInfo.classID);
	}
#endif
}