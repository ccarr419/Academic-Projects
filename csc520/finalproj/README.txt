Author Name:    Christian Carreras
Course Name:    Advanced OO Programming
Course Number:  CSC 520
Semester:       Spring 2018
Professor:      Dr. Schwesinger
College:        Kutztown University
Due Date:       05/07/2018

HOW TO RUN:
    (1) To build project type 'ant'
    (2) To run project type 'java -jar dist/com.library.client.jar'
    
HOW TO USE:
    (1) When ran the program will start on the home page
    (2) From here you may enter the following:
        (2.a) 'help' for a list of commands,
        (2.b) 'logon' to log in with an account
            *NOTE*
                Special made account for testing has these credentials:
                User Number: 1234
                Password: pass
            *ENDNOTE*
        (2.c) 'nonmem' continue with non-member functionality
        (2.d) 'quit' to terminate the program
    (3) Members and Non-Members have access to the following:
        (3.a) 'index' displays book indexes in the catalog
                the user may type 'browse' to look up an index
                from there the user may type 'detail' to view details
        (3.b) 'search' shows all categories, publishers, and authors
                the user may type 'query' to query seach the catalog
                from there the user may type 'detail' to view details
    (4) Only Members have access to the following:
        (4.a) 'acc' account information page
        (4.b) 'res' reservations page/create reservation
        (4.c) 'bbook' borrowed book page
        (4.d) 'pass' password page
        (4.e) 'chpass' change user password
        (4.f) 'logoff' log off the user
        (4.g) 'cancel' cancel reservation
    (5) These commands are available on every page*
        (5.a) 'refrsh' refresh the page
        (5.b) 'back' go to the previous page*
            *(Not available on home or member page)
    *NOTE*
        Certain commands can only be used on certain pages.
        Enter command 'help' in system for a full list of
        all commands and where they can be used
    *ENDNOTE*
    
DOCUMENTATION:
    (1) Documentation is found at
        http://csitrd.kutztown.edu/~ccarr419/csc520/final/finalproj/
    (2) If documentation is not found or link is broken please
        feel to email me at ccarr419@live.kutztown.edu or edit
        the build.xml to your liking -- you have my permission.
        
NOTES:
    (1) Because of a lack of time, there was no unit testing involved
    (2) Because of a lack of time, a limited amount of integration 
        testing was done (only to make sure all parts of the client work)
    (3) At random times (~1-5% of the time) test data may not upload
        correctly causing logon to fail. Quitting and restarting the
        client or recompiling the system will most likely fix this.
        If it does not work the first time, it will certainly fix
        itself if done multiple times. There may either be a lag
        with data retrieval/entry somewhere or a hidden bug.

