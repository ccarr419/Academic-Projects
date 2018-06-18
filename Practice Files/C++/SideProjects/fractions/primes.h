#ifndef PRIMES_H
#define PRIMES_H
#include <iostream>
#include <vector>

using namespace std;

class primes {

public:
	primes(const int num = 100);
	void setPrimes(const int);
	void setPowers();
	void resetPrimes();
	void resetPowers();
	void printPrimes();
	int gcd(int, int);
	int lcm(int, int);
private:
	vector<int> primeNum;
	vector<int> powers;
	void gcdMaxHelper(int, int, int);
	void gcdMinHelper(int, int, int);
};

#endif
