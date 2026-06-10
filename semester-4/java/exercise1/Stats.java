import java.io.*;
import java.util.*;
import javax.swing.JOptionPane;

/**
 * This class takes a text file with numbers and prints some stats about them.
 *
 * @author Souvlaki42
 * @version 1.0
 */
class Stats {

  /**
   * This is the main method of the class
   *
   * @param args command line arguments containing the text file with the numbers, as well as the
   *     output file
   */
  public static void main(String[] args) {
    // print usage message if we don't have enough arguments
    if (args.length != 2) {
      System.err.println("Usage: java Stats <input.txt> <output.txt>");
      System.exit(1);
    }

    // create a dynamic array of integers
    ArrayList<Integer> numberList = new ArrayList<Integer>();

    // create some input readers and output writers
    Scanner numberReader = null;
    PrintWriter logWriter = null;
    PrintWriter outputWriter = null;

    try {
      // try opening the numbers file as a reader
      numberReader = new Scanner(new File(args[0]));

      // try opening the log file as a writer
      logWriter = new PrintWriter(new FileOutputStream("numbers.log", true));

      // try opening the output file as a writer
      outputWriter = new PrintWriter(args[1]);

      // loop until there are no lines left in the number file
      while (numberReader.hasNextLine()) {
        try {
          // read each line in the number file
          String data = numberReader.nextLine();

          // try parse the line as an integer
          int number = Integer.parseInt(data);

          // throw exception if the number is negative
          if (number <= 0) {
            throw new NumberFormatException(
              "Number " + number + " is not a positive integer!"
            );
          }

          // add the number to the dynamic array
          numberList.add(number);
        } catch (NumberFormatException e) {
          // handle the line not being an integer or being negative
          // print the error in the console
          System.err.println(e.getMessage());
          // write the error in thee log file
          logWriter.println(e.getMessage());
          // skip to the next loop iteration
          continue;
        }
      }

      // sort the number array in decending order
      Collections.sort(numberList);

      // turn the dynamic array into a static array
      Integer[] numbers = new Integer[numberList.size()];
      numbers = numberList.toArray(numbers);

      int min = numbers[0]; // get the minimum from the first element as the array is sorted
      int max = numbers[numbers.length - 1]; // get the maximum from the last element as the array is sorted
      int length = numbers.length; // get the array's length
      int total = 0;
      int mean = 0;
      int median = 0;

      // calculate the sum of all the numbers
      for (int i = 0; i < length; i++) {
        total += numbers[i];
        // write the number to the output file
        outputWriter.println(numbers[i]);
      }

      // calculate the mean
      mean = total / length;

      if (length % 2 == 0) {
        // calculate the median if length is even
        median = (numbers[length / 2] + numbers[length / 2 + 1]) / 2;
      } else {
        // calculate the median if the length is odd
        median = numbers[(length + 1) / 2];
      }

      // store the stats in a string
      String message = String.format(
        "Min: %d\nMax: %d\nLength: %d\nMean: %d\nMedian: %d",
        min,
        max,
        length,
        mean,
        median
      );

      // display a message with all the stats
      JOptionPane.showMessageDialog(
        null,
        message,
        "Stats",
        JOptionPane.PLAIN_MESSAGE
      );
    } catch (FileNotFoundException e) {
      // print error if reader or writer constructors failed
      System.err.println("Files needed cannot be opened!");
    }

    // close the readers and writers that were sucessfully opened
    if (numberReader != null) numberReader.close();
    if (outputWriter != null) outputWriter.close();
    if (logWriter != null) logWriter.close();
  }
}
