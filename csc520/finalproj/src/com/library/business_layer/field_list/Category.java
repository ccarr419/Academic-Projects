package com.library.business_layer.field_list;
import java.io.Serializable;

/**
* The Category class represents a genre for a book to classified under.
* A Category Object contains the category name and a unique identifier.
* Identifiers are meant to act similar to a primary key in a database and 
* as such should be unique. Implements Serializable so it can be serialized
* for later use. Implements Comparable so two categories can be compared.
* BUSINESS LAYER CLASS
*/
public class Category implements Serializable, Comparable<Category> {
    private int id;
    private String name;
        
    /**
    * Contstructs Category Object by setting its attributes to a value.
    * @param i identifier
    * @param n name
    */
    public Category(int i, String n) {
        setId(i);
        setName(n);
    }
        
    /**
    * Gets the int identifier value for this Object.
    * @return id as int
    */
    public int getId() { return id; }
        
    /**
    * Gets the name of the Category as a String.
    * @return name String
    */
    public String getName() { return name; }
        
    /**
    * Sets the value for the Object identifier.
    * @param i int to set id to
    */
    public void setId(int i) { id = i; }
        
    /**
    * Sets the value for the Category name.
    * @param n String to set name to
    */
    public void setName(String n) { name = n; }
    
    /**
    * Compares this Category to another Category and returns whether this 
    * Category is greater than, less than or equal to the other Category.
    * @param c Category to compare to
    * @return 1 greater than, -1 less than, 0 equal
    */
    public int compareTo(Category c) {
        return getName().compareToIgnoreCase(c.getName());
    }
}