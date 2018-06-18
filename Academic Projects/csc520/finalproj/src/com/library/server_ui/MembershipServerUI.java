package com.library.server_ui;
import com.library.server_layer.MembershipServer;
import com.library.protocol.field_list.PMember;
import com.library.protocol.field_list.PCreditCard;
import com.library.protocol.field_list.PAddress;
import java.util.Arrays;
import java.util.Scanner;
import java.io.Console;

/**
* The role of the MembershipServerUI is to let the server and user communicate 
* back and forth. This is done by reading/writing to the console. The 
* functionality of this server UI includes printing account information and the
* option for a member to change their password.
* SERVER LAYER
*/
public class  MembershipServerUI {
    private MembershipServer ms;
    
    /**
    * Basic constructor that initializes its corresponding server.
    */
    public MembershipServerUI() {
        ms = new MembershipServer();
    }
    
    /**
    * Prints the member with the session id's account information. Only logged
    * in members can view account details. Fails if a member does not exist
    * with that session id.
    * @param sess int session id
    */
    public void member(int sess) {
        ms.update();
        if(sess <= 0) { //Only logged in users can view account info
            System.out.println("You must be logged in to view account information\n");
            return;
        }
        PMember pMem = ms.readMember(sess);
        PCreditCard pCC = ms.readCreditCard(sess);
        PAddress pADD = ms.readAddress(sess);
        if(pMem != null && pCC != null && pADD != null) {
            System.out.println("ACCOUNT INFORMATION");
            System.out.println(pMem.toString());
            System.out.println("PAYMENT INFORMATION");
            System.out.println(pCC.toString());
            System.out.println("ADDRESS INFORMATION");
            System.out.println(pADD.toString());
        }
        else { System.out.println("An error has occurred\n"); }
    }
    
    /**
    * Prints the member with the session id's password information. Only logged
    * in members can view password details. Fails if a member does not exist
    * with that session id. Actual password is not shown for security reasons.
    * @param i int session id
    */
    public void password(int i) {
        if(i <= 0) { //Only logged in users can view password info
            System.out.println("You must be logged in to view password information\n");
            return;
        }
        ms.update();
        char[] currentPass = new char[ms.readPassword(i).length()];
        Arrays.fill(currentPass, '*');
        System.out.println("Current Password: " + new String(currentPass) + "\n");    
    }
    
    /**
    * Allows a member to change their password. Lets the member enter their
    * old password and a new password. If the old password matches and the new
    * password is not the same as the old one, the member is taken to the
    * confirm page. Otherwise the password change fails. A user must be logged
    * in to change their password.
    * @param i int session id
    * @param reader Scanner read user input
    */
    public void changePassword(int i, Scanner reader) {
        if(i <= 0) { //Only logged in users can change password
            System.out.println("You must be logged in to change password\n");
            return;
        }
        ms.update();
        String choice = ""; //Confirm with the user if they want to change
        while(!(choice.toLowerCase().equals("y") || choice.toLowerCase().equals("n"))) {
            System.out.print("Change your password? [y/n]: ");
            choice = reader.nextLine();
        }
        if(choice.toLowerCase().equals("n")) { return; }
        String oldPass = "", newPass = "";
        Console console = System.console(); //Get old password for clearance
        System.out.print("Please enter old password: ");
        oldPass = new String(console.readPassword()); //Get new password
        System.out.print("Please enter new password: ");
        newPass = new String(console.readPassword());
        
        String checkPass = ms.readPassword(i);
        if(oldPass.equals(newPass)) { //Make sure new password is not the old one
            System.out.println("New password cannot be the same as old password\n");
        }
        else if(checkPass.equals(oldPass)) { //Make sure the old password matches
            confirm(i, oldPass, newPass, reader);
        }
        else {
            System.out.println("The old password entered was not correct\n");
        }
    }
    
    /**
    * Confirms if the member wants to change their password. If the member
    * wishes to continue, the password will attempt to be changed.
    * @param i int session id
    * @param o String old password
    * @param n String new password
    * @param reader Scanner read user input
    */
    public void confirm(int i, String o, String n, Scanner reader) {
        if(i <= 0) {
            System.out.println("You must be logged in to change password\n");
            return;
        }
        ms.update();
        String choice = "";
        while(!(choice.toLowerCase().equals("y") || choice.toLowerCase().equals("n"))) {
            System.out.print("Confirm change? [y/n]: ");
            choice = reader.nextLine();
        }
        if(choice.toLowerCase().equals("n")) { 
            System.out.println("Aborting new password request\n"); 
        }
        else {
            if(ms.changePassword(i, o, n)) {
                System.out.println("You have successfully changed your password\n");
            }
            else { System.out.println("An error has occured\n"); }
        }
    }
}
