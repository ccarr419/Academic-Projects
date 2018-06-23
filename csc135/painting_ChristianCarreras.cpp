/***********************************************************************

This program uses pass by values and pass by references in seperate 
functions to create an interface that calculates the total price
of the labor and price of paint per gallon involved in painting
a space in square feet. The user enters the values of the
amount of space to be painted and the price of the paint.

Author: Christian Carreras
Class: CSC 135
Due Date: 11/06/2012

**********************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

//Seperate functions
void displayInstructions();
void getSqft(float&sqft1);
float getCostPaint();
void calcJob(float sqft2, float&job1);
void calcCostPaint(float job2, float costpergallon2, float&paintcost1);
void calcCostLabor(float job3, float&labor1);
void calcTotalCost(float paintcost2, float labor2, float&totalcost1);

//Main function
int main()
{
  //Variables
  float sqft, costpergallon, job, paintcost, labor, totalcost;
  //Function calls
  displayInstructions();
  getSqft(sqft);
  costpergallon = getCostPaint();
  if(costpergallon < 10) //If the entered amount for paint is less than $10.
    {
      cout << "Cost of paint per gallon cannot be less than $10.\n\n";
    }
  else //Everything else
    {
      //More function calls
      calcJob(sqft, job);
      calcCostPaint(job, costpergallon, paintcost);
      calcCostLabor(job, labor);
      calcTotalCost(paintcost, labor, totalcost);

      //Display information
      cout << setprecision(2) << fixed;
      cout << "Square feet:\t" << sqft << endl;
      cout << "Paint cost:\t$" << paintcost << endl;
      cout << "Labor cost:\t$" << labor << endl;
      cout << "Total cost:\t$" << totalcost << endl << endl;
    }
  return 0;
}

/****************************************
This function displays the instructions
for the user to follow.
****************************************/
void displayInstructions()
{
  cout << "\n\t========================================\t\n";
  cout << "\t\tPainting Cost Calculator\t\t\n";
  cout << "\t========================================\t\n";
  cout << "This program will calculate the total cost of a space to be\n";
  cout << "painted based on the cost of the paint per gallon and the labor\n";
  cout << "required to complete the job. The amount of space to be painted\n";
  cout << "is to be entered in square feet and the cost per gallon of paint\n";
  cout << "cannot be less than $10.\n\n";
}

/*************************************
This function asks the user for the
amount of square feet to be painted.
*************************************/
void getSqft(float&sqft1)
{
  cout << "How many square feet of space needs to be painted? ";
  cin >> sqft1;
}

/****************************************
This function gets the cost of paint per
gallon and returns the value back to
the main function.
****************************************/
float getCostPaint()
{
  float costpergallon1;
  cout << "What is the price of the paint per gallon? $";
  cin >> costpergallon1;
  cout << endl;
  return costpergallon1;
}

/****************************************
This function calculates the number for
future functions.
****************************************/
void calcJob(float sqft2, float&job1)
{
  job1 = sqft2/115;
}

/***************************************
This function calculates the number of
gallons required for the number of 
square feet entered.
***************************************/
void calcCostPaint(float job2, float costpergallon2, float&paintcost1)
{
  paintcost1 = job2*costpergallon2;
}

/***************************************
This function calculates the number of
hours required in labor for the amount
of square feeet entered.
***************************************/
void calcCostLabor(float job3, float&labor1)
{
  labor1 = job3*(8*18.00);
}

/****************************************
This program adds the price for gallons
of paint used and the price for labor
hours for a total price.
****************************************/
void calcTotalCost(float paintcost1, float labor2, float&totalcost1)
{
  totalcost1 = paintcost1 + labor2;
}
