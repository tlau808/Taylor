import UIKit

class SearchTableViewController: UITableViewController {
    let userDefaults = UserDefaults.standard
    @IBOutlet var myTable: UITableView!

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        self.tableView.reloadData()
    }

    override func didReceiveMemoryWarning() {super.didReceiveMemoryWarning()}
    
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if let history = userDefaults.array(forKey: "history") {return history.count} else {return 0}
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "cell", for: indexPath)
        var history: Array = userDefaults.array(forKey: "history")!
        cell.textLabel?.text = history[indexPath.row] as? String
        return cell
    }
    
    override func tableView(_ tableView: UITableView, canEditRowAt indexPath: IndexPath) -> Bool {return true}
    
    
    override func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCellEditingStyle, forRowAt indexPath: IndexPath) {
        var history: Array = userDefaults.array(forKey: "history")!
        if editingStyle == .delete {
            history.remove(at: indexPath.row)
            userDefaults.set(history, forKey: "history")
            tableView.deleteRows(at: [indexPath], with: .automatic)
        }
    }
    
    @IBAction func clear(_ sender: UIButton) {
        userDefaults.removeObject(forKey: "history")
        self.tableView.reloadData()
    }
}
