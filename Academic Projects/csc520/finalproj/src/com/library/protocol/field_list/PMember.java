package com.library.protocol.field_list;
import com.library.business_layer.field_list.Member;

/**
* PMember serves as a protocol to transfer Table information from the server
* to the UI. Only serves as a way to view, print and facilitate information.
* PROTOCOL LAYER
* @see com.library.business_layer.field_list.Member
*/
public class PMember {
    private String name;
    private String phone;
    private int amountDue;
    private boolean inGoodStanding;
    private String number;
       
    /**
    * Basic constructor that sets all attributes.
    * @param n String member name
    * @param p String member phone number
    * @param a int member amount due
    * @param igs boolean member in good standing
    * @param num String member number
    */
    public PMember(String n, String p, int a, boolean igs, String num) {
        name = n;
        phone = p;
        amountDue = a;
        inGoodStanding = igs;
        number = num;
    }

    /**
    * @return String member name
    * @see com.library.business_layer.field_list.Member#getName()
    */
    public String getName() { return name; }
        
    /**
    * @return String member phone number
    * @see com.library.business_layer.field_list.Member#getPhone()
    */
    public String getPhone() { return phone; }

    /**
    * @return int member amount due
    * @see com.library.business_layer.field_list.Member#getAmountDue()
    */
    public int getAmountDue() { return amountDue; }
        
    /**
    * @return boolean member in good standing
    * @see com.library.business_layer.field_list.Member#getInGoodStanding()
    */
    public boolean getInGoodStanding() { return inGoodStanding; }
    
    /**
    * @return String member number
    * @see com.library.business_layer.field_list.Member#getNumber()
    */
    public String getNumber() { return number; }
    
    /**
    * Prints the Member in a human understandable summary.
    */
    public String toString() {
        String out = "";
        out += ("Name: " + getName() + "\nNumber: " + getNumber() + "\n");
        out += ("Phone: " + getPhone() + "\n");
        out += ("Amount Due: $" + getAmountDue() + "\n");
        if(getInGoodStanding()) { out += ("In Good Standing\n"); }
        else { out += ("Not In Good Standing\n"); }
        return out;
    }
}
