/**
 * This class extends Pizza but includes the delivery details
 *
 * @author Souvlaki42
 * @version 1.0
 * @see Pizza
 */
public class DeliveryPizza extends Pizza {

  // The cost of the delivery
  double deliveryCost;
  // The address the pizza should be delivered to
  String deliveryAddress;

  /**
   * Parameterized constructor.
   *
   * @param descr pizza description
   * @param price pizza price
   * @param deriveryAdress address for the delivery
   */
  public DeliveryPizza(String descr, double price, String deriveryAdress) {
    super(descr, price);
    this.deliveryAddress = deriveryAdress;
    this.deliveryCost = price > 15 ? 3 : 5;
  }
}
