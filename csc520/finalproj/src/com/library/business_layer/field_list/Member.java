package com.library.business_layer.field_list;
import java.io.Serializable;

/**
* The Member class represents a real-life person who wishes to use the
* library's online and in person services. A Member Object contains the 
* member's name, phone number, amount due, member number, credit card id,
* address id, internet account id, whether they are in good standing, and a
* unique identifier. Identifiers are meant to act similar to a primary key 
* in a database and as such should be unique. Also implements Serializable 
* so it can be serialized for later use.
* BUSINESS LAYER CLASS
* @see com.library.business_layer.field_list.Address
* @see com.library.business_layer.field_list.CreditCard
* @see com.library.business_layer.field_list.InternetAccount
*/
public class Member implements Serializable {
    private int id;
    private String name;
    private String phone;
    private int amountDue;
    private boolean inGoodStanding;
    private String number;
    private int creditCardId;
    private int addressId;
    private int internetAccountId;
        
    /**
    * Contstructs Member Object by setting its attributes to a value.
    * @param i identifier
    * @param n name
    * @param p phone number
    * @param a amount due
    * @param igs in good standing
    * @param num member number
    * @param ci credit card id
    * @param ai address id
    * @param ii internet account id
    */
    public Member(int i, String n, String p, int a, boolean igs, String num,
        int ci, int ai, int ii) {
        setId(i);
        setName(n);
        setPhone(p);
        setAmountDue(a);
        setInGoodStanding(igs);
        setNumber(num);
        setCreditCardId(ci);
        setAddressId(ai);
        setInternetAccountId(ii);
    }
        
    /**
    * Gets the int identifier value for this Object.
    * @return id as int
    */
    public int getId() { return id; }
        
    /**
    * Gets the name of the Member as a String.
    * @return name String
    */
    public String getName() { return name; }
        
    /**
    * Gets the Member's phone number as a String.
    * @return phone number String
    */
    public String getPhone() { return phone; }
        
    /**
    * Gets the amount due by the Member as an int.
    * @return amount due int
    */
    public int getAmountDue() { return amountDue; }
        
    /**
    * Gets the state of the Member's standing as a boolean.
    * @return in good standing boolean
    */
    public boolean getInGoodStanding() { return inGoodStanding; }
        
    /**
    * Gets the Members user number as a String.
    * @return number String
    */
    public String getNumber() { return number; }
    
    /**
    * Gets the indentifier for the Member CreditCard.
    * @return credit card id int
    */
    public int getCreditCardId() { return creditCardId; }
    
    /**
    * Gets the indentifier for the Member Address.
    * @return address id int
    */
    public int getAddressId() { return addressId; }
    
    /**
    * Gets the indentifier for the Member InternetAccount.
    * @return internet account id int
    */
    public int getInternetAccountId() { return internetAccountId; }
        
    /**
    * Sets the value for the Object identifier.
    * @param i int to set id to
    */
    public void setId(int i) { id = i; }
        
    /**
    * Sets the value for Member's name.
    * @param n String to set name to
    */
    public void setName(String n) { name = n; }
        
    /**
    * Sets the value for Member's phone number.
    * @param p String to set name to
    */
    public void setPhone(String p) { phone = p; }
        
    /**
    * Sets the value for Member's amount due.
    * @param a int to set amount due to
    */
    public void setAmountDue(int a) { amountDue = a; }
        
    /**
    * Sets the value for Member's current state.
    * @param igs boolean to set in good standing to
    */
    public void setInGoodStanding(boolean igs) { inGoodStanding = igs; }
        
    /**
    * Sets the value for Member's number.
    * @param num String to set number to
    */
    public void setNumber(String num) { number = num; }
    
    /**
    * Sets the value for the CreditCard id.
    * @param ci int to set credit card id to
    */
    public void setCreditCardId(int ci) { creditCardId = ci; }
    
    /**
    * Sets the value for the Address id.
    * @param ai int to set address id to
    */
    public void setAddressId(int ai) { addressId = ai; }
    
    /**
    * Sets the value for the InternetAccount id.
    * @param ii int to set internet account id to
    */
    public void setInternetAccountId(int ii) { internetAccountId = ii; }
}