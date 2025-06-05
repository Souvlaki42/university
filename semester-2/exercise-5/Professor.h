#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "Person.h"
#include <string>

using std::string;

class Professor : public Person
{
private:
  string code;
  string specialty;

public:
  Professor(const char *ID, const string &name, int birthYear, const string &code, const string &specialty);
  Professor(
      const char *ID,
      const string &name,
      int birthYear,
      const string &address,
      const string &phone,
      const string &email,
      const string &code,
      const string &specialty);
  Professor(const Professor &);

  string getCode() const;
  void setCode(const string &code);
  string getSpecialty() const;
  void setSpecialty(const string &specialty);

  Professor &operator=(const Professor &other);
};

#endif