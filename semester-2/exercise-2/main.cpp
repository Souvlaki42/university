#include <iostream>
#include <string>

using std::cout, std::cin, std::cerr, std::endl;

void sum_and_factorial(uint N, uint &sum, uint &factorial)
{
  // Resetting the values
  sum = 0;
  factorial = 1;

  // Calculate the sum of numbers from 1 to N
  for (uint i = 1; i <= N; i++)
  {
    if (sum + i > 4294967295)
    {
      sum = 0;
      factorial = 0;
    }
    sum += i;
  }

  // Calculate the factorial of N
  for (uint i = 2; i <= N; i++)
  {
    if (factorial * i > 4294967295)
    {
      sum = 0;
      factorial = 0;
    }
    factorial *= i;
  }
}

// IMPORTANT: Instructions https://docs.google.com/document/d/1lvCpETl5k8R4Q20xrlgCwwrwcmIlm0rnjY2UOOQiQ-Q/edit?tab=t.0
int main()
{
  unsigned long long int sum_of_sums = 0;
  unsigned long long int sum_of_factorials = 0;
  size_t length_of_sums = 0;
  size_t length_of_factorials = 0;
  uint number, sum, factorial;

  for (int i = 0; i < 1000000; i++)
  {
    cin >> number;
    sum_and_factorial(number, sum, factorial);
    if (sum != 0)
    {
      sum_of_sums += sum;
      length_of_sums += 1;
    }

    if (factorial != 0)
    {
      sum_of_factorials += factorial;
      length_of_factorials += 1;
    }
  }

  if (length_of_sums > 0)
  {
    cout << "Mean of sums: " << sum_of_sums / length_of_sums << endl;
  }
  else
  {
    cerr << "Length of sums is 0" << endl;
  }

  if (length_of_factorials > 0)
  {
    cout << "Mean of factorials: " << sum_of_factorials / length_of_factorials << endl;
  }
  else
  {
    cerr << "Length of factorials is 0" << endl;
  }

  return 0;
}
