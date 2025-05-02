#include "Person.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstring>

using namespace std;

Person::Person(char *ID, string name, int birthYear)
{
  this->ID = ID;
  this->name = name;
  this->birthYear = birthYear;
  this->address = "Άγνωστο";
  this->phone = "Άγνωστο";
  this->email = "Άγνωστο";
}

Person::Person(char *ID, string name, int birthYear, string address, string phone, string email)
{
  this->ID = ID;
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

  cout << "Αντιγράφηκε ο/η " << this->name << endl;
}

Person::~Person()
{
  if (this->ID != nullptr)
  {
    delete[] this->ID;
    this->ID = nullptr;
  }
  cout << "Αντίο " << this->name << "!" << endl;
}

char *Person::getID()
{
  cout << "" << endl;
  return this->ID;
}

void Person::setID(char *ID)
{
  this->ID = ID;
}

string Person::getName()
{
  return this->name;
}

void Person::setName(string name)
{
  this->name = name;
}

int Person::getBirthYear()
{
  return this->birthYear;
}

void Person::setBirthYear(int birthYear)
{
  this->birthYear = birthYear;
}

string Person::getAddress()
{
  return this->address;
}

void Person::setAddress(string address)
{
  this->address = address;
}

string Person::getPhone()
{
  return this->phone;
}

void Person::setPhone(string phone)
{
  this->phone = phone;
}

string Person::getEmail()
{
  return this->email;
}

void Person::setEmail(string email)
{
  this->email = email;
}

int Person::getAge()
{
  time_t now = time(0);
  tm *ltm = localtime(&now);
  int age = (1900 + ltm->tm_year) - this->birthYear;
  return age;
}