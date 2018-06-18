/**************************************************
This program uses parameters and pass by values to
create functions and display information.
Author: Christian Carreras
**************************************************/

#include <iostream>
#include <string>
using namespace std;

void displayNameAge(string , int); //Function with name and age
void displaySumDifference(int, int); //Function with sum and difference

int main() //Main function
{
  int age, num1, num2, sum, difference;
  string name;

  //Ask user for name and age
  cout << "What is your name? ";
  getline(cin, name);
  cout << "How old are you? ";
  cin >> age;

  //Ask user for any two integers
  cout << "Please enter an integer: ";
  cin >> num1;
  cout << "Please enter another integer: ";
  cin >> num2;

  //Call functions
  displayNameAge(name, age);

  displaySumDifference(num1, num2);

  return 0;
}

//Name and age function
void displayNameAge(string name, int age)
{
  cout << "Hello, " << name << endl;
  cout << "You are " << age << " years old.\n";
}

//Sum and differce function
void displaySumDifference(int num1, int num2)
{
  cout << "The sum of the two integers is " << (num1 + num2) <<  ".\n";
  cout << "The difference of the two integers is " << (num1 - num2) << ".\n";
}
