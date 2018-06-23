package com.library.protocol.message_list;
import com.library.protocol.field_list.PPublisher;

/**
* PPublisherHome serves a singular purpose of creating protocol variables
* that will be used and sent back and forth from server to UI.
* PROTOCOL LAYER
*/
public class PPublisherHome {

    /**
    * Creates a PPublisher protocol variable.
    * @param name String publisher name
    * @return PPublisher
    */
    public PPublisher create(String name) {
        PPublisher pPub = new PPublisher(name);
        return pPub;
    }
}
