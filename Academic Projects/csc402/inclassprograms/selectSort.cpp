#include <iostream>
using namespace std;

void printList(int[], int);
void selectSort(int[], int);
void swap(int&, int&);

int main()
{
	int input;
	int list[100];
	int i = 0;
	int size = 0;
	cout << "Input your list to sort: (Press -1 to quit)\n";
	while(input != -1)
	{
		cin >> input;
		if(input == -1) break;
		list[i] = input;
		i++;
		size++;
	}
	cout << "Current list: ";
	printList(list, size);
	cout << "Now lets use select sort...\n";
	selectSort(list, size);
	cout << "Ordered list: ";
	printList(list, size);
	return 0;
}

void printList(int list[], int size)
{
	for(int i = 0; i < size; i++)
	{
		cout << list[i];
		cout << " ";
	}
	cout << endl;
}

void selectSort(int list[], int size)
{
	for(int i = 0; i < size; i++)
	{
		int currLow = i;
		for(int j = i; j < size; j++)
		{
			if(list[j] < list[i] && list[j] < list[currLow])
				currLow = j;	
		}
		if(currLow == i) continue;
		swap(list[i], list[currLow]);
		printList(list, size);
	}
}

void swap(int &i, int &j)
{
	int temp = i;
	i = j;
	j = temp;
}