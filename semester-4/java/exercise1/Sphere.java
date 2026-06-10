/**
 * This class defines a sphere and allows calculating and printing its details.
 *
 * @author Souvlaki42
 * @version 1.0
 * @see ThreeDShape
 */
public class Sphere extends ThreeDShape {

  /** Constructor without density */
  Sphere(double radius) {
    super("Sphere", radius, radius * 2, 0, 0);
  }

  /**
   * Constructor with all arguments
   *
   * @param radius the radius
   * @param density the density
   */
  Sphere(double radius, double density) {
    super("Sphere", radius, radius * 2, 0, density);
  }

  /**
   * Method that returns the radius
   *
   * @return radius
   */
  public double getRadius() {
    return this.x;
  }

  /**
   * Method that returns diameter
   *
   * @return diameter
   */
  public double getDiameter() {
    return this.y;
  }

  /**
   * Method that returns the area
   *
   * @return 4 * pi * r^2
   */
  public double getArea() {
    return 4 * Math.PI * this.x * this.x;
  }

  /**
   * Method that returns the volume
   *
   * @return 4/3 * pi * r^3
   */
  public double getVolume() {
    return (4f / 3) * Math.PI * this.x * this.x * this.x;
  }

  /**
   * Method that returns the mass
   *
   * @return volume * density
   */
  public double getMass() {
    return this.getVolume() * this.density;
  }
}
