package class07;

import java.util.ArrayList;

public class AlunoLicenciatura extends Aluno {
	private String curso;
	private ArrayList<Disciplina> disciplinas;
	private Aluno aluno;

	public AlunoLicenciatura(Aluno aluno, String curso) {
		super(aluno.getNumero(), aluno.getNome());
		this.curso = curso;
	}

	public ArrayList<Disciplina> getDisciplinas() {
		return disciplinas;
	}

	public void setDisciplinas(ArrayList<Disciplina> disciplinas) {
		for (Disciplina disciplina : disciplinas) {
			this.disciplinas.add(disciplina);
		}
	}

	public String getCurso() {
		return curso;
	}

	public void setCurso(String curso) {
		this.curso = curso;
	}

	public void addDisciplina(Disciplina disciplina) {
		if (!disciplinas.contains(disciplina)) {
			disciplinas.add(disciplina);
		}
	}

	public int getNotaDisciplina(int codigo) {
		for (Disciplina disciplina : disciplinas) {
			if (disciplina.getCodigo() == codigo) {
				return disciplina.getNota();
			}
		}

		return -1;
	}

	public int getMedia() {
		int soma = 0;

		for (Disciplina disciplina : disciplinas) {
			soma += disciplina.getNota();
		}

		return soma / disciplinas.size();
	}
}
