package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

public class JniPlayBallHelper {
	public static String TAG = JniPlayBallHelper.class.getSimpleName();

	public static Handler mHandler;

	public static Handler getmHandler() {
		return mHandler;
	}

	public static void setmHandler(Handler handler) {
		if (handler != null) {
			mHandler = handler;
		}
	}

	// Google
	public static final int MESSAGE_CREATE_GOOGLE_HELPER = 0x101;
	public static final int MESSAGE_PURCHASE_GOOGLE_SKU = 0x102;
	public static final int MESSAGE_SHOW_GOOGLE_ADS = 0x103;

	// BluePay
	public static final int MESSAGE_PURCHASE_BLUEPAY = 0x201;

	//¹ã¸æ
	public static final int MESSAGE_SHOW_CHARTBOOST_ADS = 0x301;
	
	
	// �����ļ�·��
	public static native void setSaveFolderPath(String storageFolderPath);

	// ֧���ص�
	public static native void PayCallBack(String iPayprice, int iResultStatus);

	public static native void BuyPackageCallBack(int aAddGold);

	public static native void BuyGoodsCallBack(int aAddGold);

	public static native void BuyVipCallBack();

	public static native void LoginSuccess(String openid, String openkey,
			String pay_token, String pf, String pfKey, String plat);


	// 谷歌充值成功
	public static native void GooglePaySuccess(String openid, String openkey,
			String pay_token, String pf, String pfKey, String plat);

	public static native void LoginFail();

	public static native void buySuccess();

	public static native void buyFail();

	public static native void buySuccessByMSM();
	
	//add by zxf
	//type ½±Æ·ÀàÐÍ  amount ½±Æ·ÊýÁ¿
	public static native void onGoogleAdsRewarded(String string, int amount);

	public static void buySuccessJava(final int realIndex) {
		Cocos2dxGLSurfaceView.getInstance().queueEvent(new Runnable() {
			@Override
			public void run() {
				if (realIndex == 1)
					BuyGoodsCallBack(0);
				else
					BuyVipCallBack();
			}
		});
	}

	public static void QQLogin() {
		System.out.println("mJniHandler Callback QQLogin");
		System.out.println("QQLogin");
		if (mHandler != null) {
			Message msg = new Message();
			msg.what = 1;

			mHandler.sendMessage(msg);
		}
	}

	public static void WxLogin() {
		if (mHandler != null) {
			System.out.println("WxLogin");
			Message msg = new Message();
			msg.what = 2;

			mHandler.sendMessage(msg);
		}
	}

	// googleplay
	public static void DoPay(int index) {
		if (mHandler != null) {
			Log.d(TAG, "DoPay index = " + index);
			Message msg = new Message();
			msg.what = MESSAGE_PURCHASE_GOOGLE_SKU;
			msg.arg1 = index;
			mHandler.sendMessage(msg);
		}
	}

	public static void DoPayBySMS(int price) {
		if (mHandler != null) {
			Log.d(TAG, "DoPayBySMS, price = " + price);
			Message msg = new Message();
			msg.what = MESSAGE_PURCHASE_BLUEPAY;
			msg.arg1 = price;
			mHandler.sendMessage(msg);
		}
	}

	public static void CreateGoogleHelper() {
		if (mHandler != null) {
			Log.d(TAG, "CreateGoogleHelper");
			mHandler.sendEmptyMessage(MESSAGE_CREATE_GOOGLE_HELPER);
		}
	}

	public static void ShowGoogleAds() {
		if (mHandler != null) {
			Log.d(TAG, "ShowGoogleAds");
			mHandler.sendEmptyMessage(MESSAGE_SHOW_GOOGLE_ADS);
		}
	}
	
	public static void ShowChartboostAds() {
		if (mHandler != null) {
			Log.d(TAG, "ShowChartboostAds");
			mHandler.sendEmptyMessage(MESSAGE_SHOW_CHARTBOOST_ADS);
		}
	}
}
