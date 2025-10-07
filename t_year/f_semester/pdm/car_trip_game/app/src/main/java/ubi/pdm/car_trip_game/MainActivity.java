package ubi.pdm.car_trip_game;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import androidx.appcompat.app.AppCompatActivity;
import android.util.Log;

public class MainActivity extends AppCompatActivity {
    private EditText editNumero1;
    private EditText editNumero2;

    private Button btnIncrementar1;
    private Button btnIncrementar2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        editNumero1 = findViewById(R.id.editNumero1);
        editNumero2 = findViewById(R.id.editNumero2);

        btnIncrementar1 = findViewById(R.id.btnIncrementar1);
        btnIncrementar2 = findViewById(R.id.btnIncrementar2);

        btnIncrementar1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.d("APP DEBUG", "Clicked button 1");
                int valor = Integer.parseInt(editNumero1.getText().toString());
                editNumero1.setText(String.valueOf(valor + 1));
            }
        });

        btnIncrementar2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.d("APP DEBUG", "Clicked button 2");
                int valor = Integer.parseInt(editNumero2.getText().toString());
                editNumero2.setText(String.valueOf(valor + 1));
            }
        });
    }
}