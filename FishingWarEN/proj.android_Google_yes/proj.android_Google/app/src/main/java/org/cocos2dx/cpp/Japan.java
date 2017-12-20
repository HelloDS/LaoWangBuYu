/**
 * Google Play SDK
 * Created by Aaron on 12/4/16.
 */

package org.cocos2dx.cpp;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.Intent;
import android.content.IntentSender;
import android.net.Uri;
import android.os.Bundle;

import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.util.Log;
import android.widget.Toast;

import com.google.android.gms.auth.api.Auth;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.auth.api.signin.GoogleSignInOptions;
import com.google.android.gms.auth.api.signin.GoogleSignInResult;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.Scopes;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.common.api.ResultCallback;
import com.google.android.gms.common.api.Scope;
import com.google.android.gms.common.api.Status;
import com.yueyou.googleutil.*;

import org.cocos2dx.lib.Cocos2dxHelper;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.util.HashMap;
import java.util.Hashtable;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;


public class Japan  implements
        GoogleApiClient.OnConnectionFailedListener, GoogleApiClient.ConnectionCallbacks

{
    private static Activity mActivity = null;

    // 打印的tag值
    static final String TAG = "tank1111111111";

    // 登录的cb
    static int loginCb = 0;


    //****************** google SDK *************//
    //
    static final String GOOGLE_PAY_KEY = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAnvenBpyNYVoeuFUscg4DTllkrtPZSNXLL9LKnU8HNWiXW3BLn8nDoP8IH/fHeE/CiDGlpRNbzNNmT8WDusCJLGCq0tZd3lCX9fzcUxFak7JOOJ2E7YoDwJgOgQbIPYkvdDj9SXrALbgFKsSKuBp39w1uxe0hsCnt/nF1El54Rz0y+Z1XQaneWgqD2LM6Pd886rf6G2jSGby6qXbQsqsdpB4y6Ri63mYwBo667qf59BBVYaCx6LsvwHhUIEslpEgqSYW8EKaLhBkcHOre8Jg8YUrZhWUL9lxF3HE8OoLaPCi3V7Gx7uuYJg3k6uBmVAKwGHQfIwnl24wOprb6fMIkPwIDAQAB";
    // The helper object
    IabHelper mHelper;



    private static String accountName = null;
    private GoogleApiClient  mGoogleApiClient;
    private  static String clientServerID = "156299380832-4gbdl4mvk5esvnf2rouaq73budoejmcq.apps.googleusercontent.com";
    private static final int RC_SIGN_IN = 9001;
    private  boolean  isgin = false;
    private boolean iap_is_ok = false;

    // SKUs for our products
    static final String vsgT1  = "com.facai.fishingboom.id1";
    static final String vsgT2 = "com.facai.fishingboom.id2";
    static final String vsgT3 = "com.facai.fishingboom.id3";
    static final String vsgT4 = "com.facai.fishingboom.id4";
    static final String vsgT5 = "com.facai.fishingboom.id5";
    static final String vsgT6 = "com.facai.fishingboom.id6";
    static final String vsgT7 = "com.facai.fishingboom.id7";
    static final String vsgT8 = "com.facai.fishingboom.idvip";

    static final String[] product_list = {vsgT1,vsgT2,vsgT3,vsgT4,vsgT5,vsgT6,vsgT7,vsgT8};


    // Request code to use when launching the resolution activity
    private static final int REQUEST_RESOLVE_ERROR = 1001;
    // Unique tag for the error dialog fragment
    private static final String DIALOG_ERROR = "dialog_error";
    // Bool to track whether the app is already resolving an error
    private boolean mResolvingError = false;


    public void onInit( Activity _activity)
    {
        mActivity = _activity;
        initGooglePlay();
        initGoogleHelper();


        TimerTask task = new TimerTask()
        {
            public void run()
            {
                //Pay("id1","1",1);
                Log.d(TAG,"111111111111111111111");
            }
        };
        Timer timer = new Timer();
        timer.schedule(task,5000);

    }



    public void Login(final int cb)
    {
        loginCb = cb;
        Intent signInIntent = Auth.GoogleSignInApi.getSignInIntent(mGoogleApiClient);
        if (signInIntent == null || mGoogleApiClient == null)
        {
            Log.d(TAG,"GooglePlay---Login==============ERROR");
            return;
        }
        mActivity.startActivityForResult(signInIntent, RC_SIGN_IN);
        Log.d(TAG,"GooglePlay---Login==============OVER");

    }


    public void Login(final boolean refresh,final int cb)
    {

    }


    public void logoutFacebook()
    {
        Log.d(TAG,"logout facebook");
        //LoginManager.getInstance().logOut();
        signOut();
    }


    /**
     * 检测谷歌SDK 登录状态函数
     */
    @Override
    public void onConnected(@Nullable Bundle bundle)
    {
        showToast("谷歌服务连接成功");

    }

    @Override
    public void onConnectionSuspended(int i)
    {
        Log.d(TAG, "google======暂停连接"+ i);
    }

    @Override
    public void onConnectionFailed(@NonNull ConnectionResult result)
    {
        Log.d(TAG, "google======发生了无法解析的错误:" + result);

        showToast("需要更新谷歌服务");
        if (result.hasResolution())
        {
            try
            {
                mResolvingError = true;
                result.startResolutionForResult(mActivity, REQUEST_RESOLVE_ERROR);
            }
            catch (IntentSender.SendIntentException e)
            {
                // There was an error with the resolution intent. Try again.
                mGoogleApiClient.connect();
            }
        }
        else
        {
            // Show dialog using GoogleApiAvailability.getErrorDialog()


            mResolvingError = true;
        }

    }


    /**
     * 谷歌注销用户 登出函数 成功的回调函数
     */
    private void signOut()
    {
        // 会崩溃  是木有连接到谷歌
        Auth.GoogleSignInApi.signOut(mGoogleApiClient).setResultCallback(
                new ResultCallback<Status>() {
                    @Override
                    public void onResult(Status status) {
                        Log.d(TAG, "signOut:onResult:" + status);
                        showToast("谷歌登出成功");
                    }
                });
    }
    /**
     * 初始化 谷歌sdk
     */
    private void initGooglePlay()
    {
        // 初始化
        Log.d(TAG, "initGooglePlay.....");

        GoogleSignInOptions.Builder gsoBuilder = new GoogleSignInOptions.Builder(GoogleSignInOptions.DEFAULT_SIGN_IN)
                .requestIdToken(clientServerID)
                .requestServerAuthCode(clientServerID)
                .requestId()
                .requestEmail();

        mGoogleApiClient = new GoogleApiClient.Builder(mActivity)
                .addConnectionCallbacks(this)
                .addOnConnectionFailedListener(this)
                .addApi(Auth.CREDENTIALS_API)
                .addApi(Auth.GOOGLE_SIGN_IN_API, gsoBuilder.build())
                .addScope(new Scope(Scopes.PROFILE))
                .addScope(new Scope(Scopes.EMAIL))
                .build();

        mGoogleApiClient.connect();

    }



    /**
     * 从谷歌账户的Activity切换后获得登录信息
     */
    public void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        Log.d(TAG, "google--requestCode========"+requestCode);
        if (requestCode == RC_SIGN_IN)
        {
            GoogleSignInResult result1 = Auth.GoogleSignInApi.getSignInResultFromIntent(data);
            if (result1.isSuccess())
            {
                GoogleSignInAccount acct = result1.getSignInAccount();
                GoogleSignInResult result = Auth.GoogleSignInApi.getSignInResultFromIntent(data);
                String personName = acct.getDisplayName();
                String personEmail = acct.getEmail();
                String personId = acct.getId();
                Uri personPhoto = acct.getPhotoUrl();

                String idToken = acct.getIdToken();

                // TODO(developer): send token to server and validate
                Log.d(TAG, "google==========登录成功=====" + idToken);
                showToast("登录成功");
             //   onLoginSuccess(loginCb,personId,personName,idToken);
            }
            else
            {
                Log.d(TAG, "google==========登录失败");
                showToast("登录失败");
            }
        }
        if (requestCode == REQUEST_RESOLVE_ERROR) {
            mResolvingError = false;

            if (!mGoogleApiClient.isConnecting() &&
                    !mGoogleApiClient.isConnected()) {
                mGoogleApiClient.connect();
            }
        }

        if (!mHelper.handleActivityResult(requestCode, resultCode, data))
        {

        }
        else
        {
            Log.d(TAG, "onActivityResult handled by IABUtil.");
        }
    }


    private int pay_callback;
    private double price;


    public void Pay(int pidIndex, String extra, final int cb)
    {
        String product_id = product_list[pidIndex];
        pay_callback = cb;
        // 在这里进行验证
        String payload = "";
        JniPlayBallHelper.GooglePaySuccess("1","1","1","1","1","1");
        Log.d(TAG, "product_id: " + product_id);

        // 测试返回
        if (cb>=0)
        {
            showToast("java充值测试订单开始返回----");
           // return;
        }


        if (iap_is_ok)
        {
            try
            {
                if (mHelper != null) mHelper.flagEndAsync();

                mHelper.launchPurchaseFlow(mActivity,product_id,10001, mPurchaseFinishedListener);
            }
            catch (IabHelper.IabAsyncInProgressException e)
            {
                alert(null,"Error launching purchase flow. Another async operation in progress.");
            }

        }
        else
        {
            alert("提示", "Google Play初始化失败,当前无法进行支付，请确定您所在地区支持Google Play支付或重启游戏再试！");
        }

    }


    void alert(String title, String message)
    {
        AlertDialog.Builder bld = new AlertDialog.Builder(mActivity);
        bld.setTitle(title == null || title.equals("") ? "Alert":title);
        bld.setMessage(message);
        bld.setNeutralButton("OK", null);
        Log.d(TAG, "Showing alert dialog: " + message);
        bld.create().show();
    }


    private void showToast(String text)
    {
        Toast.makeText(mActivity, text, Toast.LENGTH_SHORT).show();
    }

    public void onStop()
    {
        mGoogleApiClient.disconnect();
    };



    public void onRestart()
    {
        mGoogleApiClient.connect();
    }





    /**
     * 初始化谷歌 购买-消耗 的工具类
     */
    public void  initGoogleHelper()
    {
        String base64EncodedPublicKey = GOOGLE_PAY_KEY;
        mHelper = new IabHelper(mActivity, base64EncodedPublicKey);

        // enable debug logging (for a production application, you should set this to false).
        mHelper.enableDebugLogging(true);

        /*
         * 检查是否有权限和连接到Google Billing service是否成功;
         * 若成功调用queryInventoryAsync查看产品id是否可以使用;
         * 查询完成后会调用IabHelper.QueryInventoryFinishedListener 这个回调接口进行通知，在这个接口中可以获取商品的详细信息SkuDetails和Purchase信息。
        */
        mHelper.startSetup(new IabHelper.OnIabSetupFinishedListener()
        {
            public void onIabSetupFinished(IabResult result)
            {
                Log.d(TAG, "Setup finished.");

                if (!result.isSuccess())
                {
                    alert(null,"Problem setting up in-app billing: " + result);
                    return;
                }

                if (mHelper == null) return;

                iap_is_ok = true;

                // IAB is fully set up. Now, let's get an inventory of stuff we own.
                Log.d(TAG, "Setup successful. Querying inventory.");

                // 获取商品列表
                try
                {
                    mHelper.queryInventoryAsync(mGotInventoryListener);
                }
                catch (IabHelper.IabAsyncInProgressException e)
                {
                    alert(null,"Error querying inventory. Another async operation in progress.");
                }
            }
        });
    }


    /**
     * 查询方法的回调：
     */
    IabHelper.QueryInventoryFinishedListener mGotInventoryListener = new IabHelper.QueryInventoryFinishedListener()
    {
        public void onQueryInventoryFinished(IabResult result, Inventory inventory) {
            Log.d(TAG, "Query inventory finished.");

            // Have we been disposed of in the meantime? If so, quit.
            if (mHelper == null) return;

            // Is it a failure?
            if (result.isFailure())
            {
                alert(null,"Failed to query inventory: " + result);
                return;
            }

            Log.d(TAG, "Query inventory was successful.");

            showToast("正在查询用户商品信息");

            for(int i=0;i<product_list.length;i++)
            {
                String product_id = product_list[i];
                Boolean b = inventory.hasDetails(product_id);

                if (b)
                {
                    SkuDetails details = inventory.getSkuDetails(product_id);

                    try
                    {
                        mHelper.consumeAsync(inventory.getPurchase(product_id), mConsumeFinishedListener);

                    }
                    catch (IabHelper.IabAsyncInProgressException e)
                    {
                        // alert(null,"Error consuming. Another async operation in progress.");
                        return;
                    }

                }
                else
                {
                    Log.d(TAG,product_id+" hasDetails = "+b);
                }

            }
        }
    };


    /**
     * 消耗商品的回调：
     */
    IabHelper.OnConsumeFinishedListener mConsumeFinishedListener = new IabHelper.OnConsumeFinishedListener()
    {
        public void onConsumeFinished(Purchase purchase, IabResult result)
        {
            Log.d(TAG, "Consumption finished. Purchase: " + purchase + ", result: " + result);
            if (mHelper == null)
            {
                Log.d(TAG, "OnConsumeFinishedListener====mHelper===== null.");
                return;
            }


            if (result.isSuccess())
            {
                // 消费成功   以下是游戏逻辑
                Log.d(TAG, "Consumption successful. Provisioning.");

                JSONObject json = new JSONObject();
                try {
                    //json.put("autoRenewing", purchase.isAutoRenewing());
                    json.put("orderId", purchase.getOrderId());
                    json.put("packageName", purchase.getPackageName());
                    json.put("productId", purchase.getSku());
                    json.put("purchaseTime", purchase.getPurchaseTime());
                    json.put("purchaseState", purchase.getPurchaseState());
                    json.put("purchaseToken", purchase.getToken());
                    json.put("signature",purchase.getSignature());
                    json.put("type","2");

                    JniPlayBallHelper.GooglePaySuccess(purchase.getOrderId(),purchase.getPackageName()
                            ,purchase.getSku(),"purchaseTime",purchase.getToken(),purchase.getSignature());

                }catch (JSONException e) {
                    e.printStackTrace();
                }

                showToast("消耗商品成功的回调");
                // 支付成功的 java到lua的参数
              //  onPaySuccess(pay_callback,json);
            }
            else {
                alert(null,"Error while consuming: " + result);
            }

            Log.d(TAG, "End consumption flow.");
        }
    };






    /**
     * 支付完成的回调，如果是受管理的商品在此回调中直接可以将道具给用户
     */
    IabHelper.OnIabPurchaseFinishedListener mPurchaseFinishedListener = new IabHelper.OnIabPurchaseFinishedListener() {
        public void onIabPurchaseFinished(IabResult result, Purchase purchase) {
            Log.d(TAG, "Purchase finished: " + result + ", purchase: " + purchase);

            // if we were disposed of in the meantime, quit.
            if (mHelper == null) return;

            if (result.isFailure()) {
                alert(null,"Error purchasing" + String.valueOf(result));
                return;
            }

            if (!verifyDeveloperPayload(purchase)) {
                alert(null,"Error:Error purchasing. Authenticity verification failed.");
                return;
            }

            showToast("支付完成的回调");

            // 立即消费
            try {
                mHelper.consumeAsync(purchase, mConsumeFinishedListener);
            } catch (IabHelper.IabAsyncInProgressException e) {
                alert(null,"Error consuming. Another async operation in progress.");
                return;
            }

        }
    };


    /**
     * 验证购买的开发人员有效负载是否正确
     */
    boolean verifyDeveloperPayload(Purchase p)
    {
        String payload = p.getDeveloperPayload();
        return true;
    }


    /**
     * 2个积分SDK的回调
     * cb 1是CA积分  2是Tp积分
     * userid 用户唯一标识
     */
    public void ShaerToIntegral(int cb,String userid)
    {
        if(cb == 1)
        {
        }
        else if(cb == 2)
        {
        }
        else
        {
            showToast("lua端口传入错误参数");
        }
    };



    public void show_Text(final String str)
    {
        mActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                showToast(str);
            }
        });
    }


}





