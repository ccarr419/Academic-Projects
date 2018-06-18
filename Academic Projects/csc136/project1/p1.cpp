/* * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                 * 
 * Author: Christian Carreras                      *
 *                                                 *
 * Course: CSC 136                                 *
 *                                                 *
 * Assignment: 1                                   *
 *                                                 *
 * Due Date: September 12, 2013 at 11:59 PM        *
 *                                                 *
 * File: p1.cpp                                    *
 *                                                 *
 * Purpose: This program reads a user specified    *
 *  file and lists the number of characters,       *
 *  paragraphs, words and how many letters         *
 *  are in the words of said file.                 *
 *                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

void getFileName(string&); //Gets file name
bool openFile(ifstream&, string&); //Opens file
void getChar(ifstream&, int&, int&); //Gets # of characters & paragraphs
void getWords(ifstream&, int[], string); //Sorts words by # of letters
void Output(string, int&, int&, int[]); //Outputs all data
int getTotalWords(int[]); //Gets # of words


int main()
{
  ifstream inf;
  string fileName; //File entered by user
  bool fileOpen; //Checks if file exists
  int count[10]; //Sorts words by # of letters
  int characters = 0; //Total characters in file
  int paragraphs = 0; //Total paragraphs in file

  //Sets all elements in the count array to 0.
  for(int i = 0; i < 10; i++)
    {
      count[i] = 0;
    }

  //Get file from user.
  getFileName(fileName);

  //Attempt to open file.
  fileOpen = openFile(inf, fileName);

  //Checks to see if file exists.
  if(fileOpen == true)
    {
      //Find total characters/paragraphs in the file.
      getChar(inf, paragraphs, characters);

      //Sort words by # of letters.
      getWords(inf, count, fileName);

      //Output the data to screen.
      Output(fileName, characters, paragraphs, count);
    }
  else
    {
      //Error message if file does not exist.
      cout << "ERROR: Failure to open file.\n";
    }

  return 0;
}

/*******************************************
 *                                         *
 * Funtion Name: getFileName               *
 *                                         *
 * Description: Asks user for file to open *
 *                                         *
 * Parameters: string fileName             *
 *                                         *
 * Return Value: none                      *
 *                                         *
 *******************************************/
void getFileName(string &fileName)
{
  cout << "\nPlease enter the file name: ";
  cin >> fileName;
}

/****************************************************
 *                                                  *
 * Function Name: openFile                          *
 *                                                  *
 * Description: Attempts to open the file specified *
 *              by the user and returns a false     *
 *              value if it does not exist          *
 *                                                  *
 * Parameters: ifstream inf                         *
 *             string fileName                      *
 *                                                  *
 * Return Value: bool fileOpen                      *
 *                                                  *
 ****************************************************/
bool openFile(ifstream &inf, string &fileName)
{
  bool fileOpen;
  inf.open(fileName.c_str());
  //If file does not exist.
  if (inf.fail())
    return fileOpen = false;
  //If file does exist.
  else
    return fileOpen = true;
}

/**************************************************************
 *                                                            *
 * Function Name: getChar                                     *
 *                                                            *
 * Description: Finds the number of characters and paragraphs *
 *                                                            *
 * Parameters: ifstream inf                                   *
 *             int paragraphs                                 *
 *             int characters                                 *
 *                                                            *
 * Return Value: none                                         *
 *                                                            *
 **************************************************************/
void getChar(ifstream &inf, int &paragraphs, int &characters)
{
  char ch;
  //Use get fucntion to get all characters in file.
   while(inf.get(ch)) 
    {
      //Detect new line character for # of paragraphs.
      if(ch == '\n')
	{
	  paragraphs++;
	  characters++;
	}
      //Add to charcters if not a white space.
      else
	{
	  characters++;
	}
    }
}

/*******************************************************************
 *                                                                 *
 * Function Name: getWords                                         *
 *                                                                 *
 * Description: This function finds the number of letters in the   *
 *              words of the user specified file and sorts them    *
 *              into the appropriate space in the count array      *
 *              with count[0] holding all words with 10+ letters   *
 *                                                                 *
 * Parameters: ifstream inf                                        *
 *             int count[10]                                       *
 *             string fileName                                     *
 *                                                                 *
 * Return Value: none                                              *
 *                                                                 *
 *******************************************************************/
void getWords(ifstream &inf, int count[], string fileName)
{
  string word;
  //Rewind the file.
  inf.close();
  inf.clear();
  inf.open(fileName.c_str());
  while(inf >> word)
    {
      word.size();
      //Sorts according to # of letters.
      if(word.size() < 10)
	count[word.size()]++;
      //Sorts all words with 10+ letters to count[0].
      else
	count[0]++;
    }
}

/*********************************************************************
 *                                                                   *
 * Function Name: Output                                             *
 *                                                                   *
 * Description: Outputs all data collected from other functions      *
 *                                                                   *
 * Parameters: string fileName                                       *
 *             int characters                                        *
 *             int paragraphs                                        *
 *             int count[10]                                         *
 *                                                                   *
 * Return Value: none                                                *
 *                                                                   *
 *********************************************************************/
void Output(string fileName, int &characters, int &paragraphs, int count[])
{
  int words = 0;
  //Get the total amount of words in the file.
  words = getTotalWords(count);
  cout << "\nFile: " << fileName;
  cout << "\tCharacters: " << characters;
  cout << "\t\tWords: " << words;
  cout << "\tParagraphs: " << paragraphs << endl;
  cout << "\nAnalysis of Words\n\n";
  cout << "Size\t1\t2\t3\t4\t5\t6\t7\t8\t9\t10+\n";
  cout << "#Words";
  //Display the words sorted by # of letter from 1-10+.
  for(int i = 1; i < 10; i++)
    {
      cout << "\t" << count[i];
    }
  cout << "\t" << count[0] << endl;
}

/*********************************************************
 *                                                       *
 * Function Name: getTotalWords                          *
 *                                                       *
 * Description: Adds the total number of words           *
 *                                                       *
 * Parameters: int count[10]                             *
 *                                                       *
 * Return Value: int words                               *
 *                                                       *
 *********************************************************/
int getTotalWords(int count[])
{
  int words;
  for(int i = 0; i < 10; i++)
    {
      words += count[i];
    }
  return words;
}
