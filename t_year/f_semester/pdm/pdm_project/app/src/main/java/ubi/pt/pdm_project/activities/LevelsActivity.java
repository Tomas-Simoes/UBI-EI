package ubi.pt.pdm_project.activities;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.FrameLayout;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import ubi.pt.pdm_project.R;
import ubi.pt.pdm_project.managers.DataPersistenceManager;

public class LevelsActivity extends AppCompatActivity {

    private static final int REQUEST_CODE_GAME = 1;
    private DataPersistenceManager dataPersistenceManager;
    private ActivityResultLauncher<Intent> gameLauncher;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        dataPersistenceManager = DataPersistenceManager.getInstance(this);

        setContentView(R.layout.activity_level);

        gameLauncher = registerForActivityResult(
                new ActivityResultContracts.StartActivityForResult(),
                result -> {
                    if (result.getResultCode() == RESULT_OK) {
                        // This will be called when GameActivity finishes with setResult(RESULT_OK)
                        updateLevelStats();
                        Log.d("GameData", "Returned from GameActivity, updating stats");
                    }
                }
        );

        setupLevelButtons();
        updateLevelStats();
    }

    private void setupLevelButtons() {
        ImageButton level1 = findViewById(R.id.level1);
        ImageButton level2 = findViewById(R.id.level2);
        ImageButton level3 = findViewById(R.id.level3);
        ImageButton level4 = findViewById(R.id.level4);

        level1.setOnClickListener(v -> openLevel(1));
        level2.setOnClickListener(v -> openLevel(2));
        level3.setOnClickListener(v -> openLevel(3));
        level4.setOnClickListener(v -> openLevel(4));
    }

    private void updateLevelStats() {
        int[] frameIds = {
                R.id.levelFrame1,
                R.id.levelFrame2,
                R.id.levelFrame3,
                R.id.levelFrame4,
        };

        for (int i = 0; i < frameIds.length; i++) {
            int levelNumber = i + 1;
            FrameLayout levelFrame = findViewById(frameIds[i]);

            LinearLayout linearLayout = (LinearLayout) levelFrame.getChildAt(1);

            TextView recordTextView = (TextView) linearLayout.getChildAt(1);
            TextView collectiblesTextView = (TextView) linearLayout.getChildAt(2);

            long bestTimeMs = dataPersistenceManager.getBestTimeMs(levelNumber);
            int blueCoins = dataPersistenceManager.getBlueCoinsCollected(levelNumber);

            String recordText;
            if (bestTimeMs == Long.MAX_VALUE) {
                recordText = "Your Record: --";
            } else {
                long totalSeconds = bestTimeMs / 1000;
                long minutes = totalSeconds / 60;
                long seconds = totalSeconds % 60;
                recordText = String.format("Your Record: %02d:%02d", minutes, seconds);
            }

            String collectiblesText = "Blue Coins: " + blueCoins + "/4";

            recordTextView.setText(recordText);
            collectiblesTextView.setText(collectiblesText);
        }
    }

    private void openLevel(int levelNumber) {
        Intent intent = new Intent(LevelsActivity.this, GameActivity.class);

        intent.putExtra("LEVEL_NUMBER", levelNumber);
        Toast.makeText(this, "Opening Level " + levelNumber, Toast.LENGTH_SHORT).show();

        gameLauncher.launch(intent);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        Log.d("GameData", "yo");
        updateLevelStats();
    }
}