#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string getFileName();
bool openFile(ifstream&, string);
void getChar(ifstream&, string&);

int main()
{
	string fileName, output;
	ifstream inf;
	fileName = getFileName();
	if (openFile(inf, fileName))
	{
		cout << "File opened!\n";
		getChar(inf, output);
		cout << output << endl;;
	}
	else
		cout << "Error!\n";
	
	return 0;
}

string getFileName()
{
	string fileName;
	cout << "\nPlease enter the file name: ";
	cin >> fileName;
	return fileName;
}

bool openFile(ifstream &inf, string fileName)
{
	bool fileOpen;
	inf.open(fileName.c_str());
	if (inf.fail())
		return fileOpen = false;
	else
		return fileOpen = true;
}

void getChar(ifstream &inf, string &out)
{
	char ch, chTemp;
	int i = 0;
	string temp = "";
	string holder = "";
	while(inf.get(ch)) 
    {
		cout << ch;
		if(ch != '\n')
		{
			if(i % 2 == 0)	
				out += ch;
			else
				temp += ch;
		}
		else
		{
			if(i % 2 == 0)
			{	
				out += ch;
				i++;
			}
			
			else
			{
				for(int j = 0; j < temp.length(); j++)
				{
					chTemp = temp[j];
					out += chTemp;
					/*if(chTemp != ' ')
						holder += chTemp;
					else
						strHolder.push_back(holder);*/
				}
				out += chTemp;
				out += ch;
				temp = "";
				i++;
			}
		}
    }
}

