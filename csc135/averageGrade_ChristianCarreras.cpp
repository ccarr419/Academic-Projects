//This program calculates the average of grades by using a while loop.
#include <iostream>
using namespace std;
int main()
{
  int timesran;
  float average, sum, grade;
  timesran = 0;
  sum = 0;
  cout << "Enter a grade, enter -1 to end: ";
  cin >> grade;

  while (grade != -1)
    {
      sum+=grade;
      cout << "Enter a grade, enter -1 to end: ";
      cin >> grade;
      timesran++;
    }
  average = sum/timesran;
  cout << "The class average is " << average << ".\n";

  return 0;
} 
