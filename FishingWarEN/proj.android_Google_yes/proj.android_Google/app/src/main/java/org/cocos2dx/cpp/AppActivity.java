/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.cpp;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

import android.support.multidex.MultiDex;
import android.util.Log;
import android.widget.Toast;

import com.chartboost.sdk.Chartboost;

import org.cocos2dx.cpp.Japan;
import org.json.JSONObject;
import com.chartboost.sdk.Chartboost;
import com.chartboost.sdk.CBLocation;
import com.chartboost.sdk.ChartboostDelegate;

public class AppActivity extends Cocos2dxActivity
{
	public static String TAG = AppActivity.class.getSimpleName();
	public static Japan mJapan = new Japan();



	public static String ChartboostiD = "5a2a84e555fbf70b8d779035";

	public static String ChartboostQM = "4674ba9989e5b13efd6cf25e74087d1ff79b2909";

	public static String MyAppPackage = "com.facai.fishingboom";


	
	public Cocos2dxGLSurfaceView onCreateView() {
		Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
		glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
		return glSurfaceView;
	}

	private boolean isSelfRequestAds = false;

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		createJniHandler();
		mJapan.onInit( this );

		// 初始化
		Chartboost.startWithAppId(this, ChartboostiD, ChartboostQM);
		Chartboost.onCreate(this);
		// 缓存视频
		Chartboost.cacheInterstitial(CBLocation.LOCATION_DEFAULT);

	}


	@Override
	protected void onStart() {
		// TODO Auto-generated method stub
		super.onStart();

	}

	@Override
	protected void onRestart() {
		// TODO Auto-generated method stub
		super.onRestart();
		mJapan.onRestart();


	}

	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();

	}

	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
	}

	@Override
	protected void onStop() {
		// TODO Auto-generated method stub
		super.onStop();
		mJapan.onStop();
	}

	@Override
	public void onBackPressed() {
			super.onBackPressed();
	}



	private void showChartboostAds() {

	}

	// google sdk start

	/**
	 * Check the device to make sure it has the Google Play Services APK.If it
	 * doesn't, display a dialog that allows users to download the APK from the
	 * Google Play Store or enable it in the device's system settings
	 */
	private static final int PLAY_SERVICES_RESOLUTION_REQUEST = 9000;
	private boolean isSupportGoogle = false;

	private boolean isSupportGoogle() {
		return true;
	}

	private String[] skus = { "com.djby0.99", "com.djbu1.99", "com.djby4.99", "com.djby9.99",
			"com.djby19.99", "com.djby39.99", "vip.5.99" };
	// The helper object

	// (arbitrary) request code for the purchase flow
	static final int RC_REQUEST = 9999;
	private static String payload = "";



	public void createJniHandler()
	{
		Handler mJniHandler = new Handler(new Handler.Callback() {

			@Override
			public boolean handleMessage(Message msg)
			{
				if (msg.what == 1)
				{

				} else if (msg.what == 2)
				{

				} else if (msg.what == 3)
				{

				}
				 else if (msg.what == JniPlayBallHelper.MESSAGE_PURCHASE_GOOGLE_SKU)
				{
					int idx = msg.arg1;
				//	mJapan.Pay(idx,"11",1);
					Chartboost.cacheRewardedVideo(CBLocation.LOCATION_GAMEOVER);
					Chartboost.showRewardedVideo(CBLocation.LOCATION_GAMEOVER);
				}
				else if (msg.what == JniPlayBallHelper.MESSAGE_SHOW_GOOGLE_ADS)
				{
				}
				else if (msg.what == JniPlayBallHelper.MESSAGE_PURCHASE_BLUEPAY)
				{
				}
				else if (msg.what == JniPlayBallHelper.MESSAGE_SHOW_CHARTBOOST_ADS)
				{
					showChartboostAds();
				}
				return false;
			}
		});
		JniPlayBallHelper.setmHandler(mJniHandler);
	}





	public void PayLoginSuccessJson(JSONObject json)
	{

	}


	@Override
	protected  void onActivityResult(int requestCode, int resultCode, Intent data)
	{
		super.onActivityResult(requestCode, resultCode, data);
		mJapan.onActivityResult(requestCode, resultCode, data);
	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
	}

	@Override
	protected void attachBaseContext(Context base) {
		super.attachBaseContext(base); MultiDex.install(this);
	}
}
