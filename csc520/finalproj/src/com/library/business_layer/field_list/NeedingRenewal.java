package com.library.business_layer.field_list;
import java.io.Serializable;
import java.util.Date;

/**
* The NeedingRenewal class represents a reservation that must be renewed in
* the near future to avoid penalties. NeedingRenewal contains the date the 
* reservation needs to be renewed, the foreign key to reservation id, and a 
* unique identifier. Identifiers are meant to act similar to a primary key 
* in a database and as such should be unique. Also implements Serializable
* so it can be serialized for later use.
* BUSINESS LAYER CLASS
* @see com.library.business_layer.field_list.Reservation
*/
public class NeedingRenewal implements Serializable {
    private int id;
    private Date dateRenewalNeeded;
    private int reservationId;
        
    /**
    * Contstructs NeedingRenewal Object by setting its attributes to a value.
    * @param i identifier
    * @param d date renewal needed
    * @param r reservation id
    */
    public NeedingRenewal(int i, Date d, int r) {
        setId(i);
        setDateRenewalNeeded(d);
        setReservationId(r);
    }
        
    /**
    * Gets the int identifier value for this Object.
    * @return id as int
    */
    public int getId() { return id; }
        
    /**
    * Gets the date the reservation needs to be renewed by.
    * @return date renewal needed Date
    */
    public Date getDateRenewalNeeded() { return dateRenewalNeeded; }
    
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
    * Sets the value for the date the reservation needs renewal.
    * @param drn Date to set date renewal needed to
    */
    public void setDateRenewalNeeded(Date drn) { dateRenewalNeeded = drn; }
    
    /**
    * Sets the value for the reservation id.
    * @param i int to set reservation id to
    */
    public void setReservationId(int i) { reservationId = i; }
}