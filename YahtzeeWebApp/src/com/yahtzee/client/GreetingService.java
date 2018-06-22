package com.yahtzee.client;

import com.yahtzee.client.playerStats;
import com.google.gwt.user.client.rpc.RemoteService;
import com.google.gwt.user.client.rpc.RemoteServiceRelativePath;

/*
* Author:       Christian Carreras
* File Name:    GreetingService.java
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
 * The client-side stub for the RPC service.
 */
@RemoteServiceRelativePath("greet")
public interface GreetingService extends RemoteService {
    /**
    * Checks to see if it is the calling player's turn.
    * @param i the player who is calling
    * @return true if it is the player's turn, false if not
    */
    public Boolean getUpdate(int i);
    
    /**
    * Retrieves the stats of the other player for the calling player.
    * @return the stats of the other player
    */
    public playerStats confirmUpdate();
    
    /**
    * Sets the server copy of player stats to the calling player's stats.
    * @param ps the calling player's stats
    */
    public void setStats(playerStats ps);
    
    /**
    * Start the game by only allowing two players at a time. Inform all players
    * who enter while there are already two players playing that they game
    * already has players.
    * @return 1 for player#1, 2 for player#2, 0 for game full
    */
    public Integer start();
    
    /**
    * Restart the game and reinitialize variables. Allow other users to play.
    */
    public void quit();
}
