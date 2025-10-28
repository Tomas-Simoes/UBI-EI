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

import java.util.List;

public class AuthorsActivity extends AppCompatActivity {
    private Button btnAddAuthors;
    private TextView authorsView;
    private TextInputEditText inputAuthor;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_authors);

        btnAddAuthors = findViewById(R.id.btnAddAuthor);
        inputAuthor = findViewById(R.id.inputAuthor);
        authorsView = findViewById(R.id.authorsView);

        DBHelper db = new DBHelper(this);

        List<String> authors = db.getAllUserNames();
        if(!authors.isEmpty()) {
            authorsView.setText("");
        }

        int i = 1;
        for (String author : authors) {
            authorsView.append("Author " + i + ": " + author + "\n");
            i++;
        }

        btnAddAuthors.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String newAuthor = inputAuthor.getText().toString();

                long id = db.insertUser(newAuthor);
                if(id > 0) authorsView.append("Author " + id + ": " + newAuthor + "\n");
            }
        });


    }
}