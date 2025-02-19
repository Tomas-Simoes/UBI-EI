package exercice1;

import java.util.ArrayList;

public class main {

	public static void main(String[] args) {
		Disciplina d1 = new Disciplina(15395, "POO", 2);
		d1.setNotas(new double[] { 12, 16 });

		System.out.println(d1);

		try {
			d1.atribuirNota(-1, 20.);
		} catch (TesteException e) {
			System.out.println(e.getMessage());
		} catch (NotaException e) {
			System.out.println(e.getMessage());
		}

		System.out.println(d1);
		System.out.println("Media: " + d1.notaFinal());
	}

	public static int positivasCount(ArrayList<Estudante> estudantes) {
		int positivas = 0;

		for (Estudante estudante : estudantes) {
			for (Disciplina disciplina : estudante.disciplinas) {
				for (double nota : disciplina.getNotas()) {
					if (nota > 9.5) {
						positivas++;
					}
				}
			}
		}

		return positivas;
	}

	public static void doutoramentosCount(ArrayList<Estudante> estudantes) {
		int count = 0;

		for (Estudante estudante : estudantes) {
			if (estudante instanceof EstD) {
				count++;
			}
		}
	}
}
