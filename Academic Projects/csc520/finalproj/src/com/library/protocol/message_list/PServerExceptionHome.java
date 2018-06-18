package com.library.protocol.message_list;
import com.library.protocol.field_list.PServerException;

/**
* PServerExceptionHome serves a singular purpose of creating protocol variables
* that will be used and sent back and forth from server to UI.
* PROTOCOL LAYER
*/
public class PServerExceptionHome {

    /**
    * Creates a PServerException protocol variable.
    * @param m String server exception message
    * @return PServerException
    */
    public PServerException create(String m) {
        PServerException pSE = new PServerException(m);
        return pSE;
    }
}