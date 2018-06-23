package com.library.protocol.field_list;
import com.library.business_layer.field_list.CreditCard;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
* PCreditCard serves as a protocol to transfer Table information from the server
* to the UI. Only serves as a way to view, print and facilitate information.
* PROTOCOL LAYER
* @see com.library.business_layer.field_list.CatalogQuery
*/
public class PCreditCard {
    private String type;
    private String number;
    private Date expiration;
        
    /**
    * Basic constructor that sets all attributes.
    * @param t String card type
    * @param n String card number
    * @param e Date card expiration date
    */
    public PCreditCard(String t, String n, Date e) {
        type = t;
        number = n;
        expiration = e;
    }

    /**
    * @return String card type
    * @see com.library.business_layer.field_list.CreditCard#getType()
    */
    public String getType() { return type; }
        
    /**
    * @return String card number
    * @see com.library.business_layer.field_list.CreditCard#getNumber()
    */
    public String getNumber() { return number; }
        
    /**
    * @return Date card expiration date
    * @see com.library.business_layer.field_list.CreditCard#getExpiration()
    */
    public Date getExpiration() { return expiration; }
    
    /**
    * Prints the CreditCard in a human understandable summary. Full CreditCard
    * numbers are not shown for security reasons.
    */
    public String toString() {
        String out = "";
        out += (getType() + "\n");
        int numbers = getNumber().length();
        int hide = numbers - (numbers/4);
        String hideStr = getNumber().substring(0, hide);
        char[] chStr = hideStr.toCharArray();
        for(int i = 0; i < chStr.length; i++) {
            if(chStr[i] != '-') { chStr[i] = 'x'; }
        }
        hideStr = new String(chStr);
        String showStr = getNumber().substring(hide, getNumber().length());
        SimpleDateFormat f = new SimpleDateFormat("MM/yy"); 
        out += (hideStr + showStr + "\nExp. " + f.format(getExpiration()));
        out += "\n";
        return out;
    }
}
