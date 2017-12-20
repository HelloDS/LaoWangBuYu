package com.chartboost.sdk.sample;

import android.annotation.TargetApi;
import android.content.pm.ActivityInfo;
import android.content.res.Configuration;
import android.os.Build;
import android.os.Bundle;
import android.preference.CheckBoxPreference;
import android.preference.Preference;
import android.preference.PreferenceActivity;
import android.preference.SwitchPreference;
import android.util.Log;
import android.widget.Toast;

import com.chartboost.sdk.Chartboost;

/**
 * Created by Gonzalo on 5/13/16.
 */
public class SettingsActivity extends PreferenceActivity {

    private static final String TAG = "Settings Activity";

    //CheckboxPreferences for API < 14
    CheckBoxPreference lockOrientationCheckBox;
    CheckBoxPreference setShouldRequestInterstitialsInFirstSessionCheckBox;
    CheckBoxPreference setShouldPrefetchVideoContentCheckBox;
    CheckBoxPreference setAutoCacheAdsCheckBox;

    //SwitchPreference for API > 14
    SwitchPreference lockOrientationSwitch;
    SwitchPreference setShouldRequestInterstitialsInFirstSessionSwitch;
    SwitchPreference setShouldPrefetchVideoContentSwitch;
    SwitchPreference setAutoCacheAdsSwitch;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        addPreferencesFromResource(R.xml.preferences);
        if (Build.VERSION.SDK_INT < 14) {
            setUpCheckBoxes();
        } else {
            setUpSwitches();
        }
    }

    private void setUpCheckBoxes() {

        lockOrientationCheckBox = (CheckBoxPreference) findPreference(getString(R.string.key_lock_orientation));
        lockOrientationCheckBox.setOnPreferenceChangeListener(new Preference.OnPreferenceChangeListener() {
            @Override
            public boolean onPreferenceChange(Preference preference, Object newValue) {
                return onlockOrientationChanged((Boolean) newValue);
            }
        });
        lockOrientationCheckBox.setEnabled(false);

        setShouldRequestInterstitialsInFirstSessionCheckBox = (CheckBoxPreference) findPreference(getString(R.string.key_request_interstitial_in_first_session));
        setShouldRequestInterstitialsInFirstSessionCheckBox.setOnPreferenceChangeListener(new Preference.OnPreferenceChangeListener() {
            @Override
            public boolean onPreferenceChange(Preference preference, Object newValue) {
                return onSetShouldRequestInterstitialsInFirstSessionChanged(newValue);
            }
        });


        setShouldPrefetchVideoContentCheckBox = (CheckBoxPreference) findPreference(getString(R.string.key_enable_video_prefetch));
        setShouldPrefetchVideoContentCheckBox.setOnPreferenceChangeListener(new Preference.OnPreferenceChangeListener() {
            @Override
            public boolean onPreferenceChange(Preference preference, Object newValue) {
                return onSetShouldPrefetchVideoContentChanged(newValue);
            }
        });

        setAutoCacheAdsCheckBox = (CheckBoxPreference) findPreference(getString(R.string.key_enable_autocache));
        setAutoCacheAdsCheckBox.setOnPreferenceChangeListener(new Preference.OnPreferenceChangeListener() {
            @Override
            public boolean onPreferenceChange(Preference preference, Object newValue) {
                return onSetAutoCacheAdsChanged(newValue);
            }
        });
    }

    @TargetApi(14)
    private void setUpSwitches() {

        lockOrientationSwitch = (SwitchPreference) findPreference(getString(R.string.key_lock_orientation));
        lockOrientationSwitch.setOnPreferenceChangeListener(new Preference.OnPreferenceChangeListener() {
            @Override
            public boolean onPreferenceChange(Preference preference, Object newValue) {
                return onlockOrientationChanged((Boolean) newValue);
            }
        });
        lockOrientationSwitch.setEnabled(false);

        setShouldRequestInterstitialsInFirstSessionSwitch = (SwitchPreference) findPreference(getString(R.string.key_request_interstitial_in_first_session));
        setShouldRequestInterstitialsInFirstSessionSwitch.setOnPreferenceChangeListener(new Preference.OnPreferenceChangeListener() {
            @Override
            public boolean onPreferenceChange(Preference preference, Object newValue) {
                return onSetShouldRequestInterstitialsInFirstSessionChanged(newValue);
            }
        });

        setShouldPrefetchVideoContentSwitch = (SwitchPreference) findPreference(getString(R.string.key_enable_video_prefetch));
        setShouldPrefetchVideoContentSwitch.setOnPreferenceChangeListener(new Preference.OnPreferenceChangeListener() {
            @Override
            public boolean onPreferenceChange(Preference preference, Object newValue) {
                return onSetShouldPrefetchVideoContentChanged(newValue);
            }
        });

        setAutoCacheAdsSwitch = (SwitchPreference) findPreference(getString(R.string.key_enable_autocache));
        setAutoCacheAdsSwitch.setOnPreferenceChangeListener(new Preference.OnPreferenceChangeListener() {
            @Override
            public boolean onPreferenceChange(Preference preference, Object newValue) {
                return onSetAutoCacheAdsChanged(newValue);
            }
        });
    }

    private boolean onSetAutoCacheAdsChanged(Object newValue) {
        Log.v(TAG, "Auto cache ads : " + newValue);
        Chartboost.setAutoCacheAds((Boolean) newValue);
        return true;
    }

    private boolean onSetShouldPrefetchVideoContentChanged(Object newValue) {
        Log.v(TAG, "Prefetch set to : " + newValue);
        Chartboost.setShouldPrefetchVideoContent((Boolean) newValue);
        return true;
    }

    private boolean onSetShouldRequestInterstitialsInFirstSessionChanged(Object newValue) {
        Log.v(TAG, "Request interstitials in first session : " + newValue);
        Chartboost.setShouldRequestInterstitialsInFirstSession((Boolean) newValue);
        return true;
    }

    private boolean onlockOrientationChanged(Boolean newValue) {
        if (ChartboostSample.activity == null) {
            Toast.makeText(SettingsActivity.this, "Unable to lock orientation, Debug Activity not initiated", Toast.LENGTH_SHORT).show();
            return false;
        }
        if (newValue) {
            int currentOrientation = getResources().getConfiguration().orientation;
            if (currentOrientation == Configuration.ORIENTATION_LANDSCAPE) {
                ChartboostSample.activity.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_LANDSCAPE);
            } else {
                ChartboostSample.activity.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_PORTRAIT);
            }
        } else {
            ChartboostSample.activity.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_UNSPECIFIED);
        }
        return true;
    }
}
