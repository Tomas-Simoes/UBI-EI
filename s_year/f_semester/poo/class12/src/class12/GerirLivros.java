package class12;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.ArrayList;

public class GerirLivros {

	public static int menu() { // função na classe do main
		int opcao;
		System.out.println("1 - Novo livro");
		System.out.println("2 - Listar livros");
		System.out.println("3 - Apagar livro");
		System.out.println("4 - Consultar livro dado título");
		System.out.println("5 - Alterar título livro");
		System.out.println("6 – Qual o autor com mais livros");
		System.out.println("7 - Sair");
		System.out.println("Qual a sua opção:");
		opcao = Ler.umInt();
		return opcao;
	}

	public static void main(String[] args) {
		int escolha;
		ArrayList<Livro> meusLivros = new ArrayList<Livro>();

		try {
			ObjectInputStream is = new ObjectInputStream(new FileInputStream("d:\\teste\\livros.dat"));
			meusLivros = (ArrayList<Livro>) is.readObject();
		} catch (IOException e) {
			System.out.println(e.getMessage());
		} catch (ClassNotFoundException e) {
			System.out.println(e.getMessage());
		}
		do {
			escolha = menu();
			switch (escolha) {
			case 1:
				FuncLivros.inserirLivro(meusLivros);
				break;
			case 2:
				System.out.println(meusLivros);
				break;
			case 3:
			case 4:
			case 5:
			case 6:
			}
		} while (escolha != 7);
	}
}