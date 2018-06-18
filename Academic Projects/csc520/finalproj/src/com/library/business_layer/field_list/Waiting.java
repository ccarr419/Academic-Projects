package com.library.business_layer.field_list;
import java.io.Serializable;
import java.util.Date;

/**
* The Waiting class represents a reservation that is waiting to be available. 
* Waiting contains the date the reservation was last renewed, the foreign key 
* to reservation id and a unique identifier. Identifiers are meant to act 
* similar to a primary key in a database and as such should be unique. Also 
* implements Serializable so it can be serialized for later use.
* BUSINESS LAYER CLASS
* @see com.library.business_layer.field_list.Reservation
*/
public class Waiting implements Serializable {
    private int id;
    private Date lastRenewedDate;
    private int reservationId;
        
    /**
    * Contstructs Waiting Object by setting its attributes to a value.
    * @param i identifier
    * @param d last renewed date
    * @param r reservation id
    */
    public Waiting(int i, Date d, int r) {
        setId(i);
        setLastRenewedDate(d);
        setReservationId(r);
    }
        
    /**
    * Gets the int identifier value for this Object.
    * @return id as int
    */
    public int getId() { return id; }
    
    /**
    * Gets the date the reservation was last renewed.
    * @return date last renewed Date
    */
    public Date getLastRenewedDate() { return lastRenewedDate; }
    
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
    * Sets the value for the date the reservation was last renewed.
    * @param lrd Date to set last renewed date to
    */
    public void setLastRenewedDate(Date lrd) { lastRenewedDate = lrd; }
    
    /**
    * Sets the value for the reservation id.
    * @param i int to set reservation id to
    */
    public void setReservationId(int i) { reservationId = i; }
}