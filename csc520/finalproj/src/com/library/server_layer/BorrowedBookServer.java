package com.library.server_layer;
import com.library.business_layer.field_list.Member;
import com.library.business_layer.field_list.BorrowedBook;
import com.library.business_layer.message_list.BorrowedBookHome;
import com.library.business_layer.message_list.MemberHome;
import com.library.protocol.message_list.PBorrowedBookHome;
import com.library.protocol.field_list.PBorrowedBook;
import com.library.persistence_layer.*;
import java.util.ArrayList;

/**
* The role of the BorrowedBookServer is to communicate between the Home
* classes and server UI classes. The functionality of this server includes
* returning all borrowed books for a member session id.
* SERVER LAYER
*/
public class BorrowedBookServer {
    private MemberHome mh;
    private BorrowedBookHome bbh;
    private PBorrowedBookHome pBBH;

    /**
    * Basic constructor for this Object that initializes used Home classes.
    */
    public BorrowedBookServer() { 
        mh = new MemberHome();
        bbh = new BorrowedBookHome();
        pBBH = new PBorrowedBookHome();
    }
    
    /**
    * Get all BorrowedBooks for a member with the session id. Transforms all
    * BorrowedBooks into PBorrowedBook for tranferring to server UI.
    * @param i int session id
    * @return ArrayList of PBorrowedBook
    */
    public ArrayList<PBorrowedBook> readBorrowedBook(int i) {
        ArrayList<PBorrowedBook> pBBList = new ArrayList<>();
        Member mem = mh.findBySessionId(i);
        if(mem != null) {
            for(BorrowedBook bb : bbh.findByMember(mem)) {
                pBBList.add(pBBH.create(bb.getStartDate(), bb.getDueDate()));
            }
        }
        return pBBList;
    }
    
    /**
    * Force the update of the AuthenticationServer and all its Homes
    */
    public void update() {
        mh.update();
        bbh.update();
    }
}