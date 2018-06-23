package com.library.business_layer.field_list;
import java.io.Serializable;
import java.util.Date;

/**
* The Notifiable class represents a reservation that was moved aside for
* the person who made the reservation. Notifiable contains the date the 
* reservation was put aside, the foreign key to reservation id, and a 
* unique identifier. Identifiers are meant to act similar to a primary key 
* in a database and as such should be unique. Also implements Serializable
* so it can be serialized for later use.
* BUSINESS LAYER CLASS
* @see com.library.business_layer.field_list.Reservation
*/
public class Notifiable implements Serializable {
    private int id;
    private Date datePutAside;
    private int reservationId;
        
    /**
    * Contstructs Notifiable Object by setting its attributes to a value.
    * @param i identifier
    * @param d date put aside
    * @param r reservation id
    */
    public Notifiable(int i, Date d, int r) {
        setId(i);
        setDatePutAside(d);
        setReservationId(r);
    }
        
    /**
    * Gets the int identifier value for this Object.
    * @return id as int
    */
    public int getId() { return id; }
        
    /**
    * Gets the date the reservation was put aside.
    * @return date put aside Date
    */
    public Date getDatePutAside() { return datePutAside; }
    
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
    * Sets the value for the date the reservation was put aside.
    * @param dpa Date to set date renewal needed to
    */
    public void setDatePutAside(Date dpa) { datePutAside = dpa; }
    
    /**
    * Sets the value for the reservation id.
    * @param i int to set reservation id to
    */
    public void setReservationId(int i) { reservationId = i; }
}