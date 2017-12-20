package com.chartboost.sdk.sample;

import android.annotation.TargetApi;
import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.os.Build;
import android.os.Bundle;
import android.text.Layout;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.RelativeLayout;
import android.widget.Spinner;
import android.widget.TextView;

import com.chartboost.sdk.Chartboost;
import com.chartboost.sdk.ChartboostDelegate;
import com.chartboost.sdk.InPlay.CBInPlay;
import com.chartboost.sdk.Libraries.CBLogging;
import com.chartboost.sdk.Model.CBError;

public class ChartboostSample extends Activity {

    private final String TAG = "ChartboostSample";

    public static Activity activity;

    protected final static String impressionTypeKey = "IMPRESSION_TYPE_KEY";

    protected enum ImpressionType {
        INTERSTITIAL,
        REWARDED,
        IN_PLAY
    }

    private ImpressionType impressionType;

    private String location = "default";

    // Views
    private TextView title;

    // Button
    private Button backButton;
    private Button cacheButton;
    private Button showButton;
    private Button clearButton;
    private ImageButton settingsButton;

    // Log
    private TextView logTextView;

    // Counters
    private TextView displayCounter;
    private TextView failClickCounter;
    private TextView clickCounter;
    private TextView cacheCounter;
    private TextView dismissCounter;
    private TextView completeCounter;
    private TextView failLoadCounter;
    private TextView closeCounter;
    private TextView rewardCounter;

    // Location
    private Spinner locationSpinner;
    private TextView hasLocation;

    // In Play
    private ImageButton inPlayIcon;
    private ImageButton inPlayCloseButton;
    private RelativeLayout inPlayAd;
    private boolean inPlayShowing = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Chartboost.setActivityCallbacks(false);
        Chartboost.setDelegate(delegate);
        Chartboost.setLoggingLevel(CBLogging.Level.ALL);
        Chartboost.onCreate(this);
        setContentView(R.layout.activity_chartboost_sample);

        hideSystemUI();
        activity = this;

        title = (TextView) findViewById(R.id.title);

        Bundle extras = getIntent().getExtras();
        if (extras != null) {
            impressionType = (ImpressionType) extras.get(impressionTypeKey);
        }
        switch (impressionType){
            case INTERSTITIAL:
                title.setText("Interstitial");
                break;
            case REWARDED:
                title.setText("Rewarded");
                break;
            case IN_PLAY:
                title.setText("InPlay");
                break;
        }

        // Buttons
        backButton = (Button) findViewById(R.id.backButton);
        cacheButton = (Button) findViewById(R.id.cacheButton);
        showButton = (Button) findViewById(R.id.showButton);
        clearButton = (Button) findViewById(R.id.clearButton);
        settingsButton = (ImageButton) findViewById(R.id.settingsButton);

        // Log
        logTextView = (TextView) findViewById(R.id.logText);
        logTextView.setText(logTextView.getText(), TextView.BufferType.EDITABLE);
        logTextView.setMovementMethod(new ScrollingMovementMethod());

        // Counters
        displayCounter = (TextView) findViewById(R.id.displayCounter);
        failClickCounter = (TextView) findViewById(R.id.failClickCounter);
        clickCounter = (TextView) findViewById(R.id.clickCounter);
        cacheCounter = (TextView) findViewById(R.id.cacheCounter);
        dismissCounter = (TextView) findViewById(R.id.dismissCounter);
        completeCounter = (TextView) findViewById(R.id.completeCounter);
        failLoadCounter = (TextView) findViewById(R.id.failLoadCounter);
        closeCounter = (TextView) findViewById(R.id.closeCounter);
        rewardCounter = (TextView) findViewById(R.id.rewardCounter);

        // In Play
        inPlayIcon = (ImageButton) findViewById(R.id.inPlayIcon);
        inPlayCloseButton = (ImageButton) findViewById(R.id.inPlayCloseButton);
        inPlayAd = (RelativeLayout) findViewById(R.id.inPlayAd);
        if(!inPlayShowing) {
            inPlayAd.setVisibility(View.GONE);
        }
        // Location
        hasLocation = (TextView) findViewById(R.id.hasText);
        locationSpinner = (Spinner) findViewById(R.id.locationSpinner);
        locationSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parentView, View selectedItemView, int position, long id) {
                hideSystemUI();
                location = parentView.getItemAtPosition(position).toString();
                hasLocation.setText(isAdReadyToDisplay(location) ? "Yes" : "No");
                addToUILog("Location changed to " + location);
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });

        addToUILog("Using Chartboost v" + Chartboost.getSDKVersion());

        backButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                finish();
                startActivity(new Intent(ChartboostSample.this, SelectionActivity.class));
            }
        });

        settingsButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(ChartboostSample.this, SettingsActivity.class));
            }
        });

        cacheButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                switch (impressionType){
                    case INTERSTITIAL:
                        Chartboost.cacheInterstitial(location);
                        break;
                    case REWARDED:
                        Chartboost.cacheRewardedVideo(location);
                        break;
                    case IN_PLAY:
                        CBInPlay.cacheInPlay(location);;
                        break;
                }
            }
        });

        showButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                switch (impressionType){
                    case INTERSTITIAL:
                        Chartboost.showInterstitial(location);
                        break;

                    case REWARDED:
                        Chartboost.showRewardedVideo(location);
                        break;

                    case IN_PLAY:
                        final CBInPlay inPlay = CBInPlay.getInPlay(location);
                        if (inPlay == null) {
                            addToUILog("In Play was not ready at " + location);
                            break;
                        }
                        Bitmap inPlayBitmap = null;
                        try {
                            inPlayBitmap = inPlay.getAppIcon();
                        } catch (Exception ex) {
                            String exceptionAsString = Log.getStackTraceString(ex);

                            addToUILog(exceptionAsString);
                        }
                        if (inPlayBitmap == null) {
                            addToUILog("Unable to get InPlay bitmap at " + location);
                            break;
                        }
                        inPlayIcon.setImageBitmap(inPlayBitmap);
                        inPlayAd.setVisibility(View.VISIBLE);
                        inPlay.show();
                        addToUILog("In Play shown at " + location);
                        inPlayShowing = true;

                        inPlayIcon.setOnClickListener(new View.OnClickListener() {
                            @Override
                            public void onClick(View v) {
                                if (inPlay != null) {
                                    inPlay.click();
                                    inPlayAd.setVisibility(View.GONE);
                                    addToUILog("In Play clicked at " + location);
                                    inPlayShowing = false;
                                }
                            }
                        });

                        inPlayCloseButton.setOnClickListener(new View.OnClickListener() {
                            @Override
                            public void onClick(View v) {
                                inPlayAd.setVisibility(View.GONE);
                                inPlayShowing = false;
                            }
                        });
                        break;
                }
            }
        });

        clearButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                clearUI();
            }
        });

    }

    private boolean isAdReadyToDisplay(String location){
        switch (impressionType) {
            case INTERSTITIAL:
                return Chartboost.hasInterstitial(location);
            case REWARDED:
                return Chartboost.hasRewardedVideo(location);
            case IN_PLAY:
                return CBInPlay.hasInPlay(location);
            default:
                return false;
        }
    }

    @TargetApi(Build.VERSION_CODES.KITKAT)
    protected void hideSystemUI() {
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

    private void clearUI() {
        displayCounter.setText("0");
        failClickCounter.setText("0");
        clickCounter.setText("0");
        cacheCounter.setText("0");
        dismissCounter.setText("0");
        completeCounter.setText("0");
        failLoadCounter.setText("0");
        closeCounter.setText("0");
        rewardCounter.setText("0");
        hasLocation.setText("No");
        logTextView.setText("");
    }

    private void setTextSafely(final TextView textView, final String text) {
        this.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                textView.setText(text);
            }
        });
    }

    public void scrollToBottom(final TextView textView, final boolean bottom) {

        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if(textView == null) {
                    return;
                }
                if (textView.getLayout() != null) {
                    Layout layout = textView.getLayout();

                    int scrollAmount = 0;
                    if(bottom) {
                        scrollAmount = layout.getLineTop(textView.getLineCount()) -
                                textView.getHeight();
                    }
                    // if there is no need to scroll, scrollAmount will be <=0
                    if (scrollAmount > 0) {
                        textView.scrollTo(0, scrollAmount);
                    }
                    else
                        textView.scrollTo(0, 0);
                }
            }
        });


    }

    private void setHasAdForLocation(String location) {
        setTextSafely(hasLocation, isAdReadyToDisplay(location) ? "Yes" : "No");
    }

    public void addToUILog(final String message) {
        StringBuilder stringBuilder = new StringBuilder(logTextView.getText())
                .append(message).append("\n");

        setTextSafely(logTextView, stringBuilder.toString());
        scrollToBottom(logTextView, true);
        Log.i(TAG, message);
    }



    private void incrementCounter(TextView counter) {
        addToCounter(counter, 1);
    }

    private void addToCounter(TextView counter, int amount) {
        setTextSafely(counter, String.valueOf(Integer.parseInt(counter.getText().toString()) + amount));
    }

    /**
     * Chartboost Activity Life Cycle Methods
     */

    @Override
    protected void onStart() {
        super.onStart();
        hideSystemUI();
        Chartboost.onStart(this);
    }

    @Override
    protected void onPause() {
        super.onPause();
        Chartboost.onPause(this);
    }

    @Override
    protected void onResume() {
        super.onResume();
        hideSystemUI();
        Chartboost.onResume(this);
    }

    @Override
    protected void onStop() {
        super.onStop();
        Chartboost.onStop(this);
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        Chartboost.onDestroy(this);
    }

    @Override
    public void onBackPressed()
    {

        if (!Chartboost.onBackPressed())
            super.onBackPressed();
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);
        hideSystemUI();
    }

    /**
     * Chartboost Delegates
     */
    
    public ChartboostDelegate delegate = new ChartboostDelegate() {

        @Override
        public boolean shouldRequestInterstitial(String location) {
            addToUILog("Should request interstitial at " + location + "?");
            return true;
        }

        @Override
        public boolean shouldDisplayInterstitial(String location) {
            addToUILog("Should display interstitial at " + location + "?");
            return true;
        }

        @Override
        public void didCacheInterstitial(String location) {
            addToUILog("Interstitial cached at " + location);
            setHasAdForLocation(location);
            incrementCounter(cacheCounter);
        }

        @Override
        public void didFailToLoadInterstitial(String location, CBError.CBImpressionError error) {
            addToUILog("Interstitial failed to load at " + location + " with error: " + error.name());
            setHasAdForLocation(location);
            incrementCounter(failLoadCounter);
        }

        @Override
        public void willDisplayInterstitial(String location) {
            addToUILog("Will display interstitial at " + location);
        }

        @Override
        public void didDismissInterstitial(String location) {
            addToUILog("Interstitial dismissed at " + location);
            incrementCounter(dismissCounter);
        }

        @Override
        public void didCloseInterstitial(String location) {
            addToUILog("Interstitial closed at " + location);
            incrementCounter(closeCounter);
        }

        @Override
        public void didClickInterstitial(String location) {
            addToUILog("Interstitial clicked at " + location );
            incrementCounter(clickCounter);
        }

        @Override
        public void didDisplayInterstitial(String location) {
            addToUILog("Interstitial displayed at " + location);
            setHasAdForLocation(location);
            incrementCounter(displayCounter);
        }

        @Override
        public void didFailToRecordClick(String uri, CBError.CBClickError error) {
            addToUILog("Failed to record click " + (uri != null ? uri : "null") + ", error: " + error.name());
            incrementCounter(failClickCounter);
        }

        @Override
        public boolean shouldDisplayRewardedVideo(String location) {
            addToUILog("Should display rewarded video at " + location + "?");
            return true;
        }

        @Override
        public void didCacheRewardedVideo(String location) {
            addToUILog("Did cache rewarded video " + location);
            setHasAdForLocation(location);
            incrementCounter(cacheCounter);
        }

        @Override
        public void didFailToLoadRewardedVideo(String location,
                                               CBError.CBImpressionError error) {
            addToUILog("Rewarded Video failed to load at " + location + " with error: " + error.name());
            setHasAdForLocation(location);
            incrementCounter(failLoadCounter);
        }

        @Override
        public void didDismissRewardedVideo(String location) {
            addToUILog("Rewarded video dismissed at " + location);
            incrementCounter(dismissCounter);
        }

        @Override
        public void didCloseRewardedVideo(String location) {
            addToUILog("Rewarded video closed at " + location);
            incrementCounter(closeCounter);
        }

        @Override
        public void didClickRewardedVideo(String location) {
            addToUILog("Rewarded video clicked at " + location);
            incrementCounter(clickCounter);
        }

        @Override
        public void didCompleteRewardedVideo(String location, int reward) {
            addToUILog("Rewarded video completed at " + location + "for reward: " + reward);
            incrementCounter(completeCounter);
            addToCounter(rewardCounter, reward);
        }

        @Override
        public void didDisplayRewardedVideo(String location) {
            addToUILog("Rewarded video displayed at " + location);
            setHasAdForLocation(location);
            incrementCounter(displayCounter);
        }

        @Override
        public void willDisplayVideo(String location) {
            addToUILog("Will display video at " + location);
        }

        @Override
        public void didCacheInPlay(String location) {
            addToUILog("In Play loaded at " + location);
            setHasAdForLocation(location);
            incrementCounter(cacheCounter);
        }

        @Override
        public void didFailToLoadInPlay(String location, CBError.CBImpressionError error) {
            addToUILog("In play failed to load at " + location + ", with error: " + error);
            setHasAdForLocation(location);
            incrementCounter(failLoadCounter);
        }

        @Override
        public void didInitialize() {
            addToUILog("Chartboost SDK is initialized and ready!");
        }

    };
}
