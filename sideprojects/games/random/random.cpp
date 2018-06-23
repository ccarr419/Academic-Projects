#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

bool yahtzee(int[]);
bool fourOfaKind(int[]);
bool threeOfaKind(int[]);
bool aPair(int[]);
int keep(int, int[]);
void sort(int[]);

int main()
{	srand(time(NULL));
	int dice[5];
	int rolls = 0;
	int counter = 0;
	char choice;
	
	do
	{	for(int i = counter; i < 5; i++)
			dice[i] = rand() % (6 - 1) + 1;
		
		rolls++;
		if(rolls > 1)
			sort(dice);
		
		if(rolls == 3)
			break;
			
		if(yahtzee(dice))
			break;
		
		cout << "Your roll: ";
		for(int i = 0; i < 5; i++)
			cout << dice[i] << " ";
		cout << endl;
			
		cout << "What number would you like to keep? ";
		cin >> choice;
		switch (choice)
		{	case '0':
				break;
			case '1':
				counter = keep(1, dice);
				break;
			case '2':
				counter = keep(2, dice);
				break;
			case '3':
				counter = keep(3, dice);
				break;
			case '4':
				counter = keep(4, dice);
				break;
			case '5':
				counter = keep(5, dice);
				break;
			case '6':
				counter = keep(6, dice);
				break;
			default:
				cout << "I cannot understand \"" << choice << "\"\n";
				rolls--;
				break;
		}
	} while(1);
	
	cout << "Final: ";
	for(int i = 0; i < 5; i++)
		cout << dice[i] << " ";
	cout << endl;
	if(yahtzee(dice))
		cout << "Yahtzee!\n";
	else if(fourOfaKind(dice))
		cout << "Four of a kind!\n";
	else if(threeOfaKind(dice))
		cout << "Three of a kind!\n";
	else if(aPair(dice))
		cout << "A pair!\n";
	else
		cout << "Better luck next time!\n";
	return 0;
}

bool yahtzee(int dice[])
{	for(int i = 1; i < 5; i++)
	{	if(dice[i] == dice[i-1]) continue;
		else
			return false;
	}
	return true;
}

bool fourOfaKind(int dice[])
{	int counter = 1;
	for(int i = 1; i < 5; i++)
	{	if(dice[i] == dice[i-1])
			counter++;
		else
			break;
	}
	if(counter == 4)
		return true;
	else
		return false;
}

bool threeOfaKind(int dice[])
{	int counter = 1;
	for(int i = 1; i < 5; i++)
	{	if(dice[i] == dice[i-1])
			counter++;
		else
			break;
	}
	if(counter == 3)
		return true;
	else
		return false;
}

bool aPair(int dice[])
{	int counter = 1;
	for(int i = 1; i < 5; i++)
	{	if(dice[i] == dice[i-1])
			counter++;
		else
			break;
	}
	if(counter == 2)
		return true;
	else
		return false;
}

int keep(int num, int dice[])
{	int counter = 0;
	for(int i = 0; i < 5; i++)
		if(dice[i] == num)
			counter++;
	
	for(int j = 0; j < 5; j++)
		if(j < counter)
			dice[j] = num;
		else
			dice[j] = 0;
	return counter;
}
			
void sort(int dice[])
{	int num = dice[0];
	int idx = 0;
	for(int i = 1; i < 5; i++)
	{	if(dice[i] != num)
		{	if(idx == 0)
				idx = i;
			else
				idx++;
		}
		else
		{	int temp = dice[idx];
			dice[i] = dice[idx];
			dice[idx] = num;
		}
	}
}
	