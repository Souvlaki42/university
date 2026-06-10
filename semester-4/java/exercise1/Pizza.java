/**
 * This class defines and prints the description and price of a pizza.
 *
 * @author Souvlaki42
 * @version 1.0
 */
public class Pizza {

  // pizza description
  String descr;

  // pizza price
  double price;

  /**
   * Parameterized constructor.
   *
   * @param descr pizza description
   * @param price pizza price
   */
  public Pizza(String descr, double price) {
    this.descr = descr;
    this.price = price;
  }

  /** This method prints the details of the pizza to stdout. */
  public void print() {
    System.out.println(
      "This pizza is " + this.descr + " and costs " + this.price + " euros"
    );
  }
}
