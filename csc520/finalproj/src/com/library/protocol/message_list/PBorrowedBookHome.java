package com.library.protocol.message_list;
import com.library.protocol.field_list.PBorrowedBook;
import java.util.ArrayList;
import java.util.Date;

/**
* PBorrowedBookHome serves a singular purpose of creating protocol variables
* that will be used and sent back and forth from server to UI.
* PROTOCOL LAYER
*/
public class PBorrowedBookHome {

    /**
    * Creates a PBorrowedBook protocol variable.
    * @param start Date borrowed start date
    * @param end Date borrowed due date
    * @return PBorrowedBook
    */
    public PBorrowedBook create(Date start, Date end) {
        PBorrowedBook pBB = new PBorrowedBook(start, end);
        return pBB;
    }
}
