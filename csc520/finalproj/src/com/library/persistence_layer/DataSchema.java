package com.library.persistence_layer;
import com.library.business_layer.field_list.*;
import com.library.persistence_layer.Table;
import java.io.Serializable;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.IOException;
import java.io.File;

/**
* The DataSchema creates and controls all tables for all business layer
* field list classes. Data is maintained on a persistent level meaning that
* it will continue to exists after the program has terminated. DataSchema
* extends the Table abstract class to create a unique Table for every class
* in the business layer field list. All other methods deal with serializing
* and deserializing Tables, creating and reading/writing to files.
* PERSISTENCE LAYER
* @see com.library.persistence_layer.Table
*/
public class DataSchema implements Serializable {
    private static final String dataDir = "data/";
    
    //All tables is the DataSchema
    public AddressTable                     addr = new AddressTable();
    public AuthorTable                      auth = new AuthorTable();
    public AuthorCatalogedBookDetailsTable  acbd = new AuthorCatalogedBookDetailsTable();
    public BookTable                        book = new BookTable();
    public BorrowedBookTable                borb = new BorrowedBookTable();
    public BorrowedBookMemberTable          bobm = new BorrowedBookMemberTable();
    public CatalogedBookTable               catb = new CatalogedBookTable();
    public CatalogedBookDetailsTable        cabd = new CatalogedBookDetailsTable();
    public CategoryTable                    cate = new CategoryTable();
    public CollectableReservationTable      coll = new CollectableReservationTable();
    public ConcludedReservationTable        conc = new ConcludedReservationTable();
    public CreditCardTable                  card = new CreditCardTable();
    public DisplayableReservationTable      disp = new DisplayableReservationTable();
    public InternetAccountTable             iacc = new InternetAccountTable();
    public MemberTable                      memb = new MemberTable();
    public NeedingRenewalReservationTable   rene = new NeedingRenewalReservationTable();
    public PublisherTable                   publ = new PublisherTable();
    public ReservationTable                 rese = new ReservationTable();
    public WaitingReservationTable          wait = new WaitingReservationTable();
    
    /**
    * Table that contains Address elements.
    * @see com.library.business_layer.field_list.Address
    */
    public static class AddressTable extends Table<Address> {
        public String getDefaultTable() { return "address.ser"; }
        public Class<?> getDefaultClass() { return getClassName("Address"); }
    }
    
    /**
    * Table that contains Author elements.
    * @see com.library.business_layer.field_list.Author
    */
    public static class AuthorTable extends Table<Author> {
        public String getDefaultTable() { return "author.ser"; }
        public Class<?> getDefaultClass() { return getClassName("Author"); }
    }
    
    /**
    * Table that contains AuthorCatalogedBookDetails elements.
    * @see com.library.business_layer.field_list.AuthorCatalogedBookDetails
    */
    public static class AuthorCatalogedBookDetailsTable extends Table<AuthorCatalogedBookDetails> { 
        public String getDefaultTable() { return "author_cataloged_book_details.ser"; }
        public Class<?> getDefaultClass() { return getClassName("AuthorCatalogedBookDetails"); }
    }
    
    /**
    * Table that contains Book elements.
    * @see com.library.business_layer.field_list.Book
    */
    public static class BookTable extends Table<Book> { 
        public String getDefaultTable() { return "book.ser"; }
        public Class<?> getDefaultClass() { return getClassName("Book"); }
    }
    
    /**
    * Table that contains BorrowedBook elements.
    * @see com.library.business_layer.field_list.BorrowedBook
    */
    public static class BorrowedBookTable extends Table<BorrowedBook> { 
        public String getDefaultTable() { return "borrowed_book.ser"; }
        public Class<?> getDefaultClass() { return getClassName("BorrowedBook"); }
    }
    
    /**
    * Table that contains BorrowedBookMember elements.
    * @see com.library.business_layer.field_list.BorrowedBookMember
    */
    public static class BorrowedBookMemberTable extends Table<BorrowedBookMember> { 
        public String getDefaultTable() { return "borrowed_book_member.ser"; }
        public Class<?> getDefaultClass() { return getClassName("BorrowedBookMember"); }
    }
    
    /**
    * Table that contains CatalogedBook elements.
    * @see com.library.business_layer.field_list.CatalogedBook
    */
    public static class CatalogedBookTable extends Table<CatalogedBook> { 
        public String getDefaultTable() { return "cataloged_book.ser"; }
        public Class<?> getDefaultClass() { return getClassName("CatalogedBook"); }
    }
    
    /**
    * Table that contains CatalogedBookDetails elements.
    * @see com.library.business_layer.field_list.CatalogedBookDetails
    */
    public static class CatalogedBookDetailsTable extends Table<CatalogedBookDetails> { 
        public String getDefaultTable() { return "cataloged_book_details.ser"; }
        public Class<?> getDefaultClass() { return getClassName("CatalogedBookDetails"); }
    }
    
    /**
    * Table that contains Category elements.
    * @see com.library.business_layer.field_list.Category
    */
    public static class CategoryTable extends Table<Category> { 
        public String getDefaultTable() { return "category.ser"; }
        public Class<?> getDefaultClass() { return getClassName("Category"); }
    } 
    
    /**
    * Table that contains Collectable elements.
    * @see com.library.business_layer.field_list.Collectable
    */
    public static class CollectableReservationTable extends Table<Collectable> { 
        public String getDefaultTable() { return "collectable_reservation.ser"; }
        public Class<?> getDefaultClass() { return getClassName("Collectable"); }
    }
    
    /**
    * Table that contains Concluded elements.
    * @see com.library.business_layer.field_list.Concluded
    */
    public static class ConcludedReservationTable extends Table<Concluded> { 
        public String getDefaultTable() { return "concluded_reservation.ser"; }
        public Class<?> getDefaultClass() { return getClassName("Concluded"); }
    } 
    
    /**
    * Table that contains CreditCard elements.
    * @see com.library.business_layer.field_list.CreditCard
    */
    public static class CreditCardTable extends Table<CreditCard> { 
        public String getDefaultTable() { return "credit_card.ser"; }
        public Class<?> getDefaultClass() { return getClassName("CreditCard"); }
    }
    
    /**
    * Table that contains Displayable elements.
    * @see com.library.business_layer.field_list.Displayable
    */
    public static class DisplayableReservationTable extends Table<Displayable> { 
        public String getDefaultTable() { return "displayable_reservation.ser"; }
        public Class<?> getDefaultClass() { return getClassName("Displayable"); }
    }
    
    /**
    * Table that contains InternetAccount elements.
    * @see com.library.business_layer.field_list.InternetAccount
    */
    public static class InternetAccountTable extends Table<InternetAccount> { 
        public String getDefaultTable() { return "internet_account.ser"; }
        public Class<?> getDefaultClass() { return getClassName("InternetAccount"); }
    }
    
    /**
    * Table that contains Member elements.
    * @see com.library.business_layer.field_list.Member
    */
    public static class MemberTable extends Table<Member> { 
        public String getDefaultTable() { return "member.ser"; }
        public Class<?> getDefaultClass() { return getClassName("Member"); }
    }
    
    /**
    * Table that contains NeedingRenewal elements.
    * @see com.library.business_layer.field_list.NeedingRenewal
    */
    public static class NeedingRenewalReservationTable extends Table<NeedingRenewal> { 
        public String getDefaultTable() { return "needing_renewal_reservation.ser"; }
        public Class<?> getDefaultClass() { return getClassName("NeedingRenewal"); }
    }
    
    /**
    * Table that contains Notifiable elements.
    * @see com.library.business_layer.field_list.Notifiable
    */
    public static class NotifiableReservationTable extends Table<Notifiable> { 
        public String getDefaultTable() { return "notifiable_reservation.ser"; }
        public Class<?> getDefaultClass() { return getClassName("Notifiable"); }
    }
    
    /**
    * Table that contains Publisher elements.
    * @see com.library.business_layer.field_list.Publisher
    */
    public static class PublisherTable extends Table<Publisher> { 
        public String getDefaultTable() { return "publisher.ser"; }
        public Class<?> getDefaultClass() { return getClassName("Publisher"); }
    }
    
    /**
    * Table that contains Reservation elements.
    * @see com.library.business_layer.field_list.Reservation
    */
    public static class ReservationTable extends Table<Reservation> { 
        public String getDefaultTable() { return "reservation.ser"; }
        public Class<?> getDefaultClass() { return getClassName("Reservation"); }
    }
    
    /**
    * Table that contains Waiting elements.
    * @see com.library.business_layer.field_list.Waiting
    */
    public static class WaitingReservationTable extends Table<Waiting> { 
        public String getDefaultTable() { return "waiting_reservation.ser"; }
        public Class<?> getDefaultClass() { return getClassName("Waiting"); }
    }
    
    /**
    * Creates a new Table and serializes it if it does not exist. Has package
    * level, static visibility so it can only be used for Table.
    * @param table Table with T elements
    * @param file String file to write to
    * @return true if table created, false if not
    */
    static <T> boolean createIfNotExists(T table, String file) {
        if(!fileExists(file)) {
            if(serializeTable(table, file)) { return true; }
        }
        return false;
    }
    
    /**
    * Retrieves a Table from an existing file by deserializing it. Has package
    * level, static visibility so it can only be used for Table.
    * @param table Table with T elements
    * @param file String file to read from
    * @return true if table was read from, false if not
    */
    static <T> T retrieve(T table, String file) {
        T tmpTable = deserializeTable(table, file);
        if(tmpTable != null) { return tmpTable; }
        else { return table; }
    }
    
    /**
    * Updates a Table by deleting the old one and serializing a new one. Has 
    * package level, static visibility so it can only be used for Table.
    * @param table Table with T elements
    * @param file String file update
    * @return true if table updated, false if not
    */
    static <T> boolean update(T table, String file) {
        if(fileExists(file)) {
            File doomed = new File(dataDir + file);
            doomed.delete();
            if(serializeTable(table, file)) { return true; }
        }
        return false;
    }
    
    /**
    * Serializes a Table to the given file name. Has package level, static 
    * visibility so it can only be used for Table. Assumes file does not exist.
    * @param table Table with T elements
    * @param file String file to serialize to
    * @return true if table was serialized, false if not
    */
    static <T> boolean serializeTable(T table, String file) {
        try {
            FileOutputStream fileOut = new FileOutputStream(dataDir + file);
            ObjectOutputStream out = new ObjectOutputStream(fileOut);
            out.writeObject(table);
            out.close();
            fileOut.close();
            return true;
        }
        catch(IOException ex) { ex.printStackTrace(); }
        return false; 
    }
    
    /**
    * Deserializes a file to the given Table. Has package level, static 
    * visibility so it can only be used for Table.
    * @param table Table with T elements
    * @param file String file to deserialize from
    * @return the new deserialized table if successful, or old table if failure
    */
    static <T> T deserializeTable(T table, String file) {
        if(fileExists(file)) {
            try {
                FileInputStream fileIn = new FileInputStream(dataDir + file);
                ObjectInputStream in = new ObjectInputStream(fileIn);
                T tmpTable = (T) in.readObject();
                in.close();
                fileIn.close();
                return tmpTable;
            }
            catch(IOException ex) { ex.printStackTrace(); }
            catch(ClassNotFoundException ex) { ex.printStackTrace(); }
        }
        return table;
    }
    
    /**
    * Checks if the given file exists.
    * @param file String
    * @return true if file exists, false if not
    */
    static boolean fileExists(String file) {
        File tmp = new File(dataDir + file);
        if(tmp.exists()) { return true; }
        else { return false; }
    }
    
    /**
    * Gets the full class name of the given class name.
    * @param someClass String base name of the class
    * @return String containing the full class name
    */
    static Class<?> getClassName(String someClass) {
        String classPath = "com.library.business_layer.field_list.";
        Class<?> classToReturn = null;
        try { classToReturn = Class.forName(classPath + someClass); }
        catch(ClassNotFoundException ex) { ex.printStackTrace(); }
        return classToReturn;
    }
}
