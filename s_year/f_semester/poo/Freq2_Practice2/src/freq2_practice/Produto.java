package freq2_practice;

public class Produto {
	private int cod;
	private String nome;
	private double custo;

	public Produto(int cod, String nome) {
		this.cod = cod;
		this.nome = nome;
		this.custo = 0.0;
	}

	@Override
	public String toString() {
		return String.format("Produto %s (%d): %f€", nome, cod, custo);
	}

	@Override
	public boolean equals(Object obj) {
		if (obj == null || this.getClass() != obj.getClass()) {
			return false;
		}

		Produto produto = (Produto) obj;
		return this.cod == produto.cod && this.nome == produto.nome && this.custo == produto.custo;
	}

	public Object clone() {
		Produto produto = new Produto(this.cod, this.nome);
		produto.custo = this.custo;

		return produto;
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

	public double getCusto() {
		return custo;
	}

	public void setCusto(double custo) {
		this.custo = custo;
	}

	public void raiseCusto(float raise) throws ValorException {
		if (raise <= 0 || raise > 100) {
			throw new ValorException("O valor de aumento tem de estar entre 0 e 100");
		}

		this.setCusto(custo + (custo * (raise / 100)));
	}
}

class ValorException extends Exception {
	public ValorException() {
		super();
	}

	public ValorException(String errorMessage) {
		super(errorMessage);
	}
}
