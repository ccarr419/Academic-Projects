/****************************************************************************

Project 4: Loops (Restaurant Bill)

This program uses while and for loops as well as nested loops to create
an interface for a restaurant which asks the user for how many people
were at the table and the price of their meals (assuming 1 meal per person)
Then the program will display the subtotal, sales tax, tip and total.
The program terminates when the user enters 0 or any value less than 0.

Author: Christian Carreras
Course: CSC 135
Due Date: 11/27/2012

****************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
  const float tax = 0.06; //Pa state tax 6%.

  //Variables.
  float sum, meal, salestax, tip, total;
  int people, num, counter;
  sum = 0;

  //Ask user for the number of people at the table.
  cout << "\nHow many people are at the table?: ";
  cin >> people;

  //If the user entered any number greater than or equal to 0.
  if(people >= 0)
    {

      //While loop for when the entered value is not 0.
      while(people != 0)
	{
	  //Nested for loop which gathers the price of the meals
	  //relative to the number of people at the table.
	  for(counter = 0; counter < people; counter++)
	    {
	      cout << "Enter the price of the meal: $";
	      cin >> meal;
	      sum+=meal; //Add up all the meal values.
	    }

	  //Calculate tip relative to number of people
	  //at the table. If < 5 then use 18%.
	  //If >= 5 then use 20%.
	  if(people < 5)
	    tip = sum * 0.18;

	  else if(people >= 5)
	    tip = sum *0.20;

	  //Calculate sales tax and total.
	  salestax = sum * tax;
	  total = sum + salestax + tip;

	  //Display information (Restaurant Bill)
	  cout << setprecision(2) << fixed; //setprecision to 2 decimal places.
	  cout << "\nPeople:\t\t" << people << endl;
	  cout << "Subtotal:\t$" << sum << endl;
	  cout << "Sales Tax:\t$" << salestax << endl;
	  cout << "Tip:\t\t$" << tip << endl;
	  cout << "Total:\t\t$" << total << endl;

	  //Reinterate loop by asking for the number of people at
	  //the table again.
	  cout << "\nHow many people are at the table?: ";
	  cin >> people;
	  sum = 0; //Reset sum to 0.
	}

      //When the user enters 0.
      cout << "Goodbye\n\n";
    }

  //When the user enters any value < 0.
  else
    cout << "Invalid Entry!\n\n";

  return 0;
}
