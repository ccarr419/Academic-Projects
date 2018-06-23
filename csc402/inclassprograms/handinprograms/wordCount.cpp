#include <iostream>
#include <fstream>
#include <cctype>
#include <map>
using namespace std;

int main()
{
	ifstream inf;
	inf.open("article.txt");
	
	map<string, int> m;
	int num;
	char c;
	string str = "";
	while(inf.get(c))
	{
		if(c >= 65 && c <= 122)
		{
			c = tolower(c);
			str += c;
		}
		
		else
		{
			if(str == "") continue;
			
			else if(!m.count(str))
				m.insert(pair<string, int>(str, 1));
			
			else
			{
				map<string, int>::iterator it = m.find(str);
				it->second++;
			}
			
			str = "";
		}
	}
	
	map<string, int>::iterator max = m.begin();
	for(map<string, int>::iterator i = m.begin(); i != m.end(); ++i)
	{
		if(i->second > max->second)
			max = i;
	}
	
	cout << "The word that occurs the most is '";
	cout << max->first << "' with " << max->second << " occurrences.\n";
}
