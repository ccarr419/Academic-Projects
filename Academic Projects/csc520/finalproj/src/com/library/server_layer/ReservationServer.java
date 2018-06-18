package com.library.server_layer;
import com.library.business_layer.field_list.Member;
import com.library.business_layer.field_list.Reservation;
import com.library.business_layer.field_list.CatalogedBook;
import com.library.business_layer.message_list.MemberHome;
import com.library.business_layer.message_list.CatalogedBookHome;
import com.library.business_layer.message_list.ReservationHome;
import com.library.protocol.message_list.PCatalogedBookHome;
import com.library.protocol.message_list.PReservationHome;
import com.library.protocol.field_list.PCatalogedBook;
import com.library.protocol.field_list.PReservation;
import java.util.ArrayList;
import java.sql.Timestamp;
import java.util.Date;

/**
* The role of the ReservationServer is to communicate between the Home
* classes and server UI classes. The functionality of this server includes
* reading reservations and reserved books, creating and cancelling reservations.
* SERVER LAYER
*/
public class ReservationServer {
    private int resCount; //Needed for reservation number
    private MemberHome mh;
    private ReservationHome rh;
    private CatalogedBookHome cbh;
    private PReservationHome pRH;
    private PCatalogedBookHome pCBH;
    
    /**
    * Basic constructor for this Object that initializes used Home classes.
    */
    public ReservationServer() {
        resCount = 0;
        mh = new MemberHome();
        rh = new ReservationHome();
        cbh = new CatalogedBookHome();
        pRH = new PReservationHome();
        pCBH = new PCatalogedBookHome();
    }
    
    /**
    * Get all Reservations for a member with the session id. Transforms all
    * Reservation into PReservation for tranferring to server UI.
    * @param i int session id
    * @return ArrayList of PReservation
    */
    public ArrayList<PReservation> readReservations(int i) {
        ArrayList<PReservation> pRList = new ArrayList<>();
        Member mem = mh.findBySessionId(i);
        if(mem != null) {
            for(Reservation r : rh.findUnconcludedByMember(mem)) {
                pRList.add(pRH.create(r.getNumber(), r.getTimestamp()));
            }
        }
        return pRList;
    }
    
    /**
    * Get all reserved CatalogedBooks for a member with the session id. 
    * Transforms all CatalogedBook into PCatalogedBook for tranferring to server UI.
    * @param i int session id
    * @return ArrayList of PCatalogedBook
    */
    public ArrayList<PCatalogedBook> readReservedBooks(int i) {
        ArrayList<PCatalogedBook> cbList = new ArrayList<>();
        ArrayList<CatalogedBook> tmp = new ArrayList<>();
        Member mem = mh.findBySessionId(i);
        if(mem != null) {
            for(Reservation r : rh.findUnconcludedByMember(mem)) {
                tmp = cbh.getCatalogedBooks().selectWhere("id", r.getCatalogedBookId());
                if(!tmp.isEmpty()) {
                    cbList.add(
                        pCBH.create(tmp.get(0).getIsbn(), tmp.get(0).getName()
                    ));
                }
            }
        }
        return cbList;
    }
    
    /**
    * Creates a new Reservation and returns PReservation for tranferring to 
    * server UI.
    * @param i int session id
    * @param c int cataloged book id
    * @return PReservation
    */
    public PReservation createReservation(int i, int c) {
        Member mem = mh.findBySessionId(i);
        if(mem != null) {
            int memid = mem.getId();
            Reservation r = rh.create(Integer.toString(++resCount), 
                new Timestamp(new Date().getTime()), memid, c);
            return pRH.create(r.getNumber(), r.getTimestamp());
        }
        return null;
    }
    
    /**
    * Cancels Reservation for a member with the session id.
    * @param i int session id
    * @param r int reservation id
    * @return true if reservation was cancelled, false if not
    */
    public boolean cancelReservation(int i, int r) {
        Member mem = mh.findBySessionId(i);
        if(mem != null) {
            for(Reservation res : rh.findUnconcludedByMember(mem)) {
                if(res.getId() == r) {
                    rh.getReservations().deleteId(r);
                    return true;
                }
            }
        }
        return false;
    }
    
    /**
    * Force the update of the ReservationServer and all its Homes
    */
    public void update() {
        mh.update();
        rh.update();
        cbh.update();
    }
}