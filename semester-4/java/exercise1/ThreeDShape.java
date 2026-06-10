/**
 * This class represents a basic 3D shape of any kind.
 *
 * @author Souvlaki42
 * @version 1.0
 */
public class ThreeDShape {

  protected String type; // type (spere, cylinder, cone etc)
  protected double x; // first dimension (ie width)
  protected double y; // second dimension (ie height)
  protected double z; // third dimension (ie depth)
  protected double density; // density

  /**
   * Basic constructor only setting the type and leaving everything else as 0
   *
   * @param type type
   */
  ThreeDShape(String type) {
    this.type = type;
    this.x = 0;
    this.y = 0;
    this.z = 0;
    this.density = 0;
  }

  /**
   * Constructor setting type, dimensions and intensity
   *
   * @param type type
   * @param x first dimension
   * @param y second dimension
   * @param z third dimension
   * @param density density
   */
  ThreeDShape(String type, double x, double y, double z, double density) {
    this.type = type;
    this.x = x;
    this.y = y;
    this.z = z;
    this.density = density;
  }

  /**
   * Return shape's type
   *
   * @return type
   */
  public String getType() {
    return this.type;
  }

  /**
   * Return shape's density
   *
   * @return density
   */
  public double getDensity() {
    return this.density;
  }
}
