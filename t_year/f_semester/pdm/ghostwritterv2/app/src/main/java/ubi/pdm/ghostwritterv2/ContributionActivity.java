package ubi.pdm.ghostwritterv2;

import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.textfield.TextInputEditText;

import java.util.List;

public class ContributionActivity extends AppCompatActivity {

    private Button btnAdd;
    private TextInputEditText inputArea;
    private TextView contributorsTextView;
    private Spinner authorsSpinner;
    private DBHelper db;

    private int numContributors = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_contribution);

        // Views
        btnAdd = findViewById(R.id.btnAdd);
        inputArea = findViewById(R.id.inputTextArea);
        contributorsTextView = findViewById(R.id.contributorsTextView);
        authorsSpinner = findViewById(R.id.authorsSpinner);

        // DBHelper
        db = new DBHelper(this);

        // Carregar autores no spinner
        updateAuthorsSpinner();

        // Número de contribuições recebido via intent
        numContributors = getIntent().getIntExtra("numContributors", 0);
        updateContributorsText();

        btnAdd.setOnClickListener(v -> {
            String newText = inputArea.getText().toString().trim();

            if (!newText.isEmpty()) {
                // Pega autor selecionado
                String authorName = (String) authorsSpinner.getSelectedItem();
                long userId = db.getUserIdByName(authorName);
                if (userId <= 0) {
                    // Autor não existe? Criar
                    userId = db.insertUser(authorName);
                }

                // Criar nova sessão com essa contribuição
                long sessionId = db.insertSession(
                        java.time.LocalDateTime.now().toString(), // date_iso
                        newText,
                        null // text_path
                );

                // Ligar sessão ao autor
                db.linkUsersToSession(sessionId, List.of(authorName));

                // Atualizar contador
                numContributors++;
                updateContributorsText();

                // Limpar input
                inputArea.setText("");
            }
        });
    }

    private void updateAuthorsSpinner() {
        List<String> authors = db.getAllUserNames();
        if (authors.isEmpty()) {
            // Se não houver autores ainda
            authors.add("Anonymous");
        }
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(
                this,
                android.R.layout.simple_spinner_item,
                authors
        ) {
            @Override
            public View getView(int position, View convertView, android.view.ViewGroup parent) {
                TextView v = (TextView) super.getView(position, convertView, parent);
                v.setTextColor(getResources().getColor(android.R.color.white, null));
                return v;
            }

            @Override
            public View getDropDownView(int position, View convertView, android.view.ViewGroup parent) {
                TextView v = (TextView) super.getDropDownView(position, convertView, parent);
                v.setTextColor(getResources().getColor(android.R.color.white, null));
                return v;
            }
        };
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        authorsSpinner.setAdapter(adapter);
    }

    private void updateContributorsText() {
        contributorsTextView.setText(String.format("%d ghostwriters have\ncontributed so far!", numContributors));
    }
}
