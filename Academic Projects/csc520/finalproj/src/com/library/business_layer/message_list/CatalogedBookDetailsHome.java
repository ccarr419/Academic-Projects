package com.library.business_layer.message_list;
import com.library.business_layer.field_list.CatalogedBookDetails;
import com.library.business_layer.field_list.CatalogedBook;
import com.library.persistence_layer.*;
import java.util.ArrayList;

/**
* CatalogedBookDetailsHome serves as a way to access the 
* CatalogBookDetailsTable. Thus it also serves as an accessor to the table's 
* element's attributes. Another purpose of CatalogedBookDetailsHome is to 
* create and add any new entries to the CatalogedBookDetailsTable.
* BUSINESS LAYER CLASS
* @see com.library.business_layer.field_list.CatalogedBookDetails
*/
public class CatalogedBookDetailsHome {
    private Table cbdTable;
    private Table cbTable;
    
    /**
    * Basic constructor for CatalogedBookDetailsHome that instantiates home's Tables.
    */
    public CatalogedBookDetailsHome() { 
        cbdTable = new DataSchema.CatalogedBookDetailsTable();
        cbTable = new DataSchema.CatalogedBookTable();
    }
    
    /**
    * Gets the CatalogedBookDetailsTable as a whole.
    * @return DataSchema.CatalogedBookDetailsTable
    */
    public DataSchema.CatalogedBookDetailsTable getCatalogedBookDetails() { 
        return (DataSchema.CatalogedBookDetailsTable) cbdTable;
    }
    
    /**
    * Gets a list of all author arrays for every CatalogedBookDetails
    * @return ArrayList of String arrays containing authors
    */
    public ArrayList<String[]> findAuthors() {
        ArrayList<String[]> authorList = new ArrayList<>();
        for(CatalogedBookDetails cbd : getCatalogedBookDetails().selectAll()) {
            authorList.add(cbd.getAuthors());
        }
        return authorList;
    }
    
    /**
    * Finds CatalogedBookDetails by its primary key identifier.
    * @param id int
    * @return CatalogedBookDetails
    */
    public CatalogedBookDetails findByPrimaryKey(int id) {
        return (CatalogedBookDetails) cbdTable.selectId(id);
    }
    
    /**
    * Creates a new CatalogedBookDetails and appends it to the CatalogedBookDetailsTable.
    * @param edit String book edition
    * @param auth String[] book authors
    * @param desc String book description
    * @return the newly created CatalogedBookDetails
    */
    public CatalogedBookDetails create(String edit, String auth[], String desc) { 
        CatalogedBookDetails newCatalogedBookDetails = 
            new CatalogedBookDetails(cbdTable.nextKey(), edit, auth, desc);
        cbdTable.append(newCatalogedBookDetails);
        return newCatalogedBookDetails;
    }
    
    /**
    * Finds CatalogedBookDetails for a given CatalogedBook id.
    * @param id cataloged book to find details for
    * @return CatalogedBookDetails for CatalogedBook or null if does not exist
    */
    public CatalogedBookDetails findByCatalogedBookId(int id) {
        ArrayList<CatalogedBook> cb = cbTable.selectWhere("id", id);
        if(!cb.isEmpty()) { //Make sure a CatalogedBook exists with that id
            CatalogedBook book = cb.get(0); //ArrayList will only by one entry
            ArrayList<CatalogedBookDetails> cbd = 
                cbdTable.selectWhere("id", book.getDetailsId());
            if(!cbd.isEmpty()) { return cbd.get(0); } //Make sure details exist
        }
        return null; //A CatalogedBook with that id does not exist
    }
    
    /**
    * Force the update of all CatalogedBookDetailsHome Tables.
    */
    public void update() {
        cbdTable.updateList();
        cbTable.updateList();
    }
}