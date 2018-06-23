package com.yahtzee.client;

import java.io.Serializable;

/*
* Author:       Christian Carreras
* File Name:    playerStats.java
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
* Class to hold all incoming and outgoing data from the server. The only
* necessary data of use to the other player is their score and which categories
* they picked. All other data is negligible when used in network play. All data
* is serialized so they can be passed back and forth from the server.
*/
public class playerStats implements Serializable {
    private static final long serialVersionUID = 1L;
    public int scores[]; //The player's score
    public boolean pCats[]; //The categories the player picked

    public playerStats() {}
}