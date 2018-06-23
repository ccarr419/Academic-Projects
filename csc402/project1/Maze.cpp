/*There is a maze, use recursive method to get out
**print the route each time
**                                                */

#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include<iostream>

using namespace std;

void print_array(char maze[12][12],int max_row,int max_col)
{		//delay(300);
		system("sleep 1");
		system("clear");
		//gotoxy(1,1);
        for(int i=0;i<max_row;i++)
        {
                for(int j=0;j<max_col;j++)
                cout<<maze[i][j]<<' ';
                cout<<endl;
        }
        
}
void mazeTraverse(char maze[12][12],int start_row,int start_col)
{
        if(start_row>=0&&start_row<12&&start_col>=0&&start_col<12)
        {
        
                if(start_row==4&&start_col==11)
                cout<<"success"<<endl;
                if(maze[start_row][start_col]=='.')
                {
                        maze[start_row][start_col]='x';
                        print_array(maze,12,12);
                        mazeTraverse(maze,start_row-1,start_col);
                        mazeTraverse(maze,start_row,start_col-1);
                        mazeTraverse(maze,start_row+1,start_col);
                        mazeTraverse(maze,start_row,start_col+1);
						maze[start_row][start_col]='*';
                        
                }
        }
}

main()
{
        char array[][12]={{'#','#','#','#','#','#','#','#','#','#','#','#'},
                           { '#','.','.','.','#','.','.','.','.','.','.','#'},
                           { '.','.','#','.','#','.','#','#','#','#','.','#'},
                           { '#','#','#','.','#','.','.','.','.','#','.','#'},
                           {'#','.','.','.','.','#','#','#','.','#','.','.'},
                           { '#','#','#','#','.','#','.','#','.','#','.','#'},
                           {'#','.','.','#','.','#','.','#','.','#','.','#'},
                           { '#','#','.','#','.','#','.','#','.','#','.','#'},
                           { '#','.','.','.','.','.','.','.','.','#','.','#'},
                           {'#','#','#','#','#','#','.','#','#','#','.','#' },
                           { '#','.','.','.','.','.','.','#','#','#','.','#'},
                           {'#','#','#','#','#','#','#','#','#','#','#','#'}};  
        mazeTraverse(array,2,0);
}

