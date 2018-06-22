* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Yahtzee © 2017 Hasbro, Inc.
* Version 5.0
* Christian Carreras BS Computer Science
* Kutztown University of Pennsylvania
*
* Official Rules:
* https://www.hasbro.com/common/instruct/Yahtzee.pdf
*
* JavaDocs Link:
* http://csitrd.kutztown.edu/~ccarr419/csc421/assignment5/
*
* - - - - - - - - - - MY DESIGN CHOICES - - - - - - - - - -
*
*   For this project I made a GWT application through a
*   Unix environment with the help of a tomcat server to
*   unpack my projects' war onto the web. My project
*   was extended from the previous version by making the
*   necessary additions specified in the project guidelines.
*   The main changes between this version and the previous
*   version is the addition of a server-based two-player
*   network game support. Minor multimedia additions were
*   added such as the mute button if the player wants to
*   turn off all sound. I tried not to make too many visual
*   changes compared to the previous versions so I could
*   keep things simple and put more effort into the server.
*   The only difference with this visually is the addition 
*   of a DialogBox with a single button that is displayed
*   when it is not the player's turn. The button will check
*   with the server and see if it is the player's turn. If
*   it is the player's turn, it will transition to that
*   player's turn. Otherwise the player will have to keep
*   waiting until the other player is done with their turn.
*   Scores are added to the scoresheets after each player's
*   round and a winner, loser, or tie game is announced
*   when both players finish their scoresheet. To use
*   the two-player version simply accept the first prompt
*   given at page load. To use the one-player version,
*   cancel the first prompt at page load. To restart the
*   game just refresh the browser. If there are two players
*   playing the two player server-based game already, all
*   incoming players will default to the one player version.
*
* - - - - - - - - - - - HOW TO PLAY - - - - - - - - - - - -
*
*   On page load, the player or players will be prompted
*   with the choice of a one-player or two-player game.
*   If the one-player version is picked, there will be a
*   singular checksheet. If the two-player version is
*   checked, there will be two checksheets along with
*   text that displays which player's turn it is. If there
*   are two players already playing the two player game
*   the player will default to a one player game.
*
*   When the game begins, the game starts with an initial
*   roll. There is no need to manually start the game. The
*   same rule applies to once a category is picked. Once
*   a category is picked the game proceeds to the next
*   round and/or player turn with an initial roll.
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
*   updated automatically as well. If there is more than
*   one player, individual scoresheets can be selected
*   by clicking on the specific player's tab.
*
*   The "How To Play" button will bring you to this readme
*   file that will hold information to help you play.
*
*   There is no game reset button once the game has reached
*   its natural end. To reset the game from the beginning
*   please refresh your browser.
*
*   A winner will be announced at the end of the game if
*   there is more than one player.
*
*   Players will not be able to do anything until it is
*   their turn, be patient and wait for the other player.
*   Waiting player's screens will be locked to ensure this.
*
* - - - - - - - - - - -  WORKS CITED  - - - - - - - - - - -
*
*   Images:
*     dice1.jpg, dice2.jpg, dice3.jpg, dice4.jpg, dice5.jpg, dice6.jpg:
*       http://clipart-library.com/clipart/pT7KbK78c.htm
*       *Note* Picked versions were made from the set of the images above
*     Yahtzee.png:
*       https://en.wikipedia.org/wiki/Yahtzee
*     soundOn.png:
*       http://www.iconarchive.com/show/windows-8-icons-by-icons8/Media-Controls-Volume-Up-icon.html
*     soundOff.png:
*       http://www.iconarchive.com/show/windows-8-icons-by-icons8/Media-Controls-Mute-icon.html
*
*   Sounds:
*     diceThrow01.wav:
*       https://www.mediamusicnow.co.uk/royalty-free-sound-effects/casino/poker-cards-dice/dice-throw-five-dice-on-wood-table-01.aspx
*     diceThrow02.wav:
*       https://www.mediamusicnow.co.uk/royalty-free-sound-effects/casino/poker-cards-dice/dice-throw-five-dice-on-wood-table-03.aspx
*     diceThrow03.wav:
*       https://www.mediamusicnow.co.uk/royalty-free-sound-effects/casino/poker-cards-dice/dice-throw-five-dice-on-wood-table-04.aspx
*     pickCategory.wav:
*       https://www.youtube.com/watch?v=ZNjSEyd4w-w
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
