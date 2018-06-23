package com.yahtzee.client;
import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Random;

/*
* Author:       Christian Carreras
* File Name:    YLogic.java
* File Package: com.yahtzee.client
* File Version: 1.1
* File Date:    10/05/2017
* Due Date:     11/17/2017
* Assignment:   #4
* Professor:    Dr. Dylan Schwesinger
* Course #:     CSC421
* Course Name:  Web-Based Software Design & Development
* University:   Kutztown University
* Major:        CSCM Software Development
*/

/**
* The YLogic class controls all aspects of the game itself. It initializes all
* necessary game objects and methods for proper mutation, facilitation and
* inspection of all game logic variables. Part of the YLogic class is the
* nested class Dice which controls all things relating the the game dice.
* Nested enums are used for special groupings of constants such as the
* category names in the game scoresheet or the scores of specific categories.
* YLogic does not handle any input nor does it display any information to the
* screen. In fact, the YLogic class can not handle any amount of user
* interaction. Because of this a separate class is necessary to see over the
* task of interacting with the user. For the benefit of the developer and the
* user, a nested class called roundData was added to store game data across
* all rounds. It was with good intentions that this data will make the game
* easier to play, understand and result in a more enjoyable experience.
*/
public class YLogic {
    /** Array that holds the score of the categories */
    private int[] score;
    /** The current amount of rolls rolled */
    private int rollNum;
    /** The current round the player is on */
    private int roundNum;
    /** The total amount of rolls rolled */
    private int totalRolls;
    /** The number of yahtzees *officially* rolled */
    private int yahtzeeCount;
    /** Controls the flow of the game and game stages */
    private boolean gameInPrg;
    /** Lets the game know the player kept dice */
    private boolean playerKept;
    /** Array the shows which categories were picked */
    private boolean[] catPicked;
    /** Amount of rolls per round */
    public static final int ROLL_LIMIT = 3;
    /** Amount of rounds per game */
    public static final int ROUND_LIMIT = 13;   
    /** Enum of constant category indexes */
    public Categories c;
    /** Enum of constant category scores */
    public Scores sc;
    /** Game Dice class to handle all dice related functions */
    public Dice dice;
    /** Game data class to record all useful user data during a game */
    public roundData rd;
    
//ENUMS & CLASSES
    
    /**
    * Assigns a category to a specific number. This is necessary for indexing
    * all arrays to the correct category regarding the scoresheet.
    */
    public enum Categories {
        ACES (0), 
        TWOS (1), 
        THREES (2), 
        FOURS (3), 
        FIVES (4), 
        SIXES (5), 
        THREE_OF_A_KIND (6), 
        FOUR_OF_A_KIND (7), 
        FULL_HOUSE (8), 
        SMALL_STRAIGHT (9), 
        LARGE_STRAIGHT (10),
        YAHTZEE (11), 
        CHANCE (12);
        
        private final int value;        
        Categories(int v) { this.value = v; }       
        public int value() { return value; }
    }
    
    /**
    * Assigns a score to categories that have a static score. Static scores
    * such as these will remain the same no matter the dice combination.
    */
    public enum Scores {
        FULL_HOUSE (25), 
        SMALL_STRAIGHT (30), 
        LARGE_STRAIGHT (40),
        YAHTZEE (50), 
        UPPER_BONUS (35),
        LOWER_BONUS (100);
        
        private final int value;        
        Scores(int v) { this.value = v; }       
        private int value() { return value; }
    }
    
    /**
    * Exception that should be thrown when an array that is being used to
    * initialize a category/score array is not of length {@value #ROUND_LIMIT}.
    */
    private class InvalidScoreCardSizeException extends Exception {
        /** Gives error message, prints the stack trace, then terminates. */
        public InvalidScoreCardSizeException() {
            System.err.println("Error: Invalid size for scoressheet array.");
            this.printStackTrace();
            //System.exit(0);
        }
    }
    
    /**
    * The Dice class object is defining part of the YLogic class. Being a
    * nested class YLogic has access to all non-private functions inside.
    * This way YLogic can easily interact with the Dice object but it is still
    * secure from the outside. To implement the dice of Yahtzee, an int array
    * is used to represent the dice. A random number generator is used to
    * represent the act of rolling the dice. The class also instantiates a
    * list to hold previous rolls and a boolean array to hold which dice are
    * being kept. All mutating methods are either protected or private so only
    * the YLogic class can use them or itself. All non-mutating methods are 
    * public so they can still be accessed with a YLogic class instance. Last
    * the Dice class creates two exceptions to catch certain errors dealing
    * with wrong sizes and wrond die face numbers.
    */
    public class Dice {
        /** Int array that represents dice */
        private int[] playerDice;
        /** Array that shows which dice are kept */
        private boolean[] keptDice;
        /** List of previous dice rolled */
        private List<int[]> prevRolls;
        /** Number of dice allowed in the game */
        public static final int NUM_DICE = 5;
        /** Minimum dice face number allowed for any die */
        public static final int DIE_NUM_MIN = 1;
        /** Maximum dice face number allowed for any die */
        public static final int DIE_NUM_MAX = 6;
        
    //EXCEPTION CLASSES
        
        /**
        * Exception that should be thrown when the dice array is initilized to
        * any other value than {@value #NUM_DICE}.
        */
        private class InvalidTotalDiceException extends Exception {
            /** Gives error message, prints the stack trace, then terminates. */
            public InvalidTotalDiceException() {
                System.err.println("Error: Invalid total number of dice.");
                this.printStackTrace();
                //System.exit(0);
            }
        }
        
        /**
        * Exception that should be thrown when the dice array is not initilized
        * to a value between {@value #DIE_NUM_MIN} and {@value #DIE_NUM_MAX}.
        */
        private class InvalidDieNumberException extends Exception {
            /** Gives error message, prints the stack trace, then terminates. */
            public InvalidDieNumberException() {
                System.err.println("Error: Invalid die number.");
                this.printStackTrace();
                //System.exit(0);
            }
        }
        
    //CONSTRUCTORS
        
        /**
        * Basic constructor to initialize the Dice object by rolling a new
        * dice array and initializing all other variables.
        */
        protected Dice() {
            setDice(rollDice());
            setKeptDice();
            setPrevRolls();
            addRoll();
        }
        
        /**
        * Alternate constructor where the dice array is initialized as the
        * given array parameter insted of rolling a new dice array.
        * @param d Dice array to set the game's dice to
        */
        protected Dice(int d[]) {
            setDice(d);
            setKeptDice();
            setPrevRolls();
            addRoll();
        }
        
    //GETS
    
        /**
        * Gets the int array representing the dice of the game.
        * @return The int array representing the game's dice
        */
        public int[] getDice() {
            return playerDice;
        }
        
        /**
        * Gets a specific die in the dice array.
        * @param i The die to retrieve
        * @return An int representing a singal die of the game's dice
        */
        public int getDie(int i) {
            return getDice()[i];
        }
        
        /**
        * Gets the boolean array representing the kept dice.
        * @return The boolean array representing the game's kept dice
        */
        public boolean[] getKeptDice() {
            return keptDice;
        }
        
        /**
        * Gets a specific kept die in the kept dice array.
        * @param i The die to retrieve
        * @return A boolean representing a singal kept die of the kept dice
        */
        public boolean getKeptDie(int i) {
            return keptDice[i];
        }
        
        /**
        * Gets the list of previous dice rolled
        * @return The list of int arrays representing the previous dice rolls
        */
        public List<int[]> getPrevRolls() {
            return prevRolls;
        }
        
    //SETS
    
        /**
        * Sets the dice array to a new int array of length {@value #NUM_DICE}.
        */
        protected void setDice() {
            playerDice = new int[NUM_DICE];
        }
        
        /**
        * Sets the dice array to a specific dice configuration. The dice array
        * must be of length {@value #NUM_DICE}.
        * @param d Dice array to set the game's dice to
        */
        protected void setDice(int d[]) {
            //Make sure that the dice are initialized before continuing
            if(playerDice == null) { setDice(); }
            try {
                //If the array parameter is not the right size; throw exception
                if(d.length != NUM_DICE) {
                    throw new InvalidTotalDiceException();
                }
                //Otherwise the right size, set each die individually in order
                //to check each die number for errors
                else {
                    for(int i = 0; i < NUM_DICE; i++) {
                        setDie(i, d[i]);
                    }
                }
            }
            catch(InvalidTotalDiceException e) { }
        }
        
        /**
        * Sets a specific die to the given value. Must be between
        * {@value #DIE_NUM_MIN} and {@value #DIE_NUM_MAX}.
        * @param die The die number in which to change the value of
        * @param num The new value to set the die to
        */
        private void setDie(int die, int num) {
            try {
                //Make sure the new value is in the range of dice face values
                if(num < DIE_NUM_MIN || num > DIE_NUM_MAX) {
                    throw new InvalidDieNumberException();
                }
                else playerDice[die] = num;
            }
            catch(InvalidDieNumberException e) { }
        }
        
        /**
        * Sets the kept dice array to a new boolean array of length
        * {@value #NUM_DICE}.
        */
        protected void setKeptDice() {
            keptDice = new boolean[NUM_DICE];
        }
        
        /**
        * Sets the kept dice array to a specific boolean configuration. The
        * kept dice array must be of length {@value #NUM_DICE}.
        * @param b Boolean array to set the game's kept dice
        */
        protected void setKeptDice(boolean b[]) {
            //Make sure that the kept dice are initialized before continuing
            if(keptDice == null) { setKeptDice(); }
            try {
                //If the array parameter is not the right size; throw exception
                if(b.length != NUM_DICE) {
                    throw new InvalidTotalDiceException();
                }
                //Otherwise the right size, set each die individually in order
                //to check each die number for errors
                else {
                    for(int i = 0; i < NUM_DICE; i++) {
                        setKeptDie(i, b[i]);
                    }
                }
            }
            catch(InvalidTotalDiceException e) { }
        }
        
        /**
        * Sets a specific kept die to the given boolean t/f value.
        * @param die The die number in which to change the value of
        * @param b The new boolean value to set the die to
        */
        protected void setKeptDie(int die, boolean b) {
            keptDice[die] = b;
        }
        
        /** Sets the previous dice list to a new ArrayList of int arrays. */
        protected void setPrevRolls() {
            prevRolls = new ArrayList<int[]>();
        }
        
    //METHODS
    
        /**
        * Returns a new dice int array, initializing it to a random
        * configuration to representing a player rolling the dice.
        * @return The freshly initialized and rolled dice array
        */
        protected int[] rollDice() {
            //Generate pseudo-random number for each dice
            int[] d = new int[NUM_DICE];
            for(int i = 0; i < NUM_DICE; i++) {
                Random ran = new Random(); //Random number generator
                int num = ran.nextInt(6) + 1; //Get random number between 1 & 6
                d[i] = num;
            }
            return d;
        }
        
        /**
        * Adds a roll to the list of previous rolls by cloning the dice array.
        * This is necessary since duplicate references in a list will all be
        * edited at the same time no matter which one is being edited.
        */
        protected void addRoll() {
            int[] tmpDice = new int[NUM_DICE];
            System.arraycopy(getDice(), 0, tmpDice, 0, NUM_DICE);
            //tmpDice = getDice().clone();
            prevRolls.add(tmpDice);
        }
        
        /**
        * Rolls the dice and places the new dice in a temporary holder. Then 
        * the dice array swaps out die values that were not kept.
        */
        protected void swapDice() {
            Dice d = new Dice();
            //Only swap values that are not kept (false in the kept array)
            for(int i = 0; i < dice.NUM_DICE; i++) {
                if(!getKeptDie(i)) { setDie(i, d.getDie(i)); }
            }
        }
        
        /**
        * Finds how many of a die number occur in the dice.
        * @param num the die number to count
        * @return The amount of die occurrences
        */
        public int countDiceOfNum(int num) {
            int counter = 0;
            try {
                //Make sure the given parameter is actually a die number
                if(num < DIE_NUM_MIN || num > DIE_NUM_MAX) {
                    throw new InvalidDieNumberException();
                }
                //Go through the dice and add how many there are
                for(int die : getDice()) {
                    if(die == num) { counter++; }
                }
            }
            catch(InvalidDieNumberException e) { }
            return counter;
        }
        
        /**
        * Finds the sum of all the dice's die numbers added together.
        * @return The sum of all the dice
        */
        public int diceSum() {
            int sum = 0;
            for(int i : getDice()) { sum += i; }
            return sum;
        }
        
        /**
        * Transforms the dice array into a String.
        * @return The dice array in String form
        */
        public String toString() {
            String str = "";
            for(int die : getDice()) {
                str += (die + " ");
            }
            return str;
        }
        
        /**
        * Transform the array of currently kept dice into a String.
        * @return The current kept dice in String form
        */
        public String keptToStr() {
            String str = "";
            for(int i = 0; i < NUM_DICE; i++) {
                //Get only the dice that were kept
                if(getKeptDie(i) == true) { str += ((getDie(i)) + " "); }
            }
            return str;
        }
        
        /**
        * Transform the list of previous dice rolls into a String.
        * @return The list of previous rolls in String form
        */
        public String prevRollsToStr() {
            String str = "";
            //Get and number each previous roll
            for(int i = 0; i < getPrevRolls().size(); i++) {
                Dice d = new Dice(getPrevRolls().get(i));
                str += ((i+1) + ".) " + d.toString() + "\n");
            }
            return str;
        }
        
        /**
        * Checks whether the current dice configuration is a Yahtzee.
        * @return True if a Yahtzee. False if not
        */
        public boolean isYahtzee() {
            int diceCount = 0;
            for(int i = DIE_NUM_MIN; i <= DIE_NUM_MAX; i++) {
                if((diceCount = countDiceOfNum(i)) == NUM_DICE) {
                    return true;
                }
            }
            return false;
        }
    }
    
    /**
    * This class records all useful user data over the course of a game. Data
    * recorded is easily accessed and can be easily presented back to the user.
    * The idea was to have game stats ready for the user so they can focus
    * more on the game and not have to worry about the technicalities or
    * recording the stats themselves. The idea was also a way to help the
    * develop bug-test and score-test the logic of the game class.
    */
    public class roundData {
        /** List of all the rolls rolled (in order) in the entire game */
        private List<List<int[]> > allRolls;
        /** String array containing the list of categories picked in order */
        private String[] categoriesPicked;
        /** Int array of all the scores for each round in order */
        private int[] roundScores;
        /** Int array of the number of rolls each round in order */
        private int[] roundRolls;

    //CONSTRUCTOR
    
        /** A basic constructor that initilizes all the data fields. */
        public roundData() {
            setAllRolls();
            setCategoriesPicked();
            setRoundScores();
            setRoundRolls();
        }
    
    //GETS
    
        /**
        * Gets the list of all the rolls in the game.
        * @return A List of List of int arrays (a matrix of int arrays)
        */
        public List<List<int[]> > getAllRolls() {
            return allRolls;
        }
        
        /**
        * Gets the list of a specific round's rolls.
        * @param i The index of the round
        * @return A List of int arrays representing the round's rolls
        */
        public List<int[]> getAllRolls(int i) {
            return allRolls.get(i);
        }
        
        /**
        * Gets the array of categories in the order they were picked.
        * @return The String array carrying the ordered picked categories
        */
        public String[] getCategoriesPicked() {
            return categoriesPicked;
        }
        
        /**
        * Gets the name of specific picked category.
        * @param i The index of the category
        * @return The name of the category picked in String form
        */
        public String getCategoriesPicked(int i) {
            return categoriesPicked[i];
        }
        
        /**
        * Gets the array of all the round's scores in the game
        * @return The int array of round scores
        */
        public int[] getRoundScores() {
            return roundScores;
        }
        
        /**
        * Gets a score from a specific round.
        * @param i The index representing the round
        * @return The score from a round
        */
        public int getRoundScores(int i) {
            return roundScores[i];
        }
        
        /**
        * Gets the array of all the rolls rolled for each round.
        * @return The int array of rolls per round
        */
        public int[] getRoundRolls() {
            return roundRolls;
        }
        
        /**
        * Gets the number of rolls from a specific round.
        * @param i The index representing the round
        * @return The number of rolls in a round
        */
        public int getRoundRolls(int i) {
            return roundRolls[i];
        }
    
    //SETS
        
        /** Sets the List holding every round's rolls to a new. */
        protected void setAllRolls() {
            allRolls = new ArrayList<List<int[]> >();
        }
        
        /** Sets the array holding every category picked to new. */
        protected void setCategoriesPicked() {
            categoriesPicked = new String[YLogic.ROUND_LIMIT];
        }
        
        /**
        * Sets the picked category array to a given array.
        * @param strs The String array to set the picked category array to
        */
        protected void setCategoriesPicked(String strs[]) {
            categoriesPicked = strs;
        }
        
        /**
        * Sets the value of a single picked category to another String.
        * @param idx The round index of where to change the category
        * @param str The String holding the new category name
        */
        protected void setCategoriesPicked(int idx, String str) {
            categoriesPicked[idx] = str;
        }
        
        /** Sets the array holding every round's score to new. */
        protected void setRoundScores() {
            roundScores = new int[YLogic.ROUND_LIMIT];
        }
        
        /**
        * Sets the round scores array to a given array.
        * @param scores The int array set the new scores to
        */
        protected void setRoundScores(int scores[]) {
            roundScores = scores;
        }
        
        /**
        * Sets the value of a single round score to another score.
        * @param idx The round index of where to change the score
        * @param score The new score to replace the old score
        */
        protected void setRoundScores(int idx, int score) {
            roundScores[idx] = score;
        }
        
        /** Sets the array holding every round's amount of rolls to new. */
        protected void setRoundRolls() {
            roundRolls = new int[YLogic.ROUND_LIMIT];
        }
        
        /**
        * Sets the array holding every round's amount of rolls to a given array.
        * @param rolls The int array to set the new rolls to
        */
        protected void setRoundRolls(int rolls[]) {
            roundRolls = rolls;
        }
        
        /**
        * Sets the value of a single round amount of rolls to another int.
        * @param idx The round index of where to change the round rolls
        * @param roll The new amount of rolls to replace the old amount
        */
        protected void setRoundRolls(int idx, int roll) {
            roundRolls[idx] = roll;
        }
    
    //METHODS
        
        /**
        * Adds a List of int arrays to the list of all rolls in the game
        * @param roundRolls A List of int arrays representing a round's rolls
        */
        public void addRoundRolls(List<int[]> roundRolls) {
            allRolls.add(roundRolls);
        }
    }
    
//CONSTRUCTORS

    /**
    * Constructs the game logic class object by initializing all variables to
    * a pre-game state. The game will need to be told to start.
    */
    public YLogic() {
        dice = new Dice();
        rd = new roundData();
        setScore();
        setCatPicked();
        setRollNum(1);
        setRoundNum(1);
        setTotalRolls(1);
        setYahtzeeCount(0);
        setGameInPrg(false);
        setPlayerKept(false);
    }
    
    /** 
    * Constructs the game from a starting dice roll. Will still initialize
    * all remaing variables but will put the game in a game-ready state.
    * @param d The dice array to start the game off with
    */
    public YLogic(int d[]) {
        dice = new Dice(d);
        setScore();
        setCatPicked();
        setRollNum(1);
        setRoundNum(1);
        setTotalRolls(1);
        setYahtzeeCount(0);
        setGameInPrg(true);
        setPlayerKept(false);
    }
    
//GETS

    /**
    * Gets the array of scores ordered by category.
    * @return The array of category scores
    */
    public int[] getScore() {
        return score;
    }
    
    /**
    * Gets the value of a specific category's score.
    * @param i The index of the category to get the score from
    * @return The category's score
    */
    public int getCatScore(int i) {
        return score[i];
    }
    
    /**
    * Gets the current round number.
    * @return The round number
    */
    public int getRoundNum() {
        return roundNum;
    }
    
    /**
    * Gets the number of rolls rolled this round.
    * @return The roll number
    */
    public int getRollNum() {
        return rollNum;
    }
    
    /**
    * Gets the total amount of rolls rolled in the game.
    * @return The total of rolls
    */
    public int getTotalRolls() {
        return totalRolls;
    }
    
    /**
    * Gets the number of *official* Yahtzees rolled.
    * @return The number of Yahtzees
    */
    public int getYahtzeeCount() {
        return yahtzeeCount;
    }
    
    /**
    * Gets the boolean representing the current state of the game.
    * @return True if the game is in progress. False if not
    */
    public boolean getGameInPrg() {
        return gameInPrg;
    }
    
    /**
    * Gets the boolean representing whether the player picked dice to keep.
    * @return True if the player kept. False if not
    */
    public boolean getPlayerKept() {
        return playerKept;
    }
    
    /**
    * Gets the boolean array of categories that were picked by the user.
    * @return The array of categories picked
    */
    public boolean[] getCatPicked() {
        return catPicked;
    }
    
    /**
    * Gets the state of a single category being whether it was picked or not.
    * @param i The index of the category to get the picked state from
    * @return True if the category was picked. False if not
    */
    public boolean getCatPicked(int i) {
        return catPicked[i];
    }
    
    /**
    * Gets the String name of a given category index.
    * @param i The index of the category to get the name from
    * @return The name of the category in String form
    */
    public String getCatName(int i) {
        for(Categories cat : c.values()) {
            if(cat.value() == i) {
                return cat.name();
            }
        }
        return "";
    }
    
//SETS

    /** Sets the array holding each category's score to new. */
    public void setScore() {
        score = new int[ROUND_LIMIT];
    }
    
    /** 
    * Sets the array holding each category's score to a given array.
    * @param s Array of new scores to set the old scores to
    */
    public void setScore(int s[]) {
        //Make sure the score array is initialized
        if(score == null) { setScore(); }
        try {
            //Make sure the new array is the right length
            if(s.length != ROUND_LIMIT) {
                throw new InvalidScoreCardSizeException();
            }
            else { //Set each category score indvidually
                for(int i = 0; i < ROUND_LIMIT; i++) {
                    setCatScore(i, s[i]);
                }
            }
        }
        catch(InvalidScoreCardSizeException e) { }
    }
    
    /** 
    * Sets a specific category's score to a new score.
    * @param cat the index for the category
    * @param num the new score for the category
    */
    public void setCatScore(int cat, int num) {
        score[cat] = num;
    }
    
    /** 
    * Sets the rolls rolled this round to a new given amount. The new number
    * will be forced to be non-negative and less than {@value #ROLL_LIMIT}.
    * @param roll New rolls rolled for this round
    */
    public void setRollNum(int roll) {
        rollNum = (roll < 0) ? 0 : roll;
        rollNum = (roll > ROLL_LIMIT) ? ROLL_LIMIT : roll;
    }
    
    /** 
    * Sets the current round number to a new given amount. The new number
    * will be forced to be non-negative.
    * @param round New round number
    */
    public void setRoundNum(int round) {
        roundNum = (round < 0) ? 0 : round;
    }
    
    /** 
    * Sets the rolls rolled this round to a new given amount. The new number
    * will be forced to be non-negative and less than {@value #ROLL_LIMIT}.
    * @param total New rolls rolled for this round
    */
    public void setTotalRolls(int total) {
        totalRolls = total;
    }
    
    /** 
    * Sets the amount of *official* Yahtzees.
    * @param num New number of Yahtzees
    */
    public void setYahtzeeCount(int num) {
        yahtzeeCount = num;
    }
    
    /** 
    * Sets the state of the game to in progress or not.
    * @param b True for game in progress. False if not
    */
    public void setGameInPrg(boolean b) {
        gameInPrg = b;
    }
    
    /** 
    * Sets the player kept state to true or false.
    * @param b True for the player kept. False if not
    */
    public void setPlayerKept(boolean b) {
        playerKept = b;
    }
    
    /** Sets the array holding each category's picked state to new. */
    public void setCatPicked() {
        catPicked = new boolean[ROUND_LIMIT];
    }
    
    /** 
    * Sets the array holding each category's picked state to a given array.
    * @param b Array of new picked states to set the old states to
    */
    public void setCatPicked(boolean b[]) {
        //Make sure category picked array is initialized first
        if(catPicked == null) { setCatPicked(); }
        try {
            //Make sure new array is the correct length
            if(b.length != ROUND_LIMIT) {
                throw new InvalidScoreCardSizeException();
            }
            else { //Set each category individually
                for(int i = 0; i < ROUND_LIMIT; i++) {
                    setCatPicked(i, b[i]);
                }
            }
        }
        catch(InvalidScoreCardSizeException e) { }
    }
    
    /** 
    * Sets a specific category's picked state to a new state.
    * @param cat the index for the category
    * @param b True for the category is picked. False if not
    */
    public void setCatPicked(int cat, boolean b) {
        catPicked[cat] = b;
    }
    
//METHODS

    /**
    * Represents the player's choice to roll the dice during a round. Will
    * swap the dice with a new roll, keeping any dice the user said to. Will
    * increment the number of rolls and total rolls. Adds the new roll to the
    * list of previous rolls, and last changes the player kept state to false.
    * The change in player state is done as a saftey precaution so the user
    * does not mistakingly roll without keeping dice next roll.
    */
    public void playerRoll() {
        dice.swapDice();
        setRollNum(getRollNum()+1);
        setTotalRolls(getTotalRolls()+1);
        dice.addRoll();
        setPlayerKept(false);
    }
    
    /**
    * Represents the end of a round in the game. The list of previous rolls will
    * be added to the list of all rolls, then cleared, along with the player
    * kept dice. The dice will be set to a freshly rolled dice array and placed 
    * in the newly empty list of previous rolls. The roll number will be set 
    * back to one and the total rolls and round number will both be incremented.
    */
    public void endRound() {
        rd.setRoundRolls(getRoundNum()-1, getRollNum());
        //Need a new variable reference, cannot use one already in the list
        List<int[]> tmp = new ArrayList<int[]>(dice.getPrevRolls());
        rd.addRoundRolls(tmp);
        dice.setDice(dice.rollDice());
        setRollNum(1); //First roll of the new round
        setTotalRolls(getTotalRolls()+1); //New roll of the round: add it
        setRoundNum(getRoundNum()+1); //Go to next round
        dice.setKeptDice();
        dice.setPrevRolls();
        dice.addRoll();
    }            
    
    /**
    * Find the scores of each and every category depending of the current dice
    * configuration. Will give the scores pack in array form.
    * @return Array of scores for the current dice
    */
    public int[] findDiceScores() {
        int scoreArr[] = new int[ROUND_LIMIT];
        List<Integer> diceCount = new ArrayList<Integer>();
        //UPPER SECTION
        for(int i = 0; i < dice.NUM_DICE; i++) {
            scoreArr[dice.getDie(i)-1] += dice.getDie(i);
        }       
        //LOWER SECTION - OF A KIND & YAHTZEE
        for(int i = dice.DIE_NUM_MIN; i <= dice.DIE_NUM_MAX; i++) {
            diceCount.add(dice.countDiceOfNum(i));
            //If there is 3 of the same die face number : Three of a kind
            if((diceCount.get(i-1) >= 3)) {
                scoreArr[c.THREE_OF_A_KIND.value()] = dice.diceSum();
            }
            //If there is 4 of the same die face number : Four of a kind
            if((diceCount.get(i-1) >= 4)) {
                scoreArr[c.FOUR_OF_A_KIND.value()] = dice.diceSum();
            }
            //If there is 4 of the same die face number : Yahtzee
            if(diceCount.get(i-1) >= 5) {
                scoreArr[c.YAHTZEE.value()] = sc.YAHTZEE.value();
            }
        }
        //LOWER SECTION - FULL HOUSE (3 of one die number, 2 of another)
        //Joker rule overrides previous rule
        if((diceCount.contains(2) && diceCount.contains(3)) || (checkJokerRule())) {
            scoreArr[c.FULL_HOUSE.value()] = sc.FULL_HOUSE.value();
        }
        //LOWER SECTION - STRAIGHTS (sequential dice i.e. 1,2,3,4,5; etc.)
        //Joker rule overrides previous rule
        int counter = findStraight(diceCount);
        if((counter >= 4) || (checkJokerRule())) { 
            scoreArr[c.SMALL_STRAIGHT.value()] = sc.SMALL_STRAIGHT.value(); 
        }
        if((counter == 5) || (checkJokerRule())) { 
            scoreArr[c.LARGE_STRAIGHT.value()] = sc.LARGE_STRAIGHT.value();; 
        } 
        //LOWER SECTION - CHANCE (any combination)
        scoreArr[c.CHANCE.value()] = dice.diceSum();
        
        return scoreArr;
    }
    
    /**
    * Checks whether the conditions are met for the Joker Rule to be used.
    * According to the Joker Rule: if the Yahtzee category has been picked and
    * the player rolls another Yahtzee, the Yahtzee may be used as a full house,
    * small straight, or large straight if the corresponding upper section has
    * already been filled. Note: Score does not matter for the Yahtzee category.
    * @return True if the Joker Rule can be used. False if not
    */
    public boolean checkJokerRule() {
        //Dice must be a Yahtzee and the Yahtzee category must be filled
        //Does not matter what the score is for the Yahtzee category.
        if(dice.isYahtzee() && getCatPicked(c.YAHTZEE.value())) {
            //Might as well get the first one because they are all the same
            //If that category is picked Joker Rule applies
            if(getCatPicked(dice.getDie(0)-1)) { return true; }
        }
        return false;
    }
    
    /**
    * Checks whether the Yahtzee count can be incremented. If it can be
    * incremented, do it. If not do not do anything. Will only be incremented
    * If the Yahtzee category was picked with a non-zero score.
    */
    public void incYahtzeeCount() {
        if((!getCatPicked(c.YAHTZEE.value())) 
            || (getCatScore(c.YAHTZEE.value()) != 0)) {
            setYahtzeeCount(getYahtzeeCount()+1);
        }
    }
    
    /**
    * Calculates the total score of the upper section. Upper bonus is not added.
    * @return The total score of the upper section without bonus
    */
    public int upperTotal() {
        int sum = 0;
        //Upper section matches the die face numbers minus one
        for(int i = 0; i < dice.DIE_NUM_MAX; i++) {
            if(catPicked[i]) {
                sum += score[i];
            }
        }
        return sum;
    }
    
    /**
    * Calculates the upper section bonus. 
    * @return The upper section bonus
    */
    public int upperBonus() {
        //Upper bonus is 0 unless the upper Total is greater than 63
        if(upperTotal() > 63) { return sc.UPPER_BONUS.value(); }
        else { return 0; }
    }
    
    /**
    * Calculates the total score of the lower section. Lower bonus is not added.
    * @return The total score of the lower section without bonus
    */
    public int lowerTotal() {
        int sum = 0;
        //Lower section matches last die face number to the number of categories
        for(int i = dice.DIE_NUM_MAX; i < ROUND_LIMIT; i++) {
            if(catPicked[i]) {
                sum += score[i];
            }
        }
        return sum;
    }
    
    /**
    * Calculates the lower section bonus. 
    * @return The lower section bonus
    */
    public int lowerBonus() {
        //Lower bonus is 100 for every Yahtzee used after the Yahtzee category
        //was filled with a non-zero score
        if(getYahtzeeCount() > 1) { 
            return((getYahtzeeCount()-1) * sc.LOWER_BONUS.value()); 
        }
        else { return 0; }
    }
    
    /**
    * Calculates the grand total of the whole game. Will be the sum of the
    * upper total and bonus plus the sum of the lower total and bonus.
    * @return The grand total score of the game
    */
    public int grandTotal() {
        return(upperTotal() + upperBonus() + lowerTotal() + lowerBonus());
    }
    
    /**
    * Checks for sequential dice in the current dice configuration.
    * @param diceCount List of the number of occurrences for each die number
    * @return The number of sequential dice (only 3 or 4 are significant)
    */
    private int findStraight(List<Integer> diceCount) {
        int counter = 0;
        for(Iterator<Integer> i = diceCount.iterator(); i.hasNext();) {
            int num = i.next();
            //Make sure there is only between 1 and 2 dice of that number
            if(num > 0 && num < 3) { counter++; }
            //If the counter is less than 2, there's still a chance
            else if(counter < 2) { counter = 0; }
            //Else leave as there's no chance for a sequential category
            //Or have have already met the requirements for one
            else { return counter; }
        }
        return counter;
    }
}
