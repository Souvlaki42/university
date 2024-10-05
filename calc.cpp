#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

vector<string> split(string &s, const string &delimiter)
{
  vector<string> tokens;
  size_t pos = 0;
  string token;
  while ((pos = s.find(delimiter)) != string::npos)
  {
    token = s.substr(0, pos);
    tokens.push_back(token);
    s.erase(0, pos + delimiter.length());
  }
  tokens.push_back(s);

  return tokens;
}

int main()
{
  string expression;
  cout << "Welcome to Calculator++!" << endl;
  cout << "Enter an expression: ";
  getline(cin, expression);

  vector<string> tokens = split(expression, " ");

  if (tokens.size() != 3)
  {
    cout << "Invalid expression!" << endl;
    return 1;
  }

  double result;

  double a = stoi(tokens[0]);
  char op = tokens[1][0];
  double b = stoi(tokens[2]);

  switch (op)
  {
  case '+':
    result = a + b;
    break;
  case '-':
    result = a - b;
    break;
  case '*':
    result = a * b;
    break;
  case '/':
    result = a / b;
    break;
  case '^':
    result = pow(a, b);
    break;
  case '%':
    result = fmod(a, b);
    break;
  default:
    cout << "Invalid operator!" << endl;
    return 1;
  }

  cout << "Result: " << result << endl;

  return 0;
}