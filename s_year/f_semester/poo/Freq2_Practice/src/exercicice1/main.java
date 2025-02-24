package exercicice1;

public class main {

	public static void main(String[] args) {
		Produto p1, p2, p3;
		p1 = new Produto(1, "Produto1");
		p2 = (Produto) p1.clone();
		p3 = p2;
		p1.setCusto(100);
		p2.setCusto(500);
		p3.setCusto(700);
		System.out.println(p1 == p2);
		System.out.println(p2 == p3);
		System.out.println(p1.equals(p2));
		System.out.println(p2.equals(p3));
		System.out.println(p2);

		try {
			p2.raiseCusto(20);
		} catch (ValorException e) {
			e.getMessage();
		}
	}

}
