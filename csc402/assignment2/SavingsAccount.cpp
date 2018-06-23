#include <iostream>
#include "BankAccount.h"
#include "SavingsAccount.h"

using namespace std;

SavingsAccount::SavingsAccount() : BankAccount()
{
	setAccountNumber(1234567890);
	setBalance(0.00);
	setInterestRate(1);
	minBalance = 100.00;
}

SavingsAccount::SavingsAccount(int n, float b, float r) : BankAccount(n, b)
{
	setAccountNumber(n);
	setBalance(b);
	setInterestRate(r);
	minBalance = 100.00;
}

void SavingsAccount::setInterestRate(double rate)
{
	interestRate = rate*0.01;
}

void SavingsAccount::withdraw(double amount)
{
	if((getBalance() - amount) < 0)
	{
		if(getBalance() <= 0) //(no count towards withdrawal)
		{
			setBalance(getBalance()-35); //$35 penalty
			setBalance(getBalance()-1); //below minBalnce penalty
		}
		else
		{
				setBalance(0); //withdraw to zero
				setBalance(getBalance()-35); //minus $35 overdraft fee
				setBalance(getBalance()-1); //below minBalance penalty
		}
	}
	else
	{
		if(getBalance() < minBalance || (getBalance() - amount) < minBalance)
		{	
			setBalance(getBalance()-amount);
			setBalance(getBalance()-1); // below minBalance penalty
		}
		else
			setBalance(getBalance()-amount);
	}
}

void SavingsAccount::monthEnd()
{
	if(getBalance() >= minBalance)
		setBalance(getBalance()+(getBalance()*getInterestRate()));
}

double SavingsAccount::getInterestRate()
{
	return interestRate;
}
	