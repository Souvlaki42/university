#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <ctime>
#include <cstring>

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

  char *getID();
  void setID(char *ID);

  string getName();
  void setName(string name);

  int getBirthYear();
  void setBirthYear(int birthYear);

  string getAddress();
  void setAddress(string address);

  string getPhone();
  void setPhone(string phone);

  string getEmail();
  void setEmail(string email);

  int getAge();
};

#endif
