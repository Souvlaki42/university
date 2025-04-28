#include <iostream>
#include <string>
#include <ctime>

using namespace std;

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
  Person(char *ID, string name, int birthYear)
  {
    this->ID = ID;
    this->name = name;
    this->birthYear = birthYear;
    this->address = "Άγνωστο";
    this->phone = "Άγνωστο";
    this->email = "Άγνωστο";
  }

  Person(char *ID, string name, int birthYear, string address, string phone, string email)
  {
    this->ID = ID;
    this->name = name;
    this->birthYear = birthYear;
    this->address = address;
    this->phone = phone;
    this->email = email;
  }

  Person(const Person &)
  {
    cout << "Γιατί αντιγράφεις τον/την " << this->name << ";" << endl;
  }

  ~Person()
  {
    delete this->ID;
    cout << "Αντίο " << this->name << "!" << endl;
  }

  char *getID()
  {
    cout << "" << endl;
    return this->ID;
  }

  void setID(char *ID)
  {
    this->ID = ID;
  }

  string getName()
  {
    return this->name;
  }

  void setName(string name)
  {
    this->name = name;
  }

  int getBirthYear()
  {
    return this->birthYear;
  }

  void setBirthYear(int birthYear)
  {
    this->birthYear = birthYear;
  }

  string getAddress()
  {
    return this->address;
  }

  void setAddress(string address)
  {
    this->address = address;
  }

  string getPhone()
  {
    return this->phone;
  }

  void setPhone(string phone)
  {
    this->phone = phone;
  }

  string getEmail()
  {
    return this->email;
  }

  void setEmail(string email)
  {
    this->email = email;
  }

  int getAge()
  {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int age = (1900 + ltm->tm_year) - this->birthYear;
    cout << "Είμαι " << age << " χρονών!" << endl;
    return age;
  }
};