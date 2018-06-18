package com.library.business_layer.field_list;
import java.io.Serializable;

/**
* The AuthorCatalogedBookDetails exists solely as a connection between an
* Author and CatalogedBookDetails Object. Contains only the Author's and
* CatalogedBookDetails' unique identifiers. Also implements Serializable so 
* it can be serialized for later use.
* BUSINESS LAYER CLASS
* @see com.library.business_layer.field_list.Author
* @see com.library.business_layer.field_list.CatalogedBookDetails
*/
public class AuthorCatalogedBookDetails implements Serializable {
    private int authorId;
    private int catalogedBookDetailsId;
    
    /**
    * Contstructs AuthorCatalogedBookDetails Object and its foreign key ids.
    * @param ai Author id
    * @param cbdi CatalogedBookDetails id
    */
    public AuthorCatalogedBookDetails(int ai, int cbdi) {
        setAuthorId(ai);
        setCatalogedBookDetailsId(cbdi);
    }
    
    /**
    * Gets the Author identifier as an int.
    * @return Author id int
    */
    public int getAuthorId() { return authorId; }
    
    /**
    * Gets the CatalogedBookDetails identifier as an int.
    * @return CatalogedBookDetails id int
    */
    public int getCatalogedBookDetailsId() { return catalogedBookDetailsId; }
    
    /**
    * Sets the value for the Author identifier.
    * @param ai int to set Author id to
    */
    public void setAuthorId(int ai) { authorId = ai; }
    
    /**
    * Sets the value for the Author identifier.
    * @param cbdi int to set CatalogedBookDetails id to
    */
    public void setCatalogedBookDetailsId(int cbdi) { catalogedBookDetailsId = cbdi; }
}