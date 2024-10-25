package class06;

public class Disciplina {
	private int codigo;
	private String nome;
	private String prof;

	public Disciplina() {
		codigo = 0;
		nome = "";
		prof = "";
	}

	public Disciplina(int codigo, String nome, String prof) {
		this.codigo = codigo;
		this.nome = nome;
		this.prof = prof;
	}

	public int getCodigo() {
		return this.codigo;
	}

	public String getNome() {
		return this.nome;
	}
}
