package com.library.business_layer.field_list;
import java.io.Serializable;
import java.util.Date;

/**
* The CreditCard class represents a real-life credit or debit card.
* A CreditCard Object contains the card type, number, exiration date and a 
* unique identifier. Identifiers are meant to act similar to a primary key 
* in a database and as such should be unique. Also implements Serializable 
* so it can be serialized for later use.
* BUSINESS LAYER CLASS
*/
public class CreditCard implements Serializable {
    private int id;
    private String type;
    private String number;
    private Date expiration;
        
    /**
    * Contstructs CreditCard Object by setting its attributes to a value.
    * @param i identifier
    * @param t type
    * @param n number
    * @param e expiration date
    */
    public CreditCard(int i, String t, String n, Date e) {
        setId(i);
        setType(t);
        setNumber(n);
        setExpiration(e);
    }
     
    /**
    * Gets the int identifier value for this Object.
    * @return id as int
    */
    public int getId() { return id; }
        
    /**
    * Gets the type of CreditCard as a String.
    * @return type String
    */
    public String getType() { return type; }
        
    /**
    * Gets the number on the CreditCard as a String.
    * @return number String
    */
    public String getNumber() { return number; }
        
    /**
    * Gets the exipriation date on the CreditCard as a Date Object.
    * @return expiration Date
    */
    public Date getExpiration() { return expiration; }
    
    /**
    * Sets the value for the Object identifier.
    * @param i int to set id to
    */
    public void setId(int i) { id = i; }
        
    /**
    * Sets the value for CreditCard type.
    * @param t String to set type to
    */
    public void setType(String t) { type = t; }
        
    /**
    * Sets the value for CreditCard number.
    * @param n String to set number to
    */
    public void setNumber(String n) { number = n; }
        
    /**
    * Sets the value for CreditCard exipiration date.
    * @param e Date to set expiration date to
    */
    public void setExpiration(Date e) { expiration = e; }
}