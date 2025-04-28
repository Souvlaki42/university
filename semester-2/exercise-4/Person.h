#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <ctime>

class Person
{
private:
  char *ID;
  std::string name;
  int birthYear;
  std::string address;
  std::string phone;
  std::string email;

public:
  Person(char *ID, std::string name, int birthYear);
  Person(
      char *ID,
      std::string name,
      int birthYear,
      std::string address,
      std::string phone,
      std::string email);
  Person(const Person &);
  ~Person();

  char *getID();
  void setID(char *ID);

  std::string getName();
  void setName(std::string name);

  int getBirthYear();
  void setBirthYear(int birthYear);

  std::string getAddress();
  void setAddress(std::string address);

  std::string getPhone();
  void setPhone(std::string phone);

  std::string getEmail();
  void setEmail(std::string email);

  int getAge();
};

#endif
