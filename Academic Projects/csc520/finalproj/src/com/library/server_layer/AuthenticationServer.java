package com.library.server_layer;
import com.library.business_layer.field_list.Member;
import com.library.business_layer.field_list.InternetAccount;
import com.library.business_layer.message_list.MemberHome;
import com.library.persistence_layer.*;
import java.util.ArrayList;

/**
* The role of the AuthenticationServer is to communicate between the Home
* classes and server UI classes. The functionality of this server includes
* logging a member on and off.
* SERVER LAYER
*/
public class AuthenticationServer {
    private MemberHome mh;
    
    /**
    * Basic constructor for this Object that initializes used Home classes.
    */
    public AuthenticationServer() { 
        mh = new MemberHome();
    }
    
    /**
    * Logs the member on by checking the given user number and password
    * to a matching member found within the memberHome.
    * @param n String user number
    * @param p String user password
    * @param s boolean steal session
    * @return int session id
    */
    public int logon(String n, String p, boolean s) {
        Member mem = mh.findByMembershipNumber(n);
        InternetAccount ia = mh.findAccountByMember(mem);
        long sessionId = -1;
        //Check if member with the number exists
        if(mem != null && ia != null) {
            //Check if password matches member password
            if(!p.equals(ia.getPassword())) { return (int) sessionId; }           
            Table accTable = mh.getInternetAccounts();
            if(s) { //If the member wants to steal a session
                for(int i = 0; i < accTable.size(); i++) {
                    InternetAccount acc = (InternetAccount) accTable.get(i);
                    if(acc.getSessionId() > 0) {
                        sessionId = acc.getSessionId();
                        accTable.setForId(acc.getId(), "sessionId", -1);
                    }
                }
            } //Otherwise give member a unique session id
            if(sessionId == -1) {
                sessionId = (long)
                    Math.floor(Math.pow(mem.getId(),2) / 16) 
                    + (1000 + mem.getId());
            }
            accTable.setForId(ia.getId(), "sessionId", sessionId);
        }
        return (int) sessionId;
    }
    
    /**
    * Logs the member off by finding the session and terminating it.
    * @param i int session id
    * @return true if the member successfully logged off, false if not
    */
    public boolean logoff(int i) {
        if(i <= 0) { return false; }
        InternetAccount ia = mh.findAccountBySessionId(i);
        if(ia != null) {
            Table accTable = mh.getInternetAccounts();
            accTable.setForId(ia.getId(), "sessionId", -1);
            return true;
        }
        return false;
    }
    
    /**
    * Force the update of the AuthenticationServer and all its Homes
    */
    public void update() {
        mh.update();
    }
}
