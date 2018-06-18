package com.library.protocol.message_list;
import com.library.protocol.field_list.PCatalogedBookDetails;

/**
* PCatalogedBookDetailsHome serves a singular purpose of creating protocol variables
* that will be used and sent back and forth from server to UI.
* PROTOCOL LAYER
*/
public class PCatalogedBookDetailsHome {

    /**
    * Creates a PCatalogedBookDetails protocol variable.
    * @param e String book edition
    * @param a String[] book author(s)
    * @param d String book description
    * @return PCatalogedBookDetails
    */
    public PCatalogedBookDetails create(String e, String a[], String d) {
        PCatalogedBookDetails pCBD = new PCatalogedBookDetails(e, a, d);
        return pCBD;
    }
}
