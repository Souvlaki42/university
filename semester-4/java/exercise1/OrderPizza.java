/**
 * This class demonstrates the methods of the Pizza and DeliveryPizza classes.
 *
 * @author Souvlaki42
 * @version 1.0
 * @see Pizza
 * @see DeliveryPizza
 */
public class OrderPizza {

  /**
   * This is the main method.
   *
   * @param args Unused.
   */
  public static void main(String[] args) {
    // A margarita pizza
    Pizza margarita = new Pizza("a pizza margaritta", 9.5);
    // A special pizza
    Pizza special = new Pizza("a special pizza", 18);

    // Delivery details for margarita pizza
    DeliveryPizza margaritaDelivery = new DeliveryPizza(
      margarita.descr,
      margarita.price,
      "Aiolou 12"
    );

    // Delivery details for special pizza
    DeliveryPizza specialDelivery = new DeliveryPizza(
      special.descr,
      special.price,
      "Maraphonos 25"
    );

    // Printing the details of margarita pizza
    margaritaDelivery.print();
    System.out.println(
      "The pizza will be delivered to " +
        margaritaDelivery.deliveryAddress +
        " and the delivery will cost " +
        margaritaDelivery.deliveryCost +
        " euros"
    );

    // Printing the details of special pizza
    specialDelivery.print();
    System.out.println(
      "The pizza will be delivered to " +
        specialDelivery.deliveryAddress +
        " and the delivery will cost " +
        specialDelivery.deliveryCost +
        " euros"
    );
  }
}
