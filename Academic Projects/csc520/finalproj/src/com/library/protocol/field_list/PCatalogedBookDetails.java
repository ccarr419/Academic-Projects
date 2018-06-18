package com.library.protocol.field_list;
import com.library.business_layer.field_list.CatalogedBookDetails;

/**
* PCatalogedBookDetails serves as a protocol to transfer Table information from 
* the server to the UI. Only serves as a way to view, print and facilitate 
* information.
* PROTOCOL LAYER
* @see com.library.business_layer.field_list.BorrowedBook
*/
public class PCatalogedBookDetails {
    private String edition;
    private String authors[];
    private String description;
        
    /**
    * Basic constructor that sets all attributes.
    * @param e String book edition
    * @param a String[] book authors
    * @param d String book description
    */
    public PCatalogedBookDetails(String e, String a[], String d) {
        edition = e;
        authors = a;
        description = d;
    }

    /**
    * @return String book edition
    * @see com.library.business_layer.field_list.CatalogedBookDetails#getEdition()
    */
    public String getEdition() { return edition; }
        
    /**
    * @return String[] book author(s)
    * @see com.library.business_layer.field_list.CatalogedBookDetails#getAuthors()
    */
    public String[] getAuthors() { return authors; }
        
    /**
    * @return String book description
    * @see com.library.business_layer.field_list.CatalogedBookDetails#getDescription()
    */
    public String getDescription() { return description; }
    
    /**
    * Prints the CatalogedBookDetails in a human understandable summary.
    */
    public String toString() {
        String out = "";
        out += ("Edition: " + getEdition() + "\nAuthors: ");
        for(int i = 0; i < getAuthors().length; i++) {
            out += (getAuthors()[i]);
            if(i < getAuthors().length-1) { out += ", "; }
        }
        out += ("\nDescription: " + getDescription() + "\n");
        return out;
    }
}