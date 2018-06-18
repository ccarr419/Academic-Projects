/**
   This program simulates a bank with checking and savings accounts.
*/

#include <iostream>
#include "BankAccount.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"

using namespace std;

int main()
{
	// Array of BankAccount pointer
	BankAccount* accountList[2];
	accountList[0] = new CheckingAccount(1,1000);
	accountList[0]->withdraw(100);
	accountList[0]->withdraw(100);
	accountList[0]->withdraw(100);
	accountList[0]->withdraw(100);	
	accountList[0]->monthEnd();
	accountList[0]->withdraw(100);	
	accountList[0]->deposit(1000);
	accountList[0]->printAccount(cout);

	accountList[1] = new SavingsAccount(2,1000, 5);
	accountList[1]->withdraw(100);
	accountList[1]->monthEnd();
	accountList[1]->withdraw(100);	
	accountList[1]->printAccount(cout);
/*
	// test your program using the code below.
	// when you turn in your programming assignment, please comment the code below.
	// The grading program can not interact with your code, sorry:()
	
	
      // Create accounts
	  SavingsAccount savings = SavingsAccount();
	  savings.setAccountNumber(1);
	  savings.setInterestRate(5);
	  
	  CheckingAccount checking = CheckingAccount();
	  checking.setAccountNumber(2);
	  
	  
      bool done = false;
      while (!done)
      {
		 int accountNumber;
		 cout << "Please enter your account number: " ;
		 cin >> accountNumber; 
			
         cout << "D)eposit  W)ithdraw  M)onth end  Q)uit: " << endl; 
         string input;
		 cin >> input;
		 
         if (accountNumber == 1 && (input=="D" || input=="W")) // Deposit or withdrawal
         {
            cout << "Enter amount: " ;
 			double amount;
			cin >> amount;

            if (input=="D") { savings.deposit(amount); }
            else { savings.withdraw(amount); }

            savings.printAccount(cout);
         }
         else if ( accountNumber == 1 && input=="M") // Month end processing
         {
               savings.monthEnd();
               savings.printAccount(cout);
         }
		 else if (accountNumber == 2 && (input=="D" || input=="W")) // Deposit or withdrawal
         {
            cout << "Enter amount: " ;
 			double amount;
			cin >> amount;

            if (input=="D") { checking.deposit(amount); }
            else { checking.withdraw(amount); }

            checking.printAccount(cout);
         }
         else if ( accountNumber == 2 && input=="M") // Month end processing
         {
               checking.monthEnd();
               checking.printAccount(cout);
         }
         else if (input == "Q")
         {
            done = true;
         }
   }
*/   
   return 0;
}
