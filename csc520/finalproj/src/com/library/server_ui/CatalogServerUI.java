package com.library.server_ui;
import com.library.server_layer.CatalogServer;
import com.library.protocol.field_list.PCatalogQuery;
import com.library.protocol.field_list.PCatalogedBook;
import com.library.protocol.field_list.PCatalogedBookDetails;
import com.library.protocol.message_list.PCatalogQueryHome;
import com.library.persistence_layer.*;
import java.util.ArrayList;
import java.util.Collections;

/**
* The role of the BorrowedBookServer is to let the server and user communicate 
* back and forth. This is done by reading/writing to the console. The 
* functionality of this server UI includes getting all borrowed books of a member.
* SERVER LAYER
*/
public class CatalogServerUI {
    private CatalogServer cs;
    private PCatalogQueryHome pCQH;
    
    /**
    * Basic constructor that initializes its corresponding server.
    */
    public CatalogServerUI() {
        cs = new CatalogServer();
        pCQH = new PCatalogQueryHome();
    }
    
    /**
    * Goes through and prints all available index headings.
    */
    public void index() {
        cs.update();
        ArrayList<String> headings = cs.readIndexHeadings();
        if(headings.isEmpty()) { 
            System.out.println("No Cataloged Books Found"); 
        }
        else {
            for(String str : headings) {
                System.out.println(str);
            }
        }
        System.out.println("");
    }
    
    /**
    * Browses, returns and prints all books that fall under the index heading.
    * @param h String index heading
    */
    public void browse(String h) {
        cs.update();
        String index = h.toUpperCase(); //Show the current index
        System.out.println("\nIndex Heading " + index + ":");
        ArrayList<String> nameList = cs.readCatalogedBookNames(h);
        if(nameList.isEmpty()) { //No books for the given heading
            System.out.println("No Cataloged Books Found\n");
        }
        else {
            Collections.sort(nameList); //Iterate through and number
            for(int i = 0; i < nameList.size(); i++) {
                System.out.println("" + (i+1) + ".) " + nameList.get(i));
            }
            System.out.println("");
        }
    }
    
    /**
    * Prints all available categories, publishers and authors. Items are
    * printed in a sorted and tabular manner.
    */
    public void search() {
        cs.update(); //Format the string for tabular output
        String table = 
            String.format("%-20s%-25s%-25s","Categories","Publishers","Authors");
        table += "\n" +
            String.format("%-20s%-25s%-25s","==========","==========","=======");
        ArrayList<String> categories = cs.readCategoryNames();
        ArrayList<String> publishers = cs.readPublisherNames();
        ArrayList<String> authors = cs.readAuthorNames();
        
        int max; //Get the list with the most elements, that will be max size
        if(categories.size() >= publishers.size() &&
            categories.size() >= authors.size()) { max = categories.size(); }
        else if(publishers.size() >= categories.size() &&
            publishers.size() >= categories.size()) { max = publishers.size(); }
        else { max = authors.size(); }
        //Iterate through to the max size. If a list ran out of items, print nothing
        for(int i = 0; i < max; i++) {
            String category, publisher, author;
            if(i < categories.size()) { category = categories.get(i); }
            else { category = ""; }
            if(i < publishers.size()) { publisher = publishers.get(i); }
            else { publisher = ""; }
            if(i < authors.size()) { author = authors.get(i); }
            else { author = ""; }
            //Format category, publisher and author in tabular manner
            table += "\n" + String.format("%-20s%-25s%-25s", 
                category, 
                publisher,
                author
            );
        }
        System.out.println(table + "\n");
    }
    
    /**
    * Searches books for a subset that match a given query. Prints all books
    * that match the publishers, categories and authors given. Print the query
    * and results, if no books were found inform the user.
    * @param pid int[] publisher ids
    * @param cid int[] category ids
    * @param auth String[] author names
    */
    public void query(int pid[], int cid[], String auth[]) {
        cs.update();
        PCatalogQuery q = pCQH.create(pid, cid, auth); //Create protocol query
        ArrayList<String> nameList = cs.readCatalogedBookNames(q);
        System.out.println(q.toString()); //Show the user the query they searched for
        if(nameList.isEmpty()) { System.out.println("No Books Found\n"); return; }
        Collections.sort(nameList); //Sort and number the results
        for(int i = 0; i < nameList.size(); i++) {
            System.out.println("" + (i+1) + ".) " + nameList.get(i));
        }
        System.out.println("");
    }
    
    /**
    * Finds and prints the book details for a given book id. Fails if the
    * CatalogedBook id does not exist.
    * @param id int CatalogedBook id
    */
    public void details(int id) {
        cs.update();
        PCatalogedBook pCB = cs.readCatalogedBook(id);
        PCatalogedBookDetails pCBD = cs.readCatalogedBookDetails(id);
        if(pCB != null && pCBD != null) {
            System.out.println(pCB.toString());
            System.out.println("ISBN: " + pCB.getIsbn());
            System.out.println(pCBD.toString());
        }
        else { System.out.println("An error has occurred\n"); }
    }
}
