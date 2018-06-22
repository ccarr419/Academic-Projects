package com.yahtzee.server;

import com.yahtzee.client.playerStats;
import com.yahtzee.client.GreetingService;
import com.yahtzee.shared.FieldVerifier;
import com.google.gwt.user.server.rpc.RemoteServiceServlet;

/*
* Author:       Christian Carreras
* File Name:    GreetingServiceImpl.java
* File Package: com.yahtzee.server
* File Version: 1.0
* File Date:    12/04/2017
* Due Date:     12/13/2017
* Assignment:   #5
* Professor:    Dr. Dylan Schwesinger
* Course #:     CSC421
* Course Name:  Web-Based Software Design & Development
* University:   Kutztown University
* Major:        CSCM Software Development
*/

/**
 * The server-side implementation of the RPC service.
 */
@SuppressWarnings("serial")
public class GreetingServiceImpl extends RemoteServiceServlet implements
    GreetingService {
    
    private static final long serialVersionUID = 1L; //For serialization
    private static playerStats stats = new playerStats(); //Last player to update stats
    private static boolean hasPlayerOne = false; //Game has a player one
    private static boolean hasPlayerTwo = false; //Game has a player two
    private static int playerTurn = 1; //Which player turn is it?
    
    /**
    * Checks to see if it is the calling player's turn.
    * @param player the player who is calling
    * @return true if it is the player's turn, false if not
    */
    public Boolean getUpdate(int player) {
        if(player != playerTurn) { return false; }
        else { return true; }
    }
    
    /**
    * Retrieves the stats of the other player for the calling player.
    * @return the stats of the other player
    */
    public playerStats confirmUpdate() {
        return stats;
    }
    
    /**
    * Sets the server copy of player stats to the calling player's stats.
    * @param gLog the calling player's stats
    */
    public void setStats(playerStats gLog) {
        //Switch to the other player's turn while you are at it
        if(playerTurn == 1) { playerTurn = 2; } 
        else if(playerTurn == 2) { playerTurn = 1; }
        stats = gLog;
    }
    
    /**
    * Start the game by only allowing two players at a time. Inform all players
    * who enter while there are already two players playing that they game
    * already has players.
    * @return 1 for player#1, 2 for player#2, 0 for game full
    */
    public Integer start() {
        stats = new playerStats(); //Reset game stats
        Integer result = 0; //The ID of the incoming player
        //If the game does not have a player one, assign as player one
        if (!hasPlayerOne) { 
            hasPlayerOne = true;
            result = 1;
        }
        //If the game has a player one but no player two, assign as player two
        else if(!hasPlayerTwo) {
            hasPlayerTwo = true;
            result = 2;
        }
        //Else the game is full, return zero
        return result;
    }
    
    /**
    * Restart the game and reinitialize variables. Allow other users to play.
    */
    public void quit() {
        hasPlayerOne = false;
        hasPlayerTwo = false;
        playerTurn = 1;
    }
}
