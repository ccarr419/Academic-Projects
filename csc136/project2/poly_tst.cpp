/////////////////////////////////////////////////////////////
//File:			poly_tst.cpp
//Author:		Christian Carreras
//Description:	Tests and impliments the Polynomial class
//				with a menu and user interface
////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "poly.h" //Polynomial header file
using namespace std;

////////////////////////////////////////////////////
//Function:		openFile
//Description:	Asks the user for a file
//				and checks if it exists
//Parameters:	ifstream - to open and read file
//Returns:		bool
///////////////////////////////////////////////////
bool openFile(ifstream&);

///////////////////////////////
//Function:		menu
//Description:	Opens menu
//Parameters:	none
//Returns:		void
//////////////////////////////
void menu();

//////////////////////////////////////////////////////////
//Function:		choose
//Description:	Opens user interface
//Parameters:	Polynomial - uses the polynomial class
//Returns:		bool
/////////////////////////////////////////////////////////
bool choose(Polynomial&);

//////////////////////////////////////////////////////
//Function:		evaluate
//Description:	Evaluates polynomial for input x
//Parameters:	Polynomial
//Returns:		void
//////////////////////////////////////////////////////
void evaluate(Polynomial&);

/////////////////////////////////////////////////////////
//Function:		multiply
//Description:	Multiplies polynomial by a scalar value
//Parameters:	Polynomial
//Returns:		void
/////////////////////////////////////////////////////////
void multiply(Polynomial&);

//////////////////////////////////////////////////////
//Function:		print
//Description:	Prints polynomial to screen
//Parameters:	Polynomial
//Returns:		void
//////////////////////////////////////////////////////
void print(Polynomial&);

//////////////////////////////////////////////////////
//Function:		add
//Description:	Adds a term to the polynomial
//Parameters:	Polynomial
//Returns:		void
//////////////////////////////////////////////////////
void add(Polynomial&);

///////////////////////////////////////
//Function:		exit
//Description:	Closes the program
//Parameters:	Polynomial
//Returns:		bool
///////////////////////////////////////
bool exit(Polynomial&);

/////////////////////////////////////////////////////////////
//Funciton:		saveToFile
//Description:	Saves the polynomial to a user-defined file
//Parameters:	Polynomial
//Returns:		void
/////////////////////////////////////////////////////////////
void saveToFile(Polynomial&);

int main()
{	Polynomial poly; //Polynomial class
	ifstream inf;
	bool fileOpen;
	
	//Get file from user and check to see if it exists
	fileOpen = openFile(inf);
	
	//If the file exists
	if(fileOpen == true)
	{	cout << "\nFile Loaded\n\n";
		poly.readFile(inf);	//Read the file into the polynomial
		do //Menu system that will run at least once
		{	
			menu();
			fileOpen = choose(poly);
		}	while(fileOpen == true);
	}
	
	//Error message and terminate program
	else
	{	cout << "Failed to open file\n\n"; } 
	
	return 0;
}

//Asks user for file and checks if it exists
bool openFile(ifstream &inf)
{	string file;
	cout << "\nPlease enter a file: ";
	getline(cin, file);
	inf.open(file.c_str()); //Attempt to open the file
	if(inf.fail()) //If the file doesn't exist
		return false;
	else //If the file exists
		return true;
}

//Menu layout for user
void menu()
{	
	cout << "Chris' Polynomial Program\n";
	for(int j = 0; j < 25; j++)
	{	cout << "="; }		
	cout << "\n(E)valuate\n";
	cout << "(M)ultiply\n";
	cout << "(P)rint\n";
	cout << "(A)dd\n";
	cout << "E(x)it\n\n";
	//Ask user to enter their choice
	cout << "Please enter your choice: ";
}
 
//User interface
bool choose(Polynomial &poly)
{	bool doNotClose;
	char choice;
	cin >> choice;
	switch(toupper(choice))
	{	//Evaluate
		case 'E': //Ask the user for a value of x
			evaluate(poly);
			return doNotClose = true;
			break;
		//Multiply
		case 'M': //This will multiply all the coeff by a scalar value
			multiply(poly);
			return doNotClose = true;
			break;
		//Print
		case 'P': //Shows the polynomial read in from the file
			print(poly);
			return doNotClose = true;
			break;
		//Add
		case 'A': //Asks the for a coeff and expn to added to the polynomial
			add(poly);
			return doNotClose = true;
			break;
		//Exit
		case 'X':
			return doNotClose = exit(poly);
			break;
		//Error message
		default:
			cout << "Invalid entry\n\n";
			return doNotClose = true;
			break;
	}
}

//Evaluates polynomial for x which is user defined
void evaluate(Polynomial &poly)
{	double x; //Holds value for 'x' in the Polynomial
	cout << "\nPlease enter a value for X: ";
	cin >> x;
	//Call the overloaded () operator
	cout << "\nThe polynomial equals " << poly.operator()(x);
	cout << " for x = " << x << endl << endl;
}

//Multiplies the polynomial by the user defined scalar value
void multiply(Polynomial &poly)
{	float factor;
	cout << "\nPlease enter a value to multiply by: ";
	cin >> factor;
	//Call the overloaded *= operator
	poly.operator*=(factor);
	cout << "\nThe polynomial equals " << poly << endl << endl;
}

//Prints the polynomial to the screen
void print(Polynomial &poly)
{	cout << "\nThe polynomial equals " << poly << endl << endl;
}

//Adds a user-defined term to the polynomial
void add(Polynomial &poly)
{	float coeff;
	int expn;
	//Ask for the coefficient to be added
	cout << "\nPlease enter a value for the coefficient: ";
	cin >> coeff;
	//Ask for the exponent to be added
	cout << "Please enter a value for the exponent: ";
	cin >> expn;
	//Add to polynomial if it meets the add function's criteria
	poly.add(coeff, expn);
	//Display the polynomial
	cout << "\nThe polynomial equals " << poly << endl << endl;
}

//Asks the user if they really want to exit and if they
//want to save the polynomial to an external file
bool exit(Polynomial &poly)
{	bool doNotClose;
	char answer, save;
	//Is the user sure if they they want to exit?
	cout << "Are you sure you want to exit? (y or n): ";
	cin >> answer;
	if(tolower(answer) == 'y')
	{	//Ask the user if they want to save the polynomial
		cout << "Do you want to save the polynomial? (y or n): ";
		cin >> save;
		if(tolower(save) == 'y')
		{	saveToFile(poly);
			return doNotClose = false; //Quit program
		}
		else
			return doNotClose = false; 
	}
	else if(tolower(answer) == 'n') //Return to the menu
	{	cout << "Back to the menu\n";
		return doNotClose = true;
	}
	else
	{
		//Will return user to menu interface
		cout << "Invalid entry\n\n";
		return doNotClose = true;
	}
}


//Saves the polynomial to the user-defined file
void saveToFile(Polynomial &poly)
{	ofstream out;
	string file; //User-defined file
	cout << "Please enter the name of the file you wish to save to: ";
	cin >> file;
	out.open(file.c_str());
	out << poly;
	out.close();
	//Confirm file has been made and the polynomial has been saved
	cout << "The file has been saved!\n\n";
}
