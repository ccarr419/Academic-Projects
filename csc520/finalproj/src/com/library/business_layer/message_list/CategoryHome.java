package com.library.business_layer.message_list;
import com.library.business_layer.field_list.Category;
import com.library.persistence_layer.*;
import java.util.Collections;
import java.util.ArrayList;

/**
* CategoryHome serves as a way to access the CategoryTable. Thus it also 
* serves as an accessor to the table's element's attributes. Another purpose of
* CategoryHome is to create and add any new entries to the CategoryTable.
* BUSINESS LAYER CLASS
* @see com.library.business_layer.field_list.Category
*/
public class CategoryHome {
    private Table catTable;
    
    /**
    * Basic constructor for CategoryHome that instantiates home's Tables.
    */
    public CategoryHome() { 
        catTable = new DataSchema.CategoryTable();
    }
    
    /**
    * Gets the CategoryTable as a whole.
    * @return DataSchema.CategoryTable
    */
    public DataSchema.CategoryTable getCategories() { 
        return (DataSchema.CategoryTable) catTable;
    }

    /**
    * Finds a Category by its primary key identifier.
    * @param id int
    * @return Category
    */
    public Category findByPrimaryKey(int id) {
        return (Category) catTable.selectId(id);
    }
    
    /**
    * Creates a new Category and appends it to the CategoryTable.
    * @param name String category name
    * @return the newly created Category
    */
    public Category create(String name) { 
        Category newCategory = new Category(catTable.nextKey(), name);
        catTable.append(newCategory);
        return newCategory;
    }
    
    /**
    * Gets the all the Categories in CategoryTable sorted by name.
    * @return sorted ArrayList&lt;Category&gt;
    */
    public ArrayList<Category> findCategoryNames() {
        ArrayList<Category> c = catTable.selectAll();
        Collections.sort(c);
        return c;
    }
    
    /**
    * Force the update of all CategoryHome Tables.
    */
    public void update() {
        catTable.updateList();
    }
}