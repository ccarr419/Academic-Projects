package com.library.business_layer.field_list;
import java.io.Serializable;

/**
* The InternetAccount class represents a digital construct of a user account.
* A InternetAccount Object contains the member's password, current session id
* and unique identifier. Identifiers are meant to act similar to a primary key 
* in a database and as such should be unique. Also implements Serializable 
* so it can be serialized for later use.
* BUSINESS LAYER CLASS
*/
public class InternetAccount implements Serializable {
    private int id;
    private String password;
    private long sessionid;
        
    /**
    * Contstructs InternetAccount Object by setting its attributes to a value.
    * @param i identifier
    * @param p password
    * @param s session id
    */
    public InternetAccount(int i, String p, long s) {
        setId(i);
        setPassword(p);
        setSessionId(s);
    }
        
    /**
    * Gets the int identifier value for this Object.
    * @return id as int
    */
    public int getId() { return id; }
        
    /**
    * Gets the password for the account as a String.
    * @return password String
    */
    public String getPassword() { return password; }
        
    /**
    * Gets the session id for the account as a long.
    * @return session id long
    */
    public long getSessionId() { return sessionid; }
        
    /**
    * Sets the value for the Object identifier.
    * @param i int to set id to
    */
    public void setId(int i) { id = i; }
        
    /**
    * Sets the value for account password.
    * @param p String to set password to
    */
    public void setPassword(String p) { password = p; }
        
    /**
    * Sets the value for account session id.
    * @param s long to set session id to
    */
    public void setSessionId(long s) { sessionid = s; }
}