/**
* Author:		Dr. Spiegel
* Updated By:	Christian Carreras
* File:		Treetest.cpp
* Date:		25/04/2014
* Purpose:	Application to thoroughly test the BinarySearchTree by letting
*			users add and remove integers from the tree, change existing
*			elements within the tree, and print the tree as it currently is
**/

#include <iostream>
#include <string>
#include "BinarySearchTree.h"

using namespace std;

typedef BinaryTree<int> BinarySearchTree;

/*
* Function Name:	getChoice
* Parameters:		string - import only
* Return Value:	char - users choice
* Purpose:		returns the first char in the string that the user
*				entered regardless of other chars in the string
*				Then converts the char to its uppercase form
**/
char getChoice(string ok);

int main()
{	BinarySearchTree Tree;
	int entry, *result, data;
	char Choice;
	do	//Print menu to screen
	{	cout << "Select: A)dd    R)emove     C)hange     P)rint";
		cout << "     T)ree Print      Q)uit\n";
  
		Choice=getChoice("ARCPTQ");//User enters choice
		switch (Choice) 
		{	case 'A': //Add integer to tree
				cout << " Enter an Integer >";
				cin >> entry;
				Tree.insertToTree(entry);
				break;
			case 'R': //Remove integer from tree
				cout << "Value to Delete? >";
				cin >> entry;
				if (!Tree.treeSearch(entry)) //Integer not within tree
					cout << entry << " Not Found\n";
				else //Integer is in tree
				{	if(Tree.hasMultiples(entry))//Check for multiplicity
					{	cout << "Do you want to delete (1) or (a)ll? >";
						char choice;
						cin >> choice;
						switch(choice)
						{	case '1'://Delete only one
								Tree.decCount(entry);
								break;
							case 'a'://Delete all
								Tree.deleteFromTree(entry);
								break;
							default: //User entered something else
								cout << "I cannot understand ";
								cout << choice << endl;
								break;
						}
					}
					else //Only one copy, delete it
						Tree.deleteFromTree(entry);
				}
				break;
			case 'C': //Changes one integer to another within the tree
				cout << "Value to change? >";
				cin >> entry;
				if(!(Tree.treeSearch(entry)))//Integer not in tree
					cout << entry << " Not Found\n";
				else //Integer is in the tree
				{	cout << "Value to change it to? >";
					cin >> data;
					Tree.change(entry, data);
				}				
				break;
			case 'P': //Print the tree in order least to greatest
				cout << "The Tree:" << endl;
				Tree.inorder();
				break;
			
			case 'T'://Print the tree to actually look somewhat like a tree
				cout << "The tree, as it appears (sort of)..\n";
				Tree.treePrint();
				break;	
		}
	} while (Choice != 'Q'); //While the user doesn't quit the program
}

//Get the user's choice for the menu
char getChoice(string ok)
{	char ch=' ';
	do ch=toupper(cin.get()); 
	while (ok.find(ch)==string::npos);
	cin.get(); // eat CR
	return(toupper(ch));
}
