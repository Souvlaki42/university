#include "Lesson.h"
#include <iostream>
using std::cout, std::vector;

Lesson::Lesson(const string &code, const string &name, int semester, Professor &professor)
    : code(code), name(name), semester(semester), professor(professor) {}

Lesson::Lesson(const Lesson &other)
    : code(other.code), name(other.name), semester(other.semester), professor(other.professor), grades(other.grades)
{
  cout << "Αντιγράφηκε το μάθημα " << this->name << "\n";
}

Lesson::~Lesson()
{
  cout << "Διαγράφηκε το μάθημα " << this->name << "!\n";
}

string Lesson::getCode() const { return code; }
string Lesson::getName() const { return name; }
int Lesson::getSemester() const { return semester; }
Professor Lesson::getProfessor() const { return professor; }
vector<float> Lesson::getGrades() const { return grades; }

void Lesson::setCode(const string &code) { this->code = code; }
void Lesson::setName(const string &name) { this->name = name; }
void Lesson::setSemester(int semester) { this->semester = semester; }
void Lesson::setProfessor(const Professor &professor) { this->professor = professor; }
void Lesson::setGrades(const vector<float> &grades) { this->grades = grades; }

Lesson &Lesson::operator=(const Lesson &other)
{
  if (this == &other)
    return *this;

  code = other.code;
  name = other.name;
  semester = other.semester;
  professor = other.professor;
  grades = other.grades;

  return *this;
}