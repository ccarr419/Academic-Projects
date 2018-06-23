#include <iostream>
using namespace std;

template<class k, class v>
class Pair {
	public:
		k firstItem;
		v secondItem;
		
		void print()
		{ cout << firstItem << "\t" << secondItem << endl; }
		
		bool operator == (const Pair &aPair)
		{	return (firstItem == aPair.firstItem && secondItem == aPair.secondItem); }
};

int main ()
{
	Pair<int, string> p1;
	p1.firstItem = 1;
	p1.secondItem = "csc";
	p1.print();
	
	Pair<string, string> p2;
	p2.firstItem = "csc";
	p2.secondItem = "402";
	p2.print();
	
	return 0;
}
