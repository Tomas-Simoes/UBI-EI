package practice_freq1;

public class main {
	/*
	 * 1) Variável de instância é uma variável de uma classe que todos os objetos
	 * que pertencem a essa classe têm uma copia com o seu propio valor.
	 * 
	 * Variavel de classe é uma variavel que pertence em si há classe e é comum a
	 * todos os objetos da classe.
	 * 
	 * 2) Os modificadores de acesso é o que diz se podemos ou não aceder uma
	 * variável. Tecnicas como o encapsulamento fazem esse trabalho.
	 */

	public static void main(String[] args) {
		Turma ta, tb, tc;
		ta = new Turma("EI");
		tb = new Turma("InfoWeb");
		tc = (Turma) ta.clone();
		System.out.println(ta == tc);
		System.out.println(tb);
		ta = tb;
		System.out.println(ta.toString());
	}

}
