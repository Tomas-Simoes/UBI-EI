package ubi.pdm.calculator;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import com.google.android.material.textfield.TextInputEditText;

public class MainActivity extends AppCompatActivity {

    private Button btnAdd;
    private Button btnSub;
    private Button btnMul;
    private Button btnDiv;

    private TextInputEditText inputNum1;
    private TextInputEditText inputNum2;

    private TextView textResult;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btnAdd = findViewById(R.id.btnAdd);
        btnSub = findViewById(R.id.btnSub);
        btnMul = findViewById(R.id.btnMul);
        btnDiv = findViewById(R.id.btnDiv);

        inputNum1 = findViewById(R.id.inputNum1);
        inputNum2 = findViewById(R.id.inputNum2);

        textResult = findViewById(R.id.textResult);

        btnAdd.setOnClickListener(v -> onOperation("+"));
        btnSub.setOnClickListener(v -> onOperation("-"));
        btnMul.setOnClickListener(v -> onOperation("*"));
        btnDiv.setOnClickListener(v -> onOperation("/"));
    }

    private void onOperation(String operator) {
        Float input1, input2;

        input1 = Float.parseFloat(inputNum1.getText().toString());
        input2 = Float.parseFloat(inputNum2.getText().toString());

        switch (operator) {
            case "+":
                textResult.setText(String.valueOf(input1 + input2));
                break;
            case "-":
                textResult.setText(String.valueOf(input1 - input2));
                break;
            case "*":
                textResult.setText(String.valueOf(input1 * input2));
                break;
            case "/":
                if (input2 == 0) {
                    Toast.makeText(this, "Cannot divide by zero", Toast.LENGTH_SHORT).show();
                    textResult.setText("Error");
                } else {
                    textResult.setText(String.valueOf(input1 / input2));
                }
                break;
            default:
                Toast.makeText(this, "Unknown operator", Toast.LENGTH_SHORT).show();
                textResult.setText("Error");
                break;
        }

    }
}