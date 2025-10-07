package ubi.pdm.magic_8ball;

import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import android.util.Log;
public class MainActivity extends AppCompatActivity {

    private Button spin_btn;
    private EditText prediction_txt;
    private ConstraintLayout main_layout;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        spin_btn =findViewById(R.id.spin_button);
        prediction_txt = findViewById(R.id.prediction_text);
        main_layout = findViewById(R.id.main);

        spin_btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int prediction = 1 + (int) (Math.random() * 3);
                String new_prediction = "";
                switch (prediction) {
                    case 1:
                        new_prediction = "Yes";
                        break;
                    case 2:
                        new_prediction = "No";
                        break;
                    case 3:
                        new_prediction = "Maybe";
                        break;
                    default:
                        Log.d("APP_DEBUG", "Error in randomizing prediction");
                        break;
                }

                prediction_txt.setText(new_prediction);
            }
        });
    }
}