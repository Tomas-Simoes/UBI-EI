package ubi.pt.pdm_project.activities;

import android.content.Intent;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.ImageButton;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import java.util.Locale;

import ubi.pt.pdm_project.R;
import ubi.pt.pdm_project.entities.Necromancer;
import ubi.pt.pdm_project.entities.Player;
import ubi.pt.pdm_project.managers.DataPersistenceManager;
import ubi.pt.pdm_project.managers.InputManager;
import ubi.pt.pdm_project.tmxconverter.TMXLoader;
import ubi.pt.pdm_project.tmxconverter.TMXSurfaceView;
import ubi.pt.pdm_project.tmxconverter.TileMapData;
import ubi.pt.pdm_project.util.LevelCoordinates;

public class GameActivity extends AppCompatActivity {
    private final LevelCoordinates[] startCoordinates = new LevelCoordinates[] {
            new LevelCoordinates(150, 500),
            new LevelCoordinates(150, 500),
            new LevelCoordinates(180, 400),
            new LevelCoordinates(150, 500)

    };


    public TMXSurfaceView mapView;
    private View completed_overlay;
    private View death_overlay;


    private long startTime; // <-- To store the level start time
    private int currentLevelNumber;

    private InputManager inputManager;
    private DataPersistenceManager dataPersistenceManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        dataPersistenceManager = DataPersistenceManager.getInstance(this);

        currentLevelNumber = getIntent().getIntExtra("LEVEL_NUMBER", 1);
        String mapPath = "maps/level_" + currentLevelNumber + ".tmx";

        TileMapData mapData = TMXLoader.readTMX(mapPath, this);

        if (mapData == null) {
            Log.e("GameActivity", "Failed to load map");
            return;
        }

        Bitmap mapBitmap = TMXLoader.createBitmap(mapData, this);

        if (mapBitmap == null) {
            Log.e("GameActivity", "Failed to create bitmap");
            return;
        }

        Player player = new Player(this, startCoordinates[currentLevelNumber - 1].x, startCoordinates[currentLevelNumber - 1].y);

        mapView = new TMXSurfaceView(this, mapBitmap, mapData, 4.0f, player, currentLevelNumber);
        inputManager = new InputManager(this, mapView);

        FrameLayout rootLayout = new FrameLayout(this);
        rootLayout.addView(mapView); // bottom layer

        completed_overlay = getLayoutInflater().inflate(R.layout.activity_level_complete, rootLayout, false);
        completed_overlay.setVisibility(View.GONE);
        rootLayout.addView(completed_overlay);
        setContentView(rootLayout);

        death_overlay = getLayoutInflater().inflate(R.layout.activity_game_over, rootLayout, false);
        death_overlay.setVisibility(View.GONE);
        rootLayout.addView(death_overlay);
        setContentView(rootLayout);

        this.startTime = System.currentTimeMillis();
    }

    public void onDeath(int coinsCollected, int blueCoinsCollected){
        if(death_overlay != null) {
            death_overlay.setVisibility(View.VISIBLE);

            // Update the stats text if needed
            TextView coinsCollectedView = death_overlay.findViewById(R.id.tvCoinsCollected);
            TextView blueCoinsCollectedView = death_overlay.findViewById(R.id.tvBlueCoinsCollected);
            TextView timeTextView = death_overlay.findViewById(R.id.tvLevelTime);

            long elapsedTimeMs = System.currentTimeMillis() - startTime;
            long totalSeconds = elapsedTimeMs / 1000;
            long minutes = totalSeconds / 60;
            long seconds = totalSeconds % 60;
            timeTextView.setText(String.format(Locale.US, "%02d:%02d", minutes, seconds));
            coinsCollectedView.setText(String.valueOf(coinsCollected));
            blueCoinsCollectedView.setText(String.valueOf(blueCoinsCollected));

            ImageButton btnPlayAgain = death_overlay.findViewById(R.id.btnNextLevel);
            ImageButton btnHome = death_overlay.findViewById(R.id.btnHome);

            // Play again: restart the same level
            btnPlayAgain.setOnClickListener(v -> {
                Intent intent = new Intent(this, GameActivity.class);
                intent.putExtra("LEVEL_NUMBER", currentLevelNumber);
                startActivity(intent);
                finish();
            });

            btnHome.setOnClickListener(v -> {
                setResult(RESULT_OK);
                finish();
            });


        }
    }
    public void completeLevel(int coinsCollected, int blueCoinsCollected) {
        if (completed_overlay != null) {
            completed_overlay.setVisibility(View.VISIBLE);

            long elapsedTimeMs = System.currentTimeMillis() - startTime;
            long totalSeconds = elapsedTimeMs / 1000;
            long minutes = totalSeconds / 60;
            long seconds = totalSeconds % 60;

            String timeFormatted = String.format(Locale.US, "%02d:%02d", minutes, seconds);

            TextView timeTextView = completed_overlay.findViewById(R.id.tvLevelTime);
            TextView coinsCollectedView = completed_overlay.findViewById(R.id.tvCoinsCollected);
            TextView blueCoinsCollectedView = completed_overlay.findViewById(R.id.tvBlueCoinsCollected);

            timeTextView.setText(timeFormatted);
            coinsCollectedView.setText(String.valueOf(coinsCollected));
            blueCoinsCollectedView.setText(String.valueOf(blueCoinsCollected));

            if (dataPersistenceManager != null) {
                dataPersistenceManager.registerNewRun(currentLevelNumber, blueCoinsCollected, elapsedTimeMs);
            }

            ImageButton btnNextLevel = completed_overlay.findViewById(R.id.btnNextLevel);
            ImageButton btnHome = completed_overlay.findViewById(R.id.btnHome);

            btnNextLevel.setOnClickListener(v -> {
                int nextLevel = currentLevelNumber + 1;

                Intent intent = new Intent(this, GameActivity.class);
                intent.putExtra("LEVEL_NUMBER", nextLevel);
                startActivity(intent);
                finish();
            });

            btnHome.setOnClickListener(v -> {
                setResult(RESULT_OK);
                finish();
            });
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        inputManager.register();
    }

    @Override
    protected void onPause() {
        super.onPause();
        inputManager.unregister();
    }
}