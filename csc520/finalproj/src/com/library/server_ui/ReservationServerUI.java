package com.library.server_ui;
import com.library.server_layer.ReservationServer;
import com.library.protocol.field_list.PReservation;
import com.library.protocol.field_list.PCatalogedBook;
import java.util.ArrayList;
import java.sql.Timestamp;
import java.util.Scanner;
import java.util.Date;

/**
* The role of the ReservationServerUI is to let the server and user communicate 
* back and forth. This is done by reading/writing to the console. The 
* functionality of this server UI includes reserving a book, viewing member
* reservations and cancelling an existing reservation.
* SERVER LAYER
*/
public class ReservationServerUI {
    private ReservationServer rs;
    
    /**
    * Basic constructor that initializes its corresponding server.
    */
    public ReservationServerUI() {
        rs = new ReservationServer();
    }
    
    /**
    * Reserves a book for the member with the session id. Only logged in users
    * can reserve a book. Members will have to confirm the reservation.
    * @param i int session id
    * @param c int CatalogedBook id
    * @param reader Scanner read user input
    */
    public void reserve(int i, int c, Scanner reader) {
        if(i <= 0) { //Only logged in users can reserve a book
            System.out.println("You must be logged in to create a reservation\n");
            return;
        }
        String choice = ""; //Confirm the reservation
        while(!(choice.toLowerCase().equals("y") || choice.toLowerCase().equals("n"))) {
            System.out.print("Confirm reservation? [y/n]: ");
            choice = reader.nextLine();
        }
        if(choice.toLowerCase().equals("n")) {
            System.out.println("Aborting reservation request\n"); 
        }
        else { confirmReservation(i, c); }
    }
    
    /**
    * Confirms the book reservation for the member with the session id.
    * @param i int session id
    * @param c int CatalogedBook id
    */
    public void confirmReservation(int i, int c) {
        if(i <= 0) { //Only logged in users can reserve a book
            System.out.println("You must be logged in to create a reservation\n");
            return;
        }
        rs.update();
        PReservation res = rs.createReservation(i, c);
        ok(res);
    }
    
    /**
    * Tells the user that the book was reserved or there was an error.
    * @param r PReservation
    */
    public void ok(PReservation r) {
        if(r != null) { //If the reservation was created
            System.out.println("You have successfully reserved this book!\n");
        }
        else { //No reservation was created
            System.out.println("There was an error reserving this book\n");
        }
    }
    
    /**
    * Prints all reservations for a member with the session id. Only logged in
    * users can view reservations. Reservations are printed in order of creation.
    * @param i int session id
    */
    public void reservations(int i) {
        if(i <= 0) { //User must be logged in to view reservations
            System.out.println("You must be logged in to view reservations\n");
            return;
        }
        rs.update(); //Check to make sure there are reservations for user
        ArrayList<PReservation> resList = rs.readReservations(i);
        ArrayList<PCatalogedBook> books = rs.readReservedBooks(i);
        if(resList.isEmpty() || books.isEmpty()) {
            System.out.println("No Reservations At This Time");
        } //Print book title and reservation information in timestamp order
        for(int j = 0; j < resList.size(); j++) {
            System.out.println("" + (j+1) + ".) " + 
                books.get(j).toString() + " " + resList.get(j));
        }
        System.out.println("");
    }
    
    /**
    * Cancels a book reservation for the member with the session id. Only logged
    * in users can cancel a reservation. Members will have to confirm the 
    * reservation cancel request.
    * @param i int session id
    * @param r int Reservation id
    * @param reader Scanner read user input
    */
    public void cancel(int i, int r, Scanner reader) {
        if(i <= 0) { //Only logged in users can cancel a reservation
            System.out.println("You must be logged in to cancel a reservation\n");
            return;
        }
        String choice = ""; //Confirm the reservation cancellation request
        while(!(choice.toLowerCase().equals("y") || choice.toLowerCase().equals("n"))) {
            System.out.print("Cancel reservation? [y/n]: ");
            choice = reader.nextLine();
        }
        if(choice.toLowerCase().equals("n")) { 
            System.out.println("Aborting reservation cancellation request\n"); 
        }
        else { confirmCancel(i, r); }
    }
    
    /**
    * Confirms the cancellation of a book reservation for the member with the 
    * session id.
    * @param i int session id
    * @param r int Reservation id
    */
    public void confirmCancel(int i, int r) {
        if(i <= 0) { //Only logged in users can cancel a reservation
            System.out.println("You must be logged in to cancel a reservation\n");
            return;
        }
        rs.update();
        if(rs.cancelReservation(i, r)) { //Reservation was cancelled
            System.out.println("Reservation has been successfully cancelled\n");
        }
        else { //Reservation was not found
            System.out.println("There was an error cancelling this reservation\n");
        }
    }
}
