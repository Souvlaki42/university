#include "Student.h"
#include "Lesson.h"
#include "Record.h"
#include <iostream>
#include <fstream>
#include <set>
using std::cout, std::vector, std::ofstream, std::set;

void Record::addStudent(const Student &student)
{
  this->students.push_back(student);
}

void Record::fixStudent(const Student &student)
{
  for (int i = 0; i < this->students.size(); i++)
  {
    if (this->students[i].getRegistrationNumber() == student.getRegistrationNumber())
    {
      this->students[i] = student;
      return;
    }
  }
  cout << "Ο φοιτητής που ψάχνεται δεν υπάρχει!\n";
}

void Record::removeStudent(const Student &student)
{
  for (size_t i = 0; i < this->students.size();)
  {
    if (this->students[i].getRegistrationNumber() == student.getRegistrationNumber())
    {
      this->students.erase(this->students.begin() + i);
      return;
    }
    else
    {
      ++i;
    }
  }
  cout << "Ο φοιτητής που ψάχνεται δεν υπάρχει!\n";
};

void Record::addLesson(const Lesson &lesson)
{
  this->lessons.push_back(lesson);
};

void Record::fixLesson(const Lesson &lesson)
{
  for (int i = 0; i < this->lessons.size(); i++)
  {
    if (this->lessons[i].getCode() == lesson.getCode())
    {
      this->lessons[i] = lesson;
      return;
    }
  }
  cout << "Το μάθημα που ψάχνεται δεν υπάρχει!\n";
};
void Record::removeLesson(const Lesson &lesson)
{
  for (size_t i = 0; i < this->lessons.size();)
  {
    if (this->lessons[i].getCode() == lesson.getCode())
    {
      this->lessons.erase(this->lessons.begin() + i);
      return;
    }
    else
    {
      ++i;
    }
  }
  cout << "Το μάθημα που ψάχνεται δεν υπάρχει!\n";
};
void Record::sendEmailToAllStudents(const string &message)
{
  cout << "Στάλθηκε email με μήνυμα \"" << message << "\" σε όλους τους φοιτητές του τμήματος με επιτυχία!\n";
};
void Record::sendEmailToAllProfessors(const string &message)
{
  cout << "Στάλθηκε email με μήνυμα \"" << message << "\" σε όλους τους καθηγητές του τμήματος με επιτυχία!\n";
};
void Record::addGrade(const Student &student, Lesson &lesson, int grade)
{
  // Validate grade
  if (grade < 0 || grade > 10)
  {
    throw RecordException("Invalid grade value. Grade must be between 0 and 10.");
  }

  // Find the lesson in our record
  bool lessonFound = false;
  for (auto &recordLesson : lessons)
  {
    if (recordLesson.getCode() == lesson.getCode())
    {
      lesson = recordLesson; // Update the reference to point to our lesson
      lessonFound = true;
      break;
    }
  }
  if (!lessonFound)
  {
    throw RecordException("Lesson " + lesson.getCode() + " not found in record.");
  }

  // Find the student
  bool studentFound = false;
  size_t studentIndex = 0;
  for (size_t i = 0; i < students.size(); i++)
  {
    if (students[i].getRegistrationNumber() == student.getRegistrationNumber())
    {
      studentFound = true;
      studentIndex = i;
      break;
    }
  }
  if (!studentFound)
  {
    throw RecordException("Student with registration number " +
                          std::to_string(student.getRegistrationNumber()) + " not found in record.");
  }

  // Get current grades and ensure vector is properly sized
  vector<float> grades = lesson.getGrades();
  if (grades.size() <= studentIndex)
  {
    grades.resize(students.size(), -1); // Resize and initialize with -1 (invalid grade)
  }

  // Update the grade
  grades[studentIndex] = grade;
  lesson.setGrades(grades);

  // Update the lesson in our record
  for (auto &recordLesson : lessons)
  {
    if (recordLesson.getCode() == lesson.getCode())
    {
      recordLesson = lesson;
      break;
    }
  }
}
void Record::fixGrade(const Student &student, Lesson &lesson, int grade)
{
  // Reuse addGrade since the logic is the same
  // The only difference is semantic - fixGrade implies the grade already exists
  try
  {
    addGrade(student, lesson, grade);
  }
  catch (const RecordException &e)
  {
    throw RecordException("Could not fix grade: " + string(e.what()));
  }
}

void Record::saveToCsv(const string &filename)
{
  // Save professors first since they are referenced by lessons
  ofstream profFile(filename + "_professors.csv");
  if (!profFile.is_open())
  {
    throw RecordException("Could not open professors file for writing");
  }

  // Write professors header
  profFile << "ID,name,birthYear,address,phone,email,code,specialty\n";

  // Keep track of professors we've written to avoid duplicates
  set<string> writtenProfessorIds;

  // Write professors from lessons
  for (const auto &lesson : lessons)
  {
    const Professor &prof = lesson.getProfessor();
    if (writtenProfessorIds.insert(prof.getID()).second)
    {
      profFile << prof.getID() << ","
               << prof.getName() << ","
               << prof.getBirthYear() << ","
               << prof.getAddress() << ","
               << prof.getPhone() << ","
               << prof.getEmail() << ","
               << prof.getCode() << ","
               << prof.getSpecialty() << "\n";
    }
  }
  profFile.close();

  // Save lessons
  ofstream lessonFile(filename + "_lessons.csv");
  if (!lessonFile.is_open())
  {
    throw RecordException("Could not open lessons file for writing");
  }

  lessonFile << "code,name,semester,professorID\n";
  for (const auto &lesson : lessons)
  {
    lessonFile << lesson.getCode() << ","
               << lesson.getName() << ","
               << lesson.getSemester() << ","
               << lesson.getProfessor().getID() << "\n";
  }
  lessonFile.close();

  // Save students
  ofstream studentFile(filename + "_students.csv");
  if (!studentFile.is_open())
  {
    throw RecordException("Could not open students file for writing");
  }

  studentFile << "ID,name,birthYear,address,phone,email,registrationNumber,semester\n";
  for (const auto &student : students)
  {
    studentFile << student.getID() << ","
                << student.getName() << ","
                << student.getBirthYear() << ","
                << student.getAddress() << ","
                << student.getPhone() << ","
                << student.getEmail() << ","
                << student.getRegistrationNumber() << ","
                << student.getSemester() << "\n";
  }
  studentFile.close();

  // Save grades
  ofstream gradeFile(filename + "_grades.csv");
  if (!gradeFile.is_open())
  {
    throw RecordException("Could not open grades file for writing");
  }

  gradeFile << "studentID,lessonCode,grade\n";
  for (const auto &lesson : lessons)
  {
    const vector<float> &grades = lesson.getGrades();
    for (size_t i = 0; i < grades.size() && i < students.size(); ++i)
    {
      if (grades[i] >= 0)
      { // Only write valid grades
        gradeFile << students[i].getID() << ","
                  << lesson.getCode() << ","
                  << grades[i] << "\n";
      }
    }
  }
  gradeFile.close();
}

void Record::loadFromCsv(const string &filename) {

};