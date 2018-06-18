#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

int main()
{
	vector<char> alphabet;
	for(int i = 65; i < 91; i++)
	{
		char c = i;
		alphabet.push_back(c);
	}
	
	vector<char>::iterator active_letter = alphabet.begin();

	string name = "YES", s = "";
	int count = name.length();
	vector<char> input;
	for(int i = 0; i < name.length(); i++)
		input.push_back(name[i]);
	
/*	while(!input.empty())
	{
		vector<char>::iterator i = input.begin(), lowest = i;	
		for(vector<char>::iterator j = i; j != input.end(); ++j)
		{
			if(*j < *lowest)
				lowest = j;
		}
		s += *lowest;
		input.erase(lowest);
	}*/
	
	char c = 'A';
	
	while(!input.empty())
	{
		vector<char>::iterator i = input.begin(), lowest = i;
		int lowest_diff = fabs(*i - c);
		for(vector<char>::iterator j = i; j != input.end(); ++j)
		{
			int diff = fabs(*j - c);
			if(diff > 13)
				diff = (26 - diff);
			
			if(diff < lowest_diff)
			{
				lowest_diff = diff;
				lowest = j;
			}	
		}
		cout << lowest_diff << endl;
		count += lowest_diff;
		c = *lowest;
		s += *lowest;
		input.erase(lowest);
	}
/*		
	for(int i = 0; i < s.length(); i++)
	{	
		int num1 = *active_letter, num2 = s[i];
		int diff = num1 - num2;
		
		while(*active_letter != s[i])
		{
				if(diff > 0)
				{
					if(diff > 13)
					{	if(active_letter == alphabet.end())
							active_letter = alphabet.begin();
						++active_letter;
						count++;
					}
					else
					{
						--active_letter;
						count++;
					}
				}
				else
				{
					if(diff < -13)
					{	if(active_letter == alphabet.begin())
							active_letter = alphabet.end();
						--active_letter;
						count++;
					}
					else
					{
						++active_letter;
						count++;
					}
				}
				
		}
	}*/
	cout << name << endl;
	cout << s << endl;
	cout << count << endl;
}