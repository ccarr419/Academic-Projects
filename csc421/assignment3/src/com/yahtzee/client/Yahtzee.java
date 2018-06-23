package com.yahtzee.client;

import com.yahtzee.client.YLogic;
import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.core.client.GWT;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.RootPanel;
import com.google.gwt.dom.client.Document;
import com.google.gwt.dom.client.Element;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.ui.Grid;
import com.google.gwt.user.client.ui.ToggleButton;
import com.google.gwt.user.client.ui.HTML;

/*
* Author:       Christian Carreras
* File Name:    Yahtzee.java
* File Package: com.yahtzee.client
* File Version: 1.0
* File Date:    10/05/2017
* Due Date:     11/03/2017
* Assignment:   #3
* Professor:    Dr. Dylan Schwesinger
* Course #:     CSC421
* Course Name:  Web-Based Software Design & Development
* University:   Kutztown University
* Major:        CSCM Software Development
*/

/**
 * The Yahtzee class represents a game of Yahtzee in the form of a GUI.
 * This is made possible by the use of the GWT. GWT makes it possible for
 * java code to be run on the web by turning the java byte code into javascript.
 * This makes is very to easy to transfer a logic-heavy game of Yahtzee
 * into a GUI for anyone to play. The logic for the game of Yahtzee was
 * taken from a previous version of the project and adapted for use in a GUI.
 * Fortunately not much modification was needed as GWT does much of the heavy
 * lifting. Most if not all of the user/game interaction is handled by a
 * handful of buttons and widgets that hold said buttons.
 */
public class Yahtzee implements EntryPoint {
    Grid gameGrid; //Dice container
    YLogic gLog; //Yahtzee game logic

    /**
    * This function instantiates the GWT module by creating widgets required
    * for the game to work and placing them inside webpage. Thus creating
    * the GUI representing a game of Yahtzee.
    */
    public void onModuleLoad() {
        gLog = new YLogic();
        gameGrid = new Grid(1, gLog.dice.NUM_DICE);
        //Create a button for each die and place it in the game grid
        for(int col = 0; col < gLog.dice.NUM_DICE; col++) {
            final int i = col;
            ToggleButton b = createDiceButton(i);
            gameGrid.setWidget(0, col, b);
        }
        //Create a button to roll the dice
        Button rollB = createRollButton(gameGrid);
        //Create a button to take the player to the readme so they can learn
        //how to play the game or pick up any other useful information
        Button helpB = new Button("How To Play", new ClickHandler() {
            public void onClick(ClickEvent event) {
                Window.open(
                "http://csitrd.kutztown.edu/~ccarr419/csc421/assignment3/README.txt",
                "_blank", "");
            }
        });
        //Place all the widgets in the RootPanel a.k.a. the webpage
        rollB.setWidth("150px");
        helpB.setWidth("150px");
        RootPanel.get("GameContainer").add(gameGrid);
        RootPanel.get("RollContainer").add(rollB);
        RootPanel.get("HelpContainer").add(helpB);
        RootPanel.get("CategoryContainer").add(createCatGrid());
    }
    
    /**
    * Creates a grid containg every category in the game and their current
    * scores. Scores depend on the current dice configuration. Categories
    * can be picked with a button in the same row. Categories that were picked
    * will be crossed out and have their buttons disabled.
    * @return The grid containing the categories, scores and buttons
    */
    public Grid createCatGrid() {
        Grid categoryGrid = new Grid(gLog.ROUND_LIMIT, 3);
        int[] scores = gLog.findDiceScores();
        int i = 0;
        //Create a row for every category
        for(final YLogic.Categories cat : gLog.c.values()) {
            final int idx = i;
            final int score = scores[i];
            //Replace the underscores in the name with spaces
            final String str = cat.toString().replaceAll("_", " ");
            //Create a button that picks that category
            Button b = new Button("Pick Category", new ClickHandler() {
                public void onClick(ClickEvent event) {
                    //Make sure that this is what the user wants to do
                    if(!Window.confirm("Pick " + str + " and score " + score + "?")) {
                        return;
                    }
                    //Make sure that the category is picked and cannot be
                    //picked again
                    gLog.setCatPicked(idx, true);
                    gLog.setCatScore(idx, score);
                    Element e = Document.get().getElementById("CatContainer" + idx);
                    e.setInnerText("" + score);
                    resetRound(); //End the round and proceed to the next
                }
            });
            //If this category was picked already cross it out
            if(gLog.getCatPicked(idx)) { 
                b.setEnabled(false);
                HTML h = new HTML("<strong><del>" + str + "</del></strong>");
                categoryGrid.setWidget(idx, 0, h);
                categoryGrid.setText(idx, 1, "x");
            }
            else { //Otherwise display it as normal
                HTML h = new HTML("<strong>" + str + "</strong>");
                categoryGrid.setWidget(idx, 0, h);
                categoryGrid.setText(idx, 1, "" + score);
            }
            //Format each cell to a css class rule
            categoryGrid.getCellFormatter().setStyleName(idx, 0, "gridCell");
            categoryGrid.getCellFormatter().setStyleName(idx, 1, "gridCell");
            categoryGrid.getCellFormatter().setStyleName(idx, 2, "gridCell");
            
            //Alternate the background color for readability
            if(idx % 2 != 0) { 
                categoryGrid.getRowFormatter().setStyleName(idx, "altRow");
            }
            else { 
                categoryGrid.getRowFormatter().setStyleName(idx, "gridRow");
            }
            //Format everything else
            categoryGrid.setStyleName("gridStyle");
            b.setStyleName("gridButton");
            categoryGrid.setWidget(idx, 2, b);
            i++;
        }
        return categoryGrid;
    }
    
    /**
    * Removes the old category grid and replaces it with a new updated grid.
    * Updated scores and crosses out picked categories.
    */
    public void resetCatGrid() {
        RootPanel cc = RootPanel.get("CategoryContainer");
        cc.remove(cc.getWidget(0));
        cc.add(createCatGrid());
    }
    
    /**
    * Creates the button to roll the dice. Once pressed, the button will ask
    * the player if they wish to continue with the roll if they did not pick
    * dice to keep. If the player has picked dice to keep or they bypassed the
    * warning all non-kept dice are rolled and replaced with new dice. The roll
    * button may only be used if the player has not used up all of their rolls for
    * the round and the game is not over. Otherwise the button will be disabled.
    * @param g The grid containing the game's dice
    * @return The roll button created
    */
    public Button createRollButton(final Grid g) {
        Button rollB = new Button("Roll", new ClickHandler() {
            public void onClick(ClickEvent event) {
                //Make sure the user wants to roll if they did not pick any
                //dice to keep
                if(!gLog.getPlayerKept()) {
                    if(!Window.confirm("You did not pick dice to keep. Roll anyway?")) {
                        return;
                    }
                }
                gLog.playerRoll();
                Button tmp = (Button) event.getSource();
                //Roll the dice and replace all non-kept dice
                for(int col = 0; col < gLog.dice.NUM_DICE; col++) {
                    ToggleButton gB = (ToggleButton) g.getWidget(0, col);
                    gB.setText("" + gLog.dice.getDie(col));
                }
                //Update category scores, round and roll information
                resetCatGrid();
                updateRoundAndRoll(tmp);
            }
        });
        return rollB;
    }
    
    /**
    * Creates a button that represents a die. The button will contain a
    * number that is its die-face number. If the player clicks the die it
    * will act as the player keeping the die. The player can click the die
    * again to not keep the die; essentially acting as a toggle between keeping
    * and not keeping the die.
    * @param num The die to retrieve
    * @return The dice button created
    */
    public ToggleButton createDiceButton(final int num) {
        ToggleButton b = new ToggleButton(("" + gLog.dice.getDie(num)), 
            new ClickHandler() {
            public void onClick(ClickEvent event) {
                ToggleButton tmp = (ToggleButton) event.getSource();
                if(tmp.isDown()) { //While the button is down, keep the die
                    gLog.dice.setKeptDie(num, true);
                    gLog.setPlayerKept(true);
                } //Otherwise do not keep the die
                else { gLog.dice.setKeptDie(num, false); }
            }
        }); b.setPixelSize(50, 50);
        return b;
    }
    
    /**
    * Updates the scores in the player scoresheet. Totals will be calculated
    * and added. Bonus applicability will be judged and calculated. Also the 
    * yahtzee bonus checkmarks will be added if also applicable.
    */
    public void updateScores() {
        //Make an array of totals for easy insertion into the scoresheet
        final int[] totals = 
            { gLog.upperTotal(), gLog.upperTotal() + gLog.upperBonus(),
                gLog.upperTotal() + gLog.upperBonus(),
                gLog.lowerTotal() + gLog.lowerBonus(), gLog.grandTotal()
            };
        //Make an array of bonuses for easy insertion into the scoresheet
        final int[] bonuses = { gLog.upperBonus(), gLog.lowerBonus() };
        for(int i = 0; i < totals.length; i++) { //Insert every total
            final int idx = i;
            Element e = Document.get().getElementById("TotalContainer" + idx);
            e.setInnerHTML("<strong>" + totals[idx] + "</strong>");
        }
        for(int i = 0; i < bonuses.length; i++) { //Insert every bonus
            final int idx = i;
            Element e = Document.get().getElementById("BonusContainer" + idx);
            e.setInnerHTML("<strong>" + bonuses[idx] + "</strong>");
        }
        String yStr = ""; 
        //Create the string of checkmarks for every Yahtzee bonus
        for(int i = 0; i < gLog.getYahtzeeCount()-1; i++) {
            yStr += "&#10003;";
        } //Then add that string to the checksheet
        Element e = Document.get().getElementById("YahtzeeCountContainer");
        e.setInnerHTML("<strong>" + yStr + "</strong>");
    }
    
    /**
    * Updates the round and roll numbers. If the player has used all of their
    * rolls, the roll button will be deactivated. If the player has ran out
    * of rounds the roll button will be deactivated.
    * @param b The roll button
    */
    public void updateRoundAndRoll(Button b) {
        //Get the element that contains the roll and round numbers
        Element e1 = Document.get().getElementById("RoundNumContainer");
        Element e2 = Document.get().getElementById("RollNumContainer");
        //Player exceeded round limit? Game is over.
        if(gLog.getRoundNum() > gLog.ROUND_LIMIT) {
            e1.setInnerText("Game");
            e2.setInnerText("Over");
            b.setEnabled(false); //Disable roll button
        }
        else { //Otherwise game is still in progress
            e1.setInnerText("Round #" + gLog.getRoundNum());
            e2.setInnerText("Roll #" + gLog.getRollNum());
            //If the player ran out of rolls, disable the roll button
            if(gLog.getRollNum() >= gLog.ROLL_LIMIT) { b.setEnabled(false); }
            else { b.setEnabled(true); }
        }
    }
    
    /**
    * Resets the round by progressing the game to the next round. This function
    * should be called immediately at the end of a round. This function will 
    * end the round and bring the game to the beginning the next round. Thus 
    * updating scores, dice, and available categories accordingly.
    */
    public void resetRound() {
        //Increment the Yahtzee count if the dice is a Yahtzee and the
        //Yahtzee category was filled with a non-zero score.
        if(gLog.dice.isYahtzee() 
            && gLog.getCatPicked(gLog.c.YAHTZEE.value())) {
            gLog.incYahtzeeCount();
        }
        //End the round and fill in the score for this round
        gLog.endRound();
        updateScores();
        //Reset the roll button and roll the dice for the new round
        Button b = (Button) RootPanel.get("RollContainer").getWidget(0);
        Grid g = (Grid) RootPanel.get("GameContainer").getWidget(0);
        for(int col = 0; col < gLog.dice.NUM_DICE; col++) {
            ToggleButton tB = createDiceButton(col);
            g.setWidget(0, col, tB);
        }
        //Update scores, round and roll numbers for new round
        resetCatGrid();
        updateRoundAndRoll(b);
    }
}
