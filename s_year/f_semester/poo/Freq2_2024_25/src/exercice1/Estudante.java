package exercice1;

import java.util.ArrayList;

public class Estudante {
	private static int lastNum = 0;
	public String nome;
	public int numero;
	public ArrayList<Disciplina> disciplinas;

	public Estudante(String nome) {
		lastNum++;
		this.numero = lastNum;
		this.nome = nome;
	}

	@Override
	public String toString() {
		return String.format("Estudante %s (%d) com notas: %s", nome, numero, disciplinas.toString());
	}

	public void addDisciplina(Disciplina d) {
		if (!disciplinas.contains(d)) {
			disciplinas.add(d);
		}
	}

	public void removeDisciplina(int cod) {
		for (Disciplina disciplina : disciplinas) {
			if (disciplina.getCod() == cod) {
				disciplinas.remove(disciplina);
			}
		}
	}

	public void mediaAluno() {
		int sum = 0;

		for (Disciplina disciplina : disciplinas) {
			// sum += disciplina.getNotas()
		}
	}
}
