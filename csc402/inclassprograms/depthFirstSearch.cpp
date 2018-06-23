#include <iostream>
#include <set>
using namespace std;

void DFS(int startNode, bool flag);

int main()
{
	return 0;
}

void DFS(int startNode, bool flag)
{
	set<int> s; //store all visited nodes
	s.insert(startNode);
	for(int i = 0; i < numVertices; i++)
	{
		if(matrix[startNode][i] == 1 && s.find(i) == s.end())
		{
			DFS(i, false);
		}
	}
}
