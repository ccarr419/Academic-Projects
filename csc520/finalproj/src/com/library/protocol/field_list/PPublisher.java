package com.library.protocol.field_list;
import com.library.business_layer.field_list.Publisher;

/**
* PPublisher serves as a protocol to transfer Table information from the server
* to the UI. Only serves as a way to view, print and facilitate information.
* PROTOCOL LAYER
* @see com.library.business_layer.field_list.Publisher
*/
public class PPublisher {
    private String name;
      
    /**
    * Basic constructor that sets all attributes.
    * @param n String publisher name
    */
    public PPublisher(String n) {
        name = n;
    }

    /**
    * @return String publisher name
    * @see com.library.business_layer.field_list.Publisher#getName()
    */
    public String getName() { return name; }
    
    /**
    * Prints the Publisher in a human understandable summary.
    */
    public String toString() {
        String out = "";
        out += (getName());
        return out;
    }
}