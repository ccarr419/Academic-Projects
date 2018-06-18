#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string hypen(string str);
void hypenHelper(string &str);
void getChar(ifstream &inf);
bool checkVowel(char);
//bool checkRule3(string);

int main(int argc, char *argv[])
{
	ifstream inf;
	string fileName;
	if(argc > 1)
	{
		string fileName = argv[1];
		inf.open(fileName.c_str());
		getChar(inf);
	}
	else
	{
		cout << "Enter file name: ";
		cin >> fileName;
		inf.open(fileName.c_str());
		getChar(inf);
	}
	return 0;
}

string hypen(string str)
{
	string tempStr;
	int pos = 0;
	int ptr = 0;
	while(ptr != str.length())
	{
		if(checkVowel(str[ptr]))
		{
			if((str[ptr] == 'u' && ptr > 0) && str[ptr-1] == 'q')
			{
				ptr++;
			}
			else
			{
				
			}
		}
		else
		{
			ptr++;
		}
	}
}

void hypenHelper(string &str)
{
	
}

void getChar(ifstream &inf)
{
	char ch;
	string tempString = "";
	while(inf.get(ch)) 
    {
		if(ch == ' ' || ch == '\n')
		{
			tempString = hypen(tempString);
			cout << tempString << endl;
			tempString = "";
		}
		else
		{
			tempString += ch;
		}
	}
}

bool checkVowel(char ch)
{
	const char vowels[12] = {'a', 'e', 'i', 'o', 'u', 'y', 
				'A', 'E', 'I', 'O', 'U', 'Y'};
	for(int i = 0; i < 12; i++)
	{	if(ch == vowels[i])
			return true;
	}
	return false;	
}

/*
bool checkRule3(string str)
{
	const string seq[10] = {"qu", "tr", "br", "str", "st", "sl", "bl", "cr",
		"ph", "ch"};
	for(int i = 0; i < 10; i++)
	{	if(str == seq[i])
			return true;
	}
	return false;	
}*/
