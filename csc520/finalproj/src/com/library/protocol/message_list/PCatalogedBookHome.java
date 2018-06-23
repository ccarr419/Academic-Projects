package com.library.protocol.message_list;
import com.library.protocol.field_list.PCatalogedBook;

/**
* PCatalogedBookHome serves a singular purpose of creating protocol variables
* that will be used and sent back and forth from server to UI.
* PROTOCOL LAYER
*/
public class PCatalogedBookHome {

    /**
    * Creates a PCatalogedBook protocol variable.
    * @param isbn String book ISBN
    * @param name String book title
    * @return PCatalogedBook
    */
    public PCatalogedBook create(String isbn, String name) {
        PCatalogedBook pCB = new PCatalogedBook(isbn, name);
        return pCB;
    }
}
