import UIKit

class DetailController: UIViewController {
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        let json = getJSON(path: "https://api.themoviedb.org/3/movie/" + String(idNumber) + "?api_key=9d53e87b326612db4f78d0d369ae940b")
        if (json["runtime"] != JSON.null) {
            runtime = json["runtime"].int!
        }
        if (json["title"] != JSON.null) {
            movieTitle = json["title"].string!
        }
        if (json["budget"] != JSON.null) {
            budget = json["budget"].int!
        }
        if (json["release_date"] != JSON.null) {
            releaseDate = json["release_date"].string!
        }
        if (json["poster_path"] != JSON.null) {
            backdrop = json["poster_path"].string!
        }
        let url = URL(string: "http://image.tmdb.org/t/p/w185/" + backdrop)
        let data = try? Data(contentsOf: url!)
        let image = UIImage(data: data!)
        movieLength.text = String(runtime) + " minutes"
        movieImage.image = image
        movieBudget.text = "$" + String(budget)
        movieDate.text = releaseDate
        self.title = movieTitle
    }

    override func didReceiveMemoryWarning() {super.didReceiveMemoryWarning()}

    @IBOutlet weak var movieLength: UILabel!
    @IBOutlet weak var movieDate: UILabel!
    @IBOutlet weak var movieImage: UIImageView!
    @IBOutlet weak var movieBudget: UILabel!
    let userDefaults = UserDefaults.standard
    var idNumber = 0
    var movieTitle = ""
    var runtime = 0
    var budget = 0
    var releaseDate = ""
    var backdrop = ""
    
    @IBAction func makeFavorite(_ sender: UIButton) {
        if (userDefaults.object(forKey: "favorites") == nil) {userDefaults.set([String](), forKey: "favorites")}
        var fav: Array = userDefaults.array(forKey: "favorites")!
        fav.append(movieTitle)
        userDefaults.set(fav, forKey: "favorites")
        let fc = storyboard?.instantiateViewController(withIdentifier: "FC") as! FavoritesController
        fc.tableView.reloadData()
    }
    
    private func getJSON(path: String) -> JSON {
        guard let url = URL(string: path) else { return JSON.null }
        do {
            let data = try Data(contentsOf: url)
            return try JSON(data: data)
        } catch {return JSON.null}
    }
}
