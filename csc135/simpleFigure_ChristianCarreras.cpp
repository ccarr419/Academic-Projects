#include <iostream>
using namespace std;

void drawCircle();
void drawIntersect();
void drawBase();

int main()
{
  drawCircle();

  drawIntersect();

  drawBase();

  drawIntersect();

  return 0;
}

void drawBase()
{
  cout << "-------\n";
}
void drawIntersect()
{
  cout << "  / \\\n" << " /   \\ " << endl;
}
void drawCircle()
{
  cout << "   *\n *   *\n  * *\n";
}
