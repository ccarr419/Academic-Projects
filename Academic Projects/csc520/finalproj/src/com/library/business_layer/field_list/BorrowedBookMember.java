package com.library.business_layer.field_list;
import java.io.Serializable;

/**
* The BorrowedBookMember exists solely as a connection between a BorrowedBook
* and Member Object. Contains only the BorrowedBook's and Member's unique 
* identifiers. Also implements Serializable so it can be serialized for later use.
* BUSINESS LAYER CLASS
* @see com.library.business_layer.field_list.BorrowedBook
* @see com.library.business_layer.field_list.Member
*/
public class BorrowedBookMember implements Serializable {
    private int borrowedBookId;
    private int memberId;
    
    /**
    * Contstructs BorrowedBookMember Object and its foreign key ids.
    * @param bi BorrowedBook id
    * @param mi Member id
    */
    public BorrowedBookMember(int bi, int mi) {
        setBorrowedBookId(bi);
        setMemberId(mi);
    }
    
    /**
    * Gets the BorrowedBook identifier as an int.
    * @return BorrowedBook id int
    */
    public int getBorrowedBookId() { return borrowedBookId; }
    
    /**
    * Gets the Member identifier as an int.
    * @return Member id int
    */
    public int getMemberId() { return memberId; }
    
    /**
    * Sets the value for the BorrowedBook identifier.
    * @param bi int to set BorrowdBook id to
    */
    public void setBorrowedBookId(int bi) { borrowedBookId = bi; }
    
    /**
    * Sets the value for the Member identifier.
    * @param mi int to set Member id to
    */
    public void setMemberId(int mi) { memberId = mi; }
}