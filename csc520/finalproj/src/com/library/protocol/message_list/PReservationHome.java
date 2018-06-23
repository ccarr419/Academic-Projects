package com.library.protocol.message_list;
import com.library.protocol.field_list.PReservation;
import java.sql.Timestamp;

/**
* PReservationHome serves a singular purpose of creating protocol variables
* that will be used and sent back and forth from server to UI.
* PROTOCOL LAYER
*/
public class PReservationHome {

    /**
    * Creates a PReservation protocol variable.
    * @param n String reservation number
    * @param t Timestamp
    * @return PReservation
    */
    public PReservation create(String n, Timestamp t) {
        PReservation pRes = new PReservation(n, t);
        return pRes;
    }
}
