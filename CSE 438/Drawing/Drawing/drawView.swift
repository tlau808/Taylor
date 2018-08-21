//
//  drawView.swift
//  Drawing
//
//  Created by Taylor Lau on 10/2/17.
//  Copyright © 2017 Taylor Lau. All rights reserved.
//

import UIKit

class drawView: UIView {
    var color = UIColor.green
    var thickness:CGFloat = 5
    var pointHistory = [CGPoint]() // so we can call createQuadPath()
    var pathHistory = [UIImage]() // so we can undo
    var lastPoint: CGPoint!
    var preDisplay: UIImage! // the previous state of the drawing
    var theShape = ""
    var grid = false
    var spacing = 20
    
    override init(frame: CGRect) {super.init(frame: frame)}
    
    required init?(coder aDecoder: NSCoder) {super.init(coder: aDecoder)}
    
    // when touch begins
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        lastPoint = touches.first?.location(in: self)
        pointHistory.append(lastPoint)
    }
    
    // while touch is in motion
    override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?) {
        let newPoint = touches.first?.location(in: self)
        pointHistory.append(newPoint!)
        lastPoint = newPoint
        setNeedsDisplay()
    }
    
    // when touch ends
    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
        UIGraphicsBeginImageContextWithOptions(self.bounds.size, false, 0.0)
        if (preDisplay != nil) {pathHistory.last?.draw(in: self.bounds)}
        color.setStroke()
        createQuadPath(points: pointHistory).stroke()
        preDisplay = UIGraphicsGetImageFromCurrentImageContext()
        pathHistory.append(preDisplay)
        UIGraphicsEndImageContext()
        setNeedsDisplay()
        pointHistory.removeAll()
    }
    
    override func draw(_ rect: CGRect) {
        super.draw(rect)
        if (grid) {
            UIColor.lightGray.setStroke()
            drawGrid().stroke()
        }
        UIColor.cyan.setStroke()
        UIColor.cyan.setFill()
        drawShape().stroke()
        if (preDisplay != nil) {pathHistory.last?.draw(in: self.bounds)}
        color.setStroke()
        createQuadPath(points: pointHistory).stroke()
    }
    
    // clear all lines
    func clear() {
        preDisplay = nil
        pathHistory.removeAll()
        setNeedsDisplay()
    }
    
    // undo last line
    func undo() {
        if (pathHistory.count > 0) {pathHistory.removeLast()}
        setNeedsDisplay()
    }
    
    func drawGrid() -> UIBezierPath {
        let gridPath = UIBezierPath()
        for i in 0...40 {
            gridPath.move(to: CGPoint(x: 0, y:spacing*i))
            gridPath.addLine(to: CGPoint(x: 400, y:spacing*i))
            gridPath.move(to: CGPoint(x: spacing*i, y:0))
            gridPath.addLine(to: CGPoint(x:spacing*i, y:600))
        }
        return gridPath
    }
    
    func drawShape() -> UIBezierPath {
        let path = UIBezierPath()
        if (theShape == "circle") {path.addArc(withCenter: CGPoint(x: UIScreen.main.bounds.size.width/2, y: UIScreen.main.bounds.size.height/2), radius: CGFloat(100), startAngle: CGFloat(0), endAngle:CGFloat(Double.pi * 2), clockwise: true)}
        if (theShape == "square") {
            path.move(to: CGPoint(x: UIScreen.main.bounds.size.width/2-100, y: UIScreen.main.bounds.size.height/2-100))
            path.addLine(to: CGPoint(x: UIScreen.main.bounds.size.width/2-100, y: UIScreen.main.bounds.size.height/2+100))
            path.addLine(to: CGPoint(x: UIScreen.main.bounds.size.width/2+100, y: UIScreen.main.bounds.size.height/2+100))
            path.addLine(to: CGPoint(x: UIScreen.main.bounds.size.width/2+100, y: UIScreen.main.bounds.size.height/2-100))
        }
        if (theShape == "triangle") {
            path.move(to: CGPoint(x: UIScreen.main.bounds.size.width/2, y: 200))
            path.addLine(to: CGPoint(x: UIScreen.main.bounds.size.width/2-100, y: 400))
            path.addLine(to: CGPoint(x: UIScreen.main.bounds.size.width/2+100, y: 400))
        }
        path.close()
        path.fill()
        return path
    }
    
    private func midpoint(first: CGPoint, second: CGPoint) -> CGPoint {return CGPoint(x: (first.x+second.x)/2, y: (first.y+second.y)/2)}
    
    // for smooth lines
    func createQuadPath(points: [CGPoint]) -> UIBezierPath {
        let path = UIBezierPath()
        path.lineWidth = thickness
        if (points.count == 0) {return path}
        if (points.count == 1) {
            path.addArc(withCenter: points[0], radius: thickness/2, startAngle: 0, endAngle:CGFloat(Double.pi * 2), clockwise: true)
            color.setFill()
            path.fill()
            return path
        }
        let firstPoint = points[0]
        let secondPoint = points[1]
        let firstMidpoint = midpoint(first: firstPoint, second: secondPoint)
        path.move(to: firstPoint)
        path.addLine(to: firstMidpoint)
        for index in 1 ..< points.count-1 {
            let currentPoint = points[index]
            let nextPoint = points[index + 1]
            let midPoint = midpoint(first: currentPoint, second: nextPoint)
            path.addQuadCurve(to: midPoint, controlPoint: currentPoint)
        }
        guard let lastLocation = points.last else { return path }
        path.addLine(to: lastLocation)
        return path
    }
}
