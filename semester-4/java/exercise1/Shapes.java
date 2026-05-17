import java.util.Scanner;

class ThreeDShape {
  private String name;
  private double width;
  private double height;
  private double intensity;

  ThreeDShape(String name, double width, double height) {
    this.name = name;
    this.width = width;
    this.height = height;
    this.intensity = 0;
  }

  ThreeDShape(String name, double width, double height, double intensity) {
    this.name = name;
    this.width = width;
    this.height = height;
    this.intensity = intensity;
  }

  public String getName() {
    return this.name;
  }

  public double getWidth() {
    return this.width;
  }

  public double getHeight() {
    return this.height;
  }

  public double getintensity() {
    return this.intensity;
  }
}

class Sphere extends ThreeDShape {
  private double radius;

  Sphere(double radius) {
    super("Sphere", radius, radius * 2);
    this.radius = radius;
  }

  Sphere(double radius, double intensity) {
    super("Sphere", radius, radius * 2, intensity);
    this.radius = radius;
  }

  public double getRadius() {
    return this.radius;
  }

  public double getDiameter() {
    return this.getHeight();
  }

  public double getArea() {
    return 4 * Math.PI * this.radius * this.radius;
  }

  public double getVolume() {
    return 4f / 3 * Math.PI * this.radius * this.radius * this.radius;
  }

  public double getMass() {
    return this.getVolume() * this.getintensity();
  }
}

class Cylinder extends ThreeDShape {
  private double radius;

  Cylinder(double radius, double height) {
    super("Cylinder", radius, height);
    this.radius = radius;
  }

  Cylinder(double radius, double height, double intensity) {
    super("Cylinder", radius, height, intensity);
    this.radius = radius;
  }

  public double getRadius() {
    return this.radius;
  }

  public double getArea() {
    return (2 * Math.PI * this.radius) * (this.getHeight() + this.radius);
  }

  public double getVolume() {
    return Math.PI * this.radius * this.radius * this.getHeight();
  }

  public double getMass() {
    return this.getVolume() * this.getintensity();
  }
}

class Cone extends ThreeDShape {
  private double radius;

  Cone(double radius, double height) {
    super("Cone", radius, height);
    this.radius = radius;
  }

  Cone(double radius, double height, double intensity) {
    super("Cone", radius, height, intensity);
    this.radius = radius;
  }

  public double getRadius() {
    return this.radius;
  }

  public double getArea() {
    return (Math.PI * this.radius)
        * (Math.sqrt(Math.pow(this.radius, 2) + Math.pow(this.getHeight(), 2)) + this.radius);
  }

  public double getVolume() {
    return 1f / 3 * (Math.PI * this.radius * this.radius * this.getHeight());
  }

  public double getMass() {
    return this.getVolume() * this.getintensity();
  }
}

class Shapes {
  public static void main(String args[]) {
    Scanner scanner = new Scanner(System.in);
    boolean loop = true;

    while (loop) {
      System.out.print("Enter shape type: ");
      String type = scanner.next().toLowerCase();

      if (type.equals("sphere")) {
        System.out.print("Enter radius: ");
        double radius = scanner.nextDouble();
        System.out.print("Enter intensity: ");
        double intensity = scanner.nextDouble();
        Sphere sphere = new Sphere(radius, intensity);
        System.out.println("Area: " + sphere.getArea());
        System.out.println("Diameter: " + sphere.getArea());
        System.out.println("Volume: " + sphere.getVolume());
      } else if (type.equals("cylinder")) {

      } else if (type.equals("cone")) {

      } else {
        System.err.println("Unknown shape.");
      }

      System.out.print("Continue? (y/n): ");
      char answer = scanner.next().toLowerCase().charAt(0);

      if (answer != 'y') loop = false;
    }

    scanner.close();
  }
}
