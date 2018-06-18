package com.library.server_layer;
import com.library.business_layer.field_list.Member;
import com.library.business_layer.field_list.CreditCard;
import com.library.business_layer.field_list.Address;
import com.library.business_layer.field_list.InternetAccount;
import com.library.business_layer.message_list.MemberHome;
import com.library.protocol.message_list.PMemberHome;
import com.library.protocol.field_list.PMember;
import com.library.protocol.field_list.PCreditCard;
import com.library.protocol.field_list.PAddress;

/**
* The role of the MembershipServer is to communicate between the Home
* classes and server UI classes. The functionality of this server includes
* reading Member, CreditCard, Address and Password for a session id and 
* the ability for a member to change their password.
* SERVER LAYER
*/
public class MembershipServer {
    private MemberHome mh;
    private PMemberHome pMH;
    
    /**
    * Basic constructor for this Object that initializes used Home classes.
    */
    public MembershipServer() {
        mh = new MemberHome();
        pMH = new PMemberHome();
    }
    
    /**
    * Get Member with the session id. Transforms Member into PMember for 
    * tranferring to server UI.
    * @param i int session id
    * @return PMember
    */
    public PMember readMember(int i) {
        Member mem = mh.findBySessionId(i);
        if(mem != null) {
            return pMH.create(mem.getName(), mem.getPhone(), mem.getAmountDue(),
                mem.getInGoodStanding(), mem.getNumber());
        }
        return null;
    }
    
    /**
    * Get CreditCard with the session id. Transforms Member into PCreditCard 
    * for tranferring to server UI.
    * @param i int session id
    * @return PCreditCard
    */
    public PCreditCard readCreditCard(int i) {
        CreditCard cc = mh.findCardBySessionId(i);
        if(cc != null) {
            return pMH.create(cc.getType(), cc.getNumber(), cc.getExpiration());
        }
        return null;
    }
    
    /**
    * Get Address with the session id. Transforms Member into PAddress 
    * for tranferring to server UI.
    * @param i int session id
    * @return PAddress
    */
    public PAddress readAddress(int i) {
        Address add = mh.findAddressBySessionId(i);
        if(add != null) {
            return pMH.create(add.getHouse(), add.getStreet(), 
                            add.getCounty(), add.getZip());
        }
        return null;
    }
    
    /**
    * Get Member password with the session id.
    * @param i int session id
    * @return String password
    */
    public String readPassword(int i) {
        InternetAccount ia = mh.findAccountBySessionId(i);
        if(ia != null) {
            return ia.getPassword();
        }
        return null;
    }
    
    /**
    * Changes the old password to a new password for the session id Member.
    * @param i int session id
    * @param o String old password
    * @param n String new password
    * @return true if password was changed, false if not
    */
    public boolean changePassword(int i, String o, String n) {
        InternetAccount ia = mh.findAccountBySessionId(i);
        if(ia != null) {
            if(ia.getPassword().equals(o)) {
                mh.getInternetAccounts().setForId(ia.getId(), "password", n);
                return true;
            }
        }
        return false;
    }
    
    /**
    * Force the update of the MembershipServer and all its Homes
    */
    public void update() {
        mh.update();
    }
}