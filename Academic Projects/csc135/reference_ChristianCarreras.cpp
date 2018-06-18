/******************************************
This program asks the user to input two 
integers and using pass by reference
will sort the two integers by
smallest to largest.
Author: Christian Carreras
******************************************/

#include <iostream>
using namespace std;

void readInput(int&num1, int&num2);//Asks user for two integers
void sort(int&a, int&b);//Sorts the numbers with the smaller first

int main()
{
  //Variables
  int a, b;
  //Call functions
  readInput(a, b);
  sort(a, b);
  //Prints sorted inputs
  cout << "The number in sorted order: " << a << " " << b << endl;
  return 0;
}

/*********************************
This function asks the user for
two integers and assigns them by
pass by reference to a and b in
the main function.
*********************************/
void readInput(int&num1, int&num2)
{
  cout << "Please enter an integer: ";
  cin >> num1;
  cout << "Please enter another integer: ";
  cin >> num2;
}

/*********************************
This function sorts the inputs
by using if statments to put the
smaller integer fisrt.
*********************************/
void sort(int&a, int&b)
{
  int num3;
  if(b < a || a > b)
    {
      num3 = a;
      a = b;
      b = num3;
    }
} 

