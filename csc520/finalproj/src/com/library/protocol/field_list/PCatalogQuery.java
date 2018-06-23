package com.library.protocol.field_list;
import com.library.business_layer.field_list.CatalogQuery;

/**
* PCatalogQuery serves as a protocol to transfer Table information from the server
* to the UI. Only serves as a way to view, print and facilitate information.
* PROTOCOL LAYER
* @see com.library.business_layer.field_list.CatalogQuery
*/
public class PCatalogQuery {
    private int[] publisherIds;
    private int[] categoryIds;
    private String[] authors;
    
    /**
    * Basic constructor that sets all attributes.
    * @param p int[] publisher ids
    * @param c int[] category ids
    * @param a String[] author names
    */
    public PCatalogQuery(int p[], int c[], String a[]) {
        publisherIds = p;
        categoryIds = c;
        authors = a;
    }
    
    /**
    * @return int[] publisher ids
    * @see com.library.business_layer.field_list.CatalogQuery#getPublisherIds()
    */
    public int[] getPublisherIds() { return publisherIds; }
    
    /**
    * @return int[] category ids
    * @see com.library.business_layer.field_list.CatalogQuery#getCategoryIds()
    */
    public int[] getCategoryIds() { return categoryIds; }
    
    /**
    * @return String[] author names
    * @see com.library.business_layer.field_list.CatalogQuery#getAuthors()
    */
    public String[] getAuthors() { return authors; }
    
    /**
    * Prints the CatalogQuery in a human understandable summary.
    */
    public String toString() {
        String out = "";
        out += ("Query: {\n  Publishers: [");
        for(int i = 0; i < getPublisherIds().length; i++) {
            out += (Integer.toString(getPublisherIds()[i]));
            if(i < getPublisherIds().length-1) { out += ", "; }
        }
        out += ("];\n  Categories: [");
        for(int i = 0; i < getCategoryIds().length; i++) {
            out += (Integer.toString(getCategoryIds()[i]));
            if(i < getCategoryIds().length-1) { out += ", "; }
        }
        out += ("];\n  Authors:    [");
        for(int i = 0; i < getAuthors().length; i++) {
            out += ("'" + getAuthors()[i] + "'");
            if(i < getAuthors().length-1) { out += ", "; }
        }
        out += ("];\n}");
        return out;
    }
}
