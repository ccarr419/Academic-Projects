package com.library.protocol.field_list;
import com.library.business_layer.field_list.Address;

/**
* PAddress serves as a protocol to transfer Table information from the server
* to the UI. Only serves as a way to view, print and facilitate information.
* PROTOCOL LAYER
* @see com.library.business_layer.field_list.Address
*/
public class PAddress {
    private String house;
    private String street;
    private String county;
    private String zip;
    
    /**
    * Basic constructor that sets all attributes.
    * @param h String house number
    * @param s String street address
    * @param c String address county
    * @param z String zip code
    */
    public PAddress(String h, String s, String c, String z) {
        house = h;
        street = s;
        county = c;
        zip = z;
    }
    
    /**
    * @return String house number
    * @see com.library.business_layer.field_list.Address#getHouse()
    */
    public String getHouse() { return house; }
    
    /**
    * @return String street address
    * @see com.library.business_layer.field_list.Address#getStreet()
    */
    public String getStreet() { return street; }
        
    /**
    * @return String address county
    * @see com.library.business_layer.field_list.Address#getCounty()
    */
    public String getCounty() { return county; }
    
    /**
    * @return String zip code
    * @see com.library.business_layer.field_list.Address#getZip()
    */
    public String getZip() { return zip; } 
    
    /**
    * Prints the Address in a human understandable summary.
    */
    public String toString() {
        String out = "";
        out += (getHouse() + " " + getStreet() + "\n");
        out += (getCounty() + " " + getZip() + "\n");
        return out;
    }
}
