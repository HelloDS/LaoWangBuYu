package com.chartboost.sdk.sample;

import android.annotation.TargetApi;
import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Build;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.View;
import android.widget.ImageButton;

import com.chartboost.sdk.Chartboost;
import com.chartboost.sdk.sample.ChartboostSample.ImpressionType;

public class SelectionActivity extends Activity {

    ImageButton settingsButton;
    SharedPreferences sharedPreferences = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_selection);
        Chartboost.startWithAppId(this, getResources().getString(R.string.appId), getResources().getString(R.string.appSignature));
        setupSdkWithCustomSettings();

        Chartboost.onCreate(this);
        hideSystemUI();

        createOnClickListener(R.id.interstitialButton, ImpressionType.INTERSTITIAL);
        createOnClickListener(R.id.rewardedButton, ImpressionType.REWARDED);
        createOnClickListener(R.id.inPlayButton, ImpressionType.IN_PLAY);
        settingsButton = (ImageButton) findViewById(R.id.settingsButton);
        settingsButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(SelectionActivity.this, SettingsActivity.class));
            }
        });
    }

    private void setupSdkWithCustomSettings() {

        sharedPreferences = PreferenceManager.getDefaultSharedPreferences(getBaseContext());

        Chartboost.setShouldPrefetchVideoContent(
                sharedPreferences.getBoolean(getString(R.string.key_enable_video_prefetch), true));
        Chartboost.setShouldRequestInterstitialsInFirstSession(
                sharedPreferences.getBoolean(getString(R.string.key_request_interstitial_in_first_session), true));
        Chartboost.setAutoCacheAds(
                sharedPreferences.getBoolean(getString(R.string.key_enable_autocache), true));

    }

    private void createOnClickListener(int buttonID, ImpressionType type) {
        findViewById(buttonID).setOnClickListener(new ImpressionClickListener(type));
    }

    private class ImpressionClickListener implements View.OnClickListener {

        private final ImpressionType type;

        public ImpressionClickListener(ImpressionType type) {
             this.type = type;
        }

        @Override
        public void onClick(View v) {
            Intent intent = new Intent(getBaseContext(), ChartboostSample.class);
            intent.putExtra(ChartboostSample.impressionTypeKey, this.type);
            startActivity(intent);
        }
    }

    @TargetApi(Build.VERSION_CODES.KITKAT)
    private void hideSystemUI() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) {
            this.getWindow().getDecorView().setSystemUiVisibility(
                    View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                            | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                            | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                            | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION // hide nav bar
                            | View.SYSTEM_UI_FLAG_FULLSCREEN // hide status bar
                            | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
        }
    }
}
