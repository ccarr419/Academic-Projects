package com.library.business_layer.field_list;
import java.io.Serializable;

/**
* The Publisher class represents a real-life publishing company. A Publishing 
* Object contains the publisher name and a unique identifier. Identifiers are 
* meant to act similar to a primary key in a database and as such should be 
* unique. Implements Serializable so it can be serialized for later use.
* Implements Comparable so two Publishers can be compared.
* BUSINESS LAYER CLASS
*/
public class Publisher implements Serializable, Comparable<Publisher> {
    private int id;
    private String name;
        
    /**
    * Contstructs Publisher Object by setting its attributes to a value.
    * @param i identifier
    * @param n name
    */
    public Publisher(int i, String n) {
        setId(i);
        setName(n);
    }
        
    /**
    * Gets the int identifier value for this Object.
    * @return id as int
    */
    public int getId() { return id; }
        
    /**
    * Gets the name of the Publisher as a String.
    * @return name String
    */
    public String getName() { return name; }
        
    /**
    * Sets the value for the Object identifier.
    * @param i int to set id to
    */
    public void setId(int i) { id = i; }
        
    /**
    * Sets the value for Member's name.
    * @param n String to set name to
    */
    public void setName(String n) { name = n; }
    
    /**
    * Compares this Publisher to another Publisher and returns whether this 
    * Publisher is greater than, less than or equal to the other Publisher.
    * @param p Publisher to compare to
    * @return 1 greater than, -1 less than, 0 equal
    */
    public int compareTo(Publisher p) {
        return getName().compareToIgnoreCase(p.getName());
    }
}