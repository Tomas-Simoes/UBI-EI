package class08;

import java.util.ArrayList;

public class EmpregadosManager {
	private ArrayList<Empregado> empregados;

	public EmpregadosManager() {
		empregados = new ArrayList<Empregado>();
	}

	public Empregado createEmpregado(int socialSecurity, String name, int salary) {
		Empregado newEmpregado = new Empregado(socialSecurity, name, salary);
		empregados.add(newEmpregado);

		return newEmpregado;
	}

	public String getEmpregados() {
		String empregadosString = "";

		for (Empregado empregado : empregados) {
			empregadosString += empregado.toString() + "\n";
		}

		return empregadosString;
	}

	public void deleteEmpregado(Empregado empregado) {
		empregados.remove(empregado);
	}

	public void deleteEmpregado(String name) {
		for (Empregado empregado : empregados) {
			if (empregado.getName() == name) {
				empregados.remove(empregado);
			}
		}
	}

	public void modifyEmpregado(Empregado empregado, Integer socialSecurity, String name, Integer salary) {
		if (socialSecurity != null) {
			empregado.setSocialSecurity((int) socialSecurity);
		}

		if (name != null) {
			empregado.setName(name);
		}

		if (salary != null) {
			empregado.setSalary((int) salary);
		}
	}

	public int getTotalSalary() {
		int totalSalary = 0;

		for (Empregado empregado : empregados) {
			totalSalary += empregado.getSalary();
		}

		return totalSalary;
	}

	public ArrayList<Empregado> withoutFixedPhone() {
		ArrayList<Empregado> thisEmpregados = new ArrayList<Empregado>();

		for (Empregado empregado : empregados) {
			thisEmpregados.add(empregado);
			for (Telefone contact : empregado.getContacts()) {
				if (contact.getTipo() == "Fixo") {
					thisEmpregados.remove(empregado);
				}
			}
		}

		return thisEmpregados;
	}

}
