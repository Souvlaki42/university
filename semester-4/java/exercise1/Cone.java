/**
 * This class represents a cone
 *
 * @author Souvlaki42
 * @version 1.0
 * @see ThreeDShape
 */
public class Cone extends ThreeDShape {

  /**
   * Constructor for dimensions plus slant height sqrt(radius ^ 2 + height ^ 2)
   *
   * @param radius radius
   * @param height height
   */
  Cone(double radius, double height) {
    super(
      "Cone",
      radius,
      height,
      Math.sqrt(Math.pow(radius, 2) + Math.pow(height, 2)),
      0
    );
  }

  /**
   * Constructor for everything plus slant height sqrt(radius ^ 2 + height ^ 2)
   *
   * @param radius radius
   * @param height height
   * @param density density
   */
  Cone(double radius, double height, double density) {
    super(
      "Cone",
      radius,
      height,
      Math.sqrt(Math.pow(radius, 2) + Math.pow(height, 2)),
      density
    );
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
   * Method that returns the height
   *
   * @return height
   */
  public double getHeight() {
    return this.y;
  }

  /**
   * Method that returns the slant height
   *
   * @return slant height
   */
  public double getSlantHeight() {
    return this.z;
  }

  /**
   * Method that returns the area
   *
   * @return (pi * radius) * (radius + slant height)
   */
  public double getArea() {
    return (Math.PI * this.x) * (this.x + this.z);
  }

  /**
   * Method that returns the volume
   *
   * @return 1/3 * (pi * radius ^ 2 * height)
   */
  public double getVolume() {
    return (1f / 3) * (Math.PI * this.x * this.x * this.y);
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
