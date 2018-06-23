package com.library.business_layer.field_list;
import java.io.Serializable;
import java.util.Date;

/**
* A Collectable represents a reservation that can be collected i.e. is ready
* to be picked up. Collectable contains the date the user who made the
* reservation was notified, the foreign key to reservation id, and a unique
* identifier. Identifiers are meant to act similar to a primary key in a 
* database and as such should be unique. Also implements Serializable so it 
* can be serialized for later use.
* BUSINESS LAYER CLASS
* @see com.library.business_layer.field_list.Reservation
*/
public class Collectable implements Serializable {
    private int id;
    private Date dateNotified;
    private int reservationId;
        
    /**
    * Contstructs Collectable Object by setting its attributes to a value.
    * @param i identifier
    * @param d date notified
    * @param r reservation id
    */
    public Collectable(int i, Date d, int r) {
        setId(i);
        setDateNotified(d);
        setReservationId(r);
    }
        
    /**
    * Gets the int identifier value for this Object.
    * @return id as int
    */
    public int getId() { return id; }
        
    /**
    * Gets the Date the user was notified of Collectable.
    * @return date notified Date
    */
    public Date getDateNotified() { return dateNotified; }
    
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
    * Sets the value for the date notified.
    * @param d Date to set date notified to
    */
    public void setDateNotified(Date d) { dateNotified = d; }
    
    /**
    * Sets the value for the reservation id.
    * @param i int to set reservation id to
    */
    public void setReservationId(int i) { reservationId = i; }
}