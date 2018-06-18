#include <iostream>
using namespace std;

void menu();


struct coin
{	int year;
	char city;
};

int main()
{
	const int NUM_COINS = 400;
	coin coin_collection[NUM_COINS];
	int total;
	int coin_year;
	char coin_city;
	menu();
	
	int i = 0;
	while(i != -1)
	{	cout << "Enter year: ";
		cin >> coin_year;
		if(coin_collection.year == 'q')
			return (i = -1);
			
		else
			coin_collection.year = coin_year;
			
		cout << "Enter city: ";
		cin >> coin_city;
		if(coin_collection.city == 'q')
			return (i = -1);
			
		else
			coin_collection.city = coin_city;

		i++;
	}
	
	total = i+1;
	for(int j = 0; j < total; j++)
	{	cout << j+1;
		cout << "Year: " << coin_collection[j].year << "\t";
		cout << "City: " << coin_collection[j].city << endl;
	}
	
	return 0;
	
}

void menu()
{	cout << "Enter coin year in format 'xxxx'\n";
	cout << "Enter city as in one character\n";
	cout << "Press 'q' anytime to quit\n";
	cout << endl;
}
	
	