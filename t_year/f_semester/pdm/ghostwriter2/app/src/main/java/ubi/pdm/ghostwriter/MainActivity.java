package ubi.pdm.ghostwriter;

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



public class MainActivity extends AppCompatActivity {

    private Button btnAdd;
    private Button btnFinish;
    private TextInputEditText inputArea;
    private TextView resultView;
    private TextView contributorsTextView;

    private String completeText = "";
    private boolean showingCompleteText;
    private int numContributors = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);

        btnAdd = findViewById(R.id.btnAdd);
        btnFinish = findViewById(R.id.btnFinish);
        inputArea = findViewById(R.id.inputTextArea);
        resultView = findViewById(R.id.resultView);
        contributorsTextView = findViewById(R.id.contributorsTextView);


        btnAdd.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(showingCompleteText){
                    numContributors = 0;
                    showingCompleteText = false;
                    resultView.setText("The complete result will appear on here...");
                }

                String newText = String.valueOf(inputArea.getText());
                completeText += "\n" + newText;
                inputArea.setText("");

                numContributors += 1;
                contributorsTextView.setText(String.format("%d ghostwriters have\ncontributed!", numContributors));  // FIX TYPO
            }
        });

        btnFinish.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(showingCompleteText){
                    numContributors = 0;
                    showingCompleteText = false;
                    resultView.setText("The complete result will appear on here...");
                }

                resultView.setText(completeText);
                completeText = "";
                showingCompleteText = true;
            }
        });
    }
}