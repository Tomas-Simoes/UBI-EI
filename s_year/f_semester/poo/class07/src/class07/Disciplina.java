package class07;

public class Disciplina {
	private int codigo;
	private String nome;
	private int nota;

	public Disciplina() {
		codigo = 0;
		nota = 0;
		nome = "";
	}

	public Disciplina(int codigo, String nome) {
		this.codigo = codigo;
		this.nome = nome;
	}

	public Disciplina(Disciplina d) {
		this.codigo = d.codigo;
		this.nome = d.nome;
	}

	public int getCodigo() {
		return codigo;
	}

	public void setCodigo(int codigo) {
		this.codigo = codigo;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public int getNota() {
		return nota;
	}

	public void setNota(int nota) {
		this.nota = nota;
	}
}
