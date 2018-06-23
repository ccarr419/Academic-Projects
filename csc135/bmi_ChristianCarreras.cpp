//This program calculates the user's bmi
#include <iostream>
#include <string>
using namespace std;

int main()
{
  string name;
  float weight, height, bmi;

  cout << "What is your name? ";
  getline(cin, name);

  cout << "What is your weight in pounds? ";
  cin >> weight;

  cout << "What is your height in inches? ";
  cin >> height;

  bmi = (703*weight)/(height*height);

  cout << "Hello, " << name << endl;
  cout << "Your weight is " << weight << " pounds.\n";
  cout << "Your height is " << height << " inches.\n";
  cout << "Your body mass index is " << bmi << "." << endl;

  return 0;
}
