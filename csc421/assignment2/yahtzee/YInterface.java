package yahtzee;
import java.io.*;
import java.util.*;
import yahtzee.YLogic;

/*
* Author:       Christian Carreras
* File Name:    YInterface.java
* File Package: yahtzee
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
* The YIterface class controls/displays the game UI and information. It handles
* all user interaction/commands and maps them to their corresponding game logic
* function. Only modifies the YLogic (game logic) class when necessary occording
* to player commands or the flow of the game. Most functions however deal with
* displaying information to the screen for the user to see. Commands are hard-
* coded into the class as well as file names that are used for displaying
* certain pages related to the game. All methods that directly or indirectly
* mutate the YLogic class, flow of the game, or is a helper function will be 
* private in order to prevent outside-class use. All public functions will
* only facilitate/inspect YLogic class elements with the exception of the
* playerPrompt method which starts the game.
* @author Christian Carreras
**/
public class YInterface {
    /** File that contains list of commands and design choices
    * @see <a href=
        "http://csitrd.kutztown.edu/~ccarr419/csc421/assignment2/README.txt"
        target="_blank">README.txt</a>
    */
    public final File HELPFILE = new File("README.txt");
    /** File that contains list all available categories to choose from 
    * @see <a href=
        "http://csitrd.kutztown.edu/~ccarr419/csc421/assignment2/CATEGORIES.txt"
        target="_blank">CATEGORIES.txt</a>
    */
    public final File CATFILE = new File("CATEGORIES.txt");
    /** File that controls the format of the player score sheet. Will be have
    * no scores as the scores are inserted at runtime.
    * @see <a href=
        "http://csitrd.kutztown.edu/~ccarr419/csc421/assignment2/SCORESHEET.txt"
        target="_blank">SCORESHEET.txt</a>
    */
    public final File SCOREFILE = new File("SCORESHEET.txt");
    /** Read user input from System.in */
    private Scanner scan = new Scanner(System.in); 
    
    /** User command to display the help page */
    public final String HELP = "help";
    /** User command to start or restart the game */
    public final String START = "start";
    /** User command to display current round statistics */
    public final String ROUNDST = "rstat";
    /** User command to display current game statistics */
    public final String GAMEST = "gstat";
    /** User command to display the player's scoresheet */
    public final String SCORE = "score";
    /** User command to print the current roll */
    public final String PRINTD = "pdice";
    /** User command to roll the dice */
    public final String ROLL = "roll";
    /** User command select dice to keep from the current roll */
    public final String KEEP = "keep";
    /** User command to display all categories in the game */
    public final String CATEGOR = "cat";
    /** User command to display all available (non-picked) categories */
    public final String AVAILCT = "acat";
    /** User command to pick a category currently avaiable to them */
    public final String PICKCAT = "pcat";
    /** User command to clear the screen. Works like UNIX 'clear' */
    public final String CLEAR = "clear";
    /** User command to quit the game */
    public final String QUIT = "quit";
    /** User command to cheat and pick their dice */
    public final String CHEAT = "ccc";
    
    /**
    * Constructs the user interface by presenting the intro tag.
    */
    public YInterface() {
        printIntroTag();
    }
    
    /**
    * Constructs the user interface by presenting the intro tag and starting
    * the player prompt from the given game logic class object.
    * @param gLog YLogic (game logic) object
    */
    public YInterface(YLogic gLog) {
        printIntroTag();
        playerPrompt(gLog);
    }
    
    /**
    * Handles all user input commands and maps them to their corresponding
    * functions. Prompt will continue until program termination (quit).
    * @param gLog YLogic (game logic) object
    */
    public void playerPrompt(YLogic gLog) {
        //Loop until user quits
        while(true) {
            checkEndRound(gLog);
            System.out.print("> ");
            String input = scan.nextLine();
            //Handle user input and link commands to functions
            switch(input.toLowerCase()) {
                case "": //User did not enter anything
                    break;
                case HELP: //show help page
                    printList(parseFile(HELPFILE));
                    break;
                case START: //start/restart game
                    gLog = beginGame(gLog);
                    break;
                case ROUNDST: //show current game stats if game in progress
                    if(!prgErr(gLog.getGameInPrg(), 
                        "Cannot show round status.")) { }
                    else { playerStats(gLog); }
                    break;
                case GAMEST: //show current game stats if game in progress
                    if(!prgErr(gLog.getGameInPrg(), 
                        "Cannot show game status.")) { }
                    else { gameStats(gLog); }
                    break;
                case SCORE: //show current player scoresheet
                    if(!prgErr(gLog.getGameInPrg(), 
                        "Cannot show scoresheet.")) { }
                    else { printScoreSheet(gLog); }
                    break; 
                case PRINTD: //print current dice if game in progress
                    if(!prgErr(gLog.getGameInPrg(), "Cannot print dice.")) { }
                    else { printRoll(gLog); }
                    break; 
                case ROLL: //roll dice if game in progress
                    if(!prgErr(gLog.getGameInPrg(), "Cannot roll dice.")) { }
                    else { roll(gLog); }
                    break;           
                case KEEP: //keep user-specified dice if game in progress
                    if(!prgErr(gLog.getGameInPrg(), 
                        "Cannot pick dice to keep.")) { }
                    else { keepDice(gLog); }
                    break;             
                case CATEGOR: //show all categories in the game
                    printList(parseFile(CATFILE));
                    break;      
                case AVAILCT: //show all available categories during a game
                    if(!prgErr(gLog.getGameInPrg(), 
                        "Cannot show available categories.")) { }
                    else { printList(availableCategories(gLog, true));
                        System.out.print("\n"); }
                    break;  
                case PICKCAT: //pick an avaiable category during a game
                    if(!prgErr(gLog.getGameInPrg(), 
                        "Cannot pick category.")) { }
                    else { pickCategory(gLog); }
                    break;
                case CLEAR: //Only supported on ANSI-supported systems
                    System.out.print("\033[H\033[2J");
                    break;
                case QUIT: //quit the game and terminate the program
                    quitGame();
                    break;
                case CHEAT: //lets the user specify exactly what dice they want
                    if(!prgErr(gLog.getGameInPrg(), 
                        "Sshhh... Cannot use this here..")) { }
                    else { cheat(gLog); }
                    break;
                default: //state the the entered String is not a command
                    System.out.println("Error: '" + input + 
                        "' is not an internal command.");
            }
        }
    }
    
    /**
    * Compiles a list of categories available to user at the moment of this
    * method call. All categories that were picked already will be x'd out.
    * @param gLog YLogic (game logic) object
    * @param b True to add the table headers. False to not print.
    * @return List of Strings which holds all available categories
    */
    public List<String> availableCategories(YLogic gLog, boolean b) {
        List<String> list = new ArrayList<String>(); //List to hold categories
        int[] scores = gLog.findDiceScores(); //Player's current score list
        int i = 0;
        if(b) { //Control if the table headers will be added or not
            list.add("Score\tCategory\n");
            list.add("-----\t--------\n");
        }
        //Get list of all categories in the game
        for(YLogic.Categories cat : gLog.c.values()) {
            //If the category is not picked, show the category name
            //Also show the score of that category if it would be picked at
            //the moment of this method call.
            if(!gLog.getCatPicked(i)) {
                list.add(scores[i] + "\t" + cat + "\n");
            }
            //If the category was picked, x out the score and name fields
            else {
                list.add("xxxxx\txxxxxxxx\n");
            } i++;
        }
        return list;
    }
    
    /**
    * Shows the current statistics of the user's current round. Will show the
    * current round number, number of rolls rolled, current dice rolled, 
    * current kept dice if applicable and previous rolls rolled this round
    * including the current roll.
    * @param gLog YLogic (game logic) object
    */
    public void playerStats(YLogic gLog) {
        System.out.println("\nCurrent Round: " + gLog.getRoundNum());
        System.out.println("Number of Rolls: " + gLog.getRollNum());      
        System.out.println("Current Dice: " + gLog.dice.toString());
        System.out.println("Current Kept Dice: " + gLog.dice.keptToStr());    
        System.out.println("\nPrevious Rolls:\n" + gLog.dice.prevRollsToStr());
    }
    
    /**
    * Shows the current statistics of the user's current game. Will show the
    * current total of rolls rolled, Yahtzee count, raw score, bonus score,
    * total score, and individual round information if applicable. Round
    * information includes the score of the round, the category picked and
    * every roll rolled for that round. At least on round must be completed
    * before round information will be shown to the user.
    * @param gLog YLogic (game logic) object
    */
    public void gameStats(YLogic gLog) {
        //Total rolls will always be off by one only at the end of the game 
        //because of how the end of round is handled by the game logic class
        if(gLog.getRoundNum() >= gLog.ROUND_LIMIT) {
            System.out.println("\nTotal Rolls: " + (gLog.getTotalRolls()-1)); }
        else {
            System.out.println("\nTotal Rolls: " + gLog.getTotalRolls()); }
        System.out.println("Yahtzee Count: " + gLog.getYahtzeeCount());
        System.out.println("Raw Score: " + (gLog.upperTotal()+gLog.lowerTotal()));
        System.out.println("Bonus Score: " + (gLog.upperBonus()+gLog.lowerBonus()));
        System.out.println("Total Score: " + gLog.grandTotal() + "\n");
        //Make sure a round was completed before continuing
        if(gLog.getRoundNum() > 1) {
            //Only supported on ANSI-supported systems
            final String ANSI_RESET = "\u001B[0m";
            final String ANSI_GRAY = "\u001B[90m";
            //Create the table headers by formatting the output
            System.out.format("%-5s %5s %-15s %-10s %-10s %-10s\n", "ROUND",
                "SCORE", "CATEGORY", "ROLL #1", "ROLL #2", "ROLL #3");
            System.out.format("%5s %5s %5s%5s%5s %5s%5s %5s%5s %5s%4s\n",
                "=====","=====","=====","=====","=====","=====",
                "=====","=====","=====","=====","====");
            //Go through each round gathering their data
            for(int i = 0; i < gLog.getRoundNum()-1; i++) {
                //For readability, flip the color for each row
                if(!(i % 2 == 0)) { System.out.print(ANSI_GRAY); }
                System.out.format("%-6s", ((i+1) + ".)"));
                System.out.format("%-6d", gLog.rd.getRoundScores(i));
                System.out.format("%-16s", gLog.rd.getCategoriesPicked(i));
                //Print each roll in that round. Will try to print three rolls
                //but if there is less than three rolls then print a dash '-'
                for(int j = 0; j < gLog.ROLL_LIMIT; j++) {
                    //Get the roll and print each die with a space in between
                    if(j < gLog.rd.getAllRolls(i).size()) {
                        int[] arr = gLog.rd.getAllRolls(i).get(j);
                        String s = "";
                        for(int k : arr) { s += k + " "; }
                        System.out.format("%-11s", s);
                    }
                    else { System.out.format("%-11s", "-"); }
                } System.out.print("\n"); //Print newline for the next round
                System.out.print(ANSI_RESET); //Return to normal color
            } System.out.println("");
        }
        //No rounds have been completed yet
        else { System.out.println("No rounds completed yet.\n"); }
    }
    
    /**
    * Prints whether the current roll is a Yahtzee i.e. all dice the same
    * @param gLog YLogic (game logic) object
    */
    public void checkYahtzee(YLogic gLog) {
        if(gLog.dice.isYahtzee()) {
            System.out.println("Yahtzee!\n");
        }
    }
    
    /**
    * Gets the blank scoresheet file from the file parser method and then
    * adds the player's scores dynamically occording to the the category.
    * Normal categories are depicted as parentheses, bonus categories are
    * depicted as curly braces and total categories are depcited as brackets.
    * A special category for the Yahtzee bonus count uses the lt gt signs.
    * Will only show the scores of categories picked, bonuses and totals.
    * @param gLog YLogic (game logic) object
    */
    public void printScoreSheet(YLogic gLog) {
        List<String> list = parseFile(SCOREFILE); //the blank scoresheet
        int idx, scoreCounter = 0, totalCounter = 0, bonusCounter = 0;
        //Ordered array of totals as they appear in the scoresheet
        int[] totals = 
            { gLog.upperTotal(), gLog.upperTotal() + gLog.upperBonus(),
                gLog.upperTotal() + gLog.upperBonus(),
                gLog.lowerTotal() + gLog.lowerBonus(), gLog.grandTotal()
            };
        //Ordered arrary of bonus scores as they appear in the scoresheet
        int[] bonuses = { gLog.upperBonus(), gLog.lowerBonus() };
        //Read the parsed file line by line
        for(int i = 0; i < list.size(); i++) {
            String str = list.get(i);
            //If there is a left-parentheses, insert a category score
            if((idx = str.indexOf('(')) != -1) {
                //Only show the score if the category was picked
                if(gLog.getCatPicked(scoreCounter)) {
                    String score = "" + gLog.getCatScore(scoreCounter);
                    //Insert the score into the line string
                    insRep(list, str, score, idx+1, i);
                } scoreCounter++;
            }
            //If there is a left-bracket, insert a total score
            else if((idx = str.indexOf('[')) != -1) {
                String total = "" + totals[totalCounter++];
                insRep(list, str, total, idx+1, i); 
            }
            //If there is a left-curly brace, insert a bonus score
            else if((idx = str.indexOf('{')) != -1) {
                String bonus = "" + bonuses[bonusCounter++];
                insRep(list, str, bonus, idx+1, i);
            }
            //For every Yahtzee bonus insert a '*' in lieu of a checkmark
            else if((idx = str.indexOf('<')) != -1) {
                String check = "";
                for(int j = 0; j < gLog.getYahtzeeCount()-1; j++) {
                    check += "*";
                }
                insRep(list, str, check, idx+1, i);
            }
        }        
        printList(list); //Print the freshly-made scoresheet
    }
    
    /**
    * Method to print an intro tag to welcome the user to the game and inform
    * them of basic game information or anything else helpful.
    */
    public void printIntroTag() {
        System.out.print("\n" +
            "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n" +
            "* Welcome to Yahtzee!\n*\n" +
            "* Type 'help' for a list of game commands\n*\n" +
            "* Programmed by Christian Carreras\n" +
            "* Yahtzee © 2017 Hasbro, Inc.\n" +
            "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
   }
    
    /**
    * Prints the current roll in both dice format and number format. Also
    * displays the current round and roll number. Will also determine if the
    * roll is a Yahtzee or not.
    * @param gLog YLogic (game logic) object
    */
    public void printRoll(YLogic gLog) {
        printDiceImage(gLog);
        System.out.print("\nROUND " + gLog.getRoundNum());
        System.out.println(" ROLL " + gLog.getRollNum());
        System.out.print("Current roll: ");
        printDice(gLog);
        System.out.print("\n");
        checkYahtzee(gLog);
    }
    
    /**
    * Prints the dice the user has decided to keep to the screen.
    * @param gLog YLogic (game logic) object
    */
    public void printKeptDice(YLogic gLog) {
        for(int i = 0; i < gLog.dice.NUM_DICE; i++) {
            if(gLog.dice.getKeptDie(i) == true) { 
                System.out.print(gLog.dice.getDie(i) + " "); 
            }
        }
        System.out.print("\n");
    }
    
    /**
    * Prints the dice object by converting it to a string
    * @param gLog YLogic (game logic) object
    */
    public void printDice(YLogic gLog) {
        System.out.println(gLog.dice.toString());
    }
    
    /**
    * Prints the dice object as an image
    * @param gLog YLogic (game logic) object
    */
    public void printDiceImage(YLogic gLog) {
        System.out.print(diceToImage(gLog));
    }
    
    /**
    * Creates a visible image to the likeness of a dice face. Each dice face
    * will correspond to each number in the roll. Calls a helper function to
    * figure what section of the dice face to print according to what level
    * of the print the method is on. Dice faces are printed horizontally.
    * @param gLog YLogic (game logic) object
    * @return The string containing the dice face images
    * @see #imagerHelper
    */
    public String diceToImage(YLogic gLog) {
        int[] dice = gLog.dice.getDice();
        boolean colorMe = false;
        //Only supported in an ANSI-supported environment
        final String ANSI_RESET = "\u001B[0m";
        final String ANSI_BLACK = "\u001B[30m";
        final String ANSI_WHITE_BACKGROUND = "\u001B[47m";
        int midSections = 3;
        //Strings that are used for all combinations of dice faces
        String dTop = " _________ "; //Dice face top
        String none = "|         |"; //Dice face none
        String lOne = "| •       |"; //Dice face one dot left
        String cOne = "|    •    |"; //Dice face one dot center
        String rOne = "|       • |"; //Dice face one dot right
        String both = "| •     • |"; //Dice face two dots (both)
        String dBot = "|_________|"; //Dice face bottom
        String out = "";
        
        //If you want to colorize the dice i.e. white w/ black dots
        if(colorMe) {
            dTop = "           "; //Dice face top
            none = "" + ANSI_BLACK + ANSI_WHITE_BACKGROUND + "           " 
                + ANSI_RESET; //Dice face none
            lOne = "" + ANSI_BLACK + ANSI_WHITE_BACKGROUND + "  •        " 
                + ANSI_RESET; //Dice face one dot left
            cOne = "" + ANSI_BLACK + ANSI_WHITE_BACKGROUND + "     •     " 
                + ANSI_RESET; //Dice face one dot center
            rOne = "" + ANSI_BLACK + ANSI_WHITE_BACKGROUND + "        •  " 
                + ANSI_RESET; //Dice face one dot right
            both = "" + ANSI_BLACK + ANSI_WHITE_BACKGROUND + "  •     •  " 
                + ANSI_RESET; //Dice face two dots (both)
            dBot = "" + ANSI_BLACK + ANSI_WHITE_BACKGROUND + "           " 
                + ANSI_RESET; //Dice face bottom
        }
        
        //Put Strings that change depending on the dice number inside a map
        //The helper function will help pick the right choice from the map
        Map<Integer, String> map = new HashMap<Integer, String>();
        map.put(0, none);
        map.put(1, lOne);
        map.put(2, cOne);
        map.put(3, rOne);
        map.put(4, both);
        
        int NUMDICE = dice.length;
        //Automatically add the top portion as it is the same for every number
        for(int i = 0; i < NUMDICE-1; i++) { out += dTop + " "; }
        out += dTop + "\n"; //Separate the last one because it needs a new line
      
        //Automatically add the second top portion as it is the same too
        for(int i = 0; i < NUMDICE-1; i++) { out += none + " "; }
        out += none + "\n"; //Separate the last one because it needs a new line
      
        //The next three portions change depending on which dice number it is
        //Call the helper function to get the key of what String to print
        //located within the map
        for(int i = 0; i < midSections; i++) { //Mid sections of dots
            //Holds the value of the next for loop since it falls out of scope
            int temp = 0; 
            //Get the correct String to print according to its dice number
            //and its section number
            for(int j = 0; j < NUMDICE-1; j++) { 
                out += map.get(imagerHelper(dice[j], i)) + " ";
                temp = j; //Give temp the value since j will fall out of scope
            }
            //Separate the last one because it needs a new line
            out += map.get(imagerHelper(dice[temp+1], i)) + "\n";
        }
        //Automatically add the last portion as it is the same for every number
        for(int i = 0; i < NUMDICE-1; i++) { out += dBot + " "; }
        out += dBot + "\n";
      
      return out; 
    }
    
    /**
    * Begins the game by setting the roll, total rolls, and round number to one
    * as well as printing the first roll and setting the game in progress 
    * boolean to true. If this function is called during a game in progress.
    * The user will be warned that game is about to be restarted. If the user
    * wishes to continue an new game will be started, if not the game function
    * will return and the game will proceed as normal.
    * @param gLog YLogic (game logic) object
    * @return The new instance of the game logic object.
    */
    private YLogic beginGame(YLogic gLog) {
        //If the game is in progress warn the user about it
        if(gLog.getGameInPrg() == true) {
            //If the user wants to restart, create a new game logic instance
            if(yesNoPrompt("Warning. Restart the game? [y/n]: ")) {
                System.out.println("Starting new game...");
                gLog = new YLogic();
            }
            //Otherwise return the the existing game
            else { 
                System.out.println("Continuing...\n");
                return gLog;
            }
        }
        //Set the game to in progress
        gLog.setRollNum(1);
        gLog.setRoundNum(1);
        gLog.setTotalRolls(1);
        printRoll(gLog);
        gLog.setGameInPrg(true);
        return gLog;
    }
    
    /**
    * Prompts the user if they really wish to quit the game. If the user picks
    * yes the program will terminate. If no is picked, the game will continue.
    */
    private void quitGame() {
        if(yesNoPrompt("Are you sure you want to quit? [y/n]: ")) {
            System.out.println("Goodbye.\n");
            System.exit(0);
        }
        else { System.out.println("Continuing...\n"); }
    }
    
    /**
    * Allows the user to pick a category from the currently available 
    * categories. Choosing a category will end the round and continue to the
    * next round. The user may exit from making a choice by entering zero
    * unless it is currently the last roll of the round.
    * @param gLog YLogic (game logic) object
    * @return True if a category was picked. False if one was not picked.
    * @exception NumberFormatException User entered non-numeric input
    */
    private boolean pickCategory(YLogic gLog) {
        System.out.println("Select a category by entering the number before " +
         "it.\nOR enter zero to exit if not the last roll of the round.");
        System.out.print("\n#\tScore\tCategory\n");
        System.out.print("---\t-----\t--------");
        //Get the list of available categories (without the table header)
        List<String> categories = availableCategories(gLog, false);
        printNumberedList(categories); //Number the categories
        System.out.print("\n");
        do {
            System.out.print("Enter a number between 1 and " + 
                categories.size() + ": ");
            String command = scan.nextLine();
            try {
                int choice = Integer.parseInt(command);
                //Check if the number entered was in range of options
                if(choice >= 1 && choice <= categories.size()) {
                    //Make sure the category was not picked already
                    if(!gLog.getCatPicked(choice-1)) {
                        //Get the category category occording the current dice
                        int newScore = gLog.findDiceScores()[choice-1];
                        //Display what category the user picked and what the
                        //score was for the choice they made
                        System.out.println("You picked: "
                            + gLog.getCatName(choice-1));
                        System.out.println("You scored: " + newScore);
                        //Set the scores in the game logic object and set the
                        //category to picked (true)
                        gLog.setCatScore((choice-1), newScore);
                        gLog.setCatPicked((choice-1), true);
                        //Change the game in progress to false to end the round
                        gLog.setGameInPrg(false);
                        //Set the round data object values so the values can
                        //be displayed at a later time
                        gLog.rd.setCategoriesPicked(gLog.getRoundNum()-1,
                            gLog.getCatName(choice-1));
                        gLog.rd.setRoundScores(gLog.getRoundNum()-1, newScore);
                        //If the dice was a Yahtzee when the category was picked
                        //Check to see if the Yahtzee count can be incremented
                        if(gLog.dice.isYahtzee() 
                            && gLog.getCatPicked(gLog.c.YAHTZEE.value())) {
                            gLog.incYahtzeeCount();
                        }
                        return true;
                    } //The category was picked already, choose again
                    else { System.out.println("Category #" + choice + " was picked already."); }
                }
                //Zero represents the exit command, exit back to game if entered
                else if(choice == 0) {
                    //Make sure it is not the last round, the user must pick a
                    //category if that is the case
                    if(gLog.getRollNum() >= gLog.ROLL_LIMIT) {
                        System.out.println("Cannot exit on last roll of round.");
                    }
                    else {
                        System.out.println("No category picked. Returning.\n");
                        return false; 
                    }
                }
                //Return the prompt to choose a category for out of range numbers
                else { continue; } 
            }
            //Return the prompt to choose a category for non-numeric input
            catch(NumberFormatException e) { continue; }
        } while(true); //Keep looping until a choice is made
    }
    
    /**
    * Checks if the game has reached the end of the round i.e. by meeting or
    * exceeding the number of alloted rolls. Also checks if the game is over
    * i.e. by meeting or exceeding the number of alloted rounds.
    * @param gLog YLogic (game logic) object
    */
    private void checkEndRound(YLogic gLog) {
        //Check if the user met the roll limit or the game is not in progress
        //Reasons for the game to not be in progress includes the game just
        //started (the user ran the game but did not start it yet), or the
        //user picked a category before all their rolls were used up
        if((gLog.getRollNum() >= gLog.ROLL_LIMIT) || !gLog.getGameInPrg()) {
            //If the game is in progress, the user must have ran out of rolls,
            //in that case make them pick a category
            if(gLog.getGameInPrg()) {
                pickCategory(gLog);
            }
            //In any case if the user has ran out of rounds, end the game, show
            //the game stats and terminate the program. 
            if(gLog.getRoundNum() >= gLog.ROUND_LIMIT) {
                gLog.endRound();
                gameStats(gLog);
                System.out.println("Game Over.\n");
                System.exit(0);
            }
            //Check if the roll number or round number is zero
            //i.e. the game was not started yet
            if(gLog.getRollNum() == 0 || gLog.getRoundNum() == 0) {
                System.out.println("\nType 'start' to play.\n");
            }
            //Otherwise it must be the end of the round
            else {
                System.out.println("\nROUND " + gLog.getRoundNum() + " OVER");
                gLog.endRound();
                gLog.setGameInPrg(true);
                printRoll(gLog);
            }            
        }
    }
   
    /**
    * Rolls the player's dice. If the user has not recently picked dice to keep
    * this method will warn them with a prompt on whether they wish to return
    * and pick dice to keep or continue with the roll anyway
    * @param gLog YLogic (game logic) object
    */
    private void roll(YLogic gLog) {
        //Check if the user kept this roll
        if(!gLog.getPlayerKept()) {
            //If they did not keep make sure they want to roll the dice
            if(yesNoPrompt("Are you sure you want to roll " +
                "w/o keeping dice? [y/n]: ")) {
                gLog.playerRoll();
                printRoll(gLog);
            }
            else { //User decided to go back and pick dice to keep
                System.out.println("Aborting roll request.\n");
                return;
            }
        }
        else { //User already kept, continue with the roll
            gLog.playerRoll();
            printRoll(gLog);
        }
    }
    
    /**
    * Method that allows the user decide what dice they would like to keep. The
    * user will be asked for each die if they want to keep it or not. After
    * successfully deciding what dice to keep, the kept dice will be printed.
    * @param gLog YLogic (game logic) object
    */
    private void keepDice(YLogic gLog) {
        boolean[] keptDice = new boolean[gLog.dice.NUM_DICE];
        //Individually prompt the user to choose if they wish to keep the dice
        for(int i = 0; i < gLog.dice.NUM_DICE; i++) {
            if(yesNoPrompt("Do you want to keep dice #" + (i + 1) +
                " (" + gLog.dice.getDie(i) + ")? [y/n]: ")) {
                keptDice[i] = true; //User decided to keep the dice
            }
            else { keptDice[i] = false; } //User decided not to keep
        }
        gLog.dice.setKeptDice(keptDice);
        //Print the dice the user decided to keep
        System.out.print("You kept: ");
        printKeptDice(gLog);
        System.out.print("\n");
        gLog.setPlayerKept(true); //Let the game know that the player kept dice
    }
    
    /**
    * Allows the player to 'cheat' by selecting whatever dice they want for
    * their roll. The use of this function should be used exclusively for bug-
    * testing or score-testing. Using this function does not modify round
    * data so data may be inconsistent if the user cheats.
    * @param gLog YLogic (game logic) object
    */
    private void cheat(YLogic gLog) {
        int[] newDice = new int[gLog.dice.NUM_DICE];
        for(int i = 0; i < gLog.dice.NUM_DICE; i++) {
            do {
                try { //make sure the input cooresponds with dice face numbers
                    System.out.print("(" + (i+1) + ") > ");
                    String input = scan.nextLine();
                    if(Integer.parseInt(input) <= gLog.dice.DIE_NUM_MIN || 
                        Integer.parseInt(input) > gLog.dice.DIE_NUM_MAX) {
                        continue;
                    }
                    newDice[i] = Integer.parseInt(input);
                    break;
                }
                catch(NumberFormatException e) { continue; }
            } while(true); //loop until all the cheated dice are picked
        } //put the cheated dice into the game logic's dice
        gLog.dice.setDice(newDice);
    }
    
    /**
    * Helps the {@link diceToImage} method by returning a key to get the
    * correct portion of the dice face to print according to the number given
    * and the section number.
    * @param num The dice number
    * @param pos The section position number
    * @return The key which is used to access the correct String in a String map
    */
    private int imagerHelper(int num, int pos) {
        //Int keys representing what String to print
        int none = 0, lOne = 1, cOne = 2, rOne = 3, both = 4;
        switch(pos) {
            case 0: //Section zero
                //1 returns none, 2 & 3 returns rOne, everything else returns both
                if(num == 2 || num == 3) { return rOne; }
                else if(num > 3) { return both; }
                else { return none; }
            case 1: //Section one
                //1, 3 & 5 return cOne, 6 returns both, the rest return none
                if(num == 1 || num == 3 || num == 5) { return cOne; }
                else if(num == 6) { return both; }
                else { return none; }
            case 2: //Section two
                //1 returns none, 2 & 3 returns lOne, everything else returns both
                if(num == 2 || num == 3) { return lOne; }
                else if(num > 3) { return both; }
                else { return none; }
            default: return -1; //Error on section input
        }
    }
    
    /**
    * Prompts the user with a yes or no question. Changes the input to lower
    * case for maximum compatibility.
    * @param str String for the prompt to print (Should be a yes/no question)
    * @return true if the user entered y (yes) False if the user entered n (no).
    */
    private boolean yesNoPrompt(String str) {
        String choice = "";
        do { //keep looping until 'y' or 'n' is entered
            System.out.print(str);
            choice = scan.nextLine();
        } while(!choice.toLowerCase().equals("y") && 
            !choice.toLowerCase().equals("n"));
        //If 'y' is entered return true, if 'n' is entered return false
        if(choice.toLowerCase().equals("y")) { return true; }
        else { return false; }
    }  
    
    /**
    * Parses a file and splits it into token Strings by line. The strings are 
    * added to a list of Strings and returned once the whole file is parsed.
    * @param file The file to parse
    * @return The list that contains the String tokens
    */
    private List<String> parseFile(File file) {
        BufferedReader reader = null;
        List<String> list = new ArrayList<String>(); //List to split tokens into
        String text = null; //Temporary String token holder
        try {
            //Read the file line by line. Once a line is read, add a new line
            reader = new BufferedReader(new FileReader(file));
            while((text = reader.readLine()) != null) { //While not EoF
                list.add(text);
                list.add("\n");
            }
            reader.close(); //Be a good samaritan and close the file 
        }
        //Catch for read/write errors and if the file does not exist
        catch(FileNotFoundException e) { e.printStackTrace(); }
        catch(IOException e) { e.printStackTrace(); }
        finally {
            try {
                //If file was still left open for any reason close it
                if(reader != null) { 
                    reader.close();
                    return list;
                }
            }
            catch(IOException e) { }
        }
        return null;
    }
    
    /**
    * Prints a given list of Strings. Mostly used for printing parsed files.
    * @param list List to print to screen (most likely parsed file)
    */
    private void printList(List<String> list) {
        System.out.println("");
        for(Iterator<String> i = list.iterator(); i.hasNext();) {
            Object item = i.next();
            System.out.print(item.toString()); 
        }
    }
    
    /**
    * Prints a list of strings but numbers them according to their order in the
    * list. Each entry is separated by a new-line.
    * @param list List used to print a numbered list
    */
    private void printNumberedList(List<String> list) {
        int counter = 1;
        System.out.println("");
        for(Iterator<String> i = list.iterator(); i.hasNext();) {
            Object item = i.next();
            System.out.print((counter++) + ".)\t" + item.toString());
        }
    }
    
    /**
    * Inserts a given String into an exact position of another String. It will
    * then take that String and place it in a list of Strings at a given index.
    * Uses a StringBuilder to handle the String insertion.
    * @param l The list of Strings to place the new String inside of
    * @param tot The String to edit
    * @param r The String to insert into tot
    * @param idx The position in String tot to place String r
    * @param i The position in l to swap for the newly build String
    */
    private void insRep(List<String> l, String tot, String r, int idx, int i) {
        String str = new StringBuilder(tot).insert(idx, r).toString();
        //Swap, remove the old String and put the new String in its place
        l.remove(i);
        l.add(i, str);
    }
    
    /**
    * If the game is not in progress this will print an error message to screen.
    * @param b Boolean that tells if the game is in progress or not
    * @param str String to add to the "Game not in progress." error message
    * @return gPrg: in order be able to place this function in an if statement
    */
    private boolean prgErr(boolean b, String str) {
        if(!b) { System.out.println("Game not in progress. " + str); }
        return b;
   }
}
