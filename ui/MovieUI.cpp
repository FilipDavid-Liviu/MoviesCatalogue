#include "MovieUI.h"
#include <limits>
void normalizeName(string& name){
    int is_new_word = 1;
    for (char & i : name) {
        if (isalpha(i) && is_new_word) {
            i = (char)toupper((int)i);
            is_new_word = 0;
        }
        else if (isalpha(i)) {
            i = (char)tolower((int)i);
        }
        else {
            is_new_word = 1;
        }
    }
}

MovieUI::MovieUI(){
    cout<<"CSV or HTML?\n>";
    string filetype;
    getline(cin, filetype);
    normalizeName(filetype);
    services = new MovieService(filetype);
}

MovieUI::~MovieUI() {
    delete services;
}

void clearBuffer(){
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

const char *add_option= "1";
const char *remove_option= "2";
const char *update_option = "3";
const char *print_option= "4";
const char *exit_option= "0";
const char *admin_option= "1";
const char *user_option= "2";
const char *genre_option = "1";
const char *watchlist_option = "2";
const char *delete_option = "3";
const char *next_option = "2";

void MovieUI::run() {

    while (true){
        printMenuStart();
        string option;
        printf(">");
        getline(cin, option);
        if (option == admin_option) {
            adminMenu();
            return;
        }
        else if (option == user_option) {
            userMenu();
            return;
        }
        else if (option == exit_option) {
            return;
        }
        else {
            cout<<"Invalid option\n";
        }
    }
}

void MovieUI::adminMenu() {


    while (true){
        printMenuAdmin();
        string option;
        printf(">");
        getline(cin, option);
        if (option == add_option) {
            addMovie();
        }
        else if (option == remove_option) {
            removeMovie();
        }
        else if (option == update_option) {
            updateMovie();
        }
        else if (option == print_option) {
            printAllMovies();
        }
        else if (option == exit_option) {
            return;
        }
        else if (option == "z") {
            services->undo();
        }
        else if (option == "y") {
            services->redo();
        }
        else {
            cout<<"Invalid option\n";
        }
    }
}

void MovieUI::userMenu() {

    while (true) {
        printMenuUser();
        string option;
        printf(">");
        getline(cin, option);
        if (option == genre_option) {
            movieMenu();
        }
        else if (option == watchlist_option) {
            printWatchlist();
        }
        else if (option == delete_option) {
            deleteMovie();
        }
        else if (option == exit_option) {
            return;
        }
        else {
            cout<<"Invalid option\n";
        }
    }
}
//#include <windows.h>
void MovieUI::movieMenu() {

    string genre;
    cout << "Genre:";
    getline(cin, genre);
    normalizeName(genre);
    auto* movies = services->getGenreList(genre);
    if (movies->getLength() == 0){
        cout<<"No such genre in the database\n";
        return;
    }
    int i = 0;
    while (true) {
        cout<<endl<<movies->getElements()[i].toString();
        string command = "start firefox \"" + movies->getElements()[i].getTrailer() + "\"";
        system(command.c_str());
        printMenuMovie();
        string option;
        cout<<">";
        getline(cin, option);
        if (option == add_option) {
            try {services->addMovieWatchlist(movies->getElements()[i]);}
            catch (MovieServiceException& error){cout << error.message();}
            i = (i + 1) % movies->getLength();
        }
        else if (option == next_option) {
            i = (i + 1) % movies->getLength();
        }
        else if (option == exit_option) {
            delete movies;
            return;
        }
        else {
            cout<<"Invalid option\n";
        }
    }
}

void MovieUI::printMenuStart() {
    cout << "\n1. Admin Mode\n";
    cout << "2. User Mode\n";
    cout << "0. Exit\n";
}

void MovieUI::printMenuAdmin() {
    cout << "\n1. Add Movie\n";
    cout << "2. Remove Movie\n";
    cout << "3. Update a movie\n";
    cout << "4. Print All Movies\n";
    cout << "0. Exit\n";
}

void MovieUI::printMenuUser() {
    cout << "\n1. Search\n";
    cout << "2. See Watchlist\n";
    cout << "3. Remove from Watchlist\n";
    cout << "0. Exit\n";
}

void MovieUI::printMenuMovie() {
    cout << "\n1. Add Movie to Watchlist\n";
    cout << "2. Next\n";
    cout << "0. Exit\n";
}


void MovieUI::addMovie() {
    string title, genre, trailer;
    int yearOfRelease, numberOfLikes;

    cout << "Enter title:";
    getline(cin, title);
    normalizeName(title);

    cout << "Enter genre:";
    getline(cin, genre);
    normalizeName(genre);

    cout << "Enter year of release:";
    cin >> yearOfRelease;
    clearBuffer();

    cout << "Enter new number of likes:";
    cin >> numberOfLikes;
    clearBuffer();

    cout << "Enter trailer:";
    getline(cin, trailer);
    cout<<"\n";
    try{services->addMovie(title, genre, yearOfRelease, numberOfLikes, trailer);}
    catch (MovieServiceException& error){cout << error.message();}
}

void MovieUI::removeMovie() {
    string title;
    cout << "Enter the title of the movie to remove:";
    getline(cin, title);
    normalizeName(title);
    try{services->removeMovie(title);}
    catch (MovieServiceException& error){cout << error.message();}
}

void MovieUI::updateMovie() {
    string title, genre, trailer;
    int yearOfRelease, numberOfLikes;

    cout << "Enter title:";
    getline(cin, title);
    normalizeName(title);

    cout << "Enter new genre:";
    getline(cin, genre);
    normalizeName(genre);

    cout << "Enter new year of release:";
    cin >> yearOfRelease;
    clearBuffer();

    cout << "Enter new number of likes:";
    cin >> numberOfLikes;
    clearBuffer();

    cout << "Enter new trailer:";
    getline(cin, trailer);
    cout<<"\n";
    try{services->updateMovie(title, genre, yearOfRelease, numberOfLikes, trailer);}
    catch (MovieServiceException& error){cout << error.message();}
}

void MovieUI::printAllMovies() const {
    auto* movies = services->getAllMovies();
    if (movies->getLength() == 0) {
        cout << "No movies in the repository.\n";
    } else {
        cout << "All Movies:\n";
        for (int i = 0; i < movies->getLength(); ++i) {
            cout << (i + 1) << ")";
            cout<<movies->getElements()[i].toString();
            cout << endl;
        }
    }
}

void MovieUI::printWatchlist() const {
    auto movies = services->getWatchlist();

    if (movies->getLength() == 0) {
        cout << "No movies in watchlist.\n";
    } else {
        string file = "movie_watchlist";
        movies->writeToUserFile(file);

        cout << "Watchlist:\n";
        for (auto i = 0; i < movies->getLength(); ++i) {
            cout << (i + 1) << ")";
            cout<<movies->getElements()[i].toString();
            cout << endl;
        }
    }
}

void MovieUI::deleteMovie(){
    string title;
    cout << "Title of the movie to delete from watchlist:";
    getline(cin, title);
    normalizeName(title);
    try{
        services->deleteMovie(title);
        cout<<"Did you enjoy the movie?(Y/N)\n";
        string yesno;
        getline(cin, yesno);
        normalizeName(yesno);
        if (yesno == "Y" || yesno == "Yes")
            services->addLike(title);
    }
    catch (MovieServiceException& error){cout << error.message();}
}