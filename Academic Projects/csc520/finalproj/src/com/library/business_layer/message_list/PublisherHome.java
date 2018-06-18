package com.library.business_layer.message_list;
import com.library.business_layer.field_list.Publisher;
import com.library.persistence_layer.*;
import java.util.Collections;
import java.util.ArrayList;

/**
* PublisherHome serves as a way to access the PublisherTable. Thus it also 
* serves as an accessor to the table's element's attributes. Another purpose of
* PublisherHome is to create and add any new entries to the PublisherTable.
* BUSINESS LAYER CLASS
* @see com.library.business_layer.field_list.Publisher
*/
public class PublisherHome {
    private Table pubTable;
    
    /**
    * Basic constructor for PublisherHome that instantiates home's Tables.
    */
    public PublisherHome() { 
        pubTable = new DataSchema.PublisherTable();
    }
    
    /**
    * Gets the PublisherTable as a whole.
    * @return DataSchema.PublisherTable
    */
    public DataSchema.PublisherTable getPublishers() { 
        return (DataSchema.PublisherTable) pubTable;
    }
    
    /**
    * Finds a Publisher by their primary key identifier.
    * @param id int
    * @return Publisher
    */
    public Publisher findByPrimaryKey(int id) {
        return (Publisher) pubTable.selectId(id);
    }
    
    /**
    * Creates a new Publisher and appends it to the PublisherTable.
    * @param name String publisher name
    * @return the newly created Publisher
    */
    public Publisher create(String name) { 
        Publisher newMember = new Publisher(pubTable.nextKey(), name);
        pubTable.append(newMember);
        return newMember;
    }
    
    /**
    * Gets the all the Publishers in PublisherTable sorted by name.
    * @return sorted ArrayList&lt;Publisher&gt;
    */
    public ArrayList<Publisher> findPublisherNames() {
        ArrayList<Publisher> p = pubTable.selectAll();
        Collections.sort(p);
        return p;
    }
    
    /**
    * Force the update of all PublisherHome Tables.
    */
    public void update() {
        pubTable.updateList();
    }
}