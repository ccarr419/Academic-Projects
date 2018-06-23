package com.library.server_ui;
import com.library.server_layer.AuthenticationServer;
import java.util.Scanner;
import java.io.Console;

/**
* The role of the AuthenticationServerUI is to let the server and user
* communicate back and forth. This is done by reading/writing to the console.
* The functionality of this server UI includes logging on and off.
* SERVER LAYER
*/
public class AuthenticationServerUI {
    private AuthenticationServer as;
    
    /**
    * Basic constructor that initializes its corresponding server.
    */
    public AuthenticationServerUI() {
        as = new AuthenticationServer();
    }
    
    /**
    * Lets the user enter their user number and password. Credentials are then
    * checked for correctness by looking through corresponding Tables. If the
    * credentials match an existing account, the user will be logged in to
    * a session id. If there is no match, the user is told. The user may also
    * choose to steal an existing session if applicable. Session ids are
    * generated to be unique to each account unless stolen. Accounts that have
    * their session stolen should be logged out.
    * @param reader Scanner read user input
    * @return int the unique or stolen session id, -1 if log in failed
    */
    public int logon(Scanner reader) {
        as.update();
        String num = "", pass = "", steal = "";
        Console console = System.console();
        boolean s;
        while(num.equals("")) { //Get user number
            System.out.print("User Number: ");
            num = reader.nextLine();
        }
        while(pass.equals("")) { //Get user password
            System.out.print("Password: ");
            pass = new String(console.readPassword());
        } //Ask if the user wishes to steal an existing session
        while(!(steal.toLowerCase().equals("y") || steal.toLowerCase().equals("n"))) {
            System.out.print("Steal an existing session? [y/n]: ");
            steal = reader.nextLine();
        }
        if(steal.toLowerCase().equals("y")) { s = true; }
        else { s = false; }
        int sess = as.logon(num, pass, s);
        if(sess > 0) { //User got a session id, they are logged in
            System.out.println("You have successfully logged on\n");
        }
        else { //User log in has failed
            System.out.println("User number or password was incorrect\n");
        }
        return sess;
    }
    
    /**
    * Attempts to log off a user with the session id. Only fails if there
    * is no user with that session id.
    * @param i int session id
    */
    public void logoff(int i) {
        as.update();
        System.out.println("Logging off...");
        if(as.logoff(i)) {
            System.out.println("You have successfully logged off\n");
        }
        else {
            System.out.println("An error has occurred when logging off\n");
        }
    }
}
