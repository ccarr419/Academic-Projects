package com.library.business_layer.message_list;
import com.library.business_layer.field_list.Reservation;
import com.library.business_layer.field_list.Concluded;
import com.library.business_layer.field_list.Member;
import com.library.persistence_layer.*;
import java.util.ArrayList;
import java.sql.Timestamp;

/**
* ReservationHome serves as a way to access the ReservationTable. Thus it also 
* serves as an accessor to the table's element's attributes. Another purpose of
* ReservationHome is to create and add any new entries to the ReservationTable.
* BUSINESS LAYER CLASS
* @see com.library.business_layer.field_list.Reservation
*/
public class ReservationHome {
    private Table resTable;
    private Table conTable;
    
    /**
    * Basic constructor for ReservationHome that instantiates home's Tables.
    */
    public ReservationHome() { 
        resTable = new DataSchema.ReservationTable();
        conTable = new DataSchema.ConcludedReservationTable();
    }
    
    /**
    * Gets the ReservationTable as a whole.
    * @return DataSchema.ReservationTable
    */
    public DataSchema.ReservationTable getReservations() { 
        return (DataSchema.ReservationTable) resTable;
    }
    
    /**
    * Finds a Reservation by its primary key identifier.
    * @param id int
    * @return Reservation
    */
    public Reservation findByPrimaryKey(int id) {
        return (Reservation) resTable.selectId(id);
    }
    
    /**
    * Creates a new Reservation and appends it to the ReservationTable.
    * @param num String reservation number
    * @param t Timestamp timestamp of reservation
    * @param memId int member id
    * @param cbId int cataloged book id
    * @return the newly created Reservation
    */
    public Reservation create(String num, Timestamp t, int memId, int cbId) { 
        Reservation newReservation = 
            new Reservation(resTable.nextKey(), num, t, memId, cbId);
        resTable.append(newReservation);
        return newReservation;
    }
    
    /**
    * Find all Reservations for a member that were not concluded.
    * @param m Member
    * @return List of unconcluded Reservations
    */
    public ArrayList<Reservation> findUnconcludedByMember(Member m) {
        ArrayList<Reservation> res = resTable.selectWhere("memberId", m.getId());
        for(Reservation r : res) {
            ArrayList<Concluded> con = conTable.selectWhere("reservationId", r.getId());
            if(!con.isEmpty()) { res.remove(r); }
        }
        return res;
    }
    
    /**
    * Force the update of all ReservationHome Tables.
    */
    public void update() {
        resTable.updateList();
        conTable.updateList();
    }
}