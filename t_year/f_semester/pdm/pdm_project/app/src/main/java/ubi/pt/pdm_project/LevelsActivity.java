package ubi.pt.pdm_project;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class LevelsActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_level);

        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.rootFrame), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        setupLevelButtons();
    }

    private void setupLevelButtons() {
        ImageButton level1 = findViewById(R.id.level1);
        ImageButton level2 = findViewById(R.id.level2);
        ImageButton level3 = findViewById(R.id.level3);
        ImageButton level4 = findViewById(R.id.level4);
        ImageButton level5 = findViewById(R.id.level5);
        ImageButton level6 = findViewById(R.id.level6);

        level1.setOnClickListener(v -> openLevel(1));
        level2.setOnClickListener(v -> openLevel(2));
        level3.setOnClickListener(v -> openLevel(3));
        level4.setOnClickListener(v -> openLevel(4));
        level5.setOnClickListener(v -> openLevel(5));
        level6.setOnClickListener(v -> openLevel(6));
    }

    private void openLevel(int levelNumber) {
        Intent intent = new Intent(LevelsActivity.this, GameActivity.class);

        intent.putExtra("LEVEL_NUMBER", levelNumber);
        Toast.makeText(this, "Opening Level " + levelNumber, Toast.LENGTH_SHORT).show();

        startActivity(intent);
    }

    private void openLevelWithCheck(int levelNumber) {
        if (isLevelUnlocked(levelNumber)) {
            Intent intent = new Intent(LevelsActivity.this, GameActivity.class);
            intent.putExtra("LEVEL_NUMBER", levelNumber);
            startActivity(intent);
        } else {
            Toast.makeText(this, "Level " + levelNumber + " is locked!", Toast.LENGTH_SHORT).show();
        }
    }

    private boolean isLevelUnlocked(int levelNumber) {
        if (levelNumber == 1) return true;

        return true;
    }
}