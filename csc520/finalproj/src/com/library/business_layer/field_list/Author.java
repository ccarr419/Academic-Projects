package com.library.business_layer.field_list;
import java.io.Serializable;

/**
* The Author class represents a real or made up author for a book. Author only
* contains the author's name along with an identifier. Identifiers are meant
* to act similar to a primary key in a database and as such should be unique.
* Also implements Serializable so it can be serialized for later use.
* BUSINESS LAYER CLASS
*/
public class Author implements Serializable {
    private int id;
    private String name;
    
    /**
    * Contstructs Author Object by setting its attributes to a value.
    * @param i identifier
    * @param n author name
    */
    public Author(int i, String n) {
        setId(i);
        setName(n);
    }
    
    /**
    * Gets the int identifier value for this Object.
    * @return id as int
    */
    public int getId() { return id; }
    
    /**
    * Gets the Author name as a String.
    * @return author name String
    */
    public String getName() { return name; }
    
    /**
    * Sets the value for the Object identifier.
    * @param i int to set id to
    */
    public void setId(int i) { id = i; }
    
    /**
    * Sets the value for the Author name.
    * @param n String to set name to
    */
    public void setName(String n) { name = n; }
}