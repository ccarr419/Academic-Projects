#include <iostream>
#include "BankAccount.h"
#include "CheckingAccount.h"

using namespace std;

CheckingAccount::CheckingAccount() : BankAccount()
{	
	setAccountNumber(1234567890);
	setBalance(0.00);
	setWithdrawals(0);
}

CheckingAccount::CheckingAccount(int n, float b) : BankAccount(n, b)
{
	setAccountNumber(n);
	setBalance(b);
	setWithdrawals(0);
}

void CheckingAccount::setWithdrawals(int w)
{
	withdrawals = w;
}

int CheckingAccount::getWithdrawals()
{
	return withdrawals;
}

void CheckingAccount::withdraw(double amount)
{
	if((getBalance() - amount) < 0)
	{
		if(getBalance() <= 0)
			setBalance(getBalance()-35); //$35 penalty 
		else
		{
			if(getWithdrawals() >= 3)
			{
				setBalance(0); //withdraw to zero
				setBalance(getBalance()-35); //minus $35 overdraft fee
				setBalance(getBalance()-1); //withdraw fee
			}
			else
			{
				setBalance(0); //withdraw to zero
				setBalance(getBalance()-35); //minus $35 overdraft fee
			}
		}
	}
	else
	{
		if(getWithdrawals() >= 3)
		{	
			setBalance(getBalance()-amount);
			setBalance(getBalance()-1); // withdraw fee
		}
		else
			setBalance(getBalance()-amount);
	}
	setWithdrawals(getWithdrawals()+1);
}

void CheckingAccount::monthEnd()
{
	setWithdrawals(0);
}
