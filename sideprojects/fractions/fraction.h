#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>

using namespace std;

class fraction {	

public:
	
	fraction(int num = 1, int den = 1);
	
	void setNumerator(int);
	
	void setDenominator(int);
	
	void setFraction(int, int);
	
	int getNumerator() const;
	
	int getDenominator() const;
	
	bool operator<(fraction&) const;
	
	bool operator<(double) const;
	
	bool operator>(fraction&) const;
	
	bool operator>(double) const;
	
	bool operator<=(fraction&) const;
	
	bool operator<=(double) const;
	
	bool operator>=(fraction&) const;
	
	bool operator>=(double) const;
	
	bool operator==(fraction&) const;
	
	bool operator==(double) const;
	
	bool operator!=(fraction&) const;
	
	bool operator!=(double) const;
	
	void operator=(fraction&);
	
	void operator*=(fraction&);
	
	void operator/=(fraction&);
	
	void operator+=(fraction&);
	
	void operator-=(fraction&);
	
	double convertToDecimal() const;
		
	void checkReduce();
	
	void printImproper() const;
	
private:
	int numerator;
	int denominator;
};

ostream &operator<<(ostream&, const fraction&);
	
#endif
