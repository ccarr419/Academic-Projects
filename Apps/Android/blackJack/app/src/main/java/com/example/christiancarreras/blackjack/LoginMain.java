/*
*   Author:     Christian Carreras
*   File:       LoginMain.java
*   Date:       04/27/2016
*   Class:      Kutztown University of Pennsylvania, CSC 330 Mobile Development
*   Purpose:    This java file holds the functionality for the log in page.
*               This is the first page the user will see when opening the app. The app will
*               prompt the user to enter a username and password to create an account or login.
*               If an account already exists, the user can log into that account; it will not be
*               able to be created. Vice versa an uncreated account cannot be logged into.
*/

package com.example.christiancarreras.blackjack;

import android.database.sqlite.SQLiteDatabase; //Tools and methods for SQLite usage
import android.database.Cursor; //For creating Cursor objects to search through the database
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View; //Allows for communication between the view and back
import android.content.Intent; //For creating Intent objects to switch activities
import android.widget.EditText; //For creating EditText reference objects
import android.widget.Toast; //For created Toast objects to show pop-up messages on screen

public class LoginMain extends AppCompatActivity {
    SQLiteDatabase mydatabase; //Database that holds all users
    //This string will be sent with the intent so a message can be sent with it.
    public final static String EXTRA_MESSAGE = "com.example.christiancarreras.blackjack.MESSAGE";

    /*
    *   Method Name:    onCreate
    *   Method Type:    n/a
    *   Parameters:     Bundle - (import only)
    *   Return Value:   void
    *   Purpose:        Creates a database if one does not exist. Then creates a table in that
    *                   database with the columns: Username, Password and Balance. If the database
    *                   exists then it will just be opened.
    */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login_main);
        //Create the database if it does not exist. Just open it if it does
        mydatabase = openOrCreateDatabase("blackjackDatabase", MODE_PRIVATE, null);
        //Create a table for user info in the database if it does not exist already
        mydatabase.execSQL("CREATE TABLE IF NOT EXISTS BlackjackUsers(Username VARCHAR,Password VARCHAR,Balance INTEGER);");
    }

    /*
    *   Method Name:    login
    *   Method Type:    facilitator
    *   Parameters:     View - (import only)
    *   Return Value:   void
    *   Purpose:        Will check to make sure a username and password is entered with an
    *                   appropriate length. If a password and username of appropriate length is
    *                   entered then the user will be authenticated. If the account exists, the
    *                   user will be logged on and will be taken to the next page. If not, the
    *                   user will remain on the page and will be told the account does not exit.
    */
    public void login(View view) {
        EditText usernameText = (EditText) findViewById(R.id.usernameText);
        EditText passwordText = (EditText) findViewById(R.id.passwordText);
        String username = usernameText.getText().toString();
        String password = passwordText.getText().toString();

        //Username must be 3 or more characters, password must be 5 or more characters
        if(username.length() >= 3 && password.length() >= 5) {
            //Check if the account exists
            if (authenticate(username, password)) {
                //The account exists and is authenticated, move to the next page
                Intent intent = new Intent(this, UserAccountMain.class);
                //Send the user's username as a message so the balance can be retrieved
                //and displayed in the next activity (UserAccountMain)
                intent.putExtra(EXTRA_MESSAGE, username);
                mydatabase.close(); //Close the database for security purposes
                startActivity(intent);
            }
            else //The account does not exist, inform the user
                Toast.makeText(getApplicationContext(), "Account Does Not Exist", Toast.LENGTH_LONG).show();
        }
        else //The username/password is not long enough to match
            Toast.makeText(getApplicationContext(), "Please Enter A Longer Username And/Or Password", Toast.LENGTH_LONG).show();
    }

    /*
    *   Method Name:    createAccount
    *   Method Type:    mutator
    *   Parameters:     View - (import only)
    *   Return Value:   void
    *   Purpose:        Will first check if the username and password entered are of appropriate
    *                   length. Then there will be a check as to whether that account exists
    *                   already. If the account does not exist yet, it will be inserted into the
    *                   database. If it does, the user will be informed that account already exists.
    */
    public void createAccount(View view) {
        EditText usernameText = (EditText) findViewById(R.id.usernameText);
        EditText passwordText = (EditText) findViewById(R.id.passwordText);
        String username = usernameText.getText().toString();
        String password = passwordText.getText().toString();

        //Username must be 3 or more characters, password must be 5 or more characters
        if(username.length() >= 3 && password.length() >= 5) {
            //Check to see if the account already exists
            if(!checkEntries(username)) {
                //The account does not exist yet, create the account for the user
                mydatabase.execSQL("INSERT INTO BlackjackUsers VALUES('" + username + "','" + password + "','" + 1000 + "');");
                Toast.makeText(getApplicationContext(), "Account Created", Toast.LENGTH_LONG).show();
            }
            else //The account already exists, inform the user
                Toast.makeText(getApplicationContext(), "Account Exists Already", Toast.LENGTH_LONG).show();
        }
        else //The username/password is not of appropriate length
            Toast.makeText(getApplicationContext(), "Please Enter A Longer Username And/Or Password", Toast.LENGTH_LONG).show();
    }

    /*
    *   Method Name:    checkEntries
    *   Method Type:    facilitator
    *   Parameters:     String - (import only)
    *   Return Value:   boolean (true if entry exists, false if not)
    *   Purpose:        Checks the database for any rows that have a Username value that
    *                   matches the user's username. If there is a row, return true, else
    *                   return false.
    */
    private boolean checkEntries(String username) {
        //Select all the rows from the database where the Username value = the user's username
        String query = "SELECT * FROM BlackjackUsers WHERE Username = '" + username + "'";
        Cursor mycursor = mydatabase.rawQuery(query, null);
        if(mycursor.getCount() <= 0) //The query returned no results
            return false;
        mycursor.close();
        return true;
    }

    /*
    *   Method Name:    authenticate
    *   Method Type:    facilitator
    *   Parameters:     String - (import only)
    *                   String - (import only)
    *   Return Value:   boolean - (true if entry exists, false if not)
    *   Purpose:        Similar to the checkEntries method except the username and password must
    *                   both be validated.
    */
    private boolean authenticate(String username, String password) {
        //Select all rows from the database where the username and password match
        String query = "SELECT * FROM BlackjackUsers WHERE Username = '" + username + "' AND Password = '" + password + "'";
        Cursor mycursor = mydatabase.rawQuery(query, null);
        if(mycursor.getCount() <= 0) //The query returned no results
            return false;
        mycursor.close();
        return true;
    }
}
