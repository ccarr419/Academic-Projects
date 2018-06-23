#include <iostream>
#include <iomanip>
#include "BankAccount.h"

using namespace std;

BankAccount::BankAccount()
{
	setAccountNumber(1234567890);
	setBalance(0.00);
}

BankAccount::BankAccount(int n, float b)
{
	setAccountNumber(n);
	setBalance(b);
}

void BankAccount::setAccountNumber(int n)
{
	accountNumber = n;
}

int BankAccount::getAccountNumber()
{
	return accountNumber;
}

void BankAccount::deposit(double amount)
{
	setBalance(getBalance()+amount);
}

void BankAccount::withdraw(double amount)
{
	if((getBalance() - amount) < 0)
	{
		if(getBalance() < 0)
			setBalance(getBalance()-35); //$35 penalty
		else
		{
			setBalance(0); //withdraw to zero
			setBalance(getBalance()-35); //minus $35 overdraft fee
		}
	}
	else
		setBalance(getBalance()-amount);
}

void BankAccount::monthEnd()
{
}

void BankAccount::setBalance(float amount)
{
	balance = amount;
}

double BankAccount::getBalance()
{
	return balance;
}

void BankAccount::printAccount(ostream &out)
{
	out << "$" << getBalance() << endl;
}