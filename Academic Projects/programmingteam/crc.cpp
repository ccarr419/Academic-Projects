#include <iostream>
#include <fstream>
using namespace std;

void getChar(ifstream&);

int main()
{
	ifstream inf;
	string fileName;
	cin >> fileName;
	inf.open(fileName.c_str());
	getChar(inf);
	inf.close();
	return 0;

}

void getChar(ifstream &inf)
{
	char ch;
	while(inf.get(ch))
	{
		
	}
}