package com.library.server_layer;
import com.library.business_layer.field_list.CatalogedBook;
import com.library.business_layer.field_list.CatalogedBookDetails;
import com.library.business_layer.field_list.CatalogQuery;
import com.library.business_layer.field_list.Category;
import com.library.business_layer.field_list.Publisher;
import com.library.business_layer.message_list.CatalogQueryHome;
import com.library.business_layer.message_list.CatalogedBookHome;
import com.library.business_layer.message_list.CatalogedBookDetailsHome;
import com.library.business_layer.message_list.CategoryHome;
import com.library.business_layer.message_list.PublisherHome;
import com.library.protocol.field_list.PCatalogQuery;
import com.library.protocol.field_list.PCatalogedBook;
import com.library.protocol.field_list.PCatalogedBookDetails;
import com.library.protocol.message_list.PCatalogedBookHome;
import com.library.protocol.message_list.PCatalogedBookDetailsHome;
import com.library.protocol.message_list.PCategoryHome;
import com.library.protocol.message_list.PPublisherHome;
import com.library.persistence_layer.*;
import java.util.ArrayList;
import java.util.Collections;

/**
* The role of the CatalogServer is to communicate between the Home
* classes and server UI classes. The functionality of this server includes
* reading CatalogedBook, CatalogedBookDetails, Category, Publisher and Authors
* through various methods and indexing all CatalogedBooks.
* SERVER LAYER
*/
public class CatalogServer {
    private CatalogQueryHome cqh;
    private CatalogedBookHome cbh;
    private CatalogedBookDetailsHome cbdh;
    private CategoryHome cath;
    private PublisherHome pubh;
    private PCatalogedBookHome pCBH;
    private PCatalogedBookDetailsHome pCBDH;
    private PCategoryHome pCATH;
    private PPublisherHome pPUBH;
    
    /**
    * Basic constructor for this Object that initializes used Home classes.
    */
    public CatalogServer() {
        cqh = new CatalogQueryHome();
        cbh = new CatalogedBookHome();
        cbdh = new CatalogedBookDetailsHome();
        cath = new CategoryHome();
        pubh = new PublisherHome();
        pCBH = new PCatalogedBookHome();
        pCBDH = new PCatalogedBookDetailsHome();
        pCATH = new PCategoryHome();
        pPUBH = new PPublisherHome();
    }
    
    /**
    * Get all Category names with the Category id concatenated.
    * @return ArrayList of String names
    */
    public ArrayList<String> readCategoryNames() {
        ArrayList<String> nameList = new ArrayList<>();
        ArrayList<Category> cat = cath.getCategories().selectAll();
        for(int i = 0; i < cat.size(); i++) {
            //List is already in order by primary key
            nameList.add(cat.get(i).getName() + "(" + (i+1) + ")");
        }
        Collections.sort(nameList);
        return nameList;
    }
    
    /**
    * Get all Publisher names with the Publisher id concatenated.
    * @return ArrayList of String names
    */
    public ArrayList<String> readPublisherNames() {
        ArrayList<String> nameList = new ArrayList<>();
        ArrayList<Publisher> pub = pubh.getPublishers().selectAll();
        for(int i = 0; i < pub.size(); i++) {
            //List is already in order by primary key
            nameList.add(pub.get(i).getName() + "(" + (i+1) + ")");
        }
        Collections.sort(nameList);
        return nameList;
    }
    
    /**
    * Get all CatalogedBooks names under the given index heading.
    * @param h String index heading
    * @return ArrayList of String names 
    */
    public ArrayList<String> readCatalogedBookNames(String h) {
        ArrayList<String> nameList = new ArrayList<>();
        for(CatalogedBook cb : cbh.findByIndexHeading(h)) {
            nameList.add(cb.getName() + "(" + cb.getId() + ")");
        }
        return nameList;
    }
    
    /**
    * Get all authors from every CatalogedBook.
    * @return ArrayList of String names 
    */
    public ArrayList<String> readAuthorNames() {
        ArrayList<String> authors = new ArrayList<>();
        ArrayList<String[]> authorList = cbdh.findAuthors();
        for(String[] auth: authorList) {
            for(String a : auth) {
                if(!authors.contains(a)) {
                    authors.add(a);
                }
            }
        }
        Collections.sort(authors);
        return authors;
    }
    
    /**
    * Get all available indexes and the number of CatalogedBooks within them.
    * @return ArrayList of String indexes with number of books 
    */
    public ArrayList<String> readIndexHeadings() {
        //Hold separate variable since a number index heading is a wild card
        int numCount = 0; 
        boolean numHeading = false;
        //Number of CatalogedBooks for each index
        ArrayList<Integer> countList = new ArrayList<>();
        //List of index headings
        ArrayList<String> indexList = new ArrayList<>();
        //Fill with zeroes for each alphabet letter so it can be incremented later
        for(int i = 0; i < 26; i++) { countList.add(0); }
        for(CatalogedBook cb : cbh.getCatalogedBooks().selectAll()) {
            //Get the first letter of the CatalogedBook name to upper case
            String heading = "" + cb.getName().toUpperCase().charAt(0);
            //Position in list will be ASCII value minus 65
            int i = (int) heading.charAt(0)-65;
            if(i < 0) { //Negative means a numeric index heading
                if(!indexList.contains("#")) {
                    numHeading = true;
                    numCount++;
                } //Increment number of CatalogedBooks with numeric heading
                else { numCount++; } 
            } //If the list does not contain index add it
            else if(!indexList.contains(heading)) {
                indexList.add(heading);
                int j = indexList.indexOf(heading);
                countList.set(j, countList.get(j)+1);
            }
            else { //Otherwise just increment that index's count
                int j = indexList.indexOf(heading);
                countList.set(j, countList.get(j)+1); 
            } 
        } //Place the index heading and its count into the same string
        for(int i = 0; i < indexList.size(); i++) {
            indexList.set(i, (indexList.get(i) + " (" + countList.get(i) + ")"));
        } //Sort the list by alphanumeric value
        Collections.sort(indexList); //Then place the numeric heading first
        if(numCount > 0) { indexList.add(0, "# (" + numCount + ")"); }
        return indexList;
    }
    
    /**
    * Get all CatalogedBooks names under the given index heading. Transform
    * the CatalogedBooks into PCatalogedBooks for transferring to a server UI.
    * @param h String index heading
    * @return ArrayList of PCatalogedBooks 
    */
    public ArrayList<PCatalogedBook> readCatalogedBooks(String h) {
        ArrayList<PCatalogedBook> cbList = new ArrayList<>();
        for(CatalogedBook cb : cbh.findByIndexHeading(h)) {
            cbList.add(pCBH.create(cb.getIsbn(), cb.getName()));
        }
        return cbList;
    }
    
    /**
    * Get all CatalogedBooks that fall under the subset of a query. Transform
    * the CatalogedBooks into PCatalogedBooks for transferring to a server UI.
    * @param q PCatalogQuery query
    * @return ArrayList of PCatalogedBooks 
    */
    public ArrayList<PCatalogedBook> readCatalogedBooks(PCatalogQuery q) {
        ArrayList<PCatalogedBook> cbList = new ArrayList<>();
        CatalogQuery cq = 
            cqh.create(q.getPublisherIds(), q.getCategoryIds(), q.getAuthors());
        
        for(CatalogedBook cb : cbh.findByQuery(cq)) {
            cbList.add(pCBH.create(cb.getIsbn(), cb.getName()));
        }
        return cbList;
    }
    
    /**
    * Get all CatalogedBooks names that fall under the subset of a query.
    * @param q PCatalogQuery query
    * @return ArrayList of String names
    */
    public ArrayList<String> readCatalogedBookNames(PCatalogQuery q) {
        ArrayList<String> nameList = new ArrayList<>();
        CatalogQuery cq = 
            cqh.create(q.getPublisherIds(), q.getCategoryIds(), q.getAuthors());
        
        ArrayList<CatalogedBook> cbList = cbh.findByQuery(cq);
        for(int i = 0; i < cbList.size(); i++) {
            nameList.add("\"" + cbList.get(i).getName() + "\"(" + cbList.get(i).getId() + ")");
        }
        return nameList;
    }
    
    /**
    * Get the CatalogedBookDetails for a CatalogedBook id. Transform the
    * CatalogedBookDetails into PCatalogedBookDetails for transferring to a
    * server UI.
    * @param i int CatalogedBook id
    * @return PCatalogedBookDetails
    */
    public PCatalogedBookDetails readCatalogedBookDetails(int i) {
        CatalogedBookDetails cbd = cbdh.findByCatalogedBookId(i);
        if(cbd != null) { 
            return pCBDH.create(cbd.getEdition(), cbd.getAuthors(), 
            cbd.getDescription());
        }
        else { return null; }
    }
    
    /**
    * Get the CatalogedBookDetails for a CatalogedBook id. Transform the
    * CatalogedBookDetails into PCatalogedBookDetails for transferring to a
    * server UI.
    * @param i int CatalogedBook id
    * @return PCatalogedBookDetails
    */
    public PCatalogedBook readCatalogedBook(int i) {
        CatalogedBook cb = cbh.findByPrimaryKey(i);
        if(cb != null) { 
            return pCBH.create(cb.getIsbn(), cb.getName());
        }
        else { return null; }
    }
    
    /**
    * Get all CatalogedBookDetails for all CatalogedBooks. Transform all the
    * CatalogedBookDetails into PCatalogedBookDetails for transferring to a
    * server UI.
    * @return ArrayList of PCatalogedBookDetails
    */
    public ArrayList<PCatalogedBookDetails> readCatalogedBookDetails() {
        ArrayList<PCatalogedBookDetails> cbdList = new ArrayList<>();
        for(CatalogedBookDetails cbd : cbdh.getCatalogedBookDetails().selectAll()) {
            cbdList.add(pCBDH.create(cbd.getEdition(), cbd.getAuthors(),
                cbd.getDescription()));
        }
        return cbdList;
    }
    
    /**
    * Get all CatalogedBooks that have a certain author. Transform all the
    * CatalogedBooks into PCatalogedBooks for transferring to a server UI.
    * @param a String author name
    * @return ArrayList of PCatalogedBooks
    */
    public ArrayList<PCatalogedBook> readCatalogedBooksByAuthor(String a) {
        ArrayList<PCatalogedBook> pCBList = new ArrayList<>();
        ArrayList<CatalogedBook> cbList = new ArrayList<>();
        for(CatalogedBook cb : cbh.findByAuthor(a)) {
            cbList = cbh.findByAuthor(a);
            pCBList.add(pCBH.create(cb.getIsbn(), cb.getName()));
        }
        return pCBList;
    }
    
    /**
    * Force the update of the CatalogServer and all its Homes
    */
    public void update() {
        cbh.update();
        cbdh.update();
        cath.update();
        pubh.update();
    }
}