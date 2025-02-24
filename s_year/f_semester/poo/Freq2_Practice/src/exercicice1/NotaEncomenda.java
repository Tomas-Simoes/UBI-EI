package exercicice1;

import java.util.ArrayList;

public class NotaEncomenda {
	private static int ultimoNumero = 0;
	private int numeroEncomenda;
	private int numeroContribuinte;
	private ArrayList<Produto> produtos;

	public NotaEncomenda(int numeroContribuinte) {
		ultimoNumero++;
		this.numeroEncomenda = ultimoNumero;
		this.numeroContribuinte = numeroContribuinte;
	}

	public void addProduto(Produto produto) {
		if (!produtos.contains(produto)) {
			produtos.add(produto);
		}
	}
}
