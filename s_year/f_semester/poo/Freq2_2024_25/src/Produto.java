
public class Produto {
	private int cod;
	private String nome;
	private double custo;

	public Produto(int cod, String nome) {
		this.cod = cod;
		this.nome = nome;
		this.custo = 0.0;
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

	@Override
	public String toString() {
		return String.format("Produto %s (%d) com custo %f", nome, cod, custo);
	}

	@Override
	public boolean equals(Object obj) {
		if (obj == null || obj.getClass() != this.getClass()) {
			return false;
		}

		Produto prod = (Produto) obj;

		return this.cod == prod.getCod() && this.nome == prod.getNome() && this.custo == prod.getCusto();

	}

	public Object clone() {
		Produto prod = new Produto(this.cod, this.nome);
		prod.setCusto(this.custo);

		return prod;
	}

	public void raiseCusto(int raise) throws ValorException {
		if (raise <= 0 && raise >= 100) {
			throw new ValorException("o valor " + raise + "deve ser maior que 0 e menor que 100");
		}

		this.setCusto(custo + (custo * (raise / 100)));
	}
}

class ValorException extends Exception {
	public ValorException() {
		super();
	}

	public ValorException(String msg) {
		super(msg);
	}
}