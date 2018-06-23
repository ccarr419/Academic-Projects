package com.library.business_layer.field_list;
import java.io.Serializable;
import java.util.Date;

/**
* The BorrowedBook class represents a scenario where a book has been borrowed.
* BorrowedBook contains the unique number for the borrowed book, the date the
* book was borrowed, the date the book should be returned as well as its
* unique identifier. Identifiers are meant to act similar to a primary key 
* in a database and as such should be unique. Also implements Serializable so 
* it can be serialized for later use.
* BUSINESS LAYER CLASS
*/
public class BorrowedBook implements Serializable {
    private int id;
    private String number;
    private Date startDate;
    private Date dueDate;
    
    /**
    * Contstructs BorrowedBook Object by setting its attributes to a value.
    * @param i identifier
    * @param n number
    * @param s start date
    * @param e due date
    */
    public BorrowedBook(int i, String n, Date s, Date e) {
        setId(i);
        setNumber(n);
        setStartDate(s);
        setDueDate(e);
    }
        
    /**
    * Gets the int identifier value for this Object.
    * @return id as int
    */
    public int getId() { return id; }
    
    /**
    * Gets the BorrowedBook number as a String.
    * @return number String
    */
    public String getNumber() { return number; }
    
    /**
    * Gets the borrow start date as a Date Object.
    * @return start date Date
    */
    public Date getStartDate() { return startDate; }
    
    /**
    * Gets the borrow due date as a Date Object.
    * @return due date Date
    */
    public Date getDueDate() { return dueDate; }
    
    /**
    * Sets the value for the Object identifier.
    * @param i int to set id to
    */
    public void setId(int i) { id = i; }
    
    /**
    * Sets the value for the BorrowedBook number.
    * @param n String to set number to
    */
    public void setNumber(String n) { number = n; }
    
    /**
    * Sets the value for the borrowedBook start date.
    * @param s Date to set start date to
    */
    public void setStartDate(Date s) { startDate = s; }
        
    /**
    * Sets the value for the borrowedBook due date.
    * @param e Date to set due date to
    */
    public void setDueDate(Date e) { dueDate = e; } 
}