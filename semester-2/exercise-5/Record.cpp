#include "Student.h"
#include "Lesson.h"
#include "Record.h"
#include <iostream>

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
  std::cout << "Ο φοιτητής που ψάχνεται δεν υπάρχει!\n";
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
  std::cout << "Ο φοιτητής που ψάχνεται δεν υπάρχει!\n";
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
  std::cout << "Το μάθημα που ψάχνεται δεν υπάρχει!\n";
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
  std::cout << "Το μάθημα που ψάχνεται δεν υπάρχει!\n";
};
void Record::sendEmailToAllStudents(const string &message)
{
  std::cout << "Στάλθηκε email με μήνυμα \"" << message << "\" σε όλους τους φοιτητές του τμήματος με επιτυχία!\n";
};
void Record::sendEmailToAllProfessors(const string &message)
{
  std::cout << "Στάλθηκε email με μήνυμα \"" << message << "\" σε όλους τους καθηγητές του τμήματος με επιτυχία!\n";
};
void Record::addGrade(const Student &student, Lesson &lesson, int grade)
{
  for (int i = 0; i < this->students.size(); i++)
  {
    if (this->students[i].getRegistrationNumber() == student.getRegistrationNumber())
    {
      std::vector<float> grades = lesson.getGrades();
      grades[i] = grade;
      lesson.setGrades(grades);
      return;
    }
  }
}
void Record::fixGrade(const Student &student, Lesson &lesson, int grade)
{
  for (int i = 0; i < this->students.size(); i++)
  {
    if (this->students[i].getRegistrationNumber() == student.getRegistrationNumber())
    {
      std::vector<float> grades = lesson.getGrades();
      grades[i] = grade;
      lesson.setGrades(grades);
      return;
    }
  }
};

void Record::saveToCsv(const string &filename) {
};

void Record::loadFromCsv(const string &filename) {

};