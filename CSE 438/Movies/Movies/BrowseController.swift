import UIKit

var titles = [String]()
var links = [String]()
var ids = [Int]()
class BrowseController: UIViewController, UICollectionViewDelegate, UICollectionViewDataSource, UISearchBarDelegate, UIPickerViewDelegate, UIPickerViewDataSource {
    let userDefaults = UserDefaults.standard
    override func viewDidLoad() {
        super.viewDidLoad()
        picker.delegate = self
        picker.dataSource = self
        UIView.setAnimationsEnabled(false)
        self.collectionView.delegate = self
        self.collectionView.dataSource = self
        searchBar.delegate = self
        searchBar.returnKeyType = UIReturnKeyType.done
        picker.isHidden = true
    }
    
    override func didReceiveMemoryWarning() {super.didReceiveMemoryWarning()}
    
    @IBOutlet weak var collectionView: UICollectionView!
    @IBOutlet weak var searchBar: UISearchBar!
    @IBOutlet weak var indicator: UIActivityIndicatorView!
    @IBOutlet weak var picker: UIPickerView!
    
    let queries = ["", "Most popular movies", "Movies by Christopher Nolan", "Highest voted movies"]
    let queryLinks = ["", "https://api.themoviedb.org/3/discover/movie?api_key=9d53e87b326612db4f78d0d369ae940b&sort_by=popularity.desc", "https://api.tmdb.org/3/search/person?api_key=9d53e87b326612db4f78d0d369ae940b&query=christopher%20nolan", "https://api.tmdb.org/3/discover/movie?api_key=9d53e87b326612db4f78d0d369ae940b&sort_by=vote_average.desc"]
    
    func numberOfComponents(in pickerView: UIPickerView) -> Int {return 1}
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {return queries.count}
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {return queries[row]}
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        remove()
        if (row > 0) {
            self.indicator.startAnimating()
            DispatchQueue.global(qos: .userInitiated).async {
                let json = self.getJSON(path: self.queryLinks[row])
                if (row == 2) { // discover by person is formatted differently
                    for i in 0...2 {
                        titles.append(json["results"][0]["known_for"][i]["title"].string!)
                        links.append(json["results"][0]["known_for"][i]["poster_path"].string!)
                        ids.append(json["results"][0]["known_for"][i]["id"].int!)
                    }
                } else {
                    for i in 0...json["results"].count-1 {
                        if (json["results"][i]["title"] != JSON.null) {
                            titles.append(json["results"][i]["title"].string!)}
                        if (json["results"][i]["poster_path"] != JSON.null) { // in case there is no poster
                            links.append(json["results"][i]["poster_path"].string!) // append poster link
                        } else {links.append("nolink")}
                        ids.append(json["results"][i]["id"].int!) // append ID
                    }
                }
                DispatchQueue.main.async {
                    self.collectionView.reloadData()
                    self.indicator.stopAnimating()
                }
            }
        }
        picker.isHidden = true
    }
    
    private func getJSON(path: String) -> JSON {
        guard let url = URL(string: path) else { return JSON.null }
        do {
            let data = try Data(contentsOf: url)
            return try JSON(data: data)
        } catch {return JSON.null}
    }
    
    func remove() {
        titles.removeAll()
        links.removeAll()
        ids.removeAll()
    }
    
    func searchBar(_ searchBar: UISearchBar, textDidChange searchText: String) {
        remove()
        self.indicator.startAnimating()
        DispatchQueue.global(qos: .userInitiated).async {
            let json = self.getJSON(path: "https://api.themoviedb.org/3/search/movie?api_key=9d53e87b326612db4f78d0d369ae940b&query=" + searchText)
            if (searchText != "" && json["results"].count > 0) {
                for i in 0...json["results"].count-1 {
                    if (json["results"][i]["title"] != JSON.null) {
                        titles.append(json["results"][i]["title"].string!) // append title
                    } else {titles.append("No title")}
                    if (json["results"][i]["poster_path"] != JSON.null) {
                        links.append(json["results"][i]["poster_path"].string!) // append poster link if available
                    } else {links.append("nolink")}
                    ids.append(json["results"][i]["id"].int!) // append ID. assume every movie has an ID
                }
            }
            DispatchQueue.main.async {
                self.collectionView.reloadData()
                self.indicator.stopAnimating()
            }
        }
    }
    
    @IBAction func showPicker(_ sender: UIButton) {picker.isHidden = false}
    
    override func prepare(for segue: UIStoryboardSegue, sender: (Any)?) {
        let path = collectionView.indexPathsForSelectedItems?[0] as NSIndexPath?
        let dc = segue.destination as! DetailController
        navigationItem.title = nil
        dc.idNumber = ids[(path?.row)!] // store ID of movie to perform another request
        if (userDefaults.object(forKey: "history") == nil) {userDefaults.set([String](), forKey: "history")}
        var history: Array = userDefaults.array(forKey: "history")!
        if !history.contains(where: {$0 as? String == searchBar.text}) {
            history.append(searchBar.text!)
        }
        userDefaults.set(history, forKey: "history")
    }
    
    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {return titles.count}
    
    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        let cell = collectionView.dequeueReusableCell(withReuseIdentifier: "collection_cell", for: indexPath) as! CollectionViewCell
        if (titles.count > 0) {
            if (links[indexPath.row] != "nolink") {
                let url = URL(string: "http://image.tmdb.org/t/p/w185/" + links[indexPath.row])
                let data = try? Data(contentsOf: url!)
                let image = UIImage(data: data!)
                cell.title.text = titles[indexPath.row]
                cell.image.image = image
            }
        }
        return cell
    }
}
