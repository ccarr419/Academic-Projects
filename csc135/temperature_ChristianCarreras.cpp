//This program uses if/else to tell the user how cold/warm it is.
#include <iostream>
using namespace std;
int main()
{
  float temperature;

  //Ask user for temperature.
  cout << "What is the current temperature? ";
  cin >> temperature;

  //If/else statements.
  if (temperature < 32)
    cout << "It is freezing today.\n";
  else if (temperature < 59)
    cout << "It is cold today.\n";
  else if (temperature < 86)
    cout << "It is warm today.\n";
  else
    cout << "It is hot today.\n";

  return 0;
}
