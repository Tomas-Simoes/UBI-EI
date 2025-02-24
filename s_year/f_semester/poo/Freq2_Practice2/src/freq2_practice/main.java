package freq2_practice;

import java.util.ArrayList;

public class main {

	public static void main(String[] args) {

	}

	public static ArrayList<String> cheapestProduct(ArrayList<Produto> produtos) {
		double min;
		ArrayList<String> nomes = new ArrayList<String>();

		min = produtos.get(0).getCusto();

		for (Produto produto : produtos) {
			if (min == produto.getCusto()) {
				nomes.add(produto.getNome());
			}

			if (min > produto.getCusto()) {
				nomes.clear();

				min = produto.getCusto();
				nomes.add(produto.getNome());
			}
		}

		return nomes;
	}
}
