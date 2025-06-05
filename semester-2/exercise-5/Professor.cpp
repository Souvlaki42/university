#include "Professor.h"
#include <iostream>

Professor::Professor(const char *ID, const string &name, int birthYear, const string &code, const string &specialty)
    : Person(ID, name, birthYear), code(code), specialty(specialty) {}

Professor::Professor(const char *ID, const string &name, int birthYear, const string &address, const string &phone, const string &email, const string &code, const string &specialty)
    : Person(ID, name, birthYear, address, phone, email), code(code), specialty(specialty) {}

Professor::Professor(const Professor &other) : Person(other), code(other.code), specialty(other.specialty) {}

string Professor::getCode() const
{
  return this->code;
}

void Professor::setCode(const string &code)
{
  this->code = code;
}

string Professor::getSpecialty() const
{
  return this->specialty;
}

void Professor::setSpecialty(const string &specialty)
{
  this->specialty = specialty;
}

Professor &Professor::operator=(const Professor &other)
{
  if (this == &other)
  {
    return *this;
  }

  Person::operator=(other);

  this->code = other.code;
  this->specialty = other.specialty;

  return *this;
}