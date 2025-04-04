#include <iostream>
#include <cstring>

using namespace std;

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

void add_string(char **&list, int &list_length, const char *str_input)
{
  for (int i = 0; i < list_length; i++)
  {
    if (strcmp(str_input, list[i]) == 0)
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

  new_strings[list_length] = new char[strlen(str_input) + 1];
  strcpy(new_strings[list_length], str_input);

  delete[] list;

  list = new_strings;
  list_length++;
}

void remove_string(char **&list, int &list_length, const char *str_input)
{
  int index_to_remove = -1;
  for (int i = 0; i < list_length; i++)
  {
    if (strcmp(str_input, list[i]) == 0)
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
  const int MAX_INPUT = 200;

  system("clear");
  char choice, **strings = nullptr;
  int number_of_strings = 0;
  char *str_input = new char[MAX_INPUT];

  cout << "1. Εισαγωγή συμβολοσειράς" << endl;
  cout << "2. Διαγραφή συμβολοσειράς" << endl;
  cout << "3. Τύπωμα όλων των συμβολοσειρών" << endl;
  cout << "4. Έξοδος" << endl;

  while (choice != '4')
  {
    cout << "Επιλέξτε λειτουργια: ";
    choice = getchar();
    while (getchar() != '\n')
      ;

    switch (choice)
    {
    case '1':
      system("clear");
      cout << "Δώστε μία νέα συμβολοσειρά: ";
      fgets(str_input, MAX_INPUT, stdin);
      add_string(strings, number_of_strings, str_input);
      break;
    case '2':
      system("clear");
      cout << "Δώστε μία υπάρχουσα συμβολοσειρά: ";
      fgets(str_input, MAX_INPUT, stdin);
      remove_string(strings, number_of_strings, str_input);
      break;
    case '3':
      system("clear");
      print_list(strings, number_of_strings);
      break;
    case '4':
      continue;
    default:
      system("clear");
      cout << "Λάθος αριθμός λειτουργίας. Επιλέξτε έναν αριθμό από το 1 εώς το 4." << endl;
    }
  }

  for (int i = 0; i < number_of_strings; i++)
  {
    delete[] strings[i];
  }
  delete[] strings;
  delete[] str_input;

  return 0;
}