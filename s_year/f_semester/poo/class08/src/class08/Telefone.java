package class08;

public class Telefone {
	private String tipo; // Casa | Emprego | Móvel | ...
	private int numero;

	public Telefone() {
		this.tipo = "";
		this.numero = 0;
	}

	public Telefone(String tipo, int numero) {
		this.tipo = tipo;
		this.numero = numero;
	}

	public String getTipo() {
		return tipo;
	}

	public int getNumero() {
		return numero;
	}

	public void setTipo(String tipo) {
		this.tipo = tipo;
		// tipo é uma variável local ao método
	}

	public void setNumero(int numero) {
		this.numero = numero;
	}

	public String toString() {
		String s = "Tipo: " + tipo + " Número: " + numero;
		return s;
	}

	public boolean equals(Object obj) {
		return this.equals(obj);
	}

	public Telefone clone() {
		return this;
	}

}
