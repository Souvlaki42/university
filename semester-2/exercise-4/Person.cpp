#include "Person.h"
#include <iostream>
#include <ctime>
#include <cstring>

using std::cout;

Person::Person(char *ID, string name, int birthYear)
{
  this->ID = new char[strlen(ID) + 1];
  strcpy(this->ID, ID);
  this->name = name;
  this->birthYear = birthYear;
  this->address = "Άγνωστο";
  this->phone = "Άγνωστο";
  this->email = "Άγνωστο";
}

Person::Person(char *ID, string name, int birthYear, string address, string phone, string email)
{
  this->ID = new char[strlen(ID) + 1];
  strcpy(this->ID, ID);
  this->name = name;
  this->birthYear = birthYear;
  this->address = address;
  this->phone = phone;
  this->email = email;
}

Person::Person(const Person &other)
{
  this->ID = new char[strlen(other.ID) + 1];
  strcpy(this->ID, other.ID);

  this->name = other.name;
  this->birthYear = other.birthYear;
  this->address = other.address;
  this->phone = other.phone;
  this->email = other.email;

  cout << "Αντιγράφηκε ο/η " << this->name << "\n";
}

Person::~Person()
{
  if (this->ID != nullptr)
  {
    delete[] this->ID;
    this->ID = nullptr;
  }
  cout << "Αντίο " << this->name << "!" << "\n";
}

const char *Person::getID() const
{
  return this->ID;
}

void Person::setID(char *ID)
{
  if (this->ID == ID)
    return; // Avoid self-assignment
  if (this->ID != nullptr)
    delete[] this->ID;
  if (ID)
  {
    this->ID = new char[strlen(ID) + 1];
    strcpy(this->ID, ID);
  }
  else
  {
    this->ID = new char[1];
    this->ID[0] = '\0';
  }
}

string Person::getName() const
{
  return this->name;
}

void Person::setName(string name)
{
  this->name = name;
}

int Person::getBirthYear() const
{
  return this->birthYear;
}

void Person::setBirthYear(int birthYear)
{
  this->birthYear = birthYear;
}

string Person::getAddress() const
{
  return this->address;
}

void Person::setAddress(string address)
{
  this->address = address;
}

string Person::getPhone() const
{
  return this->phone;
}

void Person::setPhone(string phone)
{
  this->phone = phone;
}

string Person::getEmail() const
{
  return this->email;
}

void Person::setEmail(string email)
{
  this->email = email;
}

int Person::getAge() const
{
  time_t now = time(0);
  tm *ltm = localtime(&now);
  int age = (1900 + ltm->tm_year) - this->birthYear;
  return age;
}

Person &Person::operator=(const Person &other)
{
  if (this == &other)
    return *this;

  if (this->ID != nullptr)
    delete[] this->ID;

  this->ID = new char[strlen(other.ID) + 1];
  strcpy(this->ID, other.ID);

  this->name = other.name;
  this->birthYear = other.birthYear;
  this->address = other.address;
  this->phone = other.phone;
  this->email = other.email;

  return *this;
}