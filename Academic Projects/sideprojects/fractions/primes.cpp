#include <iostream>
#include "primes.h"
#include <assert.h>
#include <cmath>

using namespace std;

primes::primes(const int num)
{	setPrimes(num);
	setPowers();
}

void primes::setPrimes(const int num)
{	for(int i = 2; i < num; i++)
	{	for(int j = 2; j <= i; j++)
		{	if(i == j)
				primeNum.push_back(i);
			else if(i % j == 0)
				break;
		}
	}	
}

void primes::setPowers()
{	powers.resize(primeNum.size(), 0);
}

void primes::resetPrimes()
{	primeNum.clear(); }

void primes::resetPowers()
{	powers.clear(); }

void primes::printPrimes()
{	for(unsigned i = 0; i < primeNum.size(); i++)
	{	cout << primeNum.at(i) << endl; }
}

int primes::gcd(int a, int b)
{	if(a == b)
		return a;
	else
	{	int max = fmax(a, b);
		int min = fmin(a, b);
		assert(max > 0 && min > 0)
		if(max == 1 || min == 1)
			return(1);
		else
		{	gcdMaxHelper(max, 0, 0);
		}
	}
}

void primes::gcdMaxHelper(int min, int prime, int power)
{	if(min == 1)
		return;
	else
	{	do
		{	powers[power] += 1;
		} 	while(min % pow(primeNum.at(prime), powers.at(power)) == 0);
		
		powers.at(power) -= 1;
		
		min = min/pow(primeNum.at(prime), powers.at(power));
		gcdMaxHelper(min, prime++, power++);
	}
}



