package class12;

import java.io.Serializable;

public class Livro implements Serializable {
	private int id;
	private String titulo;
	private String autor;

	public Livro(int id, String titulo, String autor) {
		this.id = id;
		this.titulo = titulo;
		this.autor = autor;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getTitulo() {
		return titulo;
	}

	public void setTitulo(String titulo) {
		this.titulo = titulo;
	}

	public String getAutor() {
		return autor;
	}

	public void setAutor(String autor) {
		this.autor = autor;
	}

	@Override
	public String toString() {
		return "Livro{" + "id=" + id + ", titulo=" + titulo + ", autor=" + autor + '}';
	}

	public boolean equals(Object obj) {
		if (obj != null && this.getClass() == obj.getClass()) {
			Livro li = (Livro) obj;
			return this.id == li.id && this.autor.equals(li.autor) && this.titulo.equals(li.titulo);
		}
		return false;
	}

	public Object clone() {
		Livro copia = new Livro(this.id, this.titulo, this.autor);
		return copia;
	}
}
