#include "Student.h"
#include <iostream>

Student::Student(const char *ID, const string &name, int birthYear, int registrationNumber,
                 int semester,
                 vector<Lesson> lessons)
    : Person(ID, name, birthYear), registrationNumber(registrationNumber), semester(semester), lessons(lessons) {}

Student::Student(const char *ID, const string &name, int birthYear, const string &address, const string &phone, const string &email, int registrationNumber,
                 int semester,
                 vector<Lesson> lessons)
    : Person(ID, name, birthYear, address, phone, email), registrationNumber(registrationNumber), semester(semester), lessons(lessons) {}

Student::Student(const Student &other) : Person(other), registrationNumber(other.registrationNumber), semester(other.semester), lessons(other.lessons) {}

int Student::getRegistrationNumber() const
{
  return this->registrationNumber;
}

void Student::setRegistrationNumber(int registrationNumber)
{
  this->registrationNumber = registrationNumber;
}

int Student::getSemester() const
{
  return this->semester;
}

void Student::setSemester(int semester)
{
  this->semester = semester;
}
vector<Lesson> Student::getLessons() const
{
  return this->lessons;
}

void Student::setLessons(vector<Lesson> lessons)
{
  this->lessons = lessons;
}

Student &Student::operator=(const Student &other)
{
  if (this == &other)
  {
    return *this;
  }

  Person::operator=(other);

  this->registrationNumber = other.registrationNumber;
  this->semester = other.semester;
  this->lessons = other.lessons;

  return *this;
}