package com.library.protocol.field_list;
import com.library.business_layer.field_list.BorrowedBook;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
* PBorrowedBook serves as a protocol to transfer Table information from the server
* to the UI. Only serves as a way to view, print and facilitate information.
* PROTOCOL LAYER
* @see com.library.business_layer.field_list.BorrowedBook
*/
public class PBorrowedBook {
    private Date startDate;
    private Date dueDate;
      
    /**
    * Basic constructor that sets all attributes.
    * @param start Date start date
    * @param end Date due date
    */
    public PBorrowedBook(Date start, Date end) {
        startDate = start;
        dueDate = end;
    }
    
    /**
    * @return Date borrowed start date
    * @see com.library.business_layer.field_list.BorrowedBook#getStartDate()
    */
    public Date getStartDate() { return startDate; }
        
    /**
    * @return Date borrowed due date
    * @see com.library.business_layer.field_list.BorrowedBook#getDueDate()
    */
    public Date getDueDate() { return dueDate; }
    
    /**
    * Prints the BorrowedBook in a human understandable summary.
    */
    public String toString() {
        String out = "";
        Date start = getStartDate();
        Date end = getDueDate();
        SimpleDateFormat f = new SimpleDateFormat("(MM-dd-yyyy)");  
        out += ("Start Date: ");
        out += f.format(getStartDate());
        out += (" Due Date: ");
        out += f.format(getDueDate());
        return out;
    }
}
