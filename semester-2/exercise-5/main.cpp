#include <iostream>
#include "Person.h"
#include "Student.h"
#include "Professor.h"
#include "Lesson.h"
#include "Record.h"

using std::cout, std::cerr, std::exception;

//! Instructions: https://docs.google.com/document/d/1nMDT4gnUEltD7OcAKuQf_lIiVbFMjDZRmQ_88wc7eyA/edit?tab=t.0
int main()
{
  try
  {
    // Καθηγητές
    Professor prof1("12345", "Γεώργιος Παπαδόπουλος", 1975, "Λεωφ. Συγγρού 123", "6977123456", "gpap@uniwa.gr", "ICE-AVCLOM", "Δίκτυα");
    Professor prof2("67890", "Μαρία Αλεξίου", 1980, "Οδός Σόλωνος 45", "6978234567", "malex@uniwa.gr", "ICE-HORTBO", "Βάσεις Δεδομένων");

    // Μαθήματα
    Lesson lesson1("CS101", "Σχεδιάση δικτύων", 1, prof1);
    Lesson lesson2("CS102", "Βάσεις Δεδομένων", 2, prof2);

    // Φοιτητές
    Student student1("AM123", "Νίκος Κωνσταντίνου", 2000,
                     12345, 1, {lesson1, lesson2});
    Student student2("AM124", "Ελένη Παπαδοπούλου", 2001,
                     12346, 1, {lesson1});

    // Φοιτητολόγιο
    Record record;

    // Προσθήκη φοιτητών και μαθημάτων
    record.addStudent(student1);
    record.addStudent(student2);
    record.addLesson(lesson1);
    record.addLesson(lesson2);

    // Προσθήκη βαθμών
    record.addGrade(student1, lesson1, 8.5);
    record.addGrade(student1, lesson2, 9.0);
    record.addGrade(student2, lesson1, 7.5);

    // Αποστολή μηνυμάτων
    record.sendEmailToAllStudents("Σας υπενθυμίζουμε ότι οι εξετάσεις ξεκινούν την επόμενη εβδομάδα!");
    record.sendEmailToAllProfessors("Παρακαλούμε να υποβάλετε τους βαθμούς έως την Παρασκευή.");

    // Αποθήκευση σε CSV
    record.saveToCsv();
    cout << "\nΤα δεδομένα αποθηκεύτηκαν επιτυχώς στο αρχείο.\n";

    // Δημιουργία νέου αρχείου και φόρτωση δεδομένων
    Record newRecord;
    newRecord.loadFromCsv();
    cout << "\nΤα δεδομένα φορτώθηκαν επιτυχώς από το αρχείο.\n";
  }
  catch (const RecordException &e)
  {
    cerr << "Σφάλμα φοιτητολογίου: " << e.what() << "\n";
    return 1;
  }
  catch (const std::exception &e)
  {
    cerr << "Απρόσμενο σφάλμα: " << e.what() << "\n";
    return 1;
  }
  catch (...)
  {
    cerr << "Άγνωστο σφάλμα!\n";
    return 1;
  }

  return 0;
}