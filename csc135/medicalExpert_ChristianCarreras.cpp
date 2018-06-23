//This program diagnoses the user
#include <iostream>
using namespace std;
int main()
{
  char answer1, answer2, answer3;

  cout << "Are you coughing? [y/n]: ";
  cin >> answer1;

  if (answer1 == 'y')
    {
      cout << "Are you short of breath or weezing? [y/n]: ";
      cin >> answer2;
      
      if (answer2 == 'y')
	cout << "You possibly have pneumonia or an infection of the airways\n";

      else if (answer2 == 'n')
	  cout << "You have a possible viral infection\n";
      else 
	cout << "Invalid entry\n";
    }
  else if (answer1 == 'n')
    {
      cout << "Do you have a headache? [y/n]: ";
      cin >> answer3;

      if (answer3 == 'y')
      cout << "You have a possiblity of meningitis\n";

      else if (answer3 == 'n')
      cout << "You are healthy\n";

      else
	cout << "Invalid entry\n";
    }
  else 
    cout << "Invalid entry\n";

return 0;
}
