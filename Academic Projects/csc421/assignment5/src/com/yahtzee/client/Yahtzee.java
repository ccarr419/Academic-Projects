package com.yahtzee.client;

import java.util.Random;
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
import com.google.gwt.user.client.ui.HTML;
import com.google.gwt.user.client.ui.Image;
import com.google.gwt.media.client.Audio;
import com.google.gwt.user.client.ui.TabPanel;
import com.google.gwt.user.client.ui.ToggleButton;
import com.google.gwt.user.client.ui.DialogBox;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.ui.VerticalPanel;

/*
* Author:       Christian Carreras
* File Name:    Yahtzee.java
* File Package: com.yahtzee.client
* File Version: 3.0
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
 * The Yahtzee class represents a game of Yahtzee in the form of a GUI.
 * This is made possible by the use of the GWT. GWT makes it possible for
 * java code to be run on the web by turning the java byte code into javascript.
 * This makes is very to easy to transfer a logic-heavy game of Yahtzee
 * into a GUI for anyone to play. The logic for the game of Yahtzee was
 * taken from a previous version of the project and adapted for use in a GUI.
 * Fortunately not much modification was needed as GWT does much of the heavy
 * lifting. Most if not all of the user/game interaction is handled by a
 * handful of buttons and widgets that hold said buttons. This version
 * improves upon the previous by adding multimedia images and sounds as well
 * as adding two-player network/server support.
 */
public class Yahtzee implements EntryPoint {
    Grid gameGrid; //Dice container
    YLogic gLog; //Yahtzee game logic (current player's turn)
    YLogic playerOne; //Player 1 game instance
    YLogic playerTwo; //Player 2 game instance
    int players; //Number of players
    int currentPlayer; //Player ID
    boolean turn; //Determines which player turn it is
    final yServlet gServ = new yServlet(); //Async servet - access the server
    final DialogBox waitTurnBox = new DialogBox(); //Make players wait for their turn
    //Check to see if it is the player's turn
    final Button refreshButton = new Button("Check If It Is Your Turn", new ClickHandler() {
        public void onClick(ClickEvent event) {
            gServ.checkForUpdates(); // Check if it is your turn
        }
    });
    //Mute or unmute the sound in the game
    final ToggleButton soundB = new ToggleButton(
        new Image("yahtzee/images/soundOn.png"),
        new Image("yahtzee/images/soundOff.png")
    );
    
    //Access to the server
    private final GreetingServiceAsync greetingService = GWT.create(GreetingService.class);
    
    /**
    * The servlet handles all information going to and coming from the server.
    * All functions are asynchronous as not to interrupt the flow of the page
    * or game. Will handle all major transitions between players in the game.
    */
    public class yServlet {
        playerStats p = new playerStats(); //Incoming/Outgoing player stats
        
        /**
        * Checks the if the other player has completed their turn and uploaded
        * their stats to the server. If so, request those stats. If not, inform
        * the player that the other player's turn is still in progress.
        */
        public void checkForUpdates() {
            greetingService.getUpdate(currentPlayer, new AsyncCallback<Boolean>() {
                //If the call to the server fails
                public void onFailure(Throwable caught) {
                    Window.alert("Unable to obtain server response: " +
                    caught.getMessage());
                }
                public void onSuccess(Boolean result) {
                    if(result) { //If it is the player's turn
                        waitTurnBox.hide(); //Remove the waiting box and dim screen
                        RootPanel.get("appFront").getElement().setAttribute("hidden", "");
                        getUpdates(); //Fetch the stats from the other player
                    }
                    else { //If it is not the player's turn
                        Window.alert("It is still not your turn");
                    }
                }
            });
        }
        
        /**
        * Retrieves the stats sent across the server by the other player. It
        * will then take those stats and fill in that player's checksheet.
        * Afterwards a transition will be made to this player's turn.
        */
        private void getUpdates() {
            greetingService.confirmUpdate(new AsyncCallback<playerStats>() {
                public void onFailure(Throwable caught) {
                    Window.alert("Unable to obtain server response: " +
                    caught.getMessage());
                }
                public void onSuccess(playerStats result) {
                    //Store the stats in the other player's game object
                    playerTwo.setCatPicked(result.pCats);
                    playerTwo.setScore(result.scores);
                    //Enter the scores from the other player into their scoresheet
                    for(int i = 0; i < YLogic.ROUND_LIMIT; i++) {
                        Element e = Document.get().getElementById("CatContainer" + scrStr() + i);
                        if(result.pCats[i]) {
                            e.setInnerText("" + result.scores[i]); //Set the new score
                        }
                    }
                    //End the game if both players are done
                    if(gLog.getRoundNum() > gLog.ROUND_LIMIT) {
                        endGame();
                    }
                    //Otherwise go to your next turn
                    else {
                        Element e = Document.get().getElementById("CurrentPlayer");
                        e.setInnerText("Your Turn");
                        e.setAttribute("class", "gamePlayer");
                        gLog = playerTwo;
                        updateScores(); //Update the other players totals
                        turn = true; //Set it to your turn
                        gLog = playerOne;
                    }
                }
            });
        }
        
        /**
        * Send the player's stats to the server for the other player to acquire.
        */
        private void setUpdate() {
            p.scores = gLog.getScore(); //Put the player's score in the serialized object
            p.pCats = gLog.getCatPicked(); //Put the categories picked in the object too
            greetingService.setStats(p, new AsyncCallback<Void>() {
                public void onFailure(Throwable caught) {
                    Window.alert("Unable to obtain server response: " +
                    caught.getMessage());
                }
                //No need to do anything since you will know if it does not work
                public void onSuccess(Void v) {} 
            });
        }
        
        /**
        * Attempt to connect to the server and play a game with another player.
        * If the player is the first to contact the server for a game, they
        * will be player one. If they are the second, they will be player two.
        * Otherwise the game is full already and the player will default to a
        * one player version of the game.
        */
        public void start() {
            greetingService.start(new AsyncCallback<Integer>() {
                public void onFailure(Throwable caught) {
                    Window.alert("Unable to obtain server response: " +
                    caught.getMessage());
                }
                public void onSuccess(Integer result) {
                    if (result == 1 || result == 2) {
                        currentPlayer = result;
                        //Let the player know which player they are
                        Window.alert("You are Player #" + result);
                        Element e = Document.get().getElementById("CurrentPlayer");
                        //Player one will always go first
                        if(result == 1) {
                            turn = true;
                            e.setInnerText("Your Turn");
                            e.setAttribute("class", "gamePlayer");
                        }
                        //Player two will always go next
                        else if(result == 2) {
                            turn = false;
                            //Display waiting box until it is the player's turn
                            waitTurnBox.center();
                            refreshButton.setFocus(true);
                            RootPanel.get("appFront").getElement().removeAttribute("hidden");
                            e.setInnerText("Other Player's Turn");
                            e.setAttribute("class", "gamePlayerOpp");
                        }
                    }
                    //Otherwise the game is full already, default to one player game
                    else {
                        Window.alert("There are already two players. Try again later.");
                        players = 1;
                    }
                }
            });
        }
        
        /**
        * Quit the game to refresh the server and allow others to play.
        */
        public void quitGame() {
            greetingService.quit(new AsyncCallback<Void>() {
                public void onFailure(Throwable caught) {
                    Window.alert("Unable to obtain server response: " +
                    caught.getMessage());
                }
                public void onSuccess(Void v) {}
            });
        }
    }
    
    /**
    * This function instantiates the GWT module by creating widgets required
    * for the game to work and placing them inside webpage. Thus creating
    * the GUI representing a game of Yahtzee.
    */
    public void onModuleLoad() {
        //Make a dialog box to stop the player from doing anything when it is
        //not their turn to play. Will only close when it is the player's turn.
        VerticalPanel dialogVPanel = new VerticalPanel();
        dialogVPanel.add(refreshButton);
        waitTurnBox.setWidget(dialogVPanel);
        waitTurnBox.setText("Please Wait Your Turn");     
    
        playerOne = new YLogic();
        //Check if there is going to be more than one player
        if(Window.confirm("Want to play a 2 player game?")) { 
            playerTwo = new YLogic(); //Create second player instance
            players = 2;
            gServ.start(); //Start network play and look for another player
        }
        else { //User selected one player
            players = 1; 
        }
        gLog = playerOne; //start of the game with player one
        
        //Create a tab panel that holds each player's scoresheet
        TabPanel tp = new TabPanel();
        Element ss = Document.get().getElementById("Scoresheet");
        tp.add(new HTML(ss.getInnerHTML()), "Your Score");
        if(players > 1) {
            newPlayerScoresheet(tp, ss);
        }
        tp.selectTab(0); //Open up the first scoresheet tab
        ss.setInnerHTML(""); //Get rid of template code

        gameGrid = new Grid(1, gLog.dice.NUM_DICE);
        //Create an Image for each die and place it in the game grid
        for(int col = 0; col < gLog.dice.NUM_DICE; col++) {
            final int i = col;
            Image b = createDiceButton(i);
            gameGrid.setWidget(0, col, b);
        }
        //Create a button to roll the dice
        Button rollB = createRollButton(gameGrid);
        //Create a button to take the player to the readme so they can learn
        //how to play the game or pick up any other useful information
        Button helpB = new Button("How To Play", new ClickHandler() {
            public void onClick(ClickEvent event) {
                Window.open(
                "http://csitrd.kutztown.edu/~ccarr419/csc421/assignment5/README.txt",
                "_blank", "");
            }
        });
        //Place all the widgets in the RootPanel a.k.a. the webpage
        rollB.setWidth("150px");
        helpB.setWidth("150px");
        soundB.setPixelSize(24,24);
        RootPanel.get("GameContainer").add(gameGrid);
        RootPanel.get("RollContainer").add(rollB);
        RootPanel.get("HelpContainer").add(helpB);
        RootPanel.get("CategoryContainer").add(createCatGrid());
        RootPanel.get("ScoreContainer").add(tp);
        RootPanel.get("MuteContainer").add(soundB);
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
                    //Make sure that the category is picked and cannot be picked again
                    gLog.setCatPicked(idx, true);
                    gLog.setCatScore(idx, score);
                    //Get the right score container from the right player's scoresheet
                    Element e = Document.get().getElementById("CatContainer" + scrStr() + idx);
                    e.setInnerText("" + score); //Set the new score
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
    * This will play a dice rolling sound everytime a player rolls.
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
                //Play one of three sounds to represent rolling the dice
                Audio dr = Audio.createIfSupported();
                if(dr != null && !soundB.isDown()) { 
                    //Randomly select one audio file from a set of three
                    Random ran = new Random();
                    int num = ran.nextInt(3) + 1;
                    dr.setSrc("yahtzee/sounds/diceThrow0" + num + ".wav");
                    dr.play();
                }
                gLog.playerRoll();
                Button tmp = (Button) event.getSource();
                //Roll the dice and replace all non-kept dice
                for(int col = 0; col < gLog.dice.NUM_DICE; col++) {
                    Image gB = (Image) g.getWidget(0, col);
                    if(gLog.dice.getKeptDie(col) == true) {
                        //Make sure the dice still looks picked if it is picked
                        gB.setUrl("yahtzee/images/dice" + gLog.dice.getDie(col) + "Picked.jpg");
                    }
                    else {
                        //Make sure the dice still looks unpicked
                        gB.setUrl("yahtzee/images/dice" + gLog.dice.getDie(col) + ".jpg");
                    }
                    gB.setAltText("" + gLog.dice.getDie(col));
                }
                //Update category scores, round and roll information
                resetCatGrid();
                updateRoundAndRoll(tmp);
            }
        });
        return rollB;
    }
    
    /**
    * Creates an Image that represents a die. The Image will represent a die
    * face number and have a click-handler similar to a button. If the player 
    * clicks the die it will act as the player keeping the die. The player can
    * click the die again to not keep the die; essentially acting as a toggle
    * between keeping and not keeping the die.
    * @param num The die to retrieve
    * @return The dice Image created
    */
    public Image createDiceButton(final int num) {
        Image i = new Image("yahtzee/images/dice" + gLog.dice.getDie(num) + ".jpg");
        i.setAltText("" + gLog.dice.getDie(num));
        i.addClickHandler(new ClickHandler() {
            public void onClick(ClickEvent event) {
                Image tmp = (Image) event.getSource();
                if(gLog.dice.getKeptDie(num) == false) { //While the button is down, keep the die
                    gLog.dice.setKeptDie(num, true);
                    gLog.setPlayerKept(true);
                    //Change the image to the picked dice image
                    tmp.setUrl("yahtzee/images/dice" + gLog.dice.getDie(num) + "Picked.jpg");
                } //Otherwise do not keep the die
                else { 
                    //Place the button up, change to the normal dice image
                    gLog.dice.setKeptDie(num, false); 
                    tmp.setUrl("yahtzee/images/dice" + gLog.dice.getDie(num) + ".jpg");
                }
            }
        }); i.setPixelSize(50, 50);
        return i;
    }
    
    /**
    * Updates the scores in a player's scoresheet. Totals will be calculated
    * and added. Bonus applicability will be judged and calculated. Also the 
    * yahtzee bonus checkmarks will be added if also applicable. A player's
    * should be updated after their turn.
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
            Element e = Document.get().getElementById("TotalContainer" + scrStr() + idx);
            e.setInnerHTML("<strong>" + totals[idx] + "</strong>");
        }
        for(int i = 0; i < bonuses.length; i++) { //Insert every bonus
            final int idx = i;
            Element e = Document.get().getElementById("BonusContainer" + scrStr() + idx);
            e.setInnerHTML("<strong>" + bonuses[idx] + "</strong>");
        }
        String yStr = ""; 
        //Create the string of checkmarks for every Yahtzee bonus
        for(int i = 0; i < gLog.getYahtzeeCount()-1; i++) {
            yStr += "&#10003;";
        } //Then add that string to the checksheet
        Element e = Document.get().getElementById("YahtzeeCountContainer" + scrStr());
        e.setInnerHTML("<strong>" + yStr + "</strong>");
    }
    
    /**
    * Updates the round and roll numbers. If a player has used all of their
    * rolls, the roll button will be deactivated. If the players have run out
    * of rounds the roll button will be deactivated. If there is more than
    * one player, a winner will be announced at the end of the game.
    * @param b The roll button
    */
    public void updateRoundAndRoll(Button b) {
        //Get the element that contains the roll and round numbers
        Element e1 = Document.get().getElementById("RoundNumContainer");
        Element e2 = Document.get().getElementById("RollNumContainer");
        Element e3 = Document.get().getElementById("CurrentPlayer");
        //Player exceeded round limit? Game is over.
        if(gLog.getRoundNum() > gLog.ROUND_LIMIT) {
            e1.setInnerText("Game");
            e2.setInnerText("Over");
            
            //Make sure both players have picked every category before ending the game
            boolean allCatPicked = true;
            for(int i = 0; i < YLogic.ROUND_LIMIT; i++) {
                //If one category is not picked no need to keep looking
                if(playerOne.getCatPicked(i) != true ||
                    playerTwo.getCatPicked(i) != true) {
                        allCatPicked = false;
                        break;
                }
            }
            //Check if there is more than one player and they are both finished
            //so a winner, loser, or tie game can be announced
            if(players > 1 && allCatPicked) {
                endGame();
            }
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
    * Ends the turn of one player and goes to the next player's turn. If the
    * round is over for both players the game will progress to the beginning of
    * the next round. Thus updating scores, dice, and available categories.
    */
    public void resetRound() {
        //Increment the Yahtzee count if the dice is a Yahtzee and the
        //Yahtzee category was filled with a non-zero score.
        if(gLog.dice.isYahtzee() 
            && gLog.getCatPicked(gLog.c.YAHTZEE.value())) {
            gLog.incYahtzeeCount();
        }
        //Play a sound to represent a category being picked
        Audio pc = Audio.createIfSupported();
        if(pc != null && !soundB.isDown()) { 
            pc.setSrc("yahtzee/sounds/pickCategory.wav");
            pc.play();
        }
        //End the round and fill in the score for this round
        gLog.endRound();
        updateScores();
        //Check for more than one player
        //If there is more than one player, switch to the other player
        if(players > 1) {
            Element e = Document.get().getElementById("CurrentPlayer");
            RootPanel ss = RootPanel.get("ScoreContainer");
            TabPanel tp = (TabPanel) ss.getWidget(0);
            
            playerOne = gLog; //Save the round info in player one's instance
            turn = false;
            waitTurnBox.center(); //Show the waiting dialog box
            refreshButton.setFocus(true);
            //Block the player from doing anything until it is there turn
            RootPanel.get("appFront").getElement().removeAttribute("hidden");
            e.setAttribute("class", "gamePlayerOpp");
            e.setInnerText("Other Player's Turn"); //Show its their opponnents turn
            gServ.setUpdate(); //Send the player's stats to the server
        }
        //Reset the roll button and roll the dice for the new round
        Button b = (Button) RootPanel.get("RollContainer").getWidget(0);
        Grid g = (Grid) RootPanel.get("GameContainer").getWidget(0);
        for(int col = 0; col < gLog.dice.NUM_DICE; col++) {
            Image tB = createDiceButton(col);
            g.setWidget(0, col, tB);
        }
        //Update scores, round and roll numbers for new round
        resetCatGrid();
        updateRoundAndRoll(b);
    }
    
    /**
    * Ends the game by displaying a winner, loser, or tie game. Also tells the 
    * server to refresh and allow other players to play. On the client side it
    * removes all dialog boxes from the screen so the player's can look at the 
    * scoresheets. Only should be called at the end of a two player game.
    */
    public void endGame() {
        Element e = Document.get().getElementById("CurrentPlayer");
        //The player had a higher score than the other player
        if(playerOne.grandTotal() > playerTwo.grandTotal()) {
            e.setInnerText("Congratulations, You Won!");
        }
        //The other player had a higher score than the player
        else if(playerOne.grandTotal() < playerTwo.grandTotal()) {
            e.setInnerText("You Lost, Better Luck Next Time!");
        }
        else { //Scores match so tie game
            e.setInnerText("You Both Tied, Good Game!");
        }
        gServ.quitGame(); //Let other users play together
        waitTurnBox.hide(); //Remove all the clutter so player's can see scores
        RootPanel.get("appFront").getElement().setAttribute("hidden", "");
    }
    
    /**
    * Creates new scoresheet table to be inserted into the page. The scoresheet
    * will be an exact duplicate of the given scoresheet except all unique
    * tags will be given a new identifier.
    * @param tp The TabPanel to insert the new scoresheet into
    * @param e The scoresheet to copy
    */
    private void newPlayerScoresheet(TabPanel tp, Element e) {
        String h = e.getInnerHTML();
        h = h.replace("_", "__");
        tp.add(new HTML(h), "Other's Score");
    }
    
    /**
    * Returns a string to get the unique identifier of a tag in a player's
    * scoresheet depending on which player's turn it is.
    * @return The string to add to get the unique id
    */
    private String scrStr() {
        if(turn) { return "_"; }
        else { return "__"; }
    }
}
