/*
*   Author:     Christian Carreras
*   File:       UserAccountMain.java
*   Date:       04/27/2016
*   Class:      Kutztown University of Pennsylvania, CSC 330 Mobile Development
*   Purpose:    This java file holds the functionality for the user account page.
*               The user must first log in to view this page. Upon log in,
*               the user will see his/her username and current balance.
*               They will also have the option to start playing or log out.
*/

package com.example.christiancarreras.blackjack;

import android.content.Intent; //For creating Intent objects to switch activities
import android.content.Context; //For creating Context objects to get the database path
import android.database.Cursor; //For creating Cursor objects to search through the database
import android.database.sqlite.SQLiteDatabase; //Tools and methods for SQLite usage
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View; //Allows for communication between the view and back
import android.widget.TextView; //For creating TextView reference objects

public class UserAccountMain extends AppCompatActivity {
    //This string will be sent with the intent so a message can be sent with it.
    public final static String EXTRA_MESSAGE = "com.example.christiancarreras.blackjack.MESSAGE";
    SQLiteDatabase mydatabase; //Database that holds all users
    String username; //Current user logged in

    /*
    *   Method Name:    onCreate
    *   Method Type:    n/a
    *   Parameters:     Bundle - (import only)
    *   Return Value:   void
    *   Purpose:        Opens the database and finds the user who logged by the username that was
    *                   sent in the intent message from LoginMain.java. After finding the users row,
    *                   it will get the user's balance from the Balance column of the database and
    *                   display that in the appropriate text box.
    */
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_account);

        //Open the database and allow modification
        mydatabase = SQLiteDatabase.openDatabase(getDBPath(getApplicationContext()), null, SQLiteDatabase.OPEN_READWRITE);
        TextView usernameText = (TextView) findViewById(R.id.usernameText);
        Intent intent = getIntent(); //Retrieve intent from previous activity
        //Get the username sent as a message from the login page
        username = intent.getStringExtra(LoginMain.EXTRA_MESSAGE);

        //If the username is null, the message must have been sent from the game page (MainActivity)
        if(username == null)
            username = intent.getStringExtra(MainActivity.EXTRA_MESSAGE);

        //Display the user's username and balance
        usernameText.setText("Welcome, " + username);
        getBalance();
    }

    /*
    *   Method Name:    play
    *   Method Type:    n/a
    *   Parameters:     View - (import only)
    *   Return Value:   void
    *   Purpose:        This method will first close the database for security purposes.
    *                   After the database is closed, an intent will be created with an extra
    *                   message of the user's username. The intent will be started and the user
    *                   will be taken to the game screen (MainActivity).
    */
    public void play(View view) {
        mydatabase.close();
        //Create an intent and send the username as a message so the next activity can retrieve
        //the user's balance
        Intent intent = new Intent(this, MainActivity.class);
        intent.putExtra(EXTRA_MESSAGE, username);
        startActivity(intent);
    }

    /*
    *   Method Name:    logout
    *   Method Type:    n/a
    *   Parameters:     View - (import only)
    *   Return Value:   void
    *   Purpose:        This method will first close the database for security purposes.
    *                   After the database is closed, an intent will be created that will take
    *                   the user back to the log in screen (LoginMain.java). The user will have to
    *                   log back in again if he/she wishes to view this page.
    */
    public void logout(View view) {
        mydatabase.close();
        Intent intent = new Intent(this, LoginMain.class);
        startActivity(intent);
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

    /*
    *   Method Name:    getBalance
    *   Method Type:    mutator
    *   Parameters:     n/a
    *   Return Value:   void
    *   Purpose:        This method gets the user's balance from the database's Balance column by
    *                   searching for the row where the user's username resides. The cursor will
    *                   then point to the user's balance. From there the string holding the user's
    *                   balance is placed in the balance TextView.
    */
    public void getBalance() {
        TextView userBalanceText = (TextView) findViewById(R.id.playerBalanceText);
        //Create a query to select the user's balance from the database by finding a row
        //where the Username value matches the user's username
        String query = "SELECT Balance FROM BlackjackUsers WHERE Username = '" + username + "'";
        Cursor mycursor = mydatabase.rawQuery(query, null);
        if(mycursor.moveToFirst()) //Go to the first (there will only be one) and get the balance
            userBalanceText.setText(mycursor.getString(mycursor.getColumnIndex("Balance")));
        mycursor.close(); //Close the cursor to insure security
    }
}
