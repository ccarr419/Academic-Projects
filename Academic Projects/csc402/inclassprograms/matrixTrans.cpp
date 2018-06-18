#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string	getFileName();
bool 	openFile(ifstream&, string);
void	getMatrix(ifstream&, int[2][3]);
void 	transpose(int[2][3], int[3][2]);
void	printMatrix(int[3][2]);

int main()
{
	ifstream inf;
	string fileName = getFileName();
	int matrix[2][3];
	int result[3][2];
	if(openFile(inf, fileName))
	{
		getMatrix(inf, matrix);
		transpose(matrix, result);
		printMatrix(result);
	}
	else
		cout << "Error: File not found\n";
}

string getFileName()
{
	string fileName;
	cout << "Enter matrix file name: ";
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

void getMatrix(ifstream &inf, int matrix[2][3])
{
	char ch;
	int i = 0;
	int j = 0;
	while(inf.get(ch))
	{
		if(i > 1 || j > 2)
			return;
		if(ch >= 48 && ch <= 57)
		{		matrix[i][j] = ch;
				i++;
		}
		else if(ch == '\n')
		{	
			j++;
			i = 0;
		}
	}
}

void transpose(int orig[2][3], int result[3][2])
{
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 3; j++)
			result[j][i] = orig[i][j];
}

void printMatrix(int matrix[3][2])
{
	for(int i = 0; i < 2; i++)
	{	
		for(int j = 0; j < 3; j++)
		{
			cout << matrix[i][j];
			cout << " ";
		}
		cout << endl;
	}
}
