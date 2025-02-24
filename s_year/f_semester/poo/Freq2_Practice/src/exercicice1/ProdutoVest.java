package exercicice1;

public class ProdutoVest extends Produto {
	private char genero;
	private int tamanho;

	public ProdutoVest(int cod, String nome, int custo, char genero, int tamanho) {
		super(cod, nome);
		super.setCusto(custo);

		this.genero = ' ';
		this.tamanho = 0;
	}

	public ProdutoVest(Produto produto) {
		super(produto.getCod(), produto.getNome());
		super.setCusto(produto.getCusto());

		this.genero = ' ';
		this.tamanho = 0;
	}

}
