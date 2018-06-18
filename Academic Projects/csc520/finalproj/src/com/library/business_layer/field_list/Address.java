package com.library.business_layer.field_list;
import java.io.Serializable;

/**
* The Address class represents a real-life address. Address contains a
* house number, street name, county and a zip code. Identifiers are meant
* to act similar to a primary key in a database and as such should be unique.
* Also implements Serializable so it can be serialized for later use.
* BUSINESS LAYER CLASS
*/
public class Address implements Serializable {
    private int id;
    private String house;
    private String street;
    private String county;
    private String zip;
    
    /**
    * Contstructs Address Object by setting its attributes to a value.
    * @param i identifier
    * @param h house number
    * @param s street address
    * @param c county
    * @param z zip code
    */
    public Address(int i, String h, String s, String c, String z) {
        setId(i);
        setHouse(h);
        setStreet(s);
        setCounty(c);
        setZip(z);
    }
    
    /**
    * Gets the int identifier value for this Object.
    * @return id as int
    */
    public int getId() { return id; }
    
    /**
    * Gets the address house number as a String.
    * @return house number String
    */
    public String getHouse() { return house; }
     
    /**
    * Gets the street address as a String.
    * @return street address String
    */
    public String getStreet() { return street; }
    
    /**
    * Gets the address county name as a String.
    * @return county name String
    */  
    public String getCounty() { return county; }
        
    /**
    * Get the address zip code as a String.
    * @return zip code String
    */
    public String getZip() { return zip; }
        
    /**
    * Sets the value for the Object identifier.
    * @param i int to set id to
    */
    public void setId(int i) { id = i; }
        
    /**
    * Sets the value for the address house number.
    * @param h String to set house number to
    */
    public void setHouse(String h) { house = h; }
        
    /**
    * Sets the value for the street address.
    * @param s String to set street address to
    */
    public void setStreet(String s) { street = s; }
        
    /**
    * Sets the value for the address county.
    * @param c String to set county to
    */
    public void setCounty(String c) { county = c; }
        
    /**
    * Sets the value for the address zip code.
    * @param z String to set zip code to
    */
    public void setZip(String z) { zip = z; }
}