//
//  ViewController.swift
//  Drawing
//
//  Created by Taylor Lau on 9/26/17.
//  Copyright © 2017 Taylor Lau. All rights reserved.
//

import UIKit

class ViewController: UIViewController ,UIPickerViewDelegate, UIPickerViewDataSource {
    @IBOutlet weak var slider: UISlider!
    @IBOutlet weak var drawing: drawView!
    @IBOutlet weak var shape: UIPickerView!
    @IBOutlet weak var stepper: UIStepper!
    var shapes = ["", "circle", "square", "triangle"]

    override func viewDidLoad() {
        super.viewDidLoad()
        shape.delegate = self
        shape.dataSource = self
    }
    
    @IBAction func thickness(_ sender: UISlider) {drawing.thickness = CGFloat(sender.value)}
    
    @IBAction func spacing(_ sender: UIStepper) {
        drawing.spacing = Int(sender.value)
        drawing.setNeedsDisplay()
    }
    
    @IBAction func gridOn(_ sender: UIButton) {
        drawing.grid = !drawing.grid
        drawing.setNeedsDisplay()
    }
    
    @IBAction func clear(_ sender: UIButton) {drawing.clear()}
    @IBAction func undo(_ sender: UIButton) {drawing.undo()}
    @IBAction func green(_ sender: Any) {drawing.color = UIColor.green}
    @IBAction func black(_ sender: Any) {drawing.color = UIColor.black}
    @IBAction func red(_ sender: Any) {drawing.color = UIColor.red}
    @IBAction func blue(_ sender: Any) {drawing.color = UIColor.blue}
    @IBAction func purple(_ sender: Any) {drawing.color = UIColor.purple}

    func numberOfComponents(in pickerView: UIPickerView) -> Int {return 1}
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {return shapes.count}
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {return shapes[row]}
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        drawing.theShape = shapes[row]
        drawing.setNeedsDisplay()
    }
    
    override func didReceiveMemoryWarning() {super.didReceiveMemoryWarning()}
}
