package com.library.business_layer.message_list;
import com.library.business_layer.field_list.Collectable;
import com.library.business_layer.field_list.Concluded;
import com.library.business_layer.field_list.Displayable;
import com.library.business_layer.field_list.NeedingRenewal;
import com.library.business_layer.field_list.Notifiable;
import com.library.business_layer.field_list.Reservation;
import com.library.business_layer.field_list.Waiting;
import com.library.persistence_layer.*;
import java.util.ArrayList;
import java.sql.Timestamp;
import java.util.Date;

/**
* ReservationStateHome serves as a way to access the all Reservation states
* Tables. Thus it also serves as an accessor to the table's element's 
* attributes. Another purpose of ReservationStateHome is to create and add any 
* new entries to any of the Reservation states Tables.
* BUSINESS LAYER CLASS
* @see com.library.business_layer.field_list.Collectable
* @see com.library.business_layer.field_list.Concluded
* @see com.library.business_layer.field_list.Displayable
* @see com.library.business_layer.field_list.NeedingRenewal
* @see com.library.business_layer.field_list.Notifiable
* @see com.library.business_layer.field_list.Waiting
*/
public class ReservationStateHome {
    private Table colTable, conTable, disTable, neeTable, notTable, waiTable;
    
    /**
    * Basic constructor for ReservationStateHome that instantiates home's Tables.
    */
    public ReservationStateHome() {
        colTable = new DataSchema.CollectableReservationTable();
        conTable = new DataSchema.ConcludedReservationTable();
        disTable = new DataSchema.DisplayableReservationTable();
        neeTable = new DataSchema.NeedingRenewalReservationTable();
        notTable = new DataSchema.NotifiableReservationTable();
        waiTable = new DataSchema.WaitingReservationTable();
    }
    
    /**
    * Gets the CollectableReservationTable as a whole.
    * @return DataSchema.CollectableReservationTable
    */
    public DataSchema.CollectableReservationTable getCollectables() { 
        return (DataSchema.CollectableReservationTable) colTable;
    }
    
    /**
    * Gets the ConcludedReservationTable as a whole.
    * @return DataSchema.ConcludedReservationTable
    */
    public DataSchema.ConcludedReservationTable getConcluded() { 
        return (DataSchema.ConcludedReservationTable) conTable;
    }
    
    /**
    * Gets the DisplayableReservationTable as a whole.
    * @return DataSchema.DisplayableReservationTable
    */
    public DataSchema.DisplayableReservationTable getDisplayables() { 
        return (DataSchema.DisplayableReservationTable) disTable;
    }
    
    /**
    * Gets the NeedingRenewalReservationTable as a whole.
    * @return DataSchema.NeedingRenewalReservationTable
    */
    public DataSchema.NeedingRenewalReservationTable getNeedingRenewals() { 
        return (DataSchema.NeedingRenewalReservationTable) neeTable;
    }
    
    /**
    * Gets the NotifiableReservationTable as a whole.
    * @return DataSchema.NotifiableReservationTable
    */
    public DataSchema.NotifiableReservationTable getNotifiables() { 
        return (DataSchema.NotifiableReservationTable) notTable;
    }
    
    /**
    * Gets the WaitingReservationTable as a whole.
    * @return DataSchema.WaitingReservationTable
    */
    public DataSchema.WaitingReservationTable getWaiting() { 
        return (DataSchema.WaitingReservationTable) waiTable;
    }
    
    /**
    * Creates a new Collectable and appends it to the CollectableReservationTable.
    * @param d Date date notified
    * @param resId int reservation id
    * @return the newly created Collectable
    */
    public Collectable createCollectable(Date d, int resId) {
        Collectable newCollectable = new Collectable(colTable.nextKey(), d, resId);
        colTable.append(newCollectable);
        return newCollectable;
    }
    
    /**
    * Creates a new Concluded and appends it to the ConcludedReservationTable.
    * @param reason String reason for conclusion
    * @param resId int reservation id
    * @return the newly created Concluded
    */
    public Concluded createConcluded(String reason, int resId) {
        Concluded newConcluded = new Concluded(conTable.nextKey(), reason, resId);
        conTable.append(newConcluded);
        return newConcluded;
    }
    
    /**
    * Creates a new Displayable and appends it to the DisplayableReservationTable.
    * @param reason String reason for termination
    * @param resId int reservation id
    * @return the newly created Displayable
    */
    public Displayable createDisplayable(String reason, int resId) {
        Displayable newDisplayable = new Displayable(disTable.nextKey(), reason, resId);
        disTable.append(newDisplayable);
        return newDisplayable;
    }
    
    /**
    * Creates a new NeedingRenewal and appends it to the NeedingRenewalReservationTable.
    * @param d Date renewal deadline date
    * @param resId int reservation id
    * @return the newly created NeedingRenewal
    */
    public NeedingRenewal createNeedingRenewal(Date d, int resId) {
        NeedingRenewal newNeedingRenewal = new NeedingRenewal(neeTable.nextKey(), d, resId);
        neeTable.append(newNeedingRenewal);
        return newNeedingRenewal;
    }
    
    /**
    * Creates a new Notifiable and appends it to the NotifiableReservationTable.
    * @param d Date date book put aside
    * @param resId int reservation id
    * @return the newly created Notifiable
    */
    public Notifiable createNotifiable(Date d, int resId) {
        Notifiable newNotifiable = new Notifiable(notTable.nextKey(), d, resId);
        notTable.append(newNotifiable);
        return newNotifiable;
    }
    
    /**
    * Creates a new Waiting and appends it to the WaitingReservationTable.
    * @param d Date last renewal date
    * @param resId int reservation id
    * @return the newly created Waiting
    */
    public Waiting createWaiting(Date d, int resId) {
        Waiting newWaiting = new Waiting(waiTable.nextKey(), d, resId);
        waiTable.append(newWaiting);
        return newWaiting;
    }
    
    /**
    * Tests whether the Reservation is Collectable or not.
    * @param r Reservation
    * @return true if the Reservation is Collectable, false if not
    */
    public boolean isCollectable(Reservation r) {
        if(colTable.selectWhere("reservationId", r.getId()).isEmpty()) {
            return false;
        }
        else { return true; }
    }
    
    /**
    * Tests whether the Reservation is Concluded or not.
    * @param r Reservation
    * @return true if the Reservation is Concluded, false if not
    */
    public boolean isConcluded(Reservation r) {
        if(conTable.selectWhere("reservationId", r.getId()).isEmpty()) {
            return false;
        }
        else { return true; }
    }
    
    /**
    * Tests whether the Reservation is Displayable or not.
    * @param r Reservation
    * @return true if the Reservation is Displayable, false if not
    */
    public boolean isDisplayable(Reservation r) {
        if(disTable.selectWhere("reservationId", r.getId()).isEmpty()) {
            return false;
        }
        else { return true; }
    }
    
    /**
    * Tests whether the Reservation is NeedingRenewal or not.
    * @param r Reservation
    * @return true if the Reservation is NeedingRenewal, false if not
    */
    public boolean isNeedingRenewal(Reservation r) {
        if(neeTable.selectWhere("reservationId", r.getId()).isEmpty()) {
            return false;
        }
        else { return true; }
    }
    
    /**
    * Tests whether the Reservation is Notifiable or not.
    * @param r Reservation
    * @return true if the Reservation is Notifiable, false if not
    */
    public boolean isNotifiable(Reservation r) {
        if(notTable.selectWhere("reservationId", r.getId()).isEmpty()) {
            return false;
        }
        else { return true; }
    }
    
    /**
    * Tests whether the Reservation is Waiting or not.
    * @param r Reservation
    * @return true if the Reservation is Waiting, false if not
    */
    public boolean isWaiting(Reservation r) {
        if(waiTable.selectWhere("reservationId", r.getId()).isEmpty()) {
            return false;
        }
        else { return true; }
    }
    
    /**
    * Force the update of all ReservationStateHome Tables.
    */
    public void update() {
        colTable.updateList();
        conTable.updateList();
        disTable.updateList();
        neeTable.updateList();
        notTable.updateList();
        waiTable.updateList();
    }
}