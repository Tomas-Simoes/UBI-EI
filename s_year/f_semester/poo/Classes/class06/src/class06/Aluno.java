package class06;

public class Aluno {
	private static int ultimo = 0;
	private int numero;
	private String nome;
	private Disciplina[] lista;

	public Aluno() {
		nome = "";
		lista = new Disciplina[3];
	}

	public Aluno(String nome, Disciplina[] lista) {
		this.nome = nome;
		this.lista = lista;
		this.numero = ultimo++;
	}

	public String getNome() {
		return this.nome;
	}

	public Disciplina[] getLista() {
		return this.lista;
	}

	public int getNumero() {
		return this.numero;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public void setDisciplina(Disciplina[] lista) {
		this.lista = lista;
	}

	public void addDisciplina(Disciplina d, int p) {
		this.lista[p] = d;
	}

	public boolean checkDisciplina(Disciplina d) {
		for (Disciplina disciplina : lista) {
			if (d.getCodigo() == disciplina.getCodigo()) {
				return true;
			}
		}

		return false;
	}

	public String toString() {
		String _disciplinas = "";
		for (Disciplina d : lista) {
			_disciplinas += d.getNome() + " ";
		}
		return "Aluno " + nome + ": Nº" + numero + " com disciplinas " + _disciplinas;
	}

}
