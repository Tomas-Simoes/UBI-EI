package class12;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.util.ArrayList;

public class FuncLivros {

	public static void inserirLivro(ArrayList<Livro> livros) {
		System.out.println("Qual o número do Livro? ");
		int num = Ler.umInt();

		// validar número de livro
		for (int i = 0; i < livros.size(); i++) {
			if (livros.get(i).getId() == num) {
				System.out.println("Já existe um livro com esse número");
				return;
			}
		}
		// obter dados do livro; instanciar o objeto Livro;
		System.out.println("Qual o nome do Livro? ");
		String nome = Ler.umaString();
		System.out.println("Qual o autor do Livro? ");
		String autor = Ler.umaString();
		Livro l = new Livro(num, nome, autor);

		// adicionar o novo livro à lista
		livros.add(l);
		// atualizar ficheiro
		try {
			ObjectOutputStream os = new ObjectOutputStream(new FileOutputStream("d:\\teste\\livros.dat"));
			// escrever o objeto livros no ficheiro
			os.writeObject(livros);
			os.flush(); // os dados são copiados de memória para o disco
		} catch (IOException e) {
			System.out.println(e.getMessage());
		}
	}
}
