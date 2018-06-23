package com.library.business_layer.field_list;
import java.io.Serializable;

/**
* A Concluded represents a reservation that is concluded i.e. terminated
* through various means. Concluded contains the reason the reservation was
* concluded, the foreign key to reservation id, and a unique identifier.
* Identifiers are meant to act similar to a primary key in a database and 
* as such should be unique. Also implements Serializable so it can be 
* serialized for later use.
* BUSINESS LAYER CLASS
* @see com.library.business_layer.field_list.Reservation
*/
public class Concluded implements Serializable {
    private int id;
    private String reason;
    private int reservationId;
        
    /**
    * Contstructs Concluded Object by setting its attributes to a value.
    * @param i identifier
    * @param r reason
    * @param ri reservation id
    */
    public Concluded(int i, String r, int ri) {
        setId(i);
        setReason(r);
        setReservationId(ri);
    }
        
    /**
    * Gets the int identifier value for this Object.
    * @return id as int
    */
    public int getId() { return id; }
        
    /**
    * Gets the reason the reservation was concluded.
    * @return reason String
    */
    public String getReason() { return reason; }
    
    /**
    * Gets the indentifier for the reservation.
    * @return reservation id int
    */
    public int getReservationId() { return reservationId; }
        
    /**
    * Sets the value for the Object identifier.
    * @param i int to set id to
    */
    public void setId(int i) { id = i; }
        
    /**
    * Sets the value for the reason the reservation was concluded.
    * @param r String to set reason to
    */
    public void setReason(String r) { reason = r; }
    
    /**
    * Sets the value for the reservation id.
    * @param i int to set reservation id to
    */
    public void setReservationId(int i) { reservationId = i; }
}