#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include "Lesson.h"
#include <vector>

using std::vector;

class Student : public Person
{
private:
  int registrationNumber;
  int semester;
  vector<Lesson> lessons;

public:
  Student(const char *ID, const string &name, int birthYear, int registrationNumber, int semester, vector<Lesson> lessons);
  Student(
      const char *ID,
      const string &name,
      int birthYear,
      const string &address,
      const string &phone,
      const string &email,
      int registrationNumber,
      int semester,
      vector<Lesson> lessons);
  Student(const Student &);

  int getRegistrationNumber() const;
  void setRegistrationNumber(int registrationNumber);
  int getSemester() const;
  void setSemester(int semester);
  vector<Lesson> getLessons() const;
  void setLessons(vector<Lesson> lessons);

  Student &operator=(const Student &other);
};

#endif