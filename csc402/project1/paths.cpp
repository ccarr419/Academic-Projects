/*
* Filename:		paths.cpp
* Date Created:	09/06/2014
* Author:			Christian Carreras
* Class:			CSIT 402 (Data Structures II)
* Instructor:		Dr. Spiegel
* Purpose:		This file uses the Matrix class to create the ideas of
*				graphs, paths and cost. The user will read a file into the
*				Matrix object and will select a starting point and
*				destination. The program will then find all possible path
*				ways from the start vertex to destination vertex in the
*				order of cost.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "Matrix.h"

using namespace std;

/*
* Function Name:	startUp
* Parameters:		ifstream& (import/export) - file to be read
*				string& (import only) - name of the file
* Return Value:	void
* Purpose:		Calls all necessary functions to open the file, display
*				the menu and let the user take control from there
*/
void startUp(ifstream&, string&);

/*
* Function Name:	openFile
* Parameters:		ifstream& (import/export) - file to be read
*				string& (import only) - name of the file to open
* Return Value:	true - if file exists and could be opened
*				false - file could not be found or opened
* Purpose:		Attempts to open a file from the given file name
*				string argument and returns true or false based on
*				the results
*/
bool openFile(ifstream&, string&);

/*
* Function Name:	readIntoMatrix
* Parameters:		ifstream& (import/export) - file to read into matrix
*				Matrix<int>& (import/export) - Matrix object to hold data
* Return Value:	void
* Purpose:		Uses the Matrix class' insertion operator (>>) to insert
*				data from a given file
*/
void readIntoMatrix(ifstream&, Matrix<int>&);

/*
* Function Name:	getFileName
* Parameters:		none
* Return Value:	string - file name entered by the user
* Purpose:		Gets file name from user to later test if it can be opened
*/
string getFileName();

/*
* Function Name:	chooseOption
* Parameters:		Matrix<int>& (import only) - needed for sub-functions
* Return Value:	true - keep menu going (user did not quit)
*				false - user decided to quit (end loop)	
* Purpose:		Provides the switch statement so user can choose his/her
*				option and be directed towards the correct function
*				or terminate the program
*/
bool chooseOption(Matrix<int>&);

/*
* Function Name:	menu
* Parameters:		none
* Return Value:	void
* Purpose:		Displays the menu options for the user
*/
void menu();

/*
* Function Name:	findPath
* Parameters:		
* Return Value:	
* Purpose:		
*/
void findPaths(Matrix<int>&);

void findPathsHelper(int, int, int, int, int, int, int, int ,int, int, int,
	vector<int>, vector<int>, map<int, vector<vector<int> > >&,
	Matrix<int>&);
	
bool checkDup(vector<int>, int);

/*
* Function Name:	displayMatrix
* Parameters:		Matrix<int>& (import only) - Matrix to display
* Return Value:	void
* Purpose:		Displays the Matrix object to the screen by the use of
*				the class' (<<) operator
*/
void displayMatrix(Matrix<int> &mx);

/*
* Check for command-line arguments or resume normally
* Only difference is program asks for file name is it not entered via
* command-line argument
*/
int main(int argc, char *argv[])
{
	ifstream inf;
	string fileName; //Name of the file to be used
	
	if(argc > 1) //If there was an input on the command-line
	{
		fileName = argv[1]; //Use command-line argument as file name
		startUp(inf, fileName); 
		return 0;
	}
	
	fileName = getFileName(); //Non command-line file name enter
	startUp(inf, fileName);
	
	return 0;
}

/*
* Sets the course of the program no matter if a command-line argument is
* entered or not. Calls the functions to open the file and lets the user
* select the options he or she wants to use from the menu
*/
void startUp(ifstream &inf, string &fileName)
{	
	Matrix<int> mx;
	if(openFile(inf, fileName))
	{	//File exists: transfer data into matrix
		readIntoMatrix(inf, mx);
		while(chooseOption(mx)); //Keep menu open until user quits
	}
	
	else //File does not exist or exists and cannot be opened
		cout << "Could not open file!\n";
}

/*
* Asks the user for the name of the file to use and returns the string
*/
string getFileName()
{
	string fileName;
	cout << "\nPlease enter the file name: ";
	cin >> fileName;
	return fileName;
}

/*
* Attempts to open a file from the give file name, if the file does not
* exists or exists and fails to open, the function will return false.
* Otherwise the function will return true
*/
bool openFile(ifstream &inf, string &fileName)
{
	inf.open(fileName.c_str());
	if (inf.fail()) //If file does not exist.
		return false;
	else //If file does exist.
		return true;
}

/*
* By the use of the overloaded insertion operator (>>) in the Matrix class 
* the file given is inserted directly into the Matrix object
*/
void readIntoMatrix(ifstream &inf, Matrix<int> &mx)
{	inf >> mx; }

/*
* Displays the Matrix object to the screen by the use of the overloaded
* (<<) operator in the Matrix class
*/
void displayMatrix(Matrix<int> &mx)
{	cout << mx << endl; }

/*
* User enters a choice and a switch statement matches the choice up to
* its correct sub-function to carry out the task
*/
bool chooseOption(Matrix<int> &mx)
{
	char choice;
	menu();
	cin >> choice;
	switch(choice)
	{	
		case '1': //Find a path between two vertices
			findPaths(mx);
			break;
		
		case '2': //Display the matrix imported from file
			displayMatrix(mx);
			break;
			
		case '3': //Quit
			return false;
			
		default: //User entered something other than 1-3
			cout << "Sorry, I cannot understand \"" << choice << "\"\n\n";
			break;
	}
	return true;
}

/*
* Displays the options for the user to choose
*/
void menu()
{
	cout << "1.)\tFind path\n";
	cout << "2.)\tDisplay matrix\n";
	cout << "3.)\tQuit\n\n";
	cout << "Choose an option: ";
}

void findPaths(Matrix<int> &mx)
{
	map<int, vector<vector<int> > > path;
	vector<int> current_path, path_history;
	int f_idx, l_idx, row, col, current_pos, cost;
	int row_brkpt, col_brkpt, itr_pos;
	unsigned start, end;
	cout << "Enter starting vertex: ";
	cin >> start;
	
	cout << "Enter destination vertex: ";
	cin >> end;
	
	f_idx = 0;
	l_idx = mx.getColumns()-1;
	row = start;
	col = f_idx;
	current_pos = mx.get(row, col);
	row_brkpt = start;
	col_brkpt = f_idx;
	itr_pos = f_idx;
	cost = 0;
	
	findPathsHelper(row, col, start, end, cost, row_brkpt, col_brkpt, f_idx, 
		l_idx, current_pos, itr_pos, current_path, path_history, path, mx);
}

void findPathsHelper(int row, int col, int start, int end, int cost,
	int row_brkpt, int col_brkpt, int f_idx, int l_idx, int current_pos,
	int itr_pos, vector<int> current_path, vector<int> path_history,
	map<int, vector<vector<int> > > &path, Matrix<int> &mx)
{	
	if((((col == l_idx) && checkDup(current_path, current_pos)) || 
	((col == l_idx) && (current_pos == 0))) 
	|| (((col == f_idx) && checkDup(current_path, current_pos)) || 
	((col == f_idx) && (current_pos == 0))))
	{
		if(itr_pos == l_idx)
			return;
	}
	
	if(current_path.empty())
	{
		if(!path_history.empty())	
			current_path = path_history;
			
		else
		{
			current_path.push_back(start);
			path_history.push_back(start);
		}
	}			
	
	current_pos = mx.get(row, col);
	
	
	if(current_pos != 0)
	{
		current_path.push_back(current_pos);
		cost += current_pos;
		if(col_brkpt == itr_pos)
		{
			
		if(col == end)
		{
			path[cost].push_back(current_path);
			current_path.clear();
			cost = 0;
			
			if(
			
			itr_pos++;
			row = start;
			col = itr_pos;
			findPathsHelper(
			
		else
		{
			if(
			
	}
}

bool checkDup(vector<int> path_to_check, int current_pos)
{		
	for(vector<int>::iterator it = path_to_check.begin(); it != path_to_check.end(); ++it)
		if(current_pos == *it)
			return true;
			
	return false;
	
}
