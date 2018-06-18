package com.library.client;
import com.library.server_ui.*;
import com.library.test.LibraryTestData;
import java.util.Scanner;

/**
* A client to test the integration of the library system. Behaves as a mixture
* between a web page and command-line program.
*/
public class LibraryClient {
    public static int sessionId;
    public static Scanner reader = new Scanner(System.in);
    public static AuthenticationServerUI asUI = new AuthenticationServerUI();
    public static BorrowedBookServerUI bbsUI = new BorrowedBookServerUI();
    public static ReservationServerUI resUI = new ReservationServerUI();
    public static MembershipServerUI memUI = new MembershipServerUI();
    public static CatalogServerUI csUI  = new CatalogServerUI();

    /**
    * Starts the client and places the user on the home page.
    * @param args String[] command-line arguments
    */
    public static void main(String[] args) {
        LibraryTestData.create();
        welcomeMessage();
        homePage();
    }
    
    /**
    * Prints the welcome message that displays author information.
    */
    private static void welcomeMessage() {
        System.out.println("");
        System.out.println("==============================");
        System.out.println("*  LIBRARY  CATALOG  SYSTEM  *");
        System.out.println("*  ------------------------  *");
        System.out.println("*         Version 1.0        *");
        System.out.println("*    Christian B. Carreras   *");
        System.out.println("*     Kutztown University    *");
        System.out.println("==============================");
        System.out.println("");
    }
    
    /**
    * Home page serves as a portal for members to log on, non members to browse
    * and to terminate the program.
    */
    private static void homePage() {
        System.out.println("");
        System.out.println("===============");
        System.out.println("*  HOME PAGE  *");
        System.out.println("===============");
        System.out.println("You are not logged on. Type 'logon' to log on");
        System.out.println("or 'nonmem' to continue as a non-member. Type");
        System.out.println("'help' for a list of commands\n");
        
        String input = "";
        while(true) {
            System.out.print(">");
            input = reader.nextLine();
            switch(input.toLowerCase()) {
                case("help"):
                    helpPage();
                    break;
                case("logon"):
                    sessionId = asUI.logon(reader);
                    if(sessionId > 0) { memberPage(); }
                    break;
                case("refrsh"):
                    homePage();
                    break;
                case("nonmem"):
                    nonmemberPage();
                    break;
                case("quit"):
                    System.out.println("Goodbye\n");
                    reader.close();
                    System.exit(0);
                default:
                    if(!input.isEmpty()) {
                        System.out.println(
                            "Error: '" + input + "' is not a command for this page");
                    }
            }
        }
    }
    
    /**
    * Member page serves as a portal to all member and non-member services
    */
    private static void memberPage() {
        if(sessionId <= 0) { nonmemberPage(); }
        System.out.println("");
        System.out.println("===============");
        System.out.println("* MEMBER PAGE *");
        System.out.println("===============");
        System.out.println("Welcome!\n");
        
        String input = "";
        while(true) {
            System.out.print(">");
            input = reader.nextLine();
            switch(input.toLowerCase()) {
                case("help"):
                    helpPage();
                    break;
                case("logoff"):
                    asUI.logoff(sessionId);
                    sessionId = -1;
                    homePage();
                    break;
                case("refrsh"):
                    memberPage();
                    break;
                case("index"):
                    indexPage();
                    break;
                case("search"):
                    searchPage();
                    break;
                case("acc"):
                    membershipPage();
                    break;
                case("pass"):
                    passwordPage();
                    break;
                case("chpass"):
                    changePasswordPage();
                    break;
                case("bbook"):
                    borrowedBookPage();
                    break;
                case("res"):
                    reservationsPage();
                    break;
                default:
                    if(!input.isEmpty()) {
                        System.out.println(
                            "Error: '" + input + "' is not a command for this page");
                    }
            }
        }
    }
    
    /**
    * Non-member page serves as a portal to all non-member services
    */
    private static void nonmemberPage() {
        if(sessionId > 0) { memberPage(); }
        System.out.println("");
        System.out.println("===================");
        System.out.println("* NON-MEMBER PAGE *");
        System.out.println("===================");
        System.out.println("Welcome!\n");
        
        String input = "";
        while(true) {
            System.out.print(">");
            input = reader.nextLine();
            switch(input.toLowerCase()) {
                case("help"):
                    helpPage();
                    break;
                case("back"):
                    homePage();
                    break;
                case("refrsh"):
                    nonmemberPage();
                    break;
                case("index"):
                    indexPage();
                    break;
                case("search"):
                    searchPage();
                    break;
                default:
                    if(!input.isEmpty()) {
                        System.out.println(
                            "Error: '" + input + "' is not a command for this page");
                    }
            }
        }
    }
    
    /**
    * Index page serves as a way for members or non-members to browse cataloged
    * books by index heading.
    */
    private static void indexPage() {
        System.out.println("");
        System.out.println("==============");
        System.out.println("* INDEX PAGE *");
        System.out.println("==============");
        csUI.index();
        String input = "";
        while(true) {
            System.out.print(">");
            input = reader.nextLine();
            switch(input.toLowerCase()) {
                case("help"):
                    helpPage();
                    break;
                case("back"):
                    memberPage();
                    break;
                case("refrsh"):
                    indexPage();
                    break;
                case("browse"):
                    resultsPage(false);
                    indexPage();
                    break;
                default:
                    if(!input.isEmpty()) {
                        System.out.println(
                            "Error: '" + input + "' is not a command for this page");
                    }
            }
        }
    }
    
    /**
    * Search page serves as a way for members or non-members to search
    * cataloged books by query
    */
    private static void searchPage() {
        System.out.println("");
        System.out.println("===============");
        System.out.println("* SEARCH PAGE *");
        System.out.println("===============");
        csUI.search();
        String input = "";
        while(true) {
            System.out.print(">");
            input = reader.nextLine();
            switch(input.toLowerCase()) {
                case("help"):
                    helpPage();
                    break;
                case("back"):
                    memberPage();
                    break;
                case("refrsh"):
                    searchPage();
                    break;
                case("query"):
                    resultsPage(true);
                    searchPage();
                    break;
                default:
                    if(!input.isEmpty()) {
                        System.out.println(
                            "Error: '" + input + "' is not a command for this page");
                    }
            }
        }
    }
    
    /**
    * Results page shows the results of a index heading browsing or search query.
    * @param s boolean whether the results are from a search or not
    */
    private static void resultsPage(boolean s) {
        String browseResult = "";
        String[] authors = new String[0];
        int[] pubIds = new int[0];
        int[] catIds = new int[0];
        if(s) {
            System.out.print("  categories: ");
            String cat = reader.nextLine();
            System.out.print("  publishers: ");
            String pub = reader.nextLine();
            System.out.print("  authors: ");
            String auth = reader.nextLine();
            String[] pubs = pub.split("\\s+");
            String[] cats = cat.split("\\s+");
            authors = auth.split("\\s+");
            pubIds = new int[pubs.length];
            catIds = new int[cats.length];
            for(int i = 0; i < pubs.length; i++) {
                try {
                    pubIds[i] = Integer.parseInt(pubs[i]);
                }
                catch(NumberFormatException ex) { continue; }
            }
            for(int i = 0; i < cats.length; i++) {
                try {
                    catIds[i] = Integer.parseInt(cats[i]);
                }
                catch(NumberFormatException ex) { continue; }
            }
            System.out.println("");
            System.out.println("===============");
            System.out.println("* RESULT PAGE *");
            System.out.println("===============");
            csUI.query(pubIds, catIds, authors);
        }
        else {
            System.out.print("  index: ");
            browseResult = reader.nextLine();
            System.out.println("");
            System.out.println("===============");
            System.out.println("* RESULT PAGE *");
            System.out.println("===============");
            csUI.browse(browseResult);
        }
        String input = "";
        while(true) {
            System.out.print(">");
            input = reader.nextLine();
            switch(input.toLowerCase()) {
                case("help"):
                    helpPage();
                    break;
                case("back"):
                    return;
                case("refrsh"):
                    System.out.println("");
                    System.out.println("===============");
                    System.out.println("* RESULT PAGE *");
                    System.out.println("===============");
                    if(s) { csUI.query(pubIds, catIds, authors); }
                    else { csUI.browse(browseResult); }
                    break;
                case("detail"):
                    System.out.print("  book id: ");
                    input = reader.nextLine();
                    try {
                        detailsPage(Integer.parseInt(input));
                    }
                    catch(NumberFormatException ex) { 
                        System.out.println("Invalid Book ID"); 
                    }
                    System.out.println("");
                    System.out.println("===============");
                    System.out.println("* RESULT PAGE *");
                    System.out.println("===============");
                    if(s) { csUI.query(pubIds, catIds, authors); }
                    else { csUI.browse(browseResult); }
                    break;
                default:
                    if(!input.isEmpty()) {
                        System.out.println(
                            "Error: '" + input + "' is not a command for this page");
                    }
            }
        }
        
    }
    
    /**
    * Details page shows details of a book selected
    * @param i int cataloged book id
    */
    private static void detailsPage(int i) {
        System.out.println("");
        System.out.println("================");
        System.out.println("* DETAILS PAGE *");
        System.out.println("================");
        csUI.details(i);
        String input = "";
        while(true) {
            System.out.print(">");
            input = reader.nextLine();
            switch(input.toLowerCase()) {
                case("help"):
                    helpPage();
                    break;
                case("back"):
                    return;
                case("refrsh"):
                    detailsPage(i);
                case("res"):
                    resUI.reserve(sessionId, i, reader);
                    break;
                default:
                    if(!input.isEmpty()) {
                        System.out.println(
                            "Error: '" + input + "' is not a command for this page");
                    }
            }
        }
    }
    
    /**
    * Membership page shows all account details for the member.
    */
    private static void membershipPage() {
        System.out.println("");
        System.out.println("================");
        System.out.println("* ACCOUNT PAGE *");
        System.out.println("================");
        memUI.member(sessionId);
        String input = "";
        while(true) {
            System.out.print(">");
            input = reader.nextLine();
            switch(input.toLowerCase()) {
                case("help"):
                    helpPage();
                    break;
                case("back"):
                    memberPage();
                    break;
                case("refrsh"):
                    membershipPage();
                    break;
                default:
                    if(!input.isEmpty()) {
                        System.out.println(
                            "Error: '" + input + "' is not a command for this page");
                    }
            }
        }
    }
    
    /**
    * Password page shows all password information for the memeber.
    */
    private static void passwordPage() {
        System.out.println("");
        System.out.println("=================");
        System.out.println("* PASSWORD PAGE *");
        System.out.println("=================");
        memUI.password(sessionId);
        String input = "";
        while(true) {
            System.out.print(">");
            input = reader.nextLine();
            switch(input.toLowerCase()) {
                case("help"):
                    helpPage();
                    break;
                case("back"):
                    memberPage();
                    break;
                case("refrsh"):
                    passwordPage();
                    break;
                default:
                    if(!input.isEmpty()) {
                        System.out.println(
                            "Error: '" + input + "' is not a command for this page");
                    }
            }
        }
    }
    
    /**
    * ChangePassword page allows a member to change their password.
    */
    private static void changePasswordPage() {
        System.out.println("");
        System.out.println("===================");
        System.out.println("* CHANGE PASSWORD *");
        System.out.println("===================");
        memUI.changePassword(sessionId, reader);
        memberPage();
    }
    
    /**
    * BorrowedBook page shows all borrowed books a member has.
    */
    private static void borrowedBookPage() {
        System.out.println("");
        System.out.println("==================");
        System.out.println("* BORROWED BOOKS *");
        System.out.println("==================");
        bbsUI.borrowedBooks(sessionId);
        String input = "";
        while(true) {
            System.out.print(">");
            input = reader.nextLine();
            switch(input.toLowerCase()) {
                case("help"):
                    helpPage();
                    break;
                case("back"):
                    memberPage();
                    break;
                case("refrsh"):
                    borrowedBookPage();
                    break;
                default:
                    if(!input.isEmpty()) {
                        System.out.println(
                            "Error: '" + input + "' is not a command for this page");
                    }
            }
        }
    }

    /**
    * Reservations page shows all reservation books the member has made and
    * allows them to cancel a reservation.
    */
    private static void reservationsPage() {
        System.out.println("");
        System.out.println("==================");
        System.out.println("* RESERVED BOOKS *");
        System.out.println("==================");
        resUI.reservations(sessionId);
        String input = "";
        while(true) {
            System.out.print(">");
            input = reader.nextLine();
            switch(input.toLowerCase()) {
                case("help"):
                    helpPage();
                    break;
                case("back"):
                    memberPage();
                    break;
                case("cancel"): 
                    System.out.print("  reservation id: ");
                    input = reader.nextLine();
                    try {
                        resUI.cancel(sessionId, Integer.parseInt(input), reader);
                    }
                    catch(NumberFormatException ex) { 
                        System.out.println("Invalid Reservation ID"); 
                    }
                    reservationsPage();
                    break;
                case("refrsh"):
                    reservationsPage();
                    break;
                default:
                    if(!input.isEmpty()) {
                        System.out.println(
                            "Error: '" + input + "' is not a command for this page");
                    }
            }
        }
    }
    
    /**
    * Help page shows all commands and on which pages they can be used.
    */
    private static void helpPage() {
        System.out.println("");
        System.out.println("This is a list of commands per page ");
        System.out.println("in the library catalog system.");
        System.out.println("");
        System.out.println("HOME PAGE");
        System.out.println("  help:   view list of commands");
        System.out.println("  logon:  log on to system as member");
        System.out.println("  nonmem: continue as non-member");
        System.out.println("  refrsh: refresh page");
        System.out.println("  quit:   terminate client");
        System.out.println("");
        System.out.println("MEMBER PAGE");
        System.out.println("  help:   view list of commands");
        System.out.println("  logoff: log off of current account");
        System.out.println("  index:  go to index page");
        System.out.println("  search: go to search page");
        System.out.println("  acc:    view account info");
        System.out.println("  pass:   view password info");
        System.out.println("  chpass: change password");
        System.out.println("  bbook:  view borrowed books");
        System.out.println("  res:    view reservations");
        System.out.println("  refrsh: refresh page");
        System.out.println("");
        System.out.println("NON-MEMBER PAGE");
        System.out.println("  help:   view list of commands");
        System.out.println("  back:   return to home page");
        System.out.println("  index:  go to index page");
        System.out.println("  search: go to search page");
        System.out.println("  refrsh: refresh page");
        System.out.println("");
        System.out.println("INDEX PAGE");
        System.out.println("  help:   view list of commands");
        System.out.println("  back:   return to member/non-member page");
        System.out.println("  browse: browse books by index");
        System.out.println("  refrsh: refresh page");
        System.out.println("");
        System.out.println("SEARCH PAGE");
        System.out.println("  help:   view list of commands");
        System.out.println("  back:   return to member/non-member page");
        System.out.println("  query:  search for publisher, category and author");
        System.out.println("          using ids for publishers and categories");
        System.out.println("          and names for authors. Mulitples of each");
        System.out.println("          can be put in query if separated by space");
        System.out.println("  refrsh: refresh page");
        System.out.println("");
        System.out.println("RESULTS PAGE");
        System.out.println("  help:   view list of commands");
        System.out.println("  back:   return to member/non-member page");
        System.out.println("  detail: show details for book id found in ()");
        System.out.println("  refrsh: refresh page");
        System.out.println("");
        System.out.println("DETAILS PAGE");
        System.out.println("  help:   view list of commands");
        System.out.println("  back:   return to index/search page");
        System.out.println("  res:    reserve book");
        System.out.println("  refrsh: refresh page");
        System.out.println("");
        System.out.println("ACCOUNT PAGE");
        System.out.println("  help:   view list of commands");
        System.out.println("  back:   return to member page");
        System.out.println("  refrsh: refresh page");
        System.out.println("");
        System.out.println("PASSWORD PAGE");
        System.out.println("  help:   view list of commands");
        System.out.println("  back:   return to member page");
        System.out.println("  refrsh: refresh page");
        System.out.println("");
        System.out.println("BORROWED BOOK PAGE");
        System.out.println("  help:   view list of commands");
        System.out.println("  back:   return to member page");
        System.out.println("  refrsh: refresh page");
        System.out.println("");
        System.out.println("RESERVATION PAGE");
        System.out.println("  help:   view list of commands");
        System.out.println("  back:   return to member page");
        System.out.println("  cancel: cancel a reservation");
        System.out.println("  refrsh: refresh page");
        System.out.println("");
    }
}
