#include <iostream>
using namespace std;

studentType getOlder(studentType);
void 		getOlder(studentType&);

struct studentType
{
	string 	name;
	int 	age;
	float 	gpa;
};

int main()
{
	studentType s1;
	s1.name = "Chris";
	s1.age = 21;
	s1.gpa = 3.0;
	
	getOlder(s1);
	cout << s1.age << endl;
	
	return 0;
}

studentType getOlder(studentType s1)
{	s1.age++;
	return s1; }

void getOlder(studentType &s1)
{	s1.age++; }
