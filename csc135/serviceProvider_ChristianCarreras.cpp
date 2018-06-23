/*****************************************************************
Project 2
This program uses switch and if/else statements to create a menu
system which tells the user how much he/she owes for the month
Author: Christian Carreras
Class: CSC 135
Date Due: 10/18/2012
******************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
  //Declare variables
  char choice; //User's choice
  float price_a, price_b, price_c; //Price of the choice

  cout << endl;
  cout << "What package did you purchase? [A, B, C]: "; //Menu
  cin >> choice;

  switch (choice) //Switch statement
    {
    case 'A': //If user enters A
      int hours1;
      price_a = 9.95; //Package A
      cout << "How many hours did you use? "; //Ask user for hours
      cin >> hours1;
      cout << endl;
      if (hours1 > 10) //If the hours entered are greater than 10
	{
	  float output; 
	  output = price_a + (hours1 - 10) * 2.00; //Calculate
	  cout << setprecision(2) << fixed; // Display results
	  cout << choice << setw(10) << hours1 << setw(10) << "$" << output << endl; 
	}
      else //If the hours entered are less than 10
	cout << choice << setw(10) << hours1 << setw(10) << "$" << price_a << endl;
      break;
    case 'B': //If user enters B
      int hours2;
      price_b = 14.95; //Package B
      cout << "How many hours did you use? "; //Ask user for hours
      cin >> hours2;
      cout << endl;
      if (hours2 > 20) //If the hours entered are greater than 20
	{
	  float output;
	  output = price_b + (hours2 - 20) * 1.00; //Calculate
	  cout << setprecision(2) << fixed; //Display results
	  cout << choice << setw(10) << hours2 << setw(10) << "$" << output << endl;
	}
      else  //If the hours entered are less than 20
	cout << choice << setw(10) << hours2 << setw(10) << "$" << price_b << endl;
      break;
    case 'C': //If user enters C
      price_c = 19.99; //Package C
      cout << endl; //Display results
      cout << choice << setw(20) << "$" << price_c << endl;
      break;
    default: //If the user enters anything other than A, B or C
      cout << choice << setw(33) << "Invalid entry\n";
      break;
    }
  cout << endl;
  return 0;
}
