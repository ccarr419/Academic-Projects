//This program tells you if you passed or failed your course.
#include <iostream>
using namespace std;
int main()
{
  int grade;

  //Ask user grade/user inputs grade.
  cout << "Please input your grade: ";
  cin >> grade;

  //if/else statements.
  if (grade >= 60)
    cout << "You passed the course.\n";
  else
    cout << "You failed.\n";

  return 0;
}
