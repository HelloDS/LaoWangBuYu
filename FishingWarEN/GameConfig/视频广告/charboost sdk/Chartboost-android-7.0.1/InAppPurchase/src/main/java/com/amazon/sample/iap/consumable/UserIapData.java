package com.amazon.sample.iap.consumable;


/**
 * This is a simple example used in Amazon InAppPurchase Sample App, to show how
 * developer's application holding the customer's InAppPurchase data.
 * 
 * 
 */
public class UserIapData {
    private volatile int remainingOranges = 0;
    private volatile int consumedOranges = 0;
    private final String amazonUserId;
    private final String amazonMarketplace;
    public String getAmazonUserId() {
        return amazonUserId;
    }

    public String getAmazonMarketplace() {
        return amazonMarketplace;
    }

    public void setRemainingOranges(final int remaining) {
        this.remainingOranges = remaining;
    }

    public void setConsumedOranges(final int consumed) {
        this.consumedOranges = consumed;
    }

    public int getRemainingOranges() {
        return this.remainingOranges;
    }

    public int getConsumedOranges() {
        return this.consumedOranges;
    }

    public UserIapData(final String amazonUserId, final String amazonMarketplace) {
        this.amazonUserId = amazonUserId;
        this.amazonMarketplace = amazonMarketplace;
    }
}
