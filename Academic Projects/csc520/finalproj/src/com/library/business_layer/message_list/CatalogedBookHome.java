package com.library.business_layer.message_list;
import com.library.business_layer.field_list.CatalogedBook;
import com.library.business_layer.field_list.CatalogedBookDetails;
import com.library.business_layer.field_list.CatalogQuery;
import com.library.persistence_layer.*;
import java.util.ArrayList;
import java.util.Iterator;

/**
* CatalogedBookHome serves as a way to access the CatalogBookTable. Thus it 
* also serves as an accessor to the table's element's attributes. Another purpose 
* of CatalogedBookHome is to createand add any new entries to the CatalogedBookTable.
* BUSINESS LAYER CLASS
* @see com.library.business_layer.field_list.CatalogedBook
*/
public class CatalogedBookHome {
    private Table cbTable;
    private Table cbdTable;
    
    /**
    * Basic constructor for CatalogedBookHome that instantiates home's Tables.
    */
    public CatalogedBookHome() {
        cbTable = new DataSchema.CatalogedBookTable();
        cbdTable = new DataSchema.CatalogedBookDetailsTable();
    }
    
    /**
    * Gets the CatalogedBookTable as a whole.
    * @return DataSchema.CatalogedBookTable
    */
    public DataSchema.CatalogedBookTable getCatalogedBooks() { 
        return (DataSchema.CatalogedBookTable) cbTable;
    }
    
    /**
    * Gets the CatalogedBookDetailsTable as a whole.
    * @return DataSchema.CatalogedBookDetailsTable
    */
    private DataSchema.CatalogedBookDetailsTable getCatalogedBookDetails() { 
        return (DataSchema.CatalogedBookDetailsTable) cbdTable;
    }
    
    /**
    * Finds a CatalogedBook by its primary key identifier.
    * @param id int
    * @return CatalogedBook
    */
    public CatalogedBook findByPrimaryKey(int id) {
        return (CatalogedBook) cbTable.selectId(id);
    }
    
    /**
    * Creates a new CatalogedBook and appends it to the CatalogedBookTable.
    * @param isbn String ISBN
    * @param name String book title
    * @param cid int category id
    * @param did int details id
    * @param pid int publisher id
    * @return the newly created CatalogedBook
    */
    public CatalogedBook create(String isbn, String name, int cid, int did, int pid) { 
        CatalogedBook newCatalogedBook = 
            new CatalogedBook(cbTable.nextKey(), isbn, name, cid, did, pid);
        cbTable.append(newCatalogedBook);
        return newCatalogedBook;
    }
    
    /**
    * Finds a CatalogedBook by its index heading. Goes through all the
    * CatalogedBooks and tosses out all the ones that do not match the heading
    * i.e. the first character in the title. CatalogedBooks that have a number
    * at the beginning of its name will fall under the '#' heading.
    * @param h String index heading to search for
    * @return ArrayList of CatalogedBooks with a index heading of 'h'
    */
    public ArrayList<CatalogedBook> findByIndexHeading(String h) {
        String checkStr = h.toLowerCase(); //The index to check for
        ArrayList<CatalogedBook> outList = new ArrayList<>();
        ArrayList<CatalogedBook> cbList = getCatalogedBooks().selectAll();
        //Get all CatalogedBooks and search for the ones under this index
        for(CatalogedBook cb : cbList) {
            String title = cb.getName().toLowerCase();
            //For each character in the heading, check if the first character
            //in the CatalogedBook name matches
            for(int i = 0; i < h.length(); i++) {
                if((title.indexOf(checkStr.charAt(i))) == 0) {
                    outList.add(cb); //Only select the ones that match
                }
                //Check all numeric values if heading contains the '#' sign
                else if(checkStr.charAt(i) == '#') {
                    for(int j = 0; j < 10; j++) {
                        //j+48 will equal a value of 0-9 in ASCII
                        if((title.indexOf((char)j+48)) == 0) {
                            outList.add(cb);
                        }
                    }
                }
            }
        }
        return outList;
    }
    
    /**
    * Finds all CatalogedBooks that match a specific query parameter. A query
    * will search by any number of publishers, any number of categories, any
    * number of authors or any combination of the three. CatalogedBooks that
    * are returned meet the requirements of matching all given query conditions.
    * @param q CatalogQuery query
    * @return ArrayList of CatalogedBooks meeting the requirements of query
    */
    public ArrayList<CatalogedBook> findByQuery(CatalogQuery q) {
        Iterator<CatalogedBook> itr;
        //List of CatalogedBooks that match the given query publishers
        ArrayList<CatalogedBook> cb1 = new ArrayList<>();
        //List of CatalogedBooks that match the given query categories
        ArrayList<CatalogedBook> cb2 = new ArrayList<>();
        //List of CatalogedBooks that match the given query authors
        ArrayList<CatalogedBook> cb3 = new ArrayList<>();
        //Temporary list used to check for duplicates
        ArrayList<CatalogedBook> tmp = new ArrayList<>();
        //List of CatalogedBooks to return
        ArrayList<CatalogedBook> resultList = new ArrayList<>();
        for(int id : q.getPublisherIds()) {
            tmp = cbTable.selectWhere("publisherId", id);
            if(!tmp.isEmpty()) { //Find all unique books for given publishers
                for(CatalogedBook c : tmp) {
                    if(!cb1.contains(c)) {
                        cb1.add(c); 
                    }
                }
            }
        }
        for(int id : q.getCategoryIds()) {
            tmp = cbTable.selectWhere("categoryId", id);
            if(!tmp.isEmpty()) { //Find all unique books for given categories
                for(CatalogedBook c : tmp) {
                    if(!cb2.contains(c)) {
                        cb2.add(c); 
                    }
                }  
            }
        }
        for(String auth : q.getAuthors()) {
            tmp = findByAuthor(auth);
            if(!tmp.isEmpty()) { //Find all unique books for given authors
                for(CatalogedBook c : tmp) {
                    if(!cb3.contains(c)) {
                        cb3.add(c); 
                    }
                }
            }
        }
        //If query contained publishers
        if(!cb1.isEmpty()) {
            //Get iterator so modify and iterate at same time
            itr = cb1.iterator(); 
            while(itr.hasNext()) {
                CatalogedBook cb = itr.next();
                for(int i = 0; i < cb2.size(); i++) {
                    //Iterate through query categories and if a CatalogedBook
                    //from query publishers is not present, remove it
                    if(!cb.equals(cb2.get(i)) && i == cb2.size()-1) {
                        itr.remove();
                    } //If the CatalogedBook is found, move to the next one
                    else if(cb.equals(cb2.get(i))) { break; }
                }
            }
            //Get iterator so modify and iterate at same time
            itr = cb1.iterator();
            while(itr.hasNext()) {
                CatalogedBook cb = itr.next();
                for(int i = 0; i < cb3.size(); i++) {
                    //Iterate through query authors and if a CatalogedBook
                    //from query publishers is not present, remove it
                    if(!cb.equals(cb3.get(i)) && i == cb3.size()-1) {
                        itr.remove();
                    } //If the CatalogedBook is found, move to the next one
                    else if(cb.equals(cb3.get(i))) { break; }
                }
            } //All non sequitur CatalogedBooks should be removed, return list
            resultList = (ArrayList<CatalogedBook>) cb1.clone();
        }
        //If query contains categories but not publishers
        else if(!cb2.isEmpty()) { 
            //Get iterator so modify and iterate at same time
            itr = cb2.iterator();
            while(itr.hasNext()) {
                CatalogedBook cb = itr.next();
                for(int i = 0; i < cb3.size(); i++) {
                    //Iterate through query authors and if a CatalogedBook
                    //from query categories is not present, remove it
                    if(!cb.equals(cb3.get(i)) && i == cb3.size()-1) {
                        itr.remove();
                    } //If the CatalogedBook is found, move to the next one
                    else if(cb.equals(cb3.get(i))) { break; }
                }
            } //All non sequitur CatalogedBooks should be removed, return list
            resultList = (ArrayList<CatalogedBook>) cb2.clone();
        }
        //If query only contains authors, just return the authors
        else { resultList = (ArrayList<CatalogedBook>) cb3.clone(); }
        
        return resultList;
    }
    
    /**
    * Finds all CatalogedBooks that were written by a specific author.
    * @param a String author name
    * @return ArrayList of CatalogedBooks by author
    */
    public ArrayList<CatalogedBook> findByAuthor(String a) {
        ArrayList<CatalogedBook> cbList = new ArrayList<>();
        //Holds the selected CatalogedBook for certain details id
        ArrayList<CatalogedBook> tmp = new ArrayList<>();
        //Iterate through all CatalogedBookDetails and their authors
        for(CatalogedBookDetails cbd : getCatalogedBookDetails().selectAll()) {
            for(String author : cbd.getAuthors()) {
                if(author.equals(a)) { //If author matches, get the CatalogedBook
                    tmp = cbTable.selectWhere("detailsId", cbd.getId());
                    if(!tmp.isEmpty()) { //Add the CatalogedBook if it exists
                        cbList.add(tmp.get(0));
                        break;
                    }
                }
            }
        }
        return cbList;
    }
    
    /**
    * Force the update of all CatalogedBookHome Tables.
    */
    public void update() {
        cbTable.updateList();
        cbdTable.updateList();
    }
}
    