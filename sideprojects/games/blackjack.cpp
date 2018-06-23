#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
using namespace std;

string findSuit(int);
string findRank(int);
string convertInt(int);
int getScore(int, int);
bool blackJack(int);

int main()
{	srand(time(NULL));
	int hand[5], tempCard, score = 0, idx = 0;
	
	hand[idx] = (rand() % (52 - 1) + 1);
	idx++;
	
	do
	{	tempCard = (rand() % (52 - 1) + 1);
	}	while(tempCard == hand[0]);
	
	hand[idx] = tempCard;
	idx++;
	
	cout << "Card One: " << findRank(hand[0]) << " of " << findSuit(hand[0]) << endl;
	cout << "Card Two: " << findRank(hand[1]) << " of " << findSuit(hand[1]) << endl;

	score = getScore(hand[0], score);
	score += getScore(hand[1], score);
	
	cout << "Current Score: " << score << endl;
	
	char draw;
	cout << "Would you like another card? [y: yes | n: no] ";
	cin >> draw;
	
	if(draw == 'y')
	{	do
		{	tempCard = (rand() % (52 - 1) + 1);
		}	while(tempCard == hand[0] || tempCard == hand[1]);
		
		hand[idx] = tempCard;
		idx++;
		
		score += getScore(hand[2], score);
		cout << "Card Drew: " << findRank(hand[2]) << " of " << findSuit(hand[2]) << endl;
		cout << "Current Score: " << score << endl;
		if(score > 21)
			cout << "Busted! You Lose!\n";
			
		else
		{	int dealScore = (rand() % (26 - 11) + 11);
			cout << "Dealer Score: " << dealScore << endl;
			if(dealScore > 21)
				cout << "Dealer Busted! You Win!\n";
			else if(dealScore == 21)
				cout << "Dealer Blackjack! You Lose!\n";
			else if(dealScore > score)
				cout << "Dealer Scored Higher! You Lose!\n";
			else if(dealScore == score)
				cout << "Dealer Scored Same! Dealer Wins By Default!\n";
			else if(dealScore < score)
				cout << "Dealer Scored Lower! You Win!\n";
		}	
			
	}
	
	else if(draw == 'n')
	{	int dealScore = (rand() % (26- 11) + 11);
		cout << "Dealer Score: " << dealScore << endl;
		if(dealScore > 21)
			cout << "Dealer Busted! You Win!\n";
		else if(dealScore == 21)
			cout << "Dealer Blackjack! You Lose!\n";
		else if(dealScore > score)
			cout << "Dealer Scored Higher! You Lose!\n";
		else if(dealScore == score)
				cout << "Dealer Scored Same! Dealer Wins By Default!\n";
		else if(dealScore < score)
			cout << "Dealer Scored Lower! You Win!\n";
	}		
	
	if(blackJack(score))
		cout << "Black Jack!\n";
	
	return 0;
}

string findSuit(int card)
{	if(card / 13 < 1)
		return "Clubs";
		
	else if(card / 13 < 2)
		return "Diamonds";
	
	else if(card / 13 < 3)
		return "Hearts";
		
	else
		return "Spades";
}

string findRank(int card)
{	if(card % 13 == 0)
		return "Ace";
	
	else if((card+1) % 13 == 0)
		return "King";
		
	else if((card+2) % 13 == 0)
		return "Queen";
		
	else if((card+3) % 13 == 0)
		return "Jack";
	
	else
		if(card / 13 < 1)
			return convertInt(card+1);
		
		else if(card / 13 < 2)
			return convertInt((card-13)+1);
	
		else if(card / 13 < 3)
			return convertInt((card-26)+1);
			
		else
			return convertInt((card-39)+1);
}

int getScore(int card, int currentScore)
{	int score;
	if(card % 13 == 0)
		if(currentScore > 10)
			return 1;
		else
			return 11;
	
	else if((card+1) % 13 == 0)
		return 10;
		
	else if((card+2) % 13 == 0)
		return 10;
		
	else if((card+3) % 13 == 0)
		return 10;
	
	else
		if(card / 13 < 1)
			return card+1;
		
		else if(card / 13 < 2)
			return (card-13)+1;
	
		else if(card / 13 < 3)
			return (card-26)+1;
			
		else
			return (card-39)+1;
}

bool blackJack(int score)
{	if(score == 21)
		return true;
		
	else
		return false;
}

string convertInt(int number)
{
   stringstream ss;
   ss << number;
   return ss.str();
}
