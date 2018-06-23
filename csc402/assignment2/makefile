debugFlag=-g

AccountDemo: AccountDemo.o BankAccount.o CheckingAccount.o SavingsAccount.o
	g++ -o AccountDemo AccountDemo.o BankAccount.o CheckingAccount.o SavingsAccount.o $(debugFlag)

BankAccount.o: BankAccount.cpp BankAccount.h
	g++ -c BankAccount.cpp $(debugFlag)

CheckingAccount.o: CheckingAccount.cpp CheckingAccount.h BankAccount.h
	g++ -c CheckingAccount.cpp $(debugFlag)

SavingsAccount.o: SavingsAccount.cpp SavingsAccount.h BankAccount.h
	g++ -c SavingsAccount.cpp $(debugFlag)
	
AccountDemo.o: AccountDemo.cpp BankAccount.h CheckingAccount.h SavingsAccount.h
	g++ -c AccountDemo.cpp $(debugFlag)
	
clean: 
	\rm -f *.o accountDemo
