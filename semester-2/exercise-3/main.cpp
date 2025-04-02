#include <iostream>
#include <cstring>
#include <string>

using std::cout, std::cin, std::endl, std::string;

void print_list(char **list, int list_length)
{
  if (list_length == 0)
  {
    system("clear");
    cout << "Δεν έχετε πρόσθεσει καμοία συμβολοσειρά ακόμα." << endl;
  }
  else
  {
    cout << "Οι συμβολοσειρές σας:" << endl;
    for (int i = 0; i < list_length; i++)
    {
      cout << i + 1 << ". " << list[i] << endl;
    }
  }
}

void add_string(char **&list, int &list_length, string str_input)
{
  for (int i = 0; i < list_length; i++)
  {
    if (strcmp(str_input.c_str(), list[i]) == 0)
    {
      cout << "Αυτή η συμβολοσειρά υπάρχει ήδη στην λίστα σας." << endl;
      return;
    }
  }

  char **new_strings = new char *[list_length + 1];
  for (int i = 0; i < list_length; i++)
  {
    new_strings[i] = new char[strlen(list[i]) + 1];
    strcpy(new_strings[i], list[i]);
  }

  new_strings[list_length] = new char[str_input.length() + 1];
  strcpy(new_strings[list_length], str_input.c_str());

  delete[] list;

  list = new_strings;
  list_length++;
}

void remove_string(char **&list, int &list_length, string str_input)
{
  int index_to_remove = -1;
  for (int i = 0; i < list_length; i++)
  {
    if (strcmp(str_input.c_str(), list[i]) == 0)
    {
      index_to_remove = i;
      break;
    }
  }

  if (index_to_remove == -1)
  {
    cout << "Αυτή η συμβολοσειρά δεν υπάρχει στην λίστα σας." << endl;
    return;
  }

  char **new_strings = new char *[list_length - 1];
  int new_index = 0;
  for (int i = 0; i < list_length; i++)
  {
    if (i != index_to_remove)
    {
      new_strings[new_index] = new char[strlen(list[i]) + 1];
      strcpy(new_strings[new_index], list[i]);
      new_index++;
    }
    else
    {
      delete[] list[i];
    }
  }

  delete[] list;
  list = new_strings;
  list_length--;
}

// IMPORTANT: Instructions https://docs.google.com/document/d/1jNKrjStygBJd4Q_B-kcfwgPWmtULCvQYWqw6VPNtP_k/edit?tab=t.0
int main()
{
  system("clear");
  char choice, **strings = nullptr;
  int number_of_strings = 0;
  string str_input;

  cout << "1. Εισαγωγή συμβολοσειράς" << endl;
  cout << "2. Διαγραφή συμβολοσειράς" << endl;
  cout << "3. Τύπωμα όλων των συμβολοσειρών" << endl;
  cout << "4. Έξοδος" << endl;

  while (true)
  {
    cout << "Επιλέξτε λειτουργια: ";
    choice = getchar();
    while (getchar() != '\n')
      ;
    if (choice == '1')
    {
      system("clear");
      cout << "Δώστε μία νέα συμβολοσειρά: ";
      getline(cin, str_input);
      add_string(strings, number_of_strings, str_input);
    }
    else if (choice == '2')
    {
      system("clear");
      cout << "Δώστε μία υπάρχουσα συμβολοσειρά: ";
      getline(cin, str_input);
      remove_string(strings, number_of_strings, str_input);
    }
    else if (choice == '3')
    {
      system("clear");
      print_list(strings, number_of_strings);
    }
    else if (choice == '4')
    {
      break;
    }
    else
    {
      system("clear");
      cout << "Λάθος αριθμός λειτουργίας. Επιλέξτε έναν αριθμό από το 1 εώς το 4." << endl;
    }
  }

  for (int i = 0; i < number_of_strings; i++)
  {
    delete[] strings[i];
  }
  delete[] strings;

  return 0;
}