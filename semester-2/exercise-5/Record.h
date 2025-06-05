#ifndef RECORD_H
#define RECORD_H

#include "Student.h"
#include "Lesson.h"
#include "Professor.h"

class Record
{
private:
  vector<Student> students;
  vector<Lesson> lessons;

public:
  void addStudent(const Student &student);
  void fixStudent(const Student &student);
  void removeStudent(const Student &student);
  void addLesson(const Lesson &lesson);
  void fixLesson(const Lesson &lesson);
  void removeLesson(const Lesson &lesson);
  void sendEmailToAllStudents(const string &message);
  void sendEmailToAllProfessors(const string &message);
  void addGrade(const Student &student, Lesson &lesson, int grade);
  void fixGrade(const Student &student, Lesson &lesson, int grade);
  void saveToCsv(const string &filename);
  void loadFromCsv(const string &filename);
};

#endif