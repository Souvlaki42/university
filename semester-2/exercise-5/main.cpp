#include <iostream>
#include "Person.h"

using std::cout;

#define CAPACITY 3

//! Instructions: https://docs.google.com/document/d/1nMDT4gnUEltD7OcAKuQf_lIiVbFMjDZRmQ_88wc7eyA/edit?tab=t.0
int main()
{
  Person **people_list = new Person *[CAPACITY];
  for (int i = 0; i < CAPACITY; i++)
  {
    people_list[i] = nullptr;
  }

  char id[] = "12345";
  people_list[0] = new Person(id, "Ιωάννης Παπαδόπουλος", 1990);

  char id2[] = "096743";
  people_list[1] = new Person(id2, "Κώστας Γουρούνας", 1965, "Αιόλου 65", "6986529881", "kgourounas65@gmail.com");

  people_list[2] = new Person(*people_list[0]);

  cout << people_list[0]->getAge() << "\n";
  people_list[1]->setPhone("6976781234");
  cout << people_list[1]->getPhone() << "\n";

  for (int i = 0; i < CAPACITY; i++)
  {
    if (people_list[i] != nullptr)
    {
      delete people_list[i];
      people_list[i] = nullptr;
    }
  }
  delete[] people_list;
  people_list = nullptr;
}