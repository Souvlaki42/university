/**
 * This class represents a cylinder
 *
 * @author Souvlaki42
 * @version 1.0
 * @see ThreeDShape
 */
public class Cylinder extends ThreeDShape {

  /**
   * Constructor with radius and height
   *
   * @param radius radius
   * @param height height
   */
  Cylinder(double radius, double height) {
    super("Cylinder", radius, height, 0, 0);
  }

  /**
   * Construct with all params
   *
   * @param radius radius
   * @param height height
   * @param density density
   */
  Cylinder(double radius, double height, double density) {
    super("Cylinder", radius, height, 0, density);
  }

  /**
   * Method that returns radius
   *
   * @return radius
   */
  public double getRadius() {
    return this.x;
  }

  /**
   * Method that returns height
   *
   * @return height
   */
  public double getHeight() {
    return this.y;
  }

  /**
   * Method that returns area
   *
   * @return (2 * pi * radius) * (radius + height)
   */
  public double getArea() {
    return (2 * Math.PI * this.x) * (this.y + this.x);
  }

  /**
   * Method that returns volume
   *
   * @return pi * radius ^ 2 * height
   */
  public double getVolume() {
    return Math.PI * this.x * this.x * this.y;
  }

  /**
   * Method that returns mass
   *
   * @return volume * density
   */
  public double getMass() {
    return this.getVolume() * this.density;
  }
}
