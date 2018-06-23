/*This program takes the total colleted sales and calculates to find the
product sales, county tax sales, state tax sales and total sales tax.
Author: Christian Carreras
Due Date: 10/2/2012*/

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
int main()
{
  //Declaring constant values.
  const float PRODUCT_SALES = 1.06;
  const float COUNTY_TAX = 0.02;
  const float STATE_TAX = 0.04;
  const float TOTAL_TAX = 0.06;

  //Declaring variables.
  float total_collected, product_sales, county_sales_tax;
  float state_sales_tax, total_sales_tax;
  int year;

  //Declaring string variable.
  string month;

  //Ask user for month.
  cout << "\nPlease enter the current month: ";
  cin >> month;

  //Ask user for year.
  cout << "Please enter the current year: ";
  cin >> year;

  //Ask user for the total amount collected.
  cout << "Please enter the total amount collected: $";
  cin >> total_collected;
  cout << endl;

  //Calculate taxes and sales.
  product_sales = total_collected / PRODUCT_SALES;
  county_sales_tax = product_sales * COUNTY_TAX;
  state_sales_tax = product_sales * STATE_TAX;
  total_sales_tax = product_sales * TOTAL_TAX;

  //Display information to user.
  cout.precision(2); //Changes the decimal precision to 2.
  cout << fixed; //Forces variables to be a fixed number.
  cout << left; //Changes orientation to left.
  cout << setw(8) << "Month:" << month << endl;
  cout << setw(8) << "Year:" << year << endl;
  cout << "---------------------------------\n";
  cout << setw(22) << "Total Collected:" << "$" << total_collected << endl;
  cout << setw(22) << "Product Sales:" << "$" << product_sales << endl;
  cout << setw(22) << "County Sales Tax: " << "$" << county_sales_tax << endl;
  cout << setw(22) << "State Sales Tax:" << "$" << state_sales_tax << endl;
  cout << setw(22) << "Total Sales Tax:" << "$" << total_sales_tax << endl;
  cout << endl;

  return 0;
}
