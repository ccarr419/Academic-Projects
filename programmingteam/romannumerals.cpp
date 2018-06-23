#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string getFileName();
bool openFile(ifstream&, string);
void translate(ifstream&);
int getNum(char);

int main()
{
	string fileName;
	ifstream inf;
	fileName = getFileName();
	openFile(inf, fileName);
	translate(inf);
	return 0;
}

string getFileName()
{
	string fileName;
	cout << "Enter file name: ";
	cin >> fileName;
	return fileName;
}

bool openFile(ifstream& inf, string fileName)
{
	bool fileOpen;
	inf.open(fileName.c_str());
	if (inf.fail())
		return fileOpen = false;
	else
		return fileOpen = true;
}

void translate(ifstream &inf)
{
	char ch;
	int num1 = 0;
	int num2 = 0;
	int total = 0;
	string numString = "";
	while(inf.get(ch))
	{
		if(ch == ' ' || ch == '\n')
		{
			cout << numString << " translated to " << total << endl;
			num1 = 0;
			num2 = 0;
			total = 0;
			numString = "";
		}
		else
		{
			if(num1 == 0)
			{
				num1 = getNum(ch);
				if(num2 < num1)
				{
					total += (num1 - num2);
					total -= num2;
				}
				else
				{
					total += num1;
				}
			}
			else
			{
				num2 = getNum(ch);
				if(num1 < num2)
				{
					total += (num2 - num1);
					total -= num1;
					num1 = 0;
				}
				else
				{
					total += num2;
					num1 = 0;
				}
			}
			numString += ch;
		}
	}
}

int getNum(char ch)
{
	const char romNum[5] = {'I', 'V', 'X', 'L', 'C'};
	ch = toupper(ch);
	if(ch == romNum[0])
		return 1;
	if(ch == romNum[1])
		return 5;
	if(ch == romNum[2])
		return 10;
	if(ch == romNum[3])
		return 50;
	if(ch == romNum[4])
		return 100;
	return 0;
}
