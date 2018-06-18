package com.library.business_layer.field_list;
import java.io.Serializable;
import java.sql.Timestamp;

/**
* The Reservation class represents a real-word scenario where a member reserves
* a book so they are guaranteed to have it next when next available.
* Reservation contains the reservation number, timestamp, foreign key to 
* Member id, CatalogedBook id and a unique identifier. Identifiers are meant 
* to act similar to a primary key in a database and as such should be unique. 
* Also implements Serializable so it can be serialized for later use. 
* Reservation acts as basis and foundation for all reservation states.
* BUSINESS LAYER CLASS
* @see com.library.business_layer.field_list.Collectable
* @see com.library.business_layer.field_list.Concluded
* @see com.library.business_layer.field_list.Displayable
* @see com.library.business_layer.field_list.NeedingRenewal
* @see com.library.business_layer.field_list.Notifiable
* @see com.library.business_layer.field_list.Waiting
*/
public class Reservation implements Serializable {
    private int id;
    private String number;
    private Timestamp timestamp;
    private int memberId;
    private int catalogedBookId;
        
    /**
    * Contstructs Reservation Object by setting its attributes to a value.
    * @param i identifier
    * @param n number
    * @param t timestamp
    * @param m member id
    * @param c cataloged book id
    */
    public Reservation(int i, String n, Timestamp t, int m, int c) {
        setId(i);
        setNumber(n);
        setTimestamp(t);
        setMemberId(m);
        setCatalogedBookId(c);
    }
        
    /**
    * Gets the int identifier value for this Object.
    * @return id as int
    */
    public int getId() { return id; }
        
    /**
    * Gets the Reservation number as a String.
    * @return number String
    */
    public String getNumber() { return number; }
        
    /**
    * Gets the Reservation timestamp as a Timeestamp.
    * @return timestamp Timestamp
    */
    public Timestamp getTimestamp() { return timestamp; }
    
    /**
    * Gets the Reservation Member identification.
    * @return member int
    */
    public int getMemberId() { return memberId; }
    
    /**
    * Gets the Reservation CatalogedBook identification.
    * @return cataloged book int
    */
    public int getCatalogedBookId() { return catalogedBookId; }
        
    /**
    * Sets the value for the Object identifier.
    * @param i int to set id to
    */
    public void setId(int i) { id = i; }
    
    /**
    * Sets the value for the Reservation's number.
    * @param n String to set number to
    */
    public void setNumber(String n) { number = n; }
        
    /**
    * Sets the value for the Reservation's Timestamp.
    * @param t Timestamp to set timestamp to
    */
    public void setTimestamp(Timestamp t) { timestamp = t; }
    
    /**
    * Sets the value for the Reservation's Member identification.
    * @param i int to set member id to
    */
    public void setMemberId(int i) { memberId = i; }
    
    /**
    * Sets the value for the Reservation's CatalogedBook identification.
    * @param i int to set cataloged book id to
    */
    public void setCatalogedBookId(int i) { catalogedBookId = i; }
}