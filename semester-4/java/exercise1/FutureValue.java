import java.util.Scanner;

/**
 * This class calculates the expected return of a monthly investment with stable interest rates over
 * a period.
 *
 * @author Souvlaki42
 * @version 1.0
 */
public class FutureValue {

  /**
   * This is the main method.
   *
   * @param args Unused.
   */
  // scanner instance reading from stdin
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);

    while (true) {
      // infinite loop
      double total = 0; // this is the expected return value

      // Asking for the monthly investment in euros
      System.out.print("Enter monthly investment: ");
      double investment = scanner.nextDouble();

      // Asking for the interest rate per year
      System.out.print("Enter yearly interest rate: ");
      double interest = scanner.nextDouble();

      // Asking for the numbers of years the investment will compound for
      System.out.print("Enter number of years: ");
      int years = scanner.nextInt();

      // Calculate the result in monthly compounds
      for (int i = 0; i < years * 12; i++) {
        total += investment; // increasing result by monthly investment
        total *= (1 + ((interest / 100) / 12)); // increasing result by interest rate percentage
      }

      // Printing the expected return
      System.out.println(
        "Future value: " + String.format("%.2f", total) + " €"
      );

      // Asking whenever to continue the loop or not
      System.out.print("Continue? (y/n): ");
      char answer = scanner.next().toLowerCase().charAt(0);

      // breaking the loop if the answer is anything other than yes
      if (answer != 'y') break;
    }

    // terminating the scanner of stdin
    scanner.close();
  }
}
