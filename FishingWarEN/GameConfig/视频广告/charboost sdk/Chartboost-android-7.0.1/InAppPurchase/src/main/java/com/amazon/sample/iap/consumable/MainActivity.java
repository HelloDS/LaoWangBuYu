package com.amazon.sample.iap.consumable;

import java.util.HashSet;
import java.util.Set;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.amazon.device.iap.PurchasingService;
import com.amazon.device.iap.model.RequestId;
import com.chartboost.inapppurchase.R;

/**
 * Main activity for IAP Consumable Sample Code
 * 
 * This is the main activity for this project.
 */
public class MainActivity extends Activity {
    private SampleIapManager sampleIapManager;

    /**
     * Setup IAP SDK and other UI related objects specific to this sample
     * application.
     */
    @Override
    protected void onCreate(final Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setupApplicationSpecificOnCreate();
        setupIAPOnCreate();
    }

    /**
     * Setup for IAP SDK called from onCreate. Sets up {@link SampleIapManager}
     * to handle InAppPurchasing logic and {@link SamplePurchasingListener} for
     * listening to IAP API callbacks
     */
    private void setupIAPOnCreate() {
        sampleIapManager = new SampleIapManager(this);
        sampleIapManager.activate();
        final SamplePurchasingListener purchasingListener = new SamplePurchasingListener(sampleIapManager);
        Log.d(TAG, "onCreate: registering PurchasingListener");
        PurchasingService.registerListener(this.getApplicationContext(), purchasingListener);
        Log.d(TAG, "IS_SANDBOX_MODE:" + PurchasingService.IS_SANDBOX_MODE);
    }

    /**
     * Call {@link PurchasingService#getProductData(Set)} to get the product
     * availability
     */
    @Override
    protected void onStart() {
        super.onStart();
        Log.d(TAG, "onStart: call getProductData for skus: " + MySku.values());
        final Set<String> productSkus = new HashSet<String>();
        for (final MySku mySku : MySku.values()) {
            productSkus.add(mySku.getSku());
        }
        PurchasingService.getProductData(productSkus);
    }

    /**
     * Calls {@link PurchasingService#getUserData()} to get current Amazon
     * user's data and {@link PurchasingService#getPurchaseUpdates(boolean)} to
     * get recent purchase updates
     */
    @Override
    protected void onResume() {
        super.onResume();
        sampleIapManager.activate();
        Log.d(TAG, "onResume: call getUserData");
        PurchasingService.getUserData();
        Log.d(TAG, "onResume: getPurchaseUpdates");
        PurchasingService.getPurchaseUpdates(false);
    }

    /**
     * Deactivate Sample IAP manager on main activity's Pause event
     */
    @Override
    protected void onPause() {
        super.onPause();
        sampleIapManager.deactivate();
    }

    /**
     * Click handler invoked when user clicks button to buy an orange
     * consumable. This method calls {@link PurchasingService#purchase(String)}
     * with the SKU to initialize the purchase from Amazon Appstore
     */
    public void onBuyOrangeClick(final View view) {
        final RequestId requestId = PurchasingService.purchase(MySku.ORANGE.getSku());
        Log.d(TAG, "onBuyOrangeClick: requestId (" + requestId + ")");
    }

    /**
     * Click handler called when user clicks button to eat an orange consumable.
     */
    public void onEatOrangeClick(final View view) {
        try {
            sampleIapManager.eatOrange();
            Log.d(TAG, "onEatOrangeClick: consuming 1 orange");

            updateOrangesInView(sampleIapManager.getUserIapData().getRemainingOranges(),
                                sampleIapManager.getUserIapData().getConsumedOranges());
        } catch (final RuntimeException e) {
            showMessage("Unknow error when eat Orange");
        }
    }

    // ///////////////////////////////////////////////////////////////////////////////////////
    // ////////////////////////// Application specific code below
    // ////////////////////////////
    // ///////////////////////////////////////////////////////////////////////////////////////

    private static final String TAG = "SampleIAPConsumablesApp";
    protected Handler guiThreadHandler;

    protected Button buyOrangeButton;
    protected Button eatOrangeButton;

    protected TextView numOranges;
    protected TextView numOrangesConsumed;

    /**
     * Setup application specific things, called from onCreate()
     */
    protected void setupApplicationSpecificOnCreate() {
        setContentView(R.layout.activity_main);

        buyOrangeButton = (Button) findViewById(R.id.buy_orange_button);

        eatOrangeButton = (Button) findViewById(R.id.eat_orange_button);
        eatOrangeButton.setEnabled(false);

        numOranges = (TextView) findViewById(R.id.num_oranges);
        numOrangesConsumed = (TextView) findViewById(R.id.num_oranges_consumed);

        guiThreadHandler = new Handler();
    }

    /**
     * Disable buy button for any unavailable SKUs. In this sample app, this
     * would just disable "Buy Orange" button
     * 
     * @param unavailableSkus
     */
    protected void disableButtonsForUnavailableSkus(final Set<String> unavailableSkus) {
        for (final String unavailableSku : unavailableSkus) {
            if (MySku.ORANGE.getSku().equals(unavailableSku)) {
                Log.d(TAG, "disableButtonsForUnavailableSkus: disabling buyOrangeButton");
                disableBuyOrangeButton();
            }
        }
    }

    /**
     * Disable "Buy Orange" button
     */
    void disableBuyOrangeButton() {
        buyOrangeButton.setEnabled(false);
    }

    /**
     * Enable "Buy Orange" button
     */
    void enableBuyOrangeButton() {
        buyOrangeButton.setEnabled(true);
    }

    /**
     * Update view with how many oranges I have and how many I've consumed.
     * 
     * @param haveQuantity
     * @param consumedQuantity
     */
    protected void updateOrangesInView(final int haveQuantity, final int consumedQuantity) {
        Log.d(TAG, "updateOrangesInView with haveQuantity (" + haveQuantity
                   + ") and consumedQuantity ("
                   + consumedQuantity
                   + ")");
        guiThreadHandler.post(new Runnable() {
            @Override
            public void run() {
                numOranges.setText(String.valueOf(haveQuantity));
                numOrangesConsumed.setText(String.valueOf(consumedQuantity));

                if (haveQuantity > 0) {
                    eatOrangeButton.setEnabled(true);
                } else {
                    eatOrangeButton.setEnabled(false);
                }
            }
        });
    }

    /**
     * Show message on UI
     * 
     * @param message
     */
    public void showMessage(final String message) {
        Toast.makeText(MainActivity.this, message, Toast.LENGTH_LONG).show();
    }
}
