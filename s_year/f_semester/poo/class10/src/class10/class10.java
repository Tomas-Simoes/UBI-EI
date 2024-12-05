package class10;

public class class10 {
	public static void main(String[] args) {
		int i;

	}

	public static int verifyNumber(int i, int upper, int lower) throws Exception {
		if (lower < i && i < upper) {
			return i;
		} else {

			throw new Exception("Erro, o valor não está entre " + lower + " e " + upper + ".");
		}
	}
}
