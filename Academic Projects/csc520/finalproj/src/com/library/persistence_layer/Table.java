package com.library.persistence_layer;
import com.library.persistence_layer.DataSchema;
import java.util.ArrayList;
import java.io.Serializable;
import java.lang.reflect.Method;
import java.lang.reflect.InvocationTargetException;

/**
* Table is an abstract that method that was modeled to behave similarly to
* a mixture between a database, ArrayList and reading/writing to file. Tables
* are serialized so the data inserted can persist across program use. Methods
* mostly consist of inspectors and facilitors because adding elements and 
* reading what the table contained were the most important features. Names
* of functions allude to similarities to a database. Ultimately a Table comes
* down to a Object that behaves like a database but can be accessed like an
* ArrayList with some extra, special and custom tools. Since this class
* is abstract it can not me used in its current form. Inheriting classes must
* make simple modifications to get a Table up and running.
* PERSISTENCE LAYER
* @see com.library.persistence_layer.DataSchema
*/
public abstract class Table<T> implements Serializable {
    private int key; //Keep record of last key in case elements are removed
    private ArrayList<T> list; //Holds all the data elements
    private final String DEFAULT_TABLE = ""; //The name of the data file
    private Class<?> DEFAULT_CLASS = null; //The class being held in the table
    
    /**
    * Contructor that creates a new table if it does not exist. If the table
    * already exists, simply retrieve the data from that table.
    */
    public Table() {
        key = 1;
        list = new ArrayList<>();
        if(!DataSchema.createIfNotExists(selectAll(), getDefaultTable())) {
            updateList();
        }
    }
    
    /**
    * Get the element in the Table at index.
    * @param i int index
    * @return element T at index i or null if i is out-of-range
    */
    public T get(int i) {
        while(i < 0 && size() != 0) { i += size(); }
        if(i >= 0 && i < size()) { return selectAll().get(i); }
        else { return null; }
    }
    
    /**
    * Get the Table default data file. Must be overriden by subclass.
    * @return the default data file to write/read to
    */
    public String getDefaultTable() { return DEFAULT_TABLE; }
    
    /**
    * Get the Table default class. Must be overriden by subclass.
    * @return the default class of the elements within the Table
    */
    public Class<?> getDefaultClass() { return DEFAULT_CLASS; }
    
    /**
    * Takes an element T and places it at the end of the Table if it is a
    * unique entry. If the Table contains the element already, it is discarded.
    * @param entry T element to append to the end of the Table
    * @return true if the element was successfully appended, false if not
    */
    public boolean append(T entry) {
        updateList();
        if(!selectAll().isEmpty()) {
            if(selectAll().contains(entry)) {
                return false;
            }
        }
        list.add(entry);
        DataSchema.update(selectAll(), getDefaultTable()); 
        key++;
        return true;
    }
    
    /**
    * Get the first element in the Table
    * @return first T element
    */
    public T first() {
        if(!selectAll().isEmpty()) { return get(0); }
        else { return null; }
    }
    
    /**
    * Get the last element in the Table
    * @return last T element
    */
    public T last() {
        if(!selectAll().isEmpty()) { return get(-1); }
        else { return null; }
    }
    
    /**
    * Get the whole list of elements
    * @return ArrayList of T elements
    */
    public ArrayList<T> selectAll() { return list; }
    
    /**
    * Return the element that matches the unique identifier.
    * @param i int element id
    * @return element T that matches id
    */
    public T selectId(int i) {
        ArrayList<T> entry = selectWhere("id", i);
        if(!entry.isEmpty()) { return entry.get(0); }
        else { return null; }
    }
    
    /**
    * Finds a sublist where each element specified attribute matches a given 
    * value. Method can be called for any element attribute as long as it has
    * a corresponding getter method to access the value.
    * @param attribute String attribute to match to value
    * @param value K value to search for
    * @return ArrayList of T elements that have value for attribute
    */
    public <K> ArrayList<T> selectWhere(String attribute, K value) {
        ArrayList<T> subset = new ArrayList<T>();
        Method theMethod = findMethod(attribute, false);
        if(theMethod != null) { //Get the getter method for this attribute
            for(T item : selectAll()) {
                try { 
                    //Get all elements and compare its attribute to the value
                    //by invoking its getter methods
                    K tmp = (K) theMethod.invoke(item);
                    if(tmp.equals(value)) {
                        subset.add(item); //Add element if attribute matches
                    }
                }
                catch(InvocationTargetException ex) { ex.printStackTrace(); }
                catch(IllegalAccessException ex) { ex.printStackTrace(); }
            }
        }
        return subset;
    }
    
    /**
    * Finds the elment with the unique identifier and changes it attribute to
    * to a new value. Method can be called for any element attribute as long 
    * as it has a corresponding setter method to access the value. Does nothing
    * on failure of any kind minus exceptions.
    * @param id int element id
    * @param attribute String attribute to change to value
    * @param value K value to change to
    */
    public <K> void setForId(int id, String attribute, K value) {
        Method theMethod = findMethod(attribute, true);
        if(theMethod != null) { //Get the setter method for this attribute
            T item = selectId(id);
            if(item != null) {
                for(int i = 0; i < size(); i++) {
                    if(get(i).equals(item)) { //Get element from list
                        try { theMethod.invoke(list.get(i), value); }
                        catch(InvocationTargetException ex) { ex.printStackTrace(); }
                        catch(IllegalAccessException ex) { ex.printStackTrace(); }
                        DataSchema.update(selectAll(), getDefaultTable()); 
                        return;
                    }
                }
            }
        }
    }
    
    /**
    * Sets the element with the unique identifier to entirely new element of
    * the same type. Only modifies if an elment with that id exists in the Table.
    * @param id int element id
    */
    public void setForId(int id, T value) {
        T item = selectId(id);
        if(item != null) {
            for(int i = 0; i < size(); i++) {
                if(get(i).equals(item)) {
                    set(i, value);
                    return;
                }
            }
        }
    }
    
    /**
    * Sets the element at index to entirely new element of the same type.
    * Assumes the idex is not out-of-range.
    * @param i int index
    * @param value T new element value
    */
    public void set(int i, T value) { 
        list.set(i, value);
        DataSchema.update(selectAll(), getDefaultTable()); 
    }
    
    /**
    * Finds the getter or setter method for the given attribute.
    * @param attribute String attribute to find accessor method for
    * @param set_flag boolean true to serach for setter, false for getter
    * @param Method Object pointing to a getter/setter, null if method does not exist
    */
    private Method findMethod(String attribute, boolean set_flag) {
        String att = attribute.toLowerCase(); //Get all methods for this class
        for(Method method: getDefaultClass().getMethods()) {
            String mStr = method.toString().toLowerCase();
            if(set_flag) { //Find in setters that contain attribute name
                if(mStr.contains("set") && mStr.contains(att)) {
                    return method;
                }
            }
            else { //Find in getters that contain attribute name
                if(mStr.contains("get") && mStr.contains(att)) {
                    return method;
                }
            }
        }
        return null; //Method was not found
    }
    
    /**
    * Removes the element with the unique identifier from the Table.
    * @param id int element id
    * @return true if element was removed, false if not
    */
    public boolean deleteId(int id) {
        T item = selectId(id);
        if(item != null) {
            list.remove(item);
            DataSchema.update(selectAll(), getDefaultTable()); 
            return true;
        }
        return false;
    }
    
    /**
    * Gets the number of elements in the Table.
    * @return Table size
    */
    public int size() { return selectAll().size(); }
    
    /**
    * Gets the next available primary key to be used when an element is
    * inserted into the Table.
    * @return key as int
    */
    public int nextKey() { return key; }
    
    /**
    * Checks if the Table is empty or not.
    * @return true if the Table is empty, false if not
    */
    public boolean isEmpty() { return selectAll().isEmpty(); }
    
    /**
    * Forces the Table to update the list by retrieving the serialized Table.
    */
    public void updateList() {
        list = DataSchema.retrieve(selectAll(), getDefaultTable());
        key = size()+1;
    }
}
