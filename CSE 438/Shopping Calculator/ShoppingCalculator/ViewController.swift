//
//  ViewController.swift
//  ShoppingCalculator
//
//  Created by Taylor Lau on 8/31/17.
//  Copyright © 2017 Taylor Lau. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UITextFieldDelegate {
    
    @IBOutlet weak var original: UITextField!
    @IBOutlet weak var discount: UITextField!
    @IBOutlet weak var tax: UITextField!
    @IBOutlet weak var final: UITextField!
    @IBOutlet weak var buyers: UITextField!
    
    override func viewDidLoad() {
        super.viewDidLoad()
    }
    
    
    @IBAction func calculate(_ sender: Any) {
        var o = 0.0
        var d = 0.0
        var t = 0.0
        var b = 0.0
        if (!(original.text?.isEmpty)! && Double((original.text)!) != nil) {
            o = Double(original.text!)!
        }
        if (!(discount.text?.isEmpty)! && Double((discount.text)!) != nil) {
            d = Double(discount.text!)!
        }
        if (!(tax.text?.isEmpty)! && Double((tax.text)!) != nil) {
            t = Double(tax.text!)!
        }
        if (!(buyers.text?.isEmpty)! && Double((buyers.text)!) != nil) {
            b = Double(buyers.text!)!
        }
        let alpha = (100-d)/100
        let beta = (100+t)/100
        let raw = o*beta*alpha/(b+1)
        final.text = "\(String(format: "%.2f", raw))"
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
}
