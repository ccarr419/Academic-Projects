package com.library.server_ui;
import com.library.server_layer.BorrowedBookServer;
import com.library.protocol.field_list.PBorrowedBook;
import java.util.ArrayList;

/**
* The role of the BorrowedBookServer is to let the server and user communicate 
* back and forth. This is done by reading/writing to the console. The 
* functionality of this server UI includes getting all borrowed books of a member.
* SERVER LAYER
*/
public class BorrowedBookServerUI {
    private BorrowedBookServer bbs;
    
    /**
    * Basic constructor that initializes its corresponding server.
    */
    public BorrowedBookServerUI() {
        bbs = new BorrowedBookServer();
    }
    
    /**
    * Finds and prints all borrowed books for a member with the session id.
    * If the user has no borrowed books they are told so. Only logged in
    * members with a valid session id may view borrowed books.
    * @param i int session id
    */
    public void borrowedBooks(int i) {
        bbs.update();
        System.out.println("Borrowed Books:");
        if(i <= 0) { //Only logged in members can view borrowed books
            System.out.println("You must be logged in to view borrowed books\n");
            return;
        }
        ArrayList<PBorrowedBook> pBBList = bbs.readBorrowedBook(i);
        if(pBBList.isEmpty()) { //There are no borrowed books for this member
            System.out.println("No Borrowed Books Currently");
            return;
        }
        String out = "";
        int bbCount = 0; //Iterate through and number each borrowed book
        for(PBorrowedBook pBB : pBBList) {
            out += (Integer.toString(++bbCount) + ".) ");
            out += pBB.toString();
            out += "\n";
        }
        System.out.println(out);
    }
}
