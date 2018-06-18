//This program uses for-loops to process array elements.
//Author: Christian Carreras
#include <iostream>
using namespace std;
int main()
{
  //Declare array and variables
  int number[10];
  int i, highest, lowest, sum, average, counter;
  sum = 0;
  counter = 0;

  //For-loop that asks user for 10 numbers
  for(i = 0; i < 10; i++)
    {
      cout << "Please enter a number: ";
      cin >> number[i];
    }

  //For-loop that restates the numbers in the entered order
  cout << "\nYou entered: ";

  for(i = 0; i < 10; i++)
    {
      cout << number[i] << " ";
    }

  //For-loop that states the numbers in reverse order
  cout << "\nReverse order: ";

  for(i = 9; i >= 0; i--)
    {
      cout << number[i] << " ";
    }

  cout << endl;

  //For-loop that finds the highest number
  highest = number[0];

  for(i = 0; i < 10; i++)
    {
      if(number[i] > highest)
	highest = number[i];
    }

  cout << "The highest grade is " << highest << endl;

  //For-loop that finds the lowest grade
  lowest = number[0];

  for(i = 0; i < 10; i++)
    {
      if(number[i] < lowest)
	lowest = number[i];
    }

  cout << "The lowest grade is " << lowest << endl;


  //For-loop that finds the average grade
  for(i = 0; i < 10; i++)
    {
      sum+=number[i];
    }

  average = sum/10;

  cout << "The average grade is " << average << endl;

  //For-loop that finds how many numbers were above average
  for(i = 0; i < 10; i++)
    {
      if(number[i] > average)
	counter++;
    }

  cout << "There are " << counter << " grades above average\n";

  return 0;
}
