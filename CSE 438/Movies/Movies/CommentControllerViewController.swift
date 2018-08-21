import UIKit

class CommentControllerViewController: UIViewController, UITextViewDelegate {
    let userDefaults = UserDefaults.standard
    var commentNumber = 0
    @IBOutlet weak var comment: UITextView!
    @IBOutlet weak var slider: UISlider!

    override func viewDidLoad() {
        super.viewDidLoad()
        comment.delegate = self
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        if (userDefaults.object(forKey: "comments") == nil) {
            userDefaults.set(Array(repeating: "", count: 100), forKey: "comments")
        }
        if (userDefaults.object(forKey: "ratings") == nil) {
            userDefaults.set(Array(repeating: 5.0, count: 100), forKey: "ratings")
        }
        var ratings: Array = userDefaults.array(forKey: "ratings")!
        slider.value = ratings[commentNumber] as! Float
        var comms: Array = userDefaults.array(forKey: "comments")!
        comment.text = comms[commentNumber] as! String

    }
    
    override func didReceiveMemoryWarning() {super.didReceiveMemoryWarning()}
    
    @IBAction func sliding(_ sender: UISlider) {
        var ratings: Array = userDefaults.array(forKey: "ratings")!
        ratings[commentNumber] = sender.value
        userDefaults.set(ratings, forKey:"ratings")
    }
    
    
    func textViewDidChange(_ textView: UITextView) {
        var comms: Array = userDefaults.array(forKey: "comments")!
        comms[commentNumber] = textView.text
        userDefaults.set(comms, forKey: "comments")
    }
}
