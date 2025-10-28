package ubi.pdm.ghostwritterv2;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.textfield.TextInputEditText;

public class MainActivity extends AppCompatActivity {

    private Button btnAdd;
    private Button btnFinish;
    private Button btnSettings;
    private Button btnAuthors;

    private TextInputEditText inputArea;
    private TextView resultView;
    private TextView contributorsTextView;

    private String completeText = "";
    private boolean showingCompleteText = false;
    private int numContributors = 0;

    private ActivityResultLauncher<Intent> contributionLauncher;
    private ActivityResultLauncher<Intent> summaryLauncher;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);

        btnAdd = findViewById(R.id.btnAdd);
        btnAuthors = findViewById(R.id.btnAuthors);
        btnFinish = findViewById(R.id.btnFinish);
        btnSettings = findViewById(R.id.btnSettings);

        btnSettings.setOnClickListener(v -> {
            Intent intent = new Intent(MainActivity.this, SettingsActivity.class);
            startActivity(intent);
        });

        contributionLauncher = registerForActivityResult(
                new ActivityResultContracts.StartActivityForResult(),
                result -> {
                    if (result.getResultCode() == Activity.RESULT_OK) {
                        Intent data = result.getData();
                        if (data != null) {
                            String contribution = data.getStringExtra("contribution");
                            if (contribution != null && !contribution.isEmpty()) {
                                numContributors++;
                                completeText += contribution + "\n";
                            }
                        }
                    }
                }
        );

        summaryLauncher = registerForActivityResult(
                new ActivityResultContracts.StartActivityForResult(),
                result -> {
                    if (result.getResultCode() == Activity.RESULT_OK) {
                        numContributors = 0;
                        completeText = "";
                    }
                }
        );

        btnAdd.setOnClickListener(v -> {
            Intent intent = new Intent(MainActivity.this, ContributionActivity.class);
            intent.putExtra("numContributors", numContributors);
            contributionLauncher.launch(intent);
        });

        btnFinish.setOnClickListener(v -> {
            Intent intent = new Intent(MainActivity.this, SummaryActivity.class);
            intent.putExtra("completeText", completeText);
            intent.putExtra("numContributors", numContributors);
            summaryLauncher.launch(intent);
        });

        btnAuthors.setOnClickListener(v -> {
            Intent intent = new Intent(MainActivity.this, AuthorsActivity.class);
            startActivity(intent);
        });

    }
}
