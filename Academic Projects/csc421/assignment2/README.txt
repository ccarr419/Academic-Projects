* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Yahtzee © 2017 Hasbro, Inc.
* Version 2.0
* Christian Carreras BS Computer Science
* Kutztown University of Pennsylvania
*
* JavaDocs Link:
* http://csitrd.kutztown.edu/~ccarr419/csc421/assignment2/
*
* - - - - - - - - - - MY DESIGN CHOICES - - - - - - - - - -
*
*     For this project I decided to make a command-based
*  version of Yahtzee similar to computer console-like
*  commands. The user is provided with a prompt and can
*  enter commands freely. The user may start and quit the
*  game freely at will as well. To represent the dice I 
*  created a Dice class object that made use of a int array
*  and used a pseudo-random number generator to represent a
*  roll of the dice. The Dice class is nested within the
*  YLogic class which holds the functions that modifies and
*  facilitates all necessary operations for the logic of
*  a game of Yahtzee. Within the YLogic class there is also
*  the nested class called roundData which collects data 
*  from the game as the user plays it. Data from this class
*  is used for the 'gstat' command documented further down
*  the page. The YLogic class also creates two enums to
*  hold game-dependent constants like category indexes and
*  scores for certain categories and bonuses. To display
*  the game properly a separate class was created to
*  represent the interface of the game. This class' sole
*  purpose is to handle the interactions of the player 
*  and the logic of the game. It will only call the 
*  corresponding functions in the logic class depending 
*  on user-input and game status. Lastly the Yahtzee.java 
*  file is used to only call the functions to start the
*  interface, it no longer checks for command-line input.
*  The help page (this page), the categories page, the
*  and the scoresheet page are all read from files located
*  in the folder for easier editing and displaying purposes
*  (plus it cleans up the code!) The exception with the
*  scoresheet is that it is edited at runtime by inserting
*  the player scores into their rightful category. All
*  entered commands are transformed to lower-case for
*  compatibility and error-handling. All non-commands
*  are handled gracefully and returns the player prompt.
*  As a side note: the Yahtzee count variable shown under
*  the 'gstat' command will always show zero if you choose
*  the Yahtzee category with a score of zero. Even if you
*  roll a Yahtzee after the fact. This is completely 
*  intentional as it is necessary in order to calculate
*  the Lower Section bonus in the scoresheet.
*
*  Psst, hey you. Yes you! Want to hear something cool?
*  You didn't hear it from me but.. I heard you can pick
*  your own dice if you wanted to! Just type the magic
*  phrase 'ccc' and you will be able to set the dice
*  to your liking. Pretty cool huh? Just don't expect
*  the data guardians to keep up with your sorcery!
*
* - - - - - - - - - - - - HELP PAGE - - - - - - - - - - - -
*                    GAME INPUT COMMANDS
*
* help   - brings up the help page which displays the
*           complete list of commands that can be used 
*           throughout the game. Can be called at any 
*           point before or during the game.
*
* start  - begin the game with the initial first roll.
*           Can also be called during a game to restart
*           the game from the beginning. A warning prompt
*           will be displayed if this command is called
*           during an active game.
*
* rstat  - shows the current round information including
*           the current round, current roll, current dice,
*           current kept dice, and the dice previously
*           rolled this round. Can only be called during
*           an active game.
*
* gstat  - shows the current game information including
*           the total number of rolls, the number of 
*           Yahtzees rolled, total score, the score for
*           each round, the category picked for every 
*           round, and the dice rolled for each roll in
*           every round. Can only be called during an 
*           active game. Round information will only
*           be displayed if the user has completed one
*           or more rounds.
*
* score  - shows the current player's score sheet. The
*           score sheet can only be viewed during a game.
*           The score sheet will be updated after every
*           round. Categories left blank are categories
*           not picked yet. Totals and bonuses are
*           calculated regardless of what categories
*           are picked or not picked.
*
* pdice  - prints the current rolled dice in both dice
*           and numeric form. Can only be called
*           during a game in progress.
*
* roll   - continues the round by rolling the dice again.
*           A player will only be able to use this
*           command if a game is in progress i.e.
*           the game has started and the player has
*           not exceeded the number of allotted rolls.
*           Should be preceded by the keep command to
*           keep dice through the next roll.
*
* keep   - lets the user select which dice they wish to
*           keep before the next roll. Saved dice will
*           be carried over future rolls until the user
*           decides to change which dice are kept. The
*           user can use the keep command multiple times
*           before or after a roll if they choose to.
*           Can only be called during a game.
*
* cat    - shows the complete list of categories that can
*           be picked by the user regardless if they meet
*           the prerequisites or not. This command can be
*           called before or during a game.
*
* acat   - shows the available categories the user can
*           choose at the moment of this command call i.e.
*           categories the user has not picked yet. Will
*           also show what the user will score for each
*           specific category. Can only be called during
*           an active game.
*
* pcat   - lets the user pick a category for their round
*           to fall under. Will only show available
*           categories similar to the acat command. Any 
*           category not previously picked can be picked 
*           even if the score will be zero. Can only be 
*           called during an active game.
*
* clear  - clears the buffer and aligns the prompt to the
*           top of the screen. Behaves exactly like the
*           UNIX 'clear' command or the Windows 'cls'
*           command. Can be called at any time. Only works
*           in an ANSI-supported environment.
*
* quit   - lets the user end the game and terminate the
*           program at any point before or during a
*           game. The user will be prompted if they are
*           sure they want to quit.
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
