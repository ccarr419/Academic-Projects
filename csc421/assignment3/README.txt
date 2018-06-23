* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Yahtzee © 2017 Hasbro, Inc.
* Version 3.0
* Christian Carreras BS Computer Science
* Kutztown University of Pennsylvania
*
* Official Rules:
* https://www.hasbro.com/common/instruct/Yahtzee.pdf
*
* JavaDocs Link:
* http://csitrd.kutztown.edu/~ccarr419/csc421/assignment3/
*
* - - - - - - - - - - MY DESIGN CHOICES - - - - - - - - - -
*
*     For this project I made a GWT application through a
*   Unix environment with the help of a tomcat server to
*   unpack my projects' war onto the web. First my project
*   was created with the GWT command webAppCreator. From
*   there I modified the html file to create the necessary
*   divs/tables for my game information. Then I made
*   modifications to the Yahtzee.java code to create the
*   game's widgets and inject game information/data. I
*   made buttons that look like dice the main aspect of
*   the game. So when a player clicks on the dice it acts
*   as if they pulled the dice aside to keep. Players
*   can choose a category at any point during a round.
*   However players will be forced to pick a category once
*   they run out of rolls if they wish to continue the
*   game. Players choose a category by selecting the button
*   across from the category they wish to pick. They
*   will be prompted with a pop-up prompt if they want to
*   pick that category in the case of misclicks. The game
*   will progress until the player has run out of
*   categories to fill. At that point the game is over.
*   To restart the game simply refresh the browser. Lastly
*   I made changes to the Yahtzee.css file to create the
*   look and feel of the GUI.
*
* - - - - - - - - - - - HOW TO PLAY - - - - - - - - - - - -
*
*   When the webpage loads, the game starts with an initial
*   roll. There is no need to manually start the game. The
*   same rule applies to once a category is picked. Once
*   a category is picked the game proceeds to the next
*   round with an initial roll.
*   
*   The player can select dice to keep by simply clicking
*   the dice they want to keep. The player can unkeep the
*   dice they kept by clicking on the kept dice again.
*   White dice signify unkept dice. Yellow/cream colored
*   dice signify kept dice.
*
*   The roll button will roll the dice. There is a maximum
*   of three rolls per round. With the first roll being
*   rolled automatically the player will only be able to
*   roll twice before reaching the roll limit. Once the
*   roll limit is reached they will no longer be able to
*   roll until a category is picked. If the player has not
*   picked any dice to keep before clicking the roll button
*   the player will be shown a prompt if they wish to
*   continue with the roll without keeping.
*
*   At any point during a round the player may select a
*   category to fill for the round. The score depends
*   on the current dice configuration. To select a score
*   the player must click the button horizontally across
*   from the category they wish to fill. The player will
*   be prompted everytime in the case of misclicks. Once a
*   category is picked it cannot be unpicked so make
*   sure to choose wisely. Players will be forced to choose
*   a category once they use all their rolls. Categories
*   that were previously picked will be crossed out.
*
*   Scores for the player can be found in the scoresheet
*   on the left side of the webpage. Scores will be
*   automatically injected into the scoresheet once a
*   category is picked with bonuses and totals being
*   updated automatically as well.
*
*   The "How To Play" button will bring you to this readme
*   file that will hold information to help you play.
*
*   There is no game reset button once the game has reached
*   its natural end. To reset the game from the beginning
*   please refresh your browser.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
