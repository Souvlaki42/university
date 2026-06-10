/**
 * This class computes the factorial of a series of positive integers provided by arguments
 *
 * @author Souvlaki42
 * @version 1.0
 */
public class Factorial {

  /**
   * This method computes the factorial of a positive integer recursively
   *
   * @param n the integer
   * @return n!
   */
  public static long factor(int n) {
    if (n == 0) return 0; // if n is 0 return 0
    if (n == 1) return 1; // if n is 1 return 1

    // else return n multiplied by the factorial of the previous integer
    return factor(n - 1) * n;
  }

  /**
   * This is the main method.
   *
   * @param args Unused.
   */
  public static void main(String[] args) {
    long sum = 0; // the sum of factorials

    // printing the header
    if (args.length > 0) System.out.println("Results:");
    else System.out.println("No results");

    for (int i = 0; i < args.length; i++) {
      try {
        // parse every argument as an integer
        int num = Integer.parseInt(args[i]);
        // throw exception if parsed argument is negative
        if (num < 0) {
          throw new NumberFormatException("negative number");
        }
        // calculate the number's factorial
        long factorial = factor(num);
        // increase sum by computed factorial
        sum += factorial;
        // print the results
        System.out.println(
          "Number: " + num + "   Factorial: " + factorial + "    Sum:    " + sum
        );
      } catch (NumberFormatException e) {
        // handle the exceptions above by printing an error message
        System.err.println(
          "Argument passed is not a positive integer: " + args[i]
        );
      }
    }
  }
}
