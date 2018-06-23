* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Yahtzee © 2017 Hasbro, Inc.
* Version 1.0
* Christian Carreras BS Computer Science
* Kutztown University of Pennsylvania
*
* JavaDocs Link:
* http://csitrd.kutztown.edu/~ccarr419/csc421/assignment1/
*
* - - - - - - - - - - MY DESIGN CHOICES - - - - - - - - - -
*
*     For this project I decided to make a command-based
*  version of Yahtzee similar to computer console-like
*  commands. The user is provided with a prompt and can
*  enter commands freely. The user may start and quit the
*  game freely at will as well. To represent the dice I 
*  used an integer array and used a pseudo-random number 
*  generator to represent a roll of the dice. In hindsight, 
*  I believe using a class to define the dice object would 
*  have been easier to implement and read but too much 
*  progress was made without implementing a class that 
*  changing it could create complications and break the 
*  majority of the existing code. I am greatly considering
*  using classes in the future when extending this game.
*  Command-line arguments are fully set up and were
*  originally intended for bug-testing but can be used to
*  start the game with a specific initial roll. To use
*  the command-line arguments feature, type the code
*  to run the game followed by five dice digits (1-6),
*  each separated by a space. The help page (this page),
*  the categories page, the rules page, and global stats
*  page are all read from files for easier editing and
*  displaying purposes (plus it cleans up the code!)
*  All entered commands are transformed to lower-case for
*  compatibility and error-handling. All non-commands
*  are handled gracefully and returns the player prompt.
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
*           the round/game from the beginning.
*
* stats  - shows the current game information including
*           current roll, current kept dice, the number  
*           of rolls rolled, and the dice rolled for each 
*           roll. Can only be called during an active game.
*
* gstat  - shows the total number of rounds played by any
*           user on the machine and the average amount
*           of rolls rolled by each user. Can be called
*           at any point before or during a game.
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
*           choose at the moment of this command call.
*           Can only be called during a game.
*
* pcat   - lets the user pick a category for their round
*           to fall under. Will only show available
*           categories similar to the acat command. Can
*           only be called during an active game.
*
* quit   - lets the user end the game and terminate the
*           program at any point before or during a
*           game. Game information will not be logged
*           if this command is used before round end.
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
