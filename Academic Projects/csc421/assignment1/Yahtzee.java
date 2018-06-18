/* JavaDoc Link: http://csitrd.kutztown.edu/~ccarr419/csc421/assignment1/ */
import java.util.*;
import java.io.*;

/**
<h1>CSC421 Web-Based Design: Assignment #1</h1>
<table>
   <caption></caption>
   <tr>
      <th>Author:</th>
      <td>Christian Carreras</td>
   </tr>
   <tr>
      <th>Major:</th>
      <td>CSC Masters Software Development</td>
   </tr>
   <tr>
      <th>Creation Date:</th>
      <td>09/12/2017</td>
   </tr>
   <tr>
      <th>Due Date:</th>
      <td>09/22/2017</td>
   </tr>
   <tr>
      <th>School:</th>
      <td>Kutztown University of Pennsylvania</td>
   </tr>
   <tr>
      <th>Course:</th>
      <td>CSC 421 Web-Based Programming</td>
   </tr>
   <tr>
      <th>Professor Name:</th>
      <td>Dr. Dylan Schwesinger</td>
   </tr>
   <tr>
      <th>Assignment:</th>
      <td>#1</td>
   </tr>
   <tr>
      <th>Filename:</th>
      <td>a1.java</td>
   </tr>
   <tr>
      <th style="vertical-align:top">Purpose:</th>
      <td>To partially implement a text-based version of the  game of Yahtzee.
         This project<br> will implement a one player version of the game that 
         plays a single round of Yahtzee.
      </td>
   </tr>
</table>
<h1>Help</h1>
<p>Commands and project design decisions can be found in the 
<a href="http://csitrd.kutztown.edu/~ccarr419/csc421/assignment1/README.txt" 
   target="_blank">readme</a>.<br>
Categories for Yahtzee can be found 
<a href="http://csitrd.kutztown.edu/~ccarr419/csc421/assignment1/CATEGORIES.txt"
   target="_blank">here</a>.<br>
Official rules to Yahtzee can be found
<a href="https://www.hasbro.com/common/instruct/Yahtzee.pdf" target="_blank">
   here</a>.</p>
*/
public class Yahtzee {
   /** Number of dice allowed in the game */
   public static final int NUMDICE = 5;
   /** Number of rolls allowed per round */
   public static final int NUMROLLS = 3;
   /** User command to display the help page */
   public static final String COMMAND_HELP = "help";
   /** User command to start or restart the game */
   public static final String COMMAND_START = "start";
   /** User command to display current game statistics */
   public static final String COMMAND_STATUS = "stats";
   /** User command to display global game statistics */
   public static final String COMMAND_GLOBST = "gstat";
   /** User command to print the current roll */
   public static final String COMMAND_PRINTD = "pdice";
   /** User command to roll the dice */
   public static final String COMMAND_ROLL = "roll";
   /** User command select dice to keep from the current roll */
   public static final String COMMAND_KEEP = "keep";
   /** User command to display all categories in the game */
   public static final String COMMAND_CATEGOR = "cat";
   /** User command to display all available categories with the current roll */
   public static final String COMMAND_AVAILCT = "acat";
   /** User command to pick a category currently avaiable to them */
   public static final String COMMAND_PICKCAT = "pcat";
   /** User command to quit the game */
   public static final String COMMAND_QUIT = "quit";
   /** File that contains list of commands and design choices
   * @see <a href=
      "http://csitrd.kutztown.edu/~ccarr419/csc421/assignment1/README.txt"
      target="_blank">README.txt</a>
   */
   public static final File helpFile = new File("README.txt");
   /** File that contains list all available categories to choose from 
   * @see <a href=
      "http://csitrd.kutztown.edu/~ccarr419/csc421/assignment1/CATEGORIES.txt"
      target="_blank">CATEGORIES.txt</a>
   */
   public static final File catFile = new File("CATEGORIES.txt");
   /** Data file that stores game information for reading and writing */
   public static final File logFile = new File("log.dat");
   /** Reads user input from {@code System.in} */
   public static Scanner scan = new Scanner(System.in);
   
   /**
   * Main method to the Yahtzee program. Starts the game normally or from the
   * command-line.
   * @param args String array of command-line arguments
   */
   public static void main(String[] args) {
      //Make an array to hold command-line input if present
      int[] clDice = new int[NUMDICE];
      //Check to see if command-line arguments match the required format
      if((checkClArgs(args, clDice)) == true) {
         beginGame(clDice); //start game with command-line dice
         playerPrompt(clDice, true, 1);
      }
      //There is no command-line input or incorrect command-line format
      else {
         printIntroTag(); //Show welcome tag for basic game information
         playerPrompt(null, false, 0);
      }
   }
   
   /**
   * Checks command-line input for correct format. Correct format dictates
   * that there must be {@value #NUMDICE} integers separated by a space.
   * Integers must be in the range of one to six.
   * @param args The list of command-line arguments if present
   * @param clDice Int array to return the command-line dice if applicable
   * @return True if correct command-line format. False if not.
   * @exception NumberFormatException Non-numeric data
   */ 
   public static boolean checkClArgs(String[] args, int clDice[]) {
      //Check if there is no command-line arguments
      if(args.length == 0) { return false; }
      //If there is command-line arguments, make sure there are exactly NUMDICE
      else if(args.length == NUMDICE) {
         for(int i = 0; i < NUMDICE; i++) {
            try { //Try to turn command-line arugments into integers
               clDice[i] = Integer.parseInt(args[i]);
               //Make sure entered integers are dice face values (1-6)
               if(clDice[i] < 1 || clDice[i] > 6) {
                  System.out.println("Error: bad command-line arguments.");
                  System.out.println("Initializing normal game start sequence.");
                  return false;
               }
            }
            //The user entered something other than integers
            catch(NumberFormatException e) {
               System.out.println("Error: bad command-line arguments.");
               System.out.println("Initializing normal game start sequence.");
               return false;
            }   
         }
         return true; //Correct command-line input
      }
      else { //Too many or too few command-line arguments
         System.out.println("Error: invalid number of command-line arguments.");
         System.out.println("Initializing normal game start sequence.");
         return false;
      }
   }
   
   /**
   * Handles all user input commands and links them to their corresponding
   * fucntions. Prompt will continue until program termination (quit).
   * @param clDice Command-line entered dice if applicable
   * @param start Used to signify whether to start the game initially
   * @param rnd Used to set the initial roll number
   */
   public static void playerPrompt(int[] clDice, boolean start, int rnd) {
      boolean gameInPrg = start, plKept = false;
      int rollNum = rnd;
      int[] dice = clDice;
      List<int[]> prevRolls = new ArrayList<int[]>();
      boolean[] keptDice = new boolean[NUMDICE];
      
      //Check if command-line dice were entered, if so add to previous rolls
      if(dice != null) { addRoll(dice, prevRolls); }
      
      //Loop until user quits
      while(true) { 
         //Check if the game has reached the end of the round
         //Set gameInPrg to false if the end of round, true otherwise
         gameInPrg = chkEndRnd(dice, prevRolls, keptDice, gameInPrg, rollNum);
         //Set current roll to zero if the game is not in progress
         rollNum = (gameInPrg) ? rollNum : 0; 

         System.out.print("> ");
         String command = scan.next();
         //Handle user input and link commands to functions
         switch(command.toLowerCase()) {   
            case COMMAND_HELP: //show help page
               printList(parseFile(helpFile));
               break;
            case COMMAND_START: //start/restart game
               dice = beginGame(null);
               gameInPrg = init(dice, prevRolls, keptDice);
               rollNum = 1;
               break;
            case COMMAND_STATUS: //show current game stats if game in progress
               if(!prgErr(gameInPrg, "Cannot show game status.")) { }
               else { playerStats(prevRolls, dice, keptDice, rollNum); }
               break; 
            case COMMAND_GLOBST: //show game global stats
               printGlobStats();
               break;
            case COMMAND_PRINTD: //print current dice if game in progress
               if(!prgErr(gameInPrg, "Cannot print dice.")) { }
               else {
                  System.out.print(translateToImage(dice));
                  System.out.println("Current roll: " + printDice(dice)); }
               break; 
            case COMMAND_ROLL: //roll dice if game in progress
               if(!prgErr(gameInPrg, "Cannot roll dice.")) { }
               else { if(playerRoll(dice, keptDice, plKept)) {
                  plKept = nextRoll(dice, prevRolls, keptDice, ++rollNum); } }
               break;           
            case COMMAND_KEEP: //keep user-specified dice if game in progress
               if(!prgErr(gameInPrg, "Cannot pick dice to keep.")) { }
               else { keptDice = keepDice(dice); plKept = true; }
               break;             
            case COMMAND_CATEGOR: //show all categories in the game
               printList(parseFile(catFile));
               break;      
            case COMMAND_AVAILCT: //show all available categories during a game
               if(!prgErr(gameInPrg, "Cannot show available categories.")) { }
               else { printNumberedList(availCategor(dice)); }
               break;  
            case COMMAND_PICKCAT: //pick an avaiable category during a game
               if(!prgErr(gameInPrg, "Cannot pick category.")) { }
               else { if(pickCategory(dice, rollNum)) { gameInPrg = false; } }
               break;   
            case COMMAND_QUIT: //quit the game and terminate the program
               System.out.println("Goodbye.");
               System.exit(0);
               break; 
            default: //state the the entered String is not a command
               System.out.println("Error: '" + command + 
                  "' is not an internal command.");
         }
      }
   }
   
   /**
   * Sets all necessary data objects to their initial empty state and adds the  
   * current dice roll to the list of previous rolls.
   * @param dice Integer array that holds the current roll
   * @param rolls A list of int arrays containing all previous rolls
   * @param kept Boolean array that that tells which dice are kept
   * @return Always true to signify start of game
   */
   public static boolean init(int dice[], List<int[]> rolls, boolean kept[]) {
      for(int i = 0; i < NUMDICE; i++) { kept[i] = false; }
      rolls.clear();
      addRoll(dice, rolls);
      return true;
   }
   
   /**
   * Checks if the game has reached the end of the round i.e. the number of
   * rolls equals {@value #NUMROLLS} or the user picked a category.
   * @param dice Integer array that holds the current roll
   * @param rolls A list of int arrays containing all previous rolls
   * @param kept Boolean array that that tells which dice are kept
   * @param gPrg Boolean which states whether the game is currently in progress
   * @param rollNum How many rolls the user has currently rolled
   * @return True if the game has reached the end of the round. False if not.
   */
   public static boolean chkEndRnd(int dice[], List<int[]> rolls,
      boolean kept[], boolean gPrg, int rollNum) {
      if(rollNum >= NUMROLLS || !gPrg) {
         //Player ran out of rolls
         if(gPrg) { pickCategory(dice, rollNum); }
         //Player ran out of rolls or picked a category early
         if(rollNum > 0) { 
            System.out.println("\nROUND OVER");
            playerStats(rolls, dice, kept, rollNum);
         }
         System.out.println("\nType 'start' to play.\n");
         return false; //Game not in progress
      }
      return true; //Game still in progress
   }
   
   /**
   * Begins the game by printing the global stats compiled from the games
   * before, rolling the dice and printing said dice to the screen. Checks if
   * dice is set before rolling the dice.
   * @param d Int array that will hold the first roll of the dice
   * @return The freshly rolled dice if d was not set. Returns d if d is set.
   */
   public static int[] beginGame(int d[]) {
      System.out.println("\nLet's Play!");
      printGlobStats();
      int[] dice = new int[NUMDICE];
      if(d != null) { dice = d; } //Check if d is already set
      else { dice = rollDice(); } //Otherwise roll the dice
      System.out.println("\nRoll #1");
      System.out.print(translateToImage(dice));
      System.out.println("Current roll: " + printDice(dice));
      return dice;
   }
   
   /**
   * If the game is not in progress this will print an error message to screen.
   * @param gPrg Boolean that tells if the game is in progress or not
   * @param str String to add to the "Game not in progress." error message
   * @return gPrg: in order be able to place this function in an if statement
   */
   public static boolean prgErr(boolean gPrg, String str) {
      if(!gPrg) { System.out.println("Game not in progress. " + str); }
      return gPrg;
   }
   
   /**
   * Shows the current statistics of the user's current round. Will show the
   * number of rolls rolled, current dice rolled, current kept dice if
   * applicable and all previous rolls including the current roll.
   * @param rolls A list of int arrays containing all previous rolls
   * @param dice Integer array that holds the current roll
   * @param kept Boolean array that that tells which dice are kept
   * @param round the number of rolls rolled by the user
   */
   public static void playerStats(List<int[]> rolls, int dice[], 
      boolean kept[], int round) {
      System.out.println("\nNumber of Rolls: " + round);
      System.out.println("Current Dice: " + printDice(dice));
      System.out.print("Current Kept Dice: ");
      printKeptDice(dice, kept);
      System.out.println("\nPrevious Rolls:");
      for(int i = 0; i < rolls.size(); i++) {
         System.out.println((i+1) + ".) " + printDice(rolls.get(i)));
      }
   }
   
   /**
   * Logs the results of each round of the game to the log file.
   * Information logged to the file include six integers: five corresponding
   * to the current dice at round end and the last to represent how many rolls
   * were rolled. The last bit of information is a String which stores what
   * category the user picked at round end.
   * @param dice Integer array that holds the current roll
   * @param category The category picked by the user
   * @param roll Number of rolls rolled by the user
   */
   public static void logStats(int dice[], String category, int roll) { 
      try {
         DataOutputStream out = new DataOutputStream(
            new FileOutputStream(logFile, true));
         //Write the dice integers to file separated by space
         for(int i = 0; i < NUMDICE; i++) {
            out.writeInt(dice[i]);
            out.write(" ".getBytes());
         }
         //Write number of rolls and category picked
         out.writeInt(roll);
         out.write(" ".getBytes());
         out.write(category.getBytes());
         out.write("\n".getBytes());
         out.close(); //Be a good samaritan and close the file
      }
      //Catch for write errors
      catch(IOException e) { e.printStackTrace(); }
   }
   
   /**
   * Prints information from the log file to the screen. Information
   * printed includes number of rounds played by any user and the average
   * amount of rolls per round. Checks to see if the log file exists
   * first. If the file does not exist tell the user they are first to play.
   */
   public static void printGlobStats() {
      //Check if file exists before reading from it
      if(logFile.exists()) {
         System.out.println("");
         System.out.println("A total of " + findGlobRounds() + 
            " rounds have been played.");
         System.out.println("Each round averaged " + findGlobAvg() + 
            " rolls long.");
      }
      //If the file does not exist then this user is the first to play
      else { System.out.println("You are the first to play!"); }
   }
   
   /**
   * Finds the average number of rolls per round for each round logged into
   * the data log file. Assumes the log file exists.
   * @return The average rolls for each round played and logged
   */
   public static float findGlobAvg() {
      byte[] bArr = getFileBytes(logFile); //File returns bytes
      int count = 0;
      float sum = 0, num = 0;
      //Find all numbers between one an six. That will help locate the number
      //of rounds in the file because it will always be the sixth integer in
      //each series of six numbers between one and six.
      for(int i = 0; i < bArr.length; i++) { 
         if(bArr[i] > 0 && bArr[i] <= 6) { //Important numbers are only 1-6
            if(++count == 6) { //Rolls will always be the sixth number
               count = 0;
               sum += bArr[i];
               num++;
            }
         }
      }
      return(sum / num); //return the average
   }
   
   /**
   * Finds the total number of rounds played by any user logged into the
   * data log file. Assumes the log file exists.
   * @return The total number of rounds played by any user
   */
   public static int findGlobRounds() {
      byte[] bArr = getFileBytes(logFile); //File returns bytes
      String str = new String(bArr);
      int count = 0;
      //Look for the new line character, this will equal the number of rounds
      for(int i = 0; i < str.length(); i++) {
         if(str.charAt(i) == '\n') { count++; }
      }
      return count;
   }
   
   /**
   * Get all the bytes contained within a file. If the file does not exist,
   * print the stack trace and terminate the program.
   * @param file The file to open and get the bytes from
   * @return The byte array which contains all the bytes from the file
   */
   public static byte[] getFileBytes(File file) {
      try {
         //The method read only returns bytes
         FileInputStream input = new FileInputStream(file);
         byte[] bArr = new byte[(int)file.length()];
         input.read(bArr);
         input.close(); //Be a good samaritan and close the file
         return bArr;
      }
      //File does not exist or some other related error
      catch(IOException e) { e.printStackTrace(); }
      return null;
   }
   
   /**
   * Compiles a list of categories available to user at the moment of this
   * method call. Calls helper functions to separate the lower/upper sections.
   * @param dice Integer array that holds the current roll
   * @return List of Strings which holds all available categories
   * @see #catUpperSectHelper
   * @see #catLowerSectHelper
   */
   public static List<String> availCategor(int dice[]) {
      List<String> catList = new ArrayList<String>();
      catUpperSectHelper(dice, catList); //Check upper section categories
      catLowerSectHelper(dice, catList); //Check lower section categories
      catList.add("Chance"); //This catgegory will always show
      return catList;
   }
   
   /**
   * Adds to the list of categories by checking if the current dice fufill
   * the prerequisites of each upper section categories. The upper section
   * represents categories that only require a minimum of one dice of the
   * matching number in order to be fulfilled. Helps {@link availCategor}.
   * @param dice Integer array that holds the current roll
   * @param catList List of Strings to add categories to
   */
   public static void catUpperSectHelper(int dice[], List<String> catList) {
      //Add category to list if one dice matches the category and the
      //category is not in the list already
      for(int i = 0; i < NUMDICE; i++) {
         if(dice[i] == 1) { addUnique(catList, "Aces"); }
         else if(dice[i] == 2) { addUnique(catList, "Twos"); }
         else if(dice[i] == 3) { addUnique(catList, "Threes"); }
         else if(dice[i] == 4) { addUnique(catList, "Fours"); }
         else if(dice[i] == 5) { addUnique(catList, "Fives"); }
         else { addUnique(catList, "Sixes"); }
      }
   }
   
   /**
   * Adds to the list of categories by checking if the current dice fufill
   * the prerequisites of each lower section categories. The lower section
   * represents categories that are special configurations of the dice
   * including three dice the same, four dice the same, all five dice the same,
   * three dice the same of one number and two the same of another, four
   * sequential dice and five sequential dice. Helps {@link availCategor}.
   * @param dice Integer array that holds the current roll
   * @param catList List of Strings to add categories to
   */
   public static void catLowerSectHelper(int dice[], List<String> catList) {
      int counter = 0;
      List<Integer> diceCount = new ArrayList<Integer>();
      //Compile a list of integers which signify each dice and their
      //number of occurances in the roll
      for(int i = 1; i <= 6; i++) { diceCount.add(countDice(dice, i)); }
      //Check for multiples of the same dice for "of a kind" categories
      for(int i = 0; i < diceCount.size(); i++) { 
         if(diceCount.get(i) >= 3) { catList.add("Three of a Kind"); }
         if(diceCount.get(i) >= 4) { catList.add("Four of a Kind"); }
         if(diceCount.get(i) == 5) { catList.add("Yahtzee"); }
      }
      //Check for two of one dice the same and three of another the same
      if(diceCount.contains(2) && diceCount.contains(3)) {
         catList.add("Full House"); }
      
      //Count the number of sequential dice by checking how many ones
      //or twos are next to each other
      for(Iterator<Integer> i = diceCount.iterator(); i.hasNext();) {
         int num = i.next();
         //Make sure there is only between 1 and 2 dice of that number
         if(num > 0 && num < 3) { counter++; }
         //If the counter is less than 2, there's still a chance
         else if(counter < 2) { counter = 0; }
         //Else leave as there's no chance for a sequential category
         //Or have have already met the requirements for one
         else { break; }
      }
      //Sequential dice categories
      if(counter >= 4) { catList.add("Small Straight"); }
      if(counter == 5) { catList.add("Large Straight"); }
   }
   
   /**
   * Allows the user to pick a category from the currently available categories.
   * Choosing a category will end the round and log the results of the round
   * to the data file. Player may exit from making a choice by entering zero.
   * @param dice Integer array that holds the current roll
   * @param roll Number of rolls rolled by the user
   * @return True if a category was picked. False if one was not picked.
   * @exception NumberFormatException User entered non-numeric input
   */
   public static boolean pickCategory(int dice[], int roll) {
      List<String> categories = availCategor(dice);
      System.out.println("Select a category by entering the number before " +
         "it.\nOR enter zero to exit if it is not the last roll.");
      //Print a numbered list of available categories
      printNumberedList(categories);     
      do {
         System.out.print("Enter a number between 1 and " + 
            categories.size() + ": ");
         String command = scan.next();
         try {
            int choice = Integer.parseInt(command);
            //Check if the number entered was in range of options
            if(choice >= 1 && choice <= categories.size()) {
               System.out.println("You picked: " + categories.get(choice-1));
               logStats(dice, categories.get(choice-1), roll);
               return true;
            }
            //Zero represents the exit command, exit back to game if entered
            else if(choice == 0) {
               //Make sure it is not the last round, the user must pick a
               //category if that is the case
               if(roll >= NUMROLLS) {
                  System.out.println("Cannot exit on last roll.");
               }
               else {
                  System.out.println("No category picked. Returning.");
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
   * Counts the number of dice that appear in the current roll that match
   * the given parameter number.
   * @param dice Integer array that holds the current roll
   * @param num The number to look for in the current roll
   * @return The number of dice that exist in the roll with that number
   */
   public static int countDice(int dice[], int num) {
      int counter = 0;
      for(int i = 0; i < NUMDICE; i++) {
         if(dice[i] == num) { counter++; }
      }
      return counter;
   }
   
   /**
   * Checks to see if there is an entry that matches the given String within
   * the list already. If no such entry exists, add the String to the list.
   * @param list List to add to and search for duplicate
   * @param str String to seach for within the list and add if it is unique
   */
   public static void addUnique(List<String> list, String str) {
      if(list.contains(str)) { return; }
      else { list.add(str); }
   }
   
   /**
   * Parses a file and splits it into token Strings by line. The strings are 
   * added to a list of Strings and returned once the whole file is parsed.
   * @param file The file to parse
   * @return The list that contains the String tokens
   */
   public static List<String> parseFile(File file) {
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
   * Prints a given list of Strings. Used for printing parsed files.
   * @param list List to print to screen (most likely parsed file)
   */
   public static void printList(List<String> list) {
      System.out.println("");
      for(Iterator<String> i = list.iterator(); i.hasNext();) {
         String word = i.next();
         System.out.print(word); 
      }
   }
   
   /**
   * Prints a list of strings but numbers them according to their order in the
   * list. Each entry is separated by a new-line.
   * @param list List used to print a numbered list
   */
   public static void printNumberedList(List<String> list) {
      int counter = 1;
      System.out.println("");
      for(Iterator<String> i = list.iterator(); i.hasNext();) {
         String category = i.next();
         System.out.println((counter++) + ".) " + category);
      }
   }
   
   /**
   * Method to print a intro tag to welcome the user to the game and inform
   * them of basic game information or anything else helpful.
   */
   public static void printIntroTag() {
      System.out.print("\n" +
         "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n" +
         "* Welcome to Yahtzee!\n*\n" +
         "* Type 'help' for a list of game commands\n*\n" +
         "* Programmed by Christian Carreras\n" +
         "* Yahtzee © 2017 Hasbro, Inc.\n" +
         "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
   }
	
   /**
   * Prints the roll to the screen and adds the roll to the previous rolls list.
   * @param dice Integer array that holds the current roll
   * @param rolls List of previous rolls rolled by the user this round
   * @param kept Boolean list representing what dice the user is keeping
   * @param rnd The current roll the user is on this round
   * @return Always false, signifies the user has not updated their kept dice
   */
   public static boolean nextRoll(int dice[], List<int[]> rolls,
      boolean kept[], int rnd) {
      System.out.println("\nRoll #" + rnd);
      System.out.print(translateToImage(dice)); //Print dice image
      System.out.println("Current roll: " + printDice(dice));
      addRoll(dice, rolls); //Add roll to list of previous rolls
      return false;
   }
   
   /**
   * Method to roll the dice. First checks if the user has recently picked
   * dice to keep from the previous rolls. If the user has not kept any dice
   * a warning will be printed and the user will be asked to continue with the
   * roll. If the user already picked dice to keep, the roll will continue
   * without any warning.
   * @param dice Integer array that holds the current roll
   * @param kept Boolean list representing what dice the user is keeping
   * @param pk Boolean to signify whether the user picked dice to keep or not
   * @return True if the user successfully rolled. False if not.
   */
   public static boolean playerRoll(int dice[], boolean kept[], boolean pk) {
      if(pk == false) {
         System.out.println("");
         //Ask the user if they wish to continue with the roll if they
         //did not keep dice from their previous roll
         if(yesNoPrompt("Are you sure you want to roll " +
            "w/o keeping dice? [y/n]: ")) {
               swapDice(dice, kept); //Only roll the not kept dice if any
               return true;
         }                
         else { //User decided to go back and pick dice to keep
            System.out.println("Aborting roll request."); 
            return false;
         }
      }
      //Player already kept so go through with the roll
      else {
         swapDice(dice, kept); //Only roll the not kept dice if any
         return true;
      }
   }
   
   /**
   * Rolls the dice and places the dice in a temporary holder. Then the actual
   * dice object swaps out dice values that were not kept by the user.
   * @param dice Integer array that holds the current roll
   * @param kept Boolean list representing what dice the user is keeping
   */
   public static void swapDice(int dice[], boolean kept[]) {
      int[] temp = rollDice();
      //Only swap values that are not kept (false in the kept array)
      for(int i = 0; i < NUMDICE; i++) {
         if(!kept[i]) { dice[i] = temp[i]; }
      }
   }  
   
   /**
   * Adds a new roll to the list of previous rolls. This method is necessary
   * because lists in java need to add new values. Adding old values already
   * in the list modifies each one of the values to the newly added value.
   * @param dice Integer array that holds the current roll
   * @param rolls List of previous rolls rolled by the user this round
   */
   public static void addRoll(int dice[], List<int[]> rolls) {
      int[] d = new int[NUMDICE];
      d = dice.clone();
      rolls.add(d);
   }
   
   /**
   * Makes a roll of pseudo-random dice and returns that dice array
   * @return The newly created (rolled) dice array
   */
   public static int[] rollDice() {
      int[] dice = new int[NUMDICE];
      //Generate pseudo-random number for each dice
      for(int i = 0; i < NUMDICE; i++) {
         Random ran = new Random(); //Random number generator
         int num = ran.nextInt(6) + 1; //Generate random number between 1 and 6
         dice[i] = num;
      }
      return dice;
   }
	
   /**
   * Method that allows the user decide what dice they would like to keep. The
   * user will be asked for each dice if they want to keep it or not. After
   * successfully deciding what dice to keep, the kept dice will be printed.
   * @param dice Integer array that holds the current roll
   * @return Boolean array containing which dice are kept and which are not
   */
   public static boolean[] keepDice(int dice[]) {
      boolean[] keptDice = new boolean[NUMDICE];
      //Individually prompt the user to choose if they wish to keep the dice
      for(int i = 0; i < NUMDICE; i++) {
         if(yesNoPrompt("Do you want to keep dice #" + (i + 1) +
            " (" + dice[i] + ")? [y/n]: ")) {
               keptDice[i] = true; //User decided to keep the dice
         }
         else { keptDice[i] = false; } //User decided not to keep
      }
      //Print the dice the user decided to keep
      System.out.print("You kept: ");
      printKeptDice(dice, keptDice);
      return keptDice;
   }
   
   /**
   * Prompts the user with a yes or no question. Changes the input to lower
   * case for maximum compatibility.
   * @param str String for the prompt to print (Should be a yes/no question)
   * @return true if the user entered y (yes). False if the user entered n (no).
   */
   public static boolean yesNoPrompt(String str) {
      String choice = "";
      do { //keep looping until 'y' or 'n' is entered
         System.out.print(str);
         choice = scan.next();
      } while(!choice.toLowerCase().equals("y") && 
         !choice.toLowerCase().equals("n"));
      //If 'y' is entered return true, if 'n' is entered return false
      if(choice.toLowerCase().equals("y")) { return true; }
      else { return false; }
   }   
	
   /**
   * Prints the dice the user has decided to keep to the screen.
   * @param dice Integer array that holds the current roll
   * @param keptDice Boolean list representing what dice the user is keeping
   */
   public static void printKeptDice(int dice[], boolean keptDice[]) {
      for(int i = 0; i < NUMDICE; i++) {
         if(keptDice[i] == true) { System.out.print(dice[i] + " "); }
      }
      System.out.print("\n");
   }
	
   /**
   * Print each dice number separated by a space.
   * @param dice Integer array that holds the current roll
   * @return The String that contains the five dice ints separated by a space
   */
   public static String printDice(int dice[]) {
      String diceStr = "";
      for(int i = 0; i < NUMDICE; i++) {
         diceStr += dice[i];
         diceStr += " ";
      }
      return diceStr;
   }
   
   /**
   * Creates a visible image to the likeness of a dice face. Each dice face
   * will correspond to each number in the roll. Calls a helper function to
   * figure what section of the dice face to print according to what level
   * of the print the method is on. Dice faces are printed horizontally.
   * @param dice Integer array that holds the current roll
   * @return The string containing the dice face images
   * @see #imagerHelper
   */
   public static String translateToImage(int dice[]) {
      //Strings that are used for all combinations of dice faces
      String dTop = " _________ "; //Dice face top
      String none = "|         |"; //Dice face none
      String lOne = "| •       |"; //Dice face one dot left
      String cOne = "|    •    |"; //Dice face one dot center
      String rOne = "|       • |"; //Dice face one dot right
      String both = "| •     • |"; //Dice face two dots (both)
      String dBot = "|_________|"; //Dice face bottom
      String out = "";
      
      //Put Strings that change depending on the dice number inside a map
      //The helper function will help pick the right choice from the map
      Map<Integer, String> map = new HashMap<Integer, String>();
      map.put(0, none);
      map.put(1, lOne);
      map.put(2, cOne);
      map.put(3, rOne);
      map.put(4, both);
      
      //Automatically add the top portion as it is the same for every number
      for(int i = 0; i < NUMDICE-1; i++) { out += dTop + " "; }
      out += dTop + "\n"; //Separate the last one because it needs a new line
      
      //Automatically add the second top portion as it is the same too
      for(int i = 0; i < NUMDICE-1; i++) { out += none + " "; }
      out += none + "\n"; //Separate the last one because it needs a new line
      
      //The next three portions change depending on which dice number it is
      //Call the helper function to get the key of what String to print
      //located within the map
      for(int i = 0; i < 3; i++) { //Three sections of dots
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
      out += dBot + "\n\n";
      
      return out; 
   }
   
   /**
   * Helps the {@link translateToImage} method by returning a key to get the
   * correct portion of the dice face to print according to the number given
   * and the section number.
   * @param num The dice number
   * @param pos The section position number
   * @return The key which is used to access the correct String in a String map
   */
   public static int imagerHelper(int num, int pos) {
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
}
