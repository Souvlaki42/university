/**
 * This class calculates the expected return of a monthly investment with stable interest rates over
 * a period in a GUI.
 *
 * @author Souvlaki42
 * @version 1.0
 */
public class FutureValueGUI extends javax.swing.JFrame {

  /*
   * Constructor that calls component initializer method
   */
  public FutureValueGUI() {
    initComponents();
  }

  /*
   * Method that initializes all components in the GUI
   */
  private void initComponents() {
    // constructs gui elements
    investmentLabel = new javax.swing.JLabel();
    investmentField = new javax.swing.JFormattedTextField(0);
    interestLabel = new javax.swing.JLabel();
    interestField = new javax.swing.JFormattedTextField(0);
    yearLabel = new javax.swing.JLabel();
    yearField = new javax.swing.JFormattedTextField(0);
    resultLabel = new javax.swing.JLabel();
    calculateBtn = new javax.swing.JButton();

    // sets the app to exit when the close button is pressed
    setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

    // sets the app's window title
    setTitle("FutureValueGUI");

    // sets the text of the investment label
    investmentLabel.setText("Enter monthly investment:");

    // sets the investment field to format the input as a number
    investmentField.setFormatterFactory(
      new javax.swing.text.DefaultFormatterFactory(
        new javax.swing.text.NumberFormatter(
          new java.text.DecimalFormat("#0.00")
        )
      )
    );

    // sets the text of the interest label
    interestLabel.setText("Enter yearly interest rate:");

    // sets the interest field to format the input as an integer
    interestField.setFormatterFactory(
      new javax.swing.text.DefaultFormatterFactory(
        new javax.swing.text.NumberFormatter(
          java.text.NumberFormat.getIntegerInstance()
        )
      )
    );

    // sets the text of the year label
    yearLabel.setText("Enter number of years: ");

    // sets the year field to format the input as an integer
    yearField.setFormatterFactory(
      new javax.swing.text.DefaultFormatterFactory(
        new javax.swing.text.NumberFormatter(
          java.text.NumberFormat.getIntegerInstance()
        )
      )
    );

    // sets the text of the result label
    resultLabel.setText("Future value: No value yet");

    // sets the text of the calculate button
    calculateBtn.setText("Calculate");

    // hooks up the calculate button to call the calculateBtnActionPerformed method
    calculateBtn.addActionListener(this::calculateBtnActionPerformed);

    // creates a group layout for the app
    javax.swing.GroupLayout layout = new javax.swing.GroupLayout(
      getContentPane()
    );

    // sets the app's layout to the group layout
    getContentPane().setLayout(layout);

    // adds all the gui elements to the group layout
    layout.setHorizontalGroup(
      layout
        .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGroup(
          layout
            .createSequentialGroup()
            .addGap(27, 27, 27)
            .addGroup(
              layout
                .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(
                  layout
                    .createParallelGroup(
                      javax.swing.GroupLayout.Alignment.LEADING,
                      false
                    )
                    .addComponent(
                      yearLabel,
                      javax.swing.GroupLayout.DEFAULT_SIZE,
                      javax.swing.GroupLayout.DEFAULT_SIZE,
                      Short.MAX_VALUE
                    )
                    .addComponent(
                      yearField,
                      javax.swing.GroupLayout.PREFERRED_SIZE,
                      160,
                      javax.swing.GroupLayout.PREFERRED_SIZE
                    )
                )
                .addGroup(
                  layout
                    .createParallelGroup(
                      javax.swing.GroupLayout.Alignment.LEADING,
                      false
                    )
                    .addComponent(
                      interestLabel,
                      javax.swing.GroupLayout.DEFAULT_SIZE,
                      javax.swing.GroupLayout.DEFAULT_SIZE,
                      Short.MAX_VALUE
                    )
                    .addComponent(
                      interestField,
                      javax.swing.GroupLayout.PREFERRED_SIZE,
                      160,
                      javax.swing.GroupLayout.PREFERRED_SIZE
                    )
                )
                .addGroup(
                  layout
                    .createParallelGroup(
                      javax.swing.GroupLayout.Alignment.LEADING,
                      false
                    )
                    .addComponent(
                      investmentLabel,
                      javax.swing.GroupLayout.DEFAULT_SIZE,
                      javax.swing.GroupLayout.DEFAULT_SIZE,
                      Short.MAX_VALUE
                    )
                    .addComponent(investmentField)
                )
                .addGroup(
                  layout
                    .createParallelGroup(
                      javax.swing.GroupLayout.Alignment.TRAILING,
                      false
                    )
                    .addComponent(
                      calculateBtn,
                      javax.swing.GroupLayout.Alignment.LEADING,
                      javax.swing.GroupLayout.DEFAULT_SIZE,
                      javax.swing.GroupLayout.DEFAULT_SIZE,
                      Short.MAX_VALUE
                    )
                    .addComponent(
                      resultLabel,
                      javax.swing.GroupLayout.Alignment.LEADING,
                      javax.swing.GroupLayout.DEFAULT_SIZE,
                      javax.swing.GroupLayout.DEFAULT_SIZE,
                      Short.MAX_VALUE
                    )
                )
            )
            .addContainerGap(27, Short.MAX_VALUE)
        )
    );

    layout.setVerticalGroup(
      layout
        .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGroup(
          layout
            .createSequentialGroup()
            .addGap(23, 23, 23)
            .addComponent(investmentLabel)
            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(
              investmentField,
              javax.swing.GroupLayout.PREFERRED_SIZE,
              javax.swing.GroupLayout.DEFAULT_SIZE,
              javax.swing.GroupLayout.PREFERRED_SIZE
            )
            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(interestLabel)
            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(
              interestField,
              javax.swing.GroupLayout.PREFERRED_SIZE,
              javax.swing.GroupLayout.DEFAULT_SIZE,
              javax.swing.GroupLayout.PREFERRED_SIZE
            )
            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(yearLabel)
            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(
              yearField,
              javax.swing.GroupLayout.PREFERRED_SIZE,
              javax.swing.GroupLayout.DEFAULT_SIZE,
              javax.swing.GroupLayout.PREFERRED_SIZE
            )
            .addGap(18, 18, 18)
            .addComponent(resultLabel)
            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(calculateBtn)
            .addContainerGap(23, Short.MAX_VALUE)
        )
    );

    pack();
  }

  /**
   * This method is called when the calculate button is clicked
   *
   * @param evt The event that was generated by the click of the calculate button
   */
  private void calculateBtnActionPerformed(java.awt.event.ActionEvent evt) {
    // grab the value of the investment field as a double
    double investment = ((Number) investmentField.getValue()).doubleValue();
    // grab the value of the interest field as a double
    double interest = ((Number) interestField.getValue()).doubleValue();
    // grab the value of the year field as an int
    int years = ((Number) yearField.getValue()).intValue();

    // create the variable to store the result
    double result = 0;

    // Calculate the result in monthly compounds
    for (int i = 0; i < years * 12; i++) {
      result += investment; // increasing result by monthly investment
      result *= (1 + ((interest / 100) / 12)); // increasing result by interest rate percentage
    }

    // set the text of the result label to the formatted result value
    resultLabel.setText(
      "Future value: " + String.format("%.2f", result) + " €"
    );
  }

  /**
   * This is the main method of the app
   *
   * @param args unused
   */
  public static void main(String[] args) {
    // invoke the app to display the gui window
    java.awt.EventQueue.invokeLater(() ->
      new FutureValueGUI().setVisible(true)
    );
  }

  // definitions of all gui elements
  private javax.swing.JButton calculateBtn;
  private javax.swing.JFormattedTextField interestField;
  private javax.swing.JLabel interestLabel;
  private javax.swing.JFormattedTextField investmentField;
  private javax.swing.JLabel investmentLabel;
  private javax.swing.JLabel resultLabel;
  private javax.swing.JFormattedTextField yearField;
  private javax.swing.JLabel yearLabel;
}
