import UIKit

class FavoritesController: UITableViewController {
    let userDefaults = UserDefaults.standard
    @IBOutlet weak var myTable: UITableView!
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        self.tableView.reloadData()
    }

    override func didReceiveMemoryWarning() {super.didReceiveMemoryWarning()}
    
    override func prepare(for segue: UIStoryboardSegue, sender: (Any)?) {
        let path = myTable.indexPathForSelectedRow
        let dc = segue.destination as! CommentControllerViewController
        dc.commentNumber = (path?.row)!
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if let fav = userDefaults.array(forKey: "favorites") {return fav.count} else {return 0}
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "cell", for: indexPath)
        var fav: Array = userDefaults.array(forKey: "favorites")!
        cell.textLabel?.text = fav[indexPath.row] as? String
        return cell
    }

    override func tableView(_ tableView: UITableView, canEditRowAt indexPath: IndexPath) -> Bool {return true}

    
    override func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCellEditingStyle, forRowAt indexPath: IndexPath) {
        var fav: Array = userDefaults.array(forKey: "favorites")!
        if editingStyle == .delete {
            fav.remove(at: indexPath.row)
            userDefaults.set(fav, forKey: "favorites")
            tableView.deleteRows(at: [indexPath], with: .automatic)
        }
    }
    
    @IBAction func clear(_ sender: UIButton) {
        userDefaults.removeObject(forKey: "favorites")
        userDefaults.removeObject(forKey: "comments")
        userDefaults.removeObject(forKey: "ratings")
        self.tableView.reloadData()
    }
}
