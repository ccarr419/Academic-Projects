#include <iostream>
using namespace std;

class employeeTimeCard {
	public:
		employeeTimeCard(string fname, string lname, char offloc, char unst, 
		string id, int hrs, float rate, int dep, int ovtm);
							
		void setTimeCard(string fname, string lname, char offloc, char unst,
		string id, int hrs, float rate, int dep, int ovtm);
							
		void setFirstName(string);
		void setLastName(string);
		void setOfficeLocation(char);
		void setUnionStanding(char);
		void setEmployeeId(string);
		void setHours(int);
		void setRate(float);
		void setDependents(int);
		void setOvertime(int);
		
		string getFirstName() const;
		string getLastName() const;
		char getOfficeLocation() const;
		char getUnionStanding() const;
		string getEmployeeId() const;
		int getHours() const;
		float getRate() const;
		int getDependents() const;
		int getOvertime() const;
		
		void printTimeCard() const;
		float grossPay() const;
		float federalTax() const;
		float socialSecurity() const;
		float cityTax() const;
		float unionDues() const;
		float netPay() const;		
		
	private:
		string last_name;
		string first_name;
		char office_location;
		char union_standing;
		string employee_id;
		int employee_hours;
		float employee_rate;
		int num_dependents;
		int overtime_hours;
};
		
employeeTimeCard::employeeTimeCard(string fname, string lname,
char offloc, char unst, string id, int hrs, float rate, int dep, int ovtm)
{
	setTimeCard(fname, lname, offloc, unst, id, hrs, rate, dep, ovtm);
}							
							
void employeeTimeCard::setTimeCard(string fname, string lname,
char offloc, char unst, string id, int hrs, float rate, int dep, int ovtm)
{
	setFirstName(fname);
	setLastName(lname);
	setOfficeLocation(offloc);
	setUnionStanding(unst);
	setEmployeeId(id);
	setHours(hrs);
	setRate(rate);
	setDependents(dep);
	setOvertime(ovtm);
}		
		
void employeeTimeCard::setFirstName(string fname)
{
	first_name = fname;
}	
		
void employeeTimeCard::setLastName(string lname)
{
	last_name = lname;
}
		
void employeeTimeCard::setOfficeLocation(char offloc)
{
	office_location = offloc;
}
		
void employeeTimeCard::setUnionStanding(char unst)
{
	union_standing = unst;
}	
		
void employeeTimeCard::setEmployeeId(string id)
{
	employee_id = id;
}	
		
void employeeTimeCard::setHours(int hrs)
{
	employee_hours = hrs;
}	
		
void employeeTimeCard::setRate(float rate)
{
	employee_rate = rate;
}	
		
void employeeTimeCard::setDependents(int dep)
{
	num_dependents = dep;
}	
		
void employeeTimeCard::setOvertime(int ovtm)
{
	overtime_hours = ovtm;
}	
		
string employeeTimeCard::getFirstName() const
{
	return first_name;
}	
		
string employeeTimeCard::getLastName() const
{
	return last_name;
}	
		
char employeeTimeCard::getOfficeLocation() const
{
	return office_location;
}	
		
char employeeTimeCard::getUnionStanding() const
{
	return union_standing;
}	
		
string employeeTimeCard::getEmployeeId() const
{
	return employee_id;
}	
		
int employeeTimeCard::getHours() const
{
	return employee_hours;
}	
		
float employeeTimeCard::getRate() const
{
	return employee_rate;
}	
		
int employeeTimeCard::getDependents() const
{
	return num_dependents;
}	
		
int employeeTimeCard::getOvertime() const
{
	return overtime_hours;
}	
		
		
void employeeTimeCard::printTimeCard() const
{
	cout << getLastName() << " " << getFirstName() << " " << getOfficeLocation();
	cout << " " << getUnionStanding() << " " << getEmployeeId() << endl;
	cout << "Gross Pay: $" << grossPay() << endl << endl;
	cout << "Federal Tax: $" << federalTax() << endl << endl;
	cout << "Social Security: $" << socialSecurity() << endl << endl;
	cout << "Net Pay: $" << netPay() << endl;
}	
		
float employeeTimeCard::grossPay() const
{
	return ( ( getHours() * getRate() ) + ( getOvertime() * 1.5 * getRate() ) );
}	
		
float employeeTimeCard::federalTax() const
{
	return ( 0.14 * ( grossPay() - ( 13 * getDependents() ) ) );
}	
		
float employeeTimeCard::socialSecurity() const
{
	return ( 0.052 * grossPay() );
}	
		
float employeeTimeCard::cityTax() const
{
	if(getOfficeLocation() == 'c')
		return ( 0.04 * grossPay() );
	else
		return 0.0;
}	
		
float employeeTimeCard::unionDues() const
{
	if(getUnionStanding() == 'u')
		return ( 6.75 * grossPay() );
	else
		return 0.0;
}
		
float employeeTimeCard::netPay() const
{
	int deductions = (federalTax() + socialSecurity() + cityTax() + unionDues());
	return grossPay() - deductions;
}

int main()
{	
	string fname;
	string lname;
	char offloc;
	char unst;
	string id;
	int hrs;
	float rate;
	int dep;
	int ovtm;

	cout << "Enter first name: ";
	cin >> fname;
	cout << "Enter last name: ";
	cin >> lname;
	cout << "Enter office location: ";
	cin >> offloc;
	cout << "Enter union standing: ";
	cin >> unst;
	cout << "Enter employee id: ";
	cin >> id;
	cout << "Enter regular hours: ";
	cin >> hrs;
	cout << "Enter hourly rate: ";
	cin >> rate;
	cout << "Enter number of dependents: ";
	cin >> dep;
	cout << "Enter amount of overtime hours: ";
	cin >> ovtm;
		
	employeeTimeCard timeCard(fname, lname, offloc, unst, id, hrs, rate, dep, ovtm);
	cout << endl;
	timeCard.printTimeCard();
	cout << endl;
		
	return 0;
}
