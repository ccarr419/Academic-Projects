package com.library.business_layer.field_list;
import java.io.Serializable;

/**
* A CatalogedBookDetails represents more fine-grain details of a book.
* CatalogedBookDetails contains the book edition, list of authors,
* a description, and a unique identifier. Identifiers are meant to 
* act similar to a primary key in a database and as such should be unique. 
* Also implements Serializable so it can be serialized for later use.
* BUSINESS LAYER CLASS
*/
public class CatalogedBookDetails implements Serializable {
    private int id;
    private String edition;
    private String authors[];
    private String description;
        
    /**
    * Contstructs CatalogedBookDetails Object by setting its attributes to a value.
    * @param i identifier
    * @param e edition
    * @param a authors
    * @param d description
    */
    public CatalogedBookDetails(int i, String e, String a[], String d) {
        setId(i);
        setEdition(e);
        setAuthors(a);
        setDescription(d);
    }
        
    /**
    * Gets the int identifier value for this Object.
    * @return id as int
    */
    public int getId() { return id; }
        
    /**
    * Gets the edition of the book as a String.
    * @return edition String
    */
    public String getEdition() { return edition; }
     
    /**
    * Gets the list of authors as a String array.
    * @return authors String array
    */
    public String[] getAuthors() { return authors; }
        
    /**
    * Gets the description of the book as a String.
    * @return description String
    */
    public String getDescription() { return description; }
        
    /**
    * Sets the value for the Object identifier.
    * @param i int to set id to
    */
    public void setId(int i) { id = i; }
        
    /**
    * Sets the value for the book's edition.
    * @param e String to set edition to
    */
    public void setEdition(String e) { edition = e; }
        
    /**
    * Sets the value for the book's list of authors.
    * @param a String array to set authors to
    */
    public void setAuthors(String a[]) { authors = a; }
        
    /**
    * Sets the value for the book's description.
    * @param d String to set description to
    */
    public void setDescription(String d) { description = d; }
}