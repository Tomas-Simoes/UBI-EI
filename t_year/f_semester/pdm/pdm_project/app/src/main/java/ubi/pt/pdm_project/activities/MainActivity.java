package ubi.pt.pdm_project.activities;

import android.content.Intent;
import android.os.Bundle;
import android.widget.ImageButton;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import ubi.pt.pdm_project.R;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);

        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        ImageButton btnLevels = findViewById(R.id.btnLevels);
        ImageButton btnExit = findViewById(R.id.btnExit);

        btnLevels.setOnClickListener(v -> {
            Intent intent = new Intent(MainActivity.this, LevelsActivity.class);
            startActivity(intent);
        });

        btnExit.setOnClickListener(v -> {
            finishAffinity();
        });
    }
}
