package com.csc520Code;

/*
* Author:          Christian Carreras
* File Name:       Card.java
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
* The card class attempts to represent a playing card. Playing cards are
* denoted by their rank and suit. Ranks include two through ten, jack, queen,
* king, and ace (in order least to highest). Suits include clubs, diamonds,
* hearts and spades. Suits each contain their own set of ranks. One suit is
* not greater or lesser than another suit and serve the only purpose of
* creating another seperate set for the ranks. Ranks and suits are represented
* as integers for simplicity, especially when comparing. The class ensures
* that only cards found in the range representing a tradional playing card
* can be created. All other options will force a run-time exception. Users
* cannot modify a card in any way, they can only inspect card information
* after the card object has been instantiated.
*/
public class Card implements Comparable<Card> {
    private int rank; //Determines greater or less than
    private int suit; //Determines set of the rank
    private static final int R_LIMIT = 13; //Number of ranks allowed
    private static final int S_LIMIT = 4; //Number of suits allowed
    
    /**
    * An enumeration of all the possible ranks for a card.
    */
    private enum Ranks {
        TWO (0),
        THREE (1),
        FOUR (2),
        FIVE (3),
        SIX (4),
        SEVEN (5),
        EIGHT (6),
        NINE (7),
        TEN (8),
        JACK (9),
        QUEEN (10),
        KING (11),
        ACE (12);
        
        private final int value;        
        Ranks(int v) { this.value = v; }       
        public int value() { return value; }
    }
    
    /**
    * An enumeration of all the possible suits for a card.
    */
    private enum Suits {
        CLUBS (0),
        DIAMONDS (1),
        HEARTS (2),
        SPADES (3);
        
        private final int value;        
        Suits(int v) { this.value = v; }       
        public int value() { return value; }
    }
    
    /**
    * An exception that is thrown when the user tries to create a card with a
    * rank outside the accepted range of ranks.
    */
    private class InvalidCardRankException extends Exception {
        /** Gives error message, prints the stack trace, then terminates. */
        public InvalidCardRankException() {
            System.err.println("Error: Invalid rank for card.");
            this.printStackTrace();
            System.exit(0);
        }
    }
    
    /**
    * An exception that is thrown when the user tries to create a card with a
    * suit outside the accepted range of suits.
    */
    private class InvalidCardSuitException extends Exception {
        /** Gives error message, prints the stack trace, then terminates. */
        public InvalidCardSuitException() {
            System.err.println("Error: Invalid suit for card.");
            this.printStackTrace();
            System.exit(0);
        }
    }
    
    /**
    * A basic constructor that creates a card object with the given rank and
    * suite. A rank and suit must be given as a blank card serves no purpose.
    * @param r the rank of the newly created card
    * @param s the suit of the newly created card
    */
    public Card(int r, int s) {
        //Call the set functions to make sure rank and suite are acceptable
        setRank(r);
        setSuit(s);
    }
    
    /**
    * Gets the rank of the card in the form of an integer.
    * @return the int value representing the card's rank
    */
    public int getRank() { 
        return rank; 
    } 
    
    /**
    * Gets the suit of the card in the form of an integer.
    * @return the int value representing the card's suit
    */
    public int getSuit() { 
        return suit; 
    }
    
    /**
    * Turns the integers reprenting the rank and suit into their mnemonic form
    * and inserts into a string to be returned.
    * @return the name of the card in a string
    */
    public String toString() {
        String outStr = "";
        //Find the card's rank and append its rank name to string
        for(Ranks r : Ranks.values()) {
            if(r.value == rank) {
                outStr += ("" + r.name() + " of ");
                break; //No need to look at the others
            }
        }
        //Find the card's suit and append its suit name to string
        for(Suits s : Suits.values()) {
            if(s.value == suit) {
                outStr += ("" + s.name());
                break; //No need to look at the others
            }
        }
        return outStr;
    }
    
    /**
    * Overloaded function from Comparable that allows cards to be sorted.
    * Cards will be sorted by suit first then by rank.
    * @param otherCard the card to compare to this card
    * @return 1 if this card is greater than, -1 if less than, and 0 if equal
    */
    public int compareTo(Card otherCard) {
        //Order by suit first
        if(suit > otherCard.getSuit()) { return 1; }
        else if(suit < otherCard.getSuit()) { return -1; }
        //Then order by rank
        else {
            if(rank > otherCard.getRank()) { return 1; }
            else if(rank < otherCard.getRank()) { return -1; }
            else { return 0; } //The cards are equal
        }
    }
    
    /**
    * Sets the rank of the card but first checks if the rank is within the
    * acceptable range of ranks. Throws an exception if necessary.
    * @param r the rank to set the card to
    */
    private void setRank(int r) {
        try { //Make sure a negative/out-of-range rank is not given
            if(r >= R_LIMIT || r < 0) {
                throw new InvalidCardRankException();
            }
            else {
                rank = r;
            }
        } //If a bad rank was given, throw a run-time exception
        catch(InvalidCardRankException e) { }     
    }
    
    /**
    * Sets the suit of the card but first checks if the suit is within the
    * acceptable range of suits. Throws an exception if necessary.
    * @param s the suit to set the card to
    */
    private void setSuit(int s) { 
        try { //Make sure a negative/out-of-range suit is not given
            if(s >= S_LIMIT || s < 0) {
                throw new InvalidCardSuitException();
            }
            else {
                suit = s;
            }
        } //If a bad suit was given, throw a run-time exception
        catch(InvalidCardSuitException e) { } 
    }
}