/*
	Author:		Christian Carreras
	File:		edge.h
	Class:		CSC 402
	Date:		10/11/2015
*/

#include <iostream>
using namespace std;

struct edge {
	int from;
	int to;
	int weight;
	edge(int f, int t) {
		from = t;
		to = t;
	}
	edge(int f, int t, int w) {
		edge(f, t);
		weight = w;
	}
};
