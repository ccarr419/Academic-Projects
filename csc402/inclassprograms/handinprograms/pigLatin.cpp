#include <iostream>
#include <string>
using namespace std;

string 	translate(string);
bool	isVowel(char);

int main()
{
	string inputString, outputString;
	cout << "Enter your string here: ";
	cin >> inputString;
	outputString = translate(inputString);
	cout << "Translated to pig latin: " << outputString << endl;
}

string translate(string input)
{
	string temp1, temp2, output;
	
	if(input == "")
		return "";
	
	temp1 = "";
	temp2 = "";
	for(int i = 0; i < input.length(); i++)
	{
		if(i == 0 && isVowel(input[i]))
			return (input += "-way");
		if(isVowel(input[i]))
		{
			for(int j = i; j < input.length(); j++)
				temp2 += input[j];
			output = temp2;
			output += "-";
			output += temp1;
			output += "ay";
			return output;
		}
		else
			temp1 += input[i];
	}
	return (input += "-way");
}

bool isVowel(char input)
{
	const char vowels[12] = {'a', 'e', 'i', 'o', 'u', 'y', 
				'A', 'E', 'I', 'O', 'U', 'Y'};
	for(int i = 0; i < 12; i++)
	{	if(input == vowels[i])
			return true;
	}
	return false;	
}
