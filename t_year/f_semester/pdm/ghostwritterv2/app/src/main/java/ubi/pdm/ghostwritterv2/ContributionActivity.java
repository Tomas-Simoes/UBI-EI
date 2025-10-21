package ubi.pdm.ghostwritterv2;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import com.google.android.material.textfield.TextInputEditText;
import android.content.Intent;

public class ContributionActivity extends AppCompatActivity {
    private Button btnAdd;
    private Button btnHome;

    private String completeText = "";
    private TextInputEditText inputArea;
    private TextView contributorsTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_contribution);

        btnAdd = findViewById(R.id.btnAdd);
        btnHome = findViewById(R.id.btnHome);
        inputArea = findViewById(R.id.inputTextArea);
        contributorsTextView = findViewById(R.id.contributorsTextView);

        int numContributors = getIntent().getIntExtra("numContributors", 0);
        contributorsTextView.setText(String.format("%d ghostwriters have\ncontributed!", numContributors));  // FIX TYPO

        btnAdd.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String newText = String.valueOf(inputArea.getText()).trim();

                if (!newText.isEmpty()) {
                    Intent resultIntent = new Intent();
                    resultIntent.putExtra("contribution", newText);

                    setResult(RESULT_OK, resultIntent);
                } else {
                    setResult(RESULT_CANCELED);
                }

                finish();
            }
        });


    }
}