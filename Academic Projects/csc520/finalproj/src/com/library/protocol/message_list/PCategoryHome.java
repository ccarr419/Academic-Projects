package com.library.protocol.message_list;
import com.library.protocol.field_list.PCategory;

/**
* PCategoryHome serves a singular purpose of creating protocol variables
* that will be used and sent back and forth from server to UI.
* PROTOCOL LAYER
*/
public class PCategoryHome {

    /**
    * Creates a PCatalogQuery protocol variable.
    * @param name String category name
    * @return PCatalogQuery
    */
    public PCategory create(String name) {
        PCategory pCat = new PCategory(name);
        return pCat;
    }
}
