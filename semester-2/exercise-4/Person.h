#ifndef PERSON_H
#define PERSON_H

#include <string>

using std::string;

class Person
{
private:
  char *ID;
  string name;
  int birthYear;
  string address;
  string phone;
  string email;

public:
  Person(char *ID, string name, int birthYear);
  Person(
      char *ID,
      string name,
      int birthYear,
      string address,
      string phone,
      string email);
  Person(const Person &);
  ~Person();

  const char *getID() const;
  void setID(char *ID);

  string getName() const;
  void setName(string name);

  int getBirthYear() const;
  void setBirthYear(int birthYear);

  string getAddress() const;
  void setAddress(string address);

  string getPhone() const;
  void setPhone(string phone);

  string getEmail() const;
  void setEmail(string email);

  int getAge() const;

  Person &operator=(const Person &other);
};

#endif
