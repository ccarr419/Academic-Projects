package com.library.protocol.field_list;
import com.library.business_layer.field_list.Category;

/**
* PCategory serves as a protocol to transfer Table information from the server
* to the UI. Only serves as a way to view, print and facilitate information.
* PROTOCOL LAYER
* @see com.library.business_layer.field_list.CatalogQuery
*/
public class PCategory {
    private String name;
        
    /**
    * Basic constructor that sets all attributes.
    * @param n String category name
    */
    public PCategory(String n) {
        name = n;
    }

    /**
    * @return String category name
    * @see com.library.business_layer.field_list.Category#getName()
    */
    public String getName() { return name; }
    
    /**
    * Prints the Category in a human understandable summary.
    */
    public String toString() {
        String out = "";
        out += (getName());
        return out;
    }
}
