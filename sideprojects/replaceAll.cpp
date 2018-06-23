#include <iostream>
#include <string>
using namespace std;

string replaceAll(string, string, string);
string replaceAllNoReplace(string, string, string);
int main(int argc, char** argv) {
	cout << "Before: " << argv[1] << endl;
	string myStr = replaceAll(argv[1], argv[2], argv[3]);
	cout << "After: " << myStr << endl;
	
	cout << endl << "NO REPLACE\n\n";
	
	cout << "Before: " << argv[1] << endl;
	myStr = replaceAllNoReplace(argv[1], argv[2], argv[3]);
	cout << "After: " << myStr << endl;
}

string replaceAll(string inStr, string toRep, string repStr) {
	size_t pos = 0, from = 0;
	while((pos = inStr.find(toRep, from)) != std::string::npos) {
		inStr.replace(pos, toRep.length(), repStr, 0, repStr.length());
		from = pos+repStr.length();
	}		
	return inStr;
}

string replaceAllNoReplace(string inStr, string toRep, string repStr) {
	size_t pos = 0, from = 0;
	while((pos = inStr.find(toRep, from)) != std::string::npos) {
		inStr.erase(pos, toRep.length());
		inStr.insert(pos, repStr);
		from = pos+repStr.length();
	}
	return inStr;
}

/* JAVA EQUIVALENT
public string replaceAllNoReplace(string inStr, string toRep, string repStr) {
	int pos = 0, from = 0;
	while((pos = inStr.indexOf(toRep, from)) != -1) {
		inStr.erase(pos, toRep.length());
		inStr.insert(pos, repStr);
		from = pos+repStr.length();
	}
}
*/	
