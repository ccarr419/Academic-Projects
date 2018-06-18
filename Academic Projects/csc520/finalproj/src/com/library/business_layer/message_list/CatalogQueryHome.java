package com.library.business_layer.message_list;
import com.library.business_layer.field_list.CatalogQuery;
import java.util.ArrayList;

/**
* CatalogQueryHome serves as a way to create queries to search for. The home
* also serves as a history for all past quries created.
* BUSINESS LAYER CLASS
* @see com.library.business_layer.field_list.CatalogQuery
*/
public class CatalogQueryHome {
    private ArrayList<CatalogQuery> cqHistory;
    
    /**
    * Basic constructor for CatalogQueryHome that initializes history list.
    */
    public CatalogQueryHome() {
        cqHistory = new ArrayList<CatalogQuery>();
    }
    
    /**
    * Gets the CatalogQuery list as a whole.
    * @return ArrayList&lt;CatalogQuery&gt; history
    */
    public ArrayList<CatalogQuery> getQueryHistory() {
        return cqHistory;
    }
    
    /**
    * Creates a new CatalogQuery and appends it to history.
    * @param p int[] publishers
    * @param c int[] categories
    * @param a String[] authors
    * @return the newly created CatalogQuery
    */
    public CatalogQuery create(int p[], int c[], String a[]) {
        CatalogQuery q = new CatalogQuery(p, c, a);
        cqHistory.add(q);
        return q;
    }
}
