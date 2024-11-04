#include <iostream>
#include <unordered_map>
#include <string>
#include <cctype>

using namespace std;

int main(void)
{
  unordered_map<char, string> phonetic = {
      {'a', "alfa"},
      {'b', "bravo"},
      {'c', "charlie"},
      {'d', "delta"},
      {'e', "echo"},
      {'f', "foxtrot"},
      {'g', "golf"},
      {'h', "hotel"},
      {'i', "india"},
      {'j', "juliett"},
      {'k', "kilo"},
      {'l', "lima"},
      {'m', "mike"},
      {'n', "november"},
      {'o', "oscar"},
      {'p', "papa"},
      {'q', "quebec"},
      {'r', "romeo"},
      {'s', "sierra"},
      {'t', "tango"},
      {'u', "uniform"},
      {'v', "victor"},
      {'w', "whiskey"},
      {'x', "x-ray"},
      {'y', "yankee"},
      {'z', "zulu"},
  };

  char ch;
  cout << "Enter a string of characters (. to end): ";
  do
  {
    if (isalpha(ch) && isupper(ch))
    {
      string phonetic_word = phonetic[tolower(ch)];
      phonetic_word[0] = toupper(phonetic_word[0]);
      cout << phonetic_word;
    }
    else if (isalpha(ch) && islower(ch))
    {
      string phonetic_word = phonetic[ch];
      cout << phonetic_word;
    }
    else if (isdigit(ch))
    {
      cout << string((ch - '0'), '*');
    }
    else
    {
      cout << ch;
    }
  } while ((ch = getchar()) != '.');

  return 0;
}