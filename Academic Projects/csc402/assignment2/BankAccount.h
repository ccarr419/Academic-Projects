/**
   A bank account has a balance and a mechanism for applying interest or fees at 
   the end of the month.
*/

#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <iostream>
using namespace std;

class BankAccount
{
   private:
   int accountNumber;
   double balance;

   /**
      Constructs a bank account with zero balance.
   */
   public:
   BankAccount();
   /**
      Constructs a bank account with initialized account number and balance.
   */
   BankAccount(int n, float b);
   
   /**
      Set account number.
	  @param account number
   */
   void setAccountNumber(int n);
   /**
      Get account number.
	  @return account number
   */
   int getAccountNumber();
   
   /**
      Makes a deposit into this account.
      @param amount the amount of the deposit
   */
   void deposit(double amount);
   
   /**
      Makes a withdrawal from this account, or charges a penalty if
      sufficient funds are not available.
      @param amount the amount of the withdrawal
   */
   /*this function should be override by subclasses, 
     for checking account, after every withdraw, the number of withdraws should be decreased
	 for saving account, the minBalance should be check before each withdraw.
   */
   virtual void withdraw(double amount);
   
   /**
      Carries out the end of month processing that is appropriate
      for this account.
	  For checking account, reset the transaction count to 3
	  For saving account, calculate the interests and accumulate the balance
   */

   virtual void monthEnd() = 0;
   
   void setBalance(float amount);
   
   /**
      Gets the current balance of this bank account.
      @return the current balance
   */
   double getBalance();
   /**
      print the current balance of this bank account.
      @return the current balance
   */
   void printAccount(ostream &out);
};

#endif
