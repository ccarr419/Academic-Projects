/********************************************
This program finds simple derivates of f(x)!
Author: Christian Carreras
********************************************/
#include <iostream> //Main header
#include <iomanip> //Input/Output Manipulator
#include <locale> //Required for string-number commands
#include <sstream> //Required for string-number commands
#include <string> //Required for strings
#include <cmath> //Needed for complex math calculations
using namespace std;
int main()
{
  //Variables and arrays
  string value[500], pownumstring, multiplestring;
  char answer, choice;
  float pownumnum[500], multiplenum;
  int i;

  //User Interface
  cout << "\nWelcome! Please select the type\n";
  cout << "of function you wish to derive.\n\n";

  cout << "1. (Single Term)\n"; //Completed
  cout << "2. (Multiple Term) *N\\A*\n"; //Not Started
  cout << "3. (Product Rule) *N\\A*\n"; //Not Started
  cout << "4. (Quotient Rule) *N\\A*\n"; //Not Started
  cout << "5. (Chain Rule) *N\\A*\n"; //Not Started
  cout << "6. (Trig Terms) *N\\A*\n"; //Not Started
  //Probably not worth it to attempt 3-6 as of now

  cout << "\nYour choice: ";
  cin >> answer;

  switch(answer)
    {
    case '1': //User chooses: (Single Term)

      //Rules for user input
      cout << "\nRules: (Please Read!)\n";
      cout << "1. Enter characters indivdually.\n";
      cout << "2. Only exception to Rule #1\n  (Numbers can be written in entirety.)\n";
      cout << "3. Write in terms of x.\n";
      cout << "4. For exponents use the ^ key.\n";
      cout << "5. Do not use exponents on numbers.\n";
      cout << "6. Do not use fractions or decimals.\n";
      cout << "7. Do not use adding, subtracting,\n   multiplying terms or dividing.\n";
      cout << "8. Enter the function -f(x) as -1f(x)\n";
      cout << "9. When finished type 'end'.\n\n"; 

      //Make sure the user reads the rules
      cout << "Do you agree to the rules?[y/n]: ";
      cin >> choice ;
      cout << endl;

      //Note: will end program if anything besides 'y' is entered.
      //(I should fix this later)
      while(choice  == 'y')
	{
	  //User enters characters here
	  //(Shouldn't be longer than 4 charcters entered)
	  for(i = 0; i < 500; i++)
	    {
	      cout << "Enter: ";
	      cin >> value[i];
	      if(value[i] == "end") //Terminates loop when 'end' is entered
		break;
	    }

	  //Restates the function entered by user	  
	  cout << "f(x)= ";
	  
	  for (i = 0; i < 500; i++)
	    {
	      if(value[i] == "end")
		{
		  value[i] = " "; //Replaces "end" with a blank space
		  //This is so it is not restated again in
		  //the fuction, I may want to fix this
		  //later but it is not a big prority. 
		}
	      else //Shows the character the user entered
		{
		  cout << value[i];
		}
	    }
	  
	  cout << endl;
	  
	  //Another for loop for when the function contains 'x'
	  for(i = 0; i < 500; i++)
	    {
	      if(value[i] == "x") //Function contains 'x'
		{
		  for(i = 0; i < 500; i++)
		    {
		      if(value[i] == "^") //If the function contains an exponent
			//Note: User should not enter x^1 or x^0
			//(I have nothing stopping this, I may want to fix this later.
			{ 
			  //Converting exponent string to a number
			  pownumstring = value[i+1];
			  istringstream convert(pownumstring);
			  if ( !(convert >> pownumnum[i]) ) //If for some reason this doesn't work 
			    {
			      pownumnum[i] = 0;
			    }
			  pownumnum[i]-= 1; //Easy way to find derivatives
			  //nf(x)^n-1
			  if(value[0] == "x") //If the function begins with 'x'
			    {
			      if(pownumnum[i] == 1) //If the exponent with subtracted by 1 equals 1
				{
				  cout << "f'(x)= " << pownumnum[i] + 1 << "x\n"; //No need to show exponent then
				  goto StartAgain; //Goto function which goes to point "StartAgain" ***
				}
			      else if(pownumnum[i] == -2)
				{
				  cout << "f'(x)= -x^" << pownumnum[i] << endl;
				  goto StartAgain; // ***
				}
			      else //If the exponent is anything else
				{
				  cout << "f'(x)= " << pownumnum[i] + 1 << "x^" << pownumnum[i] << endl; 
				  goto StartAgain; // ***
				}
			    }
			}
		      //If the function contains 'x' but not an exponent
		      else if(value[i] != "^" && value[i+1] != "^")
			{
			  cout << "f'(x)= 1\n";
			  goto StartAgain; // ***
			}
		    }
		}
	      
	      //If the function does not begin with 'x'
	      else if(value[0] != "x")
		{
		  //Converting the multiple in front (string) to a number
		  multiplestring = value[0];
		  istringstream convert(multiplestring);
		  if ( !(convert >> multiplenum) )
		    {
		      multiplenum = 0;
		    }
		  //For loop that checks for an 'x' in the rest of the function
		  for(i = 0; i < 500; i++)
		    {
		      if(value[i] == "x") //If there's an 'x'
			{
			  //For loop that checks for exponents
			  for(i = 0; i < 500; i++)
			    {
			      if(value[i] == "^") //If there's exponents
				{  
				  //Converting the exponent string to a number
				  pownumstring = value[i+1];
				  istringstream convert(pownumstring);
				  if ( !(convert >> pownumnum[i]) )
				    {
				      pownumnum[i] = 0;
				    }
				  //Multiplies the multiple in front by the exponent
				  multiplenum*= pownumnum[i];	
				  pownumnum[i]-= 1;
				  if(multiplenum == 1) //If the multiple in front equals 1
				    {
				      if(pownumnum[i] == 1) //If the exponent equals 1
					{
					  cout << "f'(x)= x\n"; //No need to show exponent
					  goto StartAgain; // ***
					}
				      else if(pownumnum[i] == 0) //If the exponent equals zero for some reason
					{
					  cout << "f'(x)= 1\n"; //Anything to the zero power equals 1
					  goto StartAgain; // ***
					}
				      else //This would work towards fractions and decimals
					//but it created more problems than solved.
					{
					  //cout << "f'(x)= " pownumnum[i] + 1 << "x^" << pownumnum[i] << endl;
					  goto StartAgain; // ***
					} 
				    }
				  else if(multiplenum != 1) //If the multiple in front doesn't equal 1
				    {
				      if(pownumnum[i] == 1) //If the exponent equals 1
					{
					  cout << "f'(x)= " << multiplenum << "x\n"; //No need for an exponent
					  goto StartAgain; // ***
					}
				      else //If the exponent equals anything else
					{ 
					  cout << "f'(x)= " << multiplenum << "x^" << pownumnum[i] << endl;
					  goto StartAgain; // ***
					}
				    }
				}
			      //If the function contains a multiple in front but not an exponent
			      else if(value[0] != "^" && value[1] != "^" && value[2] != "^")
				{
				  cout << "f'(x)= " << multiplenum << endl; //Get rid of 'x'
				  //Do this because x^0 = 1
				  goto StartAgain; // ***
				}	
			    }
			  
			}
		      
		      //If the function does not contain an 'x' whatsoever
		      else if(value[0] != "x" && value[1] != "x" && value[2] != "x")
			{
			  cout << "f'(x)= 0\n"; //The derivative of any constant is zero
			  goto StartAgain; // ***
			}
		      
		    }
		}
	    }
	  
	StartAgain: //Goto function brings user here after the derivative is found
	  cout << "\nWould you like to find another derivative?[y/n]: ";
	  cin >> choice; //If yes it will start the process again starting from case "1"
	  cout << endl;
	}
    }
  
  return 0;
}
