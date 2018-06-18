package com.library.business_layer.message_list;
import com.library.business_layer.field_list.Member;
import com.library.business_layer.field_list.InternetAccount;
import com.library.business_layer.field_list.CreditCard;
import com.library.business_layer.field_list.Address;
import com.library.persistence_layer.*;
import java.util.ArrayList;
import java.util.Date;

/**
* MemberHome serves as a way to access the MemberTable, AddressTable,
* CreditCardTable and InternetAccountTable. Thus it also serves as an accessor 
* to the each table element attributes. Another purpose of MemberHome is to 
* create and addany new entries to MemberTable, AddressTable, CreditCardTable
* and the InternetAccountTable.
* BUSINESS LAYER CLASS
* @see com.library.business_layer.field_list.Address
* @see com.library.business_layer.field_list.CreditCard
* @see com.library.business_layer.field_list.InternetAccount
* @see com.library.business_layer.field_list.Member
*/
public class MemberHome {
    private Table memTable;
    private Table iaTable;
    private Table ccTable;
    private Table addTable;

    /**
    * Basic constructor for MemberHome that instantiates home's Tables.
    */
    public MemberHome() { 
        memTable = new DataSchema.MemberTable();
        iaTable = new DataSchema.InternetAccountTable();
        ccTable = new DataSchema.CreditCardTable();
        addTable = new DataSchema.AddressTable();
    }
    
    /**
    * Gets the MemberTable as a whole.
    * @return DataSchema.MemberTable
    */
    public DataSchema.MemberTable getMembers() { 
        return (DataSchema.MemberTable) memTable;
    }
    
    /**
    * Gets the InternetAccountTable as a whole.
    * @return DataSchema.InternetAccountTable
    */
    public DataSchema.InternetAccountTable getInternetAccounts() { 
        return (DataSchema.InternetAccountTable) iaTable;
    }
    
    /**
    * Gets the CreditCardTable as a whole.
    * @return DataSchema.CreditCardTable
    */
    public DataSchema.CreditCardTable getCreditCards() { 
        return (DataSchema.CreditCardTable) ccTable;
    }
    
    /**
    * Gets the AddressTable as a whole.
    * @return DataSchema.AddressTable
    */
    public DataSchema.AddressTable getAddresses() { 
        return (DataSchema.AddressTable) addTable;
    }
    
    /**
    * Finds a Member by their primary key identifier.
    * @param id int
    * @return Member
    */
    public Member findByPrimaryKey(int id) {
        return (Member) memTable.selectId(id);
    }
    
    /**
    * Creates a new Member and appends entries to the MemberTable.
    * @param name String member name
    * @param phone String phone number
    * @param amount int amount due
    * @param igs boolean in good standing
    * @param num String member number
    * @param ccId int credit card id
    * @param addId int address id
    * @param iaId int internet account id
    * @return the newly created Member
    */
    public Member create(String name, String phone, int amount, boolean igs,
        String num, int ccId, int addId, int iaId) { 
        Member newMember = new Member(memTable.nextKey(), name, phone, amount,
            igs, num, ccId, addId, iaId);
        memTable.append(newMember);
        return newMember;
    }
    
    /**
    * Creates a new InternetAccount and appends it to the InternetAccountTable.
    * @param pass String password
    * @param sess long session id
    * @return the newly created InternetAccount
    */
    public InternetAccount create(String pass, long sess) {
        InternetAccount newAccount = new InternetAccount(iaTable.nextKey(), pass, sess);
        iaTable.append(newAccount);
        return newAccount;
    }
    
    /**
    * Creates a new CreditCard and appends it to the CreditCardTable.
    * @param type String credit card type
    * @param num String credit card number
    * @param ex Date credit card expiration date
    * @return the newly created CreditCard
    */
    public CreditCard create(String type, String num, Date ex) {
        CreditCard newCC = new CreditCard(ccTable.nextKey(), type, num, ex);
        ccTable.append(newCC);
        return newCC;
    }
    
    /**
    * Creates a new Address and appends it to the AddressTable.
    * @param house String address house number
    * @param street String street address
    * @param county String county address resides
    * @param zip String address zip code
    * @return the newly created Address
    */
    public Address create(String house, String street, String county, String zip) {
        Address newAdd = new Address(addTable.nextKey(), house, street, county, zip);
        addTable.append(newAdd);
        return newAdd;
    }
    
    /**
    * Finds a Member by their member number.
    * @param n String member number
    * @return Member
    */
    public Member findByMembershipNumber(String n) {
        ArrayList<Member> mem = memTable.selectWhere("number", n);
        if(!mem.isEmpty()) { return mem.get(0); }
        else { return null; }
    }
    
    /**
    * Finds a Member with the current session id.
    * @param id int session id
    * @return Member
    */
    public Member findBySessionId(int id) {
        if(id <= 0) { return null; }
        InternetAccount account = findAccountBySessionId(id);
        if(account != null) {
            ArrayList<Member> mem = 
                memTable.selectWhere("internetAccountId", account.getId());
            if(!mem.isEmpty()) { return mem.get(0); }
        }
        return null;
    }
    
    /**
    * Finds the CreditCard for the Member with the current session id.
    * @param id int session id
    * @return CreditCard
    */
    public CreditCard findCardBySessionId(int id) {
        Member mem = findBySessionId(id);
        if(mem != null) {
            ArrayList<CreditCard> ccList = 
                getCreditCards().selectWhere("id", mem.getCreditCardId());
            if(!ccList.isEmpty()) {
                return ccList.get(0);
            }
        }
        return null;
    }
    
    /**
    * Finds the Address for the Member with the current session id.
    * @param id int session id
    * @return Address
    */
    public Address findAddressBySessionId(int id) {
        Member mem = findBySessionId(id);
        if(mem != null) {
            ArrayList<Address> addList = 
                getAddresses().selectWhere("id", mem.getAddressId());
            if(!addList.isEmpty()) {
                return addList.get(0);
            }
        }
        return null;
    }
    
    /**
    * Finds the InternetAccount that matches the session id.
    * @param id int session id
    * @return InternetAccount
    */
    public InternetAccount findAccountBySessionId(int id) {
        ArrayList<InternetAccount> iaList = iaTable.selectWhere("sessionId", (long) id);
        if(!iaList.isEmpty()) { return iaList.get(0); }
        else { return null; }
    }
    
    /**
    * Finds the InternetAccount connected to a certain Member.
    * @param m Member
    * @return InternetAccount
    */
    public InternetAccount findAccountByMember(Member m) {
        if(m != null) {
            int id = m.getInternetAccountId();
            InternetAccount ia = (InternetAccount) iaTable.selectId(id);
            if(ia != null) { return ia; }
        }
        return null;
    }
    
    /**
    * Force the update of all MemberHome Tables.
    */
    public void update() {
        memTable.updateList();
        iaTable.updateList();
        ccTable.updateList();
        addTable.updateList();
    }
}