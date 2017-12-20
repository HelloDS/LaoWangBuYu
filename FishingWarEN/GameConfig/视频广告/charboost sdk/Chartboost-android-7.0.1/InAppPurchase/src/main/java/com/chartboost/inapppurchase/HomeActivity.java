package com.chartboost.inapppurchase;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.Window;

import com.amazon.sample.iap.consumable.MainActivity;
import com.chartboost.sdk.Chartboost;
import com.chartboost.sdk.Libraries.CBLogging.Level;

public class HomeActivity extends Activity {

    @Override
    public void onCreate(Bundle savedInstanceState) { 
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        Chartboost.startWithAppId(this, getResources().getString(R.string.appId), getResources().getString(R.string.appSignature));
        setContentView(R.layout.home);
        Chartboost.setLoggingLevel(Level.ALL);
    }
    public void gotoGoogleActivityIAP(View view) {
        this.startActivity(new Intent(this, GoogleIAPTracking.class));
    }
    
    public void gotoAmazonActivityIAP(View view) {
        this.startActivity(new Intent(this, MainActivity.class));
    }
}