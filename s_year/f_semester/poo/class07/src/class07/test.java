package class07;

public class test {
	public static int getAlunosLICount(Aluno[] alunos) {
		int count = 0;

		for (Aluno aluno : alunos) {
			if (aluno instanceof AlunoLicenciatura) {
				count++;
			}
		}

		return count;
	}
}
