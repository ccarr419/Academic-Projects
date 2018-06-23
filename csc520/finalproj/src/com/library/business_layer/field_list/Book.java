package com.library.business_layer.field_list;
import java.io.Serializable;
import java.util.Date;

/**
* The Book class represents a real-life physical book. Book contains the bar
* code for the book, how many times it has been borrowed, the date it was
* lost if applicable and its unique identifier. Identifiers are meant
* to act similar to a primary key in a database and as such should be unique.
* Also implements Serializable so it can be serialized for later use.
* BUSINESS LAYER CLASS
*/
public class Book implements Serializable {
    private int id;
    private String barCode;
    private int borrowedCount;
    private Date dateLost;
    
    /**
    * Contstructs Book Object by setting its attributes to a value.
    * @param i identifier
    * @param bar book bar code
    * @param bor borrowed count
    * @param d date lost
    */
    public Book(int i, String bar, int bor, Date d) {
        setId(i);
        setBarCode(bar);
        setBorrowedCount(bor);
        setDateLost(d);
    }
     
    /**
    * Gets the int identifier value for this Object.
    * @return id as int
    */
    public int getId() { return id; }
        
    /**
    * Gets the Book bar code as a String.
    * @return bar code String
    */
    public String getBarCode() { return barCode; }
    
    /**
    * Gets the Book borrowed count as an int.
    * @return borrowed count as int
    */
    public int getBorrowedCount() { return borrowedCount; }
    
    /**
    * Gets the Date the Book was lost as a Date Object.
    * @return date the book was lost as Date Object.
    */
    public Date getDateLost() { return dateLost; }
    
    /**
    * Sets the value for the Object identifier.
    * @param i int to set id to
    */
    public void setId(int i) { id = i; }
    
    /**
    * Sets the value for the Book bar code.
    * @param bar String to set bar code to
    */
    public void setBarCode(String bar) { barCode = bar; }
        
    /**
    * Sets the value for the Book borrowed count.
    * @param bor int to set borrowed count to
    */
    public void setBorrowedCount(int bor) { borrowedCount = bor; }
    
    /**
    * Sets the value for the date the Book was lost.
    * @param d Date to set date lost to
    */
    public void setDateLost(Date d) { dateLost = d; }
}