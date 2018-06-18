#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

using namespace std;

void findNotes(const string[], string[], vector<string>&, int);
void printFretboard(map<int, vector<string> >&, int, int, int);

int main()
{
	const string sharp[12] = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
	const string flat[12]  = {"A", "Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab"};
	string tuning[6] = {"E", "A", "D", "G", "B", "E"};
	
	int num_strings = 6;
	int curr_string = 0;
	int fret_num = 0;
	
	char choice;

	vector<string> notes;
	map<int, vector<string> > guitar_string;
	
	cout << "Would you like to use sharps (s) or flats (f)? ";
	cin >> choice;
	cout << "Enter your tuning: ";
	cin >> tuning[0] >> tuning[1] >> tuning[2] >> tuning[3] >> tuning[4] >> tuning[5];
	cout << endl;
	
	if(choice == 's')
	{	for(int i = 0; i < num_strings; i++)
		{
			findNotes(sharp, tuning, notes, curr_string);
			guitar_string[curr_string] = notes;
			curr_string++;
			notes.clear();
		}
	}
	
	else if(choice == 'f')
	{	for(int i = 0; i < num_strings; i++)
		{
			findNotes(flat, tuning, notes, curr_string);
			guitar_string[curr_string] = notes;
			curr_string++;
			notes.clear();
		}
	}
	
	curr_string = 0;	
	printFretboard(guitar_string, num_strings, curr_string, fret_num);		
	
	return 0;
}

void findNotes(const string notation[], string tuning[], vector<string> &notes, int curr_string)
{
	for(int i = 0; i < 12; i++)
	{
		if(notation[i] == tuning[curr_string])
		{
			for(int j = i; j < 12; j++)
				notes.push_back(notation[j]);
			
			for(int j = 0; j <= i; j++)
				notes.push_back(notation[j]);
				
			return;
		}
	}
}

void printFretboard(map<int, vector<string> > &guitar_string, int num_strings, int curr_string, int fret_num)
{
	for(int i = num_strings; i > 0; i--)
		cout << "\t" << i;
		
	cout << "\n\t";
	
	for(int i = 0; i < 42; i++)
		cout << "-";
		
	cout << "\n";
		
	for(int i = 0; i < guitar_string[curr_string].size(); i++)
	{			
		for(int j = curr_string; j < num_strings; j++)
		{
			if(j == 0)
				cout << fret_num << "\t" << guitar_string[j].at(i);
			else
				cout << "\t" << guitar_string[j].at(i);
		}
		cout << "\n";
		fret_num++;
		
		cout << "\t";
		for(int i = 0; i < 42; i++)
			cout << "-";
		cout << "\n";
	}
}
