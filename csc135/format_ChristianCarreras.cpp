//This program uses setw to format information.
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
int main()
{
  //User inputed variables.
  float gross_profit, net_profit;
  int num_adult_tickets, num_child_tickets;
  string movie;

  //Movie name.
  cout << "What is the name of the movie? ";
  getline(cin, movie);

  //Adult/child tickets.
  cout << "What was the number of adult tickets sold? ";
  cin >> num_adult_tickets;
  cout << "What was the number of child tickets sold? ";
  cin >> num_child_tickets;

  //User inputs values.
  cout << "What was the gross profit? $";
  cin >> gross_profit;
  cout << "What was the net profit? $";
  cin >> net_profit;
  cout << "\n";

  //Format information.
  cout << left;
  cout << setw(30) << "Movie Name:" << movie << endl;
  cout << setw(30) << "Adult Tickets Sold:" << num_adult_tickets << endl;
  cout << setw(30) << "Child Tickets Sold:" << num_child_tickets << endl;
  cout << setw(30) << "Gross Box Office Profit:" << "$" << gross_profit << endl;
  cout << setw(30) << "Net Box Office Profit:" << "$" << net_profit << endl;

  return 0;
}
