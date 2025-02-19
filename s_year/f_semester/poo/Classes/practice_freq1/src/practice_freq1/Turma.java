package practice_freq1;

import java.util.ArrayList;

public class Turma {
	private static int ultima = 0;
	private int numero;
	private String nome;
	private ArrayList<String> alunos;
	private int[] horario;

	public Turma() {
		numero = 0;
		nome = "";
		alunos = new ArrayList<String>(0);
		horario = new int[0];
	}

	public Turma(String nome) {
		this.nome = nome;
		numero = 0;
		alunos = new ArrayList<String>(0);
		horario = new int[0];
	}

	public int getNumero() {
		return numero;
	}

	public String getNome() {
		return nome;
	}

	public ArrayList<String> getAlunos() {
		return alunos;
	}

	public int[] getHorario() {
		return horario;
	}

	public void setNumero(int numero) {
		this.numero = numero;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public void setAlunos(ArrayList<String> alunos) {
		this.alunos = alunos;
	}

	public void setHorario(int[] horario) {
		this.horario = horario;
	}

	public String toString() {
		String turmaString = "Turma " + numero + " (" + nome + ")\nAlunos: ";

		for (String aluno : alunos) {
			turmaString += aluno + " ";
		}

		return turmaString;
	}

	public void addAluno(String aluno) {
		alunos.add(aluno);
	}

	public boolean checkAluno(String aluno) {
		return alunos.contains(aluno);
	}

	public int checkHorario() {
		int min = horario[0];

		for (int horas : horario) {
			min = horas <= min ? horas : min;
		}

		return min;
	}

	@Override
	public boolean equals(Object o) {
		if (this == o) {
			return true;
		}

		if (o == null) {
			return false;
		}

		Turma turma = (Turma) o;
		return this.nome == turma.nome && this.alunos == turma.alunos && this.numero == turma.numero
				&& this.horario == turma.horario;
	}

	@Override
	protected Object clone() {
		try {
			return super.clone();
		} catch (CloneNotSupportedException cnse) {
			cnse.printStackTrace();
			return null;
		}
	}

}
