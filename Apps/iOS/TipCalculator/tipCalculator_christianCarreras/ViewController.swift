//
//  ViewController.swift
//  tipCalculator_christianCarreras
//
//  Created by Christian Carreras on 2/14/16.
//  Copyright © 2016 Christian Carreras. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var billAmountLabel: UILabel!
    @IBOutlet weak var customTipPercentageLabel1: UILabel!
    @IBOutlet weak var customTipPercentageSlider: UISlider!
    @IBOutlet weak var tip15Label: UILabel!
    @IBOutlet weak var total15Label: UILabel!
    @IBOutlet weak var customTipPercentageLabel2: UILabel!
    @IBOutlet weak var tipCustomLabel: UILabel!
    @IBOutlet weak var totalCustomLabel: UILabel!
    @IBOutlet weak var inputTextField: UITextField!
    @IBOutlet weak var customPartySizeLabel: UILabel!
    @IBOutlet weak var customPartySizeSlider: UISlider!
    @IBOutlet weak var customTipPercentageLabel3: UILabel!
    @IBOutlet weak var partyPay15Label: UILabel!
    @IBOutlet weak var partyPayCustomLabel: UILabel!
    
    let decimal100 = NSDecimalNumber(string: "100.0")
    let decimal15Percent = NSDecimalNumber(string: "0.15")
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        inputTextField.becomeFirstResponder()
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    @IBAction func calculateTip(sender: AnyObject) {
        let inputString = inputTextField.text
        
        let sliderValue = NSDecimalNumber(integer: Int(customTipPercentageSlider.value))
        
        let customPercent = sliderValue/decimal100
        
        let partySize = NSDecimalNumber(integer: Int(customPartySizeSlider.value))
        
        if sender is UISlider
        {
            customTipPercentageLabel1.text =
                NSNumberFormatter.localizedStringFromNumber(customPercent, numberStyle: NSNumberFormatterStyle.PercentStyle)
            customTipPercentageLabel2.text =
                customTipPercentageLabel1.text
            customTipPercentageLabel3.text =
                customTipPercentageLabel1.text
            customPartySizeLabel.text =
                NSNumberFormatter.localizedStringFromNumber(partySize, numberStyle: NSNumberFormatterStyle.NoStyle)
        }
        
        if !inputString!.isEmpty
        {
            let billAmount =
            NSDecimalNumber(string: inputString) / decimal100
            let fifteenTip = billAmount * decimal15Percent
            let customTip = billAmount * customPercent
            
            if sender is UITextField
            {
                billAmountLabel.text = " " + formatAsCurrency(billAmount)
                tip15Label.text = formatAsCurrency(fifteenTip)
                total15Label.text = formatAsCurrency(billAmount + fifteenTip)
                partyPay15Label.text = formatAsCurrency((billAmount + fifteenTip)/partySize)
            }
            
            tipCustomLabel.text = formatAsCurrency(customTip)
            totalCustomLabel.text = formatAsCurrency(billAmount + customTip)
            partyPayCustomLabel.text = formatAsCurrency((billAmount + customTip)/partySize)
            partyPay15Label.text = formatAsCurrency((billAmount + fifteenTip)/partySize)
        }
            
        else
        {
            billAmountLabel.text = ""
            tip15Label.text = ""
            total15Label.text = ""
            tipCustomLabel.text = ""
            totalCustomLabel.text = ""
        }
    }

}

func formatAsCurrency(number: NSNumber) -> String
{
    return NSNumberFormatter.localizedStringFromNumber(number, numberStyle: NSNumberFormatterStyle.CurrencyStyle)
}

func +(left: NSDecimalNumber, right: NSDecimalNumber) -> NSDecimalNumber
{
    return left.decimalNumberByAdding(right)
}

func *(left: NSDecimalNumber, right: NSDecimalNumber) -> NSDecimalNumber
{
    return left.decimalNumberByMultiplyingBy(right)
}

func /(left: NSDecimalNumber, right: NSDecimalNumber) -> NSDecimalNumber
{
    return left.decimalNumberByDividingBy(right)
}

