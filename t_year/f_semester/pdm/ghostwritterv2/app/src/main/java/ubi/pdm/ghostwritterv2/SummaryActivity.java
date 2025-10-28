package ubi.pdm.ghostwritterv2;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.charset.StandardCharsets;

public class SummaryActivity extends AppCompatActivity {

    private TextView resultView;
    private TextView contributorsTextView;
    private Button btnHome;
    private Button btnSave;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_summary);

        resultView = findViewById(R.id.resultView);
        contributorsTextView = findViewById(R.id.contributorsTextView);
        btnHome = findViewById(R.id.btnHome);
        btnSave = findViewById(R.id.btnLocalSave);

        int numContributors = getIntent().getIntExtra("numContributors", 0);

        String aux = getIntent().getStringExtra("completeText");
        final String completeText = aux == null || aux.isEmpty() ? "No contributions yet." : aux;

        resultView.setText(completeText);
        contributorsTextView.setText(numContributors + " ghostwriters have\ncontributed!");

        btnHome.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent resultIntent = new Intent();
                setResult(RESULT_OK, resultIntent);
                finish();
            }
        });

        btnSave.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    String fileName = "prosa_" + System.currentTimeMillis() + ".txt";
                    FileOutputStream fos = openFileOutput(fileName, MODE_PRIVATE);
                    fos.write(completeText.getBytes(StandardCharsets.UTF_8));
                    fos.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
    }
}
