package com.csc520Code;
import java.util.List;
import java.util.Arrays;
import java.util.ArrayList;
import com.csc520Code.Card;

/*
* Author:          Christian Carreras
* File Name:       Hand.java
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
* The hand object behaves similarly to the deck object with the exception that
* that there should be more transparency since users will be interacting
* with hands directly. Hands can be sorted at whim by the user if they feel
* so inclined. The hand can also be searched by the user for a certain Card.
* Hands are initialized as empty and must have Cards added to it.
*/
public class Hand {
    private Card[] cards; //Array to hold the hand's Cards
    private int cardCount; //Number of Cards in the hand
    private static final int H_LIMIT = 5; //Number of Cards allowed in the hand
    
    /**
    * A basic constructor to initialize the hand's Card array as empty.
    */
    public Hand() {
        cards = new Card[H_LIMIT];
    }
    
    /**
    * Gets the hand Card array index for a given Card parameter. This function
    * is private since the user should not need to know the position of any
    * card in the hand. Intended for use in checking if the hand Card array
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
        return -1; //Card is not in the hand
    }
    
    /**
    * Attempts to add a Card to the hand. If the Card was added successfully
    * the function will return true. If the hand already contains the card the
    * function will return false. The cardCount will be incremented on a
    * successful Card addition to the hand Card array.
    * @param c the Card to try and add to the hand
    * @return true if the card was added, false if not
    */
    public boolean addCard(Card c) { 
        if(getIndex(c) == -1) { //If the Card is not found in the hand, add it
            cards[cardCount] = c; //Append the Card to the end of the hand
            cardCount++; //Increment the total number of Cards in the hand
            return true; //Card was added succesfully
        }
        else { return false; } //Card exists already and was not added
    }
    
    /**
    * Attempts to remove a Card from the hand. If the Card was removed
    * successfully the function will return true. If the hand does not contain
    * the card the function will return false. The cardCount will be decremented
    * on a successful Card removal from the hand Card array.
    * @param c the Card to try and remove from the hand
    * @return true if the card was removed, false if not
    */
    public boolean removeCard(Card c) { 
        int tmp = getIndex(c); //Try and get the index of the Card
        if(tmp != -1) { //If the Card was found in the hand
            //Create a list so the some functions can be called for easier Card
            //removal and the rest of the hand will adjust accordingly.
            List<Card> tmpList = new ArrayList<Card>(toList());
            tmpList.remove(tmpList.get(tmp));
            //Assign the new hand with the removed Card to the hand's Card array
            cards = tmpList.toArray(cards);
            cardCount--; //Decrement the total number of Cards in the hand
            return true; //Card was removed successfully
        }
        else { return false; } //The card does not exist in the hand
    }
    
    /**
    * A user version of getIndex() that returns a boolean instead of a integer.
    * @param c the Card to check for in the hand
    * @return true if the Card is in the hand, false if not
    */
    public boolean contains(Card c) { 
        if(getIndex(c) != -1) { return true; }
        else { return false; }
    }
    
    /**
    * Sorts the hand by the natural-order of the Card object. Thus the hand
    * will be sorted by suit first, then rank. Array.sort() does all the work.
    * If the deck is less than or equal to one, the hand will not be sorted.
    */
    public void sortHand() {
        if(cardCount <= 1) { return; }
        else { Arrays.sort(cards); }
    }
    
    /**
    * Returns the List equivalent of the hand Card array. Useful for calling
    * functions that a normal array would not be able to do.
    * @return the hand Card array in abstract List form
    */
    public List<Card> toList() { 
        return Arrays.asList(cards); 
    }
}
