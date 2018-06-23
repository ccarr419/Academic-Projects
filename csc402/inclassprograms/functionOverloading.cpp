#include <iostream>
using namespace std;

/*
void exchange(int &n1, int &n2)
{
	int tmp;
	tmp = n1;
	n1 = n2;
	n2 = tmp;
}

void exchange(float &n1, float &n2)
{
	float tmp;
	tmp = n1;
	n1 = n2;
	n2 = tmp;
}

void exchange(char &n1, char &n2)
{
	char tmp;
	tmp = n1;
	n1 = n2;
	n2 = tmp;
}
*/
namespace myNameSpace {
	template<class T>
	void swap(T &n1, T &n2)
	{
		cout << "Using my name space swap\n";
		T tmp;
		tmp = n1;
		n1 = n2;
		n2 = tmp;
	}
};

int main()
{
	int a = 1, b = 2;
	cout << a << "\t" << b << endl;
	myNameSpace::swap (a, b);
	cout << a << "\t" << b << endl;
	
	float c = 3.5, d = 4.2;
	cout << c << "\t" << d << endl;
	myNameSpace::swap (c, d);
	cout << c << "\t" << d << endl;
	
	char e = '#', f = '*';
	cout << e << "\t" << f << endl;
	myNameSpace::swap (e, f);
	cout << e << "\t" << f << endl;
	
	return 0;
}
