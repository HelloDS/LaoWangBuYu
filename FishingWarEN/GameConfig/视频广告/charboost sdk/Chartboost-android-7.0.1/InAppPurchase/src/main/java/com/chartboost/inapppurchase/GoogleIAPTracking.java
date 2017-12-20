package com.chartboost.inapppurchase;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.chartboost.sdk.CBLocation;
import com.chartboost.sdk.Chartboost;
import com.chartboost.sdk.ChartboostDelegate;
import com.chartboost.sdk.Tracking.CBAnalytics;
import com.chartboost.sdk.sample.cbtest.inappbilling.util.IabHelper;
import com.chartboost.sdk.sample.cbtest.inappbilling.util.IabResult;
import com.chartboost.sdk.sample.cbtest.inappbilling.util.Inventory;
import com.chartboost.sdk.sample.cbtest.inappbilling.util.Purchase;
import com.chartboost.sdk.sample.cbtest.inappbilling.util.SkuDetails;

public class GoogleIAPTracking extends Activity{

    private static final String TAG = "com.chartboost.sdk.sample.cbtest.inappbilling";
    
    private static final int INAPP_REQUEST_CODE = 10001;
    
    //private static final String RELEASE_ITEM_SKU = "com.example.buttonclick";
    
    private static final String TEST_ITEM_SKU = "android.test.purchased";
    
    private Button clickButton;
    
    private Button buyButton;
    
    private String ITEM_SKU;    
    
    IabHelper mHelper;
    
    Inventory inventory;
    
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.pit);
        Chartboost.onCreate(this);      
        Chartboost.setDelegate(delegate);
        buyButton = (Button)findViewById(R.id.buyButton);
        clickButton = (Button)findViewById(R.id.clickButton);   
        clickButton.setEnabled(false);
        ITEM_SKU = TEST_ITEM_SKU;
        String base64EncodedPublicKey = getResources().getString(R.string.base64EncodedPublicKey);

        /*Setting up Inapp billing purchase*/
        mHelper = new IabHelper(this, base64EncodedPublicKey);
        mHelper.enableDebugLogging(true);
        mHelper.startSetup(new 
        IabHelper.OnIabSetupFinishedListener() {
        public void onIabSetupFinished(IabResult result) 
        {
        if (!result.isSuccess()) {
          Log.d(TAG, "In-app Billing setup failed: " + 
        result);
        } else {
            Log.d(TAG, "############# In-app Billing is set up ###############");
            Log.d(TAG, "In-app Billing is set up OK");          
        }
        }
        });
    }
    
    public void buttonClicked (View view)
    {
//      clickButton.setEnabled(false);
//      buyButton.setEnabled(true);
    }
    
    public void buyClick(View view) {
         mHelper.launchPurchaseFlow(this, ITEM_SKU, INAPP_REQUEST_CODE,  mPurchaseFinishedListener, "mypurchasetoken");
    }
    
    IabHelper.OnIabPurchaseFinishedListener mPurchaseFinishedListener = new IabHelper.OnIabPurchaseFinishedListener() {

    @Override
    public void onIabPurchaseFinished(IabResult result, Purchase purchase) {
        Log.d(TAG,"###### onIabPurchaseFinished"+purchase +"#####"+ ITEM_SKU);
        if (result.isFailure()) {
             Runnable r = new Runnable() {              
            @Override
            public void run() {
                mHelper.myconsume(GoogleIAPTracking.this.getPackageName(), "inapp:"+getPackageName()+":android.test.purchased");
            }
        };
        r.run(); 
        Log.d(TAG,"###### onIabPurchaseFinished Error ");
         return;
         }      
         else if (purchase.getSku().equals(ITEM_SKU)) {
                mHelper.queryInventoryAsync(mReceivedInventoryListener);
                buyButton.setEnabled(false);
        }
        
        }
    };
        
    IabHelper.QueryInventoryFinishedListener mReceivedInventoryListener 
           = new IabHelper.QueryInventoryFinishedListener() {
        
            @Override
            public void onQueryInventoryFinished(IabResult result, Inventory inv) {
                Log.d(TAG,"###### onQueryInventoryFinished : " + inv);
                  if (result.isFailure()) {
                      // Handle failure
                      } 
                  else {
                      Log.d(TAG," ####### Its in the inventory consuming the item !!!!");
                      try{
                          // MIGHT THROW AN EXCEPTION IF Chartboost.onStart() is not called. 
                          Log.d(TAG,"########## Send it to Chartboost PIT ###########");
                             SkuDetails item = inv.getSkuDetails(ITEM_SKU);
                             Purchase purchase = inv.getPurchase(ITEM_SKU);
                             if(item !=null && purchase != null) {
                                 String data =purchase.getOriginalJson();                            
                                 String signature = TextUtils.isEmpty(purchase.getSignature()) ?"test":purchase.getSignature();
                                 signature = TextUtils.isEmpty(signature) ?"test":signature;
                                 if(item != null){
                                     CBAnalytics.trackInAppGooglePlayPurchaseEvent(item.getTitle(),
                                                                                               item.getDescription(),
                                                                                               item.getPrice(),
                                                                                               item.getCurrencyCode(),
                                                                                               purchase.getSku(),
                                                                                               data,
                                                                                               signature);
                                 }
                             }
                        } catch(Exception e){
                            Log.d(TAG, e.getMessage());
                        }
                      mHelper.consumeAsync(inv.getPurchase(ITEM_SKU), mConsumeFinishedListener);
                    }
            }
    };
        
    IabHelper.OnConsumeFinishedListener mConsumeFinishedListener =
        new IabHelper.OnConsumeFinishedListener() {
         public void onConsumeFinished(Purchase purchase, 
               IabResult result) {
             Log.d(TAG,"###### onConsumeFinished");
            if (result.isSuccess()) {                
                Log.d(TAG,"###### onConsumeFinished sucess");
            } 
            buyButton.setEnabled(true);
        }
    };

        
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        Log.d(TAG, "onActivityResult(" + requestCode + "," + resultCode + "," + data);
        // Pass on the activity result to the helper for handling
        if (!mHelper.handleActivityResult(requestCode, resultCode, data)) {
            // not handled, so handle it ourselves (here's where you'd
            // perform any handling of activity results not related to in-app
            // billing...
            super.onActivityResult(requestCode, resultCode, data);
        }
        else {
            Log.d(TAG, "onActivityResult handled by IABUtil.");
        }
        
    };
    
    /* The following methods reflect the buttons in our UI. */

    public void onLoadButtonClick(View view) {
        String toastStr = "Loading Interstitial";
        Toast.makeText(this, toastStr, Toast.LENGTH_SHORT).show();
        Chartboost.showInterstitial(CBLocation.LOCATION_STARTUP);
    }

    public void onMoreButtonClick(View view) {
        String toastStr = "Loading More Apps";
        Toast.makeText(this, toastStr, Toast.LENGTH_SHORT).show();
        Chartboost.showMoreApps(CBLocation.LOCATION_GAME_SCREEN);
    }
    
    public void trackMiscRevenueGeneratingEventOfType(View view) {
        String toastStr = "Sending trackMiscRevenueGeneratingEventOfType to SDK ..";
        Toast.makeText(this, toastStr, Toast.LENGTH_SHORT).show();
        //pit.trackMiscRevenueGeneratingEvent(CBMiscRevenueGeneratingEventType.CBMiscRevenueGeneratingEventType1, 100, "USD", "HayDay");
    }
    
    public void trackCustomEventOfType(View view) {
        String toastStr = "Sending trackCustomEventOfType to SDK ..";
        Toast.makeText(this, toastStr, Toast.LENGTH_SHORT).show();
        //pit.trackCustomEventofType(CBCustomEventType.CBCustomEventType1, 2);
    }
    
    public void trackInGameScore(View view) {
        String toastStr = "Sending trackInGameScore to SDK ..";
        Toast.makeText(this, toastStr, Toast.LENGTH_SHORT).show();
        //pit.trackInGameScore(10);
    }
    
    public void trackPlayerCurrencyBalance(View view) {
        String toastStr = "Sending trackPlayerCurrencyBalance to SDK ..";
        Toast.makeText(this, toastStr, Toast.LENGTH_SHORT).show();
        //pit.trackPlayerCurrencyBalance(5, "USD");
    }

    /*Activity callback methods*/
    @Override
    protected void onStart() {
        super.onStart();
        Chartboost.onStart(this);
    }
    
    @Override
    protected void onResume() {
        super.onResume();
        Log.d(TAG,"### onResume");
    }
    
    @Override
    protected void onPause() {
        super.onPause();
    }

    @Override
    protected void onStop() {
        super.onStop();
        Chartboost.onStop(this);
    }

    @Override
    public void onBackPressed() {
        if (Chartboost.onBackPressed())
            return;
        else
            super.onBackPressed();
    }
    
    @Override
    public void onDestroy() {
        super.onDestroy();
        Chartboost.onDestroy(this);
        if (mHelper != null) mHelper.dispose();
        mHelper = null;
    }
    
     /**
      * Chartboost Delegate callbacks
      */
     private ChartboostDelegate delegate = new ChartboostDelegate() {
    
     };
}
