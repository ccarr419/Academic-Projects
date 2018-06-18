package com.library.business_layer.message_list;
import com.library.business_layer.field_list.BorrowedBook;
import com.library.business_layer.field_list.BorrowedBookMember;
import com.library.business_layer.field_list.Member;
import com.library.persistence_layer.*;
import java.util.ArrayList;
import java.util.Date;

/**
* BorrowedBookHome serves as a way to access the BorrowedBook and
* BorrowedBookMember Tables. Thus it also serves as an accessor to each
* table element attributes. Another purpose of BorrowedBook Home is
* to create and add any new entries to the BorrowedBook and BorrowedBookMember Tables.
* BUSINESS LAYER CLASS
* @see com.library.business_layer.field_list.BorrowedBook
* @see com.library.business_layer.field_list.BorrowedBookMember
*/
public class BorrowedBookHome {
    private Table bbTable;
    private Table bbmTable;
    
    /**
    * Basic constructor for BorrowedBookHome that instantiates home's Tables.
    */
    public BorrowedBookHome() { 
        bbTable = new DataSchema.BorrowedBookTable();
        bbmTable = new DataSchema.BorrowedBookMemberTable();
    }
    
    /**
    * Gets the BorrowedBook Table as a whole.
    * @return DataSchema.BorrowedBookTable
    */
    public DataSchema.BorrowedBookTable getBorrowedBooks() { 
        return (DataSchema.BorrowedBookTable) bbTable; 
    }
    
    /**
    * Gets the BorrowedBookMember Table as a whole.
    * @return DataSchema.BorrowedBookMemberTable
    */
    public DataSchema.BorrowedBookMemberTable getBorrowedBookMembers() { 
        return (DataSchema.BorrowedBookMemberTable) bbmTable; 
    }
    
    /**
    * Finds a Borrowed by its primary key identifier.
    * @param id int
    * @return BorrowedBook
    */
    public BorrowedBook findByPrimaryKey(int id) {
        return (BorrowedBook) bbTable.selectId(id);
    }
    
    /**
    * Creates a new BorrowedBook and appends it to the BorrowedBookTable and 
    * BorrowedBookMemberTable.
    * @param num String borrowed book number
    * @param startDate Date borrowed book start date
    * @param dueDate Date borrowed book due date
    * @param mid int member id
    * @return the newly created BorrowedBook
    */
    public BorrowedBook create(String num, Date startDate, Date dueDate, int mid) { 
        int key = bbTable.nextKey();
        BorrowedBook newBorrowedBook = 
            new BorrowedBook(key, num, startDate, dueDate);
        BorrowedBookMember newBorrowedBookMember =
            new BorrowedBookMember(key, mid);
        bbTable.append(newBorrowedBook);
        bbmTable.append(newBorrowedBookMember);
        return newBorrowedBook;
    }
    
    /**
    * Finds all BorrowedBooks connected to a specific Member.
    * @param m Member to find borrowed books for
    * @return ArrayList of the member's borrowed books
    */
    public ArrayList<BorrowedBook> findByMember(Member m) { 
        ArrayList<BorrowedBookMember> tmp = new ArrayList<>();
        ArrayList<BorrowedBook> out = new ArrayList<>();
        tmp = bbmTable.selectWhere("memberId", m.getId());
        //Go through member table to find all connected borrowed books
        for(BorrowedBookMember mem : tmp) {
            out.add((BorrowedBook)
                bbTable.selectId(mem.getBorrowedBookId())
            );
        }
        return out;
    }
    
    /**
    * Force the update of all BorrowedBookHome Tables.
    */
    public void update() {
        bbTable.updateList();
        bbmTable.updateList();
    }
}