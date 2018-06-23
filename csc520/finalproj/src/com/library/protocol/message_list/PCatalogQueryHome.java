package com.library.protocol.message_list;
import com.library.protocol.field_list.PCatalogQuery;

/**
* PCatalogQueryHome serves a singular purpose of creating protocol variables
* that will be used and sent back and forth from server to UI.
* PROTOCOL LAYER
*/
public class PCatalogQueryHome {

    /**
    * Creates a PCatalogQuery protocol variable.
    * @param pid int[] publisher ids
    * @param cid int[] category ids
    * @param auth String[] author names
    * @return PCatalogQuery
    */
    public PCatalogQuery create(int pid[], int cid[], String auth[]) {
        PCatalogQuery pCQ = new PCatalogQuery(pid, cid, auth);
        return pCQ;
    }
}
