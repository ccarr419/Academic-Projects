import yahtzee.YLogic;
import yahtzee.YInterface;

/*
* Author:       Christian Carreras
* File Name:    Yahtzee.java
* File Date:    10/05/2017
* Due Date:     10/13/2017
* Assignment:   #2
* Professor:    Dr. Dylan Schwesinger
* Course #:     CSC421
* Course Name:  Web-Based Software Design & Development
* University:   Kutztown University
* Major:        CSCM Software Development
*/

/**
* The only purpose of this file is to intiate the Yahtzee game by constructing
* both the game logic and interface class objects. The game is initated by
* calling the playerPrompt method in the game interface class.
*/
public class Yahtzee {  
    public static void main(String[] args) {
        YLogic gLog = new YLogic();         //game logic class object
        YInterface gInt = new YInterface(gLog); //game interface class object
    }
}
