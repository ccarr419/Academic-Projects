#include <iostream>
using namespace std;

class clockType {
	public:
		clockType(int h = 12, int m = 0, int sec = 0);
		clockType(const clockType &);
		void setTime(int, int, int);
		void setHours(int);
		void setMinutes(int);
		void setSeconds(int);
		int getHours() const;
		int getMinutes() const;
		int getSeconds() const;
		
		void incrementHours();
		void incrementMinutes();
		void incrementSeconds();
		void decrementHours();
		void decrementMinutes();
		void decrementSeconds();
		
		void printTime();
	
	private:
		int hr;
		int min;
		int sec;
};

clockType::clockType(int h, int m, int s)
{	setTime(h, m, s); }

clockType::clockType(const clockType &clock)
{	setTime(clock.getHours(), clock.getMinutes(), clock.getSeconds()); }

void clockType::setTime(int hr, int min, int sec)
{
		setHours(hr);
		setMinutes(min);
		setSeconds(sec);
}

void clockType::setHours(int hour)
{ 	
	if(hour > 0 && hour <= 12)
		hr = hour; 
	else
		hr = 12;
}

void clockType::setMinutes(int minute)
{	
	if(minute >= 0 && minute < 60)
		min = minute;
	else
		min = 0; 
}

void clockType::setSeconds(int second)
{	
	if(second >= 0 && second < 60)
		sec = second;
	else
		sec = 0;
}

int clockType::getHours() const
{	return hr; }

int clockType::getMinutes() const
{	return min; }

int clockType::getSeconds() const
{	return sec; }

void clockType::incrementHours()
{	setHours(getHours()+1); }

void clockType::incrementMinutes()
{	setMinutes(getMinutes()+1); }

void clockType::incrementSeconds()
{	setSeconds(getSeconds()+1); }

void clockType::decrementHours()
{	setHours(getHours()-1); }

void clockType::decrementMinutes()
{	setMinutes(getMinutes()-1); }

void clockType::decrementSeconds()
{	setSeconds(getSeconds()-1); }

void clockType::printTime()
{	cout << getHours() << ":" << getMinutes() << ":" << getSeconds() << endl; }

int main()
{
	clockType clock1(1, 30, 24);
	cout << "Clock1 is ";
	clock1.printTime();
	
	cout << "Clock2 is copied from Clock1 ";
	clockType clock2(clock1);
	clock1.printTime();
	
	clock2.setTime(10, 55, 8);	
	cout << "Clock2 is changed to ";
	clock2.printTime();
	return 0;
}
