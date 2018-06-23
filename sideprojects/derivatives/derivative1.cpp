/* Author: Christian Carreras
** File: derivatve1.cpp
** Purpose: To find the derivative of polynomials
*/

#include <iostream>
using namespace std;

/* Function: menu()
** Returns: void
** Parameters: none
** Purpose: displays the menu for the user
*/
void menu();

/* Function: select()
** Returns: int
** Parameters: none
** Purpose: user selects the option to commence
*/
int select();

/* Function: singleTerm()
** Returns: void
** Parameters: none
** Purpose: user enters a single term and exponent
*/
void singleTerm();

/* Function: foX() "f of x"
** Returns: void
** Parameters: float, int
** Purpose: finds the derivative of the given polynomial
*/
void foX(float, int);

//Polynomial containing a term and exponent
struct poly
{	float term;
	int exp;
};

int main()
{	menu();
	int option = select();
	while(!option)
	{	cout << "\nThat is not a valid choice\n";
		menu();
		option = select();
	}
	
	while(option != -1)
	{	menu();
		option = select();
	}

	return 0;
}

void menu()
{	cout << "\nPlease select an option\n";
	cout << "1. (Single Term)\n";
	cout << "2. (Multiple Term) *N/A\n";
	cout << "3. (Product Rule) *N/A\n";
	cout << "4. (Quotient Rule) *N/A\n";
	cout << "5. (Chain Rule) *N/A\n";
	cout << "6. (Trig Terms) *N/A\n";
	cout << "<-1 to exit>\n";
}

int select()
{	int choice;
	cout << "\nPlease enter your choice: ";
	cin >> choice;
	switch(choice)
	{	case 1:
			singleTerm();
			return 1;
		case 2:
			return 2;
		case 3:
			return 3;
		case 4: 
			return 4;
		case 5:
			return 5;
		case 6:
			return 6;
		case -1:
			return -1;
		default:
			return 0;
	}
}

void singleTerm()
{	poly singlePoly;
	cout << "Please enter the term: ";
	cin >> singlePoly.term;
	cout << "Please enter the exponent: ";
	cin >> singlePoly.exp;
	foX(singlePoly.term, singlePoly.exp);
}

void foX(float term, int exp)
{	if(term == 0)
	{	cout << "f(x)  = 0\n";
		cout << "f'(x) = 0\n";
	}
	else if(exp == 0)
	{	cout << "f(x)  = " << term << endl;
		cout << "f'(x) = 0\n";
	}
	else if(term == 1)
	{	if(exp == 1)
		{	cout << "f(x)  = x\n";
			cout << "f'(x) = 1\n";
		}
		else
		{	cout << "f(x)  = x^" << exp << endl;
			if(exp == 2)
				cout << "f'(x) = " << exp << "x\n";
			else
				cout << "f'(x) = " << exp << "x^" << exp-1 << endl;
		}
	}
	else if(term == -1)
	{	if(exp == 1)
		{	cout << "f(x)  = -x\n";
			cout << "f'(x) = -1\n";
		}
		else
		{	cout << "f(x)  = -x^" << exp << endl;
			if(exp == 2)
				cout << "f'(x) = " << term*exp << "x\n";
			else	
				cout << "f'(x) = " << term*exp << "x^" << exp-1 << endl;
		}	
	}
	else
	{	if(exp == 1)
		{	cout << "f(x)  = " << term << "x\n";
			cout << "f'(x) = " << term << endl;
		}
		else
		{	cout << "f(x)  = " << term << "x^" << exp << endl;
			if(exp == 2)
				cout << "f'(x) = " << term*exp << "x\n";
			else	
				cout << "f'(x) = " << term*exp << "x^" << exp-1 << endl;
		}
	}
}
