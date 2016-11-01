/* * * * * * * * * * * * * * * * * * * * * * * *
*   Author:     Christian Carreras
*   File:       ViewController.swift
*   Project:    GuitarPlayer
*   Course:     CSC 330 Mobile Architecture
*   Date:       03/29/2016
* * * * * * * * * * * * * * * * * * * * * * * */

import UIKit
import AVFoundation     //For all audio related functions
import Darwin           //For usleep function

class ViewController: UIViewController, UITextFieldDelegate {
    
    var startTime: NSTimeInterval!              //the time when a note if first pressed (for debugging purposes)
    var recordStart: NSTimeInterval!            //the time when the record button is pressed
    var time: NSTimeInterval!                   //the difference in time since startTime (for debugging purposes)
    var recordTime: NSTimeInterval!             //the difference in time since recordStart
    var Isrecording: Bool!                      //boolean value to check if the app is recording or not
    var player: AVAudioPlayer!                  //audio handler, plays the notes
    var theRecording: Array<NSTimeInterval>!    //array that holds the times of when the notes are pressed
    var parallelRecording: Array<Int32>!        //parallel array to theRecording that holds which notes are pressed
    var timer: NSTimer!                         //holds the value of time to wait between playing notes in the recording
    var recordingName: String!
    var recordingHolder: Array<Array<NSTimeInterval>>!
    var recordingHolderParallel: Array<Array<Int32>>!
    var recordingCount: Int32!
    var currentRecording: Int32!
    @IBOutlet weak var recordButton: UIButton!          //the button to press to record
    @IBOutlet weak var stopRecordingButton: UIButton!   //the button to press to stop recording
    @IBOutlet weak var playRecording: UIButton!         //the button to press to play the recording
    @IBOutlet weak var nameRecording: UITextField!
    @IBOutlet weak var renameRecording: UIButton!
    @IBOutlet weak var renameRecordingButton: UIButton!
    @IBOutlet weak var deleteRecordingButton: UIButton!
    @IBOutlet weak var nameLabel: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.startTime = NSDate.timeIntervalSinceReferenceDate()    //time since app opened
        self.Isrecording = false;       //make sure recording app is not recording yet
        self.player = AVAudioPlayer()
        self.theRecording = [NSTimeInterval]()  //set up arrays for recording later
        self.parallelRecording = [Int32]()
        self.nameRecording.delegate = self
        self.recordingHolder = Array<Array<NSTimeInterval>>()
        self.recordingHolderParallel = Array<Array<Int32>>()
        self.recordingCount = 0
        self.currentRecording = 0
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    //This function plays the note and handles part of the recording functionality
    @IBAction func playNoteOn(b:UIButton) {
        let note = String(b.tag) //hold the tag to get the correct audio file
        
        setUpPlayer(note) //get the correct file ready
        
        //debugging information
        self.time = (NSDate.timeIntervalSinceReferenceDate() - startTime)
        print("silence for \(self.time) seconds")
        
        //Do this when recording
        if(Isrecording == true)
        {
            //record start of note press and put it in the array
            recordTime = (NSDate.timeIntervalSinceReferenceDate() - recordStart)
            theRecording.append(recordTime)
            parallelRecording.append(0) //zero indicates that nothing was pressed in that interval of time
        }
        
        self.startTime = NSDate.timeIntervalSinceReferenceDate() //for debugging
        player.play() //play the note
    }
    
    //This function stops playing the current note beiing played
    @IBAction func playNoteOff(b:UIButton) {
        player.stop()
        
        //for debugging purposes
        self.time = (NSDate.timeIntervalSinceReferenceDate() - startTime)
        print("note \(b.tag) pressed for \(self.time) seconds")
        
        //Execute if recording
        if(Isrecording == true)
        {
            //record the time when the note was released
            recordTime = (NSDate.timeIntervalSinceReferenceDate() - recordStart)
            theRecording.append(recordTime)
            parallelRecording.append(Int32(b.tag)) //place the note number in the array
        }
    }
    
    //This function starts up the recording process when the record button is pressed
    @IBAction func recordPlaying(sender: AnyObject) {
        //Clear the last recording
        theRecording.removeAll()
        parallelRecording.removeAll()
        recordingName = ""
        nameRecording.text = ""
        nameLabel.text = ""
        
        //Hide the recording and play recording button, show the stop recording button,
        recordButton.hidden = true
        recordButton.enabled = false
        stopRecordingButton.enabled = true
        stopRecordingButton.hidden = false
        playRecording.hidden = true
        playRecording.enabled = false
        renameRecordingButton.hidden = true
        renameRecordingButton.enabled = false
        deleteRecordingButton.hidden = true
        deleteRecordingButton.enabled = false
        
        //Switch the app to recording mode
        Isrecording = true;
        print("start recording...")
        self.recordStart = NSDate.timeIntervalSinceReferenceDate() //Denote the time when recording started
    }
    
    //This function wraps up the recording process and returns the app to normal
    @IBAction func stopRecording(sender: AnyObject) {
        //Denote the end time of the recording
        recordTime = (NSDate.timeIntervalSinceReferenceDate() - recordStart)
        
        //Hide the stop recording button, show the record and play recording button
        stopRecordingButton.hidden = true
        stopRecordingButton.enabled = false
        recordButton.hidden = false
        recordButton.enabled = true
        playRecording.hidden = false
        playRecording.enabled = true
        print("recorded for \(self.recordTime) seconds") //display total amount of time spent recording for debugging
        
        //Place last elements in arrays
        theRecording.append(recordTime)
        parallelRecording.append(0)
        
        recordingHolder.append(theRecording)
        recordingHolderParallel.append(parallelRecording)
        
        recordingCount = recordingCount + 1
        
        Isrecording = false //turn off recording
        nameRecording.hidden = false
        nameRecording.enabled = true
        nameRecording.becomeFirstResponder()
    }
    
    //This function plays back what the user recorded
    @IBAction func playTheRecording(sender: AnyObject) {
        //Disable buttons so the user cannot mess anything up
        playRecording.enabled = false
        recordButton.enabled = false
        renameRecordingButton.enabled = false
        deleteRecordingButton.enabled = false
        print("playing '\(recordingName)'")
        var i: Int = 0 //index variable
        if(theRecording.count < 2) { //if the array's count is less than two, the user did not record anything
            return
        }
        
        while (i < theRecording.count) {
            if(i == 0) { //the first element in the array will always be silence
                //get the time of the first silence in microseconds
                let timer = useconds_t(theRecording[0]*960000) //closer to normal speed for some reason
                print("waiting...")
                usleep(timer) //wait until the first note is played (in microseconds)
            }
            else {
                //get the time between when the note was pressed and was stopped in microseconds
                let timer = useconds_t((theRecording[i]-theRecording[i-1])*960000) //closer to normal speed for some reason
                //if the note is 0 then just wait
                if(parallelRecording[i] == 0) {
                    print("waiting...")
                    usleep(timer)
                }
                //an acutal note was pressed, prepare to play it
                else {
                    setUpPlayer(String(parallelRecording[i]))
                    print("playing note: \(parallelRecording[i])")
                    //play note for the set amount of time
                    player.play()
                    usleep(timer)
                    self.player.stop()
                }
            }
            i++ //increment index
        }
        print("end")
        //Return buttons to normal
        playRecording.enabled = true
        recordButton.enabled = true
        renameRecordingButton.enabled = true
        deleteRecordingButton.enabled = true
    }
    
    @IBAction func renameRecording(sender: AnyObject) {
        nameRecording.hidden = false
        nameRecording.enabled = true
        nameRecording.becomeFirstResponder()
        nameLabel.text = recordingName
    }
    
    @IBAction func deleteRecording(sender: AnyObject) {
        theRecording.removeAll()
        parallelRecording.removeAll()
        recordingName = ""
        nameRecording.text = ""
        nameLabel.text = ""
        
        playRecording.hidden = true
        playRecording.enabled = false
        renameRecordingButton.hidden = true
        renameRecordingButton.enabled = false
        deleteRecordingButton.hidden = true
        deleteRecordingButton.enabled = false
        print("recording deleted")
    }
    
    //This function setups up the audio player to play the correct note
    func setUpPlayer(note: String) {
        //get the address of the note to play by placing the note number in the string
        let guitarNote = NSURL(fileURLWithPath: NSBundle.mainBundle().pathForResource("Strat P- "+note, ofType: "wav")!)
        
        do //do try catch for error checking
        {
            //hook up the audio player to the audio file
            try player = AVAudioPlayer.init(contentsOfURL: guitarNote, fileTypeHint: "wav")
        }
        catch //if there was an error locating the file
        {
            print("error: file not found")
        }
    }
    
    func textFieldShouldReturn(textField: UITextField) -> Bool {
        self.view.endEditing(true)
        recordingName = nameRecording.text
        nameRecording.enabled = false
        nameRecording.hidden = true
        renameRecordingButton.enabled = true
        renameRecordingButton.hidden = false
        deleteRecordingButton.enabled = true
        deleteRecordingButton.hidden = false
        nameLabel.text = recordingName
        return false
    }
}

