/**************************************************
This program opens a file and uses the information
within to display if the student passed the test
as well as how many they got right/wrong and
which numbers on the test the got wrong.

Author: Christian Carreras
Due Date: 12/11/2012
**************************************************/
#include <iostream>
#include <fstream> //Required to open file
using namespace std;

//Function prototype
char getAnswers(ifstream &fp);

int main()
{
  ifstream fp;
  //Correct answers for the driving test
  char correct_answers[20]={'B', 'D', 'A', 'A', 'C', 'A', 'B', 'A', 'C', 'D', 'B', 'C', 'D', 'A', 'D', 'C', 'C', 'B', 'D', 'A'};
  char student_answer[20];
  int student_grade[20];
  int counter1 = 0; //Number right
  int counter2 = 20; //Number wrong
  //Open file driving.dat
  fp.open("driving.dat");
  if(!fp)
    {
      cout << "Error opening file\n";
      return 0;
    }

  //Header table
  cout << "Passed\t\tCorrect\t\tWrong\t\tNumbers Wrong\n";
  cout << "--------------------------------------------------------------\n";

  //Gets information from getAnswers and displays information
  for(int i = 0; i < 20; i++)
    {
      student_answer[i] = getAnswers(fp);
      if(student_answer[i] == correct_answers[i])
	{
	  student_grade[i] = 1;
	  counter1++;
	  counter2--;
	}
      else
	student_grade[i] = 0;
    }

  if(counter1 < 15)
    {
      cout << "No\t\t" << counter1 << "\t\t" << counter2 << "\t\t";
      for(int i = 0; i < 20; i++)
	{
	  if(student_grade[i] == 0)
	    {
	      cout << i + 1 << " ";
	    }
	}
    }

  else
    {
      cout << "Yes\t\t" << counter1 << "\t\t" << counter2 << "\t\t";
      for(int i = 0; i < 20; i++)
	{
	  if(student_grade[i] == 0)
	    {
	      cout << i + 1 << " ";
	    }
	}
    }

  //Reset
  cout << endl;
  counter1 = 0;
  counter2 = 20;

  //Same
  for(int i = 0; i < 20; i++)
    {
      student_answer[i] = getAnswers(fp);
      if(student_answer[i] == correct_answers[i])
	{
	  student_grade[i] = 1;
	  counter1++;
	  counter2--;
	}
      else
	student_grade[i] = 0;
    }

  if(counter1 < 15)
    {
      cout << "No\t\t" << counter1 << "\t\t" << counter2 << "\t\t";
      for(int i = 0; i < 20; i++)
	{
	  if(student_grade[i] == 0)
	    {
	      cout << i + 1 << " ";
	    }
	}
    }

  else
    {
      cout << "Yes\t\t" << counter1 << "\t\t" << counter2 << "\t\t";
      for(int i = 0; i < 20; i++)
	{
	  if(student_grade[i] == 0)
	    {
	      cout << i + 1 << " ";
	    }
	}
    }

  //Reset
  cout << endl;
  counter1 = 0;
  counter2 = 20;

  //Same
  for(int i = 0; i < 20; i++)
    {
      student_answer[i] = getAnswers(fp);
      if(student_answer[i] == correct_answers[i])
	{
	  student_grade[i] = 1;
	  counter1++;
	  counter2--;
	}
      else
	student_grade[i] = 0;
    }

  if(counter1 < 15)
    {
      cout << "No\t\t" << counter1 << "\t\t" << counter2 << "\t\t";
      for(int i = 0; i < 20; i++)
	{
	  if(student_grade[i] == 0)
	    {
	      cout << i + 1 << " ";
	    }
	}
    }

  else
    {
      cout << "Yes\t\t" << counter1 << "\t\t" << counter2 << "\t\t";
      for(int i = 0; i < 20; i++)
	{
	  if(student_grade[i] == 0)
	    {
	      cout << i + 1 << " ";
	    }
	}
    }

  //Reset
  cout << endl;
  counter1 = 0;
  counter2 = 20;

  //Same
  for(int i = 0; i < 20; i++)
    {
      student_answer[i] = getAnswers(fp);
      if(student_answer[i] == correct_answers[i])
	{
	  student_grade[i] = 1;
	  counter1++;
	  counter2--;
	}
      else
	student_grade[i] = 0;
    }

  if(counter1 < 15)
    {
      cout << "No\t\t" << counter1 << "\t\t" << counter2 << "\t\t";
      for(int i = 0; i < 20; i++)
	{
	  if(student_grade[i] == 0)
	    {
	      cout << i + 1 << " ";
	    }
	}
    }

  else
    {
      cout << "Yes\t\t" << counter1 << "\t\t" << counter2 << "\t\t";
      for(int i = 0; i < 20; i++)
	{
	  if(student_grade[i] == 0)
	    {
	      cout << i + 1 << " ";
	    }
	}
    }

  //Reset
  cout << endl;
  counter1 = 0;
  counter2 = 20;

  //Same
  for(int i = 0; i < 20; i++)
    {
      student_answer[i] = getAnswers(fp);
      if(student_answer[i] == correct_answers[i])
	{
	  student_grade[i] = 1;
	  counter1++;
	  counter2--;
	}
      else
	student_grade[i] = 0;
    }

  if(counter1 < 15)
    {
      cout << "No\t\t" << counter1 << "\t\t" << counter2 << "\t\t";
      for(int i = 0; i < 20; i++)
	{
	  if(student_grade[i] == 0)
	    {
	      cout << i + 1 << " ";
	    }
	}
    }

  else
    {
      cout << "Yes\t\t" << counter1 << "\t\t" << counter2 << "\t\t";
      for(int i = 0; i < 20; i++)
	{
	  if(student_grade[i] == 0)
	    {
	      cout << i + 1 << " ";
	    }
	}
    }

  //Reset
  cout << endl;
  counter1 = 0;
  counter2 = 20;

  //Same
  for(int i = 0; i < 20; i++)
    {
      student_answer[i] = getAnswers(fp);
      if(student_answer[i] == correct_answers[i])
	{
	  student_grade[i] = 1;
	  counter1++;
	  counter2--;
	}
      else
	student_grade[i] = 0;
    }

  if(counter1 < 15)
    {
      cout << "No\t\t" << counter1 << "\t\t" << counter2 << "\t\t";
      for(int i = 0; i < 20; i++)
	{
	  if(student_grade[i] == 0)
	    {
	      cout << i + 1 << " ";
	    }
	}
    }

  else
    {
      cout << "Yes\t\t" << counter1 << "\t\t" << counter2 << "\t\t";
      for(int i = 0; i < 20; i++)
	{
	  if(student_grade[i] == 0)
	    {
	      cout << i + 1 << " ";
	    }
	}
    }

  //Reset
  cout << endl;
  counter1 = 0;
  counter2 = 20;

  //Same
  for(int i = 0; i < 20; i++)
    {
      student_answer[i] = getAnswers(fp);
      if(student_answer[i] == correct_answers[i])
	{
	  student_grade[i] = 1;
	  counter1++;
	  counter2--;
	}
      else
	student_grade[i] = 0;
    }

  if(counter1 < 15)
    {
      cout << "No\t\t" << counter1 << "\t\t" << counter2 << "\t\t";
      for(int i = 0; i < 20; i++)
	{
	  if(student_grade[i] == 0)
	    {
	      cout << i + 1 << " ";
	    }
	}
    }

  else
    {
      cout << "Yes\t\t" << counter1 << "\t\t" << counter2 << "\t\t";
      for(int i = 0; i < 20; i++)
	{
	  if(student_grade[i] == 0)
	    {
	      cout << i + 1 << " ";
	    }
	}
    }

  cout << endl;

  return 0;
}

//This function directs the information from the file to an array
char getAnswers(ifstream &fp)
{
  char student_answer[20];
  while(fp.eof()==false)
    {
      for(int i = 0; i < 20; i++)
	{
	  fp>>student_answer[i];
	  return student_answer[i];
	}
    }
}
 



