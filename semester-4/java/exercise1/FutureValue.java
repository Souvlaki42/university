import java.util.Scanner;

class FutureValue {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    boolean loop = true;

    while (loop) {
      double total = 0;

      System.out.print("Enter monthly investment: ");
      double investment = scanner.nextDouble();

      System.out.print("Enter yearly interest rate: ");
      double interest = scanner.nextDouble();

      System.out.print("Enter number of years: ");
      int years = scanner.nextInt();

      for (int i = 0; i < years * 12; i++) {
        total += investment;
        total *= (1 + ((interest / 100) / 12));
      }

      System.out.println("Future value: " + String.format("%.2f", total) + " €");

      System.out.print("Continue? (y/n): ");
      char answer = scanner.next().charAt(0);

      if (answer != 'y') loop = false;
    }

    scanner.close();
  }
}
