//This program uses a menu and switch statements to do problems
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
  //variable for choice
  int choice;

  // menu
  cout << "What do you want to do?\n";
  cout << "1.  Compute area of a circle\n";
  cout << "2.  Compute area of a rectangle\n";
  cout << "3.  Compute area of a triangle\n";
  cout << "4.  None of them\n";
  cin >> choice;

  switch (choice) //switch statement
    {
    case 1: // area of a circle
      float radius, area_circle;
      cout << "What is the radius of the circle? ";
      cin >> radius;
      area_circle = 3.14*pow(radius, 2);
      cout << "The answer is " << area_circle << endl;
      break;
    case 2: // area of a rectangle
      float length, width, area_rectangle;
      cout << "What is the length of the rectangle? ";
      cin >> length;
      cout << "What is the width of the rectangle? ";
      cin >> width;
      area_rectangle = length*width;
      cout << "The answer is " << area_rectangle << endl;
      break;
    case 3: // area of a triangle
      float base, height, area_triangle;
      cout << "What is the base of the triangle? ";
      cin >> base;
      cout << "What is the height of the triangle? ";
      cin >> height;
      area_triangle = 0.5*base*height;
      cout << "The answer is " << area_triangle << endl;
      break;
    case 4: // end program
      break;
    default: // entry other than 1-4
      cout << "Invalid entry\n";
      break;
    }
  return 0;
}



