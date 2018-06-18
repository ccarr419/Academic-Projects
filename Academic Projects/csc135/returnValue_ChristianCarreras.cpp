/*********************************************************
This program uses parameters and pass by values to
calculate the total tickets sold, total ticket price and
total tax.
Author: Christian Carreras
*********************************************************/ 

#include <iostream>
using namespace std;

//Function prototypes
int getNumber(); //No parameters, returns value
float calculateTotal(int tickets1); //Returns value
float calculateTax(float total1); //Returns value
void displayResult(int tickets2, float total2, float tax1); //Returns no value

//Main function
int main()
{
  //Variables
  int ticketssold;
  float total, totaltax;

  //Call functions with return values
  ticketssold = getNumber();
  total = calculateTotal(ticketssold);
  totaltax = calculateTax(total);
  //Call function with void return type
  displayResult(ticketssold, total, totaltax);
  return 0;
}

/*****************************************
This fuction asks for the total tickets
sold and returns the value back to the 
main function.
*****************************************/
int getNumber()
{
  int tickets;
  cout << "How many tickets were sold? ";
  cin >> tickets;
  cout << endl;
  return tickets;
}

/**********************************
This function calculates the total
of price of every ticket sold and 
returns it to the main function.
**********************************/
float calculateTotal(int tickets1)
{
  float ticketprice;
  ticketprice = tickets1 * 10.99;
  return ticketprice;
}

/*********************************
This function calculates the total
tax from the total ticket price
and returns the value to the main
function.
*********************************/
float calculateTax(float total1)
{
  float tax;
  tax = total1 * 0.06;
  return tax;
}

/*********************************************************
This fuction displays tickets sold, total sales and tax
when called in the main function.
*********************************************************/
void displayResult(int tickets2, float total2, float tax1)
{
  cout << "Tickets Sold:\t" << tickets2 << endl;
  cout << "Total Sales:\t$" << total2 << endl;
  cout << "Tax\t\t$" << tax1 << endl;
}
