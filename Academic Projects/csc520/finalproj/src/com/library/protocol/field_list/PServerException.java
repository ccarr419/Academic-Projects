package com.library.protocol.field_list;

/**
* PServerException servers as a protocol to transfer information from the server
* to the UI. Only serves as a way to view, print and facilitate information.
* PROTOCOL LAYER
*/
public class PServerException {
    String message;
    
    /**
    * Basic constructor that sets all attributes.
    * @param m String message
    */
    public PServerException(String m) {
        message = m;
    }
    
    /**
    * Gets the exception message.
    * @return String message
    */
    public String getMessage() { return message; }
    
    /**
    * Prints the ServerException in a human understandable summary.
    */
    public String toString() {
        String out = "";
        out += (getMessage());
        return out;
    }
}