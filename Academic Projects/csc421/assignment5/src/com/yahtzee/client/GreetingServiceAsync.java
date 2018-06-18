package com.yahtzee.client;

import com.yahtzee.client.playerStats;
import com.google.gwt.user.client.rpc.AsyncCallback;

/*
* Author:       Christian Carreras
* File Name:    GreetingServiceAsync.java
* File Package: com.yahtzee.client
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
 * The async counterpart of <code>GreetingService</code>.
 */
public interface GreetingServiceAsync {
    /**
    * Checks to see if it is the calling player's turn.
    * @param i the player who is calling
    * @param callback async callback
    */
    void getUpdate(int i, AsyncCallback<Boolean> callback);
    
    /**
    * Retrieves the stats of the other player for the calling player.
    * @param callback async callback
    */
    void confirmUpdate(AsyncCallback<playerStats> callback);
    
    /**
    * Sets the server copy of player stats to the calling player's stats.
    * @param ps the calling player's stats
    * @param callback async callback
    */
    void setStats(playerStats ps, AsyncCallback<Void> callback);
    
    /**
    * Start the game by only allowing two players at a time. Inform all players
    * who enter while there are already two players playing that they game
    * already has players.
    * @param callback async callback
    */
    void start(AsyncCallback<Integer> callback);
    
    /**
    * Restart the game and reinitialize variables. Allow other users to play.
    * @param callback async callback
    */
    void quit(AsyncCallback<Void> callback);
}
