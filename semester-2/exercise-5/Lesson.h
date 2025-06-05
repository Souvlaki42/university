#ifndef LESSON_H
#define LESSON_H

#include <string>
#include <vector>
#include "Professor.h"
using std::string, std::vector;

class Lesson
{
private:
  string code;
  string name;
  int semester;

  Professor &professor;
  vector<float> grades;

public:
  Lesson(const string &code, const string &name, int semester, Professor &professor);
  Lesson(const Lesson &);
  ~Lesson();

  string getCode() const;
  string getName() const;
  int getSemester() const;
  Professor getProfessor() const;
  vector<float> getGrades();

  void setCode(const string &code);
  void setName(const string &name);
  void setSemester(int semester);
  void setProfessor(const Professor &professor);
  void setGrades(const vector<float> &grades);

  Lesson &operator=(const Lesson &other);
};

#endif