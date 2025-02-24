package exercice1;

public class EstD extends Estudante {
	private String tema;
	private String orientador;

	public EstD(Estudante estudante, String tema, String orientador) {
		super(estudante.nome);

		this.disciplinas = estudante.disciplinas;

		this.tema = tema;
		this.orientador = orientador;

	}

	public int numeroDisciplinas() {
		return this.disciplinas.size();
	}
}
