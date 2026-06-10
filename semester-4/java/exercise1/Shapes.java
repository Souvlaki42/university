import java.util.Scanner;

/**
 * This class tests the functionality of the other shape classes.
 *
 * @author Souvlaki42
 * @version 1.0
 * @see ThreeDShape
 * @see Sphere
 * @see Cylinder
 * @see Cone
 */
public class Shapes {

  /**
   * This is the main method of the program
   *
   * @param args Unused
   */
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in); // this scanner takes stdin

    while (true) {
      // infinite loop
      System.out.print("Enter shape type: "); // asking for the shape type
      String type = scanner.next().toLowerCase(); // converting the shape type to lowercase

      if (type.equals("sphere")) {
        // checking if type is sphere
        System.out.print("Enter radius: ");
        double radius = scanner.nextDouble(); // asking for the radius
        System.out.print("Enter density: ");
        double density = scanner.nextDouble(); // asking for density
        Sphere sphere = new Sphere(radius, density); // creating the sphere instance
        System.out.println("Radius: " + sphere.getRadius()); // printing the radius
        System.out.println("Diameter: " + sphere.getDiameter()); // printing the diameter
        System.out.println("Density: " + sphere.getDensity()); // printing the density
        System.out.println("Area: " + sphere.getArea()); // printing the area
        System.out.println("Mass: " + sphere.getMass()); // printing the mass
        System.out.println("Volume: " + sphere.getVolume()); // printing the volume
      } else if (type.equals("cylinder")) {
        // checking if type is cylinder
        System.out.print("Enter radius: ");
        double radius = scanner.nextDouble(); // asking for radius
        System.out.print("Enter height: ");
        double height = scanner.nextDouble(); // asking for height
        System.out.print("Enter density: ");
        double density = scanner.nextDouble(); // asking for density
        Cylinder cylinder = new Cylinder(radius, height, density); // creating the cylinder instance
        System.out.println("Radius: " + cylinder.getRadius()); // printing the radius
        System.out.println("Height: " + cylinder.getHeight()); // printing the height
        System.out.println("Density: " + cylinder.getDensity()); // printing the density
        System.out.println("Area: " + cylinder.getArea()); // printing the area
        System.out.println("Mass: " + cylinder.getMass()); // printing the mass
        System.out.println("Volume: " + cylinder.getVolume()); // printing the volume
      } else if (type.equals("cone")) {
        // checking if type is cone
        System.out.print("Enter radius: ");
        double radius = scanner.nextDouble(); // asking the radius
        System.out.print("Enter height: ");
        double height = scanner.nextDouble(); // asking the height
        System.out.print("Enter density: ");
        double density = scanner.nextDouble(); // asking the density
        Cone cone = new Cone(radius, height, density); // creating the cone instance
        System.out.println("Radius: " + cone.getRadius()); // printing the radius
        System.out.println("Height: " + cone.getHeight()); // printing the height
        System.out.println("Slant Height: " + cone.getSlantHeight()); // printing the slant height
        System.out.println("Density: " + cone.getDensity()); // printing the density
        System.out.println("Area: " + cone.getArea()); // printing the area
        System.out.println("Mass: " + cone.getMass()); // printing the mass
        System.out.println("Volume: " + cone.getVolume()); // printing the volume
      } else {
        System.err.println("Unknown shape."); // failing the loop iteration for unknown shapes
      }

      System.out.print("Continue? (y/n): "); // asking if user wants to continue
      char answer = scanner.next().toLowerCase().charAt(0); // taking the lowercase answer

      if (answer != 'y') break; // stopping the loop if answer isn't yes
    }

    scanner.close(); // close the stdin scanner at the end
  }
}
