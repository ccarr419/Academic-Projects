//This program uses a while loop and a nested for loop to
//calculate the subtotal of meals for the number of people
//at the table.
#include <iostream>
using namespace std;
int main()
{
  float sum, meal, subtotal;
  int people, num, counter;
  sum = 0;

  cout << "\nHow many people are at the table?: ";
  cin >> people;

  while(people!=0)
    {
      for(counter=0; counter < people; counter++)
	{
	  cout << "Enter the price of the meal: $";
	  cin >> meal;
	  sum+=meal;
	}
      
      cout << "\nSubtotal: $" << sum << endl;

      cout << "\nHow many people are at the table?: ";
      cin >> people;
      sum=0;
    }

  cout << "Bye!\n";

  return 0;
}
