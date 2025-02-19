package class11;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.ArrayList;

public class class11 {
	private static ArrayList<Aluno> alunos = new ArrayList<Aluno>();

	public static void main(String[] args) {

		try {
			ObjectInputStream in = new ObjectInputStream(new FileInputStream("src/class11/fichAlunos"));
			alunos = (ArrayList<Aluno>) in.readObject();
		} catch (IOException e) {
			System.out.println(e.getMessage());
		} catch (ClassNotFoundException e) {
			System.out.println(e.getMessage());
		}
	}

	public Aluno createAluno(String name) {
		Aluno newAluno = new Aluno(name);
		alunos.add(newAluno);

		return newAluno;
	}

	public Aluno getAluno(int num) {
		for (Aluno aluno : alunos) {
			if (aluno.getNumero() == num) {
				return aluno;
			}
		}

		return null;
	}

	public Aluno getAluno(String name) {
		for (Aluno aluno : alunos) {
			if (aluno.getNome() == name) {
				return aluno;
			}
		}

		return null;
	}

	public String listAlunos() {
		String res = "";

		for (Aluno aluno : alunos) {
			res += "Aluno " + aluno.getNome();
		}

		return res;
	}

	public void removeAluno(int num) {
		for (Aluno aluno : alunos) {
			if (aluno.getNumero() == num) {
				alunos.remove(aluno);
			}
		}
	}

	public void changeName(int num, String nome) {
		for (Aluno aluno : alunos) {
			if (aluno.getNumero() == num) {
				aluno.setNome(nome);
				;
			}
		}
	}
}
