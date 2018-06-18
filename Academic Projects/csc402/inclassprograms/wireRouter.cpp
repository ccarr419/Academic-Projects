#include <iostream>
#include <queue>
#include <fstream>
#include <stack>
using namespace std;

struct position {
	int row;
	int col;
	
	position(int r, int c) {
		row = r;
		col = c;
	}
	
	bool equal(position p) {
		return row == p.row && col == p.col;
	}
	
	position upper() {
		return position(row-1, col);
	}
	
	position lower() {
		return position(row+1, col);
	}
	
	position right() {
		return position(row, col+1);
	}
	
	position left() {
		return position(row, col-1);
	}
	
	void print() {
		cout << "(" << row << ", " << col << ")" << endl;
	}
};

void readGrid(int[6][6]);
bool findPath(position, position, int[6][6]);
void printPath(position, position, int[6][6]);
void printGrid(int[6][6]);

int main() {
	int grid[6][6];
	readGrid(grid);
	position startPin(1, 1);
	position endPin(4, 3);
	if(findPath(startPin, endPin, grid)) {
		cout << "Path found!\n";
		printGrid(grid);
		printPath(startPin, endPin, grid);
	}
	
	else
		cout << "No path found.\n";
	
	return 0;
}

void readGrid(int grid[6][6]) {
	ifstream fin;
	fin.open("grid.dat");
	if(fin.fail()) {
		cout << "Error reading file";
		return;
	}
	
	for(int i = 0; i < 6; i++)
		for(int j = 0; j < 6; j++)
			fin >> grid[i][j];
}

bool findPath(position startPin, position endPin, int grid[6][6]) {
	if(startPin.equal(endPin))
		return true;
	queue<position> q;
	position thePosition = startPin;
	q.push(startPin);
	
	while(!q.empty()) {
		thePosition = q.front();
		q.pop();
		int step = grid[thePosition.row][thePosition.col];
		if(grid[thePosition.upper().row][thePosition.upper().col] != -1) {
			q.push(thePosition.upper());
			grid[thePosition.upper().row][thePosition.upper().col] = step+1;
			if(thePosition.upper().equal(endPin))
				return true;
		}
		
		if(grid[thePosition.lower().row][thePosition.lower().col] != -1) {
			q.push(thePosition.lower());
			grid[thePosition.lower().row][thePosition.lower().col] = step+1;
			if(thePosition.lower().equal(endPin))
				return true;
		}
		
		if(grid[thePosition.left().row][thePosition.left().col] != -1) {
			q.push(thePosition.left());
			grid[thePosition.left().row][thePosition.left().col] = step+1;
			if(thePosition.left().equal(endPin))
				return true;
		}
		
		if(grid[thePosition.right().row][thePosition.right().col] != -1) {
			q.push(thePosition.right());
			grid[thePosition.right().row][thePosition.right().col] = step+1;
			if(thePosition.right().equal(endPin))
				return true;
		}
	}
	return false;
}

void printPath(position startPin, position endPin, int grid[6][6]) {
	int step = grid[endPin.row][endPin.col];
	stack<position> s;
	s.push(endPin);
	while(step != 1) {
		position p = s.top();
		step = grid[p.row][p.col];
		if(grid[p.upper().row][p.upper().col] == step-1)
			s.push(p.upper());
		
		if(grid[p.lower().row][p.lower().col] == step-1)
			s.push(p.lower());
		
		if(grid[p.left().row][p.left().col] == step-1)
			s.push(p.left());
		
		if(grid[p.right().row][p.right().col] == step-1)
			s.push(p.right());
	}
	
	while(!s.empty()) {
		s.top().print();
		s.pop();
	}
}

void printGrid(int grid[6][6]) {
	for(int i = 0; i < 6; i++)
	{	for(int j = 0; j < 6; j++)
			cout << grid[i][j] << ' ';
		cout << endl;
	}
}
