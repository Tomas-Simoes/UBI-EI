package ubi.pt.pdm_project.managers;

import android.content.Context;
import android.content.SharedPreferences;
import android.util.Log;

public class DataPersistenceManager {
    private static DataPersistenceManager instance;

    private static final String PREFS_NAME = "GameStatsPrefs";
    private static final String KEY_TIME_FORMAT = "level_%d_best_time_ms";
    private static final String KEY_BLUE_COINS_FORMAT = "level_%d_blue_coins";

    private final SharedPreferences prefs;

    public DataPersistenceManager(Context context) {
        this.prefs = context.getSharedPreferences(PREFS_NAME, Context.MODE_PRIVATE);
    }

    public static DataPersistenceManager getInstance(Context context) {
        if (instance == null) {
            instance = new DataPersistenceManager(context.getApplicationContext());
        }
        return instance;
    }

    public boolean registerNewRun(int levelNumber, int blueCoinsCollected, long timeMs) {
        long bestTimeMs = getBestTimeMs(levelNumber);

        if (timeMs < bestTimeMs) {
            prefs.edit()
                    .putLong(String.format(KEY_TIME_FORMAT, levelNumber), timeMs)
                    .putInt(String.format(KEY_BLUE_COINS_FORMAT, levelNumber), blueCoinsCollected)
                    .apply();

            Log.d("GameDataPersistence", "New best time for Level " + levelNumber + ": "
                    + timeMs + " ms with " + blueCoinsCollected + " blue coins");
            return true;
        } else {
            Log.d("GameDataPersistence", "Run not better than best time for Level " + levelNumber
                    + ": " + timeMs + " ms, best is " + bestTimeMs + " ms");
            return false;
        }
    }

    public long getBestTimeMs(int levelNumber) {
        String key = String.format(KEY_TIME_FORMAT, levelNumber);
        return prefs.getLong(key, Long.MAX_VALUE);
    }


    public int getBlueCoinsCollected(int levelNumber) {
        String key = String.format(KEY_BLUE_COINS_FORMAT, levelNumber);
        return prefs.getInt(key, 0);
    }

    public void clearAllData() {
        prefs.edit().clear().apply();
        Log.d("GameDataPersistence", "All saved game data cleared");
    }

}
