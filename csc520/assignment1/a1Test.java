/*
 * Author:          Christian Carreras
 * File Name:       a1Test.java
 * Creation Date:   01/30/2018
 * Due Date:        02/12/2018
 * Course:          CSC 520 - Advanced Object Oriented Programming
 * Professor Name:  Dr. Schwesinger
 * Assignment:      #1
 * Major:           MS Software Development
 * Institution:     Kutztown University of Pennsylvania
 * Purpose:         To implement the code-based equivalent of a UML class
 *                  diagram. The UML diagram depicts three seperate classes
 *                  that have an aggregated relationship. The three classes are
 *                  Card, Deck, and Hand. Deck and Hand are dependent on
 *                  Card but are not aware of each other. All attributes and
 *                  operations are implemented along with other hidden basics
 *                  in order to get everything hooked up and running i.e.
 *                  construction, facilitation, and inspection needs.
 *
 * JavaDoc Link:    http://csitrd.kutztown.edu/~ccarr419/csc520/assignment1/
*/

import java.util.List;
import java.util.ArrayList;
import com.csc520Code.*;

/**
* This class sole purpose is to fully test the functionality of the Card, Deck,
* and Hand classes and show all exceptions.
*/
public class a1Test {
    /**
    * Main method starting the test session.
    * @param args list of command-line arguments
    */
    public static void main(String[] args) {
        Deck deck = new Deck();
        Hand hand = new Hand();
        
        //Test toString function for Cards
        testShuffle(deck);
        //Test drawing cards from deck and adding it to hand
        testDraw(deck, hand);
        //Test sorting the hand
        testHandSort(hand);
        //Show that there are less cards in deck from drawing cards
        System.out.println("Current deck:" + deckToString(deck));
        //Test contains for Hand
        testContains(hand);
        //Test failed addCard for Hand
        testAddDupHand(hand);
        //Test removeCard for Hand and addCard for Deck
        testHand2Deck(deck, hand);
        //Show the sortHand does not fail on empty hand
        hand.sortHand();
        //Show that the deck is full again
        System.out.println("\nCurrent deck: " + deckToString(deck) + "\n");
        //Show remaining add/remove card to/from deck possibilites
        testDeckCardFunc(deck);
        //Show that Card fails to be created upon improper format
        //THE PROGRAM IS SUPPOSED TO FAIL ON PURPOSE
        //THIS IS NOT AN ERROR ON MY PART
        //THIS IS MEANT TO DEMONSTRATE EXCEPTION CATCHING
        testExcepCard();
    }
    
    /**
    * Tests the shuffle function for Deck. Shows before and after.
    * @param deck the deck to shuffle
    */
    public static void testShuffle(Deck deck) {
        System.out.println("Current deck:" + deckToString(deck));
        System.out.println("Shuffling deck...");
        deck.shuffle(); //Test shuffle() for Deck
        System.out.println("Shuffled deck:" + deckToString(deck));
    }
    
    /**
    * Tests drawing cards from the deck and adding them to the hand.
    * @param deck the deck to draw from
    * @param hand the hand to add the drawn card
    */
    public static void testDraw(Deck deck, Hand hand) {
        System.out.println("\nDrawing cards from deck to hand...");
        for(int i = 0; i < 5; i++) {
            Card card = deck.draw();
            System.out.println("You drew: " + card.toString());
            hand.addCard(card);
            System.out.println("Current hand: " + handToString(hand));
        }
    }
    
    /**
    * Tests the sortHand function for Hand. Prints the shuffled hand.
    * @param hand the hand to shuffle
    */
    public static void testHandSort(Hand hand) {
        System.out.println("\nSorting hand...");
        hand.sortHand(); //Test sorting hand
        System.out.println("Sorted hand: " + handToString(hand));
    }
    
    /**
    * Tests the contain function for Hand. Tests one case that can be true or
    * false (most likely false) and one case where it is always true.
    * @param hand the hand to check for cards
    */
    public static void testContains(Hand hand) {
        Card c = new Card(4,2);
        //Check for a specific card
        if(hand.contains(c)) {
            System.out.println("\nThe hand contains " + c.toString());
        }
        else {
            System.out.println("\nThe hand does not contain " + c.toString());
        }
        //Check for a know card in the hand -- always true for contains
        List<Card> handList = new ArrayList<Card>(hand.toList());
        c = handList.get(0);
        if(hand.contains(c)) {
            System.out.println("The hand contains " + c.toString());
        }
    }
    
    /**
    * Tests the addCard function for Hand in an always fail scenario.
    * @param hand the hand to try and add a card to
    */
    public static void testAddDupHand(Hand hand) {
        List<Card> handList = new ArrayList<Card>(hand.toList());
        Card c = handList.get(0);
        if(hand.addCard(c) == false) {
            System.out.println("Cannot add card " + c.toString() +
                ", card is already within the hand\n");
        }
    }
    
    /**
    * Tests removing all the cards from the hand and placing them in the deck.
    * @param deck the deck to add cards to
    * @param hand the hand to remove cards from
    */
    public static void testHand2Deck(Deck deck, Hand hand) {
        Card c = new Card(4,2);
        for(int i = 4; i >= 0; i--) {
            Card tmpCard = removeFirstHand(hand);
            System.out.println("Removed " + tmpCard.toString() + " from hand " +
                "and added to deck");
            System.out.println("Current hand: " + handToString(hand));
            deck.addCard(tmpCard);
        }
        //Test failed removeCard for Hand
        if(!hand.removeCard(c)) { 
            System.out.println("Cannot remove card " + c.toString() +
                ", card is not within the hand");
        }
    }
    
    /**
    * Tests fail scenarios for removeCard, addCard, and draw, as well as others
    * for Deck.
    * @param deck the deck to test exceptions for
    */
    public static void testDeckCardFunc(Deck deck) {
        Card c = new Card(4,2);
        //Test failed addCard for Deck
        if(!deck.addCard(c)) { 
            System.out.println("Cannot add card " + c.toString() +
                ", card is already within the deck");
        }
        //Test removeCard for Deck
        if(deck.removeCard(c)) { 
            System.out.println("Card " + c.toString() +
                " was removed from deck");
        }
        //Test failed draw for Deck
        System.out.println("Removing all cards from deck...");
        removeAllDeck(deck);
        if(deck.draw() == null) {
            System.out.println("Cannot draw, no cards left!");
        }
        //Test failed removeCard for Deck
        if(!deck.removeCard(c)) { 
            System.out.println("Cannot remove card " + c.toString() +
                ", card is not within the deck");
        }
        //Show empty deck
        System.out.println("Current deck: " + deckToString(deck));
        deck.shuffle(); //Show that shuffle does not fail on empty deck
    }
    
    /**
    * Tests the exception catching of the Card class when given bad parameters
    * for its constructor. This will cause the program to crash since it is
    * deliberately creating and exception.
    */
    public static void testExcepCard() {
        System.out.println("\nThis next line of code should fail...\n" +
            "I repeat, the program should now fail ON PURPOSE in order\n" +
            "to show the exception handling of the Card class.\n");
        Card fake = new Card(-1,24); //There is no rank -1 so catch exception
    }
    
    /**
    * Removes the first card from the given Hand parameter.
    * @param hand the hand to remove the first card from
    */
    public static Card removeFirstHand(Hand hand) {
        for(int i = 0; i < 4; i++ ) {
            for(int j = 0; j < 13; j++) {
                Card c = new Card(j, i);
                if(hand.contains(c)) {
                    hand.removeCard(c);
                    return c;
                }
            }
        }
        return null;
    }
    
    /**
    * Removes all cards from the given Deck parameter.
    * @param the deck to remove all the cards from
    */
    public static void removeAllDeck(Deck deck) {
        for(int i = 0; i < 4; i++ ) {
            for(int j = 0; j < 13; j++) {
                Card c = new Card(j, i);
                deck.removeCard(c);
            }
        }
    }
    
    /**
    * Turns the given Hand into a String. Formated as a list of tuples.
    * @param hand the hand to turn into a String
    */
    public static String handToString(Hand hand) {
        String outStr = "";
        List<Card> handList = new ArrayList<Card>(hand.toList());
        for(int i = 0; i < handList.size(); i++) {
            if(handList.get(i) != null) {
                outStr += ("[" + handList.get(i).getRank());
                outStr += ("," + handList.get(i).getSuit() + "], ");
            }
        }
        return outStr;
    }
    
    /**
    * Turns the given deck into a String. Formated as a list of tuples.
    * @param deck the deck to turn into a String
    */
    public static String deckToString(Deck deck) {
        String outStr = "";
        List<Card> deckList = new ArrayList<Card>(deck.toList());
        for(int i = 0; i < deckList.size(); i++) {
            if(deckList.get(i) != null) {
                if(i % 10 == 0) {
                    outStr += "\n";
                }
                outStr += ("[" + deckList.get(i).getRank());
                outStr += ("," + deckList.get(i).getSuit() + "], ");
            }
        }
        return outStr;
    }
}
