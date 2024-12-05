package class08;

import java.util.ArrayList;

public class Empregado {
	private int socialSecurity;
	private String name;
	private int salary;
	private ArrayList<Telefone> contacts;

	public Empregado() {
		socialSecurity = 0;
		name = "";
		salary = 0;
		contacts = new ArrayList<Telefone>();
	}

	public Empregado(int socialSecurity, String name, int salary) {
		this.socialSecurity = socialSecurity;
		this.name = name;
		this.salary = salary;
		contacts = new ArrayList<Telefone>();

	}

	public int getSocialSecurity() {
		return socialSecurity;
	}

	public void setSocialSecurity(int socialSecurity) {
		this.socialSecurity = socialSecurity;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getSalary() {
		return salary;
	}

	public void setSalary(int salary) {
		this.salary = salary;
	}

	public ArrayList<Telefone> getContacts() {
		return contacts;
	}

	public void setContacts(ArrayList<Telefone> contacts) {
		this.contacts = contacts;
	}

	public void addSalary(float raise) {
		this.salary += (salary * raise);
	}

	public void addContact(Telefone contact) {
		if (!this.contacts.contains(contact)) {
			this.contacts.add(contact);
		}
	}

	public int searchContact(String type) {
		for (Telefone contact : contacts) {
			if (contact.getTipo() == type) {
				return contact.getNumero();
			}
		}

		return -1;
	}

}
