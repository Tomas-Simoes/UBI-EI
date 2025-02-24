package class06;

public class testClass {

	public static void main(String[] args) {
		Disciplina poo = new Disciplina(1000, "POO", "Paula Prata");
		Disciplina ia = new Disciplina(2000, "IA", "Luís Alexandre");
		Disciplina multimedia = new Disciplina(3000, "Multimédia", "Manuela Pereira");
		Disciplina pe = new Disciplina(4000, "Probabilidade e Estatistica", "João Duque");

		Aluno aluno1 = new Aluno("Manuel Silva", new Disciplina[] { poo, ia, multimedia });
		Aluno aluno2 = new Aluno("Maria Espinho", new Disciplina[] { poo, pe });

		System.out.println(aluno1.toString());
		System.out.println(aluno2.toString());

		aluno2.addDisciplina(multimedia, 1);
		System.out.println(aluno2.toString());

		aluno1.setNome("Carlinhos");
		System.out.println(aluno1.toString());
	}

}
