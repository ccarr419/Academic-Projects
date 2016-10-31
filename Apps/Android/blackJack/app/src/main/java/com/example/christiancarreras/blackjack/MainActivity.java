/*
*   Author:     Christian Carreras
*   File:       MainActivity.java
*   Date:       04/22/2016
*   Class:      Kutztown University of Pennsylvania, CSC 330 Mobile Development
*   Purpose:    This java file creates all the functionality necessary for a user
*               to play Blackjack. The user must try to get a score equal to or less than 21
*               at the same time as getting a score greater than the dealer. The user has the
*               ability to place bets, hit, stick, fold, double down, end the game at any point
*               and reshuffle the deck at the end of a round. This file also helps implement the
*               user interface by displaying the correct cards that are stored in the deck list.
*               Card playing sounds are also added and randomly selected for game enhancement.
*/

package com.example.christiancarreras.blackjack;

import android.content.Context; //For creating Context objects to get the database path
import android.content.Intent; //For creating Intent objects to switch activities
import android.database.Cursor; //For creating Cursor objects to search through the database
import android.database.sqlite.SQLiteDatabase; //Tools and methods for SQLite usage
import android.graphics.Color; //For creating Color objects to switch font color
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.*; //Get all libraries under view
import android.util.*; //Get all libraries under util
import android.widget.Button; //For creating Button reference objects
import android.widget.ImageView; //For creating ImageView reference objects
import android.widget.NumberPicker; //For creating NumberPicker reference objects
import android.widget.TextView; //For creating TextView reference objects
import android.graphics.Bitmap; //Allows for use of bitmaps
import android.graphics.BitmapFactory; //Allows for modification of bitmaps
import android.content.res.Resources; //Tools for working with app resources
import android.media.MediaPlayer; //Tools for playing audio files

import java.util.*; //Java utilities

public class MainActivity extends AppCompatActivity {
    //This string will be sent with the intent so a message can be sent with it.
    public final static String EXTRA_MESSAGE = "com.example.christiancarreras.blackjack.MESSAGE";
    SQLiteDatabase mydatabase; //Database that holds all users
    String username; //Current user logged in

    //Holds the cards reference values (0-51)
    //0-12: Clubs
    //13-25: Diamonds
    //26-38: Hearts
    //39-51: Spades
    Integer cards[] = new Integer[52];
    ArrayList<Integer> deck; //Holds the shuffled reference values
    ArrayList<Integer> recyclePile; //Holds discarded cards after the each round
    int idx = 0; //The deck card index
    int availableSlot = 1; //The available slot for a card to be placed
    int splitAvailableSlot = 1;
    boolean placedBet = false; //Boolean flag as to whether the user placed a bet or not

    int playerHand[] = new int[5]; //Holds the values for each individual card in the user's hand
    Integer playerCards[] = new Integer[5]; //Holds a reference to each card in the user's hand
    int playerNumAces = 0; //Number of aces in the user's possession
    int playerHandIdx = 0; //Current index in the user's hand where a new card can be placed

    int splitHand[] = new int[5];
    Integer splitCards[] = new Integer[5];
    int splitNumAces = 0;
    int splitHandIdx = 0;

    int dealerHand[] = new int[5]; //Holds the values for each individual card in the dealer's hand
    Integer dealerCards[] = new Integer[5]; //Holds a reference to each card in the dealer's hand
    int dealerNumAces = 0; //Number of aces in the dealer's possession
    int dealerHandIdx = 0; //Current index in the dealer's hand where a new card can be placed

    int randomNumber = 0; //Holds a randomly selected integer
    Random randomGenerator = new Random(); //Generates random numbers from a given range

    MediaPlayer cardPlacer, cardShuffler, chipPlacer, handfold; //Will play resource audio files

    /*
    *   Method Name:    onCreate
    *   Method Type:    n/a
    *   Parameters:     Bundle - (import only)
    *   Returns:        void
    *   Purpose:        This method will set up that deck list and shuffle it. It will also import
    *                   the user's balance from the database and set the number pickers' max
    *                   value as the balance that was retrieved.
    */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //Open the database and allow it to be modified
        mydatabase = SQLiteDatabase.openDatabase(getDBPath(getApplicationContext()), null, SQLiteDatabase.OPEN_READWRITE);
        Intent intent = getIntent();
        //Get the user's username from the last activity's intent message
        username = intent.getStringExtra(UserAccountMain.EXTRA_MESSAGE);

        //Set balance from the user's balance
        getBalance();
        TextView userChipsText = (TextView) findViewById(R.id.playerChipsText);
        int userBalance = Integer.parseInt(userChipsText.getText().toString());

        //Place the numbers 0 through 51 in an Integer array
        for (int i = 0; i < 52; i++) {
            cards[i] = i;
        }
        //Instantiate the deck list from the Integer array
        deck = new ArrayList<>(Arrays.asList(cards));
        recyclePile = new ArrayList<>(); //Instantiate the recycle pile list
        shuffleDeck();

        //Make the bet selector have a min value of 1 and a max value of the user's balance
        NumberPicker betSlider = (NumberPicker) findViewById(R.id.userBetSlider);
        betSlider.setMaxValue(userBalance);
        betSlider.setMinValue(1);
    }

    /*
    *   Method Name:    getBalance
    *   Method Type:    facilitator
    *   Parameters:     n/a
    *   Returns:        void
    *   Purpose:        This method gets the user's balance from the database's Balance column by
    *                   searching for the row where the user's username resides. The cursor will
    *                   then point to the user's balance. From there the string holding the user's
    *                   balance is placed in the user Chips TextView.
    */
    public void getBalance() {
        TextView userChipsText = (TextView) findViewById(R.id.playerChipsText);
        //Create a query to select the user's balance from the database by finding a row
        //where the Username value matches the user's username
        String query = "SELECT Balance FROM BlackjackUsers WHERE Username = '" + username + "'";
        Cursor mycursor = mydatabase.rawQuery(query, null);
        if(mycursor.moveToFirst()) //Go to the first (there will only be one) and get the balance
            userChipsText.setText(mycursor.getString(mycursor.getColumnIndex("Balance")));
        mycursor.close(); //Close the cursor to insure security
    }

    /*
    *   Method Name:    deal
    *   Method Type:    mutator
    *   Parameters:     View - (import only)
    *   Returns:        void
    *   Purpose:        This method starts the game by hiding/showing View element, drawing the
    *                   user's initial first two cards and taking the user's bet. The bet will be
    *                   subtracted from the user's chip count. The ability to choose a bet will
    *                   be disabled as soon as the game starts.
    */
    public void deal(View view) {
        //Assign variables references to buttons needed by the game and the buttons
        //that appear before the game begins
        Button hitButton = (Button) findViewById(R.id.hitButton);
        Button stickButton = (Button) findViewById(R.id.stickButton);
        Button dealButton = (Button) findViewById(R.id.dealButton);
        Button reshuffleButton = (Button) findViewById(R.id.reshuffleButton);
        Button foldButton = (Button) findViewById(R.id.foldButton);
        Button doubleDownButton = (Button) findViewById(R.id.doubleDownButton);

        //Hide the the deal and reshuffle buttons and show the game buttons
        //Game buttons: hit, stick, fold, double down
        hitButton.setEnabled(true);
        hitButton.setAlpha(1);
        stickButton.setEnabled(true);
        stickButton.setAlpha(1);
        foldButton.setEnabled(true);
        foldButton.setAlpha(1);
        doubleDownButton.setEnabled(true);
        doubleDownButton.setAlpha(1);
        dealButton.setEnabled(false);
        dealButton.setAlpha(0);
        reshuffleButton.setEnabled(false);
        reshuffleButton.setAlpha(0);

        //Hide and update the bet selector if deal is pressed before the select a bet button
        hideNumberPicker();
        updateBet(view);

        //Draw the first two cards to start the game
        drawTopCard();
        drawTopCard();

        //Check if the cards are the same in order to show the split button
        if (checkForSameCards()) {
            //Show the split button, the first two cards are the same
            Button splitButton = (Button) findViewById(R.id.splitButton);
            splitButton.setAlpha(1);
            splitButton.setEnabled(true);
        }

        TextView playerChipText = (TextView) findViewById(R.id.playerChipsText);
        TextView playerBetText = (TextView) findViewById(R.id.playerBetEditText);

        //If the bet was not officially placed (always false at the beginning of a round)
        if (placedBet == false) {
            int playerBet = Integer.parseInt(playerBetText.getText().toString());
            int playerChips = Integer.parseInt(playerChipText.getText().toString());
            int newChipCount = playerChips - playerBet; //Subtract bet from user's chips
            playerChipText.setText("" + newChipCount);

            //Change user chip text to red if it is negative, black if not
            if (newChipCount >= 0)
                playerChipText.setTextColor(Color.parseColor("#000000"));
            else
                playerChipText.setTextColor(Color.parseColor("#ff0000"));
        }

        //The player has made a bet, disable future bets until the end of the round
        placedBet = true;
        playerBetText.setEnabled(false);
    }

    /*
    *   Method Name:    shuffleDeck
    *   Method Type:    mutator
    *   Parameters:     n/a
    *   Returns:        void
    *   Purpose:        Randomizes the element within the deck array list object.
    *                   This simulates someone shuffling the deck.
    */
    public void shuffleDeck() {
        playCardShuffleSound();
        long seed = System.nanoTime(); //a seed is needed for random sort
        Collections.shuffle(deck, new Random(seed));
    }

    /*
    *   Method Name:    checkForSameCards
    *   Method Type:    facilitator
    *   Parameters:     n/a
    *   Returns:        boolean - (true if the cards are the same, false if not)
    *   Purpose:        Checks if the first to cards dealt are the same. This is needed to insure
    *                   the user can split his/her hand if they want to. Checks equality by the
    *                   reference number given to the cards at the beginning. Must check both ways.
    *   Prerequisite:   There must be at least two cards in the user's hand
    */
    public boolean checkForSameCards() {
        if (playerCards[0] == (playerCards[1] - 13))
            return true;
        else if (playerCards[0] == (playerCards[1] - 26))
            return true;
        else if (playerCards[0] == (playerCards[1] - 39))
            return true;
        else if (playerCards[1] == (playerCards[0] - 13))
            return true;
        else if (playerCards[1] == (playerCards[0] - 26))
            return true;
        else if (playerCards[1] == (playerCards[0] - 39))
            return true;
        else
            return false;
    }

    /*
    *   Method Name:    showNumberPicker
    *   Method Type:    mutator
    *   Parameters:     View - (import only)
    *   Returns:        void
    *   Purpose:        This method shows the bet selector and enables it. Only used when the
    *                   user bet TextView.
    */
    public void showNumberPicker(View view) {
        NumberPicker betSlider = (NumberPicker) findViewById(R.id.userBetSlider);
        Button select = (Button) findViewById(R.id.selectBetButton);
        select.setEnabled(true);
        select.setAlpha(1);
        betSlider.setEnabled(true);
        betSlider.setAlpha(1);
    }

    /*
    *   Method Name:    hideNumberPicker
    *   Method Type:    mutator
    *   Parameters:     n/a
    *   Returns:        void
    *   Purpose:        This method hides the bet selector and disables it.
    */
    public void hideNumberPicker() {
        NumberPicker betSlider = (NumberPicker) findViewById(R.id.userBetSlider);
        Button select = (Button) findViewById(R.id.selectBetButton);
        betSlider.setEnabled(false);
        betSlider.setAlpha(0);
        select.setEnabled(false);
        select.setAlpha(0);
    }

    /*
    *   Method Name:    updateBet
    *   Method Type:    mutator
    *   Parameters:     View - (import only)
    *   Returns:        void
    *   Purpose:        This method updates the bet from the value of the bet slider (number picker)
    */
    public void updateBet(View view) {
        TextView userBetText = (TextView) findViewById(R.id.playerBetEditText);
        NumberPicker betSlider = (NumberPicker) findViewById(R.id.userBetSlider);
        userBetText.setText("" + betSlider.getValue());
        hideNumberPicker();
    }

    /*
    *   Method Name:    getCard
    *   Method Type:    facilitator
    *   Parameters:     int - the card to get the value of (import only)
    *   Returns:        int - the value of the card
    *   Purpose:        This method finds the value of the parameter card. Also the suit of
    *                   the card is assigned for debugging purposes. It will assign a value of
    *                   0 through 10 to the card, regardless of suit and call its helper function.
    */
    public int getCard(int card) {
        int cardValue;
        if (card < 13) //cards 0-12
            cardValue = checkCard(card, "Clubs");

        else if (card < 26) //cards 13-25
            cardValue = checkCard(card - 13, "Diamonds");

        else if (card < 39) //cards 26-38
            cardValue = checkCard(card - 26, "Hearts");

        else //cards 39-51
            cardValue = checkCard(card - 39, "Spades");

        return cardValue;
    }

    /*
    *   Method Name:    checkCard
    *   Method Type:    facilitator
    *   Parameters:     int - the card to get the value of (import only)
    *                   String - the card's suit for debugging purposes
    *   Returns:        int - the value of the card
    *   Purpose:        This method gets the value of the card according the the parameter value
    *                   given (always 0-12). The name of the card is logged for debugging purposes.
    */
    public int checkCard(int cardNum, String suit) {
        String cardName;
        int cardValue;

        switch (cardNum) {
            case 0: //The card is an ace
                cardValue = 1; //Make the card value 1 since only one ace can be 11 per hand
                //Choice of whether the ace will be 11 or 1 will be made later
                cardName = "Ace of " + suit;
                break;
            case 10: //The card is a 10
                cardValue = 10;
                cardName = "Jack of " + suit;
                break;
            case 11: //The card is a queen
                cardValue = 10;
                cardName = "Queen of " + suit;
                break;
            case 12: //The card is a king
                cardValue = 10;
                cardName = "King of " + suit;
                break;
            default: //Make the card value one higher than the given value
                cardValue = cardNum + 1;
                cardName = cardValue + " of " + suit;
                break;
        }
        Log.d("Deck Card: ", cardName + "; Card Value: " + cardValue);
        return cardValue;
    }

    /*
    *   Method Name:    drawTopCard
    *   Method Type:    mutator
    *   Parameters:     n/a
    *   Returns:        void
    *   Purpose:        Handles the event when the user needs to draw a card from the top of the
    *                   deck. This will be the normal handler and will not cover split hands or the
    *                   dealer's event of drawing a card.
    */
    public void drawTopCard() {
        //Create a new thread to take stress off the main stress
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                //Check if the deck is out of cards
                //Deck size needs to be checked since it could be less than 52
                if (idx >= deck.size()) {
                    //Make the deck equal to the recycle pile
                    deck = new ArrayList<>(recyclePile);
                    recyclePile.clear(); //Clear the recycle pile since it was put in the deck
                    shuffleDeck();
                    idx = 0; //Reset the deck index
                }

                //Log the deck index for debugging purposes
                Log.d("Idx", "" + idx);

                //Get the resource id for the card's image
                int resId = getResources().getIdentifier("card" + deck.get(idx), "drawable", getPackageName());
                //Get the resource id for the next available slot to put the card
                int slotId = getResources().getIdentifier("cardSlot" + availableSlot, "id", getApplicationContext().getPackageName());

                //Make references to the user chip and bet TextViews
                TextView scoreText = (TextView) findViewById(R.id.userScoreText);
                TextView betText = (TextView) findViewById(R.id.playerBetEditText);
                //Get the user's bet by parsing it as an int
                int userBet = Integer.parseInt(betText.getText().toString());

                //Get the next available card slot's ImageView
                ImageView topCard = (ImageView) findViewById(slotId);
                //Resize the image to fit the container to save memory
                topCard.setImageBitmap(decodeSampledBitmapFromResource(getResources(), resId, 75, 75));

                playCardPlaceSound();

                //Get the card from the deck, place its value in the playerHand array
                playerHand[playerHandIdx] = getCard(deck.get(idx));
                //Place a reference to the card in the playerCards array
                playerCards[playerHandIdx] = deck.get(idx);

                //If the card is an ace
                if (playerHand[playerHandIdx] == 1) {
                    playerNumAces++;
                    //If there is only one ace in the hand, make its value 11 as long as the
                    //hands sum is not over 21
                    if (playerNumAces == 1) {
                        if (sumHand(playerHand) + 10 <= 21) {
                            playerHand[playerHandIdx] = 11;
                        }
                    }
                }

                //Increment indexes
                playerHandIdx++;
                availableSlot++;
                idx++;

                //If the user's hand sum is over 21, make sure aces are not causing it
                if (sumHand(playerHand) > 21) {
                    changeAces();
                }

                //The user busted by having a hand sum over 21, user loses
                if (sumHand(playerHand) > 21) {
                    scoreText.setText("Busted!");
                    playAgain();
                }

                //The user got 21 off the first two cards which is Blackjack
                if ((sumHand(playerHand) == 21) && (playerHandIdx == 2)) {
                    //Make sure the dealer does not have Blackjack before winning
                    if (!checkDealerBlackJack()) {
                        scoreText.setText("Black Jack!");
                        changeChips(userBet);
                        playAgain(); //user wins
                    }
                }

                //If the user has 5 cards in the hand and its sum is less than or equal to 21:
                //This is known as 5 card Charlie, user wins automatically
                if ((sumHand(playerHand) <= 21) && (playerHandIdx == 5)) {
                    scoreText.setText("You Win!");
                    changeChips(userBet);
                    playAgain();
                }
            }
        });
    }

    /*
    *   Method Name:    dealerDraw
    *   Method Type:    mutator
    *   Parameters:     n/a
    *   Returns:        void
    *   Purpose:        This method is similar to the drawTopCard function but is
    *                   modified for the dealer.
    */
    public void dealerDraw() {
        //Create a new thread to take stress off the main stress
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                //Check if the deck is out of cards
                //Deck size needs to be checked since it could be less than 52
                if (idx >= deck.size()) {
                    deck = new ArrayList<>(recyclePile);
                    recyclePile.clear();
                    shuffleDeck();
                    idx = 0;
                }

                //Log the deck index for debugging purposes
                Log.d("Idx", "" + idx);

                //Get the resource id for the card's image
                int resId = getResources().getIdentifier("card" + deck.get(idx), "drawable", getPackageName());
                //Get the resource id for the next available slot to put the card
                int slotId = getResources().getIdentifier("dealerSlot" + availableSlot, "id", getApplicationContext().getPackageName());

                //Make references to the user chip and bet TextViews
                TextView scoreText = (TextView) findViewById(R.id.userScoreText);
                TextView betText = (TextView) findViewById(R.id.playerBetEditText);
                //Get the user's bet by parsing it as an int
                int userBet = Integer.parseInt(betText.getText().toString());

                //Get the next available card slot's ImageView
                ImageView topCard = (ImageView) findViewById(slotId);
                //Resize the image to fit the container to save memory
                topCard.setImageBitmap(decodeSampledBitmapFromResource(getResources(), resId, 75, 75));

                playCardPlaceSound();

                //Get the card from the deck, place its value in the dealerHand array
                dealerHand[dealerHandIdx] = getCard(deck.get(idx));
                //Place a reference to the card in the dealerCards array
                dealerCards[dealerHandIdx] = deck.get(idx);

                //If the card is an ace
                if (dealerHand[dealerHandIdx] == 1) {
                    dealerNumAces++;
                    //If there is only one ace in the hand, make its value 11 as long as the
                    //hands sum is not over 21
                    if (dealerNumAces == 1) {
                        if (sumHand(dealerHand) + 10 <= 21) {
                            dealerHand[dealerHandIdx] = 11;
                        }
                    }
                }

                //Increment indexes
                dealerHandIdx++;
                availableSlot++;
                idx++;

                //If the dealer's hand sum is over 21, make sure aces are not causing it
                if (sumHand(dealerHand) > 21) {
                    changeAces();
                }

                //The dealer busted by having a hand sum over 21, user wins
                if (sumHand(dealerHand) > 21) {
                    scoreText.setText("Dealer Busted!");
                    changeChips(userBet);
                    playAgain();
                }

                //The dealer has Blackjack, the user loses
                if ((sumHand(dealerHand) == 21) && (dealerHandIdx == 2)) {
                    scoreText.setText("Dealer Black Jack!");
                    playAgain();
                }

                //The dealer got 5 card Charlie, user loses
                if ((sumHand(dealerHand) <= 21) && (dealerHandIdx == 5)) {
                    scoreText.setText("Dealer Wins!");
                    playAgain();
                }
            }
        });
    }

    /*
    *   Method Name:    dealersTurn
    *   Method Type:    mutator
    *   Parameters:     n/a
    *   Returns:        void
    *   Purpose:        This method delegates the dealer turn. The dealer will draw two cards to
    *                   start off, then keeping drawing cards until the sum of the hand is
    *                   15 or less. If the dealer does not bust or win by Blackjack or Charlie,
    *                   the dealer's hand will be compared to the user's hand.
    */
    public void dealersTurn() {
        TextView scoreText = (TextView) findViewById(R.id.userScoreText);
        TextView playerBetText = (TextView) findViewById(R.id.playerBetEditText);
        Button playAgainButton = (Button) findViewById(R.id.playAgainButton);
        int playerBet = Integer.parseInt(playerBetText.getText().toString());
        availableSlot = 1;

        //Draw first 2 cards
        dealerDraw();
        dealerDraw();

        //Draw until the hand sum is 16 or higher
        while (sumHand(dealerHand) < 16)
            dealerDraw();

        //If the dealer did not bust or win by Blackjack or Charlie
        if (!playAgainButton.isEnabled()) {
            //Compare the dealer's hand to the user's hand
            //The dealer wins in the sum is equal to or greater to the user's sum(s)
            if (sumHand(dealerHand) >= sumHand(playerHand) && sumHand(dealerHand) >= sumHand(splitHand)) {
                scoreText.setText("Dealer Wins!");
                playAgain();
            } else { //If the user's hand sum is greater than the dealer's, the user wins
                scoreText.setText("You Win!");
                changeChips(playerBet);
                playAgain();
            }
        }
    }

    /*
    *   Method Name:    checkDealerBlackJack
    *   Method Type:    facilitator
    *   Parameters:     n/a
    *   Returns:        boolean - (true if the dealer has Blackjack, false if not)
    *   Purpose:        Check if the dealer has Blackjack before letting the player win
    */
    public boolean checkDealerBlackJack() {
        Button playAgainButton = (Button) findViewById(R.id.playAgainButton);
        availableSlot = 1;
        //Draw two cards
        dealerDraw();
        dealerDraw();
        //Check for Blackjack
        if (playAgainButton.isEnabled())
            return true;
        return false;
    }

    /*
    *   Method Name:    changeChips
    *   Method Type:    mutator
    *   Parameters:     int - the user's bet (import only)
    *   Returns:        void
    *   Purpose:        This method changes the user's chips by the current bet.
    *                   This method assumes the player won.
    */
    public void changeChips(int bet) {
        TextView playerChipText = (TextView) findViewById(R.id.playerChipsText);
        int playerChips = Integer.parseInt(playerChipText.getText().toString());
        //2 times the bet since the bet was already removed from the player's chips
        int newChipCount = playerChips + (2 * bet);

        //If the chipPlacer MediaPlayer already has a value
        if (chipPlacer != null)
            chipPlacer.release();

        //If the user had a big bet, play the big bet chip sound
        if (bet >= 200) {
            chipPlacer = MediaPlayer.create(getApplicationContext(), R.raw.bigchipsound);
            chipPlacer.start();
        }

        //If the bet was not big, play normal chip sounds randomly selected
        else {
            //Get a random number in order to randomly select a audio file
            randomNumber = randomGenerator.nextInt(4);
            while (randomNumber == 0) { //There is no audio file indexed as 0
                randomNumber = randomGenerator.nextInt(4);
            }
            //Get resource id for the chip sound audio file
            int resId = getResources().getIdentifier("chipsound" + randomNumber, "raw", getPackageName());
            chipPlacer = MediaPlayer.create(getApplicationContext(), resId);
            chipPlacer.start();
        }

        //Set the text of the player chip TextView to the new chip count
        playerChipText.setText("" + newChipCount);

        //Change the color of the player's Chip TextView to red if negative, black if not
        if (newChipCount >= 0)
            playerChipText.setTextColor(Color.parseColor("#000000"));
        else
            playerChipText.setTextColor(Color.parseColor("#ff0000"));
    }

    /*
    *   Method Name:    playAgain
    *   Method Type:    mutator
    *   Parameters:     n/a
    *   Returns:        void
    *   Purpose:
    */
    public void playAgain() {
        //Get references to View elements
        Button playAgainButton = (Button) findViewById(R.id.playAgainButton);
        Button hit = (Button) findViewById(R.id.hitButton);
        Button stick = (Button) findViewById(R.id.stickButton);
        Button fold = (Button) findViewById(R.id.foldButton);
        Button doubleDown = (Button) findViewById(R.id.doubleDownButton);
        Button splitButton = (Button) findViewById(R.id.splitButton);
        Button splitHit = (Button) findViewById(R.id.splitHandHit);
        Button splitStick = (Button) findViewById(R.id.splitHandStick);
        Button normalHit = (Button) findViewById(R.id.normalHandHit);
        Button noramlStick = (Button) findViewById(R.id.normalHandStick);
        TextView playerChipText = (TextView) findViewById(R.id.playerChipsText);
        TextView playerBetText = (TextView) findViewById(R.id.playerBetEditText);

        //Parse user's chip and bet values as integers
        int playerBet = Integer.parseInt(playerBetText.getText().toString());
        int playerChips = Integer.parseInt(playerChipText.getText().toString());

        //Hide and disable game buttons
        hit.setAlpha(0);
        hit.setEnabled(false);
        stick.setAlpha(0);
        stick.setEnabled(false);
        fold.setAlpha(0);
        fold.setEnabled(false);
        doubleDown.setAlpha(0);
        doubleDown.setEnabled(false);
        splitButton.setAlpha(0);
        splitButton.setEnabled(false);
        splitHit.setAlpha(0);
        splitHit.setEnabled(false);
        splitStick.setAlpha(0);
        splitStick.setEnabled(false);
        normalHit.setAlpha(0);
        normalHit.setEnabled(false);
        noramlStick.setAlpha(0);
        noramlStick.setEnabled(false);
        //Show and enable the play again button
        playAgainButton.setAlpha(1);
        playAgainButton.setEnabled(true);

        //Change the color of the player's Chip TextView to red if negative, black if not
        if (playerChips >= 0)
            playerChipText.setTextColor(Color.parseColor("#000000"));
        else
            playerChipText.setTextColor(Color.parseColor("#ff0000"));

        //If the player's chips goes negative make the bet the absolute value of the player's chips
        if (playerBet > playerChips)
            playerBetText.setText("" + Math.abs(playerChips));

        NumberPicker betSlider = (NumberPicker) findViewById(R.id.userBetSlider);
        betSlider.setMinValue(1);

        //If the player's chips is non-negative, set the max value to the value
        if (playerChips > 0)
            betSlider.setMaxValue(playerChips);

        //Other set the max value to the absolute value of the player's chips value
        else if (playerChips < 0)
            betSlider.setMaxValue(Math.abs(playerChips));
    }

    /*
    *   Method Name:    playCardPlaceSound
    *   Method Type:    facilitator
    *   Parameters:     n/a
    *   Returns:        void
    *   Purpose:        This method plays a card placing sound from a randomly selected audio file.
    */
    public void playCardPlaceSound() {
        //Check if the MediaPlayer already has a value
        if (cardPlacer != null)
            cardPlacer.release();
        //Get a random number from 0-3
        randomNumber = randomGenerator.nextInt(4);
        while (randomNumber == 0) { //Except 0 is not an index in the audio files
            randomNumber = randomGenerator.nextInt(4);
        }
        //Get the randomly selected audio file resource id
        int resId = getResources().getIdentifier("cardplace" + randomNumber, "raw", getPackageName());
        cardPlacer = MediaPlayer.create(getApplicationContext(), resId);
        cardPlacer.start();
    }

    /*
    *   Method Name:    playCardShuffleSound
    *   Method Type:    facilitator
    *   Parameters:     n/a
    *   Returns:        void
    *   Purpose:        This method plays a card placing shuffling from a randomly selected audio file.
    */
    public void playCardShuffleSound() {
        //Check if the MediaPlayer already has a value
        if (cardShuffler != null)
            cardShuffler.release();
        //Get a random number from 0-4
        randomNumber = randomGenerator.nextInt(5);
        while (randomNumber == 0) { //Except 0 is not an index in the audio files
            randomNumber = randomGenerator.nextInt(5);
        }
        //Get the randomly selected audio file resource id
        int resId = getResources().getIdentifier("shufflingcards" + randomNumber, "raw", getPackageName());
        cardShuffler = MediaPlayer.create(getApplicationContext(), resId);
        cardShuffler.start();
    }

    /*
    *   Method Name:    playHandFoldSound
    *   Method Type:    facilitator
    *   Parameters:     n/a
    *   Returns:        void
    *   Purpose:        This method plays a card fold sound from a randomly selected audio file.
    */
    public void playHandFoldSound() {
        //Check if the MediaPlayer already has a value
        if (handfold != null)
            handfold.release();
        //Get the card fold audio file reference
        handfold = MediaPlayer.create(getApplicationContext(), R.raw.cardshove);
        handfold.start();
    }

    /*
    *   Method Name:    sumHand
    *   Method Type:    facilitator
    *   Parameters:     int[] - hand to sum (import only)
    *   Returns:        int - the value of the hand
    *   Purpose:        This method sums the hand and returns the sum
    */
    public int sumHand(int hand[]) {
        int sum = 0;
        if(hand != null) {
            for (int i = 0; i < hand.length; i++) {
                sum += hand[i];
            }
        }
        return sum;
    }

    /*
    *   Method Name:    changeAces
    *   Method Type:    mutator
    *   Parameters:     n/a
    *   Returns:        void
    *   Purpose:        This method change any aces from 11 to 1.
    *   Prerequisite:   The playerHand array must be initialized.
    */
    public void changeAces() {
        for (int i = 0; i < playerHandIdx; i++) {
            if (playerHand[i] == 11) {
                playerHand[i] = 1;
            }
        }
    }

    /*
    *   Method Name:    hit
    *   Method Type:    mutator
    *   Parameters:     View - (import only)
    *   Returns:        void
    *   Purpose:        User takes a hit, draws a card.
    */
    public void hit(View view) {
        if (playerHandIdx == 5)
            replay(view);
        else
            drawTopCard();
    }

    /*
    *   Method Name:    stick
    *   Method Type:    mutator
    *   Parameters:     View - (import only)
    *   Returns:        void
    *   Purpose:        This method ends the user's turn and starts the dealer's turn.
    */
    public void stick(View view) {
        dealersTurn();
    }

    /*
    *   Method Name:    reshuffle
    *   Method Type:    mutator
    *   Parameters:     View - (import only)
    *   Returns:        void
    *   Purpose:        This method reshuffles the deck and resets the deck index.
    */
    public void reshuffle(View view) {
        deck = new ArrayList<>(Arrays.asList(cards));
        shuffleDeck();
        idx = 0;
    }

    /*
    *   Method Name:    fold
    *   Method Type:    mutator
    *   Parameters:     View - (import only)
    *   Returns:        void
    *   Purpose:        This method ends the game and returns half of the user's bet.
    */
    public void fold(View view) {
        TextView playerBetText = (TextView) findViewById(R.id.playerBetEditText);
        TextView playerChipsText = (TextView) findViewById(R.id.playerChipsText);
        int playerBet = Integer.parseInt(playerBetText.getText().toString());
        int playerChips = Integer.parseInt(playerChipsText.getText().toString());

        //Get half of the users bet and return it.
        int foldReturn = (int) Math.floor(playerBet / 2);
        int newChipCount = playerChips + foldReturn;
        playerChipsText.setText("" + newChipCount);
        playHandFoldSound();
        playAgain();
    }

    /*
    *   Method Name:    doubleDown
    *   Method Type:    mutator
    *   Parameters:     View - (import only)
    *   Returns:        void
    *   Purpose:        This method doubles the user's bet and draws one more card.
    */
    public void doubleDown(View view) {
        TextView playerBetText = (TextView) findViewById(R.id.playerBetEditText);
        TextView playerChipText = (TextView) findViewById(R.id.playerChipsText);
        Button playAgainButton = (Button) findViewById(R.id.playAgainButton);

        int playerChips = Integer.parseInt(playerChipText.getText().toString());
        int playerBet = Integer.parseInt(playerBetText.getText().toString());
        //Double the user's bet
        int doubleDownBet = playerBet * 2;
        int newChipCount = playerChips - playerBet;
        //Set the new bet and chip count
        playerChipText.setText("" + newChipCount);
        playerBetText.setText("" + doubleDownBet);
        drawTopCard();

        //If the player did not bust, go to the dealer's turn
        if (!playAgainButton.isEnabled()) {
            dealersTurn();
        }
    }

    /*
    *   Method Name:    split
    *   Method Type:    mutator
    *   Parameters:     View - (import only)
    *   Returns:        void
    *   Purpose:        This method splits the users hand into two individual hands against the
    *                   dealer. This will open happen if the first to cards dealt to the user are
    *                   of the same value.
    */
    public void split(View view) {
        ImageView split1 = (ImageView) findViewById(R.id.splitSlot1);
        ImageView playerHandCard = (ImageView) findViewById(R.id.cardSlot2);
        Button splitButton = (Button) findViewById(R.id.splitButton);
        Button hitButton = (Button) findViewById(R.id.hitButton);
        Button stickButton = (Button) findViewById(R.id.stickButton);
        Button splitHitButton = (Button) findViewById(R.id.splitHandHit);
        Button splitStickButton = (Button) findViewById(R.id.splitHandStick);
        Button normalHitButton = (Button) findViewById(R.id.normalHandHit);
        Button normalStickButton = (Button) findViewById(R.id.normalHandStick);

        //Get the access to the split hand slot and the card to put there
        int resId = getResources().getIdentifier("card" + playerCards[1], "drawable", getPackageName());
        split1.setImageBitmap(decodeSampledBitmapFromResource(getResources(), resId, 75, 75));
        if(playerHand[1] == 1) {
            playerNumAces--;
            splitNumAces++;
        }
        //Move the second card in the hand to the new hand
        splitHand[0] = playerHand[1];
        splitCards[0] = playerCards[1];

        //Get rid of the normal hit and stick buttons
        splitButton.setEnabled(false);
        splitButton.setAlpha(0);
        hitButton.setEnabled(false);
        hitButton.setAlpha(0);
        stickButton.setEnabled(false);
        stickButton.setAlpha(0);

        //Show the two hit and stick buttons for both hands
        splitHitButton.setEnabled(true);
        splitHitButton.setAlpha(1);
        splitStickButton.setEnabled(true);
        splitStickButton.setAlpha(1);
        normalHitButton.setEnabled(true);
        normalHitButton.setAlpha(1);
        normalStickButton.setEnabled(true);
        normalStickButton.setAlpha(1);

        //Do not show the card that was moved
        playerHandCard.setImageResource(0);
        //The user's original hand will now have one less...
        playerHandIdx--;
        availableSlot--;
        //...And the user's second hand will gain one
        splitAvailableSlot++;
        splitHandIdx++;
    }

    /*
    *   Method Name:    splitStick
    *   Method Type:    mutator
    *   Parameters:     View - (import only)
    *   Returns:        void
    *   Purpose:        This method sticks the second hand of the user. If the first hand is not
    *                   already sticking or busted, wait until then to do so.
    */
    public void splitStick(View view) {
        Button splitHit = (Button) findViewById(R.id.splitHandHit);
        Button splitStick = (Button) findViewById(R.id.splitHandStick);
        Button normalButton = (Button) findViewById(R.id.normalHandHit);
        splitHit.setEnabled(false);
        splitHit.setAlpha(0);
        splitStick.setEnabled(false);
        splitStick.setAlpha(0);
        if(!normalButton.isEnabled())
            dealersTurn();
    }

    /*
    *   Method Name:    normalStick
    *   Method Type:    mutator
    *   Parameters:     View - (import only)
    *   Returns:        void
    *   Purpose:        This method sticks the first hand of the user. If the second hand is not
    *                   already sticking or busted, wait until then to do so.
    */
    public void normalStick(View view) {
        Button normalHit = (Button) findViewById(R.id.normalHandHit);
        Button normalStick = (Button) findViewById(R.id.normalHandStick);
        Button splitButton = (Button) findViewById(R.id.splitHandHit);
        normalStick.setEnabled(false);
        normalStick.setAlpha(0);
        normalHit.setEnabled(false);
        normalHit.setAlpha(0);
        if(!splitButton.isEnabled())
            dealersTurn();
    }

    /*
    *   Method Name:    splitHit
    *   Method Type:    mutator
    *   Parameters:     View - (import only)
    *   Returns:        void
    *   Purpose:        This method takes a hit for the second user hand. If the user busts on this
    *                   hand, this method will check if user busted the other hand or stuck before
    *                   handing the turn over to the dealer or ending the round.
    */
    public void splitHit(View view) {
        if (splitHandIdx == 5)
            replay(view);
        else {
            //Create a new thread to take stress off the main stress
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Button splitHit = (Button) findViewById(R.id.splitHandHit);
                    Button splitStick = (Button) findViewById(R.id.splitHandStick);
                    Button normalButton = (Button) findViewById(R.id.normalHandHit);
                    //Check if the deck is out of cards
                    //Deck size needs to be checked since it could be less than 52
                    if (idx >= deck.size()) {
                        //Make the deck equal to the recycle pile
                        deck = new ArrayList<>(recyclePile);
                        recyclePile.clear(); //Clear the recycle pile since it was put in the deck
                        shuffleDeck();
                        idx = 0; //Reset the deck index
                    }

                    //Log the deck index for debugging purposes
                    Log.d("Idx", "" + idx);

                    //Get the resource id for the card's image
                    int resId = getResources().getIdentifier("card" + deck.get(idx), "drawable", getPackageName());
                    //Get the resource id for the next available slot to put the card
                    int slotId = getResources().getIdentifier("splitSlot" + splitAvailableSlot, "id", getApplicationContext().getPackageName());

                    //Make references to the user chip and bet TextViews
                    TextView scoreText = (TextView) findViewById(R.id.userScoreText);
                    TextView betText = (TextView) findViewById(R.id.playerBetEditText);
                    //Get the user's bet by parsing it as an int
                    int userBet = Integer.parseInt(betText.getText().toString());

                    //Get the next available card slot's ImageView
                    ImageView topCard = (ImageView) findViewById(slotId);
                    //Resize the image to fit the container to save memory
                    topCard.setImageBitmap(decodeSampledBitmapFromResource(getResources(), resId, 75, 75));

                    playCardPlaceSound();

                    //Get the card from the deck, place its value in the playerHand array
                    splitHand[splitHandIdx] = getCard(deck.get(idx));
                    //Place a reference to the card in the playerCards array
                    splitCards[splitHandIdx] = deck.get(idx);

                    //If the card is an ace
                    if (splitHand[splitHandIdx] == 1) {
                        splitNumAces++;
                        //If there is only one ace in the hand, make its value 11 as long as the
                        //hands sum is not over 21
                        if (splitNumAces == 1) {
                            if (sumHand(splitHand) + 10 <= 21) {
                                splitHand[splitHandIdx] = 11;
                            }
                        }
                    }

                    //Increment indexes
                    splitHandIdx++;
                    splitAvailableSlot++;
                    idx++;

                    //If the user's hand sum is over 21, make sure aces are not causing it
                    if (sumHand(splitHand) > 21) {
                        changeAces();
                    }

                    //The user busted by having a hand sum over 21, user loses
                    if (sumHand(splitHand) > 21) {
                        splitHit.setEnabled(false);
                        splitHit.setAlpha(0);
                        splitStick.setEnabled(false);
                        splitStick.setAlpha(0);

                        //Empty the player's hand so the value will be zero
                        splitHand = null;

                        //Check if the user bust on the other hand
                        if(playerHand == null) {
                            scoreText.setText("Busted!");
                            playAgain();
                        }
                        //Check if the user choose to stick the other hand
                        else if(!normalButton.isEnabled())
                            dealersTurn();
                    }

                    //The user got 21 off the first two cards which is Blackjack
                    if ((sumHand(splitHand) == 21) && (splitHandIdx == 2)) {
                        //Make sure the dealer does not have Blackjack before winning
                        if (!checkDealerBlackJack()) {
                            scoreText.setText("Black Jack!");
                            changeChips(userBet);
                            playAgain(); //user wins
                        }
                    }

                    //If the user has 5 cards in the hand and its sum is less than or equal to 21:
                    //This is known as 5 card Charlie, user wins automatically
                    if ((sumHand(splitHand) <= 21) && (splitHandIdx == 5)) {
                        scoreText.setText("You Win!");
                        changeChips(userBet);
                        playAgain();
                    }
                }
            });
        }
    }

    /*
    *   Method Name:    normalHit
    *   Method Type:    mutator
    *   Parameters:     View - (import only)
    *   Returns:        void
    *   Purpose:        This method takes a hit for the first user hand. If the user busts on this
    *                   hand, this method will check if user busted the other hand or stuck before
    *                   handing the turn over to the dealer or ending the round.
    */
    public void normalHit(View view) {
        if (playerHandIdx == 5)
            replay(view);
        else {
            //Create a new thread to take stress off the main stress
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Button normalHit = (Button) findViewById(R.id.normalHandHit);
                    Button normalStick = (Button) findViewById(R.id.normalHandStick);
                    Button splitButton = (Button) findViewById(R.id.splitHandHit);
                    //Check if the deck is out of cards
                    //Deck size needs to be checked since it could be less than 52
                    if (idx >= deck.size()) {
                        //Make the deck equal to the recycle pile
                        deck = new ArrayList<>(recyclePile);
                        recyclePile.clear(); //Clear the recycle pile since it was put in the deck
                        shuffleDeck();
                        idx = 0; //Reset the deck index
                    }

                    //Log the deck index for debugging purposes
                    Log.d("Idx", "" + idx);

                    //Get the resource id for the card's image
                    int resId = getResources().getIdentifier("card" + deck.get(idx), "drawable", getPackageName());
                    //Get the resource id for the next available slot to put the card
                    int slotId = getResources().getIdentifier("cardSlot" + availableSlot, "id", getApplicationContext().getPackageName());

                    //Make references to the user chip and bet TextViews
                    TextView scoreText = (TextView) findViewById(R.id.userScoreText);
                    TextView betText = (TextView) findViewById(R.id.playerBetEditText);
                    //Get the user's bet by parsing it as an int
                    int userBet = Integer.parseInt(betText.getText().toString());

                    //Get the next available card slot's ImageView
                    ImageView topCard = (ImageView) findViewById(slotId);
                    //Resize the image to fit the container to save memory
                    topCard.setImageBitmap(decodeSampledBitmapFromResource(getResources(), resId, 75, 75));

                    playCardPlaceSound();

                    //Get the card from the deck, place its value in the playerHand array
                    playerHand[playerHandIdx] = getCard(deck.get(idx));
                    //Place a reference to the card in the playerCards array
                    playerCards[playerHandIdx] = deck.get(idx);

                    //If the card is an ace
                    if (playerHand[playerHandIdx] == 1) {
                        playerNumAces++;
                        //If there is only one ace in the hand, make its value 11 as long as the
                        //hands sum is not over 21
                        if (playerNumAces == 1) {
                            if (sumHand(playerHand) + 10 <= 21) {
                                playerHand[playerHandIdx] = 11;
                            }
                        }
                    }

                    //Increment indexes
                    playerHandIdx++;
                    availableSlot++;
                    idx++;

                    //If the user's hand sum is over 21, make sure aces are not causing it
                    if (sumHand(playerHand) > 21) {
                        changeAces();
                    }

                    //The user busted by having a hand sum over 21, user loses
                    if (sumHand(playerHand) > 21) {
                        normalStick.setEnabled(false);
                        normalStick.setAlpha(0);
                        normalHit.setEnabled(false);
                        normalHit.setAlpha(0);

                        //Empty the player's hand so the value will be zero
                        playerHand = null;

                        //Check if the user bust on the other hand
                        if(splitHand == null) {
                            scoreText.setText("Busted!");
                            playAgain();
                        }
                        //Check if the user choose to stick the other hand
                        else if(!splitButton.isEnabled())
                            dealersTurn();
                    }

                    //The user got 21 off the first two cards which is Blackjack
                    if ((sumHand(playerHand) == 21) && (playerHandIdx == 2)) {
                        //Make sure the dealer does not have Blackjack before winning
                        if (!checkDealerBlackJack()) {
                            scoreText.setText("Black Jack!");
                            changeChips(userBet);
                            playAgain(); //user wins
                        }
                    }

                    //If the user has 5 cards in the hand and its sum is less than or equal to 21:
                    //This is known as 5 card Charlie, user wins automatically
                    if ((sumHand(playerHand) <= 21) && (playerHandIdx == 5)) {
                        scoreText.setText("You Win!");
                        changeChips(userBet);
                        playAgain();
                    }
                }
            });
        }
    }

    /*
    *   Method Name:    replay
    *   Method Type:    mutator
    *   Parameters:     View - (import only)
    *   Returns:        void
    *   Purpose:        This method resets the game and starts a new round
    */
    public void replay(View view) {
        Button playAgainButton = (Button) findViewById(R.id.playAgainButton);
        Button deal = (Button) findViewById(R.id.dealButton);
        Button reshuffleButton = (Button) findViewById(R.id.reshuffleButton);
        playAgainButton.setAlpha(0);
        playAgainButton.setEnabled(false);
        deal.setAlpha(1);
        deal.setEnabled(true);
        reshuffleButton.setAlpha(1);
        reshuffleButton.setEnabled(true);
        recycleHand();
        clearEverything();
    }

    /*
    *   Method Name:    recycleHand
    *   Method Type:    mutator
    *   Parameters:     n/a
    *   Returns:        void
    *   Purpose:        This method takes the cards from both the user's and the dealer's hand
    *                   and places it inside the recycle pile.
    */
    private void recycleHand() {
        //Get the user's cards
        for (int i = 0; i < playerHandIdx; i++) {
            Log.d("Player Cards", "" + playerCards[i]);
            recyclePile.add(playerCards[i]);
        }
        //Get the dealer's cards
        for (int i = 0; i < dealerHandIdx; i++) {
            Log.d("Dealer Cards", "" + dealerCards[i]);
            recyclePile.add(dealerCards[i]);
        }
        //Get the user's split hand cards
        for (int i = 0; i < splitHandIdx; i++) {
            Log.d("Dealer Cards", "" + splitCards[i]);
            recyclePile.add(splitCards[i]);
        }
    }

    /*
    *   Method Name:    clearEverything
    *   Method Type:    mutator
    *   Parameters:     n/a
    *   Returns:        void
    *   Purpose:        This method resets all indexes, arrays and ImageViews.
    */
    private void clearEverything() {
        TextView playerBetText = (TextView) findViewById(R.id.playerBetEditText);
        TextView gameMessage = (TextView) findViewById(R.id.userScoreText);
        availableSlot = 1;
        playerHandIdx = 0;
        playerNumAces = 0;
        playerHand = new int[5];
        playerCards = new Integer[5];

        splitAvailableSlot = 1;
        splitHandIdx = 0;
        splitNumAces = 0;
        splitHand = new int[5];
        splitCards = new Integer[5];

        dealerHandIdx = 0;
        dealerNumAces = 0;
        dealerHand = new int[5];
        dealerCards = new Integer[5];
        playerBetText.setEnabled(true);
        gameMessage.setText("");
        placedBet = false;

        //Remove all cards from the slots, point to null
        ImageView card1 = (ImageView) findViewById(R.id.cardSlot1);
        card1.setImageResource(0);
        ImageView card2 = (ImageView) findViewById(R.id.cardSlot2);
        card2.setImageResource(0);
        ImageView card3 = (ImageView) findViewById(R.id.cardSlot3);
        card3.setImageResource(0);
        ImageView card4 = (ImageView) findViewById(R.id.cardSlot4);
        card4.setImageResource(0);
        ImageView card5 = (ImageView) findViewById(R.id.cardSlot5);
        card5.setImageResource(0);
        ImageView dealer1 = (ImageView) findViewById(R.id.dealerSlot1);
        dealer1.setImageResource(0);
        ImageView dealer2 = (ImageView) findViewById(R.id.dealerSlot2);
        dealer2.setImageResource(0);
        ImageView dealer3 = (ImageView) findViewById(R.id.dealerSlot3);
        dealer3.setImageResource(0);
        ImageView dealer4 = (ImageView) findViewById(R.id.dealerSlot4);
        dealer4.setImageResource(0);
        ImageView dealer5 = (ImageView) findViewById(R.id.dealerSlot5);
        dealer5.setImageResource(0);
        ImageView split1 = (ImageView) findViewById(R.id.splitSlot1);
        split1.setImageResource(0);
        ImageView split2 = (ImageView) findViewById(R.id.splitSlot2);
        split2.setImageResource(0);
        ImageView split3 = (ImageView) findViewById(R.id.splitSlot3);
        split3.setImageResource(0);
        ImageView split4 = (ImageView) findViewById(R.id.splitSlot4);
        split4.setImageResource(0);
        ImageView split5 = (ImageView) findViewById(R.id.splitSlot5);
        split5.setImageResource(0);
    }

    /*
    *   Method Name:    endGame
    *   Method Type:    mutator
    *   Parameters:     View - (import only)
    *   Returns:        void
    *   Purpose:        This method ends the game by saving the new balance of the user and sending
    *                   the username as a message with an intent. The user will be taken to the
    *                   account page (UserAccountMain).
    */
    public void endGame(View view) {
        Intent intent = new Intent(this, UserAccountMain.class);
        intent.putExtra(EXTRA_MESSAGE, username);
        changeBalance(); //Update the balance in the database
        mydatabase.close(); //Close the database for security purposes
        startActivity(intent);
    }

    /*
    *   Method Name:    changeBalance
    *   Method Type:    mutator
    *   Parameters:     n/a
    *   Returns:        void
    *   Purpose:        This method changes the user's balance in the database to the new balance.
    */
    public void changeBalance() {
        TextView userChipsText = (TextView) findViewById(R.id.playerChipsText);
        int userChips = Integer.parseInt(userChipsText.getText().toString());
        //Update the balance in the database where the Username matches the user's username
        String query = "UPDATE BlackjackUsers SET Balance = " + userChips + "  WHERE Username = '" + username + "'";
        Cursor mycursor = mydatabase.rawQuery(query, null);
        mycursor.moveToFirst(); //Move to first, there should only be one
        mycursor.close(); //Close the cursor for security purposes
    }

    /*
    *   Method Name:    calculateInSampleSize
    *   Method Type:    mutator
    *   Parameters:     BitmapFactory.Options options - (import only)
    *                   int - width (import only)
    *                   int - height (import only)
    *   Returns:        static int
    *   Purpose:        This method resizes the bitmap to a preset width and height.
    *   Note:           This is not my code. I take no credit. Taken from Android API resources.
    */
    public static int calculateInSampleSize(
            BitmapFactory.Options options, int reqWidth, int reqHeight) {
        // Raw height and width of image
        final int height = options.outHeight;
        final int width = options.outWidth;
        int inSampleSize = 1;

        if (height > reqHeight || width > reqWidth) {

            final int halfHeight = height / 2;
            final int halfWidth = width / 2;

            // Calculate the largest inSampleSize value that is a power of 2 and keeps both
            // height and width larger than the requested height and width.
            while ((halfHeight / inSampleSize) > reqHeight
                    && (halfWidth / inSampleSize) > reqWidth) {
                inSampleSize *= 2;
            }
        }

        return inSampleSize;
    }

    /*
    *   Method Name:    decodeSampledBitmapFromResource
    *   Method Type:    mutator
    *   Parameters:     Resources - (import only)
    *                   int - resId (import only)
    *                   int - width (import only)
    *                   int - height (import only)
    *   Returns:        static Bitmap
    *   Purpose:        This method resizes the bitmap to a preset width and height.
    *   Note:           This is not my code. I take no credit. Taken from Android API resources.
    */
    public static Bitmap decodeSampledBitmapFromResource(Resources res, int resId,
                                                         int reqWidth, int reqHeight) {

        // First decode with inJustDecodeBounds=true to check dimensions
        final BitmapFactory.Options options = new BitmapFactory.Options();
        options.inJustDecodeBounds = true;
        BitmapFactory.decodeResource(res, resId, options);

        // Calculate inSampleSize
        options.inSampleSize = calculateInSampleSize(options, reqWidth, reqHeight);

        // Decode bitmap with inSampleSize set
        options.inJustDecodeBounds = false;
        return BitmapFactory.decodeResource(res, resId, options);
    }

    /*
    *   Method Name:    getDBPath
    *   Method Type:    facilitator
    *   Parameters:     Context - (import only)
    *   Return Value:   String
    *   Purpose:        This method gets the database path from the given Context and returns it.
    */
    public String getDBPath(Context context) {
        String path = context.getDatabasePath("blackjackDatabase").getPath();
        return path;
    }
}
