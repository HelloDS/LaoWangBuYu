package com.amazon.sample.iap.consumable;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.util.Log;

import com.amazon.sample.iap.consumable.SampleIapManager.PurchaseRecord;


/**
 * DAO class for sample purchase data
 * 
 * 
 */
public class PurchaseDataSource {
    public static enum PurchaseStatus {
        PAID, FULFILLED, UNAVAILABLE, UNKNOWN
    }

    private static final String TAG = "SampleIAPManager";

    private SQLiteDatabase database;
    private final SampleSQLiteHelper dbHelper;

    private final String[] allColumns = { SampleSQLiteHelper.COLUMN_RECEIPT_ID, SampleSQLiteHelper.COLUMN_USER_ID,
            SampleSQLiteHelper.COLUMN_STATUS };

    public PurchaseDataSource(final Context context) {
        dbHelper = new SampleSQLiteHelper(context);
    }

    public void open() throws SQLException {
        database = dbHelper.getWritableDatabase();
    }

    public void close() {
        dbHelper.close();
    }

    /**
     * Create the purchase record in sqlite database
     * 
     * @param receiptId
     *            amazon's receipt id
     * @param userId
     *            amazon user id
     * @param status
     *            the status for the purchase
     */
    public void createPurchase(final String receiptId, final String userId, final PurchaseStatus status) {
        Log.d(TAG, "createPurchase: receiptId (" + receiptId + "),userId (" + userId + "), status (" + status + ")");

        final ContentValues values = new ContentValues();
        values.put(SampleSQLiteHelper.COLUMN_RECEIPT_ID, receiptId);
        values.put(SampleSQLiteHelper.COLUMN_USER_ID, userId);
        values.put(SampleSQLiteHelper.COLUMN_STATUS, status.toString());
        try {
            database.insertOrThrow(SampleSQLiteHelper.TABLE_PURCHASES, null, values);
        } catch (final SQLException e) {
            Log.w(TAG, "A purchase with given receipt id already exists, simply discard the new purchase record");
        }
    }

    private PurchaseRecord cursorToPurchaseRecord(final Cursor cursor) {
        final PurchaseRecord purchaseRecord = new PurchaseRecord();
        purchaseRecord.setReceiptId(cursor.getString(cursor.getColumnIndex(SampleSQLiteHelper.COLUMN_RECEIPT_ID)));
        purchaseRecord.setUserId(cursor.getString(cursor.getColumnIndex(SampleSQLiteHelper.COLUMN_USER_ID)));
        try {
            purchaseRecord.setStatus(PurchaseStatus.valueOf(cursor.getString(cursor.getColumnIndex(SampleSQLiteHelper.COLUMN_STATUS))));
        } catch (final Exception e) {
            purchaseRecord.setStatus(PurchaseStatus.UNKNOWN);
        }
        return purchaseRecord;
    }

    /**
     * Return the purchase record by receipt id
     * 
     * @param receiptId
     *            amazon receipt id
     * @param userId
     *            user id used to verify the purchase record
     * @return
     */
    public final PurchaseRecord getPurchaseRecord(final String receiptId, final String userId) {
        Log.d(TAG, "getPurchaseRecord: receiptId (" + receiptId + "), userId (" + userId + ")");

        final String where = SampleSQLiteHelper.COLUMN_RECEIPT_ID + " = ?";
        final Cursor cursor = database.query(SampleSQLiteHelper.TABLE_PURCHASES,
                                             allColumns,
                                             where,
                                             new String[] { receiptId },
                                             null,
                                             null,
                                             null);
        cursor.moveToFirst();
        // no record found for the given receipt id
        if (cursor.isAfterLast()) {
            Log.d(TAG, "getPurchaseRecord: no record found for receipt id (" + receiptId + ")");
            cursor.close();
            return null;
        }
        final PurchaseRecord purchaseRecord = cursorToPurchaseRecord(cursor);
        cursor.close();
        if (purchaseRecord.getUserId() != null && purchaseRecord.getUserId().equalsIgnoreCase(userId)) {
            Log.d(TAG, "getPurchaseRecord: record found for receipt id (" + receiptId + ")");
            return purchaseRecord;
        } else {
            Log.d(TAG, "getPurchaseRecord: user id not match, receipt id (" + receiptId + "), userId (" + userId + ")");
            // cannot verify the purchase is for the correct user;
            return null;
        }

    }

    /**
     * Update Purchase status for given receipt id
     * 
     * @param receiptId
     *            receipt id to update
     * @param fromStatus
     *            current status for the purchase record in table
     * @param toStatus
     *            latest status for the purchase record
     * @return
     */
    public boolean updatePurchaseStatus(final String receiptId,
            final PurchaseStatus fromStatus,
            final PurchaseStatus toStatus) {
        Log.d(TAG, "updatePurchaseStatus: receiptId (" + receiptId + "), status:(" + fromStatus + "->" + toStatus + ")");

        String where = SampleSQLiteHelper.COLUMN_RECEIPT_ID + " = ?";
        String[] whereArgs = new String[] { receiptId };

        if (fromStatus != null) {
            where = where + " and " + SampleSQLiteHelper.COLUMN_STATUS + " = ?";
            whereArgs = new String[] { receiptId, fromStatus.toString() };
        }
        final ContentValues values = new ContentValues();
        values.put(SampleSQLiteHelper.COLUMN_STATUS, toStatus.toString());
        final int updated = database.update(SampleSQLiteHelper.TABLE_PURCHASES, values, where, whereArgs);
        Log.d(TAG, "updatePurchaseStatus: updated " + updated);
        return updated > 0;

    }
}
