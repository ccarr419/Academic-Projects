package com.library.protocol.message_list;
import com.library.protocol.field_list.PMember;
import com.library.protocol.field_list.PAddress;
import com.library.protocol.field_list.PCreditCard;
import java.util.Date;

/**
* PMemberHome serves a singular purpose of creating protocol variables
* that will be used and sent back and forth from server to UI.
* PROTOCOL LAYER
*/
public class PMemberHome {

    /**
    * Creates a PMember protocol variable.
    * @param n String member name
    * @param p String member phone number
    * @param a int member amount due
    * @param igs boolean member in good standing
    * @param num String member number
    * @return PMember
    */
    public PMember create(String n, String p, int a, boolean igs, String num) {
        PMember pMem = new PMember(n, p, a, igs, num);
        return pMem;
    }
    
    /**
    * Creates a PCreditCard protocol variable.
    * @param type String card type
    * @param num String card number
    * @param ex Date card expiration date
    * @return PCreditCard
    */
    public PCreditCard create(String type, String num, Date ex) {
        PCreditCard newCC = new PCreditCard(type, num, ex);
        return newCC;
    }
    
    /**
    * Creates a PAddress protocol variable.
    * @param house String house number
    * @param street String street addres
    * @param county String address county
    * @param zip String zip code
    * @return PAddress
    */
    public PAddress create(String house, String street, String county, String zip) {
        PAddress newAdd = new PAddress(house, street, county, zip);
        return newAdd;
    }
}
