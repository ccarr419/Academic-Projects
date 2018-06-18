package com.csc520Code;
import java.util.List;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.Collections;
import com.csc520Code.Card;

/*
* Author:          Christian Carreras
* File Name:       Deck.java
* Creation Date:   01/30/2018
* Due Date:        02/12/2018
* Course:          CSC 520 - Advanced Object Oriented Programming
* Professor Name:  Dr. Schwesinger
* Assignment:      #1
* Major:           MS Software Development
* University:      Kutztown University of Pennsylvania
* JavaDoc Link:    http://csitrd.kutztown.edu/~ccarr419/csc520/assignment1/
*/

/**
* The deck is an object that holds Card objects. On instantiation, the deck
* will hold every possible Card object that can be created and then be
* randomly shuffled to ensure that the deck is not received in order. As far
* as implementation-wise, the deck works similarly to a queue in that cards
* are added to the end of deck and "should" be removed from the front of the
* deck. Although a card from anywhere in the deck, it was intended as well
* as advised for a card to only be removed from the front. As such, users
* cannot see the positions of certain cards within the deck because like in
* reality, one cannot see the position of a specific card within a deck.
*/
public class Deck {
    private Card[] cards; //Array to hold the deck's cards
    private int cardCount; //Number of cards in the deck
    //Number of cards allowed in the deck
    private static final int D_LIMIT = 52; //(Card.R_LIMIT * Card.S_LIMIT);
    
    /**
    * A constructor that creates every possible combination of cards and
    * inserts them into the deck Card array. The deck is then shuffled so
    * the deck will not be in order on instantiation.
    */
    public Deck() {
        cardCount = 0; //Starting off with no cards in the deck
        cards = new Card[D_LIMIT]; //Allocate the deck Card array
        //Create every card by going through each possible suit and rank
        //Numbers come from Card.S_LIMIT and Card.R_LIMIT
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 13; j++) {
                addCard(new Card(j, i));
            }
        }
        shuffle(); //Assert that the deck will not be in order
    }
    
    /**
    * Gets the deck Card array index for a given Card parameter. This function
    * is private since the user should not need to know the position of any
    * card in the deck. Intended for use in checking if the deck Card array
    * contains a specific Card.
    * @param c the Card to find the index for
    * @return the index of the Card if found, -1 if not found
    */
    private int getIndex(Card c) {
        for(int i = 0; i < cardCount; i++) {
            if(cards[i].compareTo(c) == 0) {
                return i; //Card found at index i
            }
        }
        return -1; //Card is not in the deck
    }
    
    /**
    * Attempts to add a Card to the deck. If the Card was added successfully
    * the function will return true. If the deck already contains the card the
    * function will return false. The cardCount will be incremented on a
    * successful Card addition to the deck Card array.
    * @param c the Card to try and add to the deck
    * @return true if the card was added, false if not
    */
    public boolean addCard(Card c) {
        if(getIndex(c) == -1) { //If the Card is not found in the deck, add it
            cards[cardCount] = c; //Append the Card to the end of the deck
            cardCount++; //Increment the total number of Cards in the deck
            return true; //Card was added succesfully
        }
        else { return false; } //Card exists already and was not added
    }
    
    /**
    * Attempts to remove a Card from the deck. If the Card was removed
    * successfully the function will return true. If the deck does not contain
    * the card the function will return false. The cardCount will be decremented
    * on a successful Card removal from the deck Card array.
    * @param c the Card to try and remove from the deck
    * @return true if the card was removed, false if not
    */
    public boolean removeCard(Card c) {
        int tmp = getIndex(c); //Try and get the index of the Card
        if(tmp != -1) { //If the Card was found in the deck
            //Create a list so the some functions can be called for easier Card
            //removal and the rest of the deck will adjust accordingly.
            List<Card> tmpList = new ArrayList<Card>(toList());
            tmpList.remove(tmpList.get(tmp));
            //Assign the new deck with the removed Card to the deck's Card array
            cards = tmpList.toArray(cards);
            cardCount--; //Decrement the total number of Cards in the deck
            return true; //Card was removed successfully
        }
        else { return false; } //The card does not exist in the deck
    }
    
    /**
    * Shuffles the deck by randomly shifting the Cards positions in the deck
    * Card array. Uses Collections.shuffle() to do the heavy lifting.
    */
    public void shuffle() { 
        //Turn the Cards array into a List so Collections can shuffle it
        List<Card> tmpList = new ArrayList<Card>(toList());
        Collections.shuffle(tmpList);
        cards = tmpList.toArray(cards); //Assign the newly shuffled deck
    }
    
    /**
    * Draws the top Card within the deck (i.e the Card at index zero), returns
    * it to the user, then removes it from the deck. If there are no cards
    * within the deck, null is returned instead.
    * @return the top Card in the deck
    */
    public Card draw() {
        if(cardCount == 0) { return null; } //No Cards to draw
        else {
            Card drawnCard = cards[0]; //Get the top Card
            removeCard(drawnCard); //Remove the Card from the deck
            return drawnCard; //Give the Card to the user
        }
    }
    
    /**
    * Returns the List equivalent of the deck Card array. Useful for calling
    * functions that a normal array would not be able to do.
    * @return the deck Card array in abstract List form
    */
    public List<Card> toList() {
        return Arrays.asList(cards);
    }
}