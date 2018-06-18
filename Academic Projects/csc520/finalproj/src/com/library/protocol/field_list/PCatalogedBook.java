package com.library.protocol.field_list;
import com.library.business_layer.field_list.CatalogedBook;

/**
* PCatalogedBook serves as a protocol to transfer Table information from the server
* to the UI. Only serves as a way to view, print and facilitate information.
* PROTOCOL LAYER
* @see com.library.business_layer.field_list.BorrowedBook
*/
public class PCatalogedBook {
    private String isbn;
    private String name;
    
    /**
    * Basic constructor that sets all attributes.
    * @param i String ISBN
    * @param n String book title
    */
    public PCatalogedBook(String i, String n) {
        isbn = i;
        name = n;
    }
    
    /**
    * @return String book ISBN
    * @see com.library.business_layer.field_list.CatalogedBook#getIsbn()
    */
    public String getIsbn() { return isbn; }
        
    /**
    * @return String book title
    * @see com.library.business_layer.field_list.CatalogedBook#getName()
    */
    public String getName() { return name; }
    
    /**
    * Prints the CatalogedBook in a human understandable summary.
    */
    public String toString() {
        String out = "";
        out += ("\"" + getName() + "\"");
        return out;
    }
}
    