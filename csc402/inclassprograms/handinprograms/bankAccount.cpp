#include <iostream>
#include <iomanip>
using namespace std;

// Parent class bankAccount
class bankAccount {
	public:
		bankAccount(float m);
		void setMoney(float m);
		float getMoney() const;
		void deposit(float m);
		void withdraw(float m);
		void printMoney();
	private:
		float money;
};

// bankAccount member functions
bankAccount::bankAccount(float m)
{	setMoney(m); }

void bankAccount::setMoney(float m)
{	money = m; }

float bankAccount::getMoney() const
{	return money; }

void bankAccount::deposit(float m)
{	money += m; }

void bankAccount::withdraw(float m)
{	money -= m; }

void bankAccount::printMoney()
{	cout << "$" << setprecision(2) << getMoney(); }

// Child class savingsAccount
class savingsAccount : public bankAccount {
	public:
		savingsAccount(float);
		float getInterest();
		void addInterest();
	private:
		float interest;
		void setInterest(float i);
		
};

// savingsAccount member functions
savingsAccount::savingsAccount(float m) : bankAccount(m)
{	
	setMoney(m); 
	setInterest(0.01);
}

void savingsAccount::setInterest(float i)
{	interest = i; }

float savingsAccount::getInterest()
{	return interest; }

void savingsAccount::addInterest()
{	
	float total_interest = getMoney() * getInterest();
	setMoney(getMoney() + total_interest);
}

// Child class checkingAccount
class checkingAccount : public bankAccount {
	public:
		checkingAccount(float m);
		int getWithdrawals() const;
		void incWithdrawals();
		void resetWithdrawals();
	private:
		int withdrawals;
};

// checkingAccount member functions
checkingAccount::checkingAccount(float m) : bankAccount(m)
{	
	setMoney(m); 
	resetWithdrawals();
}

int checkingAccount::getWithdrawals() const
{	return withdrawals; }

void checkingAccount::incWithdrawals()
{	withdrawals++; }

void checkingAccount::resetWithdrawals()
{	withdrawals = 0; }

void menu();

int main()
{	
	char choice;
	while(toupper(choice) != 'Q')
	{
		menu();
		cout << "Enter your choice: ";
		cin >> choice;
		switch(toupper(choice));
		{
			
		}
	}				
	return 0;
}

void menu()
{
	cout << "Choose one of the following:\n";
	cout << "D)eposit\n";
	cout << "W)ithdraw\n";
	cout << "M)onth End\n";
	cout << "Q)uit\n";
}
