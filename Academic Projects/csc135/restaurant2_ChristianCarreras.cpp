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
#include <fstream>
#include <iomanip>
using namespace std;

float getSum(ifstream &fp);

int main()
{
  ifstream fp;
  fp.open("bill.dat");
  if(!fp)
    {
      cout << "Error opening file\n";
      return 0;
    }

  const float tax = 0.06; //Pa state tax 6%.

  //Variables.
  float tip, salestax, total, people;
  float sum = getSum(fp);
  int i;



  //Calculate tip relative to number of people
  //at the table. If < 5 then use 18%.
  //If >= 5 then use 20%.
  for(i = 0; i < 4; i++)
    {
  if(people < 5)
    {
    tip = sum * 0.18;
    }

  else if(people >= 5)
    {
    tip = sum *0.20;
    }
  
  //Calculate sales tax and total.
  salestax = sum * tax;
  total = sum + salestax + tip;

  //Display information (Restaurant Bill
  cout << setprecision(2) << fixed; //setprecision to 2 decimal places.
  cout << "\nPeople:\t\t" << people << endl;
  cout << "Subtotal:\t$" << sum << endl;
  cout << "Sales Tax:\t$" << salestax << endl;
  cout << "Tip:\t\t$" << tip << endl;
  cout << "Total:\t\t$" << total << endl;
    }
  return 0;
}

float getSum(ifstream &fp)
{
  float num, sum = 0;
  while (fp.eof()==false)
    {
      fp>>num;
      sum+=num;
    }
  return sum;
}
