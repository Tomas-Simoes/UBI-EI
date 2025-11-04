package ubi.pt.pdm_project;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.io.IOException;

public class GameActivity extends AppCompatActivity {

    private TMXView mapView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        int levelNumber = getIntent().getIntExtra("LEVEL_NUMBER", 1); // 1 is the default value
        Log.d("GameActivity", "Loaded Level Number: " + levelNumber);
        String mapPath = "maps/level_" + levelNumber + ".tmx";

        // Load the TMX file
        TileMapData mapData = TMXLoader.readTMX(mapPath, this);

        if (mapData == null) {
            Log.e("MainActivity", "Failed to load map!");
            return;
        }

        // Create bitmap from all layers
        Bitmap mapBitmap = TMXLoader.createBitmap(mapData, this);

        if (mapBitmap == null) {
            Log.e("MainActivity", "Failed to create bitmap!");
            return;
        }

        Player player = new Player(this, 0, 0);
        TMXView mapView = new TMXView(this, mapBitmap, 4.0f, player);
        setContentView(mapView);
    }
}
