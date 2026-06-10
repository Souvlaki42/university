import java.io.*;
import java.util.*;
import javax.swing.JFileChooser;

/**
 * This class calculates grade entries.
 *
 * @author Souvlaki42
 * @version 1.0
 */
public class GradesGUI extends javax.swing.JFrame {

  /** Constructor initializer */
  public GradesGUI() {
    initComponents();
  }

  /** Initializes components */
  private void initComponents() {
    fileChooser = new javax.swing.JFileChooser();
    inputFileField = new javax.swing.JTextField();
    inputBtn = new javax.swing.JButton();
    inputLabel = new javax.swing.JLabel();
    outputLabel = new javax.swing.JLabel();
    outputField = new javax.swing.JTextField();
    outputBtn = new javax.swing.JButton();
    gradesNumLabel = new javax.swing.JLabel();
    minGradeLabel = new javax.swing.JLabel();
    maxGradeLabel = new javax.swing.JLabel();
    meanGradeLabel = new javax.swing.JLabel();
    medianGradeLabel = new javax.swing.JLabel();
    calculateBtn = new javax.swing.JButton();

    setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
    setTitle("Grades GUI");

    inputBtn.setText("Choose");
    inputBtn.addActionListener(this::inputBtnActionPerformed);

    inputLabel.setText("Choose input file:");

    outputLabel.setText("Choose output file:");

    outputBtn.setText("Choose");
    outputBtn.addActionListener(this::outputBtnActionPerformed);

    gradesNumLabel.setText("Valid grades: -");

    minGradeLabel.setText("Mininum grade: -");

    maxGradeLabel.setText("Maximum grade: -");

    meanGradeLabel.setText("Grade mean: -");

    medianGradeLabel.setText("Grade median : -");

    calculateBtn.setText("Calculate");
    calculateBtn.addActionListener(this::calculateBtnActionPerformed);

    javax.swing.GroupLayout layout = new javax.swing.GroupLayout(
      getContentPane()
    );
    getContentPane().setLayout(layout);
    layout.setHorizontalGroup(
      layout
        .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGroup(
          layout
            .createSequentialGroup()
            .addGap(15, 15, 15)
            .addGroup(
              layout
                .createParallelGroup(
                  javax.swing.GroupLayout.Alignment.LEADING,
                  false
                )
                .addGroup(
                  layout
                    .createSequentialGroup()
                    .addComponent(
                      inputFileField,
                      javax.swing.GroupLayout.PREFERRED_SIZE,
                      432,
                      javax.swing.GroupLayout.PREFERRED_SIZE
                    )
                    .addPreferredGap(
                      javax.swing.LayoutStyle.ComponentPlacement.UNRELATED
                    )
                    .addComponent(inputBtn)
                )
                .addComponent(inputLabel)
                .addGroup(
                  layout
                    .createSequentialGroup()
                    .addComponent(
                      outputField,
                      javax.swing.GroupLayout.PREFERRED_SIZE,
                      432,
                      javax.swing.GroupLayout.PREFERRED_SIZE
                    )
                    .addPreferredGap(
                      javax.swing.LayoutStyle.ComponentPlacement.UNRELATED
                    )
                    .addComponent(outputBtn)
                )
                .addComponent(outputLabel)
                .addComponent(
                  gradesNumLabel,
                  javax.swing.GroupLayout.DEFAULT_SIZE,
                  javax.swing.GroupLayout.DEFAULT_SIZE,
                  Short.MAX_VALUE
                )
                .addComponent(
                  minGradeLabel,
                  javax.swing.GroupLayout.DEFAULT_SIZE,
                  javax.swing.GroupLayout.DEFAULT_SIZE,
                  Short.MAX_VALUE
                )
                .addComponent(
                  maxGradeLabel,
                  javax.swing.GroupLayout.DEFAULT_SIZE,
                  javax.swing.GroupLayout.DEFAULT_SIZE,
                  Short.MAX_VALUE
                )
                .addComponent(
                  meanGradeLabel,
                  javax.swing.GroupLayout.DEFAULT_SIZE,
                  javax.swing.GroupLayout.DEFAULT_SIZE,
                  Short.MAX_VALUE
                )
                .addComponent(
                  medianGradeLabel,
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
            .addContainerGap(15, Short.MAX_VALUE)
        )
    );
    layout.setVerticalGroup(
      layout
        .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGroup(
          layout
            .createSequentialGroup()
            .addGap(20, 20, 20)
            .addComponent(inputLabel)
            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(
              layout
                .createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                .addComponent(
                  inputFileField,
                  javax.swing.GroupLayout.PREFERRED_SIZE,
                  javax.swing.GroupLayout.DEFAULT_SIZE,
                  javax.swing.GroupLayout.PREFERRED_SIZE
                )
                .addComponent(inputBtn)
            )
            .addGap(18, 18, 18)
            .addComponent(outputLabel)
            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(
              layout
                .createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                .addComponent(
                  outputField,
                  javax.swing.GroupLayout.PREFERRED_SIZE,
                  javax.swing.GroupLayout.DEFAULT_SIZE,
                  javax.swing.GroupLayout.PREFERRED_SIZE
                )
                .addComponent(outputBtn)
            )
            .addGap(18, 18, 18)
            .addComponent(gradesNumLabel)
            .addPreferredGap(
              javax.swing.LayoutStyle.ComponentPlacement.UNRELATED
            )
            .addComponent(minGradeLabel)
            .addPreferredGap(
              javax.swing.LayoutStyle.ComponentPlacement.UNRELATED
            )
            .addComponent(maxGradeLabel)
            .addPreferredGap(
              javax.swing.LayoutStyle.ComponentPlacement.UNRELATED
            )
            .addComponent(meanGradeLabel)
            .addPreferredGap(
              javax.swing.LayoutStyle.ComponentPlacement.UNRELATED
            )
            .addComponent(medianGradeLabel)
            .addGap(18, 18, 18)
            .addComponent(calculateBtn)
            .addContainerGap(
              javax.swing.GroupLayout.DEFAULT_SIZE,
              Short.MAX_VALUE
            )
        )
    );

    pack();
  }

  /**
   * Main function
   *
   * @param args used
   */
  public static void main(String[] args) {
    java.awt.EventQueue.invokeLater(() -> new GradesGUI().setVisible(true));
  }

  /**
   * Opens the open file dialog
   *
   * @param evt event when button clicked
   */
  private void inputBtnActionPerformed(java.awt.event.ActionEvent evt) {
    if (fileChooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
      inputFileField.setText(fileChooser.getSelectedFile().getAbsolutePath());
    }
  }

  /**
   * Opens a save file dialog
   *
   * @param evt event when button clicked
   */
  private void outputBtnActionPerformed(java.awt.event.ActionEvent evt) {
    if (fileChooser.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
      outputField.setText(fileChooser.getSelectedFile().getAbsolutePath());
    }
  }

  /**
   * Calculates the grades
   *
   * @param evt event when button is clicked
   */
  private void calculateBtnActionPerformed(java.awt.event.ActionEvent evt) {
    Scanner gradeReader = null;
    PrintWriter logWriter = null;
    PrintWriter outputWriter = null;

    ArrayList<String> ids = new ArrayList<String>();
    ArrayList<String> courses = new ArrayList<String>();
    ArrayList<Float> grades = new ArrayList<Float>();

    float min = 11;
    float max = 0;
    float total = 0;

    try {
      // try opening the input file as a reader
      gradeReader = new Scanner(new File(inputFileField.getText()));

      // try opening the log file as a writer
      logWriter = new PrintWriter(new FileOutputStream("err.log", true));

      // try opening the output file as a writer
      outputWriter = new PrintWriter(outputField.getText());

      // loop until there are no lines left in the input file
      while (gradeReader.hasNextLine()) {
        String line = gradeReader.nextLine();
        try {
          // read each line in the input file
          String[] data = line.split(":", 3);

          // try parse the line as an integer
          Float grade = Float.parseFloat(data[2]);

          if (grade < min) min = grade;

          if (grade > max) max = grade;

          total += grade;

          grades.add(grade);

          ids.add(data[0]);

          courses.add(data[1]);
        } catch (NumberFormatException e) {
          logWriter.println("Invalid record:\t" + line);
          // skip to the next loop iteration
          continue;
        }
      }

      HashMap<String, ArrayList<Float>> student_grades = new HashMap<
        String,
        ArrayList<Float>
      >();

      // converts dynamic arrays to per student hashmap
      for (int i = 0; i < grades.size(); i++) {
        ArrayList<Float> totals = student_grades.get(ids.get(i));
        if (totals == null) {
          totals = new ArrayList<Float>();
          totals.add(grades.get(i));
          student_grades.put(ids.get(i), totals);
        } else {
          totals.add(grades.get(i));
          student_grades.put(ids.get(i), totals);
        }
      }

      // calculates and stores per student mean
      for (Map.Entry<
        String,
        ArrayList<Float>
      > entry : student_grades.entrySet()) {
        float total_grade = 0;
        for (int j = 0; j < entry.getValue().size(); j++) {
          total_grade += entry.getValue().get(j);
        }
        outputWriter.println(
          String.format("%s:%.1f", entry.getKey(), total_grade)
        );
      }

      // calculates stats
      float length = grades.size();
      float mean = total / length;
      float median = grades.get((int) Math.floor(length / 2));

      // updates stats labels
      gradesNumLabel.setText("Valid grades: " + length);
      minGradeLabel.setText("Mininum grade: " + min);
      maxGradeLabel.setText("Maximum grade: " + max);
      meanGradeLabel.setText("Grade mean: " + mean);
      medianGradeLabel.setText("Grade median : " + median);
    } catch (FileNotFoundException e) {
      // print error if reader or writer constructors failed
      System.err.println("Files needed cannot be opened!");
    }

    // close the readers and writers that were sucessfully opened
    if (gradeReader != null) gradeReader.close();
    if (outputWriter != null) outputWriter.close();
    if (logWriter != null) logWriter.close();
  }

  // defines gui elements
  private javax.swing.JButton calculateBtn;
  private javax.swing.JFileChooser fileChooser;
  private javax.swing.JLabel gradesNumLabel;
  private javax.swing.JButton inputBtn;
  private javax.swing.JTextField inputFileField;
  private javax.swing.JLabel inputLabel;
  private javax.swing.JLabel maxGradeLabel;
  private javax.swing.JLabel meanGradeLabel;
  private javax.swing.JLabel medianGradeLabel;
  private javax.swing.JLabel minGradeLabel;
  private javax.swing.JButton outputBtn;
  private javax.swing.JTextField outputField;
  private javax.swing.JLabel outputLabel;
}
