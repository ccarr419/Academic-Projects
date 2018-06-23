package com.library.test;
import com.library.business_layer.message_list.*;
import java.util.Date;

/**
* Creates and inserts test data to be used in a client. Will only create if
* the data Tables are empty as to not duplicate entries.
*/
public class LibraryTestData {
    private static MemberHome mh = new MemberHome();
    private static CategoryHome cath = new CategoryHome();
    private static PublisherHome pubh = new PublisherHome();
    private static ReservationHome resh = new ReservationHome();
    private static BorrowedBookHome bbh = new BorrowedBookHome();
    private static CatalogedBookHome cbh = new CatalogedBookHome();
    private static ReservationStateHome rsth = new ReservationStateHome();
    private static CatalogedBookDetailsHome cbdh = new CatalogedBookDetailsHome();
    
    public static void create() {
        if(!testDataExists()) { //If all tables are empty, create and add data
            //Create Member
            mh.create("John Doe", "555-555-5555", 0, true, "1234", 1, 1, 1);
            mh.create("Visa", "0000-0000-0000-0001", new Date());
            mh.create("111", "Kutztown Ln.", "Berks", "18091");
            mh.create("pass", -1);
            //Borrowed Books for Member
            bbh.create("0001", new Date(), new Date(2018 - 1900, 5, 11), 1);
            bbh.create("0002", new Date(), new Date(2018 - 1900, 5, 13), 1);
            bbh.create("0003", new Date(), new Date(2018 - 1900, 5, 21), 1);
            bbh.create("0004", new Date(), new Date(2018 - 1900, 5, 30), 1);
            //CatalogedBooks
            cbh.create("12as20aef09", "Apples & Oranges", 8, 1, 1);
            cbh.create("12as20aef08", "Another Slice of Pie", 4, 2, 1);
            cbh.create("12as20aef07", "Bob the Cook", 4, 3, 2);
            cbh.create("12as20aef06", "The Dog in the Hat", 8, 4, 3);
            cbh.create("12as20aef05", "Something Wild This Way Comes", 9, 5, 4);
            cbh.create("12as20aef04", "123 ABC", 8, 6, 1);
            cbh.create("12as20aef03", "Alligator Bop!", 12, 7, 5);
            cbh.create("12as20aef02", "X-Rays and You. Invisible Helpers!", 3, 8, 3);
            cbh.create("12as20aef01", "Cuddly Kittens", 8, 9, 6);
            cbh.create("12as20aef00", "Me, Myself and I", 1, 10, 2);
            cbh.create("12as20aee99", "So How Far Away Is The Moon?", 2, 11, 3);
            //CatalogedBooksDetails
            cbdh.create("1", new String[] {"Carreras"}, "Learn the difference between many things in life!");
            cbdh.create("2", new String[] {"Pesto"}, "What makes a perfect pizza? Insider secrets they do not want you to know!");
            cbdh.create("1", new String[] {"Richardson", "Belcher"}, "Cook the Bob way! It goes great with fries!");
            cbdh.create("3", new String[] {"Carreras"}, "What is better than a cat in a hat? Nothing, but a dog in a hat comes close.");
            cbdh.create("1", new String[] {"Sanchez"}, "Can this brother and sister duo escape the horrors left by their grandfather?");
            cbdh.create("1", new String[] {"Smith", "Anderson"}, "A book for a perfectly normal human toddler.");
            cbdh.create("2", new String[] {"Baggins"}, "How I came to grips with my insecurity at the slopes of Mt. Doom.");
            cbdh.create("2", new String[] {"Baggins"}, "Absolutely harmless gamma radiation all for the taking!");
            cbdh.create("4", new String[] {"Catlady"}, "How many cats are enough? The answer will surprise you.");
            cbdh.create("1", new String[] {"Hawking", "Descartes", "Strange"}, "Who am I? Do I think therefore I am?");
            cbdh.create("3", new String[] {"Skywalker"}, "Is that a moon? That does not seem like a moon.");
            //Categories
            cath.create("Fiction");
            cath.create("Non-Fiction");
            cath.create("Educational");
            cath.create("Cooking");
            cath.create("Sports");
            cath.create("History");
            cath.create("Sci-Fi");
            cath.create("Kids");
            cath.create("Horror");
            cath.create("Romance");
            cath.create("Classic");
            cath.create("Biography");
            //Publishers
            pubh.create("Stoneyfarm Publ.");
            pubh.create("C&C Inc.");
            pubh.create("KU Printing");
            pubh.create("Allman Sisters");
            pubh.create("Sunrise Valley");
            pubh.create("SuperDuper Co.");
        }
    }
    
    /**
    * Checks to see if all tables are empty.
    * @return true if all tables are empty, false if not
    */
    private static boolean testDataExists() {
        int size =
            bbh.getBorrowedBooks().size()         
            + bbh.getBorrowedBookMembers().size()
            + cbh.getCatalogedBooks().size()    
            + cbdh.getCatalogedBookDetails().size()
            + cath.getCategories().size()
            + mh.getMembers().size()
            + mh.getInternetAccounts().size()
            + mh.getCreditCards().size()
            + mh.getAddresses().size()
            + pubh.getPublishers().size()
            + resh.getReservations().size()
            + rsth.getCollectables().size()
            + rsth.getConcluded().size()
            + rsth.getDisplayables().size()
            + rsth.getNeedingRenewals().size()
            + rsth.getNotifiables().size()
            + rsth.getWaiting().size();
        
        if(size <= 0) { return false; }
        else { return true; }
    }
}
