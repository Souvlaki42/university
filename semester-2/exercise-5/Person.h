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
  Person(const char *ID, const string &name, int birthYear);
  Person(
      const char *ID,
      const string &name,
      int birthYear,
      const string &address,
      const string &phone,
      const string &email);
  Person(const Person &);
  ~Person();

  const char *getID() const;
  void setID(const char *ID);

  string getName() const;
  void setName(const string &name);

  int getBirthYear() const;
  void setBirthYear(int birthYear);

  string getAddress() const;
  void setAddress(const string &address);

  string getPhone() const;
  void setPhone(const string &phone);

  string getEmail() const;
  void setEmail(const string &email);

  int getAge() const;

  Person &operator=(const Person &other);
};

#endif
