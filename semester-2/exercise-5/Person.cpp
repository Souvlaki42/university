#include "Person.h"
#include <iostream>
#include <ctime>
#include <cstring>
using std::cout;

Person::Person(const char *ID, const string &name, int birthYear)
    : name(name), birthYear(birthYear), address("Άγνωστο"), phone("Άγνωστο"), email("Άγνωστο")
{
  if (ID != nullptr)
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

Person::Person(const char *ID, const string &name, int birthYear, const string &address, const string &phone, const string &email)
    : name(name), birthYear(birthYear), address(address), phone(phone), email(email)
{
  if (ID != nullptr)
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

Person::Person(const Person &other)
    : name(other.name), birthYear(other.birthYear), address(other.address), phone(other.phone), email(other.email)
{
  if (other.ID != nullptr)
  {
    this->ID = new char[strlen(other.ID) + 1];
    strcpy(this->ID, other.ID);
  }
  else
  {
    this->ID = new char[1];
    this->ID[0] = '\0';
  }

  cout << "Αντιγράφηκε ο/η " << this->name << "\n";
}

Person::~Person()
{
  delete[] this->ID;
  this->ID = nullptr;
  cout << "Αντίο " << this->name << "!\n";
}

const char *Person::getID() const
{
  return this->ID;
}

void Person::setID(const char *ID)
{
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

void Person::setName(const string &name)
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

void Person::setAddress(const string &address)
{
  this->address = address;
}

string Person::getPhone() const
{
  return this->phone;
}

void Person::setPhone(const string &phone)
{
  this->phone = phone;
}

string Person::getEmail() const
{
  return this->email;
}

void Person::setEmail(const string &email)
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

  delete[] this->ID;

  if (other.ID != nullptr)
  {
    this->ID = new char[strlen(other.ID) + 1];
    strcpy(this->ID, other.ID);
  }
  else
  {
    this->ID = new char[1];
    this->ID[0] = '\0';
  }

  this->name = other.name;
  this->birthYear = other.birthYear;
  this->address = other.address;
  this->phone = other.phone;
  this->email = other.email;

  return *this;
}