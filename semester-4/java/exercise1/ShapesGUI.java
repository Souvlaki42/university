/**
 * This class calculates properties of different 3D shape types.
 *
 * @author Souvlaki42
 * @version 1.0
 * @see ThreeDShape
 * @see Sphere
 * @see Cylinder
 * @see Cone
 */
public class ShapesGUI extends javax.swing.JFrame {

  /** Constructor that calls component initializer */
  public ShapesGUI() {
    initComponents();
  }

  /** Method that initializes gui components */
  private void initComponents() {
    // all components initialized
    shapeInput = new javax.swing.JComboBox<>();
    shapeLabel = new javax.swing.JLabel();
    radiusLabel = new javax.swing.JLabel();
    radiusInput = new javax.swing.JFormattedTextField(0);
    heightLabel = new javax.swing.JLabel();
    heightInput = new javax.swing.JFormattedTextField(0);
    densityLabel = new javax.swing.JLabel();
    densityInput = new javax.swing.JFormattedTextField(0);
    areaLabel = new javax.swing.JLabel();
    massLabel = new javax.swing.JLabel();
    volumeLabel = new javax.swing.JLabel();
    calculateBtn = new javax.swing.JButton();

    // sets exit on close
    setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
    // sets window's title
    setTitle("Shapes GUI");

    // sets combobox's values
    shapeInput.setModel(
      new javax.swing.DefaultComboBoxModel<>(new String[] {
        "None",
        "Sphere",
        "Cone",
        "Cylinder",
      })
    );

    // sets shape label's text
    shapeLabel.setText("Choose shape:");

    // sets radius label's text
    radiusLabel.setText("Enter radius:");

    // set radius input to format as numbers
    radiusInput.setFormatterFactory(
      new javax.swing.text.DefaultFormatterFactory(
        new javax.swing.text.NumberFormatter()
      )
    );

    // sets height label's text
    heightLabel.setText("Enter height:");

    // set height input to format as numbers
    heightInput.setFormatterFactory(
      new javax.swing.text.DefaultFormatterFactory(
        new javax.swing.text.NumberFormatter()
      )
    );

    // set density label's text
    densityLabel.setText("Enter density:");

    // set density input to format as numbers
    densityInput.setFormatterFactory(
      new javax.swing.text.DefaultFormatterFactory(
        new javax.swing.text.NumberFormatter()
      )
    );

    // set area label's text
    areaLabel.setText("Area: -");

    // set mass label's text
    massLabel.setText("Mass: -");

    // set volume label's text
    volumeLabel.setText("Volume: -");

    // set calculate button's text
    calculateBtn.setText("Calculate");

    // make calculate button call calculateBtnActionPerformed method when clicked
    calculateBtn.addActionListener(
      new java.awt.event.ActionListener() {
        public void actionPerformed(java.awt.event.ActionEvent evt) {
          calculateBtnActionPerformed(evt);
        }
      }
    );

    // create main layout
    javax.swing.GroupLayout layout = new javax.swing.GroupLayout(
      getContentPane()
    );

    // set app's layout to the main layout
    getContentPane().setLayout(layout);

    // add all gui components to the layout
    layout.setHorizontalGroup(
      layout
        .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGroup(
          javax.swing.GroupLayout.Alignment.TRAILING,
          layout
            .createSequentialGroup()
            .addContainerGap(27, Short.MAX_VALUE)
            .addGroup(
              layout
                .createParallelGroup(
                  javax.swing.GroupLayout.Alignment.LEADING,
                  false
                )
                .addComponent(densityLabel)
                .addComponent(heightLabel)
                .addComponent(radiusLabel)
                .addComponent(
                  shapeInput,
                  0,
                  javax.swing.GroupLayout.DEFAULT_SIZE,
                  Short.MAX_VALUE
                )
                .addComponent(radiusInput)
                .addComponent(heightInput)
                .addComponent(densityInput)
                .addComponent(
                  areaLabel,
                  javax.swing.GroupLayout.Alignment.TRAILING,
                  javax.swing.GroupLayout.DEFAULT_SIZE,
                  193,
                  Short.MAX_VALUE
                )
                .addComponent(
                  massLabel,
                  javax.swing.GroupLayout.DEFAULT_SIZE,
                  193,
                  Short.MAX_VALUE
                )
                .addComponent(
                  volumeLabel,
                  javax.swing.GroupLayout.DEFAULT_SIZE,
                  193,
                  Short.MAX_VALUE
                )
                .addComponent(
                  shapeLabel,
                  javax.swing.GroupLayout.DEFAULT_SIZE,
                  javax.swing.GroupLayout.DEFAULT_SIZE,
                  Short.MAX_VALUE
                )
                .addComponent(
                  calculateBtn,
                  javax.swing.GroupLayout.DEFAULT_SIZE,
                  javax.swing.GroupLayout.DEFAULT_SIZE,
                  Short.MAX_VALUE
                )
            )
            .addGap(27, 27, 27)
        )
    );
    layout.setVerticalGroup(
      layout
        .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGroup(
          layout
            .createSequentialGroup()
            .addGap(14, 14, 14)
            .addComponent(shapeLabel)
            .addPreferredGap(
              javax.swing.LayoutStyle.ComponentPlacement.UNRELATED
            )
            .addComponent(
              shapeInput,
              javax.swing.GroupLayout.PREFERRED_SIZE,
              javax.swing.GroupLayout.DEFAULT_SIZE,
              javax.swing.GroupLayout.PREFERRED_SIZE
            )
            .addGap(18, 18, 18)
            .addComponent(radiusLabel)
            .addPreferredGap(
              javax.swing.LayoutStyle.ComponentPlacement.UNRELATED
            )
            .addComponent(
              radiusInput,
              javax.swing.GroupLayout.PREFERRED_SIZE,
              javax.swing.GroupLayout.DEFAULT_SIZE,
              javax.swing.GroupLayout.PREFERRED_SIZE
            )
            .addGap(18, 18, 18)
            .addComponent(heightLabel)
            .addPreferredGap(
              javax.swing.LayoutStyle.ComponentPlacement.UNRELATED
            )
            .addComponent(
              heightInput,
              javax.swing.GroupLayout.PREFERRED_SIZE,
              javax.swing.GroupLayout.DEFAULT_SIZE,
              javax.swing.GroupLayout.PREFERRED_SIZE
            )
            .addGap(18, 18, 18)
            .addComponent(densityLabel)
            .addPreferredGap(
              javax.swing.LayoutStyle.ComponentPlacement.UNRELATED
            )
            .addComponent(
              densityInput,
              javax.swing.GroupLayout.PREFERRED_SIZE,
              javax.swing.GroupLayout.DEFAULT_SIZE,
              javax.swing.GroupLayout.PREFERRED_SIZE
            )
            .addGap(18, 18, 18)
            .addComponent(areaLabel)
            .addGap(18, 18, 18)
            .addComponent(massLabel)
            .addGap(18, 18, 18)
            .addComponent(volumeLabel)
            .addGap(18, 18, 18)
            .addComponent(calculateBtn)
            .addContainerGap(14, Short.MAX_VALUE)
        )
    );

    pack();
  }

  /**
   * @param evt event generated when button is clicked
   */
  private void calculateBtnActionPerformed(java.awt.event.ActionEvent evt) {
    // grab radius value as double
    double radius = ((Number) radiusInput.getValue()).doubleValue();
    // grab height value as double
    double height = ((Number) heightInput.getValue()).doubleValue();
    // grab density value as double
    double density = ((Number) densityInput.getValue()).doubleValue();
    // grab shape type as string
    String shape = shapeInput.getSelectedItem().toString();

    // check shape type
    if (shape.equals("Sphere")) {
      // create sphere
      Sphere sphere = new Sphere(radius, density);
      // set area, volume, mass, labels by calling sphere's methods
      areaLabel.setText("Area: " + sphere.getArea());
      volumeLabel.setText("Volume: " + sphere.getVolume());
      massLabel.setText("Mass: " + sphere.getMass());
    } else if (shape.equals("Cylinder")) {
      // create cylinder
      Cylinder cylinder = new Cylinder(radius, height, density);
      // set area, volume, mass, labels by calling cylinder's methods
      areaLabel.setText("Area: " + cylinder.getArea());
      volumeLabel.setText("Volume: " + cylinder.getVolume());
      massLabel.setText("Mass: " + cylinder.getMass());
    } else if (shape.equals("Cone")) {
      // create cone
      Cone cone = new Cone(radius, height, density);
      // set area, volume, mass, labels by calling cone's methods
      areaLabel.setText("Area: " + cone.getArea());
      volumeLabel.setText("Volume: " + cone.getVolume());
      massLabel.setText("Mass: " + cone.getMass());
    } else {
      return;
    }
  }

  /**
   * This is the main method of the app
   *
   * @param args unused
   */
  public static void main(String[] args) {
    // invoke the app to display the gui window
    java.awt.EventQueue.invokeLater(() -> new ShapesGUI().setVisible(true));
  }

  // definitions of all gui elements
  private javax.swing.JLabel areaLabel;
  private javax.swing.JButton calculateBtn;
  private javax.swing.JLabel massLabel;
  private javax.swing.JComboBox<String> shapeInput;
  private javax.swing.JLabel shapeLabel;
  private javax.swing.JLabel volumeLabel;
  private javax.swing.JFormattedTextField radiusInput;
  private javax.swing.JLabel radiusLabel;
  private javax.swing.JFormattedTextField heightInput;
  private javax.swing.JLabel heightLabel;
  private javax.swing.JFormattedTextField densityInput;
  private javax.swing.JLabel densityLabel;
}
