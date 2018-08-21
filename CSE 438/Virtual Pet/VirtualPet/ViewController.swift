//
//  ViewController.swift
//  VirtualPet
//
//  Created by Taylor Lau on 9/18/17.
//  Copyright © 2017 Taylor Lau. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    @IBOutlet weak var foodLevel: UILabel!
    @IBOutlet weak var pet: UIImageView!
    @IBOutlet weak var happinessLevel: UILabel!
    @IBOutlet weak var petBackground: UIView!
    @IBOutlet var happyBar: DisplayView!
    @IBOutlet var foodBar: DisplayView!
    @IBOutlet weak var hardMode: UISwitch!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        color(c: UIColor.orange)
        pet.image = UIImage(named: "dog")
        timer = Timer.scheduledTimer(timeInterval: 2, target: self, selector: #selector(loseFood), userInfo: nil, repeats: true)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    // col 0: current happiness
    // col 1: current food level
    // col 2: total plays
    // col 3: total feeds
    var info : [[Int]] = Array(repeating: Array(repeating: 0, count: 4), count: 5)
    var timer = Timer()
    var currPet = 0
    
    // call every 2 seconds, decreases food level if hard mode is toggled on
    func loseFood() {
        if (hardMode.isOn) {
            for i in 0...4 {
                if (info[i][1] > 0) {
                    info[i][1] -= 1;
                }
            }
            update()
        }
    }
    
    // updates text and bars
    func update() {
        happyBar.value = CGFloat(Double(info[currPet][0])/10.0)
        foodBar.value = CGFloat(Double(info[currPet][1])/10.0)
        happinessLevel.text = String(info[currPet][2])
        foodLevel.text = String(info[currPet][3])
    }
    
    // colors bars and background
    func color(c : UIColor) {
        petBackground.backgroundColor = c
        happyBar.color = c
        foodBar.color = c
    }
    
    @IBAction func dog(_ sender: Any) {
        color(c: UIColor.orange)
        pet.image = UIImage(named: "dog")
        currPet = 0
        update()
    }
    @IBAction func cat(_ sender: Any) {
        color(c: UIColor.red)
        pet.image = UIImage(named: "cat")
        currPet = 1
        update()
    }
    @IBAction func bird(_ sender: Any) {
        color(c: UIColor.blue)
        pet.image = UIImage(named: "bird")
        currPet = 2
        update()
    }
    @IBAction func bunny(_ sender: Any) {
        color(c: UIColor.green)
        pet.image = UIImage(named: "bunny")
        currPet = 3
        update()
    }
    @IBAction func fish(_ sender: Any) {
        color(c: UIColor.purple)
        pet.image = UIImage(named: "fish")
        currPet = 4
        update()
    }

    // food level goes down, happiness goes up
    @IBAction func play(_ sender: Any) {
        if (info[currPet][1] > 0) { // need food to play
            info[currPet][1] -= 1
            info[currPet][0] += 1
            info[currPet][2] += 1
            update()
        }
    }
    
    // food level goes up
    @IBAction func feed(_ sender: Any) {
        if (info[currPet][1] < 10) {
            info[currPet][1] += 1
        }
        info[currPet][3] += 1
        update()
    }
}
