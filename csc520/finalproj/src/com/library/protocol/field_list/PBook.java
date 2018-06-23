package com.library.protocol.field_list;
import com.library.business_layer.field_list.Book;

/**
* PBook serves as a protocol to transfer Table information from the server
* to the UI. Only serves as a way to view, print and facilitate information.
* PROTOCOL LAYER
* @see com.library.business_layer.field_list.Book
*/
public class PBook {
    private int borrowedCount;
        
    /**
    * Basic constructor that sets all attributes.
    * @param bor int borrowed count
    */
    public PBook(int bor) {
        borrowedCount = bor;
    }
        
    /**
    * @return int borrowed count
    * @see com.library.business_layer.field_list.Book#getBorrowedCount()
    */
    public int getBorrowedCount() { return borrowedCount; }
    
    /**
    * Prints the Book in a human understandable summary.
    */
    public String toString() {
        String out = "";
        out += ("Borrowed Count: " + Integer.toString(getBorrowedCount()));
        return out;
    }
}