// File: Demo.h
// Debug exercise to learn how classes and the debugger work

#ifndef DEMO_H
#define DEMO_H

class Demo
{
	public:
		Demo(int = 10, double = 50.0);		// constructor
		Demo(const Demo&);			// copy constructor
		~Demo();				// destructor
		int getX() const;			// inspector for x
		Demo operator=(const Demo &);		// overloaded assignment
		
		Demo operator++(int);			// postincrement
	private:
		int	x;
		double	y;
};

#endif
