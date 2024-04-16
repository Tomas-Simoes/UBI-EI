import java.util.Random;

public class Programa{
  public static void main(String args[]){
    Random oR = new Random(105);
    int random = oR.nextInt();
    System.out.println( random > 0 ? random : -random );
  }
}
