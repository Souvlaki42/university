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
  throw RecordException("Δεν υπάρχει φοιτητής με AM " + std::to_string(student.getRegistrationNumber()));
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
  throw RecordException("Δεν υπάρχει φοιτητής με AM " + std::to_string(student.getRegistrationNumber()));
}

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
  throw RecordException("Δεν υπάρχει μάθημα με κωδικό " + lesson.getCode());
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
  throw RecordException("Δεν υπάρχει μάθημα με κωδικό " + lesson.getCode());
}

void Record::sendEmailToAllStudents(const string &message)
{
  cout << "Στάλθηκε email με μήνυμα \"" << message << "\" σε όλους τους φοιτητές του τμήματος με επιτυχία!\n";
}

void Record::sendEmailToAllProfessors(const string &message)
{
  cout << "Στάλθηκε email με μήνυμα \"" << message << "\" σε όλους τους καθηγητές του τμήματος με επιτυχία!\n";
}

void Record::addGrade(const Student &student, Lesson &lesson, float grade)
{
  if (grade < 0 || grade > 10)
  {
    throw RecordException("Ο βαθμός πρέπει να είναι μεταξύ 0 και 10");
  }

  int lessonIndex = -1;
  for (int i = 0; i < this->lessons.size(); i++)
  {
    if (this->lessons[i].getCode() == lesson.getCode())
    {
      lessonIndex = i;
      break;
    }
  }

  if (lessonIndex == -1)
  {
    throw RecordException("Δεν υπάρχει μάθημα με κωδικό " + lesson.getCode());
  }

  int studentIndex = -1;
  for (int i = 0; i < this->students.size(); i++)
  {
    if (this->students[i].getRegistrationNumber() == student.getRegistrationNumber())
    {
      studentIndex = i;
      break;
    }
  }

  if (studentIndex == -1)
  {
    throw RecordException("Δεν υπάρχει φοιτητής με AM " + std::to_string(student.getRegistrationNumber()));
  }

  Lesson &selectedLesson = this->lessons[lessonIndex];
  vector<float> grades = selectedLesson.getGrades();

  if (grades.size() <= studentIndex)
  {
    grades.resize(this->students.size(), -1);
  }
  grades[studentIndex] = grade;
  selectedLesson.setGrades(grades);
}

void Record::fixGrade(const Student &student, Lesson &lesson, float grade)
{
  try
  {
    addGrade(student, lesson, grade);
  }
  catch (const RecordException &e)
  {
    throw RecordException(string(e.what()));
  }
}

void Record::saveToCsv()
{
  ofstream profFile("professors_record.csv");
  if (!profFile.is_open())
  {
    throw RecordException("Το άρχείο καθηγητών δεν μπόρεσε να ανοιχθεί");
  }

  profFile << "ID,name,birthYear,address,phone,email,code,specialty\n";

  set<string> writtenProfessorIds;

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

  ofstream lessonFile("lessons_record.csv");
  if (!lessonFile.is_open())
  {
    throw RecordException("Το άρχείο μαθημάτων δεν μπόρεσε να ανοιχθεί");
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

  ofstream studentFile("students_record.csv");
  if (!studentFile.is_open())
  {
    throw RecordException("Το άρχείο μαθητών δεν μπόρεσε να ανοιχθεί");
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

  ofstream gradeFile("grades_record.csv");
  if (!gradeFile.is_open())
  {
    throw RecordException("Το άρχείο βαθμών δεν μπόρεσε να ανοιχθεί");
  }

  gradeFile << "studentID,lessonCode,grade\n";
  for (const auto &lesson : lessons)
  {
    const vector<float> &grades = lesson.getGrades();
    for (size_t i = 0; i < grades.size() && i < students.size(); ++i)
    {
      if (grades[i] >= 0)
      {
        gradeFile << students[i].getID() << ","
                  << lesson.getCode() << ","
                  << grades[i] << "\n";
      }
    }
  }
  gradeFile.close();
}

void Record::loadFromCsv() {}