package com.library.business_layer.field_list;
import java.io.Serializable;

/**
* A CatalogedBook is a representaion of basic book identifying information.
* CatalogedBook contains the book ISBN, title, foreign keys to category,
* details and publisher, and a unique identifier. Identifiers are meant to 
* act similar to a primary key in a database and as such should be unique. 
* Also implements Serializable so it can be serialized for later use.
* BUSINESS LAYER CLASS
* @see com.library.business_layer.field_list.CatalogedBookDetails
* @see com.library.business_layer.field_list.Category
* @see com.library.business_layer.field_list.Publisher
*/
public class CatalogedBook implements Serializable {
    private int id;
    private String isbn;
    private String name;
    private int categoryId;
    private int detailsId;
    private int publisherId;
    
    /**
    * Contstructs CatalogedBook Object by setting its attributes to a value.
    * @param i identifier
    * @param is isbn
    * @param n book name
    * @param c category id
    * @param d details id
    * @param p publisher id
    */
    public CatalogedBook(int i, String is, String n, int c, int d, int p) {
        setId(i);
        setIsbn(is);
        setName(n);
        setCategoryId(c);
        setDetailsId(d);
        setPublisherId(p);
    }
        
    /**
    * Gets the int identifier value for this Object.
    * @return id as int
    */
    public int getId() { return id; }
        
    /**
    * Gets the CatalogedBook isbn as a String.
    * @return isbn String
    */
    public String getIsbn() { return isbn; }
        
    /**
    * Gets the CatalogedBook name as a String.
    * @return name String
    */
    public String getName() { return name; }
    
    /**
    * Gets the identifier for this CatalogedBook's Category as an int.
    * @return category id int
    */
    public int getCategoryId() { return categoryId; }
    
    /**
    * Gets the identifier for this CatalogedBook's details as an int.
    * @return details id int
    */
    public int getDetailsId() { return detailsId; }
    
    /**
    * Gets the identifier for this CatalogedBook's publisher as an int.
    * @return publisher id int
    */
    public int getPublisherId() { return publisherId; }
        
    /**
    * Sets the value for the Object identifier.
    * @param i int to set id to
    */
    public void setId(int i) { id = i; }
       
    /**
    * Sets the value for the CatalogedBook's isbn.
    * @param is String to set isbn to
    */
    public void setIsbn(String is) { isbn = is; }
        
    /**
    * Sets the value for the CatalogedBook's name.
    * @param n String to set name to
    */
    public void setName(String n) { name = n; }
    
    /**
    * Sets the value for the Category id.
    * @param c int to set Category id to
    */
    public void setCategoryId(int c) { categoryId = c; }
    
    /**
    * Sets the value for the details id.
    * @param d int to set details id to
    */
    public void setDetailsId(int d) { detailsId = d; }
    
    /**
    * Sets the value for the publisher id.
    * @param p int to set publisher id to
    */
    public void setPublisherId(int p) { publisherId = p; }
}