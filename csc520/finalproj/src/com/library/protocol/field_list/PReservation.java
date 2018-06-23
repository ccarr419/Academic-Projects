package com.library.protocol.field_list;
import com.library.business_layer.field_list.Reservation;
import java.sql.Timestamp;

/**
* PReservation serves as a protocol to transfer Table information from the server
* to the UI. Only serves as a way to view, print and facilitate information.
* PROTOCOL LAYER
* @see com.library.business_layer.field_list.Reservation
*/
public class PReservation {
    private String number;
    private Timestamp timestamp;
    
    /**
    * Basic constructor that sets all attributes.
    * @param n String reservation number
    * @param t Timestamp
    */
    public PReservation(String n, Timestamp t) {
        number = n;
        timestamp = t;
    }
        
    /**
    * @return String reservation number
    * @see com.library.business_layer.field_list.Reservation#getNumber()
    */
    public String getNumber() { return number; }
      
    /**
    * @return Timestamp
    * @see com.library.business_layer.field_list.Reservation#getTimestamp()
    */
    public Timestamp getTimestamp() { return timestamp; }
    
    /**
    * Prints the Reservation in a human understandable summary.
    */
    public String toString() {
        String out = "";
        out += ("(" + getNumber() + ") " + getTimestamp().toString());
        return out;
    }
}