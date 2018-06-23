package com.library.business_layer.field_list;

/**
* A CatalogQuery is a user search query that is used to search the catalog of
* books for a certain book or subset of books. A CatalogQuery can contain
* multiple publisher ids, category ids and authors to search for.
* BUSINESS LAYER CLASS
* @see com.library.business_layer.field_list.Author
* @see com.library.business_layer.field_list.Category
* @see com.library.business_layer.field_list.Publisher
*/
public class CatalogQuery {
    private int[] publisherIds;
    private int[] categoryIds;
    private String[] authors;
    
    /**
    * Contstructs CatalogQuery Object by setting its attributes to a value.
    * @param p publisher ids
    * @param c category ids
    * @param a authors
    */
    public CatalogQuery(int p[], int c[], String a[]) {
        setPublisherIds(p);
        setCategoryIds(c);
        setAuthors(a);
    }
    
    /**
    * Gets the publisher ids in the query as an array.
    * @return publiser ids int array
    */
    public int[] getPublisherIds() { return publisherIds; }
    
    /**
    * Gets the category ids in the query as an array.
    * @return edition int array
    */
    public int[] getCategoryIds() { return categoryIds; }
    
    /**
    * Gets the authors in the query as an array.
    * @return authors String array
    */
    public String[] getAuthors() { return authors; }
    
    /**
    * Sets the publisher id list for the query.
    * @param p int array to set publisher ids to
    */
    public void setPublisherIds(int p[]) { publisherIds = p; }
    
    /**
    * Sets the category id list for the query.
    * @param c int array to set category ids to
    */
    public void setCategoryIds(int c[]) { categoryIds = c; }
    
    /**
    * Sets the author list for the query.
    * @param a String array to set authors to
    */
    public void setAuthors(String a[]) { authors = a; }
}
