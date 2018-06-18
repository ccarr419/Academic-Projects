//This program uses a for loop to calculate subtotal and total
//of user entered values.
#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
  float value, sum, tax, salestax, total;
  int num, counter;
  tax = 0.08;
  sum = 0;

  cout << "How many items are in the order? ";
  cin >> num;

  for (counter=1; counter <= num; counter++)
    {
      cout << "Enter the price of an item: $";
      cin >> value;
      sum+=value;
    }

  salestax = tax*sum;
  total = salestax + sum;
  cout << setprecision(2) << fixed << endl;
  cout << "Subtotal:\t$" << sum << endl;
  cout << "Sales Tax:\t$" << salestax << endl;
  cout << "Total:\t\t$" << total << endl;

    return 0;
}
