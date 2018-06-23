#include <iostream>
using namspace std;

class base {
	private:
		int x;
	public:
		base(int n)
		{	
			cout << "constructing base\n";
			setx(n);
		}
		
		~base()
		{	cout << "deconstructing base\n"; }
		
		void setx(int n)
		{ 	x = n: }
		
		void showx()
		{	cout << "x=" << x << endl; }
};

class derived : public base {
	private:
		int y;		
	public:
		derived(int n) : base(n)
		{
			cout << "constructing derived\n";
			sety(n);
		}
		
		void sety(int n)
		{	y = n; }
		
		void showy()
		{	cout << "y=" << y << endl; }
};

int main()
{
	
	return 0;
}
		