package class002;

public class fixTheCode {
	public static void main(String[] args) {
		int numero;
		int p[] = new int[2];
		Double decNum, rD;
		numero = -100000;
		decNum = 12345.6789;
		System.out.println("O valor da variável inteira é: " + numero);
		System.out.println("O valor da variável real é: " + decNum);
		char letra = 'A';
		System.out.println( letra);
		letra = 65;
		System.out.println( letra);
		letra = 'a';
		System.out.println( letra);
		Double z = -1.0;
		float x = 12.5f, y=3E30F, zero, rF;
		short xpto = -130, sht=9, rS;
		long lng=0xEFFFFF, rL;
		System.out.println(lng);
		rL = lng *10; System.out.println("rL: " + rL);
		rF = lng + 1; System.out.println("rF: " + rF);
		System.out.println("rF: " + rF);
		rF = 0/0; System.out.println("rF: " + rF);
		rF = sht + b * y * x * lng; System.out.println("rF: " + rF);
		rD = - b * (sht + zero + x * lng + y * decNum * - numero / letra);
		System.out.println("rD: " + rD );
		rD* = 1E269;
		System.out.println("rD: " + rD );

	}
}
