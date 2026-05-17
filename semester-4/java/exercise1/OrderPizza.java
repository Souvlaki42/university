class Pizza {
  String descr;
  double price;

  public Pizza(String descr, double price) {
    this.descr = descr;
    this.price = price;
  }

  public void print() {
    System.out.println("This pizza is " + this.descr + " and costs " + this.price + " euros");
  }
}

class DeliveryPizza extends Pizza {
  double deliveryCost;
  String deliveryAddress;

  public DeliveryPizza(String descr, double price, String deriveryAdress) {
    super(descr, price);
    this.deliveryAddress = deriveryAdress;
    this.deliveryCost = price > 15 ? 3 : 5;
  }
}

class OrderPizza {
  public static void main(String[] args) {
    Pizza margarita = new Pizza("a pizza margaritta", 9.5);
    Pizza special = new Pizza("a special pizza", 18);

    DeliveryPizza margaritaDelivery =
        new DeliveryPizza(margarita.descr, margarita.price, "Aiolou 12");
    DeliveryPizza specialDelivery =
        new DeliveryPizza(special.descr, special.price, "Maraphonos 25");

    margaritaDelivery.print();
    System.out.println(
        "The pizza will be delivered to "
            + margaritaDelivery.deliveryAddress
            + " and the delivery will cost "
            + margaritaDelivery.deliveryCost
            + " euros");

    specialDelivery.print();
    System.out.println(
        "The pizza will be delivered to "
            + specialDelivery.deliveryAddress
            + " and the delivery will cost "
            + specialDelivery.deliveryCost
            + " euros");
  }
}
