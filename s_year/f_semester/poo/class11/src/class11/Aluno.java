package class11;

import java.io.Serializable;

public class Aluno implements Serializable {
	private static int ultimo = 0;
	private int numero;
	private String nome;

	public Aluno(String n) {
		ultimo++;
		numero = ultimo;
		nome = n;
	}

	public static int getUltimo() {
		return ultimo;
	}

	public static void setUltimo(int ultimo) {
		Aluno.ultimo = ultimo;
	}

	public void setNome(String n) {
		nome = n;
	}

	public String getNome() {
		return nome;
	}

	public int getNumero() {
		return numero;
	}

	public String toString() {
		return "Aluno nº: " + numero + "\t Nome: " + nome;
	}
}
