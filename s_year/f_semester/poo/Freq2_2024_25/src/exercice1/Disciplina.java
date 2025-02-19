package exercice1;

import java.util.Arrays;

public class Disciplina {
	private int cod;
	private String nome;
	private double[] notas;

	public Disciplina(int cod, String nome, int numNotas) {
		this.cod = cod;
		this.nome = nome;
		notas = new double[numNotas];
	}

	public double[] getNotas() {
		return notas;
	}

	public void setNotas(double[] notas) {
		this.notas = notas;
	}

	public int getCod() {
		return cod;
	}

	public void setCod(int cod) {
		this.cod = cod;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	@Override
	public String toString() {
		return String.format("Disciplina %s (%d) com notas: %s", nome, cod, Arrays.toString(notas));
	}

	@Override
	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		Disciplina objDisciplina = (Disciplina) obj;

		return objDisciplina.cod == this.cod && objDisciplina.nome == this.nome
				&& Arrays.equals(this.notas, objDisciplina.notas);
	}

	public Object clone() {
		return new Disciplina(this.cod, this.nome, notas.length);
	}

	public void atribuirNota(int numero, double nota) throws TesteException, NotaException {

		if (numero <= 0 || numero > notas.length) {
			throw new TesteException("Posicao " + numero + " nao e uma nota valida");
		}

		if (nota < 0 || nota > 20) {
			throw new NotaException(nota + " nao e uma nota valida");
		}

		notas[numero - 1] = nota;
	}

	public double notaFinal() {
		double sum = 0;

		for (double nota : notas) {
			sum += nota;
		}

		return sum / notas.length;
	}
}

class TesteException extends Exception {
	public TesteException() {
		super();
	}

	public TesteException(String msg) {
		super(msg);
	}
}

class NotaException extends Exception {
	public NotaException() {
		super();
	}

	public NotaException(String msg) {
		super(msg);
	}
}
